#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>

int ExporterMindMap::DocEntry::counter = 0;

using osk = OrgSemKind;


void ExporterMindMap::visitSubtree(
    std::monostate&       s,
    CR<sem::Subtree::Ptr> ptr) {
    stack.push_back(DocSubtree::shared());
    auto& res = stack.back();
    if (stack.size() == 1) {
        root = stack.back();
    }


    res->original = ptr;

    for (const auto& sub : ptr->subnodes) {
        if (sub->is(SemSet{osk::Newline})) {
            // Skip
        } else if (sub->is(osk::Subtree)) {
            visit(s, sub);

        } else {
            auto entry     = newEntry();
            entry->content = sub;
            if (sub->is(osk::Paragraph)
                && sub->as<sem::Paragraph>()->isFootnoteDefinition()) {
                res->unordered.push_back(entry);
            } else {
                res->ordered.push_back(entry);
            }
        }
    }

    auto last = stack.pop_back_v();
    stack.back()->subtrees.push_back(last);
}

void ExporterMindMap::visitDocument(
    std::monostate&        s,
    CR<sem::Document::Ptr> doc) {
    stack.push_back(DocSubtree::shared());


    stack.back()->original = doc;
    documents.push_back(doc);
    for (const auto& sub : doc->subnodes) {
        visit(s, sub);
    }

    if (stack.size() == 1) {
        root = stack.pop_back_v();
    } else {
        auto last = stack.pop_back_v();
        stack.back()->subtrees.push_back(last);
    }
}

void ExporterMindMap::visitEnd(In<sem::Org> doc) {
    UnorderedMap<int, DocEntry::Ptr> entriesOut;
    for (auto const& entry : entryList) {
        int id         = entry->content->id.value();
        entriesOut[id] = entry;
        qDebug() << "Entry ID" << id;
    }

    UnorderedMap<int, DocSubtree::Ptr> subtreesOut;
    Func<void(DocSubtree::Ptr)>        aux;
    aux = [&](DocSubtree::Ptr tree) {
        subtreesOut[tree->original->id.value()] = tree;
        for (auto sub : tree->subtrees) {
            aux(sub);
        }
    };


    auto getResolved = [&](sem::Org::Ptr node) {
        Opt<DocLink> resolved;
        for (const auto& doc : documents) {
            auto resolve = doc->resolve(node);
            if (resolve) {
                Opt<DocEntry::Ptr> target = entriesOut.get(
                    resolve.value()->id.value());
                if (target) {
                    qDebug() << "Resolved link to paragraph";
                    resolved = DocLink{.resolved = target.value()};
                    // TODO consider multiple documents in a group and
                    // issue diagnostic message in case of duplicates
                    break;
                }

                Opt<DocSubtree::Ptr> subtree = subtreesOut.get(
                    resolve.value()->id.value());
                if (subtree) {
                    qDebug() << "Resolved link to subtree";
                    resolved = DocLink{.resolved = subtree.value()};
                    break;
                }
            }
        }

        return resolved;
    };

    for (auto& entry : entryList) {
        entry->content->eachSubnodeRec([&](sem::Org::Ptr node) {
            Opt<DocLink> resolved = getResolved(node);
            if (resolved) {
                entry->outgoing.push_back(*resolved);
            }
        });
    }
}

using G = Graphviz;

Graphviz::Graph ExporterMindMap::toGraph() {
    Func<Opt<Graphviz::Graph>(
        CR<DocSubtree::Ptr>, CR<Opt<Graphviz::Graph>>)>
        auxSubtree;

    int subgraphCounter = 0;

    auto uniqueName = [&]() { return to_string(++subgraphCounter); };
    auto nodeName   = [](CR<sem::Org::Ptr> node) {
        return "name" + to_string(node->id.value());
    };

    auto fillOrdered = [&](Graphviz::Graph&    graph,
                           CR<DocSubtree::Ptr> doc) {
        if (doc->ordered.empty()) {
            return;
        } else if (doc->ordered.size() == 1) {
            auto node = graph.node(nodeName(doc->ordered.at(0)->content));
            node.setLabel(
                ExporterUltraplain::toStr(doc->ordered.at(0)->content));
        } else {
            Opt<Str> prev;
            auto     cluster = graph.newSubgraph("cluster" + uniqueName());
            cluster.setRankDirection(G::Graph::RankDirection::TB);
            for (const auto& ord : doc->ordered) {
                auto name = nodeName(ord->content);
                auto node = cluster.node(name);
                if (prev) {
                    cluster.edge(*prev, name);
                }
                prev = name;

                node.setLabel(ExporterUltraplain::toStr(ord->content));
            }
        }
    };

    auxSubtree = [&](CR<DocSubtree::Ptr>  doc,
                     Opt<Graphviz::Graph> parent) -> Opt<Graphviz::Graph> {
        if (doc->subtrees.empty()) {
            auto canvas = parent ? *parent : Graphviz::Graph("root");
            fillOrdered(canvas, doc);
            return canvas;
        } else {
            auto result = parent
                            ? parent->newSubgraph("cluster" + uniqueName())
                            : Graphviz::Graph("root");

            fillOrdered(result, doc);

            for (const auto& it : doc->subtrees) {
                auxSubtree(it, result);
            }

            return result;
        }
    };

    Q_CHECK_PTR(root);
    auto result = auxSubtree(root, std::nullopt);


    for (const auto& entry : entryList) {
        for (const auto& edge : entry->outgoing) {
            if (edge.resolved.index() == 0) {
                result->edge(
                    nodeName(entry->content),
                    nodeName(std::get<0>(edge.resolved)->content));
            } else {
                result->edge(
                    nodeName(entry->content),
                    nodeName(std::get<1>(edge.resolved)->original));
            }
        }
    }

    result->setRankDirection(G::Graph::RankDirection::LR);
    Q_CHECK_PTR(result->get());
    result->defaultNode.setShape(G::Node::Shape::rect);
    Q_CHECK_PTR(result->get());
    return result.value();
}
