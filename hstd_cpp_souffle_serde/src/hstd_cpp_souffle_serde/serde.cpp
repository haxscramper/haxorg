#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <souffle/SouffleFunctor.h>

#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using Json   = nlohmann::json;
using Domain = souffle::RamDomain;

void require(bool condition, std::string const& message) {
    if (!condition) { throw std::invalid_argument{message}; }
}

struct Schema {
    Json metadata{};

    explicit Schema(Json metadata) {
        this->metadata = std::move(metadata);
        require(
            this->metadata.at("format") == 1,
            "Serde metadata format must be 1; regenerate metadata with example.py");
        const int bits{this->metadata.at("domain_bits").get<int>()};
        require(
            bits == RAM_DOMAIN_SIZE,
            fmt::format(
                "Metadata uses {}-bit domains, but this functor uses {}; rebuild the "
                "library",
                bits,
                RAM_DOMAIN_SIZE));
        for (const auto& [type, info] : this->metadata.at("ADTs").items()) {
            for (const auto& branch : info.at("branches")) {
                require(
                    branch.at("names").size() == branch.at("types").size(),
                    fmt::format(
                        "Metadata for {} constructor {} has different field-name and "
                        "field-type counts",
                        type,
                        branch.at("name").get<std::string>()));
            }
        }
    }

    std::string qualify(std::string const& name) const {
        for (const std::string category : {"ADTs", "records"}) {
            for (const auto& [type, info] : metadata.at(category).items()) {
                if (type.substr(2) == name) { return type; }
            }
        }
        const std::map<std::string, std::string> primitives{
            {"symbol", "s:symbol"},
            {"number", "i:number"},
            {"unsigned", "u:unsigned"},
            {"float", "f:float"}};
        require(
            primitives.contains(name),
            fmt::format(
                "Root type '{}' is absent from compiler metadata; regenerate it for this "
                "program",
                name));
        return primitives.at(name);
    }
};

// Cache immutable schemas, never record IDs: IDs belong to the current Souffle tables.
std::shared_ptr<const Schema> schema_for(std::string const& text) {
    static std::mutex                                           mutex{};
    static std::map<std::string, std::shared_ptr<const Schema>> schemas{};
    const std::lock_guard                                       lock{mutex};
    if (!schemas.contains(text)) {
        schemas.insert_or_assign(text, std::make_shared<const Schema>(Json::parse(text)));
    }
    return schemas.at(text);
}

struct Codec {
    const Schema&         schema;
    souffle::SymbolTable& symbols;
    souffle::RecordTable& records;

    std::vector<Domain> unpack(Domain value, int arity) const {
        require(
            value != 0,
            fmt::format("Cannot unpack nil as a record with {} fields", arity));
        const Domain* data{records.unpack(value, arity)};
        return std::vector<Domain>{data, data + arity};
    }

    Domain pack(std::vector<Domain> const& values) const {
        return records.pack(values.data(), static_cast<int>(values.size()));
    }

    void check_fields(Json const& value, Json const& names, std::string const& path)
        const {
        require(
            value.is_object(),
            fmt::format("{} must be a fields object, got {}", path, value.dump()));
        for (const auto& name : names) {
            require(
                value.contains(name.get<std::string>()),
                fmt::format(
                    "{} is missing field {}; expected fields {}",
                    path,
                    name.dump(),
                    names.dump()));
        }
        require(
            value.size() == names.size(),
            fmt::format(
                "{} has unexpected fields: got {}, expected {}",
                path,
                value.dump(),
                names.dump()));
    }

    void check_node(Json const& value, std::string const& path) const {
        require(
            value.is_object() && value.size() == 2 && value.contains("head")
                && value.contains("fields"),
            fmt::format(
                "{} must contain exactly 'head' and 'fields', got {}",
                path,
                value.dump()));
        require(
            value.at("head").is_string(),
            fmt::format(
                "{}.head must be a constructor or record type name, got {}",
                path,
                value.at("head").dump()));
    }

    Domain decode_fields(
        Json const&        fields,
        Json const&        info,
        std::string const& path,
        bool               direct) const {
        const auto& names{info.at("names")};
        const auto& types{info.at("types")};
        check_fields(fields, names, path);
        std::vector<Domain> values{};
        for (int index{0}; index < static_cast<int>(types.size()); ++index) {
            const auto name{names.at(index).get<std::string>()};
            values.push_back(decode(
                fields.at(name),
                types.at(index).get<std::string>(),
                fmt::format("{}.{}", path, name)));
        }
        if (direct && values.size() == 1) { return values.at(0); }
        return pack(values);
    }

    Json encode_fields(
        std::vector<Domain> const& values,
        Json const&                info,
        std::string const&         path) const {
        auto        fields = Json::object();
        const auto& names{info.at("names")};
        const auto& types{info.at("types")};
        for (int index{0}; index < static_cast<int>(types.size()); ++index) {
            const auto name{names.at(index).get<std::string>()};
            fields.get_ref<Json::object_t&>().insert_or_assign(
                name,
                encode(
                    values.at(index),
                    types.at(index).get<std::string>(),
                    fmt::format("{}.{}", path, name)));
        }
        return fields;
    }

    Domain decode(Json const& value, std::string const& type, std::string const& path)
        const {
        switch (type.at(0)) {
            case 's': {
                require(
                    value.is_string(),
                    fmt::format(
                        "{} expects {} as a JSON string, got {}",
                        path,
                        type,
                        value.dump()));
                return symbols.encode(value.get<std::string>());
            }
            case 'i': {
                require(
                    value.is_number_integer(),
                    fmt::format(
                        "{} expects {} as a JSON integer, got {}",
                        path,
                        type,
                        value.dump()));
                if (value.is_number_unsigned()) {
                    const auto number{value.get<std::uint64_t>()};
                    require(
                        std::in_range<Domain>(number),
                        fmt::format(
                            "{} value {} exceeds the {}-bit signed domain",
                            path,
                            number,
                            RAM_DOMAIN_SIZE));
                    return static_cast<Domain>(number);
                }
                const auto number{value.get<std::int64_t>()};
                require(
                    std::in_range<Domain>(number),
                    fmt::format(
                        "{} value {} exceeds the {}-bit signed domain",
                        path,
                        number,
                        RAM_DOMAIN_SIZE));
                return static_cast<Domain>(number);
            }
            case 'u': {
                require(
                    value.is_number_integer()
                        && (value.is_number_unsigned() || 0 <= value.get<std::int64_t>()),
                    fmt::format(
                        "{} expects {} as a nonnegative JSON integer, got {}",
                        path,
                        type,
                        value.dump()));
                const auto number{value.get<std::uint64_t>()};
                require(
                    std::in_range<souffle::RamUnsigned>(number),
                    fmt::format(
                        "{} value {} exceeds the {}-bit unsigned domain",
                        path,
                        number,
                        RAM_DOMAIN_SIZE));
                return std::bit_cast<Domain>(static_cast<souffle::RamUnsigned>(number));
            }
            case 'f': {
                require(
                    value.is_number(),
                    fmt::format(
                        "{} expects {} as a JSON number, got {}",
                        path,
                        type,
                        value.dump()));
                const auto number{value.get<souffle::RamFloat>()};
                require(
                    std::isfinite(number),
                    fmt::format(
                        "{} cannot represent {} as a finite {}-bit float",
                        path,
                        value.dump(),
                        RAM_DOMAIN_SIZE));
                return std::bit_cast<Domain>(number);
            }
            case 'r': {
                if (value.is_null()) { return 0; }
                check_node(value, path);
                require(
                    value.at("head") == type.substr(2),
                    fmt::format(
                        "{}.head must be '{}', got {}",
                        path,
                        type.substr(2),
                        value.at("head").dump()));
                return decode_fields(
                    value.at("fields"),
                    schema.metadata.at("records").at(type),
                    fmt::format("{}.fields", path),
                    false);
            }
            case '+': {
                check_node(value, path);
                const auto& info{schema.metadata.at("ADTs").at(type)};
                const auto& branches{info.at("branches")};
                for (int tag{0}; tag < static_cast<int>(branches.size()); ++tag) {
                    const auto& branch{branches.at(tag)};
                    if (branch.at("name") == value.at("head")) {
                        if (info.at("enum").get<bool>()) {
                            check_fields(
                                value.at("fields"),
                                branch.at("names"),
                                fmt::format("{}.fields", path));
                            return tag;
                        }
                        const auto payload{decode_fields(
                            value.at("fields"),
                            branch,
                            fmt::format("{}.fields", path),
                            true)};
                        return records.pack({tag, payload});
                    }
                }
                auto expected = Json::array();
                for (const auto& branch : branches) {
                    expected.push_back(branch.at("name"));
                }
                throw std::invalid_argument{fmt::format(
                    "{}.head {} is not a constructor of {}; expected {}",
                    path,
                    value.at("head").dump(),
                    type,
                    expected.dump())};
            }
            default: {
                throw std::invalid_argument{fmt::format(
                    "{} has unsupported compiler type qualifier '{}'", path, type)};
            }
        }
    }

    Json encode(Domain value, std::string const& type, std::string const& path) const {
        switch (type.at(0)) {
            case 's': {
                return symbols.decode(value);
            }
            case 'i': {
                return value;
            }
            case 'u': {
                return std::bit_cast<souffle::RamUnsigned>(value);
            }
            case 'f': {
                const auto number{std::bit_cast<souffle::RamFloat>(value)};
                require(
                    std::isfinite(number),
                    fmt::format(
                        "{} contains a nonfinite {} value; JSON requires finite numbers",
                        path,
                        type));
                return number;
            }
            case 'r': {
                if (value == 0) { return nullptr; }
                const auto& info{schema.metadata.at("records").at(type)};
                const auto  values{
                    unpack(value, static_cast<int>(info.at("types").size()))};
                return Json{
                    {"head", type.substr(2)},
                    {"fields", encode_fields(values, info, path)}};
            }
            case '+': {
                const auto& info{schema.metadata.at("ADTs").at(type)};
                const bool  enumeration{info.at("enum").get<bool>()};
                const auto  outer{
                    enumeration ? std::vector<Domain>{value, 0} : unpack(value, 2)};
                const auto  tag{outer.at(0)};
                const auto& branches{info.at("branches")};
                require(
                    0 <= tag && tag < static_cast<Domain>(branches.size()),
                    fmt::format(
                        "{} has tag {} outside the constructor range for {}",
                        path,
                        tag,
                        type));
                const auto&         branch{branches.at(static_cast<int>(tag))};
                const int           arity{static_cast<int>(branch.at("types").size())};
                std::vector<Domain> values{};
                if (arity == 1) {
                    values.push_back(outer.at(1));
                } else if (1 < arity) {
                    values = unpack(outer.at(1), arity);
                }
                return Json{
                    {"head", branch.at("name")},
                    {"fields", encode_fields(values, branch, path)}};
            }
            default: {
                throw std::invalid_argument{fmt::format(
                    "{} has unsupported compiler type qualifier '{}'", path, type)};
            }
        }
    }
};
} // namespace

extern "C" Domain hstd_init_souffle_analysis(
    souffle::SymbolTable* symbols,
    souffle::RecordTable*,
    Domain metadata) {
    schema_for(symbols->decode(metadata));
    return metadata;
}

extern "C" Domain hstd_from_json(
    souffle::SymbolTable* symbols,
    souffle::RecordTable* records,
    Domain                metadata,
    Domain                root,
    Domain                payload) {
    const auto  schema{schema_for(symbols->decode(metadata))};
    const Codec codec{.schema = *schema, .symbols = *symbols, .records = *records};
    return codec.decode(
        Json::parse(symbols->decode(payload)),
        schema->qualify(symbols->decode(root)),
        "$root");
}

extern "C" Domain hstd_to_json(
    souffle::SymbolTable* symbols,
    souffle::RecordTable* records,
    Domain                metadata,
    Domain                root,
    Domain                value) {
    const auto  schema{schema_for(symbols->decode(metadata))};
    const Codec codec{.schema = *schema, .symbols = *symbols, .records = *records};
    return symbols->encode(
        codec.encode(value, schema->qualify(symbols->decode(root)), "$root").dump());
}
