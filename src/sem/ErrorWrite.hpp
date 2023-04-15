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
    inline int get_offset() const { return offset; }

    // Get the character length of this line.
    inline int get_len() const { return len; }

    // Get the offset Codespan of this line in the original `Source`.
    inline Slice<int> span() const { return {offset, offset + len}; }
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
    inline void add(Id id, QString const& source) {
        sources[id] = std::make_shared<Source>(source);
    }

    inline std::shared_ptr<Source> fetch(const Id& id) override {
        return sources.at(id);
    }

    inline std::optional<QString> display(const Id& id) const override {
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
    inline Label with_message(const QString& msg) {
        this->msg = msg;
        return *this;
    }

    // Give this label a highlight color
    inline Label with_color(const Color& color) {
        this->color = color;
        return *this;
    }

    // Specify the order of this label relative to other labels
    inline Label with_order(int32_t order) {
        this->order = order;
        return *this;
    }

    // Specify the priority of this label relative to other labels
    inline Label with_priority(int32_t priority) {
        this->priority = priority;
        return *this;
    }

    inline Label(const std::shared_ptr<CodeSpan>& Codespan)
        : span(Codespan), msg(""), color(Color()), order(0), priority(0) {}

    std::shared_ptr<CodeSpan> span;
    std::optional<QString>    msg;
    Color                     color;
    int32_t                   order;
    int32_t                   priority;

    bool operator==(Label const& other) const { return msg == other.msg; }

    inline int last_offset() const {
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
        , tab_width(4) {}

    inline Config& with_cross_gap(bool cross_gap) {
        this->cross_gap = cross_gap;
        return *this;
    }

    inline Config& with_label_attach(LabelAttach label_attach) {
        this->label_attach = label_attach;
        return *this;
    }

    inline Config& with_compact(bool compact) {
        this->compact = compact;
        return *this;
    }

    inline Config& with_underlines(bool underlines) {
        this->underlines = underlines;
        return *this;
    }

    inline Config& with_multiline_arrows(bool multiline_arrows) {
        this->multiline_arrows = multiline_arrows;
        return *this;
    }

    inline Config& with_color(bool color) {
        this->color = color;
        return *this;
    }

    inline Config& with_tab_width(int tab_width) {
        this->tab_width = tab_width;
        return *this;
    }

    inline Config& with_char_set(MessageCharSet char_set) {
        this->char_set = char_set;
        return *this;
    }

    inline std::optional<Color> error_color() {
        return color ? std::make_optional(Color::Red) : std::nullopt;
    }

    inline std::optional<Color> warning_color() {
        return color ? std::make_optional(Color::Yellow) : std::nullopt;
    }

    inline std::optional<Color> advice_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    inline std::optional<Color> margin_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    inline std::optional<Color> unimportant_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    inline std::optional<Color> note_color() {
        return color ? std::make_optional(Color::Fixed) : std::nullopt;
    }

    std::pair<QChar, int> char_width(QChar c, int col) const {
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
    bool           underlines = true;
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
    inline Report& with_code(const QString& code) {
        this->code = code;
        return *this;
    }

    // Set the message of this report.
    inline void set_message(const QString& msg) { this->msg = msg; }

    // Add a message to this report.
    inline Report& with_message(const QString& msg) {
        set_message(msg);
        return *this;
    }

    // Set the note of this report.
    inline void set_note(const QString& note) { this->note = note; }

    // Set the note of this report.
    inline Report& with_note(const QString& note) {
        set_note(note);
        return *this;
    }

    // Set the help message of this report.
    inline void set_help(const QString& help) { this->help = help; }

    // Set the help message of this report.
    Report& with_help(const QString& help) {
        set_help(help);
        return *this;
    }

    // Add a label to the report.
    inline void add_label(const Label& label) { labels.push_back(label); }

    // Add multiple labels to the report.
    template <typename Container>
    void add_labels(const Container& labels) {
        this->labels.insert(
            this->labels.end(), labels.begin(), labels.end());
    }

    // Add a label to the report.
    inline Report& with_label(const Label& label) {
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
    inline Report& with_config(const Config& config) {
        this->config = config;
        return *this;
    }

    inline Report(ReportKind kind, Id id, int offset)
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


    inline void write(Cache& cache, QTextStream& w) {
        write_for_stream(cache, w);
    }

    // Write this diagnostic out to stderr.
    inline void eprint(Cache& cache) { write(cache, qcout); }

    // Write this diagnostic out to stdout.
    // In most cases, eprint is the more correct function to use.
    inline void print(Cache& cache) { write(cache, qcout); }


    void write_for_stream(Cache& cache, QTextStream& w);
};
