#include <hstd/stdlib/Filesystem.hpp>
#include <fstream>
#include <sstream>

using namespace hstd;

void hstd::writeFile(const fs::path& target, const std::string& content) {
    std::ofstream file{target.native()};
    // REFACTOR truncate file on write
    // REFACTOR add error message on write failure
    if (file.is_open()) {
        file << content;
    } else {
        throw FilesystemError::init(
            "Could not write to file '" + target.native());
    }
}

std::string hstd::readFile(const fs::path& target) {
    std::ifstream in{target.native()};
    if (in.is_open()) {
        std::stringstream result;
        result << in.rdbuf();
        return result.str();
    } else {
        throw FilesystemError::init(
            "Could not open file '" + target.native() + "'");
    }
}

void hstd::writeFileOrStdout(
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

void hstd::writeDebugFile(
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
}

void hstd::createDirectory(
    const fs::path& target,
    bool            parents,
    bool            existsOk) {
    if (target.native().empty()) {
        throw FilesystemError::init(
            fmt("Cannot create directory, target is empty"));
    }

    if (fs::is_regular_file(target)) {
        throw FilesystemError::init(
            fmt("Cannot create directory {} -- the file with this name "
                "already exists",
                target));
    }

    if (fs::is_directory(target) && !existsOk) {
        throw FilesystemError::init(
            fmt("Cannot create directory {} -- the path already exists",
                target));
    }

    if (!fs::is_directory(target.parent_path()) && !parents) {
        throw FilesystemError::init(
            fmt("Cannot create directory {} -- parent path does not exist",
                target));
    }

    std::function<void(fs::path const& target)> aux;
    aux = [&](fs::path const& target) {
        // apparently `/` root directory has parent path according to this
        // code, so the `!=` thing is the only one that worked.
        if (target.parent_path() != target) {
            aux(target.parent_path());
            if (fs::is_directory(target.parent_path())) {
                fs::create_directory(target);
            }
        }
    };
    aux(target);
}
