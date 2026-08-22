#include "haxorg/serde/SemOrgSerde.hpp"
#include "proto_to_xml.hpp"
#include "src/hstd/ext/graph/base/graph_base.pb.h"

using CB  = hstd::ProtoXmlMapper::Override;
using Xml = hstd::XmlNode;

template <typename T>
std::pair<std::string, hstd::ProtoXmlMapper::Override> make_map(
    Xml (*cb)(T const&, std::string const& name, hstd::ProtoXmlMapper const&)) {
    return {
        std::string{T::descriptor()->full_name()},
        CB{
            [cb](
                google::protobuf::Message const& message,
                std::string const&               name,
                hstd::ProtoXmlMapper const&      mapper) {
                auto const& value = dynamic_cast<T const&>(message);
                return cb(value, name, mapper);
            },
        },
    };
}


template <typename T>
std::pair<std::string, hstd::ProtoXmlMapper::Override> make_map(
    void (*cb)(T const&, Xml&, hstd::ProtoXmlMapper const&)) {
    return {
        std::string{T::descriptor()->full_name()},
        CB{
            [cb](
                google::protobuf::Message const& message,
                std::string const&               name,
                hstd::ProtoXmlMapper const&      mapper) {
                auto const& value = dynamic_cast<T const&>(message);
                Xml         node{name};
                cb(value, node, mapper);
                return node;
            },
        },
    };
}

void map_location(
    orgproto::org_parse_SourceLoc const& loc,
    Xml&                                 node,
    hstd::ProtoXmlMapper const&          mapper) {
    node.set_attr("line", loc.line());
    node.set_attr("column", loc.column());
    node.set_attr("pos", loc.pos());

    if (loc.has_file()) { node.set_attr("file", loc.file().id()); }
}

template <typename LeafNode>
void map_leaf_node(LeafNode const& word, Xml& node, hstd::ProtoXmlMapper const& mapper) {
    if (word.has_loc()) { map_location(word.loc(), node, mapper); }
    node.set_text(word.text());
}

template <typename OnlyNested>
void map_only_nested_node(
    OnlyNested const&           it,
    Xml&                        node,
    hstd::ProtoXmlMapper const& mapper) {
    if (it.has_loc()) { map_location(it.loc(), node, mapper); }
    for (auto const& sub : it.subnodes()) { node.push_back(mapper.map(sub)); }
}

template <std::size_t N>
struct FixedString {
    char value[N];

    constexpr FixedString(char const (&text)[N]) { std::copy_n(text, N, value); }
};

template <typename Oneof, FixedString KindField = "kind">
Xml map_oneof_type(
    Oneof const& value,
    std::string const&,
    hstd::ProtoXmlMapper const& mapper) {
    auto const* descriptor = value.GetDescriptor();
    auto const* reflection = value.GetReflection();
    auto const* kind       = descriptor->FindOneofByName(KindField.value);

    auto const* active_field = reflection->GetOneofFieldDescriptor(value, kind);

    if (active_field == nullptr) {
        throw hstd::logic_error::init("Oneof type has no active kind");
    }

    if (active_field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
        throw hstd::logic_error::init("Oneof kind is not a message");
    }

    return mapper.map(reflection->GetMessage(value, active_field));
}


hstd::ProtoXmlMapper make_proto_xml_mapper() {
    return hstd::ProtoXmlMapper{
        std::unordered_map<std::string, CB>{
            make_map(&map_location),
            make_map(&map_leaf_node<orgproto::Word>),
            make_map(&map_leaf_node<orgproto::Space>),
            make_map(&map_leaf_node<orgproto::Newline>),
            make_map(&map_leaf_node<orgproto::BigIdent>),
            make_map(&map_leaf_node<orgproto::Word>),
            make_map(&map_leaf_node<orgproto::AtMention>),
            make_map(&map_leaf_node<orgproto::RawText>),
            make_map(&map_leaf_node<orgproto::Punctuation>),
            make_map(&map_leaf_node<orgproto::Placeholder>),
            make_map(&map_leaf_node<orgproto::TextTarget>),
            make_map(&map_leaf_node<orgproto::ErrorSkipToken>),
            make_map(&map_only_nested_node<orgproto::Monospace>),
            make_map(&map_only_nested_node<orgproto::Bold>),
            make_map(&map_only_nested_node<orgproto::Italic>),
            make_map(&map_only_nested_node<orgproto::Verbatim>),
            make_map(&map_only_nested_node<orgproto::Italic>),
            make_map(&map_only_nested_node<orgproto::Strike>),
            make_map(&map_only_nested_node<orgproto::Par>),
            make_map(&map_only_nested_node<orgproto::Paragraph>),
            make_map(&map_only_nested_node<orgproto::ColonExample>),
            make_map(&map_oneof_type<orgproto::AnyNode>),
            make_map(&map_oneof_type<orgproto::NamedProperty::Data>),
            make_map(+[](orgproto::hstd_UserTime const& loc,
                         Xml&                           node,
                         hstd::ProtoXmlMapper const&    mapper) {
                node.set_attr("time", loc.time());
                if (loc.has_zone()) { node.set_attr("zone", loc.zone()); }
                node.set_attr("align", loc.align());
            }),
            make_map(+[](hstd::ext::graph::proto::IEdge const& loc,
                         Xml&                                  node,
                         hstd::ProtoXmlMapper const&           mapper) {
                node.set_attr("line", loc.stable_id());
                node.set_attr("source_vertex_id", loc.source_vertex_id());
                node.set_attr("target_vertex_id", loc.target_vertex_id());
            }),
        },
    };
};
