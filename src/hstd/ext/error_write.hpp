#pragma once

#include "hstd/stdlib/Slice.hpp"
#include <string>
#include <utility>
#include <memory>
#include <functional>
#include <optional>
#include <iostream>

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Map.hpp>

#include <boost/describe.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/ext/bimap_wrap.hpp>
#include <hstd/stdlib/Filesystem.hpp>

namespace hstd::ext {

class Source;

/// \brief A trait implemented by `Source` caches.
using Id = int;

/// \brief A trait implemented by spans within a character-based source.
struct CodeSpan {
    Id         id;
    Slice<int> range;

    /// \brief Get the identifier of the source that this Codespan refers
    /// to.
    const Id source() const { return id; }

    /// Get the start offset of this Codespan.
    /// Offsets are zero-indexed character offsets from the beginning of
    /// the source.
    int start() const { return range.first; }

    /// Get the (exclusive) end offset of this Codespan.
    /// The end offset should *always* be greater than or equal to the
    /// start offset as given by CodeSpan::start(). Offsets are
    /// zero-indexed character offsets from the beginning of the source.
    int end() const { return range.last; }

    /// Get the length of this Codespan (difference between the start of
    /// the Codespan and the end of the Codespan).
    int len() const { return end() - start(); }

    /// Determine whether the Codespan contains the given offset.
    bool contains(int offset) const { return range.contains(offset); }
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
    int offset;
    int len;
    // std::string chars;

    // Get the offset of this line in the original `Source` (i.e: the
    // number of characters that precede it).
    int get_offset() const { return offset; }

    /// \brief Get the character length of this line.
    int get_len() const { return len; }

    /// \brief Get the offset Codespan of this line in the original
    /// `Source`.
    Slice<int> span() const { return {offset, offset + len}; }

    DESC_FIELDS(Line, (offset, len));
};

/// A type representing a single source that may be referred to by
/// `CodeSpan`s.
///
/// In most cases, a source is a single input file.
struct Source {
    Vec<Line> lines;
    int       len;
    ColText   content;

    Source(Str const& l);

    struct OffsetLine {
        const Line& line;
        int         idx = 0;
        int         col = 0;
        DESC_FIELDS(OffsetLine, (idx, col));
    };

    /// \brief Get access to a specific, zero-indexed Line.
    std::optional<Line> line(int idx) const {
        if (idx < lines.size()) {
            return std::cref(lines[idx]);
        } else {
            return std::nullopt;
        }
    }

    /// Get the line that the given offset appears on, and the line/column
    /// numbers of the offset. Note that the line/column numbers are
    /// zero-indexed.
    std::optional<OffsetLine> get_offset_line(int offset);

    /// Get the range of lines that this Codespan runs across.
    /// The resulting range is guaranteed to contain valid line indices
    /// (i.e: those that can be used for Source::line()).
    Slice<int> get_line_range(const CodeSpan& span);

    ColText get_line_text(CR<Line> line);

    DESC_FIELDS(Source, (lines, len));
};

class StrCache : public Cache {

    /// Cache interface
  public:
    UnorderedMap<Id, std::shared_ptr<Source>>      sources;
    hstd::ext::Unordered1to1Bimap<Id, std::string> names;
    std::function<std::string(std::string const&)> getFileSource;

    void add(Id id, std::string const& source, std::string const& name);
    Id   add_path(hstd::fs::path const& path);

    inline std::shared_ptr<Source> fetch(const Id& id) override {
        return sources.at(id);
    }

    inline std::optional<std::string> display(
        const Id& id) const override {
        return names.get_right(id);
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
    /// \brief Give this label a message
    Label& with_message(const ColText& msg) {
        this->msg = msg;
        return *this;
    }

    /// \brief Give this label a highlight color
    Label& with_color(const ColStyle& color) {
        this->color = color;
        return *this;
    }

    /// \brief Specify the order of this label relative to other labels
    Label& with_order(int order) {
        this->order = order;
        return *this;
    }

    /// \brief Specify the priority of this label relative to other labels
    Label& with_priority(int priority) {
        this->priority = priority;
        return *this;
    }

    Label& with_span(Id id, Slice<int> range) {
        this->span = CodeSpan{id, range};
        return *this;
    }


    Label& with_id(int label_id) {
        this->id = label_id;
        return *this;
    }

    Label clone() const { return *this; }

    int                    id;
    CodeSpan               span;
    std::optional<ColText> msg      = std::nullopt;
    ColStyle               color    = ColStyle{};
    int                    order    = 0;
    int                    priority = 0;

    DESC_FIELDS(Label, (span, msg, color, order, priority, id));

    bool operator==(Label const& other) const {
        return this->id == other.id;
    }
};


struct LabelInfo {
    LabelKind kind;
    Label     label;
    DESC_FIELDS(LabelInfo, (kind));
};


struct SourceGroup {
    Id             src_id;
    Slice<int>     span;
    Vec<LabelInfo> labels;
    DESC_FIELDS(SourceGroup, (src_id, span, labels));
};

enum class ReportKind
{
    Error,
    Warning,
    Advice,
    Custom
};

BOOST_DESCRIBE_ENUM(ReportKind, Error, Warning, Advice, Custom);

enum class LabelAttach
{
    /// Arrows should attach to the start of the label Codespan.
    Start,
    /// Arrows should attach to the middle of the label Codespan (or as
    /// close to the middle as we can get).
    Middle,
    /// Arrows should attach to the end of the label Codespan.
    End,
};

BOOST_DESCRIBE_ENUM(LabelAttach, Start, Middle, End);


struct Config {
    Config()
        : cross_gap(true)
        , label_attach(LabelAttach::Middle)
        , compact(false)
        , underlines(true)
        , multiline_arrows(true)
        , color(true)
        , tab_width(4) {}

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

    Config& with_char_set(Characters char_set) {
        this->char_set = char_set;
        return *this;
    }

    Config& with_debug_writes(bool debug_writes) {
        this->debug_writes = debug_writes;
        return *this;
    }


    Config& with_debug_report_info(bool debug_report_info) {
        this->debug_report_info = debug_report_info;
        return *this;
    }

    Config& with_debug_scopes(bool debug_scopes) {
        this->debug_scopes = debug_scopes;
        return *this;
    }

    ColStyle error_color       = ColStyle{} + TermColorBg8Bit::Red;
    ColStyle warning_color     = ColStyle{} + TermColorBg8Bit::Yellow;
    ColStyle advice_color      = ColStyle{} + TermColorBg8Bit::Magenta;
    ColStyle margin_color      = ColStyle{} + TermColorBg8Bit::White;
    ColStyle unimportant_color = ColStyle{} + TermColorBg8Bit::Default;
    ColStyle note_color        = ColStyle{} + TermColorBg8Bit::Cyan;

    std::pair<char, int> char_width(char c, int col) const;


    bool        cross_gap;
    LabelAttach label_attach;
    bool        compact;
    bool        underlines = true;
    bool        multiline_arrows;
    bool        color;
    int         tab_width;
    bool        debug_writes      = false;
    bool        debug_scopes      = false;
    bool        debug_report_info = false;
    Characters  char_set          = Config::unicode();

    static Characters unicode();
    static Characters ascii();

    DESC_FIELDS(
        Config,
        (error_color,
         warning_color,
         advice_color,
         margin_color,
         unimportant_color,
         note_color,
         cross_gap,
         label_attach,
         compact,
         underlines,
         multiline_arrows,
         color,
         tab_width,
         debug_writes,
         debug_scopes));
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

    DESC_FIELDS(
        Report,
        (kind, code, msg, note, help, location, labels, config));


    /// \brief Give this report a numerical code that may be used to more
    /// precisely \brief look up the error in documentation.
    Report& with_code(const std::string& code) {
        this->code = code;
        return *this;
    }

    /// \brief Set the message of this report.
    void set_message(const ColText& msg) { this->msg = msg; }

    /// \brief Add a message to this report.
    Report& with_message(const ColText& msg) {
        set_message(msg);
        return *this;
    }

    /// \brief Set the note of this report.
    void set_note(const ColText& note) { this->note = note; }

    /// \brief Set the note of this report.
    Report& with_note(const ColText& note) {
        set_note(note);
        return *this;
    }

    /// \brief Set the help message of this report.
    void set_help(const ColText& help) { this->help = help; }

    /// \brief Set the help message of this report.
    Report& with_help(const ColText& help) {
        set_help(help);
        return *this;
    }

    /// \brief Add a label to the report.
    void add_label(const Label& label) { labels.push_back(label); }

    /// \brief Add multiple labels to the report.
    template <typename Container>
    void add_labels(const Container& labels) {
        this->labels.insert(
            this->labels.end(), labels.begin(), labels.end());
    }

    /// \brief Add a label to the report.
    Report& with_label(const Label& label) {
        add_label(label);
        return *this;
    }

    /// \brief Add multiple labels to the report.
    template <typename Container>
    Report& with_labels(const Container& labels) {
        add_labels(labels);
        return *this;
    }

    /// \brief Use the given Config to determine diagnostic attributes.
    Report& with_config(const Config& config) {
        this->config = config;
        return *this;
    }

    Report(ReportKind kind, Id id, int offset)
        : kind(kind), location({id, offset}) {}

    Vec<SourceGroup> get_source_groups(Cache* cache) const;


    void write(Cache& cache, std::ostream& w) {
        write_for_stream(cache, w);
    }

    void write_for_stream(Cache& cache, std::ostream& stream) const {
        ColStream w{stream};
        write_for_stream(cache, w);
    }

    void write_for_stream(Cache& cache, ColStream& w) const;

    std::string to_string(Cache& cache, bool colored) const {
        ColStream buf;
        write_for_stream(cache, buf);
        return buf.toString(colored);
    }

    static Vec<Label> build_multi_labels(Vec<LabelInfo> const& labels);
};

} // namespace hstd::ext


template <>
struct std::formatter<hstd::ext::CodeSpan> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const hstd::ext::CodeSpan& p, FormatContext& ctx) const {
        return ::hstd::fmt_ctx(
            hstd::fmt("<{}:{}..{}>", p.source(), p.start(), p.end()), ctx);
    }
};


template <>
struct std::formatter<hstd::ext::CodeSpan*>
    : public hstd::std_format_ptr_as_value<hstd::ext::CodeSpan> {
    using std_format_ptr_as_value<hstd::ext::CodeSpan>::format;
};
