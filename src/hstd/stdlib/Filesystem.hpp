#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <hstd/stdlib/Ptrs.hpp>
#include <format>

namespace fs = std::filesystem;

#define __CURRENT_FILE_PATH__ fs::path(__FILE__)
#define __CURRENT_FILE_DIR__ fs::path(__FILE__).parent_path()

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


void        writeFile(fs::path const& target, std::string const& content);
std::string readFile(fs::path const& target);

template <>
struct std::formatter<fs::path> : std::formatter<std::string> {
    using FmtType = fs::path;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(p.native(), ctx);
    }
};
