#pragma once

#include <hstd/stdlib/Map.hpp>
#include <src/utils/value_ptr.hpp>
#include <hstd/stdlib/Ptrs.hpp>

namespace org::graph {
class IGraphObjectBase {
  public:
    virtual std::size_t getHash() const                              = 0;
    virtual bool        isEqual(IGraphObjectBase const* other) const = 0;
    virtual std::string getRepr() const                              = 0;

    virtual IGraphObjectBase* copy() const = 0;

    virtual ~IGraphObjectBase() = default;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }
};


class IProperty : public IGraphObjectBase {
  public:
    using Val = hstd::value_ptr<IProperty>;
};


class IVertexID : public IGraphObjectBase {
  public:
    using Val = hstd::value_ptr<IVertexID>;
};

/// \brief Categorize the in/out edge connections between vertices.
///
/// The concept of the node port is linked with the layout, but the the
/// abstract graph interface it is also used to group different connections
/// of edge to the vertices.
class IPortID : public IGraphObjectBase {
  public:
    using Val = hstd::value_ptr<IPortID>;
};

class IEdgeID : public IGraphObjectBase {
  public:
    virtual IVertexID const* getSource() const = 0;
    virtual IVertexID const* getTarget() const = 0;

    virtual hstd::Opt<IPortID::Val> getSourcePort() const {
        return std::nullopt;
    };

    virtual hstd::Opt<IPortID::Val> getTargetPort() const {
        return std::nullopt;
    }

    using Val = hstd::value_ptr<IEdgeID>;

    bool operator==(IEdgeID const& other) const {
        return this->isEqual(&other);
    }
};

class IEdgeCategory : public IGraphObjectBase {
  public:
    using Val = hstd::value_ptr<IEdgeCategory>;
};


struct property_value_ptr_hasher {
    std::size_t operator()(IProperty::Val const& k) const {
        return k->getHash();
    }
};

struct property_value_ptr_comparator {
    std::size_t operator()(
        IProperty::Val const& lhs,
        IProperty::Val const& rhs) const {
        return lhs->isEqual(rhs.get());
    }
};

struct vertex_value_ptr_hasher {
    std::size_t operator()(IVertexID::Val const& k) const {
        return k->getHash();
    }
};

struct vertex_value_ptr_comparator {
    std::size_t operator()(
        IVertexID::Val const& lhs,
        IVertexID::Val const& rhs) const {
        return lhs->isEqual(rhs.get());
    }
};

class IPropertyTracker : public hstd::SharedPtrApi<IPropertyTracker> {
    std::unordered_map<
        IProperty::Val,
        hstd::Vec<IVertexID::Val>,
        property_value_ptr_hasher,
        property_value_ptr_comparator>
        map;

  protected:
    virtual void addVertex(
        IProperty::Val const& property,
        IVertexID::Val const& vertex);

    virtual void delVertex(
        IProperty::Val const& property,
        IVertexID::Val const& vertex);

  public:
    virtual void addVertex(IVertexID::Val const& vertex) = 0;
    virtual void delVertex(IVertexID::Val const& vertex) = 0;

    virtual hstd::Vec<IVertexID::Val> const& getVertices(IProperty::Val const& prop) = 0;
    virtual hstd::Vec<IEdgeID::Val> getOutgoingEdges(IVertexID::Val const& id) = 0;
};

class IEdgeCollection : public hstd::SharedPtrApi<IEdgeCollection> {
    std::unordered_map<
        IVertexID::Val,
        std::unordered_map<
            IVertexID::Val,
            hstd::Vec<IEdgeID::Val>,
            vertex_value_ptr_hasher,
            vertex_value_ptr_comparator>,
        vertex_value_ptr_hasher,
        vertex_value_ptr_comparator>
        edges;

    std::unordered_map<
        IVertexID::Val,
        hstd::Vec<IVertexID::Val>,
        vertex_value_ptr_hasher,
        vertex_value_ptr_comparator>
        incoming_from;

  protected:
    virtual void addEdge(IEdgeID::Val const& id);
    virtual void delEdge(IEdgeID::Val const& id);

  public:
    virtual void addVertex(IVertexID::Val const& id);
    virtual void delVertex(IVertexID::Val const& id);

    virtual hstd::Vec<IEdgeID::Val> getOutgoing(IVertexID::Val const& vert) = 0;
    virtual IEdgeCategory::Val getCategory() const = 0;
};

class IGraph {
  protected:
    hstd::Vec<IEdgeCollection::Ptr>  collections;
    hstd::Vec<IPropertyTracker::Ptr> trackers;

  public:
    void addTracker(IPropertyTracker::Ptr const& tracker) {
        trackers.push_back(tracker);
    }

    virtual void addVertex(IVertexID::Val const& id);
    virtual void delVertex(IVertexID::Val const& id);

    virtual void addVertexList(hstd::Vec<IVertexID::Val> const& ids);
    virtual void delVertexList(hstd::Vec<IVertexID::Val> const& ids);
};
} // namespace org::graph
