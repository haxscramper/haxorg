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

/// \brief Single key-value (or positional)
struct ImmAttr : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmAttr() = default;
  BOOST_DESCRIBE_CLASS(ImmAttr,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        arg))
  static OrgSemKind const staticKind;
  sem::AttrValue arg;
  virtual OrgSemKind getKind() const { return OrgSemKind::Attr; }
  bool operator==(org::ImmAttr const& other) const;
};

/// \brief Data type to wrap list of identical command arguments
struct ImmAttrList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmAttrList() = default;
  BOOST_DESCRIBE_CLASS(ImmAttrList,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        args))
  static OrgSemKind const staticKind;
  /// \brief List of arguments
  ImmVec<org::ImmIdT<org::ImmAttr>> args = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::AttrList; }
  bool operator==(org::ImmAttrList const& other) const;
};

/// \brief Additional arguments for command blocks
struct ImmAttrs : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmAttrs() = default;
  BOOST_DESCRIBE_CLASS(ImmAttrs,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        positional,
                        named))
  static OrgSemKind const staticKind;
  /// \brief Positional arguments with no keys
  org::ImmIdT<org::ImmAttrList> positional = org::ImmIdT<org::ImmAttrList>::Nil();
  /// \brief Stored key-value mapping
  ImmMap<Str, org::ImmIdT<org::ImmAttrList>> named;
  virtual OrgSemKind getKind() const { return OrgSemKind::Attrs; }
  bool operator==(org::ImmAttrs const& other) const;
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
                       (parameters))
  /// \brief Additional parameters aside from 'exporter',
  ImmBox<Opt<org::ImmIdT<org::ImmAttrs>>> parameters = std::nullopt;
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
  bool operator==(org::ImmCmdTblfm const& other) const;
};

/// \brief Single or nested inline hash-tag
struct ImmHashTag : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  BOOST_DESCRIBE_CLASS(ImmHashTag,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        head,
                        subtags))
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  ImmBox<Str> head;
  /// \brief List of nested tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> subtags = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
  bool operator==(org::ImmHashTag const& other) const;
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmFootnote : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmFootnote() = default;
  BOOST_DESCRIBE_CLASS(ImmFootnote,
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
  virtual OrgSemKind getKind() const { return OrgSemKind::Footnote; }
  bool operator==(org::ImmFootnote const& other) const;
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
  org::ImmTime::Static const& getStatic() const { return std::get<0>(time); }
  org::ImmTime::Static& getStatic() { return std::get<0>(time); }
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
                        parameters))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  ImmBox<Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::ImmIdT<org::ImmAttrs> parameters = org::ImmIdT<org::ImmAttrs>::Nil();
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

/// \brief ~<<<target>>>~
struct ImmRadioTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRadioTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmRadioTarget,
                       (ImmLeaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
  bool operator==(org::ImmRadioTarget const& other) const;
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
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw,
                         (),
                         (),
                         (),
                         (text))
    ImmBox<Str> text;
    bool operator==(org::ImmLink::Raw const& other) const;
  };

  struct Id {
    BOOST_DESCRIBE_CLASS(Id,
                         (),
                         (),
                         (),
                         (text))
    ImmBox<Str> text;
    bool operator==(org::ImmLink::Id const& other) const;
  };

  struct Person {
    BOOST_DESCRIBE_CLASS(Person,
                         (),
                         (),
                         (),
                         (name))
    ImmBox<Str> name;
    bool operator==(org::ImmLink::Person const& other) const;
  };

  struct UserProtocol {
    BOOST_DESCRIBE_CLASS(UserProtocol,
                         (),
                         (),
                         (),
                         (protocol, target))
    ImmBox<Str> protocol;
    ImmBox<Str> target;
    bool operator==(org::ImmLink::UserProtocol const& other) const;
  };

  struct Internal {
    BOOST_DESCRIBE_CLASS(Internal,
                         (),
                         (),
                         (),
                         (target))
    ImmBox<Str> target;
    bool operator==(org::ImmLink::Internal const& other) const;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote,
                         (),
                         (),
                         (),
                         (target))
    ImmBox<Str> target;
    bool operator==(org::ImmLink::Footnote const& other) const;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File,
                         (),
                         (),
                         (),
                         (file))
    ImmBox<Str> file;
    bool operator==(org::ImmLink::File const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         (file))
    ImmBox<Str> file;
    bool operator==(org::ImmLink::Attachment const& other) const;
  };

  using Data = std::variant<org::ImmLink::Raw, org::ImmLink::Id, org::ImmLink::Person, org::ImmLink::UserProtocol, org::ImmLink::Internal, org::ImmLink::Footnote, org::ImmLink::File, org::ImmLink::Attachment>;
  enum class Kind : short int { Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment)
  using variant_enum_type = org::ImmLink::Kind;
  using variant_data_type = org::ImmLink::Data;
  BOOST_DESCRIBE_CLASS(ImmLink,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind,
                        description,
                        data))
  static OrgSemKind const staticKind;
  ImmBox<Opt<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  org::ImmLink::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  bool operator==(org::ImmLink const& other) const;
  org::ImmLink::Raw const& getRaw() const { return std::get<0>(data); }
  org::ImmLink::Raw& getRaw() { return std::get<0>(data); }
  org::ImmLink::Id const& getId() const { return std::get<1>(data); }
  org::ImmLink::Id& getId() { return std::get<1>(data); }
  org::ImmLink::Person const& getPerson() const { return std::get<2>(data); }
  org::ImmLink::Person& getPerson() { return std::get<2>(data); }
  org::ImmLink::UserProtocol const& getUserProtocol() const { return std::get<3>(data); }
  org::ImmLink::UserProtocol& getUserProtocol() { return std::get<3>(data); }
  org::ImmLink::Internal const& getInternal() const { return std::get<4>(data); }
  org::ImmLink::Internal& getInternal() { return std::get<4>(data); }
  org::ImmLink::Footnote const& getFootnote() const { return std::get<5>(data); }
  org::ImmLink::Footnote& getFootnote() { return std::get<5>(data); }
  org::ImmLink::File const& getFile() const { return std::get<6>(data); }
  org::ImmLink::File& getFile() { return std::get<6>(data); }
  org::ImmLink::Attachment const& getAttachment() const { return std::get<7>(data); }
  org::ImmLink::Attachment& getAttachment() { return std::get<7>(data); }
  static org::ImmLink::Kind getLinkKind(org::ImmLink::Data const& __input) { return static_cast<org::ImmLink::Kind>(__input.index()); }
  org::ImmLink::Kind getLinkKind() const { return getLinkKind(data); }
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
  BOOST_DESCRIBE_CLASS(ImmBlockExport,
                       (ImmBlock),
                       (),
                       (),
                       (staticKind,
                        format,
                        exporter,
                        placement,
                        content))
  static OrgSemKind const staticKind;
  /// \brief Export block type
  org::ImmBlockExport::Format format = Format::Inline;
  /// \brief Exporter backend name
  ImmBox<Str> exporter;
  /// \brief Customized position of the text in the final exporting document.
  ImmBox<Opt<Str>> placement = std::nullopt;
  /// \brief Raw exporter content string
  ImmBox<Str> content;
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
  /// \brief Base value for the log variant
  struct DescribedLog {
    BOOST_DESCRIBE_CLASS(DescribedLog,
                         (),
                         (),
                         (),
                         (desc))
    /// \brief Optional description of the log entry
    ImmBox<Opt<org::ImmIdT<org::ImmStmtList>>> desc = std::nullopt;
    bool operator==(org::ImmSubtreeLog::DescribedLog const& other) const;
  };

  /// \brief Priority added
  struct Priority : public org::ImmSubtreeLog::DescribedLog {
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
    BOOST_DESCRIBE_CLASS(Priority,
                         (DescribedLog),
                         (),
                         (),
                         (oldPriority, newPriority, on, action))
    /// \brief Previous priority for change and removal
    ImmBox<Opt<std::string>> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    ImmBox<Opt<std::string>> newPriority = std::nullopt;
    /// \brief When priority was changed
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Which action taken
    org::ImmSubtreeLog::Priority::Action action;
    bool operator==(org::ImmSubtreeLog::Priority const& other) const;
  };

  /// \brief Timestamped note
  struct Note : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(Note,
                         (DescribedLog),
                         (),
                         (),
                         (on))
    /// \brief Where log was taken
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    bool operator==(org::ImmSubtreeLog::Note const& other) const;
  };

  /// \brief Refiling action
  struct Refile : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(Refile,
                         (DescribedLog),
                         (),
                         (),
                         (on, from))
    /// \brief When the refiling happened
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Link to the original subtree
    org::ImmIdT<org::ImmLink> from = org::ImmIdT<org::ImmLink>::Nil();
    bool operator==(org::ImmSubtreeLog::Refile const& other) const;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(Clock,
                         (DescribedLog),
                         (),
                         (),
                         (from, to))
    /// \brief Clock start time
    org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Optional end of the clock
    ImmBox<Opt<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
    bool operator==(org::ImmSubtreeLog::Clock const& other) const;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(State,
                         (DescribedLog),
                         (),
                         (),
                         (from, to, on))
    ImmBox<Str> from;
    ImmBox<Str> to;
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    bool operator==(org::ImmSubtreeLog::State const& other) const;
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(Tag,
                         (DescribedLog),
                         (),
                         (),
                         (on, tag, added))
    /// \brief When the log was assigned
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Tag in question
    org::ImmIdT<org::ImmHashTag> tag = org::ImmIdT<org::ImmHashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
    bool operator==(org::ImmSubtreeLog::Tag const& other) const;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown : public org::ImmSubtreeLog::DescribedLog {
    BOOST_DESCRIBE_CLASS(Unknown,
                         (DescribedLog),
                         (),
                         (),
                         ())
    bool operator==(org::ImmSubtreeLog::Unknown const& other) const;
  };

  using LogEntry = std::variant<org::ImmSubtreeLog::Priority, org::ImmSubtreeLog::Note, org::ImmSubtreeLog::Refile, org::ImmSubtreeLog::Clock, org::ImmSubtreeLog::State, org::ImmSubtreeLog::Tag, org::ImmSubtreeLog::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Tag, Unknown)
  using variant_enum_type = org::ImmSubtreeLog::Kind;
  using variant_data_type = org::ImmSubtreeLog::LogEntry;
  BOOST_DESCRIBE_CLASS(ImmSubtreeLog,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        log))
  static OrgSemKind const staticKind;
  org::ImmSubtreeLog::LogEntry log = Note{};
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  bool operator==(org::ImmSubtreeLog const& other) const;
  org::ImmSubtreeLog::Priority const& getPriority() const { return std::get<0>(log); }
  org::ImmSubtreeLog::Priority& getPriority() { return std::get<0>(log); }
  org::ImmSubtreeLog::Note const& getNote() const { return std::get<1>(log); }
  org::ImmSubtreeLog::Note& getNote() { return std::get<1>(log); }
  org::ImmSubtreeLog::Refile const& getRefile() const { return std::get<2>(log); }
  org::ImmSubtreeLog::Refile& getRefile() { return std::get<2>(log); }
  org::ImmSubtreeLog::Clock const& getClock() const { return std::get<3>(log); }
  org::ImmSubtreeLog::Clock& getClock() { return std::get<3>(log); }
  org::ImmSubtreeLog::State const& getState() const { return std::get<4>(log); }
  org::ImmSubtreeLog::State& getState() { return std::get<4>(log); }
  org::ImmSubtreeLog::Tag const& getTag() const { return std::get<5>(log); }
  org::ImmSubtreeLog::Tag& getTag() { return std::get<5>(log); }
  org::ImmSubtreeLog::Unknown const& getUnknown() const { return std::get<6>(log); }
  org::ImmSubtreeLog::Unknown& getUnknown() { return std::get<6>(log); }
  static org::ImmSubtreeLog::Kind getLogKind(org::ImmSubtreeLog::LogEntry const& __input) { return static_cast<org::ImmSubtreeLog::Kind>(__input.index()); }
  org::ImmSubtreeLog::Kind getLogKind() const { return getLogKind(log); }
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
  ImmBox<Opt<org::ImmIdT<org::ImmSubtreeCompletion>>> completion = std::nullopt;
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
  ImmBox<Opt<org::ImmIdT<org::ImmTime>>> closed = std::nullopt;
  /// \brief When is the deadline
  ImmBox<Opt<org::ImmIdT<org::ImmTime>>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  ImmBox<Opt<org::ImmIdT<org::ImmTime>>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  ImmBox<Opt<Str>> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  bool operator==(org::ImmSubtree const& other) const;
};

/// \brief Completion status of the subtree list element
struct ImmSubtreeCompletion : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmSubtreeCompletion() = default;
  BOOST_DESCRIBE_CLASS(ImmSubtreeCompletion,
                       (ImmInline),
                       (),
                       (),
                       (staticKind,
                        done,
                        full,
                        isPercent))
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeCompletion; }
  bool operator==(org::ImmSubtreeCompletion const& other) const;
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

/// \brief Top-level or inline paragraph with prefix annotation
struct ImmAnnotatedParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmAnnotatedParagraph() = default;
  struct None {
    BOOST_DESCRIBE_CLASS(None,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmAnnotatedParagraph::None const& other) const;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote,
                         (),
                         (),
                         (),
                         (name))
    ImmBox<Str> name;
    bool operator==(org::ImmAnnotatedParagraph::Footnote const& other) const;
  };

  struct Admonition {
    BOOST_DESCRIBE_CLASS(Admonition,
                         (),
                         (),
                         (),
                         (name))
    /// \brief Prefix admonition for the paragraph
    org::ImmIdT<sem::BigIdent> name = org::ImmIdT<org::ImmBigIdent>::Nil();
    bool operator==(org::ImmAnnotatedParagraph::Admonition const& other) const;
  };

  struct Timestamp {
    BOOST_DESCRIBE_CLASS(Timestamp,
                         (),
                         (),
                         (),
                         (time))
    /// \brief Leading timestamp for the paragraph
    org::ImmIdT<org::ImmTime> time = org::ImmIdT<org::ImmTime>::Nil();
    bool operator==(org::ImmAnnotatedParagraph::Timestamp const& other) const;
  };

  using Data = std::variant<org::ImmAnnotatedParagraph::None, org::ImmAnnotatedParagraph::Footnote, org::ImmAnnotatedParagraph::Admonition, org::ImmAnnotatedParagraph::Timestamp>;
  enum class AnnotationKind : short int { None, Footnote, Admonition, Timestamp, };
  BOOST_DESCRIBE_NESTED_ENUM(AnnotationKind, None, Footnote, Admonition, Timestamp)
  using variant_enum_type = org::ImmAnnotatedParagraph::AnnotationKind;
  using variant_data_type = org::ImmAnnotatedParagraph::Data;
  BOOST_DESCRIBE_CLASS(ImmAnnotatedParagraph,
                       (ImmStmt),
                       (),
                       (),
                       (staticKind,
                        data))
  static OrgSemKind const staticKind;
  org::ImmAnnotatedParagraph::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::AnnotatedParagraph; }
  bool operator==(org::ImmAnnotatedParagraph const& other) const;
  org::ImmAnnotatedParagraph::None const& getNone() const { return std::get<0>(data); }
  org::ImmAnnotatedParagraph::None& getNone() { return std::get<0>(data); }
  org::ImmAnnotatedParagraph::Footnote const& getFootnote() const { return std::get<1>(data); }
  org::ImmAnnotatedParagraph::Footnote& getFootnote() { return std::get<1>(data); }
  org::ImmAnnotatedParagraph::Admonition const& getAdmonition() const { return std::get<2>(data); }
  org::ImmAnnotatedParagraph::Admonition& getAdmonition() { return std::get<2>(data); }
  org::ImmAnnotatedParagraph::Timestamp const& getTimestamp() const { return std::get<3>(data); }
  org::ImmAnnotatedParagraph::Timestamp& getTimestamp() { return std::get<3>(data); }
  static org::ImmAnnotatedParagraph::AnnotationKind getAnnotationKind(org::ImmAnnotatedParagraph::Data const& __input) { return static_cast<org::ImmAnnotatedParagraph::AnnotationKind>(__input.index()); }
  org::ImmAnnotatedParagraph::AnnotationKind getAnnotationKind() const { return getAnnotationKind(data); }
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
                        parameters,
                        isCommand))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  ImmBox<Str> name;
  /// \brief Additional parameters aside from 'exporter',
  org::ImmIdT<org::ImmAttrs> parameters = org::ImmIdT<org::ImmAttrs>::Nil();
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
                        maxSubtreeLevelExport))
  static OrgSemKind const staticKind;
  InitialSubtreeVisibility initialVisibility = InitialSubtreeVisibility::ShowEverything;
  ImmVec<sem::NamedProperty> properties = {};
  sem::DocumentExportConfig exportConfig;
  ImmBox<Opt<bool>> fixedWidthSections = std::nullopt;
  ImmBox<Opt<bool>> startupIndented = std::nullopt;
  ImmBox<Opt<Str>> category = std::nullopt;
  ImmBox<Opt<Str>> setupfile = std::nullopt;
  ImmBox<Opt<int>> maxSubtreeLevelExport = std::nullopt;
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

struct ImmInclude : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInclude() = default;
  struct Example {
    BOOST_DESCRIBE_CLASS(Example,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmInclude::Example const& other) const;
  };

  struct Export {
    BOOST_DESCRIBE_CLASS(Export,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmInclude::Export const& other) const;
  };

  struct Src {
    BOOST_DESCRIBE_CLASS(Src,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::ImmInclude::Src const& other) const;
  };

  struct OrgDocument {
    BOOST_DESCRIBE_CLASS(OrgDocument,
                         (),
                         (),
                         (),
                         (minLevel))
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    ImmBox<Opt<int>> minLevel = std::nullopt;
    bool operator==(org::ImmInclude::OrgDocument const& other) const;
  };

  using Data = std::variant<org::ImmInclude::Example, org::ImmInclude::Export, org::ImmInclude::Src, org::ImmInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  using variant_enum_type = org::ImmInclude::Kind;
  using variant_data_type = org::ImmInclude::Data;
  BOOST_DESCRIBE_CLASS(ImmInclude,
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
  org::ImmInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::Include; }
  bool operator==(org::ImmInclude const& other) const;
  org::ImmInclude::Example const& getExample() const { return std::get<0>(data); }
  org::ImmInclude::Example& getExample() { return std::get<0>(data); }
  org::ImmInclude::Export const& getExport() const { return std::get<1>(data); }
  org::ImmInclude::Export& getExport() { return std::get<1>(data); }
  org::ImmInclude::Src const& getSrc() const { return std::get<2>(data); }
  org::ImmInclude::Src& getSrc() { return std::get<2>(data); }
  org::ImmInclude::OrgDocument const& getOrgDocument() const { return std::get<3>(data); }
  org::ImmInclude::OrgDocument& getOrgDocument() { return std::get<3>(data); }
  static org::ImmInclude::Kind getIncludeKind(org::ImmInclude::Data const& __input) { return static_cast<org::ImmInclude::Kind>(__input.index()); }
  org::ImmInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
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

}
/* clang-format on */