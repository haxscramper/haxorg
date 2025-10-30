#pragma once

#include <src/model/graph/IOrgGraph.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

class DiaGraphVertex : org::graph::IVertexID {
    DiaUniqId id;
};

class DiaHierarchyEdgeCollection : public org::graph::IEdgeCollection {
    // IEdgeCollection interface
  public:
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


    virtual void addVertex(const org::graph::IVertexID::Val& id) override {
    }

    virtual void delVertex(const org::graph::IVertexID::Val& id) override {
    }

    virtual org::graph::IEdgeCategory::Val getCategory() const override {
        return org::graph::IEdgeCategory::Val(Category{});
    }
};

class DiaGraph : org::graph::IGraph {};
