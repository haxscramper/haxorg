#pragma once

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <hstd/stdlib/Ptrs.hpp>

#define __CURRENT_FILE_PATH__ QFileInfo(__FILE__)
#define __CURRENT_FILE_DIR__ QFileInfo(__FILE__).dir()

struct FilesystemError : public std::runtime_error {
    explicit FilesystemError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};

inline QString operator/(QDir const& lhs, QString const& rhs) {
    return QDir::cleanPath(lhs.path() + QDir::separator() + rhs);
}


void writeFileOrStdout(
    const QFileInfo& target,
    const QString&   content,
    bool             useFile,
    bool             useStdoutStream = true);

struct IoContext {
    QFile             file;
    SPtr<QTextStream> stream;

    bool needClose = false;


    ~IoContext() {
        if (needClose) {
            file.close();
        }
    }
};

struct IoOpenConf {
    bool enableRead    = false;
    bool enableWrite   = true;
    bool createDirs    = false;
    bool useStdout     = false;
    bool truncateWrite = true;
};

SPtr<IoContext> openFileOrStream(
    QFileInfo const& info,
    bool             useFile,
    IoOpenConf       conf = {});

void         writeFile(QFileInfo const& target, QString const& content);
QString      readFile(QFileInfo const& target);
QTextStream& operator<<(QTextStream& stream, QFileInfo const& info);
