#include "Node.hpp"

using namespace org::parse;
using namespace hstd;

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::Id NodeGroup<N, K, V, M>::endTree(
    int offset) {
    LOGIC_ASSERTION_CHECK(0 < pendingTrees.size(), "");
    auto start = pendingTrees.pop_back_v();
    nodes.at(start).extend(distance(start, nodes.back()) + offset);
    return start;
}

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::Id NodeGroup<N, K, V, M>::failTree(
    Node<N, K, V, M> replacement) {
    LOGIC_ASSERTION_CHECK(0 < pendingTrees.size(), "");
    auto start      = pendingTrees.pop_back_v();
    nodes.at(start) = replacement;
    return start;
}

template <typename N, typename K, typename V, typename M>
void NodeGroup<N, K, V, M>::removeTail(Id id) {
    nodes.content.erase(
        nodes.content.begin() + id.getIndex(), nodes.content.end());
}

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::iterator NodeGroup<N, K, V, M>::begin(
    NodeGroup<N, K, V, M>::Id start) const {
    if (start.getIndex() < size()) {
        auto result = iterator(start, this);
        result.check();
        return result;
    } else {
        return end(nodes.back());
    }
}

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::iterator NodeGroup<N, K, V, M>::end(
    NodeGroup<N, K, V, M>::Id last) const {
    ++last;
    return iterator(last, this);
}


template <typename N, typename K, typename V, typename M>
Opt<Pair<typename NodeGroup<N, K, V, M>::iterator, typename NodeGroup<N, K, V, M>::iterator>> NodeGroup<
    N,
    K,
    V,
    M>::subnodesOf(typename NodeGroup<N, K, V, M>::Id node) const {
    // TODO return empty range for iterator start
    if (at(node).isTerminal()) {
        return std::nullopt;

    } else {
        auto begini = begin(node + 1);
        auto endi   = end(node + at(node).getExtent());
        return Pair<iterator, iterator>{begini, endi};
    }
}

template <typename N, typename K, typename V, typename M>
Opt<Slice<typename NodeGroup<N, K, V, M>::Id>> NodeGroup<N, K, V, M>::
    allSubnodesOf(Id node) const {
    if (0 < at(node).getExtent()) {
        return slice<Id>(node + 1, node + at(node).getExtent());
    } else {
        return std::nullopt;
    }
}

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::Id NodeGroup<N, K, V, M>::parent(
    NodeGroup<N, K, V, M>::Id node) const {
    NodeGroup<N, K, V, M>::Id parent = node;
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

template <typename N, typename K, typename V, typename M>
int NodeGroup<N, K, V, M>::size(Id node) const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int result        = 0;
        for (; begin != end; ++begin) { ++result; }
        return result;

    } else {
        return 0;
    }
}

template <typename N, typename K, typename V, typename M>
typename NodeGroup<N, K, V, M>::Id NodeGroup<N, K, V, M>::subnode(
    Id  node,
    int index) const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int i             = 0;
        for (; begin != end; ++begin, ++i) {
            if (i == index) { return *begin; }
        }

        throw RangeError::init(
            fmt("Could not get subnode with index {} for node with id {} "
                "-- it contains only {} items",
                index,
                node.getUnmasked(),
                i));
    } else {
        throw RangeError::init(
            fmt("Node {} of kind {} does not have subnode range",
                node,
                at(node).kind));
    }
}


template <typename N, typename K, typename V, typename M>
void NodeGroup<N, K, V, M>::treeRepr(
    ColStream&       os,
    Id               node,
    int              level,
    CR<TreeReprConf> conf,
    int              subnodeIdx,
    Opt<Id>          parent) const {
    using Pos = TreeReprConf::WritePos;
    using Par = TreeReprConf::WriteParams;

    Par par{
        .os         = os,
        .current    = node,
        .parent     = parent,
        .subnodeIdx = subnodeIdx,
        .level      = level,
    };

    if (conf.customWrite) {
        par.pos = Pos::LineStart;
        conf.customWrite(par);
    }

    os << repeat("  ", level) << std::format("{}", at(node).kind);

    if (conf.customWrite) {
        par.pos = Pos::AfterKind;
        conf.customWrite(par);
    }

    if (conf.withSubnodeIdx) {
        os << os.cyan() << fmt("[{}]", subnodeIdx) << os.end();
    }

    if (conf.withTreeMask) { os << fmt(" MASK:{}", node.getMask()); }

    if (conf.withTreeId) {
        os << " " << os.blue() << fmt("ID:{}", node.getUnmasked())
           << os.end();
    }

    if (at(node).isTerminal()) {
        auto tok = at(node).getToken();
        if (tok.isNil()) {
            os << " # " << os.cyan() << "<nil>" << os.end();
        } else {
            os << " # " << fmt1(tok.getUnmasked()) << " " << os.green()
               << fmt1(at(tok).kind) << os.end() << " " << os.yellow()
               << fmt1(at(tok).value) << os.end();
        }
    } else {
        if (conf.withExt) { os << fmt(" EXT:{}", at(node).getExtent()); }

        auto [begin, end] = subnodesOf(node).value();
        int  idx          = 0;
        auto id           = end.id;
        for (; begin != end &&
               (begin.id <= end.id
                /* FIXME hack to handle tree that is created by the sweep operation  */);) {
            LOGIC_ASSERTION_CHECK(id == end.id, "");
            LOGIC_ASSERTION_CHECK(begin.id != end.id, "");
            LOGIC_ASSERTION_CHECK(begin.id <= end.id, "");
            if (conf.flushEach) { os.flush(); }
            if (conf.customWrite) {
                par.pos = Pos::LineEnd;
                conf.customWrite(par);
            }
            os << "\n";
            treeRepr(os, *begin, level + 1, conf, idx, node);

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

template <typename N, typename K, typename V, typename M>
std::string NodeGroup<N, K, V, M>::treeRepr(Id node, CR<TreeReprConf> conf)
    const {
    std::stringstream buffer;
    ColStream         text{buffer};
    text.colored = false;
    treeRepr(text, node, 0, conf);
    return buffer.str();
}
