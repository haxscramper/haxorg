#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Set.hpp>
#include "error_write.hpp"
#include "hstd/stdlib/Enumerate.hpp"
#include <hstd/ext/logger.hpp>
#include <boost/preprocessor/seq.hpp>

using namespace hstd::ext;
using namespace hstd;


Characters Config::unicode() {
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

Characters Config::ascii() {
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
    ColStream&    stream;
    Config const* config;

    bool dbg_report() const { return config->debug_report_info; }

    void debug(std::string const& message) {
        if (config->debug_writes) { stream << message; }
    }

    template <typename T>
    void write(
        CR<T>       value,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        HSLOG_DEBUG(
            "write: {}:{} {}",
            function,
            line,
            hstd::escape_literal(hstd::fmt1(value)));

        if (config->debug_writes) {
            stream << stream.green() << value << stream.end()
                   << stream.blue() << fmt("@{}", line) << stream.end();
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
    _field(int, line_number_width, 0);
    _field(bool, draw_labels, false);
    _field(int, arrow_len, 0);
    Line const&                         line;
    std::optional<std::pair<int, bool>> report_row = std::nullopt;
    Vec<LineLabel> const&               line_labels;
    std::optional<LineLabel> const&     margin_label;
    std::shared_ptr<Source>             src;
    Vec<Label> const&                   multi_labels;
    Config const&                       config;

    MarginContext& with_report_row(std::pair<int, bool> const& value) {
        report_row = value;
        return *this;
    }


    Characters const& draw() const { return config.char_set; }

    finally_std scope(
        Str const& function    = Str{__builtin_FUNCTION()},
        bool       force_scope = false,
        int        line        = __builtin_LINE()) const {
        if (config.debug_scopes || force_scope) {
            w.stream << fmt("«{}:{}«", line, function);
            return finally_std{[&]() { w.stream << "»»"; }};
        } else {
            return finally_std::nop();
        }
    }
};

int get_arrow_len(MarginContext const& base) {
    // Determine label bounds so we know where to put error
    // messages
    HSLOG_DEBUG("get arrow len");
    HSLOG_DEPTH_SCOPE_ANON();
    int arrow_len = 0;
    for (const auto& ll : base.line_labels) {
        if (ll.multi) {
            arrow_len = base.line.get_len();
        } else {
            arrow_len = std::max(
                arrow_len, ll.label.span.end() - base.line.offset);
        }
    }

    arrow_len += base.config.compact ? 1 : 2; // add arrow end space
    return arrow_len;
}

std::optional<LineLabel> get_margin_label(
    Line const&       line,
    Vec<Label> const& multi_labels) {
    std::optional<LineLabel> margin_label;
    int                      min_key = std::numeric_limits<int>::max();
    HSLOG_DEBUG("get margin label");
    HSLOG_DEPTH_SCOPE_ANON();
    for (int i = 0; i < multi_labels.size(); ++i) {
        HSLOG_DEBUG("[{}]", i);
        HSLOG_DEPTH_SCOPE_ANON();
        Label const& label    = multi_labels[i];
        bool         is_start = line.span().contains(label.span.start());
        bool         is_end   = line.span().contains(label.span.end());
        HSLOG_DEBUG_FMT_LINE(is_start, is_end, line.span(), label.span);

        if (is_start || is_end) {
            LineLabel ll{
                .col = (is_start ? label.span.start() : label.span.end())
                     - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };


            int key = (ll.col << 1) | (!label.span.start());
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
                return label.span.contains(c.line.span().first);
            });
        if (!is_ellipsis && within_label) {
            is_ellipsis = true;
        } else {
            if (!c.config.compact && !is_ellipsis) {
                write_margin(c.clone().with_is_ellipsis(is_ellipsis));
                c.w.write("\n");
            }
            is_ellipsis = true;
            return false;
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
                       a.label.order, a.col, !a.label.span.start())
                 < std::make_tuple(
                       b.label.order, b.col, !b.label.span.start());
        });

    return true;
}

/// \brief Information for rendering the left-most part of the report.
struct MarginElements {
    Opt<Label>                 hbar       = std::nullopt;
    Opt<Label>                 vbar       = std::nullopt;
    Opt<Pair<Label, bool>>     corner     = std::nullopt;
    Opt<Pair<LineLabel, bool>> margin_ptr = std::nullopt;
    DESC_FIELDS(MarginElements, (hbar, vbar, corner, margin_ptr));
};

/// \brief
MarginElements fill_margin_elements(MarginContext const& c, int col) {
    HSLOG_DEBUG("fill_margin_elements");
    HSLOG_DEPTH_SCOPE_ANON();

    MarginElements result;

    Slice<int> line_span = c.src->line(c.idx).value().span();
    for (int i = 0; i < std::min(col + 1, c.multi_labels.size()); ++i) {
        HSLOG_DEPTH_SCOPE_ANON();
        auto label = c.multi_labels.at(i);
        HSLOG_DEBUG("{} label {}", i, label.span);
        Opt<LineLabel> margin;
        if (c.margin_label && label == c.margin_label->label) {
            margin = c.margin_label;
            hstd::log::log_described_record(margin.value()).end();
        }

        HSLOG_DEBUG_FMT_STACK(line_span);

        HSLOG_DEBUG_FMT_STACK(
            label.span.start(),
            line_span.last,
            label.span.start() <= line_span.last,
            line_span.first,
            label.span.end(),
            line_span.first < label.span.end());

        if (label.span.start() <= line_span.last
            && line_span.first <= label.span.end()) {
            bool is_parent = i != col;
            bool is_start  = line_span.contains(label.span.start());
            bool is_end    = line_span.contains(label.span.end());
            HSLOG_DEBUG_FMT_LINE(is_parent, is_start, is_end);

            if (margin && c.is_line) {
                HSLOG_DEBUG("-- ");
                result.margin_ptr = std::make_pair(
                    margin.value(), is_start);
            } else if (!is_start && (!is_end || c.is_line)) {
                HSLOG_DEBUG("-- ");
                if (!result.vbar && !is_parent) {
                    HSLOG_DEBUG("-- ");
                    result.vbar = label;
                }
            } else if (c.report_row.has_value()) {
                HSLOG_DEBUG("-- ");
                auto report_row_value = c.report_row.value();
                int  label_row        = 0;
                for (int r = 0; r < c.line_labels.size(); ++r) {
                    if (label == c.line_labels[r].label) {
                        HSLOG_DEBUG("-- ");
                        label_row = r;
                        break;
                    }
                }

                if (report_row_value.first == label_row) {
                    HSLOG_DEBUG("-- ");
                    if (margin) {
                        if (col == i) {
                            HSLOG_DEBUG("-- ");
                            result.vbar = margin->label;
                        } else {
                            HSLOG_DEBUG("-- ");
                            result.vbar = std::nullopt;
                        }

                        if (is_start) {
                            HSLOG_DEBUG("-- ");
                            continue;
                        }
                    }

                    if (report_row_value.second) {
                        HSLOG_DEBUG("-- ");
                        result.hbar = label;
                        if (!is_parent) {
                            HSLOG_DEBUG("-- ");
                            result.corner = std::make_pair(
                                label, is_start);
                        }
                    } else if (!is_start) {
                        HSLOG_DEBUG("-- ");
                        if (!result.vbar && !is_parent) {
                            HSLOG_DEBUG("-- ");
                            result.vbar = label;
                        }
                    }
                } else {
                    HSLOG_DEBUG("-- ");
                    if (!result.vbar && !is_parent
                        && (is_start
                            ^ (report_row_value.first < label_row))) {
                        HSLOG_DEBUG("-- ");
                        result.vbar = label;
                    }
                }
            }
        }
    }

    return result;
}

Pair<ColRune, ColRune> get_corner_elements(
    MarginContext const&  c,
    int                   col,
    MarginElements const& margin,
    CR<Opt<CRw<Label>>>   multi_label) {
    ColRune base;
    ColRune extended;

    if (margin.corner) {
        auto [label, is_start] = *margin.corner;
        if (is_start) {
            base = ColRune(c.draw().ltop, label.color)
                       .dbg_origin(c.config.debug_writes);
        } else {
            base = ColRune(c.draw().lbot, label.color)
                       .dbg_origin(c.config.debug_writes);
        }

        extended = ColRune(c.draw().hbar, label.color)
                       .dbg_origin(c.config.debug_writes);
    } else if (margin.hbar && margin.vbar && !c.config.cross_gap) {
        base = ColRune(c.draw().xbar, margin.hbar->color)
                   .dbg_origin(c.config.debug_writes);
        extended = ColRune(c.draw().hbar, margin.hbar->color)
                       .dbg_origin(c.config.debug_writes);
    } else if (margin.hbar) {
        base = ColRune(c.draw().hbar, margin.hbar->color)
                   .dbg_origin(c.config.debug_writes);
        extended = ColRune(c.draw().hbar, margin.hbar->color)
                       .dbg_origin(c.config.debug_writes);
    } else if (margin.vbar) {
        if (c.is_ellipsis) {
            base = ColRune(c.draw().vbar_gap, margin.vbar->color)
                       .dbg_origin(c.config.debug_writes);
        } else {
            base = ColRune(c.draw().vbar, margin.vbar->color)
                       .dbg_origin(c.config.debug_writes);
        }
        extended = ColRune(' ').dbg_origin(c.config.debug_writes);
    } else if (margin.margin_ptr && c.is_line) {
        auto [label, is_start] = *margin.margin_ptr;
        bool is_col   = multi_label && (multi_label->get() == label.label);
        bool is_limit = col == c.multi_labels.size();
        if (is_limit) {
            base = ColRune(c.draw().rarrow, label.label.color)
                       .dbg_origin(c.config.debug_writes);
        } else if (is_col) {
            if (is_start) {
                base = ColRune(c.draw().ltop, label.label.color)
                           .dbg_origin(c.config.debug_writes);
            } else {
                base = ColRune(c.draw().lcross, label.label.color)
                           .dbg_origin(c.config.debug_writes);
            }
        } else {
            base = ColRune(c.draw().hbar, label.label.color)
                       .dbg_origin(c.config.debug_writes);
        }

        if (is_limit) {
            extended = ColRune(' ').dbg_origin(c.config.debug_writes);
        } else {
            extended = ColRune(c.draw().hbar, label.label.color)
                           .dbg_origin(c.config.debug_writes);
        }
    } else {
        base     = ColRune(' ').dbg_origin(c.config.debug_writes);
        extended = ColRune(' ').dbg_origin(c.config.debug_writes);
    }

    return {base, extended};
}

/// \brief Write end arrows, line number, vertical part of the image or an
/// empty space to help with the alignment of the rest of the label.
void write_margin(MarginContext const& c) {
    auto __scope = c.scope("margin");
    HSLOG_DEBUG("write_margin idx:{}", c.idx);
    HSLOG_DEPTH_SCOPE_ANON();
    Str line_number;

    // Get the line number text for the report.
    if (c.is_line && !c.is_ellipsis) {
        int line_no = c.idx + 1;
        line_number = Str(" ").repeated(
                          c.line_number_width - fmt1(line_no).length())
                    + Str(fmt1(line_no)) + Str(" ") + Str(c.draw().vbar);
    } else {
        line_number = Str(" ").repeated(c.line_number_width + 1);
        line_number += (c.is_ellipsis ? c.draw().vbar_gap : c.draw().vbar);
    }

    c.w.write(" ");
    c.w.write(ColText(c.config.margin_color, line_number));
    c.w.write(c.config.compact ? "" : " ");


    // Multi-line margins -- for labels that have spans over multiple lines
    // at once.
    if (c.draw_labels) {
        for (int col = 0; col < c.multi_labels.size()
                                    + (0 < c.multi_labels.size() ? 1 : 0);
             ++col) {
            Opt<CRw<Label>> multi_label = c.multi_labels.get(col);
            auto            margin      = fill_margin_elements(c, col);
            hstd::log::log_described_record(margin).as_debug().end();

            if (margin.margin_ptr && c.is_line) {
                bool is_col = multi_label
                           && (*multi_label
                               == margin.margin_ptr->first.label);

                bool is_limit = col + 1 == c.multi_labels.size();
                if (!is_col && !is_limit) {
                    margin.hbar = margin.hbar.value_or(
                        margin.margin_ptr->first.label);
                }
            }

            if (margin.hbar
                && !(
                    (*margin.hbar != c.margin_label->label)
                    || !c.is_line)) {
                margin.hbar = std::nullopt;
            }

            auto [base, extended] = get_corner_elements(
                c, col, margin, multi_label);

            c.w.write(base);
            if (!c.config.compact) { c.w.write(extended); }
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
    for (const auto& [line_label_row, ll] : enumerate(line_labels)) {
        // Ignore empty labels
        if (!ll.label.msg.has_value()) { continue; }
        // Ignore multiline labels when drawing bars under the lines
        if (margin_label.has_value()
            && ll.label.id == margin_label->label.id) {
            continue;
        }

        if (ll.col == col && row <= line_label_row) { return ll; }
    }
    return std::nullopt;
};


Opt<CRw<Label>> get_highlight(
    int                      col,
    MarginContext const&     base,
    std::optional<LineLabel> margin_label) {
    Vec<CRw<Label>> candidates;

    if (margin_label) { candidates.push_back(margin_label->label); }
    for (const auto& l : base.multi_labels) { candidates.push_back(l); }
    for (const auto& l : base.line_labels) {
        candidates.push_back(l.label);
    }

    auto it = std::min_element(
        candidates.begin(),
        candidates.end(),
        [&](const auto& a, const auto& b) {
            return std::make_tuple(-a.get().priority, a.get().span.len())
                 < std::make_tuple(-b.get().priority, b.get().span.len());
        });


    if (it != candidates.end()
        && it->get().span.contains(base.line.offset + col)) {
        return *it;
    } else {
        return std::nullopt;
    }
};


auto get_underline(MarginContext const& c, int col) -> Opt<LineLabel> {
    Vec<CRw<LineLabel>> candidates;
    for (const auto& it : c.line_labels) {
        if (c.config.underlines && !it.multi
            && it.label.span.contains(c.line.offset + col)) {
            candidates.push_back(it);
        }
    }

    if (candidates.empty()) { return std::nullopt; }

    return *std::min_element(
        candidates.begin(),
        candidates.end(),
        [&](CRw<LineLabel> a, CRw<LineLabel> b) {
            return std::make_tuple(
                       -a.get().label.priority, a.get().label.span.len())
                 < std::make_tuple(
                       -b.get().label.priority, b.get().label.span.len());
        });
};

void write_line_label_arrows(
    MarginContext const& c,
    int                  row,
    int                  arrow_len) {
    // Lines alternate
    HSLOG_DEBUG_FMT_STACK(row, arrow_len);
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {

        Opt<LineLabel> underline = get_underline(c, col);
        if (row != 0) { underline.reset(); }

        HSLOG_DEBUG_FMT_STACK(col, underline);

        ColRune ch;
        ColRune tail;
        // original rust code is a barely legible nested if-else
        // expression, and even after several days of looking at the
        // `write.rs` file I don't have any confidence in my understanding
        // of what this thing is supposed to be in the end. It draws the
        // arrows, yes, but if I actually use the `tail` code, like it is
        // written in the rust version, the final result looks horrible.
        if (Opt<LineLabel> vbar = get_vbar(
                col, row, c.line_labels, c.margin_label)) {
            if (underline) {
                // the original comment from the `write.rs` regarding the
                // `|| true` on the first branch. No idea what "feature"
                // this refers to, but maybe in the future I will figure it
                // out.

                // clang-format off
                // // TODO: Is this good?
                // // The `true` is used here because it's temporarily disabling a
                // // feature that might be reenabled later.
                // #[allow(clippy::overly_complex_bool_expr)]
                // clang-format on

                if (vbar->label.span.len() == 0) {
                    ch   = c.draw().underbar;
                    tail = c.draw().underline;
                } else if (
                    c.line.offset + col == vbar->label.span.start()) {
                    ch   = c.draw().ltop;
                    tail = c.draw().underbar;
                } else if (c.line.offset + col == vbar->label.span.end()) {
                    ch   = c.draw().rtop;
                    tail = c.draw().underbar;
                } else {
                    ch   = c.draw().underbar;
                    tail = c.draw().underline;
                }
            } else if (
                vbar->multi && row == 0 && c.config.multiline_arrows) {
                ch   = c.draw().uarrow;
                tail = ColRune(' ');
            } else {
                ch   = c.draw().vbar;
                tail = ColRune(' ');
            }
        } else if (underline) {
            ch   = ColRune(c.draw().underline, underline->label.color);
            tail = ColRune(c.draw().underline, underline->label.color);
        } else {
            ch   = ColRune(' ');
            tail = ColRune(' ');
        }

        if (true) {
            c.w.write(ch);
        } else {
            if (col == 0) {
                c.w.write(ch);
            } else {
                c.w.write(tail);
            }
        }

        if (chars != c.line_text.end()) { ++chars; }
    }
}


/// \brief Collect line labels associated with the input line. Include both
/// labels that are contained in the range of the single line, and ones
/// that span multiple lines.
Vec<LineLabel> build_line_labels(
    Config const&           config,
    Line const&             line,
    Vec<LabelInfo> const&   labels,
    Opt<LineLabel> const&   margin_label,
    Vec<Label> const&       multi_labels,
    std::shared_ptr<Source> src) {
    HSLOG_DEBUG("Build line labels");
    HSLOG_DEPTH_SCOPE_ANON();
    HSLOG_DEBUG_FMT_LINE(
        labels.size(), margin_label.has_value(), multi_labels.size());
    HSLOG_DEBUG_FMT_LINE(line);

    Vec<LineLabel> line_labels;
    for (CR<Label> label : multi_labels) {
        HSLOG_DEBUG("multi_label");
        HSLOG_DEPTH_SCOPE_ANON();
        bool is_start = line.span().contains(label.span.start());
        bool is_end   = line.span().contains(label.span.end());
        bool different_from_margin_label
            = (!margin_label.has_value() || label != margin_label->label);

        if (is_start && different_from_margin_label) {
            LineLabel ll{
                .col      = label.span.start() - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };
            line_labels.push_back(ll);
        } else if (is_end) {
            LineLabel ll{
                .col      = label.span.end() - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };
            line_labels.push_back(ll);
        }
    }

    for (const LabelInfo& label_info : labels) {
        HSLOG_DEBUG("label_info");
        HSLOG_DEPTH_SCOPE_ANON();
        if (label_info.label.msg) {
            HSLOG_DEBUG(
                "label.info.label.msg = {}",
                hstd::escape_literal(
                    label_info.label.msg.value().toString(false)));
        }

        hstd::log::log_described_record(label_info.label).end();
        hstd::log::log_described_record(line).end();
        HSLOG_DEBUG_FMT_STACK(
            line.span().first,
            label_info.label.span.start(),
            line.span().first <= label_info.label.span.start(),
            label_info.label.span.end(),
            line.span().last,
            label_info.label.span.end() <= line.span().last);

        // if the line fully contains an inline label
        if (line.span().first <= label_info.label.span.start()
            && (label_info.label.span.end() <= line.span().last
                // or if the inline label starts on the line and goes
                // out of the source range (e.g. error with "unexpected
                // end of file" might require this).
                || src->len <= label_info.label.span.end())) {
            if (label_info.kind == LabelKind::Inline) {
                int position = 0;
                switch (config.label_attach) {
                    case LabelAttach::Start:
                        position = label_info.label.span.start();
                        break;
                    case LabelAttach::Middle:
                        position = (label_info.label.span.start()
                                    + label_info.label.span.end())
                                 / 2;
                        break;
                    case LabelAttach::End:
                        position = label_info.label.span.end();
                        break;
                }

                LineLabel ll{
                    .col = std::max(
                               position, label_info.label.span.start())
                         - line.offset,
                    .label    = label_info.label,
                    .multi    = false,
                    .draw_msg = true,
                };


                line_labels.push_back(ll);
            }
        }
    }

    HSLOG_DEBUG_FMT_LINE(line_labels.size());
    return line_labels;
}

int get_line_number_width(Vec<SourceGroup> const& groups, Cache& cache) {
    int line_number_width = 0;
    for (const auto& group : groups) {
        Str  src_name = cache.display(group.src_id).value_or("<unknown>");
        auto src      = cache.fetch(group.src_id);

        auto line_range   = src->get_line_range(CodeSpan{{}, group.span});
        int  width        = fmt1(line_range.last).size();
        line_number_width = std::max(line_number_width, width);
    }
    return line_number_width;
}

/// \brief Write long horizontal part of the lines that connect the label
/// to the target on some other line.
void write_lines(
    MarginContext const& c,
    Line const&          line,
    int                  arrow_len,
    LineLabel const&     line_label,
    int                  row,
    bool                 is_first_label_line) {
    HSLOG_DEBUG("write_lines");
    HSLOG_DEPTH_SCOPE_ANON();
    HSLOG_DEBUG_FMT_STACK(
        arrow_len, row, line_label, is_first_label_line, line);

    // Lines
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {
        HSLOG_DEBUG("col:{}", col);
        HSLOG_DEPTH_SCOPE_ANON();
        int  width   = 1;
        bool is_hbar = false;
        if (is_first_label_line && line_label.label.msg.has_value()) {
            is_hbar = (
                //
                (line_label.col < col && !line_label.multi)
                //
                || (col <= line_label.col && line_label.multi)
                //
                || (line_label.label.msg && line_label.draw_msg
                    && line_label.col < col));
        }

        std::optional<LineLabel> vbar_ll = get_vbar(
            col, row, c.line_labels, c.margin_label);

        if (col == line_label.col && line_label.label.msg
            && (!c.margin_label.has_value()
                || line_label.label != c.margin_label->label)) {
            if (line_label.multi) {
                if (line_label.draw_msg) {
                    c.w.write(
                        ColRune(c.draw().mbot, line_label.label.color)
                            .dbg_origin(c.config.debug_writes));
                } else {
                    c.w.write(
                        ColRune(c.draw().rbot, line_label.label.color)
                            .dbg_origin(c.config.debug_writes));
                }
            } else {
                if (is_first_label_line) {
                    c.w.write(
                        ColRune(c.draw().lbot, line_label.label.color)
                            .dbg_origin(c.config.debug_writes));
                } else {
                    c.w.write(
                        ColRune(' ').dbg_origin(c.config.debug_writes));
                }
            }

        } else if (
            vbar_ll.has_value()
            && (col != line_label.col || line_label.label.msg)) {
            if (!c.config.cross_gap && is_hbar) {
                c.w.write(ColRune(c.draw().xbar, line_label.label.color)
                              .dbg_origin(c.config.debug_writes));
            } else if (is_hbar) {
                c.w.write(ColRune(c.draw().hbar, line_label.label.color)
                              .dbg_origin(c.config.debug_writes));
            } else {
                if (vbar_ll->multi && row == 0 && c.config.compact) {
                    c.w.write(
                        ColRune(c.draw().uarrow, vbar_ll->label.color)
                            .dbg_origin(c.config.debug_writes));
                } else {
                    c.w.write(ColRune(c.draw().vbar, vbar_ll->label.color)
                                  .dbg_origin(c.config.debug_writes));
                }
            }
        } else if (is_hbar) {
            c.w.write(ColRune(c.draw().hbar, line_label.label.color)
                          .dbg_origin(c.config.debug_writes));
        } else {
            c.w.write(ColRune(' ').dbg_origin(c.config.debug_writes));
        }

        if (chars != c.line_text.end()) { ++chars; }
    }
}
}; // namespace

Vec<Label> Report::build_multi_labels(Vec<LabelInfo> const& labels) {
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
            return (a.span.len()) > (b.span.len());
        });

    return multi_labels;
}


Vec<SourceGroup> Report::get_source_groups(Cache* cache) const {
    Vec<SourceGroup> groups;
    for (const auto& label : labels) {
        auto src_display            = cache->display(label.span.source());
        std::shared_ptr<Source> src = cache->fetch(label.span.source());
        if (!src) { continue; }

        LOGIC_ASSERTION_CHECK(
            label.span.start() <= label.span.end(),
            "Label start is after its end");

        auto const start_line = src->get_offset_line(label.span.start());
        LOGIC_ASSERTION_CHECK(
            start_line.has_value(),
            "Could not get line for offset {} from label span {}. Source "
            "len is {}",
            label.span.start(),
            label.span,
            src->len);

        auto start_line_idx = start_line.value().idx;

        int const offset = std::max(
            label.span.end() - 1, label.span.start());
        auto const offset_line = src->get_offset_line(offset);
        LOGIC_ASSERTION_CHECK(
            offset_line.has_value(),
            "Could not get line for offset {} from label span {}. Source "
            "len is {}",
            offset,
            label.span,
            src->len);
        auto end_line = offset_line.value().idx;

        LabelInfo label_info{
            .kind  = (start_line_idx == end_line) ? LabelKind::Inline
                                                  : LabelKind::Multiline,
            .label = label,
        };

        auto it = std::find_if(
            groups.begin(), groups.end(), [&](const SourceGroup& group) {
                return group.src_id == label.span.source();
            });

        if (it != groups.end()) {
            it->span.first = std::min(it->span.first, label.span.start());
            it->span.last  = std::max(it->span.last, label.span.end());
            it->labels.push_back(label_info);
        } else {
            groups.push_back(SourceGroup{
                .src_id = label.span.source(),
                .span   = slice(label.span.start(), label.span.end()),
                .labels = {label_info}});
        }
    }
    return groups;
}

void write_report_group_header(
    Config const&      config,
    int                group_idx,
    int                line_number_width,
    Cache&             cache,
    Report const&      report,
    Writer&            op,
    SourceGroup const& group) {

    std::shared_ptr<Source> src = cache.fetch(group.src_id);
    Str src_name = cache.display(group.src_id).value_or("<unknown>");

    op.write(Str(" ").repeated(line_number_width + 2));
    op.write(
        (group_idx == 0 ? ColRune(config.char_set.ltop)
                        : ColRune(config.char_set.lcross))
        + config.margin_color);
    op.write(ColRune(config.char_set.hbar) + config.margin_color);
    op.write(ColRune(config.char_set.lbox) + config.margin_color);
    if (!config.compact) { op.write(ColRune{' '}); }
    op.write(src_name);

    // File name & reference
    int location = (group.src_id == report.location.first)
                     ? report.location.second
                     : group.labels[0].label.span.start();

    auto offset_line = src->get_offset_line(location);

    // Error line and column number in the error message header
    if (offset_line) {
        op.write(":");
        op.write(fmt1(offset_line->idx + 1));
        op.write(":");
        op.write(fmt1(offset_line->col + 1));
    } else {
        op.write(":?:?");
    }
    if (!config.compact) { op.write(ColRune{' '}); }

    op.write(ColRune(config.char_set.rbox) + config.margin_color);
    op.write("\n");

    if (!config.compact) {
        op.write(Str(" ").repeated(line_number_width + 2));
        op.write(ColRune(config.char_set.vbar) + config.margin_color);
        op.write("\n");
    }
}

void write_report_source_line(
    MarginContext const&            base,
    std::optional<LineLabel> const& margin_label) {
    HSLOG_DEBUG("write_report_source_line");
    HSLOG_DEPTH_SCOPE_ANON();
    write_margin(base.clone()
                     .with_is_line(true)
                     .with_is_ellipsis(base.is_ellipsis)
                     .with_draw_labels(true));

    // Lines
    if (!base.is_ellipsis) {
        int col = 0;
        for (ColRune const& c : base.line_text) {
            Opt<CRw<Label>> highlight = get_highlight(
                col, base, margin_label);

            ColStyle color = highlight ? highlight->get().color
                                       : base.config.unimportant_color;

            base.w.write(ColRune(c.rune, color));

            col++;
        }
    }
}

void write_report_line_annotations(MarginContext base) {
    HSLOG_DEBUG("write_report_line_annotations");
    HSLOG_DEPTH_SCOPE_ANON();
    auto scope = base.scope("line_annotations");
    for (int row = 0; row < base.line_labels.size(); ++row) {
        const auto& line_label = base.line_labels[row];

        if (!base.config.compact) {
            // Margin alternate
            write_margin(
                base.clone().with_draw_labels(true).with_report_row(
                    {row, false}));

            write_line_label_arrows(
                base.with_is_ellipsis(base.is_ellipsis),
                row,
                base.arrow_len);

            base.w.write("\n");
        }

        // Margin for the first line of the label.
        write_margin(base.clone()
                         .with_is_ellipsis(base.is_ellipsis)
                         .with_report_row({row, true})
                         .with_draw_labels(true));

        write_lines(
            base.clone(),
            base.line,
            base.arrow_len,
            line_label,
            row,
            true);

        if (line_label.label.msg) {
            base.w.write(" ");
            auto split = line_label.label.msg.value().split("\n");
            if (split.size() <= 1) {
                base.w.write(line_label.label.msg.value());
            } else {
                for (auto const& it : enumerator(split)) {
                    if (!it.is_first()) {
                        base.w.write("\n");
                        write_margin(base.clone().with_draw_labels(true));

                        write_lines(
                            base,
                            base.line,
                            base.arrow_len,
                            line_label,
                            row,
                            false);
                        base.w.write(" ");
                    }
                    base.w.write(it.value());
                }
            }
        }
        base.w.write("\n");
    }
}

void write_report_group(
    int                     group_idx,
    int                     line_number_width,
    Cache&                  cache,
    Report const&           report,
    Vec<SourceGroup> const& groups,
    Writer&                 op) {
    HSLOG_INFO("write report group");
    HSLOG_DEPTH_SCOPE_ANON();
    SourceGroup const&      group  = groups[group_idx];
    auto const&             config = report.config;
    std::shared_ptr<Source> src    = cache.fetch(group.src_id);

    write_report_group_header(
        config, group_idx, line_number_width, cache, report, op, group);

    // Generate a list of multi-line labels
    Vec<Label> multi_labels = Report::build_multi_labels(group.labels);
    Slice<int> line_range = src->get_line_range(CodeSpan{{}, group.span});

    HSLOG_DEBUG_FMT_LINE(multi_labels.size());

    bool is_ellipsis = false;
    for (int idx = line_range.first; idx <= line_range.last; ++idx) {

        /* auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED(
            ([idx = idx, debug_writes = op.config->debug_writes]() {
                return ::hstd::log::init_file_sink(hstd::fmt(
                    "/tmp/formatting_line_{}_{}.log", idx, debug_writes));
            }));*/


        auto line_opt = src->line(idx);
        if (!line_opt) { continue; }

        HSLOG_DEBUG("Build line labels for {}", idx);
        HSLOG_DEPTH_SCOPE_ANON();

        Line const&              line         = line_opt.value();
        std::optional<LineLabel> margin_label = get_margin_label(
            line, multi_labels);

        Vec<LineLabel> line_labels //
            = build_line_labels(
                config,
                line,
                group.labels,
                margin_label,
                multi_labels,
                src);

        MarginContext base{
            .w                 = op,
            .config            = config,
            .multi_labels      = multi_labels,
            .line_labels       = line_labels,
            .src               = src,
            .idx               = idx,
            .line_number_width = line_number_width,
            .line              = line,
            .margin_label      = margin_label,
            .line_text         = src->get_line_text(line),
        };

        {
            HSLOG_INFO("Margin context");
            HSLOG_DEPTH_SCOPE_ANON();
            HSLOG_DEBUG_FMT_LINE(config);
            HSLOG_DEBUG_FMT_LINE(multi_labels);
            HSLOG_DEBUG_FMT_LINE(line_labels);
            HSLOG_DEBUG_FMT_LINE(idx);
            HSLOG_DEBUG_FMT_LINE(line_number_width);
            HSLOG_DEBUG_FMT_LINE(line);
            HSLOG_DEBUG_FMT_LINE(margin_label);
            HSLOG_DEBUG_FMT_LINE(src->get_line_text(line));
        }


        if (sort_line_labels(base, is_ellipsis, line_labels)) {
            base.with_is_ellipsis(is_ellipsis);
            int arrow_len = get_arrow_len(base);
            base.with_arrow_len(arrow_len);
            write_report_source_line(base, margin_label);
            op.write("\n");
            write_report_line_annotations(base);
        }
    }

    bool is_final_group = group_idx + 1 == groups.size();

    Opt<LineLabel> null_label = std::nullopt;
    MarginContext  base{
         .w                 = op,
         .config            = config,
         .multi_labels      = multi_labels,
         .line_labels       = {},
         .src               = src,
         .idx               = 0,
         .line_number_width = line_number_width,
         .draw_labels       = true,
         .is_line           = false,
         .is_ellipsis       = false,
         .report_row        = std::pair{0, false},
         .line              = Line{},
         .margin_label      = null_label,
    };

    auto write_annotation = [&](std::string const&   note,
                                hstd::ColText const& text) {
        if (!config.compact) {
            write_margin(base);
            op.write("\n");
        }

        auto noteLines = text.split("\n");
        if (noteLines.size() <= 1) {
            write_margin(base);
            op.write(note);
            op.write(text);
            op.write("\n");
        } else {
            for (auto const& it : enumerator(noteLines)) {
                write_margin(base);
                if (it.is_first()) {
                    op.write(note);
                } else {
                    op.write(hstd::Str(" ").repeated(note.size()));
                }

                op.write(it.value());
                op.write("\n");
            }
        }
    };


    // Help
    if (!report.help.empty() && is_final_group) {
        HSLOG_DEBUG("write_annotation: Help");
        HSLOG_DEPTH_SCOPE_ANON();
        if (report.help.size() == 1) {
            write_annotation("Help: ", report.help.at(0));
        } else {
            for (auto const& it : enumerator(report.help)) {
                write_annotation(
                    hstd::fmt("Help {}: ", it.index() + 1), it.value());
            }
        }
    }

    // Note
    if (!report.note.empty() && is_final_group) {
        HSLOG_DEBUG("write_annotation: Note");
        HSLOG_DEPTH_SCOPE_ANON();
        if (report.note.size() == 1) {
            write_annotation("Note: ", report.note.at(0));
        } else {
            for (auto const& it : enumerator(report.note)) {
                write_annotation(
                    hstd::fmt("Note {}: ", it.index() + 1), it.value());
            }
        }
    }

    // Tail of report
    if (!config.compact) {
        if (is_final_group) {
            op.write(
                Str(config.char_set.hbar).repeated(line_number_width + 2));
            op.write(config.char_set.rbot);
            op.write("\n");
        } else {
            op.write(Str(" ").repeated(line_number_width + 2));
            op.write(config.char_set.vbar);
            op.write("\n");
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
        op.write(ColText(kind_color, ("[" + *report.code + "] ")));
    }

    auto kind = ColText(kind_color, kindName);
    if (report.msg) {
        auto split = report.msg.value().split("\n");
        if (split.size() <= 1) {
            op.write(kind);
            op.write(": ");
            op.write(report.msg.value());
            op.write("\n");
        } else {
            for (auto const& it : enumerator(split)) {
                if (it.is_first()) {
                    op.write(kind);
                    op.write(": ");
                } else {
                    op.write(Str{" "}.repeated(kind.size() + 2));
                }
                op.write(it.value());
                op.write("\n");
            }
        }

    } else {
        op.write(kind);
        op.write(": ");
        op.write("\n");
    }
}

void Report::write_for_stream(Cache& cache, ColStream& w) const {
    UnorderedMap<int, int> label_ids;
    for (auto const& [label_idx, l] : enumerate(labels)) {
        if (label_ids.contains(l.id)) {
            throw std::logic_error(
                fmt("Report labels must have unique IDs: label with index "
                    "{} has id {} which is a duplicate of label index {}",
                    label_idx,
                    l,
                    label_ids.at(l.id)));
        }

        label_ids[l.id] = label_idx;
    }

    w.colored = true;
    auto op   = Writer{w, &config};
    write_report_header(*this, op);

    Vec<SourceGroup> groups = get_source_groups(&cache);

    // Line number maximum width
    int line_number_width = get_line_number_width(groups, cache);
    // --- Source sections ---
    for (int group_idx = 0; group_idx < groups.size(); ++group_idx) {

        write_report_group(
            group_idx, line_number_width, cache, *this, groups, op);
    }
}

Source::Source(const Str& l) : content{l} {
    int offset = 0;

    if (l.empty()) {
        Line l{.offset = offset, .len = 0};
        lines.push_back(l);
    } else {
        for (std::string const& line : l.split('\n')) {
            Line l{.offset = offset, .len = rune_length(line)};
            offset += l.len + 1;
            lines.push_back(l);
        }
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
                return line.offset <= offset;
            });
        if (it != lines.begin()) { --it; }
        int idx = std::distance(lines.begin(), it);
        if (lines.has(idx)) {
            const Line& line = lines[idx];
            LOGIC_ASSERTION_CHECK(
                line.offset <= offset,
                "line.offset = {} <= offset = {}",
                line.offset,
                offset);
            return OffsetLine{std::ref(line), idx, offset - line.offset};
        } else {
            return std::nullopt;
        }
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
    if (line.len == 0) {
        return ColText{};
    } else {
        return content.at(slice(line.offset, line.offset + line.len - 1));
    }
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

void StrCache::add(
    Id                 id,
    const std::string& source,
    const std::string& name) {
    auto knownName = names.get_right(id);
    LOGIC_ASSERTION_CHECK(
        !knownName.has_value() || knownName == name,
        "Attempting to add source with name '{}' as ID {}. This ID is "
        "already used for source name '{}'",
        name,
        id,
        knownName.value());

    if (!knownName.has_value()) {
        sources[id] = std::make_shared<Source>(source);
        names.add_unique(id, name);
    }
}

Id StrCache::add_path(const hstd::fs::path& path) {
    Id id = std::hash<std::string>{}(path.native());
    if (!names.get_right(id).has_value()) {
        add(id, getFileSource(path), path);
    }
    return id;
}
