#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <exporters/ExporterJson.hpp>
#include <boost/property_map/function_property_map.hpp>

using osk = OrgSemKind;
using namespace boost;

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
    DocSubtree::Ptr                                   startRoot,
    Func<void(DocEntry::Ptr, const DocSubtree::Ptr&)> cb) {
    eachSubtree(startRoot, [cb](DocSubtree::Ptr tree) {
        for (const auto& entry : tree->ordered) {
            cb(entry, tree);
        }

        for (const auto& entry : tree->unordered) {
            cb(entry, tree);
        }
    });
}

void ExporterMindMap::visitSubtree(
    std::monostate&           s,
    sem::SemIdT<sem::Subtree> ptr) {

    Opt<DocSubtree::Ptr> top;
    if (!stack.empty()) {
        stack.back();
    }

    stack.push_back(DocSubtree::shared());

    auto& res     = stack.back();
    res->parent   = top;
    res->original = ptr;

    for (const auto& sub : ptr->subnodes) {
        if (sub->is(SemSet{osk::Newline, osk::Space})) {
            // Skip
        } else if (sub->is(osk::Subtree)) {
            visit(s, sub);

        } else if (
            sub->is(osk::List)
            && sub.as<sem::List>()->isDescriptionList()) {
            for (const auto& it : sub->subnodes) {
                if (it->is(osk::ListItem)) {
                    if (it.as<sem::ListItem>()->isDescriptionItem()) {
                        // Push temporary outgoing doc link -- all links
                        // will be resolved in the `visitEnd` once the
                        // whole document is mapped out.
                        res->outgoing.push_back(DocLink{
                            .description = it,
                            .parent      = top,
                            .location    = it,
                        });
                    }
                } else {
                    // TODO
                }
            }

        } else {
            auto entry     = DocEntry::shared();
            entry->parent  = top;
            entry->content = sub;

            if (sub->is(osk::Paragraph)
                && sub.as<sem::Paragraph>()->isFootnoteDefinition()) {
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
    std::monostate&            s,
    sem::SemIdT<sem::Document> doc) {
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

void ExporterMindMap::visitEnd(sem::SemId doc) {
    entriesOut.clear();
    eachEntry(
        root, [&](DocEntry::Ptr entry, DocSubtree::Ptr const& parent) {
            auto id = entry->content;
            Q_ASSERT_X(
                !entriesOut.contains(id),
                "map outgoing entries",
                "ID $# has already been used" % to_string_vec(id));

            entriesOut[id] = entry;
        });

    subtreesOut.clear();
    eachSubtree(root, [&](DocSubtree::Ptr tree) {
        Q_ASSERT_X(
            !subtreesOut.contains(tree->original),
            "map outgoing subtrees",
            "ID $# $# has already been used"
                % to_string_vec(
                    tree->original,
                    ExporterUltraplain::toStr(
                        tree->original.as<sem::Subtree>()->title)));

        subtreesOut[tree->original] = tree;
    });

    eachEntry(
        root, [&](DocEntry::Ptr entry, DocSubtree::Ptr const& parent) {
            entry->content.eachSubnodeRec([&](sem::SemId node) {
                Opt<DocLink> resolved = getResolved(node, parent);
                if (resolved) {
                    entry->outgoing.push_back(*resolved);
                } else {
                    // TODO: Diagnostic required
                }
            });
        });

    eachSubtree(root, [&](DocSubtree::Ptr tree) {
        // Move old list of outoing links out and replace it with a list of
        // fully resolved links.
        Vec<DocLink> oldOutgoing = std::move(tree->outgoing);
        tree->outgoing.clear();
        for (const auto& out : oldOutgoing) {
            Opt<DocLink> resolved = getResolved(*out.description, tree);
            if (resolved) {
                tree->outgoing.push_back(*resolved);
            } else {
                // TODO: Diagnostic for unresolved links
            }
        }
    });
}

Opt<ExporterMindMap::DocLink> ExporterMindMap::getResolved(
    sem::SemId                  node,
    Opt<DocSubtree::Ptr> const& parent) {

    for (const auto& doc : documents) {
        // Check if the entry is the list item that can be used for
        // resolution.
        if (node->is(osk::ListItem)
            && node.as<sem::ListItem>()->isDescriptionItem()) {
            sem::SemIdT<sem::ListItem> item = node.as<sem::ListItem>();
            Opt<DocLink>               resolved;
            item->header.value().eachSubnodeRec([&](CR<sem::SemId> node) {
                if (!resolved && node->is(osk::Link)) {
                    resolved = getResolved(node, parent);
                }
            });
            if (resolved) {
                resolved->description = node.context->createInSame(
                    node, osk::StmtList, node);
                (*resolved->description)->subnodes = item->subnodes;
                resolved->parent                   = parent;
                return resolved;
            }
        }

        auto resolve = doc->resolve(node);
        if (resolve) {
            sem::SemId           id      = resolve.value();
            Opt<DocEntry::Ptr>   entry   = entriesOut.get(id);
            Opt<DocSubtree::Ptr> subtree = subtreesOut.get(id);

            if (entry) {
                // TODO consider multiple documents in a group and
                // issue diagnostic message in case of duplicates
                return DocLink{
                    .parent   = parent,
                    .resolved = Node{entry.value()},
                    .location = node,
                };
            }

            if (subtree) {
                return DocLink{
                    .parent   = parent,
                    .resolved = Node{subtree.value()},
                    .location = node,
                };
            }
        }
    }
    return std::nullopt;
}

Opt<ExporterMindMap::Node> ExporterMindMap::getParentNode(
    sem::SemId node) const {
    for (sem::SemId parent : node.getParentChain(true)) {
        if (entriesOut.contains(parent)) {
            return Node(entriesOut.at(parent));
        } else if (subtreesOut.contains(parent)) {
            return Node(subtreesOut.at(parent));
        }
    }

    return std::nullopt;
}

ExporterMindMap::VertDesc ExporterMindMap::getVertex(
    CR<DocLink> link) const {
    if (link.isEntry()) {
        return entryNodes.at(link.getEntry().entry->content);
    } else {
        return subtreeNodes.at(link.getSubtree().subtree->original);
    }
}

Opt<ExporterMindMap::VertDesc> ExporterMindMap::getVertex(
    sem::SemId id) const {
    if (entryNodes.contains(id)) {
        return entryNodes.at(id);
    } else if (subtreeNodes.contains(id)) {
        return subtreeNodes.at(id);
    } else {
        return std::nullopt;
    }
}

using namespace boost;


ExporterMindMap::Graph& ExporterMindMap::toGraph() {
    graph.clear();
    subtreeNodes.clear();
    entryNodes.clear();

    auto auxEntry = [&](CR<DocEntry::Ptr> entry,
                        Opt<int>          idx) -> VertDesc {
        return add_vertex(
            VertexProp{
                .data = VertexProp::Entry{.entry = entry, .order = idx}},
            graph);
    };

    Func<VertDesc(CR<DocSubtree::Ptr>)> auxSubtree;


    auxSubtree = [&](CR<DocSubtree::Ptr> tree) -> VertDesc {
        VertDesc desc = add_vertex(
            VertexProp{.data = VertexProp::Subtree{.subtree = tree}},
            graph);

        for (const auto& sub : tree->subtrees) {
            VertDesc nested = auxSubtree(sub);
            add_edge(
                desc,
                nested,
                EdgeProp{.data = EdgeProp::NestedIn{}},
                graph);
        }

        for (const auto& [idx, sub] : enumerate(tree->ordered)) {
            auto entry = auxEntry(sub, idx);
            add_edge(
                desc,
                entry,
                EdgeProp{.data = EdgeProp::PlacedIn{}},
                graph);
        }

        for (const auto& sub : tree->unordered) {
            auto entry = auxEntry(sub, std::nullopt);
            add_edge(
                desc,
                entry,
                EdgeProp{.data = EdgeProp::PlacedIn{}},
                graph);
        }


        return desc;
    };


    auxSubtree(root);

    for (auto vp = vertices(graph); vp.first != vp.second; ++vp.first) {
        VertexProp const& prop = graph[*vp.first];
        if (prop.getKind() == VertexProp::Kind::Entry) {
            entryNodes[prop.getEntry().entry->content] = *vp.first;
        } else {
            subtreeNodes[prop.getSubtree().subtree->original] = *vp.first;
        }
    }

    auto addEdge =
        [&](VertDesc desc, CR<DocLink> link, CR<EdgeProp> prop) {
            add_edge(desc, getVertex(link), prop, graph);
        };

    auto addLink = [&](VertDesc desc, CR<DocLink> link) {
        if (link.isEntry()) {
            addEdge(
                desc,
                link,
                EdgeProp{
                    .location = link.location,
                    .data     = EdgeProp::RefersTo{.target = link}});
        } else {
            addEdge(
                desc,
                link,
                EdgeProp{
                    .location = link.location,
                    .data     = EdgeProp::RefersTo{.target = link}});
        }
    };

    eachEntry(
        root, [&](DocEntry::Ptr entry, DocSubtree::Ptr const& parent) {
            for (const auto& out : entry->outgoing) {
                addLink(entryNodes[entry->content], out);
            }
        });

    eachSubtree(root, [&](DocSubtree::Ptr subtree) {
        auto const& id = subtreeNodes[subtree->original];
        for (const auto& out : subtree->outgoing) {
            addLink(id, out);
        }

        for (const auto& out : subtree->ordered) {
            for (DocLink const& link : out->outgoing) {
                if (link.isSubtree()) {
                    addEdge(
                        id,
                        link,
                        EdgeProp{
                            .data     = EdgeProp::InternallyRefers{},
                            .location = link.location,
                        });
                }
            }
        }

        for (auto const& out : subtree->unordered) {
            for (DocLink const& link : out->outgoing) {
                if (link.isSubtree()) {
                    addEdge(
                        id,
                        link,
                        EdgeProp{
                            .data     = EdgeProp::InternallyRefers{},
                            .location = link.location,
                        });
                }
            }
        }
    });

    return graph;
}

QString ExporterMindMap::toGraphML() { return ""; }

namespace {
QString toPlainStr(sem::SemId org) {
    if (org->is(osk::Subtree)) {
        return toPlainStr(org.as<sem::Subtree>()->title);
    } else if (org->is(osk::Document)) {
        return "Document";
    } else {
        return Graphviz::alignText(
            ExporterUltraplain::toStr(org), Graphviz::TextAlign::Left);
    }
}
} // namespace


QString ExporterMindMap::toGraphviz() {
    std::stringstream         os;
    boost::dynamic_properties dp;

    auto getOrgNode = [](VertexProp const& prop) {
        if (prop.getKind() == VertexProp::Kind::Entry) {
            return prop.getEntry().entry->content;
        } else {
            return prop.getSubtree().subtree->original;
        }
    };


    dp
        // Original node ID map
        .property("node_id", get(vertex_index, graph))
        // Graph property configuration
        .property(
            "splines",
            boost::make_constant_property<Graph*>(std::string("polyline")))
        // Default node shape configuration
        .property(
            "shape",
            boost::make_constant_property<Graph::vertex_descriptor>(
                std::string("rect")))
        // Edge descriptor map
        .property(
            "out_index",
            boost::make_function_property_map<EdgeDesc, int>(
                [&](EdgeDesc const& prop) -> int {
                    return edgeOutIndex(prop);
                }))
        // Vertex property map
        .property(
            "org_id",
            make_transform_value_property_map<std::string>(
                [&](VertexProp const& prop) -> std::string {
                    return getOrgNode(prop).getReadableId().toStdString();
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

json ExporterMindMap::toJsonGraph() {
    Graph const& g     = graph;
    json         nodes = json::object();
    json         edges = json::array();

    auto vertexId = [&](VertDesc v) { return getId(g[v]); };

    for (auto [it, it_end] = boost::edges(g); it != it_end; ++it) {
        edges.push_back(toJsonGraphEdge(*it));
    }

    for (auto [it, it_end] = boost::vertices(g); it != it_end; ++it) {
        nodes[vertexId(*it).toStdString()] = toJsonGraphNode(*it);
    }

    json result        = json::object();
    result["nodes"]    = nodes;
    result["edges"]    = edges;
    result["metadata"] = json::object();
    result["type"]     = "Haxorg MindMap Export";
    return result;
}

json ExporterMindMap::toJsonGraphNode(CR<VertDesc> n) {
    Graph const& g    = graph;
    json         node = json::object();
    json         meta = json::object();
    meta["kind"]      = to_string(g[n].getKind());
    meta["id"]        = getId(g[n]);

    switch (g[n].getKind()) {
        case VertexProp::Kind::Subtree: {
            auto tree = g[n].getSubtree();
            if (tree.subtree->original.is(osk::Subtree)) {
                auto id       = tree.subtree->original.as<sem::Subtree>();
                auto title    = id->title;
                meta["title"] = ExporterUltraplain::toStr(title);
                ExporterJson exp = getJsonExporter();
                exp.visitSubtreeValueFields(meta, id);
            }

            if (tree.subtree->parent) {
                meta["parent"] = getId(tree.subtree->parent.value());
            } else {
                meta["parent"] = json();
            }


            if (!tree.subtree->subtrees.empty()) {
                json nested = json::array();
                for (auto const& sub : tree.subtree->subtrees) {
                    nested.push_back(getId(sub));
                }
                meta["nested"] = nested;
            }

            if (!tree.subtree->ordered.empty()) {
                json ordered = json::array();
                for (auto const& sub : tree.subtree->ordered) {
                    ordered.push_back(getId(sub));
                }
                meta["ordered"] = ordered;
            }


            if (!tree.subtree->unordered.empty()) {
                json unordered = json::array();
                for (auto const& sub : tree.subtree->unordered) {
                    unordered.push_back(getId(sub));
                }

                meta["unordered"] = unordered;
            }

            break;
        }
        case VertexProp::Kind::Entry: {
            auto entry = g[n].getEntry();
            if (entry.entry->parent) {
                meta["parent"] = getId(entry.entry->parent.value());
            } else {
                meta["parent"] = json();
            }

            if (!entry.entry->content.isNil()) {
                auto exp        = getJsonExporter();
                meta["content"] = exp.visitTop(entry.entry->content);
            }

            if (entry.order) {
                meta["order"] = entry.order.value();
            }


            if (!entry.entry->outgoing.empty()) {
                json out = json::array();
                int  idx = 0;
                for (auto [it, it_end] = out_edges(n, g); it != it_end;
                     ++it) {
                    auto e              = *it;
                    json target         = json::object();
                    target["out_index"] = idx;
                    target["target"]    = getId(g[boost::target(e, g)]);
                    target["source"]    = getId(g[boost::source(e, g)]);
                    out.push_back(target);
                    ++idx;
                }

                meta["outgoing"] = out;
            }

            break;
        }
    }

    node["metadata"] = meta;
    return node;
}

json ExporterMindMap::toJsonGraphEdge(CR<EdgeDesc> e) {
    Graph const&    g    = graph;
    json            res  = json::object();
    EdgeProp const& edge = g[e];
    res["source"]        = getId(g[source(e, g)]);
    res["target"]        = getId(g[target(e, g)]);
    json meta            = json::object();
    meta["kind"]         = to_string(edge.getKind());
    if (edge.getKind() == EdgeProp::Kind::RefersTo
        && edge.getRefersTo().target.description) {
        auto exp            = getJsonExporter();
        meta["description"] = exp.visitTop(
            edge.getRefersTo().target.description.value());
    }

    meta["out_index"] = edgeOutIndex(e);
    res["metadata"]   = meta;
    return res;
}

int ExporterMindMap::edgeOutIndex(CR<EdgeDesc> e) {
    Graph const& g   = graph;
    int          idx = 0;
    for (auto [it, it_end] = boost::out_edges(source(e, g), g);
         it != it_end;
         ++it) {

        if (*it == e) {
            return idx;
        }
        ++idx;
    }

    return idx;
}

QString ExporterMindMap::getId(const VertexProp& prop) {
    switch (prop.getKind()) {
        case VertexProp::Kind::Subtree:
            return getId(prop.getSubtree().subtree);
        case VertexProp::Kind::Entry: return getId(prop.getEntry().entry);
    }
}

QString ExporterMindMap::getId(sem::SemId id) {
    return to_string(id.getStoreIndex()) + "_" + to_string(id.getKind())
         + "_" + to_string(id.getNodeIndex());
}

QString ExporterMindMap::getId(const DocEntry::Ptr& entry) {
    return getId(entry->content);
}

QString ExporterMindMap::getId(const DocSubtree::Ptr& entry) {
    return getId(entry->original);
}

QString ExporterMindMap::getId(const DocLink& link) {
    switch (link.getKind()) {
        case Node::Kind::Entry: return getId(link.getEntry().entry);
        case Node::Kind::Subtree: return getId(link.getSubtree().subtree);
    }
}

ExporterMindMap::MindMapJsonExporter ExporterMindMap::getJsonExporter() {
    MindMapJsonExporter exp;
    exp.skipId         = true;
    exp.skipLocation   = true;
    exp.skipEmptyLists = true;
    exp.skipNullFields = true;

    exp.visitCb = [&](json& res, sem::SemId id) {
        json map = json::object();
        if (entriesOut.contains(id) && entriesOut.get(id)) {
            map["entry"] = getId(entriesOut.get(id).value());
        }

        if (subtreesOut.contains(id) && subtreesOut.get(id)) {
            map["subtree"] = getId(subtreesOut.get(id).value());
        }

        if (id.is(osk::Link)) {
            Opt<Node> owner  = getParentNode(id);
            auto      parent = id->getParentSubtree();

            Opt<DocLink> resolved = getResolved(
                id,
                parent ? subtreesOut.get(parent.value()) : std::nullopt);

            if (resolved) {
                DocLink const& link   = resolved.value();
                json           target = json::object();

                map["target"] = getId(resolved.value());
                if (owner) {
                    int idx = 0;
                    for (auto [it, it_end] = boost::out_edges(
                             getVertex(owner->getOrgNode()).value(),
                             graph);
                         it != it_end;
                         ++it) {
                        if (graph[*it].location == id) {
                            map["out_index"] = idx;
                            break;
                        }
                        ++idx;
                    }
                    map["source"] = getId(owner->getOrgNode());
                }
            }
        }

        if (!map.empty()) {
            res["map"] = map;
        }
    };

    return exp;
}

json ExporterMindMap::toJsonTree() {
    auto exportLink = [](DocLink const& link) -> json {
        json res    = json::object();
        res["kind"] = to_string(link.getKind());
        if (link.isEntry()) {
            res["entry"] = link.getEntry().entry->content.id;
        } else {
            res["subtree"] = link.getSubtree().subtree->original.id;
        }

        return res;
    };

    auto exportEntry = [&](DocEntry::Ptr const& entry) -> json {
        json res    = json::object();
        res["kind"] = "Entry";
        res["id"]   = getId(entry);

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
        result["id"]   = getId(tree);
        if (tree->original->is(osk::Subtree)) {
            result["title"] = ExporterUltraplain::toStr(
                tree->original.as<sem::Subtree>()->title);
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

sem::SemId ExporterMindMap::Node::getOrgNode() const {
    if (this->isEntry()) {
        return getEntry().entry->content;
    } else {
        return getSubtree().subtree->original;
    }
}


#include <exporters/Exporter.cpp>

template class Exporter<ExporterMindMap, std::monostate>;
