#pragma once
#include "hstd/stdlib/Formatter.hpp"
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/system/basic_typedefs.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Map.hpp>
#include <haxorg/lexbase/SourceManager.hpp>

namespace org::sem {
struct [[refl]] OrgJson {
    mutable std::shared_ptr<json> value;
    bool                          holds_value;

    DESC_FIELDS(OrgJson, ());

    [[refl]] OrgJsonKind getKind() const;

    OrgJson(json const* ptr);
    OrgJson(json const& copy);
    OrgJson() : holds_value{false} {}

    bool operator==(OrgJson const& other) const;

    bool isPtr() const;

    json*       getPtr() const;
    json const& getValue() const;
    json const& getRef() const;

    [[refl]] std::string                              getJsonString() const;
    [[refl(R"({"unique-name": "atIndex"})")]] OrgJson at(int idx) const;
    [[refl(R"({"unique-name": "atField"})")]] OrgJson at(std::string const& name) const;
    [[refl]] std::string                              getString() const;
    [[refl]] OrgJson            getField(std::string const& name) const;
    [[refl]] OrgJson            getItem(int index) const;
    [[refl]] int                getInt() const;
    [[refl]] bool               getBool() const;
    [[refl]] hstd::Vec<OrgJson> getArray() const;
    [[refl]] std::string        dump(int indent) const;
};

namespace detail {
std::string format_enum_value(OrgSemKind kind);
std::string format_enum_value(OrgTokenKind kind);
std::string format_enum_value(OrgNodeKind kind);
} // namespace detail

} // namespace org::sem

// Explicitly instantiating the formatters for large enums can save up to
// several minutes of the build time. Token kind takes 17s to instantiate
// and used at least 15 times, OrgSemKind and OrgNodeKind both take around
// 800-900ms and are instantiated in about 20 translation units.


namespace hstd {
using back_inserter_string_format_context = std::
    basic_format_context<std::back_insert_iterator<std::basic_string<char>>, char>;
}


template <>
struct fmt::formatter<OrgTokenKind> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(OrgTokenKind const& value, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx(org::sem::detail::format_enum_value(value), ctx);
    }
};

template <>
struct fmt::formatter<OrgSemKind> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(OrgSemKind const& value, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx(org::sem::detail::format_enum_value(value), ctx);
    }
};

template <>
struct fmt::formatter<OrgNodeKind> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    auto           format(OrgNodeKind const& value, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx(org::sem::detail::format_enum_value(value), ctx);
    }
};
