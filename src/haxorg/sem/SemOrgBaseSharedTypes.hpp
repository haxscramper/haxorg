#pragma once
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

    [[refl]] std::string getJsonString() const;
    [[refl(R"({"unique-name": "atIndex"})")]] OrgJson at(int idx) const;
    [[refl(R"({"unique-name": "atField"})")]] OrgJson at(
        std::string const& name) const;
    [[refl]] std::string        getString() const;
    [[refl]] OrgJson            getField(std::string const& name) const;
    [[refl]] OrgJson            getItem(int index) const;
    [[refl]] int                getInt() const;
    [[refl]] bool               getBool() const;
    [[refl]] hstd::Vec<OrgJson> getArray() const;
    [[refl]] std::string        dump(int indent) const;
};
} // namespace org::sem

// Explicitly instantiating the formatters for large enums can save up to
// several minutes of the build time. Token kind takes 17s to instantiate
// and used at least 15 times, OrgSemKind and OrgNodeKind both take around
// 800-900ms and are instantiated in about 20 translation units.


// clang-format off

namespace hstd {
using back_inserter_string_format_context = std::basic_format_context<std::back_insert_iterator<std::basic_string<char>>, char>;
}

template <>
struct std::formatter<OrgTokenKind> : std::formatter<std::string> {
    std::format_context::iterator format(OrgTokenKind const&, std::format_context&) const;
    hstd::back_inserter_string_format_context::iterator format(OrgTokenKind const&, hstd::back_inserter_string_format_context&) const;
};

template <>
struct std::formatter<OrgSemKind> : std::formatter<std::string> {
    std::format_context::iterator format(OrgSemKind const&, std::format_context&) const;
    hstd::back_inserter_string_format_context::iterator format(OrgSemKind const&, hstd::back_inserter_string_format_context&) const;
};

template <>
struct std::formatter<OrgNodeKind> : std::formatter<std::string> {
    std::format_context::iterator format(OrgNodeKind const&, std::format_context&) const;
    hstd::back_inserter_string_format_context::iterator format(OrgNodeKind const&, hstd::back_inserter_string_format_context&) const;
};
// clang-format on
