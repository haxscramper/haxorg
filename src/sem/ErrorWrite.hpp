#include "hstd/stdlib/Slice.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <memory>
#include <functional>
#include <ranges>
#include <optional>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>

#include <cassert>

#include <fmt/core.h>
#include <hstd/stdlib/Vec.hpp>

#include <boost/describe.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/reflection.hpp>

class Source;

// A trait implemented by `Source` caches.
using Id = int;

// A trait implemented by spans within a character-based source.
class CodeSpan {
  public:
    // Get the identifier of the source that this Codespan refers to.
    virtual const Id source() const = 0;

    // Get the start offset of this Codespan.
    // Offsets are zero-indexed character offsets from the beginning of the
    // source.
    virtual int start() const = 0;

    // Get the (exclusive) end offset of this Codespan.
    // The end offset should *always* be greater than or equal to the start
    // offset as given by CodeSpan::start(). Offsets are zero-indexed
    // character offsets from the beginning of the source.
    virtual int end() const = 0;

    // Get the length of this Codespan (difference between the start of the
    // Codespan and the end of the Codespan).
    int len() const { return end() - start(); }

    // Determine whether the Codespan contains the given offset.
    bool contains(int offset) const {
        return start() <= offset && offset < end();
    }
};

// CodeSpan implementation for Range<usize>
class RangeCodeSpan : public CodeSpan {
  public:
    explicit RangeCodeSpan(Slice<int> range) : range_(range) {}

    virtual const Id source() const override { return -1; }
    int              start() const override { return range_.first; }
    int              end() const override { return range_.last; }

  private:
    Slice<int> range_;
};

// CodeSpan implementation for (Id, Range<usize>)
class TupleCodeSpan : public CodeSpan {
  public:
    explicit TupleCodeSpan(Id id, Slice<int> range)
        : id_(std::move(id)), range_(range) {}

    const Id source() const override { return id_; }
    int      start() const override { return range_.first; }
    int      end() const override { return range_.last; }

  private:
    Id         id_;
    Slice<int> range_;
};

class Cache {
  public:
    // Fetch the `Source` identified by the given ID, if possible.
    // TODO: Don't box
    virtual std::shared_ptr<Source> fetch(Id const& id) = 0;

    // Display the given ID. as a single inline value.
    virtual std::optional<QString> display(Id const& id) const = 0;
};


// A type representing a single line of a `Source`.
struct Line {
    int     offset;
    int     len;
    QString chars;

    // Get the offset of this line in the original `Source` (i.e: the
    // number of characters that precede it).
    int get_offset() const { return offset; }

    // Get the character length of this line.
    int get_len() const { return len; }

    // Get the offset Codespan of this line in the original `Source`.
    Slice<int> span() const { return {offset, offset + len}; }
};

BOOST_DESCRIBE_STRUCT(Line, (), (offset, len, chars));

inline QTextStream& operator<<(QTextStream& os, Line const& value) {
    return described_class_printer(os, value);
}

// A type representing a single source that may be referred to by
// `CodeSpan`s.
//
// In most cases, a source is a single input file.
struct Source {
    Vec<Line> lines;
    int       len;

    Source(QString const& l) {
        int offset = 0;
        for (QString const& line : l.split('\n')) {
            Line l{
                .offset = offset,
                .len    = line.size() + 1,
                .chars  = line,
            };

            offset += l.len;
            qDebug() << l;
            lines.push_back(l);
        }
        len = offset;
    }

    struct OffsetLine {
        const Line& line;
        int         idx = 0;
        int         col = 0;
    };

    // Get access to a specific, zero-indexed Line.
    std::optional<Line> line(int idx) const {
        if (idx < lines.size()) {
            return std::cref(lines[idx]);
        } else {
            return std::nullopt;
        }
    }

    // Get the line that the given offset appears on, and the line/column
    // numbers of the offset. Note that the line/column numbers are
    // zero-indexed.
    std::optional<OffsetLine> get_offset_line(int offset) {
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

    // Get the range of lines that this Codespan runs across.
    // The resulting range is guaranteed to contain valid line indices
    // (i.e: those that can be used for Source::line()).
    Slice<int> get_line_range(const CodeSpan& Codespan) {
        std::optional<OffsetLine> start = get_offset_line(
            Codespan.start());
        std::optional<OffsetLine> end = get_offset_line(Codespan.end());

        if (start && end) {
            return {start->idx, end->idx};
        } else {
            return {0, lines.size()};
        }
    }
};

class StrCache : public Cache {


    // Cache interface
  public:
    std::unordered_map<Id, std::shared_ptr<Source>> sources;
    void add(Id id, QString const& source) {
        sources[id] = std::make_shared<Source>(source);
    }
    std::shared_ptr<Source> fetch(const Id& id) override {
        return sources.at(id);
    }
    std::optional<QString> display(const Id& id) const override {
        return "";
    }
};

struct Characters {
    QChar hbar;
    QChar vbar;
    QChar xbar;
    QChar vbar_break;
    QChar vbar_gap;

    QChar uarrow;
    QChar rarrow;

    QChar ltop;
    QChar mtop;
    QChar rtop;
    QChar lbot;
    QChar rbot;
    QChar mbot;

    QChar lbox;
    QChar rbox;

    QChar lcross;
    QChar rcross;

    QChar underbar;
    QChar underline;
};

Characters unicode();

Characters ascii();

enum LabelKind
{
    Inline,
    Multiline
};

enum class Color
{
    Unset,
    Default,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Fixed,
    RGB,
};

struct Label {
    // Give this label a message
    Label with_message(const QString& msg) {
        this->msg = msg;
        return *this;
    }

    // Give this label a highlight color
    Label with_color(const Color& color) {
        this->color = color;
        return *this;
    }

    // Specify the order of this label relative to other labels
    Label with_order(int32_t order) {
        this->order = order;
        return *this;
    }

    // Specify the priority of this label relative to other labels
    Label with_priority(int32_t priority) {
        this->priority = priority;
        return *this;
    }

    Label(const std::shared_ptr<CodeSpan>& Codespan)
        : span(Codespan), msg(""), color(Color()), order(0), priority(0) {}

    std::shared_ptr<CodeSpan> span;
    std::optional<QString>    msg;
    Color                     color;
    int32_t                   order;
    int32_t                   priority;

    bool operator==(Label const& other) const { return msg == other.msg; }

    int last_offset() const {
        return std::max(span->end() - 1, span->start());
    }
};
struct LabelInfo {
    LabelKind   kind;
    const Label label;
};


struct SourceGroup {
    Id             src_id;
    Slice<int>     span;
    Vec<LabelInfo> labels;
};

enum class ReportKind
{
    Error,
    Warning,
    Advice,
    Custom
};

enum class LabelAttach
{
    // Arrows should attach to the start of the label Codespan.
    Start,
    // Arrows should attach to the middle of the label Codespan (or as
    // close to the middle as we can get).
    Middle,
    // Arrows should attach to the end of the label Codespan.
    End,
};


enum class MessageCharSet
{
    // Unicode characters (an attempt is made to use only
    // commonly-supported characters).
    Unicode,
    // ASCII-only characters.
    Ascii,
};

struct Config {
    Config()
        : cross_gap(true)
        , label_attach(LabelAttach::Middle)
        , compact(false)
        , underlines(true)
        , multiline_arrows(true)
        , color(true)
        , tab_width(4)
        , char_set(MessageCharSet::Ascii) {}

    Config& with_cross_gap(bool cross_gap) {
        this->cross_gap = cross_gap;
        return *this;
    }

    Config& with_label_attach(LabelAttach label_attach) {
        this->label_attach = label_attach;
        return *this;
    }

    Config& with_compact(bool compact) {
        this->compact = compact;
        return *this;
    }

    Config& with_underlines(bool underlines) {
        this->underlines = underlines;
        return *this;
    }

    Config& with_multiline_arrows(bool multiline_arrows) {
        this->multiline_arrows = multiline_arrows;
        return *this;
    }

    Config& with_color(bool color) {
        this->color = color;
        return *this;
    }

    Config& with_tab_width(int tab_width) {
        this->tab_width = tab_width;
        return *this;
    }

    Config& with_char_set(MessageCharSet char_set) {
        this->char_set = char_set;
        return *this;
    }

    std::optional<Color> error_color() {
        return color ? std::make_optional(Color::Red) : std::nullopt;
    }

    std::optional<Color> warning_color() {
        return color ? std::make_optional(Color::Yellow) : std::nullopt;
    }

    std::optional<Color> advice_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    std::optional<Color> margin_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    std::optional<Color> unimportant_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    std::optional<Color> note_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    std::pair<QChar, int> char_width(QChar c, int col) {
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


    bool           cross_gap;
    LabelAttach    label_attach;
    bool           compact;
    bool           underlines;
    bool           multiline_arrows;
    bool           color;
    int            tab_width;
    MessageCharSet char_set = MessageCharSet::Unicode;
};

auto fg = [](QChar ch, std::optional<Color> col) { return ch; };

class Report {
  public:
    ReportKind             kind;
    std::optional<QString> code;
    std::optional<QString> msg;
    std::optional<QString> note;
    std::optional<QString> help;
    std::pair<Id, int>     location;
    Vec<Label>             labels;
    Config                 config;


    // Give this report a numerical code that may be used to more precisely
    // look up the error in documentation.
    Report& with_code(const QString& code) {
        this->code = code;
        return *this;
    }

    // Set the message of this report.
    void set_message(const QString& msg) { this->msg = msg; }

    // Add a message to this report.
    Report& with_message(const QString& msg) {
        set_message(msg);
        return *this;
    }

    // Set the note of this report.
    void set_note(const QString& note) { this->note = note; }

    // Set the note of this report.
    Report& with_note(const QString& note) {
        set_note(note);
        return *this;
    }

    // Set the help message of this report.
    void set_help(const QString& help) { this->help = help; }

    // Set the help message of this report.
    Report& with_help(const QString& help) {
        set_help(help);
        return *this;
    }

    // Add a label to the report.
    void add_label(const Label& label) { labels.push_back(label); }

    // Add multiple labels to the report.
    template <typename Container>
    void add_labels(const Container& labels) {
        this->labels.insert(
            this->labels.end(), labels.begin(), labels.end());
    }

    // Add a label to the report.
    Report& with_label(const Label& label) {
        add_label(label);
        return *this;
    }

    // Add multiple labels to the report.
    template <typename Container>
    Report& with_labels(const Container& labels) {
        add_labels(labels);
        return *this;
    }

    // Use the given Config to determine diagnostic attributes.
    Report& with_config(const Config& config) {
        this->config = config;
        return *this;
    }

    Report(ReportKind kind, Id id, int offset)
        : kind(kind), location({id, offset}) {}

    Vec<SourceGroup> get_source_groups(Cache* cache) {
        Vec<SourceGroup> groups;
        for (const auto& label : labels) {
            auto src_display = cache->display(label.span->source());
            std::shared_ptr<Source> src = cache->fetch(
                label.span->source());
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
                groups.begin(),
                groups.end(),
                [&](const SourceGroup& group) {
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
                    .span = slice(label.span->start(), label.span->end()),
                    .labels = {label_info}});
            }
        }
        return groups;
    }


    void write(Cache& cache, QTextStream& w) {
        write_for_stream(cache, w);
    }

    // Write this diagnostic out to stderr.
    void eprint(Cache& cache) { write(cache, qcout); }

    // Write this diagnostic out to stdout.
    // In most cases, eprint is the more correct function to use.
    void print(Cache& cache) { write(cache, qcout); }

    struct LineLabel {
        int   col;
        Label label;
        bool  multi;
        bool  draw_msg;
    };


    struct MarginContext {
        QTextStream&                        w;
        int                                 idx;
        bool                                is_line       = false;
        bool                                is_ellipsis   = false;
        bool                                draw_labels   = false;
        std::optional<std::pair<int, bool>> report_row    = std::nullopt;
        const Vec<LineLabel>&               line_labels   = {};
        const std::optional<LineLabel>&     margin_label  = std::nullopt;
        int                                 line_no_width = 0;
        std::shared_ptr<Source>             src;
        Vec<const Label*>&                  multi_labels;
        Characters                          draw;
    };

    void write_margin(MarginContext c) {
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
                auto         line_span = c.src->line(c.idx).value().span();

                for (int i = 0;
                     i < std::min(col + 1, c.multi_labels.size());
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
                        bool is_end = line_span.contains(
                            label.last_offset());

                        if (margin && c.is_line) {
                            margin_ptr = std::make_pair(margin, is_start);
                        } else if (!is_start && (!is_end || c.is_line)) {
                            vbar = vbar ? vbar
                                        : (!is_parent ? &label : nullptr);
                        } else if (c.report_row.has_value()) {
                            auto report_row_value = c.report_row.value();
                            int  label_row        = 0;
                            for (int r = 0; r < c.line_labels.size();
                                 ++r) {
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
                                    vbar = vbar ? vbar
                                                : (!is_parent ? &label
                                                              : nullptr);
                                }
                            } else {
                                vbar = vbar
                                         ? vbar
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
                    bool is_col              = multi_label
                                                 ? (*multi_label == margin->label)
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
                    bool is_col             = multi_label
                                                ? (*multi_label == margin->label)
                                                : false;
                    bool is_limit           = col == c.multi_labels.size();
                    ab                      = {
                        is_limit ? fg(c.draw.rarrow, margin->label.color)
                                             : is_col ? (
                              is_start
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
    };


    void write_for_stream(Cache& cache, QTextStream& w) {
        qDebug() << "Write for stream requested";
        Characters draw;
        switch (config.char_set) {
            case MessageCharSet::Unicode: draw = unicode(); break;
            case MessageCharSet::Ascii: draw = ascii(); break;
        }

        // --- Header ---
        std::optional<QString> code;
        if (code.has_value()) {
            code = "[" + *code + "] ";
        }
        QString id = "TODO_FORMAT"; // fmt::format("{}{}:", code,
                                    // kind);
        std::optional<Color> kind_color;
        switch (kind) {
            case ReportKind::Error:
                kind_color = config.error_color();
                break;
            case ReportKind::Warning:
                kind_color = config.warning_color();
                break;
            case ReportKind::Advice:
                kind_color = config.advice_color();
                break;
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
            for (int idx = line_range.first; idx <= line_range.last;
                 ++idx) {
                auto line_opt = src->line(idx);
                if (!line_opt) {
                    continue;
                }

                Line line = line_opt.value();

                std::optional<LineLabel> margin_label;
                int min_key = std::numeric_limits<int>::max();
                for (int i = 0; i < multi_labels.size(); ++i) {
                    const Label* label    = multi_labels[i];
                    bool         is_start = line.span().contains(
                        label->span->start());
                    bool is_end = line.span().contains(
                        label->last_offset());

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
                    bool is_start = line.span().contains(
                        label->span->start());
                    bool is_end = line.span().contains(
                        label->last_offset());
                    bool different_from_margin_label
                        = (!margin_label.has_value()
                           || reinterpret_cast<const void*>(label)
                                  != reinterpret_cast<const void*>(
                                      &margin_label->label));

                    if ((is_start && different_from_margin_label)
                        || is_end) {
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
                        && label_info.label.span->end()
                               <= line.span().last) {
                        if (label_info.kind == LabelKind::Inline) {
                            int position = 0;
                            switch (config.label_attach) {
                                case LabelAttach::Start:
                                    position = label_info.label.span
                                                   ->start();
                                    break;
                                case LabelAttach::Middle:
                                    position = (label_info.label.span
                                                    ->start()
                                                + label_info.label.span
                                                      ->end())
                                             / 2;
                                    break;
                                case LabelAttach::End:
                                    position = label_info.label
                                                   .last_offset();
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
                            return label->span->contains(
                                line.span().first);
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

                // Should we draw a vertical bar as part of a label arrow
                // on this line?
                auto get_vbar = [&](int col, int row) -> LineLabel* {
                    auto it = std::find_if(
                        line_labels.begin(),
                        line_labels.end(),
                        [&](const auto& ll) {
                            return ll.label.msg
                                && (!margin_label.has_value()
                                    || ll.label != margin_label->label)
                                && ll.col == col
                                && ((row <= &ll - &line_labels[0]
                                     && !ll.multi)
                                    || (row <= &ll - &line_labels[0]
                                        && ll.multi));
                        });
                    return it != line_labels.end() ? &(*it) : nullptr;
                };

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

                auto get_underline = [&](int col) -> LineLabel* {
                    Vec<LineLabel>::iterator it = std::min_element(
                        line_labels.begin(),
                        line_labels.end(),
                        [&](const auto& a, const auto& b) {
                            return std::make_tuple(
                                       -a.label.priority,
                                       a.label.span->len())
                                 < std::make_tuple(
                                       -b.label.priority,
                                       b.label.span->len());
                        });

                    return (it != line_labels.end() && config.underlines
                            && !it->multi
                            && it->label.span->contains(line.offset + col))
                             ? &(*it)
                             : nullptr;
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
                //                write_margin(
                //                    w,
                //                    idx,
                //                    true,
                //                    is_ellipsis,
                //                    true,
                //                    std::nullopt,
                //                    line_labels,
                //                    margin_label);

                // Line
                if (!is_ellipsis) {
                    int col = 0;
                    for (QChar c : line.chars) {
                        auto highlight   = get_highlight(col);
                        auto color       = highlight
                                             ? highlight->color
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
                        //                        write_margin(
                        //                            w,
                        //                            idx,
                        //                            false,
                        //                            is_ellipsis,
                        //                            true,
                        //                            std::make_optional(std::make_pair(row,
                        //                            false)), line_labels,
                        //                            margin_label);

                        // Lines alternate
                        auto chars = line.chars.begin();
                        for (int col = 0; col < arrow_len; ++col) {
                            int width = (chars != line.chars.end())
                                          ? config.char_width(*chars, col)
                                                .second
                                          : 1;

                            auto vbar = get_vbar(col, row);

                            // let underline =
                            // get_underline(col).filter(|_| row == 0); I
                            // think it translates like this, but fuck this
                            // Rust garbage
                            LineLabel* underline = nullptr;
                            if (row == 0) {
                                if (LineLabel* tmp = get_underline(col)) {
                                    underline = tmp;
                                }
                            }

                            std::array<QChar, 2> ct_array;
                            if (auto vbar_ll = vbar) {
                                std::array<QChar, 2> ct_inner;
                                if (underline) {
                                    // TODO: Is this good?
                                    if (vbar_ll->label.span->len() <= 1
                                        || true) {
                                        ct_inner = {
                                            draw.underbar, draw.underline};
                                    } else if (
                                        line.offset + col
                                        == vbar_ll->label.span->start()) {
                                        ct_inner = {
                                            draw.ltop, draw.underbar};
                                    } else if (
                                        line.offset + col
                                        == vbar_ll->label.last_offset()) {
                                        ct_inner = {
                                            draw.rtop, draw.underbar};
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
                                    fg(draw.underline,
                                       underline->label.color),
                                    fg(draw.underline,
                                       underline->label.color)};
                            } else {
                                ct_array = {
                                    fg(' ', std::nullopt),
                                    fg(' ', std::nullopt)};
                            }

                            for (int i = 0; i < width; ++i) {
                                w
                                    << ((i == 0) ? ct_array[0]
                                                 : ct_array[1]);
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
                    //                    write_margin(
                    //                        w,
                    //                        idx,
                    //                        false,
                    //                        is_ellipsis,
                    //                        true,
                    //                        std::make_optional(std::make_pair(row,
                    //                        true)), line_labels,
                    //                        margin_label);

                    // Lines
                    auto chars = line.chars.begin();
                    for (int col = 0; col < arrow_len; ++col) {
                        int width = (chars != line.chars.end())
                                      ? config.char_width(*chars, col)
                                            .second
                                      : 1;

                        bool is_hbar = (((col > line_label.col)
                                         ^ line_label.multi)
                                        || (line_label.label.msg
                                            && line_label.draw_msg
                                            && col > line_label.col))
                                    && line_label.label.msg;
                        std::array<QChar, 2> ct_array;
                        if (col == line_label.col && line_label.label.msg
                            && (!margin_label.has_value()
                                || line_label.label
                                       != margin_label->label)) {
                            ct_array = {
                                fg((line_label.multi
                                        ? (line_label.draw_msg ? draw.mbot
                                                               : draw.rbot)
                                        : draw.lbot),
                                   line_label.label.color),
                                fg(draw.hbar, line_label.label.color),
                            };
                        } else if (LineLabel* vbar_ll = nullptr;
                                   (vbar_ll = get_vbar(col, row))
                                   && (col != line_label.col
                                       || line_label.label.msg)) {
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
                                    fg((vbar_ll->multi && row == 0
                                                && config.compact
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
                    //                    write_margin(
                    //                        w,
                    //                        0,
                    //                        false,
                    //                        false,
                    //                        true,
                    //                        std::make_pair(0, false),
                    //                        {},
                    //                        std::nullopt);
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
                //                write_margin(
                //                    w,
                //                    0,
                //                    false,
                //                    false,
                //                    true,
                //                    std::make_pair(0, false),
                //                    {},
                //                    std::nullopt);
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
                    //                    write_margin(
                    //                        w,
                    //                        0,
                    //                        false,
                    //                        false,
                    //                        true,
                    //                        std::make_pair(0, false),
                    //                        {},
                    //                        std::nullopt);
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
                //                write_margin(
                //                    w,
                //                    0,
                //                    false,
                //                    false,
                //                    true,
                //                    std::make_pair(0, false),
                //                    {},
                //                    std::nullopt);
                w << "Note"
                  << ": " << note.value() << "\n";
            }

            // Tail of report
            if (!config.compact) {
                if (is_final_group) {
                    w << QString(draw.hbar).repeated(line_no_width + 2)
                      << draw.rbot << "\n";
                } else {
                    w << QString(" ").repeated(line_no_width + 2)
                      << draw.vbar << "\n";
                }
            }
        }
    }
};
