#include <hstd/stdlib/Filesystem.hpp>
#include <fstream>
#include <absl/log/check.h>
#include <sstream>
#include <absl/log/log.h>

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
        std::stringstream result;
        result << in.rdbuf();
        return result.str();
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

void writeDebugFile(
    const std::string& content,
    const std::string& extension,
    bool               writeLog,
    const std::string& stem_suffix,
    int                line,
    const char*        function,
    const char*        file) {
    auto        filename  = fs::path{file}.stem();
    std::string full_path = fmt(
        "/tmp/{}_{}{}.{}", filename, function, stem_suffix, extension);

    writeFile(full_path, content);
    if (writeLog) {
        LOG(INFO) << fmt(
            "{}:{}:{} wrote to {}", filename, function, line, full_path);
    }
}

void createDirectory(const fs::path& target, bool parents, bool existsOk) {
    if (target.native().empty()) {
        throw FilesystemError{
            fmt("Cannot create directory, target is empty")};
    }

    if (fs::is_regular_file(target)) {
        throw FilesystemError(
            fmt("Cannot create directory {} -- the file with this name "
                "already exists",
                target));
    }

    if (fs::is_directory(target) && !existsOk) {
        throw FilesystemError(
            fmt("Cannot create directory {} -- the path already exists",
                target));
    }

    if (!fs::is_directory(target.parent_path()) && !parents) {
        throw FilesystemError(
            fmt("Cannot create directory {} -- parent path does not exist",
                target));
    }

    std::function<void(fs::path const& target)> aux;
    aux = [&](fs::path const& target) {
        if (fs::is_directory(target.parent_path())) {
            fs::create_directory(target);
        } else {
            aux(target.parent_path());
        }
    };
    aux(target);
}
