#pragma once

#include <haxorg/lexbase/Node.hpp>
#include <haxorg/lexbase/NodeStore.hpp>

namespace org::parse {

/// \brief Node adapter for more convenient access operations on the tree
template <typename N, typename K, typename V, typename M>
struct NodeAdapter {
    using NodeIdType    = NodeId<N, K, V, M>;
    using NodeGroupType = NodeGroup<N, K, V, M>;
    NodeGroupType const* group;
    NodeIdType           id;

    N    getKind() const { return group->at(id).kind; }
    bool empty() const { return size() == 0; }
    int  size() const { return group->size(id); }
    /// \brief Check if node adapter is default-constructed and does not
    /// contain pointers to the underlying content.
    bool isNil() const { return group == nullptr && id == NodeIdType::Nil(); }

    V const& val() const { return group->val(id); }
    N        kind() const { return group->at(id).kind; }
    bool     isTerminal() const { return group->at(id).isTerminal(); }
    bool     isMono() const { return group->at(id).isMono(); }
    M const  getMono() const { return group->at(id).getMono(); }
    bool     isNonTerminal() const { return group->at(id).isNonTerminal(); }

    Node<N, K, V, M> const& get() const { return group->at(id); }


    NodeAdapter<N, K, V, M>(NodeGroupType const* group, NodeIdType id)
        : group(group), id(id) {
        LOGIC_ASSERTION_CHECK_FMT(group->nodes.contains(id), "{}", id);
    }

    NodeAdapter() : group(nullptr), id(NodeIdType::Nil()) {}

    // FIXME temporary workaround until I figure out how to properly fix
    // invalid index genenerated by the tree sweep in parser in certain
    // cases. At the moment it is not fully clear what is causing creation
    // of a separate node group.
    bool isValid() const { return !id.isNil() && id.getIndex() < group->size(); }

    NodeAdapter<N, K, V, M> at(int index) const {
        return {group, group->subnode(id, index)};
    }

    NodeAdapter<N, K, V, M> operator[](int index) const {
        return {group, group->subnode(id, index)};
    }


    void treeRepr(
        hstd::ColStream&                            os,
        int                                         level = 0,
        typename NodeGroupType::TreeReprConf const& conf =
            typename NodeGroupType::TreeReprConf()) const {
        group->treeRepr(os, id, level, conf);
    }

    std::string format() const {
        std::stringstream buffer;
        hstd::ColStream   text{buffer};
        text.colored = false;
        typename NodeGroupType::TreeReprConf conf;
        conf.maxDepth = 2;
        group->treeRepr(text, id, 0, conf);
        return buffer.str();
    }

    std::string treeRepr(bool colored = false) const {
        std::stringstream buffer;
        hstd::ColStream   text{buffer};
        text.colored = colored;
        treeRepr(text);
        return buffer.str();
    }

    hstd::generator<NodeAdapter<N, K, V, M>> items() {
        for (int i = 0; i < group->size(id); ++i) { co_yield this->operator[](i); }
    }

    template <typename H, typename L>
    hstd::Vec<NodeAdapter<N, K, V, M>> at(hstd::HSlice<H, L> range) {
        hstd::Vec<NodeAdapter<N, K, V, M>> result;
        const auto [start, end] = getSpan(group->size(id), range, true);
        for (const auto& i : hstd::slice(start, end)) {
            result.push_back(this->operator[](i));
        }
        return result;
    }

    class iterator {
      private:
        typename NodeGroupType::iterator iter;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef NodeAdapter<N, K, V, M>   value_type;
        typedef NodeAdapter<N, K, V, M>*  pointer;
        typedef NodeAdapter<N, K, V, M>&  reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(typename NodeGroupType::iterator iter) : iter(iter) {}

        NodeAdapter<N, K, V, M> operator*() const {
            return NodeAdapter<N, K, V, M>(iter.group, iter.id);
        }

        iterator& operator++() {
            // increment current iterator state
            ++iter;
            return *this;
        }

        bool operator!=(iterator const& other) {
            // implement iterator inequality comparison
            return this->iter != other.iter;
        }
    };

    iterator begin() {
        if ((id + 1).getIndex() < group->size()) {
            return iterator(group->begin(id + 1));
        } else {
            return end();
        }
    }

    iterator end() { return iterator(group->end(id + group->at(id).getExtent())); }

    iterator begin() const {
        if ((id + 1).getIndex() < group->size()) {
            return iterator(group->begin(id + 1));
        } else {
            return end();
        }
    }

    iterator end() const { return iterator(group->end(id + group->at(id).getExtent())); }

    class flat_extent_iterator {
      private:
        typename NodeGroupType::flat_extent_iterator iter;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef NodeAdapter<N, K, V, M>   value_type;
        typedef NodeAdapter<N, K, V, M>*  pointer;
        typedef NodeAdapter<N, K, V, M>&  reference;
        typedef std::ptrdiff_t            difference_type;

        flat_extent_iterator(typename NodeGroupType::flat_extent_iterator iter)
            : iter(iter) {}

        NodeAdapter<N, K, V, M> operator*() const {
            return NodeAdapter<N, K, V, M>(iter.group, iter.id);
        }

        flat_extent_iterator& operator++() {
            ++iter;
            return *this;
        }

        bool operator!=(flat_extent_iterator const& other) {
            return this->iter != other.iter;
        }
    };


    std::pair<flat_extent_iterator, flat_extent_iterator> full_flat_extent_pair() const {
        return {
            flat_extent_iterator(group->begin_extent(id)),
            flat_extent_iterator(group->end_extent(id + group->at(id).getExtent())),
        };
    }
};

} // namespace org::parse
