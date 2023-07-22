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

};

/// \brief Base class for all inline elements
struct Inline : public Org {

};

/// \brief Zero or more statement nodes
struct StmtList : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<StmtList> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Node without content
struct Empty : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Empty> create(SemId parent,
                              Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Table row
struct Row : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Row> create(SemId parent,
                            Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Table
struct Table : public Stmt {
  /// \brief Document
  static SemId const staticKind;
  /// \brief List of rows for the table
  Vec<SemIdT<Row>> rows;
  static SemIdT<Table> create(SemId parent,
                              Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Single or nested inline hash-tag
struct HashTag : public Inline {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Main part of the tag
  Str head;
  /// \brief List of nested tags
  Vec<SemIdT<HashTag>> subtags;
  static SemIdT<HashTag> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  /// \brief Check if list of tag names is a prefix for either
  ///   of the nested hash tags in this one
  bool prefixMatch(CR<Vec<QString>> prefix) const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public Inline {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Footnote text target name
  Str tag;
  /// \brief Link to possibly resolved definition
  Opt<SemId> definition;
  static SemIdT<Footnote> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Completion status of the subtree list element
struct Completion : public Inline {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Number of completed tasks
  int done;
  /// \brief Full number of tasks
  int full;
  /// \brief Use fraction or percent to display completion
  bool isPercent;
  static SemIdT<Completion> create(SemId parent,
                                   Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Top-level or inline paragraph
struct Paragraph : public Stmt {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Paragraph> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  /// \brief Check if paragraph defines footnote
  bool isFootnoteDefinition() const;
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {

};

/// \brief Center nested content in export
struct Center : public Format {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Center> create(SemId parent,
                               Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Base class for block or line commands
struct Command : public Org {

};

/// \brief Line commands
struct LineCommand : public Command {

};

/// \brief Standalone commands that can be placed individuall on the the
/// top level and don't have to be attached to any subsequent elements
struct Standalone : public LineCommand {

};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {

};

/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Content description
  SemIdT<Paragraph> text;
  static SemIdT<Caption> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Multiple attachable commands will get grouped into this element
///  unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<CommandGroup> create(SemId parent,
                                     Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Block command type
struct Block : public Command {

};

/// \brief Quotation block
struct Quote {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Quote content
  SemIdT<Paragraph> text;
  static SemIdT<Quote> create(SemId parent,
                              Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Example block
struct Example : public Block {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Example> create(SemId parent,
                                Opt<SemId> original);
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

  /// \brief Document
  static SemId const staticKind;
  /// \brief Export block type
  Format format;
  /// \brief Exporter backend name
  QString exporter;
  /// \brief Raw exporter content string
  QString content;
  static SemIdT<Export> create(SemId parent,
                               Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Block of text with admonition tag: 'note', 'warning'
struct AdmonitionBlock : public Block {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<AdmonitionBlock> create(SemId parent,
                                        Opt<SemId> original);
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
      Str format;
    };

    struct RemoveCallout {
      bool remove;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      Vec<int> line;
    };

    struct Dedent {
      int value;
    };

    SUB_VARIANTS(Kind,
                 Data,
                 data,
                 getKind,
                 CalloutFormat,
                 RemoveCallout,
                 EmphasizeLine,
                 Dedent);
    Data data;
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
  static SemIdT<Code> create(SemId parent,
                             Opt<SemId> original);
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

    /// \brief mode
    Mode mode;
    /// \brief period
    Period period;
    /// \brief count
    int count;
  };

  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Time> create(SemId parent,
                             Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Range of time delimited by two points
struct TimeRange : public Org {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Starting time
  SemIdT<Time> from;
  /// \brief Finishing time
  SemIdT<Time> to;
  static SemIdT<TimeRange> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Inline macro invocation
struct Macro : public Org {
  /// \brief Document
  static SemId const staticKind;
  /// \brief Macro name
  QString name;
  /// \brief Raw uninterpreted macro arguments
  Vec<QString> arguments;
  static SemIdT<Macro> create(SemId parent,
                              Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Text symbol or symbol command
struct Symbol : public Org {
  /// \brief Symbol parameters
  struct Param {
    /// \brief Key -- for non-positional
    Opt<QString> key;
    /// \brief Uninterpreted value
    QString value;
  };

  /// \brief Document
  static SemId const staticKind;
  /// \brief Name of the symbol
  QString name;
  /// \brief Optional list of parameters
  Vec<Param> parameters;
  /// \brief Positional parameters
  SemId positional;
  static SemIdT<Symbol> create(SemId parent,
                               Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Single subtree log entry
struct SubtreeLog : public Org {
  /// \brief Base value for the log variant
  struct DescribedLog {
    /// \brief Optional description of the log entry
    Opt<SemIdT<StmtList>> desc;
  };

  /// \brief Timestamped note
  struct Note : public DescribedLog {
    /// \brief Where log was taken
    SemIdT<Time> on;
  };

  /// \brief Refiling action
  struct Refile : public DescribedLog {
    /// \brief When the refiling happened
    SemIdT<Time> on;
    /// \brief Link to the original subtree
    SemIdT<Link> from;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public DescribedLog {
    /// \brief Start-end or only start period
    Variant<SemIdT<Time>, SemIdT<TimeRange>> range;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public DescribedLog {
    OrgBigIdentKind from;
    OrgBigIdentKind to;
    SemIdT<Time> on;
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public DescribedLog {
    /// \brief When the log was assigned
    SemIdT<Time> on;
    /// \brief Tag in question
    SemIdT<HashTag> tag;
    /// \brief Added/removed?
    bool added;
  };

  SUB_VARIANTS(Kind,
               LogEntry,
               data,
               getLogKind,
               Note,
               Refile,
               Clock,
               State,
               Tag);
  LogEntry data;
  /// \brief Document
  static SemId const staticKind;
  /// \brief Log
  LogEntry log;
  static SemIdT<SubtreeLog> create(SemId parent,
                                   Opt<SemId> original);
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
      QString latexClass;
    };

    struct ExportLatexHeader {
      QString header;
    };

    struct ExportLatexCompiler {
      QString compiler;
    };

    struct Ordered {
      bool isOrdered;
    };

    struct Effort {
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

      Level level;
    };

    struct ExportOptions {
      QString backend;
      UnorderedMap<Str, Str> values;
    };

    struct Blocker {
      Vec<QString> blockers;
    };

    struct Unnumbered {

    };

    struct Created {
      SemIdT<Time> time;
    };

    SUB_VARIANTS(Kind,
                 Data,
                 data,
                 getKind,
                 ExportLatexClass,
                 ExportLatexHeader,
                 ExportLatexCompiler,
                 Ordered,
                 Effort,
                 Visibility,
                 ExportOptions,
                 Blocker,
                 Unnumbered,
                 Created);
    Data data;
    Property(CR<Data> data) : data(data) {}
    bool matches(Kind kind, CR<QString> subkind = "") const;
  };

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
  static SemIdT<Subtree> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  Vec<Period> getTimePeriods(IntSet<Period::Kind> kinds) const;
  Vec<Property> getProperties(Property::Kind kind,
                              CR<QString> subkind) const;
  Opt<Property> getProperty(Property::Kind kind,
                            CR<QString> subkind) const;
  Vec<Property> getContextualProperties(Property::Kind kind,
                                        CR<QString> subkind) const;
  Opt<Property> getContextualProperty(Property::Kind kind,
                                      CR<QString> subkind) const;
};

/// \brief Latex code body
struct LatexBody : public Org {

};

/// \brief Inline math
struct InlineMath : public LatexBody {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<InlineMath> create(SemId parent,
                                   Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief Final node
struct Leaf : public Org {
  /// \brief Final leaf value
  QString text;
};

/// \brief Escaped text
struct Escaped : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Escaped> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief \n newline
struct Newline : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Newline> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief ' ' space
struct Space : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Space> create(SemId parent,
                              Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief word
struct Word : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Word> create(SemId parent,
                             Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

/// \brief @mention
struct AtMention : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<AtMention> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct RawText : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<RawText> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Punctuation : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Punctuation> create(SemId parent,
                                    Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Placeholder : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Placeholder> create(SemId parent,
                                    Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct BigIdent : public Leaf {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<BigIdent> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Markup : public Org {

};

struct Bold : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Bold> create(SemId parent,
                             Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Underline : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Underline> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Monospace : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Monospace> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct MarkQuote : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<MarkQuote> create(SemId parent,
                                  Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Verbatim : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Verbatim> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Italic : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Italic> create(SemId parent,
                               Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Strike : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Strike> create(SemId parent,
                               Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Par : public Markup {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Par> create(SemId parent,
                            Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct List : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<List> create(SemId parent,
                             Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  bool isDescriptionList() const;
};

struct ListItem : public Org {
  enum class Checkbox  : short int{
    None,
    Done,
    Empty,
  };

  /// \brief Document
  static SemId const staticKind;
  Checkbox checkbox;
  Opt<SemIdT<Paragraph>> header;
  static SemIdT<ListItem> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  bool isDescriptionList() const;
};

struct Link : public Org {
  struct Raw {
    QString text;
  };

  struct Id {
    QString text;
  };

  struct Person {
    QString name;
  };

  struct Footnote {
    QString target;
  };

  struct File {
    QString file;
  };

  SUB_VARIANTS(Kind,
               Data,
               data,
               getLinkKind,
               Raw,
               Id,
               Person,
               Footnote,
               File);
  Data data;
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Link> create(SemId parent,
                             Opt<SemId> original);
  virtual OrgSemKind getKind() const;
  Opt<SemId> resolve(CR<Document> doc) const;
  Opt<SemId> resolve() const;
};

struct Document : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Document> create(SemId parent,
                                 Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct ParseError : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<ParseError> create(SemId parent,
                                   Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct FileTarget : public Org {
  /// \brief Document
  static SemId const staticKind;
  QString path;
  Opt<int> line;
  Opt<QString> searchTarget;
  bool restrictToHeadlines;
  Opt<QString> targetId;
  Opt<QString> regexp;
  static SemIdT<FileTarget> create(SemId parent,
                                   Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct TextSeparator : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<TextSeparator> create(SemId parent,
                                      Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct Include : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<Include> create(SemId parent,
                                Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct DocumentOptions : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<DocumentOptions> create(SemId parent,
                                        Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

struct DocumentGroup : public Org {
  /// \brief Document
  static SemId const staticKind;
  static SemIdT<DocumentGroup> create(SemId parent,
                                      Opt<SemId> original);
  virtual OrgSemKind getKind() const;
};

} // namespace sem