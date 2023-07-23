#pragma once
#include <sem/SemOrgEnums.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <parse/OrgTypes.hpp>
#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <functional>
#include <QDateTime>
#include <sem/SemOrgBase.hpp>
#include <sem/SemOrgEnums.hpp>
namespace sem {
/// \brief Base class for all document-level entries. Note that some node kinds
/// might also have inline entries (examples include links, source code blocks,
/// call blocks)
struct Stmt : public Org {
  BOOST_DESCRIBE_CLASS(Stmt,
                       (Org),
                       (),
                       (),
                       ())
};

/// \brief Base class for all inline elements
struct Inline : public Org {
  BOOST_DESCRIBE_CLASS(Inline,
                       (Org),
                       (),
                       (),
                       ())
};

/// \brief Zero or more statement nodes
struct StmtList : public Org {
  BOOST_DESCRIBE_CLASS(StmtList,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<StmtList>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<StmtList> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Node without content
struct Empty : public Org {
  BOOST_DESCRIBE_CLASS(Empty,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Empty>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Empty> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Table row
struct Row : public Org {
  BOOST_DESCRIBE_CLASS(Row,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Row>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Row> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Table
struct Table : public Stmt {
  BOOST_DESCRIBE_CLASS(Table,
                       (Stmt),
                       (),
                       (),
                       (staticKind /* field */,
                        rows /* field */,
                        (SemIdT<Table>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief List of rows for the table
  Vec<SemIdT<Row>> rows;
  static SemIdT<Table> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Single or nested inline hash-tag
struct HashTag : public Inline {
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind /* field */,
                        head /* field */,
                        subtags /* field */,
                        (SemIdT<HashTag>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (bool(CR<Vec<QString>>) const) prefixMatch /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Main part of the tag
  Str head;
  /// \brief List of nested tags
  Vec<SemIdT<HashTag>> subtags;
  static SemIdT<HashTag> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  /// \brief Check if list of tag names is a prefix for either
  ///   of the nested hash tags in this one
  bool prefixMatch(CR<Vec<QString>> prefix) const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public Inline {
  BOOST_DESCRIBE_CLASS(Footnote,
                       (Inline),
                       (),
                       (),
                       (staticKind /* field */,
                        tag /* field */,
                        definition /* field */,
                        (SemIdT<Footnote>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Footnote text target name
  Str tag;
  /// \brief Link to possibly resolved definition
  Opt<SemId> definition;
  static SemIdT<Footnote> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Completion status of the subtree list element
struct Completion : public Inline {
  BOOST_DESCRIBE_CLASS(Completion,
                       (Inline),
                       (),
                       (),
                       (staticKind /* field */,
                        done /* field */,
                        full /* field */,
                        isPercent /* field */,
                        (SemIdT<Completion>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Number of completed tasks
  int done;
  /// \brief Full number of tasks
  int full;
  /// \brief Use fraction or percent to display completion
  bool isPercent;
  static SemIdT<Completion> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Top-level or inline paragraph
struct Paragraph : public Stmt {
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Paragraph>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (bool() const) isFootnoteDefinition /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Paragraph> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  /// \brief Check if paragraph defines footnote
  bool isFootnoteDefinition() const;
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {
  BOOST_DESCRIBE_CLASS(Format,
                       (Org),
                       (),
                       (),
                       ())
};

/// \brief Center nested content in export
struct Center : public Format {
  BOOST_DESCRIBE_CLASS(Center,
                       (Format),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Center>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Center> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Base class for block or line commands
struct Command : public Org {
  BOOST_DESCRIBE_CLASS(Command,
                       (Org),
                       (),
                       (),
                       ())
};

/// \brief Line commands
struct LineCommand : public Command {
  BOOST_DESCRIBE_CLASS(LineCommand,
                       (Command),
                       (),
                       (),
                       ())
};

/// \brief Standalone commands that can be placed individuall on the the
/// top level and don't have to be attached to any subsequent elements
struct Standalone : public LineCommand {
  BOOST_DESCRIBE_CLASS(Standalone,
                       (LineCommand),
                       (),
                       (),
                       ())
};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {
  BOOST_DESCRIBE_CLASS(Attached,
                       (LineCommand),
                       (),
                       (),
                       ())
};

/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
  BOOST_DESCRIBE_CLASS(Caption,
                       (Attached),
                       (),
                       (),
                       (staticKind /* field */,
                        text /* field */,
                        (SemIdT<Caption>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Content description
  SemIdT<Paragraph> text;
  static SemIdT<Caption> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Multiple attachable commands will get grouped into this element
///  unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
  BOOST_DESCRIBE_CLASS(CommandGroup,
                       (Stmt),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<CommandGroup>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<CommandGroup> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Block command type
struct Block : public Command {
  BOOST_DESCRIBE_CLASS(Block,
                       (Command),
                       (),
                       (),
                       ())
};

/// \brief Quotation block
struct Quote {
  BOOST_DESCRIBE_CLASS(Quote,
                       (),
                       (),
                       (),
                       (staticKind /* field */,
                        text /* field */,
                        (SemIdT<Quote>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Quote content
  SemIdT<Paragraph> text;
  static SemIdT<Quote> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Example block
struct Example : public Block {
  BOOST_DESCRIBE_CLASS(Example,
                       (Block),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Example>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Example> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Direct export passthrough
struct Export : public Block {
  /// \brief Export block format type
  enum class Format  : short int{
    /// \brief Export directly in the paragraph
    Inline,
    /// \brief Single line of export
    Line,
    /// \brief Multiple lines of export
    Block,
  };

  BOOST_DESCRIBE_CLASS(Export,
                       (Block),
                       (),
                       (),
                       (staticKind /* field */,
                        format /* field */,
                        exporter /* field */,
                        content /* field */,
                        (SemIdT<Export>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Export block type
  Format format;
  /// \brief Exporter backend name
  QString exporter;
  /// \brief Raw exporter content string
  QString content;
  static SemIdT<Export> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Block of text with admonition tag: 'note', 'warning'
struct AdmonitionBlock : public Block {
  BOOST_DESCRIBE_CLASS(AdmonitionBlock,
                       (Block),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<AdmonitionBlock>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<AdmonitionBlock> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Base class for all code blocks
struct Code : public Block {
  /// \brief Extra configuration switches that can be used to control
  /// representation of the rendered code block. This field does not
  /// exactly correspond to the `-XX` parameters that can be passed
  /// directly in the field, but also works with attached `#+options`
  /// from the block
  struct Switch {
    struct CalloutFormat {
      BOOST_DESCRIBE_CLASS(CalloutFormat,
                           (),
                           (),
                           (),
                           (format /* field */))
      Str format;
    };

    struct RemoveCallout {
      BOOST_DESCRIBE_CLASS(RemoveCallout,
                           (),
                           (),
                           (),
                           (remove /* field */))
      bool remove;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      BOOST_DESCRIBE_CLASS(EmphasizeLine,
                           (),
                           (),
                           (),
                           (line /* field */))
      Vec<int> line;
    };

    struct Dedent {
      BOOST_DESCRIBE_CLASS(Dedent,
                           (),
                           (),
                           (),
                           (value /* field */))
      int value;
    };

    SUB_VARIANTS(Kind, Data, data, getKind, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent);
    Data data;
    BOOST_DESCRIBE_CLASS(Switch,
                         (),
                         (),
                         (),
                         ())
  };

  /// \brief What to do with newly evaluated result
  enum class Results  : short int{
    /// \brief Remove old result, replace with new value
    Replace,
  };

  /// \brief What part of the code block should be visible in export
  enum class Exports  : short int{
    /// \brief Hide both original code and run result
    None,
    /// \brief Show output and code
    Both,
    /// \brief Show only code
    Code,
    /// \brief Show only evaluation results
    Results,
  };

  BOOST_DESCRIBE_CLASS(Code,
                       (Block),
                       (),
                       (),
                       (staticKind /* field */,
                        lang /* field */,
                        switches /* field */,
                        exports /* field */,
                        cache /* field */,
                        eval /* field */,
                        noweb /* field */,
                        hlines /* field */,
                        tangle /* field */,
                        (SemIdT<Code>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Code block language name
  Opt<QString> lang;
  /// \brief Switch options for block
  Vec<Switch> switches;
  /// \brief What to export
  Exports exports;
  /// \brief Do cache values?
  bool cache;
  /// \brief Eval on export?
  bool eval;
  /// \brief Web-tangle code on export/run
  bool noweb;
  /// \brief ?
  bool hlines;
  /// \brief ?
  bool tangle;
  static SemIdT<Code> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public Org {
  /// \brief Repetition information for static time
  struct Repeat {
    /// \brief Timestamp repetition mode
    enum class Mode  : short int{
      /// \brief Do not repeat task on completion
      None,
      /// \brief ?
      Exact,
      /// \brief Repeat on the first matching day in the future
      FirstMatch,
      /// \brief Repeat task on the same day next week/month/year
      SameDay,
    };

    /// \brief Repetition period. Temporary placeholder for now, until I
    /// figure out what would be the proper way to represent whatever
    /// org can do ... which is to be determined as well
    enum class Period  : short int{
      Year,
      Month,
      Week,
      Day,
      Hour,
      Minute,
    };

    BOOST_DESCRIBE_CLASS(Repeat,
                         (),
                         (),
                         (),
                         (mode /* field */,
                          period /* field */,
                          count /* field */))
    /// \brief mode
    Mode mode;
    /// \brief period
    Period period;
    /// \brief count
    int count;
  };

  BOOST_DESCRIBE_CLASS(Time,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Time>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Time> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Range of time delimited by two points
struct TimeRange : public Org {
  BOOST_DESCRIBE_CLASS(TimeRange,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        from /* field */,
                        to /* field */,
                        (SemIdT<TimeRange>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Starting time
  SemIdT<Time> from;
  /// \brief Finishing time
  SemIdT<Time> to;
  static SemIdT<TimeRange> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Inline macro invocation
struct Macro : public Org {
  BOOST_DESCRIBE_CLASS(Macro,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        name /* field */,
                        arguments /* field */,
                        (SemIdT<Macro>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Macro name
  QString name;
  /// \brief Raw uninterpreted macro arguments
  Vec<QString> arguments;
  static SemIdT<Macro> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Text symbol or symbol command
struct Symbol : public Org {
  /// \brief Symbol parameters
  struct Param {
    BOOST_DESCRIBE_CLASS(Param,
                         (),
                         (),
                         (),
                         (key /* field */,
                          value /* field */))
    /// \brief Key -- for non-positional
    Opt<QString> key;
    /// \brief Uninterpreted value
    QString value;
  };

  BOOST_DESCRIBE_CLASS(Symbol,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        name /* field */,
                        parameters /* field */,
                        positional /* field */,
                        (SemIdT<Symbol>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Name of the symbol
  QString name;
  /// \brief Optional list of parameters
  Vec<Param> parameters;
  /// \brief Positional parameters
  SemId positional;
  static SemIdT<Symbol> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Single subtree log entry
struct SubtreeLog : public Org {
  /// \brief Base value for the log variant
  struct DescribedLog {
    BOOST_DESCRIBE_CLASS(DescribedLog,
                         (),
                         (),
                         (),
                         (desc /* field */))
    /// \brief Optional description of the log entry
    Opt<SemIdT<StmtList>> desc;
  };

  /// \brief Timestamped note
  struct Note : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Note,
                         (DescribedLog),
                         (),
                         (),
                         (on /* field */))
    /// \brief Where log was taken
    SemIdT<Time> on;
  };

  /// \brief Refiling action
  struct Refile : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Refile,
                         (DescribedLog),
                         (),
                         (),
                         (on /* field */,
                          from /* field */))
    /// \brief When the refiling happened
    SemIdT<Time> on;
    /// \brief Link to the original subtree
    SemIdT<Link> from;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Clock,
                         (DescribedLog),
                         (),
                         (),
                         (range /* field */))
    /// \brief Start-end or only start period
    Variant<SemIdT<Time>, SemIdT<TimeRange>> range;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public DescribedLog {
    BOOST_DESCRIBE_CLASS(State,
                         (DescribedLog),
                         (),
                         (),
                         (from /* field */,
                          to /* field */,
                          on /* field */))
    OrgBigIdentKind from;
    OrgBigIdentKind to;
    SemIdT<Time> on;
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Tag,
                         (DescribedLog),
                         (),
                         (),
                         (on /* field */,
                          tag /* field */,
                          added /* field */))
    /// \brief When the log was assigned
    SemIdT<Time> on;
    /// \brief Tag in question
    SemIdT<HashTag> tag;
    /// \brief Added/removed?
    bool added;
  };

  SUB_VARIANTS(Kind, LogEntry, data, getLogKind, Note, Refile, Clock, State, Tag);
  LogEntry data;
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        log /* field */,
                        (SemIdT<SubtreeLog>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Log
  LogEntry log;
  static SemIdT<SubtreeLog> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Subtree
struct Subtree : public Org {
  /// \brief Type of the subtree associated time periods
  struct Period {
    /// \brief Period kind
    enum class Kind  : short int{
      /// \brief Time period of the task execution.
      Clocked,
      /// \brief Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned
      Scheduled,
      /// \brief Single point or time range used in title. Single point can also be a simple time, such as `12:20`
      Titled,
      /// \brief Date of task completion. Must be a single time point
      Deadline,
      /// \brief When the subtree was created
      Created,
      /// \brief Last repeat time of the recurring tasks
      Repeated,
    };

    BOOST_DESCRIBE_CLASS(Period,
                         (),
                         (),
                         (),
                         (kind /* field */,
                          period /* field */,
                          (SemIdT<Time>()) getTime /* method */,
                          (SemIdT<Time>()) getTimeRange /* method */))
    /// \brief Time period kind -- not associated with point/range distinction
    Kind kind;
    /// \brief Stored time point/range
    Variant<SemIdT<Time>, SemIdT<TimeRange>> period;
    /// \brief Get associated time point
    SemIdT<Time> getTime();
    /// \brief Get associated time period
    SemIdT<Time> getTimeRange();
  };

  /// \brief Single subtree property
  struct Property {
    struct ExportLatexClass {
      BOOST_DESCRIBE_CLASS(ExportLatexClass,
                           (),
                           (),
                           (),
                           (latexClass /* field */))
      QString latexClass;
    };

    struct ExportLatexHeader {
      BOOST_DESCRIBE_CLASS(ExportLatexHeader,
                           (),
                           (),
                           (),
                           (header /* field */))
      QString header;
    };

    struct ExportLatexCompiler {
      BOOST_DESCRIBE_CLASS(ExportLatexCompiler,
                           (),
                           (),
                           (),
                           (compiler /* field */))
      QString compiler;
    };

    struct Ordered {
      BOOST_DESCRIBE_CLASS(Ordered,
                           (),
                           (),
                           (),
                           (isOrdered /* field */))
      bool isOrdered;
    };

    struct Effort {
      BOOST_DESCRIBE_CLASS(Effort,
                           (),
                           (),
                           (),
                           (hours /* field */,
                            minutes /* field */))
      int hours;
      int minutes;
    };

    struct Visibility {
      enum class Level  : short int{
        Folded,
        Children,
        Content,
        All,
      };

      BOOST_DESCRIBE_CLASS(Visibility,
                           (),
                           (),
                           (),
                           (level /* field */))
      Level level;
    };

    struct ExportOptions {
      BOOST_DESCRIBE_CLASS(ExportOptions,
                           (),
                           (),
                           (),
                           (backend /* field */,
                            values /* field */))
      QString backend;
      UnorderedMap<Str, Str> values;
    };

    struct Blocker {
      BOOST_DESCRIBE_CLASS(Blocker,
                           (),
                           (),
                           (),
                           (blockers /* field */))
      Vec<QString> blockers;
    };

    struct Unnumbered {
      BOOST_DESCRIBE_CLASS(Unnumbered,
                           (),
                           (),
                           (),
                           ())
    };

    struct Created {
      BOOST_DESCRIBE_CLASS(Created,
                           (),
                           (),
                           (),
                           (time /* field */))
      SemIdT<Time> time;
    };

    SUB_VARIANTS(Kind, Data, data, getKind, ExportLatexClass, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created);
    Data data;
    Property(CR<Data> data) : data(data) {}
    bool matches(Kind kind, CR<QString> subkind = "") const;
    BOOST_DESCRIBE_CLASS(Property,
                         (),
                         (),
                         (),
                         ())
  };

  BOOST_DESCRIBE_CLASS(Subtree,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        level /* field */,
                        treeId /* field */,
                        todo /* field */,
                        completion /* field */,
                        tags /* field */,
                        title /* field */,
                        logbook /* field */,
                        properties /* field */,
                        closed /* field */,
                        deadline /* field */,
                        scheduled /* field */,
                        (SemIdT<Subtree>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (Vec<Period>(IntSet<Period::Kind>) const) getTimePeriods /* method */,
                        (Vec<Property>(Property::Kind, CR<QString>) const) getProperties /* method */,
                        (Opt<Property>(Property::Kind, CR<QString>) const) getProperty /* method */,
                        (Vec<Property>(Property::Kind, CR<QString>) const) getContextualProperties /* method */,
                        (Opt<Property>(Property::Kind, CR<QString>) const) getContextualProperty /* method */))
  /// \brief Document
  static SemId const staticKind;
  /// \brief Subtree level
  int level;
  /// \brief :ID: property
  Opt<QString> treeId;
  /// \brief Todo state of the tree
  Opt<QString> todo;
  /// \brief Task completion state
  Opt<SemIdT<Completion>> completion;
  /// \brief Trailing tags
  Vec<SemIdT<HashTag>> tags;
  /// \brief Main title
  SemIdT<Paragraph> title;
  /// \brief Associated subtree log
  Vec<SemIdT<SubtreeLog>> logbook;
  /// \brief Immediate properties
  Vec<Property> properties;
  /// \brief When subtree was marked as closed
  Opt<SemIdT<Time>> closed;
  /// \brief When is the deadline
  Opt<SemIdT<Time>> deadline;
  /// \brief When the event is scheduled
  Opt<SemIdT<Time>> scheduled;
  static SemIdT<Subtree> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  Vec<Period> getTimePeriods(IntSet<Period::Kind> kinds) const;
  Vec<Property> getProperties(Property::Kind kind, CR<QString> subkind = "") const;
  Opt<Property> getProperty(Property::Kind kind, CR<QString> subkind = "") const;
  Vec<Property> getContextualProperties(Property::Kind kind, CR<QString> subkind = "") const;
  Opt<Property> getContextualProperty(Property::Kind kind, CR<QString> subkind = "") const;
};

/// \brief Latex code body
struct LatexBody : public Org {
  BOOST_DESCRIBE_CLASS(LatexBody,
                       (Org),
                       (),
                       (),
                       ())
};

/// \brief Inline math
struct InlineMath : public LatexBody {
  BOOST_DESCRIBE_CLASS(InlineMath,
                       (LatexBody),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<InlineMath>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<InlineMath> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief Final node
struct Leaf : public Org {
  BOOST_DESCRIBE_CLASS(Leaf,
                       (Org),
                       (),
                       (),
                       (text /* field */))
  /// \brief Final leaf value
  QString text;
};

/// \brief Escaped text
struct Escaped : public Leaf {
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Escaped>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Escaped> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief \n newline
struct Newline : public Leaf {
  BOOST_DESCRIBE_CLASS(Newline,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Newline>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Newline> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief ' ' space
struct Space : public Leaf {
  BOOST_DESCRIBE_CLASS(Space,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Space>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Space> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief word
struct Word : public Leaf {
  BOOST_DESCRIBE_CLASS(Word,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Word>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Word> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

/// \brief @mention
struct AtMention : public Leaf {
  BOOST_DESCRIBE_CLASS(AtMention,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<AtMention>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<AtMention> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct RawText : public Leaf {
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<RawText>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<RawText> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Punctuation : public Leaf {
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Punctuation>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Punctuation> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Placeholder : public Leaf {
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Placeholder>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Placeholder> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct BigIdent : public Leaf {
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<BigIdent>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<BigIdent> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Markup : public Org {
  BOOST_DESCRIBE_CLASS(Markup,
                       (Org),
                       (),
                       (),
                       ())
};

struct Bold : public Markup {
  BOOST_DESCRIBE_CLASS(Bold,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Bold>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Bold> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Underline : public Markup {
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Underline>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Underline> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Monospace : public Markup {
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Monospace>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Monospace> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct MarkQuote : public Markup {
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<MarkQuote>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<MarkQuote> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Verbatim : public Markup {
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Verbatim>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Verbatim> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Italic : public Markup {
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Italic>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Italic> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Strike : public Markup {
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Strike>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Strike> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Par : public Markup {
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Par>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Par> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct List : public Org {
  BOOST_DESCRIBE_CLASS(List,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<List>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (bool() const) isDescriptionList /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<List> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  bool isDescriptionList() const;
};

struct ListItem : public Org {
  enum class Checkbox  : short int{
    None,
    Done,
    Empty,
  };

  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        checkbox /* field */,
                        header /* field */,
                        (SemIdT<ListItem>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (bool() const) isDescriptionList /* method */))
  /// \brief Document
  static SemId const staticKind;
  Checkbox checkbox;
  Opt<SemIdT<Paragraph>> header;
  static SemIdT<ListItem> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  bool isDescriptionList() const;
};

struct Link : public Org {
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw,
                         (),
                         (),
                         (),
                         (text /* field */))
    QString text;
  };

  struct Id {
    BOOST_DESCRIBE_CLASS(Id,
                         (),
                         (),
                         (),
                         (text /* field */))
    QString text;
  };

  struct Person {
    BOOST_DESCRIBE_CLASS(Person,
                         (),
                         (),
                         (),
                         (name /* field */))
    QString name;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote,
                         (),
                         (),
                         (),
                         (target /* field */))
    QString target;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File,
                         (),
                         (),
                         (),
                         (file /* field */))
    QString file;
  };

  SUB_VARIANTS(Kind, Data, data, getLinkKind, Raw, Id, Person, Footnote, File);
  Data data;
  BOOST_DESCRIBE_CLASS(Link,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Link>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (Opt<SemId>(CR<Document>) const) resolve /* method */,
                        (Opt<SemId>() const) resolve /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Link> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  Opt<SemId> resolve(CR<Document> doc) const;
  Opt<SemId> resolve() const;
};

struct Document : public Org {
  BOOST_DESCRIBE_CLASS(Document,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        idTable /* field */,
                        nameTable /* field */,
                        footnoteTable /* field */,
                        anchorTable /* field */,
                        title /* field */,
                        author /* field */,
                        creator /* field */,
                        email /* field */,
                        language /* field */,
                        options /* field */,
                        exportFileName /* field */,
                        (SemIdT<Document>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  UnorderedMap<QString, SemId> idTable;
  UnorderedMap<QString, SemId> nameTable;
  UnorderedMap<QString, SemId> footnoteTable;
  UnorderedMap<QString, SemId> anchorTable;
  Opt<SemIdT<Paragraph>> title;
  Opt<SemIdT<Paragraph>> author;
  Opt<SemIdT<Paragraph>> creator;
  Opt<SemIdT<RawText>> email;
  Opt<Vec<QString>> language;
  SemIdT<DocumentOptions> options;
  Opt<QString> exportFileName;
  static SemIdT<Document> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct ParseError : public Org {
  BOOST_DESCRIBE_CLASS(ParseError,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<ParseError>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<ParseError> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct FileTarget : public Org {
  BOOST_DESCRIBE_CLASS(FileTarget,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        path /* field */,
                        line /* field */,
                        searchTarget /* field */,
                        restrictToHeadlines /* field */,
                        targetId /* field */,
                        regexp /* field */,
                        (SemIdT<FileTarget>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  QString path;
  Opt<int> line;
  Opt<QString> searchTarget;
  bool restrictToHeadlines;
  Opt<QString> targetId;
  Opt<QString> regexp;
  static SemIdT<FileTarget> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct TextSeparator : public Org {
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<TextSeparator>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<TextSeparator> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct Include : public Org {
  BOOST_DESCRIBE_CLASS(Include,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<Include>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Include> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

struct DocumentOptions : public Org {
  enum class BrokenLinks  : short int{
    Raise,
    Ignore,
    Mark,
  };

  enum class Visibility  : short int{
    Overview,
    Content,
    ShowAll,
    Show2Levels,
    Show3Levels,
    Show4Levels,
    Show5Levels,
    ShowEverything,
  };

  BOOST_DESCRIBE_CLASS(DocumentOptions,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        brokenLinks /* field */,
                        initialVisibility /* field */,
                        properties /* field */,
                        smartQuotes /* field */,
                        emphasizedText /* field */,
                        specialStrings /* field */,
                        fixedWidthSections /* field */,
                        includeTimestamps /* field */,
                        preserveLineBreaks /* field */,
                        plaintextSubscripts /* field */,
                        exportArchived /* field */,
                        exportWithAuthor /* field */,
                        exportBrokenLinks /* field */,
                        exportWithClock /* field */,
                        exportWithCreator /* field */,
                        (SemIdT<DocumentOptions>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */,
                        (Vec<Subtree::Property>(Subtree::Property::Kind, CR<QString>) const) getProperties /* method */,
                        (Opt<Subtree::Property>(Subtree::Property::Kind, CR<QString>) const) getProperty /* method */))
  /// \brief Document
  static SemId const staticKind;
  BrokenLinks brokenLinks;
  Visibility initialVisibility;
  Vec<Subtree::Property> properties;
  bool smartQuotes;
  bool emphasizedText;
  bool specialStrings;
  bool fixedWidthSections;
  bool includeTimestamps;
  bool preserveLineBreaks;
  bool plaintextSubscripts;
  bool exportArchived;
  bool exportWithAuthor;
  bool exportBrokenLinks;
  bool exportWithClock;
  bool exportWithCreator;
  static SemIdT<DocumentOptions> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
  Vec<Subtree::Property> getProperties(Subtree::Property::Kind kind, CR<QString> subKind = "") const;
  Opt<Subtree::Property> getProperty(Subtree::Property::Kind kind, CR<QString> subKind = "") const;
};

struct DocumentGroup : public Org {
  BOOST_DESCRIBE_CLASS(DocumentGroup,
                       (Org),
                       (),
                       (),
                       (staticKind /* field */,
                        (SemIdT<DocumentGroup>(SemId, Opt<SemId>)) create /* method */,
                        (OrgSemKind() const) getKind /* method */))
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<DocumentGroup> create(SemId parent, Opt<SemId> original = std::nullopt);
  virtual OrgSemKind getKind() const;
};

} // namespace sem