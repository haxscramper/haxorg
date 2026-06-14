#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/system/exceptions.hpp>

namespace hstd {

namespace fs = std::filesystem;

#define __CURRENT_FILE_PATH__ ::hstd::fs::path(__FILE__)
#define __CURRENT_FILE_DIR__ ::hstd::fs::path(__FILE__).parent_path()

struct FilesystemError : public CRTP_hexception<FilesystemError> {};

void writeFileOrStdout(
    fs::path const&    target,
    std::string const& content,
    bool               useFile,
    bool               useStdoutStream = true);

struct IoContext {
    fs::path           file;
    SPtr<std::ostream> stream;
};

void writeFile(fs::path const& target, std::string const& content);
void createDirectory(fs::path const& target, bool parents = true, bool existsOk = true);

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
struct fmt::formatter<hstd::fs::path> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }

    hstd::fmt_iter format(hstd::fs::path const& p, fmt::format_context& ctx) const {
        return hstd::fmt_ctx(p.native(), ctx);
    }
};
