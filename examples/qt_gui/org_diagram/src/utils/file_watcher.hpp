#include <QObject>
#include <QThread>
#include <QFileInfo>
#include <QTimer>
#include <sys/inotify.h>
#include <unistd.h>
#include <QSocketNotifier>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>

struct FileChangeEvent {
    DECL_DESCRIBED_ENUM(
        Type,
        Modified,
        Created,
        Deleted,
        MovedFrom,
        MovedTo,
        Accessed,
        AttributeChanged);

    QString  path;
    Type     type;
    uint32_t cookie;
    bool     isDirectory;
    qint64   timestamp;
    DESC_FIELDS(
        FileChangeEvent,
        (path, type, cookie, isDirectory, timestamp));
};

class InotifyFileWatcher : public QObject {
    Q_OBJECT

  public:
    explicit InotifyFileWatcher(QObject* parent = nullptr);

    ~InotifyFileWatcher() {
        if (inotifyFd != -1) { close(inotifyFd); }
    }

    bool addPath(QString const& path);

    void removePath(QString const& path);

  signals:
    void fileChanged(FileChangeEvent const& event);

  private slots:
    void handleInotifyEvent();

  private:
    int                 inotifyFd      = -1;
    QSocketNotifier*    socketNotifier = nullptr;
    QHash<int, QString> watchDescriptors;
};

class FileWatcherThread : public QThread {
    Q_OBJECT

  public:
    FileWatcherThread(QObject* parent = nullptr) : QThread(parent) {}

    void addWatchPath(QString const& path);

    void removeWatchPath(QString const& path);

  signals:
    void fileChanged(FileChangeEvent const& event);

  protected:
    void run() override;

  private:
    InotifyFileWatcher* watcher = nullptr;
};
