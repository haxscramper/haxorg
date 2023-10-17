#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <hstd/stdlib/Ptrs.hpp>
#include <format>

namespace fs = std::filesystem;

#define __CURRENT_FILE_PATH__ QFileInfo(__FILE__)
#define __CURRENT_FILE_DIR__ QFileInfo(__FILE__).dir()

struct FilesystemError : public std::runtime_error {
    explicit FilesystemError(const std::string& message)
        : std::runtime_error(message) {}
};

void writeFileOrStdout(
    const fs::path&    target,
    const std::string& content,
    bool               useFile,
    bool               useStdoutStream = true);

struct IoContext {
    fs::path           file;
    SPtr<std::ostream> stream;
};

struct IoOpenConf {
    bool enableRead    = false;
    bool enableWrite   = true;
    bool createDirs    = false;
    bool useStdout     = false;
    bool truncateWrite = true;
};

SPtr<IoContext> openFileOrStream(
    fs::path const& info,
    bool            useFile,
    IoOpenConf      conf = {});

void        writeFile(fs::path const& target, std::string const& content);
std::string readFile(fs::path const& target);
std::ostream& operator<<(std::ostream& stream, fs::path const& info);

template <>
struct std::formatter<fs::path> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) {
        return std::formatter<std::string>::format(p.native(), ctx);
    }
};
