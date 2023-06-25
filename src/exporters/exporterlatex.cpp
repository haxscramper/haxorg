#include "exporterlatex.hpp"

ExporterLatex::Res ExporterLatex::command(
    const QString&      name,
    const Vec<QString>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        res->add(string("{" + arg + "}"));
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&  name,
    const Vec<Res>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        res->add(string("{"));
        res->add(arg);
        res->add(string("}"));
    }
    return res;
}


ExporterLatex::Res ExporterLatex::visit(sem::SemId org) {
    __visit_eval_scope(org);
    Res tmp = nullptr;
    visit(tmp, org);
    if (tmp == nullptr) {
        tmp = string("TODO" + to_string(org->getKind()));
    }
    return tmp;
}

void ExporterLatex::visitDocument(Res& res, In<sem::Document> value) {
    __visit_specific_kind(res, value);
    res = b::stack();
    res->add(string(R"(\begin{document})"));
    for (const auto& it : value->subnodes) {
        res->add(visit(it));
    }
    res->add(string(R"(\end{document})"));
}

void ExporterLatex::visitSubtree(Res& res, In<sem::Subtree> tree) {
    __visit_specific_kind(res, tree);
    res = b::stack();

    QString name;
    switch (tree->level) {
        case 0: name = "section"; break;
        case 1: name = "subsection"; break;
        case 2: name = "subsubsection"; break;
        default: name = "textbf"; break;
    }

    res->add(command(name, {visit(tree->title)}));
    for (const auto& it : tree->subnodes) {
        res->add(visit(it));
    }
}

void ExporterLatex::visitParagraph(Res& res, In<sem::Paragraph> par) {
    __visit_specific_kind(res, par);
    res = b::line();
    for (auto const& sub : par->subnodes) {
        res->add(visit(sub));
    }

    if (res->size() == 0) {
        res->add(string(" "));
    }
}

void ExporterLatex::visitTime(Res& res, In<sem::Time> time) {
    if (time->isStatic()) {
        res = string(
            time->getStatic().time.getDateTime().toString(Qt::ISODate));
    } else {
        res = string("TODO dynamic time");
    }
}
