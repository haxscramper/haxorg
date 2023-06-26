#include "exporterlatex.hpp"
#include <exporters/ExporterUltraplain.hpp>

#pragma clang diagnostic ignored "-Wreorder-init-list"

using namespace sem;
using osk  = OrgSemKind;
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

QString getSubtreeCommand(ExporterLatex::In<sem::Subtree> tree) {
    auto lclass = getLatexClass(tree->getDocument());
    if (lclass == "book") {
        switch (tree->level) {
            case 1: return "chapter";
            case 2: return "section";
            case 3: return "subsection";
            case 4: return "subsubsection";
            case 5: return "paragraph";
            case 6: return "subparagraph";
            default: return "textbf";
        }
    } else {
        switch (tree->level) {
            case 1: return "section";
            case 2: return "subsection";
            case 3: return "subsubsection";
            case 4: return "paragraph";
            case 5: return "subparagraph";
            default: return "textbf";
        }
    }
}

QString getRefKind(SemId id) {
    switch (id->getKind()) {
        case osk::Subtree: {
            auto command = getSubtreeCommand(id.as<sem::Subtree>());
            if (command == "section") {
                return "sec:";
            } else {
                return "";
            }
        }
        default: {
            return "";
        }
    }
}

void ExporterLatex::visitDocument(Res& res, In<Document> value) {
    __visit_specific_kind(res, value);
    res = b::stack();

    res->add(command("documentclass", {"14pt"}, {getLatexClass(value)}));

    for (const auto& hdr :
         value->getProperties(Prop::Kind::ExportLatexHeader)) {
        res->add(string(hdr.getExportLatexHeader().header));
    }

    res->add(command("usepackage", {"csquotes"}));
    res->add(command("usepackage", {"bookmarks"}, {"hyperref"}));

    res->add(command("begin", {"document"}));
    if (value->options) {
        auto exp = value->options->tocExport;
        if (std::holds_alternative<bool>(exp)) {
            if (std::get<bool>(exp)) {
                res->add(command("tableofcontents"));
            }
        } else {
            int level = std::get<int>(exp);
            res->add(command("tableofcontents"));
            res->add(
                command("setcounter", {"tocdepth", to_string(level)}));
        }
    }


    for (const auto& it : value->subnodes) {
        res->add(visit(it));
    }
    res->add(command("end", {"document"}));
}

void ExporterLatex::visitSubtree(Res& res, In<Subtree> tree) {
    __visit_specific_kind(res, tree);
    res = b::stack();

    auto titleText = b::line();
    for (const auto& item : tree->title->subnodes) {
        switch (item->getKind()) {
#define _direct(__Kind)                                                   \
    case osk::__Kind: titleText->add(visit(item)); break;
            EACH_SEM_ORG_LEAF_KIND(_direct)
#undef _direct

            default: {
                titleText->add(command(
                    "texorpdfstring",
                    {visit(item),
                     string(ExporterUltraplain::toStr(item))}));
            }
        }
    }

    res->add(command(getSubtreeCommand(tree), {titleText}));


    if (tree->treeId) {
        res->add(command(
            "label", {getRefKind(tree) + tree->treeId.value().toBase()}));
    }

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
        QString str;
        switch (time->getStatic().time.getKind()) {
            case UserTime::Kind::Date: {
                str = time->getStatic().time.getDate().toString(
                    Qt::ISODate);
                break;
            }
            case UserTime::Kind::DateTime: {
                str = time->getStatic().time.getDate().toString(
                    Qt::ISODate);
                break;
            }
            case UserTime::Kind::Time: {
                str = time->getStatic().time.getTime().toString(
                    Qt::ISODate);
                break;
            }
        }


        res = command("fbox", {command("texttt", {str})});
    } else {
        res = string("TODO dynamic time");
    }
}

void ExporterLatex::visitTimeRange(Res& res, In<sem::TimeRange> range) {
    res = b::line({visit(range->from), string("--"), visit(range->to)});
}

void ExporterLatex::visitBold(Res& res, In<sem::Bold> bold) {
    res = command("textbf", {b::line(subnodes(bold))});
}

void ExporterLatex::visitItalic(Res& res, In<sem::Italic> italic) {
    res = command("textit", {b::line(subnodes(italic))});
}

void ExporterLatex::visitVerbatim(Res& res, In<sem::Verbatim> verb) {
    res = command("textsc", {b::line(subnodes(verb))});
}

void ExporterLatex::visitQuote(Res& res, In<sem::Quote> quote) {
    res = b::stack();
    res->add(command("begin", {"displayquote"}));
    res->add(b::stack(subnodes(quote)));
    res->add(command("end", {"displayquote"}));
}

void ExporterLatex::visitLink(Res& res, In<sem::Link> link) {
    switch (link->getLinkKind()) {
        case sem::Link::Kind::Id: {
            auto target = link->resolve();
            if (target) {
                res = b::line({command(
                    "ref",
                    {string(
                        getRefKind(*target)
                        + link->getId().text.toBase())})});

                if (link->description) {
                    res->add(visit(link->description.value()));
                }

            } else {
                res = string("UNRESOLVED LINK");
            }

            break;
        }
        case sem::Link::Kind::Raw: {
            res = command(
                "href",
                {string(link->getRaw().text)},
                {link->description ? visit(link->description.value())
                                   : string("link")});
            res = string("href");
            break;
        }
        default: {
            res = string("LINK KIND" + to_string(link->getLinkKind()));
        }
    }
}

void ExporterLatex::visitList(Res& res, In<sem::List> list) {
    res = b::stack();
    res->add(command("begin", {"itemize"}));
    res->add(subnodes(list));
    res->add(command("end", {"itemize"}));
}

void ExporterLatex::visitListItem(Res& res, In<sem::ListItem> item) {
    res = b::line();
    if (item->isDescriptionItem()) {
        res->add(command("item", {visit(item->header.value())}));
    } else {
        res->add(command("item"));
    }
    res->add(string(" "));
    res->add(subnodes(item));
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
