/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org{
/// \brief Single key-value (or positional)
struct ImmCmdArgument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgument() = default;
  static OrgSemKind const staticKind;
  /// \brief Key
  Opt<ImmBox<Str>> key = std::nullopt;
  /// \brief When used in the `:var` assignment, this stores variable name
  Opt<ImmBox<Str>> varname = std::nullopt;
  /// \brief Value
  ImmBox<Str> value;
};

/// \brief Data type to wrap list of identical command arguments
struct ImmCmdArgumentList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgumentList() = default;
  static OrgSemKind const staticKind;
  /// \brief List of arguments
  ImmVec<org::ImmIdT<org::ImmCmdArgument>> args = {};
};

/// \brief Additional arguments for command blocks
struct ImmCmdArguments : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArguments() = default;
  static OrgSemKind const staticKind;
  /// \brief Positional arguments with no keys
  sem::ImmIdT<org::ImmCmdArgumentList> positional = org::ImmIdT<CmdArgumentList>::Nil();
  /// \brief Stored key-value mapping
  ImmMap<Str, org::ImmIdT<org::ImmCmdArgumentList>> named;
};

struct ImmErrorItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorItem() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> message;
  /// \brief Conversion function name where the error was created
  Opt<ImmBox<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<ImmBox<int>> line = std::nullopt;
};

/// \brief Group of value conversion errors
struct ImmErrorGroup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorGroup() = default;
  static OrgSemKind const staticKind;
  ImmVec<org::ImmIdT<org::ImmErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  Opt<ImmBox<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<ImmBox<Str>> line = std::nullopt;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct ImmStmt : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  ImmVec<org::ImmIdT<org::ImmOrg>> attached;
};

/// \brief Base class for all inline elements
struct ImmInline : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
};

/// \brief Zero or more statement nodes
struct ImmStmtList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  static OrgSemKind const staticKind;
};

/// \brief Node without content
struct ImmEmpty : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  static OrgSemKind const staticKind;
};

/// \brief Base class for block or line commands
struct ImmCmd : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  /// \brief Additional parameters aside from 'exporter',
  Opt<ImmBox<org::ImmIdT<org::ImmCmdArguments>>> parameters = std::nullopt;
};

/// \brief Block command type
struct ImmBlock : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
};

/// \brief Line commands
struct ImmLineCommand : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
};

/// \brief Line command that might get attached to some block element
struct ImmAttached : public org::ImmLineCommand {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
};

/// \brief Final node
struct ImmLeaf : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  /// \brief Final leaf value
  ImmBox<Str> text = "";
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdCaption : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCaption() = default;
  static OrgSemKind const staticKind;
  /// \brief Content description
  sem::ImmIdT<org::ImmParagraph> text = org::ImmIdT<Paragraph>::Nil();
};

/// \brief Name identifier for the statement elements.
struct ImmCmdName : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
};

/// \brief Custom line command with list of parsed arguments
struct ImmCmdCustomArgs : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCustomArgs() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
};

/// \brief Custom command with raw unparsed string value
struct ImmCmdCustomRaw : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomRaw() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  ImmBox<Str> text;
};

/// \brief Custom line command with text paragraph value
struct ImmCmdCustomText : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomText() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  sem::ImmIdT<org::ImmParagraph> text = org::ImmIdT<Paragraph>::Nil();
};

struct ImmCmdResults : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdResults() = default;
  static OrgSemKind const staticKind;
};

/// \brief Tblfm command type
struct ImmCmdTblfm : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  static OrgSemKind const staticKind;
};

/// \brief Single or nested inline hash-tag
struct ImmHashTag : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  ImmBox<Str> head;
  /// \brief List of nested tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> subtags = {};
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmFootnote : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmFootnote() = default;
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  ImmBox<Str> tag = "";
  /// \brief Link to possibly resolved definition
  Opt<ImmBox<org::ImmIdT<org::ImmOrg>>> definition = std::nullopt;
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct ImmTime : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTime() = default;
  /// \brief Repetition information for static time
  struct Repeat {
    /// \brief Timestamp repetition mode
    enum class Mode : short int {
      /// \brief Do not repeat task on completion
      None,
      /// \brief ?
      Exact,
      /// \brief Repeat on the first matching day in the future
      FirstMatch,
      /// \brief Repeat task on the same day next week/month/year
      SameDay,
    };
    BOOST_DESCRIBE_NESTED_ENUM(Mode, None, Exact, FirstMatch, SameDay)
    /// \brief Repetition period. Temporary placeholder for now, until I figure out what would be the proper way to represent whatever org can do ... which is to be determined as well
    enum class Period : short int { Year, Month, Week, Day, Hour, Minute, };
    BOOST_DESCRIBE_NESTED_ENUM(Period, Year, Month, Week, Day, Hour, Minute)
    /// \brief mode
    sem::Time::Repeat::Mode mode;
    /// \brief period
    sem::Time::Repeat::Period period;
    /// \brief count
    int count;
  };

  struct Static {
    Opt<ImmBox<sem::Time::Repeat>> repeat;
    UserTime time;
  };

  struct Dynamic {
    ImmBox<Str> expr;
  };

  using TimeVariant = std::variant<sem::Time::Static, sem::Time::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  sem::Time::TimeVariant time;
};

/// \brief Range of time delimited by two points
struct ImmTimeRange : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTimeRange() = default;
  static OrgSemKind const staticKind;
  /// \brief Starting time
  sem::ImmIdT<org::ImmTime> from = org::ImmIdT<Time>::Nil();
  /// \brief Finishing time
  sem::ImmIdT<org::ImmTime> to = org::ImmIdT<Time>::Nil();
};

/// \brief Inline macro invocation
struct ImmMacro : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMacro() = default;
  static OrgSemKind const staticKind;
  /// \brief Macro name
  ImmBox<Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  sem::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<CmdArguments>::Nil();
};

/// \brief Text symbol or symbol command
struct ImmSymbol : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymbol() = default;
  /// \brief Symbol parameters
  struct Param {
    /// \brief Key -- for non-positional
    Opt<ImmBox<Str>> key;
    /// \brief Uninterpreted value
    ImmBox<Str> value;
  };

  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  ImmBox<Str> name;
  /// \brief Optional list of parameters
  ImmVec<sem::Symbol::Param> parameters;
  /// \brief Positional parameters
  ImmVec<org::ImmIdT<org::ImmOrg>> positional;
};

/// \brief Escaped text
struct ImmEscaped : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  static OrgSemKind const staticKind;
};

/// \brief \n newline
struct ImmNewline : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  static OrgSemKind const staticKind;
};

/// \brief ' "space",
struct ImmSpace : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  static OrgSemKind const staticKind;
};

/// \brief word
struct ImmWord : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  static OrgSemKind const staticKind;
};

/// \brief @mention
struct ImmAtMention : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  static OrgSemKind const staticKind;
};

struct ImmRawText : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  static OrgSemKind const staticKind;
};

struct ImmPunctuation : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  static OrgSemKind const staticKind;
};

struct ImmPlaceholder : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  static OrgSemKind const staticKind;
};

struct BigIdent : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  static OrgSemKind const staticKind;
};

/// \brief ~<<<target>>>~
struct ImmRadioTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRadioTarget() = default;
  static OrgSemKind const staticKind;
};

/// \brief ~<<target>>~
struct ImmTextTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  static OrgSemKind const staticKind;
};

struct ImmMarkup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
};

struct ImmBold : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  static OrgSemKind const staticKind;
};

struct ImmUnderline : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  static OrgSemKind const staticKind;
};

struct ImmMonospace : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  static OrgSemKind const staticKind;
};

struct ImmMarkQuote : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  static OrgSemKind const staticKind;
};

struct ImmVerbatim : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  static OrgSemKind const staticKind;
};

struct ImmItalic : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  static OrgSemKind const staticKind;
};

struct ImmStrike : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  static OrgSemKind const staticKind;
};

struct ImmPar : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  static OrgSemKind const staticKind;
};

/// \brief Latex code body
struct ImmLatex : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  static OrgSemKind const staticKind;
};

struct ImmLink : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmLink() = default;
  struct Raw {
    ImmBox<Str> text;
  };

  struct Id {
    ImmBox<Str> text;
  };

  struct Person {
    ImmBox<Str> name;
  };

  struct UserProtocol {
    ImmBox<Str> protocol;
    ImmBox<Str> target;
  };

  struct Internal {
    ImmBox<Str> target;
  };

  struct Footnote {
    ImmBox<Str> target;
  };

  struct File {
    ImmBox<Str> file;
  };

  struct Attachment {
    ImmBox<Str> file;
  };

  using Data = std::variant<sem::Link::Raw, sem::Link::Id, sem::Link::Person, sem::Link::UserProtocol, sem::Link::Internal, sem::Link::Footnote, sem::Link::File, sem::Link::Attachment>;
  enum class Kind : short int { Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment)
  static OrgSemKind const staticKind;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  sem::Link::Data data;
};

/// \brief Center nested content in export
struct ImmBlockCenter : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCenter() = default;
  static OrgSemKind const staticKind;
};

/// \brief Quotation block
struct ImmBlockQuote : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  static OrgSemKind const staticKind;
};

/// \brief Comment block
struct ImmBlockComment : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  static OrgSemKind const staticKind;
};

/// \brief Verse quotation block
struct ImmBlockVerse : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  static OrgSemKind const staticKind;
};

/// \brief Example block
struct ImmBlockExample : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  static OrgSemKind const staticKind;
};

/// \brief Direct export passthrough
struct ImmBlockExport : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExport() = default;
  /// \brief Export block format type
  enum class Format : short int {
    /// \brief Export directly in the paragraph
    Inline,
    /// \brief Single line of export
    Line,
    /// \brief Multiple lines of export
    Block,
  };
  BOOST_DESCRIBE_NESTED_ENUM(Format, Inline, Line, Block)
  static OrgSemKind const staticKind;
  /// \brief Export block type
  sem::BlockExport::Format format = sem::BlockExport::Format::Inline;
  /// \brief Exporter backend name
  ImmBox<Str> exporter;
  /// \brief Customized position of the text in the final exporting document.
  Opt<ImmBox<Str>> placement = std::nullopt;
  /// \brief Raw exporter content string
  ImmBox<Str> content;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct ImmBlockAdmonition : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  static OrgSemKind const staticKind;
};

/// \brief Base class for all code blocks
struct ImmBlockCode : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCode() = default;
  struct Line {
    struct Part {
      struct Raw {
        ImmBox<Str> code;
      };

      struct Callout {
        ImmBox<Str> name;
      };

      struct Tangle {
        ImmBox<Str> target;
      };

      using Data = std::variant<sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Tangle>;
      enum class Kind : short int { Raw, Callout, Tangle, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
      sem::BlockCode::Line::Part::Data data;
    };

    /// \brief parts of the single line
    ImmVec<sem::BlockCode::Line::Part> parts = {};
  };

  /// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
  struct Switch {
    /// \brief Enumerate code lines starting from `start` value instead of default indexing.
    struct LineStart {
      /// \brief First line number
      int start;
      /// \brief Continue numbering from the previous block nstead of starting anew
      bool extendLast = false;
    };

    struct CalloutFormat {
      ImmBox<Str> format = "";
    };

    struct RemoveCallout {
      bool remove = true;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      ImmVec<int> line = {};
    };

    struct Dedent {
      int value = 0;
    };

    using Data = std::variant<sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::Dedent>;
    enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
    sem::BlockCode::Switch::Data data;
  };

  /// \brief What to do with newly evaluated result
  enum class Results : short int {
    /// \brief Remove old result, replace with new value
    Replace,
  };
  BOOST_DESCRIBE_NESTED_ENUM(Results, Replace)
  /// \brief What part of the code block should be visible in export
  enum class Exports : short int {
    /// \brief Hide both original code and run result
    None,
    /// \brief Show output and code
    Both,
    /// \brief Show only code
    Code,
    /// \brief Show only evaluation results
    Results,
  };
  BOOST_DESCRIBE_NESTED_ENUM(Exports, None, Both, Code, Results)
  struct EvalResult {
    /// \brief Default value
    struct None {};

    /// \brief Source code block evaluated to an org-mode node element
    struct OrgValue {
      /// \brief Parsed value of the evaluation result
      sem::ImmIdT<org::ImmOrg> value = org::ImmIdT<Org>::Nil();
    };

    /// \brief Output evaluation results to a file
    struct File {
      ImmBox<Str> path;
    };

    /// \brief Evaluation output is a raw text
    struct Raw {
      ImmBox<Str> text;
    };

    using Data = std::variant<sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::Raw>;
    enum class Kind : short int { None, OrgValue, File, Raw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, None, OrgValue, File, Raw)
    sem::BlockCode::EvalResult::Data data;
  };

  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<ImmBox<Str>> lang = std::nullopt;
  /// \brief Switch options for block
  ImmVec<sem::BlockCode::Switch> switches = {};
  /// \brief What to export
  sem::BlockCode::Exports exports = sem::BlockCode::Exports::Both;
  /// \brief Code evaluation results
  Opt<ImmBox<sem::BlockCode::EvalResult>> result = std::nullopt;
  /// \brief Collected code lines
  ImmVec<sem::BlockCode::Line> lines = {};
  /// \brief Do cache values?
  bool cache = false;
  /// \brief Eval on export?
  bool eval = false;
  /// \brief Web-tangle code on export/run
  bool noweb = false;
  /// \brief ?
  bool hlines = false;
  /// \brief ?
  bool tangle = false;
};

/// \brief Single subtree log entry
struct ImmSubtreeLog : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtreeLog() = default;
  /// \brief Base value for the log variant
  struct DescribedLog {
    /// \brief Optional description of the log entry
    Opt<ImmBox<org::ImmIdT<org::ImmStmtList>>> desc = std::nullopt;
  };

  /// \brief Priority added
  struct Priority : public sem::SubtreeLog::DescribedLog {
    /// \brief Priority change action
    enum class Action : short int {
      /// \brief `Priority B added on [timestamp]`
      Added,
      /// \brief `Priority C removed on [timestamp]`
      Removed,
      /// \brief `Priority B changed from C on [timestamp]`
      Changed,
    };
    BOOST_DESCRIBE_NESTED_ENUM(Action, Added, Removed, Changed)
    /// \brief Previous priority for change and removal
    Opt<ImmBox<std::string>> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<ImmBox<std::string>> newPriority = std::nullopt;
    /// \brief When priority was changed
    sem::ImmIdT<org::ImmTime> on = org::ImmIdT<Time>::Nil();
    /// \brief Which action taken
    sem::SubtreeLog::Priority::Action action;
  };

  /// \brief Timestamped note
  struct Note : public sem::SubtreeLog::DescribedLog {
    /// \brief Where log was taken
    sem::ImmIdT<org::ImmTime> on = org::ImmIdT<Time>::Nil();
  };

  /// \brief Refiling action
  struct Refile : public sem::SubtreeLog::DescribedLog {
    /// \brief When the refiling happened
    sem::ImmIdT<org::ImmTime> on = org::ImmIdT<Time>::Nil();
    /// \brief Link to the original subtree
    sem::ImmIdT<org::ImmLink> from = org::ImmIdT<Link>::Nil();
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public sem::SubtreeLog::DescribedLog {
    /// \brief Clock start time
    sem::ImmIdT<org::ImmTime> from = org::ImmIdT<Time>::Nil();
    /// \brief Optional end of the clock
    Opt<ImmBox<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public sem::SubtreeLog::DescribedLog {
    ImmBox<Str> from;
    ImmBox<Str> to;
    sem::ImmIdT<org::ImmTime> on = org::ImmIdT<Time>::Nil();
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public sem::SubtreeLog::DescribedLog {
    /// \brief When the log was assigned
    sem::ImmIdT<org::ImmTime> on = org::ImmIdT<Time>::Nil();
    /// \brief Tag in question
    sem::ImmIdT<org::ImmHashTag> tag = org::ImmIdT<HashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown : public sem::SubtreeLog::DescribedLog {};

  using LogEntry = std::variant<sem::SubtreeLog::Priority, sem::SubtreeLog::Note, sem::SubtreeLog::Refile, sem::SubtreeLog::Clock, sem::SubtreeLog::State, sem::SubtreeLog::Tag, sem::SubtreeLog::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Tag, Unknown)
  static OrgSemKind const staticKind;
  sem::SubtreeLog::LogEntry log = sem::SubtreeLog::Note{};
};

/// \brief Subtree
struct ImmSubtree : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtree() = default;
  /// \brief Type of the subtree associated time periods
  struct Period {
    /// \brief Period kind
    enum class Kind : short int {
      /// \brief Time period of the task execution.
      Clocked,
      /// \brief Task marked as closed
      Closed,
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
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Clocked, Closed, Scheduled, Titled, Deadline, Created, Repeated)
    /// \brief Time period kind -- not associated with point/range distinction
    sem::Subtree::Period::Kind kind;
    /// \brief Clock start time
    sem::ImmIdT<org::ImmTime> from = org::ImmIdT<Time>::Nil();
    /// \brief Optional end of the clock
    Opt<ImmBox<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
  };

  /// \brief Single subtree property
  struct Property {
    enum class SetMode : short int { Override, Add, Subtract, };
    BOOST_DESCRIBE_NESTED_ENUM(SetMode, Override, Add, Subtract)
    enum class InheritanceMode : short int { ThisAndSub, OnlyThis, OnlySub, };
    BOOST_DESCRIBE_NESTED_ENUM(InheritanceMode, ThisAndSub, OnlyThis, OnlySub)
    struct Nonblocking {
      bool isBlocking;
    };

    struct Trigger {};

    struct Origin {
      sem::ImmIdT<org::ImmParagraph> text = org::ImmIdT<Paragraph>::Nil();
    };

    struct ExportLatexClass {
      ImmBox<Str> latexClass;
    };

    struct ExportLatexClassOptions {
      ImmVec<Str> options;
    };

    struct ExportLatexHeader {
      ImmBox<Str> header;
    };

    struct ExportLatexCompiler {
      ImmBox<Str> compiler;
    };

    struct Ordered {
      bool isOrdered;
    };

    struct Effort {
      int hours = 0;
      int minutes = 0;
    };

    struct Visibility {
      enum class Level : short int { Folded, Children, Content, All, };
      BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
      sem::Subtree::Property::Visibility::Level level;
    };

    struct ExportOptions {
      ImmBox<Str> backend;
      ImmMap<Str, Str> values;
    };

    struct Blocker {
      ImmVec<Str> blockers;
    };

    struct Unnumbered {};

    struct Created {
      sem::ImmIdT<org::ImmTime> time = org::ImmIdT<Time>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomArgs {
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property target specialization
      Opt<ImmBox<Str>> sub = std::nullopt;
      /// \brief Property parameters
      sem::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<CmdArguments>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomRaw {
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property value
      ImmBox<Str> value = "";
    };

    using Data = std::variant<sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Trigger, sem::Subtree::Property::Origin, sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::Ordered, sem::Subtree::Property::Effort, sem::Subtree::Property::Visibility, sem::Subtree::Property::ExportOptions, sem::Subtree::Property::Blocker, sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Created, sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomRaw>;
    enum class Kind : short int { Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw)
    sem::Subtree::Property::SetMode mainSetRule = sem::Subtree::Property::SetMode::Override;
    sem::Subtree::Property::SetMode subSetRule = sem::Subtree::Property::SetMode::Override;
    sem::Subtree::Property::InheritanceMode inheritanceMode = sem::Subtree::Property::InheritanceMode::ThisAndSub;
    sem::Subtree::Property::Data data;
  };

  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  Opt<ImmBox<Str>> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<ImmBox<Str>> todo = std::nullopt;
  /// \brief Task completion state
  Opt<ImmBox<org::ImmIdT<org::ImmSubtreeCompletion>>> completion = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  /// \brief Trailing tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> tags = {};
  /// \brief Main title
  sem::ImmIdT<org::ImmParagraph> title = org::ImmIdT<Paragraph>::Nil();
  /// \brief Associated subtree log
  ImmVec<org::ImmIdT<org::ImmSubtreeLog>> logbook = {};
  /// \brief Immediate properties
  ImmVec<sem::Subtree::Property> properties = {};
  /// \brief When subtree was marked as closed
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> closed = std::nullopt;
  /// \brief When is the deadline
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  Opt<ImmBox<Str>> priority = std::nullopt;
};

/// \brief Completion status of the subtree list element
struct ImmSubtreeCompletion : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmSubtreeCompletion() = default;
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
};

/// \brief Table cell
struct ImmCell : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCell() = default;
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Table row
struct ImmRow : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmRow() = default;
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  ImmVec<org::ImmIdT<org::ImmCell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Table
struct ImmTable : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmTable() = default;
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  ImmVec<org::ImmIdT<org::ImmRow>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Top-level or inline paragraph
struct ImmParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  static OrgSemKind const staticKind;
};

/// \brief Top-level or inline paragraph with prefix annotation
struct ImmAnnotatedParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmAnnotatedParagraph() = default;
  struct None {};

  struct Footnote {
    ImmBox<Str> name;
  };

  struct Admonition {
    /// \brief Prefix admonition for the paragraph
    sem::ImmIdT<sem::BigIdent> name = org::ImmIdT<BigIdent>::Nil();
  };

  struct Timestamp {
    /// \brief Leading timestamp for the paragraph
    sem::ImmIdT<org::ImmTime> time = org::ImmIdT<Time>::Nil();
  };

  using Data = std::variant<sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Timestamp>;
  enum class AnnotationKind : short int { None, Footnote, Admonition, Timestamp, };
  BOOST_DESCRIBE_NESTED_ENUM(AnnotationKind, None, Footnote, Admonition, Timestamp)
  static OrgSemKind const staticKind;
  sem::AnnotatedParagraph::Data data;
};

/// \brief Shortened colon example block
struct ImmColonExample : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmColonExample() = default;
  static OrgSemKind const staticKind;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdAttr : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> target;
};

/// \brief Inline, statement or block call
struct ImmCall : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCall() = default;
  static OrgSemKind const staticKind;
  /// \brief Call target name
  ImmBox<Str> name;
  /// \brief Additional parameters aside from 'exporter',
  sem::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<CmdArguments>::Nil();
  bool isCommand = false;
};

struct ImmList : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  static OrgSemKind const staticKind;
};

struct ImmListItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, Partial, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty, Partial)
  static OrgSemKind const staticKind;
  sem::ListItem::Checkbox checkbox = sem::ListItem::Checkbox::None;
  /// \brief Description list item header
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  Opt<ImmBox<Str>> bullet = std::nullopt;
};

struct ImmDocumentOptions : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentOptions() = default;
  struct ExportConfig {
    struct TaskExport {
      ImmVec<Str> taskWhitelist = {};
    };

    enum class TagExport : short int {
      None,
      All,
      /// \brief Expot tags in subtree titles but not in the table of content
      NotInToc,
    };
    BOOST_DESCRIBE_NESTED_ENUM(TagExport, None, All, NotInToc)
    enum class TaskFiltering : short int {
      /// \brief Include tasks from the whitelist
      Whitelist,
      /// \brief Include tasks marked as done
      Done,
      /// \brief Exclude all task subtrees from export
      None,
      /// \brief Add all task subtrees to export
      All,
    };
    BOOST_DESCRIBE_NESTED_ENUM(TaskFiltering, Whitelist, Done, None, All)
    enum class BrokenLinks : short int { Raise, Ignore, Mark, };
    BOOST_DESCRIBE_NESTED_ENUM(BrokenLinks, Raise, Ignore, Mark)
    struct DoExport {
      bool exportToc;
    };

    struct ExportFixed {
      int exportLevels;
    };

    using TocExport = std::variant<sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::ExportFixed>;
    enum class TocExportKind : short int { DoExport, ExportFixed, };
    BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
    Opt<ImmBox<bool>> inlinetasks = std::nullopt;
    Opt<ImmBox<bool>> footnotes = std::nullopt;
    Opt<ImmBox<bool>> clock = std::nullopt;
    Opt<ImmBox<bool>> author = std::nullopt;
    Opt<ImmBox<bool>> emphasis = std::nullopt;
    Opt<ImmBox<bool>> specialStrings = std::nullopt;
    Opt<ImmBox<bool>> propertyDrawers = std::nullopt;
    Opt<ImmBox<bool>> statisticsCookies = std::nullopt;
    /// \brief Include todo keywords in export
    Opt<ImmBox<bool>> todoText = std::nullopt;
    sem::DocumentOptions::ExportConfig::BrokenLinks brokenLinks = sem::DocumentOptions::ExportConfig::BrokenLinks::Mark;
    sem::DocumentOptions::ExportConfig::TocExport tocExport = sem::DocumentOptions::ExportConfig::DoExport{false};
    sem::DocumentOptions::ExportConfig::TagExport tagExport = sem::DocumentOptions::ExportConfig::TagExport::All;
    sem::DocumentOptions::ExportConfig::TocExport data;
  };

  enum class Visibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
  static OrgSemKind const staticKind;
  sem::DocumentOptions::Visibility initialVisibility = sem::DocumentOptions::Visibility::ShowEverything;
  ImmVec<sem::Subtree::Property> properties = {};
  sem::DocumentOptions::ExportConfig exportConfig;
  Opt<ImmBox<bool>> fixedWidthSections = std::nullopt;
  Opt<ImmBox<bool>> startupIndented = std::nullopt;
  Opt<ImmBox<Str>> category = std::nullopt;
  Opt<ImmBox<Str>> setupfile = std::nullopt;
  Opt<ImmBox<int>> maxSubtreeLevelExport = std::nullopt;
};

struct ImmDocument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocument() = default;
  static OrgSemKind const staticKind;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> title = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> author = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> creator = std::nullopt;
  ImmVec<org::ImmIdT<org::ImmHashTag>> filetags = {};
  Opt<ImmBox<org::ImmIdT<org::ImmRawText>>> email = std::nullopt;
  ImmVec<Str> language = {};
  sem::ImmIdT<org::ImmDocumentOptions> options = org::ImmIdT<DocumentOptions>::Nil();
  Opt<ImmBox<Str>> exportFileName = std::nullopt;
};

struct ImmFileTarget : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmFileTarget() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> path;
  Opt<ImmBox<int>> line = std::nullopt;
  Opt<ImmBox<Str>> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  Opt<ImmBox<Str>> targetId = std::nullopt;
  Opt<ImmBox<Str>> regexp = std::nullopt;
};

struct ImmTextSeparator : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  static OrgSemKind const staticKind;
};

struct ImmInclude : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInclude() = default;
  struct Example {};

  struct Export {};

  struct Src {};

  struct OrgDocument {
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    Opt<ImmBox<int>> minLevel = std::nullopt;
  };

  using Data = std::variant<sem::Include::Example, sem::Include::Export, sem::Include::Src, sem::Include::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  static OrgSemKind const staticKind;
  /// \brief Path to include
  ImmBox<Str> path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  Opt<ImmBox<int>> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  Opt<ImmBox<int>> lastLine = std::nullopt;
  sem::Include::Data data;
};

struct ImmDocumentGroup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentGroup() = default;
  static OrgSemKind const staticKind;
};

}
/* clang-format on */