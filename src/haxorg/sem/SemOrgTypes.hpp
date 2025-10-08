/* clang-format off */
#pragma once
#include <haxorg/sem/SemOrgEnums.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <haxorg/parse/OrgTypes.hpp>
#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <haxorg/sem/SemOrgBase.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>
#include <haxorg/sem/SemOrgSharedTypes.hpp>
namespace org::sem {
/// \brief No node
struct None : public org::sem::Org {
  using Org::Org;
  virtual ~None() = default;
  BOOST_DESCRIBE_CLASS(None,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::None; }
};

struct ErrorItem : public org::sem::Org {
  using Org::Org;
  virtual ~ErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ErrorItem,
                       (Org),
                       (),
                       (),
                       (staticKind, message, function, line))
  static OrgSemKind const staticKind;
  hstd::Str message;
  /// \brief Conversion function name where the error was created
  hstd::Opt<hstd::Str> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::Opt<int> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorItem; }
};

/// \brief Group of value conversion errors
struct ErrorGroup : public org::sem::Org {
  using Org::Org;
  virtual ~ErrorGroup() = default;
  BOOST_DESCRIBE_CLASS(ErrorGroup,
                       (Org),
                       (),
                       (),
                       (staticKind, diagnostics, function, line))
  static OrgSemKind const staticKind;
  hstd::Vec<org::sem::SemId<org::sem::ErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  hstd::Opt<hstd::Str> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  hstd::Opt<int> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorGroup; }
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct Stmt : public org::sem::Org {
  using Org::Org;
  virtual ~Stmt() = default;
  Stmt() {}
  Stmt(hstd::Vec<SemId<Org>> const& attached, hstd::Vec<SemId<Org>> const& subnodes) : Org(subnodes), attached(attached) {}
  BOOST_DESCRIBE_CLASS(Stmt,
                       (Org),
                       (),
                       (),
                       (attached))
  hstd::Vec<org::sem::SemId<org::sem::Org>> attached;
  /// \brief Return attached nodes of a specific kinds or all attached (if kind is nullopt)
  hstd::Vec<org::sem::SemId<org::sem::Org>> getAttached(hstd::Opt<hstd::Str> const& kind = std::nullopt) const;
  hstd::Vec<org::sem::SemId<org::sem::Org>> getCaption() const;
  hstd::Vec<hstd::Str> getName() const;
  /// \brief Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.
  virtual hstd::Vec<org::sem::AttrValue> getAttrs(hstd::Opt<hstd::Str> const& kind = std::nullopt) const;
  /// \brief Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities
  virtual hstd::Opt<org::sem::AttrValue> getFirstAttr(hstd::Str const& kind) const;
  hstd::Opt<hstd::Str> getFirstAttrString(hstd::Str const& kind) const;
  hstd::Opt<int> getFirstAttrInt(hstd::Str const& kind) const;
  hstd::Opt<bool> getFirstAttrBool(hstd::Str const& kind) const;
  hstd::Opt<double> getFirstAttrDouble(hstd::Str const& kind) const;
  hstd::Opt<org::sem::AttrValue::LispValue> getFirstAttrLisp(hstd::Str const& kind) const;
  hstd::Opt<org::sem::AttrValue::Kind> getFirstAttrKind(hstd::Str const& kind) const;
};

/// \brief Base class for all inline elements
struct Inline : public org::sem::Org {
  using Org::Org;
  virtual ~Inline() = default;
  BOOST_DESCRIBE_CLASS(Inline, (Org), (), (), ())
};

/// \brief Zero or more statement nodes
struct StmtList : public org::sem::Org {
  using Org::Org;
  virtual ~StmtList() = default;
  BOOST_DESCRIBE_CLASS(StmtList,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::StmtList; }
};

/// \brief Node without content
struct Empty : public org::sem::Org {
  using Org::Org;
  virtual ~Empty() = default;
  BOOST_DESCRIBE_CLASS(Empty,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
};

/// \brief Base class for block or line commands
struct Cmd : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~Cmd() = default;
  BOOST_DESCRIBE_CLASS(Cmd,
                       (Stmt),
                       (),
                       (),
                       (attrs))
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  /// \brief Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.
  virtual hstd::Vec<org::sem::AttrValue> getAttrs(hstd::Opt<hstd::Str> const& key = std::nullopt) const override;
  /// \brief Override of the base statement argument get, prioritizing the explicit command parameters
  virtual hstd::Opt<org::sem::AttrValue> getFirstAttr(hstd::Str const& kind) const override;
};

/// \brief Block command type
struct Block : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~Block() = default;
  BOOST_DESCRIBE_CLASS(Block, (Cmd), (), (), ())
};

/// \brief Line commands
struct LineCommand : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~LineCommand() = default;
  BOOST_DESCRIBE_CLASS(LineCommand, (Cmd), (), (), ())
};

/// \brief Line command that might get attached to some block element
struct Attached : public org::sem::LineCommand {
  using LineCommand::LineCommand;
  virtual ~Attached() = default;
  BOOST_DESCRIBE_CLASS(Attached, (LineCommand), (), (), ())
};

/// \brief Final node
struct Leaf : public org::sem::Org {
  using Org::Org;
  virtual ~Leaf() = default;
  BOOST_DESCRIBE_CLASS(Leaf,
                       (Org),
                       (),
                       (),
                       (text))
  /// \brief Final leaf value
  hstd::Str text = "";
  hstd::Str getText() const { return text; }
};

/// \brief Caption annotation for any subsequent node
struct CmdCaption : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdCaption() = default;
  BOOST_DESCRIBE_CLASS(CmdCaption,
                       (Attached),
                       (),
                       (),
                       (staticKind, text))
  static OrgSemKind const staticKind;
  /// \brief Content description
  org::sem::SemId<org::sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
};

/// \brief Caption annotation for any subsequent node
struct CmdColumns : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdColumns() = default;
  BOOST_DESCRIBE_CLASS(CmdColumns,
                       (Attached),
                       (),
                       (),
                       (staticKind, view))
  static OrgSemKind const staticKind;
  org::sem::ColumnView view;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdColumns; }
};

/// \brief Name identifier for the statement elements.
struct CmdName : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdName() = default;
  BOOST_DESCRIBE_CLASS(CmdName,
                       (Attached),
                       (),
                       (),
                       (staticKind, name))
  static OrgSemKind const staticKind;
  hstd::Str name;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
};

/// \brief Custom line command with list of parsed arguments
struct CmdCustomArgs : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~CmdCustomArgs() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomArgs,
                       (Cmd),
                       (),
                       (),
                       (staticKind, name, isAttached))
  static OrgSemKind const staticKind;
  hstd::Str name;
  bool isAttached = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomArgs; }
};

/// \brief Custom command with raw unparsed string value
struct CmdCustomRaw : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~CmdCustomRaw() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomRaw,
                       (Stmt),
                       (),
                       (),
                       (staticKind, name, isAttached, text))
  static OrgSemKind const staticKind;
  hstd::Str name;
  bool isAttached = false;
  hstd::Str text;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomRaw; }
};

/// \brief Custom line command with text paragraph value
struct CmdCustomText : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~CmdCustomText() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomText,
                       (Stmt),
                       (),
                       (),
                       (staticKind, name, isAttached, text))
  static OrgSemKind const staticKind;
  hstd::Str name;
  bool isAttached = false;
  org::sem::SemId<org::sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomText; }
};

struct CmdCall : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdCall() = default;
  BOOST_DESCRIBE_CLASS(CmdCall,
                       (Attached),
                       (),
                       (),
                       (staticKind,
                        name,
                        fileName,
                        insideHeaderAttrs,
                        callAttrs,
                        endHeaderAttrs,
                        result))
  static OrgSemKind const staticKind;
  /// \brief Code block call name
  hstd::Str name = "";
  /// \brief Which file code block should come from
  hstd::Opt<hstd::Str> fileName = std::nullopt;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup insideHeaderAttrs;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup callAttrs;
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup endHeaderAttrs;
  /// \brief Code evaluation results
  hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>> result = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCall; }
};

/// \brief Tblfm command type
struct CmdTblfm : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~CmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(CmdTblfm,
                       (Cmd),
                       (),
                       (),
                       (staticKind, expr))
  static OrgSemKind const staticKind;
  org::sem::Tblfm expr;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
};

struct HashTag : public org::sem::Inline {
  using Inline::Inline;
  virtual ~HashTag() = default;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind, text))
  static OrgSemKind const staticKind;
  org::sem::HashTagText text;
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct InlineFootnote : public org::sem::Inline {
  using Inline::Inline;
  virtual ~InlineFootnote() = default;
  BOOST_DESCRIBE_CLASS(InlineFootnote,
                       (Inline),
                       (),
                       (),
                       (staticKind, tag, definition))
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  hstd::Str tag = "";
  /// \brief Link to possibly resolved definition
  hstd::Opt<org::sem::SemId<org::sem::Org>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineFootnote; }
};

/// \brief Inline export
struct InlineExport : public org::sem::Inline {
  using Inline::Inline;
  virtual ~InlineExport() = default;
  BOOST_DESCRIBE_CLASS(InlineExport,
                       (Inline),
                       (),
                       (),
                       (staticKind, exporter, content))
  static OrgSemKind const staticKind;
  hstd::Str exporter = "";
  hstd::Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineExport; }
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public org::sem::Org {
  using Org::Org;
  virtual ~Time() = default;
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
    org::sem::Time::Repeat::Mode mode;
    /// \brief period
    org::sem::Time::Repeat::Period period;
    /// \brief count
    int count;
    Repeat() {  }
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static, (), (), (), (repeat, warn, time))
    hstd::Vec<org::sem::Time::Repeat> repeat = {};
    hstd::Opt<org::sem::Time::Repeat> warn = std::nullopt;
    hstd::UserTime time;
    Static() {  }
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic, (), (), (), (expr))
    org::sem::LispCode expr;
    Dynamic() {  }
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
  hstd::Opt<int> getYear() const;
  hstd::Opt<int> getMonth() const;
  hstd::Opt<int> getDay() const;
  hstd::Opt<int> getHour() const;
  hstd::Opt<int> getMinute() const;
  hstd::Opt<int> getSecond() const;
  hstd::UserTime getStaticTime() const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  org::sem::Time::Static const& getStatic() const { return hstd::variant_get<0>(time); }
  org::sem::Time::Static& getStatic() { return hstd::variant_get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::sem::Time::Dynamic const& getDynamic() const { return hstd::variant_get<1>(time); }
  org::sem::Time::Dynamic& getDynamic() { return hstd::variant_get<1>(time); }
  static org::sem::Time::TimeKind getTimeKind(org::sem::Time::TimeVariant const& __input) { return static_cast<org::sem::Time::TimeKind>(__input.index()); }
  org::sem::Time::TimeKind getTimeKind() const { return getTimeKind(time); }
  char const* sub_variant_get_name() const { return "time"; }
  org::sem::Time::TimeVariant const& sub_variant_get_data() const { return time; }
  org::sem::Time::TimeKind sub_variant_get_kind() const { return getTimeKind(); }
};

/// \brief Range of time delimited by two points
struct TimeRange : public org::sem::Org {
  using Org::Org;
  virtual ~TimeRange() = default;
  BOOST_DESCRIBE_CLASS(TimeRange,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        from,
                        to))
  static OrgSemKind const staticKind;
  /// \brief Starting time
  org::sem::SemId<org::sem::Time> from = sem::SemId<sem::Time>::Nil();
  /// \brief Finishing time
  org::sem::SemId<org::sem::Time> to = sem::SemId<sem::Time>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
  hstd::Opt<int64_t> getClockedTimeSeconds() const;
};

/// \brief Inline macro invocation
struct Macro : public org::sem::Org {
  using Org::Org;
  virtual ~Macro() = default;
  BOOST_DESCRIBE_CLASS(Macro,
                       (Org),
                       (),
                       (),
                       (staticKind, name, attrs))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  hstd::Str name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::sem::AttrGroup attrs;
  virtual OrgSemKind getKind() const { return OrgSemKind::Macro; }
};

/// \brief Text symbol or symbol command
struct Symbol : public org::sem::Org {
  using Org::Org;
  virtual ~Symbol() = default;
  /// \brief Symbol parameters
  struct Param {
    BOOST_DESCRIBE_CLASS(Param, (), (), (), (key, value))
    /// \brief Key -- for non-positional
    hstd::Opt<hstd::Str> key;
    /// \brief Uninterpreted value
    hstd::Str value;
  };

  BOOST_DESCRIBE_CLASS(Symbol,
                       (Org),
                       (),
                       (),
                       (staticKind, name, parameters, positional))
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  hstd::Str name;
  /// \brief Optional list of parameters
  hstd::Vec<org::sem::Symbol::Param> parameters;
  /// \brief Positional parameters
  hstd::Vec<org::sem::SemId<org::sem::Org>> positional;
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
};

/// \brief Escaped text
struct Escaped : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Escaped() = default;
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Escaped; }
};

/// \brief \n newline
struct Newline : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Newline() = default;
  BOOST_DESCRIBE_CLASS(Newline,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Newline; }
};

/// \brief ' "space",
struct Space : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Space() = default;
  BOOST_DESCRIBE_CLASS(Space,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Space; }
};

/// \brief word
struct Word : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Word() = default;
  BOOST_DESCRIBE_CLASS(Word,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Word; }
};

/// \brief `@mention`
struct AtMention : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~AtMention() = default;
  BOOST_DESCRIBE_CLASS(AtMention,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
};

struct RawText : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~RawText() = default;
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
};

struct Punctuation : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Punctuation() = default;
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
};

struct Placeholder : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~Placeholder() = default;
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
};

struct BigIdent : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~BigIdent() = default;
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
};

/// \brief `<<target>>`
struct TextTarget : public org::sem::Leaf {
  using Leaf::Leaf;
  virtual ~TextTarget() = default;
  BOOST_DESCRIBE_CLASS(TextTarget,
                       (Leaf),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextTarget; }
};

struct Markup : public org::sem::Org {
  using Org::Org;
  virtual ~Markup() = default;
  BOOST_DESCRIBE_CLASS(Markup, (Org), (), (), ())
};

struct Bold : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Bold() = default;
  BOOST_DESCRIBE_CLASS(Bold,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
};

struct Underline : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Underline() = default;
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
};

struct Monospace : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Monospace() = default;
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
};

struct MarkQuote : public org::sem::Markup {
  using Markup::Markup;
  virtual ~MarkQuote() = default;
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
};

struct Verbatim : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Verbatim() = default;
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
};

struct Italic : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Italic() = default;
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
};

struct Strike : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Strike() = default;
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
};

struct Par : public org::sem::Markup {
  using Markup::Markup;
  virtual ~Par() = default;
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
};

/// \brief `<<<target>>>`
struct RadioTarget : public org::sem::Org {
  using Org::Org;
  virtual ~RadioTarget() = default;
  BOOST_DESCRIBE_CLASS(RadioTarget,
                       (Org),
                       (),
                       (),
                       (staticKind, words))
  static OrgSemKind const staticKind;
  hstd::Vec<hstd::Str> words = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
};

/// \brief Latex code body
struct Latex : public org::sem::Org {
  using Org::Org;
  virtual ~Latex() = default;
  BOOST_DESCRIBE_CLASS(Latex,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Latex; }
};

struct Link : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~Link() = default;
  BOOST_DESCRIBE_CLASS(Link,
                       (Stmt),
                       (),
                       (),
                       (staticKind, description, target))
  static OrgSemKind const staticKind;
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> description = std::nullopt;
  org::sem::LinkTarget target;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
};

/// \brief Center nested content in export
struct BlockCenter : public org::sem::Block {
  using Block::Block;
  virtual ~BlockCenter() = default;
  BOOST_DESCRIBE_CLASS(BlockCenter,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCenter; }
};

/// \brief Quotation block
struct BlockQuote : public org::sem::Block {
  using Block::Block;
  virtual ~BlockQuote() = default;
  BOOST_DESCRIBE_CLASS(BlockQuote,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockQuote; }
};

/// \brief Comment block
struct BlockComment : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~BlockComment() = default;
  BOOST_DESCRIBE_CLASS(BlockComment,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockComment; }
};

/// \brief Verse quotation block
struct BlockVerse : public org::sem::Block {
  using Block::Block;
  virtual ~BlockVerse() = default;
  BOOST_DESCRIBE_CLASS(BlockVerse,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockVerse; }
};

struct BlockDynamicFallback : public org::sem::Block {
  using Block::Block;
  virtual ~BlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(BlockDynamicFallback,
                       (Block),
                       (),
                       (),
                       (staticKind, name))
  static OrgSemKind const staticKind;
  hstd::Str name = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockDynamicFallback; }
};

/// \brief Example block
struct BlockExample : public org::sem::Block {
  using Block::Block;
  virtual ~BlockExample() = default;
  BOOST_DESCRIBE_CLASS(BlockExample,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExample; }
};

/// \brief Direct export passthrough
struct BlockExport : public org::sem::Block {
  using Block::Block;
  virtual ~BlockExport() = default;
  BOOST_DESCRIBE_CLASS(BlockExport,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        exporter,
                        content))
  static OrgSemKind const staticKind;
  hstd::Str exporter = "";
  hstd::Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
  /// \brief Return value of the :placement attribute if present
  hstd::Opt<hstd::Str> getPlacement() const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct BlockAdmonition : public org::sem::Block {
  using Block::Block;
  virtual ~BlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(BlockAdmonition,
                       (Block),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockAdmonition; }
};

/// \brief Parsed results of code block evaluation
struct BlockCodeEvalResult : public org::sem::Block {
  using Block::Block;
  virtual ~BlockCodeEvalResult() = default;
  BOOST_DESCRIBE_CLASS(BlockCodeEvalResult,
                       (Block),
                       (),
                       (),
                       (staticKind, raw, node))
  static OrgSemKind const staticKind;
  hstd::Vec<org::sem::OrgCodeEvalOutput> raw;
  org::sem::SemId<org::sem::Org> node = sem::SemId<sem::Org>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCodeEvalResult; }
};

/// \brief Base class for all code blocks
struct BlockCode : public org::sem::Block {
  using Block::Block;
  virtual ~BlockCode() = default;
  BOOST_DESCRIBE_CLASS(BlockCode,
                       (Block),
                       (),
                       (),
                       (staticKind,
                        lang,
                        result,
                        lines,
                        switches))
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  hstd::Opt<hstd::Str> lang = std::nullopt;
  /// \brief Code evaluation results
  hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>> result = {};
  /// \brief Collected code lines
  hstd::Vec<org::sem::BlockCodeLine> lines = {};
  /// \brief Dash-based switches for code block execution
  org::sem::AttrGroup switches;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCode; }
  hstd::Opt<org::sem::AttrValue> getVariable(hstd::Str const& varname) const;
};

/// \brief Single subtree log entry
struct SubtreeLog : public org::sem::Org {
  using Org::Org;
  virtual ~SubtreeLog() = default;
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
  hstd::Opt<org::sem::SemId<org::sem::StmtList>> desc = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  void setDescription(org::sem::SemId<org::sem::StmtList> desc);
};

/// \brief Subtree
struct Subtree : public org::sem::Org {
  using Org::Org;
  virtual ~Subtree() = default;
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
  hstd::Opt<hstd::Str> treeId = std::nullopt;
  /// \brief Todo state of the tree
  hstd::Opt<hstd::Str> todo = std::nullopt;
  /// \brief Task completion state
  hstd::Opt<org::sem::SubtreeCompletion> completion = std::nullopt;
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> description = std::nullopt;
  /// \brief Trailing tags
  hstd::Vec<org::sem::SemId<org::sem::HashTag>> tags = {};
  /// \brief Main title
  org::sem::SemId<org::sem::Paragraph> title = sem::SemId<sem::Paragraph>::Nil();
  /// \brief Associated subtree log
  hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>> logbook = {};
  /// \brief Immediate properties
  hstd::Vec<org::sem::NamedProperty> properties = {};
  /// \brief When subtree was marked as closed
  hstd::Opt<org::sem::SemId<org::sem::Time>> closed = std::nullopt;
  /// \brief When is the deadline
  hstd::Opt<org::sem::SemId<org::sem::Time>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  hstd::Opt<org::sem::SemId<org::sem::Time>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  hstd::Opt<hstd::Str> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  hstd::Vec<org::sem::SubtreePeriod> getTimePeriods(hstd::IntSet<org::sem::SubtreePeriod::Kind> kinds) const;
  hstd::Vec<org::sem::NamedProperty> getProperties(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
  hstd::Opt<org::sem::NamedProperty> getProperty(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subkind = std::nullopt) const;
  /// \brief Remove all instances of the property with matching kind/subkind from the property list
  void removeProperty(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subkind = std::nullopt);
  /// \brief Create or override existing property value in the subtree property list
  void setProperty(org::sem::NamedProperty const& value);
  /// \brief Assign a raw string literal to a property.
  ///
  /// This function will not do the conversion or parsing of the assigned value, so if it is a 'created' or some other property with a typed value, it will still remain as string until the file is written and then parsed back from scratch.
  void setPropertyStrValue(hstd::Str const& value, hstd::Str const& kind, hstd::Opt<hstd::Str> const& subkind = std::nullopt);
  /// \brief Get subtree title as a flat string, without markup nodes, but with all left strings
  hstd::Str getCleanTitle() const;
  hstd::Opt<hstd::Str> getTodoKeyword() const;
};

/// \brief Table cell
struct Cell : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~Cell() = default;
  BOOST_DESCRIBE_CLASS(Cell,
                       (Cmd),
                       (),
                       (),
                       (staticKind, isBlock))
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Cell; }
};

/// \brief Table row
struct Row : public org::sem::Cmd {
  using Cmd::Cmd;
  virtual ~Row() = default;
  BOOST_DESCRIBE_CLASS(Row,
                       (Cmd),
                       (),
                       (),
                       (staticKind, cells, isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  hstd::Vec<org::sem::SemId<org::sem::Cell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
};

/// \brief Table
struct Table : public org::sem::Block {
  using Block::Block;
  virtual ~Table() = default;
  BOOST_DESCRIBE_CLASS(Table,
                       (Block),
                       (),
                       (),
                       (staticKind, rows, isBlock))
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  hstd::Vec<org::sem::SemId<org::sem::Row>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
};

/// \brief Top-level or inline paragraph
struct Paragraph : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~Paragraph() = default;
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  bool isFootnoteDefinition() const;
  hstd::Opt<hstd::Str> getFootnoteName() const;
  bool hasAdmonition() const;
  hstd::Vec<hstd::Str> getAdmonitions() const;
  hstd::Vec<org::sem::SemId<org::sem::BigIdent>> getAdmonitionNodes() const;
  bool hasTimestamp() const;
  hstd::Vec<hstd::UserTime> getTimestamps() const;
  hstd::Vec<org::sem::SemId<org::sem::Time>> getTimestampNodes() const;
  bool hasLeadHashtags() const;
  hstd::Vec<org::sem::SemId<org::sem::HashTag>> getLeadHashtags() const;
  /// \brief Return content of the paragraph, without prefix idents, hashtags, footnotes etc.
  hstd::Vec<org::sem::SemId<org::sem::Org>> getBody() const;
};

/// \brief Shortened colon example block
struct ColonExample : public org::sem::Org {
  using Org::Org;
  virtual ~ColonExample() = default;
  BOOST_DESCRIBE_CLASS(ColonExample,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::ColonExample; }
};

/// \brief Caption annotation for any subsequent node
struct CmdAttr : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdAttr() = default;
  BOOST_DESCRIBE_CLASS(CmdAttr,
                       (Attached),
                       (),
                       (),
                       (staticKind, target))
  static OrgSemKind const staticKind;
  hstd::Str target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
};

/// \brief Single line of passthrough code
struct CmdExport : public org::sem::Attached {
  using Attached::Attached;
  virtual ~CmdExport() = default;
  BOOST_DESCRIBE_CLASS(CmdExport,
                       (Attached),
                       (),
                       (),
                       (staticKind, exporter, content))
  static OrgSemKind const staticKind;
  hstd::Str exporter = "";
  hstd::Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdExport; }
};

/// \brief Inline, statement or block call
struct Call : public org::sem::Org {
  using Org::Org;
  virtual ~Call() = default;
  BOOST_DESCRIBE_CLASS(Call,
                       (Org),
                       (),
                       (),
                       (staticKind, name, attrs, isCommand))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  hstd::Str name;
  /// \brief Additional parameters aside from 'exporter'
  org::sem::AttrGroup attrs;
  bool isCommand = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
};

struct List : public org::sem::Stmt {
  using Stmt::Stmt;
  virtual ~List() = default;
  BOOST_DESCRIBE_CLASS(List,
                       (Stmt),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  hstd::Vec<org::sem::AttrValue> getListAttrs(hstd::Str const& key) const;
  ListFormattingMode getListFormattingMode() const;
  /// \brief List is marked as description if any list item has a header
  bool isDescriptionList() const;
  /// \brief List is marked as numbered if any list item has bullet text set
  bool isNumberedList() const;
};

struct ListItem : public org::sem::Org {
  using Org::Org;
  virtual ~ListItem() = default;
  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        checkbox,
                        header,
                        bullet))
  static OrgSemKind const staticKind;
  CheckboxState checkbox = CheckboxState::None;
  /// \brief Description list item header
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  hstd::Opt<hstd::Str> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool isDescriptionItem() const;
  /// \brief Return flat text for the description list header
  hstd::Opt<hstd::Str> getCleanHeader() const;
};

struct DocumentOptions : public org::sem::Org {
  using Org::Org;
  virtual ~DocumentOptions() = default;
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
                        columns,
                        todoKeywords,
                        doneKeywords))
  static OrgSemKind const staticKind;
  InitialSubtreeVisibility initialVisibility = InitialSubtreeVisibility::ShowEverything;
  hstd::Vec<org::sem::NamedProperty> properties = {};
  org::sem::DocumentExportConfig exportConfig;
  hstd::Opt<bool> fixedWidthSections = std::nullopt;
  hstd::Opt<bool> startupIndented = std::nullopt;
  hstd::Opt<hstd::Str> category = std::nullopt;
  hstd::Opt<hstd::Str> setupfile = std::nullopt;
  hstd::Opt<int> maxSubtreeLevelExport = std::nullopt;
  hstd::Opt<org::sem::ColumnView> columns = std::nullopt;
  hstd::Vec<org::sem::TodoKeyword> todoKeywords = {};
  hstd::Vec<org::sem::TodoKeyword> doneKeywords = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  hstd::Vec<org::sem::NamedProperty> getProperties(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
  hstd::Opt<org::sem::NamedProperty> getProperty(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
};

/// \brief Part of the document embedded in a larger file (e.g. in comments)
struct DocumentFragment : public org::sem::Org {
  using Org::Org;
  virtual ~DocumentFragment() = default;
  BOOST_DESCRIBE_CLASS(DocumentFragment,
                       (Org),
                       (),
                       (),
                       (staticKind, baseLine, baseCol))
  static OrgSemKind const staticKind;
  int baseLine;
  int baseCol;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentFragment; }
};

/// \brief https://fletcher.github.io/MultiMarkdown-6/syntax/critic.html
struct CriticMarkup : public org::sem::Org {
  using Org::Org;
  virtual ~CriticMarkup() = default;
  enum class Kind : short int { Deletion, Addition, Substitution, Highlighting, Comment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Deletion, Addition, Substitution, Highlighting, Comment)
  BOOST_DESCRIBE_CLASS(CriticMarkup,
                       (Org),
                       (),
                       (),
                       (staticKind, kind))
  static OrgSemKind const staticKind;
  org::sem::CriticMarkup::Kind kind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CriticMarkup; }
};

struct Document : public org::sem::Org {
  using Org::Org;
  virtual ~Document() = default;
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
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> title = std::nullopt;
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> author = std::nullopt;
  hstd::Opt<org::sem::SemId<org::sem::Paragraph>> creator = std::nullopt;
  hstd::Vec<org::sem::SemId<org::sem::HashTag>> filetags = {};
  hstd::Opt<org::sem::SemId<org::sem::RawText>> email = std::nullopt;
  hstd::Vec<hstd::Str> language = {};
  org::sem::SemId<org::sem::DocumentOptions> options = sem::SemId<sem::DocumentOptions>::Nil();
  hstd::Opt<hstd::Str> exportFileName = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  hstd::Vec<org::sem::NamedProperty> getProperties(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
  hstd::Opt<org::sem::NamedProperty> getProperty(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
};

struct FileTarget : public org::sem::Org {
  using Org::Org;
  virtual ~FileTarget() = default;
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
  hstd::Str path;
  hstd::Opt<int> line = std::nullopt;
  hstd::Opt<hstd::Str> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  hstd::Opt<hstd::Str> targetId = std::nullopt;
  hstd::Opt<hstd::Str> regexp = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
};

struct TextSeparator : public org::sem::Org {
  using Org::Org;
  virtual ~TextSeparator() = default;
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
};

struct DocumentGroup : public org::sem::Org {
  using Org::Org;
  virtual ~DocumentGroup() = default;
  BOOST_DESCRIBE_CLASS(DocumentGroup,
                       (Org),
                       (),
                       (),
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
};

struct File : public org::sem::Org {
  using Org::Org;
  virtual ~File() = default;
  struct Document {
    BOOST_DESCRIBE_CLASS(Document, (), (), (), ())
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment, (), (), (), ())
  };

  struct Source {
    BOOST_DESCRIBE_CLASS(Source, (), (), (), ())
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
  hstd::Str relPath = "";
  /// \brief Absolute resolved path to physical file
  hstd::Str absPath = "";
  org::sem::File::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::File; }
  bool isDocument() const { return getFileKind() == Kind::Document; }
  org::sem::File::Document const& getDocument() const { return hstd::variant_get<0>(data); }
  org::sem::File::Document& getDocument() { return hstd::variant_get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  org::sem::File::Attachment const& getAttachment() const { return hstd::variant_get<1>(data); }
  org::sem::File::Attachment& getAttachment() { return hstd::variant_get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  org::sem::File::Source const& getSource() const { return hstd::variant_get<2>(data); }
  org::sem::File::Source& getSource() { return hstd::variant_get<2>(data); }
  static org::sem::File::Kind getFileKind(org::sem::File::Data const& __input) { return static_cast<org::sem::File::Kind>(__input.index()); }
  org::sem::File::Kind getFileKind() const { return getFileKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::File::Data const& sub_variant_get_data() const { return data; }
  org::sem::File::Kind sub_variant_get_kind() const { return getFileKind(); }
};

struct Directory : public org::sem::Org {
  using Org::Org;
  virtual ~Directory() = default;
  BOOST_DESCRIBE_CLASS(Directory,
                       (Org),
                       (),
                       (),
                       (staticKind, relPath, absPath))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory, empty if this is the root directory
  hstd::Str relPath = "";
  /// \brief Absolute resolved path to physical directory
  hstd::Str absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Directory; }
};

struct Symlink : public org::sem::Org {
  using Org::Org;
  virtual ~Symlink() = default;
  BOOST_DESCRIBE_CLASS(Symlink,
                       (Org),
                       (),
                       (),
                       (staticKind, isDirectory, absPath))
  static OrgSemKind const staticKind;
  bool isDirectory;
  /// \brief Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.
  hstd::Str absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Symlink; }
};

struct CmdInclude : public org::sem::Org {
  using Org::Org;
  virtual ~CmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase, (), (), (), ())
    IncludeBase() {  }
  };

  struct Example : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Example, (IncludeBase), (), (), ())
    Example() {  }
  };

  struct Export : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Export, (IncludeBase), (), (), (language))
    /// \brief Source code language for export
    hstd::Str language;
    Export() {  }
  };

  /// \brief Second positional argument in the include command can have any arbitrary value -- default src/export/example have additional properties, but user can provide anything else there.
  struct Custom : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Custom, (IncludeBase), (), (), (blockName))
    /// \brief Block name not covered by the default values
    hstd::Str blockName;
    Custom() {  }
  };

  struct Src : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Src, (IncludeBase), (), (), (language))
    /// \brief Source code language for code block
    hstd::Str language;
    Src() {  }
  };

  struct OrgDocument : public org::sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(OrgDocument,
                         (IncludeBase),
                         (),
                         (),
                         (onlyContent, subtreePath, minLevel, customIdTarget))
    /// \brief omits any planning lines or property drawers
    hstd::Opt<bool> onlyContent = std::nullopt;
    /// \brief Include first subtree matching path with `file.org::* tree`
    hstd::Opt<org::sem::SubtreePath> subtreePath = std::nullopt;
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    hstd::Opt<int> minLevel = std::nullopt;
    /// \brief Include target subtree content with `file.org::#custom`
    hstd::Opt<hstd::Str> customIdTarget = std::nullopt;
    OrgDocument() {  }
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
  hstd::Str path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  hstd::Opt<int> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  hstd::Opt<int> lastLine = std::nullopt;
  org::sem::CmdInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdInclude; }
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  org::sem::CmdInclude::Example const& getExample() const { return hstd::variant_get<0>(data); }
  org::sem::CmdInclude::Example& getExample() { return hstd::variant_get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  org::sem::CmdInclude::Export const& getExport() const { return hstd::variant_get<1>(data); }
  org::sem::CmdInclude::Export& getExport() { return hstd::variant_get<1>(data); }
  bool isCustom() const { return getIncludeKind() == Kind::Custom; }
  org::sem::CmdInclude::Custom const& getCustom() const { return hstd::variant_get<2>(data); }
  org::sem::CmdInclude::Custom& getCustom() { return hstd::variant_get<2>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  org::sem::CmdInclude::Src const& getSrc() const { return hstd::variant_get<3>(data); }
  org::sem::CmdInclude::Src& getSrc() { return hstd::variant_get<3>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  org::sem::CmdInclude::OrgDocument const& getOrgDocument() const { return hstd::variant_get<4>(data); }
  org::sem::CmdInclude::OrgDocument& getOrgDocument() { return hstd::variant_get<4>(data); }
  static org::sem::CmdInclude::Kind getIncludeKind(org::sem::CmdInclude::Data const& __input) { return static_cast<org::sem::CmdInclude::Kind>(__input.index()); }
  org::sem::CmdInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::CmdInclude::Data const& sub_variant_get_data() const { return data; }
  org::sem::CmdInclude::Kind sub_variant_get_kind() const { return getIncludeKind(); }
};

}
/* clang-format on */