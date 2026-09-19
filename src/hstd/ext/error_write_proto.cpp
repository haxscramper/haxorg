#include "error_write_proto.hpp"

#if ORG_BUILD_WITH_PROTOBUF

namespace hstd::serde {

void proto_serde<error_write_proto::TermColorFg8Bit, hstd::TermColorFg8Bit>::write(
    error_write_proto::TermColorFg8Bit* out,
    hstd::TermColorFg8Bit const&        in) {
    out->set_value(static_cast<int32_t>(in));
}

void proto_serde<error_write_proto::TermColorFg8Bit, hstd::TermColorFg8Bit>::read(
    error_write_proto::TermColorFg8Bit const& in,
    hstd::TermColorFg8Bit*                    out) {
    *out = static_cast<hstd::TermColorFg8Bit>(in.value());
}

void proto_serde<error_write_proto::TermColorBg8Bit, hstd::TermColorBg8Bit>::write(
    error_write_proto::TermColorBg8Bit* out,
    hstd::TermColorBg8Bit const&        in) {
    out->set_value(static_cast<int32_t>(in));
}

void proto_serde<error_write_proto::TermColorBg8Bit, hstd::TermColorBg8Bit>::read(
    error_write_proto::TermColorBg8Bit const& in,
    hstd::TermColorBg8Bit*                    out) {
    *out = static_cast<hstd::TermColorBg8Bit>(in.value());
}

void proto_serde<error_write_proto::Style, hstd::Style>::write(
    error_write_proto::Style* out,
    hstd::Style const&        in) {
    out->set_value(static_cast<int32_t>(in));
}

void proto_serde<error_write_proto::Style, hstd::Style>::read(
    error_write_proto::Style const& in,
    hstd::Style*                    out) {
    *out = static_cast<hstd::Style>(in.value());
}

void proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
    error_write_proto::ColStyle* out,
    hstd::ColStyle const&        in) {
    proto_serde<error_write_proto::TermColorFg8Bit, hstd::TermColorFg8Bit>::write(
        out->mutable_fg(), in.fg);

    proto_serde<error_write_proto::TermColorBg8Bit, hstd::TermColorBg8Bit>::write(
        out->mutable_bg(), in.bg);

    out->clear_style();
    for (hstd::Style const value : in.style) {
        proto_serde<error_write_proto::Style, hstd::Style>::write(
            out->add_style(), value);
    }
}

void proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
    error_write_proto::ColStyle const& in,
    hstd::ColStyle*                    out) {
    proto_serde<error_write_proto::TermColorFg8Bit, hstd::TermColorFg8Bit>::read(
        in.fg(), &out->fg);

    proto_serde<error_write_proto::TermColorBg8Bit, hstd::TermColorBg8Bit>::read(
        in.bg(), &out->bg);

    out->style = {};
    for (error_write_proto::Style const& value : in.style()) {
        hstd::Style style;
        proto_serde<error_write_proto::Style, hstd::Style>::read(value, &style);
        out->style.incl(style);
    }
}

void proto_serde<error_write_proto::ColRune, hstd::ColRune>::write(
    error_write_proto::ColRune* out,
    hstd::ColRune const&        in) {
    out->set_rune(in.rune);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_style(), in.style);
}

void proto_serde<error_write_proto::ColRune, hstd::ColRune>::read(
    error_write_proto::ColRune const& in,
    hstd::ColRune*                    out) {
    out->rune = in.rune();
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.style(), &out->style);
}

void proto_serde<error_write_proto::ColText, hstd::ColText>::write(
    error_write_proto::ColText* out,
    hstd::ColText const&        in) {
    out->clear_runes();
    for (hstd::ColRune const& rune : in) {
        proto_serde<error_write_proto::ColRune, hstd::ColRune>::write(
            out->add_runes(), rune);
    }
}

void proto_serde<error_write_proto::ColText, hstd::ColText>::read(
    error_write_proto::ColText const& in,
    hstd::ColText*                    out) {
    out->clear();
    out->reserve(in.runes_size());

    for (error_write_proto::ColRune const& rune : in.runes()) {
        hstd::ColRune value;
        proto_serde<error_write_proto::ColRune, hstd::ColRune>::read(rune, &value);
        out->push_back(std::move(value));
    }
}

void proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::write(
    error_write_proto::ReportSourceId* out,
    hstd::ext::ReportSourceId const&   in) {
    out->set_value(static_cast<uint64_t>(in.getValue()));
}

void proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::read(
    error_write_proto::ReportSourceId const& in,
    hstd::ext::ReportSourceId*               out) {
    *out = hstd::ext::ReportSourceId{static_cast<std::size_t>(in.value())};
}

void proto_serde<error_write_proto::ReportLabelId, hstd::ext::ReportLabelId>::write(
    error_write_proto::ReportLabelId* out,
    hstd::ext::ReportLabelId const&   in) {
    out->set_value(static_cast<uint64_t>(in.getValue()));
}

void proto_serde<error_write_proto::ReportLabelId, hstd::ext::ReportLabelId>::read(
    error_write_proto::ReportLabelId const& in,
    hstd::ext::ReportLabelId*               out) {
    *out = hstd::ext::ReportLabelId{static_cast<std::size_t>(in.value())};
}

void proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::write(
    error_write_proto::IntSlice* out,
    hstd::Slice<int> const&      in) {
    out->set_first(in.first);
    out->set_last(in.last);
}

void proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::read(
    error_write_proto::IntSlice const& in,
    hstd::Slice<int>*                  out) {
    out->first = in.first();
    out->last  = in.last();
}

void proto_serde<error_write_proto::CodeSpan, hstd::ext::CodeSpan>::write(
    error_write_proto::CodeSpan* out,
    hstd::ext::CodeSpan const&   in) {
    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::write(
        out->mutable_id(), in.id);

    proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::write(
        out->mutable_range(), in.range);
}

void proto_serde<error_write_proto::CodeSpan, hstd::ext::CodeSpan>::read(
    error_write_proto::CodeSpan const& in,
    hstd::ext::CodeSpan*               out) {
    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::read(
        in.id(), &out->id);

    proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::read(
        in.range(), &out->range);
}

void proto_serde<error_write_proto::ReportSourceCache, hstd::ext::ReportSourceCache>::
    write(error_write_proto::ReportSourceCache*, hstd::ext::ReportSourceCache const&) {}

void proto_serde<error_write_proto::ReportSourceCache, hstd::ext::ReportSourceCache>::
    read(error_write_proto::ReportSourceCache const&, hstd::ext::ReportSourceCache*) {}

void proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::write(
    error_write_proto::ReportSourceLine* out,
    hstd::ext::ReportSourceLine const&   in) {
    out->set_offset(in.offset);
    out->set_len(in.len);
}

void proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::read(
    error_write_proto::ReportSourceLine const& in,
    hstd::ext::ReportSourceLine*               out) {
    out->offset = in.offset();
    out->len    = in.len();
}

void proto_serde<
    error_write_proto::ReportSource::OffsetLine,
    hstd::ext::ReportSource::OffsetLine>::
    write(
        error_write_proto::ReportSource::OffsetLine* out,
        hstd::ext::ReportSource::OffsetLine const&   in) {
    proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::write(
        out->mutable_line(), in.line);

    out->set_idx(in.idx);
    out->set_col(in.col);
}

void proto_serde<
    error_write_proto::ReportSource::OffsetLine,
    hstd::ext::ReportSource::OffsetLine>::
    read(
        error_write_proto::ReportSource::OffsetLine const& in,
        hstd::ext::ReportSource::OffsetLine*               out) {
    proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::read(
        in.line(), const_cast<hstd::ext::ReportSourceLine*>(&out->line));

    out->idx = in.idx();
    out->col = in.col();
}

void proto_serde<error_write_proto::ReportSource, hstd::ext::ReportSource>::write(
    error_write_proto::ReportSource* out,
    hstd::ext::ReportSource const&   in) {
    out->clear_lines();
    for (hstd::ext::ReportSourceLine const& line : in.lines) {
        proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::
            write(out->add_lines(), line);
    }

    out->set_len(in.len);

    proto_serde<error_write_proto::ColText, hstd::ColText>::write(
        out->mutable_content(), in.content);
}

void proto_serde<error_write_proto::ReportSource, hstd::ext::ReportSource>::read(
    error_write_proto::ReportSource const& in,
    hstd::ext::ReportSource*               out) {
    out->lines.clear();
    out->lines.reserve(in.lines_size());

    for (error_write_proto::ReportSourceLine const& line : in.lines()) {
        hstd::ext::ReportSourceLine value;
        proto_serde<error_write_proto::ReportSourceLine, hstd::ext::ReportSourceLine>::
            read(line, &value);
        out->lines.push_back(std::move(value));
    }

    out->len = in.len();

    proto_serde<error_write_proto::ColText, hstd::ColText>::read(
        in.content(), &out->content);
}

void proto_serde<
    error_write_proto::ReportSourceStrCache,
    hstd::ext::ReportSourceStrCache>::
    write(
        error_write_proto::ReportSourceStrCache* out,
        hstd::ext::ReportSourceStrCache const&   in) {
    out->clear_sources();
    out->clear_names();

    for (auto const& [id, source] : in.sources) {
        auto* entry = out->add_sources();

        proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::write(
            entry->mutable_id(), id);

        proto_serde<error_write_proto::ReportSource, hstd::ext::ReportSource>::write(
            entry->mutable_source(), *source);
    }

    for (auto const& [id, source] : in.sources) {
        std::optional<std::string> const name = in.names.get_right(id);
        if (name) {
            auto* entry = out->add_names();

            proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::
                write(entry->mutable_id(), id);

            entry->set_name(*name);
        }
    }
}

void proto_serde<
    error_write_proto::ReportSourceStrCache,
    hstd::ext::ReportSourceStrCache>::
    read(
        error_write_proto::ReportSourceStrCache const& in,
        hstd::ext::ReportSourceStrCache*               out) {
    out->sources.clear();

    for (auto const& entry : in.sources()) {
        auto id = hstd::ext::ReportSourceId::FromValue(entry.id().value());

        auto source = std::make_shared<hstd::ext::ReportSource>("");
        proto_serde<error_write_proto::ReportSource, hstd::ext::ReportSource>::read(
            entry.source(), source.get());

        out->sources[id] = std::move(source);
    }

    for (auto const& entry : in.names()) {
        auto id = hstd::ext::ReportSourceId::FromValue(entry.id().value());
        out->names.add_unique(id, entry.name());
    }
}

void proto_serde<error_write_proto::ReportCharacters, hstd::ext::ReportCharacters>::write(
    error_write_proto::ReportCharacters* out,
    hstd::ext::ReportCharacters const&   in) {
    out->set_hbar(in.hbar);
    out->set_vbar(in.vbar);
    out->set_xbar(in.xbar);
    out->set_vbar_break(in.vbar_break);
    out->set_vbar_gap(in.vbar_gap);
    out->set_uarrow(in.uarrow);
    out->set_rarrow(in.rarrow);
    out->set_ltop(in.ltop);
    out->set_mtop(in.mtop);
    out->set_rtop(in.rtop);
    out->set_lbot(in.lbot);
    out->set_rbot(in.rbot);
    out->set_mbot(in.mbot);
    out->set_lbox(in.lbox);
    out->set_rbox(in.rbox);
    out->set_lcross(in.lcross);
    out->set_rcross(in.rcross);
    out->set_underbar(in.underbar);
    out->set_underline(in.underline);
}

void proto_serde<error_write_proto::ReportCharacters, hstd::ext::ReportCharacters>::read(
    error_write_proto::ReportCharacters const& in,
    hstd::ext::ReportCharacters*               out) {
    out->hbar       = in.hbar();
    out->vbar       = in.vbar();
    out->xbar       = in.xbar();
    out->vbar_break = in.vbar_break();
    out->vbar_gap   = in.vbar_gap();
    out->uarrow     = in.uarrow();
    out->rarrow     = in.rarrow();
    out->ltop       = in.ltop();
    out->mtop       = in.mtop();
    out->rtop       = in.rtop();
    out->lbot       = in.lbot();
    out->rbot       = in.rbot();
    out->mbot       = in.mbot();
    out->lbox       = in.lbox();
    out->rbox       = in.rbox();
    out->lcross     = in.lcross();
    out->rcross     = in.rcross();
    out->underbar   = in.underbar();
    out->underline  = in.underline();
}

void proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::write(
    error_write_proto::ReportLabel* out,
    hstd::ext::ReportLabel const&   in) {
    proto_serde<error_write_proto::ReportLabelId, hstd::ext::ReportLabelId>::write(
        out->mutable_id(), in.id);

    proto_serde<error_write_proto::CodeSpan, hstd::ext::CodeSpan>::write(
        out->mutable_span(), in.span);

    if (in.msg) {
        proto_serde<error_write_proto::ColText, hstd::ColText>::write(
            out->mutable_msg(), *in.msg);
    } else {
        out->clear_msg();
    }

    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_color(), in.color);

    out->set_order(in.order);
    out->set_priority(in.priority);
}

void proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::read(
    error_write_proto::ReportLabel const& in,
    hstd::ext::ReportLabel*               out) {
    proto_serde<error_write_proto::ReportLabelId, hstd::ext::ReportLabelId>::read(
        in.id(), &out->id);

    proto_serde<error_write_proto::CodeSpan, hstd::ext::CodeSpan>::read(
        in.span(), &out->span);

    if (in.has_msg()) {
        hstd::ColText msg;
        proto_serde<error_write_proto::ColText, hstd::ColText>::read(in.msg(), &msg);
        out->msg = std::move(msg);
    } else {
        out->msg = std::nullopt;
    }

    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.color(), &out->color);

    out->order    = in.order();
    out->priority = in.priority();
}

void proto_serde<error_write_proto::LabelInfo, hstd::ext::LabelInfo>::write(
    error_write_proto::LabelInfo* out,
    hstd::ext::LabelInfo const&   in) {
    out->set_kind(static_cast<error_write_proto::LabelKind>(in.kind));

    proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::write(
        out->mutable_label(), in.label);
}

void proto_serde<error_write_proto::LabelInfo, hstd::ext::LabelInfo>::read(
    error_write_proto::LabelInfo const& in,
    hstd::ext::LabelInfo*               out) {
    out->kind = static_cast<hstd::ext::LabelKind>(in.kind());

    proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::read(
        in.label(), &out->label);
}

void proto_serde<error_write_proto::SourceGroup, hstd::ext::SourceGroup>::write(
    error_write_proto::SourceGroup* out,
    hstd::ext::SourceGroup const&   in) {
    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::write(
        out->mutable_src_id(), in.src_id);

    proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::write(
        out->mutable_span(), in.span);

    out->clear_labels();
    for (hstd::ext::LabelInfo const& label : in.labels) {
        proto_serde<error_write_proto::LabelInfo, hstd::ext::LabelInfo>::write(
            out->add_labels(), label);
    }
}

void proto_serde<error_write_proto::SourceGroup, hstd::ext::SourceGroup>::read(
    error_write_proto::SourceGroup const& in,
    hstd::ext::SourceGroup*               out) {
    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::read(
        in.src_id(), &out->src_id);

    proto_serde<error_write_proto::IntSlice, hstd::Slice<int>>::read(
        in.span(), &out->span);

    out->labels.clear();
    out->labels.reserve(in.labels_size());

    for (error_write_proto::LabelInfo const& label : in.labels()) {
        hstd::ext::LabelInfo value{
            .label = hstd::ext::ReportLabel(
                hstd::ext::ReportLabelId::Nil(),
                hstd::ext::CodeSpan(hstd::ext::ReportSourceId::Nil(), slice(0, 0)))};
        proto_serde<error_write_proto::LabelInfo, hstd::ext::LabelInfo>::read(
            label, &value);
        out->labels.push_back(std::move(value));
    }
}

void proto_serde<error_write_proto::ReportRenderConfig, hstd::ext::ReportRenderConfig>::
    write(
        error_write_proto::ReportRenderConfig* out,
        hstd::ext::ReportRenderConfig const&   in) {
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_error_color(), in.error_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_warning_color(), in.warning_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_advice_color(), in.advice_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_margin_color(), in.margin_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_unimportant_color(), in.unimportant_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::write(
        out->mutable_note_color(), in.note_color);

    out->set_cross_gap(in.cross_gap);
    out->set_label_attach(static_cast<error_write_proto::LabelAttach>(in.label_attach));
    out->set_compact(in.compact);
    out->set_underlines(in.underlines);
    out->set_multiline_arrows(in.multiline_arrows);
    out->set_color(in.color);
    out->set_tab_width(in.tab_width);
    out->set_debug_writes(in.debug_writes);
    out->set_debug_scopes(in.debug_scopes);
    out->set_debug_report_info(in.debug_report_info);

    proto_serde<error_write_proto::ReportCharacters, hstd::ext::ReportCharacters>::write(
        out->mutable_char_set(), in.char_set);
}

void proto_serde<error_write_proto::ReportRenderConfig, hstd::ext::ReportRenderConfig>::
    read(
        error_write_proto::ReportRenderConfig const& in,
        hstd::ext::ReportRenderConfig*               out) {
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.error_color(), &out->error_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.warning_color(), &out->warning_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.advice_color(), &out->advice_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.margin_color(), &out->margin_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.unimportant_color(), &out->unimportant_color);
    proto_serde<error_write_proto::ColStyle, hstd::ColStyle>::read(
        in.note_color(), &out->note_color);

    out->cross_gap         = in.cross_gap();
    out->label_attach      = static_cast<hstd::ext::LabelAttach>(in.label_attach());
    out->compact           = in.compact();
    out->underlines        = in.underlines();
    out->multiline_arrows  = in.multiline_arrows();
    out->color             = in.color();
    out->tab_width         = in.tab_width();
    out->debug_writes      = in.debug_writes();
    out->debug_scopes      = in.debug_scopes();
    out->debug_report_info = in.debug_report_info();

    proto_serde<error_write_proto::ReportCharacters, hstd::ext::ReportCharacters>::read(
        in.char_set(), &out->char_set);
}

void proto_serde<error_write_proto::Report, hstd::ext::Report>::write(
    error_write_proto::Report* out,
    hstd::ext::Report const&   in) {
    out->set_kind(static_cast<error_write_proto::ReportKind>(in.kind));

    if (in.code) {
        out->set_code(*in.code);
    } else {
        out->clear_code();
    }

    if (in.msg) {
        proto_serde<error_write_proto::ColText, hstd::ColText>::write(
            out->mutable_msg(), *in.msg);
    } else {
        out->clear_msg();
    }

    out->clear_note();
    for (hstd::ColText const& note : in.note) {
        proto_serde<error_write_proto::ColText, hstd::ColText>::write(
            out->add_note(), note);
    }

    out->clear_help();
    for (hstd::ColText const& help : in.help) {
        proto_serde<error_write_proto::ColText, hstd::ColText>::write(
            out->add_help(), help);
    }

    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::write(
        out->mutable_location()->mutable_source_id(), in.location.first);

    out->mutable_location()->set_offset(in.location.second);

    out->clear_labels();
    for (hstd::ext::ReportLabel const& label : in.labels) {
        proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::write(
            out->add_labels(), label);
    }

    proto_serde<error_write_proto::ReportRenderConfig, hstd::ext::ReportRenderConfig>::
        write(out->mutable_config(), in.config);
}

void proto_serde<error_write_proto::Report, hstd::ext::Report>::read(
    error_write_proto::Report const& in,
    hstd::ext::Report*               out) {
    out->kind = static_cast<hstd::ext::ReportKind>(in.kind());

    if (in.has_code()) {
        out->code = in.code();
    } else {
        out->code = std::nullopt;
    }

    if (in.has_msg()) {
        hstd::ColText msg;
        proto_serde<error_write_proto::ColText, hstd::ColText>::read(in.msg(), &msg);
        out->msg = std::move(msg);
    } else {
        out->msg = std::nullopt;
    }

    out->note.clear();
    out->note.reserve(in.note_size());
    for (error_write_proto::ColText const& note : in.note()) {
        hstd::ColText value;
        proto_serde<error_write_proto::ColText, hstd::ColText>::read(note, &value);
        out->note.push_back(std::move(value));
    }

    out->help.clear();
    out->help.reserve(in.help_size());
    for (error_write_proto::ColText const& help : in.help()) {
        hstd::ColText value;
        proto_serde<error_write_proto::ColText, hstd::ColText>::read(help, &value);
        out->help.push_back(std::move(value));
    }

    proto_serde<error_write_proto::ReportSourceId, hstd::ext::ReportSourceId>::read(
        in.location().source_id(), &out->location.first);

    out->location.second = in.location().offset();

    out->labels.clear();
    out->labels.reserve(in.labels_size());
    for (error_write_proto::ReportLabel const& label : in.labels()) {
        hstd::ext::ReportLabel value{
            hstd::ext::ReportLabelId::Nil(),
            hstd::ext::CodeSpan{
                hstd::ext::ReportSourceId::Nil(), hstd::Slice<int>{0, 0}}};

        proto_serde<error_write_proto::ReportLabel, hstd::ext::ReportLabel>::read(
            label, &value);

        out->labels.push_back(std::move(value));
    }

    proto_serde<error_write_proto::ReportRenderConfig, hstd::ext::ReportRenderConfig>::
        read(in.config(), &out->config);
}

} // namespace hstd::serde
#endif
