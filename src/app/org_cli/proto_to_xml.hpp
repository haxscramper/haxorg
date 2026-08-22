#pragma once

#include <google/protobuf/message.h>
#include <hstd/stdlib/Xml.hpp>

#include <functional>
#include <string>
#include <unordered_map>

namespace hstd {

class ProtoXmlMapper {
  public:
    using Override = std::function<
        void(google::protobuf::Message const&, XmlNode&, ProtoXmlMapper const&)>;

    using OverrideMap = std::unordered_map<std::string, Override>;

    explicit ProtoXmlMapper(OverrideMap overrides = {});

    XmlNode map(
        google::protobuf::Message const& message,
        std::string const&               root_tag = {}) const;

    void populate(google::protobuf::Message const& message, XmlNode& node) const;

  private:
    void populate_default(google::protobuf::Message const& message, XmlNode& node) const;

    void append_field(
        google::protobuf::Message const&         message,
        google::protobuf::FieldDescriptor const& field,
        XmlNode&                                 parent) const;

    std::string scalar_to_string(
        google::protobuf::Message const&         message,
        google::protobuf::FieldDescriptor const& field,
        int                                      repeated_index) const;

    OverrideMap overrides;
};

} // namespace hstd
