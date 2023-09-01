#include "exporterpandoc.hpp"

#include <exporters/Exporter.cpp>
template class Exporter<ExporterPandoc, PandocRes>;

PandocRes ExporterPandoc::newRes(sem::SemId org) {
    if (org.isNil()) {
        return json();
    } else {
        json res    = json::object();
        res["kind"] = "TODO" + to_string(org->getKind());
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

void ExporterPandoc::visitDocument(PandocRes& res, In<sem::Document> doc) {
    res = json::object({
        kv("pandoc-api-version", {1, 22, 2, 1}),
        kv("meta", json::object()),
        kv("blocks", content(doc, SemSet{osk::Newline})),
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
    In<sem::Footnote> footnote) {}

void ExporterPandoc::visitSubtree(PandocRes& res, In<sem::Subtree> tree) {
    AttrKv attrs;

    if (tree->treeId) {
        attrs.push_back({"id", tree->treeId.value()});
    }

    res = P(
        "Header",
        ar(tree->level, Attr("preface", {}, attrs), content(tree->title)));

    for (auto const& sub : tree->subnodes) {
        res.unpacked.append(visit(sub).unpacked);
    }
}

void ExporterPandoc::visitParagraph(
    PandocRes&         res,
    In<sem::Paragraph> par) {
    res = P("Para", content(par));
}

void ExporterPandoc::visitTime(PandocRes& res, In<sem::Time> time) {}

void ExporterPandoc::visitTimeRange(
    PandocRes&         res,
    In<sem::TimeRange> range) {}

void ExporterPandoc::visitBold(PandocRes& res, In<sem::Bold> bold) {}

void ExporterPandoc::visitItalic(PandocRes& res, In<sem::Italic> italic) {}

void ExporterPandoc::visitVerbatim(
    PandocRes&        res,
    In<sem::Verbatim> verb) {}

void ExporterPandoc::visitQuote(PandocRes& res, In<sem::Quote> quote) {}

void ExporterPandoc::visitLink(PandocRes& res, In<sem::Link> link) {}

void ExporterPandoc::visitList(PandocRes& res, In<sem::List> list) {}

void ExporterPandoc::visitListItem(
    PandocRes&        res,
    In<sem::ListItem> item) {}

void ExporterPandoc::visitTextSeparator(
    PandocRes&             res,
    In<sem::TextSeparator> sep) {}

void ExporterPandoc::visitHashTag(PandocRes& res, In<sem::HashTag> tag) {}

void ExporterPandoc::visitEscaped(
    PandocRes&       res,
    In<sem::Escaped> escaped) {}

void ExporterPandoc::visitUnderline(
    PandocRes&         res,
    In<sem::Underline> under) {}

void ExporterPandoc::visitSymbol(PandocRes& res, In<sem::Symbol> sym) {}

void ExporterPandoc::visitCenter(PandocRes& res, In<sem::Center> center) {}

void ExporterPandoc::visitExport(PandocRes& res, In<sem::Export> exp) {}

void ExporterPandoc::visitEmpty(PandocRes& res, In<sem::Empty> empty) {}
