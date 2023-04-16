#include <hstd/stdlib/sequtils.hpp>
#include <sem/ErrorWrite.hpp>
#include <QChar>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Debug.hpp>

Characters unicode() {
    return Characters{
        .hbar       = QChar(L'─'),
        .vbar       = QChar(L'│'),
        .xbar       = QChar(L'┼'),
        .vbar_break = QChar(L'┆'),
        .vbar_gap   = QChar(L'┆'),
        .uarrow     = QChar(L'^'),
        .rarrow     = QChar(L'>'),
        .ltop       = QChar(L'╭'),
        .mtop       = QChar(L'┬'),
        .rtop       = QChar(L'╮'),
        .lbot       = QChar(L'╰'),
        .rbot       = QChar(L'╯'),
        .mbot       = QChar(L'┴'),
        .lbox       = QChar(L'['),
        .rbox       = QChar(L']'),
        .lcross     = QChar(L'├'),
        .rcross     = QChar(L'┤'),
        .underbar   = QChar(L'┬'),
        .underline  = QChar(L'─'),
    };
}

Characters ascii() {
    return Characters{
        .hbar       = QChar('-'),
        .vbar       = QChar('|'),
        .xbar       = QChar('+'),
        .vbar_break = QChar('*'),
        .vbar_gap   = QChar(':'),
        .uarrow     = QChar('^'),
        .rarrow     = QChar('>'),
        .ltop       = QChar(','),
        .mtop       = QChar('v'),
        .rtop       = QChar('.'),
        .lbot       = QChar('`'),
        .rbot       = QChar('\''),
        .mbot       = QChar('^'),
        .lbox       = QChar('['),
        .rbox       = QChar(']'),
        .lcross     = QChar('|'),
        .rcross     = QChar('|'),
        .underbar   = QChar('|'),
        .underline  = QChar('^'),
    };
}


namespace {
struct LineLabel {
    int   col;
    Label label;
    bool  multi;
    bool  draw_msg;
};


#define _field(Type, Name, Default)                                       \
    Type           Name = Default;                                        \
    MarginContext& with_##Name(Type const& value) {                       \
        Name = value;                                                     \
        return *this;                                                     \
    }

struct MarginContext {
    ColStream&    w;
    MarginContext clone() const { return *this; }
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
    const std::optional<LineLabel>& margin_label = std::nullopt;
    //    int                                 line_no_width = 0;
    std::shared_ptr<Source> src;
    Vec<Label> const&       multi_labels;
    Characters const&       draw;
    Config const&           config;
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

                c.w << "\n";
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


void write_margin(MarginContext const& c) {
    QString line_no_margin;
    if (c.is_line && !c.is_ellipsis) {
        int line_no    = c.idx + 1;
        line_no_margin = QString(" ").repeated(
                             c.line_no_width
                             - QString::number(line_no).length())
                       + QString::number(line_no) + " " + c.draw.vbar;
    } else {
        line_no_margin = QString(" ").repeated(c.line_no_width + 1)
                       + (c.is_ellipsis ? c.draw.vbar_gap
                                        : c.draw.vbar_break);
    }

    c.w << " " << line_no_margin + c.config.margin_color
        << (c.config.compact ? "" : " ");


    // Multi-line margins
    if (c.draw_labels) {
        for (int col = 0;
             col < c.multi_labels.size() + (c.multi_labels.size() > 0);
             ++col) {
            std::optional<std::pair<const Label*, bool>>
                                 corner = std::nullopt;
            std::optional<Label> hbar   = std::nullopt;
            std::optional<Label> vbar   = std::nullopt;
            std::optional<std::pair<const LineLabel*, bool>>
                margin_ptr = std::nullopt;

            Opt<CRw<Label>> multi_label = c.multi_labels.get(col);
            auto            line_span = c.src->line(c.idx).value().span();

            for (int i = 0; i < std::min(col + 1, c.multi_labels.size());
                 ++i) {
                const auto& label  = c.multi_labels.at(i);
                auto        margin = c.margin_label
                                       ? (label == c.margin_label->label
                                              ? &(*c.margin_label)
                                              : nullptr)
                                       : nullptr;

                if (label.span->start() <= line_span.last
                    && line_span.first < label.span->end()) {
                    bool is_parent = i != col;
                    bool is_start  = line_span.contains(
                        label.span->start());
                    bool is_end = line_span.contains(label.last_offset());

                    if (margin && c.is_line) {
                        margin_ptr = std::make_pair(margin, is_start);
                    } else if (!is_start && (!is_end || c.is_line)) {
                        if (!vbar && !is_parent) {
                            vbar = label;
                        }
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

                                if (is_start) {
                                    continue;
                                }
                            }

                            if (report_row_value.second) {
                                hbar = label;
                                if (!is_parent) {
                                    corner = std::make_pair(
                                        &label, is_start);
                                }
                            } else if (!is_start) {
                                if (!vbar && !is_parent) {
                                    vbar = label;
                                }
                            }
                        } else {
                            if (!vbar && !is_parent
                                && (is_start
                                    ^ (report_row_value.first
                                       < label_row))) {
                                vbar = label;
                            }
                        }
                    }
                }
            }


            if (auto margin_ptr_value = margin_ptr;
                margin_ptr_value.has_value() && c.is_line) {
                auto [margin, _is_start] = *margin_ptr_value;
                bool is_col = multi_label ? (*multi_label == margin->label)
                                          : false;
                bool is_limit = col + 1 == c.multi_labels.size();
                if (!is_col && !is_limit) {
                    hbar = hbar.value_or(margin->label);
                }
            }

            if (hbar.has_value()
                && !(*hbar != c.margin_label->label || !c.is_line)) {
                hbar = std::nullopt;
            }

            std::pair<ColRune, ColRune> ab;

            if (auto corner_value = corner; corner_value.has_value()) {
                auto [label, is_start] = *corner_value;
                ab                     = {
                    is_start ? ColRune(c.draw.ltop, label->color)
                                                 : ColRune(c.draw.lbot, label->color),
                    ColRune(c.draw.hbar, label->color),
                };
            } else if (
                hbar.has_value() && vbar.has_value()
                && !c.config.cross_gap) {
                ab = {
                    ColRune(c.draw.xbar, hbar->color),
                    ColRune(c.draw.hbar, hbar->color),
                };
            } else if (hbar.has_value()) {
                ab = {
                    ColRune(c.draw.hbar, hbar->color),
                    ColRune(c.draw.hbar, hbar->color),
                };
            } else if (vbar.has_value()) {
                ab = {
                    c.is_ellipsis ? ColRune(c.draw.vbar_gap, vbar->color)
                                  : ColRune(c.draw.vbar, vbar->color),
                    ColRune(' '),
                };
            } else if (auto margin_ptr_value = margin_ptr;
                       margin_ptr_value.has_value() && c.is_line) {
                auto [margin, is_start] = *margin_ptr_value;
                bool is_col = multi_label ? (*multi_label == margin->label)
                                          : false;
                bool is_limit = col == c.multi_labels.size();
                ab            = {
                    is_limit ? ColRune(c.draw.rarrow, margin->label.color)
                               : is_col
                                   ? (is_start
                                          ? ColRune(c.draw.ltop, margin->label.color)
                                          : ColRune(
                                   c.draw.lcross, margin->label.color))
                                   : ColRune(c.draw.hbar, margin->label.color),
                    !is_limit ? ColRune(c.draw.hbar, margin->label.color)
                              : ColRune(' '),
                };
            } else {
                ab = {
                    ColRune(' '),
                    ColRune(' '),
                };
            }
        }
    }
}


// Should we draw a vertical bar as part of a label arrow
// on this line?
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

    if (margin_label) {
        candidates.push_back(margin_label->label);
    }

    for (const auto& l : multi_labels) {
        candidates.push_back(l);
    }

    for (const auto& l : line_labels) {
        candidates.push_back(l.label);
    }

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

    if (candidates.empty()) {
        return std::nullopt;
    }

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

void whatever(MarginContext const& c, int row, int arrow_len) {
    // Margin alternate
    write_margin(
        c.clone().with_draw_labels(true).with_report_row({row, false}));

    // Lines alternate
    auto chars = c.line.chars.begin();
    for (int col = 0; col < arrow_len; ++col) {
        int width = (chars != c.line.chars.end())
                      ? c.config.char_width(*chars, col).second
                      : 1;

        Opt<LineLabel> underline = get_underline(c, col);
        if (row != 0) {
            underline.reset();
        }

        std::array<ColRune, 2> ct_array;
        if (Opt<LineLabel> vbar = get_vbar(
                col, row, c.line_labels, c.margin_label)) {
            std::array<QChar, 2> ct_inner;
            if (underline) {
                if (vbar->label.span->len() <= 1 || true) {
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
            c.w << ((i == 0) ? ct_array[0] : ct_array[1]);
        }

        if (chars != c.line.chars.end()) {
            ++chars;
        }
    }
    c.w << "\n";
}


void build_multi_labels(
    Vec<Label>&           multi_labels,
    Vec<LabelInfo> const& labels) {
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
}

void build_line_labels(
    Vec<LineLabel>&       line_labels,
    Config const&         config,
    Line const&           line,
    Vec<LabelInfo> const& labels,
    Opt<LineLabel> const& margin_label,
    Vec<Label>            multi_labels) {
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
}

int get_line_no_width(Vec<SourceGroup> const& groups, Cache& cache) {
    int line_no_width = 0;
    for (const auto& group : groups) {
        QString src_name = cache.display(group.src_id)
                               .value_or("<unknown>");

        try {
            auto src = cache.fetch(group.src_id);

            auto line_range = src->get_line_range(
                RangeCodeSpan(group.span));
            int width     = QString::number(line_range.last).size();
            line_no_width = std::max(line_no_width, width);
        } catch (const std::exception& e) {
            std::cerr << "Unable to fetch source " << src_name << ": "
                      << e.what() << std::endl;
        }
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
    auto chars = line.chars.begin();
    for (int col = 0; col < arrow_len; ++col) {
        int width = (chars != line.chars.end())
                      ? c.config.char_width(*chars, col).second
                      : 1;

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
                    (line_label.multi ? (
                         line_label.draw_msg ? c.draw.mbot : c.draw.rbot)
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

        if (width > 0) {
            c.w << ct_array[0];
        }
        for (int i = 1; i < width; ++i) {
            c.w << ct_array[1];
        }

        if (chars != line.chars.end()) {
            ++chars;
        }
    }
}
}; // namespace

Vec<SourceGroup> Report::get_source_groups(Cache* cache) {
    Vec<SourceGroup> groups;
    for (const auto& label : labels) {
        auto src_display            = cache->display(label.span->source());
        std::shared_ptr<Source> src = cache->fetch(label.span->source());
        if (!src) {
            continue;
        }

        assert(label.span->start() <= label.span->end());

        // "Label start is after its end");
        auto start_line = src->get_offset_line(label.span->start())
                              .value()
                              .idx;

        auto end_line = src->get_offset_line(std::max(
                                                 label.span->end() - 1,
                                                 label.span->start()))
                            .value()
                            .idx;

        LabelInfo label_info{
            .kind  = (start_line == end_line) ? LabelKind::Inline
                                              : LabelKind::Multiline,
            .label = label};

        auto group_it = std::find_if(
            groups.begin(), groups.end(), [&](const SourceGroup& group) {
                return group.src_id == label.span->source();
            });

        if (group_it != groups.end()) {
            group_it->span.first = std::min(
                group_it->span.first, label.span->start());
            group_it->span.last = std::max(
                group_it->span.last, label.span->end());
            group_it->labels.push_back(label_info);
        } else {
            groups.push_back(SourceGroup{
                .src_id = label.span->source(),
                .span   = slice(label.span->start(), label.span->end()),
                .labels = {label_info}});
        }
    }
    return groups;
}

void Report::write_for_stream(Cache& cache, QTextStream& stream) {
    ColStream w{stream};
    w.colored = true;
    Characters draw;
    switch (config.char_set) {
        case MessageCharSet::Unicode: draw = unicode(); break;
        case MessageCharSet::Ascii: draw = ascii(); break;
    }

    // --- Header ---


    ColStyle kind_color;
    QString  kindName;
    switch (kind) {
        case ReportKind::Error: {
            kind_color = config.error_color;
            kindName   = "Error";
            break;
        }
        case ReportKind::Warning: {
            kind_color = config.warning_color;
            kindName   = "Warning";
            break;
        }
        case ReportKind::Advice: {
            kind_color = config.advice_color;
            kindName   = "Advice";
            break;
        }
        case ReportKind::Custom: {
            kind_color = config.unimportant_color;
            kindName   = "Custom";
            break;
        }
    }

    if (code.has_value()) {
        w << ("[" + *code + "] ") + kind_color;
    }

    w << kindName + kind_color << ": " << msg.value() << "\n";

    auto groups = get_source_groups(&cache);

    // Line number maximum width
    int line_no_width = get_line_no_width(groups, cache);
    // --- Source sections ---
    for (int group_idx = 0; group_idx < groups.size(); ++group_idx) {
        SourceGroup const& group               = groups[group_idx];
        auto const& [src_id, Codespan, labels] = group;

        QString src_name = cache.display(src_id).value_or("<unknown>");

        std::shared_ptr<Source> src;
        try {
            src = cache.fetch(src_id);
        } catch (const std::exception& e) {
            std::cerr << "Unable to fetch source " << src_name << ": "
                      << e.what() << std::endl;
            continue;
        }

        w << QString(" ").repeated(line_no_width + 2) //
          << (group_idx == 0 ? ColRune(draw.ltop) : ColRune(draw.lcross))
                 + config.margin_color                //
          << ColRune(draw.hbar) + config.margin_color //
          << ColRune(draw.lbox) + config.margin_color //
          << src_name;                                // Source file name

        // File name & reference
        int location = (src_id == this->location.first)
                         ? this->location.second
                         : labels[0].label.span->start();

        auto offset_line = src->get_offset_line(location);

        // Error line and column number in the error message header
        if (offset_line) {
            w << ":" << offset_line->idx + 1 << ":"
              << offset_line->col + 1;
        } else {
            w << ":?:?";
        }

        w << ColRune(draw.rbox) + config.margin_color << "\n";

        if (!config.compact) {
            w << QString(" ").repeated(line_no_width + 2)
              << ColRune(draw.vbar) + config.margin_color << "\n";
        }


        // Generate a list of multi-line labels
        Vec<Label> multi_labels;
        build_multi_labels(multi_labels, labels);


        Slice<int> line_range = src->get_line_range(
            RangeCodeSpan(Codespan));

        bool is_ellipsis = false;
        for (int idx = line_range.first; idx <= line_range.last; ++idx) {
            auto line_opt = src->line(idx);
            if (!line_opt) {
                continue;
            }


            Line                     line         = line_opt.value();
            std::optional<LineLabel> margin_label = get_margin_label(
                line, multi_labels);

            Vec<LineLabel> line_labels;
            build_line_labels(
                line_labels,
                config,
                line,
                labels,
                margin_label,
                multi_labels);


            MarginContext base{
                .w             = w,
                .config        = config,
                .draw          = draw,
                .multi_labels  = multi_labels,
                .line_labels   = line_labels,
                .src           = src,
                .idx           = idx,
                .line_no_width = line_no_width,
                .line          = line,
            };

            bool do_skip = sort_line_labels(
                base, is_ellipsis, line_labels);

            if (do_skip) {
                continue;
            }

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

            arrow_len += config.compact ? 1 : 2;

            // Margin
            write_margin(base.clone()
                             .with_is_line(true)
                             .with_is_ellipsis(is_ellipsis)
                             .with_draw_labels(true));

            // Line
            if (!is_ellipsis) {
                int col = 0;
                for (QChar c : line.chars) {
                    Opt<CRw<Label>> highlight = get_highlight(
                        col,
                        multi_labels,
                        line,
                        line_labels,
                        margin_label);

                    ColStyle color = highlight ? highlight->get().color
                                               : config.unimportant_color;

                    auto [wc, width] = config.char_width(c, col);

                    if (c.isSpace()) {
                        for (int i = 0; i < width; ++i) {
                            w << ColRune(wc, color);
                        }
                    } else {
                        w << ColRune(wc, color);
                    }

                    col++;
                }
            }
            w << "\n";

            for (int row = 0; row < line_labels.size(); ++row) {
                const auto& line_label = line_labels[row];

                if (!config.compact) {
                    whatever(
                        base.with_is_ellipsis(is_ellipsis),
                        row,
                        arrow_len);
                }

                // Margin
                write_margin(base.clone()
                                 .with_is_ellipsis(is_ellipsis)
                                 .with_report_row({row, true})
                                 .with_draw_labels(true));

                write_lines(
                    base.clone(), line, arrow_len, line_label, row);

                if (line_label.draw_msg) {
                    w << " " << line_label.label.msg.value();
                }
                w << "\n";
            }
        }

        bool is_final_group = group_idx + 1 == groups.size();

        MarginContext base{
            .w             = w,
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
        };


        // Help
        if (help.has_value() && is_final_group) {
            if (!config.compact) {
                write_margin(base);
                w << "\n";
            }
            write_margin(base);
            w << "Help"
              << ": " << help.value() << "\n";
        }

        // Note
        if (note.has_value() && is_final_group) {
            if (!config.compact) {
                write_margin(base);
                w << "\n";
            }
            write_margin(base);

            w << "Note"
              << ": " << note.value() << "\n";
        }

        // Tail of report
        if (!config.compact) {
            if (is_final_group) {
                w << QString(draw.hbar).repeated(line_no_width + 2)
                  << draw.rbot << "\n";
            } else {
                w << QString(" ").repeated(line_no_width + 2) << draw.vbar
                  << "\n";
            }
        }
    }

    qDebug() << w.getBuffer();
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
        if (it != lines.begin()) {
            --it;
        }
        int         idx  = std::distance(lines.begin(), it);
        const Line& line = lines[idx];
        assert(offset >= line.offset);
        return OffsetLine{std::ref(line), idx, offset - line.offset};
    } else {
        return std::nullopt;
    }
}

Slice<int> Source::get_line_range(const CodeSpan& span) {
    std::optional<OffsetLine> start = get_offset_line(span.start());
    std::optional<OffsetLine> end   = get_offset_line(span.end());

    if (start && end) {
        return {start->idx, end->idx};
    } else {
        return {0, lines.size()};
    }
}

std::pair<QChar, int> Config::char_width(QChar c, int col) const {
    if (c == '\t') {
        // Find the column that the tab should end at
        int tab_end = (col / tab_width + 1) * tab_width;
        return std::make_pair(' ', tab_end - col);
    } else if (c.isSpace()) {
        return std::make_pair(' ', 1);
    } else {
        // Assuming you have a function called 'width()' to get the
        // character width.
        int char_width = 1;
        return std::make_pair(c, char_width);
    }
}
