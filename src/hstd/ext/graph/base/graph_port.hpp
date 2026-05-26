#pragma once

#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

#include "graph_common.hpp"
#include "graph_attribute.hpp"

namespace bmi = boost::multi_index;


namespace hstd::ext::graph {

/// \brief Connection port or edge grouping port
///
/// \note For visualizatino purposes ports might be independently managed
/// by the layout run. Semantic graph
struct IPort
    : public IGraphObjectBase
    , public virtual IAttributeObject {
    using id_type = PortID;
    DESC_FIELDS(IPort, ());
    using IGraphObjectBase::IGraphObjectBase;
};

class TrivialPort
    : public IPort
    , public virtual TrivialAttributeObject {
  public:
    using IPort::IPort;
};

class IPortCollection {
  public:
    struct PortEntry {
        VertexID vertex;
        PortID   port;
        DESC_FIELDS(PortEntry, (vertex, port));
    };

    struct PortEdgeEntry {
        PortID port;
        EdgeID edge;
        /// \brief To distinguish edge ports in case of self-loops.
        bool is_source;
        DESC_FIELDS(PortEdgeEntry, (port, edge, is_source));
    };

  private:
    // Tags for each index
    struct ByPortCompositeKey {};
    struct ByPortID {};
    struct ByVertexID {};

    struct ByEdgeID {};
    struct ByPortIDInEdgeMap {};

    using PortContainer = bmi::multi_index_container<
        PortEntry,
        bmi::indexed_by<
            // Unique: port — the "right" side of the bimap
            bmi::ordered_unique<
                bmi::tag<ByPortID>,
                bmi::member<PortEntry, PortID, &PortEntry::port>>,
            // Non-unique: vertex — range query for "ports of vertex"
            bmi::ordered_non_unique<
                bmi::tag<ByVertexID>,
                bmi::member<PortEntry, VertexID, &PortEntry::vertex>>>>;

    using PortEdgeContainer = bmi::multi_index_container<
        PortEdgeEntry,
        bmi::indexed_by<
            bmi::ordered_unique<
                bmi::tag<ByPortCompositeKey>,
                bmi::composite_key<
                    PortEdgeEntry,
                    bmi::member<
                        PortEdgeEntry,
                        PortID,
                        &PortEdgeEntry::port>,
                    bmi::member<
                        PortEdgeEntry,
                        EdgeID,
                        &PortEdgeEntry::edge>,
                    bmi::member<
                        PortEdgeEntry,
                        bool,
                        &PortEdgeEntry::is_source>>>,
            bmi::ordered_non_unique<
                bmi::tag<ByEdgeID>,
                bmi::member<PortEdgeEntry, EdgeID, &PortEdgeEntry::edge>>,
            // Non-unique: edge — range query for "ports of edge"
            bmi::ordered_non_unique<
                bmi::tag<ByPortIDInEdgeMap>,
                bmi::
                    member<PortEdgeEntry, PortID, &PortEdgeEntry::port>>>>;

  public:
    struct PortSpec {
        VertexID v;
        EdgeID   e;
        bool     is_start;
    };

    // pairs of ports for the edge: source and target
    using EdgePortsSpec = hstd::Pair<PortSpec, PortSpec>;

  protected:
    PortContainer     ports;
    PortEdgeContainer port_edges;

    decltype(ports.get<ByPortID>().begin()) getPortIterator(
        PortID const& pid) const;

    /// \brief Base method to add ports to the collection, derived classes
    /// should provide the storage implementation that will generate port
    /// ID, and provide a method that will require only
    /// vertex+edge+is-start.
    void addPort(VertexID vertex, PortID pid);

    void addPort(VertexID vertex, EdgeID edge, bool is_start, PortID pid);

    void addPort(PortSpec const& spec, PortID pid) {
        return addPort(spec.v, spec.e, spec.is_start, pid);
    }

    void connectPort(
        VertexID vertex,
        EdgeID   edge,
        bool     is_start,
        PortID   pid);

  public:
    virtual ~IPortCollection() = default;

    hstd::Vec<PortEntry> getAllEntries() const {
        hstd::Vec<PortEntry> res;
        for (auto const& e : ports) { res.push_back(e); }
        return res;
    }

    void connectPort(PortSpec const& spec, PortID pid) {
        connectPort(spec.v, spec.e, spec.is_start, pid);
    }

    void addEdgeToPort(PortID pid, EdgeID edge, bool is_start) {
        auto vertex = getVertexForPort(pid);
        connectPort(vertex, edge, is_start, pid);
    }

    void addEdgeToPort(PortID pid, PortSpec const& spec) {
        connectPort(spec.v, spec.e, spec.is_start, pid);
    }


    /// \brief Check if the collection has port
    virtual PortCollectionID getCollectionID() const   = 0;
    virtual IPort const*     getPort(PortID pid) const = 0;

    IPort* getMPort(PortID pid) {
        return const_cast<IPort*>(std::as_const(*this).getPort(pid));
    }

    EdgeIDSet getEdgeForPort(PortID pid) const;

    VertexID getVertexForPort(PortID pid) const {
        return getPortIterator(pid)->vertex;
    }

    bool isSourcePort(PortID pid) const;

    bool isTargetPort(PortID pid) const { return !isSourcePort(pid); }

    PortIDSet getPortsForVertex(VertexID vid) const;

    hstd::Pair<PortID, PortID> getPortsForEdge(EdgeID eid) const;

    bool hasPortConnection(PortSpec const& spec) const {
        return hasPortConnection(spec.v, spec.e, spec.is_start);
    }

    bool hasPortConnection(VertexID vid, EdgeID eid, bool is_start) const;

    bool hasSourcePort(VertexID vid, EdgeID eid) const {
        return hasPortConnection(vid, eid, true);
    }

    bool hasTargetPort(VertexID vid, EdgeID eid) const;

    PortID getPortForConnection(VertexID vid, EdgeID eid, bool is_start)
        const;

    PortID getSourcePort(VertexID vid, EdgeID eid) const;

    PortID getTargetPort(VertexID vid, EdgeID eid) const;

    void delPort(PortID pid) {
        getPortIterator(pid);
        port_edges.get<ByPortIDInEdgeMap>().erase(pid);
        ports.get<ByPortID>().erase(pid);
    }
};

class TrivialPortCollection : public IPortCollection {
    hstd::UnorderedIncrementalStore<PortID, TrivialPort> portStore;

  public:
    PortCollectionID getCollectionID() const override {
        return hstd::ext::graph::PortCollectionID(
            hstd::hash_bits<15>(typeid(this).hash_code()));
    }

    const IPort* getPort(PortID pid) const override {
        return &portStore.at(pid);
    }

    PortID addPort(PortSpec const& spec) {
        return addPort(spec.v, spec.e, spec.is_start);
    }

    PortID addPort(
        VertexID                          vertex,
        std::optional<std::string> const& stable_id = std::nullopt);

    PortID addPort(
        VertexID                          vertex,
        EdgeID                            edge,
        bool                              is_start,
        std::optional<std::string> const& stable_id = std::nullopt);

    hstd::Pair<PortID, PortID> addPorts(EdgePortsSpec const& spec) {
        return {addPort(spec.first), addPort(spec.second)};
    }
};


} // namespace hstd::ext::graph
