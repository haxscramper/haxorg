/* clang-format off */
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
#include <sem/SemOrgBase.hpp>
#include <sem/SemOrgEnums.hpp>
namespace sem{
/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct Stmt : public sem::Org {
  using Org::Org;
  virtual ~Stmt() = default;
  Stmt() {}
  Stmt(CVec<SemId<Org>> attached, CVec<SemId<Org>> subnodes) : Org(subnodes), attached(attached) {}
  BOOST_DESCRIBE_CLASS(Stmt,
                       (Org),
                       (),
                       (),
                       (attached, (Opt<sem::SemId<sem::Org>>(OrgSemKind)) getAttached))
  Vec<sem::SemId<sem::Org>> attached;
  Opt<sem::SemId<sem::Org>> getAttached(OrgSemKind kind);
};

/// \brief Base class for all inline elements
struct Inline : public sem::Org {
  using Org::Org;
  virtual ~Inline() = default;
  BOOST_DESCRIBE_CLASS(Inline, (Org), (), (), ())
};

/// \brief Zero or more statement nodes
struct StmtList : public sem::Org {
  using Org::Org;
  virtual ~StmtList() = default;
  BOOST_DESCRIBE_CLASS(StmtList,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<StmtList>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<StmtList> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
};

/// \brief Node without content
struct Empty : public sem::Org {
  using Org::Org;
  virtual ~Empty() = default;
  BOOST_DESCRIBE_CLASS(Empty,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Empty>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Empty> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
};

/// \brief Table row
struct Row : public sem::Org {
  using Org::Org;
  virtual ~Row() = default;
  BOOST_DESCRIBE_CLASS(Row,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Row>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Row> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
};

/// \brief Table
struct Table : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~Table() = default;
  BOOST_DESCRIBE_CLASS(Table,
                       (Stmt),
                       (),
                       (),
                       (loc,
                        staticKind,
                        rows,
                        (sem::SemId<Table>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  Vec<sem::SemId<sem::Row>> rows = {};
  static sem::SemId<Table> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
};

/// \brief Single or nested inline hash-tag
struct HashTag : public sem::Inline {
  using Inline::Inline;
  virtual ~HashTag() = default;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (loc,
                        staticKind,
                        head,
                        subtags,
                        (sem::SemId<HashTag>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool(Vec<Str> const&) const) prefixMatch))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  Str head;
  /// \brief List of nested tags
  Vec<sem::SemId<sem::HashTag>> subtags = {};
  static sem::SemId<HashTag> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  /// \brief Check if list of tag names is a prefix for either of the nested hash tags in this one
  bool prefixMatch(Vec<Str> const& prefix) const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public sem::Inline {
  using Inline::Inline;
  virtual ~Footnote() = default;
  BOOST_DESCRIBE_CLASS(Footnote,
                       (Inline),
                       (),
                       (),
                       (loc,
                        staticKind,
                        tag,
                        definition,
                        (sem::SemId<Footnote>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  Str tag = "";
  /// \brief Link to possibly resolved definition
  Opt<sem::SemId<sem::Org>> definition = std::nullopt;
  static sem::SemId<Footnote> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Footnote; }
};

/// \brief Completion status of the subtree list element
struct Completion : public sem::Inline {
  using Inline::Inline;
  virtual ~Completion() = default;
  BOOST_DESCRIBE_CLASS(Completion,
                       (Inline),
                       (),
                       (),
                       (loc,
                        staticKind,
                        done,
                        full,
                        isPercent,
                        (sem::SemId<Completion>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
  static sem::SemId<Completion> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Completion; }
};

/// \brief Top-level or inline paragraph
struct Paragraph : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~Paragraph() = default;
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Paragraph>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isFootnoteDefinition))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Paragraph> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  /// \brief Check if paragraph defines footnote
  bool isFootnoteDefinition() const { return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote); }
};

/// \brief Base class for branch of formatting node classes
struct Format : public sem::Org {
  using Org::Org;
  virtual ~Format() = default;
  BOOST_DESCRIBE_CLASS(Format, (Org), (), (), ())
};

/// \brief Center nested content in export
struct Center : public sem::Format {
  using Format::Format;
  virtual ~Center() = default;
  BOOST_DESCRIBE_CLASS(Center,
                       (Format),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Center>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Center> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Center; }
};

/// \brief Base class for block or line commands
struct Command : public sem::Org {
  using Org::Org;
  virtual ~Command() = default;
  BOOST_DESCRIBE_CLASS(Command, (Org), (), (), ())
};

/// \brief Line commands
struct LineCommand : public sem::Command {
  using Command::Command;
  virtual ~LineCommand() = default;
  BOOST_DESCRIBE_CLASS(LineCommand, (Command), (), (), ())
};

/// \brief Standalone commands that can be placed individuall on the the top level and don't have to be attached to any subsequent elements
struct Standalone : public sem::LineCommand {
  using LineCommand::LineCommand;
  virtual ~Standalone() = default;
  BOOST_DESCRIBE_CLASS(Standalone, (LineCommand), (), (), ())
};

/// \brief Line command that might get attached to some block element
struct Attached : public sem::LineCommand {
  using LineCommand::LineCommand;
  virtual ~Attached() = default;
  BOOST_DESCRIBE_CLASS(Attached, (LineCommand), (), (), ())
};

/// \brief Caption annotation for any subsequent node
struct Caption : public sem::Attached {
  using Attached::Attached;
  virtual ~Caption() = default;
  BOOST_DESCRIBE_CLASS(Caption,
                       (Attached),
                       (),
                       (),
                       (loc,
                        staticKind,
                        text,
                        (sem::SemId<Caption>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Content description
  sem::SemId<sem::Paragraph> text = SemId<Paragraph>::Nil();
  static sem::SemId<Caption> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Caption; }
};

struct CmdName : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdName() = default;
  BOOST_DESCRIBE_CLASS(CmdName,
                       (Attached),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<CmdName>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<CmdName> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
};

struct CmdResults : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdResults() = default;
  BOOST_DESCRIBE_CLASS(CmdResults,
                       (Attached),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<CmdResults>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<CmdResults> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdResults; }
};

/// \brief Multiple attachable commands will get grouped into this element unless it is possible to attached them to some adjacent block command
struct CommandGroup : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~CommandGroup() = default;
  BOOST_DESCRIBE_CLASS(CommandGroup,
                       (Stmt),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<CommandGroup>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<CommandGroup> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CommandGroup; }
};

/// \brief Block command type
struct Block : public sem::Command {
  using Command::Command;
  virtual ~Block() = default;
  BOOST_DESCRIBE_CLASS(Block, (Command), (), (), ())
};

/// \brief Tblfm command type
struct Tblfm : public sem::Command {
  using Command::Command;
  virtual ~Tblfm() = default;
  BOOST_DESCRIBE_CLASS(Tblfm,
                       (Command),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Tblfm>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Tblfm> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Tblfm; }
};

/// \brief Quotation block
struct Quote : public sem::Org {
  using Org::Org;
  virtual ~Quote() = default;
  BOOST_DESCRIBE_CLASS(Quote,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Quote>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Quote> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Quote; }
};

/// \brief Verse quotation block
struct Verse : public sem::Block {
  using Block::Block;
  virtual ~Verse() = default;
  BOOST_DESCRIBE_CLASS(Verse,
                       (Block),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Verse>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Verse> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Verse; }
};

/// \brief Example block
struct Example : public sem::Block {
  using Block::Block;
  virtual ~Example() = default;
  BOOST_DESCRIBE_CLASS(Example,
                       (Block),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Example>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Example> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Example; }
};

/// \brief Additional arguments for command blocks
struct CmdArguments : public sem::Org {
  using Org::Org;
  virtual ~CmdArguments() = default;
  BOOST_DESCRIBE_CLASS(CmdArguments,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        positional,
                        named,
                        (sem::SemId<CmdArguments>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<sem::SemId<sem::CmdArgument>>(Str)) popArg))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Positional arguments that had no keys
  Vec<sem::SemId<sem::CmdArgument>> positional;
  /// \brief Stored key-value mapping
  UnorderedMap<Str, sem::SemId<sem::CmdArgument>> named;
  static sem::SemId<CmdArguments> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArguments; }
  /// \brief Remove argument value from the map and return it if present
  ///
  /// Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage
  Opt<sem::SemId<sem::CmdArgument>> popArg(Str key);
};

/// \brief Single key-value (or positional)
struct CmdArgument : public sem::Org {
  using Org::Org;
  virtual ~CmdArgument() = default;
  BOOST_DESCRIBE_CLASS(CmdArgument,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        key,
                        value,
                        (sem::SemId<CmdArgument>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Opt<int>() const) getInt,
                        (Opt<bool>() const) getBool,
                        (Str() const) getString))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Key
  Opt<Str> key = std::nullopt;
  /// \brief Value
  Str value;
  static sem::SemId<CmdArgument> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgument; }
  /// \brief Parse argument as integer value
  Opt<int> getInt() const;
  /// \brief Get argument as bool
  Opt<bool> getBool() const;
  /// \brief Get original string
  Str getString() const;
};

/// \brief Direct export passthrough
struct Export : public sem::Block {
  using Block::Block;
  virtual ~Export() = default;
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
                       (loc,
                        staticKind,
                        format,
                        exporter,
                        parameters,
                        placement,
                        content,
                        (sem::SemId<Export>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Export block type
  sem::Export::Format format = Format::Inline;
  /// \brief Exporter backend name
  Str exporter;
  /// \brief Additional parameters aside from 'exporter',
  Opt<sem::SemId<sem::CmdArguments>> parameters = std::nullopt;
  /// \brief Customized position of the text in the final exporting document.
  Opt<Str> placement = std::nullopt;
  /// \brief Raw exporter content string
  Str content;
  static sem::SemId<Export> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Export; }
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct AdmonitionBlock : public sem::Block {
  using Block::Block;
  virtual ~AdmonitionBlock() = default;
  BOOST_DESCRIBE_CLASS(AdmonitionBlock,
                       (Block),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<AdmonitionBlock>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<AdmonitionBlock> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::AdmonitionBlock; }
};

/// \brief Inline, statement or block call
struct Call : public sem::Org {
  using Org::Org;
  virtual ~Call() = default;
  BOOST_DESCRIBE_CLASS(Call,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        name,
                        (sem::SemId<Call>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Call target name
  Opt<Str> name = std::nullopt;
  static sem::SemId<Call> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
};

/// \brief Base class for all code blocks
struct Code : public sem::Block {
  using Block::Block;
  virtual ~Code() = default;
  /// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
  struct Switch {
    Switch() {}
    /// \brief Enumerate code lines starting from `start` value instead of default indexing.
    struct LineStart {
      LineStart() {}
      BOOST_DESCRIBE_CLASS(LineStart, (), (), (), (start, extendLast))
      /// \brief First line number
      int start;
      /// \brief Continue numbering from the previous block nstead of starting anew
      bool extendLast = false;
    };

    struct CalloutFormat {
      CalloutFormat() {}
      BOOST_DESCRIBE_CLASS(CalloutFormat, (), (), (), (format))
      Str format = "";
    };

    struct RemoveCallout {
      RemoveCallout() {}
      BOOST_DESCRIBE_CLASS(RemoveCallout, (), (), (), (remove))
      bool remove = true;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      EmphasizeLine() {}
      BOOST_DESCRIBE_CLASS(EmphasizeLine, (), (), (), (line))
      Vec<int> line = {};
    };

    struct Dedent {
      Dedent() {}
      BOOST_DESCRIBE_CLASS(Dedent, (), (), (), (value))
      int value = 0;
    };

    using Data = std::variant<sem::Code::Switch::LineStart, sem::Code::Switch::CalloutFormat, sem::Code::Switch::RemoveCallout, sem::Code::Switch::EmphasizeLine, sem::Code::Switch::Dedent>;
    enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
    using variant_enum_type = sem::Code::Switch::Kind;
    using variant_data_type = sem::Code::Switch::Data;
    BOOST_DESCRIBE_CLASS(Switch,
                         (),
                         (),
                         (),
                         (data,
                          (sem::Code::Switch::LineStart const&() const) getLineStart,
                          (sem::Code::Switch::LineStart&()) getLineStart,
                          (sem::Code::Switch::CalloutFormat const&() const) getCalloutFormat,
                          (sem::Code::Switch::CalloutFormat&()) getCalloutFormat,
                          (sem::Code::Switch::RemoveCallout const&() const) getRemoveCallout,
                          (sem::Code::Switch::RemoveCallout&()) getRemoveCallout,
                          (sem::Code::Switch::EmphasizeLine const&() const) getEmphasizeLine,
                          (sem::Code::Switch::EmphasizeLine&()) getEmphasizeLine,
                          (sem::Code::Switch::Dedent const&() const) getDedent,
                          (sem::Code::Switch::Dedent&()) getDedent,
                          (sem::Code::Switch::Kind(sem::Code::Switch::Data const&)) getKind,
                          (sem::Code::Switch::Kind() const) getKind))
    sem::Code::Switch::Data data;
    sem::Code::Switch::LineStart const& getLineStart() const { return std::get<0>(data); }
    sem::Code::Switch::LineStart& getLineStart() { return std::get<0>(data); }
    sem::Code::Switch::CalloutFormat const& getCalloutFormat() const { return std::get<1>(data); }
    sem::Code::Switch::CalloutFormat& getCalloutFormat() { return std::get<1>(data); }
    sem::Code::Switch::RemoveCallout const& getRemoveCallout() const { return std::get<2>(data); }
    sem::Code::Switch::RemoveCallout& getRemoveCallout() { return std::get<2>(data); }
    sem::Code::Switch::EmphasizeLine const& getEmphasizeLine() const { return std::get<3>(data); }
    sem::Code::Switch::EmphasizeLine& getEmphasizeLine() { return std::get<3>(data); }
    sem::Code::Switch::Dedent const& getDedent() const { return std::get<4>(data); }
    sem::Code::Switch::Dedent& getDedent() { return std::get<4>(data); }
    static sem::Code::Switch::Kind getKind(sem::Code::Switch::Data const& __input) { return static_cast<sem::Code::Switch::Kind>(__input.index()); }
    sem::Code::Switch::Kind getKind() const { return getKind(data); }
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
                       (loc,
                        staticKind,
                        lang,
                        switches,
                        exports,
                        parameters,
                        cache,
                        eval,
                        noweb,
                        hlines,
                        tangle,
                        (sem::SemId<Code>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<Str> lang = std::nullopt;
  /// \brief Switch options for block
  Vec<sem::Code::Switch> switches = {};
  /// \brief What to export
  sem::Code::Exports exports = Exports::Both;
  /// \brief Additional parameters that are language-specific
  Opt<sem::SemId<sem::CmdArguments>> parameters = std::nullopt;
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
  static sem::SemId<Code> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Code; }
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public sem::Org {
  using Org::Org;
  virtual ~Time() = default;
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
    enum class Period : short int { Year, Month, Week, Day, Hour, Minute, };
    BOOST_DESCRIBE_NESTED_ENUM(Period, Year, Month, Week, Day, Hour, Minute)
    BOOST_DESCRIBE_CLASS(Repeat, (), (), (), (mode, period, count))
    /// \brief mode
    sem::Time::Repeat::Mode mode;
    /// \brief period
    sem::Time::Repeat::Period period;
    /// \brief count
    int count;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static, (), (), (), (repeat, time))
    Opt<sem::Time::Repeat> repeat;
    UserTime time;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic, (), (), (), (expr))
    Str expr;
  };

  using TimeVariant = std::variant<sem::Time::Static, sem::Time::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = sem::Time::TimeKind;
  using variant_data_type = sem::Time::TimeVariant;
  BOOST_DESCRIBE_CLASS(Time,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        isActive,
                        time,
                        (sem::SemId<Time>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (sem::Time::Static const&() const) getStatic,
                        (sem::Time::Static&()) getStatic,
                        (sem::Time::Dynamic const&() const) getDynamic,
                        (sem::Time::Dynamic&()) getDynamic,
                        (sem::Time::TimeKind(sem::Time::TimeVariant const&)) getTimeKind,
                        (sem::Time::TimeKind() const) getTimeKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  sem::Time::TimeVariant time;
  static sem::SemId<Time> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
  sem::Time::Static const& getStatic() const { return std::get<0>(time); }
  sem::Time::Static& getStatic() { return std::get<0>(time); }
  sem::Time::Dynamic const& getDynamic() const { return std::get<1>(time); }
  sem::Time::Dynamic& getDynamic() { return std::get<1>(time); }
  static sem::Time::TimeKind getTimeKind(sem::Time::TimeVariant const& __input) { return static_cast<sem::Time::TimeKind>(__input.index()); }
  sem::Time::TimeKind getTimeKind() const { return getTimeKind(time); }
};

/// \brief Range of time delimited by two points
struct TimeRange : public sem::Org {
  using Org::Org;
  virtual ~TimeRange() = default;
  BOOST_DESCRIBE_CLASS(TimeRange,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        from,
                        to,
                        (sem::SemId<TimeRange>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Starting time
  sem::SemId<sem::Time> from = SemId<Time>::Nil();
  /// \brief Finishing time
  sem::SemId<sem::Time> to = SemId<Time>::Nil();
  static sem::SemId<TimeRange> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
};

/// \brief Inline macro invocation
struct Macro : public sem::Org {
  using Org::Org;
  virtual ~Macro() = default;
  BOOST_DESCRIBE_CLASS(Macro,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        name,
                        arguments,
                        (sem::SemId<Macro>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Macro name
  Str name = "";
  /// \brief Raw uninterpreted macro arguments
  Vec<Str> arguments = {};
  static sem::SemId<Macro> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
};

/// \brief Text symbol or symbol command
struct Symbol : public sem::Org {
  using Org::Org;
  virtual ~Symbol() = default;
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
                       (loc,
                        staticKind,
                        name,
                        parameters,
                        positional,
                        (sem::SemId<Symbol>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  Str name;
  /// \brief Optional list of parameters
  Vec<sem::Symbol::Param> parameters;
  /// \brief Positional parameters
  Vec<sem::SemId<sem::Org>> positional;
  static sem::SemId<Symbol> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
};

/// \brief Single subtree log entry
struct SubtreeLog : public sem::Org {
  using Org::Org;
  virtual ~SubtreeLog() = default;
  /// \brief Base value for the log variant
  struct DescribedLog {
    DescribedLog() {}
    BOOST_DESCRIBE_CLASS(DescribedLog, (), (), (), (desc))
    /// \brief Optional description of the log entry
    Opt<sem::SemId<sem::StmtList>> desc = SemId<StmtList>::Nil();
  };

  /// \brief Priority added
  struct Priority : public sem::SubtreeLog::DescribedLog {
    /// \brief Priority change action
    enum class Action : short int { Added, Removed, Changed, };
    BOOST_DESCRIBE_NESTED_ENUM(Action, Added, Removed, Changed)
    Priority() {}
    BOOST_DESCRIBE_CLASS(Priority, (DescribedLog), (), (), (oldPriority, newPriority, on))
    /// \brief Previous priority for change and removal
    Opt<std::string> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<std::string> newPriority = std::nullopt;
    /// \brief When priority was changed
    sem::SemId<sem::Time> on = SemId<Time>::Nil();
  };

  /// \brief Timestamped note
  struct Note : public sem::SubtreeLog::DescribedLog {
    Note() {}
    BOOST_DESCRIBE_CLASS(Note, (DescribedLog), (), (), (on))
    /// \brief Where log was taken
    sem::SemId<sem::Time> on = SemId<Time>::Nil();
  };

  /// \brief Refiling action
  struct Refile : public sem::SubtreeLog::DescribedLog {
    Refile() {}
    BOOST_DESCRIBE_CLASS(Refile, (DescribedLog), (), (), (on, from))
    /// \brief When the refiling happened
    sem::SemId<sem::Time> on = SemId<Time>::Nil();
    /// \brief Link to the original subtree
    sem::SemId<sem::Link> from = SemId<Link>::Nil();
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public sem::SubtreeLog::DescribedLog {
    Clock() {}
    BOOST_DESCRIBE_CLASS(Clock, (DescribedLog), (), (), (range))
    /// \brief Start-end or only start period
    Variant<sem::SemId<sem::Time>, sem::SemId<sem::TimeRange>> range = SemId<Time>::Nil();
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public sem::SubtreeLog::DescribedLog {
    State() {}
    BOOST_DESCRIBE_CLASS(State, (DescribedLog), (), (), (from, to, on))
    OrgBigIdentKind from;
    OrgBigIdentKind to;
    sem::SemId<sem::Time> on = SemId<Time>::Nil();
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public sem::SubtreeLog::DescribedLog {
    Tag() {}
    BOOST_DESCRIBE_CLASS(Tag, (DescribedLog), (), (), (on, tag, added))
    /// \brief When the log was assigned
    sem::SemId<sem::Time> on = SemId<Time>::Nil();
    /// \brief Tag in question
    sem::SemId<sem::HashTag> tag = SemId<HashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
  };

  using LogEntry = std::variant<sem::SubtreeLog::Priority, sem::SubtreeLog::Note, sem::SubtreeLog::Refile, sem::SubtreeLog::Clock, sem::SubtreeLog::State, sem::SubtreeLog::Tag>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Tag, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Tag)
  using variant_enum_type = sem::SubtreeLog::Kind;
  using variant_data_type = sem::SubtreeLog::LogEntry;
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        log,
                        (sem::SemId<SubtreeLog>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (void(sem::SemId<sem::StmtList>)) setDescription,
                        (sem::SubtreeLog::Priority const&() const) getPriority,
                        (sem::SubtreeLog::Priority&()) getPriority,
                        (sem::SubtreeLog::Note const&() const) getNote,
                        (sem::SubtreeLog::Note&()) getNote,
                        (sem::SubtreeLog::Refile const&() const) getRefile,
                        (sem::SubtreeLog::Refile&()) getRefile,
                        (sem::SubtreeLog::Clock const&() const) getClock,
                        (sem::SubtreeLog::Clock&()) getClock,
                        (sem::SubtreeLog::State const&() const) getState,
                        (sem::SubtreeLog::State&()) getState,
                        (sem::SubtreeLog::Tag const&() const) getTag,
                        (sem::SubtreeLog::Tag&()) getTag,
                        (sem::SubtreeLog::Kind(sem::SubtreeLog::LogEntry const&)) getLogKind,
                        (sem::SubtreeLog::Kind() const) getLogKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  sem::SubtreeLog::LogEntry log = Note{};
  static sem::SemId<SubtreeLog> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  void setDescription(sem::SemId<sem::StmtList> desc);
  sem::SubtreeLog::Priority const& getPriority() const { return std::get<0>(log); }
  sem::SubtreeLog::Priority& getPriority() { return std::get<0>(log); }
  sem::SubtreeLog::Note const& getNote() const { return std::get<1>(log); }
  sem::SubtreeLog::Note& getNote() { return std::get<1>(log); }
  sem::SubtreeLog::Refile const& getRefile() const { return std::get<2>(log); }
  sem::SubtreeLog::Refile& getRefile() { return std::get<2>(log); }
  sem::SubtreeLog::Clock const& getClock() const { return std::get<3>(log); }
  sem::SubtreeLog::Clock& getClock() { return std::get<3>(log); }
  sem::SubtreeLog::State const& getState() const { return std::get<4>(log); }
  sem::SubtreeLog::State& getState() { return std::get<4>(log); }
  sem::SubtreeLog::Tag const& getTag() const { return std::get<5>(log); }
  sem::SubtreeLog::Tag& getTag() { return std::get<5>(log); }
  static sem::SubtreeLog::Kind getLogKind(sem::SubtreeLog::LogEntry const& __input) { return static_cast<sem::SubtreeLog::Kind>(__input.index()); }
  sem::SubtreeLog::Kind getLogKind() const { return getLogKind(log); }
};

/// \brief Subtree
struct Subtree : public sem::Org {
  using Org::Org;
  virtual ~Subtree() = default;
  /// \brief Type of the subtree associated time periods
  struct Period {
    Period() {}
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
    Period(CR<Variant<SemId<Time>, SemId<TimeRange>>> period, Kind kind) : period(period), kind(kind) {}
    BOOST_DESCRIBE_CLASS(Period,
                         (),
                         (),
                         (),
                         (kind,
                          period,
                          (sem::SemId<sem::Time>()) getTime,
                          (sem::SemId<sem::TimeRange>()) getTimeRange))
    /// \brief Time period kind -- not associated with point/range distinction
    sem::Subtree::Period::Kind kind;
    /// \brief Stored time point/range
    Variant<sem::SemId<sem::Time>, sem::SemId<sem::TimeRange>> period = sem::SemId<sem::Time>::Nil();
    /// \brief Get associated time point
    sem::SemId<sem::Time> getTime() { return std::get<SemId<Time>>(period); }
    /// \brief Get associated time period
    sem::SemId<sem::TimeRange> getTimeRange() { return std::get<SemId<TimeRange>>(period); }
  };

  /// \brief Single subtree property
  struct Property {
    Property() {}
    enum class SetMode : short int { Override, Add, Subtract, };
    BOOST_DESCRIBE_NESTED_ENUM(SetMode, Override, Add, Subtract)
    enum class InheritanceMode : short int { ThisAndSub, OnlyThis, OnlySub, };
    BOOST_DESCRIBE_NESTED_ENUM(InheritanceMode, ThisAndSub, OnlyThis, OnlySub)
    struct Nonblocking {
      Nonblocking() {}
      BOOST_DESCRIBE_CLASS(Nonblocking, (), (), (), (isBlocking))
      bool isBlocking;
    };

    struct Trigger {
      Trigger() {}
      BOOST_DESCRIBE_CLASS(Trigger, (), (), (), ())
    };

    struct Origin {
      Origin() {}
      BOOST_DESCRIBE_CLASS(Origin, (), (), (), (text))
      sem::SemId<sem::Paragraph> text = SemId<Paragraph>::Nil();
    };

    struct ExportLatexClass {
      ExportLatexClass() {}
      BOOST_DESCRIBE_CLASS(ExportLatexClass, (), (), (), (latexClass))
      Str latexClass;
    };

    struct ExportLatexClassOptions {
      ExportLatexClassOptions() {}
      BOOST_DESCRIBE_CLASS(ExportLatexClassOptions, (), (), (), (options))
      Vec<Str> options;
    };

    struct ExportLatexHeader {
      ExportLatexHeader() {}
      BOOST_DESCRIBE_CLASS(ExportLatexHeader, (), (), (), (header))
      Str header;
    };

    struct ExportLatexCompiler {
      ExportLatexCompiler() {}
      BOOST_DESCRIBE_CLASS(ExportLatexCompiler, (), (), (), (compiler))
      Str compiler;
    };

    struct Ordered {
      Ordered() {}
      BOOST_DESCRIBE_CLASS(Ordered, (), (), (), (isOrdered))
      bool isOrdered;
    };

    struct Effort {
      Effort() {}
      BOOST_DESCRIBE_CLASS(Effort, (), (), (), (hours, minutes))
      int hours = 0;
      int minutes = 0;
    };

    struct Visibility {
      Visibility() {}
      enum class Level : short int { Folded, Children, Content, All, };
      BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
      BOOST_DESCRIBE_CLASS(Visibility, (), (), (), (level))
      sem::Subtree::Property::Visibility::Level level;
    };

    struct ExportOptions {
      ExportOptions() {}
      BOOST_DESCRIBE_CLASS(ExportOptions, (), (), (), (backend, values))
      Str backend;
      UnorderedMap<Str, Str> values;
    };

    struct Blocker {
      Blocker() {}
      BOOST_DESCRIBE_CLASS(Blocker, (), (), (), (blockers))
      Vec<Str> blockers;
    };

    struct Unnumbered {
      Unnumbered() {}
      BOOST_DESCRIBE_CLASS(Unnumbered, (), (), (), ())
    };

    struct Created {
      Created() {}
      BOOST_DESCRIBE_CLASS(Created, (), (), (), (time))
      sem::SemId<sem::Time> time = SemId<Time>::Nil();
    };

    /// \brief Unknown property name
    struct Unknown {
      Unknown() {}
      BOOST_DESCRIBE_CLASS(Unknown, (), (), (), (value))
      /// \brief Converted value of the property
      sem::SemId<sem::Org> value = SemId<Org>::Nil();
    };

    using Data = std::variant<sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Trigger, sem::Subtree::Property::Origin, sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::Ordered, sem::Subtree::Property::Effort, sem::Subtree::Property::Visibility, sem::Subtree::Property::ExportOptions, sem::Subtree::Property::Blocker, sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Created, sem::Subtree::Property::Unknown>;
    enum class Kind : short int { Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, Unknown, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, Unknown)
    using variant_enum_type = sem::Subtree::Property::Kind;
    using variant_data_type = sem::Subtree::Property::Data;
    Property(CR<Data> data) : data(data) {}
    bool matches(Kind kind, CR<std::string> subkind = "") const;
    BOOST_DESCRIBE_CLASS(Property,
                         (),
                         (),
                         (),
                         (mainSetRule,
                          subSetRule,
                          inheritanceMode,
                          data,
                          (sem::Subtree::Property::Nonblocking const&() const) getNonblocking,
                          (sem::Subtree::Property::Nonblocking&()) getNonblocking,
                          (sem::Subtree::Property::Trigger const&() const) getTrigger,
                          (sem::Subtree::Property::Trigger&()) getTrigger,
                          (sem::Subtree::Property::Origin const&() const) getOrigin,
                          (sem::Subtree::Property::Origin&()) getOrigin,
                          (sem::Subtree::Property::ExportLatexClass const&() const) getExportLatexClass,
                          (sem::Subtree::Property::ExportLatexClass&()) getExportLatexClass,
                          (sem::Subtree::Property::ExportLatexClassOptions const&() const) getExportLatexClassOptions,
                          (sem::Subtree::Property::ExportLatexClassOptions&()) getExportLatexClassOptions,
                          (sem::Subtree::Property::ExportLatexHeader const&() const) getExportLatexHeader,
                          (sem::Subtree::Property::ExportLatexHeader&()) getExportLatexHeader,
                          (sem::Subtree::Property::ExportLatexCompiler const&() const) getExportLatexCompiler,
                          (sem::Subtree::Property::ExportLatexCompiler&()) getExportLatexCompiler,
                          (sem::Subtree::Property::Ordered const&() const) getOrdered,
                          (sem::Subtree::Property::Ordered&()) getOrdered,
                          (sem::Subtree::Property::Effort const&() const) getEffort,
                          (sem::Subtree::Property::Effort&()) getEffort,
                          (sem::Subtree::Property::Visibility const&() const) getVisibility,
                          (sem::Subtree::Property::Visibility&()) getVisibility,
                          (sem::Subtree::Property::ExportOptions const&() const) getExportOptions,
                          (sem::Subtree::Property::ExportOptions&()) getExportOptions,
                          (sem::Subtree::Property::Blocker const&() const) getBlocker,
                          (sem::Subtree::Property::Blocker&()) getBlocker,
                          (sem::Subtree::Property::Unnumbered const&() const) getUnnumbered,
                          (sem::Subtree::Property::Unnumbered&()) getUnnumbered,
                          (sem::Subtree::Property::Created const&() const) getCreated,
                          (sem::Subtree::Property::Created&()) getCreated,
                          (sem::Subtree::Property::Unknown const&() const) getUnknown,
                          (sem::Subtree::Property::Unknown&()) getUnknown,
                          (sem::Subtree::Property::Kind(sem::Subtree::Property::Data const&)) getKind,
                          (sem::Subtree::Property::Kind() const) getKind))
    sem::Subtree::Property::SetMode mainSetRule = SetMode::Override;
    sem::Subtree::Property::SetMode subSetRule = SetMode::Override;
    sem::Subtree::Property::InheritanceMode inheritanceMode = InheritanceMode::ThisAndSub;
    sem::Subtree::Property::Data data;
    sem::Subtree::Property::Nonblocking const& getNonblocking() const { return std::get<0>(data); }
    sem::Subtree::Property::Nonblocking& getNonblocking() { return std::get<0>(data); }
    sem::Subtree::Property::Trigger const& getTrigger() const { return std::get<1>(data); }
    sem::Subtree::Property::Trigger& getTrigger() { return std::get<1>(data); }
    sem::Subtree::Property::Origin const& getOrigin() const { return std::get<2>(data); }
    sem::Subtree::Property::Origin& getOrigin() { return std::get<2>(data); }
    sem::Subtree::Property::ExportLatexClass const& getExportLatexClass() const { return std::get<3>(data); }
    sem::Subtree::Property::ExportLatexClass& getExportLatexClass() { return std::get<3>(data); }
    sem::Subtree::Property::ExportLatexClassOptions const& getExportLatexClassOptions() const { return std::get<4>(data); }
    sem::Subtree::Property::ExportLatexClassOptions& getExportLatexClassOptions() { return std::get<4>(data); }
    sem::Subtree::Property::ExportLatexHeader const& getExportLatexHeader() const { return std::get<5>(data); }
    sem::Subtree::Property::ExportLatexHeader& getExportLatexHeader() { return std::get<5>(data); }
    sem::Subtree::Property::ExportLatexCompiler const& getExportLatexCompiler() const { return std::get<6>(data); }
    sem::Subtree::Property::ExportLatexCompiler& getExportLatexCompiler() { return std::get<6>(data); }
    sem::Subtree::Property::Ordered const& getOrdered() const { return std::get<7>(data); }
    sem::Subtree::Property::Ordered& getOrdered() { return std::get<7>(data); }
    sem::Subtree::Property::Effort const& getEffort() const { return std::get<8>(data); }
    sem::Subtree::Property::Effort& getEffort() { return std::get<8>(data); }
    sem::Subtree::Property::Visibility const& getVisibility() const { return std::get<9>(data); }
    sem::Subtree::Property::Visibility& getVisibility() { return std::get<9>(data); }
    sem::Subtree::Property::ExportOptions const& getExportOptions() const { return std::get<10>(data); }
    sem::Subtree::Property::ExportOptions& getExportOptions() { return std::get<10>(data); }
    sem::Subtree::Property::Blocker const& getBlocker() const { return std::get<11>(data); }
    sem::Subtree::Property::Blocker& getBlocker() { return std::get<11>(data); }
    sem::Subtree::Property::Unnumbered const& getUnnumbered() const { return std::get<12>(data); }
    sem::Subtree::Property::Unnumbered& getUnnumbered() { return std::get<12>(data); }
    sem::Subtree::Property::Created const& getCreated() const { return std::get<13>(data); }
    sem::Subtree::Property::Created& getCreated() { return std::get<13>(data); }
    sem::Subtree::Property::Unknown const& getUnknown() const { return std::get<14>(data); }
    sem::Subtree::Property::Unknown& getUnknown() { return std::get<14>(data); }
    static sem::Subtree::Property::Kind getKind(sem::Subtree::Property::Data const& __input) { return static_cast<sem::Subtree::Property::Kind>(__input.index()); }
    sem::Subtree::Property::Kind getKind() const { return getKind(data); }
  };

  BOOST_DESCRIBE_CLASS(Subtree,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
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
                        (sem::SemId<Subtree>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Period>(IntSet<sem::Subtree::Period::Kind>) const) getTimePeriods,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperty,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getContextualProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getContextualProperty))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  Opt<Str> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<Str> todo = std::nullopt;
  /// \brief Task completion state
  Opt<sem::SemId<sem::Completion>> completion = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  /// \brief Trailing tags
  Vec<sem::SemId<sem::HashTag>> tags = {};
  /// \brief Main title
  sem::SemId<sem::Paragraph> title = SemId<Paragraph>::Nil();
  /// \brief Associated subtree log
  Vec<sem::SemId<sem::SubtreeLog>> logbook = {};
  /// \brief Immediate properties
  Vec<sem::Subtree::Property> properties = {};
  /// \brief When subtree was marked as closed
  Opt<sem::SemId<sem::Time>> closed = std::nullopt;
  /// \brief When is the deadline
  Opt<sem::SemId<sem::Time>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  Opt<sem::SemId<sem::Time>> scheduled = std::nullopt;
  static sem::SemId<Subtree> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  Vec<sem::Subtree::Period> getTimePeriods(IntSet<sem::Subtree::Period::Kind> kinds) const;
  Vec<sem::Subtree::Property> getProperties(sem::Subtree::Property::Kind kind, Str const& subkind = "") const;
  Opt<sem::Subtree::Property> getProperty(sem::Subtree::Property::Kind kind, Str const& subkind = "") const;
  Vec<sem::Subtree::Property> getContextualProperties(sem::Subtree::Property::Kind kind, Str const& subkind = "") const;
  Opt<sem::Subtree::Property> getContextualProperty(sem::Subtree::Property::Kind kind, Str const& subkind = "") const;
};

/// \brief Latex code body
struct LatexBody : public sem::Org {
  using Org::Org;
  virtual ~LatexBody() = default;
  BOOST_DESCRIBE_CLASS(LatexBody, (Org), (), (), ())
};

/// \brief Inline math
struct InlineMath : public sem::LatexBody {
  using LatexBody::LatexBody;
  virtual ~InlineMath() = default;
  BOOST_DESCRIBE_CLASS(InlineMath,
                       (LatexBody),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<InlineMath>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<InlineMath> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineMath; }
};

/// \brief Final node
struct Leaf : public sem::Org {
  using Org::Org;
  virtual ~Leaf() = default;
  BOOST_DESCRIBE_CLASS(Leaf, (Org), (), (), (text))
  /// \brief Final leaf value
  Str text = "";
};

/// \brief Escaped text
struct Escaped : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Escaped() = default;
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Escaped>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Escaped> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
};

/// \brief \n newline
struct Newline : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Newline() = default;
  BOOST_DESCRIBE_CLASS(Newline,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Newline>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Newline> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
};

/// \brief ' "space",
struct Space : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Space() = default;
  BOOST_DESCRIBE_CLASS(Space,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Space>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Space> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
};

/// \brief word
struct Word : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Word() = default;
  BOOST_DESCRIBE_CLASS(Word,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Word>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Word> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
};

/// \brief @mention
struct AtMention : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~AtMention() = default;
  BOOST_DESCRIBE_CLASS(AtMention,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<AtMention>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<AtMention> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
};

struct RawText : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~RawText() = default;
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<RawText>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<RawText> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
};

struct Punctuation : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Punctuation() = default;
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Punctuation>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Punctuation> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
};

struct Placeholder : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Placeholder() = default;
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Placeholder>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Placeholder> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
};

struct BigIdent : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~BigIdent() = default;
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<BigIdent>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<BigIdent> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
};

struct Markup : public sem::Org {
  using Org::Org;
  virtual ~Markup() = default;
  BOOST_DESCRIBE_CLASS(Markup, (Org), (), (), ())
};

struct Bold : public sem::Markup {
  using Markup::Markup;
  virtual ~Bold() = default;
  BOOST_DESCRIBE_CLASS(Bold,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Bold>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Bold> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
};

struct Underline : public sem::Markup {
  using Markup::Markup;
  virtual ~Underline() = default;
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Underline>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Underline> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
};

struct Monospace : public sem::Markup {
  using Markup::Markup;
  virtual ~Monospace() = default;
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Monospace>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Monospace> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
};

struct MarkQuote : public sem::Markup {
  using Markup::Markup;
  virtual ~MarkQuote() = default;
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<MarkQuote>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<MarkQuote> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
};

struct Verbatim : public sem::Markup {
  using Markup::Markup;
  virtual ~Verbatim() = default;
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Verbatim>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Verbatim> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
};

struct Italic : public sem::Markup {
  using Markup::Markup;
  virtual ~Italic() = default;
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Italic>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Italic> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
};

struct Strike : public sem::Markup {
  using Markup::Markup;
  virtual ~Strike() = default;
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Strike>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Strike> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
};

struct Par : public sem::Markup {
  using Markup::Markup;
  virtual ~Par() = default;
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<Par>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<Par> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
};

struct List : public sem::Org {
  using Org::Org;
  virtual ~List() = default;
  BOOST_DESCRIBE_CLASS(List,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<List>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionList))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<List> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  bool isDescriptionList() const;
};

struct ListItem : public sem::Org {
  using Org::Org;
  virtual ~ListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty)
  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        checkbox,
                        header,
                        (sem::SemId<ListItem>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionItem))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  sem::ListItem::Checkbox checkbox = Checkbox::None;
  Opt<sem::SemId<sem::Paragraph>> header = std::nullopt;
  static sem::SemId<ListItem> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool isDescriptionItem() const { return header.has_value(); }
};

struct Link : public sem::Org {
  using Org::Org;
  virtual ~Link() = default;
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

  using Data = std::variant<sem::Link::Raw, sem::Link::Id, sem::Link::Person, sem::Link::Footnote, sem::Link::File>;
  enum class Kind : short int { Raw, Id, Person, Footnote, File, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, Person, Footnote, File)
  using variant_enum_type = sem::Link::Kind;
  using variant_data_type = sem::Link::Data;
  BOOST_DESCRIBE_CLASS(Link,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        description,
                        data,
                        (sem::SemId<Link>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (sem::Link::Raw const&() const) getRaw,
                        (sem::Link::Raw&()) getRaw,
                        (sem::Link::Id const&() const) getId,
                        (sem::Link::Id&()) getId,
                        (sem::Link::Person const&() const) getPerson,
                        (sem::Link::Person&()) getPerson,
                        (sem::Link::Footnote const&() const) getFootnote,
                        (sem::Link::Footnote&()) getFootnote,
                        (sem::Link::File const&() const) getFile,
                        (sem::Link::File&()) getFile,
                        (sem::Link::Kind(sem::Link::Data const&)) getLinkKind,
                        (sem::Link::Kind() const) getLinkKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  sem::Link::Data data;
  static sem::SemId<Link> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  sem::Link::Raw const& getRaw() const { return std::get<0>(data); }
  sem::Link::Raw& getRaw() { return std::get<0>(data); }
  sem::Link::Id const& getId() const { return std::get<1>(data); }
  sem::Link::Id& getId() { return std::get<1>(data); }
  sem::Link::Person const& getPerson() const { return std::get<2>(data); }
  sem::Link::Person& getPerson() { return std::get<2>(data); }
  sem::Link::Footnote const& getFootnote() const { return std::get<3>(data); }
  sem::Link::Footnote& getFootnote() { return std::get<3>(data); }
  sem::Link::File const& getFile() const { return std::get<4>(data); }
  sem::Link::File& getFile() { return std::get<4>(data); }
  static sem::Link::Kind getLinkKind(sem::Link::Data const& __input) { return static_cast<sem::Link::Kind>(__input.index()); }
  sem::Link::Kind getLinkKind() const { return getLinkKind(data); }
};

struct DocumentOptions : public sem::Org {
  using Org::Org;
  virtual ~DocumentOptions() = default;
  struct DoExport {
    BOOST_DESCRIBE_CLASS(DoExport, (), (), (), (exportToc))
    bool exportToc;
  };

  struct ExportFixed {
    BOOST_DESCRIBE_CLASS(ExportFixed, (), (), (), (exportLevels))
    int exportLevels;
  };

  using TocExport = std::variant<sem::DocumentOptions::DoExport, sem::DocumentOptions::ExportFixed>;
  enum class TocExportKind : short int { DoExport, ExportFixed, };
  BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
  using variant_enum_type = sem::DocumentOptions::TocExportKind;
  using variant_data_type = sem::DocumentOptions::TocExport;
  enum class BrokenLinks : short int { Raise, Ignore, Mark, };
  BOOST_DESCRIBE_NESTED_ENUM(BrokenLinks, Raise, Ignore, Mark)
  enum class Visibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
  BOOST_DESCRIBE_CLASS(DocumentOptions,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
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
                        data,
                        (sem::SemId<DocumentOptions>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperty,
                        (sem::DocumentOptions::DoExport const&() const) getDoExport,
                        (sem::DocumentOptions::DoExport&()) getDoExport,
                        (sem::DocumentOptions::ExportFixed const&() const) getExportFixed,
                        (sem::DocumentOptions::ExportFixed&()) getExportFixed,
                        (sem::DocumentOptions::TocExportKind(sem::DocumentOptions::TocExport const&)) getTocExportKind,
                        (sem::DocumentOptions::TocExportKind() const) getTocExportKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  sem::DocumentOptions::BrokenLinks brokenLinks = BrokenLinks::Mark;
  sem::DocumentOptions::Visibility initialVisibility = Visibility::ShowEverything;
  sem::DocumentOptions::TocExport tocExport = DoExport{false};
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
  sem::DocumentOptions::TocExport data;
  static sem::SemId<DocumentOptions> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  Vec<sem::Subtree::Property> getProperties(sem::Subtree::Property::Kind kind, Str const& subKind = "") const;
  Opt<sem::Subtree::Property> getProperty(sem::Subtree::Property::Kind kind, Str const& subKind = "") const;
  sem::DocumentOptions::DoExport const& getDoExport() const { return std::get<0>(data); }
  sem::DocumentOptions::DoExport& getDoExport() { return std::get<0>(data); }
  sem::DocumentOptions::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
  sem::DocumentOptions::ExportFixed& getExportFixed() { return std::get<1>(data); }
  static sem::DocumentOptions::TocExportKind getTocExportKind(sem::DocumentOptions::TocExport const& __input) { return static_cast<sem::DocumentOptions::TocExportKind>(__input.index()); }
  sem::DocumentOptions::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
};

struct Document : public sem::Org {
  using Org::Org;
  virtual ~Document() = default;
  BOOST_DESCRIBE_CLASS(Document,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        title,
                        author,
                        creator,
                        email,
                        language,
                        options,
                        exportFileName,
                        (sem::SemId<Document>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(sem::Subtree::Property::Kind, Str const&) const) getProperty))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  Opt<sem::SemId<sem::Paragraph>> title = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> author = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> creator = std::nullopt;
  Opt<sem::SemId<sem::RawText>> email = std::nullopt;
  Vec<Str> language;
  sem::SemId<sem::DocumentOptions> options = SemId<DocumentOptions>::Nil();
  Opt<Str> exportFileName = std::nullopt;
  static sem::SemId<Document> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  Vec<sem::Subtree::Property> getProperties(sem::Subtree::Property::Kind kind, Str const& subKind = "") const;
  Opt<sem::Subtree::Property> getProperty(sem::Subtree::Property::Kind kind, Str const& subKind = "") const;
};

struct ParseError : public sem::Org {
  using Org::Org;
  virtual ~ParseError() = default;
  BOOST_DESCRIBE_CLASS(ParseError,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<ParseError>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<ParseError> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::ParseError; }
};

struct FileTarget : public sem::Org {
  using Org::Org;
  virtual ~FileTarget() = default;
  BOOST_DESCRIBE_CLASS(FileTarget,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        path,
                        line,
                        searchTarget,
                        restrictToHeadlines,
                        targetId,
                        regexp,
                        (sem::SemId<FileTarget>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  Str path;
  Opt<int> line = std::nullopt;
  Opt<Str> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  Opt<Str> targetId = std::nullopt;
  Opt<Str> regexp = std::nullopt;
  static sem::SemId<FileTarget> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
};

struct TextSeparator : public sem::Org {
  using Org::Org;
  virtual ~TextSeparator() = default;
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<TextSeparator>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<TextSeparator> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
};

struct Include : public sem::Org {
  using Org::Org;
  virtual ~Include() = default;
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

  using Data = std::variant<sem::Include::Example, sem::Include::Export, sem::Include::Src, sem::Include::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  using variant_enum_type = sem::Include::Kind;
  using variant_data_type = sem::Include::Data;
  BOOST_DESCRIBE_CLASS(Include,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        data,
                        (sem::SemId<Include>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind,
                        (sem::Include::Example const&() const) getExample,
                        (sem::Include::Example&()) getExample,
                        (sem::Include::Export const&() const) getExport,
                        (sem::Include::Export&()) getExport,
                        (sem::Include::Src const&() const) getSrc,
                        (sem::Include::Src&()) getSrc,
                        (sem::Include::OrgDocument const&() const) getOrgDocument,
                        (sem::Include::OrgDocument&()) getOrgDocument,
                        (sem::Include::Kind(sem::Include::Data const&)) getIncludeKind,
                        (sem::Include::Kind() const) getIncludeKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  sem::Include::Data data;
  static sem::SemId<Include> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::Include; }
  sem::Include::Example const& getExample() const { return std::get<0>(data); }
  sem::Include::Example& getExample() { return std::get<0>(data); }
  sem::Include::Export const& getExport() const { return std::get<1>(data); }
  sem::Include::Export& getExport() { return std::get<1>(data); }
  sem::Include::Src const& getSrc() const { return std::get<2>(data); }
  sem::Include::Src& getSrc() { return std::get<2>(data); }
  sem::Include::OrgDocument const& getOrgDocument() const { return std::get<3>(data); }
  sem::Include::OrgDocument& getOrgDocument() { return std::get<3>(data); }
  static sem::Include::Kind getIncludeKind(sem::Include::Data const& __input) { return static_cast<sem::Include::Kind>(__input.index()); }
  sem::Include::Kind getIncludeKind() const { return getIncludeKind(data); }
};

struct DocumentGroup : public sem::Org {
  using Org::Org;
  virtual ~DocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(DocumentGroup,
                       (Org),
                       (),
                       (),
                       (loc,
                        staticKind,
                        (sem::SemId<DocumentGroup>(Opt<OrgAdapter>)) create,
                        (OrgSemKind() const) getKind))
  /// \brief Document
  Opt<LineCol> loc;
  /// \brief Document
  static OrgSemKind const staticKind;
  static sem::SemId<DocumentGroup> create(Opt<OrgAdapter> original = std::nullopt);
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
};

}
/* clang-format on */