#pragma once
#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Filesystem.hpp>

namespace org {

struct ParseParams {
    SPtr<std::ostream> lexBaseTrace      = nullptr;
    int                lexBaseMaxUnknown = 0;

    ParseParams& withLexBaseTrace(CR<fs::path> file);
};

sem::SemId<sem::Document> parseString(
    CR<std::string> text,
    CR<ParseParams> params = ParseParams{});
} // namespace org
