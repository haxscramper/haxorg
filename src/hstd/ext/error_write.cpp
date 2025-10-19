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
/// \brief Line label object associated with some specific line.
struct LineLabel {
    /// \brief Which column on the line is targeted by the label. In case
    /// of the multiline label this field is used in two contexts. One for
    int col;
    /// \brief Information about the
    Label label;
    /// \brief Report is labeling content across multiple lines at once.
    bool multi;
    /// \brief Whether to draw the label on the associated line, or it will
    /// be drawn somewhere else. The `.label` field is present regardless,
    /// but only used if the `draw_msg` is set to true.
    bool draw_msg;
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
        if (config->debug_writes) {
            stream << stream.green() << value << stream.end()
                   << stream.blue() << fmt("@{}", line) << stream.end();
        } else {
            stream << value;
        }
    }
};


/// \brief Margin context provides information necessary to decide how each
/// part of the margin is going to be rendered. The initial margin object
/// is created one per anontated source code line, in `write_report_group`,
/// and then cloned and amended for use in the report labels.
struct MarginContext {
    Writer& w;
    /// \brief Return a copy of the current margin context that can then be
    /// amended for a use in various report part rendering.
    MarginContext clone() const { return *this; }
    ColText       line_text;
    _field(int, source_line_idx, 0);
    /// \brief Drawing margin for the line showing source code.
    _field(bool, is_line, false);
    /// \brief Gap in the vertical lines for empty spaces between source
    /// content lines with annotations.
    _field(bool, is_gap, false);
    /// \brief Number of characters taken by the line number in the report.
    _field(int, line_number_width, 0);
    /// \brief Draw the label part of the margin, like horizontal end rows.
    _field(bool, draw_labels, false);
    _field(int, arrow_len, 0);
    Line const& line;
    /// \brief Information about the active report label that is being
    /// drawn.
    std::optional<std::pair<int, bool>> active_label = std::nullopt;
    Vec<LineLabel> const&               line_labels;
    std::optional<LineLabel> const&     margin_label;
    std::shared_ptr<Source>             src;
    /// \brief List of the multi-labels for this record. All multi-labels
    /// are visible for margin context. Margin column index maps to the
    /// multi-label indices.
    Vec<Label> const& multi_labels;
    Config const&     config;

    // TODO: What second parameter in the tuple (the bool one) refers to?
    MarginContext& with_active_label(std::pair<int, bool> const& value) {
        active_label = value;
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

/// \brief Get the information about the multi-label on the target line.
/// Returns a single label with the start/end closest to the actual line
/// span.
std::optional<LineLabel> get_margin_label(
    Line const&       line,
    Vec<Label> const& multi_labels) {
    std::optional<LineLabel> margin_label;
    int                      min_key = std::numeric_limits<int>::max();
    for (Label const& label : multi_labels) {
        bool is_start = line.span().contains(label.span.start());
        bool is_end   = line.span().contains(label.span.end());

        if (is_start || is_end) {
            LineLabel ll{
                .col = (is_start ? label.span.start() : label.span.end())
                     - line.offset,
                .label    = label,
                .multi    = true,
                .draw_msg = is_end,
            };


            // TODO: Not clear how this construct arranges the multi-labels
            // and selects something for the target line.
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

Pair<bool, bool> is_gap_and_skip_line(
    MarginContext const&  c,
    bool                  is_gap,
    Vec<LineLabel> const& line_labels) {
    bool is_skip = false;
    // Skip this line if we don't have labels for it
    if (line_labels.size() == 0 && !c.margin_label.has_value()) {
        bool within_label = std::any_of(
            c.multi_labels.begin(),
            c.multi_labels.end(),
            [&](Label const& label) {
                return label.span.contains(c.line.span().first);
            });
        if (!is_gap && within_label) {
            is_gap = true;
        } else {
            if (!c.config.compact && !is_gap) {
                write_margin(c.clone().with_is_gap(is_gap));
                c.w.write("\n");
            }
            is_gap  = true;
            is_skip = true;
        }
    } else {
        is_gap = false;
    }
    return {is_skip, is_gap};
}

bool sort_line_labels(
    MarginContext const& c,
    Vec<LineLabel>&      line_labels) {

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
    /// \brief Which label requires drawing a horizontal bar here?
    Opt<Label> hbar_label = std::nullopt;
    /// \brief Which label requires drawing a vertical bar here?
    Opt<Label> vbar_label = std::nullopt;
    /// \brief Which label requires drawing a corner element here?
    Opt<Label> corner_label = std::nullopt;
    /// \brief If there is a label that requires drawing a corner, is this
    /// corner a start or an end?
    Opt<bool> is_corner_start = std::nullopt;
    /// \brief Line label if there is an annotation label associated with
    /// the specified column of the margin. If this field is set, then
    /// `is_margin_label_start` should also be set.
    Opt<LineLabel> margin_label          = std::nullopt;
    Opt<bool>      is_margin_label_start = std::nullopt;
    DESC_FIELDS(
        MarginElements,
        (hbar_label,
         vbar_label,
         corner_label,
         is_corner_start,
         margin_label,
         is_margin_label_start));
};

/// \brief Get information about the margin rendering at the particular
/// column. Margin context will provide additional information about active
/// labels etc.
MarginElements fill_margin_elements(
    MarginContext const& c,
    int                  margin_col) {
    MarginElements result;
    Slice<int> line_span = c.src->line(c.source_line_idx).value().span();
    // Iterate over all multi-line labels in the report to find which
    // labels are applicable for a given line span.
    for (int margin_label_idx = 0;
         margin_label_idx
         < std::min(margin_col + 1, c.multi_labels.size());
         ++margin_label_idx) {
        auto           label = c.multi_labels.at(margin_label_idx);
        Opt<LineLabel> margin;
        if (c.margin_label && label == c.margin_label->label) {
            margin = c.margin_label;
        }

        if (label.span.start() <= line_span.last
            && line_span.first <= label.span.end()) {
            // TODO: What `is_parent` represents exactly?
            bool is_parent = margin_label_idx != margin_col;
            bool is_start  = line_span.contains(label.span.start());
            bool is_end    = line_span.contains(label.span.end());


            if (margin && c.is_line) {
                // Drawing margin on the real source code line. There is a
                // margin label that is targeting this column exactly.
                result.margin_label          = margin.value();
                result.is_margin_label_start = is_start;
            } else if (
                (!is_start && !is_end) || (!is_start && c.is_line)) {
                // Drawing margin on the intermediate gap between the start
                // and the end.
                if (!result.vbar_label && !is_parent) {
                    result.vbar_label = label;
                }
            } else if (c.active_label.has_value()) {
                // There is an active report label that the code is drawing
                // margin for.
                auto [active_label_idx, active_second_wtf] //
                    = c.active_label.value();
                int label_row = 0;
                for (int r = 0; r < c.line_labels.size(); ++r) {
                    if (label == c.line_labels[r].label) {
                        label_row = r;
                        break;
                    }
                }

                if (active_label_idx == label_row) {
                    // The margin is being drawn for the active label.
                    if (margin) {
                        if (margin_col == margin_label_idx) {
                            result.vbar_label = margin->label;
                        } else {
                            result.vbar_label = std::nullopt;
                        }

                        if (is_start) { continue; }
                    }

                    if (active_second_wtf) {
                        result.hbar_label = label;
                        if (!is_parent) {
                            result.corner_label    = label;
                            result.is_corner_start = is_start;
                        }
                    } else if (!is_start) {
                        if (!result.vbar_label && !is_parent) {
                            result.vbar_label = label;
                        }
                    }
                } else {
                    // The margin is being drawn for some other label, but
                    // it is possible it (the other label) is still
                    // affecting how the margin is going to look like.
                    if (!result.vbar_label && !is_parent
                        && ((is_start && label_row <= active_label_idx)
                            || //
                            (!is_start
                             && (active_label_idx < label_row)))) {
                        result.vbar_label = label;
                    }
                }
            }
        }
    }

    return result;
}


/// \brief Get characters used to build the line margin elements.
Pair<ColRune, ColRune> get_corner_elements(
    MarginContext const&  c,
    int                   margin_col,
    MarginElements const& margin,
    CR<Opt<CRw<Label>>>   multi_label) {
    ColRune     base;
    ColRune     extended;
    auto const& d = c.draw();
// #define __DD(_value) hstd::fmt("{}:{}", #_value, __LINE__)
#define __DD(_value) _value

    if (margin.corner_label) {
        Label const& label    = margin.corner_label.value();
        bool const   is_start = margin.is_corner_start.value();
        if (is_start) {
            base = ColRune(__DD(d.ltop), label.color);
        } else {
            // <<get_corner_elements.bottom_multiline_angle>>
            // Draw the bottom left angle of the multi-line arrow for
            // position.
            base = ColRune(__DD(d.lbot), label.color);
        }

        extended = ColRune(__DD(d.hbar), label.color);
    } else if (
        margin.hbar_label && margin.vbar_label && !c.config.cross_gap) {
        base     = ColRune(__DD(d.xbar), margin.hbar_label->color);
        extended = ColRune(__DD(d.hbar), margin.hbar_label->color);
    } else if (margin.hbar_label) {
        //
        base     = ColRune(__DD(d.hbar), margin.hbar_label->color);
        extended = ColRune(__DD(d.hbar), margin.hbar_label->color);
    } else if (margin.vbar_label) {
        if (c.is_gap) {
            base = ColRune(__DD(d.vbar_gap), margin.vbar_label->color);
        } else {
            base = ColRune(__DD(d.vbar), margin.vbar_label->color);
        }
        extended = ColRune(__DD(' '));
    } else if (margin.margin_label && c.is_line) {
        auto const& label    = margin.margin_label.value();
        bool        is_start = margin.is_margin_label_start.value();
        bool is_col   = multi_label && multi_label->get() == label.label;
        bool is_limit = margin_col == c.multi_labels.size();
        // clang-format off
        /*
         *   ╭─[tao:1:14]
         * 6 │╭>    # Some x => x
         * 7 │├>    # None => 0
         *   123
         *
         *   1 - main margin attached to the location info, not returned by this function
         *   2 - `is_col`
         *   3 - `is_limit`
         */
        // clang-format on

        if (is_limit) {
            // is the rightmost column on the margin for the the content
            // line that has a label.
            base = ColRune(__DD(d.rarrow), label.label.color);
        } else if (is_col) {
            // Draw top or middle line of the multi-line label. Bottom line
            // is drawn in [get_corner_elements.bottom_multiline_angle]
            if (is_start) {
                // Topmost part of the margin label line
                base = ColRune(__DD(d.ltop), label.label.color);
            } else {
                // Continuation of a margin line for a multi-line label
                base = ColRune(__DD(d.lcross), label.label.color);
            }
        } else {
            // clang-format off
            /*
             *
             *  3 │ ╭─────────>def sixes = ["6", 6, True, (), []]
             *    │╭┼──────────────╯             │    │    │   │   MSG [26..100] 574
             *
             *    long line coming to `def` from the left is drawn here.
             */
            // clang-format on
            base = ColRune(__DD(d.hbar), label.label.color);
        }

        if (is_limit) {
            extended = ColRune(__DD(' '));
        } else {
            extended = ColRune(__DD(d.hbar), label.label.color);
        }
    } else {
        base     = ColRune(__DD(' '));
        extended = ColRune(__DD(' '));
    }

    return {base, extended};
}

void write_margin_line_number(MarginContext const& c) {
    Str line_number;

    // Get the line number text for the report.
    if (c.is_line && !c.is_gap) {
        int line_no = c.source_line_idx + 1;
        line_number = Str(" ").repeated(
                          c.line_number_width - fmt1(line_no).length())
                    + Str(fmt1(line_no)) + Str(" ") + Str(c.draw().vbar);
    } else {
        line_number = Str(" ").repeated(c.line_number_width + 1);
        line_number += (c.is_gap ? c.draw().vbar_gap : c.draw().vbar);
    }

    c.w.write(" ");
    c.w.write(ColText(c.config.margin_color, line_number));
    c.w.write(c.config.compact ? "" : " ");
}

/// \brief Write end arrows, line number, vertical part of the image or an
/// empty space to help with the alignment of the rest of the label.
void write_margin(MarginContext const& c) {
    auto __scope = c.scope("margin");
    write_margin_line_number(c);

    // Multi-line margins -- for labels that have spans over multiple lines
    // at once.
    if (c.draw_labels) {
        for (int margin_col = 0;
             margin_col
             < c.multi_labels.size() + (0 < c.multi_labels.size() ? 1 : 0);
             ++margin_col) {
            Opt<CRw<Label>> multi_label = c.multi_labels.get(margin_col);
            auto            margin = fill_margin_elements(c, margin_col);

            if (margin.margin_label && c.is_line) {
                bool is_col = multi_label
                           && (*multi_label
                               == margin.margin_label.value().label);

                bool is_limit = margin_col + 1 == c.multi_labels.size();
                if (!is_col && !is_limit) {
                    margin.hbar_label = margin.hbar_label.value_or(
                        margin.margin_label.value().label);
                }
            }

            if (margin.hbar_label
                && !(
                    (*margin.hbar_label != c.margin_label->label)
                    || !c.is_line)) {
                margin.hbar_label = std::nullopt;
            }

            auto [base, extended] = get_corner_elements(
                c, margin_col, margin, multi_label);

            c.w.write(base);
            if (!c.config.compact) { c.w.write(extended); }
        }
    }
}


/// \brief Should we draw a vertical bar as part of a label arrow
/// on this line and column?
auto get_vbar_label(
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
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {

        Opt<LineLabel> underline = get_underline(c, col);
        if (row != 0) { underline.reset(); }

        ColRune ch;
        ColRune tail;
        // original rust code is a barely legible nested if-else
        // expression, and even after several days of looking at the
        // `write.rs` file I don't have any confidence in my understanding
        // of what this thing is supposed to be in the end. It draws the
        // arrows, yes, but if I actually use the `tail` code, like it is
        // written in the rust version, the final result looks horrible.
        if (Opt<LineLabel> vbar = get_vbar_label(
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

void collect_multiline_labels(
    Vec<LineLabel>&       line_labels,
    Line const&           line,
    Vec<Label> const&     multi_labels,
    Opt<LineLabel> const& margin_label) {

    for (CR<Label> label : multi_labels) {
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
}

void collect_inline_labels(
    Vec<LineLabel>&         line_labels,
    Config const&           config,
    Line const&             line,
    Vec<LabelInfo> const&   labels,
    std::shared_ptr<Source> src) {
    for (const LabelInfo& label_info : labels) {
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
    Vec<LineLabel> line_labels;
    collect_multiline_labels(
        line_labels, line, multi_labels, margin_label);

    collect_inline_labels(line_labels, config, line, labels, src);

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

    // Lines
    auto chars = c.line_text.begin();
    for (int col = 0; col < arrow_len; ++col) {
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

        std::optional<LineLabel> vbar_ll = get_vbar_label(
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


struct ReportGroupContext {
    Report const&           report;
    int                     line_number_width;
    std::shared_ptr<Source> src;
    SourceGroup const&      group;
    Vec<Label> const&       multi_labels;
    Writer&                 op;
    Config const&           config;
    Cache&                  cache;
    int                     group_idx;
    Vec<SourceGroup> const& groups;
};

void write_report_group_header(ReportGroupContext& c) {

    std::shared_ptr<Source> src = c.cache.fetch(c.group.src_id);
    Str src_name = c.cache.display(c.group.src_id).value_or("<unknown>");

    c.op.write(Str(" ").repeated(c.line_number_width + 2));
    c.op.write(
        (c.group_idx == 0 ? ColRune(c.config.char_set.ltop)
                          : ColRune(c.config.char_set.lcross))
        + c.config.margin_color);
    c.op.write(ColRune(c.config.char_set.hbar) + c.config.margin_color);
    c.op.write(ColRune(c.config.char_set.lbox) + c.config.margin_color);
    if (!c.config.compact) { c.op.write(ColRune{' '}); }
    c.op.write(src_name);

    // File name & reference
    int location = (c.group.src_id == c.report.location.first)
                     ? c.report.location.second
                     : c.group.labels[0].label.span.start();

    auto offset_line = src->get_offset_line(location);

    // Error line and column number in the error message header
    if (offset_line) {
        c.op.write(":");
        c.op.write(fmt1(offset_line->idx + 1));
        c.op.write(":");
        c.op.write(fmt1(offset_line->col + 1));
    } else {
        c.op.write(":?:?");
    }
    if (!c.config.compact) { c.op.write(ColRune{' '}); }

    c.op.write(ColRune(c.config.char_set.rbox) + c.config.margin_color);
    c.op.write("\n");

    if (!c.config.compact) {
        c.op.write(Str(" ").repeated(c.line_number_width + 2));
        c.op.write(
            ColRune(c.config.char_set.vbar) + c.config.margin_color);
        c.op.write("\n");
    }
}

/// \brief Write the main source line of the report with all the margin
/// elements.
void write_report_source_line_text(
    MarginContext const&            base,
    std::optional<LineLabel> const& margin_label) {
    write_margin(base.clone()
                     .with_is_line(true)
                     .with_is_gap(base.is_gap)
                     .with_draw_labels(true));

    // Lines
    if (!base.is_gap) {
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


/// \brief Write all the follow-up annotations under the source line in the
/// report.
void write_report_source_line_annotations(MarginContext base) {
    auto scope = base.scope("line_annotations");
    for (int label_idx = 0; label_idx < base.line_labels.size();
         ++label_idx) {
        const auto& line_label = base.line_labels[label_idx];

        if (!base.config.compact) {
            // Margin alternate
            write_margin(
                base.clone().with_draw_labels(true).with_active_label(
                    {label_idx, false}));

            write_line_label_arrows(
                base.with_is_gap(base.is_gap), label_idx, base.arrow_len);

            base.w.write("\n");
        }

        // Margin for the first line of the label.
        write_margin(base.clone()
                         .with_is_gap(base.is_gap)
                         .with_active_label({label_idx, true})
                         .with_draw_labels(true));

        write_lines(
            base.clone(),
            base.line,
            base.arrow_len,
            line_label,
            label_idx,
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
                            label_idx,
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


void write_report_group_source_lines(ReportGroupContext& c) {
    Slice<int> line_range = c.src->get_line_range(
        CodeSpan{{}, c.group.span});

    bool is_gap = false;
    for (int line_idx = line_range.first; line_idx <= line_range.last;
         ++line_idx) {
        auto line_opt = c.src->line(line_idx);
        if (!line_opt) { continue; }

        Line const&              line         = line_opt.value();
        std::optional<LineLabel> margin_label = get_margin_label(
            line, c.multi_labels);

        // Fine labels for the source line
        Vec<LineLabel> line_labels //
            = build_line_labels(
                c.report.config,
                line,
                c.group.labels,
                margin_label,
                c.multi_labels,
                c.src);

        // Create margin context for drawing this source code line.
        MarginContext base{
            .w                 = c.op,
            .config            = c.report.config,
            .multi_labels      = c.multi_labels,
            .line_labels       = line_labels,
            .src               = c.src,
            .source_line_idx   = line_idx,
            .line_number_width = c.line_number_width,
            .line              = line,
            .margin_label      = margin_label,
            .line_text         = c.src->get_line_text(line),
        };

        auto [is_skip, is_gap_upd] = is_gap_and_skip_line(
            base, is_gap, line_labels);

        is_gap = is_gap_upd;

        if (!is_skip) {
            sort_line_labels(base, line_labels);
            base.with_is_gap(is_gap);
            int arrow_len = get_arrow_len(base);
            base.with_arrow_len(arrow_len);
            write_report_source_line_text(base, margin_label);
            c.op.write("\n");
            write_report_source_line_annotations(base);
        }
    }
}

void write_report_group_annotations(ReportGroupContext& c) {
    bool is_final_group = c.group_idx + 1 == c.groups.size();

    Opt<LineLabel> null_label = std::nullopt;
    MarginContext  base{
         .w                 = c.op,
         .config            = c.report.config,
         .multi_labels      = c.multi_labels,
         .line_labels       = {},
         .src               = c.src,
         .source_line_idx   = 0,
         .line_number_width = c.line_number_width,
         .draw_labels       = true,
         .is_line           = false,
         .is_gap            = false,
         .active_label      = std::pair{0, false},
         .line              = Line{},
         .margin_label      = null_label,
    };

    // Render text for a trailing elements that come after the report
    // labels.
    auto write_annotation = [&](std::string const&   note,
                                hstd::ColText const& text) {
        if (!c.report.config.compact) {
            write_margin(base);
            c.op.write("\n");
        }

        auto noteLines = text.split("\n");
        if (noteLines.size() <= 1) {
            write_margin(base);
            c.op.write(note);
            c.op.write(text);
            c.op.write("\n");
        } else {
            for (auto const& it : enumerator(noteLines)) {
                write_margin(base);
                if (it.is_first()) {
                    c.op.write(note);
                } else {
                    c.op.write(hstd::Str(" ").repeated(note.size()));
                }

                c.op.write(it.value());
                c.op.write("\n");
            }
        }
    };


    // Help
    if (!c.report.help.empty() && is_final_group) {
        if (c.report.help.size() == 1) {
            write_annotation("Help: ", c.report.help.at(0));
        } else {
            for (auto const& it : enumerator(c.report.help)) {
                write_annotation(
                    hstd::fmt("Help {}: ", it.index() + 1), it.value());
            }
        }
    }

    // Note
    if (!c.report.note.empty() && is_final_group) {
        if (c.report.note.size() == 1) {
            write_annotation("Note: ", c.report.note.at(0));
        } else {
            for (auto const& it : enumerator(c.report.note)) {
                write_annotation(
                    hstd::fmt("Note {}: ", it.index() + 1), it.value());
            }
        }
    }

    // Tail of report
    if (!c.report.config.compact) {
        if (is_final_group) {
            c.op.write(Str(c.report.config.char_set.hbar)
                           .repeated(c.line_number_width + 2));
            c.op.write(c.report.config.char_set.rbot);
            c.op.write("\n");
        } else {
            c.op.write(Str(" ").repeated(c.line_number_width + 2));
            c.op.write(c.report.config.char_set.vbar);
            c.op.write("\n");
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
        SourceGroup const&      group = groups.at(group_idx);
        std::shared_ptr<Source> src   = cache.fetch(group.src_id);

        // Generate a list of multi-line labels
        Vec<Label> multi_labels = Report::build_multi_labels(group.labels);

        ReportGroupContext c{
            .report            = *this,
            .line_number_width = line_number_width,
            .src               = src,
            .group             = group,
            .multi_labels      = multi_labels,
            .op                = op,
            .config            = config,
            .cache             = cache,
            .group_idx         = group_idx,
            .groups            = groups,
        };

        write_report_group_header(c);
        write_report_group_source_lines(c);
        write_report_group_annotations(c);
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
