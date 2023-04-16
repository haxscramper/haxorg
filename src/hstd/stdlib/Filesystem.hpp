#pragma once

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDir>
#include <QFileInfo>

#define __CURRENT_FILE_PATH__ QFileInfo(__FILE__)
#define __CURRENT_FILE_DIR__ QFileInfo(__FILE__).dir()

struct FilesystemError : public std::runtime_error {
    explicit FilesystemError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};

inline QString operator/(QDir const& lhs, QString const& rhs) {
    return QDir::cleanPath(lhs.path() + QDir::separator() + rhs);
}


void writeFile(QFileInfo const& target, QString const& content);

QString readFile(QFileInfo const& target);
