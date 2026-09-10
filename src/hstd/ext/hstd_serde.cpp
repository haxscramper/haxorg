#include "hstd_serde.hpp"

#if ORG_BUILD_WITH_PROTOBUF

#    include <buf/validate/validator.h>
#    include <google/protobuf/struct.pb.h>
#    include <google/protobuf/util/json_util.h>
#    include <google/protobuf/wrappers.pb.h>
#    include <hstd/stdlib/JsonUse.hpp>

namespace hstd::serde {

void json_to_struct(json const& in, ::google::protobuf::Struct* out) {
    if (!in.is_object()) {
        throw std::runtime_error(
            "VisCustom.extra must be a JSON object for protobuf Struct");
    }

    out->clear_fields();
    for (auto const& [k, v] : in.items()) {
        json_to_value(v, &(*out->mutable_fields())[k]);
    }
}

void json_to_value(json const& in, ::google::protobuf::Value* out) {
    if (in.is_null()) {
        out->set_null_value(::google::protobuf::NullValue::NULL_VALUE);
    } else if (in.is_boolean()) {
        out->set_bool_value(in.get<bool>());
    } else if (in.is_number_integer()) {
        out->set_number_value(static_cast<double>(in.get<long long>()));
    } else if (in.is_number_unsigned()) {
        out->set_number_value(static_cast<double>(in.get<unsigned long long>()));
    } else if (in.is_number_float()) {
        out->set_number_value(in.get<double>());
    } else if (in.is_string()) {
        out->set_string_value(in.get<std::string>());
    } else if (in.is_array()) {
        auto* list = out->mutable_list_value();
        list->clear_values();
        for (auto const& it : in) { json_to_value(it, list->add_values()); }
    } else if (in.is_object()) {
        json_to_struct(in, out->mutable_struct_value());
    } else {
        throw std::runtime_error("Unsupported JSON type");
    }
}

json struct_to_json(::google::protobuf::Struct const& in) {
    json out = json::object();
    for (auto const& [k, v] : in.fields()) { out[k] = value_to_json(v); }
    return out;
}

json value_to_json(::google::protobuf::Value const& in) {
    switch (in.kind_case()) {
        case ::google::protobuf::Value::kNullValue: return nullptr;
        case ::google::protobuf::Value::kNumberValue: return in.number_value();
        case ::google::protobuf::Value::kStringValue: return in.string_value();
        case ::google::protobuf::Value::kBoolValue: return in.bool_value();
        case ::google::protobuf::Value::kStructValue:
            return struct_to_json(in.struct_value());
        case ::google::protobuf::Value::kListValue: {
            json out = json::array();
            for (auto const& it : in.list_value().values()) {
                out.push_back(value_to_json(it));
            }
            return out;
        }
        case ::google::protobuf::Value::KIND_NOT_SET: return nullptr;
    }

    throw std::runtime_error("Invalid protobuf Value kind");
}


std::string getJString(google::protobuf::Message const& message) {
    std::string                          json;
    google::protobuf::json::PrintOptions j_opts;
    j_opts.add_whitespace = true;
    auto status = google::protobuf::util::MessageToJsonString(message, &json, j_opts);

    LOGIC_ASSERTION_CHECK(status.ok(), "");
    return json;
}

namespace {
std::string handle_validation(buf::validate::ValidationResult const& violations) {
    hstd::Vec<hstd::Str> errors;

    errors.push_back(
        hstd::fmt("Validation failed with {} errors:", violations.violations_size()));

    for (const auto& violation : violations.violations()) {
        auto const& p = violation.proto();
        errors.push_back(
            hstd::fmt(
                "- [Path]: {}", buf::validate::internal::fieldPathString(p.field())));
        errors.push_back(hstd::fmt("  [Rule]: {}", p.rule_id()));
        errors.push_back(hstd::fmt("  [Error]: {}", p.message()));
    }

    return hstd::join("\n"_str_view, errors) + "\n";
}
} // namespace

void protovalidate_message(google::protobuf::Message const& message) {
    std::unique_ptr<buf::validate::ValidatorFactory>
                             factory = buf::validate::ValidatorFactory::New().value();
    google::protobuf::Arena  arena;
    buf::validate::Validator validator = factory->NewValidator(&arena);
    auto                     result    = validator.Validate(message);

    if (!result.ok()) { throw hstd::runtime_error::init(result.status().ToString()); }

    if (0 < result.value().violations_size()) {
        throw hstd::invalid_argument::init(handle_validation(result.value()));
    }
}


} // namespace hstd::serde

#endif
