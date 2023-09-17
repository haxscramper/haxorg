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
namespace sem{
/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct Stmt : public Org {
  using Org::Org;
  Stmt() {}
  Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes) : Org(parent, subnodes), attached(attached) {}
  BOOST_DESCRIBE_CLASS(Stmt,
                       (Org),
                       (),
                       (),
                       (attached, (Opt<sem::SemId>(OrgSemKind)) getAttached))
  Vec<sem::SemId> attached;
  Opt<sem::SemId> getAttached(OrgSemKind kind);
};

/// \brief Base class for all inline elements
struct Inline : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Inline, (Org), (), (), ())
};

/// \brief Zero or more statement nodes
struct StmtList : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(StmtList,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<StmtList>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<StmtList> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
};

/// \brief Node without content
struct Empty : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Empty,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Empty>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Empty> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
};

/// \brief Table row
struct Row : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Row,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Row>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Row> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
};

/// \brief Table
struct Table : public Stmt {
  using Stmt::Stmt;
  BOOST_DESCRIBE_CLASS(Table,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        rows,
                        (sem::SemIdT<Table>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  Vec<sem::SemIdT<sem::Row>> rows = {};
  static sem::SemIdT<Table> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
};

/// \brief Single or nested inline hash-tag
struct HashTag : public Inline {
  using Inline::Inline;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        head,
                        subtags,
                        (sem::SemIdT<HashTag>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool(CR<Vec<Str>>) const) prefixMatch))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  Str head;
  /// \brief List of nested tags
  Vec<sem::SemIdT<sem::HashTag>> subtags = {};
  static sem::SemIdT<HashTag> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  /// \brief Check if list of tag names is a prefix for either of the nested hash tags in this one
  bool prefixMatch(CR<Vec<Str>> prefix) const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public Inline {
  using Inline::Inline;
  BOOST_DESCRIBE_CLASS(Footnote,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        tag,
                        definition,
                        (sem::SemIdT<Footnote>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  Str tag = "";
  /// \brief Link to possibly resolved definition
  Opt<sem::SemId> definition = std::nullopt;
  static sem::SemIdT<Footnote> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Footnote; }
};

/// \brief Completion status of the subtree list element
struct Completion : public Inline {
  using Inline::Inline;
  BOOST_DESCRIBE_CLASS(Completion,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        done,
                        full,
                        isPercent,
                        (sem::SemIdT<Completion>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
  static sem::SemIdT<Completion> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Completion; }
};

/// \brief Top-level or inline paragraph
struct Paragraph : public Stmt {
  using Stmt::Stmt;
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Paragraph>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isFootnoteDefinition))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Paragraph> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  /// \brief Check if paragraph defines footnote
  bool isFootnoteDefinition() const { return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote); }
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Format, (Org), (), (), ())
};

/// \brief Center nested content in export
struct Center : public Format {
  using Format::Format;
  BOOST_DESCRIBE_CLASS(Center,
                       (Format),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Center>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Center> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Center; }
};

/// \brief Base class for block or line commands
struct Command : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Command, (Org), (), (), ())
};

/// \brief Line commands
struct LineCommand : public Command {
  using Command::Command;
  BOOST_DESCRIBE_CLASS(LineCommand, (Command), (), (), ())
};

/// \brief Standalone commands that can be placed individuall on the the top level and don't have to be attached to any subsequent elements
struct Standalone : public LineCommand {
  using LineCommand::LineCommand;
  BOOST_DESCRIBE_CLASS(Standalone, (LineCommand), (), (), ())
};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {
  using LineCommand::LineCommand;
  BOOST_DESCRIBE_CLASS(Attached, (LineCommand), (), (), ())
};

/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
  using Attached::Attached;
  BOOST_DESCRIBE_CLASS(Caption,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        text,
                        (sem::SemIdT<Caption>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Content description
  sem::SemIdT<sem::Paragraph> text = SemIdT<Paragraph>::Nil();
  static sem::SemIdT<Caption> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Caption; }
};

/// \brief Multiple attachable commands will get grouped into this element unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
  using Stmt::Stmt;
  BOOST_DESCRIBE_CLASS(CommandGroup,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<CommandGroup>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<CommandGroup> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CommandGroup; }
};

/// \brief Block command type
struct Block : public Command {
  using Command::Command;
  BOOST_DESCRIBE_CLASS(Block, (Command), (), (), ())
};

/// \brief Quotation block
struct Quote : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Quote,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        text,
                        (sem::SemIdT<Quote>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Quote content
  sem::SemIdT<sem::Paragraph> text = SemIdT<Paragraph>::Nil();
  static sem::SemIdT<Quote> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Quote; }
};

/// \brief Example block
struct Example : public Block {
  using Block::Block;
  BOOST_DESCRIBE_CLASS(Example,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Example>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Example> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Example; }
};

/// \brief Additional arguments for command blocks
struct CmdArguments : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(CmdArguments,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        positional,
                        named,
                        (sem::SemIdT<CmdArguments>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<sem::SemIdT<sem::CmdArgument>>(Str)) popArg))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Positional arguments that had no keys
  Vec<sem::SemIdT<sem::CmdArgument>> positional;
  /// \brief Stored key-value mapping
  UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>> named;
  static sem::SemIdT<CmdArguments> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArguments; }
  /// \brief Remove argument value from the map and return it if present
  ///
  /// Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage
  Opt<sem::SemIdT<sem::CmdArgument>> popArg(Str key);
};

/// \brief Single key-value (or positional)
struct CmdArgument : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(CmdArgument,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        key,
                        value,
                        (sem::SemIdT<CmdArgument>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<int>() const) getInt,
                        (Opt<bool>() const) getBool,
                        (Str() const) getString))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Key
  Opt<Str> key = std::nullopt;
  /// \brief Value
  Str value;
  static sem::SemIdT<CmdArgument> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgument; }
  /// \brief Parse argument as integer value
  Opt<int> getInt() const;
  /// \brief Get argument as bool
  Opt<bool> getBool() const;
  /// \brief Get original string
  Str getString() const;
};

/// \brief Direct export passthrough
struct Export : public Block {
  using Block::Block;
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
  BOOST_DESCRIBE_CLASS(Export,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        format,
                        exporter,
                        parameters,
                        placement,
                        content,
                        (sem::SemIdT<Export>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Export block type
  Format format = Format::Inline;
  /// \brief Exporter backend name
  Str exporter;
  /// \brief Additional parameters aside from 'exporter',
  sem::SemIdT<sem::CmdArguments> parameters = SemIdT<CmdArguments>::Nil();
  /// \brief Customized position of the text in the final exporting document.
  Opt<Str> placement = std::nullopt;
  /// \brief Raw exporter content string
  Str content;
  static sem::SemIdT<Export> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Export; }
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct AdmonitionBlock : public Block {
  using Block::Block;
  BOOST_DESCRIBE_CLASS(AdmonitionBlock,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<AdmonitionBlock>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<AdmonitionBlock> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::AdmonitionBlock; }
};

/// \brief Base class for all code blocks
struct Code : public Block {
  using Block::Block;
  /// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
  struct Switch {
    /// \brief Enumerate code lines starting from `start` value instead of default indexing.
    struct LineStart {
      BOOST_DESCRIBE_CLASS(LineStart, (), (), (), (start, extendLast))
      /// \brief First line number
      int start;
      /// \brief Continue numbering from the previous block nstead of starting anew
      bool extendLast = false;
    };

    struct CalloutFormat {
      BOOST_DESCRIBE_CLASS(CalloutFormat, (), (), (), (format))
      Str format = "";
    };

    struct RemoveCallout {
      BOOST_DESCRIBE_CLASS(RemoveCallout, (), (), (), (remove))
      bool remove = true;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      BOOST_DESCRIBE_CLASS(EmphasizeLine, (), (), (), (line))
      Vec<int> line = {};
    };

    struct Dedent {
      BOOST_DESCRIBE_CLASS(Dedent, (), (), (), (value))
      int value = 0;
    };

    SUB_VARIANTS(Kind, Data, data, getKind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent);
    Data data;
    BOOST_DESCRIBE_CLASS(Switch,
                         (),
                         (),
                         (),
                         (data, (Kind() const) getKind))
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
  BOOST_DESCRIBE_CLASS(Code,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        lang,
                        switches,
                        exports,
                        parameters,
                        cache,
                        eval,
                        noweb,
                        hlines,
                        tangle,
                        (sem::SemIdT<Code>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<Str> lang = std::nullopt;
  /// \brief Switch options for block
  Vec<Switch> switches = {};
  /// \brief What to export
  Exports exports = Exports::Both;
  /// \brief Additional parameters that are language-specific
  sem::SemIdT<sem::CmdArguments> parameters = SemIdT<CmdArguments>::Nil();
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
  static sem::SemIdT<Code> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Code; }
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public Org {
  using Org::Org;
  bool isStatic() const { return std::holds_alternative<Static>(time); }
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
    enum class Period : short int {
      Year,
      Month,
      Week,
      Day,
      Hour,
      Minute,
    };
    BOOST_DESCRIBE_NESTED_ENUM(Period, Year, Month, Week, Day, Hour, Minute)
    BOOST_DESCRIBE_CLASS(Repeat, (), (), (), (mode, period, count))
    /// \brief mode
    Mode mode;
    /// \brief period
    Period period;
    /// \brief count
    int count;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static, (), (), (), (repeat, time))
    Opt<Repeat> repeat;
    UserTime time;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic, (), (), (), (expr))
    Str expr;
  };

  SUB_VARIANTS(TimeKind, TimeVariant, time, getTimeKind, Static, Dynamic);
  TimeVariant time;
  BOOST_DESCRIBE_CLASS(Time,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        isActive,
                        time,
                        (sem::SemIdT<Time>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (TimeKind() const) getTimeKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  static sem::SemIdT<Time> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
};

/// \brief Range of time delimited by two points
struct TimeRange : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(TimeRange,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        from,
                        to,
                        (sem::SemIdT<TimeRange>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Starting time
  sem::SemIdT<sem::Time> from = SemIdT<Time>::Nil();
  /// \brief Finishing time
  sem::SemIdT<sem::Time> to = SemIdT<Time>::Nil();
  static sem::SemIdT<TimeRange> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
};

/// \brief Inline macro invocation
struct Macro : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Macro,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        name,
                        arguments,
                        (sem::SemIdT<Macro>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Macro name
  Str name = "";
  /// \brief Raw uninterpreted macro arguments
  Vec<Str> arguments = {};
  static sem::SemIdT<Macro> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
};

/// \brief Text symbol or symbol command
struct Symbol : public Org {
  using Org::Org;
  /// \brief Symbol parameters
  struct Param {
    BOOST_DESCRIBE_CLASS(Param, (), (), (), (key, value))
    /// \brief Key -- for non-positional
    Opt<Str> key;
    /// \brief Uninterpreted value
    Str value;
  };

  BOOST_DESCRIBE_CLASS(Symbol,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        name,
                        parameters,
                        positional,
                        (sem::SemIdT<Symbol>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  Str name;
  /// \brief Optional list of parameters
  Vec<Param> parameters;
  /// \brief Positional parameters
  Vec<sem::SemId> positional;
  static sem::SemIdT<Symbol> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
};

/// \brief Single subtree log entry
struct SubtreeLog : public Org {
  using Org::Org;
  /// \brief Base value for the log variant
  struct DescribedLog {
    BOOST_DESCRIBE_CLASS(DescribedLog, (), (), (), (desc))
    /// \brief Optional description of the log entry
    Opt<sem::SemIdT<sem::StmtList>> desc = SemIdT<StmtList>::Nil();
  };

  /// \brief Priority added
  struct Priority : public DescribedLog {
    /// \brief Priority change action
    enum class Action : short int {
      Added,
      Removed,
      Changed,
    };
    BOOST_DESCRIBE_NESTED_ENUM(Action, Added, Removed, Changed)
    BOOST_DESCRIBE_CLASS(Priority, (DescribedLog), (), (), (oldPriority, newPriority, on))
    /// \brief Previous priority for change and removal
    Opt<QString> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<QString> newPriority = std::nullopt;
    /// \brief When priority was changed
    sem::SemIdT<sem::Time> on = SemIdT<Time>::Nil();
  };

  /// \brief Timestamped note
  struct Note : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Note, (DescribedLog), (), (), (on))
    /// \brief Where log was taken
    sem::SemIdT<sem::Time> on = SemIdT<Time>::Nil();
  };

  /// \brief Refiling action
  struct Refile : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Refile, (DescribedLog), (), (), (on, from))
    /// \brief When the refiling happened
    sem::SemIdT<sem::Time> on = SemIdT<Time>::Nil();
    /// \brief Link to the original subtree
    sem::SemIdT<sem::Link> from = SemIdT<Link>::Nil();
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Clock, (DescribedLog), (), (), (range))
    /// \brief Start-end or only start period
    Variant<sem::SemIdT<sem::Time>, sem::SemIdT<sem::TimeRange>> range = SemIdT<Time>::Nil();
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public DescribedLog {
    BOOST_DESCRIBE_CLASS(State, (DescribedLog), (), (), (from, to, on))
    OrgBigIdentKind from;
    OrgBigIdentKind to;
    sem::SemIdT<sem::Time> on = SemIdT<Time>::Nil();
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public DescribedLog {
    BOOST_DESCRIBE_CLASS(Tag, (DescribedLog), (), (), (on, tag, added))
    /// \brief When the log was assigned
    sem::SemIdT<sem::Time> on = SemIdT<Time>::Nil();
    /// \brief Tag in question
    sem::SemIdT<sem::HashTag> tag = SemIdT<HashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
  };

  SUB_VARIANTS(Kind, LogEntry, log, getLogKind, Priority, Note, Refile, Clock, State, Tag);
  LogEntry log = Note{};
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        log,
                        (sem::SemIdT<SubtreeLog>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (void(sem::SemIdT<sem::StmtList>)) setDescription,
                        (Kind() const) getLogKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<SubtreeLog> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  void setDescription(sem::SemIdT<sem::StmtList> desc);
};

/// \brief Subtree
struct Subtree : public Org {
  using Org::Org;
  /// \brief Type of the subtree associated time periods
  struct Period {
    /// \brief Period kind
    enum class Kind : short int {
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
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Clocked, Scheduled, Titled, Deadline, Created, Repeated)
    Period(CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period, Kind kind) : period(period), kind(kind) {}
    BOOST_DESCRIBE_CLASS(Period,
                         (),
                         (),
                         (),
                         (kind,
                          period,
                          (sem::SemIdT<sem::Time>()) getTime,
                          (sem::SemIdT<sem::Time>()) getTimeRange))
    /// \brief Time period kind -- not associated with point/range distinction
    Kind kind;
    /// \brief Stored time point/range
    Variant<sem::SemIdT<sem::Time>, sem::SemIdT<sem::TimeRange>> period;
    /// \brief Get associated time point
    sem::SemIdT<sem::Time> getTime() { return std::get<SemIdT<Time>>(period); }
    /// \brief Get associated time period
    sem::SemIdT<sem::Time> getTimeRange() { return std::get<SemIdT<TimeRange>>(period); }
  };

  /// \brief Single subtree property
  struct Property {
    enum class SetMode : short int {
      Override,
      Add,
      Subtract,
    };
    BOOST_DESCRIBE_NESTED_ENUM(SetMode, Override, Add, Subtract)
    enum class InheritanceMode : short int {
      ThisAndSub,
      OnlyThis,
      OnlySub,
    };
    BOOST_DESCRIBE_NESTED_ENUM(InheritanceMode, ThisAndSub, OnlyThis, OnlySub)
    struct Nonblocking {
      BOOST_DESCRIBE_CLASS(Nonblocking, (), (), (), (isBlocking))
      bool isBlocking;
    };

    struct Trigger {
      BOOST_DESCRIBE_CLASS(Trigger, (), (), (), ())
    };

    struct Origin {
      BOOST_DESCRIBE_CLASS(Origin, (), (), (), (text))
      Str text;
    };

    struct ExportLatexClass {
      BOOST_DESCRIBE_CLASS(ExportLatexClass, (), (), (), (latexClass))
      Str latexClass;
    };

    struct ExportLatexClassOptions {
      BOOST_DESCRIBE_CLASS(ExportLatexClassOptions, (), (), (), (options))
      Vec<Str> options;
    };

    struct ExportLatexHeader {
      BOOST_DESCRIBE_CLASS(ExportLatexHeader, (), (), (), (header))
      Str header;
    };

    struct ExportLatexCompiler {
      BOOST_DESCRIBE_CLASS(ExportLatexCompiler, (), (), (), (compiler))
      Str compiler;
    };

    struct Ordered {
      BOOST_DESCRIBE_CLASS(Ordered, (), (), (), (isOrdered))
      bool isOrdered;
    };

    struct Effort {
      BOOST_DESCRIBE_CLASS(Effort, (), (), (), (hours, minutes))
      int hours = 0;
      int minutes = 0;
    };

    struct Visibility {
      enum class Level : short int {
        Folded,
        Children,
        Content,
        All,
      };
      BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
      BOOST_DESCRIBE_CLASS(Visibility, (), (), (), (level))
      Level level;
    };

    struct ExportOptions {
      BOOST_DESCRIBE_CLASS(ExportOptions, (), (), (), (backend, values))
      Str backend;
      UnorderedMap<Str, Str> values;
    };

    struct Blocker {
      BOOST_DESCRIBE_CLASS(Blocker, (), (), (), (blockers))
      Vec<Str> blockers;
    };

    struct Unnumbered {
      BOOST_DESCRIBE_CLASS(Unnumbered, (), (), (), ())
    };

    struct Created {
      BOOST_DESCRIBE_CLASS(Created, (), (), (), (time))
      sem::SemIdT<sem::Time> time = SemIdT<Time>::Nil();
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created);
    Data data;
    Property(CR<Data> data) : data(data) {}
    bool matches(Kind kind, CR<QString> subkind = "") const;
    BOOST_DESCRIBE_CLASS(Property,
                         (),
                         (),
                         (),
                         (mainSetRule, subSetRule, inheritanceMode, data, (Kind() const) getKind))
    SetMode mainSetRule = SetMode::Override;
    SetMode subSetRule = SetMode::Override;
    InheritanceMode inheritanceMode = InheritanceMode::ThisAndSub;
  };

  BOOST_DESCRIBE_CLASS(Subtree,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        level,
                        treeId,
                        todo,
                        completion,
                        description,
                        tags,
                        title,
                        logbook,
                        properties,
                        closed,
                        deadline,
                        scheduled,
                        (sem::SemIdT<Subtree>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Vec<Period>(IntSet<Period::Kind>) const) getTimePeriods,
                        (Vec<Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperties,
                        (Opt<Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperty,
                        (Vec<Property>(Property::Kind, CR<Str>) const) getContextualProperties,
                        (Opt<Property>(Property::Kind, CR<Str>) const) getContextualProperty))
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  Opt<Str> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<Str> todo = std::nullopt;
  /// \brief Task completion state
  Opt<sem::SemIdT<sem::Completion>> completion = std::nullopt;
  Opt<sem::SemIdT<sem::Paragraph>> description = std::nullopt;
  /// \brief Trailing tags
  Vec<sem::SemIdT<sem::HashTag>> tags = {};
  /// \brief Main title
  sem::SemIdT<sem::Paragraph> title = SemIdT<Paragraph>::Nil();
  /// \brief Associated subtree log
  Vec<sem::SemIdT<sem::SubtreeLog>> logbook = {};
  /// \brief Immediate properties
  Vec<Property> properties = {};
  /// \brief When subtree was marked as closed
  Opt<sem::SemIdT<sem::Time>> closed = std::nullopt;
  /// \brief When is the deadline
  Opt<sem::SemIdT<sem::Time>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  Opt<sem::SemIdT<sem::Time>> scheduled = std::nullopt;
  static sem::SemIdT<Subtree> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  Vec<Period> getTimePeriods(IntSet<Period::Kind> kinds) const;
  Vec<Property> getProperties(sem::Subtree::Property::Kind kind, CR<Str> subkind = "") const;
  Opt<Property> getProperty(sem::Subtree::Property::Kind kind, CR<Str> subkind = "") const;
  Vec<Property> getContextualProperties(Property::Kind kind, CR<Str> subkind = "") const;
  Opt<Property> getContextualProperty(Property::Kind kind, CR<Str> subkind = "") const;
};

/// \brief Latex code body
struct LatexBody : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(LatexBody, (Org), (), (), ())
};

/// \brief Inline math
struct InlineMath : public LatexBody {
  using LatexBody::LatexBody;
  BOOST_DESCRIBE_CLASS(InlineMath,
                       (LatexBody),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<InlineMath>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<InlineMath> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineMath; }
};

/// \brief Final node
struct Leaf : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Leaf, (Org), (), (), (text))
  /// \brief Final leaf value
  Str text = "";
};

/// \brief Escaped text
struct Escaped : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Escaped>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Escaped> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
};

/// \brief \n newline
struct Newline : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Newline,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Newline>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Newline> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
};

/// \brief ' "space",
struct Space : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Space,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Space>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Space> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
};

/// \brief word
struct Word : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Word,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Word>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Word> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
};

/// \brief @mention
struct AtMention : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(AtMention,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<AtMention>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<AtMention> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
};

struct RawText : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<RawText>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<RawText> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
};

struct Punctuation : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Punctuation>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Punctuation> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
};

struct Placeholder : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Placeholder>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Placeholder> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
};

struct BigIdent : public Leaf {
  using Leaf::Leaf;
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<BigIdent>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<BigIdent> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
};

struct Markup : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Markup, (Org), (), (), ())
};

struct Bold : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Bold,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Bold>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Bold> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
};

struct Underline : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Underline>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Underline> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
};

struct Monospace : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Monospace>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Monospace> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
};

struct MarkQuote : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<MarkQuote>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<MarkQuote> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
};

struct Verbatim : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Verbatim>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Verbatim> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
};

struct Italic : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Italic>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Italic> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
};

struct Strike : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Strike>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Strike> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
};

struct Par : public Markup {
  using Markup::Markup;
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<Par>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Par> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
};

struct List : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(List,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<List>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionList))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<List> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  bool isDescriptionList() const;
};

struct ListItem : public Org {
  using Org::Org;
  enum class Checkbox : short int {
    None,
    Done,
    Empty,
  };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty)
  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        checkbox,
                        header,
                        (sem::SemIdT<ListItem>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionItem))
  /// \brief Document
  static OrgSemKind const staticKind;
  Checkbox checkbox = Checkbox::None;
  Opt<sem::SemIdT<sem::Paragraph>> header = std::nullopt;
  static sem::SemIdT<ListItem> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool isDescriptionItem() const { return header.has_value(); }
};

struct Link : public Org {
  using Org::Org;
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw, (), (), (), (text))
    Str text;
  };

  struct Id {
    BOOST_DESCRIBE_CLASS(Id, (), (), (), (text))
    Str text;
  };

  struct Person {
    BOOST_DESCRIBE_CLASS(Person, (), (), (), (name))
    Str name;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote, (), (), (), (target))
    Str target;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File, (), (), (), (file))
    Str file;
  };

  SUB_VARIANTS(Kind, Data, data, getLinkKind, Raw, Id, Person, Footnote, File);
  Data data;
  BOOST_DESCRIBE_CLASS(Link,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        description,
                        data,
                        (sem::SemIdT<Link>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<sem::SemId>(CR<sem::Document>) const) resolve,
                        (Opt<sem::SemId>() const) resolve,
                        (Kind() const) getLinkKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  Opt<sem::SemIdT<sem::Paragraph>> description = std::nullopt;
  static sem::SemIdT<Link> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  Opt<sem::SemId> resolve(CR<sem::Document> doc) const;
  Opt<sem::SemId> resolve() const;
};

struct Document : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(Document,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        idTable,
                        nameTable,
                        footnoteTable,
                        anchorTable,
                        title,
                        author,
                        creator,
                        email,
                        language,
                        options,
                        exportFileName,
                        (sem::SemIdT<Document>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<sem::SemId>(CR<sem::SemId>) const) resolve,
                        (Opt<sem::SemIdT<sem::Subtree>>(CR<Str>) const) getSubtree,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperty))
  /// \brief Document
  static OrgSemKind const staticKind;
  UnorderedMap<Str, sem::SemId> idTable;
  UnorderedMap<Str, sem::SemId> nameTable;
  UnorderedMap<Str, sem::SemId> footnoteTable;
  UnorderedMap<Str, sem::SemId> anchorTable;
  Opt<sem::SemIdT<sem::Paragraph>> title = std::nullopt;
  Opt<sem::SemIdT<sem::Paragraph>> author = std::nullopt;
  Opt<sem::SemIdT<sem::Paragraph>> creator = std::nullopt;
  Opt<sem::SemIdT<sem::RawText>> email = std::nullopt;
  Opt<Vec<Str>> language = std::nullopt;
  sem::SemIdT<sem::DocumentOptions> options = SemIdT<DocumentOptions>::Nil();
  Opt<Str> exportFileName = std::nullopt;
  static sem::SemIdT<Document> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  Opt<sem::SemId> resolve(CR<sem::SemId> node) const;
  Opt<sem::SemIdT<sem::Subtree>> getSubtree(CR<Str> id) const;
  Vec<sem::Subtree::Property> getProperties(sem::Subtree::Property::Kind kind, CR<Str> subKind = "") const;
  Opt<sem::Subtree::Property> getProperty(sem::Subtree::Property::Kind kind, CR<Str> subKind = "") const;
};

struct ParseError : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(ParseError,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<ParseError>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<ParseError> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::ParseError; }
};

struct FileTarget : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(FileTarget,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        path,
                        line,
                        searchTarget,
                        restrictToHeadlines,
                        targetId,
                        regexp,
                        (sem::SemIdT<FileTarget>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  Str path;
  Opt<int> line = std::nullopt;
  Opt<Str> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  Opt<Str> targetId = std::nullopt;
  Opt<Str> regexp = std::nullopt;
  static sem::SemIdT<FileTarget> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
};

struct TextSeparator : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<TextSeparator>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<TextSeparator> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
};

struct Include : public Org {
  using Org::Org;
  struct Example {
    BOOST_DESCRIBE_CLASS(Example, (), (), (), ())
  };

  struct Export {
    BOOST_DESCRIBE_CLASS(Export, (), (), (), ())
  };

  struct Src {
    BOOST_DESCRIBE_CLASS(Src, (), (), (), ())
  };

  struct OrgDocument {
    BOOST_DESCRIBE_CLASS(OrgDocument, (), (), (), ())
  };

  SUB_VARIANTS(Kind, Data, data, getIncludeKind, Example, Export, Src, OrgDocument);
  Data data;
  BOOST_DESCRIBE_CLASS(Include,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        data,
                        (sem::SemIdT<Include>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Kind() const) getIncludeKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<Include> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Include; }
};

struct DocumentOptions : public Org {
  using Org::Org;
  using TocExport = Variant<bool, int>;
  enum class BrokenLinks : short int {
    Raise,
    Ignore,
    Mark,
  };
  BOOST_DESCRIBE_NESTED_ENUM(BrokenLinks, Raise, Ignore, Mark)
  enum class Visibility : short int {
    Overview,
    Content,
    ShowAll,
    Show2Levels,
    Show3Levels,
    Show4Levels,
    Show5Levels,
    ShowEverything,
  };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
  BOOST_DESCRIBE_CLASS(DocumentOptions,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        brokenLinks,
                        initialVisibility,
                        tocExport,
                        properties,
                        smartQuotes,
                        emphasizedText,
                        specialStrings,
                        fixedWidthSections,
                        includeTimestamps,
                        preserveLineBreaks,
                        plaintextSubscripts,
                        exportArchived,
                        exportWithAuthor,
                        exportBrokenLinks,
                        exportWithClock,
                        exportWithCreator,
                        (sem::SemIdT<DocumentOptions>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, CR<Str>) const) getProperty))
  /// \brief Document
  static OrgSemKind const staticKind;
  BrokenLinks brokenLinks = BrokenLinks::Mark;
  Visibility initialVisibility = Visibility::ShowEverything;
  TocExport tocExport = false;
  Vec<sem::Subtree::Property> properties;
  bool smartQuotes = false;
  bool emphasizedText = false;
  bool specialStrings = false;
  bool fixedWidthSections = false;
  bool includeTimestamps = false;
  bool preserveLineBreaks = false;
  bool plaintextSubscripts = false;
  bool exportArchived = false;
  bool exportWithAuthor = false;
  bool exportBrokenLinks = false;
  bool exportWithClock = false;
  bool exportWithCreator = false;
  static sem::SemIdT<DocumentOptions> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  Vec<sem::Subtree::Property> getProperties(sem::Subtree::Property::Kind kind, CR<Str> subKind = "") const;
  Opt<sem::Subtree::Property> getProperty(sem::Subtree::Property::Kind kind, CR<Str> subKind = "") const;
};

struct DocumentGroup : public Org {
  using Org::Org;
  BOOST_DESCRIBE_CLASS(DocumentGroup,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        (sem::SemIdT<DocumentGroup>(sem::SemId, Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemIdT<DocumentGroup> create(sem::SemId parent, Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
};

}