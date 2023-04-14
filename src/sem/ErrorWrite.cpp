#include <sem/ErrorWrite.hpp>
#include <QChar>
#include <hstd/stdlib/Opt.hpp>

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

void Report::write_margin(MarginContext c) {
    QString line_no_margin;
    if (c.is_line && !c.is_ellipsis) {
        int line_no    = c.idx + 1;
        line_no_margin = QString(" ").repeated(
                             c.line_no_width
                             - QString::number(line_no).length())
                       + QString::number(line_no) + c.draw.vbar;
    } else {
        line_no_margin = QString(" ").repeated(c.line_no_width + 1)
                       + (c.is_ellipsis ? c.draw.vbar_gap
                                        : c.draw.vbar_break);
    }

    c.w << " " << line_no_margin << (config.compact ? "" : " ");


    if (c.draw_labels) {
        for (int col = 0;
             col < c.multi_labels.size() + (c.multi_labels.size() > 0);
             ++col) {
            std::optional<std::pair<const Label*, bool>>
                                        corner = std::nullopt;
            std::optional<const Label*> hbar   = std::nullopt;
            std::optional<const Label*> vbar   = std::nullopt;
            std::optional<std::pair<const LineLabel*, bool>>
                margin_ptr = std::nullopt;

            const Label* multi_label = (col < c.multi_labels.size())
                                         ? &multi_label[col]
                                         : nullptr;
            auto         line_span   = c.src->line(c.idx).value().span();

            for (int i = 0; i < std::min(col + 1, c.multi_labels.size());
                 ++i) {
                const auto& label  = multi_label[i];
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
                        vbar = vbar ? vbar
                                    : (!is_parent ? &label : nullptr);
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
                                vbar = (col == i) ? &margin->label
                                                  : nullptr;
                                if (is_start) {
                                    continue;
                                }
                            }

                            if (report_row_value.second) {
                                hbar = &label;
                                if (!is_parent) {
                                    corner = std::make_pair(
                                        &label, is_start);
                                }
                            } else if (!is_start) {
                                vbar = vbar
                                         ? vbar
                                         : (!is_parent ? &label : nullptr);
                            }
                        } else {
                            vbar = vbar ? vbar
                                        : (!is_parent
                                                   && (is_start
                                                       ^ (report_row_value
                                                              .first
                                                          < label_row))
                                               ? &label
                                               : nullptr);
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
                    hbar = hbar.value_or(&margin->label);
                }
            }

            if (hbar.has_value()) {
                hbar = **hbar != c.margin_label->label || !c.is_line
                         ? hbar
                         : std::nullopt;
            }

            std::pair<QChar, QChar> ab;

            if (auto corner_value = corner; corner_value.has_value()) {
                auto [label, is_start] = *corner_value;
                ab                     = {
                    is_start ? fg(c.draw.ltop, label->color)
                                                 : fg(c.draw.lbot, label->color),
                    fg(c.draw.hbar, label->color),
                };
            } else if (auto label = hbar.value();
                       vbar.has_value() && !config.cross_gap) {
                ab = {
                    fg(c.draw.xbar, label->color),
                    fg(c.draw.hbar, label->color)};
            } else if (hbar.has_value()) {
                auto label = hbar.value();
                ab         = {
                    fg(c.draw.hbar, label->color),
                    fg(c.draw.hbar, label->color),
                };
            } else if (vbar.has_value()) {
                auto label = vbar.value();
                ab         = {
                    c.is_ellipsis ? fg(c.draw.vbar_gap, label->color)
                                          : fg(c.draw.vbar, label->color),
                    fg(' ', Color::Default),
                };
            } else if (auto margin_ptr_value = margin_ptr;
                       margin_ptr_value.has_value() && c.is_line) {
                auto [margin, is_start] = *margin_ptr_value;
                bool is_col = multi_label ? (*multi_label == margin->label)
                                          : false;
                bool is_limit = col == c.multi_labels.size();
                ab            = {
                    is_limit ? fg(c.draw.rarrow, margin->label.color)
                               : is_col
                                   ? (is_start
                                          ? fg(c.draw.ltop, margin->label.color)
                                          : fg(c.draw.lcross, margin->label.color))
                                   : fg(c.draw.hbar, margin->label.color),
                    !is_limit ? fg(c.draw.hbar, margin->label.color)
                              : fg(' ', Color::Default),
                };
            } else {
                ab = {
                    fg(' ', Color::Default),
                    fg(' ', Color::Default),
                };
            }
        }
    }
}

namespace {
struct WriteForStreamCtx {};

// Should we draw a vertical bar as part of a label arrow
// on this line?
auto get_vbar(
    int                           col,
    int                           row,
    Vec<Report::LineLabel> const& line_labels,
    Opt<Report::LineLabel> const& margin_label)
    -> std::optional<Report::LineLabel> {
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


void write_lines(
    Line const&                   line,
    int                           arrow_len,
    Config const&                 config,
    Report::LineLabel const&      line_label,
    Characters const&             draw,
    Opt<Report::LineLabel> const& margin_label,
    int                           row,
    Vec<Report::LineLabel> const& line_labels,
    QTextStream&                  w) {
    // Lines
    auto chars = line.chars.begin();
    for (int col = 0; col < arrow_len; ++col) {
        int width = (chars != line.chars.end())
                      ? config.char_width(*chars, col).second
                      : 1;

        bool is_hbar = (((col > line_label.col) ^ line_label.multi)
                        || (line_label.label.msg && line_label.draw_msg
                            && col > line_label.col))
                    && line_label.label.msg;
        std::array<QChar, 2> ct_array;
        if (col == line_label.col && line_label.label.msg
            && (!margin_label.has_value()
                || line_label.label != margin_label->label)) {
            ct_array = {
                fg((line_label.multi
                        ? (line_label.draw_msg ? draw.mbot : draw.rbot)
                        : draw.lbot),
                   line_label.label.color),
                fg(draw.hbar, line_label.label.color),
            };
        } else if (std::optional<Report::LineLabel> vbar_ll = std::nullopt;
                   (vbar_ll = get_vbar(
                        col, row, line_labels, margin_label))
                   && (col != line_label.col || line_label.label.msg)) {
            if (!config.cross_gap && is_hbar) {
                ct_array = {
                    fg(draw.xbar, line_label.label.color),
                    fg(' ', line_label.label.color),
                };
            } else if (is_hbar) {
                ct_array = {
                    fg(draw.hbar, line_label.label.color),
                    fg(draw.hbar, line_label.label.color),
                };
            } else {
                ct_array = {
                    fg((vbar_ll->multi && row == 0 && config.compact
                            ? draw.uarrow
                            : draw.vbar),
                       vbar_ll->label.color),
                    fg(' ', line_label.label.color),
                };
            }
        } else if (is_hbar) {
            ct_array = {
                fg(draw.hbar, line_label.label.color),
                fg(draw.hbar, line_label.label.color),
            };
        } else {
            ct_array = {
                fg(' ', std::nullopt),
                fg(' ', std::nullopt),
            };
        }

        if (width > 0) {
            w << ct_array[0];
        }
        for (int i = 1; i < width; ++i) {
            w << ct_array[1];
        }

        if (chars != line.chars.end()) {
            ++chars;
        }
    }
}
}; // namespace

void Report::write_for_stream(Cache& cache, QTextStream& w) {
    qDebug() << "Write for stream requested";
    Characters draw;
    switch (config.char_set) {
        case MessageCharSet::Unicode: draw = unicode(); break;
        case MessageCharSet::Ascii: draw = ascii(); break;
    }

    // --- Header ---
    QString id;
    if (code.has_value()) {
        id = "[" + *code + "] ";
    }
    id += ":";

    std::optional<Color> kind_color;
    switch (kind) {
        case ReportKind::Error: kind_color = config.error_color(); break;
        case ReportKind::Warning:
            kind_color = config.warning_color();
            break;
        case ReportKind::Advice: kind_color = config.advice_color(); break;
        case ReportKind::Custom:
            kind_color = config.unimportant_color();
            break;
    }

    //        fmt::print(w, "{} {}", id.fg(kind_color, s),
    //        Show(msg.as_ref()));

    auto groups = get_source_groups(&cache);

    // Line number maximum width
    int line_no_width = 0;
    for (const auto& group : groups) {
        QString src_name = cache.display(group.src_id)
                               .value_or("<unknown>");

        try {
            auto src = cache.fetch(group.src_id);

            auto line_range = src->get_line_range(
                RangeCodeSpan(group.span));
            int width = 0;
            for (uint32_t x = 1, y = 1; line_range.last / y != 0;
                 x *= 10, y        = std::pow(10, x)) {
                ++width;
            }
            line_no_width = std::max(line_no_width, width);
        } catch (const std::exception& e) {
            std::cerr << "Unable to fetch source " << src_name << ": "
                      << e.what() << std::endl;
        }
    }

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

        Slice<int> line_range = src->get_line_range(
            RangeCodeSpan(Codespan));

        // File name & reference
        int location = (src_id == this->location.first)
                         ? this->location.second
                         : labels[0].label.span->start();

        auto offset_line = src->get_offset_line(location);
        std::pair<QString, QString> line_col;
        if (offset_line) {
            line_col = {
                QString::number(offset_line->idx + 1),
                QString::number(offset_line->col + 1)};
        } else {
            line_col = {"?", "?"};
        }

        if (!config.compact) {}


        // Generate a list of multi-line labels
        Vec<const Label*> multi_labels;
        for (LabelInfo const& label_info : labels) {
            if (label_info.kind == LabelKind::Multiline) {
                multi_labels.push_back(&label_info.label);
            }
        }


        // Sort multiline labels by length
        std::sort(
            multi_labels.begin(),
            multi_labels.end(),
            [](Label const* a, Label const* b) {
                return (a->span->len()) > (b->span->len());
            });


        bool is_ellipsis = false;
        for (int idx = line_range.first; idx <= line_range.last; ++idx) {
            auto line_opt = src->line(idx);
            if (!line_opt) {
                continue;
            }

            Line line = line_opt.value();

            std::optional<LineLabel> margin_label;
            int min_key = std::numeric_limits<int>::max();
            for (int i = 0; i < multi_labels.size(); ++i) {
                const Label* label = multi_labels[i];
                bool is_start = line.span().contains(label->span->start());
                bool is_end   = line.span().contains(label->last_offset());

                if (is_start || is_end) {
                    LineLabel ll{
                        .col = (is_start ? label->span->start()
                                         : label->last_offset())
                             - line.offset,
                        .label    = *label,
                        .multi    = true,
                        .draw_msg = is_end,
                    };


                    int key = (ll.col << 1) | (!label->span->start());
                    if (key < min_key) {
                        min_key      = key;
                        margin_label = ll;
                    }
                }
            }

            Vec<LineLabel> line_labels;
            for (const Label* label : multi_labels) {
                bool is_start = line.span().contains(label->span->start());
                bool is_end   = line.span().contains(label->last_offset());
                bool different_from_margin_label
                    = (!margin_label.has_value()
                       || reinterpret_cast<const void*>(label)
                              != reinterpret_cast<const void*>(
                                  &margin_label->label));

                if ((is_start && different_from_margin_label) || is_end) {
                    LineLabel ll{
                        .col = (is_start ? label->span->start()
                                         : label->last_offset())
                             - line.offset,
                        .label    = *label,
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
                                       position,
                                       label_info.label.span->start())
                                 - line.offset,
                            .label    = label_info.label,
                            .multi    = false,
                            .draw_msg = true,
                        };


                        line_labels.push_back(ll);
                    }
                }
            }

            // Skip this line if we don't have labels for it
            if (line_labels.size() == 0 && !margin_label.has_value()) {
                bool within_label = std::any_of(
                    multi_labels.begin(),
                    multi_labels.end(),
                    [&](const Label* label) {
                        return label->span->contains(line.span().first);
                    });
                if (!is_ellipsis && within_label) {
                    is_ellipsis = true;
                } else {
                    if (!config.compact && !is_ellipsis) {
                        write_margin({
                            .line_no_width = line_no_width,
                            .w             = w,
                            .idx           = idx,
                            .is_ellipsis   = is_ellipsis,
                            .src           = src,
                            .line_labels   = line_labels,
                            .multi_labels  = multi_labels,
                        });
                        w << "\n";
                    }
                    is_ellipsis = true;
                    continue;
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
                               a.label.order,
                               a.col,
                               !a.label.span->start())
                         < std::make_tuple(
                               b.label.order,
                               b.col,
                               !b.label.span->start());
                });

            // Determine label bounds so we know where to put error
            // messages
            int arrow_end_space = config.compact ? 1 : 2;
            int arrow_len       = std::accumulate(
                                line_labels.begin(),
                                line_labels.end(),
                                0,
                                [&](int l, const auto& ll) {
                                    if (ll.multi) {
                                        return line.get_len();
                                    } else {
                                        return std::max(
                                            l,
                                            ll.label.span->end()
                                                - line.offset);
                                    }
                                })
                          + arrow_end_space;


            auto get_highlight = [&](int col) {
                Vec<const Label*> candidates;

                // TODO fixme
                //                    for (const auto& ll :
                //                    margin_label) {
                //                        candidates.push_back(&ll.label);
                //                    }

                for (const auto& l : multi_labels) {
                    candidates.push_back(l);
                }

                for (const auto& l : line_labels) {
                    candidates.push_back(&l.label);
                }

                auto it = std::min_element(
                    candidates.begin(),
                    candidates.end(),
                    [&](const auto& a, const auto& b) {
                        return std::make_tuple(
                                   -a->priority, a->span->len())
                             < std::make_tuple(
                                   -b->priority, b->span->len());
                    });

                return (it != candidates.end()
                        && (*it)->span->contains(line.offset + col))
                         ? *it
                         : nullptr;
            };

            auto get_underline = [&](int col) -> Opt<LineLabel> {
                Vec<LineLabel>::iterator it = std::min_element(
                    line_labels.begin(),
                    line_labels.end(),
                    [&](const auto& a, const auto& b) {
                        return std::make_tuple(
                                   -a.label.priority, a.label.span->len())
                             < std::make_tuple(
                                   -b.label.priority, b.label.span->len());
                    });

                if (it != line_labels.end() && config.underlines
                    && !it->multi
                    && it->label.span->contains(line.offset + col)) {
                    return *it;
                } else {
                    return std::nullopt;
                }
            };

            // Margin
            write_margin({
                .line_no_width = line_no_width,
                .w             = w,
                .idx           = idx,
                .is_line       = true,
                .is_ellipsis   = is_ellipsis,
                .draw_labels   = true,
                .src           = src,
                .line_labels   = line_labels,
                .multi_labels  = multi_labels,
            });

            // Line
            if (!is_ellipsis) {
                int col = 0;
                for (QChar c : line.chars) {
                    auto highlight   = get_highlight(col);
                    auto color       = highlight ? highlight->color
                                                 : config.unimportant_color();
                    auto [wc, width] = config.char_width(c, col);

                    if (c.isSpace()) {
                        for (int i = 0; i < width; ++i) {
                            w << fg(wc, color);
                        }
                    } else {
                        w << fg(wc, color);
                    }

                    col++;
                }
            }
            w << "\n";

            for (int row = 0; row < line_labels.size(); ++row) {
                const auto& line_label = line_labels[row];

                if (!config.compact) {
                    // Margin alternate
                    write_margin({
                        .line_no_width = line_no_width,
                        .w             = w,
                        .idx           = idx,
                        .is_ellipsis   = is_ellipsis,
                        .draw_labels   = true,
                        .src           = src,
                        .line_labels   = line_labels,
                        .multi_labels  = multi_labels,
                        .report_row    = std::pair{row, false},
                    });

                    // Lines alternate
                    auto chars = line.chars.begin();
                    for (int col = 0; col < arrow_len; ++col) {
                        int width = (chars != line.chars.end())
                                      ? config.char_width(*chars, col)
                                            .second
                                      : 1;

                        // let underline =
                        // get_underline(col).filter(|_| row == 0); I
                        // think it translates like this, but fuck this
                        // Rust garbage
                        Opt<LineLabel> underline = std::nullopt;
                        if (row == 0) {
                            if (Opt<LineLabel> tmp = get_underline(col)) {
                                underline = tmp;
                            }
                        }

                        std::array<QChar, 2> ct_array;
                        if (auto vbar_ll = get_vbar(
                                col, row, line_labels, margin_label)) {
                            std::array<QChar, 2> ct_inner;
                            if (underline) {
                                if (vbar_ll->label.span->len() <= 1
                                    || true) {
                                    ct_inner = {
                                        draw.underbar, draw.underline};
                                } else if (
                                    line.offset + col
                                    == vbar_ll->label.span->start()) {
                                    ct_inner = {draw.ltop, draw.underbar};
                                } else if (
                                    line.offset + col
                                    == vbar_ll->label.last_offset()) {
                                    ct_inner = {draw.rtop, draw.underbar};
                                } else {
                                    ct_inner = {
                                        draw.underbar, draw.underline};
                                }
                            } else if (
                                vbar_ll->multi && row == 0
                                && config.multiline_arrows) {
                                ct_inner = {draw.uarrow, ' '};
                            } else {
                                ct_inner = {draw.vbar, ' '};
                            }
                            ct_array = {
                                fg(ct_inner[0], vbar_ll->label.color),
                                fg(ct_inner[1], vbar_ll->label.color)};
                        } else if (underline) {
                            ct_array = {
                                fg(draw.underline, underline->label.color),
                                fg(draw.underline,
                                   underline->label.color)};
                        } else {
                            ct_array = {
                                fg(' ', std::nullopt),
                                fg(' ', std::nullopt)};
                        }

                        for (int i = 0; i < width; ++i) {
                            w << ((i == 0) ? ct_array[0] : ct_array[1]);
                        }

                        if (chars != line.chars.end()) {
                            ++chars;
                        }
                    }
                    w << "\n";
                }

                // Margin
                write_margin({
                    .line_no_width = line_no_width,
                    .w             = w,
                    .idx           = idx,
                    .is_ellipsis   = is_ellipsis,
                    .draw_labels   = true,
                    .src           = src,
                    .line_labels   = line_labels,
                    .multi_labels  = multi_labels,
                    .report_row    = std::pair{row, true},
                });

                write_lines(
                    line,
                    arrow_len,
                    config,
                    line_label,
                    draw,
                    margin_label,
                    row,
                    line_labels,
                    w);

                if (line_label.draw_msg) {
                    w << " " << line_label.label.msg.value();
                }
                w << "\n";
            }
        }

        bool is_final_group = group_idx + 1 == groups.size();

        // Help
        if (help.has_value() && is_final_group) {
            if (!config.compact) {
                write_margin({
                    .line_no_width = line_no_width,
                    .w             = w,
                    .idx           = 0,
                    .is_line       = false,
                    .is_ellipsis   = false,
                    .draw_labels   = true,
                    .src           = src,
                    .multi_labels  = multi_labels,
                    .report_row    = std::pair{0, false},
                });
                w << "\n";
            }
            write_margin({
                .line_no_width = line_no_width,
                .w             = w,
                .idx           = 0,
                .is_line       = false,
                .is_ellipsis   = false,
                .draw_labels   = true,
                .src           = src,
                .multi_labels  = multi_labels,
                .report_row    = std::pair{0, false},
            });
            w << "Help"
              << ": " << help.value() << "\n";
        }

        // Note
        if (note.has_value() && is_final_group) {
            if (!config.compact) {
                write_margin({
                    .line_no_width = line_no_width,
                    .w             = w,
                    .idx           = 0,
                    .is_line       = false,
                    .is_ellipsis   = false,
                    .draw_labels   = true,
                    .src           = src,
                    .multi_labels  = multi_labels,
                    .report_row    = std::pair{0, false},
                });
                w << "\n";
            }
            write_margin({
                .line_no_width = line_no_width,
                .w             = w,
                .idx           = 0,
                .is_line       = false,
                .is_ellipsis   = false,
                .draw_labels   = true,
                .src           = src,
                .multi_labels  = multi_labels,
                .report_row    = std::pair{0, false},
            });

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
}
