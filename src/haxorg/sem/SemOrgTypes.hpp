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
#include <functional>
#include <haxorg/sem/SemOrgBase.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>
namespace sem{
/// \brief Single key-value (or positional)
struct CmdArgument : public sem::Org {
  using Org::Org;
  virtual ~CmdArgument() = default;
  BOOST_DESCRIBE_CLASS(CmdArgument,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        key,
                        varname,
                        value,
                        (OrgSemKind() const) getKind,
                        (Opt<int>() const) getInt,
                        (Opt<bool>() const) getBool,
                        (Str() const) getString))
  static OrgSemKind const staticKind;
  /// \brief Key
  Opt<Str> key = std::nullopt;
  /// \brief When used in the `:var` assignment, this stores variable name
  Opt<Str> varname = std::nullopt;
  /// \brief Value
  Str value;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgument; }
  /// \brief Parse argument as integer value
  Opt<int> getInt() const;
  /// \brief Get argument as bool
  Opt<bool> getBool() const;
  /// \brief Get original string
  Str getString() const;
};

/// \brief Data type to wrap list of identical command arguments
struct CmdArgumentList : public sem::Org {
  using Org::Org;
  virtual ~CmdArgumentList() = default;
  BOOST_DESCRIBE_CLASS(CmdArgumentList,
                       (Org),
                       (),
                       (),
                       (staticKind, args, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief List of arguments
  Vec<sem::SemId<sem::CmdArgument>> args = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArgumentList; }
};

/// \brief Additional arguments for command blocks
struct CmdArguments : public sem::Org {
  using Org::Org;
  virtual ~CmdArguments() = default;
  BOOST_DESCRIBE_CLASS(CmdArguments,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        positional,
                        named,
                        (OrgSemKind() const) getKind,
                        (Opt<sem::SemId<sem::CmdArgumentList>>(Opt<Str> const&) const) getArguments))
  static OrgSemKind const staticKind;
  /// \brief Positional arguments with no keys
  sem::SemId<sem::CmdArgumentList> positional = sem::SemId<sem::CmdArgumentList>::Nil();
  /// \brief Stored key-value mapping
  UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>> named;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdArguments; }
  Opt<sem::SemId<sem::CmdArgumentList>> getArguments(Opt<Str> const& key = std::nullopt) const;
};

struct ErrorItem : public sem::Org {
  using Org::Org;
  virtual ~ErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ErrorItem,
                       (Org),
                       (),
                       (),
                       (staticKind, message, function, line, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str message;
  /// \brief Conversion function name where the error was created
  Opt<Str> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<int> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorItem; }
};

/// \brief Group of value conversion errors
struct ErrorGroup : public sem::Org {
  using Org::Org;
  virtual ~ErrorGroup() = default;
  BOOST_DESCRIBE_CLASS(ErrorGroup,
                       (Org),
                       (),
                       (),
                       (staticKind, diagnostics, function, line, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Vec<sem::SemId<sem::ErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  Opt<Str> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<Str> line = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ErrorGroup; }
};

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
                       (attached,
                        (Vec<sem::SemId<sem::Org>>(Opt<Str> const&) const) getAttached,
                        (Opt<sem::SemId<sem::CmdArgumentList>>(Opt<Str> const&) const) getArguments,
                        (Opt<sem::SemId<sem::CmdArgument>>(Str const&) const) getFirstArgument))
  Vec<sem::SemId<sem::Org>> attached;
  /// \brief Return attached nodes of a specific kinds or all attached (if kind is nullopt)
  Vec<sem::SemId<sem::Org>> getAttached(Opt<Str> const& kind = std::nullopt) const;
  /// \brief Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.
  virtual Opt<sem::SemId<sem::CmdArgumentList>> getArguments(Opt<Str> const& kind = std::nullopt) const;
  /// \brief Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities
  virtual Opt<sem::SemId<sem::CmdArgument>> getFirstArgument(Str const& kind) const;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Empty; }
};

/// \brief Base class for block or line commands
struct Cmd : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~Cmd() = default;
  BOOST_DESCRIBE_CLASS(Cmd,
                       (Stmt),
                       (),
                       (),
                       (parameters,
                        (Opt<sem::SemId<sem::CmdArgumentList>>(Opt<Str> const&) const) getArguments,
                        (Opt<sem::SemId<sem::CmdArgument>>(Str const&) const) getFirstArgument))
  /// \brief Additional parameters aside from 'exporter',
  Opt<sem::SemId<sem::CmdArguments>> parameters = std::nullopt;
  /// \brief Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.
  virtual Opt<sem::SemId<sem::CmdArgumentList>> getArguments(Opt<Str> const& key = std::nullopt) const override;
  /// \brief Override of the base statement argument get, prioritizing the explicit command parameters
  virtual Opt<sem::SemId<sem::CmdArgument>> getFirstArgument(Str const& kind) const override;
};

/// \brief Block command type
struct Block : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~Block() = default;
  BOOST_DESCRIBE_CLASS(Block, (Cmd), (), (), ())
};

/// \brief Line commands
struct LineCommand : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~LineCommand() = default;
  BOOST_DESCRIBE_CLASS(LineCommand, (Cmd), (), (), ())
};

/// \brief Line command that might get attached to some block element
struct Attached : public sem::LineCommand {
  using LineCommand::LineCommand;
  virtual ~Attached() = default;
  BOOST_DESCRIBE_CLASS(Attached, (LineCommand), (), (), ())
};

/// \brief Final node
struct Leaf : public sem::Org {
  using Org::Org;
  virtual ~Leaf() = default;
  BOOST_DESCRIBE_CLASS(Leaf, (Org), (), (), (text))
  /// \brief Final leaf value
  Str text = "";
};

/// \brief Caption annotation for any subsequent node
struct CmdCaption : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdCaption() = default;
  BOOST_DESCRIBE_CLASS(CmdCaption,
                       (Attached),
                       (),
                       (),
                       (staticKind, text, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Content description
  sem::SemId<sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
};

/// \brief Name identifier for the statement elements.
struct CmdName : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdName() = default;
  BOOST_DESCRIBE_CLASS(CmdName,
                       (Attached),
                       (),
                       (),
                       (staticKind, name, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str name;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdName; }
};

/// \brief Custom line command with list of parsed arguments
struct CmdCustomArgs : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~CmdCustomArgs() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomArgs,
                       (Cmd),
                       (),
                       (),
                       (staticKind, name, isAttached, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str name;
  bool isAttached = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomArgs; }
};

/// \brief Custom command with raw unparsed string value
struct CmdCustomRaw : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~CmdCustomRaw() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomRaw,
                       (Stmt),
                       (),
                       (),
                       (staticKind, name, isAttached, text, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str name;
  bool isAttached = false;
  Str text;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomRaw; }
};

/// \brief Custom line command with text paragraph value
struct CmdCustomText : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~CmdCustomText() = default;
  BOOST_DESCRIBE_CLASS(CmdCustomText,
                       (Stmt),
                       (),
                       (),
                       (staticKind, name, isAttached, text, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str name;
  bool isAttached = false;
  sem::SemId<sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCustomText; }
};

struct CmdResults : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdResults() = default;
  BOOST_DESCRIBE_CLASS(CmdResults,
                       (Attached),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdResults; }
};

/// \brief Tblfm command type
struct CmdTblfm : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~CmdTblfm() = default;
  BOOST_DESCRIBE_CLASS(CmdTblfm,
                       (Cmd),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
};

/// \brief Single or nested inline hash-tag
struct HashTag : public sem::Inline {
  using Inline::Inline;
  virtual ~HashTag() = default;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind,
                        head,
                        subtags,
                        (OrgSemKind() const) getKind,
                        (bool(Vec<Str> const&) const) prefixMatch))
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  Str head;
  /// \brief List of nested tags
  Vec<sem::SemId<sem::HashTag>> subtags = {};
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
                       (staticKind, tag, definition, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  Str tag = "";
  /// \brief Link to possibly resolved definition
  Opt<sem::SemId<sem::Org>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Footnote; }
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
                       (staticKind,
                        isActive,
                        time,
                        (OrgSemKind() const) getKind,
                        (sem::Time::Static const&() const) getStatic,
                        (sem::Time::Static&()) getStatic,
                        (sem::Time::Dynamic const&() const) getDynamic,
                        (sem::Time::Dynamic&()) getDynamic,
                        (sem::Time::TimeKind(sem::Time::TimeVariant const&)) getTimeKind,
                        (sem::Time::TimeKind() const) getTimeKind))
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  sem::Time::TimeVariant time;
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
                       (staticKind, from, to, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Starting time
  sem::SemId<sem::Time> from = sem::SemId<sem::Time>::Nil();
  /// \brief Finishing time
  sem::SemId<sem::Time> to = sem::SemId<sem::Time>::Nil();
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
                       (staticKind, name, parameters, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  Str name = "";
  /// \brief Additional parameters aside from 'exporter',
  sem::SemId<sem::CmdArguments> parameters = sem::SemId<sem::CmdArguments>::Nil();
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
                       (staticKind, name, parameters, positional, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  Str name;
  /// \brief Optional list of parameters
  Vec<sem::Symbol::Param> parameters;
  /// \brief Positional parameters
  Vec<sem::SemId<sem::Org>> positional;
  virtual OrgSemKind getKind() const { return OrgSemKind::Symbol; }
};

/// \brief Escaped text
struct Escaped : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Escaped() = default;
  BOOST_DESCRIBE_CLASS(Escaped,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::AtMention; }
};

struct RawText : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~RawText() = default;
  BOOST_DESCRIBE_CLASS(RawText,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RawText; }
};

struct Punctuation : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Punctuation() = default;
  BOOST_DESCRIBE_CLASS(Punctuation,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Punctuation; }
};

struct Placeholder : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~Placeholder() = default;
  BOOST_DESCRIBE_CLASS(Placeholder,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Placeholder; }
};

struct BigIdent : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~BigIdent() = default;
  BOOST_DESCRIBE_CLASS(BigIdent,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
};

/// \brief ~<<<target>>>~
struct RadioTarget : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~RadioTarget() = default;
  BOOST_DESCRIBE_CLASS(RadioTarget,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
};

/// \brief ~<<target>>~
struct TextTarget : public sem::Leaf {
  using Leaf::Leaf;
  virtual ~TextTarget() = default;
  BOOST_DESCRIBE_CLASS(TextTarget,
                       (Leaf),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextTarget; }
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Bold; }
};

struct Underline : public sem::Markup {
  using Markup::Markup;
  virtual ~Underline() = default;
  BOOST_DESCRIBE_CLASS(Underline,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Underline; }
};

struct Monospace : public sem::Markup {
  using Markup::Markup;
  virtual ~Monospace() = default;
  BOOST_DESCRIBE_CLASS(Monospace,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Monospace; }
};

struct MarkQuote : public sem::Markup {
  using Markup::Markup;
  virtual ~MarkQuote() = default;
  BOOST_DESCRIBE_CLASS(MarkQuote,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::MarkQuote; }
};

struct Verbatim : public sem::Markup {
  using Markup::Markup;
  virtual ~Verbatim() = default;
  BOOST_DESCRIBE_CLASS(Verbatim,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Verbatim; }
};

struct Italic : public sem::Markup {
  using Markup::Markup;
  virtual ~Italic() = default;
  BOOST_DESCRIBE_CLASS(Italic,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Italic; }
};

struct Strike : public sem::Markup {
  using Markup::Markup;
  virtual ~Strike() = default;
  BOOST_DESCRIBE_CLASS(Strike,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Strike; }
};

struct Par : public sem::Markup {
  using Markup::Markup;
  virtual ~Par() = default;
  BOOST_DESCRIBE_CLASS(Par,
                       (Markup),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
};

/// \brief Latex code body
struct Latex : public sem::Org {
  using Org::Org;
  virtual ~Latex() = default;
  BOOST_DESCRIBE_CLASS(Latex,
                       (Org),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Latex; }
};

struct Link : public sem::Stmt {
  using Stmt::Stmt;
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

  struct UserProtocol {
    BOOST_DESCRIBE_CLASS(UserProtocol, (), (), (), (protocol, target))
    Str protocol;
    Str target;
  };

  struct Internal {
    BOOST_DESCRIBE_CLASS(Internal, (), (), (), (target))
    Str target;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote, (), (), (), (target))
    Str target;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File, (), (), (), (file))
    Str file;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment, (), (), (), (file))
    Str file;
  };

  using Data = std::variant<sem::Link::Raw, sem::Link::Id, sem::Link::Person, sem::Link::UserProtocol, sem::Link::Internal, sem::Link::Footnote, sem::Link::File, sem::Link::Attachment>;
  enum class Kind : short int { Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment)
  using variant_enum_type = sem::Link::Kind;
  using variant_data_type = sem::Link::Data;
  BOOST_DESCRIBE_CLASS(Link,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        description,
                        data,
                        (OrgSemKind() const) getKind,
                        (sem::Link::Raw const&() const) getRaw,
                        (sem::Link::Raw&()) getRaw,
                        (sem::Link::Id const&() const) getId,
                        (sem::Link::Id&()) getId,
                        (sem::Link::Person const&() const) getPerson,
                        (sem::Link::Person&()) getPerson,
                        (sem::Link::UserProtocol const&() const) getUserProtocol,
                        (sem::Link::UserProtocol&()) getUserProtocol,
                        (sem::Link::Internal const&() const) getInternal,
                        (sem::Link::Internal&()) getInternal,
                        (sem::Link::Footnote const&() const) getFootnote,
                        (sem::Link::Footnote&()) getFootnote,
                        (sem::Link::File const&() const) getFile,
                        (sem::Link::File&()) getFile,
                        (sem::Link::Attachment const&() const) getAttachment,
                        (sem::Link::Attachment&()) getAttachment,
                        (sem::Link::Kind(sem::Link::Data const&)) getLinkKind,
                        (sem::Link::Kind() const) getLinkKind))
  static OrgSemKind const staticKind;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  sem::Link::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
  sem::Link::Raw const& getRaw() const { return std::get<0>(data); }
  sem::Link::Raw& getRaw() { return std::get<0>(data); }
  sem::Link::Id const& getId() const { return std::get<1>(data); }
  sem::Link::Id& getId() { return std::get<1>(data); }
  sem::Link::Person const& getPerson() const { return std::get<2>(data); }
  sem::Link::Person& getPerson() { return std::get<2>(data); }
  sem::Link::UserProtocol const& getUserProtocol() const { return std::get<3>(data); }
  sem::Link::UserProtocol& getUserProtocol() { return std::get<3>(data); }
  sem::Link::Internal const& getInternal() const { return std::get<4>(data); }
  sem::Link::Internal& getInternal() { return std::get<4>(data); }
  sem::Link::Footnote const& getFootnote() const { return std::get<5>(data); }
  sem::Link::Footnote& getFootnote() { return std::get<5>(data); }
  sem::Link::File const& getFile() const { return std::get<6>(data); }
  sem::Link::File& getFile() { return std::get<6>(data); }
  sem::Link::Attachment const& getAttachment() const { return std::get<7>(data); }
  sem::Link::Attachment& getAttachment() { return std::get<7>(data); }
  static sem::Link::Kind getLinkKind(sem::Link::Data const& __input) { return static_cast<sem::Link::Kind>(__input.index()); }
  sem::Link::Kind getLinkKind() const { return getLinkKind(data); }
};

/// \brief Center nested content in export
struct BlockCenter : public sem::Block {
  using Block::Block;
  virtual ~BlockCenter() = default;
  BOOST_DESCRIBE_CLASS(BlockCenter,
                       (Block),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockCenter; }
};

/// \brief Quotation block
struct BlockQuote : public sem::Block {
  using Block::Block;
  virtual ~BlockQuote() = default;
  BOOST_DESCRIBE_CLASS(BlockQuote,
                       (Block),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockQuote; }
};

/// \brief Comment block
struct BlockComment : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~BlockComment() = default;
  BOOST_DESCRIBE_CLASS(BlockComment,
                       (Stmt),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockComment; }
};

/// \brief Verse quotation block
struct BlockVerse : public sem::Block {
  using Block::Block;
  virtual ~BlockVerse() = default;
  BOOST_DESCRIBE_CLASS(BlockVerse,
                       (Block),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockVerse; }
};

/// \brief Example block
struct BlockExample : public sem::Block {
  using Block::Block;
  virtual ~BlockExample() = default;
  BOOST_DESCRIBE_CLASS(BlockExample,
                       (Block),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExample; }
};

/// \brief Direct export passthrough
struct BlockExport : public sem::Block {
  using Block::Block;
  virtual ~BlockExport() = default;
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
  BOOST_DESCRIBE_CLASS(BlockExport,
                       (Block),
                       (),
                       (),
                       (staticKind, format, exporter, placement, content, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Export block type
  sem::BlockExport::Format format = sem::BlockExport::Format::Inline;
  /// \brief Exporter backend name
  Str exporter;
  /// \brief Customized position of the text in the final exporting document.
  Opt<Str> placement = std::nullopt;
  /// \brief Raw exporter content string
  Str content;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct BlockAdmonition : public sem::Block {
  using Block::Block;
  virtual ~BlockAdmonition() = default;
  BOOST_DESCRIBE_CLASS(BlockAdmonition,
                       (Block),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockAdmonition; }
};

/// \brief Base class for all code blocks
struct BlockCode : public sem::Block {
  using Block::Block;
  virtual ~BlockCode() = default;
  struct Line {
    struct Part {
      struct Raw {
        BOOST_DESCRIBE_CLASS(Raw, (), (), (), (code))
        Str code;
      };

      struct Callout {
        BOOST_DESCRIBE_CLASS(Callout, (), (), (), (name))
        Str name;
      };

      struct Tangle {
        BOOST_DESCRIBE_CLASS(Tangle, (), (), (), (target))
        Str target;
      };

      using Data = std::variant<sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Tangle>;
      enum class Kind : short int { Raw, Callout, Tangle, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
      using variant_enum_type = sem::BlockCode::Line::Part::Kind;
      using variant_data_type = sem::BlockCode::Line::Part::Data;
      BOOST_DESCRIBE_CLASS(Part,
                           (),
                           (),
                           (),
                           (data,
                            (sem::BlockCode::Line::Part::Raw const&() const) getRaw,
                            (sem::BlockCode::Line::Part::Raw&()) getRaw,
                            (sem::BlockCode::Line::Part::Callout const&() const) getCallout,
                            (sem::BlockCode::Line::Part::Callout&()) getCallout,
                            (sem::BlockCode::Line::Part::Tangle const&() const) getTangle,
                            (sem::BlockCode::Line::Part::Tangle&()) getTangle,
                            (sem::BlockCode::Line::Part::Kind(sem::BlockCode::Line::Part::Data const&)) getKind,
                            (sem::BlockCode::Line::Part::Kind() const) getKind))
      sem::BlockCode::Line::Part::Data data;
      sem::BlockCode::Line::Part::Raw const& getRaw() const { return std::get<0>(data); }
      sem::BlockCode::Line::Part::Raw& getRaw() { return std::get<0>(data); }
      sem::BlockCode::Line::Part::Callout const& getCallout() const { return std::get<1>(data); }
      sem::BlockCode::Line::Part::Callout& getCallout() { return std::get<1>(data); }
      sem::BlockCode::Line::Part::Tangle const& getTangle() const { return std::get<2>(data); }
      sem::BlockCode::Line::Part::Tangle& getTangle() { return std::get<2>(data); }
      static sem::BlockCode::Line::Part::Kind getKind(sem::BlockCode::Line::Part::Data const& __input) { return static_cast<sem::BlockCode::Line::Part::Kind>(__input.index()); }
      sem::BlockCode::Line::Part::Kind getKind() const { return getKind(data); }
    };

    BOOST_DESCRIBE_CLASS(Line, (), (), (), (parts))
    /// \brief parts of the single line
    Vec<sem::BlockCode::Line::Part> parts = {};
  };

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

    using Data = std::variant<sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::Dedent>;
    enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
    using variant_enum_type = sem::BlockCode::Switch::Kind;
    using variant_data_type = sem::BlockCode::Switch::Data;
    BOOST_DESCRIBE_CLASS(Switch,
                         (),
                         (),
                         (),
                         (data,
                          (sem::BlockCode::Switch::LineStart const&() const) getLineStart,
                          (sem::BlockCode::Switch::LineStart&()) getLineStart,
                          (sem::BlockCode::Switch::CalloutFormat const&() const) getCalloutFormat,
                          (sem::BlockCode::Switch::CalloutFormat&()) getCalloutFormat,
                          (sem::BlockCode::Switch::RemoveCallout const&() const) getRemoveCallout,
                          (sem::BlockCode::Switch::RemoveCallout&()) getRemoveCallout,
                          (sem::BlockCode::Switch::EmphasizeLine const&() const) getEmphasizeLine,
                          (sem::BlockCode::Switch::EmphasizeLine&()) getEmphasizeLine,
                          (sem::BlockCode::Switch::Dedent const&() const) getDedent,
                          (sem::BlockCode::Switch::Dedent&()) getDedent,
                          (sem::BlockCode::Switch::Kind(sem::BlockCode::Switch::Data const&)) getKind,
                          (sem::BlockCode::Switch::Kind() const) getKind))
    sem::BlockCode::Switch::Data data;
    sem::BlockCode::Switch::LineStart const& getLineStart() const { return std::get<0>(data); }
    sem::BlockCode::Switch::LineStart& getLineStart() { return std::get<0>(data); }
    sem::BlockCode::Switch::CalloutFormat const& getCalloutFormat() const { return std::get<1>(data); }
    sem::BlockCode::Switch::CalloutFormat& getCalloutFormat() { return std::get<1>(data); }
    sem::BlockCode::Switch::RemoveCallout const& getRemoveCallout() const { return std::get<2>(data); }
    sem::BlockCode::Switch::RemoveCallout& getRemoveCallout() { return std::get<2>(data); }
    sem::BlockCode::Switch::EmphasizeLine const& getEmphasizeLine() const { return std::get<3>(data); }
    sem::BlockCode::Switch::EmphasizeLine& getEmphasizeLine() { return std::get<3>(data); }
    sem::BlockCode::Switch::Dedent const& getDedent() const { return std::get<4>(data); }
    sem::BlockCode::Switch::Dedent& getDedent() { return std::get<4>(data); }
    static sem::BlockCode::Switch::Kind getKind(sem::BlockCode::Switch::Data const& __input) { return static_cast<sem::BlockCode::Switch::Kind>(__input.index()); }
    sem::BlockCode::Switch::Kind getKind() const { return getKind(data); }
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
      BOOST_DESCRIBE_CLASS(None, (), (), (), ())
    };

    /// \brief Source code block evaluated to an org-mode node element
    struct OrgValue {
      BOOST_DESCRIBE_CLASS(OrgValue, (), (), (), (value))
      /// \brief Parsed value of the evaluation result
      sem::SemId<sem::Org> value = sem::SemId<sem::Org>::Nil();
    };

    /// \brief Output evaluation results to a file
    struct File {
      BOOST_DESCRIBE_CLASS(File, (), (), (), (path))
      Str path;
    };

    /// \brief Evaluation output is a raw text
    struct Raw {
      BOOST_DESCRIBE_CLASS(Raw, (), (), (), (text))
      Str text;
    };

    using Data = std::variant<sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::Raw>;
    enum class Kind : short int { None, OrgValue, File, Raw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, None, OrgValue, File, Raw)
    using variant_enum_type = sem::BlockCode::EvalResult::Kind;
    using variant_data_type = sem::BlockCode::EvalResult::Data;
    BOOST_DESCRIBE_CLASS(EvalResult,
                         (),
                         (),
                         (),
                         (data,
                          (sem::BlockCode::EvalResult::None const&() const) getNone,
                          (sem::BlockCode::EvalResult::None&()) getNone,
                          (sem::BlockCode::EvalResult::OrgValue const&() const) getOrgValue,
                          (sem::BlockCode::EvalResult::OrgValue&()) getOrgValue,
                          (sem::BlockCode::EvalResult::File const&() const) getFile,
                          (sem::BlockCode::EvalResult::File&()) getFile,
                          (sem::BlockCode::EvalResult::Raw const&() const) getRaw,
                          (sem::BlockCode::EvalResult::Raw&()) getRaw,
                          (sem::BlockCode::EvalResult::Kind(sem::BlockCode::EvalResult::Data const&)) getKind,
                          (sem::BlockCode::EvalResult::Kind() const) getKind))
    sem::BlockCode::EvalResult::Data data;
    sem::BlockCode::EvalResult::None const& getNone() const { return std::get<0>(data); }
    sem::BlockCode::EvalResult::None& getNone() { return std::get<0>(data); }
    sem::BlockCode::EvalResult::OrgValue const& getOrgValue() const { return std::get<1>(data); }
    sem::BlockCode::EvalResult::OrgValue& getOrgValue() { return std::get<1>(data); }
    sem::BlockCode::EvalResult::File const& getFile() const { return std::get<2>(data); }
    sem::BlockCode::EvalResult::File& getFile() { return std::get<2>(data); }
    sem::BlockCode::EvalResult::Raw const& getRaw() const { return std::get<3>(data); }
    sem::BlockCode::EvalResult::Raw& getRaw() { return std::get<3>(data); }
    static sem::BlockCode::EvalResult::Kind getKind(sem::BlockCode::EvalResult::Data const& __input) { return static_cast<sem::BlockCode::EvalResult::Kind>(__input.index()); }
    sem::BlockCode::EvalResult::Kind getKind() const { return getKind(data); }
  };

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
                        tangle,
                        (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<Str> lang = std::nullopt;
  /// \brief Switch options for block
  Vec<sem::BlockCode::Switch> switches = {};
  /// \brief What to export
  sem::BlockCode::Exports exports = sem::BlockCode::Exports::Both;
  /// \brief Code evaluation results
  Opt<sem::BlockCode::EvalResult> result = std::nullopt;
  /// \brief Collected code lines
  Vec<sem::BlockCode::Line> lines = {};
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
    Opt<sem::SemId<sem::StmtList>> desc = std::nullopt;
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
    Priority() {}
    BOOST_DESCRIBE_CLASS(Priority,
                         (DescribedLog),
                         (),
                         (),
                         (oldPriority, newPriority, on, action))
    /// \brief Previous priority for change and removal
    Opt<std::string> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<std::string> newPriority = std::nullopt;
    /// \brief When priority was changed
    sem::SemId<sem::Time> on = sem::SemId<sem::Time>::Nil();
    /// \brief Which action taken
    sem::SubtreeLog::Priority::Action action;
  };

  /// \brief Timestamped note
  struct Note : public sem::SubtreeLog::DescribedLog {
    Note() {}
    BOOST_DESCRIBE_CLASS(Note, (DescribedLog), (), (), (on))
    /// \brief Where log was taken
    sem::SemId<sem::Time> on = sem::SemId<sem::Time>::Nil();
  };

  /// \brief Refiling action
  struct Refile : public sem::SubtreeLog::DescribedLog {
    Refile() {}
    BOOST_DESCRIBE_CLASS(Refile, (DescribedLog), (), (), (on, from))
    /// \brief When the refiling happened
    sem::SemId<sem::Time> on = sem::SemId<sem::Time>::Nil();
    /// \brief Link to the original subtree
    sem::SemId<sem::Link> from = sem::SemId<sem::Link>::Nil();
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public sem::SubtreeLog::DescribedLog {
    Clock() {}
    BOOST_DESCRIBE_CLASS(Clock, (DescribedLog), (), (), (from, to))
    /// \brief Clock start time
    sem::SemId<sem::Time> from = sem::SemId<sem::Time>::Nil();
    /// \brief Optional end of the clock
    Opt<sem::SemId<sem::Time>> to = std::nullopt;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public sem::SubtreeLog::DescribedLog {
    State() {}
    BOOST_DESCRIBE_CLASS(State, (DescribedLog), (), (), (from, to, on))
    Str from;
    Str to;
    sem::SemId<sem::Time> on = sem::SemId<sem::Time>::Nil();
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public sem::SubtreeLog::DescribedLog {
    Tag() {}
    BOOST_DESCRIBE_CLASS(Tag, (DescribedLog), (), (), (on, tag, added))
    /// \brief When the log was assigned
    sem::SemId<sem::Time> on = sem::SemId<sem::Time>::Nil();
    /// \brief Tag in question
    sem::SemId<sem::HashTag> tag = sem::SemId<sem::HashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown : public sem::SubtreeLog::DescribedLog {
    Unknown() {}
    BOOST_DESCRIBE_CLASS(Unknown, (DescribedLog), (), (), ())
  };

  using LogEntry = std::variant<sem::SubtreeLog::Priority, sem::SubtreeLog::Note, sem::SubtreeLog::Refile, sem::SubtreeLog::Clock, sem::SubtreeLog::State, sem::SubtreeLog::Tag, sem::SubtreeLog::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Tag, Unknown)
  using variant_enum_type = sem::SubtreeLog::Kind;
  using variant_data_type = sem::SubtreeLog::LogEntry;
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        log,
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
                        (sem::SubtreeLog::Unknown const&() const) getUnknown,
                        (sem::SubtreeLog::Unknown&()) getUnknown,
                        (sem::SubtreeLog::Kind(sem::SubtreeLog::LogEntry const&)) getLogKind,
                        (sem::SubtreeLog::Kind() const) getLogKind))
  static OrgSemKind const staticKind;
  sem::SubtreeLog::LogEntry log = sem::SubtreeLog::Note{};
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
  sem::SubtreeLog::Unknown const& getUnknown() const { return std::get<6>(log); }
  sem::SubtreeLog::Unknown& getUnknown() { return std::get<6>(log); }
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
    BOOST_DESCRIBE_CLASS(Period, (), (), (), (kind, from, to))
    /// \brief Time period kind -- not associated with point/range distinction
    sem::Subtree::Period::Kind kind;
    /// \brief Clock start time
    sem::SemId<sem::Time> from = sem::SemId<sem::Time>::Nil();
    /// \brief Optional end of the clock
    Opt<sem::SemId<sem::Time>> to = std::nullopt;
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
      sem::SemId<sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
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
      sem::SemId<sem::Time> time = sem::SemId<sem::Time>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomArgs {
      CustomArgs() {}
      BOOST_DESCRIBE_CLASS(CustomArgs, (), (), (), (name, sub, parameters))
      /// \brief Original name of the property
      Str name = "";
      /// \brief Property target specialization
      Opt<Str> sub = std::nullopt;
      /// \brief Property parameters
      sem::SemId<sem::CmdArguments> parameters = sem::SemId<sem::CmdArguments>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomRaw {
      CustomRaw() {}
      BOOST_DESCRIBE_CLASS(CustomRaw, (), (), (), (name, value))
      /// \brief Original name of the property
      Str name = "";
      /// \brief Property value
      Str value = "";
    };

    using Data = std::variant<sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Trigger, sem::Subtree::Property::Origin, sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::Ordered, sem::Subtree::Property::Effort, sem::Subtree::Property::Visibility, sem::Subtree::Property::ExportOptions, sem::Subtree::Property::Blocker, sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Created, sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomRaw>;
    enum class Kind : short int { Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw)
    using variant_enum_type = sem::Subtree::Property::Kind;
    using variant_data_type = sem::Subtree::Property::Data;
    Property(CR<Data> data) : data(data) {}
    BOOST_DESCRIBE_CLASS(Property,
                         (),
                         (),
                         (),
                         (mainSetRule,
                          subSetRule,
                          inheritanceMode,
                          data,
                          (bool(Str const&, Opt<Str> const&) const) isMatching,
                          (Str() const) getName,
                          (Opt<Str>() const) getSubKind,
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
                          (sem::Subtree::Property::CustomArgs const&() const) getCustomArgs,
                          (sem::Subtree::Property::CustomArgs&()) getCustomArgs,
                          (sem::Subtree::Property::CustomRaw const&() const) getCustomRaw,
                          (sem::Subtree::Property::CustomRaw&()) getCustomRaw,
                          (sem::Subtree::Property::Kind(sem::Subtree::Property::Data const&)) getKind,
                          (sem::Subtree::Property::Kind() const) getKind))
    sem::Subtree::Property::SetMode mainSetRule = sem::Subtree::Property::SetMode::Override;
    sem::Subtree::Property::SetMode subSetRule = sem::Subtree::Property::SetMode::Override;
    sem::Subtree::Property::InheritanceMode inheritanceMode = sem::Subtree::Property::InheritanceMode::ThisAndSub;
    sem::Subtree::Property::Data data;
    /// \brief Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.
    bool isMatching(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
    /// \brief Get non-normalized name of the property (for built-in and user)
    Str getName() const;
    /// \brief Get non-normalized sub-kind for the property.
    Opt<Str> getSubKind() const;
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
    sem::Subtree::Property::CustomArgs const& getCustomArgs() const { return std::get<14>(data); }
    sem::Subtree::Property::CustomArgs& getCustomArgs() { return std::get<14>(data); }
    sem::Subtree::Property::CustomRaw const& getCustomRaw() const { return std::get<15>(data); }
    sem::Subtree::Property::CustomRaw& getCustomRaw() { return std::get<15>(data); }
    static sem::Subtree::Property::Kind getKind(sem::Subtree::Property::Data const& __input) { return static_cast<sem::Subtree::Property::Kind>(__input.index()); }
    sem::Subtree::Property::Kind getKind() const { return getKind(data); }
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
                        isComment,
                        isArchived,
                        priority,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Period>(IntSet<sem::Subtree::Period::Kind>) const) getTimePeriods,
                        (Vec<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperty,
                        (void(Str const&, Opt<Str> const&)) removeProperty,
                        (void(sem::Subtree::Property const&)) setProperty,
                        (void(Str const&, Str const&, Opt<Str> const&)) setPropertyStrValue))
  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  Opt<Str> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<Str> todo = std::nullopt;
  /// \brief Task completion state
  Opt<sem::SemId<sem::SubtreeCompletion>> completion = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  /// \brief Trailing tags
  Vec<sem::SemId<sem::HashTag>> tags = {};
  /// \brief Main title
  sem::SemId<sem::Paragraph> title = sem::SemId<sem::Paragraph>::Nil();
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
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  Opt<Str> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  Vec<sem::Subtree::Period> getTimePeriods(IntSet<sem::Subtree::Period::Kind> kinds) const;
  Vec<sem::Subtree::Property> getProperties(Str const& kind, Opt<Str> const& subkind = std::nullopt) const;
  Opt<sem::Subtree::Property> getProperty(Str const& kind, Opt<Str> const& subkind = std::nullopt) const;
  /// \brief Remove all instances of the property with matching kind/subkind from the property list
  void removeProperty(Str const& kind, Opt<Str> const& subkind = std::nullopt);
  /// \brief Create or override existing property value in the subtree property list
  void setProperty(sem::Subtree::Property const& value);
  /// \brief Assign a raw string literal to a property.
  ///
  /// This function will not do the conversion or parsing of the assigned value, so if it is a 'created' or some other property with a typed value, it will still remain as string until the file is written and then parsed back from scratch.
  void setPropertyStrValue(Str const& value, Str const& kind, Opt<Str> const& subkind = std::nullopt);
};

/// \brief Completion status of the subtree list element
struct SubtreeCompletion : public sem::Inline {
  using Inline::Inline;
  virtual ~SubtreeCompletion() = default;
  BOOST_DESCRIBE_CLASS(SubtreeCompletion,
                       (Inline),
                       (),
                       (),
                       (staticKind, done, full, isPercent, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeCompletion; }
};

/// \brief Table cell
struct Cell : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~Cell() = default;
  BOOST_DESCRIBE_CLASS(Cell,
                       (Cmd),
                       (),
                       (),
                       (staticKind, isBlock, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Cell; }
};

/// \brief Table row
struct Row : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~Row() = default;
  BOOST_DESCRIBE_CLASS(Row,
                       (Cmd),
                       (),
                       (),
                       (staticKind, cells, isBlock, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  Vec<sem::SemId<sem::Cell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Row; }
};

/// \brief Table
struct Table : public sem::Block {
  using Block::Block;
  virtual ~Table() = default;
  BOOST_DESCRIBE_CLASS(Table,
                       (Block),
                       (),
                       (),
                       (staticKind, rows, isBlock, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  Vec<sem::SemId<sem::Row>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Table; }
};

/// \brief Top-level or inline paragraph
struct Paragraph : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~Paragraph() = default;
  BOOST_DESCRIBE_CLASS(Paragraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
};

/// \brief Top-level or inline paragraph with prefix annotation
struct AnnotatedParagraph : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~AnnotatedParagraph() = default;
  struct None {
    BOOST_DESCRIBE_CLASS(None, (), (), (), ())
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote, (), (), (), (name))
    Str name;
  };

  struct Admonition {
    BOOST_DESCRIBE_CLASS(Admonition, (), (), (), (name))
    /// \brief Prefix admonition for the paragraph
    sem::SemId<sem::BigIdent> name = sem::SemId<sem::BigIdent>::Nil();
  };

  struct Timestamp {
    BOOST_DESCRIBE_CLASS(Timestamp, (), (), (), (time))
    /// \brief Leading timestamp for the paragraph
    sem::SemId<sem::Time> time = sem::SemId<sem::Time>::Nil();
  };

  using Data = std::variant<sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Timestamp>;
  enum class AnnotationKind : short int { None, Footnote, Admonition, Timestamp, };
  BOOST_DESCRIBE_NESTED_ENUM(AnnotationKind, None, Footnote, Admonition, Timestamp)
  using variant_enum_type = sem::AnnotatedParagraph::AnnotationKind;
  using variant_data_type = sem::AnnotatedParagraph::Data;
  BOOST_DESCRIBE_CLASS(AnnotatedParagraph,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        data,
                        (OrgSemKind() const) getKind,
                        (sem::AnnotatedParagraph::None const&() const) getNone,
                        (sem::AnnotatedParagraph::None&()) getNone,
                        (sem::AnnotatedParagraph::Footnote const&() const) getFootnote,
                        (sem::AnnotatedParagraph::Footnote&()) getFootnote,
                        (sem::AnnotatedParagraph::Admonition const&() const) getAdmonition,
                        (sem::AnnotatedParagraph::Admonition&()) getAdmonition,
                        (sem::AnnotatedParagraph::Timestamp const&() const) getTimestamp,
                        (sem::AnnotatedParagraph::Timestamp&()) getTimestamp,
                        (sem::AnnotatedParagraph::AnnotationKind(sem::AnnotatedParagraph::Data const&)) getAnnotationKind,
                        (sem::AnnotatedParagraph::AnnotationKind() const) getAnnotationKind))
  static OrgSemKind const staticKind;
  sem::AnnotatedParagraph::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::AnnotatedParagraph; }
  sem::AnnotatedParagraph::None const& getNone() const { return std::get<0>(data); }
  sem::AnnotatedParagraph::None& getNone() { return std::get<0>(data); }
  sem::AnnotatedParagraph::Footnote const& getFootnote() const { return std::get<1>(data); }
  sem::AnnotatedParagraph::Footnote& getFootnote() { return std::get<1>(data); }
  sem::AnnotatedParagraph::Admonition const& getAdmonition() const { return std::get<2>(data); }
  sem::AnnotatedParagraph::Admonition& getAdmonition() { return std::get<2>(data); }
  sem::AnnotatedParagraph::Timestamp const& getTimestamp() const { return std::get<3>(data); }
  sem::AnnotatedParagraph::Timestamp& getTimestamp() { return std::get<3>(data); }
  static sem::AnnotatedParagraph::AnnotationKind getAnnotationKind(sem::AnnotatedParagraph::Data const& __input) { return static_cast<sem::AnnotatedParagraph::AnnotationKind>(__input.index()); }
  sem::AnnotatedParagraph::AnnotationKind getAnnotationKind() const { return getAnnotationKind(data); }
};

/// \brief Shortened colon example block
struct ColonExample : public sem::Org {
  using Org::Org;
  virtual ~ColonExample() = default;
  BOOST_DESCRIBE_CLASS(ColonExample,
                       (Org),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::ColonExample; }
};

/// \brief Caption annotation for any subsequent node
struct CmdAttr : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdAttr() = default;
  BOOST_DESCRIBE_CLASS(CmdAttr,
                       (Attached),
                       (),
                       (),
                       (staticKind, target, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
};

/// \brief Inline, statement or block call
struct Call : public sem::Org {
  using Org::Org;
  virtual ~Call() = default;
  BOOST_DESCRIBE_CLASS(Call,
                       (Org),
                       (),
                       (),
                       (staticKind, name, parameters, isCommand, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  Str name;
  /// \brief Additional parameters aside from 'exporter',
  sem::SemId<sem::CmdArguments> parameters = sem::SemId<sem::CmdArguments>::Nil();
  bool isCommand = false;
  virtual OrgSemKind getKind() const { return OrgSemKind::Call; }
};

struct List : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~List() = default;
  BOOST_DESCRIBE_CLASS(List,
                       (Stmt),
                       (),
                       (),
                       (staticKind,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionList,
                        (bool() const) isNumberedList))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  /// \brief List is marked as description if any list item has a header
  bool isDescriptionList() const;
  /// \brief List is marked as numbered if any list item has bullet text set
  bool isNumberedList() const;
};

struct ListItem : public sem::Org {
  using Org::Org;
  virtual ~ListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, Partial, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty, Partial)
  BOOST_DESCRIBE_CLASS(ListItem,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        checkbox,
                        header,
                        bullet,
                        (OrgSemKind() const) getKind,
                        (bool() const) isDescriptionItem))
  static OrgSemKind const staticKind;
  sem::ListItem::Checkbox checkbox = sem::ListItem::Checkbox::None;
  /// \brief Description list item header
  Opt<sem::SemId<sem::Paragraph>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  Opt<Str> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool isDescriptionItem() const { return header.has_value(); }
};

struct DocumentOptions : public sem::Org {
  using Org::Org;
  virtual ~DocumentOptions() = default;
  struct ExportConfig {
    struct TaskExport {
      BOOST_DESCRIBE_CLASS(TaskExport, (), (), (), (taskWhitelist))
      Vec<Str> taskWhitelist = {};
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
      BOOST_DESCRIBE_CLASS(DoExport, (), (), (), (exportToc))
      bool exportToc;
    };

    struct ExportFixed {
      BOOST_DESCRIBE_CLASS(ExportFixed, (), (), (), (exportLevels))
      int exportLevels;
    };

    using TocExport = std::variant<sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::ExportFixed>;
    enum class TocExportKind : short int { DoExport, ExportFixed, };
    BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
    using variant_enum_type = sem::DocumentOptions::ExportConfig::TocExportKind;
    using variant_data_type = sem::DocumentOptions::ExportConfig::TocExport;
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
                          data,
                          (sem::DocumentOptions::ExportConfig::DoExport const&() const) getDoExport,
                          (sem::DocumentOptions::ExportConfig::DoExport&()) getDoExport,
                          (sem::DocumentOptions::ExportConfig::ExportFixed const&() const) getExportFixed,
                          (sem::DocumentOptions::ExportConfig::ExportFixed&()) getExportFixed,
                          (sem::DocumentOptions::ExportConfig::TocExportKind(sem::DocumentOptions::ExportConfig::TocExport const&)) getTocExportKind,
                          (sem::DocumentOptions::ExportConfig::TocExportKind() const) getTocExportKind))
    Opt<bool> inlinetasks = std::nullopt;
    Opt<bool> footnotes = std::nullopt;
    Opt<bool> clock = std::nullopt;
    Opt<bool> author = std::nullopt;
    Opt<bool> emphasis = std::nullopt;
    Opt<bool> specialStrings = std::nullopt;
    Opt<bool> propertyDrawers = std::nullopt;
    Opt<bool> statisticsCookies = std::nullopt;
    /// \brief Include todo keywords in export
    Opt<bool> todoText = std::nullopt;
    sem::DocumentOptions::ExportConfig::BrokenLinks brokenLinks = sem::DocumentOptions::ExportConfig::BrokenLinks::Mark;
    sem::DocumentOptions::ExportConfig::TocExport tocExport = sem::DocumentOptions::ExportConfig::DoExport{false};
    sem::DocumentOptions::ExportConfig::TagExport tagExport = sem::DocumentOptions::ExportConfig::TagExport::All;
    sem::DocumentOptions::ExportConfig::TocExport data;
    sem::DocumentOptions::ExportConfig::DoExport const& getDoExport() const { return std::get<0>(data); }
    sem::DocumentOptions::ExportConfig::DoExport& getDoExport() { return std::get<0>(data); }
    sem::DocumentOptions::ExportConfig::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
    sem::DocumentOptions::ExportConfig::ExportFixed& getExportFixed() { return std::get<1>(data); }
    static sem::DocumentOptions::ExportConfig::TocExportKind getTocExportKind(sem::DocumentOptions::ExportConfig::TocExport const& __input) { return static_cast<sem::DocumentOptions::ExportConfig::TocExportKind>(__input.index()); }
    sem::DocumentOptions::ExportConfig::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
  };

  enum class Visibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
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
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperty))
  static OrgSemKind const staticKind;
  sem::DocumentOptions::Visibility initialVisibility = sem::DocumentOptions::Visibility::ShowEverything;
  Vec<sem::Subtree::Property> properties = {};
  sem::DocumentOptions::ExportConfig exportConfig;
  Opt<bool> fixedWidthSections = std::nullopt;
  Opt<bool> startupIndented = std::nullopt;
  Opt<Str> category = std::nullopt;
  Opt<Str> setupfile = std::nullopt;
  Opt<int> maxSubtreeLevelExport = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  Vec<sem::Subtree::Property> getProperties(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
  Opt<sem::Subtree::Property> getProperty(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
};

struct Document : public sem::Org {
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
                        exportFileName,
                        (OrgSemKind() const) getKind,
                        (Vec<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperties,
                        (Opt<sem::Subtree::Property>(Str const&, Opt<Str> const&) const) getProperty))
  static OrgSemKind const staticKind;
  Opt<sem::SemId<sem::Paragraph>> title = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> author = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> creator = std::nullopt;
  Vec<sem::SemId<sem::HashTag>> filetags = {};
  Opt<sem::SemId<sem::RawText>> email = std::nullopt;
  Vec<Str> language = {};
  sem::SemId<sem::DocumentOptions> options = sem::SemId<sem::DocumentOptions>::Nil();
  Opt<Str> exportFileName = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Document; }
  Vec<sem::Subtree::Property> getProperties(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
  Opt<sem::Subtree::Property> getProperty(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
};

struct FileTarget : public sem::Org {
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
                        regexp,
                        (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  Str path;
  Opt<int> line = std::nullopt;
  Opt<Str> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  Opt<Str> targetId = std::nullopt;
  Opt<Str> regexp = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::FileTarget; }
};

struct TextSeparator : public sem::Org {
  using Org::Org;
  virtual ~TextSeparator() = default;
  BOOST_DESCRIBE_CLASS(TextSeparator,
                       (Org),
                       (),
                       (),
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
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
    BOOST_DESCRIBE_CLASS(OrgDocument, (), (), (), (minLevel))
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    Opt<int> minLevel = std::nullopt;
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
                       (staticKind,
                        path,
                        firstLine,
                        lastLine,
                        data,
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
  static OrgSemKind const staticKind;
  /// \brief Path to include
  Str path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  Opt<int> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  Opt<int> lastLine = std::nullopt;
  sem::Include::Data data;
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
                       (staticKind, (OrgSemKind() const) getKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentGroup; }
};

}
/* clang-format on */