module hstd.stdlib.Filesystem;
import std;
import std;
import std;


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


