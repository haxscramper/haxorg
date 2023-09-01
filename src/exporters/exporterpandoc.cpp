#include "exporterpandoc.hpp"

#include <exporters/Exporter.cpp>
#include <exporters/ExporterUltraplain.hpp>

template class Exporter<ExporterPandoc, PandocRes>;

PandocRes ExporterPandoc::newRes(sem::SemId org) {
    if (org.isNil()) {
        return json();
    } else {
        json res = json::object();
        res["t"] = "TODO" + to_string(org->getKind());
        return res;
    }
}

json ExporterPandoc::content(sem::SemId id, SemSet const& skip) {
    json res = json::array();
    for (auto const& sub : id->subnodes) {
        if (!skip.contains(sub->getKind())) {
            for (auto const& it : visit(sub).unpacked) {
                res.push_back(it);
            }
        }
    }
    return res;
}


Pair<json, json> kv(json key, json value) {
    return std::make_pair(key, value);
}

json P(QString kind, json conten) {
    return json::object({
        kv("t", kind),
        kv("c", conten),
    });
}

void to_json(json& res, PandocRes const& value) { res = value.toJson(); }

template <typename T>
json convert_to_json(T const& value) {
    json result;
    to_json(result, value);
    return result;
}


template <>
json convert_to_json(json const& value) {
    return value;
}


template <typename... Args>
json ar(Args&&... args) {
    return json::array(
        {convert_to_json<std::remove_cvref_t<Args>>(args)...});
}

using AttrKv = Vec<Pair<QString, json>>;

json Attr(
    QString       identifier,
    CVec<QString> classes = {},
    AttrKv const& kvpairs = {}) {

    json pairs = json::array();
    for (auto const& [key, value] : kvpairs) {
        pairs.push_back(json::array({key, value}));
    }

    json cl = json::array();
    for (auto const& it : classes) {
        cl.push_back(it);
    }

    return json::array({identifier, cl, pairs});
}

using osk = OrgSemKind;

SemSet const NonToplevel = SemSet{osk::Newline, osk::Space, osk::Export};

void ExporterPandoc::visitDocument(PandocRes& res, In<sem::Document> doc) {
    res = json::object({
        kv("pandoc-api-version", {1, 22, 2, 1}),
        kv("meta", json::object()),
        kv("blocks", content(doc, NonToplevel)),
    });
}

void ExporterPandoc::visitNewline(PandocRes& res, In<sem::Newline> item) {
    res = P("Str", item->text);
}

void ExporterPandoc::visitSpace(PandocRes& res, In<sem::Space> item) {
    res = json::object({kv("t", "Space")});
}

void ExporterPandoc::visitWord(PandocRes& res, In<sem::Word> item) {
    res = P("Str", item->text);
}

void ExporterPandoc::visitRawText(PandocRes& res, In<sem::RawText> item) {
    res = P("Str", item->text);
}

void ExporterPandoc::visitPunctuation(
    PandocRes&           res,
    In<sem::Punctuation> item) {
    res = P("Str", item->text);
}

void ExporterPandoc::visitPlaceholder(
    PandocRes&           res,
    In<sem::Placeholder> item) {}

void ExporterPandoc::visitMonospace(
    PandocRes&         res,
    In<sem::Monospace> monospace) {}

void ExporterPandoc::visitBigIdent(
    PandocRes&        res,
    In<sem::BigIdent> item) {
    res = P("Str", item->text);
}

void ExporterPandoc::visitFootnote(
    PandocRes&        res,
    In<sem::Footnote> footnote) {
    res = P("Str", "TODO-FOOTNOTE");
}

void ExporterPandoc::visitSubtree(PandocRes& res, In<sem::Subtree> tree) {
    AttrKv attrs;

    if (tree->treeId) {
        attrs.push_back({"id", tree->treeId.value()});
    }

    res = P(
        "Header",
        ar(tree->level, Attr("preface", {}, attrs), content(tree->title)));

    for (auto const& sub : tree->subnodes) {
        if (!NonToplevel.contains(sub->getKind())) {
            res.unpacked.append(visit(sub).unpacked);
        }
    }
}

void ExporterPandoc::visitParagraph(
    PandocRes&         res,
    In<sem::Paragraph> par) {
    res = P("Para", content(par));
}

void ExporterPandoc::visitTime(PandocRes& res, In<sem::Time> time) {
    res = P("Str", time->getStatic().time.toString());
}

void ExporterPandoc::visitTimeRange(
    PandocRes&         res,
    In<sem::TimeRange> range) {
    res = P(
        "Str",
        range->from->getStatic().time.toString() + "--"
            + range->to->getStatic().time.toString());
}

void ExporterPandoc::visitBold(PandocRes& res, In<sem::Bold> bold) {
    res = P("Strong", content(bold));
}

void ExporterPandoc::visitItalic(PandocRes& res, In<sem::Italic> italic) {
    res = P("Emph", content(italic));
}

void ExporterPandoc::visitVerbatim(
    PandocRes&        res,
    In<sem::Verbatim> verb) {
    res = P("Code", ar(Attr("verbatim"), ExporterUltraplain::toStr(verb)));
}

void ExporterPandoc::visitQuote(PandocRes& res, In<sem::Quote> quote) {
    res = P("BlockQuote", ar(P("Para", content(quote->text))));
}

void ExporterPandoc::visitLink(PandocRes& res, In<sem::Link> link) {
    if (link->description) {
        res = P(
            "Link",
            ar(Attr(""),
               content(link->description.value()),
               ar(""_qs, ""_qs)));
    } else {
        res = P("Str", "");
    }
}

void ExporterPandoc::visitList(PandocRes& res, In<sem::List> list) {
    json listItems = json::array();
    for (auto const& sub : list->subnodes) {
        // Not exactly the same as what pandoc does with org mode file, but
        // it seems to do the job. Pandoc puts the list entry at the end of
        // the body as well, but haxorg has different AST structure. Later
        // on this needs to be revisited.
        json body = json::array();
        if (sub.is(osk::List)) {
            body.push_back(visit(sub).unpacked.at(0));
        } else {
            sem::SemIdT<sem::ListItem> item = sub.as<sem::ListItem>();
            for (auto const& part : item->subnodes) {
                body.push_back(P("Plain", content(part)));
            }
        }
        listItems.push_back(body);
    }

    res = P("BulletList", listItems);
}

void ExporterPandoc::visitListItem(
    PandocRes&        res,
    In<sem::ListItem> item) {}

void ExporterPandoc::visitTextSeparator(
    PandocRes&             res,
    In<sem::TextSeparator> sep) {
    res = P("HorizontalRule", "");
}

void ExporterPandoc::visitHashTag(PandocRes& res, In<sem::HashTag> tag) {
    res = P("Str", tag->head);
}

void ExporterPandoc::visitEscaped(
    PandocRes&       res,
    In<sem::Escaped> escaped) {
    res = P("Str", escaped->text);
}

void ExporterPandoc::visitUnderline(
    PandocRes&         res,
    In<sem::Underline> under) {
    res = P("Underline", content(under));
}

void ExporterPandoc::visitSymbol(PandocRes& res, In<sem::Symbol> sym) {
    res = P("Str", sym->name);
}

void ExporterPandoc::visitCenter(PandocRes& res, In<sem::Center> center) {
    res = P("Str", "CENTER");
}

void ExporterPandoc::visitExport(PandocRes& res, In<sem::Export> exp) {
    res = P("Str", "EXPORT");
}

void ExporterPandoc::visitEmpty(PandocRes& res, In<sem::Empty> empty) {
    res = P("Str", "");
}

void ExporterPandoc::visitStmtList(
    PandocRes&                 res,
    sem::SemIdT<sem::StmtList> arg) {}

void ExporterPandoc::visitAtMention(
    PandocRes&                  res,
    sem::SemIdT<sem::AtMention> arg) {}
void ExporterPandoc::visitMarkQuote(
    PandocRes&                  res,
    sem::SemIdT<sem::MarkQuote> arg) {}
void ExporterPandoc::visitInlineMath(
    PandocRes&                   res,
    sem::SemIdT<sem::InlineMath> arg) {}
void ExporterPandoc::visitCode(
    PandocRes&             res,
    sem::SemIdT<sem::Code> arg) {}
void ExporterPandoc::visitPar(PandocRes& res, sem::SemIdT<sem::Par> arg) {}
void ExporterPandoc::visitCmdArguments(
    PandocRes&                     res,
    sem::SemIdT<sem::CmdArguments> arg) {}
void ExporterPandoc::visitCommandGroup(
    PandocRes&                     res,
    sem::SemIdT<sem::CommandGroup> arg) {}
void ExporterPandoc::visitFileTarget(
    PandocRes&                   res,
    sem::SemIdT<sem::FileTarget> arg) {}
void ExporterPandoc::visitTable(
    PandocRes&              res,
    sem::SemIdT<sem::Table> arg) {}
void ExporterPandoc::visitRow(PandocRes& res, sem::SemIdT<sem::Row> arg) {}
void ExporterPandoc::visitDocumentGroup(
    PandocRes&                      res,
    sem::SemIdT<sem::DocumentGroup> arg) {}
void ExporterPandoc::visitCmdArgument(
    PandocRes&                    res,
    sem::SemIdT<sem::CmdArgument> arg) {}
void ExporterPandoc::visitDocumentOptions(
    PandocRes&                        res,
    sem::SemIdT<sem::DocumentOptions> arg) {}
void ExporterPandoc::visitAdmonitionBlock(
    PandocRes&                        res,
    sem::SemIdT<sem::AdmonitionBlock> arg) {}
void ExporterPandoc::visitSubtreeLog(
    PandocRes&                   res,
    sem::SemIdT<sem::SubtreeLog> arg) {}
void ExporterPandoc::visitCaption(
    PandocRes&                res,
    sem::SemIdT<sem::Caption> cap) {
    res = visit(cap->text);
}
void ExporterPandoc::visitInclude(
    PandocRes&                res,
    sem::SemIdT<sem::Include> arg) {}
void ExporterPandoc::visitStrike(
    PandocRes&               res,
    sem::SemIdT<sem::Strike> arg) {}
void ExporterPandoc::visitCompletion(
    PandocRes&                   res,
    sem::SemIdT<sem::Completion> arg) {}
void ExporterPandoc::visitMacro(
    PandocRes&              res,
    sem::SemIdT<sem::Macro> arg) {}
void ExporterPandoc::visitExample(
    PandocRes&                res,
    sem::SemIdT<sem::Example> arg) {}
void ExporterPandoc::visitParseError(
    PandocRes&                   res,
    sem::SemIdT<sem::ParseError> arg) {}
