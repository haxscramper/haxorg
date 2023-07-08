#pragma once

#include "Node.hpp"


template <typename N, typename K>
Str NodeGroup<N, K>::strVal(NodeGroup<N, K>::Id id) const {
    assert(notNil(tokens));
    if (at(id).isTerminal()) {
        return tokens->at(at(id).getToken()).strVal();
    } else {
        return "";
    }
}

template <typename N, typename K>
typename NodeGroup<N, K>::Id NodeGroup<N, K>::endTree(int offset) {
    Q_ASSERT(0 < pendingTrees.size());
    auto start = pendingTrees.pop_back_v();
    nodes.at(start).extend(distance(start, nodes.back()) + offset);
    return start;
}

template <typename N, typename K>
typename NodeGroup<N, K>::Id NodeGroup<N, K>::failTree(
    Node<N, K> replacement) {
    Q_ASSERT(0 < pendingTrees.size());
    auto start      = pendingTrees.pop_back_v();
    nodes.at(start) = replacement;
    return start;
}

template <typename N, typename K>
typename NodeGroup<N, K>::iterator NodeGroup<N, K>::begin(NodeGroup<N, K>::Id start) const {
    if (start.getIndex() < size()) {
        auto result = iterator(start, this);
        result.check();
        return result;
    } else {
        return end(nodes.back());
    }
}

template <typename N, typename K>
typename NodeGroup<N, K>::iterator NodeGroup<N, K>::end(NodeGroup<N, K>::Id last) const {
    ++last;
    return iterator(last, this);
}


template <typename N, typename K>
Opt<Pair<typename NodeGroup<N, K>::iterator, typename NodeGroup<N, K>::iterator>> NodeGroup<
    N,
    K>::subnodesOf(NodeGroup<N, K>::Id node) const {
    // TODO return empty range for iterator start
    if (at(node).isTerminal()) {
        return std::nullopt;

    } else {
        auto begini = begin(node + 1);
        auto endi   = end(node + at(node).getExtent());
        return Pair<iterator, iterator>{begini, endi};
    }
}

template <typename N, typename K>
Opt<Slice<typename NodeGroup<N, K>::Id>> NodeGroup<N, K>::allSubnodesOf(
    Id node) const {
    if (0 < at(node).getExtent()) {
        return slice<Id>(node + 1, node + at(node).getExtent());
    } else {
        return std::nullopt;
    }
}

template <typename N, typename K>
typename NodeGroup<N, K>::Id NodeGroup<N, K>::parent(NodeGroup<N, K>::Id node) const {
    NodeGroup<N, K>::Id parent = node;
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

template <typename N, typename K>
int NodeGroup<N, K>::size(Id node) const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int result        = 0;
        for (; begin != end; ++begin) {
            ++result;
        }
        return result;

    } else {
        return 0;
    }
}

template <typename N, typename K>
typename NodeGroup<N, K>::Id NodeGroup<N, K>::subnode(Id node, int index)
    const {
    if (auto pair = subnodesOf(node)) {
        auto [begin, end] = *pair;
        int i             = 0;
        for (; begin != end; ++begin, ++i) {
            if (i == index) {
                return *begin;
            }
        }

        throw RangeError(
            "Could not get subnode with index $# for node with id $# "
            "-- it contains only $# items"
            % to_string_vec(index, node.getUnmasked(), i));
    } else {
        qFatal("Cannot get subnode for token, TODO error msg");
    }
}

template <typename N, typename K>
void NodeGroup<N, K>::lispRepr(
    QTextStream&     os,
    Id               node,
    CR<TreeReprConf> conf) const {
    os << "(" << to_string(node.getMask()) << ":"
       << to_string(node.getUnmasked()) << " " << to_string(at(node).kind);

    if (at(node).isTerminal()) {
        auto tok = at(node).getToken();
        os << " '";
        QString     str;
        QTextStream stream{&str};
        tok.streamTo(stream, "", true);
        os << str;
        os << "'";
    } else {
        auto maybe_iter = subnodesOf(node);
        if (maybe_iter) {
            auto [begin, end] = *maybe_iter;
            for (; begin != end; ++begin) {
                os << " ";
                lispRepr(os, *begin, conf);
            }
        }
    }
    os << ")";
}

template <typename N, typename K>
void NodeGroup<N, K>::treeRepr(
    ColStream&       os,
    Id               node,
    int              level,
    CR<TreeReprConf> conf,
    int              subnodeIdx) const {

    os << repeat("  ", level);

    os << to_string(at(node).kind);
    if (conf.withSubnodeIdx) {
        os << "[" << subnodeIdx << "]";
    }

    if (conf.withTreeMask) {
        os << " MASK:" << to_string(node.getMask());
    }

    if (conf.withTreeId) {
        os << " ID:" << to_string(node.getUnmasked());
    }

    if (at(node).isTerminal()) {
        auto tok = at(node).getToken();
        if (tok.isNil()) {
            os << " # <nil>";
        } else {
            QString     str;
            QTextStream stream{&str};
            tok.streamTo(stream, "", conf.withTokenMask);
            os << " #" << str << " " << at(tok);
        }
    } else {
        if (conf.withExt) {
            os << " EXT: " << to_string(at(node).getExtent());
        }

        auto [begin, end] = subnodesOf(node).value();
        int  idx = 0;
        auto id  = end.id;
        for (; begin != end &&
               (begin.id <= end.id
                /* FIXME hack to handle tree that is created by the sweep operation  */);) {
            Q_ASSERT(id == end.id);
            Q_ASSERT(begin.id != end.id);
            Q_ASSERT(begin.id <= end.id);
            if (conf.flushEach) {
                os.flush();
            }
            os << "\n";
            treeRepr(os, *begin, level + 1, conf, idx);

            if (conf.flushEach) {
                os.flush();
            }
            ++idx;
            Id before = begin.id;
            ++begin;
            // Q_ASSERT_X(
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

    if (conf.flushEach) {
        os.flush();
    }
}

template <typename N, typename K>
QString NodeGroup<N, K>::treeRepr(Id node, CR<TreeReprConf> conf) const {
    QString     buffer;
    QTextStream os{&buffer};
    ColStream   text{os};
    treeRepr(text, node, 0, conf);
    return buffer;
}
