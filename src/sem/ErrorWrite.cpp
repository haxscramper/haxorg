#include <hstd/stdlib/sequtils.hpp>
#include <sem/ErrorWrite.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <boost/preprocessor.hpp>

Characters unicode() {
    return Characters{
        .hbar       = Str("─"),
        .vbar       = Str("│"),
        .xbar       = Str("┼"),
        .vbar_break = Str("┆"),
        .vbar_gap   = Str("┆"),
        .uarrow     = Str("^"),
        .rarrow     = Str(">"),
        .ltop       = Str("╭"),
        .mtop       = Str("┬"),
        .rtop       = Str("╮"),
        .lbot       = Str("╰"),
        .rbot       = Str("╯"),
        .mbot       = Str("┴"),
        .lbox       = Str("["),
        .rbox       = Str("]"),
        .lcross     = Str("├"),
        .rcross     = Str("┤"),
        .underbar   = Str("┬"),
        .underline  = Str("─"),
    };
}

Characters ascii() {
    return Characters{
        .hbar       = Str("-"),
        .vbar       = Str("|"),
        .xbar       = Str("+"),
        .vbar_break = Str("*"),
        .vbar_gap   = Str(":"),
        .uarrow     = Str("^"),
        .rarrow     = Str(">"),
        .ltop       = Str(","),
        .mtop       = Str("v"),
        .rtop       = Str("."),
        .lbot       = Str("`"),
        .rbot       = Str("\'"),
        .mbot       = Str("^"),
        .lbox       = Str("["),
        .rbox       = Str("]"),
        .lcross     = Str("|"),
        .rcross     = Str("|"),
        .underbar   = Str("|"),
        .underline  = Str("^"),
    };
}


namespace {
struct LineLabel {
    int   col;
    Label label;
    bool  multi;
    bool  draw_msg;
    DESC_FIELDS(LineLabel, (col, label, multi, draw_msg));
};


#define _field(Type, Name, Default)                                       \
    Type           Name = Default;                                        \
    MarginContext& with_##Name(Type const& value) {                       \
        Name = value;                                                     \
        return *this;                                                     \
    }

struct Writer {
    ColStream& stream;
    Config*    config;
    template <typename T>
    void operator()(
        CR<T>       value,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        if (config->debug_writes) {
            stream << value << fmt("@{}", line);
        } else {
            stream << value;
        }
    }
};

struct MarginContext {
    Writer&       w;
    MarginContext clone() const { return *this; }
    ColText       line_text;
    _field(int, idx, 0);
    _field(bool, is_line, false);
    _field(bool, is_ellipsis, false);
    _field(int, line_no_width, 0);
    _field(bool, draw_labels, false);
    Line const&                         line;
    std::optional<std::pair<int, bool>> report_row = std::nullopt;
    MarginContext& with_report_row(std::pair<int, bool> const& value) {
        report_row = value;
        return *this;
    }


    const Vec<LineLabel>&           line_labels;
    const std::optional<LineLabel>& margin_label;
    std::shared_ptr<Source>         src;
    Vec<Label> const&               multi_labels;
    Characters const&               draw;
    Config const&                   config;

    finally scope(
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE()) const {
        if (config.debug_scopes) {
            w.stream << fmt("«{}:{}«", line, function);
            return finally{[&]() { w.stream << "»»"; }};
        } else {
            return finally::nop();
        }
    }
};


std::optional<LineLabel> get_margin_label(
    Line const&       line,
    Vec<Label> const& multi_labels) {
    std::optional<LineLabel> margin_label;
    int                      min_key = std::numeric_limits<int>::max();
    for (int i = 0; i < multi_labels.size(); ++i) {
        Label const& label    = multi_labels[i];
        bool         is_start = line.span().contains(label.span->start());
        bool         is_end   = line.span().contains(label.last_offset());

        if (is_start || is_end) {
            LineLabel ll{
                .col = (is_start ? label.span->start()
                                 : label.last_offset())
                     - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };


            int key = (ll.col << 1) | (!label.span->start());
            if (key < min_key) {
                min_key      = key;
                margin_label = ll;
            }
        }
    }
    return margin_label;
}

void write_margin(MarginContext const& c);

#define _dfmt_impl(_1, _2, arg)                                           \
    << " " << BOOST_PP_STRINGIZE(arg) << fmt(" = ⦃{}⦄", arg)


#define _dfmt(...)                                                        \
    DLOG(INFO) << "]" BOOST_PP_SEQ_FOR_EACH(                              \
        _dfmt_impl, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__));


bool sort_line_labels(
    MarginContext const& c,
    bool&                is_ellipsis,
    Vec<LineLabel>&      line_labels) {
    // Skip this line if we don't have labels for it
    if (line_labels.size() == 0 && !c.margin_label.has_value()) {
        bool within_label = std::any_of(
            c.multi_labels.begin(),
            c.multi_labels.end(),
            [&](Label const& label) {
                return label.span->contains(c.line.span().first);
            });
        if (!is_ellipsis && within_label) {
            is_ellipsis = true;
        } else {
            if (!c.config.compact && !is_ellipsis) {
                write_margin(c.clone().with_is_ellipsis(is_ellipsis));

                c.w("\n");
            }
            is_ellipsis = true;
            return true;
        }
    } else {
        is_ellipsis = false;
    }

    // Sort the labels by their columns
    std::sort(
        line_labels.begin(),
        line_labels.end(),
        [](const LineLabel& a, const LineLabel& b) {
            return std::make_tuple(
                       a.label.order, a.col, !a.label.span->start())
                 < std::make_tuple(
                       b.label.order, b.col, !b.label.span->start());
        });

    return false;
}

void fill_margin_elements(
    MarginContext const&        c,
    int                         col,
    Opt<Pair<Label, bool>>&     corner,
    Opt<Pair<LineLabel, bool>>& margin_ptr,
    Opt<Label>&                 vbar,
    Opt<Label>&                 hbar) {

    Slice<int> line_span = c.src->line(c.idx).value().span();
    for (int i = 0; i < std::min(col + 1, c.multi_labels.size()); ++i) {
        auto           label = c.multi_labels.at(i);
        Opt<LineLabel> margin;
        if (c.margin_label && label == c.margin_label->label) {
            margin = c.margin_label;
        }

        if (label.span->start() <= line_span.last
            && line_span.first < label.span->end()) {
            bool is_parent = i != col;
            bool is_start  = line_span.contains(label.span->start());
            bool is_end    = line_span.contains(label.last_offset());

            if (margin && c.is_line) {
                margin_ptr = std::make_pair(margin.value(), is_start);
            } else if (!is_start && (!is_end || c.is_line)) {
                if (!vbar && !is_parent) { vbar = label; }
            } else if (c.report_row.has_value()) {
                auto report_row_value = c.report_row.value();
                int  label_row        = 0;
                for (int r = 0; r < c.line_labels.size(); ++r) {
                    if (label == c.line_labels[r].label) {
                        label_row = r;
                        break;
                    }
                }

                if (report_row_value.first == label_row) {
                    if (margin) {
                        if (col == i) {
                            vbar = margin->label;
                        } else {
                            vbar = std::nullopt;
                        }

                        if (is_start) { continue; }
                    }

                    if (report_row_value.second) {
                        hbar = label;
                        if (!is_parent) {
                            corner = std::make_pair(label, is_start);
                        }
                    } else if (!is_start) {
                        if (!vbar && !is_parent) { vbar = label; }
                    }
                } else {
                    if (!vbar && !is_parent
                        && (is_start
                            ^ (report_row_value.first < label_row))) {
                        vbar = label;
                    }
                }
            }
        }
    }
}

Pair<ColRune, ColRune> get_corner_elements(
    MarginContext const&                c,
    int                                 col,
    CR<Opt<Pair<CRw<Label>, bool>>>     corner,
    CR<Opt<Label>>                      vbar,
    CR<Opt<Label>>                      hbar,
    CR<Opt<Pair<CRw<LineLabel>, bool>>> margin_ptr,
    CR<Opt<CRw<Label>>>                 multi_label) {
    std::pair<ColRune, ColRune> ab;

    if (corner) {
        auto [label, is_start] = *corner;
        ab                     = {
            is_start ? ColRune(c.draw.ltop, label.get().color)
                                         : ColRune(c.draw.lbot, label.get().color),
            ColRune(c.draw.hbar, label.get().color),
        };
    } else if (hbar && vbar && !c.config.cross_gap) {
        ab = {
            ColRune(c.draw.xbar, hbar->color),
            ColRune(c.draw.hbar, hbar->color),
        };
    } else if (hbar) {
        ab = {
            ColRune(c.draw.hbar, hbar->color),
            ColRune(c.draw.hbar, hbar->color),
        };
    } else if (vbar) {
        ab = {
            c.is_ellipsis ? ColRune(c.draw.vbar_gap, vbar->color)
                          : ColRune(c.draw.vbar, vbar->color),
            ColRune(' '),
        };
    } else if (margin_ptr && c.is_line) {
        auto [margin, is_start] = *margin_ptr;
        bool is_col             = multi_label
                                    ? (multi_label->get() == margin.get().label)
                                    : false;
        bool is_limit           = col == c.multi_labels.size();
        if (is_limit) {
            ab.first = ColRune(c.draw.rarrow, margin.get().label.color);
        } else if (is_col) {
            if (is_start) {
                ab.first = ColRune(c.draw.ltop, margin.get().label.color);
            } else {
                ab.first = ColRune(
                    c.draw.lcross, margin.get().label.color);
            }
        } else {
            ab.first = ColRune(c.draw.hbar, margin.get().label.color);
        }

        if (!is_limit) {
            ab.second = ColRune(c.draw.hbar, margin.get().label.color);
        } else {
            ab.second = ColRune(' ');
        }
    } else {
        ab = {
            ColRune(' '),
            ColRune(' '),
        };
    }

    return ab;
}


void write_margin(MarginContext const& c) {
    auto __scope = c.scope("margin");
    Str  line_no_margin;
    if (c.is_line && !c.is_ellipsis) {
        int line_no    = c.idx + 1;
        line_no_margin = Str(" ").repeated(
                             c.line_no_width - fmt1(line_no).length())
                       + Str(fmt1(line_no)) + Str(" ") + Str(c.draw.vbar);
    } else {
        line_no_margin = Str(" ").repeated(c.line_no_width + 1);
        line_no_margin += (c.is_ellipsis ? c.draw.vbar_gap : c.draw.vbar_break);
    }

    c.w(" ");
    c.w(ColText(c.config.margin_color, line_no_margin));
    c.w(c.config.compact ? "" : " ");


    // Multi-line margins
    if (c.draw_labels) {
        for (int col = 0; col < c.multi_labels.size()
                                    + (0 < c.multi_labels.size() ? 1 : 0);
             ++col) {

            Opt<Label>                 hbar       = std::nullopt;
            Opt<Label>                 vbar       = std::nullopt;
            Opt<Pair<Label, bool>>     corner     = std::nullopt;
            Opt<Pair<LineLabel, bool>> margin_ptr = std::nullopt;

            Opt<CRw<Label>> multi_label = c.multi_labels.get(col);

            fill_margin_elements(c, col, corner, margin_ptr, vbar, hbar);

            if (margin_ptr && c.is_line) {
                bool is_col = multi_label
                           && (*multi_label == margin_ptr->first.label);

                bool is_limit = col + 1 == c.multi_labels.size();
                if (!is_col && !is_limit) {
                    hbar = hbar.value_or(margin_ptr->first.label);
                }
            }

            if (hbar
                && !((*hbar != c.margin_label->label) || !c.is_line)) {
                hbar = std::nullopt;
            }


            Pair<ColRune, ColRune> ab = get_corner_elements(
                c, col, corner, vbar, hbar, margin_ptr, multi_label);

            c.w(ab.first);
            if (!c.config.compact) { c.w(ab.second); }
        }
    }
}


/// \brief Should we draw a vertical bar as part of a label arrow
/// on this line?
auto get_vbar(
    int                   col,
    int                   row,
    Vec<LineLabel> const& line_labels,
    Opt<LineLabel> const& margin_label) -> std::optional<LineLabel> {
    for (const auto& ll : line_labels) {
        if (ll.label.msg
            && (!margin_label.has_value()
                || ll.label != margin_label->label)
            && ll.col == col
            && ((row <= &ll - &line_labels[0] && !ll.multi)
                || (row <= &ll - &line_labels[0] && ll.multi))) {
            return ll;
        }
    }
    return std::nullopt;
};


Opt<CRw<Label>> get_highlight(
    int                      col,
    Vec<Label> const&        multi_labels,
    Line const&              line,
    Vec<LineLabel>&          line_labels,
    std::optional<LineLabel> margin_label) {
    Vec<CRw<Label>> candidates;

    if (margin_label) { candidates.push_back(margin_label->label); }
    for (const auto& l : multi_labels) { candidates.push_back(l); }
    for (const auto& l : line_labels) { candidates.push_back(l.label); }

    auto it = std::min_element(
        candidates.begin(),
        candidates.end(),
        [&](const auto& a, const auto& b) {
            return std::make_tuple(-a.get().priority, a.get().span->len())
                 < std::make_tuple(-b.get().priority, b.get().span->len());
        });


    if (it != candidates.end()
        && it->get().span->contains(line.offset + col)) {
        return *it;
    } else {
        return std::nullopt;
    }
};


auto get_underline(MarginContext const& c, int col) -> Opt<LineLabel> {
    Vec<std::reference_wrapper<LineLabel const>> candidates;
    for (const auto& it : c.line_labels) {
        if (c.config.underlines && !it.multi
            && it.label.span->contains(c.line.offset + col)) {
            candidates.push_back(it);
        }
    }

    if (candidates.empty()) { return std::nullopt; }

    return *std::min_element(
        candidates.begin(),
        candidates.end(),
        [&](const auto& a, const auto& b) {
            return std::make_tuple(
                       -a.get().label.priority, a.get().label.span->len())
                 < std::make_tuple(
                       -b.get().label.priority, b.get().label.span->len());
        });
};

void write_line_content(MarginContext const& c, int row, int arrow_len) {
    // Lines alternate
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {
        int width = 1;
        // (chars != c.line.chars.end())
        //     ? c.config.char_width(*chars, col).second
        //     : 1;

        Opt<LineLabel> underline = get_underline(c, col);
        if (row != 0) { underline.reset(); }

        std::array<ColRune, 2> ct_array;
        if (Opt<LineLabel> vbar = get_vbar(
                col, row, c.line_labels, c.margin_label)) {
            std::array<Str, 2> ct_inner;
            if (underline) {
                if (vbar->label.span->len() <= 1) {
                    ct_inner = {c.draw.underbar, c.draw.underline};
                } else if (
                    c.line.offset + col == vbar->label.span->start()) {
                    ct_inner = {c.draw.ltop, c.draw.underbar};
                } else if (
                    c.line.offset + col == vbar->label.last_offset()) {
                    ct_inner = {c.draw.rtop, c.draw.underbar};
                } else {
                    ct_inner = {c.draw.underbar, c.draw.underline};
                }
            } else if (
                vbar->multi && row == 0 && c.config.multiline_arrows) {
                ct_inner = {c.draw.uarrow, ' '};
            } else {
                ct_inner = {c.draw.vbar, ' '};
            }
            ct_array = {
                ColRune(ct_inner[0], vbar->label.color),
                ColRune(ct_inner[1], vbar->label.color),
            };
        } else if (underline) {
            ct_array = {
                ColRune(c.draw.underline, underline->label.color),
                ColRune(c.draw.underline, underline->label.color),
            };
        } else {
            ct_array = {ColRune(' '), ColRune(' ')};
        }

        for (int i = 0; i < width; ++i) {
            c.w((i == 0) ? ct_array[0] : ct_array[1]);
        }

        if (chars != c.line_text.end()) { ++chars; }
    }
}


Vec<Label> build_multi_labels(Vec<LabelInfo> const& labels) {
    Vec<Label> multi_labels;
    for (LabelInfo const& label_info : labels) {
        if (label_info.kind == LabelKind::Multiline) {
            multi_labels.push_back(label_info.label);
        }
    }

    // Sort multiline labels by length
    std::sort(
        multi_labels.begin(),
        multi_labels.end(),
        [](Label const& a, Label const& b) {
            return (a.span->len()) > (b.span->len());
        });

    return multi_labels;
}

Vec<LineLabel> build_line_labels(

    Config const&         config,
    Line const&           line,
    Vec<LabelInfo> const& labels,
    Opt<LineLabel> const& margin_label,
    Vec<Label> const&     multi_labels) {
    Vec<LineLabel> line_labels;
    for (CR<Label> label : multi_labels) {
        bool is_start = line.span().contains(label.span->start());
        bool is_end   = line.span().contains(label.last_offset());
        bool different_from_margin_label
            = (!margin_label.has_value() || label != margin_label->label);

        if ((is_start && different_from_margin_label) || is_end) {
            LineLabel ll{
                .col = (is_start ? label.span->start()
                                 : label.last_offset())
                     - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };


            line_labels.push_back(ll);
        }
    }

    for (const LabelInfo& label_info : labels) {
        if (label_info.label.span->start() >= line.span().first
            && label_info.label.span->end() <= line.span().last) {
            if (label_info.kind == LabelKind::Inline) {
                int position = 0;
                switch (config.label_attach) {
                    case LabelAttach::Start:
                        position = label_info.label.span->start();
                        break;
                    case LabelAttach::Middle:
                        position = (label_info.label.span->start()
                                    + label_info.label.span->end())
                                 / 2;
                        break;
                    case LabelAttach::End:
                        position = label_info.label.last_offset();
                        break;
                }

                LineLabel ll{
                    .col = std::max(
                               position, label_info.label.span->start())
                         - line.offset,
                    .label    = label_info.label,
                    .multi    = false,
                    .draw_msg = true,
                };


                line_labels.push_back(ll);
            }
        }
    }

    return line_labels;
}

int get_line_no_width(Vec<SourceGroup> const& groups, Cache& cache) {
    int line_no_width = 0;
    for (const auto& group : groups) {
        Str  src_name = cache.display(group.src_id).value_or("<unknown>");
        auto src      = cache.fetch(group.src_id);

        auto line_range = src->get_line_range(RangeCodeSpan(group.span));
        int  width      = fmt1(line_range.last).size();
        line_no_width   = std::max(line_no_width, width);
    }
    return line_no_width;
}

void write_lines(
    MarginContext const& c,
    Line const&          line,
    int                  arrow_len,
    LineLabel const&     line_label,
    int                  row) {
    // Lines
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {
        int width = 1;

        bool is_hbar = (((col > line_label.col) ^ line_label.multi)
                        || (line_label.label.msg && line_label.draw_msg
                            && col > line_label.col))
                    && line_label.label.msg;
        std::array<ColRune, 2> ct_array;
        if (col == line_label.col && line_label.label.msg
            && (!c.margin_label.has_value()
                || line_label.label != c.margin_label->label)) {
            ct_array = {
                ColRune(
                    (line_label.multi ? (line_label.draw_msg ? c.draw.mbot
                                                             : c.draw.rbot)
                                      : c.draw.lbot),
                    line_label.label.color),
                ColRune(c.draw.hbar, line_label.label.color),
            };
        } else if (std::optional<LineLabel> vbar_ll = std::nullopt;
                   (vbar_ll = get_vbar(
                        col, row, c.line_labels, c.margin_label))
                   && (col != line_label.col || line_label.label.msg)) {
            if (!c.config.cross_gap && is_hbar) {
                ct_array = {
                    ColRune(c.draw.xbar, line_label.label.color),
                    ColRune(' ', line_label.label.color),
                };
            } else if (is_hbar) {
                ct_array = {
                    ColRune(c.draw.hbar, line_label.label.color),
                    ColRune(c.draw.hbar, line_label.label.color),
                };
            } else {
                ct_array = {
                    ColRune(
                        (vbar_ll->multi && row == 0 && c.config.compact
                             ? c.draw.uarrow
                             : c.draw.vbar),
                        vbar_ll->label.color),
                    ColRune(' ', line_label.label.color),
                };
            }
        } else if (is_hbar) {
            ct_array = {
                ColRune(c.draw.hbar, line_label.label.color),
                ColRune(c.draw.hbar, line_label.label.color),
            };
        } else {
            ct_array = {
                ColRune(' '),
                ColRune(' '),
            };
        }

        if (width > 0) { c.w(ct_array[0]); }
        for (int i = 1; i < width; ++i) { c.w(ct_array[1]); }
        if (chars != c.line_text.end()) { ++chars; }
    }
}
}; // namespace

Vec<SourceGroup> Report::get_source_groups(Cache* cache) {
    Vec<SourceGroup> groups;
    for (const auto& label : labels) {
        auto src_display            = cache->display(label.span->source());
        std::shared_ptr<Source> src = cache->fetch(label.span->source());
        if (!src) { continue; }

        CHECK(label.span->start() <= label.span->end())
            << "Label start is after its end";

        auto start_line //
            = src->get_offset_line(label.span->start()).value().idx;

        auto end_line //
            = src->get_offset_line(
                     std::max(label.span->end() - 1, label.span->start()))
                  .value()
                  .idx;

        LabelInfo label_info{
            .kind  = (start_line == end_line) ? LabelKind::Inline
                                              : LabelKind::Multiline,
            .label = label,
        };

        auto it = std::find_if(
            groups.begin(), groups.end(), [&](const SourceGroup& group) {
                return group.src_id == label.span->source();
            });

        if (it != groups.end()) {
            it->span.first = std::min(it->span.first, label.span->start());
            it->span.last  = std::max(it->span.last, label.span->end());
            it->labels.push_back(label_info);
        } else {
            groups.push_back(SourceGroup{
                .src_id = label.span->source(),
                .span   = slice(label.span->start(), label.span->end()),
                .labels = {label_info}});
        }
    }
    return groups;
}

void write_report_group(
    int                     group_idx,
    int                     line_no_width,
    Cache&                  cache,
    Report const&           report,
    Vec<SourceGroup> const& groups,
    Writer&                 op,
    Characters const&       draw) {
    SourceGroup const& group                = groups[group_idx];
    auto const& [src_id, char_span, labels] = group;
    auto const& config                      = report.config;

    Str src_name = cache.display(src_id).value_or("<unknown>");
    std::shared_ptr<Source> src = cache.fetch(src_id);
    op(Str(" ").repeated(line_no_width + 2));
    op((group_idx == 0 ? ColRune(draw.ltop) : ColRune(draw.lcross))
       + config.margin_color);
    op(ColRune(draw.hbar) + config.margin_color);
    op(ColRune(draw.lbox) + config.margin_color);
    op(src_name);

    // File name & reference
    int location = (src_id == report.location.first)
                     ? report.location.second
                     : labels[0].label.span->start();

    auto offset_line = src->get_offset_line(location);

    // Error line and column number in the error message header
    if (offset_line) {
        op(":");
        op(fmt1(offset_line->idx + 1));
        op(":");
        op(fmt1(offset_line->col + 1));
    } else {
        op(":?:?");
    }

    op(ColRune(draw.rbox) + config.margin_color);
    op("\n");

    if (!config.compact) {
        op(Str(" ").repeated(line_no_width + 2));
        op(ColRune(draw.vbar) + config.margin_color);
        op("\n");
    }


    // Generate a list of multi-line labels
    Vec<Label> multi_labels = build_multi_labels(labels);
    Slice<int> line_range = src->get_line_range(RangeCodeSpan(char_span));

    bool is_ellipsis = false;
    for (int idx = line_range.first; idx <= line_range.last; ++idx) {
        auto line_opt = src->line(idx);
        if (!line_opt) { continue; }

        Line                     line         = line_opt.value();
        std::optional<LineLabel> margin_label = get_margin_label(
            line, multi_labels);

        Vec<LineLabel> line_labels //
            = build_line_labels(
                config, line, labels, margin_label, multi_labels);

        for (auto const& it : line_labels) { LOG(INFO) << fmt1(it); }


        MarginContext base{
            .w             = op,
            .config        = config,
            .draw          = draw,
            .multi_labels  = multi_labels,
            .line_labels   = line_labels,
            .src           = src,
            .idx           = idx,
            .line_no_width = line_no_width,
            .line          = line,
            .margin_label  = margin_label,
            .line_text     = src->get_line_text(line),
        };

        bool do_skip = sort_line_labels(base, is_ellipsis, line_labels);

        if (do_skip) { continue; }

        // Determine label bounds so we know where to put error
        // messages
        int arrow_len = 0;
        for (const auto& ll : line_labels) {
            if (ll.multi) {
                arrow_len = line.get_len();
            } else {
                arrow_len = std::max(
                    arrow_len, ll.label.span->end() - line.offset);
            }
        }

        arrow_len += config.compact ? 1 : 2; // add arrow end space

        // Margin
        write_margin(base.clone()
                         .with_is_line(true)
                         .with_is_ellipsis(is_ellipsis)
                         .with_draw_labels(true));

        // Lines
        if (!is_ellipsis) {
            int col = 0;
            for (ColRune const& c : base.line_text) {
                Opt<CRw<Label>> highlight = get_highlight(
                    col, multi_labels, line, line_labels, margin_label);

                ColStyle color = highlight ? highlight->get().color
                                           : config.unimportant_color;

                op(ColRune(c.rune, color));

                col++;
            }
        }
        op("\n");

        for (int row = 0; row < line_labels.size(); ++row) {
            const auto& line_label = line_labels[row];

            if (!config.compact) {
                // Margin alternate
                write_margin(
                    base.clone().with_draw_labels(true).with_report_row(
                        {row, false}));

                write_line_content(
                    base.with_is_ellipsis(is_ellipsis), row, arrow_len);

                base.w("\n");
            }

            // Margin
            write_margin(base.clone()
                             .with_is_ellipsis(is_ellipsis)
                             .with_report_row({row, true})
                             .with_draw_labels(true));

            write_lines(base.clone(), line, arrow_len, line_label, row);

            if (line_label.label.msg) {
                op(" ");
                op(line_label.label.msg.value());
            }
            op("\n");
        }
    }

    bool is_final_group = group_idx + 1 == groups.size();

    Opt<LineLabel> null_label = std::nullopt;
    MarginContext  base{
         .w             = op,
         .config        = config,
         .draw          = draw,
         .multi_labels  = multi_labels,
         .line_labels   = {},
         .src           = src,
         .idx           = 0,
         .line_no_width = line_no_width,
         .draw_labels   = true,
         .is_line       = false,
         .is_ellipsis   = false,
         .report_row    = std::pair{0, false},
         .line          = Line{},
         .margin_label  = null_label,
    };


    // Help
    if (report.help.has_value() && is_final_group) {
        if (!config.compact) {
            write_margin(base);
            op("\n");
        }
        write_margin(base);
        op("Help: ");
        op(report.help.value());
        op("\n");
    }

    // Note
    if (report.note.has_value() && is_final_group) {
        if (!config.compact) {
            write_margin(base);
            op("\n");
        }
        write_margin(base);

        op("Note: ");
        op(report.note.value());
        op("\n");
    }

    // Tail of report
    if (!config.compact) {
        if (is_final_group) {
            op(Str(draw.hbar).repeated(line_no_width + 2));
            op(draw.rbot);
            op("\n");
        } else {
            op(Str(" ").repeated(line_no_width + 2));
            op(draw.vbar);
            op("\n");
        }
    }
}

void write_report_header(Report const& report, Writer& op) {
    ColStyle kind_color;
    Str      kindName;
    switch (report.kind) {
        case ReportKind::Error: {
            kind_color = report.config.error_color;
            kindName   = "Error";
            break;
        }
        case ReportKind::Warning: {
            kind_color = report.config.warning_color;
            kindName   = "Warning";
            break;
        }
        case ReportKind::Advice: {
            kind_color = report.config.advice_color;
            kindName   = "Advice";
            break;
        }
        case ReportKind::Custom: {
            kind_color = report.config.unimportant_color;
            kindName   = "Custom";
            break;
        }
    }

    if (report.code.has_value()) {
        op(ColText(kind_color, ("[" + *report.code + "] ")));
    }

    if (report.msg) {
        op(ColText(kind_color, kindName));
        op(": ");
        op(report.msg.value());
        op("\n");
    } else {
        op("\n");
    }
}

void Report::write_for_stream(Cache& cache, ColStream& w) {
    w.colored       = true;
    Characters draw = Characters{};
    switch (config.char_set) {
        case MessageCharSet::Unicode: draw = unicode(); break;
        case MessageCharSet::Ascii: draw = ascii(); break;
    }

    auto op = Writer{w, &config};

    write_report_header(*this, op);


    Vec<SourceGroup> groups = get_source_groups(&cache);

    // Line number maximum width
    int line_no_width = get_line_no_width(groups, cache);
    // --- Source sections ---
    for (int group_idx = 0; group_idx < groups.size(); ++group_idx) {

        write_report_group(
            group_idx, line_no_width, cache, *this, groups, op, draw);
    }
}

Source::Source(const Str& l) : content{l} {
    int offset = 0;
    for (std::string const& line : l.split('\n')) {
        Line l{
            .offset = offset,
            .len    = rune_length(line),
        };

        // _dfmt(line, l.len, line.size());
        offset += l.len + 1;
        lines.push_back(l);
    }
    len = offset;
}

std::optional<Source::OffsetLine> Source::get_offset_line(int offset) {
    if (offset <= len) {
        auto it = std::lower_bound(
            lines.begin(),
            lines.end(),
            offset,
            [](const Line& line, int offset) {
                return line.offset < offset;
            });
        if (it != lines.begin()) { --it; }
        int         idx  = std::distance(lines.begin(), it);
        const Line& line = lines[idx];
        CHECK(line.offset <= offset)
            << fmt("line.offset = {} <= offset = {}", line.offset, offset);
        // _dfmt(idx, offset, line.offset);
        return OffsetLine{std::ref(line), idx, offset - line.offset};
    } else {
        return std::nullopt;
    }
}

Slice<int> Source::get_line_range(const CodeSpan& span) {
    std::optional<OffsetLine> start = get_offset_line(span.start());
    std::optional<OffsetLine> end   = get_offset_line(
        std::max(span.end(), span.start()));

    int start_idx = start ? start->idx : 0;
    int end_idx   = end ? end->idx + 1 : this->lines.high();
    return slice(start_idx, end_idx);
}

ColText Source::get_line_text(CR<Line> line) {
    return content.at(slice(line.offset, line.offset + line.len - 1));
}

std::pair<char, int> Config::char_width(char c, int col) const {
    if (c == '\t') {
        // Find the column that the tab should end at
        int tab_end = (col / tab_width + 1) * tab_width;
        return std::make_pair(' ', tab_end - col);
    } else if (c == ' ') {
        return std::make_pair(' ', 1);
    } else {
        // Assuming you have a function called 'width()' to get the
        // character width.
        int char_width = 1;
        return std::make_pair(c, char_width);
    }
}
