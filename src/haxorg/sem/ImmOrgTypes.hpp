/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org::imm {
/// \brief No node
struct ImmNone : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmNone() = default;
  BOOST_DESCRIBE_CLASS(ImmNone,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::None; }
  bool operator==(org::imm::ImmNone const& other) const;
};

struct ImmErrorItem : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> message;
  /// \brief Conversion function name where the error was created
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorItem; }
  bool operator==(org::imm::ImmErrorItem const& other) const;
};

/// \brief Group of value conversion errors
struct ImmErrorGroup : public org::imm::ImmOrg {
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
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorGroup; }
  bool operator==(org::imm::ImmErrorGroup const& other) const;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct ImmStmt : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  BOOST_DESCRIBE_CLASS(ImmStmt,
                       (ImmOrg),
                       (),
                       (),
                       (attached))
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> attached;
  bool operator==(org::imm::ImmStmt const& other) const;
};

/// \brief Base class for all inline elements
struct ImmInline : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
  BOOST_DESCRIBE_CLASS(ImmInline,
                       (ImmOrg),
                       (),
                       (),
                       ())
  bool operator==(org::imm::ImmInline const& other) const;
};

/// \brief Zero or more statement nodes
struct ImmStmtList : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  BOOST_DESCRIBE_CLASS(ImmStmtList,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
  bool operator==(org::imm::ImmStmtList const& other) const;
};

/// \brief Node without content
struct ImmEmpty : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  BOOST_DESCRIBE_CLASS(ImmEmpty,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
  bool operator==(org::imm::ImmEmpty const& other) const;
};

/// \brief Base class for block or line commands
struct ImmCmd : public org::imm::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  BOOST_DESCRIBE_CLASS(ImmCmd,
                       (ImmStmt),
                       (),
                       (),
                       (attrs))
  /// \brief Additional parameters aside from 'exporter',
  hstd::ext::ImmBox<hstd::Opt<org::sem::AttrGroup>> attrs = std::nullopt;
  bool operator==(org::imm::ImmCmd const& other) const;
};

/// \brief Block command type
struct ImmBlock : public org::imm::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
  BOOST_DESCRIBE_CLASS(ImmBlock,
                       (ImmCmd),
                       (),
                       (),
                       ())
  bool operator==(org::imm::ImmBlock const& other) const;
};

/// \brief Line commands
struct ImmLineCommand : public org::imm::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
  BOOST_DESCRIBE_CLASS(ImmLineCommand,
                       (ImmCmd),
                       (),
                       (),
                       ())
  bool operator==(org::imm::ImmLineCommand const& other) const;
};

/// \brief Line command that might get attached to some block element
struct ImmAttached : public org::imm::ImmLineCommand {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
  BOOST_DESCRIBE_CLASS(ImmAttached,
                       (ImmLineCommand),
                       (),
                       (),
                       ())
  bool operator==(org::imm::ImmAttached const& other) const;
};

/// \brief Final node
struct ImmLeaf : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  BOOST_DESCRIBE_CLASS(ImmLeaf,
                       (ImmOrg),
                       (),
                       (),
                       (text))
  /// \brief Final leaf value
  hstd::ext::ImmBox<hstd::Str> text = "";
  bool operator==(org::imm::ImmLeaf const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdCaption : public org::imm::ImmAttached {
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
  org::imm::ImmIdT<org::imm::ImmParagraph> text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
  bool operator==(org::imm::ImmCmdCaption const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdColumns : public org::imm::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdColumns() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdColumns,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        view))
  static OrgSemKind const staticKind;
  org::sem::ColumnView view;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdColumns; }
  bool operator==(org::imm::ImmCmdColumns const& other) const;
};

/// \brief Name identifier for the statement elements.
struct ImmCmdName : public org::imm::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdName,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
  bool operator==(org::imm::ImmCmdName const& other) const;
};

/// \brief Custom line command with list of parsed arguments
struct ImmCmdCustomArgs : public org::imm::ImmCmd {
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
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomArgs; }
  bool operator==(org::imm::ImmCmdCustomArgs const& other) const;
};

/// \brief Custom command with raw unparsed string value
struct ImmCmdCustomRaw : public org::imm::ImmStmt {
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
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  hstd::ext::ImmBox<hstd::Str> text;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomRaw; }
  bool operator==(org::imm::ImmCmdCustomRaw const& other) const;
};

/// \brief Custom line command with text paragraph value
struct ImmCmdCustomText : public org::imm::ImmStmt {
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
  hstd::ext::ImmBox<hstd::Str> name;
  bool isAttached = false;
  org::imm::ImmIdT<org::imm::ImmParagraph> text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomText; }
  bool operator==(org::imm::ImmCmdCustomText const& other) const;
};

struct ImmCmdResults : public org::imm::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdResults() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdResults,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdResults; }
  bool operator==(org::imm::ImmCmdResults const& other) const;
};

/// \brief Tblfm command type
struct ImmCmdTblfm : public org::imm::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdTblfm,
                       (ImmCmd),
                       (),
                       (),
                       (staticKind,
                        expr))
  static OrgSemKind const staticKind;
  org::sem::Tblfm expr;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
  bool operator==(org::imm::ImmCmdTblfm const& other) const;
};

struct ImmHashTag : public org::imm::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  BOOST_DESCRIBE_CLASS(ImmHashTag,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        text))
  static OrgSemKind const staticKind;
  org::sem::HashTagText text;
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  bool operator==(org::imm::ImmHashTag const& other) const;
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmInlineFootnote : public org::imm::ImmInline {
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
  hstd::ext::ImmBox<hstd::Str> tag = "";
  /// \brief Link to possibly resolved definition
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineFootnote; }
  bool operator==(org::imm::ImmInlineFootnote const& other) const;
};

/// \brief Inline export
struct ImmInlineExport : public org::imm::ImmInline {
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
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineExport; }
  bool operator==(org::imm::ImmInlineExport const& other) const;
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct ImmTime : public org::imm::ImmOrg {
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
    org::imm::Immsem::Time::Repeat::Mode mode;
    /// \brief period
    org::imm::Immsem::Time::Repeat::Period period;
    /// \brief count
    int count;
    bool operator==(org::imm::Immsem::Time::Repeat const& other) const;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static,
                         (),
                         (),
                         (),
                         (repeat, time))
    hstd::ext::ImmBox<hstd::Opt<org::imm::Immsem::Time::Repeat>> repeat;
    hstd::UserTime time;
    bool operator==(org::imm::Immsem::Time::Static const& other) const;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic,
                         (),
                         (),
                         (),
                         (expr))
    hstd::ext::ImmBox<hstd::Str> expr;
    bool operator==(org::imm::Immsem::Time::Dynamic const& other) const;
  };

  using TimeVariant = std::variant<org::imm::Immsem::Time::Static, org::imm::Immsem::Time::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = org::imm::Immsem::Time::TimeKind;
  using variant_data_type = org::imm::Immsem::Time::TimeVariant;
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
  org::imm::Immsem::Time::TimeVariant time;
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
  bool operator==(org::imm::ImmTime const& other) const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  org::imm::Immsem::Time::Static const& getStatic() const { return std::get<0>(time); }
  org::imm::Immsem::Time::Static& getStatic() { return std::get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::imm::Immsem::Time::Dynamic const& getDynamic() const { return std::get<1>(time); }
  org::imm::Immsem::Time::Dynamic& getDynamic() { return std::get<1>(time); }
  static org::imm::Immsem::Time::TimeKind getTimeKind(org::imm::Immsem::Time::TimeVariant const& __input) { return static_cast<org::imm::Immsem::Time::TimeKind>(__input.index()); }
  org::imm::Immsem::Time::TimeKind getTimeKind() const { return getTimeKind(time); }
};

/// \brief Range of time delimited by two points
struct ImmTimeRange : public org::imm::ImmOrg {
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
  org::imm::ImmIdT<org::imm::ImmTime> from = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  /// \brief Finishing time
  org::imm::ImmIdT<org::imm::ImmTime> to = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
  bool operator==(org::imm::ImmTimeRange const& other) const;
};

/// \brief Inline macro invocation
struct ImmMacro : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
  bool operator==(org::imm::ImmMacro const& other) const;
};

/// \brief Text symbol or symbol command
struct ImmSymbol : public org::imm::ImmOrg {
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
    bool operator==(org::imm::Immsem::Symbol::Param const& other) const;
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
  hstd::ext::ImmBox<hstd::Str> name;
  /// \brief Optional list of parameters
  hstd::ext::ImmVec<org::imm::Immsem::Symbol::Param> parameters;
  /// \brief Positional parameters
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> positional;
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
  bool operator==(org::imm::ImmSymbol const& other) const;
};

/// \brief Escaped text
struct ImmEscaped : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  BOOST_DESCRIBE_CLASS(ImmEscaped,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
  bool operator==(org::imm::ImmEscaped const& other) const;
};

/// \brief \n newline
struct ImmNewline : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  BOOST_DESCRIBE_CLASS(ImmNewline,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
  bool operator==(org::imm::ImmNewline const& other) const;
};

/// \brief ' "space",
struct ImmSpace : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  BOOST_DESCRIBE_CLASS(ImmSpace,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
  bool operator==(org::imm::ImmSpace const& other) const;
};

/// \brief word
struct ImmWord : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  BOOST_DESCRIBE_CLASS(ImmWord,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
  bool operator==(org::imm::ImmWord const& other) const;
};

/// \brief @mention
struct ImmAtMention : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  BOOST_DESCRIBE_CLASS(ImmAtMention,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
  bool operator==(org::imm::ImmAtMention const& other) const;
};

struct ImmRawText : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  BOOST_DESCRIBE_CLASS(ImmRawText,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
  bool operator==(org::imm::ImmRawText const& other) const;
};

struct ImmPunctuation : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  BOOST_DESCRIBE_CLASS(ImmPunctuation,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
  bool operator==(org::imm::ImmPunctuation const& other) const;
};

struct ImmPlaceholder : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  BOOST_DESCRIBE_CLASS(ImmPlaceholder,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
  bool operator==(org::imm::ImmPlaceholder const& other) const;
};

struct ImmBigIdent : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  BOOST_DESCRIBE_CLASS(ImmBigIdent,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
  bool operator==(org::imm::ImmBigIdent const& other) const;
};

/// \brief ~<<target>>~
struct ImmTextTarget : public org::imm::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmTextTarget,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextTarget; }
  bool operator==(org::imm::ImmTextTarget const& other) const;
};

struct ImmMarkup : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkup,
                       (ImmOrg),
                       (),
                       (),
                       ())
  bool operator==(org::imm::ImmMarkup const& other) const;
};

struct ImmBold : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  BOOST_DESCRIBE_CLASS(ImmBold,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
  bool operator==(org::imm::ImmBold const& other) const;
};

struct ImmUnderline : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  BOOST_DESCRIBE_CLASS(ImmUnderline,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
  bool operator==(org::imm::ImmUnderline const& other) const;
};

struct ImmMonospace : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  BOOST_DESCRIBE_CLASS(ImmMonospace,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
  bool operator==(org::imm::ImmMonospace const& other) const;
};

struct ImmMarkQuote : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkQuote,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
  bool operator==(org::imm::ImmMarkQuote const& other) const;
};

struct ImmVerbatim : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  BOOST_DESCRIBE_CLASS(ImmVerbatim,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
  bool operator==(org::imm::ImmVerbatim const& other) const;
};

struct ImmItalic : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  BOOST_DESCRIBE_CLASS(ImmItalic,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
  bool operator==(org::imm::ImmItalic const& other) const;
};

struct ImmStrike : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  BOOST_DESCRIBE_CLASS(ImmStrike,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
  bool operator==(org::imm::ImmStrike const& other) const;
};

struct ImmPar : public org::imm::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  BOOST_DESCRIBE_CLASS(ImmPar,
                       (ImmMarkup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
  bool operator==(org::imm::ImmPar const& other) const;
};

/// \brief ~<<<target>>>~
struct ImmRadioTarget : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmRadioTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmRadioTarget,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        words))
  static OrgSemKind const staticKind;
  hstd::ext::ImmVec<hstd::Str> words = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
  bool operator==(org::imm::ImmRadioTarget const& other) const;
};

/// \brief Latex code body
struct ImmLatex : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  BOOST_DESCRIBE_CLASS(ImmLatex,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Latex; }
  bool operator==(org::imm::ImmLatex const& other) const;
};

struct ImmLink : public org::imm::ImmStmt {
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
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> description = std::nullopt;
  org::sem::LinkTarget target;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  bool operator==(org::imm::ImmLink const& other) const;
};

/// \brief Center nested content in export
struct ImmBlockCenter : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCenter() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCenter,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCenter; }
  bool operator==(org::imm::ImmBlockCenter const& other) const;
};

/// \brief Quotation block
struct ImmBlockQuote : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockQuote,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockQuote; }
  bool operator==(org::imm::ImmBlockQuote const& other) const;
};

/// \brief Comment block
struct ImmBlockComment : public org::imm::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockComment,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockComment; }
  bool operator==(org::imm::ImmBlockComment const& other) const;
};

/// \brief Verse quotation block
struct ImmBlockVerse : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockVerse,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockVerse; }
  bool operator==(org::imm::ImmBlockVerse const& other) const;
};

struct ImmBlockDynamicFallback : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockDynamicFallback,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind,
                        name))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> name = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockDynamicFallback; }
  bool operator==(org::imm::ImmBlockDynamicFallback const& other) const;
};

/// \brief Example block
struct ImmBlockExample : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockExample,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExample; }
  bool operator==(org::imm::ImmBlockExample const& other) const;
};

/// \brief Direct export passthrough
struct ImmBlockExport : public org::imm::ImmBlock {
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
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
  bool operator==(org::imm::ImmBlockExport const& other) const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct ImmBlockAdmonition : public org::imm::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockAdmonition,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockAdmonition; }
  bool operator==(org::imm::ImmBlockAdmonition const& other) const;
};

/// \brief Base class for all code blocks
struct ImmBlockCode : public org::imm::ImmBlock {
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
  bool operator==(org::imm::ImmBlockCode const& other) const;
};

/// \brief Single subtree log entry
struct ImmSubtreeLog : public org::imm::ImmOrg {
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
  org::sem::SubtreeLogHead head;
  /// \brief Optional description of the log entry
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>> desc = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  bool operator==(org::imm::ImmSubtreeLog const& other) const;
};

/// \brief Subtree
struct ImmSubtree : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> treeId = std::nullopt;
  /// \brief Todo state of the tree
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> todo = std::nullopt;
  /// \brief Task completion state
  hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>> completion = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> description = std::nullopt;
  /// \brief Trailing tags
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> tags = {};
  /// \brief Main title
  org::imm::ImmIdT<org::imm::ImmParagraph> title = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  /// \brief Associated subtree log
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> logbook = {};
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
  bool operator==(org::imm::ImmSubtree const& other) const;
};

/// \brief Table cell
struct ImmCell : public org::imm::ImmCmd {
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
  bool operator==(org::imm::ImmCell const& other) const;
};

/// \brief Table row
struct ImmRow : public org::imm::ImmCmd {
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
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
  bool operator==(org::imm::ImmRow const& other) const;
};

/// \brief Table
struct ImmTable : public org::imm::ImmBlock {
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
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
  bool operator==(org::imm::ImmTable const& other) const;
};

/// \brief Top-level or inline paragraph
struct ImmParagraph : public org::imm::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  BOOST_DESCRIBE_CLASS(ImmParagraph,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  bool operator==(org::imm::ImmParagraph const& other) const;
};

/// \brief Shortened colon example block
struct ImmColonExample : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmColonExample() = default;
  BOOST_DESCRIBE_CLASS(ImmColonExample,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::ColonExample; }
  bool operator==(org::imm::ImmColonExample const& other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdAttr : public org::imm::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdAttr,
                       (ImmAttached),
                       (),
                       (),
                       (staticKind,
                        target))
  static OrgSemKind const staticKind;
  hstd::ext::ImmBox<hstd::Str> target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
  bool operator==(org::imm::ImmCmdAttr const& other) const;
};

/// \brief Single line of passthrough code
struct ImmCmdExport : public org::imm::ImmAttached {
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
  hstd::ext::ImmBox<hstd::Str> exporter = "";
  hstd::ext::ImmBox<hstd::Str> content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdExport; }
  bool operator==(org::imm::ImmCmdExport const& other) const;
};

/// \brief Inline, statement or block call
struct ImmCall : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> name;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  bool isCommand = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
  bool operator==(org::imm::ImmCall const& other) const;
};

struct ImmList : public org::imm::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  BOOST_DESCRIBE_CLASS(ImmList,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  bool operator==(org::imm::ImmList const& other) const;
};

struct ImmListItem : public org::imm::ImmOrg {
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
  org::imm::Immsem::ListItem::Checkbox checkbox = Checkbox::None;
  /// \brief Description list item header
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool operator==(org::imm::ImmListItem const& other) const;
};

struct ImmDocumentOptions : public org::imm::ImmOrg {
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
  hstd::ext::ImmVec<org::sem::NamedProperty> properties = {};
  org::sem::DocumentExportConfig exportConfig;
  hstd::ext::ImmBox<hstd::Opt<bool>> fixedWidthSections = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<bool>> startupIndented = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> category = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> setupfile = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<int>> maxSubtreeLevelExport = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>> columns = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  bool operator==(org::imm::ImmDocumentOptions const& other) const;
};

struct ImmDocument : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> title = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> author = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> creator = std::nullopt;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> filetags = {};
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>> email = std::nullopt;
  hstd::ext::ImmVec<hstd::Str> language = {};
  org::imm::ImmIdT<org::imm::ImmDocumentOptions> options = org::imm::ImmIdT<org::imm::ImmDocumentOptions>::Nil();
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> exportFileName = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  bool operator==(org::imm::ImmDocument const& other) const;
};

struct ImmFileTarget : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> path;
  hstd::ext::ImmBox<hstd::Opt<int>> line = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> targetId = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> regexp = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
  bool operator==(org::imm::ImmFileTarget const& other) const;
};

struct ImmTextSeparator : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  BOOST_DESCRIBE_CLASS(ImmTextSeparator,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
  bool operator==(org::imm::ImmTextSeparator const& other) const;
};

struct ImmDocumentGroup : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentGroup,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
  bool operator==(org::imm::ImmDocumentGroup const& other) const;
};

struct ImmFile : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmFile() = default;
  struct Document {
    BOOST_DESCRIBE_CLASS(Document,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::imm::Immsem::File::Document const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::imm::Immsem::File::Attachment const& other) const;
  };

  struct Source {
    BOOST_DESCRIBE_CLASS(Source,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::imm::Immsem::File::Source const& other) const;
  };

  using Data = std::variant<org::imm::Immsem::File::Document, org::imm::Immsem::File::Attachment, org::imm::Immsem::File::Source>;
  enum class Kind : short int { Document, Attachment, Source, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Document, Attachment, Source)
  using variant_enum_type = org::imm::Immsem::File::Kind;
  using variant_data_type = org::imm::Immsem::File::Data;
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
  hstd::ext::ImmBox<hstd::Str> relPath = "";
  /// \brief Absolute resolved path to physical file
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  org::imm::Immsem::File::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::File; }
  bool operator==(org::imm::ImmFile const& other) const;
  bool isDocument() const { return getFileKind() == Kind::Document; }
  org::imm::Immsem::File::Document const& getDocument() const { return std::get<0>(data); }
  org::imm::Immsem::File::Document& getDocument() { return std::get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  org::imm::Immsem::File::Attachment const& getAttachment() const { return std::get<1>(data); }
  org::imm::Immsem::File::Attachment& getAttachment() { return std::get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  org::imm::Immsem::File::Source const& getSource() const { return std::get<2>(data); }
  org::imm::Immsem::File::Source& getSource() { return std::get<2>(data); }
  static org::imm::Immsem::File::Kind getFileKind(org::imm::Immsem::File::Data const& __input) { return static_cast<org::imm::Immsem::File::Kind>(__input.index()); }
  org::imm::Immsem::File::Kind getFileKind() const { return getFileKind(data); }
};

struct ImmDirectory : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> relPath = "";
  /// \brief Absolute resolved path to physical directory
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Directory; }
  bool operator==(org::imm::ImmDirectory const& other) const;
};

struct ImmSymlink : public org::imm::ImmOrg {
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
  hstd::ext::ImmBox<hstd::Str> absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Symlink; }
  bool operator==(org::imm::ImmSymlink const& other) const;
};

struct ImmCmdInclude : public org::imm::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase,
                         (),
                         (),
                         (),
                         ())
    IncludeBase() {  }
    bool operator==(org::imm::Immsem::CmdInclude::IncludeBase const& other) const;
  };

  struct Example : public org::imm::Immsem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Example,
                         (IncludeBase),
                         (),
                         (),
                         ())
    Example() {  }
    bool operator==(org::imm::Immsem::CmdInclude::Example const& other) const;
  };

  struct Export : public org::imm::Immsem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Export,
                         (IncludeBase),
                         (),
                         (),
                         (language))
    /// \brief Source code language for export
    hstd::ext::ImmBox<hstd::Str> language;
    Export() {  }
    bool operator==(org::imm::Immsem::CmdInclude::Export const& other) const;
  };

  /// \brief Second positional argument in the include command can have any arbitrary value -- default src/export/example have additional properties, but user can provide anything else there.
  struct Custom : public org::imm::Immsem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Custom,
                         (IncludeBase),
                         (),
                         (),
                         (blockName))
    /// \brief Block name not covered by the default values
    hstd::ext::ImmBox<hstd::Str> blockName;
    Custom() {  }
    bool operator==(org::imm::Immsem::CmdInclude::Custom const& other) const;
  };

  struct Src : public org::imm::Immsem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Src,
                         (IncludeBase),
                         (),
                         (),
                         (language))
    /// \brief Source code language for code block
    hstd::ext::ImmBox<hstd::Str> language;
    Src() {  }
    bool operator==(org::imm::Immsem::CmdInclude::Src const& other) const;
  };

  struct OrgDocument : public org::imm::Immsem::CmdInclude::IncludeBase {
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
    bool operator==(org::imm::Immsem::CmdInclude::OrgDocument const& other) const;
  };

  using Data = std::variant<org::imm::Immsem::CmdInclude::Example, org::imm::Immsem::CmdInclude::Export, org::imm::Immsem::CmdInclude::Custom, org::imm::Immsem::CmdInclude::Src, org::imm::Immsem::CmdInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Custom, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Custom, Src, OrgDocument)
  using variant_enum_type = org::imm::Immsem::CmdInclude::Kind;
  using variant_data_type = org::imm::Immsem::CmdInclude::Data;
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
  hstd::ext::ImmBox<hstd::Str> path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  hstd::ext::ImmBox<hstd::Opt<int>> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  hstd::ext::ImmBox<hstd::Opt<int>> lastLine = std::nullopt;
  org::imm::Immsem::CmdInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdInclude; }
  bool operator==(org::imm::ImmCmdInclude const& other) const;
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  org::imm::Immsem::CmdInclude::Example const& getExample() const { return std::get<0>(data); }
  org::imm::Immsem::CmdInclude::Example& getExample() { return std::get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  org::imm::Immsem::CmdInclude::Export const& getExport() const { return std::get<1>(data); }
  org::imm::Immsem::CmdInclude::Export& getExport() { return std::get<1>(data); }
  bool isCustom() const { return getIncludeKind() == Kind::Custom; }
  org::imm::Immsem::CmdInclude::Custom const& getCustom() const { return std::get<2>(data); }
  org::imm::Immsem::CmdInclude::Custom& getCustom() { return std::get<2>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  org::imm::Immsem::CmdInclude::Src const& getSrc() const { return std::get<3>(data); }
  org::imm::Immsem::CmdInclude::Src& getSrc() { return std::get<3>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  org::imm::Immsem::CmdInclude::OrgDocument const& getOrgDocument() const { return std::get<4>(data); }
  org::imm::Immsem::CmdInclude::OrgDocument& getOrgDocument() { return std::get<4>(data); }
  static org::imm::Immsem::CmdInclude::Kind getIncludeKind(org::imm::Immsem::CmdInclude::Data const& __input) { return static_cast<org::imm::Immsem::CmdInclude::Kind>(__input.index()); }
  org::imm::Immsem::CmdInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
};

}
/* clang-format on */