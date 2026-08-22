#include "proto_to_xml.hpp"

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/reflection.h>

#include <array>
#include <charconv>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <vector>

namespace hstd {
namespace {

std::string base64_encode(std::string_view input) {
    using Base64Iterator = boost::archive::iterators::base64_from_binary<
        boost::archive::iterators::
            transform_width<std::string_view::const_iterator, 6, 8>>;

    std::string result(Base64Iterator(input.begin()), Base64Iterator(input.end()));
    result.append((3 - input.size() % 3) % 3, '=');
    return result;
}


template <typename T>
std::string number_to_string(T value) {
    std::array<char, 64> buffer;
    auto [end, error] = std::to_chars(
        buffer.data(), buffer.data() + buffer.size(), value);

    if (error != std::errc{}) { throw std::system_error(std::make_error_code(error)); }

    return std::string(buffer.data(), end);
}

template <typename T>
std::string floating_point_to_string(T value) {
    std::array<char, 128> buffer;
    auto [end, error] = std::to_chars(
        buffer.data(),
        buffer.data() + buffer.size(),
        value,
        std::chars_format::general,
        std::numeric_limits<T>::max_digits10);

    if (error != std::errc{}) { throw std::system_error(std::make_error_code(error)); }

    return std::string(buffer.data(), end);
}

} // namespace

ProtoXmlMapper::ProtoXmlMapper(OverrideMap overrides) : overrides(std::move(overrides)) {}

XmlNode ProtoXmlMapper::map(
    google::protobuf::Message const& message,
    std::string const&               root_tag) const {
    auto const* descriptor = message.GetDescriptor();

    XmlNode result(root_tag.empty() ? std::string{descriptor->name()} : root_tag);

    populate(message, result);
    return result;
}

void ProtoXmlMapper::populate(google::protobuf::Message const& message, XmlNode& node)
    const {
    auto const* descriptor = message.GetDescriptor();
    auto const  override   = overrides.find(std::string{descriptor->full_name()});

    if (override != overrides.end()) {
        override->second(message, node, *this);
    } else {
        populate_default(message, node);
    }
}

void ProtoXmlMapper::populate_default(
    google::protobuf::Message const& message,
    XmlNode&                         node) const {
    auto const* descriptor = message.GetDescriptor();

    if (descriptor->full_name() == "google.protobuf.Any"
        && append_any_payload(message, node)) {
        return;
    }

    auto const* reflection = message.GetReflection();

    std::vector<google::protobuf::FieldDescriptor const*> fields;
    reflection->ListFields(message, &fields);

    for (auto const* field : fields) { append_field(message, *field, node); }
}

bool ProtoXmlMapper::append_any_payload(
    google::protobuf::Message const& message,
    XmlNode&                         node) const {
    auto const* any_descriptor = message.GetDescriptor();
    auto const* reflection     = message.GetReflection();

    auto const* type_url_field = any_descriptor->FindFieldByName("type_url");
    auto const* value_field    = any_descriptor->FindFieldByName("value");

    if (type_url_field == nullptr || value_field == nullptr) { return false; }

    std::string const type_url = reflection->GetString(message, type_url_field);
    std::string const payload  = reflection->GetString(message, value_field);

    auto const separator = type_url.rfind('/');
    if (separator == std::string::npos || separator + 1 == type_url.size()) {
        return false;
    }

    std::string const message_name = type_url.substr(separator + 1);

    auto const* pool               = any_descriptor->file()->pool();
    auto const* payload_descriptor = pool->FindMessageTypeByName(message_name);

    if (payload_descriptor == nullptr) { return false; }

    google::protobuf::DynamicMessageFactory factory(pool);
    factory.SetDelegateToGeneratedFactory(true);

    auto const* prototype = factory.GetPrototype(payload_descriptor);
    if (prototype == nullptr) { return false; }

    std::unique_ptr<google::protobuf::Message> decoded(prototype->New());
    if (!decoded->ParseFromString(payload)) { return false; }

    XmlNode type_url_node("type_url");
    type_url_node.set_text(type_url);
    node.push_back(std::move(type_url_node));

    XmlNode payload_node(std::string{payload_descriptor->name()});
    populate(*decoded, payload_node);
    node.push_back(std::move(payload_node));

    return true;
}


void ProtoXmlMapper::append_field(
    google::protobuf::Message const&         message,
    google::protobuf::FieldDescriptor const& field,
    XmlNode&                                 parent) const {
    auto const* reflection = message.GetReflection();

    XmlNode field_node(std::string{field.name()});


    if (field.is_repeated()) {
        int const size = reflection->FieldSize(message, &field);

        for (int index = 0; index < size; ++index) {
            if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
                auto const& item_message = reflection->GetRepeatedMessage(
                    message, &field, index);

                XmlNode item(std::string{item_message.GetDescriptor()->name()});
                populate(item_message, item);
                field_node.push_back(std::move(item));
            } else {
                std::string item_tag;

                if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_ENUM) {
                    item_tag = field.enum_type()->name();
                } else {
                    item_tag = google::protobuf::FieldDescriptor::TypeName(field.type());
                }

                XmlNode item(item_tag);
                item.set_text(scalar_to_string(message, field, index));
                field_node.push_back(std::move(item));
            }
        }
    } else if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
        populate(reflection->GetMessage(message, &field), field_node);
    } else {
        field_node.set_text(scalar_to_string(message, field, -1));
    }

    parent.push_back(std::move(field_node));
}

std::string ProtoXmlMapper::scalar_to_string(
    google::protobuf::Message const&         message,
    google::protobuf::FieldDescriptor const& field,
    int                                      repeated_index) const {
    auto const* reflection = message.GetReflection();
    bool const  repeated   = 0 <= repeated_index;

    switch (field.cpp_type()) {
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            return number_to_string(
                repeated ? reflection->GetRepeatedInt32(message, &field, repeated_index)
                         : reflection->GetInt32(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            return number_to_string(
                repeated ? reflection->GetRepeatedInt64(message, &field, repeated_index)
                         : reflection->GetInt64(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
            return number_to_string(
                repeated ? reflection->GetRepeatedUInt32(message, &field, repeated_index)
                         : reflection->GetUInt32(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
            return number_to_string(
                repeated ? reflection->GetRepeatedUInt64(message, &field, repeated_index)
                         : reflection->GetUInt64(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            return floating_point_to_string(
                repeated ? reflection->GetRepeatedDouble(message, &field, repeated_index)
                         : reflection->GetDouble(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            return floating_point_to_string(
                repeated ? reflection->GetRepeatedFloat(message, &field, repeated_index)
                         : reflection->GetFloat(message, &field));

        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            return (repeated
                        ? reflection->GetRepeatedBool(message, &field, repeated_index)
                        : reflection->GetBool(message, &field))
                     ? "true"
                     : "false";

        case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
            auto const* value = repeated ? reflection->GetRepeatedEnum(
                                               message, &field, repeated_index)
                                         : reflection->GetEnum(message, &field);

            return std::string{value->name()};
        }

        case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
            std::string value = repeated ? reflection->GetRepeatedString(
                                               message, &field, repeated_index)
                                         : reflection->GetString(message, &field);

            if (field.type() == google::protobuf::FieldDescriptor::TYPE_BYTES) {
                return base64_encode(value);
            } else {
                return value;
            }
        }

        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: break;
    }

    throw std::logic_error("Cannot convert protobuf message field to scalar text");
}

} // namespace hstd
