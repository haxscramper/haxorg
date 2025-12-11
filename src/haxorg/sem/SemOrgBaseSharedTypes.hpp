#pragma once
#pragma clang diagnostic ignored "-Wunknown-attributes"

#include <hstd/system/basic_typedefs.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>

#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Opt.hpp>

#include <hstd/system/Formatter.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Json.hpp>

namespace org::sem {
struct [[refl]] OrgJson {
    mutable hstd::Variant<json, json*> value;

    DESC_FIELDS(OrgJson, ());

    [[refl]] OrgJsonKind getKind() const {
        using K = OrgJsonKind;
        switch (getRef().type()) {
            case json::value_t::null: return K::Null;
            case json::value_t::object: return K::Object;
            case json::value_t::array: return K::Array;
            case json::value_t::string: return K::String;
            case json::value_t::boolean: return K::Boolean;
            case json::value_t::number_integer: return K::Int;
            case json::value_t::number_float: return K::Float;
            case json::value_t::number_unsigned: return K::Int;
            case json::value_t::discarded: return K::Null;
            case json::value_t::binary: return K::String;
        }
    }

    OrgJson(json const* ptr) : value{const_cast<json*>(ptr)} {}
    OrgJson(json const& copy) : value{copy} {}
    OrgJson() {}

    bool operator==(OrgJson const& other) const {
        return getRef() == other.getRef();
    }

    bool isPtr() const { return std::holds_alternative<json*>(value); }

    json*       getPtr() const { return std::get<json*>(value); }
    json const& getValue() const { return std::get<json>(value); }

    json const& getRef() const {
        if (isPtr()) {
            return *getPtr();
        } else {
            return getValue();
        }
    }

    [[refl]] std::string getJsonString() const { return getRef().dump(); }
    [[refl(R"({"unique-name": "atIndex"})")]] OrgJson at(int idx) const {
        return &getRef().at(idx);
    }
    [[refl(R"({"unique-name": "atField"})")]] OrgJson at(
        std::string const& name) const {
        return &getRef().at(name);
    }
    [[refl]] std::string getString() const {
        return getRef().get<std::string>();
    }

    [[refl]] OrgJson getField(std::string const& name) const {
        return getRef().at(name);
    }

    [[refl]] OrgJson getItem(int index) const {
        return getRef().at(index);
    }

    [[refl]] int  getInt() const { return getRef().get<int>(); }
    [[refl]] bool getBool() const { return getRef().get<bool>(); }
    [[refl]] hstd::Vec<OrgJson> getArray() const {
        hstd::Vec<OrgJson> result;
        for (auto const& sub : getRef()) { result.push_back(&sub); }
        return result;
    }
};
} // namespace org::sem


template <>
struct std::formatter<OrgTokenKind> : std::formatter<std::string> {
    std::format_context::iterator format(
        OrgTokenKind const&,
        std::format_context&) const;
};
