#include <hstd/stdlib/Filesystem.hpp>

void writeFile(const QFileInfo& target, const QString& content) {
    QFile file;
    file.setFileName(target.filePath());
    if (file.open(QIODevice::WriteOnly | QFile::Truncate)) {
        QTextStream stream{&file};
        stream << content;
        file.close();
    } else {
        throw FilesystemError(
            "Could not write to file '" + target.filePath()
            + "': " + file.errorString());
    }
}

QString readFile(const QFileInfo& target) {
    QFile file;
    file.setFileName(target.filePath());
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream{&file};
        QString     result = stream.readAll();
        file.close();
        return result;
    } else {
        throw FilesystemError(
            "Could not open file '" + target.filePath()
            + "': " + file.errorString());
    }
}

void writeFileOrStdout(
    const QFileInfo& target,
    const QString&   content,
    bool             useFile,
    bool             useStdoutStream) {
    if (useFile) {
        writeFile(target, content);

    } else {
        QFile file;
        file.open(useStdoutStream ? stdout : stderr, QIODevice::WriteOnly);
        QTextStream stream{&file};
        stream << content;
    }
}


SPtr<IoContext> openFileOrStream(
    const QFileInfo& info,
    bool             useFile,
    IoOpenConf       conf) {


    SPtr<IoContext> context = std::make_shared<IoContext>();
    context->stream         = std::make_shared<QTextStream>();
    if (useFile) {
        if (conf.createDirs) {
            if (!info.dir().exists()) {
                info.dir().mkpath(info.dir().absolutePath());
            }
        }

        QIODevice::OpenMode mode;
        if (conf.enableRead) {
            mode |= QIODevice::ReadOnly;
        }

        if (conf.enableWrite) {
            mode |= QIODevice::WriteOnly;
            if (conf.truncateWrite) {
                mode |= QIODevice::Truncate;
            }
        }

        Q_ASSERT_X(
            !info.filePath().isEmpty(),
            "open file name",
            "cannot open empty file name -- was provided with zero "
            "length");
        context->file.setFileName(info.filePath());
        if (context->file.open(mode)) {
            context->stream->setDevice(&context->file);
            context->needClose = true;
        } else {
            throw FilesystemError(
                "Could not open file '" + info.filePath()
                + "': " + context->file.errorString());
        }
    } else {
        context->file.open(
            conf.useStdout ? stdout : stderr, QIODevice::WriteOnly);
        context->stream->setDevice(&context->file);
    }

    return context;
}


QTextStream& operator<<(QTextStream& stream, QFileInfo const& info) {
    stream << '"' << info.filePath() << '"';
    return stream;
}
