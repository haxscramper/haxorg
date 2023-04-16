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
