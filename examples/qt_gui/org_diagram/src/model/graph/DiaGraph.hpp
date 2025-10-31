#pragma once

#include <src/model/graph/IOrgGraph.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

class DiaGraphVertex : public org::graph::IVertexID {
  public:
    DiaUniqId id;

    DiaGraphVertex(DiaUniqId const& id) : id{id} {}

    virtual std::size_t getHash() const override {
        return std::hash<DiaUniqId>{}(id);
    }

    virtual bool isEqual(const IGraphObjectBase* other) const override {
        return other->isInstance<DiaGraphVertex>()
            && dynamic_cast<DiaGraphVertex const*>(other)->id == id;
    }

    virtual std::string getRepr() const override {
        return std::format("DiaGraphVertex({})", id);
    }

    static hstd::value_ptr<DiaGraphVertex> FromId(DiaUniqId const& id) {
        return hstd::value_ptr<DiaGraphVertex>(DiaGraphVertex{id});
    }
};


class DiaGraphEdge : public org::graph::IEdgeID {
  public:
    DiaGraphVertex source;
    DiaGraphVertex target;
    /// \brief To disambiguate multi-edges between the source and the
    /// target
    int bundleIndex;

    using Val = hstd::value_ptr<DiaGraphEdge>;

    DiaGraphEdge(
        DiaGraphVertex const& source,
        DiaGraphVertex const& target,
        int                   bundleIndex)
        : source{source}, target{target}, bundleIndex{bundleIndex} {}

    virtual std::size_t getHash() const override {
        std::size_t res;
        hstd::hax_hash_combine(res, source.getHash());
        hstd::hax_hash_combine(res, target.getHash());
        hstd::hax_hash_combine(res, bundleIndex);
        return res;
    }

    virtual bool isEqual(const IGraphObjectBase* other) const override {
        if (other->isInstance<DiaGraphEdge>()) {
            auto edge = dynamic_cast<DiaGraphEdge const*>(other);
            return edge->source.isEqual(&source)
                && edge->target.isEqual(&target)
                && edge->bundleIndex == bundleIndex;
        } else {
            return false;
        }
    }

    virtual std::string getRepr() const override {
        return std::format("DiaGraphEdge({}->{})", source.id, target.id);
    }

    virtual const org::graph::IVertexID* getSource() const override {
        return &source;
    }

    virtual const org::graph::IVertexID* getTarget() const override {
        return &target;
    }
};

class DiaHierarchyEdgeCollection : public org::graph::IEdgeCollection {
    // IEdgeCollection interface

    DiaContext::Ptr tree_context;

  public:
    DiaHierarchyEdgeCollection(DiaContext::Ptr tree_context)
        : tree_context{tree_context} {}

    class Category : public org::graph::IEdgeCategory {
        virtual std::size_t getHash() const override {
            return typeid(Category).hash_code();
        }

        virtual bool isEqual(
            const IGraphObjectBase* other) const override {
            return other->isInstance<Category>();
        }

        virtual std::string getRepr() const override {
            return "hierarchy-edge-collection";
        }
    };

    virtual org::graph::IEdgeCategory::Val getCategory() const override {
        return org::graph::IEdgeCategory::Val(Category{});
    }

    virtual hstd::Vec<org::graph::IEdgeID::Val> getOutgoing(
        const org::graph::IVertexID::Val& vert) override;
};

class DiaGraph : org::graph::IGraph {};
