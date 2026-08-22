#include "haxorg/serde/SemOrgSerde.hpp"
#include "proto_to_xml.hpp"
#include "src/hstd/ext/graph/base/graph_base.pb.h"

using CB  = hstd::ProtoXmlMapper::Override;
using Xml = hstd::XmlNode;

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


hstd::ProtoXmlMapper make_proto_xml_mapper() {
    return hstd::ProtoXmlMapper{
        std::unordered_map<std::string, CB>{
            make_map(+[](orgproto::org_parse_SourceLoc const& loc,
                         Xml&                                 node,
                         hstd::ProtoXmlMapper const&          mapper) {
                node.set_attr("line", loc.line());
                node.set_attr("column", loc.column());
                node.set_attr("pos", loc.pos());

                if (loc.has_file()) { node.set_attr("file", loc.file().id()); }
            }),
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
