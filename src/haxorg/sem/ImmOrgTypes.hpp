/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org{
/// \brief Single key-value (or positional)
struct ImmCmdArgument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgument() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdArgument,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        key,
                        varname,
                        value))
  static OrgSemKind const staticKind;
  /// \brief Key
  ImmBox<Opt<Str>> key = std::nullopt;
  /// \brief When used in the `:var` assignment, this stores variable name
  ImmBox<Opt<Str>> varname = std::nullopt;
  /// \brief Value
  ImmBox<Str> value;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgument; }
  bool operator==(org::ImmCmdArgument const& other) const;
};

/// \brief Data type to wrap list of identical command arguments
struct ImmCmdArgumentList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgumentList() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdArgumentList,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        args))
  static OrgSemKind const staticKind;
  /// \brief List of arguments
  ImmVec<org::ImmIdT<org::ImmCmdArgument>> args = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgumentList; }
  bool operator==(org::ImmCmdArgumentList const& other) const;
};

/// \brief Additional arguments for command blocks
struct ImmCmdArguments : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArguments() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdArguments,
                       (ImmOrg),
                       (),
                       (),
                       (staticKind,
                        positional,
                        named))
  static OrgSemKind const staticKind;
  /// \brief Positional arguments with no keys
  org::ImmIdT<org::ImmCmdArgumentList> positional = org::ImmIdT<org::ImmCmdArgumentList>::Nil();
  /// \brief Stored key-value mapping
  ImmMap<Str, org::ImmIdT<org::ImmCmdArgumentList>> named;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArguments; }
  bool operator==(org::ImmCmdArguments const& other) const;
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
  ImmBox<Opt<org::ImmIdT<org::ImmCmdArguments>>> parameters = std::nullopt;
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
  org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
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
  struct Line {
    struct Part {
      struct Raw {
        BOOST_DESCRIBE_CLASS(Raw,
                             (),
                             (),
                             (),
                             (code))
        ImmBox<Str> code;
        bool operator==(org::ImmBlockCode::Line::Part::Raw const& other) const;
      };

      struct Callout {
        BOOST_DESCRIBE_CLASS(Callout,
                             (),
                             (),
                             (),
                             (name))
        ImmBox<Str> name;
        bool operator==(org::ImmBlockCode::Line::Part::Callout const& other) const;
      };

      struct Tangle {
        BOOST_DESCRIBE_CLASS(Tangle,
                             (),
                             (),
                             (),
                             (target))
        ImmBox<Str> target;
        bool operator==(org::ImmBlockCode::Line::Part::Tangle const& other) const;
      };

      using Data = std::variant<org::ImmBlockCode::Line::Part::Raw, org::ImmBlockCode::Line::Part::Callout, org::ImmBlockCode::Line::Part::Tangle>;
      enum class Kind : short int { Raw, Callout, Tangle, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
      using variant_enum_type = org::ImmBlockCode::Line::Part::Kind;
      using variant_data_type = org::ImmBlockCode::Line::Part::Data;
      BOOST_DESCRIBE_CLASS(Part,
                           (),
                           (),
                           (),
                           (data))
      org::ImmBlockCode::Line::Part::Data data;
      bool operator==(org::ImmBlockCode::Line::Part const& other) const;
      org::ImmBlockCode::Line::Part::Raw const& getRaw() const { return std::get<0>(data); }
      org::ImmBlockCode::Line::Part::Raw& getRaw() { return std::get<0>(data); }
      org::ImmBlockCode::Line::Part::Callout const& getCallout() const { return std::get<1>(data); }
      org::ImmBlockCode::Line::Part::Callout& getCallout() { return std::get<1>(data); }
      org::ImmBlockCode::Line::Part::Tangle const& getTangle() const { return std::get<2>(data); }
      org::ImmBlockCode::Line::Part::Tangle& getTangle() { return std::get<2>(data); }
      static org::ImmBlockCode::Line::Part::Kind getKind(org::ImmBlockCode::Line::Part::Data const& __input) { return static_cast<org::ImmBlockCode::Line::Part::Kind>(__input.index()); }
      org::ImmBlockCode::Line::Part::Kind getKind() const { return getKind(data); }
    };

    BOOST_DESCRIBE_CLASS(Line,
                         (),
                         (),
                         (),
                         (parts))
    /// \brief parts of the single line
    ImmVec<org::ImmBlockCode::Line::Part> parts = {};
    bool operator==(org::ImmBlockCode::Line const& other) const;
  };

  /// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
  struct Switch {
    /// \brief Enumerate code lines starting from `start` value instead of default indexing.
    struct LineStart {
      BOOST_DESCRIBE_CLASS(LineStart,
                           (),
                           (),
                           (),
                           (start, extendLast))
      /// \brief First line number
      int start;
      /// \brief Continue numbering from the previous block nstead of starting anew
      bool extendLast = false;
      bool operator==(org::ImmBlockCode::Switch::LineStart const& other) const;
    };

    struct CalloutFormat {
      BOOST_DESCRIBE_CLASS(CalloutFormat,
                           (),
                           (),
                           (),
                           (format))
      ImmBox<Str> format = "";
      bool operator==(org::ImmBlockCode::Switch::CalloutFormat const& other) const;
    };

    struct RemoveCallout {
      BOOST_DESCRIBE_CLASS(RemoveCallout,
                           (),
                           (),
                           (),
                           (remove))
      bool remove = true;
      bool operator==(org::ImmBlockCode::Switch::RemoveCallout const& other) const;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      BOOST_DESCRIBE_CLASS(EmphasizeLine,
                           (),
                           (),
                           (),
                           (line))
      ImmVec<int> line = {};
      bool operator==(org::ImmBlockCode::Switch::EmphasizeLine const& other) const;
    };

    struct Dedent {
      BOOST_DESCRIBE_CLASS(Dedent,
                           (),
                           (),
                           (),
                           (value))
      int value = 0;
      bool operator==(org::ImmBlockCode::Switch::Dedent const& other) const;
    };

    using Data = std::variant<org::ImmBlockCode::Switch::LineStart, org::ImmBlockCode::Switch::CalloutFormat, org::ImmBlockCode::Switch::RemoveCallout, org::ImmBlockCode::Switch::EmphasizeLine, org::ImmBlockCode::Switch::Dedent>;
    enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
    using variant_enum_type = org::ImmBlockCode::Switch::Kind;
    using variant_data_type = org::ImmBlockCode::Switch::Data;
    BOOST_DESCRIBE_CLASS(Switch,
                         (),
                         (),
                         (),
                         (data))
    org::ImmBlockCode::Switch::Data data;
    bool operator==(org::ImmBlockCode::Switch const& other) const;
    org::ImmBlockCode::Switch::LineStart const& getLineStart() const { return std::get<0>(data); }
    org::ImmBlockCode::Switch::LineStart& getLineStart() { return std::get<0>(data); }
    org::ImmBlockCode::Switch::CalloutFormat const& getCalloutFormat() const { return std::get<1>(data); }
    org::ImmBlockCode::Switch::CalloutFormat& getCalloutFormat() { return std::get<1>(data); }
    org::ImmBlockCode::Switch::RemoveCallout const& getRemoveCallout() const { return std::get<2>(data); }
    org::ImmBlockCode::Switch::RemoveCallout& getRemoveCallout() { return std::get<2>(data); }
    org::ImmBlockCode::Switch::EmphasizeLine const& getEmphasizeLine() const { return std::get<3>(data); }
    org::ImmBlockCode::Switch::EmphasizeLine& getEmphasizeLine() { return std::get<3>(data); }
    org::ImmBlockCode::Switch::Dedent const& getDedent() const { return std::get<4>(data); }
    org::ImmBlockCode::Switch::Dedent& getDedent() { return std::get<4>(data); }
    static org::ImmBlockCode::Switch::Kind getKind(org::ImmBlockCode::Switch::Data const& __input) { return static_cast<org::ImmBlockCode::Switch::Kind>(__input.index()); }
    org::ImmBlockCode::Switch::Kind getKind() const { return getKind(data); }
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
    struct None {
      BOOST_DESCRIBE_CLASS(None,
                           (),
                           (),
                           (),
                           ())
      bool operator==(org::ImmBlockCode::EvalResult::None const& other) const;
    };

    /// \brief Source code block evaluated to an org-mode node element
    struct OrgValue {
      BOOST_DESCRIBE_CLASS(OrgValue,
                           (),
                           (),
                           (),
                           (value))
      /// \brief Parsed value of the evaluation result
      org::ImmIdT<org::ImmOrg> value = org::ImmIdT<org::ImmOrg>::Nil();
      bool operator==(org::ImmBlockCode::EvalResult::OrgValue const& other) const;
    };

    /// \brief Output evaluation results to a file
    struct File {
      BOOST_DESCRIBE_CLASS(File,
                           (),
                           (),
                           (),
                           (path))
      ImmBox<Str> path;
      bool operator==(org::ImmBlockCode::EvalResult::File const& other) const;
    };

    /// \brief Evaluation output is a raw text
    struct Raw {
      BOOST_DESCRIBE_CLASS(Raw,
                           (),
                           (),
                           (),
                           (text))
      ImmBox<Str> text;
      bool operator==(org::ImmBlockCode::EvalResult::Raw const& other) const;
    };

    using Data = std::variant<org::ImmBlockCode::EvalResult::None, org::ImmBlockCode::EvalResult::OrgValue, org::ImmBlockCode::EvalResult::File, org::ImmBlockCode::EvalResult::Raw>;
    enum class Kind : short int { None, OrgValue, File, Raw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, None, OrgValue, File, Raw)
    using variant_enum_type = org::ImmBlockCode::EvalResult::Kind;
    using variant_data_type = org::ImmBlockCode::EvalResult::Data;
    BOOST_DESCRIBE_CLASS(EvalResult,
                         (),
                         (),
                         (),
                         (data))
    org::ImmBlockCode::EvalResult::Data data;
    bool operator==(org::ImmBlockCode::EvalResult const& other) const;
    org::ImmBlockCode::EvalResult::None const& getNone() const { return std::get<0>(data); }
    org::ImmBlockCode::EvalResult::None& getNone() { return std::get<0>(data); }
    org::ImmBlockCode::EvalResult::OrgValue const& getOrgValue() const { return std::get<1>(data); }
    org::ImmBlockCode::EvalResult::OrgValue& getOrgValue() { return std::get<1>(data); }
    org::ImmBlockCode::EvalResult::File const& getFile() const { return std::get<2>(data); }
    org::ImmBlockCode::EvalResult::File& getFile() { return std::get<2>(data); }
    org::ImmBlockCode::EvalResult::Raw const& getRaw() const { return std::get<3>(data); }
    org::ImmBlockCode::EvalResult::Raw& getRaw() { return std::get<3>(data); }
    static org::ImmBlockCode::EvalResult::Kind getKind(org::ImmBlockCode::EvalResult::Data const& __input) { return static_cast<org::ImmBlockCode::EvalResult::Kind>(__input.index()); }
    org::ImmBlockCode::EvalResult::Kind getKind() const { return getKind(data); }
  };

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
  ImmVec<org::ImmBlockCode::Switch> switches = {};
  /// \brief What to export
  org::ImmBlockCode::Exports exports = Exports::Both;
  /// \brief Code evaluation results
  ImmBox<Opt<org::ImmBlockCode::EvalResult>> result = std::nullopt;
  /// \brief Collected code lines
  ImmVec<org::ImmBlockCode::Line> lines = {};
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
    BOOST_DESCRIBE_CLASS(Period,
                         (),
                         (),
                         (),
                         (kind, from, to))
    /// \brief Time period kind -- not associated with point/range distinction
    org::ImmSubtree::Period::Kind kind;
    /// \brief Clock start time
    org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Optional end of the clock
    ImmBox<Opt<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
    bool operator==(org::ImmSubtree::Period const& other) const;
  };

  /// \brief Single subtree property
  struct Property {
    enum class SetMode : short int { Override, Add, Subtract, };
    BOOST_DESCRIBE_NESTED_ENUM(SetMode, Override, Add, Subtract)
    enum class InheritanceMode : short int { ThisAndSub, OnlyThis, OnlySub, };
    BOOST_DESCRIBE_NESTED_ENUM(InheritanceMode, ThisAndSub, OnlyThis, OnlySub)
    struct Nonblocking {
      BOOST_DESCRIBE_CLASS(Nonblocking,
                           (),
                           (),
                           (),
                           (isBlocking))
      bool isBlocking;
      bool operator==(org::ImmSubtree::Property::Nonblocking const& other) const;
    };

    struct Trigger {
      BOOST_DESCRIBE_CLASS(Trigger,
                           (),
                           (),
                           (),
                           ())
      bool operator==(org::ImmSubtree::Property::Trigger const& other) const;
    };

    struct Origin {
      BOOST_DESCRIBE_CLASS(Origin,
                           (),
                           (),
                           (),
                           (text))
      org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
      bool operator==(org::ImmSubtree::Property::Origin const& other) const;
    };

    struct ExportLatexClass {
      BOOST_DESCRIBE_CLASS(ExportLatexClass,
                           (),
                           (),
                           (),
                           (latexClass))
      ImmBox<Str> latexClass;
      bool operator==(org::ImmSubtree::Property::ExportLatexClass const& other) const;
    };

    struct ExportLatexClassOptions {
      BOOST_DESCRIBE_CLASS(ExportLatexClassOptions,
                           (),
                           (),
                           (),
                           (options))
      ImmVec<Str> options;
      bool operator==(org::ImmSubtree::Property::ExportLatexClassOptions const& other) const;
    };

    struct ExportLatexHeader {
      BOOST_DESCRIBE_CLASS(ExportLatexHeader,
                           (),
                           (),
                           (),
                           (header))
      ImmBox<Str> header;
      bool operator==(org::ImmSubtree::Property::ExportLatexHeader const& other) const;
    };

    struct ExportLatexCompiler {
      BOOST_DESCRIBE_CLASS(ExportLatexCompiler,
                           (),
                           (),
                           (),
                           (compiler))
      ImmBox<Str> compiler;
      bool operator==(org::ImmSubtree::Property::ExportLatexCompiler const& other) const;
    };

    struct Ordered {
      BOOST_DESCRIBE_CLASS(Ordered,
                           (),
                           (),
                           (),
                           (isOrdered))
      bool isOrdered;
      bool operator==(org::ImmSubtree::Property::Ordered const& other) const;
    };

    struct Effort {
      BOOST_DESCRIBE_CLASS(Effort,
                           (),
                           (),
                           (),
                           (hours, minutes))
      int hours = 0;
      int minutes = 0;
      bool operator==(org::ImmSubtree::Property::Effort const& other) const;
    };

    struct Visibility {
      enum class Level : short int { Folded, Children, Content, All, };
      BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
      BOOST_DESCRIBE_CLASS(Visibility,
                           (),
                           (),
                           (),
                           (level))
      org::ImmSubtree::Property::Visibility::Level level;
      bool operator==(org::ImmSubtree::Property::Visibility const& other) const;
    };

    struct ExportOptions {
      BOOST_DESCRIBE_CLASS(ExportOptions,
                           (),
                           (),
                           (),
                           (backend, values))
      ImmBox<Str> backend;
      ImmMap<Str, Str> values;
      bool operator==(org::ImmSubtree::Property::ExportOptions const& other) const;
    };

    struct Blocker {
      BOOST_DESCRIBE_CLASS(Blocker,
                           (),
                           (),
                           (),
                           (blockers))
      ImmVec<Str> blockers;
      bool operator==(org::ImmSubtree::Property::Blocker const& other) const;
    };

    struct Unnumbered {
      BOOST_DESCRIBE_CLASS(Unnumbered,
                           (),
                           (),
                           (),
                           ())
      bool operator==(org::ImmSubtree::Property::Unnumbered const& other) const;
    };

    struct Created {
      BOOST_DESCRIBE_CLASS(Created,
                           (),
                           (),
                           (),
                           (time))
      org::ImmIdT<org::ImmTime> time = org::ImmIdT<org::ImmTime>::Nil();
      bool operator==(org::ImmSubtree::Property::Created const& other) const;
    };

    /// \brief Custop property with unparsed arguments
    struct CustomArgs {
      BOOST_DESCRIBE_CLASS(CustomArgs,
                           (),
                           (),
                           (),
                           (name, sub, parameters))
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property target specialization
      ImmBox<Opt<Str>> sub = std::nullopt;
      /// \brief Property parameters
      org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
      bool operator==(org::ImmSubtree::Property::CustomArgs const& other) const;
    };

    /// \brief Custop property with unparsed arguments
    struct CustomRaw {
      BOOST_DESCRIBE_CLASS(CustomRaw,
                           (),
                           (),
                           (),
                           (name, value))
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property value
      ImmBox<Str> value = "";
      bool operator==(org::ImmSubtree::Property::CustomRaw const& other) const;
    };

    using Data = std::variant<org::ImmSubtree::Property::Nonblocking, org::ImmSubtree::Property::Trigger, org::ImmSubtree::Property::Origin, org::ImmSubtree::Property::ExportLatexClass, org::ImmSubtree::Property::ExportLatexClassOptions, org::ImmSubtree::Property::ExportLatexHeader, org::ImmSubtree::Property::ExportLatexCompiler, org::ImmSubtree::Property::Ordered, org::ImmSubtree::Property::Effort, org::ImmSubtree::Property::Visibility, org::ImmSubtree::Property::ExportOptions, org::ImmSubtree::Property::Blocker, org::ImmSubtree::Property::Unnumbered, org::ImmSubtree::Property::Created, org::ImmSubtree::Property::CustomArgs, org::ImmSubtree::Property::CustomRaw>;
    enum class Kind : short int { Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw)
    using variant_enum_type = org::ImmSubtree::Property::Kind;
    using variant_data_type = org::ImmSubtree::Property::Data;
    BOOST_DESCRIBE_CLASS(Property,
                         (),
                         (),
                         (),
                         (mainSetRule,
                          subSetRule,
                          inheritanceMode,
                          data))
    org::ImmSubtree::Property::SetMode mainSetRule = Property::SetMode::Override;
    org::ImmSubtree::Property::SetMode subSetRule = Property::SetMode::Override;
    org::ImmSubtree::Property::InheritanceMode inheritanceMode = Property::InheritanceMode::ThisAndSub;
    org::ImmSubtree::Property::Data data;
    bool operator==(org::ImmSubtree::Property const& other) const;
    org::ImmSubtree::Property::Nonblocking const& getNonblocking() const { return std::get<0>(data); }
    org::ImmSubtree::Property::Nonblocking& getNonblocking() { return std::get<0>(data); }
    org::ImmSubtree::Property::Trigger const& getTrigger() const { return std::get<1>(data); }
    org::ImmSubtree::Property::Trigger& getTrigger() { return std::get<1>(data); }
    org::ImmSubtree::Property::Origin const& getOrigin() const { return std::get<2>(data); }
    org::ImmSubtree::Property::Origin& getOrigin() { return std::get<2>(data); }
    org::ImmSubtree::Property::ExportLatexClass const& getExportLatexClass() const { return std::get<3>(data); }
    org::ImmSubtree::Property::ExportLatexClass& getExportLatexClass() { return std::get<3>(data); }
    org::ImmSubtree::Property::ExportLatexClassOptions const& getExportLatexClassOptions() const { return std::get<4>(data); }
    org::ImmSubtree::Property::ExportLatexClassOptions& getExportLatexClassOptions() { return std::get<4>(data); }
    org::ImmSubtree::Property::ExportLatexHeader const& getExportLatexHeader() const { return std::get<5>(data); }
    org::ImmSubtree::Property::ExportLatexHeader& getExportLatexHeader() { return std::get<5>(data); }
    org::ImmSubtree::Property::ExportLatexCompiler const& getExportLatexCompiler() const { return std::get<6>(data); }
    org::ImmSubtree::Property::ExportLatexCompiler& getExportLatexCompiler() { return std::get<6>(data); }
    org::ImmSubtree::Property::Ordered const& getOrdered() const { return std::get<7>(data); }
    org::ImmSubtree::Property::Ordered& getOrdered() { return std::get<7>(data); }
    org::ImmSubtree::Property::Effort const& getEffort() const { return std::get<8>(data); }
    org::ImmSubtree::Property::Effort& getEffort() { return std::get<8>(data); }
    org::ImmSubtree::Property::Visibility const& getVisibility() const { return std::get<9>(data); }
    org::ImmSubtree::Property::Visibility& getVisibility() { return std::get<9>(data); }
    org::ImmSubtree::Property::ExportOptions const& getExportOptions() const { return std::get<10>(data); }
    org::ImmSubtree::Property::ExportOptions& getExportOptions() { return std::get<10>(data); }
    org::ImmSubtree::Property::Blocker const& getBlocker() const { return std::get<11>(data); }
    org::ImmSubtree::Property::Blocker& getBlocker() { return std::get<11>(data); }
    org::ImmSubtree::Property::Unnumbered const& getUnnumbered() const { return std::get<12>(data); }
    org::ImmSubtree::Property::Unnumbered& getUnnumbered() { return std::get<12>(data); }
    org::ImmSubtree::Property::Created const& getCreated() const { return std::get<13>(data); }
    org::ImmSubtree::Property::Created& getCreated() { return std::get<13>(data); }
    org::ImmSubtree::Property::CustomArgs const& getCustomArgs() const { return std::get<14>(data); }
    org::ImmSubtree::Property::CustomArgs& getCustomArgs() { return std::get<14>(data); }
    org::ImmSubtree::Property::CustomRaw const& getCustomRaw() const { return std::get<15>(data); }
    org::ImmSubtree::Property::CustomRaw& getCustomRaw() { return std::get<15>(data); }
    static org::ImmSubtree::Property::Kind getKind(org::ImmSubtree::Property::Data const& __input) { return static_cast<org::ImmSubtree::Property::Kind>(__input.index()); }
    org::ImmSubtree::Property::Kind getKind() const { return getKind(data); }
  };

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
  ImmVec<org::ImmSubtree::Property> properties = {};
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
  org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
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
  struct ExportConfig {
    struct TaskExport {
      BOOST_DESCRIBE_CLASS(TaskExport,
                           (),
                           (),
                           (),
                           (taskWhitelist))
      ImmVec<Str> taskWhitelist = {};
      bool operator==(org::ImmDocumentOptions::ExportConfig::TaskExport const& other) const;
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
    enum class BrokenLinks : short int { Mark, Raise, Ignore, };
    BOOST_DESCRIBE_NESTED_ENUM(BrokenLinks, Mark, Raise, Ignore)
    struct DoExport {
      BOOST_DESCRIBE_CLASS(DoExport,
                           (),
                           (),
                           (),
                           (exportToc))
      bool exportToc;
      bool operator==(org::ImmDocumentOptions::ExportConfig::DoExport const& other) const;
    };

    struct ExportFixed {
      BOOST_DESCRIBE_CLASS(ExportFixed,
                           (),
                           (),
                           (),
                           (exportLevels))
      int exportLevels;
      bool operator==(org::ImmDocumentOptions::ExportConfig::ExportFixed const& other) const;
    };

    using TocExport = std::variant<org::ImmDocumentOptions::ExportConfig::DoExport, org::ImmDocumentOptions::ExportConfig::ExportFixed>;
    enum class TocExportKind : short int { DoExport, ExportFixed, };
    BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
    using variant_enum_type = org::ImmDocumentOptions::ExportConfig::TocExportKind;
    using variant_data_type = org::ImmDocumentOptions::ExportConfig::TocExport;
    BOOST_DESCRIBE_CLASS(ExportConfig,
                         (),
                         (),
                         (),
                         (inlinetasks,
                          footnotes,
                          clock,
                          author,
                          emphasis,
                          specialStrings,
                          propertyDrawers,
                          statisticsCookies,
                          todoText,
                          brokenLinks,
                          tocExport,
                          tagExport,
                          data))
    ImmBox<Opt<bool>> inlinetasks = std::nullopt;
    ImmBox<Opt<bool>> footnotes = std::nullopt;
    ImmBox<Opt<bool>> clock = std::nullopt;
    ImmBox<Opt<bool>> author = std::nullopt;
    ImmBox<Opt<bool>> emphasis = std::nullopt;
    ImmBox<Opt<bool>> specialStrings = std::nullopt;
    ImmBox<Opt<bool>> propertyDrawers = std::nullopt;
    ImmBox<Opt<bool>> statisticsCookies = std::nullopt;
    /// \brief Include todo keywords in export
    ImmBox<Opt<bool>> todoText = std::nullopt;
    org::ImmDocumentOptions::ExportConfig::BrokenLinks brokenLinks;
    org::ImmDocumentOptions::ExportConfig::TocExport tocExport;
    org::ImmDocumentOptions::ExportConfig::TagExport tagExport;
    org::ImmDocumentOptions::ExportConfig::TocExport data;
    bool operator==(org::ImmDocumentOptions::ExportConfig const& other) const;
    org::ImmDocumentOptions::ExportConfig::DoExport const& getDoExport() const { return std::get<0>(data); }
    org::ImmDocumentOptions::ExportConfig::DoExport& getDoExport() { return std::get<0>(data); }
    org::ImmDocumentOptions::ExportConfig::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
    org::ImmDocumentOptions::ExportConfig::ExportFixed& getExportFixed() { return std::get<1>(data); }
    static org::ImmDocumentOptions::ExportConfig::TocExportKind getTocExportKind(org::ImmDocumentOptions::ExportConfig::TocExport const& __input) { return static_cast<org::ImmDocumentOptions::ExportConfig::TocExportKind>(__input.index()); }
    org::ImmDocumentOptions::ExportConfig::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
  };

  enum class Visibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
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
  org::ImmDocumentOptions::Visibility initialVisibility = Visibility::ShowEverything;
  ImmVec<org::ImmSubtree::Property> properties = {};
  org::ImmDocumentOptions::ExportConfig exportConfig;
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