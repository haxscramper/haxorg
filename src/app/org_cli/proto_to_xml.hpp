#pragma once

#include <google/protobuf/message.h>
#include <hstd/stdlib/Xml.hpp>

#include <functional>
#include <optional>
#include <string>
#include <unordered_map>

namespace hstd {

class ProtoXmlMapper {
  public:
    using Override = std::function<XmlNode(
        google::protobuf::Message const&,
        std::string const&,
        ProtoXmlMapper const&)>;

    using OverrideMap = std::unordered_map<std::string, Override>;

    explicit ProtoXmlMapper(OverrideMap overrides = {});

    XmlNode map(
        google::protobuf::Message const& message,
        std::string const&               root_tag = {}) const;

  private:
    XmlNode map_default(google::protobuf::Message const& message, std::string const& tag)
        const;

    XmlNode map_field(
        google::protobuf::Message const&         message,
        google::protobuf::FieldDescriptor const& field) const;

    XmlNode map_scalar(
        google::protobuf::Message const&         message,
        google::protobuf::FieldDescriptor const& field,
        std::string                              tag,
        int                                      repeated_index = -1) const;

    std::optional<XmlNode> map_any_payload(
        google::protobuf::Message const& message,
        std::string const&               tag) const;

    std::string scalar_to_string(
        google::protobuf::Message const&         message,
        google::protobuf::FieldDescriptor const& field,
        int                                      repeated_index) const;

    OverrideMap overrides;
};

} // namespace hstd
