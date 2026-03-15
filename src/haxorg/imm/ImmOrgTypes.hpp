/* clang-format off */
#pragma once
#include <haxorg/imm/ImmOrgBase.hpp>
namespace org::imm {
/// \brief No node
struct ImmNoNode : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmNoNode() = default;
  BOOST_DESCRIBE_CLASS(ImmNoNode, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::NoNode; }
  bool operator==(org::imm::ImmNoNode const& /* d_orgimm_write */ other) const;
};

struct ImmErrorItem : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorItem, (ImmOrg), (), (), (staticKind, diag));
  static OrgSemKind /* imm_write */ const staticKind;
  org::sem::OrgDiagnostics diag;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ErrorItem; }
  bool operator==(org::imm::ImmErrorItem const& /* d_orgimm_write */ other) const;
};

/// \brief Group of value conversion errors
struct ImmErrorGroup : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorGroup, (ImmOrg), (), (), (staticKind, diagnostics));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */> /* imm_write */ diagnostics = {};
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ErrorGroup; }
  bool operator==(org::imm::ImmErrorGroup const& /* d_orgimm_write */ other) const;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct ImmStmt : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  BOOST_DESCRIBE_CLASS(ImmStmt, (ImmOrg), (), (), (attached));
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */ attached;
  bool operator==(org::imm::ImmStmt const& /* d_orgimm_write */ other) const;
};

/// \brief Base class for all inline elements
struct ImmInline : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
  BOOST_DESCRIBE_CLASS(ImmInline, (ImmOrg), (), (), ());
  bool operator==(org::imm::ImmInline const& /* d_orgimm_write */ other) const;
};

/// \brief Zero or more statement nodes
struct ImmStmtList : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  BOOST_DESCRIBE_CLASS(ImmStmtList, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::StmtList; }
  bool operator==(org::imm::ImmStmtList const& /* d_orgimm_write */ other) const;
};

/// \brief Node without content
struct ImmEmpty : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  BOOST_DESCRIBE_CLASS(ImmEmpty, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Empty; }
  bool operator==(org::imm::ImmEmpty const& /* d_orgimm_write */ other) const;
};

/// \brief Base class for block or line commands
struct ImmCmd : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  BOOST_DESCRIBE_CLASS(ImmCmd, (ImmStmt), (), (), (attrs));
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  bool operator==(org::imm::ImmCmd const& /* d_orgimm_write */ other) const;
};

/// \brief Block command type
struct ImmBlock : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
  BOOST_DESCRIBE_CLASS(ImmBlock, (ImmCmd), (), (), ());
  bool operator==(org::imm::ImmBlock const& /* d_orgimm_write */ other) const;
};

/// \brief Line commands
struct ImmLineCommand : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
  BOOST_DESCRIBE_CLASS(ImmLineCommand, (ImmCmd), (), (), ());
  bool operator==(org::imm::ImmLineCommand const& /* d_orgimm_write */ other) const;
};

/// \brief Line command that might get attached to some block element
struct ImmAttached : public org::imm::ImmLineCommand /* imm_write */ {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
  BOOST_DESCRIBE_CLASS(ImmAttached, (ImmLineCommand), (), (), ());
  bool operator==(org::imm::ImmAttached const& /* d_orgimm_write */ other) const;
};

/// \brief Final node
struct ImmLeaf : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  BOOST_DESCRIBE_CLASS(ImmLeaf, (ImmOrg), (), (), (text));
  /// \brief Final leaf value
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ text = "";
  bool operator==(org::imm::ImmLeaf const& /* d_orgimm_write */ other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdCaption : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCaption() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCaption, (ImmAttached), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Content description
  org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */ text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCaption; }
  bool operator==(org::imm::ImmCmdCaption const& /* d_orgimm_write */ other) const;
};

/// \brief Creator of the document
struct ImmCmdCreator : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCreator() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCreator, (ImmCmd), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Creator name text
  org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */ text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCreator; }
  bool operator==(org::imm::ImmCmdCreator const& /* d_orgimm_write */ other) const;
};

/// \brief Author of the document
struct ImmCmdAuthor : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdAuthor() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdAuthor, (ImmCmd), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Author name text
  org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */ text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdAuthor; }
  bool operator==(org::imm::ImmCmdAuthor const& /* d_orgimm_write */ other) const;
};

struct ImmCmdEmail : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdEmail() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdEmail, (ImmCmd), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ text;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdEmail; }
  bool operator==(org::imm::ImmCmdEmail const& /* d_orgimm_write */ other) const;
};

struct ImmCmdLanguage : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdLanguage() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdLanguage, (ImmCmd), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ text;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdLanguage; }
  bool operator==(org::imm::ImmCmdLanguage const& /* d_orgimm_write */ other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdColumns : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdColumns() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdColumns, (ImmAttached), (), (), (staticKind, view));
  static OrgSemKind /* imm_write */ const staticKind;
  org::sem::ColumnView view;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdColumns; }
  bool operator==(org::imm::ImmCmdColumns const& /* d_orgimm_write */ other) const;
};

/// \brief Name identifier for the statement elements.
struct ImmCmdName : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdName, (ImmAttached), (), (), (staticKind, name));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdName; }
  bool operator==(org::imm::ImmCmdName const& /* d_orgimm_write */ other) const;
};

/// \brief Custom line command with list of parsed arguments
struct ImmCmdCustomArgs : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCustomArgs() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomArgs, (ImmCmd), (), (), (staticKind, name, isAttached));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  bool /* imm_write */ isAttached = false;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCustomArgs; }
  bool operator==(org::imm::ImmCmdCustomArgs const& /* d_orgimm_write */ other) const;
};

/// \brief Custom command with raw unparsed string value
struct ImmCmdCustomRaw : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomRaw() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomRaw, (ImmStmt), (), (), (staticKind, name, isAttached, text));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  bool /* imm_write */ isAttached = false;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ text;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCustomRaw; }
  bool operator==(org::imm::ImmCmdCustomRaw const& /* d_orgimm_write */ other) const;
};

/// \brief Custom line command with text paragraph value
struct ImmCmdCustomText : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomText() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCustomText, (ImmStmt), (), (), (staticKind, name, isAttached, text));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  bool /* imm_write */ isAttached = false;
  org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */ text = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCustomText; }
  bool operator==(org::imm::ImmCmdCustomText const& /* d_orgimm_write */ other) const;
};

struct ImmCmdCall : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCall() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdCall, (ImmAttached), (), (), (staticKind,
                                                           name,
                                                           fileName,
                                                           insideHeaderAttrs,
                                                           callAttrs,
                                                           endHeaderAttrs,
                                                           result));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Code block call name
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name = "";
  /// \brief Which file code block should come from
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ fileName = std::nullopt;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup insideHeaderAttrs;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup callAttrs;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup endHeaderAttrs;
  /// \brief Code evaluation results
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */ result = {};
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdCall; }
  bool operator==(org::imm::ImmCmdCall const& /* d_orgimm_write */ other) const;
};

/// \brief Tblfm command type
struct ImmCmdTblfm : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdTblfm, (ImmCmd), (), (), (staticKind, expr));
  static OrgSemKind /* imm_write */ const staticKind;
  org::sem::Tblfm expr;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdTblfm; }
  bool operator==(org::imm::ImmCmdTblfm const& /* d_orgimm_write */ other) const;
};

struct ImmHashTag : public org::imm::ImmInline /* imm_write */ {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  BOOST_DESCRIBE_CLASS(ImmHashTag, (ImmInline), (), (), (staticKind, text));
  static OrgSemKind /* imm_write */ const staticKind;
  org::sem::HashTagText text;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::HashTag; }
  bool operator==(org::imm::ImmHashTag const& /* d_orgimm_write */ other) const;
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmInlineFootnote : public org::imm::ImmInline /* imm_write */ {
  using ImmInline::ImmInline;
  virtual ~ImmInlineFootnote() = default;
  BOOST_DESCRIBE_CLASS(ImmInlineFootnote, (ImmInline), (), (), (staticKind, tag, definition));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Footnote text target name
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ tag = "";
  /// \brief Link to possibly resolved definition
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>> /* rewrite_field */ definition = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::InlineFootnote; }
  bool operator==(org::imm::ImmInlineFootnote const& /* d_orgimm_write */ other) const;
};

/// \brief Inline export
struct ImmInlineExport : public org::imm::ImmInline /* imm_write */ {
  using ImmInline::ImmInline;
  virtual ~ImmInlineExport() = default;
  BOOST_DESCRIBE_CLASS(ImmInlineExport, (ImmInline), (), (), (staticKind, exporter, content));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ exporter = "";
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ content = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::InlineExport; }
  bool operator==(org::imm::ImmInlineExport const& /* d_orgimm_write */ other) const;
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct ImmTime : public org::imm::ImmOrg /* imm_write */ {
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
    BOOST_DESCRIBE_CLASS(Repeat, (), (), (), (mode, period, count));
    /// \brief mode
    org::imm::ImmTime::Repeat::Mode /* imm_write */ mode;
    /// \brief period
    org::imm::ImmTime::Repeat::Period /* imm_write */ period;
    /// \brief count
    int /* imm_write */ count;
    Repeat() {  }
    bool operator==(org::imm::ImmTime::Repeat const& /* imm_write */ other) const;
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static, (), (), (), (repeat, warn, time));
    hstd::ext::ImmVec<org::imm::ImmTime::Repeat /* imm_write */> /* imm_write */ repeat = {};
    hstd::ext::ImmBox<hstd::Opt<org::imm::ImmTime::Repeat /* imm_write */>> /* rewrite_field */ warn = std::nullopt;
    hstd /* imm_write */::UserTime /* imm_write */ time;
    Static() {  }
    bool operator==(org::imm::ImmTime::Static const& /* imm_write */ other) const;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic, (), (), (), (expr));
    org::sem::LispCode expr;
    Dynamic() {  }
    bool operator==(org::imm::ImmTime::Dynamic const& /* imm_write */ other) const;
  };

  using TimeVariant = std::variant<org::imm::ImmTime::Static /* imm_write */, org::imm::ImmTime::Dynamic /* imm_write */>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = org::imm::ImmTime::TimeKind /* imm_write */;
  using variant_data_type = org::imm::ImmTime::TimeVariant /* imm_write */;
  BOOST_DESCRIBE_CLASS(ImmTime, (ImmOrg), (), (), (staticKind, isActive, time));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief <active> vs [inactive]
  bool /* imm_write */ isActive = false;
  org::imm::ImmTime::TimeVariant /* imm_write */ time;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Time; }
  bool operator==(org::imm::ImmTime const& /* d_orgimm_write */ other) const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  org::imm::ImmTime::Static const& /* imm_write */ getStatic() const { return hstd::variant_get<0>(time); }
  org::imm::ImmTime::Static& /* imm_write */ getStatic() { return hstd::variant_get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::imm::ImmTime::Dynamic const& /* imm_write */ getDynamic() const { return hstd::variant_get<1>(time); }
  org::imm::ImmTime::Dynamic& /* imm_write */ getDynamic() { return hstd::variant_get<1>(time); }
  static org::imm::ImmTime::TimeKind /* imm_write */ getTimeKind(org::imm::ImmTime::TimeVariant const& /* imm_write */ __input) { return static_cast<org::imm::ImmTime::TimeKind /* imm_write */>(__input.index()); }
  org::imm::ImmTime::TimeKind /* imm_write */ getTimeKind() const { return getTimeKind(time); }
  char const* sub_variant_get_name() const { return "time"; }
  org::imm::ImmTime::TimeVariant const& /* imm_write */ sub_variant_get_data() const { return time; }
  org::imm::ImmTime::TimeKind /* imm_write */ sub_variant_get_kind() const { return getTimeKind(); }
};

/// \brief Range of time delimited by two points
struct ImmTimeRange : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmTimeRange() = default;
  BOOST_DESCRIBE_CLASS(ImmTimeRange, (ImmOrg), (), (), (staticKind, from, to));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Starting time
  org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */ from = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  /// \brief Finishing time
  org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */ to = org::imm::ImmIdT<org::imm::ImmTime>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::TimeRange; }
  bool operator==(org::imm::ImmTimeRange const& /* d_orgimm_write */ other) const;
};

/// \brief Inline macro invocation
struct ImmMacro : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmMacro() = default;
  BOOST_DESCRIBE_CLASS(ImmMacro, (ImmOrg), (), (), (staticKind, name, attrs));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Macro name
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Macro; }
  bool operator==(org::imm::ImmMacro const& /* d_orgimm_write */ other) const;
};

/// \brief Text symbol or symbol command
struct ImmSymbol : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymbol() = default;
  /// \brief Symbol parameters
  struct Param {
    BOOST_DESCRIBE_CLASS(Param, (), (), (), (key, value));
    /// \brief Key -- for non-positional
    hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ key;
    /// \brief Uninterpreted value
    hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ value;
    bool operator==(org::imm::ImmSymbol::Param const& /* imm_write */ other) const;
  };

  BOOST_DESCRIBE_CLASS(ImmSymbol, (ImmOrg), (), (), (staticKind, name, parameters, positional));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Name of the symbol
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  /// \brief Optional list of parameters
  hstd::ext::ImmVec<org::imm::ImmSymbol::Param /* imm_write */> /* imm_write */ parameters;
  /// \brief Positional parameters
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */ positional;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Symbol; }
  bool operator==(org::imm::ImmSymbol const& /* d_orgimm_write */ other) const;
};

/// \brief Escaped text
struct ImmEscaped : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  BOOST_DESCRIBE_CLASS(ImmEscaped, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Escaped; }
  bool operator==(org::imm::ImmEscaped const& /* d_orgimm_write */ other) const;
};

/// \brief \n newline
struct ImmNewline : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  BOOST_DESCRIBE_CLASS(ImmNewline, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Newline; }
  bool operator==(org::imm::ImmNewline const& /* d_orgimm_write */ other) const;
};

/// \brief ' "space",
struct ImmSpace : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  BOOST_DESCRIBE_CLASS(ImmSpace, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Space; }
  bool operator==(org::imm::ImmSpace const& /* d_orgimm_write */ other) const;
};

/// \brief word
struct ImmWord : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  BOOST_DESCRIBE_CLASS(ImmWord, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Word; }
  bool operator==(org::imm::ImmWord const& /* d_orgimm_write */ other) const;
};

/// \brief `@mention`
struct ImmAtMention : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  BOOST_DESCRIBE_CLASS(ImmAtMention, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::AtMention; }
  bool operator==(org::imm::ImmAtMention const& /* d_orgimm_write */ other) const;
};

struct ImmRawText : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  BOOST_DESCRIBE_CLASS(ImmRawText, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::RawText; }
  bool operator==(org::imm::ImmRawText const& /* d_orgimm_write */ other) const;
};

struct ImmPunctuation : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  BOOST_DESCRIBE_CLASS(ImmPunctuation, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Punctuation; }
  bool operator==(org::imm::ImmPunctuation const& /* d_orgimm_write */ other) const;
};

struct ImmPlaceholder : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  BOOST_DESCRIBE_CLASS(ImmPlaceholder, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Placeholder; }
  bool operator==(org::imm::ImmPlaceholder const& /* d_orgimm_write */ other) const;
};

struct ImmBigIdent : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  BOOST_DESCRIBE_CLASS(ImmBigIdent, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BigIdent; }
  bool operator==(org::imm::ImmBigIdent const& /* d_orgimm_write */ other) const;
};

/// \brief `<<target>>`
struct ImmTextTarget : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmTextTarget, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::TextTarget; }
  bool operator==(org::imm::ImmTextTarget const& /* d_orgimm_write */ other) const;
};

/// \brief Single token skipped during error recovery
struct ImmErrorSkipToken : public org::imm::ImmLeaf /* imm_write */ {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmErrorSkipToken() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorSkipToken, (ImmLeaf), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ErrorSkipToken; }
  bool operator==(org::imm::ImmErrorSkipToken const& /* d_orgimm_write */ other) const;
};

/// \brief Group of tokens skipped in search of the next synchronization point during parse fail recovery
struct ImmErrorSkipGroup : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorSkipGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmErrorSkipGroup, (ImmOrg), (), (), (staticKind, skipped));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */> /* imm_write */ skipped = {};
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ErrorSkipGroup; }
  bool operator==(org::imm::ImmErrorSkipGroup const& /* d_orgimm_write */ other) const;
};

struct ImmMarkup : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkup, (ImmOrg), (), (), ());
  bool operator==(org::imm::ImmMarkup const& /* d_orgimm_write */ other) const;
};

struct ImmBold : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  BOOST_DESCRIBE_CLASS(ImmBold, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Bold; }
  bool operator==(org::imm::ImmBold const& /* d_orgimm_write */ other) const;
};

struct ImmUnderline : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  BOOST_DESCRIBE_CLASS(ImmUnderline, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Underline; }
  bool operator==(org::imm::ImmUnderline const& /* d_orgimm_write */ other) const;
};

struct ImmMonospace : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  BOOST_DESCRIBE_CLASS(ImmMonospace, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Monospace; }
  bool operator==(org::imm::ImmMonospace const& /* d_orgimm_write */ other) const;
};

struct ImmMarkQuote : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmMarkQuote, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::MarkQuote; }
  bool operator==(org::imm::ImmMarkQuote const& /* d_orgimm_write */ other) const;
};

struct ImmVerbatim : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  BOOST_DESCRIBE_CLASS(ImmVerbatim, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Verbatim; }
  bool operator==(org::imm::ImmVerbatim const& /* d_orgimm_write */ other) const;
};

struct ImmItalic : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  BOOST_DESCRIBE_CLASS(ImmItalic, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Italic; }
  bool operator==(org::imm::ImmItalic const& /* d_orgimm_write */ other) const;
};

struct ImmStrike : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  BOOST_DESCRIBE_CLASS(ImmStrike, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Strike; }
  bool operator==(org::imm::ImmStrike const& /* d_orgimm_write */ other) const;
};

struct ImmPar : public org::imm::ImmMarkup /* imm_write */ {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  BOOST_DESCRIBE_CLASS(ImmPar, (ImmMarkup), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Par; }
  bool operator==(org::imm::ImmPar const& /* d_orgimm_write */ other) const;
};

/// \brief `<<<target>>>`
struct ImmRadioTarget : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmRadioTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmRadioTarget, (ImmOrg), (), (), (staticKind, words));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */ words = {};
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::RadioTarget; }
  bool operator==(org::imm::ImmRadioTarget const& /* d_orgimm_write */ other) const;
};

/// \brief Latex code body
struct ImmLatex : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  BOOST_DESCRIBE_CLASS(ImmLatex, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Latex; }
  bool operator==(org::imm::ImmLatex const& /* d_orgimm_write */ other) const;
};

struct ImmLink : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmLink() = default;
  BOOST_DESCRIBE_CLASS(ImmLink, (ImmStmt), (), (), (staticKind, description, target));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ description = std::nullopt;
  org::sem::LinkTarget target;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Link; }
  bool operator==(org::imm::ImmLink const& /* d_orgimm_write */ other) const;
};

/// \brief Center nested content in export
struct ImmBlockCenter : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCenter() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCenter, (ImmBlock), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockCenter; }
  bool operator==(org::imm::ImmBlockCenter const& /* d_orgimm_write */ other) const;
};

/// \brief Quotation block
struct ImmBlockQuote : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockQuote, (ImmBlock), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockQuote; }
  bool operator==(org::imm::ImmBlockQuote const& /* d_orgimm_write */ other) const;
};

/// \brief Comment block
struct ImmBlockComment : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockComment, (ImmStmt), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockComment; }
  bool operator==(org::imm::ImmBlockComment const& /* d_orgimm_write */ other) const;
};

/// \brief Verse quotation block
struct ImmBlockVerse : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockVerse, (ImmBlock), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockVerse; }
  bool operator==(org::imm::ImmBlockVerse const& /* d_orgimm_write */ other) const;
};

struct ImmBlockDynamicFallback : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockDynamicFallback, (ImmBlock), (), (), (staticKind, name));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockDynamicFallback; }
  bool operator==(org::imm::ImmBlockDynamicFallback const& /* d_orgimm_write */ other) const;
};

/// \brief Example block
struct ImmBlockExample : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockExample, (ImmBlock), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockExample; }
  bool operator==(org::imm::ImmBlockExample const& /* d_orgimm_write */ other) const;
};

/// \brief Direct export passthrough
struct ImmBlockExport : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExport() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockExport, (ImmBlock), (), (), (staticKind, exporter, content));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ exporter = "";
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ content = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockExport; }
  bool operator==(org::imm::ImmBlockExport const& /* d_orgimm_write */ other) const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct ImmBlockAdmonition : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockAdmonition, (ImmBlock), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockAdmonition; }
  bool operator==(org::imm::ImmBlockAdmonition const& /* d_orgimm_write */ other) const;
};

/// \brief Parsed results of code block evaluation
struct ImmBlockCodeEvalResult : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCodeEvalResult() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCodeEvalResult, (ImmBlock), (), (), (staticKind, raw, node));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> /* imm_write */ raw;
  org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */ node = org::imm::ImmIdT<org::imm::ImmOrg>::Nil();
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockCodeEvalResult; }
  bool operator==(org::imm::ImmBlockCodeEvalResult const& /* d_orgimm_write */ other) const;
};

/// \brief Base class for all code blocks
struct ImmBlockCode : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCode() = default;
  BOOST_DESCRIBE_CLASS(ImmBlockCode, (ImmBlock), (), (), (staticKind, lang, result, lines, switches));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Code block language name
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ lang = std::nullopt;
  /// \brief Code evaluation results
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */ result = {};
  /// \brief Collected code lines
  hstd::ext::ImmVec<org::sem::BlockCodeLine> /* imm_write */ lines = {};
  /// \brief Dash-based switches for code block execution
  org::sem::AttrGroup switches;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::BlockCode; }
  bool operator==(org::imm::ImmBlockCode const& /* d_orgimm_write */ other) const;
};

/// \brief Single subtree log entry
struct ImmSubtreeLog : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtreeLog() = default;
  BOOST_DESCRIBE_CLASS(ImmSubtreeLog, (ImmOrg), (), (), (staticKind, head, desc));
  static OrgSemKind /* imm_write */ const staticKind;
  org::sem::SubtreeLogHead head;
  /// \brief Optional description of the log entry
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList /* imm_write */> /* imm_write */>> /* rewrite_field */ desc = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::SubtreeLog; }
  bool operator==(org::imm::ImmSubtreeLog const& /* d_orgimm_write */ other) const;
};

/// \brief Subtree
struct ImmSubtree : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtree() = default;
  BOOST_DESCRIBE_CLASS(ImmSubtree, (ImmOrg), (), (), (staticKind,
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
                                                      priority));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Subtree level
  int /* imm_write */ level = 0;
  /// \brief :ID: property
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ treeId = std::nullopt;
  /// \brief Todo state of the tree
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ todo = std::nullopt;
  /// \brief Task completion state
  hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>> /* rewrite_field */ completion = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ description = std::nullopt;
  /// \brief Trailing tags
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */ tags = {};
  /// \brief Main title
  org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */ title = org::imm::ImmIdT<org::imm::ImmParagraph>::Nil();
  /// \brief Associated subtree log
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */> /* imm_write */ logbook = {};
  /// \brief Immediate properties
  hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */ properties = {};
  /// \brief When subtree was marked as closed
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>> /* rewrite_field */ closed = std::nullopt;
  /// \brief When is the deadline
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>> /* rewrite_field */ deadline = std::nullopt;
  /// \brief When the event is scheduled
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>> /* rewrite_field */ scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool /* imm_write */ isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool /* imm_write */ isArchived = false;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ priority = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Subtree; }
  bool operator==(org::imm::ImmSubtree const& /* d_orgimm_write */ other) const;
};

/// \brief Table cell
struct ImmCell : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmCell() = default;
  BOOST_DESCRIBE_CLASS(ImmCell, (ImmCmd), (), (), (staticKind, isBlock));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool /* imm_write */ isBlock = false;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Cell; }
  bool operator==(org::imm::ImmCell const& /* d_orgimm_write */ other) const;
};

/// \brief Table row
struct ImmRow : public org::imm::ImmCmd /* imm_write */ {
  using ImmCmd::ImmCmd;
  virtual ~ImmRow() = default;
  BOOST_DESCRIBE_CLASS(ImmRow, (ImmCmd), (), (), (staticKind, cells, isBlock));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief List of cells on the row
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */> /* imm_write */ cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool /* imm_write */ isBlock = false;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Row; }
  bool operator==(org::imm::ImmRow const& /* d_orgimm_write */ other) const;
};

/// \brief Table
struct ImmTable : public org::imm::ImmBlock /* imm_write */ {
  using ImmBlock::ImmBlock;
  virtual ~ImmTable() = default;
  BOOST_DESCRIBE_CLASS(ImmTable, (ImmBlock), (), (), (staticKind, rows, isBlock));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief List of rows for the table
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */> /* imm_write */ rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool /* imm_write */ isBlock = false;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Table; }
  bool operator==(org::imm::ImmTable const& /* d_orgimm_write */ other) const;
};

/// \brief Top-level or inline paragraph
struct ImmParagraph : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  BOOST_DESCRIBE_CLASS(ImmParagraph, (ImmStmt), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Paragraph; }
  bool operator==(org::imm::ImmParagraph const& /* d_orgimm_write */ other) const;
};

/// \brief Shortened colon example block
struct ImmColonExample : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmColonExample() = default;
  BOOST_DESCRIBE_CLASS(ImmColonExample, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ColonExample; }
  bool operator==(org::imm::ImmColonExample const& /* d_orgimm_write */ other) const;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdAttr : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdAttr, (ImmAttached), (), (), (staticKind, target));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ target;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdAttr; }
  bool operator==(org::imm::ImmCmdAttr const& /* d_orgimm_write */ other) const;
};

/// \brief Single line of passthrough code
struct ImmCmdExport : public org::imm::ImmAttached /* imm_write */ {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdExport() = default;
  BOOST_DESCRIBE_CLASS(ImmCmdExport, (ImmAttached), (), (), (staticKind, exporter, content));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ exporter = "";
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ content = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdExport; }
  bool operator==(org::imm::ImmCmdExport const& /* d_orgimm_write */ other) const;
};

/// \brief Inline, statement or block call
struct ImmCall : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmCall() = default;
  BOOST_DESCRIBE_CLASS(ImmCall, (ImmOrg), (), (), (staticKind, name, attrs, isCommand));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Call target name
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ name;
  /// \brief Additional parameters aside from 'exporter'
  org::sem::AttrGroup attrs;
  bool /* imm_write */ isCommand = false;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Call; }
  bool operator==(org::imm::ImmCall const& /* d_orgimm_write */ other) const;
};

struct ImmList : public org::imm::ImmStmt /* imm_write */ {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  BOOST_DESCRIBE_CLASS(ImmList, (ImmStmt), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::List; }
  bool operator==(org::imm::ImmList const& /* d_orgimm_write */ other) const;
};

struct ImmListItem : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmListItem() = default;
  BOOST_DESCRIBE_CLASS(ImmListItem, (ImmOrg), (), (), (staticKind, checkbox, header, bullet));
  static OrgSemKind /* imm_write */ const staticKind;
  CheckboxState /* imm_write */ checkbox = CheckboxState::None;
  /// \brief Description list item header
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ bullet = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::ListItem; }
  bool operator==(org::imm::ImmListItem const& /* d_orgimm_write */ other) const;
};

struct ImmDocumentOptions : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentOptions() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentOptions, (ImmOrg), (), (), (staticKind,
                                                              initialVisibility,
                                                              properties,
                                                              exportConfig,
                                                              fixedWidthSections,
                                                              startupIndented,
                                                              category,
                                                              setupfile,
                                                              maxSubtreeLevelExport,
                                                              columns,
                                                              todoKeywords,
                                                              doneKeywords));
  static OrgSemKind /* imm_write */ const staticKind;
  InitialSubtreeVisibility /* imm_write */ initialVisibility = InitialSubtreeVisibility::ShowEverything;
  hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */ properties = {};
  org::sem::DocumentExportConfig exportConfig;
  hstd::ext::ImmBox<hstd::Opt<bool /* imm_write */>> /* rewrite_field */ fixedWidthSections = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<bool /* imm_write */>> /* rewrite_field */ startupIndented = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ category = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ setupfile = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */ maxSubtreeLevelExport = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>> /* rewrite_field */ columns = std::nullopt;
  hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */ todoKeywords = {};
  hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */ doneKeywords = {};
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::DocumentOptions; }
  bool operator==(org::imm::ImmDocumentOptions const& /* d_orgimm_write */ other) const;
};

/// \brief Part of the document embedded in a larger file (e.g. in comments)
struct ImmDocumentFragment : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentFragment() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentFragment, (ImmOrg), (), (), (staticKind, baseLine, baseCol));
  static OrgSemKind /* imm_write */ const staticKind;
  int /* imm_write */ baseLine;
  int /* imm_write */ baseCol;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::DocumentFragment; }
  bool operator==(org::imm::ImmDocumentFragment const& /* d_orgimm_write */ other) const;
};

/// \brief https://fletcher.github.io/MultiMarkdown-6/syntax/critic.html
struct ImmCriticMarkup : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmCriticMarkup() = default;
  enum class Kind : short int { Deletion, Addition, Substitution, Highlighting, Comment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Deletion, Addition, Substitution, Highlighting, Comment)
  BOOST_DESCRIBE_CLASS(ImmCriticMarkup, (ImmOrg), (), (), (staticKind, kind));
  static OrgSemKind /* imm_write */ const staticKind;
  org::imm::ImmCriticMarkup::Kind /* imm_write */ kind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CriticMarkup; }
  bool operator==(org::imm::ImmCriticMarkup const& /* d_orgimm_write */ other) const;
};

struct ImmDocument : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocument() = default;
  BOOST_DESCRIBE_CLASS(ImmDocument, (ImmOrg), (), (), (staticKind,
                                                       title,
                                                       author,
                                                       creator,
                                                       filetags,
                                                       email,
                                                       language,
                                                       options,
                                                       exportFileName));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ title = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ author = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */ creator = std::nullopt;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */ filetags = {};
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText /* imm_write */> /* imm_write */>> /* rewrite_field */ email = std::nullopt;
  hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */ language = {};
  org::imm::ImmIdT<org::imm::ImmDocumentOptions /* imm_write */> /* imm_write */ options = org::imm::ImmIdT<org::imm::ImmDocumentOptions>::Nil();
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ exportFileName = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Document; }
  bool operator==(org::imm::ImmDocument const& /* d_orgimm_write */ other) const;
};

struct ImmFileTarget : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmFileTarget() = default;
  BOOST_DESCRIBE_CLASS(ImmFileTarget, (ImmOrg), (), (), (staticKind,
                                                         path,
                                                         line,
                                                         searchTarget,
                                                         restrictToHeadlines,
                                                         targetId,
                                                         regexp));
  static OrgSemKind /* imm_write */ const staticKind;
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ path;
  hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */ line = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ searchTarget = std::nullopt;
  bool /* imm_write */ restrictToHeadlines = false;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ targetId = std::nullopt;
  hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ regexp = std::nullopt;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::FileTarget; }
  bool operator==(org::imm::ImmFileTarget const& /* d_orgimm_write */ other) const;
};

struct ImmTextSeparator : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  BOOST_DESCRIBE_CLASS(ImmTextSeparator, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::TextSeparator; }
  bool operator==(org::imm::ImmTextSeparator const& /* d_orgimm_write */ other) const;
};

struct ImmDocumentGroup : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(ImmDocumentGroup, (ImmOrg), (), (), (staticKind));
  static OrgSemKind /* imm_write */ const staticKind;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::DocumentGroup; }
  bool operator==(org::imm::ImmDocumentGroup const& /* d_orgimm_write */ other) const;
};

struct ImmFile : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmFile() = default;
  struct Document {
    BOOST_DESCRIBE_CLASS(Document, (), (), (), ());
    bool operator==(org::imm::ImmFile::Document const& /* imm_write */ other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment, (), (), (), ());
    bool operator==(org::imm::ImmFile::Attachment const& /* imm_write */ other) const;
  };

  struct Source {
    BOOST_DESCRIBE_CLASS(Source, (), (), (), ());
    bool operator==(org::imm::ImmFile::Source const& /* imm_write */ other) const;
  };

  using Data = std::variant<org::imm::ImmFile::Document /* imm_write */, org::imm::ImmFile::Attachment /* imm_write */, org::imm::ImmFile::Source /* imm_write */>;
  enum class Kind : short int { Document, Attachment, Source, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Document, Attachment, Source)
  using variant_enum_type = org::imm::ImmFile::Kind /* imm_write */;
  using variant_data_type = org::imm::ImmFile::Data /* imm_write */;
  BOOST_DESCRIBE_CLASS(ImmFile, (ImmOrg), (), (), (staticKind, relPath, absPath, data));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Relative path from the root directory
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ relPath = "";
  /// \brief Absolute resolved path to physical file
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ absPath = "";
  org::imm::ImmFile::Data /* imm_write */ data;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::File; }
  bool operator==(org::imm::ImmFile const& /* d_orgimm_write */ other) const;
  bool isDocument() const { return getFileKind() == Kind::Document; }
  org::imm::ImmFile::Document const& /* imm_write */ getDocument() const { return hstd::variant_get<0>(data); }
  org::imm::ImmFile::Document& /* imm_write */ getDocument() { return hstd::variant_get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  org::imm::ImmFile::Attachment const& /* imm_write */ getAttachment() const { return hstd::variant_get<1>(data); }
  org::imm::ImmFile::Attachment& /* imm_write */ getAttachment() { return hstd::variant_get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  org::imm::ImmFile::Source const& /* imm_write */ getSource() const { return hstd::variant_get<2>(data); }
  org::imm::ImmFile::Source& /* imm_write */ getSource() { return hstd::variant_get<2>(data); }
  static org::imm::ImmFile::Kind /* imm_write */ getFileKind(org::imm::ImmFile::Data const& /* imm_write */ __input) { return static_cast<org::imm::ImmFile::Kind /* imm_write */>(__input.index()); }
  org::imm::ImmFile::Kind /* imm_write */ getFileKind() const { return getFileKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::imm::ImmFile::Data const& /* imm_write */ sub_variant_get_data() const { return data; }
  org::imm::ImmFile::Kind /* imm_write */ sub_variant_get_kind() const { return getFileKind(); }
};

struct ImmDirectory : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmDirectory() = default;
  BOOST_DESCRIBE_CLASS(ImmDirectory, (ImmOrg), (), (), (staticKind, relPath, absPath));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Relative path from the root directory, empty if this is the root directory
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ relPath = "";
  /// \brief Absolute resolved path to physical directory
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ absPath = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Directory; }
  bool operator==(org::imm::ImmDirectory const& /* d_orgimm_write */ other) const;
};

struct ImmSymlink : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymlink() = default;
  BOOST_DESCRIBE_CLASS(ImmSymlink, (ImmOrg), (), (), (staticKind, isDirectory, absPath));
  static OrgSemKind /* imm_write */ const staticKind;
  bool /* imm_write */ isDirectory;
  /// \brief Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ absPath = "";
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::Symlink; }
  bool operator==(org::imm::ImmSymlink const& /* d_orgimm_write */ other) const;
};

struct ImmCmdInclude : public org::imm::ImmOrg /* imm_write */ {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase, (), (), (), ());
    IncludeBase() {  }
    bool operator==(org::imm::ImmCmdInclude::IncludeBase const& /* imm_write */ other) const;
  };

  struct Example : public org::imm::ImmCmdInclude::IncludeBase /* imm_write */ {
    BOOST_DESCRIBE_CLASS(Example, (IncludeBase), (), (), ());
    Example() {  }
    bool operator==(org::imm::ImmCmdInclude::Example const& /* imm_write */ other) const;
  };

  struct Export : public org::imm::ImmCmdInclude::IncludeBase /* imm_write */ {
    BOOST_DESCRIBE_CLASS(Export, (IncludeBase), (), (), (language));
    /// \brief Source code language for export
    hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ language;
    Export() {  }
    bool operator==(org::imm::ImmCmdInclude::Export const& /* imm_write */ other) const;
  };

  /// \brief Second positional argument in the include command can have any arbitrary value -- default src/export/example have additional properties, but user can provide anything else there.
  struct Custom : public org::imm::ImmCmdInclude::IncludeBase /* imm_write */ {
    BOOST_DESCRIBE_CLASS(Custom, (IncludeBase), (), (), (blockName));
    /// \brief Block name not covered by the default values
    hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ blockName;
    Custom() {  }
    bool operator==(org::imm::ImmCmdInclude::Custom const& /* imm_write */ other) const;
  };

  struct Src : public org::imm::ImmCmdInclude::IncludeBase /* imm_write */ {
    BOOST_DESCRIBE_CLASS(Src, (IncludeBase), (), (), (language));
    /// \brief Source code language for code block
    hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ language;
    Src() {  }
    bool operator==(org::imm::ImmCmdInclude::Src const& /* imm_write */ other) const;
  };

  struct OrgDocument : public org::imm::ImmCmdInclude::IncludeBase /* imm_write */ {
    BOOST_DESCRIBE_CLASS(OrgDocument, (IncludeBase), (), (), (onlyContent, subtreePath, minLevel, customIdTarget));
    /// \brief omits any planning lines or property drawers
    hstd::ext::ImmBox<hstd::Opt<bool /* imm_write */>> /* rewrite_field */ onlyContent = std::nullopt;
    /// \brief Include first subtree matching path with `file.org::* tree`
    hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreePath>> /* rewrite_field */ subtreePath = std::nullopt;
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */ minLevel = std::nullopt;
    /// \brief Include target subtree content with `file.org::#custom`
    hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */ customIdTarget = std::nullopt;
    OrgDocument() {  }
    bool operator==(org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */ other) const;
  };

  using Data = std::variant<org::imm::ImmCmdInclude::Example /* imm_write */, org::imm::ImmCmdInclude::Export /* imm_write */, org::imm::ImmCmdInclude::Custom /* imm_write */, org::imm::ImmCmdInclude::Src /* imm_write */, org::imm::ImmCmdInclude::OrgDocument /* imm_write */>;
  enum class Kind : short int { Example, Export, Custom, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Custom, Src, OrgDocument)
  using variant_enum_type = org::imm::ImmCmdInclude::Kind /* imm_write */;
  using variant_data_type = org::imm::ImmCmdInclude::Data /* imm_write */;
  BOOST_DESCRIBE_CLASS(ImmCmdInclude, (ImmOrg), (), (), (staticKind, path, firstLine, lastLine, data));
  static OrgSemKind /* imm_write */ const staticKind;
  /// \brief Path to include
  hstd::ext::ImmBox<hstd::Str> /* rewrite_field */ path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */ firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */ lastLine = std::nullopt;
  org::imm::ImmCmdInclude::Data /* imm_write */ data;
  virtual OrgSemKind /* imm_write */ getKind() const { return OrgSemKind::CmdInclude; }
  bool operator==(org::imm::ImmCmdInclude const& /* d_orgimm_write */ other) const;
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  org::imm::ImmCmdInclude::Example const& /* imm_write */ getExample() const { return hstd::variant_get<0>(data); }
  org::imm::ImmCmdInclude::Example& /* imm_write */ getExample() { return hstd::variant_get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  org::imm::ImmCmdInclude::Export const& /* imm_write */ getExport() const { return hstd::variant_get<1>(data); }
  org::imm::ImmCmdInclude::Export& /* imm_write */ getExport() { return hstd::variant_get<1>(data); }
  bool isCustom() const { return getIncludeKind() == Kind::Custom; }
  org::imm::ImmCmdInclude::Custom const& /* imm_write */ getCustom() const { return hstd::variant_get<2>(data); }
  org::imm::ImmCmdInclude::Custom& /* imm_write */ getCustom() { return hstd::variant_get<2>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  org::imm::ImmCmdInclude::Src const& /* imm_write */ getSrc() const { return hstd::variant_get<3>(data); }
  org::imm::ImmCmdInclude::Src& /* imm_write */ getSrc() { return hstd::variant_get<3>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */ getOrgDocument() const { return hstd::variant_get<4>(data); }
  org::imm::ImmCmdInclude::OrgDocument& /* imm_write */ getOrgDocument() { return hstd::variant_get<4>(data); }
  static org::imm::ImmCmdInclude::Kind /* imm_write */ getIncludeKind(org::imm::ImmCmdInclude::Data const& /* imm_write */ __input) { return static_cast<org::imm::ImmCmdInclude::Kind /* imm_write */>(__input.index()); }
  org::imm::ImmCmdInclude::Kind /* imm_write */ getIncludeKind() const { return getIncludeKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::imm::ImmCmdInclude::Data const& /* imm_write */ sub_variant_get_data() const { return data; }
  org::imm::ImmCmdInclude::Kind /* imm_write */ sub_variant_get_kind() const { return getIncludeKind(); }
};

}
/* clang-format on */