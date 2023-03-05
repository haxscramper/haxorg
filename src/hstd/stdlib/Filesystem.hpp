#pragma once

#include <filesystem>
#include <QFile>
#include <QTextStream>
#include <QString>

namespace fs = std::filesystem;

#define __CURRENT_FILE_PATH__ fs::path(__FILE__)
#define __CURRENT_FILE_DIR__ fs::path(__FILE__).parent_path()

struct FilesystemError : public std::runtime_error {
    explicit FilesystemError(const QString& message)
        : std::runtime_error(message.toStdString()) {}
};


inline void writeFile(fs::path const& target, QString const& content) {
    QFile file;
    file.setFileName(QString::fromStdString(target.native()));
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream{&file};
        stream << content;
        file.close();
    } else {
        throw FilesystemError(
            "Could not write to file "
            + QString::fromStdString(target.native()));
    }
}
