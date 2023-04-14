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
    virtual std::size_t start() const = 0;

    // Get the (exclusive) end offset of this Codespan.
    // The end offset should *always* be greater than or equal to the start
    // offset as given by CodeSpan::start(). Offsets are zero-indexed
    // character offsets from the beginning of the source.
    virtual std::size_t end() const = 0;

    // Get the length of this Codespan (difference between the start of the
    // Codespan and the end of the Codespan).
    std::size_t len() const { return end() - start(); }

    // Determine whether the Codespan contains the given offset.
    bool contains(std::size_t offset) const {
        return start() <= offset && offset < end();
    }
};

// CodeSpan implementation for Range<usize>
class RangeCodeSpan : public CodeSpan {
  public:
    explicit RangeCodeSpan(std::pair<size_t, size_t> range)
        : range_(range) {}

    virtual const Id source() const override { return -1; }
    std::size_t      start() const override { return range_.first; }
    std::size_t      end() const override { return range_.second; }

  private:
    std::pair<size_t, size_t> range_;
};

// CodeSpan implementation for (Id, Range<usize>)
class TupleCodeSpan : public CodeSpan {
  public:
    explicit TupleCodeSpan(Id id, std::pair<size_t, size_t> range)
        : id_(std::move(id)), range_(range) {}

    const Id    source() const override { return id_; }
    std::size_t start() const override { return range_.first; }
    std::size_t end() const override { return range_.second; }

  private:
    Id                        id_;
    std::pair<size_t, size_t> range_;
};

class Cache {
  public:
    // Fetch the `Source` identified by the given ID, if possible.
    // TODO: Don't box
    virtual std::shared_ptr<Source> fetch(Id const& id) = 0;

    // Display the given ID. as a single inline value.
    virtual std::optional<std::string> display(Id const& id) const = 0;
};


// A type representing a single line of a `Source`.
struct Line {
    size_t      offset;
    size_t      len;
    std::string chars;

    // Get the offset of this line in the original `Source` (i.e: the
    // number of characters that precede it).
    size_t get_offset() const { return offset; }

    // Get the character length of this line.
    size_t get_len() const { return len; }

    // Get the offset Codespan of this line in the original `Source`.
    std::pair<size_t, size_t> Codespan() const {
        return {offset, offset + len};
    }

    // Return an iterator over the characters in the line, excluding
    // trailing whitespace.
    // TODO: Implement the iterator for `Line` class
};

// A type representing a single source that may be referred to by
// `CodeSpan`s.
//
// In most cases, a source is a single input file.
struct Source {
    std::vector<Line> lines;
    size_t            len;

    Source(std::string const& l) {
        std::istringstream iss(l);
        size_t             offset = 0;
        for (std::string line; std::getline(iss, line);) {
            Line l{
                .offset = offset,
                .len    = line.size() + 1,
                .chars  = line,
            };

            offset += l.len;
            lines.push_back(l);
        }
    }

    struct OffsetLine {
        const Line& line;
        size_t      idx = 0;
        size_t      col = 0;
    };

    // Get access to a specific, zero-indexed Line.
    std::optional<Line> line(size_t idx) const {
        if (idx < lines.size()) {
            return std::cref(lines[idx]);
        } else {
            return std::nullopt;
        }
    }

    // Get the line that the given offset appears on, and the line/column
    // numbers of the offset. Note that the line/column numbers are
    // zero-indexed.
    std::optional<OffsetLine> get_offset_line(size_t offset) {
        if (offset <= len) {
            auto it = std::lower_bound(
                lines.begin(),
                lines.end(),
                offset,
                [](const Line& line, size_t offset) {
                    return line.offset < offset;
                });
            if (it != lines.begin()) {
                --it;
            }
            size_t      idx  = std::distance(lines.begin(), it);
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
    std::pair<size_t, size_t> get_line_range(const CodeSpan& Codespan) {
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
    void add(Id id, std::string const& source) {
        sources[id] = std::make_shared<Source>(source);
    }
    std::shared_ptr<Source> fetch(const Id& id) override {
        return sources.at(id);
    }
    std::optional<std::string> display(const Id& id) const override {
        return "";
    }
};

struct Characters {
    wchar_t hbar;
    wchar_t vbar;
    wchar_t xbar;
    wchar_t vbar_break;
    wchar_t vbar_gap;

    wchar_t uarrow;
    wchar_t rarrow;

    wchar_t ltop;
    wchar_t mtop;
    wchar_t rtop;
    wchar_t lbot;
    wchar_t rbot;
    wchar_t mbot;

    wchar_t lbox;
    wchar_t rbox;

    wchar_t lcross;
    wchar_t rcross;

    wchar_t underbar;
    wchar_t underline;
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
    Label with_message(const std::string& msg) {
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
        : Codespan(Codespan)
        , msg("")
        , color(Color())
        , order(0)
        , priority(0) {}

    std::shared_ptr<CodeSpan> Codespan;
    std::string               msg;
    Color                     color;
    int32_t                   order;
    int32_t                   priority;

    bool operator==(Label const& other) const { return msg == other.msg; }

    size_t last_offset() const {
        return std::max(Codespan->end() - 1, Codespan->start());
    }
};

bool contains(std::pair<size_t, size_t> range, size_t point) {
    return range.first <= point && point <= range.second;
}


// struct LabelInfo<'a, S> {
//     kind: LabelKind,
//     label: &'a Label<S>,
// }

struct LabelInfo {
    LabelKind   kind;
    const Label label;
};

// struct SourceGroup<'a, S: CodeSpan> {
//     src_id: &'a S::SourceId,
//     Codespan: Range<usize>,
//     labels: Vec<LabelInfo<'a, S>>,
// }

struct SourceGroup {
    Id                                  src_id;
    std::pair<std::size_t, std::size_t> Codespan; // Replacing Range<usize>
                                                  // with a pair of size_t
    std::vector<LabelInfo> labels;
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
        , char_set(MessageCharSet::Unicode) {}

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

    Config& with_tab_width(size_t tab_width) {
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

    std::pair<char, std::size_t> char_width(char c, std::size_t col) {
        if (c == '\t') {
            // Find the column that the tab should end at
            std::size_t tab_end = (col / tab_width + 1) * tab_width;
            return std::make_pair(' ', tab_end - col);
        } else if (std::isspace(c)) {
            return std::make_pair(' ', 1);
        } else {
            // Assuming you have a function called 'width()' to get the
            // character width.
            std::size_t char_width = 1;
            return std::make_pair(c, char_width);
        }
    }


    bool           cross_gap;
    LabelAttach    label_attach;
    bool           compact;
    bool           underlines;
    bool           multiline_arrows;
    bool           color;
    size_t         tab_width;
    MessageCharSet char_set;
};

auto fg = [](wchar_t ch, std::optional<Color> col) { return ch; };

class Report {
  public:
    ReportKind                 kind;
    std::optional<std::string> code;
    std::optional<std::string> msg;
    std::optional<std::string> note;
    std::optional<std::string> help;
    std::pair<Id, std::size_t> location;
    std::vector<Label>         labels;
    Config                     config;


    // Give this report a numerical code that may be used to more precisely
    // look up the error in documentation.
    Report& with_code(const std::string& code) {
        this->code = code;
        return *this;
    }

    // Set the message of this report.
    void set_message(const std::string& msg) { this->msg = msg; }

    // Add a message to this report.
    Report& with_message(const std::string& msg) {
        set_message(msg);
        return *this;
    }

    // Set the note of this report.
    void set_note(const std::string& note) { this->note = note; }

    // Set the note of this report.
    Report& with_note(const std::string& note) {
        set_note(note);
        return *this;
    }

    // Set the help message of this report.
    void set_help(const std::string& help) { this->help = help; }

    // Set the help message of this report.
    Report& with_help(const std::string& help) {
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

    std::vector<SourceGroup> get_source_groups(Cache* cache) {
        std::vector<SourceGroup> groups;
        for (const auto& label : labels) {
            auto src_display = cache->display(label.Codespan->source());
            std::shared_ptr<Source> src = cache->fetch(
                label.Codespan->source());
            if (!src) {
                continue;
            }

            assert(label.Codespan->start() <= label.Codespan->end());

            // "Label start is after its end");
            auto start_line = src->get_offset_line(label.Codespan->start())
                                  .value()
                                  .idx;

            auto end_line = src
                                ->get_offset_line(std::max(
                                    label.Codespan->end() - 1,
                                    label.Codespan->start()))
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
                    return group.src_id == label.Codespan->source();
                });

            if (group_it != groups.end()) {
                group_it->Codespan.first = std::min(
                    group_it->Codespan.first, label.Codespan->start());
                group_it->Codespan.second = std::max(
                    group_it->Codespan.second, label.Codespan->end());
                group_it->labels.push_back(label_info);
            } else {
                groups.push_back(SourceGroup{
                    .src_id   = label.Codespan->source(),
                    .Codespan = std::make_pair(
                        label.Codespan->start(), label.Codespan->end()),
                    .labels = {label_info}});
            }
        }
        return groups;
    }


    void write(Cache& cache, std::ostream& w) {
        write_for_stream(cache, w);
    }

    // Write this diagnostic out to stderr.
    void eprint(Cache& cache) { write(cache, std::cerr); }

    // Write this diagnostic out to stdout.
    // In most cases, eprint is the more correct function to use.
    void print(Cache& cache) { write(cache, std::cout); }


    void write_for_stream(Cache& cache, std::ostream& w) {
        Characters draw;
        switch (config.char_set) {
            case MessageCharSet::Unicode: draw = unicode(); break;
            case MessageCharSet::Ascii: draw = ascii(); break;
        }

        // --- Header ---
        std::optional<std::string> code;
        if (code.has_value()) {
            code = "[" + *code + "] ";
        }
        std::string id = "TODO_FORMAT"; // fmt::format("{}{}:", code,
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
            std::string src_name = cache.display(group.src_id)
                                       .value_or("<unknown>");

            try {
                auto src = cache.fetch(group.src_id);

                auto line_range = src->get_line_range(
                    RangeCodeSpan(group.Codespan));
                int width = 0;
                for (uint32_t x = 1, y = 1; line_range.second / y != 0;
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

            std::string src_name = cache.display(src_id).value_or(
                "<unknown>");

            std::shared_ptr<Source> src;
            try {
                src = cache.fetch(src_id);
            } catch (const std::exception& e) {
                std::cerr << "Unable to fetch source " << src_name << ": "
                          << e.what() << std::endl;
                continue;
            }

            std::pair<size_t, size_t> line_range = src->get_line_range(
                RangeCodeSpan(Codespan));

            // File name & reference
            size_t location = (src_id == this->location.first)
                                ? this->location.second
                                : labels[0].label.Codespan->start();

            auto offset_line = src->get_offset_line(location);
            std::pair<std::string, std::string> line_col;
            if (offset_line) {
                //                line_col = {fmt::format("{}",
                //                offset_line->idx + 1), fmt::format("{}",
                //                offset_line->col + 1)};
            } else {
                line_col = {"?", "?"};
            }

            if (!config.compact) {}

            struct LineLabel {
                size_t col;
                Label  label;
                bool   multi;
                bool   draw_msg;
            };

            // Generate a list of multi-line labels
            std::vector<const Label*> multi_labels;
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
                    return (a->Codespan->len()) > (b->Codespan->len());
                });


            auto write_margin = [&](std::ostream& w,
                                    size_t        idx,
                                    bool          is_line,
                                    bool          is_ellipsis,
                                    bool          draw_labels,
                                    std::optional<std::pair<size_t, bool>>
                                        report_row,
                                    const std::vector<LineLabel>&
                                        line_labels,
                                    const std::optional<LineLabel>&
                                        margin_label) {
                if (draw_labels) {
                    for (size_t col = 0;
                         col
                         < multi_labels.size() + (multi_labels.size() > 0);
                         ++col) {
                        std::optional<std::pair<const Label*, bool>>
                                                    corner = std::nullopt;
                        std::optional<const Label*> hbar   = std::nullopt;
                        std::optional<const Label*> vbar   = std::nullopt;
                        std::optional<std::pair<const LineLabel*, bool>>
                            margin_ptr = std::nullopt;

                        const Label* multi_label   = (col
                                                    < multi_labels.size())
                                                       ? &multi_label[col]
                                                       : nullptr;
                        auto         line_Codespan = src->line(idx)
                                                 .value()
                                                 .Codespan();

                        for (size_t i = 0;
                             i < std::min(col + 1, multi_labels.size());
                             ++i) {
                            const auto& label  = multi_label[i];
                            auto        margin = margin_label
                                                   ? (label == margin_label->label
                                                          ? &(*margin_label)
                                                          : nullptr)
                                                   : nullptr;

                            if (label.Codespan->start()
                                    <= line_Codespan.second
                                && line_Codespan.first
                                       < label.Codespan->end()) {
                                bool is_parent = i != col;
                                bool is_start  = contains(
                                    line_Codespan,
                                    label.Codespan->start());
                                bool is_end = contains(
                                    line_Codespan, label.last_offset());

                                if (margin && is_line) {
                                    margin_ptr = std::make_pair(
                                        margin, is_start);
                                } else if (
                                    !is_start && (!is_end || is_line)) {
                                    vbar = vbar ? vbar
                                                : (!is_parent ? &label
                                                              : nullptr);
                                } else if (report_row.has_value()) {
                                    auto report_row_value = report_row
                                                                .value();
                                    size_t label_row = 0;
                                    for (size_t r = 0;
                                         r < line_labels.size();
                                         ++r) {
                                        if (label
                                            == line_labels[r].label) {
                                            label_row = r;
                                            break;
                                        }
                                    }

                                    if (report_row_value.first
                                        == label_row) {
                                        if (margin) {
                                            vbar = (col == i)
                                                     ? &margin->label
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
                                                        : (!is_parent
                                                               ? &label
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
                            margin_ptr_value.has_value() && is_line) {
                            auto [margin, _is_start] = *margin_ptr_value;
                            bool is_col              = multi_label
                                                         ? (*multi_label
                                               == margin->label)
                                                         : false;
                            bool is_limit = col + 1 == multi_labels.size();
                            if (!is_col && !is_limit) {
                                hbar = hbar.value_or(&margin->label);
                            }
                        }

                        if (hbar.has_value()) {
                            hbar = **hbar != margin_label->label
                                        || !is_line
                                     ? hbar
                                     : std::nullopt;
                        }

                        std::pair<wchar_t, wchar_t> ab;

                        if (auto corner_value = corner;
                            corner_value.has_value()) {
                            auto [label, is_start] = *corner_value;
                            ab                     = {
                                is_start ? fg(draw.ltop, label->color)
                                                             : fg(draw.lbot, label->color),
                                fg(draw.hbar, label->color),
                            };
                        } else if (auto label = hbar.value();
                                   vbar.has_value() && !config.cross_gap) {
                            ab = {
                                fg(draw.xbar, label->color),
                                fg(draw.hbar, label->color)};
                        } else if (hbar.has_value()) {
                            auto label = hbar.value();
                            ab         = {
                                fg(draw.hbar, label->color),
                                fg(draw.hbar, label->color),
                            };
                        } else if (vbar.has_value()) {
                            auto label = vbar.value();
                            ab         = {
                                is_ellipsis
                                            ? fg(draw.vbar_gap, label->color)
                                            : fg(draw.vbar, label->color),
                                fg(' ', Color::Default),
                            };
                        } else if (auto margin_ptr_value = margin_ptr;
                                   margin_ptr_value.has_value()
                                   && is_line) {
                            auto [margin, is_start] = *margin_ptr_value;
                            bool is_col             = multi_label
                                                        ? (*multi_label
                                               == margin->label)
                                                        : false;
                            bool is_limit = col == multi_labels.size();
                            ab            = {
                                is_limit
                                               ? fg(draw.rarrow, margin->label.color)
                                           : is_col
                                               ? (is_start ? fg(
                                           draw.ltop, margin->label.color)
                                                           : fg(
                                                    draw.lcross,
                                                    margin->label.color))
                                               : fg(draw.hbar, margin->label.color),
                                !is_limit
                                    ? fg(draw.hbar, margin->label.color)
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


            bool is_ellipsis = false;
            for (size_t idx = line_range.first; idx <= line_range.second;
                 ++idx) {
                auto line_opt = src->line(idx);
                if (!line_opt) {
                    continue;
                }

                Line line = line_opt.value();

                std::optional<LineLabel> margin_label;
                int min_key = std::numeric_limits<int>::max();
                for (size_t i = 0; i < multi_labels.size(); ++i) {
                    const Label* label    = multi_labels[i];
                    bool         is_start = contains(
                        line.Codespan(), label->Codespan->start());
                    bool is_end = contains(
                        line.Codespan(), label->last_offset());

                    if (is_start || is_end) {
                        LineLabel ll{
                            .col = (is_start ? label->Codespan->start()
                                             : label->last_offset())
                                 - line.offset,
                            .label    = *label,
                            .multi    = true,
                            .draw_msg = is_end,
                        };


                        int key = (ll.col << 1)
                                | (!label->Codespan->start());
                        if (key < min_key) {
                            min_key      = key;
                            margin_label = ll;
                        }
                    }
                }

                std::vector<LineLabel> line_labels;
                for (const Label* label : multi_labels) {
                    bool is_start = contains(
                        line.Codespan(), label->Codespan->start());
                    bool is_end = contains(
                        line.Codespan(), label->last_offset());
                    bool different_from_margin_label
                        = (!margin_label.has_value()
                           || reinterpret_cast<const void*>(label)
                                  != reinterpret_cast<const void*>(
                                      &margin_label->label));

                    if ((is_start && different_from_margin_label)
                        || is_end) {
                        LineLabel ll{
                            .col = (is_start ? label->Codespan->start()
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
                    if (label_info.label.Codespan->start()
                            >= line.Codespan().first
                        && label_info.label.Codespan->end()
                               <= line.Codespan().second) {
                        if (label_info.kind == LabelKind::Inline) {
                            size_t position = 0;
                            switch (config.label_attach) {
                                case LabelAttach::Start:
                                    position = label_info.label.Codespan
                                                   ->start();
                                    break;
                                case LabelAttach::Middle:
                                    position = (label_info.label.Codespan
                                                    ->start()
                                                + label_info.label
                                                      .Codespan->end())
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
                                           label_info.label.Codespan
                                               ->start())
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
                            return label->Codespan->contains(
                                line.Codespan().first);
                        });
                    if (!is_ellipsis && within_label) {
                        is_ellipsis = true;
                    } else {
                        if (!config.compact && !is_ellipsis) {
                            write_margin(
                                w,
                                idx,
                                false,
                                is_ellipsis,
                                false,
                                std::nullopt,
                                {},
                                std::nullopt);
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
                                   !a.label.Codespan->start())
                             < std::make_tuple(
                                   b.label.order,
                                   b.col,
                                   !b.label.Codespan->start());
                    });

                // Determine label bounds so we know where to put error
                // messages
                int    arrow_end_space = config.compact ? 1 : 2;
                size_t arrow_len       = std::accumulate(
                                       line_labels.begin(),
                                       line_labels.end(),
                                       0,
                                       [&](size_t l, const auto& ll) {
                                           if (ll.multi) {
                                               return line.get_len();
                                           } else {
                                               return std::max(
                                                   l,
                                                   ll.label.Codespan->end()
                                                       - line.offset);
                                           }
                                       })
                                 + arrow_end_space;

                // Should we draw a vertical bar as part of a label arrow
                // on this line?
                auto get_vbar = [&](size_t col, size_t row) -> LineLabel* {
                    auto it = std::find_if(
                        line_labels.begin(),
                        line_labels.end(),
                        [&](const auto& ll) {
                            return !ll.label.msg.empty()
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

                auto get_highlight = [&](size_t col) {
                    std::vector<const Label*> candidates;

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
                                       -a->priority, a->Codespan->len())
                                 < std::make_tuple(
                                       -b->priority, b->Codespan->len());
                        });

                    return (it != candidates.end()
                            && (*it)->Codespan->contains(
                                line.offset + col))
                             ? *it
                             : nullptr;
                };

                auto get_underline = [&](size_t col) -> LineLabel* {
                    std::vector<LineLabel>::iterator it = std::min_element(
                        line_labels.begin(),
                        line_labels.end(),
                        [&](const auto& a, const auto& b) {
                            return std::make_tuple(
                                       -a.label.priority,
                                       a.label.Codespan->len())
                                 < std::make_tuple(
                                       -b.label.priority,
                                       b.label.Codespan->len());
                        });

                    return (it != line_labels.end() && config.underlines
                            && !it->multi
                            && it->label.Codespan->contains(
                                line.offset + col))
                             ? &(*it)
                             : nullptr;
                };

                // Margin
                write_margin(
                    w,
                    idx,
                    true,
                    is_ellipsis,
                    true,
                    std::nullopt,
                    line_labels,
                    margin_label);

                // Line
                if (!is_ellipsis) {
                    int col = 0;
                    for (char c : line.chars) {
                        auto highlight   = get_highlight(col);
                        auto color       = highlight
                                             ? highlight->color
                                             : config.unimportant_color();
                        auto [wc, width] = config.char_width(c, col);

                        if (std::isspace(c)) {
                            for (int i = 0; i < width; ++i) {
                                //                                w <<
                                //                                fg(wc,
                                //                                color);
                            }
                        } else {
                            //                            w << fg(wc,
                            //                            color);
                        }

                        col++;
                    }
                }
                w << "\n";

                for (std::size_t row = 0; row < line_labels.size();
                     ++row) {
                    const auto& line_label = line_labels[row];

                    if (!config.compact) {
                        // Margin alternate
                        write_margin(
                            w,
                            idx,
                            false,
                            is_ellipsis,
                            true,
                            std::make_optional(std::make_pair(row, false)),
                            line_labels,
                            margin_label);

                        // Lines alternate
                        auto chars = line.chars.begin();
                        for (std::size_t col = 0; col < arrow_len; ++col) {
                            int width = (chars != line.chars.end())
                                          ? config.char_width(*chars, col)
                                                .second
                                          : 1;

                            auto vbar = get_vbar(col, row);

                            // let underline =
                            // get_underline(col).filter(|_| row == 0); I
                            // think it translates like this, but fuck this
                            // Rust garbage
                            LineLabel* underline;
                            if (row == 0) {
                                if (LineLabel* tmp = get_underline(col)) {
                                    underline = tmp;
                                }
                            }

                            std::array<wchar_t, 2> ct_array;
                            if (auto vbar_ll = vbar) {
                                std::array<wchar_t, 2> ct_inner;
                                if (underline) {
                                    // TODO: Is this good?
                                    if (vbar_ll->label.Codespan->len() <= 1
                                        || true) {
                                        ct_inner = {
                                            draw.underbar, draw.underline};
                                    } else if (
                                        line.offset + col
                                        == vbar_ll->label.Codespan
                                               ->start()) {
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
                                //                                w << ((i
                                //                                == 0) ?
                                //                                ct_array[0]
                                //                                :
                                //                                ct_array[1]);
                            }

                            if (chars != line.chars.end()) {
                                ++chars;
                            }
                        }
                        w << "\n";
                    }

                    // Margin
                    write_margin(
                        w,
                        idx,
                        false,
                        is_ellipsis,
                        true,
                        std::make_optional(std::make_pair(row, true)),
                        line_labels,
                        margin_label);

                    // Lines
                    auto chars = line.chars.begin();
                    for (std::size_t col = 0; col < arrow_len; ++col) {
                        int width = (chars != line.chars.end())
                                      ? config.char_width(*chars, col)
                                            .second
                                      : 1;

                        bool is_hbar = (((col > line_label.col)
                                         ^ line_label.multi)
                                        || (!line_label.label.msg.empty()
                                            && line_label.draw_msg
                                            && col > line_label.col))
                                    && !line_label.label.msg.empty();
                        std::array<wchar_t, 2> ct_array;
                        if (col == line_label.col
                            && !line_label.label.msg.empty()
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
                                       || !line_label.label.msg.empty())) {
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
                            //                            w << ct_array[0];
                        }
                        for (int i = 1; i < width; ++i) {
                            //                            w << ct_array[1];
                        }

                        if (chars != line.chars.end()) {
                            ++chars;
                        }
                    }

                    if (line_label.draw_msg) {
                        //                        w << " " <<
                        //                        show(line_label.label.msg.value());
                    }
                    w << "\n";
                }
            }

            bool is_final_group = group_idx + 1 == groups.size();

            // Help
            if (help.has_value() && is_final_group) {
                if (!config.compact) {
                    write_margin(
                        w,
                        0,
                        false,
                        false,
                        true,
                        std::make_pair(0, false),
                        {},
                        std::nullopt);
                    w << "\n";
                }
                write_margin(
                    w,
                    0,
                    false,
                    false,
                    true,
                    std::make_pair(0, false),
                    {},
                    std::nullopt);
                //                w << "Help".fg(self.config.note_color())
                //                << ": " << self.help.value() << "\n";
            }

            // Note
            if (note.has_value() && is_final_group) {
                if (!config.compact) {
                    write_margin(
                        w,
                        0,
                        false,
                        false,
                        true,
                        std::make_pair(0, false),
                        {},
                        std::nullopt);
                    //                    w << "\n";
                }
                write_margin(
                    w,
                    0,
                    false,
                    false,
                    true,
                    std::make_pair(0, false),
                    {},
                    std::nullopt);
                //                w << "Note" << fg(config.note_color()) <<
                //                ": " << note.value() << "\n";
            }

            // Tail of report
            if (!config.compact) {
                if (is_final_group) {
                    //                    std::string final_margin =
                    //                    show(std::make_pair(draw.hbar,
                    //                    line_no_width + 2))
                    //                    + show(draw.rbot); w <<
                    //                    final_margin.fg(config.margin_color())
                    //                    << "\n";
                } else {
                    //                    w << show(std::make_pair(' ',
                    //                    line_no_width + 2)) <<
                    //                    draw.vbar.fg(self.config.margin_color())
                    //                    << "\n";
                }
            }
        }
    }
};
