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
    // FIXME join on comma, wrap on brackets
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
    // FIXME join on comma, wrap on brackets
    for (auto const& opt : opts) {
        addWrap(res, "[", "]", opt);
    }

    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

void ExporterLatex::visitNewline(Res& res, In<sem::Newline> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitSpace(Res& res, In<sem::Space> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitWord(Res& res, In<sem::Word> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitRawText(Res& res, In<sem::RawText> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitPunctuation(Res& res, In<sem::Punctuation> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitPlaceholder(Res& res, In<sem::Placeholder> item) {
    __visit_specific_kind(res, item);
    res = command(
        "textsc",
        {command("texttt", {string("<" + escape(item->text) + ">")})});
}


void ExporterLatex::visitBigIdent(Res& res, In<sem::BigIdent> item) {
    __visit_specific_kind(res, item);
    QString specialColor;

    auto s = item->text;

    // TOOD use `parseBigIdent` from the sem convert
    if (s == "TODO") {
        specialColor = "green";
    } else if (s == "WIP") {
        specialColor = "brown";
    }

    if (0 < specialColor.size()) {
        res = command(
            "fbox",
            {command(
                "colorbox",
                {string(specialColor), string(escape(item->text))})});
    } else {
        res = string(escape(item->text));
    }
}

void ExporterLatex::visitFootnote(Res& res, In<sem::Footnote> footnote) {
    res = string("");
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
                      : "extarticle";
    } else {
        return "extarticle";
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

    // TODO replace hardcoded default value for the font size with call to
    // `getLatexClassOptions` provided in the org document.
    res->add(command("documentclass", {"14pt"}, {getLatexClass(value)}));

    for (const auto& hdr :
         value->getProperties(Prop::Kind::ExportLatexHeader)) {
        res->add(string(hdr.getExportLatexHeader().header));
    }

    res->add(command("usepackage", {"csquotes"}));
    res->add(command("usepackage", {"bookmarks"}, {"hyperref"}));
    res->add(command("usepackage", {"xcolor"}));

    res->add(string(R"(
\newcommand*\sepline{%
  \begin{center}
    \rule[1ex]{\textwidth}{1pt}
  \end{center}}
)"));

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
                     // FIXME latex exporter is broken because of sem ID
                     // overloads, need to be fixed to get the right output
                     // here.
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


void ExporterLatex::visitUnderline(Res& res, In<sem::Underline> under) {
    res = command("underline", {b::line(subnodes(under))});
}

void ExporterLatex::visitMonospace(Res& res, In<sem::Monospace> mono) {
    res = command("texttt", {b::line(subnodes(mono))});
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
                if (link->description) {
                    res = visit(link->description.value());
                } else {
                    res = string("UNRESOLVED LINK");
                }
            }

            break;
        }

        case sem::Link::Kind::Footnote: {
            auto target = link->resolve();
            if (target) {
                res = command("footnote", {visit(target.value())});
            } else {
                res = string("fn:" + link->getFootnote().target);
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

void ExporterLatex::visitTextSeparator(
    Res&                   res,
    In<sem::TextSeparator> sep) {
    res = command("sepline");
}

void ExporterLatex::visitHashTag(Res& res, In<sem::HashTag> tag) {
    QString join;

    Func<void(In<sem::HashTag> const& tag)> aux;
    aux = [&](In<sem::HashTag> const& tag) {
        join += tag->head;
        if (tag->subtags.size() == 1) {
            join += "##";
            aux(tag->subtags.at(0));
        } else if (1 < tag->subtags.size()) {
            join += "##[";
            bool first = true;
            for (auto const& sub : tag->subtags) {
                if (!first) {
                    join += ",";
                }
                first = false;
                aux(sub);
            }

            join += "]";
        }
    };
    join = "#";
    aux(tag);
    res = command("texttt", {string(escape(join))});
}

void ExporterLatex::visitEscaped(Res& res, In<sem::Escaped> escaped) {
    res = string(escape(escaped->text.mid(1)));
}


QString ExporterLatex::escape(const QString& value) {
    QString res;
    res.reserve(value.size());
    for (QChar const& ch : value) {
        switch (ch.toLatin1()) {
            case '&':
            case '_':
            case '}':
            case '{':
            case '#':
            case '%': res.append('\\' + ch); break;
            default: res.append(ch);
        }
    }
    return res;
}
