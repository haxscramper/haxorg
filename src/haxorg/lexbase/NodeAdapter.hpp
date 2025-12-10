#pragma once

#include <haxorg/lexbase/Node.hpp>
#include <haxorg/lexbase/NodeStore.hpp>

namespace org::parse {

/// \brief Node adapter for more convenient access operations on the tree
template <typename N, typename K, typename V, typename M>
struct NodeAdapter {
    NodeGroup<N, K, V, M> const* group;
    NodeId<N, K, V, M>           id;

    N    getKind() const { return group->at(id).kind; }
    bool empty() const { return size() == 0; }
    int  size() const { return group->size(id); }
    /// \brief Check if node adapter is default-constructed and does not
    /// contain pointers to the underlying content.
    bool isNil() const {
        return group == nullptr && id == NodeId<N, K, V, M>::Nil();
    }

    V const& val() const { return group->val(id); }
    N        kind() const { return group->at(id).kind; }
    bool     isTerminal() const { return group->at(id).isTerminal(); }
    bool     isMono() const { return group->at(id).isMono(); }
    M const  getMono() const { return group->at(id).getMono(); }
    bool isNonTerminal() const { return group->at(id).isNonTerminal(); }

    Node<N, K, V, M> const& get() const { return group->at(id); }


    NodeAdapter<N, K, V, M>(
        NodeGroup<N, K, V, M> const* group,
        NodeId<N, K, V, M>           id)
        : group(group), id(id) {
        LOGIC_ASSERTION_CHECK(group->nodes.contains(id), "");
    }

    NodeAdapter() : group(nullptr), id(NodeId<N, K, V, M>::Nil()) {}

    // FIXME temporary workaround until I figure out how to properly fix
    // invalid index genenerated by the tree sweep in parser in certain
    // cases. At the moment it is not fully clear what is causing creation
    // of a separate node group.
    bool isValid() const {
        return !id.isNil() && id.getIndex() < group->size();
    }

    NodeAdapter<N, K, V, M> at(int index) const {
        return {group, group->subnode(id, index)};
    }

    NodeAdapter<N, K, V, M> operator[](int index) const {
        return {group, group->subnode(id, index)};
    }


    void treeRepr(
        hstd::ColStream&                                    os,
        int                                                 level = 0,
        typename NodeGroup<N, K, V, M>::TreeReprConf const& conf =
            typename NodeGroup<N, K, V, M>::TreeReprConf()) const {
        group->treeRepr(os, id, level, conf);
    }

    std::string treeRepr(bool colored = true) const {
        std::stringstream buffer;
        hstd::ColStream   text{buffer};
        text.colored = colored;
        treeRepr(text);
        return buffer.str();
    }

    hstd::generator<NodeAdapter<N, K, V, M>> items() {
        for (int i = 0; i < group->size(id); ++i) {
            co_yield this->operator[](i);
        }
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
        typename NodeGroup<N, K, V, M>::iterator iter;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef NodeAdapter<N, K, V, M>   value_type;
        typedef NodeAdapter<N, K, V, M>*  pointer;
        typedef NodeAdapter<N, K, V, M>&  reference;
        typedef std::ptrdiff_t            difference_type;

        iterator(typename NodeGroup<N, K, V, M>::iterator iter)
            : iter(iter) {}

        NodeAdapter<N, K, V, M> operator*() const {
            return NodeAdapter<N, K, V, M>(iter.group, iter.id);
        }

        iterator& operator++() {
            // increment current iterator state
            ++iter;
            return *this;
        }

        bool operator!=(const iterator& other) {
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

    iterator end() {
        return iterator(group->end(id + group->at(id).getExtent()));
    }

    iterator begin() const {
        if ((id + 1).getIndex() < group->size()) {
            return iterator(group->begin(id + 1));
        } else {
            return end();
        }
    }

    iterator end() const {
        return iterator(group->end(id + group->at(id).getExtent()));
    }
};

} // namespace org::parse
