#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>

int ExporterMindMap::DocEntry::counter   = 0;
int ExporterMindMap::DocSubtree::counter = 0;

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

using namespace boost;


ExporterMindMap::Graph ExporterMindMap::toGraph() {
    Graph result;

    auto auxEntry = [&](CR<DocEntry::Ptr> entry,
                        Opt<int>          idx) -> VertDesc {
        return add_vertex(
            VertexProp{
                .data = VertexProp::Entry{.entry = entry, .order = idx}},
            result);
    };

    Func<VertDesc(CR<DocSubtree::Ptr>)> auxSubtree;


    auxSubtree = [&](CR<DocSubtree::Ptr> tree) -> VertDesc {
        VertDesc desc = add_vertex(
            VertexProp{.data = VertexProp::Subtree{.subtree = tree}},
            result);

        for (const auto& sub : tree->subtrees) {
            VertDesc nested = auxSubtree(sub);
            add_edge(
                desc,
                nested,
                EdgeProp{.data = EdgeProp::NestedIn{}},
                result);
        }

        for (const auto& [idx, sub] : enumerate(tree->ordered)) {
            auto entry = auxEntry(sub, idx);
            add_edge(
                desc,
                entry,
                EdgeProp{.data = EdgeProp::PlacedIn{}},
                result);
        }

        for (const auto& sub : tree->unordered) {
            auto entry = auxEntry(sub, std::nullopt);
            add_edge(
                desc,
                entry,
                EdgeProp{.data = EdgeProp::PlacedIn{}},
                result);
        }

        return desc;
    };


    auxSubtree(root);

    UnorderedMap<int, VertDesc> subtreeNodes;
    UnorderedMap<int, VertDesc> entryNodes;

    for (auto vp = vertices(result); vp.first != vp.second; ++vp.first) {
        VertexProp const& prop = result[*vp.first];
        if (prop.getKind() == VertexProp::Kind::Entry) {
            entryNodes[prop.getEntry().entry->id] = *vp.first;
        } else {
            subtreeNodes[prop.getSubtree().subtree->id] = *vp.first;
        }
    }

    auto addLink = [&](VertDesc desc, CR<DocLink> link) {
        if (link.getKind() == DocLink::Kind::Entry) {
            add_edge(
                desc,
                entryNodes[link.getEntry().entry->id],
                EdgeProp{.data = EdgeProp::RefersTo{.target = link}},
                result);
        } else {
            add_edge(
                desc,
                subtreeNodes[link.getSubtree().subtree->id],
                EdgeProp{.data = EdgeProp::RefersTo{.target = link}},
                result);
        }
    };

    eachEntry(root, [&](DocEntry::Ptr entry) {
        for (const auto& out : entry->outgoing) {
            addLink(entryNodes[entry->id], out);
        }
    });

    eachSubtree(root, [&](DocSubtree::Ptr subtree) {
        for (const auto& out : subtree->outgoing) {
            addLink(subtreeNodes[subtree->id], out);
        }
    });

    return result;
}

QString ExporterMindMap::toGraphML(CR<Graph> graph) { return ""; }

namespace {
QString toPlainStr(sem::Org::Ptr org) {
    if (org->is(osk::Subtree)) {
        return toPlainStr(org->as<sem::Subtree>()->title);
    } else if (org->is(osk::Document)) {
        return "Document";
    } else {
        return Graphviz::alignText(
            ExporterUltraplain::toStr(org), Graphviz::TextAlign::Left);
    }
}
} // namespace


QString ExporterMindMap::toGraphviz(CR<Graph> graph) {
    std::stringstream         os;
    boost::dynamic_properties dp;

    auto getOrgNode = [](VertexProp const& prop) {
        if (prop.getKind() == VertexProp::Kind::Entry) {
            return prop.getEntry().entry->content;
        } else {
            return prop.getSubtree().subtree->original;
        }
    };


    dp.property("node_id", get(vertex_index, graph))
        .property(
            "splines",
            boost::make_constant_property<Graph*>(std::string("polyline")))
        .property(
            "shape",
            boost::make_constant_property<Graph::vertex_descriptor>(
                std::string("rect")))
        .property(
            "org_id",
            make_transform_value_property_map<int>(
                [&](VertexProp const& prop) -> int {
                    return getOrgNode(prop)->id.value();
                },
                get(vertex_bundle, graph)))
        .property(
            "label",
            make_transform_value_property_map<std::string>(
                [&](VertexProp const& prop) -> std::string {
                    return toPlainStr(getOrgNode(prop)).toStdString();
                },
                get(vertex_bundle, graph)));


    write_graphviz_dp(os, graph, dp);

    return QString::fromStdString(os.str());
}

using G = Graphviz;


Graphviz::Graph ExporterMindMap::toCGraph() {

    int subgraphCounter = 0;

    auto uniqueName = [&]() { return to_string(++subgraphCounter); };
    auto nodeName   = [](CR<sem::Org::Ptr> node) {
        return "name_" + to_string(node->id.value());
    };

    auto clusterName = [](CR<sem::Org::Ptr> node) {
        return "cluster_" + to_string(node->id.value());
    };


    auto nodeFor = [&](Graphviz::Graph& graph, sem::Org::Ptr org) {
        auto node = graph.node(nodeName(org));
        node.setAttr("org_id", org->id.value());
        node.setLabel(toPlainStr(org));
        return node;
    };

    auto fillOrdered = [&](Graphviz::Graph&    graph,
                           CR<DocSubtree::Ptr> doc) {
        if (doc->ordered.empty()) {
            return;
        } else if (doc->ordered.size() == 1 && doc->unordered.empty()) {
            nodeFor(graph, doc->ordered.at(0)->content);
        } else {
            auto cluster = graph.newSubgraph(clusterName(doc->original));
            cluster.setRankDirection(G::Graph::RankDirection::TB);
            for (const auto& ord : doc->ordered) {
                auto node = nodeFor(cluster, ord->content);
            }
        }
    };

    auto fillUnordered = [&](Graphviz::Graph&    graph,
                             CR<DocSubtree::Ptr> doc) {
        for (const auto& note : doc->unordered) {
            auto node = nodeFor(graph, note->content);
            node.setColor(Qt::red);
        }
    };

    Func<void(CR<DocSubtree::Ptr>, Graphviz::Graph&)> auxSubtree;

    auxSubtree = [&](CR<DocSubtree::Ptr> doc, Graphviz::Graph& parent) {
        Graphviz::Graph graph = parent.newSubgraph(
            clusterName(doc->original));
        graph.setCompound(true);

        //        if (doc->original->is(osk::Subtree)) {
        //            graph.setLabel(ExporterUltraplain::toStr(
        //                doc->original->as<sem::Subtree>()->title));
        //        }

        fillOrdered(graph, doc);
        fillUnordered(graph, doc);

        for (const auto& it : doc->subtrees) {
            auxSubtree(it, graph);
        }

        auto subtreeNode = [&](DocSubtree::Ptr target) -> G::Node {
            if (target->ordered.empty()) {
                return nodeFor(graph, target->original);
            } else {
                return nodeFor(graph, target->ordered.at(0)->content);
            }
        };

        auto edgeTo = [&](G::Node const& source,
                          DocLink const& edge) -> G::Edge {
            if (edge.getKind() == DocLink::Kind::Entry) {
                return graph.edge(
                    source,
                    nodeFor(graph, edge.getEntry().entry->content));
            } else {
                DocSubtree::Ptr target   = edge.getSubtree().subtree;
                G::Node         node     = subtreeNode(target);
                G::Edge         nodeEdge = graph.edge(source, node);
                nodeEdge.setLHead(node);
                return nodeEdge;
            }
        };

        G::Node name = subtreeNode(doc);
        for (const auto& edge : doc->outgoing) {
            G::Edge g_edge = edgeTo(name, edge);
            g_edge.setLTail(subtreeNode(doc));
            g_edge.setLabel(ExporterUltraplain::toStr(*edge.description));
        }

        for (const auto& entry : doc->ordered + doc->unordered) {
            for (const auto& edge : entry->outgoing) {
                edgeTo(nodeFor(graph, entry->content), edge);
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
