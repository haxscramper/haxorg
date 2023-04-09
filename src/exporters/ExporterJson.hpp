#include <exporters/Exporter.hpp>

struct ExporterJson : public Exporter {
    struct Result : public ExporterResult {
        json value;
    };

    json exportTo(sem::Wrap<sem::Org> node) {
        Wrap<ExporterResult> j_sub = exportNode(node);
        return j_sub->as<Result>()->value;
    }

    template <typename T>
    json for_each_convert(Vec<T> const& values) {
        json res = json::array();
        for (const auto& it : values) {
            res.push_back(exportTo(it));
        }
        return res;
    }

    template <typename T>
    json opt_convert(Opt<T> const& value) {
        json res = json();
        if (value.has_value()) {
            res = exportTo(value.value());
        }
        return res;
    }


    inline Wrap<Result> newJson(sem::Wrap<sem::Org> node) {
        Wrap<Result> res = std::make_shared<Result>();

        json j;
        j["kind"] = to_string(node->getKind());
        if (node->loc.has_value()) {
            auto& [line, col] = node->loc.value();
            json tmp;
            tmp["line"] = line;
            tmp["col"]  = col;
            j["loc"]    = tmp;
        } else {
            j["loc"] = json();
        }

        json tmp = json::array();
        for (const auto& sub : node->subnodes) {
            tmp.push_back(exportTo(sub));
        }
        j["subnodes"] = tmp;

        res->value = j;

        return res;
    }

    // Exporter interface
  public:
    Wrap<ExporterResult> exportStmtList(sem::Wrap<sem::StmtList>) override;
    Wrap<ExporterResult> exportRow(sem::Wrap<sem::Row>) override;
    Wrap<ExporterResult> exportTable(sem::Wrap<sem::Table>) override;
    Wrap<ExporterResult> exportHashTag(sem::Wrap<sem::HashTag>) override;
    Wrap<ExporterResult> exportCompletion(
        sem::Wrap<sem::Completion>) override;
    Wrap<ExporterResult> exportParagraph(
        sem::Wrap<sem::Paragraph>) override;
    Wrap<ExporterResult> exportBigIdent(sem::Wrap<sem::BigIdent>) override;
    Wrap<ExporterResult> exportLink(sem::Wrap<sem::Link>) override;
    Wrap<ExporterResult> exportBold(sem::Wrap<sem::Bold>) override;
    Wrap<ExporterResult> exportItalic(sem::Wrap<sem::Italic>) override;
    Wrap<ExporterResult> exportStrike(sem::Wrap<sem::Strike>) override;
    Wrap<ExporterResult> exportMonospace(
        sem::Wrap<sem::Monospace>) override;
    Wrap<ExporterResult> exportVerbatim(sem::Wrap<sem::Verbatim>) override;
    Wrap<ExporterResult> exportRawText(sem::Wrap<sem::RawText>) override;
    Wrap<ExporterResult> exportList(sem::Wrap<sem::List>) override;
    Wrap<ExporterResult> exportListItem(sem::Wrap<sem::ListItem>) override;
    Wrap<ExporterResult> exportCenter(sem::Wrap<sem::Center>) override;
    Wrap<ExporterResult> exportPar(sem::Wrap<sem::Par>) override;
    Wrap<ExporterResult> exportQuote(sem::Wrap<sem::Quote>) override;
    Wrap<ExporterResult> exportExample(sem::Wrap<sem::Example>) override;
    Wrap<ExporterResult> exportCode(sem::Wrap<sem::Code>) override;
    Wrap<ExporterResult> exportTime(sem::Wrap<sem::Time>) override;
    Wrap<ExporterResult> exportSubtreeLog(
        sem::Wrap<sem::SubtreeLog>) override;
    Wrap<ExporterResult> exportTimeRange(
        sem::Wrap<sem::TimeRange>) override;
    Wrap<ExporterResult> exportSubtree(sem::Wrap<sem::Subtree>) override;
    Wrap<ExporterResult> exportNewline(sem::Wrap<sem::Newline>) override;
    Wrap<ExporterResult> exportSpace(sem::Wrap<sem::Space>) override;
    Wrap<ExporterResult> exportWord(sem::Wrap<sem::Word>) override;
    Wrap<ExporterResult> exportPunctuation(
        sem::Wrap<sem::Punctuation>) override;
    Wrap<ExporterResult> exportMarkQuote(
        sem::Wrap<sem::MarkQuote>) override;
    Wrap<ExporterResult> exportCaption(sem::Wrap<sem::Caption>) override;
    Wrap<ExporterResult> exportCommandGroup(
        sem::Wrap<sem::CommandGroup>) override;
    Wrap<ExporterResult> exportPlaceholder(
        sem::Wrap<sem::Placeholder>) override;
    Wrap<ExporterResult> exportInlineMath(
        sem::Wrap<sem::InlineMath>) override;
    Wrap<ExporterResult> exportDocument(sem::Wrap<sem::Document>) override;
    Wrap<ExporterResult> exportDocumentGroup(
        sem::Wrap<sem::DocumentGroup>) override;
};
