#include <hstd/stdlib/Filesystem.hpp>
#include <fstream>
#include <absl/log/check.h>

void writeFile(const fs::path& target, const std::string& content) {
    std::ofstream file{target.native()};
    // REFACTOR truncate file on write
    // REFACTOR add error message on write failure
    if (file.is_open()) {
        file << content;
    } else {
        throw FilesystemError(
            "Could not write to file '" + target.native());
    }
}

std::string readFile(const fs::path& target) {
    std::ifstream in{target.native()};
    if (in.is_open()) {
        std::string result;
        in >> result;
        return result;
    } else {
        throw FilesystemError(
            "Could not open file '" + target.native() + "'");
    }
}

void writeFileOrStdout(
    const fs::path&    target,
    const std::string& content,
    bool               useFile,
    bool               useStdoutStream) {
    if (useFile) {
        writeFile(target, content);

    } else {
        std::cout << content;
    }
}


SPtr<IoContext> openFileOrStream(
    const fs::path& info,
    bool            useFile,
    IoOpenConf      conf) {

    SPtr<IoContext> context = std::make_shared<IoContext>();
    context->stream         = std::make_shared<std::ostream>();
    if (useFile) {
        if (conf.createDirs) {
            if (!fs::exists(info.parent_path())) {
                fs::create_directories(info.parent_path());
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

        CHECK(!info.native().empty())
            << "open file name"
            << "cannot open empty file name -- was provided with zero "
               "length";

        context->file.setFileName(info.filePath());
        if (context->file.open(mode)) {
            context->stream->setDevice(&context->file);
            context->needClose = true;
        } else {
            throw FilesystemError(
                "Could not open file '" + info.native()
                + "': " + context->file.errorString());
        }
    } else {
        context->file.open(
            conf.useStdout ? stdout : stderr, QIODevice::WriteOnly);
        context->stream->setDevice(&context->file);
    }

    return context;
}


