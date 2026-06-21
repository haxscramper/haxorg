#if !ORG_BUILD_EMCC && ORG_BUILD_WITH_CGRAPH
#    include <hstd/ext/graph/visual/graph_graphviz.hpp>
#    include <filesystem>
#    include <hstd/ext/logger.hpp>
#    include <hstd/stdlib/Debug.hpp>


using namespace hstd;
using namespace hstd::ext;
using namespace hstd::ext::graph;

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
    Rect const&              bbox) {
    double width  = node.info()->width * gv::scaling;
    double height = node.info()->height * gv::scaling;
    double x      = node.info()->coord.x;
    double y      = bbox.height() - node.info()->coord.y;
    int    x1     = std::round(x - width / 2);
    int    y1     = std::round(y - height / 2);
    auto   result = Rect(x1, y1, width, height);

    return result;
}

/// \brief Convert grapvhiz coordinate system (y up) to the qt coordinates
/// (y down). `height` is the vertical size of the main graph bounding box.
Point toGvPoint(pointf p, float height) { return Point(p.x, height - p.y); }

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

Path getEdgeSpline(gv::EdgeAttribute const& edge, int scaling, Rect const& bbox) {
    Path     path;
    splines* spl    = edge.info()->spl;
    int      height = bbox.height();
    if ((spl->list != 0) && (spl->list->size % 3 == 1)) {
        bezier bez = spl->list[0];
        if (bez.sflag) {
            path.quadTo(toGvPoint(bez.sp, height), toGvPoint(bez.list[0], height));
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

template <typename T>
void gv::GraphvizObjBase<T>::delPayload(Str const& name) {
    agdelrec(_this()->get(), strdup(name));
}

template <typename T>
bool gv::GraphvizObjBase<T>::hasAttr(Str const& attribute) {
    return agget(_this()->get(), strdup(attribute)) != nullptr;
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& attribute, Opt<Str>& value) const {
    char* found = agget((void*)(_this()->get()), const_cast<char*>(attribute.data()));

    if (found != nullptr) {
        value = found;
    } else {
        value = std::nullopt;
    }
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& key, Opt<int>& value) const {
    Opt<Str> tmp;
    getAttr(key, tmp);
    if (tmp && !tmp->empty()) { value = tmp->toInt(); }
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& key, Opt<double>& value) const {
    Opt<Str> tmp;
    getAttr(key, tmp);
    if (tmp && !tmp->empty()) { value = tmp->toDouble(); }
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& key, Opt<bool>& value) const {
    Opt<Str> tmp;
    getAttr(key, tmp);
    if (tmp && !tmp->empty()) { value = *tmp == "true"; }
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& key, Opt<Point>& value) const {
    Opt<Str> tmp;
    getAttr(key, tmp);
    if (tmp && !tmp->empty()) {
        auto split = hstd::split(*tmp, ",");
        value      = Point(split[0].toDouble(), split[1].toDouble());
    }
}

template <typename T>
void gv::GraphvizObjBase<T>::setHtmlAttr(Str attribute, Str const& value) {
    // Define the attribute if not already defined
    Agsym_t* attr = agattr(
        agraphof(_this()->get()), T::graphvizKind, attribute.data(), "");
    if (!attr) { throw std::runtime_error("Failed to define attribute: " + attribute); }

    // Set the raw value using `agxset` and `agstrdup_html`
    agxset(
        _this()->get(),
        attr,
        agstrdup_html(agraphof(_this()->get()), const_cast<char*>(value.c_str())));
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str attribute, Str const& value) {
    if (setOverride) {
        setOverride(attribute, value);
    } else {
        agsafeset(_this()->get(), attribute.data(), const_cast<char*>(value.c_str()), "");
    }
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str const& key, int value) {
    _this()->setAttr(key, std::to_string(value));
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str const& key, u64 value) {
    _this()->setAttr(key, std::to_string(value));
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str const& key, Point value) {
    _this()->setAttr(key, fmt::format("{},{}", value.x(), value.y()));
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str const& key, double value) {
    _this()->setAttr(key, std::to_string(value));
}

template <typename T>
void gv::GraphvizObjBase<T>::setAttr(Str const& key, bool value) {
    _this()->setAttr(key, Str(value ? "true" : "false"));
}

template <typename T>
void gv::GraphvizObjBase<T>::getAttr(Str const& key, Opt<u64>& value) const {
    Opt<Str> tmp;
    getAttr(key, tmp);
    if (tmp && !tmp->empty()) { value = tmp->toU64(); }
}

template class gv::GraphvizObjBase<gv::NodeAttribute>;
template class gv::GraphvizObjBase<gv::EdgeAttribute>;
template class gv::GraphvizObjBase<gv::GraphGroup>;


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

hstd::XmlNode gv::Record::toHtml(bool horizontal) const {
    auto make_tag = [](Record const* rec, std::string const& tagname) -> hstd::XmlNode {
        hstd::XmlNode node(tagname);
        for (auto const& [key, value] : rec->htmlAttrs) { node.set_attr(key, value); }
        return node;
    };

    auto append_cell_content = [&](hstd::XmlNode& cell, Record const& rec) {
        if (rec.isFinal()) {
            cell.set_text(rec.getLabel());
        } else {
            cell.push_back(rec.toHtml());
        }
    };

    if (!isRecord()) {
        hstd::XmlNode leaf("span");
        leaf.set_text(getLabel());
        return leaf;
    }

    auto const& nested              = getNested();
    bool const  is_rectangular_grid = //
        !nested.empty()
        && std::ranges::all_of(nested, [](Record const& r) { return r.isRecord(); })
        && std::ranges::all_of(nested, [&](Record const& row) {
               return row.isRecord()
                   && row.getNested().size() == nested.front().getNested().size();
           });

    hstd::XmlNode table = make_tag(this, "table");

    if (is_rectangular_grid) {
        for (Record const& row : nested) {
            hstd::XmlNode tr = make_tag(&row, "tr");
            for (Record const& cell_rec : row.getNested()) {
                hstd::XmlNode td = make_tag(&cell_rec, "td");
                append_cell_content(td, cell_rec);
                tr.push_back(std::move(td));
            }
            table.push_back(std::move(tr));
        }
    } else {
        for (Record const& r : nested) {
            hstd::XmlNode tr = make_tag(&r, "tr");
            hstd::XmlNode td("td");
            if (!horizontal) { td.set_attr("style", "writing-mode:vertical-lr"); }
            append_cell_content(td, r);
            tr.push_back(std::move(td));
            table.push_back(std::move(tr));
        }
    }

    return table;
}

void gv::Record::set(Str const& columnKey, Record const& value) {
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

gv::Record gv::Record::fromEscapedText(Str const& text, TextAlign align) {
    Record res;
    res.content = escapeHtmlForGraphviz(text, align);
    return res;
}

gv::Record gv::Record::fromRow(Vec<Record> const& recs) {
    Record res;
    res.content = recs;
    return res;
}

gv::Record gv::Record::fromEscapedTextRow(Vec<Str> const& cells) {
    Record res = fromRow({});
    for (auto const& cell : cells) { res.add(fromEscapedText(cell)); }
    return res;
}

Str gv::Record::toString(bool braceCount) const {
    Str result;
    if (isFinal()) {
        if (tag) { result += fmt::format("<{}>", *tag); }
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
    hstd::logic_assertion_check_not_nil(head.get());
    hstd::logic_assertion_check_not_nil(tail.get());
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

gv::GraphGroup::GraphGroup(GroupContext ctx, Str const& name, Agdesc_t desc)
    : layout::IGroupVisualAttribute{ctx.run}
    , defaultEdge(nullptr, nullptr)
    , defaultNode(nullptr, nullptr)
    , ctx{ctx} {
    Agraph_t* graph_ = agopen(const_cast<char*>(name.c_str()), desc, nullptr);
    if (!graph_) {
        throw std::runtime_error("Failed to create graph");
    } else {
        graph = graph_;
    }

    initDefaultSetters();
    LOGIC_ASSERTION_CHECK(graph != nullptr, "");
}

gv::GraphGroup::GraphGroup(GroupContext ctx, fs::path const& file)
    : layout::IGroupVisualAttribute{ctx.run}
    , graph(nullptr)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr)
    , ctx{ctx} {
    LOGIC_ASSERTION_CHECK(fs::is_regular_file(file), "");

    Str   absolute = file.native();
    FILE* fp       = fopen(absolute.data(), "r");
    graph          = agread(fp, nullptr);

    initDefaultSetters();
}

gv::GraphGroup::GraphGroup(GroupContext ctx, Agraph_t* graph)
    : layout::IGroupVisualAttribute{ctx.run}
    , graph(graph)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr)
    , ctx{ctx} {
    initDefaultSetters();
}

void gv::GraphGroup::initDefaultSetters() {
    defaultNode.graph = graph;
    // FIXME simply capturing `this` causes segmentation fault because the
    // graph is deleted somewhere else or the pointer is modified. `graph =
    // this->graph` does not have this issue, but that's not how this is
    // supposed to work.
    defaultNode.setOverride = [graph = this->graph](Str const& key, Str const& value) {
        auto& r = *graph;
        LOGIC_ASSERTION_CHECK(graph != nullptr, "");
        agattr(graph, AGNODE, strdup(key), strdup(value));
    };

    defaultEdge.graph       = graph;
    defaultEdge.setOverride = [graph = this->graph](Str const& key, Str const& value) {
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
    for (Agnode_t* node = agfstnode(get()); node; node = agnxtnode(get(), node)) {
        for (Agedge_t* edge = agfstout(get(), node); edge; edge = agnxtout(get(), edge)) {
            cb(EdgeAttribute(get(), edge));
        }
    }
}

void gv::GraphGroup::eachSubgraph(Func<void(GraphGroup)> cb) const {
    for (Agraph_t* subgraph = agfstsubg(graph); subgraph;
         subgraph           = agnxtsubg(subgraph)) {
        cb(GraphGroup(ctx, subgraph));
    }
}

void gv::GraphGroup::render(
    fs::path const& path,
    LayoutType      layout,
    RenderFormat    format) {
    LOGIC_ASSERTION_CHECK(
        hasAlgorithm(),
        "Cannot generate render for the graphviz sub-group, this method "
        "can only be used on the graphviz graph");
    auto algo    = getAlgorithm<gv::Layout>();
    algo->layout = layout;
    hstd::logic_assertion_check_not_nil(algo);
    algo->renderToFile(path, *this, format);
}

hstd::SPtr<gv::NodeAttribute> hstd::ext::graph::gv::GraphGroup::node(Str const& name) {
    LOGIC_ASSERTION_CHECK(graph != nullptr, "");
    auto existing_node = agnode(graph, const_cast<char*>(name.c_str()), 0);
    if (existing_node != nullptr) {
        throw hstd::ext::graph::layout::layout_error::init(
            hstd::fmt("Node with name {} already exists in the graph", name));
    }

    auto tmp = std::make_shared<NodeAttribute>(graph, name);
    return tmp;
}

hstd::SPtr<gv::EdgeAttribute> hstd::ext::graph::gv::GraphGroup::edge(
    NodeAttribute const& head,
    NodeAttribute const& tail) {
    LOGIC_ASSERTION_CHECK(graph != nullptr, "");
    return std::make_shared<EdgeAttribute>(graph, head, tail);
}


hstd::SPtr<gv::EdgeAttribute> gv::GraphGroup::addEdge(EdgeID const& id) {
    auto attr = edge(
        *ctx.run->getVertexVisualAttribute<NodeAttribute>(run->getGraph()->getSource(id)),
        *ctx.run->getVertexVisualAttribute<NodeAttribute>(
            run->getGraph()->getTarget(id)));
    run->setEdgeAttribute(id, attr);
    return attr;
}

hstd::SPtr<gv::NodeAttribute> gv::GraphGroup::addVertex(EdgeID const& edge) {
    auto vertex_id = run->getNestedVertex(edge);
    auto vertex    = run->getVertex(vertex_id);
    auto attribute = this->node(vertex->getStableId());
    run->setNestedVertexAttribute(edge, attribute);
    return attribute;
}

hstd::SPtr<gv::GraphGroup> gv::GraphGroup::newStandaloneRootGraph(Str const& name) {
    auto gvc = SPtr<GVC_t>(gvContext(), gvFreeContext);
    if (!gvc) { throw std::runtime_error("Failed to create Graphviz context"); }

    auto result = std::make_shared<GraphGroup>(
        GroupContext{
            .context = GVContext::shared(),
            .gvc     = gvc,
        },
        name);

    auto graph  = std::make_shared<TrivialGraph>();
    auto groups = std::make_shared<IdOnlyHierarchy>();
    auto ports  = std::make_shared<TrivialPortCollection>();
    graph->addHierarchy(groups);
    graph->addPorts(ports);
    auto run = std::make_shared<layout::LayoutRun>(
        graph,
        graph->edges->getCollectionID(),
        ports->getCollectionID(),
        groups->getCollectionID());
    result->algorithm = std::static_pointer_cast<layout::IPlacementAlgorithm>(
        std::make_shared<gv::Layout>(gvc, run));

    return result;
}

hstd::SPtr<gv::GraphGroup> gv::GraphGroup::addNewNativeSubgroup(
    EdgeID const& edge,
    bool          with_algorithm) {
    hstd::SPtr<GraphGroup> res;
    if (with_algorithm) {
        res = newRootGraph(run);
    } else {
        res = newSubgraph(
            hstd::fmt(
                "GV_{}", run->getGraph()->getStableId(run->getGraph()->getTarget(edge))));
    }
    run->setNestedGroupAttribute(edge, res);
    return res;
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

std::string gv::escapeHtmlForGraphviz(std::string const& input, TextAlign direction) {
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
    agseterr(AGERR);
    hstd::logic_assertion_check_not_nil(this);
    auto g    = const_cast<Agraph_t*>(graph.get());
    auto algo = strdup(layoutTypeToString(layout).c_str());
    LOGIC_ASSERTION_CHECK(algo != nullptr, "");
    LOGIC_ASSERTION_CHECK(std::string{algo} != "", "");
    // _dbg("agwrite before layout");
    // agwrite(g, stderr);

    // char* margin = agget(g, (char*)"margin");
    // fprintf(stderr, "graph margin: %s\n", margin ? margin : "(null)");

    // char* pad = agget(g, (char*)"pad");
    // fprintf(stderr, "graph pad: %s\n", pad ? pad : "(null)");

    // char* bb = agget(g, (char*)"bb");
    // fprintf(stderr, "graph bb (before layout): %s\n", bb ? bb :
    // "(null)");

    hstd::logic_assertion_check_not_nil(gvc.get());
    hstd::logic_assertion_check_not_nil(g);
    assert(gvc.get() != nullptr);
    assert(g != nullptr);
    int res = gvLayout(gvc.get(), g, algo);
    if (res != 0) { throw std::logic_error("Could not compute layout"); }
    // Layout does not position the labels, need to call rendering pass.
    // 'dot' here is the name of the rendering backend.
    res = gvRender(gvc.get(), g, "xdot", NULL);
    if (res != 0) { throw std::logic_error("Could not execute render for the layout"); }
    // _dbg("agwrite after layout");
    // bb = agget(g, (char*)"bb");
    // fprintf(stderr, "graph bb (after layout): %s\n", bb ? bb :
    // "(null)"); agwrite(g, stderr);
}

void gv::Layout::freeLayout(GraphGroup graph) {
    LOGIC_ASSERTION_CHECK(graph.get() != nullptr, "");
    LOGIC_ASSERTION_CHECK(gvc != nullptr, "");
    gvFreeLayout(gvc.get(), const_cast<Agraph_t*>(graph.get()));
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
            gvc.get(),
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
    hstd::logic_assertion_check_not_nil(this);
    if (format == RenderFormat::DOT) {
        writeFile(path, graph, format);

    } else {
        createLayout(graph);

        writeFile(path, graph, format);
        freeLayout(graph);
    }
}

layout::IPlacementAlgorithm::Result gv::Layout::runSingleLayout(VertexID const& root_id) {
    hstd::logic_assertion_check_not_nil(run);
    auto g       = run->getGraph();
    auto __scope = run->begin_scope(
        hstd::fmt("running single layout for gv::Layout {}", g->getDebug(root_id)));
    auto rootGroup = hstd::validated_dynamic_cast<GraphGroup>(run->getGroup(root_id));

    char const* id_attr      = "_gv_layout_id";
    char const* id_sub_group = "_gv_group";

    auto aux = [&](this auto&&                self,
                   VertexID const&            id,
                   hstd::Opt<VertexID> const& parent) -> void {
        auto group = run->getGroup(id);
        if (group->hasAlgorithm() && id != root_id) {
            auto parentGroup = hstd::validated_dynamic_cast<GraphGroup>(
                run->getGroup(parent.value()));
            run->message(
                hstd::fmt("group '{}' has layout algorithm set", group->getStableId()));
            auto recursiveBBox = run->getLayout(id)->getBBox();
            auto recursiveNode = parentGroup->node(hstd::fmt("tmp-subgraph-node-{}", id));

            recursiveNode->setAttr(id_sub_group, id.getValue());

            recursiveNode->setFixedInchesWH(
                recursiveBBox.width() / scaling, recursiveBBox.height() / scaling);
        } else {
            auto gv_group = hstd::validated_dynamic_cast<GraphGroup>(group);
            LOGIC_ASSERTION_CHECK(
                gv_group != nullptr,
                "Nested subgroup without layout algorithm must be an "
                "instance of gv::GraphGroup");
            run->message(
                hstd::fmt(
                    "group '{}' is a part of parent layout '{}'",
                    group->getStableId(),
                    parent));

            gv_group->setAttr(id_sub_group, id.getValue());

            auto __scope = run->begin_scope();
            // iterate over sub-groups to find all layout switches
            for (auto const& sub : run->getSubGroups(id)) { self(sub, id); }

            // iterate over edges/vertices to insert graphviz attributes to
            // enable post-layout association.
            for (auto const& vertex : run->getDirectVertices(id)) {
                // run->message(hstd::fmt("vertex {}", vertex));
                run->getVertexVisualAttribute<NodeAttribute>(vertex)->setAttr(
                    id_attr, vertex.getValue());
            }

            for (auto const& edge : run->getDirectlyNestedEdges(id)) {
                run->message(hstd::fmt("{}", g->getDebug(edge)));
                run->getEdgeVisualAttribute<EdgeAttribute>(edge)->setAttr(
                    id_attr, edge.getValue());
            }
        }
    };

    {
        run->message("collecting nodes for the graphviz layout");
        aux(root_id, std::nullopt);
    }

    hstd::logic_assertion_check_not_nil(rootGroup);
    rootGroup->getAlgorithm<gv::Layout>()->createLayout(*rootGroup);

    layout::IPlacementAlgorithm::Result result;
    // 'each node' iterates over all nodes at once, including ones places
    // in a subgraph
    rootGroup->eachNode([&](NodeAttribute const& node) {
        if (hstd::Opt<hstd::u64> _tmp;
            node.getAttr(id_sub_group, _tmp), _tmp.has_value()) {
            auto id   = VertexID::FromValue(_tmp.value());
            auto bbox = getGraphBBox(*rootGroup);
            auto rect = getNodeRectangle(*rootGroup, node, bbox);
            run->message(
                hstd::fmt(
                    "found sub-group {} placement rect {} bbox {} ({}, "
                    "{})",
                    id,
                    rect,
                    bbox,
                    node.info()->coord.x,
                    node.info()->coord.y));

            // Full layout run will place all the nested subgroups and then
            // will execute layout for the parent group, so the
            // `getLayout()` is guaranteed to be safe to call here.
            auto const& prev_attribute = run->getLayout(id);

            run->message("replacing existing group attribute");
            auto prev_cast = hstd::validated_dynamic_cast<GraphGroupLayoutAttribute>(
                prev_attribute);
            if (prev_attribute) {
                run->message("previous attribute was a graphviz layout");
                run->getGroup<GraphGroup>(id);
                result.vertices.insert_or_assign(
                    id,
                    std::make_shared<GraphGroupLayoutAttribute>(rect, prev_cast->group));
            } else {
                run->message(
                    hstd::fmt(
                        "previous attribute was {}", typeid(prev_cast.get()).name()));
                result.vertices.insert_or_assign(
                    id, std::make_shared<GraphGroupLayoutAttribute>(rect, rootGroup));
            }


        } else {
            auto id_value = node.getAttr<hstd::u64>(id_attr);
            LOGIC_ASSERTION_CHECK_FMT(
                id_value.has_value(),
                "No ID attr property for node {}",
                node.getPropertiesAsString());

            auto id = VertexID::FromValue(id_value.value());
            // run->message(hstd::fmt("each-group iterate vertex {}", id));
            result.vertices.insert_or_assign(
                id, std::make_shared<GraphVertexLayoutAttribute>(node, *rootGroup));
        }
    });

    rootGroup->eachEdge([&](EdgeAttribute const& edge) {
        auto id = EdgeID::FromValue(edge.getAttr<hstd::u64>(id_attr).value());
        run->message(hstd::fmt("each-group iterate edge {}", id, g->getDebug(id)));

        result.edges.insert_or_assign(
            id, std::make_shared<GraphEdgeLayoutAttribute>(edge, *rootGroup));
    });

    rootGroup->eachSubgraph([&](GraphGroup const& group) {
        auto id_attr = group.getAttr<hstd::u64>(id_sub_group);
        LOGIC_ASSERTION_CHECK_FMT(
            id_attr.has_value(),
            "No ID attr property set for node {}",
            group.getPropertiesAsString());
        auto id = VertexID::FromValue(id_attr.value());
        run->message(hstd::fmt("each-group iterate group {}", id));
        result.vertices.insert_or_assign(
            id,
            std::make_shared<GraphGroupLayoutAttribute>(
                getGraphBBox(group), std::make_shared<GraphGroup>(group)));
    });

    // Bounding box for a group/sub-group is set twice. The first time is
    // when the group layout is done at the leaf level, then the
    // configuration only assigns a bounding box with height/width,
    // postiioned at 0,0. When the group layout is done as an opaque nested
    // node, then the attribute is reset with a bounding box positioned on
    // the final coordinates.
    result.vertices.insert_or_assign(
        root_id,
        std::make_shared<GraphGroupLayoutAttribute>(getGraphBBox(*rootGroup), rootGroup));


    return result;
}

gv::NodeAttribute::NodeAttribute(Agraph_t* graph, Str const& name, Record const& record)
    : NodeAttribute(graph, name) {
    setNodeShape(NodeShape::record);
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

gv::NodeAttribute* hstd::ext::graph::gv::NodeAttribute::setFixedInchesWH(
    double w,
    double h) {
    setWidth(w);
    setHeight(h);
    setAttr("fixedsize", true);
    setAttr("original_height", h);
    setAttr("original_width", w);
    return this;
}


Rect gv::GraphVertexLayoutAttribute::getBBox() const {
    return getNodeRectangle(graph, node, getGraphBBox(graph));
}


Path gv::GraphEdgeLayoutAttribute::getPath() const {
    return getEdgeSpline(
        edge,
        graph.getAlgorithm<gv::Layout>()->graphviz_size_scaling,
        getGraphBBox(graph));
}


std::string gv::EdgeAttribute::getPropertiesAsString() const {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph, AGEDGE, NULL); sym; sym = agnxtattr(graph, AGEDGE, sym)) {
        value = agxget(edge_, sym);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return result;
}

hstd::SPtr<graph::gv::GraphGroup> graph::gv::GraphGroup::newSubgraph(Str const& name) {
    auto res = std::make_shared<GraphGroup>(
        ctx, agsubg(graph, strdup("cluster_" + name), 1));

    return res;
}


std::string gv::GraphGroup::getPropertiesAsString() const {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph, AGRAPH, NULL); sym; sym = agnxtattr(graph, AGRAPH, sym)) {
        value = agget(graph, sym->name);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }
    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }
    return result;
}


hstd::SPtr<gv::GraphGroup> gv::GraphGroup::newRootGraph(
    hstd::SPtr<layout::LayoutRun> run,
    hstd::Str const&              name) {
    auto gvc = SPtr<GVC_t>(gvContext(), gvFreeContext);
    if (!gvc) { throw std::runtime_error("Failed to create Graphviz context"); }

    auto result = std::make_shared<GraphGroup>(
        GroupContext{
            .run     = run,
            .context = GVContext::shared(),
            .gvc     = gvc,
        },
        name);

    result->algorithm = std::make_shared<gv::Layout>(gvc, run);

    return result;
}

std::string gv::NodeAttribute::getPropertiesAsString() const {
    std::stringstream ss;
    Agsym_t*          sym;
    char*             value;

    for (sym = agnxtattr(graph, AGNODE, NULL); sym; sym = agnxtattr(graph, AGNODE, sym)) {
        value = agxget(node, sym);
        if (value) { ss << sym->name << " = " << value << ", "; }
    }

    std::string result = ss.str();
    if (!result.empty()) {
        result.pop_back();
        result.pop_back();
    }

    return result;
}


namespace {

/// Parse a graphviz color string to VisColor.
/// Handles "#RRGGBB", "#RRGGBBAA", and named colors (black, white, red,
/// etc.)
visual::VisColor parseGvColor(hstd::Str const& str) {
    if (str.empty()) { return visual::VisColor::black(); }
    if (str[0] == '#') {
        unsigned int r = 0, g = 0, b = 0, a = 255;
        if (str.size() == 7) {
            std::sscanf(str.c_str(), "#%02x%02x%02x", &r, &g, &b);
        } else if (str.size() == 9) {
            std::sscanf(str.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a);
        }
        return visual::VisColor{(uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a};
    }
    // Basic named colors
    if (str == "black") { return visual::VisColor::black(); }
    if (str == "white") { return visual::VisColor::white(); }
    if (str == "red") { return visual::VisColor::red(); }
    if (str == "green") { return visual::VisColor::green(); }
    if (str == "blue") { return visual::VisColor::blue(); }
    if (str == "transparent" || str == "none") { return visual::VisColor::transparent(); }
    return visual::VisColor::black();
}

visual::VisPen buildPenFromNode(gv::NodeAttribute const& node) {
    visual::VisPen pen;
    if (auto c = node.getColor()) { pen.color = parseGvColor(*c); }
    // Check for style attribute for dashed/dotted
    if (auto style = node.getStyle()) {
        if (*style == gv::Style::dashed) {
            pen.style = visual::VisPen::LineStyle::Dash;
        } else if (*style == gv::Style::dotted) {
            pen.style = visual::VisPen::LineStyle::Dot;
        } else if (*style == gv::Style::invis) {
            pen.style = visual::VisPen::LineStyle::None;
        }
    }
    if (auto pw = node.getPenWidth()) { pen.width = (float)*pw; }
    return pen;
}

visual::VisBrush buildBrushFromNode(gv::NodeAttribute const& node) {
    if (auto fc = node.getFillColor()) {
        return visual::VisBrush::solid(parseGvColor(*fc));
    }
    if (auto style = node.getStyle(); style == gv::Style::filled) {
        auto c = node.getColor();
        return visual::VisBrush::solid(
            c ? parseGvColor(*c) : visual::VisColor{192, 192, 192, 255});
    }
    return visual::VisBrush::noBrush();
}

visual::VisFont buildFontFromLabel(textlabel_t const* label) {
    visual::VisFont font;
    if (label->fontname) { font.family = hstd::Str{label->fontname}; }
    font.pixelSize = (float)label->fontsize;
    return font;
}

visual::VisElement makeLabelElement(textlabel_t const* label, float height) {
    Point pos = toGvPoint(label->pos, height);

    visual::VisElement            elem;
    visual::VisElement::TextShape text;
    text.content              = hstd::Str{label->text};
    text.anchor               = pos;
    text.font                 = buildFontFromLabel(label);
    text.alignment.horizontal = visual::VisTextAlign::HAlign::Center;
    text.alignment.vertical   = visual::VisTextAlign::VAlign::Center;
    if (label->fontcolor) { text.color = parseGvColor(hstd::Str{label->fontcolor}); }
    // Set bounding box from label dimen
    float lw         = (float)label->dimen.x;
    float lh         = (float)label->dimen.y;
    text.boundingBox = Rect(pos.x() - lw / 2.0f, pos.y() - lh / 2.0f, lw, lh);

    elem.data = text;
    return elem;
}

visual::VisPen buildPenFromEdge(gv::EdgeAttribute const& edge) {
    visual::VisPen pen;
    if (auto c = edge.getColor()) { pen.color = parseGvColor(*c); }
    if (auto style = edge.getStyle()) {
        if (*style == gv::Style::dashed) {
            pen.style = visual::VisPen::LineStyle::Dash;
        } else if (*style == gv::Style::dotted) {
            pen.style = visual::VisPen::LineStyle::Dot;
        } else if (*style == gv::Style::invis) {
            pen.style = visual::VisPen::LineStyle::None;
        }
    }
    if (auto pw = edge.getPenWidth()) { pen.width = (float)*pw; }
    return pen;
}

} // namespace


visual::VisGroup gv::GraphVertexLayoutAttribute::getVisual(VertexID const& selfId) const {
    Rect bbox     = getGraphBBox(graph);
    Rect nodeRect = getNodeRectangle(graph, node, bbox);

    visual::VisGroup result;
    result.offset                                  = Point{nodeRect.x(), nodeRect.y()};
    result.custom.extra                            = json::object();
    result.custom.extra["graphviz"]["vertex_name"] = node.name();
    result.max_point = Point{nodeRect.width(), nodeRect.height()};

    result.custom.setAttr("inkscape:label", hstd::fmt("GV VERTEX:{}", selfId));

    // Determine shape kind
    auto*            info  = node.info();
    visual::VisPen   pen   = buildPenFromNode(node);
    visual::VisBrush brush = buildBrushFromNode(node);

    visual::VisElement shapeElem;
    using S = gv::NodeShape;
    switch (node.getNodeShape().value_or(S::box)) {
        case S::ellipse:
        case S::circle:
        case S::oval: {
            visual::VisElement::EllipseShape ellipse;
            ellipse.geometry = Rect(0, 0, nodeRect.width(), nodeRect.height());
            ellipse.pen      = pen;
            ellipse.brush    = brush;
            shapeElem.data   = ellipse;
            break;
        }
        case S::point: {
            visual::VisElement::PointShape pt;
            pt.position    = Point{nodeRect.width() / 2.0f, nodeRect.height() / 2.0f};
            pt.radius      = std::min(nodeRect.width(), nodeRect.height()) / 2.0f;
            pt.pen         = pen;
            pt.brush       = brush;
            shapeElem.data = pt;
            break;
        }
        case S::polygon:
        case S::triangle:
        case S::pentagon:
        case S::octagon:
        case S::hexagon:
        case S::diamond: {
            // Read vertices from polygon shape info
            polygon_t* poly = (polygon_t*)info->shape_info;
            if (poly && poly->sides > 0 && poly->vertices) {
                visual::VisElement::PolygonShape polyShape;
                float                            cx = nodeRect.width() / 2.0f;
                float                            cy = nodeRect.height() / 2.0f;
                for (size_t i = 0; i < poly->sides; ++i) {
                    polyShape.points.push_back(
                        Point{
                            cx + (float)poly->vertices[i].x,
                            cy - (float)poly->vertices[i].y});
                }
                polyShape.pen   = pen;
                polyShape.brush = brush;
                shapeElem.data  = polyShape;
            } else {
                // Fallback to rect
                visual::VisElement::RectShape rect;
                rect.geometry  = Rect(0, 0, nodeRect.width(), nodeRect.height());
                rect.pen       = pen;
                rect.brush     = brush;
                shapeElem.data = rect;
            }
            break;
        }
        default: {
            // Default: box/rect and variants
            visual::VisElement::RectShape rect;
            rect.geometry = Rect(0, 0, nodeRect.width(), nodeRect.height());
            rect.pen      = pen;
            rect.brush    = brush;
            // Check for rounded style
            if (auto style = node.getStyle(); style == gv::Style::rounded) {
                rect.cornerRadius = std::min(nodeRect.width(), nodeRect.height()) * 0.1f;
            }
            shapeElem.data = rect;
            break;
        }
    }

    result.elements.push_back(shapeElem);

    // Add label if present
    textlabel_t* label = info->label;
    if (label && label->text && label->text[0] != '\0') {
        visual::VisElement::TextShape text;
        text.content = hstd::Str{label->text};
        // Label pos is in graph coordinates; convert to local node coords
        Point labelGlobal = toGvPoint(label->pos, bbox.height());
        text.anchor       = Point{
            labelGlobal.x() - nodeRect.x(), labelGlobal.y() - nodeRect.y()};
        text.font                 = buildFontFromLabel(label);
        text.alignment.horizontal = visual::VisTextAlign::HAlign::Center;
        text.alignment.vertical   = visual::VisTextAlign::VAlign::Center;
        if (label->fontcolor) {
            text.color = parseGvColor(hstd::Str{label->fontcolor});
        } else if (auto fc = node.getFontColor()) {
            text.color = parseGvColor(*fc);
        }
        float lw         = (float)label->dimen.x;
        float lh         = (float)label->dimen.y;
        text.boundingBox = Rect(
            text.anchor.x() - lw / 2.0f, text.anchor.y() - lh / 2.0f, lw, lh);

        visual::VisElement labelElem;
        labelElem.data = text;
        // labelElem.comment.push_back(
        //     hstd::fmt(
        //         "label pos xy:{}, {} label dimen xy:{}, {}",
        //         label->pos.x,
        //         label->pos.y,
        //         label->dimen.x,
        //         label->dimen.y));
        // labelElem.comment.push_back(hstd::fmt("node rect:{}",
        // nodeRect)); labelElem.comment.push_back(
        //     hstd::fmt("anchor:{} bbox:{}", text.anchor,
        //     text.boundingBox));
        result.elements.push_back(labelElem);
    }

    return result;
}


visual::VisGroup gv::GraphEdgeLayoutAttribute::getVisual(EdgeID const& selfId) const {
    Rect             bbox = getGraphBBox(graph);
    Path             path = getEdgeSpline(edge, scaling, bbox);
    visual::VisGroup result;

    result.custom.setAttr("inkscape:label", hstd::fmt("GV EDGE:{}", selfId));

    // Edge path
    if (!path.empty()) {
        visual::VisElement::PathShape pathShape;
        pathShape.path  = path;
        pathShape.pen   = buildPenFromEdge(edge);
        pathShape.brush = visual::VisBrush::noBrush();

        visual::VisElement pathElem;
        pathElem.data = pathShape;
        result.elements.push_back(pathElem);
    }

    // Arrowhead at end point
    auto* info = edge.info();
    if (info->spl && info->spl->list && 1 <= info->spl->list->size) {
        bezier& bez = info->spl->list[0];
        if (bez.eflag) {
            Point ep      = toGvPoint(bez.ep, bbox.height());
            Point lastCtl = toGvPoint(bez.list[bez.size - 1], bbox.height());

            // Compute arrow direction
            float dx  = ep.x() - lastCtl.x();
            float dy  = ep.y() - lastCtl.y();
            float len = std::sqrt(dx * dx + dy * dy);
            if (len > 0.001f) {
                dx /= len;
                dy /= len;
                float arrowLen  = 10.0f;
                float arrowHalf = 4.0f;
                // Perpendicular
                float px = -dy;
                float py = dx;

                visual::VisElement::PolygonShape arrow;
                arrow.points.push_back(ep);
                arrow.points.push_back(
                    Point{
                        ep.x() - dx * arrowLen + px * arrowHalf,
                        ep.y() - dy * arrowLen + py * arrowHalf});
                arrow.points.push_back(
                    Point{
                        ep.x() - dx * arrowLen - px * arrowHalf,
                        ep.y() - dy * arrowLen - py * arrowHalf});

                arrow.pen   = buildPenFromEdge(edge);
                arrow.brush = visual::VisBrush::solid(arrow.pen.color);

                visual::VisElement arrowElem;
                arrowElem.data = arrow;
                result.elements.push_back(arrowElem);
            }
        }
    }

    // Edge label
    if (info->label && info->label->text && info->label->text[0] != '\0') {
        result.elements.push_back(makeLabelElement(info->label, bbox.height()));
    }

    // Head/tail labels
    if (info->head_label && info->head_label->text && info->head_label->text[0] != '\0') {
        result.elements.push_back(makeLabelElement(info->head_label, bbox.height()));
    }
    if (info->tail_label && info->tail_label->text && info->tail_label->text[0] != '\0') {
        result.elements.push_back(makeLabelElement(info->tail_label, bbox.height()));
    }

    return result;
}

visual::VisGroup gv::GraphGroupLayoutAttribute::getVisual(VertexID const& selfId) const {
    visual::VisGroup result;
    result.offset = Point{graph.x(), graph.y()};

    result.custom.extra                           = json::object();
    result.custom.extra["graphviz"]["group_name"] = group->name();
    result.max_point                              = getGraphBBox(*group).max_corner();

    // Boundary rectangle
    visual::VisElement::RectShape rect;
    rect.geometry = Rect(0, 0, graph.width(), graph.height());
    rect.pen      = visual::VisPen{
        .color = visual::VisColor{128, 128, 128, 255},
        .width = 1.0f,
        .style = visual::VisPen::LineStyle::Dash,
    };
    rect.brush = visual::VisBrush::noBrush();


    // Read style attributes from the group if available
    if (group) {
        if (auto c = group->getColor()) { rect.pen.color = parseGvColor(*c); }
        if (auto style = group->getStyle()) {
            if (style == gv::Style::dashed) {
                rect.pen.style = visual::VisPen::LineStyle::Dash;
            } else if (style == gv::Style::dotted) {
                rect.pen.style = visual::VisPen::LineStyle::Dot;
            } else if (style == gv::Style::solid) {
                rect.pen.style = visual::VisPen::LineStyle::Solid;
            } else if (style == gv::Style::invis) {
                rect.pen.style = visual::VisPen::LineStyle::None;
            } else if (style == gv::Style::filled) {
                auto fc    = group->getFillColor();
                rect.brush = visual::VisBrush::solid(
                    fc ? parseGvColor(*fc) : visual::VisColor{230, 230, 230, 255});
            }
        }
        if (auto pw = group->getPenWidth()) { rect.pen.width = (float)*pw; }
    }

    visual::VisElement rectElem;
    rectElem.custom.addComment(hstd::fmt("graphviz group visual '{}'", group->name()));
    rectElem.data = rect;
    result.elements.push_back(rectElem);

    result.elements.push_back(
        visual::VisElement::FromText(
            hstd::fmt("GROUP:{}", group->name()), geometry::Point(0, 0)));

    result.custom.setAttr("inkscape:label", hstd::fmt("GV GROUP:{}", group->name()));
    result.custom.addDesc(hstd::fmt("bbox:{}", getBBox()));

    // Subgraph label
    if (group) {
        Rect         bbox  = getGraphBBox(*group);
        textlabel_t* label = group->info()->label;
        if (label && label->text && label->text[0] != '\0') {
            visual::VisElement::TextShape text;
            text.content = hstd::Str{label->text};
            // Label pos is in graph coordinates; convert to local group
            // coords
            Point labelGlobal = toGvPoint(label->pos, bbox.height());
            text.anchor = Point{labelGlobal.x() - graph.x(), labelGlobal.y() - graph.y()};
            text.font   = buildFontFromLabel(label);
            text.alignment.horizontal = visual::VisTextAlign::HAlign::Center;
            text.alignment.vertical   = visual::VisTextAlign::VAlign::Center;
            if (label->fontcolor) {
                text.color = parseGvColor(hstd::Str{label->fontcolor});
            }
            float lw         = (float)label->dimen.x;
            float lh         = (float)label->dimen.y;
            text.boundingBox = Rect(
                text.anchor.x() - lw / 2.0f, text.anchor.y() - lh / 2.0f, lw, lh);

            visual::VisElement labelElem;
            labelElem.data = text;
            result.elements.push_back(labelElem);
        }
    }

    return result;
}

namespace {
using ::google::protobuf::EnumValueDescriptor;
using ::google::protobuf::FieldDescriptor;
using ::google::protobuf::Message;
using ::google::protobuf::Reflection;
using namespace gv;

inline FieldDescriptor const* findField(Message const& msg, Str const& name) {
    return msg.GetDescriptor()->FindFieldByName(name);
}

template <typename T>
void setProtoField(Message* msg, Str const& name, T const& value) {
    auto const* field = msg->GetDescriptor()->FindFieldByName(name);
    if (!field) { return; }
    Reflection const* refl = msg->GetReflection();

    if constexpr (std::is_same_v<T, bool>) {
        refl->SetBool(msg, field, value);
    } else if constexpr (std::is_same_v<T, int>) {
        refl->SetInt32(msg, field, value);
    } else if constexpr (std::is_same_v<T, double>) {
        refl->SetDouble(msg, field, value);
    } else if constexpr (std::is_same_v<T, Str>) {
        refl->SetString(msg, field, value);
    } else if constexpr (std::is_enum_v<T>) {
        auto const* enum_value = field->enum_type()->FindValueByNumber(
            static_cast<int>(value));
        if (enum_value) { refl->SetEnum(msg, field, enum_value); }
    } else if constexpr (std::is_same_v<T, Point>) {
        Message*          p  = refl->MutableMessage(msg, field);
        Reflection const* pr = p->GetReflection();
        auto const*       fx = p->GetDescriptor()->FindFieldByName("x");
        auto const*       fy = p->GetDescriptor()->FindFieldByName("y");
        pr->SetDouble(p, fx, value.x());
        pr->SetDouble(p, fy, value.y());
    }
}

template <typename T>
bool getProtoField(Message const& msg, Str const& name, T& value) {
    auto const* field = msg.GetDescriptor()->FindFieldByName(name);
    if (!field) { return false; }
    Reflection const* refl = msg.GetReflection();
    if (!refl->HasField(msg, field)) { return false; }

    if constexpr (std::is_same_v<T, bool>) {
        value = refl->GetBool(msg, field);
    } else if constexpr (std::is_same_v<T, int>) {
        value = refl->GetInt32(msg, field);
    } else if constexpr (std::is_same_v<T, double>) {
        value = refl->GetDouble(msg, field);
    } else if constexpr (std::is_same_v<T, Str>) {
        value = refl->GetString(msg, field);
    } else if constexpr (std::is_enum_v<T>) {
        value = static_cast<T>(refl->GetEnum(msg, field)->number());
    } else if constexpr (std::is_same_v<T, Point>) {
        Message const&    p  = refl->GetMessage(msg, field);
        Reflection const* pr = p.GetReflection();
        auto const*       fx = p.GetDescriptor()->FindFieldByName("x");
        auto const*       fy = p.GetDescriptor()->FindFieldByName("y");
        value                = Point(pr->GetDouble(p, fx), pr->GetDouble(p, fy));
    } else {
        return false;
    }

    return true;
}

template <typename Attr, typename Payload>
void writeAttrs(Attr const* self, Payload* payload) {
#    define WRITE_ATTR(__Class, Method, key, Type)                                       \
        do {                                                                             \
            auto v = self->get##Method();                                                \
            if (v) { setProtoField(payload, #key, *v); }                                 \
        } while (false)

#    define WRITE_EATTR(__Class, Name, key, _type)                                       \
        do {                                                                             \
            auto v = self->get##Name();                                                  \
            if (v) { setProtoField(payload, #key, *v); }                                 \
        } while (false)

#    define WRITE_ALIGNED(__Class, Method, key, Type)                                    \
        do {                                                                             \
            Opt<Type>      value;                                                        \
            Opt<TextAlign> dir;                                                          \
            self->getAttr(#key, value);                                                  \
            if (value) { setProtoField(payload, #key, *value); }                         \
            if (dir) { setProtoField(payload, Str(#key) + Str("_align"), *dir); }        \
        } while (false)

    if constexpr (std::is_same_v<Attr, NodeAttribute>) {
        _GV_NODE_ATTRIBUTES(WRITE_ATTR, WRITE_EATTR, WRITE_ALIGNED);
    } else if constexpr (std::is_same_v<Attr, EdgeAttribute>) {
        _GV_EDGE_ATTRIBUTES(WRITE_ATTR, WRITE_EATTR, WRITE_ALIGNED);
    } else if constexpr (std::is_same_v<Attr, GraphGroup>) {
        _GV_GRAPH_ATTRIBUTES(WRITE_ATTR, WRITE_EATTR, WRITE_ALIGNED);
    }

#    undef WRITE_ATTR
#    undef WRITE_EATTR
#    undef WRITE_ALIGNED
}

template <typename Attr, typename Payload>
void readAttrs(Attr* self, Payload const& payload) {
#    define READ_ATTR(__Class, Method, key, Type)                                        \
        do {                                                                             \
            Type v;                                                                      \
            if (getProtoField(payload, #key, v)) { self->set##Method(v); }               \
        } while (false)

#    define READ_EATTR(__Class, Name, key, _type)                                        \
        do {                                                                             \
            _type v;                                                                     \
            if (getProtoField(payload, #key, v)) { self->set##Name(v); }                 \
        } while (false)

#    define READ_ALIGNED(__Class, Method, key, Type)                                     \
        do {                                                                             \
            Type v;                                                                      \
            if (getProtoField(payload, #key, v)) {                                       \
                TextAlign dir = TextAlign::Left;                                         \
                (void)getProtoField(payload, Str(#key) + Str("_align"), dir);            \
                self->set##Method(v, dir);                                               \
            }                                                                            \
        } while (false)

    if constexpr (std::is_same_v<Attr, NodeAttribute>) {
        _GV_NODE_ATTRIBUTES(READ_ATTR, READ_EATTR, READ_ALIGNED);
    } else if constexpr (std::is_same_v<Attr, EdgeAttribute>) {
        _GV_EDGE_ATTRIBUTES(READ_ATTR, READ_EATTR, READ_ALIGNED);
    } else if constexpr (std::is_same_v<Attr, GraphGroup>) {
        _GV_GRAPH_ATTRIBUTES(READ_ATTR, READ_EATTR, READ_ALIGNED);
    }

#    undef READ_ATTR
#    undef READ_EATTR
#    undef READ_ALIGNED
}
} // namespace

#    if ORG_BUILD_WITH_PROTOBUF

void hstd::ext::graph::gv::GraphGroup::writeSerial(
    graph::proto::IAttribute* out,
    IGraph const*             graph) const {
    layout::IGroupVisualAttribute::writeSerial(out, graph);
    writeAttrs(this, out->mutable_payload());
}

void hstd::ext::graph::gv::GraphGroup::readSerial(
    graph::proto::IAttribute const* in,
    IGraph const*                   graph,
    IGraphSerialReaderFactory*      factory,
    IAttributeObject const*         vertex) {
    layout::IGroupVisualAttribute::readSerial(in, graph, factory, vertex);
    readAttrs(this, in->payload());
}

void hstd::ext::graph::gv::NodeAttribute::writeSerial(
    graph::proto::IAttribute* out,
    IGraph const*             graph) const {
    layout::IVertexVisualAttribute::writeSerial(out, graph);
    writeAttrs(this, out->mutable_payload());
}
void hstd::ext::graph::gv::NodeAttribute::readSerial(
    graph::proto::IAttribute const* in,
    IGraph const*                   graph,
    IGraphSerialReaderFactory*      factory,
    IAttributeObject const*         vertex) {
    layout::IVertexVisualAttribute::readSerial(in, graph, factory, vertex);
    readAttrs(this, in->payload());
}

void hstd::ext::graph::gv::EdgeAttribute::writeSerial(
    graph::proto::IAttribute* out,
    IGraph const*             graph) const {
    layout::IEdgeVisualAttribute::writeSerial(out, graph);
    writeAttrs(this, out->mutable_payload());
}
void hstd::ext::graph::gv::EdgeAttribute::readSerial(
    graph::proto::IAttribute const* in,
    IGraph const*                   graph,
    IGraphSerialReaderFactory*      factory,
    IAttributeObject const*         vertex) {
    layout::IEdgeVisualAttribute::readSerial(in, graph, factory, vertex);
    readAttrs(this, in->payload());
}
#    endif

#endif
