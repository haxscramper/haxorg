#include <hstd/wrappers/graphviz.hpp>
#include <filesystem>

void Graphviz::Node::Record::set(
    const std::string& columnKey,
    CR<Record>         value) {
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

Str Graphviz::Node::Record::toString(bool braceCount) const {
    Str result;
    if (isFinal()) {
        if (tag) {
            result += "<" + *tag + "> ";
        }
        result += Record::escape(getLabel());
    } else {
        const auto& c = getNested();
        if (!c.empty()) {
            result += Str("{").repeated(braceCount);
            for (int i = 0; i < c.size(); ++i) {
                if (0 < i) {
                    result += "|";
                }
                result += c[i].toString(1);
            }
            result += Str("}").repeated(braceCount);
        }
    }

    return result;
}

Graphviz::Edge::Edge(Agraph_t* graph, CR<Node> head, CR<Node> tail)
    : graph(graph) {
    Q_CHECK_PTR(graph);
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

Graphviz::Graph::Graph(const std::string& name, Agdesc_t desc)
    : defaultEdge(nullptr, nullptr), defaultNode(nullptr, nullptr) {
    Agraph_t* graph_ = agopen(
        const_cast<char*>(name.c_str()), desc, nullptr);
    if (!graph_) {
        throw std::runtime_error("Failed to create graph");
    } else {
        graph = graph_;
    }

    initDefaultSetters();
    Q_CHECK_PTR(graph);
}

Graphviz::Graph::Graph(const QFileInfo& file)
    : graph(nullptr)
    , defaultEdge(graph, nullptr)
    , defaultNode(graph, nullptr) {
    Q_ASSERT(file.exists());

    std::string absolute = file.absoluteFilePath();
    FILE*       fp       = fopen(absolute.toLatin1().data(), "r");
    graph                = agread(fp, nullptr);

    initDefaultSetters();
}

void Graphviz::Graph::initDefaultSetters() {
    defaultNode.graph = graph;
    // FIXME simply capturing `this` causes segmentation fault because the
    // graph is deleted somewhere else or the pointer is modified. `graph =
    // this->graph` does not have this issue, but that's not how this is
    // supposed to work.
    defaultNode.setOverride = [graph = this->graph](
                                  std::string const& key,
                                  std::string const& value) {
        auto& r = *graph;
        Q_CHECK_PTR(graph);
        agattr(graph, AGNODE, strdup(key), strdup(value));
    };

    defaultEdge.graph       = graph;
    defaultEdge.setOverride = [graph = this->graph](
                                  std::string const& key,
                                  std::string const& value) {
        auto& r = *graph;
        Q_CHECK_PTR(graph);
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

std::string Graphviz::layoutTypeToString(LayoutType layoutType) {
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

std::string Graphviz::renderFormatToString(RenderFormat renderFormat) {
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

void Graphviz::createLayout(CR<Graph> graph, LayoutType layout) {
    int res = gvLayout(
        gvc,
        const_cast<Agraph_t*>(graph.get()),
        strdup(layoutTypeToString(layout)));
    qWarning() << res;
}

void Graphviz::freeLayout(Graph graph) {
    Q_ASSERT(gvLayoutDone(graph.get()));
    Q_CHECK_PTR(graph.get());
    Q_CHECK_PTR(gvc);
    gvFreeLayout(gvc, const_cast<Agraph_t*>(graph.get()));
}

void Graphviz::writeFile(
    const std::string& fileName,
    CR<Graph>          graph,
    RenderFormat       format) {
    if (format == RenderFormat::DOT) {
        FILE* output_file = fopen(fileName.c_str(), "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            return 1;
        }

        agwrite(const_cast<Agraph_t*>(graph.get()), output_file);
        fclose(output_file);

    } else {
        Q_ASSERT_X(
            GD_drawing(graph.get()) != nullptr,
            "render to file",
            "Writing non-DOT format to file requires layout. Call "
            "`createLayout()` before writing or use 'renderToFile' to "
            "execute render in one step");
        gvRenderFilename(
            gvc,
            const_cast<Agraph_t*>(graph.get()),
            strdup(renderFormatToString(format)),
            strdup(fileName));
    }
}

void Graphviz::renderToFile(
    const std::string& fileName,
    CR<Graph>          graph,
    RenderFormat       format,
    LayoutType         layout) {
    Q_CHECK_PTR(graph.get());
    Q_CHECK_PTR(gvc);
    if (format == RenderFormat::DOT) {
        writeFile(fileName, graph, format);

    } else {

        createLayout(graph, layout);

        writeFile(fileName, graph, format);
        freeLayout(graph);
    }
}

Graphviz::Node::Node(
    Agraph_t*          graph,
    const std::string& name,
    const Record&      record)
    : Node(graph, name) {
    setShape(Shape::record);
    setLabel(record.toString());
}

Graphviz::Node::Node(Agraph_t* graph, const std::string& name) {
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
