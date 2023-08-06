#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <exporters/ExporterJson.hpp>

int ExporterMindMap::DocEntry::counter   = 0;
int ExporterMindMap::DocSubtree::counter = 0;

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
    std::monostate&           s,
    sem::SemIdT<sem::Subtree> ptr) {
    stack.push_back(DocSubtree::shared());
    auto& res = stack.back();


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
                        res->outgoing.push_back(
                            DocLink{.description = it});
                    }
                } else {
                    // TODO
                }
            }

        } else {
            auto entry     = DocEntry::shared();
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
    eachEntry(root, [&](DocEntry::Ptr entry) {
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

    eachEntry(root, [&](DocEntry::Ptr entry) {
        entry->content.eachSubnodeRec([&](sem::SemId node) {
            Opt<DocLink> resolved = getResolved(node);
            if (resolved) {
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
    sem::SemId node) {
    for (const auto& doc : documents) {
        // Check if the entry is the list item that can be used for
        // resolution.
        if (node->is(osk::ListItem)
            && node.as<sem::ListItem>()->isDescriptionItem()) {
            sem::SemIdT<sem::ListItem> item = node.as<sem::ListItem>();
            Opt<DocLink>               resolved;
            item->header.value().eachSubnodeRec([&](CR<sem::SemId> node) {
                if (!resolved && node->is(osk::Link)) {
                    resolved = getResolved(node);
                }
            });
            if (resolved) {
                resolved->description = node.context->createInSame(
                    node, osk::StmtList, node);
                (*resolved->description)->subnodes = item->subnodes;
                return resolved;
            }
        }

        auto resolve = doc->resolve(node);
        if (resolve) {
            auto                 id      = resolve.value();
            Opt<DocEntry::Ptr>   entry   = entriesOut.get(id);
            Opt<DocSubtree::Ptr> subtree = subtreesOut.get(id);

            if (entry) {
                // TODO consider multiple documents in a group and
                // issue diagnostic message in case of duplicates
                return DocLink{
                    .resolved = DocLink::Entry{.entry = entry.value()}};
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

    auto getVertex = overloaded{[&](CR<DocLink> link) {
        if (link.getKind() == DocLink::Kind::Entry) {
            return entryNodes[link.getEntry().entry->id];
        } else {
            return subtreeNodes[link.getSubtree().subtree->id];
        }
    }};

    auto addEdge =
        [&](VertDesc desc, CR<DocLink> link, CR<EdgeProp> prop) {
            add_edge(desc, getVertex(link), prop, result);
        };

    auto addLink = [&](VertDesc desc, CR<DocLink> link) {
        if (link.getKind() == DocLink::Kind::Entry) {
            addEdge(
                desc,
                link,
                EdgeProp{.data = EdgeProp::RefersTo{.target = link}});
        } else {
            addEdge(
                desc,
                link,
                EdgeProp{.data = EdgeProp::RefersTo{.target = link}});
        }
    };

    eachEntry(root, [&](DocEntry::Ptr entry) {
        for (const auto& out : entry->outgoing) {
            addLink(entryNodes[entry->id], out);
        }
    });

    eachSubtree(root, [&](DocSubtree::Ptr subtree) {
        auto const& id = subtreeNodes[subtree->id];
        for (const auto& out : subtree->outgoing) {
            addLink(id, out);
        }

        for (const auto& out : subtree->ordered) {
            for (DocLink const& link : out->outgoing) {
                if (link.getKind() == DocLink::Kind::Subtree) {
                    addEdge(
                        id,
                        link,
                        EdgeProp{.data = EdgeProp::InternallyRefers{}});
                }
            }
        }

        for (auto const& out : subtree->unordered) {
            for (DocLink const& link : out->outgoing) {
                if (link.getKind() == DocLink::Kind::Subtree) {
                    addEdge(
                        id,
                        link,
                        EdgeProp{.data = EdgeProp::InternallyRefers{}});
                }
            }
        }
    });

    return result;
}

QString ExporterMindMap::toGraphML(CR<Graph> graph) { return ""; }

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
            make_transform_value_property_map<u64>(
                [&](VertexProp const& prop) -> u64 {
                    return getOrgNode(prop).id;
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
    Graph g = toGraph();
    return toJsonGraph(g);
}

json ExporterMindMap::toJsonGraph(CR<Graph> g) {
    json nodes = json::object();
    json edges = json::array();

    auto vertexId = [&](VertDesc v) { return getId(g[v]); };

    for (auto [it, it_end] = boost::edges(g); it != it_end; ++it) {
        edges.push_back(toJsonGraphEdge(g, *it));
    }

    for (auto [it, it_end] = boost::vertices(g); it != it_end; ++it) {
        nodes[vertexId(*it).toStdString()] = toJsonGraphNode(g, *it);
    }

    json result        = json::object();
    result["nodes"]    = nodes;
    result["edges"]    = edges;
    result["metadata"] = json::object();
    result["type"]     = "Haxorg MindMap Export";
    return result;
}

json ExporterMindMap::toJsonGraphNode(CR<Graph> g, CR<VertDesc> n) {
    json node    = json::object();
    json meta    = json::object();
    meta["kind"] = to_string(g[n].getKind());
    meta["id"]   = getId(g[n]);
    switch (g[n].getKind()) {
        case VertexProp::Kind::Subtree: {
            auto tree = g[n].getSubtree();
            if (tree.subtree->original.is(osk::Subtree)) {
                auto id       = tree.subtree->original.as<sem::Subtree>();
                auto title    = id->title;
                meta["title"] = ExporterUltraplain::toStr(title);
                ExporterJson().visitSubtreeValueFields(meta, id);
            }

            break;
        }
        case VertexProp::Kind::Entry: {
            break;
        }
    }

    node["metadata"] = meta;
    return node;
}

json ExporterMindMap::toJsonGraphEdge(CR<Graph> g, CR<EdgeDesc> e) {
    json edge        = json::object();
    edge["source"]   = getId(g[source(e, g)]);
    edge["target"]   = getId(g[target(e, g)]);
    json meta        = json::object();
    meta["kind"]     = to_string(g[e].getKind());
    edge["metadata"] = meta;
    return edge;
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

json ExporterMindMap::toJsonTree() {
    auto exportLink = [](DocLink const& link) -> json {
        json res    = json::object();
        res["kind"] = to_string(link.getKind());
        if (link.getKind() == DocLink::Kind::Entry) {
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

#include <exporters/Exporter.cpp>

template class Exporter<ExporterMindMap, std::monostate>;
