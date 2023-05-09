#include <exporters/exportermindmap.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>

int ExporterMindMap::DocEntry::counter = 0;

Opt<ExporterMindMap::DocLink> ExporterMindMap::resolve(
    CR<sem::Org::Ptr> node) {
    return std::nullopt;
}

void ExporterMindMap::visitSubtree(
    std::monostate&       s,
    CR<sem::Subtree::Ptr> ptr) {
    stack.push_back(DocSubtree::shared());
    if (stack.size() == 1) {
        root = stack.back();
    }

    qDebug() << QString("  ").repeated(stack.size())
             << ExporterUltraplain::toStr(ptr->title);

    //    ExporterTree::treeRepr(
    //        ptr->title,
    //        ExporterTree::TreeReprConf{}.withSkippedSubnodesOf(
    //            OrgSemKind::Subtree));

    stack.back()->original = ptr;

    for (const auto& sub : ptr->subnodes) {
        visit(s, sub);
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

Graphviz::Graph ExporterMindMap::toGraph() {
    Func<Opt<Graphviz::Graph>(
        CR<DocSubtree::Ptr>, CR<Opt<Graphviz::Graph>>)>
        auxSubtree;

    int subgraphCounter = 0;

    auxSubtree = [&](CR<DocSubtree::Ptr>  doc,
                     Opt<Graphviz::Graph> parent) -> Opt<Graphviz::Graph> {
        if (doc->subtrees.empty()) {
            auto canvas = parent ? *parent : Graphviz::Graph("root");

            //            auto node = canvas.node("node" +
            //            to_string(++subgraphCounter)); if
            //            (doc->original->is(OrgSemKind::Subtree)) {
            //                node.setLabel(ExporterUltraplain::toStr(
            //                    doc->original->as<sem::Subtree>()->title));
            //            } else {
            //                qDebug() << doc->original->getKind();
            //            }

            return canvas;
        } else {
            auto result = parent ? parent->newSubgraph(
                              "cluster" + to_string(++subgraphCounter))
                                 : Graphviz::Graph("root");
            for (const auto& it : doc->subtrees) {
                auxSubtree(it, result);
            }

            return result;
        }
    };

    Q_CHECK_PTR(root);
    auto result = auxSubtree(root, std::nullopt);
    return result.value();
}
