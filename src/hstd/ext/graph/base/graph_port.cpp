#include "graph_port.hpp"

hstd::ext::graph::PortID hstd::ext::graph::IPortCollection::
    getPortForConnection(VertexID vid, EdgeID eid, bool is_start) const {
    auto& edge_idx    = port_edges.get<ByEdgeID>();
    auto [begin, end] = edge_idx.equal_range(eid);
    for (; begin != end; ++begin) {
        if (begin->is_source != is_start) { continue; }
        if (getVertexForPort(begin->port) == vid) { return begin->port; }
    }

    throw port_structure_error::init(
        hstd::fmt(
            "No {} connection between vertex {} and edge {}",
            is_start ? "start" : "end",
            vid,
            eid));
}

hstd::Pair<hstd::ext::graph::PortID, hstd::ext::graph::PortID> hstd::ext::
    graph::IPortCollection::getPortsForEdge(EdgeID eid) const {
    auto& idx         = port_edges.get<ByEdgeID>();
    auto [begin, end] = idx.equal_range(eid);

    PortID source = PortID::Nil();
    PortID target = PortID::Nil();

    for (; begin != end; ++begin) {
        if (begin->is_source) {
            source = begin->port;
        } else {
            target = begin->port;
        }
    }

    return {source, target};
}

hstd::ext::graph::PortIDSet hstd::ext::graph::IPortCollection::
    getPortsForVertex(VertexID vid) const {
    auto& idx         = ports.get<ByVertexID>();
    auto [begin, end] = idx.equal_range(vid);
    PortIDSet result;
    for (; begin != end; ++begin) { result.incl(begin->port); }
    return result;
}

hstd::ext::graph::EdgeIDSet hstd::ext::graph::IPortCollection::
    getEdgeForPort(PortID pid) const {
    getPortIterator(pid);
    auto& idx         = port_edges.get<ByPortIDInEdgeMap>();
    auto [begin, end] = idx.equal_range(pid);
    EdgeIDSet result;
    for (; begin != end; ++begin) { result.incl(begin->edge); }
    return result;
}

decltype(hstd::ext::graph::IPortCollection::ports
             .get<hstd::ext::graph::IPortCollection::ByPortID>()
             .begin())
    hstd::ext::graph::IPortCollection::getPortIterator(
        PortID const& pid) const {
    auto& idx = ports.get<ByPortID>();
    auto  it  = idx.find(pid);
    if (it == idx.end()) {
        throw port_structure_error::init(
            hstd::fmt("port {} is not registered in the collection", pid));
    }
    return it;
}

void hstd::ext::graph::IPortCollection::addPort(
    VertexID vertex,
    PortID   pid) {
    auto& port_idx = ports.get<ByPortID>();
    if (port_idx.find(pid) != port_idx.end()) {
        throw port_structure_error::init(
            hstd::fmt(
                "port {} is already registered in the collection", pid));
    }

    ports.insert(PortEntry{vertex, pid});
}

void hstd::ext::graph::IPortCollection::addPort(
    VertexID vertex,
    EdgeID   edge,
    bool     is_start,
    PortID   pid) {
    addPort(vertex, pid);
    connectPort(vertex, edge, is_start, pid);
}

void hstd::ext::graph::IPortCollection::connectPort(
    VertexID vertex,
    EdgeID   edge,
    bool     is_start,
    PortID   pid) {
    auto port_it = getPortIterator(pid);
    if (port_it->vertex != vertex) {
        throw port_structure_error::init(
            hstd::fmt(
                "Cannot connect port {} of vertex {} to edge {} for "
                "vertex {}",
                pid,
                port_it->vertex,
                edge,
                vertex));
    }

    auto& edge_idx     = port_edges.get<ByPortCompositeKey>();
    auto [_, inserted] = edge_idx.insert(
        PortEdgeEntry{port_it->port, edge, is_start});
    if (!inserted) {
        throw port_structure_error::init(
            hstd::fmt(
                "Port {} already has connection to edge {} as {}",
                pid,
                edge,
                is_start ? "start" : "end"));
    }
}

#if ORG_BUILD_WITH_PROTOBUF
void hstd::ext::graph::IPortCollection::writeSerial(
    proto::IPortCollection* out,
    IGraph const*           graph) const {}

void hstd::ext::graph::IPortCollection::readSerial(
    proto::IPortCollection const* in,
    IGraph const*                 graph,
    IGraphSerialReaderFactory*    factory) {}
#endif

bool hstd::ext::graph::IPortCollection::isSourcePort(PortID pid) const {
    getPortIterator(pid);
    auto& idx         = port_edges.get<ByPortIDInEdgeMap>();
    auto [begin, end] = idx.equal_range(pid);
    if (begin == end) {
        throw port_structure_error::init(
            hstd::fmt("port {} has no edge connections", pid));
    }

    bool value = begin->is_source;
    ++begin;
    for (; begin != end; ++begin) {
        if (begin->is_source != value) {
            throw port_structure_error::init(
                hstd::fmt(
                    "port {} has mixed source/target edge connections",
                    pid));
        }
    }
    return value;
}

bool hstd::ext::graph::IPortCollection::hasPortConnection(
    VertexID vid,
    EdgeID   eid,
    bool     is_start) const {
    auto& edge_idx    = port_edges.get<ByEdgeID>();
    auto [begin, end] = edge_idx.equal_range(eid);
    for (; begin != end; ++begin) {
        if (begin->is_source != is_start) { continue; }
        if (getVertexForPort(begin->port) == vid) { return true; }
    }
    return false;
}

bool hstd::ext::graph::IPortCollection::hasTargetPort(
    VertexID vid,
    EdgeID   eid) const {
    return hasPortConnection(vid, eid, false);
}

hstd::ext::graph::PortID hstd::ext::graph::IPortCollection::getTargetPort(
    VertexID vid,
    EdgeID   eid) const {
    return getPortForConnection(vid, eid, false);
}

hstd::ext::graph::PortID hstd::ext::graph::IPortCollection::getSourcePort(
    VertexID vid,
    EdgeID   eid) const {
    return getPortForConnection(vid, eid, true);
}

hstd::ext::graph::PortID hstd::ext::graph::TrivialPortCollection::addPort(
    VertexID                          vertex,
    EdgeID                            edge,
    bool                              is_start,
    std::optional<std::string> const& stable_id) {
    auto id = portStore.add(
        TrivialPort{stable_id.value_or(
            hstd::fmt1(portStore.getNextId(getCollectionID().t)))},
        getCollectionID().t);
    IPortCollection::addPort(vertex, edge, is_start, id);
    return id;
}

hstd::ext::graph::PortID hstd::ext::graph::TrivialPortCollection::addPort(
    VertexID                          vertex,
    std::optional<std::string> const& stable_id) {
    auto id = portStore.add(
        TrivialPort{stable_id.value_or(
            hstd::fmt1(portStore.getNextId(getCollectionID().t)))},
        getCollectionID().t);
    IPortCollection::addPort(vertex, id);
    return id;
}
