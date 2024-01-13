#include "Node.hpp"


template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::Id NodeGroup<N, K, V>::endTree(int offset) {
    CHECK(0 < pendingTrees.size());
    auto start = pendingTrees.pop_back_v();
    nodes.at(start).extend(distance(start, nodes.back()) + offset);
    return start;
}

template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::Id NodeGroup<N, K, V>::failTree(
    Node<N, K, V> replacement) {
    CHECK(0 < pendingTrees.size());
    auto start      = pendingTrees.pop_back_v();
    nodes.at(start) = replacement;
    return start;
}

template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::iterator NodeGroup<N, K, V>::begin(
    NodeGroup<N, K, V>::Id start) const {
    if (start.getIndex() < size()) {
        auto result = iterator(start, this);
        result.check();
        return result;
    } else {
        return end(nodes.back());
    }
}

template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::iterator NodeGroup<N, K, V>::end(
    NodeGroup<N, K, V>::Id last) const {
    ++last;
    return iterator(last, this);
}


template <typename N, typename K, typename V>
Opt<Pair<typename NodeGroup<N, K, V>::iterator, typename NodeGroup<N, K, V>::iterator>> NodeGroup<
    N,
    K,
    V>::subnodesOf(typename NodeGroup<N, K, V>::Id node) const {
    // TODO return empty range for iterator start
    if (at(node).isTerminal()) {
        return std::nullopt;

    } else {
        auto begini = begin(node + 1);
        auto endi   = end(node + at(node).getExtent());
        return Pair<iterator, iterator>{begini, endi};
    }
}

template <typename N, typename K, typename V>
Opt<Slice<typename NodeGroup<N, K, V>::Id>> NodeGroup<N, K, V>::
    allSubnodesOf(Id node) const {
    if (0 < at(node).getExtent()) {
        return slice<Id>(node + 1, node + at(node).getExtent());
    } else {
        return std::nullopt;
    }
}

template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::Id NodeGroup<N, K, V>::parent(
    NodeGroup<N, K, V>::Id node) const {
    NodeGroup<N, K, V>::Id parent = node;
    --parent;
    while (!parent.isNil()) {
        auto extent = allSubnodesOf(parent);
        if (extent.has_value()) {
            if (extent->contains(node)) {
                return parent;
            } else {
                --parent;
            }
        }
    }

    return Id::Nil();
}

template <typename N, typename K, typename V>
int NodeGroup<N, K, V>::size(Id node) const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int result        = 0;
        for (; begin != end; ++begin) { ++result; }
        return result;

    } else {
        return 0;
    }
}

template <typename N, typename K, typename V>
typename NodeGroup<N, K, V>::Id NodeGroup<N, K, V>::subnode(
    Id  node,
    int index) const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int i             = 0;
        for (; begin != end; ++begin, ++i) {
            if (i == index) { return *begin; }
        }

        throw RangeError(
            "Could not get subnode with index $# for node with id $# "
            "-- it contains only $# items"
            % to_string_vec(index, node.getUnmasked(), i));
    } else {
        LOG(FATAL) << "Cannot get subnode for token, TODO error msg";
    }
}


template <typename N, typename K, typename V>
void NodeGroup<N, K, V>::treeRepr(
    ColStream&       os,
    Id               node,
    int              level,
    CR<TreeReprConf> conf,
    int              subnodeIdx) const {

    os << repeat("  ", level) << std::format("{}", at(node).kind);
    if (conf.withSubnodeIdx) { os << fmt("[{}]", subnodeIdx); }
    if (conf.withTreeMask) { os << fmt(" MASK:{}", node.getMask()); }
    if (conf.withTreeId) { os << fmt(" ID:{}", node.getUnmasked()); }

    if (at(node).isTerminal()) {
        auto tok = at(node).getToken();
        if (tok.isNil()) {
            os << " # <nil>";
        } else {
            os << std::format("# {} {}", tok, at(tok));
        }
    } else {
        if (conf.withExt) { os << fmt(" EXT:{}", at(node).getExtent()); }

        auto [begin, end] = subnodesOf(node).value();
        int  idx          = 0;
        auto id           = end.id;
        for (; begin != end &&
               (begin.id <= end.id
                /* FIXME hack to handle tree that is created by the sweep operation  */);) {
            CHECK(id == end.id);
            CHECK(begin.id != end.id);
            CHECK(begin.id <= end.id);
            if (conf.flushEach) { os.flush(); }
            os << "\n";
            treeRepr(os, *begin, level + 1, conf, idx);

            if (conf.flushEach) { os.flush(); }
            ++idx;
            Id before = begin.id;
            ++begin;
            // CHECK_X(
            //     begin.id <= end.id,
            //     "treeRepr",
            //     "Increment of the starting operator should not go "
            //     "over the end, but transitioning over subnode [$#] "
            //     "for tree $# caused jump $# -> $# which is over the "
            //     "end ($#). Full extent of the subnode is $#, extent "
            //     "of the wrapping tree is $#"
            //         % to_string_vec(
            //             idx,
            //             node.getUnmasked(),
            //             before.getUnmasked(),
            //             begin.id.getUnmasked(),
            //             end.id.getUnmasked(),
            //             at(before).getExtent(),
            //             at(node).getExtent()));
        }
    }

    if (conf.flushEach) { os.flush(); }
}

template <typename N, typename K, typename V>
std::string NodeGroup<N, K, V>::treeRepr(Id node, CR<TreeReprConf> conf)
    const {
    std::stringstream buffer;
    ColStream         text{buffer};
    treeRepr(text, node, 0, conf);
    return buffer.str();
}
