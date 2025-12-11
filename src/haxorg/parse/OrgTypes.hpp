#pragma once

#include <hstd/stdlib/dod_base.hpp>
#include <hstd/system/reflection.hpp>
#include <haxorg/sem/SemOrgSharedTypes.hpp>
#include <hstd/stdlib/Ptrs.hpp>


template <>
struct std::formatter<OrgSpecName> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        OrgSpecName const& p,
        FormatContext&     ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(
            hstd::enum_serde<OrgSpecName>::to_string(p), ctx);
    }
};

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


template <>
struct std::formatter<org::parse::OrgNodeMono::Error>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::parse::OrgNodeMono::Error& p,
        FormatContext&                        ctx) const {
        if (p.box) {
            return hstd::fmt_ctx(*p.box, ctx);
        } else {
            return hstd::fmt_ctx("Error{}", ctx);
        }
    }
};
