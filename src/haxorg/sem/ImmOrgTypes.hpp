/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org{
/// \brief No node
struct ImmNone : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmNone() = default;
  BOOST_DESCRIBE_CLASS(ImmNone,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::None; }
  bool operator==(org::ImmNone const& other) const;
};

struct ImmErrorItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorItem,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        message,
                        function,
                        line))
  static OrgSemKind const staticKind;
  ImmBox<Str> message;
  /// \brief Conversion function name where the error was created
  ImmBox<Opt<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  ImmBox<Opt<int>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorItem; }
  bool operator==(org::ImmErrorItem const& other) const;
};

/// \brief Group of value conversion errors
struct ImmErrorGroup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorGroup,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        diagnostics,
                        function,
                        line))
  static OrgSemKind const staticKind;
  ImmVec<org::ImmIdT<org::ImmErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  ImmBox<Opt<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  ImmBox<Opt<Str>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorGroup; }
  bool operator==(org::ImmErrorGroup const& other) const;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct ImmStmt : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  BOOST_DESCRIBE_CLASS(ImmStmt,
                       (ImmOrg),
                       (),
                       (),
                       (attached))
  ImmVec<org::ImmIdT<org::ImmOrg>> attached;
  bool operator==(org::ImmStmt const& other) const;
};

/// \brief Base class for all inline elements
struct ImmInline : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
  BOOST_DESCRIBE_CLASS(ImmInline,
                       (ImmOrg),
                       (),
                       (),
                       ())
  bool operator==(org::ImmInline const& other) const;
};

/// \brief Zero or more statement nodes
struct ImmStmtList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  BOOST_DESCRIBE_CLASS(ImmStmtList,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
  bool operator==(org::ImmStmtList const& other) const;
};

/// \brief Node without content
struct ImmEmpty : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  BOOST_DESCRIBE_CLASS(ImmEmpty,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
  bool operator==(org::ImmEmpty const& other) const;
};

/// \brief Base class for block or line commands
struct ImmCmd : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  BOOST_DESCRIBE_CLASS(ImmCmd,
                       (ImmStmt),
                       (),
                       (),
                       (attrs))
  /// \brief Additional parameters aside from 'exporter',
  ImmBox<Opt<sem::AttrGroup>> attrs = std::nullopt;
  bool operator==(org::ImmCmd const& other) const;
};

/// \brief Block command type
struct ImmBlock : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
  BOOST_DESCRIBE_CLASS(ImmBlock,
                       (ImmCmd),
                       (),
                       (),
                       ())
  bool operator==(org::ImmBlock const& other) const;
};

/// \brief Line commands
struct ImmLineCommand : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
  BOOST_DESCRIBE_CLASS(ImmLineCommand,
                       (ImmCmd),
                       (),
                       (),
                       ())
  bool operator==(org::ImmLineCommand const& other) const;
};

/// \brief Line command that might get attached to some block element
struct ImmAttached : public org::ImmLineCommand {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
  BOOST_DESCRIBE_CLASS(ImmAttached,
                       (ImmLineCommand),
                       (),
                       (),
                       ())
  bool operator==(org::ImmAttached const& other) const;
};

/// \brief Final node
struct ImmLeaf : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  BOOST_DESCRIBE_CLASS(ImmLeaf,
                       (ImmOrg),
                       (),
                       (),
                       (text))
  /// \brief Final leaf value
  ImmBox<Str> text = "";
  bool operator==(org::ImmLeaf const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdCaption : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCaption() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCaption,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        text))
  static OrgSemKind const staticKind;
  /// \brief Content description
  org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
  bool operator==(org::ImmCmdCaption const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdColumns : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdColumns() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdColumns,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        view))
  static OrgSemKind const staticKind;
  sem::ColumnView view;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdColumns; }
  bool operator==(org::ImmCmdColumns const& other) const;
};

/// \brief Name identifier for the statement elements.
struct ImmCmdName : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdName,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
  bool operator==(org::ImmCmdName const& other) const;
};

/// \brief Custom line command with list of parsed arguments
struct ImmCmdCustomArgs : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCustomArgs() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomArgs,
                       (ImmCmd),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached))
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomArgs; }
  bool operator==(org::ImmCmdCustomArgs const& other) const;
};

/// \brief Custom command with raw unparsed string value
struct ImmCmdCustomRaw : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomRaw() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomRaw,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached,
                        text))
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  ImmBox<Str> text;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomRaw; }
  bool operator==(org::ImmCmdCustomRaw const& other) const;
};

/// \brief Custom line command with text paragraph value
struct ImmCmdCustomText : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomText() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomText,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind,
                        name,
                        isAttached,
                        text))
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomText; }
  bool operator==(org::ImmCmdCustomText const& other) const;
};

struct ImmCmdResults : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdResults() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdResults,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdResults; }
  bool operator==(org::ImmCmdResults const& other) const;
};

/// \brief Tblfm command type
struct ImmCmdTblfm : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdTblfm,
                       (ImmCmd),
                       (),
                       (),
                       (staticKind,
                        expr))
  static OrgSemKind const staticKind;
  sem::Tblfm expr;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
  bool operator==(org::ImmCmdTblfm const& other) const;
};

struct ImmHashTag : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  BOOST_DESCRIBE_CLASS(ImmHashTag,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        text))
  static OrgSemKind const staticKind;
  sem::HashTagText text;
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  bool operator==(org::ImmHashTag const& other) const;
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmInlineFootnote : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmInlineFootnote() = default;
  BOOST_DESCRIBE_CLASS(ImmInlineFootnote,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        tag,
                        definition))
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  ImmBox<Str> tag = "";
  /// \brief Link to possibly resolved definition
  ImmBox<Opt<org::ImmIdT<org::ImmOrg>>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineFootnote; }
  bool operator==(org::ImmInlineFootnote const& other) const;
};

/// \brief Inline export
struct ImmInlineExport : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmInlineExport() = default;
  BOOST_DESCRIBE_CLASS(ImmInlineExport,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  ImmBox<Str> exporter = "";
  ImmBox<Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineExport; }
  bool operator==(org::ImmInlineExport const& other) const;
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
    BOOST_DESCRIBE_CLASS(Repeat,
                         (),
                         (),
                         (),
                         (mode, period, count))
    /// \brief mode
    org::ImmTime::Repeat::Mode mode;
    /// \brief period
    org::ImmTime::Repeat::Period period;
    /// \brief count
    int count;
    bool operator==(org::ImmTime::Repeat const& other) const;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static,
                         (),
                         (),
                         (),
                         (repeat, time))
    ImmBox<Opt<org::ImmTime::Repeat>> repeat;
    UserTime time;
    bool operator==(org::ImmTime::Static const& other) const;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic,
                         (),
                         (),
                         (),
                         (expr))
    ImmBox<Str> expr;
    bool operator==(org::ImmTime::Dynamic const& other) const;
  };

  using TimeVariant = std::variant<org::ImmTime::Static, org::ImmTime::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = org::ImmTime::TimeKind;
  using variant_data_type = org::ImmTime::TimeVariant;
  BOOST_DESCRIBE_CLASS(ImmTime,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        isActive,
                        time))
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  org::ImmTime::TimeVariant time;
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
  bool operator==(org::ImmTime const& other) const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  org::ImmTime::Static const& getStatic() const { return std::get<0>(time); }
  org::ImmTime::Static& getStatic() { return std::get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::ImmTime::Dynamic const& getDynamic() const { return std::get<1>(time); }
  org::ImmTime::Dynamic& getDynamic() { return std::get<1>(time); }
  static org::ImmTime::TimeKind getTimeKind(org::ImmTime::TimeVariant const& __input) { return static_cast<org::ImmTime::TimeKind>(__input.index()); }
  org::ImmTime::TimeKind getTimeKind() const { return getTimeKind(time); }
};

/// \brief Range of time delimited by two points
struct ImmTimeRange : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTimeRange() = default;
  BOOST_DESCRIBE_CLASS(ImmTimeRange,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        from,
                        to))
  static OrgSemKind const staticKind;
  /// \brief Starting time
  org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
  /// \brief Finishing time
  org::ImmIdT<org::ImmTime> to = org::ImmIdT<org::ImmTime>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
  bool operator==(org::ImmTimeRange const& other) const;
};

/// \brief Inline macro invocation
struct ImmMacro : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMacro() = default;
  BOOST_DESCRIBE_CLASS(ImmMacro,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        name,
                        attrs))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  ImmBox<Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  sem::AttrGroup attrs;
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
  bool operator==(org::ImmMacro const& other) const;
};

/// \brief Text symbol or symbol command
struct ImmSymbol : public org::ImmOrg {
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
    ImmBox<Opt<Str>> key;
    /// \brief Uninterpreted value
    ImmBox<Str> value;
    bool operator==(org::ImmSymbol::Param const& other) const;
  };

  BOOST_DESCRIBE_CLASS(ImmSymbol,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        name,
                        parameters,
                        positional))
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  ImmBox<Str> name;
  /// \brief Optional list of parameters
  ImmVec<org::ImmSymbol::Param> parameters;
  /// \brief Positional parameters
  ImmVec<org::ImmIdT<org::ImmOrg>> positional;
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
  bool operator==(org::ImmSymbol const& other) const;
};

/// \brief Escaped text
struct ImmEscaped : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  BOOST_DESCRIBE_CLASS(ImmEscaped,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
  bool operator==(org::ImmEscaped const& other) const;
};

/// \brief \n newline
struct ImmNewline : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  BOOST_DESCRIBE_CLASS(ImmNewline,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
  bool operator==(org::ImmNewline const& other) const;
};

/// \brief ' "space",
struct ImmSpace : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  BOOST_DESCRIBE_CLASS(ImmSpace,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
  bool operator==(org::ImmSpace const& other) const;
};

/// \brief word
struct ImmWord : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  BOOST_DESCRIBE_CLASS(ImmWord,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
  bool operator==(org::ImmWord const& other) const;
};

/// \brief @mention
struct ImmAtMention : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  BOOST_DESCRIBE_CLASS(ImmAtMention,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
  bool operator==(org::ImmAtMention const& other) const;
};

struct ImmRawText : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  BOOST_DESCRIBE_CLASS(ImmRawText,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
  bool operator==(org::ImmRawText const& other) const;
};

struct ImmPunctuation : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  BOOST_DESCRIBE_CLASS(ImmPunctuation,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
  bool operator==(org::ImmPunctuation const& other) const;
};

struct ImmPlaceholder : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  BOOST_DESCRIBE_CLASS(ImmPlaceholder,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
  bool operator==(org::ImmPlaceholder const& other) const;
};

struct ImmBigIdent : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  BOOST_DESCRIBE_CLASS(ImmBigIdent,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
  bool operator==(org::ImmBigIdent const& other) const;
};

/// \brief ~<<target>>~
struct ImmTextTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmTextTarget,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextTarget; }
  bool operator==(org::ImmTextTarget const& other) const;
};

struct ImmMarkup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkup,
                       (ImmOrg),
                       (),
                       (),
                       ())
  bool operator==(org::ImmMarkup const& other) const;
};

struct ImmBold : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  BOOST_DESCRIBE_CLASS(ImmBold,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
  bool operator==(org::ImmBold const& other) const;
};

struct ImmUnderline : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  BOOST_DESCRIBE_CLASS(ImmUnderline,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
  bool operator==(org::ImmUnderline const& other) const;
};

struct ImmMonospace : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  BOOST_DESCRIBE_CLASS(ImmMonospace,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
  bool operator==(org::ImmMonospace const& other) const;
};

struct ImmMarkQuote : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkQuote,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
  bool operator==(org::ImmMarkQuote const& other) const;
};

struct ImmVerbatim : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  BOOST_DESCRIBE_CLASS(ImmVerbatim,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
  bool operator==(org::ImmVerbatim const& other) const;
};

struct ImmItalic : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  BOOST_DESCRIBE_CLASS(ImmItalic,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
  bool operator==(org::ImmItalic const& other) const;
};

struct ImmStrike : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  BOOST_DESCRIBE_CLASS(ImmStrike,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
  bool operator==(org::ImmStrike const& other) const;
};

struct ImmPar : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  BOOST_DESCRIBE_CLASS(ImmPar,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
  bool operator==(org::ImmPar const& other) const;
};

/// \brief ~<<<target>>>~
struct ImmRadioTarget : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmRadioTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmRadioTarget,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        words))
  static OrgSemKind const staticKind;
  ImmVec<Str> words = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
  bool operator==(org::ImmRadioTarget const& other) const;
};

/// \brief Latex code body
struct ImmLatex : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  BOOST_DESCRIBE_CLASS(ImmLatex,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Latex; }
  bool operator==(org::ImmLatex const& other) const;
};

struct ImmLink : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmLink() = default;
  BOOST_DESCRIBE_CLASS(ImmLink,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind,
                        description,
                        target))
  static OrgSemKind const staticKind;
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  sem::LinkTarget target;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  bool operator==(org::ImmLink const& other) const;
};

/// \brief Center nested content in export
struct ImmBlockCenter : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCenter() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCenter,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCenter; }
  bool operator==(org::ImmBlockCenter const& other) const;
};

/// \brief Quotation block
struct ImmBlockQuote : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockQuote,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockQuote; }
  bool operator==(org::ImmBlockQuote const& other) const;
};

/// \brief Comment block
struct ImmBlockComment : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockComment,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockComment; }
  bool operator==(org::ImmBlockComment const& other) const;
};

/// \brief Verse quotation block
struct ImmBlockVerse : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockVerse,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockVerse; }
  bool operator==(org::ImmBlockVerse const& other) const;
};

struct ImmBlockDynamicFallback : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockDynamicFallback,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  ImmBox<Str> name = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockDynamicFallback; }
  bool operator==(org::ImmBlockDynamicFallback const& other) const;
};

/// \brief Example block
struct ImmBlockExample : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockExample,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExample; }
  bool operator==(org::ImmBlockExample const& other) const;
};

/// \brief Direct export passthrough
struct ImmBlockExport : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExport() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockExport,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  ImmBox<Str> exporter = "";
  ImmBox<Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
  bool operator==(org::ImmBlockExport const& other) const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct ImmBlockAdmonition : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockAdmonition,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockAdmonition; }
  bool operator==(org::ImmBlockAdmonition const& other) const;
};

/// \brief Base class for all code blocks
struct ImmBlockCode : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCode() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCode,
                       (ImmBlock),
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
  ImmBox<Opt<Str>> lang = std::nullopt;
  /// \brief Switch options for block
  ImmVec<sem::BlockCodeSwitch> switches = {};
  /// \brief What to export
  BlockCodeExports exports = BlockCodeExports::Both;
  /// \brief Code evaluation results
  ImmBox<Opt<sem::BlockCodeEvalResult>> result = std::nullopt;
  /// \brief Collected code lines
  ImmVec<sem::BlockCodeLine> lines = {};
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
  bool operator==(org::ImmBlockCode const& other) const;
};

/// \brief Single subtree log entry
struct ImmSubtreeLog : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtreeLog() = default;
  BOOST_DESCRIBE_CLASS(ImmSubtreeLog,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        head,
                        desc))
  static OrgSemKind const staticKind;
  sem::SubtreeLogHead head;
  /// \brief Optional description of the log entry
  ImmBox<Opt<org::ImmIdT<org::ImmStmtList>>> desc = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  bool operator==(org::ImmSubtreeLog const& other) const;
};

/// \brief Subtree
struct ImmSubtree : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtree() = default;
  BOOST_DESCRIBE_CLASS(ImmSubtree,
                       (ImmOrg),
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
  ImmBox<Opt<Str>> treeId = std::nullopt;
  /// \brief Todo state of the tree
  ImmBox<Opt<Str>> todo = std::nullopt;
  /// \brief Task completion state
  ImmBox<Opt<sem::SubtreeCompletion>> completion = std::nullopt;
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  /// \brief Trailing tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> tags = {};
  /// \brief Main title
  org::ImmIdT<org::ImmParagraph> title = org::ImmIdT<org::ImmParagraph>::Nil();
  /// \brief Associated subtree log
  ImmVec<org::ImmIdT<org::ImmSubtreeLog>> logbook = {};
  /// \brief Immediate properties
  ImmVec<sem::NamedProperty> properties = {};
  /// \brief When subtree was marked as closed
  ImmBox<Opt<UserTime>> closed = std::nullopt;
  /// \brief When is the deadline
  ImmBox<Opt<UserTime>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  ImmBox<Opt<UserTime>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  ImmBox<Opt<Str>> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  bool operator==(org::ImmSubtree const& other) const;
};

/// \brief Table cell
struct ImmCell : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCell() = default;
  BOOST_DESCRIBE_CLASS(ImmCell,
                       (ImmCmd),
                       (),
                       (),
                       (staticKind,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Cell; }
  bool operator==(org::ImmCell const& other) const;
};

/// \brief Table row
struct ImmRow : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmRow() = default;
  BOOST_DESCRIBE_CLASS(ImmRow,
                       (ImmCmd),
                       (),
                       (),
                       (staticKind,
                        cells,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  ImmVec<org::ImmIdT<org::ImmCell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
  bool operator==(org::ImmRow const& other) const;
};

/// \brief Table
struct ImmTable : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmTable() = default;
  BOOST_DESCRIBE_CLASS(ImmTable,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind,
                        rows,
                        isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  ImmVec<org::ImmIdT<org::ImmRow>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
  bool operator==(org::ImmTable const& other) const;
};

/// \brief Top-level or inline paragraph
struct ImmParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  BOOST_DESCRIBE_CLASS(ImmParagraph,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  bool operator==(org::ImmParagraph const& other) const;
};

/// \brief Shortened colon example block
struct ImmColonExample : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmColonExample() = default;
  BOOST_DESCRIBE_CLASS(ImmColonExample,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::ColonExample; }
  bool operator==(org::ImmColonExample const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdAttr : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdAttr,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        target))
  static OrgSemKind const staticKind;
  ImmBox<Str> target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
  bool operator==(org::ImmCmdAttr const& other) const;
};

/// \brief Single line of passthrough code
struct ImmCmdExport : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdExport() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdExport,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  ImmBox<Str> exporter = "";
  ImmBox<Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdExport; }
  bool operator==(org::ImmCmdExport const& other) const;
};

/// \brief Inline, statement or block call
struct ImmCall : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCall() = default;
  BOOST_DESCRIBE_CLASS(ImmCall,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        name,
                        attrs,
                        isCommand))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  ImmBox<Str> name;
  /// \brief Additional parameters aside from 'exporter',
  sem::AttrGroup attrs;
  bool isCommand = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
  bool operator==(org::ImmCall const& other) const;
};

struct ImmList : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  BOOST_DESCRIBE_CLASS(ImmList,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  bool operator==(org::ImmList const& other) const;
};

struct ImmListItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, Partial, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty, Partial)
  BOOST_DESCRIBE_CLASS(ImmListItem,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        checkbox,
                        header,
                        bullet))
  static OrgSemKind const staticKind;
  org::ImmListItem::Checkbox checkbox = Checkbox::None;
  /// \brief Description list item header
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  ImmBox<Opt<Str>> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool operator==(org::ImmListItem const& other) const;
};

struct ImmDocumentOptions : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentOptions() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentOptions,
                       (ImmOrg),
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
  ImmVec<sem::NamedProperty> properties = {};
  sem::DocumentExportConfig exportConfig;
  ImmBox<Opt<bool>> fixedWidthSections = std::nullopt;
  ImmBox<Opt<bool>> startupIndented = std::nullopt;
  ImmBox<Opt<Str>> category = std::nullopt;
  ImmBox<Opt<Str>> setupfile = std::nullopt;
  ImmBox<Opt<int>> maxSubtreeLevelExport = std::nullopt;
  ImmBox<Opt<sem::ColumnView>> columns = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  bool operator==(org::ImmDocumentOptions const& other) const;
};

struct ImmDocument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocument() = default;
  BOOST_DESCRIBE_CLASS(ImmDocument,
                       (ImmOrg),
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
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> title = std::nullopt;
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> author = std::nullopt;
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> creator = std::nullopt;
  ImmVec<org::ImmIdT<org::ImmHashTag>> filetags = {};
  ImmBox<Opt<org::ImmIdT<org::ImmRawText>>> email = std::nullopt;
  ImmVec<Str> language = {};
  org::ImmIdT<org::ImmDocumentOptions> options = org::ImmIdT<org::ImmDocumentOptions>::Nil();
  ImmBox<Opt<Str>> exportFileName = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  bool operator==(org::ImmDocument const& other) const;
};

struct ImmFileTarget : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmFileTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmFileTarget,
                       (ImmOrg),
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
  ImmBox<Str> path;
  ImmBox<Opt<int>> line = std::nullopt;
  ImmBox<Opt<Str>> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  ImmBox<Opt<Str>> targetId = std::nullopt;
  ImmBox<Opt<Str>> regexp = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
  bool operator==(org::ImmFileTarget const& other) const;
};

struct ImmTextSeparator : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  BOOST_DESCRIBE_CLASS(ImmTextSeparator,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
  bool operator==(org::ImmTextSeparator const& other) const;
};

struct ImmDocumentGroup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentGroup,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
  bool operator==(org::ImmDocumentGroup const& other) const;
};

struct ImmFile : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmFile() = default;
  struct Document {
    BOOST_DESCRIBE_CLASS(Document,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmFile::Document const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmFile::Attachment const& other) const;
  };

  struct Source {
    BOOST_DESCRIBE_CLASS(Source,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmFile::Source const& other) const;
  };

  using Data = std::variant<org::ImmFile::Document, org::ImmFile::Attachment, org::ImmFile::Source>;
  enum class Kind : short int { Document, Attachment, Source, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Document, Attachment, Source)
  using variant_enum_type = org::ImmFile::Kind;
  using variant_data_type = org::ImmFile::Data;
  BOOST_DESCRIBE_CLASS(ImmFile,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        relPath,
                        absPath,
                        data))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory
  ImmBox<Str> relPath = "";
  /// \brief Absolute resolved path to physical file
  ImmBox<Str> absPath = "";
  org::ImmFile::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::File; }
  bool operator==(org::ImmFile const& other) const;
  bool isDocument() const { return getFileKind() == Kind::Document; }
  org::ImmFile::Document const& getDocument() const { return std::get<0>(data); }
  org::ImmFile::Document& getDocument() { return std::get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  org::ImmFile::Attachment const& getAttachment() const { return std::get<1>(data); }
  org::ImmFile::Attachment& getAttachment() { return std::get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  org::ImmFile::Source const& getSource() const { return std::get<2>(data); }
  org::ImmFile::Source& getSource() { return std::get<2>(data); }
  static org::ImmFile::Kind getFileKind(org::ImmFile::Data const& __input) { return static_cast<org::ImmFile::Kind>(__input.index()); }
  org::ImmFile::Kind getFileKind() const { return getFileKind(data); }
};

struct ImmDirectory : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDirectory() = default;
  BOOST_DESCRIBE_CLASS(ImmDirectory,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        relPath,
                        absPath))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory, empty if this is the root directory
  ImmBox<Str> relPath = "";
  /// \brief Absolute resolved path to physical directory
  ImmBox<Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Directory; }
  bool operator==(org::ImmDirectory const& other) const;
};

struct ImmSymlink : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymlink() = default;
  BOOST_DESCRIBE_CLASS(ImmSymlink,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        isDirectory,
                        absPath))
  static OrgSemKind const staticKind;
  bool isDirectory;
  /// \brief Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.
  ImmBox<Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Symlink; }
  bool operator==(org::ImmSymlink const& other) const;
};

struct ImmCmdInclude : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase,
                         (),
                         (),
                         (),
                         (minLineRange, maxLineRange))
    /// \brief No not include nodes with position before specified line.
    ImmBox<Opt<int>> minLineRange = std::nullopt;
    /// \brief Do not include nodes with position after specified line.
    ImmBox<Opt<int>> maxLineRange = std::nullopt;
    IncludeBase() {  }
    bool operator==(org::ImmCmdInclude::IncludeBase const& other) const;
  };

  struct Example : public org::ImmCmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Example,
                         (IncludeBase),
                         (),
                         (),
                         ())
    Example() {  }
    bool operator==(org::ImmCmdInclude::Example const& other) const;
  };

  struct Export : public org::ImmCmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Export,
                         (IncludeBase),
                         (),
                         (),
                         ())
    Export() {  }
    bool operator==(org::ImmCmdInclude::Export const& other) const;
  };

  struct Src : public org::ImmCmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Src,
                         (IncludeBase),
                         (),
                         (),
                         ())
    Src() {  }
    bool operator==(org::ImmCmdInclude::Src const& other) const;
  };

  struct OrgDocument : public org::ImmCmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(OrgDocument,
                         (IncludeBase),
                         (),
                         (),
                         (subtreePath, minLevel, customIdTarget))
    /// \brief Include first subtree matching path with `file.org::* tree`
    ImmBox<Opt<Str>> subtreePath = std::nullopt;
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    ImmBox<Opt<int>> minLevel = std::nullopt;
    /// \brief Include target subtree content with `file.org::#custom`
    ImmBox<Opt<Str>> customIdTarget = std::nullopt;
    OrgDocument() {  }
    bool operator==(org::ImmCmdInclude::OrgDocument const& other) const;
  };

  using Data = std::variant<org::ImmCmdInclude::Example, org::ImmCmdInclude::Export, org::ImmCmdInclude::Src, org::ImmCmdInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  using variant_enum_type = org::ImmCmdInclude::Kind;
  using variant_data_type = org::ImmCmdInclude::Data;
  BOOST_DESCRIBE_CLASS(ImmCmdInclude,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        path,
                        firstLine,
                        lastLine,
                        data))
  static OrgSemKind const staticKind;
  /// \brief Path to include
  ImmBox<Str> path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  ImmBox<Opt<int>> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  ImmBox<Opt<int>> lastLine = std::nullopt;
  org::ImmCmdInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdInclude; }
  bool operator==(org::ImmCmdInclude const& other) const;
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  org::ImmCmdInclude::Example const& getExample() const { return std::get<0>(data); }
  org::ImmCmdInclude::Example& getExample() { return std::get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  org::ImmCmdInclude::Export const& getExport() const { return std::get<1>(data); }
  org::ImmCmdInclude::Export& getExport() { return std::get<1>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  org::ImmCmdInclude::Src const& getSrc() const { return std::get<2>(data); }
  org::ImmCmdInclude::Src& getSrc() { return std::get<2>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  org::ImmCmdInclude::OrgDocument const& getOrgDocument() const { return std::get<3>(data); }
  org::ImmCmdInclude::OrgDocument& getOrgDocument() { return std::get<3>(data); }
  static org::ImmCmdInclude::Kind getIncludeKind(org::ImmCmdInclude::Data const& __input) { return static_cast<org::ImmCmdInclude::Kind>(__input.index()); }
  org::ImmCmdInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
};

}
/* clang-format on */