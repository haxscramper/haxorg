#pragma once

#include "hstd/stdlib/Slice.hpp"
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <functional>
#include <optional>
#include <iostream>
#include <algorithm>

#include <hstd/stdlib/Vec.hpp>

#include <boost/describe.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/ColText.hpp>

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
    virtual std::optional<std::string> display(Id const& id) const = 0;
};


// A type representing a single line of a `Source`.
struct Line {
    int         offset;
    int         len;
    std::string chars;

    // Get the offset of this line in the original `Source` (i.e: the
    // number of characters that precede it).
    inline int get_offset() const { return offset; }

    // Get the character length of this line.
    inline int get_len() const { return len; }

    // Get the offset Codespan of this line in the original `Source`.
    inline Slice<int> span() const { return {offset, offset + len}; }
};

BOOST_DESCRIBE_STRUCT(Line, (), (offset, len, chars));

template <>
struct std::formatter<Line> : std::formatter<std::string> {
    template <typename FormatContext>
    typename FormatContext::iterator format(
        const Line&    p,
        FormatContext& ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(described_class_printer(p), ctx);
    }
};


// A type representing a single source that may be referred to by
// `CodeSpan`s.
//
// In most cases, a source is a single input file.
struct Source {
    Vec<Line> lines;
    int       len;

    Source(Str const& l) {
        int offset = 0;
        for (std::string const& line : l.split('\n')) {
            Line l{
                .offset = offset,
                .len    = static_cast<int>(line.size()) + 1,
                .chars  = line,
            };

            offset += l.len;
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
    std::optional<OffsetLine> get_offset_line(int offset);

    // Get the range of lines that this Codespan runs across.
    // The resulting range is guaranteed to contain valid line indices
    // (i.e: those that can be used for Source::line()).
    Slice<int> get_line_range(const CodeSpan& span);
};

class StrCache : public Cache {


    // Cache interface
  public:
    UnorderedMap<Id, std::shared_ptr<Source>> sources;
    UnorderedMap<Id, std::string>             names;

    inline void add(
        Id                 id,
        std::string const& source,
        std::string const& name) {
        sources[id] = std::make_shared<Source>(source);
        names[id]   = name;
    }

    inline std::shared_ptr<Source> fetch(const Id& id) override {
        return sources.at(id);
    }

    inline std::optional<std::string> display(
        const Id& id) const override {
        return names.get(id);
    }
};

struct Characters {
    Str hbar;
    Str vbar;
    Str xbar;
    Str vbar_break;
    Str vbar_gap;

    Str uarrow;
    Str rarrow;

    Str ltop;
    Str mtop;
    Str rtop;
    Str lbot;
    Str rbot;
    Str mbot;

    Str lbox;
    Str rbox;

    Str lcross;
    Str rcross;

    Str underbar;
    Str underline;
};

enum LabelKind
{
    Inline,
    Multiline
};

struct Label {
    // Give this label a message
    inline Label with_message(const ColText& msg) {
        this->msg = msg;
        return *this;
    }

    // Give this label a highlight color
    inline Label with_color(const ColStyle& color) {
        this->color = color;
        return *this;
    }

    // Specify the order of this label relative to other labels
    inline Label with_order(int order) {
        this->order = order;
        return *this;
    }

    // Specify the priority of this label relative to other labels
    inline Label with_priority(int priority) {
        this->priority = priority;
        return *this;
    }

    inline Label(const std::shared_ptr<CodeSpan>& Codespan)
        : span(Codespan) {}

    std::shared_ptr<CodeSpan> span     = nullptr;
    std::optional<ColText>    msg      = std::nullopt;
    ColStyle                  color    = ColStyle{};
    int                       order    = 0;
    int                       priority = 0;

    bool operator==(Label const& other) const {
        if (msg.has_value() != other.msg.has_value()) {
            return false;
        } else {
            if (msg && !(msg.value() == other.msg.value())) {
                return false;
            } else {
                return true;
            }
        }
    }

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

    ColStyle error_color       = ColStyle{} + TermColorBg8Bit::Red;
    ColStyle warning_color     = ColStyle{} + TermColorBg8Bit::Yellow;
    ColStyle advice_color      = ColStyle{} + TermColorBg8Bit::Magenta;
    ColStyle margin_color      = ColStyle{} + TermColorBg8Bit::White;
    ColStyle unimportant_color = ColStyle{} + TermColorBg8Bit::Default;
    ColStyle note_color        = ColStyle{} + TermColorBg8Bit::Cyan;

    std::pair<char, int> char_width(char c, int col) const;


    bool           cross_gap;
    LabelAttach    label_attach;
    bool           compact;
    bool           underlines = true;
    bool           multiline_arrows;
    bool           color;
    int            tab_width;
    MessageCharSet char_set = MessageCharSet::Unicode;
};

class Report {
  public:
    ReportKind                 kind     = ReportKind::Error;
    std::optional<std::string> code     = std::nullopt;
    std::optional<ColText>     msg      = std::nullopt;
    std::optional<ColText>     note     = std::nullopt;
    std::optional<ColText>     help     = std::nullopt;
    std::pair<Id, int>         location = {0, 0};
    Vec<Label>                 labels   = {};
    Config                     config   = Config{};


    // Give this report a numerical code that may be used to more precisely
    // look up the error in documentation.
    inline Report& with_code(const std::string& code) {
        this->code = code;
        return *this;
    }

    // Set the message of this report.
    inline void set_message(const ColText& msg) { this->msg = msg; }

    // Add a message to this report.
    inline Report& with_message(const ColText& msg) {
        set_message(msg);
        return *this;
    }

    // Set the note of this report.
    inline void set_note(const ColText& note) { this->note = note; }

    // Set the note of this report.
    inline Report& with_note(const ColText& note) {
        set_note(note);
        return *this;
    }

    // Set the help message of this report.
    inline void set_help(const ColText& help) { this->help = help; }

    // Set the help message of this report.
    Report& with_help(const ColText& help) {
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

    Vec<SourceGroup> get_source_groups(Cache* cache);


    inline void write(Cache& cache, std::ostream& w) {
        write_for_stream(cache, w);
    }

    void write_for_stream(Cache& cache, std::ostream& w);
};
