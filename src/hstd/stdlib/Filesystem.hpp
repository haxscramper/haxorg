#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <hstd/stdlib/Ptrs.hpp>
#include <format>

namespace hstd {

namespace fs = std::filesystem;

#define __CURRENT_FILE_PATH__ ::hstd::fs::path(__FILE__)
#define __CURRENT_FILE_DIR__ ::htsd::fs::path(__FILE__).parent_path()

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

void writeFile(fs::path const& target, std::string const& content);
void createDirectory(
    fs::path const& target,
    bool            parents  = true,
    bool            existsOk = true);

void writeDebugFile(
    std::string const& content,
    std::string const& extension,
    bool               writeLog    = false,
    std::string const& stem_suffix = "",
    int                line        = __builtin_LINE(),
    char const*        function    = __builtin_FUNCTION(),
    char const*        file        = __builtin_FILE());


std::string readFile(fs::path const& target);


} // namespace hstd


template <>
struct std::formatter<hstd::fs::path> : std::formatter<std::string> {
    using FmtType = hstd::fs::path;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(p.native(), ctx);
    }
};
