#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>

using osk = OrgSemKind;


void ExporterMindMap::eachSubtree(
    DocSubtree::Ptr             startRoot,
    Func<void(DocSubtree::Ptr)> cb) {
    Func<void(DocSubtree::Ptr)> aux;
    aux = [&](DocSubtree::Ptr tree) {
        cb(tree);
        for (const auto& sub : tree->subtrees) {
            aux(sub);
        }
    };

    aux(startRoot);
}

void ExporterMindMap::eachEntry(
    DocSubtree::Ptr           startRoot,
    Func<void(DocEntry::Ptr)> cb) {
    eachSubtree(startRoot, [cb](DocSubtree::Ptr tree) {
        for (const auto& entry : tree->ordered) {
            cb(entry);
        }

        for (const auto& entry : tree->unordered) {
            cb(entry);
        }
    });
}

void ExporterMindMap::visitSubtree(
    std::monostate&       s,
    CR<sem::Subtree::Ptr> ptr) {
    stack.push_back(DocSubtree::shared());
    auto& res = stack.back();


    res->original = ptr;

    for (const auto& sub : ptr->subnodes) {
        if (sub->is(SemSet{osk::Newline})) {
            // Skip
        } else if (sub->is(osk::Subtree)) {
            visit(s, sub);

        } else if (
            sub->is(osk::List)
            && sub->as<sem::List>()->isDescriptionList()) {
            for (const auto& it : sub->subnodes) {
                if (it->as<sem::ListItem>()->isDescriptionItem()) {
                    res->outgoing.push_back(DocLink{.description = it});
                }
            }

        } else {
            auto entry     = DocEntry::shared();
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

    if (stack.empty()) {
        root = last;
    } else {
        stack.back()->subtrees.push_back(last);
    }
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

    if (!stack.empty()) {
        auto last = stack.pop_back_v();
        if (stack.empty()) {
            root = last;
        } else {
            stack.back()->subtrees.push_back(last);
        }
    }
}

void ExporterMindMap::visitEnd(In<sem::Org> doc) {
    eachEntry(root, [&](DocEntry::Ptr entry) {
        int id = entry->content->id.value();
        Q_ASSERT_X(
            !entriesOut.contains(id),
            "collect out entries",
            "ID $# has already been used" % to_string_vec(id));
        entriesOut[id] = entry;
    });

    eachSubtree(root, [&](DocSubtree::Ptr tree) {
        auto id = tree->original->id.value();
        Q_ASSERT_X(
            !entriesOut.contains(id),
            "collect out entries",
            "ID $# has already been used" % to_string_vec(id));
        subtreesOut[id] = tree;
    });

    eachEntry(root, [&](DocEntry::Ptr entry) {
        qDebug() << "Resolving entry content =========";
        entry->content->eachSubnodeRec([&](sem::Org::Ptr node) {
            Opt<DocLink> resolved = getResolved(node);
            if (resolved) {
                qDebug() << "Resolved" << node->id;
                ExporterTree::treeRepr(node);

                entry->outgoing.push_back(*resolved);
            }
        });
    });

    eachSubtree(root, [&](DocSubtree::Ptr tree) {
        Vec<DocLink> oldOutgoing = std::move(tree->outgoing);
        tree->outgoing.clear();
        for (const auto& out : oldOutgoing) {
            Opt<DocLink> resolved = getResolved(*out.description);
            if (resolved) {
                tree->outgoing.push_back(*resolved);
            }
        }
    });
}

Opt<ExporterMindMap::DocLink> ExporterMindMap::getResolved(
    sem::Org::Ptr node) {
    for (const auto& doc : documents) {
        // Check if the entry is the list item that can be used for
        // resolution.
        if (node->is(osk::ListItem)
            && node->as<sem::ListItem>()->isDescriptionItem()) {
            sem::ListItem::Ptr item = node->as<sem::ListItem>();
            Opt<DocLink>       resolved;
            item->header.value()->eachSubnodeRec(
                [&](CR<sem::Org::Ptr> node) {
                    if (!resolved && node->is(osk::Link)) {
                        resolved = getResolved(node);
                    }
                });
            if (resolved) {
                resolved->description = std::make_shared<sem::StmtList>();
                (**resolved->description).subnodes = item->subnodes;
                return resolved;
            }
        }

        auto resolve = doc->resolve(node);
        if (resolve) {
            auto                 id      = resolve.value()->id.value();
            Opt<DocEntry::Ptr>   target  = entriesOut.get(id);
            Opt<DocSubtree::Ptr> subtree = subtreesOut.get(id);

            if (target) {
                // TODO consider multiple documents in a group and
                // issue diagnostic message in case of duplicates
                return DocLink{
                    .resolved = DocLink::Entry{.entry = target.value()}};
            }

            if (subtree) {
                return DocLink{
                    .resolved = DocLink::Subtree{
                        .subtree = subtree.value()}};
            }
        }
    }
    return std::nullopt;
}

using G = Graphviz;

Graphviz::Graph ExporterMindMap::toGraph() {

    int subgraphCounter = 0;

    auto uniqueName = [&]() { return to_string(++subgraphCounter); };
    auto nodeName   = [](CR<sem::Org::Ptr> node) {
        return "name_" + to_string(node->id.value());
    };

    auto clusterName = [](CR<sem::Org::Ptr> node) {
        return "cluster_" + to_string(node->id.value());
    };

    auto fillOrdered = [&](Graphviz::Graph&    graph,
                           CR<DocSubtree::Ptr> doc) {
        if (doc->ordered.empty()) {
            return;
        } else if (doc->ordered.size() == 1 && doc->unordered.empty()) {
            auto node = graph.node(nodeName(doc->ordered.at(0)->content));
            node.setLabel(
                ExporterUltraplain::toStr(doc->ordered.at(0)->content));
        } else {
            Opt<Str> prev;
            auto cluster = graph.newSubgraph(clusterName(doc->original));
            cluster.setRankDirection(G::Graph::RankDirection::TB);
            for (const auto& ord : doc->ordered) {
                auto name = nodeName(ord->content);
                auto node = cluster.node(name);
                //                if (prev) {
                //                    cluster.edge(*prev, name);
                //                }
                prev = name;

                node.setLabel(ExporterUltraplain::toStr(ord->content));
            }
        }
    };

    auto fillUnordered = [&](Graphviz::Graph&    graph,
                             CR<DocSubtree::Ptr> doc) {
        for (const auto& note : doc->unordered) {
            auto node = graph.node(nodeName(note->content));
            node.setColor(Qt::red);
            node.setLabel(ExporterUltraplain::toStr(note->content));
        }
    };

    Func<void(CR<DocSubtree::Ptr>, Graphviz::Graph&)> auxSubtree;

    auxSubtree = [&](CR<DocSubtree::Ptr> doc, Graphviz::Graph& parent) {
        Graphviz::Graph graph = parent.newSubgraph(
            clusterName(doc->original));
        graph.setCompound(true);

        if (doc->original->is(osk::Subtree)) {
            graph.setLabel(ExporterUltraplain::toStr(
                doc->original->as<sem::Subtree>()->title));
        }

        fillOrdered(graph, doc);
        fillUnordered(graph, doc);

        for (const auto& it : doc->subtrees) {
            auxSubtree(it, graph);
        }

        auto subtreeNodeName = [&](DocSubtree::Ptr target) -> QString {
            if (target->ordered.empty()) {
                return nodeName(target->original);
            } else {
                return nodeName(target->ordered.at(0)->content);
            }
        };

        auto edgeTo = [&](QString const& source,
                          DocLink const& edge) -> G::Edge {
            if (edge.getKind() == DocLink::Kind::Entry) {
                return graph.edge(
                    source, nodeName(edge.getEntry().entry->content));
            } else {
                DocSubtree::Ptr target   = edge.getSubtree().subtree;
                auto            name     = subtreeNodeName(target);
                G::Edge         nodeEdge = graph.edge(source, name);

                nodeEdge.setLHead(subtreeNodeName(target));
                return nodeEdge;
            }
        };

        auto name = subtreeNodeName(doc);
        for (const auto& edge : doc->outgoing) {
            G::Edge g_edge = edgeTo(name, edge);
            g_edge.setLTail(subtreeNodeName(doc));
            g_edge.setLabel(ExporterUltraplain::toStr(*edge.description));
        }

        for (const auto& entry : doc->ordered + doc->unordered) {
            for (const auto& edge : entry->outgoing) {
                edgeTo(nodeName(entry->content), edge);
            }
        }
    };

    Q_CHECK_PTR(root);

    auto result = Graphviz::Graph("root");
    auxSubtree(root, result);


    result.setRankDirection(G::Graph::RankDirection::LR);
    result.setCompound(true);
    result.setConcentrate(true);
    Q_CHECK_PTR(result.get());
    result.defaultNode.setShape(G::Node::Shape::rect);
    Q_CHECK_PTR(result.get());
    return result;
}

json ExporterMindMap::toJson() {
    auto exportLink = [](DocLink const& link) -> json {
        json res    = json::object();
        res["kind"] = to_string(link.getKind());
        if (link.getKind() == DocLink::Kind::Entry) {
            res["entry"] = link.getEntry().entry->content->id.value();
        } else {
            res["subtree"] = link.getSubtree()
                                 .subtree->original->id.value();
        }

        return res;
    };

    auto exportEntry = [&](DocEntry::Ptr const& entry) -> json {
        json res    = json::object();
        res["kind"] = "Entry";
        res["id"]   = entry->content->id.value();

        res["outgoing"] = json::array();
        for (auto const& it : entry->outgoing) {
            res["outgoing"].push_back(exportLink(it));
        }

        return res;
    };


    Func<json(DocSubtree::Ptr)> aux;
    aux = [&](DocSubtree::Ptr tree) -> json {
        json result    = json::object();
        result["kind"] = "Subtree";
        result["id"]   = tree->original->id.value();
        if (tree->original->is(osk::Subtree)) {
            result["title"] = ExporterUltraplain::toStr(
                tree->original->as<sem::Subtree>()->title);
        } else {
            result["title"] = json();
        }

        result["subtrees"] = json::array();
        for (auto const& sub : tree->subtrees) {
            result["subtrees"].push_back(aux(sub));
        }

        result["outgoing"] = json::array();
        for (auto const& sub : tree->outgoing) {
            result["outgoing"].push_back(exportLink(sub));
        }

        result["ordered"] = json::array();
        for (auto const& sub : tree->ordered) {
            result["ordered"].push_back(exportEntry(sub));
        }

        result["unordered"] = json::array();
        for (auto const& sub : tree->unordered) {
            result["unordered"].push_back(exportEntry(sub));
        }

        return result;
    };

    return aux(root);
}
