/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org::imm {
/// \brief No node
struct None : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmNone() = default;
  BOOST_DESCRIBE_CLASS(None,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::None; }
  bool operator==(org::sem::None const& other) const;
};

struct ErrorItem : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ErrorItem,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        message,
                        function,
                        line))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> message;
  /// \brief Conversion function name where the error was created
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorItem; }
  bool operator==(org::sem::ErrorItem const& other) const;
};

/// \brief Group of value conversion errors
struct ErrorGroup : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorGroup() = default;
  BOOST_DESCRIBE_CLASS(ErrorGroup,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        diagnostics,
                        function,
                        line))
  static OrgSemKind const staticKind;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::ErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorGroup; }
  bool operator==(org::sem::ErrorGroup const& other) const;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct Stmt : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  BOOST_DESCRIBE_CLASS(Stmt,
                       (Org),
                       (),
                       (),
                       (attached))
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::Org>> attached;
  bool operator==(org::sem::Stmt const& other) const;
};

/// \brief Base class for all inline elements
struct Inline : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
  BOOST_DESCRIBE_CLASS(Inline,
                       (Org),
                       (),
                       (),
                       ())
  bool operator==(org::sem::Inline const& other) const;
};

/// \brief Zero or more statement nodes
struct StmtList : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  BOOST_DESCRIBE_CLASS(StmtList,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
  bool operator==(org::sem::StmtList const& other) const;
};

/// \brief Node without content
struct Empty : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  BOOST_DESCRIBE_CLASS(Empty,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
  bool operator==(org::sem::Empty const& other) const;
};

/// \brief Base class for block or line commands
struct Cmd : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  BOOST_DESCRIBE_CLASS(Cmd,
                       (Stmt),
                       (),
                       (),
                       (attrs))
  /// \brief Additional parameters aside from 'exporter',
  hstd::ext::ImmBox<hstd::Opt<org::sem::AttrGroup>> attrs = std::nullopt;
  bool operator==(org::sem::Cmd const& other) const;
};

/// \brief Block command type
struct Block : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
  BOOST_DESCRIBE_CLASS(Block,
                       (Cmd),
                       (),
                       (),
                       ())
  bool operator==(org::sem::Block const& other) const;
};

/// \brief Line commands
struct LineCommand : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
  BOOST_DESCRIBE_CLASS(LineCommand,
                       (Cmd),
                       (),
                       (),
                       ())
  bool operator==(org::sem::LineCommand const& other) const;
};

/// \brief Line command that might get attached to some block element
struct Attached : public org::sem::LineCommand {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
  BOOST_DESCRIBE_CLASS(Attached,
                       (LineCommand),
                       (),
                       (),
                       ())
  bool operator==(org::sem::Attached const& other) const;
};

/// \brief Final node
struct Leaf : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  BOOST_DESCRIBE_CLASS(Leaf,
                       (Org),
                       (),
                       (),
                       (text))
  /// \brief Final leaf value
  hstd::ext::ImmBox<hstd::Str> text = "";
  bool operator==(org::sem::Leaf const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct CmdCaption : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCaption() = default;
  BOOST_DESCRIBE_CLASS(CmdCaption,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        text))
  static OrgSemKind const staticKind;
  /// \brief Content description
  org::imm::ImmIdT<org::sem::Paragraph> text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
  bool operator==(org::sem::CmdCaption const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct CmdColumns : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdColumns() = default;
  BOOST_DESCRIBE_CLASS(CmdColumns,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        view))
  static OrgSemKind const staticKind;
  org::sem::ColumnView view;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdColumns; }
  bool operator==(org::sem::CmdColumns const& other) const;
};

/// \brief Name identifier for the statement elements.
struct CmdName : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  BOOST_DESCRIBE_CLASS(CmdName,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
  bool operator==(org::sem::CmdName const& other) const;
};

/// \brief Custom line command with list of parsed arguments
struct CmdCustomArgs : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCustomArgs() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomArgs,
                       (Cmd),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomArgs; }
  bool operator==(org::sem::CmdCustomArgs const& other) const;
};

/// \brief Custom command with raw unparsed string value
struct CmdCustomRaw : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomRaw() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomRaw,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached,
                        text))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  hstd::ext::ImmBox<hstd::Str> text;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomRaw; }
  bool operator==(org::sem::CmdCustomRaw const& other) const;
};

/// \brief Custom line command with text paragraph value
struct CmdCustomText : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomText() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomText,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached,
                        text))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  org::imm::ImmIdT<org::sem::Paragraph> text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomText; }
  bool operator==(org::sem::CmdCustomText const& other) const;
};

struct CmdResults : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdResults() = default;
  BOOST_DESCRIBE_CLASS(CmdResults,
                       (Attached),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdResults; }
  bool operator==(org::sem::CmdResults const& other) const;
};

/// \brief Tblfm command type
struct CmdTblfm : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(CmdTblfm,
                       (Cmd),
                       (),
                       (),
                       (staticKind,
                        expr))
  static OrgSemKind const staticKind;
  org::sem::Tblfm expr;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
  bool operator==(org::sem::CmdTblfm const& other) const;
};

struct HashTag : public org::sem::Inline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        text))
  static OrgSemKind const staticKind;
  org::sem::HashTagText text;
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  bool operator==(org::sem::HashTag const& other) const;
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct InlineFootnote : public org::sem::Inline {
  using ImmInline::ImmInline;
  virtual ~ImmInlineFootnote() = default;
  BOOST_DESCRIBE_CLASS(InlineFootnote,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        tag,
                        definition))
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  hstd::ext::ImmBox<hstd::Str> tag = "";
  /// \brief Link to possibly resolved definition
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Org>>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineFootnote; }
  bool operator==(org::sem::InlineFootnote const& other) const;
};

/// \brief Inline export
struct InlineExport : public org::sem::Inline {
  using ImmInline::ImmInline;
  virtual ~ImmInlineExport() = default;
  BOOST_DESCRIBE_CLASS(InlineExport,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineExport; }
  bool operator==(org::sem::InlineExport const& other) const;
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public org::sem::Org {
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
    BOOST_DESCRIBE_CLASS(Repeat,
                         (),
                         (),
                         (),
                         (mode, period, count))
    /// \brief mode
    org::sem::Time::Repeat::Mode mode;
    /// \brief period
    org::sem::Time::Repeat::Period period;
    /// \brief count
    int count;
    bool operator==(org::sem::Time::Repeat const& other) const;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static,
                         (),
                         (),
                         (),
                         (repeat, time))
    hstd::ext::ImmBox<hstd::Opt<org::sem::Time::Repeat>> repeat;
    hstd::UserTime time;
    bool operator==(org::sem::Time::Static const& other) const;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic,
                         (),
                         (),
                         (),
                         (expr))
    hstd::ext::ImmBox<hstd::Str> expr;
    bool operator==(org::sem::Time::Dynamic const& other) const;
  };

  using TimeVariant = std::variant<org::sem::Time::Static, org::sem::Time::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = org::sem::Time::TimeKind;
  using variant_data_type = org::sem::Time::TimeVariant;
  BOOST_DESCRIBE_CLASS(Time,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        isActive,
                        time))
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  org::sem::Time::TimeVariant time;
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
  bool operator==(org::sem::Time const& other) const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  org::sem::Time::Static const& getStatic() const { return std::get<0>(time); }
  org::sem::Time::Static& getStatic() { return std::get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::sem::Time::Dynamic const& getDynamic() const { return std::get<1>(time); }
  org::sem::Time::Dynamic& getDynamic() { return std::get<1>(time); }
  static org::sem::Time::TimeKind getTimeKind(org::sem::Time::TimeVariant const& __input) { return static_cast<org::sem::Time::TimeKind>(__input.index()); }
  org::sem::Time::TimeKind getTimeKind() const { return getTimeKind(time); }
};

/// \brief Range of time delimited by two points
struct TimeRange : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmTimeRange() = default;
  BOOST_DESCRIBE_CLASS(TimeRange,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        from,
                        to))
  static OrgSemKind const staticKind;
  /// \brief Starting time
  org::imm::ImmIdT<org::sem::Time> from = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  /// \brief Finishing time
  org::imm::ImmIdT<org::sem::Time> to = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
  bool operator==(org::sem::TimeRange const& other) const;
};

/// \brief Inline macro invocation
struct Macro : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmMacro() = default;
  BOOST_DESCRIBE_CLASS(Macro,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        name,
                        attrs))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  hstd::ext::ImmBox<hstd::Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
  bool operator==(org::sem::Macro const& other) const;
};

/// \brief Text symbol or symbol command
struct Symbol : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymbol() = default;
  /// \brief Symbol parameters
  struct Param {
    BOOST_DESCRIBE_CLASS(Param,
                         (),
                         (),
                         (),
                         (key, value))
    /// \brief Key -- for non-positional
    hstd::ext::ImmBox<hstd::Opt<hstd::Str>> key;
    /// \brief Uninterpreted value
    hstd::ext::ImmBox<hstd::Str> value;
    bool operator==(org::sem::Symbol::Param const& other) const;
  };

  BOOST_DESCRIBE_CLASS(Symbol,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        name,
                        parameters,
                        positional))
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  hstd::ext::ImmBox<hstd::Str> name;
  /// \brief Optional list of parameters
  hstd::ext::ImmVec<org::sem::Symbol::Param> parameters;
  /// \brief Positional parameters
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::Org>> positional;
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
  bool operator==(org::sem::Symbol const& other) const;
};

/// \brief Escaped text
struct Escaped : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
  bool operator==(org::sem::Escaped const& other) const;
};

/// \brief \n newline
struct Newline : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  BOOST_DESCRIBE_CLASS(Newline,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
  bool operator==(org::sem::Newline const& other) const;
};

/// \brief ' "space",
struct Space : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  BOOST_DESCRIBE_CLASS(Space,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
  bool operator==(org::sem::Space const& other) const;
};

/// \brief word
struct Word : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  BOOST_DESCRIBE_CLASS(Word,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
  bool operator==(org::sem::Word const& other) const;
};

/// \brief @mention
struct AtMention : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  BOOST_DESCRIBE_CLASS(AtMention,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
  bool operator==(org::sem::AtMention const& other) const;
};

struct RawText : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
  bool operator==(org::sem::RawText const& other) const;
};

struct Punctuation : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
  bool operator==(org::sem::Punctuation const& other) const;
};

struct Placeholder : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
  bool operator==(org::sem::Placeholder const& other) const;
};

struct BigIdent : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
  bool operator==(org::sem::BigIdent const& other) const;
};

/// \brief ~<<target>>~
struct TextTarget : public org::sem::Leaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  BOOST_DESCRIBE_CLASS(TextTarget,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextTarget; }
  bool operator==(org::sem::TextTarget const& other) const;
};

struct Markup : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
  BOOST_DESCRIBE_CLASS(Markup,
                       (Org),
                       (),
                       (),
                       ())
  bool operator==(org::sem::Markup const& other) const;
};

struct Bold : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  BOOST_DESCRIBE_CLASS(Bold,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
  bool operator==(org::sem::Bold const& other) const;
};

struct Underline : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
  bool operator==(org::sem::Underline const& other) const;
};

struct Monospace : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
  bool operator==(org::sem::Monospace const& other) const;
};

struct MarkQuote : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
  bool operator==(org::sem::MarkQuote const& other) const;
};

struct Verbatim : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
  bool operator==(org::sem::Verbatim const& other) const;
};

struct Italic : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
  bool operator==(org::sem::Italic const& other) const;
};

struct Strike : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
  bool operator==(org::sem::Strike const& other) const;
};

struct Par : public org::sem::Markup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
  bool operator==(org::sem::Par const& other) const;
};

/// \brief ~<<<target>>>~
struct RadioTarget : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmRadioTarget() = default;
  BOOST_DESCRIBE_CLASS(RadioTarget,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        words))
  static OrgSemKind const staticKind;
  hstd::ext::ImmVec<hstd::Str> words = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
  bool operator==(org::sem::RadioTarget const& other) const;
};

/// \brief Latex code body
struct Latex : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  BOOST_DESCRIBE_CLASS(Latex,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Latex; }
  bool operator==(org::sem::Latex const& other) const;
};

struct Link : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmLink() = default;
  BOOST_DESCRIBE_CLASS(Link,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        description,
                        target))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> description = std::nullopt;
  org::sem::LinkTarget target;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  bool operator==(org::sem::Link const& other) const;
};

/// \brief Center nested content in export
struct BlockCenter : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCenter() = default;
  BOOST_DESCRIBE_CLASS(BlockCenter,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCenter; }
  bool operator==(org::sem::BlockCenter const& other) const;
};

/// \brief Quotation block
struct BlockQuote : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  BOOST_DESCRIBE_CLASS(BlockQuote,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockQuote; }
  bool operator==(org::sem::BlockQuote const& other) const;
};

/// \brief Comment block
struct BlockComment : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  BOOST_DESCRIBE_CLASS(BlockComment,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockComment; }
  bool operator==(org::sem::BlockComment const& other) const;
};

/// \brief Verse quotation block
struct BlockVerse : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  BOOST_DESCRIBE_CLASS(BlockVerse,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockVerse; }
  bool operator==(org::sem::BlockVerse const& other) const;
};

struct BlockDynamicFallback : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(BlockDynamicFallback,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockDynamicFallback; }
  bool operator==(org::sem::BlockDynamicFallback const& other) const;
};

/// \brief Example block
struct BlockExample : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  BOOST_DESCRIBE_CLASS(BlockExample,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExample; }
  bool operator==(org::sem::BlockExample const& other) const;
};

/// \brief Direct export passthrough
struct BlockExport : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExport() = default;
  BOOST_DESCRIBE_CLASS(BlockExport,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
  bool operator==(org::sem::BlockExport const& other) const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct BlockAdmonition : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(BlockAdmonition,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockAdmonition; }
  bool operator==(org::sem::BlockAdmonition const& other) const;
};

/// \brief Base class for all code blocks
struct BlockCode : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCode() = default;
  BOOST_DESCRIBE_CLASS(BlockCode,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        lang,
                        switches,
                        exports,
                        result,
                        lines,
                        cache,
                        eval,
                        noweb,
                        hlines,
                        tangle))
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> lang = std::nullopt;
  /// \brief Switch options for block
  hstd::ext::ImmVec<org::sem::BlockCodeSwitch> switches = {};
  /// \brief What to export
  BlockCodeExports exports = BlockCodeExports::Both;
  /// \brief Code evaluation results
  hstd::ext::ImmBox<hstd::Opt<org::sem::BlockCodeEvalResult>> result = std::nullopt;
  /// \brief Collected code lines
  hstd::ext::ImmVec<org::sem::BlockCodeLine> lines = {};
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
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCode; }
  bool operator==(org::sem::BlockCode const& other) const;
};

/// \brief Single subtree log entry
struct SubtreeLog : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtreeLog() = default;
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        head,
                        desc))
  static OrgSemKind const staticKind;
  org::sem::SubtreeLogHead head;
  /// \brief Optional description of the log entry
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::StmtList>>> desc = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  bool operator==(org::sem::SubtreeLog const& other) const;
};

/// \brief Subtree
struct Subtree : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtree() = default;
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
                        isComment,
                        isArchived,
                        priority))
  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> treeId = std::nullopt;
  /// \brief Todo state of the tree
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> todo = std::nullopt;
  /// \brief Task completion state
  hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>> completion = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> description = std::nullopt;
  /// \brief Trailing tags
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::HashTag>> tags = {};
  /// \brief Main title
  org::imm::ImmIdT<org::sem::Paragraph> title = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  /// \brief Associated subtree log
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::SubtreeLog>> logbook = {};
  /// \brief Immediate properties
  hstd::ext::ImmVec<org::sem::NamedProperty> properties = {};
  /// \brief When subtree was marked as closed
  hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>> closed = std::nullopt;
  /// \brief When is the deadline
  hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  bool operator==(org::sem::Subtree const& other) const;
};

/// \brief Table cell
struct Cell : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCell() = default;
  BOOST_DESCRIBE_CLASS(Cell,
                       (Cmd),
                       (),
                       (),
                       (staticKind,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Cell; }
  bool operator==(org::sem::Cell const& other) const;
};

/// \brief Table row
struct Row : public org::sem::Cmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmRow() = default;
  BOOST_DESCRIBE_CLASS(Row,
                       (Cmd),
                       (),
                       (),
                       (staticKind,
                        cells,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::Cell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
  bool operator==(org::sem::Row const& other) const;
};

/// \brief Table
struct Table : public org::sem::Block {
  using ImmBlock::ImmBlock;
  virtual ~ImmTable() = default;
  BOOST_DESCRIBE_CLASS(Table,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        rows,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::Row>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
  bool operator==(org::sem::Table const& other) const;
};

/// \brief Top-level or inline paragraph
struct Paragraph : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  bool operator==(org::sem::Paragraph const& other) const;
};

/// \brief Shortened colon example block
struct ColonExample : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmColonExample() = default;
  BOOST_DESCRIBE_CLASS(ColonExample,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::ColonExample; }
  bool operator==(org::sem::ColonExample const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct CmdAttr : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  BOOST_DESCRIBE_CLASS(CmdAttr,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        target))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
  bool operator==(org::sem::CmdAttr const& other) const;
};

/// \brief Single line of passthrough code
struct CmdExport : public org::sem::Attached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdExport() = default;
  BOOST_DESCRIBE_CLASS(CmdExport,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdExport; }
  bool operator==(org::sem::CmdExport const& other) const;
};

/// \brief Inline, statement or block call
struct Call : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmCall() = default;
  BOOST_DESCRIBE_CLASS(Call,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        name,
                        attrs,
                        isCommand))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  hstd::ext::ImmBox<hstd::Str> name;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  bool isCommand = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
  bool operator==(org::sem::Call const& other) const;
};

struct List : public org::sem::Stmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  BOOST_DESCRIBE_CLASS(List,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  bool operator==(org::sem::List const& other) const;
};

struct ListItem : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, Partial, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty, Partial)
  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        checkbox,
                        header,
                        bullet))
  static OrgSemKind const staticKind;
  org::sem::ListItem::Checkbox checkbox = Checkbox::None;
  /// \brief Description list item header
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool operator==(org::sem::ListItem const& other) const;
};

struct DocumentOptions : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentOptions() = default;
  BOOST_DESCRIBE_CLASS(DocumentOptions,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        initialVisibility,
                        properties,
                        exportConfig,
                        fixedWidthSections,
                        startupIndented,
                        category,
                        setupfile,
                        maxSubtreeLevelExport,
                        columns))
  static OrgSemKind const staticKind;
  InitialSubtreeVisibility initialVisibility = InitialSubtreeVisibility::ShowEverything;
  hstd::ext::ImmVec<org::sem::NamedProperty> properties = {};
  org::sem::DocumentExportConfig exportConfig;
  hstd::ext::ImmBox<hstd::Opt<bool>> fixedWidthSections = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<bool>> startupIndented = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> category = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> setupfile = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<int>> maxSubtreeLevelExport = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>> columns = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  bool operator==(org::sem::DocumentOptions const& other) const;
};

struct Document : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocument() = default;
  BOOST_DESCRIBE_CLASS(Document,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        title,
                        author,
                        creator,
                        filetags,
                        email,
                        language,
                        options,
                        exportFileName))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> title = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> author = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::Paragraph>>> creator = std::nullopt;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::sem::HashTag>> filetags = {};
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::sem::RawText>>> email = std::nullopt;
  hstd::ext::ImmVec<hstd::Str> language = {};
  org::imm::ImmIdT<org::sem::DocumentOptions> options = org::imm::ImmIdT<org::imm::ImmDocumentOptions>::Nil();
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> exportFileName = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  bool operator==(org::sem::Document const& other) const;
};

struct FileTarget : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmFileTarget() = default;
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
                        regexp))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> path;
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> targetId = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> regexp = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
  bool operator==(org::sem::FileTarget const& other) const;
};

struct TextSeparator : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
  bool operator==(org::sem::TextSeparator const& other) const;
};

struct DocumentGroup : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(DocumentGroup,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
  bool operator==(org::sem::DocumentGroup const& other) const;
};

struct File : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmFile() = default;
  struct Document {
    BOOST_DESCRIBE_CLASS(Document,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::File::Document const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::File::Attachment const& other) const;
  };

  struct Source {
    BOOST_DESCRIBE_CLASS(Source,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::File::Source const& other) const;
  };

  using Data = std::variant<org::sem::File::Document, org::sem::File::Attachment, org::sem::File::Source>;
  enum class Kind : short int { Document, Attachment, Source, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Document, Attachment, Source)
  using variant_enum_type = org::sem::File::Kind;
  using variant_data_type = org::sem::File::Data;
  BOOST_DESCRIBE_CLASS(File,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        relPath,
                        absPath,
                        data))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory
  hstd::ext::ImmBox<hstd::Str> relPath = "";
  /// \brief Absolute resolved path to physical file
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  org::sem::File::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::File; }
  bool operator==(org::sem::File const& other) const;
  bool isDocument() const { return getFileKind() == Kind::Document; }
  org::sem::File::Document const& getDocument() const { return std::get<0>(data); }
  org::sem::File::Document& getDocument() { return std::get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  org::sem::File::Attachment const& getAttachment() const { return std::get<1>(data); }
  org::sem::File::Attachment& getAttachment() { return std::get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  org::sem::File::Source const& getSource() const { return std::get<2>(data); }
  org::sem::File::Source& getSource() { return std::get<2>(data); }
  static org::sem::File::Kind getFileKind(org::sem::File::Data const& __input) { return static_cast<org::sem::File::Kind>(__input.index()); }
  org::sem::File::Kind getFileKind() const { return getFileKind(data); }
};

struct Directory : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmDirectory() = default;
  BOOST_DESCRIBE_CLASS(Directory,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        relPath,
                        absPath))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory, empty if this is the root directory
  hstd::ext::ImmBox<hstd::Str> relPath = "";
  /// \brief Absolute resolved path to physical directory
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Directory; }
  bool operator==(org::sem::Directory const& other) const;
};

struct Symlink : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymlink() = default;
  BOOST_DESCRIBE_CLASS(Symlink,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        isDirectory,
                        absPath))
  static OrgSemKind const staticKind;
  bool isDirectory;
  /// \brief Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Symlink; }
  bool operator==(org::sem::Symlink const& other) const;
};

struct CmdInclude : public org::sem::Org {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase,
                         (),
                         (),
                         (),
                         ())
    IncludeBase() {  }
    bool operator==(org::sem::CmdInclude::IncludeBase const& other) const;
  };

  struct Example : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Example,
                         (IncludeBase),
                         (),
                         (),
                         ())
    Example() {  }
    bool operator==(org::sem::CmdInclude::Example const& other) const;
  };

  struct Export : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Export,
                         (IncludeBase),
                         (),
                         (),
                         (language))
    /// \brief Source code language for export
    hstd::ext::ImmBox<hstd::Str> language;
    Export() {  }
    bool operator==(org::sem::CmdInclude::Export const& other) const;
  };

  /// \brief Second positional argument in the include command can have any arbitrary value -- default src/export/example have additional properties, but user can provide anything else there.
  struct Custom : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Custom,
                         (IncludeBase),
                         (),
                         (),
                         (blockName))
    /// \brief Block name not covered by the default values
    hstd::ext::ImmBox<hstd::Str> blockName;
    Custom() {  }
    bool operator==(org::sem::CmdInclude::Custom const& other) const;
  };

  struct Src : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Src,
                         (IncludeBase),
                         (),
                         (),
                         (language))
    /// \brief Source code language for code block
    hstd::ext::ImmBox<hstd::Str> language;
    Src() {  }
    bool operator==(org::sem::CmdInclude::Src const& other) const;
  };

  struct OrgDocument : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(OrgDocument,
                         (IncludeBase),
                         (),
                         (),
                         (onlyContent, subtreePath, minLevel, customIdTarget))
    /// \brief omits any planning lines or property drawers
    hstd::ext::ImmBox<hstd::Opt<bool>> onlyContent = std::nullopt;
    /// \brief Include first subtree matching path with `file.org::* tree`
    hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreePath>> subtreePath = std::nullopt;
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    hstd::ext::ImmBox<hstd::Opt<int>> minLevel = std::nullopt;
    /// \brief Include target subtree content with `file.org::#custom`
    hstd::ext::ImmBox<hstd::Opt<hstd::Str>> customIdTarget = std::nullopt;
    OrgDocument() {  }
    bool operator==(org::sem::CmdInclude::OrgDocument const& other) const;
  };

  using Data = std::variant<org::sem::CmdInclude::Example, org::sem::CmdInclude::Export, org::sem::CmdInclude::Custom, org::sem::CmdInclude::Src, org::sem::CmdInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Custom, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Custom, Src, OrgDocument)
  using variant_enum_type = org::sem::CmdInclude::Kind;
  using variant_data_type = org::sem::CmdInclude::Data;
  BOOST_DESCRIBE_CLASS(CmdInclude,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        path,
                        firstLine,
                        lastLine,
                        data))
  static OrgSemKind const staticKind;
  /// \brief Path to include
  hstd::ext::ImmBox<hstd::Str> path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  hstd::ext::ImmBox<hstd::Opt<int>> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  hstd::ext::ImmBox<hstd::Opt<int>> lastLine = std::nullopt;
  org::sem::CmdInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdInclude; }
  bool operator==(org::sem::CmdInclude const& other) const;
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  org::sem::CmdInclude::Example const& getExample() const { return std::get<0>(data); }
  org::sem::CmdInclude::Example& getExample() { return std::get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  org::sem::CmdInclude::Export const& getExport() const { return std::get<1>(data); }
  org::sem::CmdInclude::Export& getExport() { return std::get<1>(data); }
  bool isCustom() const { return getIncludeKind() == Kind::Custom; }
  org::sem::CmdInclude::Custom const& getCustom() const { return std::get<2>(data); }
  org::sem::CmdInclude::Custom& getCustom() { return std::get<2>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  org::sem::CmdInclude::Src const& getSrc() const { return std::get<3>(data); }
  org::sem::CmdInclude::Src& getSrc() { return std::get<3>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  org::sem::CmdInclude::OrgDocument const& getOrgDocument() const { return std::get<4>(data); }
  org::sem::CmdInclude::OrgDocument& getOrgDocument() { return std::get<4>(data); }
  static org::sem::CmdInclude::Kind getIncludeKind(org::sem::CmdInclude::Data const& __input) { return static_cast<org::sem::CmdInclude::Kind>(__input.index()); }
  org::sem::CmdInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
};

}
/* clang-format on */