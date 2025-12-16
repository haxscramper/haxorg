#include <haxorg/sem/SemOrgBaseSharedTypes.hpp>
#include <hstd/stdlib/JsonUse.hpp>

// clang-format off
std::format_context::iterator std::formatter<OrgTokenKind>::format(OrgTokenKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}

std::format_context::iterator std::formatter<OrgSemKind>::format(OrgSemKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
}

std::format_context::iterator std::formatter<OrgNodeKind>::format(OrgNodeKind const& p, std::format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgNodeKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgTokenKind>::format(OrgTokenKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgSemKind>::format(OrgSemKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
}

hstd::back_inserter_string_format_context::iterator std::formatter<OrgNodeKind>::format(OrgNodeKind const& p, hstd::back_inserter_string_format_context& ctx) const {
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgNodeKind>::to_string(p), ctx);
}
// clang-format on


OrgJsonKind org::sem::OrgJson::getKind() const {
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

org::sem::OrgJson::OrgJson(const json* ptr)
    : value{std::shared_ptr<json>(const_cast<json*>(ptr), [](json* p) {})}
    , holds_value{false} {}

org::sem::OrgJson::OrgJson(const json& copy)
    : value{std::make_shared<json>(copy)}, holds_value{true} {}

bool org::sem::OrgJson::operator==(const OrgJson& other) const {
    return getRef() == other.getRef();
}

bool org::sem::OrgJson::isPtr() const { return !holds_value; }

json* org::sem::OrgJson::getPtr() const { return value.get(); }

const json& org::sem::OrgJson::getValue() const { return *value; }

const json& org::sem::OrgJson::getRef() const {
    if (isPtr()) {
        return *getPtr();
    } else {
        return getValue();
    }
}

std::string org::sem::OrgJson::getJsonString() const {
    return getRef().dump();
}

std::string org::sem::OrgJson::getString() const {
    return getRef().get<std::string>();
}

int org::sem::OrgJson::getInt() const { return getRef().get<int>(); }

bool org::sem::OrgJson::getBool() const { return getRef().get<bool>(); }

std::string org::sem::OrgJson::dump(int indent) const {
    return getRef().dump(indent);
}

hstd::Vec<org::sem::OrgJson> org::sem::OrgJson::getArray() const {
    hstd::Vec<OrgJson> result;
    for (auto const& sub : getRef()) { result.push_back(&sub); }
    return result;
}

org::sem::OrgJson org::sem::OrgJson::getItem(int index) const {
    return getRef().at(index);
}

org::sem::OrgJson org::sem::OrgJson::getField(
    const std::string& name) const {
    return getRef().at(name);
}

org::sem::OrgJson org::sem::OrgJson::at(const std::string& name) const {
    return &getRef().at(name);
}

org::sem::OrgJson org::sem::OrgJson::at(int idx) const {
    return &getRef().at(idx);
}
