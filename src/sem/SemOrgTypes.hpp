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

};

/// \brief Node without content
struct Empty : public Org {

};

/// \brief Table row
struct Row : public Org {

};

/// \brief Table
struct Table : public Stmt {
  public:
    Vec<SemIdT<Row>> rows;
};

/// \brief Single or nested inline hash-tag
struct HashTag : public Inline {
  public:
    Str head;
  public:
    Vec<SemIdT<HashTag>> subtags;
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
    Str tag;
  public:
    Opt<SemId> definition;
};

/// \brief Completion status of the subtree list element
struct Completion : public Inline {
  public:
    int done;
  public:
    int full;
  public:
    bool isPercent;
};

/// \brief Top-level or inline paragraph
struct Paragraph : public Stmt {
  public:
    /// \brief Check if paragraph defines footnote
    bool isFootnoteDefinition() const;
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {

};

/// \brief Center nested content in export
struct Center : public Format {

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
    SemIdT<Paragraph> text;
};

/// \brief Multiple attachable commands will get grouped into this element
///  unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {

};

/// \brief Block command type
struct Block : public Command {

};

/// \brief Quotation block
struct Quote {
  public:
    SemIdT<Paragraph> text;
};

/// \brief Example block
struct Example : public Block {

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
    Format format;
  public:
    QString exporter;
  public:
    QString content;
};

/// \brief Block of text with admonition tag: 'note', 'warning'
struct AdmonitionBlock : public Block {

};

/// \brief Base class for all code blocks
struct Code : public Block {
  /// \brief Extra configuration switches that can be used to control
  /// representation of the rendered code block. This field does not
  /// exactly correspond to the `-XX` parameters that can be passed
  /// directly in the field, but also works with attached `#+options`
  /// from the block
  struct Switch {
    enum class Kind {
      CalloutFormat,
      RemoveCallout,
      EmphasizeLine,
      Dedent,
    };

    char const* from_enum(Kind _result) {
      switch (_result) {
        case Kind::CalloutFormat: return "CalloutFormat";
        case Kind::RemoveCallout: return "RemoveCallout";
        case Kind::EmphasizeLine: return "EmphasizeLine";
        case Kind::Dedent: return "Dedent";
      }
    }

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
    Opt<QString> lang;
  public:
    Vec<Switch> switches;
  public:
    Exports exports;
  public:
    bool cache;
  public:
    bool eval;
  public:
    bool noweb;
  public:
    bool hlines;
  public:
    bool tangle;
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
      Mode mode;
    public:
      Period period;
    public:
      int count;
  };

};

/// \brief Range of time delimited by two points
struct TimeRange : public Org {
  public:
    SemIdT<Time> from;
  public:
    SemIdT<Time> to;
};

/// \brief Inline macro invocation
struct Macro : public Org {
  public:
    QString name;
  public:
    Vec<QString> arguments;
};

/// \brief Text symbol or symbol command
struct Symbol : public Org {
  /// \brief Symbol parameters
  struct Param {
    public:
      Opt<QString> key;
    public:
      QString value;
  };

  public:
    QString name;
  public:
    Vec<Param> parameters;
  public:
    SemId positional;
};

/// \brief Single subtree log entry
struct SubtreeLog : public Org {
  /// \brief Base value for the log variant
  struct DescribedLog {
    public:
      Opt<SemIdT<StmtList>> desc;
  };

  enum class Kind {
    Note,
    Refile,
    Clock,
    State,
    Tag,
  };

  char const* from_enum(Kind _result) {
    switch (_result) {
      case Kind::Note: return "Note";
      case Kind::Refile: return "Refile";
      case Kind::Clock: return "Clock";
      case Kind::State: return "State";
      case Kind::Tag: return "Tag";
    }
  }

  /// \brief Timestamped note
  struct Note : public DescribedLog {
    public:
      SemIdT<Time> on;
  };

  /// \brief Refiling action
  struct Refile : public DescribedLog {
    public:
      SemIdT<Time> on;
    public:
      SemIdT<Link> from;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public DescribedLog {
    public:
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
      SemIdT<Time> on;
    public:
      SemIdT<HashTag> tag;
    public:
      bool added;
  };

  public:
    LogEntry log;
};

/// \brief Subtree
struct Subtree : public Org {
  public:
    int level;
  public:
    Opt<QString> treeId;
  public:
    Opt<QString> todo;
  public:
    Opt<SemIdT<Completion>> completion;
  public:
    Vec<SemIdT<HashTag>> tags;
  public:
    SemIdT<Paragraph> title;
  public:
    Vec<SemIdT<SubtreeLog>> logbook;
  public:
    Vec<Property> properties;
  public:
    Opt<SemIdT<Time>> closed;
  public:
    Opt<SemIdT<Time>> deadline;
  public:
    Opt<SemIdT<Time>> scheduled;
};

/// \brief Latex code body
struct LatexBody : public Org {

};

/// \brief Inline math
struct InlineMath : public LatexBody {

};

/// \brief Final node
struct Leaf : public Org {
  public:
    QString text;
};

/// \brief Escaped text
struct Escaped : public Leaf {

};

/// \brief \n newline
struct Newline : public Leaf {

};

/// \brief ' ' space
struct Space : public Leaf {

};

/// \brief word
struct Word : public Leaf {

};

/// \brief @mention
struct AtMention : public Leaf {

};

struct RawText : public Leaf {

};

struct Punctuation : public Leaf {

};

struct Placeholder : public Leaf {

};

struct BigIdent : public Leaf {

};

struct Markup : public Org {

};

struct Bold : public Markup {

};

struct Underline : public Markup {

};

struct Monospace : public Markup {

};

struct MarkQuote : public Markup {

};

struct Verbatim : public Markup {

};

struct Italic : public Markup {

};

struct Strike : public Markup {

};

struct Par : public Markup {

};

struct List : public Org {
  public:
    bool isDescriptionList() const;
};

struct ListItem : public Org {

};

struct Link : public Org {

};

struct Document : public Org {

};

struct CommandGroup : public Org {

};

struct ParseError : public Org {

};

struct FileTarget : public Org {

};

struct TextSeparator : public Org {

};

struct Include : public Org {

};

struct DocumentOptions : public Org {

};

struct DocumentGroup : public Org {

};

} // namespace sem