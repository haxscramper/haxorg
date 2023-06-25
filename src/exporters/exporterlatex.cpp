#include "exporterlatex.hpp"

using namespace sem;
using Prop = Subtree::Property;

void ExporterLatex::addWrap(
    Res&           res,
    const QString& open,
    const QString& close,
    const QString& arg) {
    res->add(string(open + arg + close));
}

void ExporterLatex::addWrap(
    Res&           res,
    const QString& open,
    const QString& close,
    const Res&     arg) {
    res->add(string(open));
    res->add(arg);
    res->add(string(close));
}

ExporterLatex::Res ExporterLatex::command(
    const QString&      name,
    const Vec<QString>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&  name,
    const Vec<Res>& opts,
    const Vec<Res>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& opt : opts) {
        addWrap(res, "[", "]", opt);
    }

    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&  name,
    const Vec<Res>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&      name,
    const Vec<QString>& opts,
    const Vec<QString>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& opt : opts) {
        addWrap(res, "[", "]", opt);
    }

    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}


ExporterLatex::Res ExporterLatex::visit(SemId org) {
    __visit_eval_scope(org);
    Res tmp = nullptr;
    visit(tmp, org);
    if (tmp == nullptr) {
        tmp = string("TODO" + to_string(org->getKind()));
    }
    return tmp;
}

QString getLatexClass(Opt<ExporterLatex::In<Document>> doc) {
    if (doc) {
        auto lclass = (*doc)->getProperty(Prop::Kind::ExportLatexClass);
        return lclass ? lclass->getExportLatexClass().latexClass
                      : "article";
    } else {
        return "article";
    }
}

void ExporterLatex::visitDocument(Res& res, In<Document> value) {
    __visit_specific_kind(res, value);
    res = b::stack();

    res->add(command("documentclass", {"12pt"}, {getLatexClass(value)}));

    for (const auto& hdr :
         value->getProperties(Prop::Kind::ExportLatexHeader)) {
        res->add(string(hdr.getExportLatexHeader().header));
    }


    {
        res->add(command("begin", {"document"}));
        for (const auto& it : value->subnodes) {
            res->add(visit(it));
        }
        res->add(command("end", {"document"}));
    }
}

void ExporterLatex::visitSubtree(Res& res, In<Subtree> tree) {
    __visit_specific_kind(res, tree);
    res = b::stack();

    QString name;
    auto    lclass = getLatexClass(tree.getDocument());
    if (lclass == "book") {
        switch (tree->level) {
            case 1: name = "chapter"; break;
            case 2: name = "section"; break;
            case 3: name = "subsection"; break;
            case 4: name = "subsubsection"; break;
            case 5: name = "paragraph"; break;
            case 6: name = "subparagraph"; break;
            default: name = "textbf"; break;
        }
    } else {
        switch (tree->level) {
            case 1: name = "section"; break;
            case 2: name = "subsection"; break;
            case 3: name = "subsubsection"; break;
            case 4: name = "paragraph"; break;
            case 5: name = "subparagraph"; break;
            default: name = "textbf"; break;
        }
    }


    res->add(command(name, {visit(tree->title)}));
    for (const auto& it : tree->subnodes) {
        res->add(visit(it));
    }
}

void ExporterLatex::visitParagraph(Res& res, In<Paragraph> par) {
    __visit_specific_kind(res, par);
    res = b::line();
    for (auto const& sub : par->subnodes) {
        res->add(visit(sub));
    }

    if (res->size() == 0) {
        res->add(string(" "));
    }
}

void ExporterLatex::visitTime(Res& res, In<Time> time) {
    if (time->isStatic()) {
        res = command(
            "textit",
            {time->getStatic().time.getDateTime().toString(Qt::ISODate)});
    } else {
        res = string("TODO dynamic time");
    }
}

QString ExporterLatex::escape(const QString& value) {
    QString res;
    res.reserve(value.size());
    for (QChar const& ch : value) {
        switch (ch.toLatin1()) {
            case '&': res.append("\\&"); break;
            case '_': res.append("\\_"); break;
            default: res.append(ch);
        }
    }
    return res;
}
