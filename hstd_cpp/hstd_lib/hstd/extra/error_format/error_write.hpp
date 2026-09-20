/// \file rewrite of the https://github.com/zesterer/ariadne/tree/main for
/// C++

#pragma once

#include <functional>
#include <hstd/stdlib/containers/Slice.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include <hstd/stdlib/containers/Map.hpp>
#include <hstd/stdlib/containers/Vec.hpp>

#include <boost/describe.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/containers/Opt.hpp>
#include <hstd/stdlib/containers/Ptrs.hpp>
#include <hstd/stdlib/containers/bimap_wrap.hpp>
#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/formatting/ColText.hpp>
#include <hstd/stdlib/formatting/Formatter.hpp>
#include <hstd/system/reflection.hpp>


namespace hstd::ext {

class ReportSource;

/// \brief A trait implemented by `Source` caches.
DECL_ID_TYPE(ReportSource, ReportSourceId, std::size_t);
DECL_ID_TYPE(ReportLabel, ReportLabelId, std::size_t);

// DECL_ID_TYPE(Commit, CommitId, std::size_t);

/// \brief A trait implemented by spans within a character-based source.
struct CodeSpan {
    ReportSourceId id;
    Slice<int>     range;
    DESC_FIELDS(CodeSpan, (id, range));

    CodeSpan(ReportSourceId id, Slice<int> const& range);

    /// \brief Get the identifier of the source that this Codespan refers
    /// to.
    const ReportSourceId source() const { return id; }

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

class [[refl]] ReportSourceCache {
  public:
    // Fetch the `ReportSource` identified by the given ID, if possible.
    // TODO: Don't box
    virtual std::shared_ptr<ReportSource> fetch(ReportSourceId const& id) = 0;

    // Display the given ID. as a single inline value.
    virtual std::optional<std::string> display(ReportSourceId const& id) const = 0;

    CodeSpan init_span(ReportSourceId id, Slice<int> const& range);

    DESC_FIELDS(ReportSourceCache, (fetch, display));

    virtual ~ReportSourceCache() = default;
};


// A type representing a single line of a `Source`.
struct ReportSourceLine {
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

    DESC_FIELDS(ReportSourceLine, (offset, len));
};

/// A type representing a single source that may be referred to by
/// `CodeSpan`s.
///
/// In most cases, a source is a single input file.
struct ReportSource {
    using id_type = ReportSourceId;
    Vec<ReportSourceLine> lines;
    int                   len;
    ColText               content;

    ReportSource(Str const& l);

    struct OffsetLine {
        const ReportSourceLine& line;
        int                     idx = 0;
        int                     col = 0;
        DESC_FIELDS(OffsetLine, (idx, col));
    };

    /// \brief Get access to a specific, zero-indexed ReportSourceLine.
    std::optional<ReportSourceLine> line(int idx) const {
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
    /// (i.e: those that can be used for ReportSource::line()).
    Slice<int> get_line_range(CodeSpan const& span);

    ColText get_line_text(ReportSourceLine const& line);

    DESC_FIELDS(ReportSource, (lines, len));
};

class [[refl]] ReportSourceStrCache : public ReportSourceCache {

    /// Cache interface
  public:
    UnorderedMap<ReportSourceId, std::shared_ptr<ReportSource>> sources;
    hstd::ext::Unordered1to1Bimap<ReportSourceId, std::string>  names;
    std::function<std::string(std::string const&)>              getFileSource;

    BOOST_DESCRIBE_CLASS(
        ReportSourceStrCache,
        (ReportSourceCache),
        (sources, names),
        (),
        ());

    void add(ReportSourceId id, std::string const& source, std::string const& name);
    ReportSourceId add_path(hstd::fs::path const& path);

    inline std::shared_ptr<ReportSource> fetch(ReportSourceId const& id) override {
        return sources.at(id);
    }

    inline std::optional<std::string> display(ReportSourceId const& id) const override {
        return names.get_right(id);
    }
};

struct ReportCharacters {
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

enum class LabelKind
{
    Inline,
    Multiline
};

BOOST_DESCRIBE_ENUM(LabelKind, Inline, Multiline);

struct ReportLabel {
    using id_type = ReportLabelId;
    /// \brief Give this label a message
    ReportLabel& with_message(ColText const& msg) {
        this->msg = msg;
        return *this;
    }

    /// \brief Give this label a highlight color
    ReportLabel& with_color(ColStyle const& color) {
        this->color = color;
        return *this;
    }

    /// \brief Specify the order of this label relative to other labels
    ReportLabel& with_order(int order) {
        this->order = order;
        return *this;
    }

    /// \brief Specify the priority of this label relative to other labels
    ReportLabel& with_priority(int priority) {
        this->priority = priority;
        return *this;
    }

    ReportLabel clone() const { return *this; }

    ReportLabel(ReportLabelId selfId, CodeSpan span) : id{selfId}, span{span} {}

    /// \brief Unique ID to disambiguate different labels from each other
    /// and uniquely identify them.
    ReportLabelId id;
    /// \brief Range of code this label applies to.
    CodeSpan               span;
    std::optional<ColText> msg      = std::nullopt;
    ColStyle               color    = ColStyle{};
    int                    order    = 0;
    int                    priority = 0;

    DESC_FIELDS(ReportLabel, (span, msg, color, order, priority, id));

    bool operator==(ReportLabel const& other) const { return this->id == other.id; }
};

/// \brief Metadata about the label.
struct LabelInfo {
    LabelKind   kind;
    ReportLabel label;
    DESC_FIELDS(LabelInfo, (kind, label));
};


struct SourceGroup {
    ReportSourceId src_id;
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


struct ReportRenderConfig {
    ReportRenderConfig()
        : cross_gap(true)
        , label_attach(LabelAttach::Middle)
        , compact(false)
        , underlines(true)
        , multiline_arrows(true)
        , color(true)
        , tab_width(4) {}

    ReportRenderConfig& with_cross_gap(bool cross_gap) {
        this->cross_gap = cross_gap;
        return *this;
    }

    ReportRenderConfig& with_label_attach(LabelAttach label_attach) {
        this->label_attach = label_attach;
        return *this;
    }

    ReportRenderConfig& with_compact(bool compact) {
        this->compact = compact;
        return *this;
    }

    ReportRenderConfig& with_underlines(bool underlines) {
        this->underlines = underlines;
        return *this;
    }

    ReportRenderConfig& with_multiline_arrows(bool multiline_arrows) {
        this->multiline_arrows = multiline_arrows;
        return *this;
    }

    ReportRenderConfig& with_color(bool color) {
        this->color = color;
        return *this;
    }

    ReportRenderConfig& with_tab_width(int tab_width) {
        this->tab_width = tab_width;
        return *this;
    }

    ReportRenderConfig& with_char_set(ReportCharacters char_set) {
        this->char_set = char_set;
        return *this;
    }

    ReportRenderConfig& with_debug_writes(bool debug_writes) {
        this->debug_writes = debug_writes;
        return *this;
    }


    ReportRenderConfig& with_debug_report_info(bool debug_report_info) {
        this->debug_report_info = debug_report_info;
        return *this;
    }

    ReportRenderConfig& with_debug_scopes(bool debug_scopes) {
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


    bool             cross_gap;
    LabelAttach      label_attach;
    bool             compact;
    bool             underlines = true;
    bool             multiline_arrows;
    bool             color;
    int              tab_width;
    bool             debug_writes      = false;
    bool             debug_scopes      = false;
    bool             debug_report_info = false;
    ReportCharacters char_set          = ReportRenderConfig::unicode();

    static ReportCharacters unicode();
    static ReportCharacters ascii();

    DESC_FIELDS(
        ReportRenderConfig,
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

class [[refl(R"({"default-constructor": false})")]] Report {
  public:
    ReportKind                     kind     = ReportKind::Error;
    std::optional<std::string>     code     = std::nullopt;
    std::optional<ColText>         msg      = std::nullopt;
    hstd::Vec<ColText>             note     = {};
    hstd::Vec<ColText>             help     = {};
    std::pair<ReportSourceId, int> location = {ReportSourceId::Nil(), 0};
    Vec<ReportLabel>               labels   = {};
    ReportRenderConfig             config   = ReportRenderConfig{};

    DESC_FIELDS(Report, (kind, code, msg, note, help, location, labels, config));


    /// \brief Give this report a numerical code that may be used to more
    /// precisely \brief look up the error in documentation.
    Report& with_code(std::string const& code) {
        this->code = code;
        return *this;
    }

    /// \brief Set the message of this report.
    void set_message(ColText const& msg) { this->msg = msg; }

    /// \brief Add a message to this report.
    Report& with_message(ColText const& msg) {
        set_message(msg);
        return *this;
    }

    /// \brief Set the note of this report.
    void add_note(ColText const& note) { this->note.push_back(note); }

    /// \brief Set the note of this report.
    Report& with_note(ColText const& note) {
        add_note(note);
        return *this;
    }

    /// \brief Set the help message of this report.
    void add_help(ColText const& help) { this->help.push_back(help); }

    /// \brief Set the help message of this report.
    Report& with_help(ColText const& help) {
        add_help(help);
        return *this;
    }

    /// \brief Add a label to the report.
    void add_label(ReportLabel const& label) { labels.push_back(label); }

    /// \brief Add multiple labels to the report.
    template <typename Container>
    void add_labels(Container const& labels) {
        this->labels.insert(this->labels.end(), labels.begin(), labels.end());
    }

    /// \brief Add a label to the report.
    Report& with_label(ReportLabel const& label) {
        add_label(label);
        return *this;
    }

    /// \brief Add multiple labels to the report.
    template <typename Container>
    Report& with_labels(Container const& labels) {
        add_labels(labels);
        return *this;
    }

    /// \brief Use the given Config to determine diagnostic attributes.
    Report& with_config(ReportRenderConfig const& config) {
        this->config = config;
        return *this;
    }

    Report(ReportKind kind, ReportSourceId id, int offset)
        : kind(kind), location({id, offset}) {}

    Vec<SourceGroup> get_source_groups(ReportSourceCache* cache) const;


    void write(ReportSourceCache& cache, std::ostream& w) { write_for_stream(cache, w); }

    void write_for_stream(ReportSourceCache& cache, std::ostream& stream) const {
        ColStream w{stream};
        write_for_stream(cache, w);
    }

    void write_for_stream(ReportSourceCache& cache, ColStream& w) const;

    std::string to_string(ReportSourceCache& cache, bool colored) const {
        ColStream buf;
        write_for_stream(cache, buf);
        return buf.toString(colored);
    }

    /// \brief Find all labels
    static Vec<ReportLabel> build_multi_labels(Vec<LabelInfo> const& labels);
};

} // namespace hstd::ext


template <>
struct fmt::formatter<hstd::ext::CodeSpan> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ext::CodeSpan const& p, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx(
            hstd::fmt("<{}:{}..{}>", p.source(), p.start(), p.end()), ctx);
    }
};


template <>
struct fmt::formatter<hstd::ext::CodeSpan*>
    : public hstd::std_format_ptr_as_value<hstd::ext::CodeSpan> {
    using std_format_ptr_as_value<hstd::ext::CodeSpan>::format;
};


template <>
struct fmt::formatter<hstd::ext::ReportSource*>
    : public hstd::std_format_ptr_as_value<hstd::ext::ReportSource> {
    using std_format_ptr_as_value<hstd::ext::ReportSource>::format;
};
