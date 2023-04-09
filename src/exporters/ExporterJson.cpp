#include <exporters/ExporterJson.hpp>

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportStmtList(
    sem::Wrap<sem::StmtList> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportRow(
    sem::Wrap<sem::Row> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportTable(
    sem::Wrap<sem::Table> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportHashTag(
    sem::Wrap<sem::HashTag> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportCompletion(
    sem::Wrap<sem::Completion> node) {

    Wrap<ExporterJson::Result> w_res = newJson(node);

    json& res        = w_res->value;
    res["done"]      = node->done;
    res["full"]      = node->full;
    res["isPercent"] = node->isPercent;

    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportParagraph(
    sem::Wrap<sem::Paragraph> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportBigIdent(
    sem::Wrap<sem::BigIdent> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportLink(
    sem::Wrap<sem::Link> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportBold(
    sem::Wrap<sem::Bold> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportItalic(
    sem::Wrap<sem::Italic> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportStrike(
    sem::Wrap<sem::Strike> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportMonospace(
    sem::Wrap<sem::Monospace> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportVerbatim(
    sem::Wrap<sem::Verbatim> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportRawText(
    sem::Wrap<sem::RawText> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportList(
    sem::Wrap<sem::List> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportListItem(
    sem::Wrap<sem::ListItem> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportCenter(
    sem::Wrap<sem::Center> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportPar(
    sem::Wrap<sem::Par> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportQuote(
    sem::Wrap<sem::Quote> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportExample(
    sem::Wrap<sem::Example> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportCode(
    sem::Wrap<sem::Code> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportTime(
    sem::Wrap<sem::Time> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;

    res["isActive"] = node->isActive;
    res["isStatic"] = node->isStatic();
    if (node->isStatic()) {
        sem::Time::Static const& impl = node->getStatic();
        json                     repeat;
        if (impl.repeat.has_value()) {
            auto& r        = *impl.repeat;
            repeat["mode"] = to_string(r.mode);
        }
        json jtime;
        jtime["repeat"] = repeat;
        jtime["time"]   = impl.time.toString(Qt::ISODate);
        res["static"]   = jtime;
    } else {
        res["dynamic"] = node->getDynamic().expr;
    }

    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportSubtreeLog(
    sem::Wrap<sem::SubtreeLog> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportTimeRange(
    sem::Wrap<sem::TimeRange> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);

    json& res   = w_res->value;
    res["from"] = exportTo(node->from);
    res["to"]   = exportTo(node->to);
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportSubtree(
    sem::Wrap<sem::Subtree> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;

    res["level"]       = node->level;
    res["todo"]        = node->todo;
    res["tags"]        = for_each_convert(node->tags);
    res["logbook"]     = for_each_convert(node->logbook);
    res["description"] = opt_convert(node->description);
    res["completion"]  = opt_convert(node->completion);
    res["title"]       = node->title ? exportTo(node->title) : json();

    json drawer = json::object();
    {
        json props = json::array();
        for (const auto& prop : node->properties) {
            json exp;
            std::visit(
                [&](auto const& prop) {
                    exp["kind"] = to_string(prop.getKind());
                },
                prop);

            std::visit(
                overloaded{
                    [&](CR<sem::Subtree::Properties::ExportOptions> prop) {
                        exp["backend"] = prop.backend;
                        exp["args"]    = prop.values;
                    },
                    [](auto&&) {}},
                prop);

            props.push_back(exp);
        }

        drawer["props"] = props;
    }

    {
        json log      = json::object();
        drawer["log"] = log;
    }

    res["drawer"] = drawer;


    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportNewline(
    sem::Wrap<sem::Newline> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportSpace(
    sem::Wrap<sem::Space> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportWord(
    sem::Wrap<sem::Word> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportPunctuation(
    sem::Wrap<sem::Punctuation> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportMarkQuote(
    sem::Wrap<sem::MarkQuote> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportCaption(
    sem::Wrap<sem::Caption> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportCommandGroup(
    sem::Wrap<sem::CommandGroup> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportPlaceholder(
    sem::Wrap<sem::Placeholder> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportInlineMath(
    sem::Wrap<sem::InlineMath> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportDocument(
    sem::Wrap<sem::Document> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}

Exporter::Wrap<Exporter::ExporterResult> ExporterJson::exportDocumentGroup(
    sem::Wrap<sem::DocumentGroup> node) {
    Wrap<ExporterJson::Result> w_res = newJson(node);
    json&                      res   = w_res->value;
    return w_res;
}
