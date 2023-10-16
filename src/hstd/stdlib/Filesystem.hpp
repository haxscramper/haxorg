#pragma once

#include <QFile>
#include <iostream>
#include <string>
#include <filesystem>
#include <filesystem>
#include <hstd/stdlib/Ptrs.hpp>

#define __CURRENT_FILE_PATH__ QFileInfo(__FILE__)
#define __CURRENT_FILE_DIR__ QFileInfo(__FILE__).dir()

struct FilesystemError : public std::runtime_error {
    explicit FilesystemError(const std::string& message)
        : std::runtime_error(message.toStdString()) {}
};

inline std::string operator/(QDir const& lhs, std::string const& rhs) {
    return QDir::cleanPath(lhs.path() + QDir::separator() + rhs);
}


void writeFileOrStdout(
    const QFileInfo& target,
    const std::string&   content,
    bool             useFile,
    bool             useStdoutStream = true);

struct IoContext {
    QFile             file;
    SPtr<std::ostream> stream;

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

void         writeFile(QFileInfo const& target, std::string const& content);
std::string      readFile(QFileInfo const& target);
std::ostream& operator<<(std::ostream& stream, QFileInfo const& info);
