#include <haxorg/sem/SemOrgBaseSharedTypes.hpp>
#include <hstd/stdlib/JsonUse.hpp>

// clang-format off
template <class FormatContext>
auto std::formatter<OrgTokenKind>::format(OrgTokenKind const& p, FormatContext& ctx) const
    -> typename FormatContext::iterator
{
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgTokenKind>::to_string(p), ctx);
}

template <class FormatContext>
auto std::formatter<OrgSemKind>::format(OrgSemKind const& p, FormatContext& ctx) const
    -> typename FormatContext::iterator
{
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
}

template <class FormatContext>
auto std::formatter<OrgNodeKind>::format(OrgNodeKind const& p, FormatContext& ctx) const
    -> typename FormatContext::iterator
{
    return std::formatter<std::string>{}.format(hstd::enum_serde<OrgNodeKind>::to_string(p), ctx);
}

template
    auto std::formatter<OrgTokenKind>::format<std::format_context>(OrgTokenKind const&, std::format_context&) const
    -> std::format_context::iterator;

template
    auto std::formatter<OrgTokenKind>::format<hstd::back_inserter_string_format_context>(
        OrgTokenKind const&, hstd::back_inserter_string_format_context&) const
    -> hstd::back_inserter_string_format_context::iterator;

template
    auto std::formatter<OrgTokenKind>::format<std::basic_format_context<std::__format::_Drop_iter<char>, char>>(
        OrgTokenKind const&, std::basic_format_context<std::__format::_Drop_iter<char>, char>&) const
    -> std::basic_format_context<std::__format::_Drop_iter<char>, char>::iterator;


template
    auto std::formatter<OrgSemKind>::format<std::format_context>(OrgSemKind const&, std::format_context&) const
    -> std::format_context::iterator;

template
    auto std::formatter<OrgSemKind>::format<hstd::back_inserter_string_format_context>(
        OrgSemKind const&, hstd::back_inserter_string_format_context&) const
    -> hstd::back_inserter_string_format_context::iterator;

template
    auto std::formatter<OrgSemKind>::format<std::basic_format_context<std::__format::_Drop_iter<char>, char>>(
        OrgSemKind const&, std::basic_format_context<std::__format::_Drop_iter<char>, char>&) const
    -> std::basic_format_context<std::__format::_Drop_iter<char>, char>::iterator;


template
    auto std::formatter<OrgNodeKind>::format<std::format_context>(OrgNodeKind const&, std::format_context&) const
    -> std::format_context::iterator;

template
    auto std::formatter<OrgNodeKind>::format<hstd::back_inserter_string_format_context>(
        OrgNodeKind const&, hstd::back_inserter_string_format_context&) const
    -> hstd::back_inserter_string_format_context::iterator;

template
    auto std::formatter<OrgNodeKind>::format<std::basic_format_context<std::__format::_Drop_iter<char>, char>>(
        OrgNodeKind const&, std::basic_format_context<std::__format::_Drop_iter<char>, char>&) const
    -> std::basic_format_context<std::__format::_Drop_iter<char>, char>::iterator;
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

org::sem::OrgJson::OrgJson(json const* ptr)
    : value{std::shared_ptr<json>(const_cast<json*>(ptr), [](json* p) {})}
    , holds_value{false} {}

org::sem::OrgJson::OrgJson(json const& copy)
    : value{std::make_shared<json>(copy)}, holds_value{true} {}

bool org::sem::OrgJson::operator==(OrgJson const& other) const {
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

std::string org::sem::OrgJson::getJsonString() const { return getRef().dump(); }

std::string org::sem::OrgJson::getString() const { return getRef().get<std::string>(); }

int org::sem::OrgJson::getInt() const { return getRef().get<int>(); }

bool org::sem::OrgJson::getBool() const { return getRef().get<bool>(); }

std::string org::sem::OrgJson::dump(int indent) const { return getRef().dump(indent); }

hstd::Vec<org::sem::OrgJson> org::sem::OrgJson::getArray() const {
    hstd::Vec<OrgJson> result;
    for (auto const& sub : getRef()) { result.push_back(&sub); }
    return result;
}

org::sem::OrgJson org::sem::OrgJson::getItem(int index) const {
    return getRef().at(index);
}

org::sem::OrgJson org::sem::OrgJson::getField(std::string const& name) const {
    return getRef().at(name);
}

org::sem::OrgJson org::sem::OrgJson::at(std::string const& name) const {
    return &getRef().at(name);
}

org::sem::OrgJson org::sem::OrgJson::at(int idx) const { return &getRef().at(idx); }
