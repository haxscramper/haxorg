#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
#    include <hstd/ext/graphviz.hpp>
#    include <filesystem>
#    include <format>


using namespace hstd;
using namespace hstd::ext;
using namespace hstd::ext::graph;

Str gv::escape(Str const& input) {
    Str escaped;
    escaped.reserve(input.size());
    for (char c : input) {
        switch (c) {
            case '"': [[fallthrough]];
            case '>': [[fallthrough]];
            case '<': [[fallthrough]];
            case '{': [[fallthrough]];
            case '}': [[fallthrough]];
            case '|': [[fallthrough]];
            case '\\': escaped += '\\'; [[fallthrough]];
            default: escaped += c;
        }
    }
    return escaped;
}

Str gv::escapeHtml(Str const& input) {
    Str escaped;
    for (char c : input) {
        switch (c) {
            case '&': escaped += "&amp;"; break;
            case '<': escaped += "&lt;"; break;
            case '>': escaped += "&gt;"; break;
            case '"': escaped += "&quot;"; break;
            case '\'': escaped += "&#39;"; break;
            default: escaped += c; break;
        }
    }
    return escaped;
}

Str gv::NodeAttribute::Record::toHtml(bool horizontal) const {
    auto generateCell = [](Record const& rec) -> Str {
        return rec.isFinal() ? rec.getLabel() : rec.toHtml();
    };

    auto get_html_tag = [&](Record const* rec, Str const& tagname) -> Str {
        Str res;
        res += "<";
        res += tagname;
        for (auto const& [key, value] : rec->htmlAttrs) {
            res += std::format(" {}='{}'", key, value);
        }
        res += ">";
        return res;
    };

    if (isRecord()) {
        auto const& nested = getNested();
        if (std::all_of(
                nested.begin(),
                nested.end(),
                [](Record const& r) { return r.isRecord(); })
            && std::all_of(
                nested.front().getNested().begin(),
                nested.front().getNested().end(),
                [&nested](Record const& r) {
                    return std::all_of(
                        nested.begin(),
                        nested.end(),
                        [&](Record const& row) {
                            return row.isRecord()
                                && row.getNested().size()
                                       == nested.front()
                                              .getNested()
                                              .size();
                        });
                })) {


            Str html = get_html_tag(this, "table");
            for (Record const& row : nested) {
                html += "\n" + get_html_tag(&row, "tr");
                for (Record const& cell : row.getNested()) {
                    html += "\n" + get_html_tag(&cell, "td")
                          + generateCell(cell) + "</td>"_ss;
                }
                html += "</tr>";
            }
            html += "</table>";
            return html;
        } else {
            Str html = get_html_tag(this, "table");
            for (Record const& r : nested) {
                if (horizontal) {
                    html += get_html_tag(&r, "tr") + "<td>"_ss;
                } else {
                    html += get_html_tag(&r, "tr");
                    html += "<td style='writing-mode:vertical-lr'>"_ss;
                }
                html += generateCell(r);
                html += "</td></tr>";
            }
            html += "</table>";
            return html;
        }
    } else {
        return getLabel();
    }
}

void gv::NodeAttribute::Record::set(
    Str const&    columnKey,
    Record const& value) {
    if (isFinal()) {
        content = Vec<Record>{Record({Record(columnKey), value})};
    } else {
        for (auto& it : getNested()) {
            if (it.isRecord()) {
                if (it.getNested()[0].isFinal()
                    && it.getNested()[0].getLabel() == columnKey) {
                    it.getNested()[1] = value;
                    return;
                }
            }
        }

        push_back(Record({Record(columnKey), value}));
    }
}

gv::NodeAttribute::Record gv::NodeAttribute::Record::fromEscapedText(
    Str const& text,
    TextAlign  align) {
    Record res;
    res.content = escapeHtmlForGraphviz(text, align);
    return res;
}

gv::NodeAttribute::Record gv::NodeAttribute::Record::fromRow(
    Vec<Record> const& recs) {
    Record res;
    res.content = recs;
    return res;
}

gv::NodeAttribute::Record gv::NodeAttribute::Record::fromEscapedTextRow(
    Vec<Str> const& cells) {
    Record res = fromRow({});
    for (auto const& cell : cells) { res.add(fromEscapedText(cell)); }
    return res;
}

Str gv::NodeAttribute::Record::toString(bool braceCount) const {
    Str result;
    if (isFinal()) {
        if (tag) { result += std::format("<{}>", *tag); }
        result += gv::escape(getLabel());
    } else {
        auto const& c = getNested();
        if (!c.empty()) {
            result += Str("{").repeated(braceCount);
            for (int i = 0; i < c.size(); ++i) {
                if (0 < i) { result += "|"; }
                result += c[i].toString(1);
            }
            result += Str("}").repeated(braceCount);
        }
    }

    return result;
}

gv::EdgeAttribute::EdgeAttribute(
    Agraph_t*            graph,
    NodeAttribute const& head,
    NodeAttribute const& tail)
    : graph(graph) {
    LOGIC_ASSERTION_CHECK(graph != nullptr, "");
    Agedge_t* edge = agedge(
        graph,
        const_cast<Agnode_t*>(head.get()),
        const_cast<Agnode_t*>(tail.get()),
        nullptr,
        1);

    if (!edge) {
        throw std::runtime_error("Failed to create edge");
    } else {
        edge_ = edge;
    }
}

gv::GraphGroup::GraphGroup(
    hstd::SPtr<layout::LayoutRun> run,
    Str const&                    name,
    Agdesc_t                      desc)
    : layout::IGroup{run}
    , defaultEdge(nullptr, nullptr)
    , defaultNode(nullptr, nullptr)
    , name{name} {
    Agraph_t* graph_ = agopen(
        const_cast<char*>(name.c_str()), desc, nullptr);
    if (!graph_) {
        throw std::runtime_error("Failed to create graph");
    } else {
        graph = graph_;
    }

    initDefaultSetters();
    LOGIC_ASSERTION_CHECK(graph != nullptr, "");
}

gv::GraphGroup::GraphGroup(
    hstd::SPtr<layout::LayoutRun> run,
    fs::path const&               file)
    : layout::IGroup{run}
    , graph(nullptr)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr)
    , name{file.filename()} {
    LOGIC_ASSERTION_CHECK(fs::is_regular_file(file), "");

    Str   absolute = file.native();
    FILE* fp       = fopen(absolute.data(), "r");
    graph          = agread(fp, nullptr);

    initDefaultSetters();
}

gv::GraphGroup::GraphGroup(
    hstd::SPtr<layout::LayoutRun> run,
    Agraph_t*                     graph)
    : layout::IGroup{run}
    , graph(graph)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr)
    , name{agnameof(graph)} {
    initDefaultSetters();
}

void gv::GraphGroup::initDefaultSetters() {
    defaultNode.graph = graph;
    // FIXME simply capturing `this` causes segmentation fault because the
    // graph is deleted somewhere else or the pointer is modified. `graph =
    // this->graph` does not have this issue, but that's not how this is
    // supposed to work.
    defaultNode.setOverride = [graph = this->graph](
                                  Str const& key, Str const& value) {
        auto& r = *graph;
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        agattr(graph, AGNODE, strdup(key), strdup(value));
    };

    defaultEdge.graph       = graph;
    defaultEdge.setOverride = [graph = this->graph](
                                  Str const& key, Str const& value) {
        auto& r = *graph;
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        agattr(graph, AGEDGE, strdup(key), strdup(value));
    };
}

void gv::GraphGroup::eachNode(Func<void(NodeAttribute)> cb) {
    Agnode_t* node;
    for (node = agfstnode(get()); node; node = agnxtnode(get(), node)) {
        cb(NodeAttribute(get(), node));
    }
}

void gv::GraphGroup::eachEdge(Func<void(EdgeAttribute)> cb) {
    for (Agnode_t* node = agfstnode(get()); node;
         node           = agnxtnode(get(), node)) {
        for (Agedge_t* edge = agfstout(get(), node); edge;
             edge           = agnxtout(get(), edge)) {
            cb(EdgeAttribute(get(), edge));
        }
    }
}

void gv::GraphGroup::eachSubgraph(Func<void(GraphGroup)> cb) const {
    for (Agraph_t* subgraph = agfstsubg(graph); subgraph;
         subgraph           = agnxtsubg(subgraph)) {
        cb(GraphGroup(run, subgraph));
    }
}

hstd::SPtr<layout::IVertexVisualAttribute> gv::GraphGroup::addVertex(
    VertexID const& id) {
    hstd::logic_assertion_check_not_nil(run);
    auto vertex = run->getVertex(id);
    hstd::logic_assertion_check_not_nil(vertex);
    run->message(
        hstd::fmt(
            "add vertex {} ({})", id.format(), vertex->getStableId()));

    for (auto const& id : run->graph->getAllVertices()) {
        run->message(
            hstd::fmt(
                "vert {} stable ID {}",
                id.format(),
                vertex->getStableId()));
    }

    auto attribute = this->node(vertex->getStableId());
    const_cast<IVertex*>(vertex)->addAttribute(attribute);
    nodeAttributes.insert_or_assign(id, attribute);
    return attribute;
}

hstd::SPtr<layout::IEdgeVisualAttribute> gv::GraphGroup::addEdge(
    EdgeID const& id) {
    auto e = const_cast<IEdge*>(run->getEdge(id));
    run->message(
        hstd::fmt(
            "add edge {} ({} -> {}) to group {}",
            id.format(),
            e->getSource().format(),
            e->getTarget().format(),
            getStableId()));

    auto attr = edge(
        *nodeAttributes.at(e->getSource()),
        *nodeAttributes.at(e->getTarget()));
    e->addAttribute(attr);
    edgeAttributes.insert_or_assign(id, attr);
    return attr;
}

layout::GroupID gv::GraphGroup::addNewSubgroup() {
    auto result = run->addGroup(
        newSubgraph(hstd::fmt("GV_{}", run->groups.getNextId())));

    subgroups.insert_or_assign(
        result,
        std::dynamic_pointer_cast<GraphGroup>(run->getGroup(result)));
    return result;
}

void gv::GraphGroup::addExistingSubgroup(layout::GroupID const& id) {
    subGroups.push_back(id);
}

void gv::GraphGroup::render(
    fs::path const& path,
    LayoutType      layout,
    RenderFormat    format) {
    LOGIC_ASSERTION_CHECK(
        algorithm.has_value(),
        "Cannot generate render for the graphviz sub-group, this method "
        "can only be used on the graphviz graph");
    auto algo = std::dynamic_pointer_cast<gv::Layout>(algorithm.value());
    algo->layout = layout;
    algo->renderToFile(path, *this, format);
}

Str gv::alignText(Str const& text, TextAlign direction) {
    Str res = text;
    switch (direction) {
        case TextAlign::Left: {
            if (res.contains('\n')) {
                res = res.replaceAll("\n", "\\l");
                res += "\\l";
            }
            break;
        }
        case TextAlign::Right: {
            if (res.contains('\n')) {
                res = res.replaceAll("\n", "\\r");
                res += "\\r";
            }
            break;
        }
        case TextAlign::Center: break;
    }

    return res;
}

std::string gv::escapeHtmlForGraphviz(
    std::string const& input,
    TextAlign          direction) {
    std::string escaped = input;
    hstd::replace_all(escaped, "&", "&amp;");
    hstd::replace_all(escaped, "<", "&lt;");
    hstd::replace_all(escaped, ">", "&gt;");
    hstd::replace_all(escaped, "\"", "&quot;");
    hstd::replace_all(escaped, "\'", "&#39;");
    std::string newline_replace = "<BR ALIGN=\"";

    switch (direction) {
        case TextAlign::Left: newline_replace += "LEFT"; break;
        case TextAlign::Right: newline_replace += "RIGHT"; break;
        case TextAlign::Center: newline_replace += "CENTER"; break;
    }

    newline_replace += "\"/>";

    hstd::replace_all(escaped, "\n", newline_replace);
    escaped += newline_replace;
    return escaped;
}

Str gv::layoutTypeToString(LayoutType layoutType) {
    switch (layoutType) {
        case LayoutType::Dot: return "dot";
        case LayoutType::Neato: return "neato";
        case LayoutType::Fdp: return "fdp";
        case LayoutType::Sfdp: return "sfdp";
        case LayoutType::Twopi: return "twopi";
        case LayoutType::Circo: return "circo";
        default: throw std::runtime_error("Invalid layout type.");
    }
}

Str gv::renderFormatToString(RenderFormat renderFormat) {
    switch (renderFormat) {
        case RenderFormat::PNG: return "png";
        case RenderFormat::PDF: return "pdf";
        case RenderFormat::SVG: return "svg";
        case RenderFormat::PS: return "ps";
        case RenderFormat::JPEG: return "jpeg";
        case RenderFormat::GIF: return "gif";
        case RenderFormat::TIF: return "tif";
        case RenderFormat::BMP: return "bmp";
        case RenderFormat::XDOT: return "xdot";
        default: throw std::runtime_error("Invalid render format.");
    }
}

void gv::Layout::createLayout(GraphGroup const& graph) {
    int res = gvLayout(
        gvc->get(),
        const_cast<Agraph_t*>(graph.get()),
        layoutTypeToString(layout).c_str());
    if (res != 0) { throw std::logic_error("Could not compute layout"); }
}

void gv::Layout::freeLayout(GraphGroup graph) {
    LOGIC_ASSERTION_CHECK(graph.get() != nullptr, "");
    LOGIC_ASSERTION_CHECK(gvc != nullptr, "");
    gvFreeLayout(gvc->get(), const_cast<Agraph_t*>(graph.get()));
}

void gv::Layout::writeFile(
    fs::path const&   path,
    GraphGroup const& graph,
    RenderFormat      format) {
    if (format == RenderFormat::DOT) {
        FILE* output_file = fopen(path.c_str(), "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            return;
        }

        agwrite(const_cast<Agraph_t*>(graph.get()), output_file);
        fclose(output_file);

    } else {
        LOGIC_ASSERTION_CHECK(
            GD_drawing(graph.get()) != nullptr,
            "render to file"
            "Writing non-DOT format to file requires layout. Call "
            "`createLayout()` before writing or use 'renderToFile' to "
            "execute render in one step");

        gvRenderFilename(
            gvc->get(),
            const_cast<Agraph_t*>(graph.get()),
            renderFormatToString(format).c_str(),
            path.c_str());
    }
}

void gv::Layout::renderToFile(
    fs::path const&   path,
    GraphGroup const& graph,
    RenderFormat      format) {
    LOGIC_ASSERTION_CHECK(graph.get() != nullptr, "");
    LOGIC_ASSERTION_CHECK(gvc != nullptr, "");
    if (format == RenderFormat::DOT) {
        writeFile(path, graph, format);

    } else {
        createLayout(graph);

        writeFile(path, graph, format);
        freeLayout(graph);
    }
}

layout::IPlacementAlgorithm::Result gv::Layout::runSingleLayout(
    layout::GroupID const& root_id) {
    hstd::logic_assertion_check_not_nil(run);
    run->message("running single layout for gv::Layout Algorithm");
    auto                       __scope = run->scopeLevel();
    hstd::Vec<layout::GroupID> algorithmSwitches;
    auto rootGroup = std::dynamic_pointer_cast<GraphGroup>(
        run->getGroup(root_id));

    char const* id_attr = "_gv_layout_id";

    auto aux = [&](this auto&&                       self,
                   layout::GroupID const&            id,
                   hstd::Opt<layout::GroupID> const& parent) -> void {
        auto group = run->getGroup(id);
        if (group->algorithm && id != root_id) {
            auto parentGroup = std::dynamic_pointer_cast<GraphGroup>(
                run->getGroup(parent.value()));
            run->message(
                hstd::fmt(
                    "group {} has layout algorithm set",
                    group->getStableId()));
            auto recursiveBBox = run->getLayout(id).getBBox();
            auto recursiveNode = parentGroup->node(
                hstd::fmt("tmp-subgraph-node-{}", id));
            recursiveNode->setFixedWH(
                recursiveBBox.width(), recursiveBBox.height());
            algorithmSwitches.push_back(id);
        } else {
            auto gv_group = std::dynamic_pointer_cast<GraphGroup>(group);
            LOGIC_ASSERTION_CHECK(
                gv_group != nullptr,
                "Nested subgroup without layout algorithm must be an "
                "instance of gv::GraphGroup");
            run->message(
                hstd::fmt(
                    "group {} is a part of parent layout",
                    group->getStableId()));

            auto __scope = run->scopeLevel();
            for (auto const& sub : group->subGroups) { self(sub, id); }

            for (auto const& vertex : group->getVertices()) {
                run->message(hstd::fmt("vertex {}", vertex.format()));
                gv_group->nodeAttributes[vertex]->setAttr(
                    id_attr, vertex.getValue());
            }


            for (auto const& edge : group->getEdges()) {
                run->message(hstd::fmt("edge {}", edge.format()));
                gv_group->edgeAttributes[edge]->setAttr(
                    id_attr, edge.getValue());
            }
        }
    };

    {
        run->message("collecting nodes for the graphviz layout");
        aux(root_id, std::nullopt);
    }

    std::dynamic_pointer_cast<gv::Layout>(rootGroup->algorithm.value())
        ->createLayout(*rootGroup);


    layout::IPlacementAlgorithm::Result result;
    // 'each node' iterates over all nodes at once, including ones places
    // in a subgraph
    rootGroup->eachNode([&](NodeAttribute const& node) {
        auto id = VertexID::FromValue(
            node.getAttr<hstd::u64>(id_attr).value());
        run->message(
            hstd::fmt("each-group iterate vertex {}", id.format()));
        result.vertices.insert_or_assign(
            id,
            std::make_shared<GraphVertexLayoutAttribute>(
                node, *rootGroup));
    });

    rootGroup->eachEdge([&](EdgeAttribute const& edge) {
        auto id = VertexID::FromValue(
            edge.getAttr<hstd::u64>(id_attr).value());
        run->message(hstd::fmt("each-group iterate edge {}", id.format()));
        result.edges.insert_or_assign(
            id,
            std::make_shared<GraphEdgeLayoutAttribute>(edge, *rootGroup));
    });


    return result;
}

gv::NodeAttribute::NodeAttribute(
    Agraph_t*     graph,
    Str const&    name,
    Record const& record)
    : NodeAttribute(graph, name) {
    setShape(Shape::record);
    setLabel(record.toString());
}

gv::NodeAttribute::NodeAttribute(Agraph_t* graph, Str const& name) {
    auto node_ = agnode(graph, const_cast<char*>(name.c_str()), 1);
    if (!node_) {
        throw std::runtime_error("Failed to create node");
    } else {
        node = node_;
    }
}

gv::NodeAttribute* hstd::ext::graph::gv::NodeAttribute::setFixedWH(
    double w,
    double h) {
    setWidth(w);
    setHeight(h);
    setAttr("fixedsize", true);
    setAttr("original_height", h);
    setAttr("original_width", w);
    return this;
}


layout::GroupID gv::Graphviz::getNewGraph() {
    auto group = std::make_shared<gv::GraphGroup>(run, hstd::Str{"root"});
    group->algorithm = std::make_shared<gv::Layout>(this, run);
    return run->addRootGroup(group);
}

namespace {
Rect getGraphBBox(gv::GraphGroup const& g) {
    boxf rect = g.info()->bb;

    // +----[UR]
    // |       |
    // [LL]----+

    auto res = Rect(0, 0, rect.UR.x, rect.UR.y);
    return res;
}


Rect getNodeRectangle(
    gv::GraphGroup const&    g,
    gv::NodeAttribute const& node,
    int                      scaling,
    Rect const&              bbox) {
    double width  = node.info()->width * scaling;
    double height = node.info()->height * scaling;
    double x      = node.info()->coord.x;
    double y      = bbox.height() - node.info()->coord.y;
    int    x1     = std::round(x - width / 2);
    int    y1     = std::round(y - height / 2);
    auto   result = Rect(
        std::round(x1),
        std::round(y1),
        std::round(width),
        std::round(height));

    return result;
}

/// \brief Convert grapvhiz coordinate system (y up) to the qt coordinates
/// (y down). `height` is the vertical size of the main graph bounding box.
Point toGvPoint(pointf p, float height) {
    return Point(p.x, height - p.y);
}

/// \brief Get bounding gox for the nested subtraph
Rect getSubgraphBBox(gv::GraphGroup const& g, Rect const& bbox) {
    boxf rect = g.info()->bb;
    LOGIC_ASSERTION_CHECK(0 <= bbox.height(), "");
    auto ll = toGvPoint(rect.LL, bbox.height());
    auto ur = toGvPoint(rect.UR, bbox.height());
    Rect res{ll.x(), ll.y(), ur.x() - ll.x(), ll.y() - ur.y()};
    LOGIC_ASSERTION_CHECK(0 <= res.height(), "");
    return res;
}

Path getEdgeSpline(
    gv::EdgeAttribute const& edge,
    int                      scaling,
    Rect const&              bbox) {
    Path     path;
    splines* spl    = edge.info()->spl;
    int      height = bbox.height();
    if ((spl->list != 0) && (spl->list->size % 3 == 1)) {
        bezier bez = spl->list[0];
        if (bez.sflag) {
            path.quadTo(
                toGvPoint(bez.sp, height), toGvPoint(bez.list[0], height));
        } else {
            path.moveTo(toGvPoint(bez.list[0], height));
        }

        for (int i = 1; i < bez.size; i += 3) {
            path.cubicTo(
                toGvPoint(bez.list[i], height),
                toGvPoint(bez.list[i + 1], height),
                toGvPoint(bez.list[i + 2], height));
        }

        if (bez.eflag) { path.moveTo(toGvPoint(bez.ep, height)); }
    }
    return path;
}

} // namespace


Rect gv::GraphVertexLayoutAttribute::getBBox() const {
    return getNodeRectangle(
        graph,
        node,
        std::dynamic_pointer_cast<gv::Layout>(graph.algorithm.value())
            ->graphviz_size_scaling,
        getGraphBBox(graph));
}


Path gv::GraphEdgeLayoutAttribute::getPath() const {
    return getEdgeSpline(
        edge,
        std::dynamic_pointer_cast<gv::Layout>(graph.algorithm.value())
            ->graphviz_size_scaling,
        getGraphBBox(graph));
}


#endif
