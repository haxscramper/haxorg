#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrgSharedTypes.hpp>
#include <hstd/stdlib/Ptrs.hpp>

namespace org {
std::string fieldname_to_code(std::string_view str);
} // namespace org

namespace org::parse {


struct OrgNodeMono {
    struct None {
        DESC_FIELDS(None, ());
    };

    struct Error {
        struct Box {
            struct ParseFail {
                sem::OrgDiagnostics::ParseError err;
                DESC_FIELDS(ParseFail, (err));
            };

            struct ParseTokenFail {
                sem::OrgDiagnostics::ParseTokenError err;
                DESC_FIELDS(ParseTokenFail, (err));
            };

            SUB_VARIANTS(
                Kind,
                Data,
                data,
                getKind,
                ParseFail,
                ParseTokenFail);
            Data data;
            DESC_FIELDS(Box, (data));
        };

        hstd::SPtr<Box> box;
        DESC_FIELDS(Error, (box));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, None, Error);
    Data data;
    DESC_FIELDS(OrgNodeMono, (data));
};

using OrgSet = hstd::IntSet<OrgNodeKind>;


} // namespace org::parse
