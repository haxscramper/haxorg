/**

\file graph_base.hpp
\brief Provide base classes for the graph and visualization.

High-level overview of the design:

- All graph elements follow the DOD-like design, with the values accessible
  both using ID and the pointers. The value itself is managed by the
derived classes, this file mainly provides virtual methods to `get*` or
`add*`.
- The grap stores a single collection of vertices, but the edges are split
  into different collections, with explicit distinction between "hierarchy"
  edge collections (acyclic tree with a set of starting/parent nodes) and
  general collection (adjacency list with no constraints).

Terminology used

- **semantic** or **structural** refer  to the classes dedicated to
  managing the vertices, edges and ports and that are not concerned with
  the visualization details.
  - \ref hstd::ext::graph::IGraph
  - \ref hstd::ext::graph::IVertex
  - \ref hstd::ext::graph::IEdge
  - \ref hstd::ext::graph::IPort this one might have dual use for visual
    and for semantic.
  - \ref hstd::ext::graph::IAttribute dual use for visual and semantic.
    For visual it will use \ref hstd::ext::graph::layout::IVisualAttribute
    and \ref hstd::ext::graph::layout::ILayoutAttribute
- **visual** refer to the classes for the graph layout and visualization
  - \ref hstd::ext::graph::layout::LayoutRun
  - \ref hstd::ext::graph::layout::IConstraint
  - \ref hstd::ext::graph::layout::IGroup
  - \ref hstd::ext::graph::layout::IPlacementAlgorithm
- **tracker** refer to classes derived from the \ref
  hstd::ext::graph::IAttributeTracker

*/

#pragma once


#include "graph_common.hpp"
#include "graph_vertex.hpp"
#include "graph_edge.hpp"
#include "graph_attribute.hpp"
#include "graph_hierarchy.hpp"
#include "graph_port.hpp"

/// \brief graph structure and visualization
namespace hstd::ext::graph {


/// \brief Single set of vertices and a collection of associated edge sets.
///
/// A graph tracks all vertices in the store, and indirectly
/// tracks additional sets of edges managed by the `IVertexHierarchy` and
/// `IEdgeCollection`. Vertices are stored as opaque IDs -- mapping ID to
/// the specific object is done by the derived classes.
///
/// \note Classes derived from graph are not required to *store* the
/// vertices -- graph API is designed to track which vertex IDs exist, and
/// map the vertex ID to the vertex object. Most graphs will store the
/// vertices directly, but it is also suitable for adapting already
/// existing graphs.
class IGraph {
  protected:
    hstd::UnorderedMap<EdgeCollectionID, hstd::SPtr<IEdgeCollection>>
        collections;
    hstd::UnorderedMap<PortCollectionID, hstd::SPtr<IPortCollection>>
        ports;
    hstd::UnorderedMap<AttributeTrackerID, hstd::SPtr<IAttributeTracker>>
        trackers;
    hstd::UnorderedMap<EdgeCollectionID, hstd::SPtr<IVertexHierarchy>>
        hierarchies;

    /// \brief Full set of all vertices in the graph
    hstd::UnorderedSet<VertexID>      vertexIDs;
    hstd::UnorderedMap<Str, VertexID> stableIdMap;

  public:
    struct Crossing {
        EdgeCollectionID    hierarchy;
        hstd::Vec<VertexID> crossings;
        DESC_FIELDS(Crossing, (hierarchy, crossings));
    };

    /// \name IGraph tracker/provider operations
    /// @{
    void addTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void delTracker(hstd::SPtr<IAttributeTracker> const& tracker);
    void addCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void delCollection(hstd::SPtr<IEdgeCollection> const& collection);
    void addHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);
    void delHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);
    void addPorts(hstd::SPtr<IPortCollection> const& collection);
    void delPorts(hstd::SPtr<IPortCollection> const& collection);

    bool hasCollection(hstd::SPtr<IEdgeCollection> const& collection);
    bool hasHierarchy(hstd::SPtr<IVertexHierarchy> const& hierarchy);

    /// \brief Get list of all edge providers in the graph: vertex
    /// hierarchies and general edge collections.
    hstd::Vec<IEdgeProvider*> getEdgeProviders();
    /// @}

    /// \name Vertices
    /// @{
    /// \brief Get vertex object associated with the edge ID.
    virtual IVertex const* getVertex(VertexID const& id) const = 0;
    virtual IVertex*       getMVertex(VertexID const& id) const {
        return const_cast<IVertex*>(getVertex(id));
    }

    // TODO: Add method to access edge ID from the stable ID. Also make
    // this method fail if there are multiple edge collections with the
    // same stable ID.
    bool hasVertexStableId(Str const& id) const {
        return stableIdMap.contains(id);
    }

    VertexID getVertexIDByStableId(Str const& id) const {
        return stableIdMap.at(id);
    }

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T const* getCastVertex(VertexID const& id) const {
        return hstd::validated_dynamic_cast<T>(getVertex(id));
    }

    template <typename T = IVertex>
        requires std::derived_from<T, IVertex>
    T* getCastMVertex(VertexID const& id) const {
        return hstd::validated_dynamic_cast<T>(getMVertex(id));
    }

    /// \brief Track attributes and edge information in the graph
    ///
    /// Add the vertex to the graph collection. Will not
    /// automatically register all nested vertices and recursive data.
    /// After the base vertex is registered, provide additional structural
    /// information using `trackSubVertexRelation`.
    ///
    /// \warning Should be called with the full list of vertices to
    /// track: this method will not attempt to expand the set of vertices
    /// to include nested ones.
    void trackVertex(VertexID const& ids);
    /// \brief Remove vertex from the graph collection and recursively drop
    /// all the elements from the hierarchies.
    ///
    /// \note No follow-up calls to `untrackSubVertexRelation` is
    /// necessary to match the `trackSubVertexRelation` -- hierarchy
    /// deletion is done by this method.
    ///
    /// \warning Calling this method will RECURSIVELY DROP ALL SUB-VERTICES
    /// under `id` if they are also deleted in all hierarchies.
    ///
    /// \return Map of the dependant deletions in the graph hierarchies.
    /// Un-registering vertex *does not delete sub-vertices from the
    /// graph*, it only removes invalid edges. The returned value from this
    /// function contains a mapping from the hierarchy ID to the list of
    /// sub-vertex deletions for this hierarchy. It is possible to delete
    /// all the nested vertices with `untrackVertexList` for each set of
    /// vertices in the dependant deletion.
    hstd::UnorderedMap<EdgeCollectionID, IEdgeCollection::DependantDeletion> untrackVertex(
        VertexID const& id);


    bool isTrackingVertex(VertexID id) const {
        return vertexIDs.contains(id);
    }

    int getVertexCount() const { return this->vertexIDs.size(); }
    int getSummedEdgeCount() const {
        int res = 0;
        for (auto const& [id, coll] : collections) {
            res += coll->getNumEdges();
        }
        for (auto const& [id, hier] : hierarchies) {
            res += hier->getNumEdges();
        }
        return res;
    }

    /// @}

    /// \name Vertex hierarchies
    /// @{
    /// \brief Get list of all vertices stored in the graph
    VertexIDSet getAllVertices() const;
    /// \brief Get root vertices for the specified hierarchy
    VertexIDSet getRootVertices(EdgeCollectionID const& hierarchy) const;
    /// \brief Get sub vertices for the specified hierarchy
    VertexIDSet getSubVertices(
        EdgeCollectionID const& hierarchy,
        VertexID const&         id) const;
    /// \brief Get parent vertices for the specified hierarchy
    hstd::Opt<VertexID> getParentVertex(
        EdgeCollectionID const& hierarchy,
        VertexID const&         id) const;

    /// \brief Return the highest level of nesting in the hierarchy.
    int getMaxNestingLevel(EdgeCollectionID const& hierarchy) const;

    /// \brief Return full parent chain for vertex in the selected
    /// hierarchy.
    hstd::Vec<VertexID> getParentChain(
        EdgeCollectionID const& hierarchy,
        VertexID const&         id) const;

    /// \brief For id with given ID, compute the list of vertex
    /// boundaries it crossed in each tracked hierarchy between the source
    /// and the target.
    hstd::Vec<Crossing> getHierarchyCrossings(EdgeID const& edge_id) const;
    /// @}

    /// \name Edges
    /// @{
    /// \brief Get the edge from the collection/hierarchy. Use the edge ID
    /// mask to determine which collection the edge comes from.
    virtual IEdge const* getEdge(EdgeID const& id) const {
        return getEdgeProvider(id)->getEdge(id);
    }

    virtual IEdge* getMEdge(EdgeID const& id) const {
        return const_cast<IEdge*>(getEdge(id));
    }

    template <typename T = IEdge>
        requires std::derived_from<T, IEdge>
    T const* getCastEdge(EdgeID const& id) const {
        return hstd::validated_dynamic_cast<T>(getEdge(id));
    }

    template <typename T = IEdge>
        requires std::derived_from<T, IEdge>
    T* getCastMEdge(EdgeID const& id) const {
        return hstd::validated_dynamic_cast<T>(getMEdge(id));
    }

    EdgeCollectionID getHierarchyID(EdgeID const& id) const;
    EdgeCollectionID getCollectionID(EdgeID const& id) const;

    hstd::SPtr<IVertexHierarchy> getHierarchy(EdgeID const& id) const {
        return hierarchies.at(getHierarchyID(id));
    }

    hstd::SPtr<IEdgeCollection> getEdgeCollection(EdgeID const& id) const {
        return collections.at(getCollectionID(id));
    }

    hstd::SPtr<IEdgeProvider> getEdgeProvider(EdgeID const& id) const {
        if (id.isHierarchyEdge()) {
            return getHierarchy(id);
        } else {
            return getEdgeCollection(id);
        }
    }

    hstd::Vec<hstd::SPtr<IEdgeProvider>> getAllEdgeProviers() const {
        hstd::Vec<hstd::SPtr<IEdgeProvider>> result;
        for (auto const& e : collections) { result.push_back(e.second); }
        for (auto const& h : hierarchies) { result.push_back(h.second); }
        return result;
    }

    virtual VertexID getSource(EdgeID const& id) const;
    virtual VertexID getTarget(EdgeID const& id) const;

    virtual EdgeIDSet getOutgoing(VertexID const& id) const {
        EdgeIDSet result;
        for (auto const& p : getAllEdgeProviers()) {
            result.incl(p->getOutgoing(id));
        }
        return result;
    }

    virtual EdgeIDSet getIncoming(VertexID const& id) const {
        EdgeIDSet result;
        for (auto const& p : getAllEdgeProviers()) {
            result.incl(p->getIncoming(id));
        }
        return result;
    }


    virtual int getInDegree(VertexID const& v) const {
        return getIncoming(v).size();
    }

    virtual int getOutDegree(VertexID const& v) const {
        return getOutgoing(v).size();
    }


    /// \brief Provide additional information about the vertex nesting
    /// relation for a specific hierarchy.
    ///
    /// \return List of newly added edges in all hierarchies.
    hstd::Vec<EdgeID> trackSubVertexRelation(
        EdgeCollectionID const& hierarchy,
        EdgeID const&           edge,
        VertexID const&         parent,
        VertexID const&         sub);
    /// \brief Remove the vertex nesting information from a specific
    /// hierarchy.
    void untrackSubVertexRelation(
        EdgeCollectionID const& hierarchy,
        VertexID const&         parent,
        VertexID const&         sub);
    /// @}

    /// \name Ports
    /// @{
    PortCollectionID getPortCollectionID(PortID const& id) const;
    hstd::SPtr<IPortCollection> getPortCollection(PortID const& id) const {
        return ports.at(getPortCollectionID(id));
    }

    virtual IPort const* getPort(PortID const& id) const {
        return getPortCollection(id)->getPort(id);
    }

    virtual IPort* getMPort(PortID const& id) const {
        return const_cast<IPort*>(getPort(id));
    }

    template <typename T = IPort>
        requires std::derived_from<T, IPort>
    T const* getCastPort(PortID const& id) const {
        return hstd::validated_dynamic_cast<T>(getPort(id));
    }

    template <typename T = IPort>
        requires std::derived_from<T, IPort>
    T* getCastMPort(PortID const& id) const {
        return hstd::validated_dynamic_cast<T>(getMPort(id));
    }
    /// @}

    struct SerialSchema {
        struct EdgeCategory {
            hstd::Vec<json> edges;
            std::string     categoryName;

            struct HierarchyCrossing {
                std::string            hierarchyName;
                hstd::Vec<std::string> crossings;
                DESC_FIELDS(HierarchyCrossing, (hierarchyName, crossings));
            };

            /// \brief EdgeId -> List of Vertex IDs for parent hierarchies
            /// it has crossed. See `getHierarchyCrossings` method for more
            /// details.
            hstd::UnorderedMap<std::string, hstd::Vec<HierarchyCrossing>>
                hierarchyEdgeCrossings;

            DESC_FIELDS(
                EdgeCategory,
                (edges, categoryName, hierarchyEdgeCrossings));
        };

        struct Hierarchy {
            std::string                                  hierarchyName;
            hstd::Vec<std::string>                       rootVertexIDs;
            hstd::UnorderedMap<std::string, std::string> vertexParentMap;
            hstd::UnorderedMap<std::string, hstd::Vec<std::string>>
                vertexNestingMap;
            int maxNestingLevel = 0;
            DESC_FIELDS(
                Hierarchy,
                (hierarchyName,
                 rootVertexIDs,
                 vertexParentMap,
                 vertexNestingMap,
                 maxNestingLevel));
        };

        hstd::UnorderedMap<std::string, json>         vertices;
        hstd::UnorderedMap<std::string, EdgeCategory> edges;
        hstd::UnorderedMap<std::string, Hierarchy>    hierarchies;
        hstd::Vec<std::string>                        flatVertexIDs;

        DESC_FIELDS(
            SerialSchema,
            (vertices, edges, hierarchies, flatVertexIDs));
    };

    virtual void write_serial(proto::IGraphProto* out) const;
    std::unique_ptr<proto::IGraphProto> get_serial() const;

    std::string getDebug(VertexIDSet const& vert) const;
    std::string getDebug(VertexIDVec const& vert) const;
    std::string getDebug(VertexID const& vert) const;

    std::string getDebug(EdgeIDSet const& vert) const;
    std::string getDebug(EdgeIDVec const& vert) const;
    std::string getDebug(EdgeID const& edge) const;

    std::string getDebug(PortID const& port) const;
    std::string getDebug(PortIDVec const& vert) const;
    std::string getDebug(PortIDSet const& vert) const;

    std::string getStableId(VertexID const& id) const {
        return getVertex(id)->getStableId();
    }

    std::string getStableId(EdgeID const& id) const {
        return getEdge(id)->getStableId();
    }

    std::string getStableId(PortID const& id) const {
        return getPort(id)->getStableId();
    }
};


struct TrivialGraph : public IGraph {
    hstd::UnorderedIncrementalStore<VertexID, TrivialVertex> vertexStore;
    hstd::SPtr<TrivialEdgeCollection>                        edges;

    TrivialGraph()
        : edges{std::make_shared<TrivialEdgeCollection>(
              EdgeCollectionID{1})} {
        addCollection(edges);
    }

    VertexID addVertex(
        std::optional<std::string> const& stable_id = std::nullopt);

    const IVertex* getVertex(VertexID const& id) const override {
        return &vertexStore.at(id);
    }

    EdgeID addEdge(
        VertexID const&               source,
        VertexID const&               target,
        hstd::Opt<std::string> const& stable_id = std::nullopt) {
        return edges->addEdge(source, target, stable_id);
    }
};


} // namespace hstd::ext::graph
