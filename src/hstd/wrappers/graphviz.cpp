#include <hstd/wrappers/graphviz.hpp>

void Graphviz::Node::Record::set(
    const QString& columnKey,
    CR<Record>     value) {
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
        const_cast<Agnode_t*>(tail.get()),
        const_cast<Agnode_t*>(head.get()),
        nullptr,
        1);

    if (!edge) {
        throw std::runtime_error("Failed to create edge");
    } else {
        edge_ = edge;
    }
}

Graphviz::Graph::Graph(const QString& name, Agdesc_t desc) {
    Agraph_t* graph_ = agopen(
        const_cast<char*>(name.toStdString().c_str()), desc, nullptr);
    if (!graph_) {
        throw std::runtime_error("Failed to create graph");
    } else {
        graph = graph_;
    }
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

void Graphviz::writeFile(
    const QString& fileName,
    CR<Graph>      graph,
    RenderFormat   format) {
    if (format == RenderFormat::DOT) {
        FILE* output_file = fopen(fileName.toStdString().c_str(), "w");
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
    const QString& fileName,
    CR<Graph>      graph,
    RenderFormat   format,
    LayoutType     layout) {
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
