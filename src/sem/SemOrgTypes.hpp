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
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<StmtList> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Node without content
struct Empty : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Empty> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Table row
struct Row : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Row> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Table
struct Table : public Stmt {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief List of rows for the table
    Vec<SemIdT<Row>> rows;
  public:
    static SemIdT<Table> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Single or nested inline hash-tag
struct HashTag : public Inline {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Main part of the tag
    Str head;
  public:
  /// \brief List of nested tags
    Vec<SemIdT<HashTag>> subtags;
  public:
    static SemIdT<HashTag> create();
  public:
    virtual OrgSemKind getKind() const;
  public:
    /// \brief Check if list of tag names is a prefix for either
    ///   of the nested hash tags in this one
    bool prefixMatch() const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public Inline {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Footnote text target name
    Str tag;
  public:
  /// \brief Link to possibly resolved definition
    Opt<SemId> definition;
  public:
    static SemIdT<Footnote> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Completion status of the subtree list element
struct Completion : public Inline {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Number of completed tasks
    int done;
  public:
  /// \brief Full number of tasks
    int full;
  public:
  /// \brief Use fraction or percent to display completion
    bool isPercent;
  public:
    static SemIdT<Completion> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Top-level or inline paragraph
struct Paragraph : public Stmt {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Paragraph> create();
  public:
    virtual OrgSemKind getKind() const;
  public:
    /// \brief Check if paragraph defines footnote
    bool isFootnoteDefinition() const;
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {

};

/// \brief Center nested content in export
struct Center : public Format {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Center> create();
  public:
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
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Content description
    SemIdT<Paragraph> text;
  public:
    static SemIdT<Caption> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Multiple attachable commands will get grouped into this element
///  unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<CommandGroup> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Block command type
struct Block : public Command {

};

/// \brief Quotation block
struct Quote {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Quote content
    SemIdT<Paragraph> text;
  public:
    static SemIdT<Quote> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Example block
struct Example : public Block {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Example> create();
  public:
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

  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Export block type
    Format format;
  public:
  /// \brief Exporter backend name
    QString exporter;
  public:
  /// \brief Raw exporter content string
    QString content;
  public:
    static SemIdT<Export> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Block of text with admonition tag: 'note', 'warning'
struct AdmonitionBlock : public Block {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<AdmonitionBlock> create();
  public:
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
      public:
        Str format;
    };

    struct RemoveCallout {
      public:
        bool remove;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      public:
        Vec<int> line;
    };

    struct Dedent {
      public:
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
    public:
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

  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Code block language name
    Opt<QString> lang;
  public:
  /// \brief Switch options for block
    Vec<Switch> switches;
  public:
  /// \brief What to export
    Exports exports;
  public:
  /// \brief Do cache values?
    bool cache;
  public:
  /// \brief Eval on export?
    bool eval;
  public:
  /// \brief Web-tangle code on export/run
    bool noweb;
  public:
  /// \brief ?
    bool hlines;
  public:
  /// \brief ?
    bool tangle;
  public:
    static SemIdT<Code> create();
  public:
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

    public:
    /// \brief mode
      Mode mode;
    public:
    /// \brief period
      Period period;
    public:
    /// \brief count
      int count;
  };

  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Time> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Range of time delimited by two points
struct TimeRange : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Starting time
    SemIdT<Time> from;
  public:
  /// \brief Finishing time
    SemIdT<Time> to;
  public:
    static SemIdT<TimeRange> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Inline macro invocation
struct Macro : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Macro name
    QString name;
  public:
  /// \brief Raw uninterpreted macro arguments
    Vec<QString> arguments;
  public:
    static SemIdT<Macro> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Text symbol or symbol command
struct Symbol : public Org {
  /// \brief Symbol parameters
  struct Param {
    public:
    /// \brief Key -- for non-positional
      Opt<QString> key;
    public:
    /// \brief Uninterpreted value
      QString value;
  };

  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Name of the symbol
    QString name;
  public:
  /// \brief Optional list of parameters
    Vec<Param> parameters;
  public:
  /// \brief Positional parameters
    SemId positional;
  public:
    static SemIdT<Symbol> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Single subtree log entry
struct SubtreeLog : public Org {
  /// \brief Base value for the log variant
  struct DescribedLog {
    public:
    /// \brief Optional description of the log entry
      Opt<SemIdT<StmtList>> desc;
  };

  /// \brief Timestamped note
  struct Note : public DescribedLog {
    public:
    /// \brief Where log was taken
      SemIdT<Time> on;
  };

  /// \brief Refiling action
  struct Refile : public DescribedLog {
    public:
    /// \brief When the refiling happened
      SemIdT<Time> on;
    public:
    /// \brief Link to the original subtree
      SemIdT<Link> from;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public DescribedLog {
    public:
    /// \brief Start-end or only start period
      Variant<SemIdT<Time>, SemIdT<TimeRange>> range;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public DescribedLog {
    public:
      OrgBigIdentKind from;
    public:
      OrgBigIdentKind to;
    public:
      SemIdT<Time> on;
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public DescribedLog {
    public:
    /// \brief When the log was assigned
      SemIdT<Time> on;
    public:
    /// \brief Tag in question
      SemIdT<HashTag> tag;
    public:
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
  public:
    LogEntry data;
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Log
    LogEntry log;
  public:
    static SemIdT<SubtreeLog> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Subtree
struct Subtree : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
  /// \brief Subtree level
    int level;
  public:
  /// \brief :ID: property
    Opt<QString> treeId;
  public:
  /// \brief Todo state of the tree
    Opt<QString> todo;
  public:
  /// \brief Task completion state
    Opt<SemIdT<Completion>> completion;
  public:
  /// \brief Trailing tags
    Vec<SemIdT<HashTag>> tags;
  public:
  /// \brief Main title
    SemIdT<Paragraph> title;
  public:
  /// \brief Associated subtree log
    Vec<SemIdT<SubtreeLog>> logbook;
  public:
  /// \brief Immediate properties
    Vec<Property> properties;
  public:
  /// \brief When subtree was marked as closed
    Opt<SemIdT<Time>> closed;
  public:
  /// \brief When is the deadline
    Opt<SemIdT<Time>> deadline;
  public:
  /// \brief When the event is scheduled
    Opt<SemIdT<Time>> scheduled;
  public:
    static SemIdT<Subtree> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Latex code body
struct LatexBody : public Org {

};

/// \brief Inline math
struct InlineMath : public LatexBody {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<InlineMath> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief Final node
struct Leaf : public Org {
  public:
  /// \brief Final leaf value
    QString text;
};

/// \brief Escaped text
struct Escaped : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Escaped> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief \n newline
struct Newline : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Newline> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief ' ' space
struct Space : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Space> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief word
struct Word : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Word> create();
  public:
    virtual OrgSemKind getKind() const;
};

/// \brief @mention
struct AtMention : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<AtMention> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct RawText : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<RawText> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Punctuation : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Punctuation> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Placeholder : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Placeholder> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct BigIdent : public Leaf {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<BigIdent> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Markup : public Org {

};

struct Bold : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Bold> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Underline : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Underline> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Monospace : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Monospace> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct MarkQuote : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<MarkQuote> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Verbatim : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Verbatim> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Italic : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Italic> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Strike : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Strike> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Par : public Markup {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Par> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct List : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<List> create();
  public:
    virtual OrgSemKind getKind() const;
  public:
    bool isDescriptionList() const;
};

struct ListItem : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<ListItem> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Link : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Link> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Document : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Document> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct ParseError : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<ParseError> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct FileTarget : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<FileTarget> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct TextSeparator : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<TextSeparator> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct Include : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<Include> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct DocumentOptions : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<DocumentOptions> create();
  public:
    virtual OrgSemKind getKind() const;
};

struct DocumentGroup : public Org {
  public:
  /// \brief Document
    static SemId const staticKind;
  public:
    static SemIdT<DocumentGroup> create();
  public:
    virtual OrgSemKind getKind() const;
};

} // namespace sem