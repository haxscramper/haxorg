#include "file_watcher.hpp"

InotifyFileWatcher::InotifyFileWatcher(QObject* parent) : QObject(parent) {
    inotifyFd = inotify_init1(IN_CLOEXEC | IN_NONBLOCK);
    if (inotifyFd == -1) { return; }

    socketNotifier = new QSocketNotifier(
        inotifyFd, QSocketNotifier::Read, this);
    connect(
        socketNotifier,
        &QSocketNotifier::activated,
        this,
        &InotifyFileWatcher::handleInotifyEvent);
}

bool InotifyFileWatcher::addPath(const QString& path) {
    if (inotifyFd == -1) { return false; }

    uint32_t mask = IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVE | IN_ATTRIB
                  | IN_ACCESS;

    QFileInfo info{path};
    if (info.isDir()) { mask |= IN_ONLYDIR; }

    int wd = inotify_add_watch(
        inotifyFd, path.toLocal8Bit().constData(), mask);
    if (wd == -1) { return false; }

    watchDescriptors.insert(wd, path);
    return true;
}

void InotifyFileWatcher::removePath(const QString& path) {
    for (auto it = watchDescriptors.begin(); it != watchDescriptors.end();
         ++it) {
        if (it.value() == path) {
            inotify_rm_watch(inotifyFd, it.key());
            watchDescriptors.erase(it);
            break;
        }
    }
}

void InotifyFileWatcher::handleInotifyEvent() {
    char    buffer[4096];
    ssize_t length = read(inotifyFd, buffer, sizeof(buffer));

    if (length <= 0) { return; }

    int i = 0;
    while (i < length) {
        inotify_event* event = reinterpret_cast<inotify_event*>(
            &buffer[i]);

        if (watchDescriptors.contains(event->wd)) {
            QString basePath = watchDescriptors.value(event->wd);
            QString fullPath = basePath;

            if (event->len > 0) {
                fullPath = basePath + "/"
                         + QString::fromLocal8Bit(event->name);
            }

            FileChangeEvent changeEvent;
            changeEvent.path        = fullPath;
            changeEvent.cookie      = event->cookie;
            changeEvent.isDirectory = event->mask & IN_ISDIR;
            changeEvent.timestamp   = QDateTime::currentMSecsSinceEpoch();

            if (event->mask & IN_MODIFY) {
                changeEvent.type = FileChangeEvent::Type::Modified;
            } else if (event->mask & IN_CREATE) {
                changeEvent.type = FileChangeEvent::Type::Created;
            } else if (event->mask & IN_DELETE) {
                changeEvent.type = FileChangeEvent::Type::Deleted;
            } else if (event->mask & IN_MOVED_FROM) {
                changeEvent.type = FileChangeEvent::Type::MovedFrom;
            } else if (event->mask & IN_MOVED_TO) {
                changeEvent.type = FileChangeEvent::Type::MovedTo;
            } else if (event->mask & IN_ACCESS) {
                changeEvent.type = FileChangeEvent::Type::Accessed;
            } else if (event->mask & IN_ATTRIB) {
                changeEvent.type = FileChangeEvent::Type::AttributeChanged;
            }

            emit fileChanged(changeEvent);
        }

        i += sizeof(inotify_event) + event->len;
    }
}

void FileWatcherThread::addWatchPath(const QString& path) {
    QMetaObject::invokeMethod(
        this,
        [this, path]() {
            if (!watcher) {
                watcher = new InotifyFileWatcher{};
                connect(
                    watcher,
                    &InotifyFileWatcher::fileChanged,
                    this,
                    &FileWatcherThread::fileChanged);
            }
            watcher->addPath(path);
        },
        Qt::QueuedConnection);
}

void FileWatcherThread::removeWatchPath(const QString& path) {
    QMetaObject::invokeMethod(
        this,
        [this, path]() {
            if (watcher) { watcher->removePath(path); }
        },
        Qt::QueuedConnection);
}

void FileWatcherThread::run() {
    watcher = new InotifyFileWatcher{};
    connect(
        watcher,
        &InotifyFileWatcher::fileChanged,
        this,
        &FileWatcherThread::fileChanged);
    exec();
    delete watcher;
    watcher = nullptr;
}
