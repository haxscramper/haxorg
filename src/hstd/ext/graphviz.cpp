#if !ORG_EMCC_BUILD
#    include <hstd/ext/graphviz.hpp>
#    include <filesystem>
#    include <format>


using namespace hstd;
using namespace hstd::ext;

Str Graphviz::Node::Record::escape(const Str& input) {
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

Str Graphviz::Node::Record::escapeHtml(CR<Str> input) {
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

Str Graphviz::Node::Record::toHtml(bool horizontal) const {
    auto generateCell = [](CR<Record> rec) -> Str {
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
                [](CR<Record> r) { return r.isRecord(); })
            && std::all_of(
                nested.front().getNested().begin(),
                nested.front().getNested().end(),
                [&nested](CR<Record> r) {
                    return std::all_of(
                        nested.begin(), nested.end(), [&](CR<Record> row) {
                            return row.isRecord()
                                && row.getNested().size()
                                       == nested.front()
                                              .getNested()
                                              .size();
                        });
                })) {


            Str html = get_html_tag(this, "table");
            for (CR<Record> row : nested) {
                html += "\n" + get_html_tag(&row, "tr");
                for (CR<Record> cell : row.getNested()) {
                    html += "\n" + get_html_tag(&cell, "td")
                          + generateCell(cell) + "</td>"_ss;
                }
                html += "</tr>";
            }
            html += "</table>";
            return html;
        } else {
            Str html = get_html_tag(this, "table");
            for (CR<Record> r : nested) {
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

void Graphviz::Node::Record::set(const Str& columnKey, CR<Record> value) {
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

Graphviz::Node::Record Graphviz::Node::Record::fromEscapedText(
    const Str& text,
    TextAlign  align) {
    Record res;
    res.content = escapeHtmlForGraphviz(text, align);
    return res;
}

Graphviz::Node::Record Graphviz::Node::Record::fromRow(
    const Vec<Record>& recs) {
    Record res;
    res.content = recs;
    return res;
}

Graphviz::Node::Record Graphviz::Node::Record::fromEscapedTextRow(
    const Vec<Str>& cells) {
    Record res = fromRow({});
    for (auto const& cell : cells) { res.add(fromEscapedText(cell)); }
    return res;
}

Str Graphviz::Node::Record::toString(bool braceCount) const {
    Str result;
    if (isFinal()) {
        if (tag) { result += std::format("<{}>", *tag); }
        result += Record::escape(getLabel());
    } else {
        const auto& c = getNested();
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

Graphviz::Edge::Edge(Agraph_t* graph, CR<Node> head, CR<Node> tail)
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

Graphviz::Graph::Graph(const Str& name, Agdesc_t desc)
    : defaultEdge(nullptr, nullptr), defaultNode(nullptr, nullptr) {
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

Graphviz::Graph::Graph(const fs::path& file)
    : graph(nullptr)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr) {
    LOGIC_ASSERTION_CHECK(fs::is_regular_file(file), "");

    Str   absolute = file.native();
    FILE* fp       = fopen(absolute.data(), "r");
    graph          = agread(fp, nullptr);

    initDefaultSetters();
}

void Graphviz::Graph::initDefaultSetters() {
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

void Graphviz::Graph::eachNode(Func<void(Node)> cb) {
    Agnode_t* node;
    for (node = agfstnode(get()); node; node = agnxtnode(get(), node)) {
        cb(Node(get(), node));
    }
}

void Graphviz::Graph::eachEdge(Func<void(Edge)> cb) {
    for (Agnode_t* node = agfstnode(get()); node;
         node           = agnxtnode(get(), node)) {
        for (Agedge_t* edge = agfstedge(get(), node); edge;
             edge           = agnxtedge(get(), edge, node)) {
            cb(Edge(get(), edge));
        }
    }
}

void Graphviz::Graph::eachSubgraph(Func<void(Graph)> cb) const {
    for (Agraph_t* subgraph = agfstsubg(graph); subgraph;
         subgraph           = agnxtsubg(subgraph)) {
        cb(Graph(subgraph));
    }
}

void Graphviz::Graph::render(
    const fs::path& path,
    LayoutType      layout,
    RenderFormat    format) {
    hstd::ext::Graphviz gvc;
    gvc.renderToFile(path, *this, format, layout);
}

Str Graphviz::alignText(const Str& text, TextAlign direction) {
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

std::string Graphviz::escapeHtmlForGraphviz(
    const std::string& input,
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

Str Graphviz::layoutTypeToString(LayoutType layoutType) const {
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

Str Graphviz::renderFormatToString(RenderFormat renderFormat) const {
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

void Graphviz::createLayout(CR<Graph> graph, LayoutType layout) const {
    int res = gvLayout(
        gvc.get(),
        const_cast<Agraph_t*>(graph.get()),
        layoutTypeToString(layout).c_str());
    if (res != 0) { throw std::logic_error("Could not compute layout"); }
}

void Graphviz::freeLayout(Graph graph) const {
    LOGIC_ASSERTION_CHECK(graph.get() != nullptr, "");
    LOGIC_ASSERTION_CHECK(gvc != nullptr, "");
    gvFreeLayout(gvc.get(), const_cast<Agraph_t*>(graph.get()));
}

void Graphviz::writeFile(
    const fs::path& fileName,
    CR<Graph>       graph,
    RenderFormat    format) const {
    if (format == RenderFormat::DOT) {
        FILE* output_file = fopen(fileName.c_str(), "w");
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
            fileName.c_str());
    }
}

void Graphviz::renderToFile(
    const fs::path& fileName,
    CR<Graph>       graph,
    RenderFormat    format,
    LayoutType      layout) const {
    LOGIC_ASSERTION_CHECK(graph.get() != nullptr, "");
    LOGIC_ASSERTION_CHECK(gvc != nullptr, "");
    if (format == RenderFormat::DOT) {
        writeFile(fileName, graph, format);

    } else {
        createLayout(graph, layout);

        writeFile(fileName, graph, format);
        freeLayout(graph);
    }
}

Graphviz::Node::Node(
    Agraph_t*     graph,
    const Str&    name,
    const Record& record)
    : Node(graph, name) {
    setShape(Shape::record);
    setLabel(record.toString());
}

Graphviz::Node::Node(Agraph_t* graph, const Str& name) {
    auto node_ = agnode(graph, const_cast<char*>(name.c_str()), 1);
    if (!node_) {
        throw std::runtime_error("Failed to create node");
    } else {
        node = node_;
    }
}

generator<CRw<Graphviz::Edge>> Graphviz::Node::outgoing() {
    for (Agedge_t* e = agfstout(graph, node); e; e = agnxtout(graph, e)) {
        auto value = Edge(graph, e);
        co_yield std::ref(value);
    }
}

generator<CRw<Graphviz::Edge>> Graphviz::Node::ingoing() {
    for (Agedge_t* e = agfstin(graph, node); e; e = agnxtin(graph, e)) {
        auto value = Edge(graph, e);
        co_yield std::ref(value);
    }
}

generator<CRw<Graphviz::Edge>> Graphviz::Node::edges() {
    for (Agedge_t* e = agfstedge(graph, node); e;
         e           = agnxtedge(graph, e, node)) {
        auto value = Edge(graph, e);
        co_yield std::ref(value);
    }
}

#endif
