/* clang-format off */
#pragma once
#include <haxorg/sem/ImmOrgBase.hpp>
namespace org{
/// \brief Single key-value (or positional)
struct ImmCmdArgument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgument() = default;
  static OrgSemKind const staticKind;
  /// \brief Key
  Opt<ImmBox<Str>> key = std::nullopt;
  /// \brief When used in the `:var` assignment, this stores variable name
  Opt<ImmBox<Str>> varname = std::nullopt;
  /// \brief Value
  ImmBox<Str> value;
};

/// \brief Data type to wrap list of identical command arguments
struct ImmCmdArgumentList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArgumentList() = default;
  static OrgSemKind const staticKind;
  /// \brief List of arguments
  ImmVec<org::ImmIdT<org::ImmCmdArgument>> args = {};
};

/// \brief Additional arguments for command blocks
struct ImmCmdArguments : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCmdArguments() = default;
  static OrgSemKind const staticKind;
  /// \brief Positional arguments with no keys
  org::ImmIdT<org::ImmCmdArgumentList> positional = org::ImmIdT<org::ImmCmdArgumentList>::Nil();
  /// \brief Stored key-value mapping
  ImmMap<Str, org::ImmIdT<org::ImmCmdArgumentList>> named;
};

struct ImmErrorItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorItem() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> message;
  /// \brief Conversion function name where the error was created
  Opt<ImmBox<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<ImmBox<int>> line = std::nullopt;
};

/// \brief Group of value conversion errors
struct ImmErrorGroup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmErrorGroup() = default;
  static OrgSemKind const staticKind;
  ImmVec<org::ImmIdT<org::ImmErrorItem>> diagnostics = {};
  /// \brief Conversion function name where the error was created
  Opt<ImmBox<Str>> function = std::nullopt;
  /// \brief Line number for the conversion where the error was created
  Opt<ImmBox<Str>> line = std::nullopt;
};

/// \brief Base class for all document-level entries. Note that some node kinds might also have inline entries (examples include links, source code blocks, call blocks)
struct ImmStmt : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmt() = default;
  ImmVec<org::ImmIdT<org::ImmOrg>> attached;
};

/// \brief Base class for all inline elements
struct ImmInline : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInline() = default;
};

/// \brief Zero or more statement nodes
struct ImmStmtList : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmStmtList() = default;
  static OrgSemKind const staticKind;
};

/// \brief Node without content
struct ImmEmpty : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmEmpty() = default;
  static OrgSemKind const staticKind;
};

/// \brief Base class for block or line commands
struct ImmCmd : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmd() = default;
  /// \brief Additional parameters aside from 'exporter',
  Opt<ImmBox<org::ImmIdT<org::ImmCmdArguments>>> parameters = std::nullopt;
};

/// \brief Block command type
struct ImmBlock : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmBlock() = default;
};

/// \brief Line commands
struct ImmLineCommand : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmLineCommand() = default;
};

/// \brief Line command that might get attached to some block element
struct ImmAttached : public org::ImmLineCommand {
  using ImmLineCommand::ImmLineCommand;
  virtual ~ImmAttached() = default;
};

/// \brief Final node
struct ImmLeaf : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLeaf() = default;
  /// \brief Final leaf value
  ImmBox<Str> text = "";
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdCaption : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdCaption() = default;
  static OrgSemKind const staticKind;
  /// \brief Content description
  org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
};

/// \brief Name identifier for the statement elements.
struct ImmCmdName : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdName() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
};

/// \brief Custom line command with list of parsed arguments
struct ImmCmdCustomArgs : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdCustomArgs() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
};

/// \brief Custom command with raw unparsed string value
struct ImmCmdCustomRaw : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomRaw() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  ImmBox<Str> text;
};

/// \brief Custom line command with text paragraph value
struct ImmCmdCustomText : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmCmdCustomText() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> name;
  bool isAttached = false;
  org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
};

struct ImmCmdResults : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdResults() = default;
  static OrgSemKind const staticKind;
};

/// \brief Tblfm command type
struct ImmCmdTblfm : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCmdTblfm() = default;
  static OrgSemKind const staticKind;
};

/// \brief Single or nested inline hash-tag
struct ImmHashTag : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmHashTag() = default;
  static OrgSemKind const staticKind;
  /// \brief Main part of the tag
  ImmBox<Str> head;
  /// \brief List of nested tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> subtags = {};
};

/// \brief Inline and regular footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct ImmFootnote : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmFootnote() = default;
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  ImmBox<Str> tag = "";
  /// \brief Link to possibly resolved definition
  Opt<ImmBox<org::ImmIdT<org::ImmOrg>>> definition = std::nullopt;
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
    /// \brief mode
    org::ImmTime::Mode mode;
    /// \brief period
    org::ImmTime::Period period;
    /// \brief count
    int count;
  };

  struct Static {
    Opt<ImmBox<org::ImmTime::Repeat>> repeat;
    UserTime time;
  };

  struct Dynamic {
    ImmBox<Str> expr;
  };

  using TimeVariant = std::variant<org::ImmTime::Static, org::ImmTime::Dynamic>;
  enum class TimeKind : short int { Static, Dynamic, };
  BOOST_DESCRIBE_NESTED_ENUM(TimeKind, Static, Dynamic)
  using variant_enum_type = org::ImmTime::TimeKind;
  using variant_data_type = org::ImmTime::TimeVariant;
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  org::ImmTime::TimeVariant time;
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
  static OrgSemKind const staticKind;
  /// \brief Starting time
  org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
  /// \brief Finishing time
  org::ImmIdT<org::ImmTime> to = org::ImmIdT<org::ImmTime>::Nil();
};

/// \brief Inline macro invocation
struct ImmMacro : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMacro() = default;
  static OrgSemKind const staticKind;
  /// \brief Macro name
  ImmBox<Str> name = "";
  /// \brief Additional parameters aside from 'exporter',
  org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
};

/// \brief Text symbol or symbol command
struct ImmSymbol : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSymbol() = default;
  /// \brief Symbol parameters
  struct Param {
    /// \brief Key -- for non-positional
    Opt<ImmBox<Str>> key;
    /// \brief Uninterpreted value
    ImmBox<Str> value;
  };

  static OrgSemKind const staticKind;
  /// \brief Name of the symbol
  ImmBox<Str> name;
  /// \brief Optional list of parameters
  ImmVec<org::ImmSymbol::Param> parameters;
  /// \brief Positional parameters
  ImmVec<org::ImmIdT<org::ImmOrg>> positional;
};

/// \brief Escaped text
struct ImmEscaped : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmEscaped() = default;
  static OrgSemKind const staticKind;
};

/// \brief \n newline
struct ImmNewline : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmNewline() = default;
  static OrgSemKind const staticKind;
};

/// \brief ' "space",
struct ImmSpace : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmSpace() = default;
  static OrgSemKind const staticKind;
};

/// \brief word
struct ImmWord : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmWord() = default;
  static OrgSemKind const staticKind;
};

/// \brief @mention
struct ImmAtMention : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmAtMention() = default;
  static OrgSemKind const staticKind;
};

struct ImmRawText : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRawText() = default;
  static OrgSemKind const staticKind;
};

struct ImmPunctuation : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPunctuation() = default;
  static OrgSemKind const staticKind;
};

struct ImmPlaceholder : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmPlaceholder() = default;
  static OrgSemKind const staticKind;
};

struct ImmBigIdent : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmBigIdent() = default;
  static OrgSemKind const staticKind;
};

/// \brief ~<<<target>>>~
struct ImmRadioTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmRadioTarget() = default;
  static OrgSemKind const staticKind;
};

/// \brief ~<<target>>~
struct ImmTextTarget : public org::ImmLeaf {
  using ImmLeaf::ImmLeaf;
  virtual ~ImmTextTarget() = default;
  static OrgSemKind const staticKind;
};

struct ImmMarkup : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmMarkup() = default;
};

struct ImmBold : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmBold() = default;
  static OrgSemKind const staticKind;
};

struct ImmUnderline : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmUnderline() = default;
  static OrgSemKind const staticKind;
};

struct ImmMonospace : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMonospace() = default;
  static OrgSemKind const staticKind;
};

struct ImmMarkQuote : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmMarkQuote() = default;
  static OrgSemKind const staticKind;
};

struct ImmVerbatim : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmVerbatim() = default;
  static OrgSemKind const staticKind;
};

struct ImmItalic : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmItalic() = default;
  static OrgSemKind const staticKind;
};

struct ImmStrike : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmStrike() = default;
  static OrgSemKind const staticKind;
};

struct ImmPar : public org::ImmMarkup {
  using ImmMarkup::ImmMarkup;
  virtual ~ImmPar() = default;
  static OrgSemKind const staticKind;
};

/// \brief Latex code body
struct ImmLatex : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmLatex() = default;
  static OrgSemKind const staticKind;
};

struct ImmLink : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmLink() = default;
  struct Raw {
    ImmBox<Str> text;
  };

  struct Id {
    ImmBox<Str> text;
  };

  struct Person {
    ImmBox<Str> name;
  };

  struct UserProtocol {
    ImmBox<Str> protocol;
    ImmBox<Str> target;
  };

  struct Internal {
    ImmBox<Str> target;
  };

  struct Footnote {
    ImmBox<Str> target;
  };

  struct File {
    ImmBox<Str> file;
  };

  struct Attachment {
    ImmBox<Str> file;
  };

  using Data = std::variant<org::ImmLink::Raw, org::ImmLink::Id, org::ImmLink::Person, org::ImmLink::UserProtocol, org::ImmLink::Internal, org::ImmLink::Footnote, org::ImmLink::File, org::ImmLink::Attachment>;
  enum class Kind : short int { Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, Person, UserProtocol, Internal, Footnote, File, Attachment)
  using variant_enum_type = org::ImmLink::Kind;
  using variant_data_type = org::ImmLink::Data;
  static OrgSemKind const staticKind;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  org::ImmLink::Data data;
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
  static OrgSemKind const staticKind;
};

/// \brief Quotation block
struct ImmBlockQuote : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockQuote() = default;
  static OrgSemKind const staticKind;
};

/// \brief Comment block
struct ImmBlockComment : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmBlockComment() = default;
  static OrgSemKind const staticKind;
};

/// \brief Verse quotation block
struct ImmBlockVerse : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockVerse() = default;
  static OrgSemKind const staticKind;
};

/// \brief Example block
struct ImmBlockExample : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockExample() = default;
  static OrgSemKind const staticKind;
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
  static OrgSemKind const staticKind;
  /// \brief Export block type
  org::ImmBlockExport::Format format = Format::Inline;
  /// \brief Exporter backend name
  ImmBox<Str> exporter;
  /// \brief Customized position of the text in the final exporting document.
  Opt<ImmBox<Str>> placement = std::nullopt;
  /// \brief Raw exporter content string
  ImmBox<Str> content;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct ImmBlockAdmonition : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockAdmonition() = default;
  static OrgSemKind const staticKind;
};

/// \brief Base class for all code blocks
struct ImmBlockCode : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmBlockCode() = default;
  struct Line {
    struct Part {
      struct Raw {
        ImmBox<Str> code;
      };

      struct Callout {
        ImmBox<Str> name;
      };

      struct Tangle {
        ImmBox<Str> target;
      };

      using Data = std::variant<org::ImmBlockCode::Line::Part::Raw, org::ImmBlockCode::Line::Part::Callout, org::ImmBlockCode::Line::Part::Tangle>;
      enum class Kind : short int { Raw, Callout, Tangle, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
      using variant_enum_type = org::ImmBlockCode::Line::Part::Kind;
      using variant_data_type = org::ImmBlockCode::Line::Part::Data;
      org::ImmBlockCode::Line::Part::Data data;
      org::ImmBlockCode::Line::Part::Raw const& getRaw() const { return std::get<0>(data); }
      org::ImmBlockCode::Line::Part::Raw& getRaw() { return std::get<0>(data); }
      org::ImmBlockCode::Line::Part::Callout const& getCallout() const { return std::get<1>(data); }
      org::ImmBlockCode::Line::Part::Callout& getCallout() { return std::get<1>(data); }
      org::ImmBlockCode::Line::Part::Tangle const& getTangle() const { return std::get<2>(data); }
      org::ImmBlockCode::Line::Part::Tangle& getTangle() { return std::get<2>(data); }
      static org::ImmBlockCode::Line::Part::Kind getKind(org::ImmBlockCode::Line::Part::Data const& __input) { return static_cast<org::ImmBlockCode::Line::Part::Kind>(__input.index()); }
      org::ImmBlockCode::Line::Part::Kind getKind() const { return getKind(data); }
    };

    /// \brief parts of the single line
    ImmVec<org::ImmBlockCode::Part> parts = {};
  };

  /// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
  struct Switch {
    /// \brief Enumerate code lines starting from `start` value instead of default indexing.
    struct LineStart {
      /// \brief First line number
      int start;
      /// \brief Continue numbering from the previous block nstead of starting anew
      bool extendLast = false;
    };

    struct CalloutFormat {
      ImmBox<Str> format = "";
    };

    struct RemoveCallout {
      bool remove = true;
    };

    /// \brief Emphasize single line -- can be repeated multiple times
    struct EmphasizeLine {
      ImmVec<int> line = {};
    };

    struct Dedent {
      int value = 0;
    };

    using Data = std::variant<org::ImmBlockCode::Switch::LineStart, org::ImmBlockCode::Switch::CalloutFormat, org::ImmBlockCode::Switch::RemoveCallout, org::ImmBlockCode::Switch::EmphasizeLine, org::ImmBlockCode::Switch::Dedent>;
    enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
    using variant_enum_type = org::ImmBlockCode::Switch::Kind;
    using variant_data_type = org::ImmBlockCode::Switch::Data;
    org::ImmBlockCode::Switch::Data data;
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
    struct None {};

    /// \brief Source code block evaluated to an org-mode node element
    struct OrgValue {
      /// \brief Parsed value of the evaluation result
      org::ImmIdT<org::ImmOrg> value = org::ImmIdT<org::ImmOrg>::Nil();
    };

    /// \brief Output evaluation results to a file
    struct File {
      ImmBox<Str> path;
    };

    /// \brief Evaluation output is a raw text
    struct Raw {
      ImmBox<Str> text;
    };

    using Data = std::variant<org::ImmBlockCode::EvalResult::None, org::ImmBlockCode::EvalResult::OrgValue, org::ImmBlockCode::EvalResult::File, org::ImmBlockCode::EvalResult::Raw>;
    enum class Kind : short int { None, OrgValue, File, Raw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, None, OrgValue, File, Raw)
    using variant_enum_type = org::ImmBlockCode::EvalResult::Kind;
    using variant_data_type = org::ImmBlockCode::EvalResult::Data;
    org::ImmBlockCode::EvalResult::Data data;
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

  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<ImmBox<Str>> lang = std::nullopt;
  /// \brief Switch options for block
  ImmVec<org::ImmBlockCode::Switch> switches = {};
  /// \brief What to export
  org::ImmBlockCode::Exports exports = Exports::Both;
  /// \brief Code evaluation results
  Opt<ImmBox<org::ImmBlockCode::EvalResult>> result = std::nullopt;
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
};

/// \brief Single subtree log entry
struct ImmSubtreeLog : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmSubtreeLog() = default;
  /// \brief Base value for the log variant
  struct DescribedLog {
    /// \brief Optional description of the log entry
    Opt<ImmBox<org::ImmIdT<org::ImmStmtList>>> desc = std::nullopt;
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
    /// \brief Previous priority for change and removal
    Opt<ImmBox<std::string>> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<ImmBox<std::string>> newPriority = std::nullopt;
    /// \brief When priority was changed
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Which action taken
    org::ImmSubtreeLog::Action action;
  };

  /// \brief Timestamped note
  struct Note : public org::ImmSubtreeLog::DescribedLog {
    /// \brief Where log was taken
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
  };

  /// \brief Refiling action
  struct Refile : public org::ImmSubtreeLog::DescribedLog {
    /// \brief When the refiling happened
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Link to the original subtree
    org::ImmIdT<org::ImmLink> from = org::ImmIdT<org::ImmLink>::Nil();
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock : public org::ImmSubtreeLog::DescribedLog {
    /// \brief Clock start time
    org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Optional end of the clock
    Opt<ImmBox<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State : public org::ImmSubtreeLog::DescribedLog {
    ImmBox<Str> from;
    ImmBox<Str> to;
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag : public org::ImmSubtreeLog::DescribedLog {
    /// \brief When the log was assigned
    org::ImmIdT<org::ImmTime> on = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Tag in question
    org::ImmIdT<org::ImmHashTag> tag = org::ImmIdT<org::ImmHashTag>::Nil();
    /// \brief Added/removed?
    bool added = false;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown : public org::ImmSubtreeLog::DescribedLog {};

  using LogEntry = std::variant<org::ImmSubtreeLog::Priority, org::ImmSubtreeLog::Note, org::ImmSubtreeLog::Refile, org::ImmSubtreeLog::Clock, org::ImmSubtreeLog::State, org::ImmSubtreeLog::Tag, org::ImmSubtreeLog::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Tag, Unknown)
  using variant_enum_type = org::ImmSubtreeLog::Kind;
  using variant_data_type = org::ImmSubtreeLog::LogEntry;
  static OrgSemKind const staticKind;
  org::ImmSubtreeLog::LogEntry log = Note{};
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
    /// \brief Time period kind -- not associated with point/range distinction
    org::ImmSubtree::Kind kind;
    /// \brief Clock start time
    org::ImmIdT<org::ImmTime> from = org::ImmIdT<org::ImmTime>::Nil();
    /// \brief Optional end of the clock
    Opt<ImmBox<org::ImmIdT<org::ImmTime>>> to = std::nullopt;
  };

  /// \brief Single subtree property
  struct Property {
    enum class SetMode : short int { Override, Add, Subtract, };
    BOOST_DESCRIBE_NESTED_ENUM(SetMode, Override, Add, Subtract)
    enum class InheritanceMode : short int { ThisAndSub, OnlyThis, OnlySub, };
    BOOST_DESCRIBE_NESTED_ENUM(InheritanceMode, ThisAndSub, OnlyThis, OnlySub)
    struct Nonblocking {
      bool isBlocking;
    };

    struct Trigger {};

    struct Origin {
      org::ImmIdT<org::ImmParagraph> text = org::ImmIdT<org::ImmParagraph>::Nil();
    };

    struct ExportLatexClass {
      ImmBox<Str> latexClass;
    };

    struct ExportLatexClassOptions {
      ImmVec<Str> options;
    };

    struct ExportLatexHeader {
      ImmBox<Str> header;
    };

    struct ExportLatexCompiler {
      ImmBox<Str> compiler;
    };

    struct Ordered {
      bool isOrdered;
    };

    struct Effort {
      int hours = 0;
      int minutes = 0;
    };

    struct Visibility {
      enum class Level : short int { Folded, Children, Content, All, };
      BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
      org::ImmSubtree::Property::Level level;
    };

    struct ExportOptions {
      ImmBox<Str> backend;
      ImmMap<Str, Str> values;
    };

    struct Blocker {
      ImmVec<Str> blockers;
    };

    struct Unnumbered {};

    struct Created {
      org::ImmIdT<org::ImmTime> time = org::ImmIdT<org::ImmTime>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomArgs {
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property target specialization
      Opt<ImmBox<Str>> sub = std::nullopt;
      /// \brief Property parameters
      org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
    };

    /// \brief Custop property with unparsed arguments
    struct CustomRaw {
      /// \brief Original name of the property
      ImmBox<Str> name = "";
      /// \brief Property value
      ImmBox<Str> value = "";
    };

    using Data = std::variant<org::ImmSubtree::Property::Nonblocking, org::ImmSubtree::Property::Trigger, org::ImmSubtree::Property::Origin, org::ImmSubtree::Property::ExportLatexClass, org::ImmSubtree::Property::ExportLatexClassOptions, org::ImmSubtree::Property::ExportLatexHeader, org::ImmSubtree::Property::ExportLatexCompiler, org::ImmSubtree::Property::Ordered, org::ImmSubtree::Property::Effort, org::ImmSubtree::Property::Visibility, org::ImmSubtree::Property::ExportOptions, org::ImmSubtree::Property::Blocker, org::ImmSubtree::Property::Unnumbered, org::ImmSubtree::Property::Created, org::ImmSubtree::Property::CustomArgs, org::ImmSubtree::Property::CustomRaw>;
    enum class Kind : short int { Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, Trigger, Origin, ExportLatexClass, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, CustomArgs, CustomRaw)
    using variant_enum_type = org::ImmSubtree::Property::Kind;
    using variant_data_type = org::ImmSubtree::Property::Data;
    org::ImmSubtree::SetMode mainSetRule = Property::SetMode::Override;
    org::ImmSubtree::SetMode subSetRule = Property::SetMode::Override;
    org::ImmSubtree::InheritanceMode inheritanceMode = Property::InheritanceMode::ThisAndSub;
    org::ImmSubtree::Property::Data data;
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

  static OrgSemKind const staticKind;
  /// \brief Subtree level
  int level = 0;
  /// \brief :ID: property
  Opt<ImmBox<Str>> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<ImmBox<Str>> todo = std::nullopt;
  /// \brief Task completion state
  Opt<ImmBox<org::ImmIdT<org::ImmSubtreeCompletion>>> completion = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> description = std::nullopt;
  /// \brief Trailing tags
  ImmVec<org::ImmIdT<org::ImmHashTag>> tags = {};
  /// \brief Main title
  org::ImmIdT<org::ImmParagraph> title = org::ImmIdT<org::ImmParagraph>::Nil();
  /// \brief Associated subtree log
  ImmVec<org::ImmIdT<org::ImmSubtreeLog>> logbook = {};
  /// \brief Immediate properties
  ImmVec<org::ImmSubtree::Property> properties = {};
  /// \brief When subtree was marked as closed
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> closed = std::nullopt;
  /// \brief When is the deadline
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> deadline = std::nullopt;
  /// \brief When the event is scheduled
  Opt<ImmBox<org::ImmIdT<org::ImmTime>>> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  Opt<ImmBox<Str>> priority = std::nullopt;
};

/// \brief Completion status of the subtree list element
struct ImmSubtreeCompletion : public org::ImmInline {
  using ImmInline::ImmInline;
  virtual ~ImmSubtreeCompletion() = default;
  static OrgSemKind const staticKind;
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
};

/// \brief Table cell
struct ImmCell : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmCell() = default;
  static OrgSemKind const staticKind;
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Table row
struct ImmRow : public org::ImmCmd {
  using ImmCmd::ImmCmd;
  virtual ~ImmRow() = default;
  static OrgSemKind const staticKind;
  /// \brief List of cells on the row
  ImmVec<org::ImmIdT<org::ImmCell>> cells = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Table
struct ImmTable : public org::ImmBlock {
  using ImmBlock::ImmBlock;
  virtual ~ImmTable() = default;
  static OrgSemKind const staticKind;
  /// \brief List of rows for the table
  ImmVec<org::ImmIdT<org::ImmRow>> rows = {};
  /// \brief Single-line pipe cell or `#+cell:` command
  bool isBlock = false;
};

/// \brief Top-level or inline paragraph
struct ImmParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmParagraph() = default;
  static OrgSemKind const staticKind;
};

/// \brief Top-level or inline paragraph with prefix annotation
struct ImmAnnotatedParagraph : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmAnnotatedParagraph() = default;
  struct None {};

  struct Footnote {
    ImmBox<Str> name;
  };

  struct Admonition {
    /// \brief Prefix admonition for the paragraph
    org::ImmIdT<sem::BigIdent> name = org::ImmIdT<org::ImmBigIdent>::Nil();
  };

  struct Timestamp {
    /// \brief Leading timestamp for the paragraph
    org::ImmIdT<org::ImmTime> time = org::ImmIdT<org::ImmTime>::Nil();
  };

  using Data = std::variant<org::ImmAnnotatedParagraph::None, org::ImmAnnotatedParagraph::Footnote, org::ImmAnnotatedParagraph::Admonition, org::ImmAnnotatedParagraph::Timestamp>;
  enum class AnnotationKind : short int { None, Footnote, Admonition, Timestamp, };
  BOOST_DESCRIBE_NESTED_ENUM(AnnotationKind, None, Footnote, Admonition, Timestamp)
  using variant_enum_type = org::ImmAnnotatedParagraph::AnnotationKind;
  using variant_data_type = org::ImmAnnotatedParagraph::Data;
  static OrgSemKind const staticKind;
  org::ImmAnnotatedParagraph::Data data;
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
  static OrgSemKind const staticKind;
};

/// \brief Caption annotation for any subsequent node
struct ImmCmdAttr : public org::ImmAttached {
  using ImmAttached::ImmAttached;
  virtual ~ImmCmdAttr() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> target;
};

/// \brief Inline, statement or block call
struct ImmCall : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmCall() = default;
  static OrgSemKind const staticKind;
  /// \brief Call target name
  ImmBox<Str> name;
  /// \brief Additional parameters aside from 'exporter',
  org::ImmIdT<org::ImmCmdArguments> parameters = org::ImmIdT<org::ImmCmdArguments>::Nil();
  bool isCommand = false;
};

struct ImmList : public org::ImmStmt {
  using ImmStmt::ImmStmt;
  virtual ~ImmList() = default;
  static OrgSemKind const staticKind;
};

struct ImmListItem : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmListItem() = default;
  enum class Checkbox : short int { None, Done, Empty, Partial, };
  BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty, Partial)
  static OrgSemKind const staticKind;
  org::ImmListItem::Checkbox checkbox = Checkbox::None;
  /// \brief Description list item header
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  Opt<ImmBox<Str>> bullet = std::nullopt;
};

struct ImmDocumentOptions : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocumentOptions() = default;
  struct ExportConfig {
    struct TaskExport {
      ImmVec<Str> taskWhitelist = {};
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
      bool exportToc;
    };

    struct ExportFixed {
      int exportLevels;
    };

    using TocExport = std::variant<org::ImmDocumentOptions::ExportConfig::DoExport, org::ImmDocumentOptions::ExportConfig::ExportFixed>;
    enum class TocExportKind : short int { DoExport, ExportFixed, };
    BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
    using variant_enum_type = org::ImmDocumentOptions::ExportConfig::TocExportKind;
    using variant_data_type = org::ImmDocumentOptions::ExportConfig::TocExport;
    Opt<ImmBox<bool>> inlinetasks = std::nullopt;
    Opt<ImmBox<bool>> footnotes = std::nullopt;
    Opt<ImmBox<bool>> clock = std::nullopt;
    Opt<ImmBox<bool>> author = std::nullopt;
    Opt<ImmBox<bool>> emphasis = std::nullopt;
    Opt<ImmBox<bool>> specialStrings = std::nullopt;
    Opt<ImmBox<bool>> propertyDrawers = std::nullopt;
    Opt<ImmBox<bool>> statisticsCookies = std::nullopt;
    /// \brief Include todo keywords in export
    Opt<ImmBox<bool>> todoText = std::nullopt;
    org::ImmDocumentOptions::BrokenLinks brokenLinks = ExportConfig::BrokenLinks::Mark;
    org::ImmDocumentOptions::TocExport tocExport = ExportConfig::DoExport{false};
    org::ImmDocumentOptions::TagExport tagExport = ExportConfig::TagExport::All;
    org::ImmDocumentOptions::ExportConfig::TocExport data;
    org::ImmDocumentOptions::ExportConfig::DoExport const& getDoExport() const { return std::get<0>(data); }
    org::ImmDocumentOptions::ExportConfig::DoExport& getDoExport() { return std::get<0>(data); }
    org::ImmDocumentOptions::ExportConfig::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
    org::ImmDocumentOptions::ExportConfig::ExportFixed& getExportFixed() { return std::get<1>(data); }
    static org::ImmDocumentOptions::ExportConfig::TocExportKind getTocExportKind(org::ImmDocumentOptions::ExportConfig::TocExport const& __input) { return static_cast<org::ImmDocumentOptions::ExportConfig::TocExportKind>(__input.index()); }
    org::ImmDocumentOptions::ExportConfig::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
  };

  enum class Visibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
  BOOST_DESCRIBE_NESTED_ENUM(Visibility, Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything)
  static OrgSemKind const staticKind;
  org::ImmDocumentOptions::Visibility initialVisibility = Visibility::ShowEverything;
  ImmVec<org::ImmSubtree::Property> properties = {};
  org::ImmDocumentOptions::ExportConfig exportConfig;
  Opt<ImmBox<bool>> fixedWidthSections = std::nullopt;
  Opt<ImmBox<bool>> startupIndented = std::nullopt;
  Opt<ImmBox<Str>> category = std::nullopt;
  Opt<ImmBox<Str>> setupfile = std::nullopt;
  Opt<ImmBox<int>> maxSubtreeLevelExport = std::nullopt;
};

struct ImmDocument : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmDocument() = default;
  static OrgSemKind const staticKind;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> title = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> author = std::nullopt;
  Opt<ImmBox<org::ImmIdT<org::ImmParagraph>>> creator = std::nullopt;
  ImmVec<org::ImmIdT<org::ImmHashTag>> filetags = {};
  Opt<ImmBox<org::ImmIdT<org::ImmRawText>>> email = std::nullopt;
  ImmVec<Str> language = {};
  org::ImmIdT<org::ImmDocumentOptions> options = org::ImmIdT<org::ImmDocumentOptions>::Nil();
  Opt<ImmBox<Str>> exportFileName = std::nullopt;
};

struct ImmFileTarget : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmFileTarget() = default;
  static OrgSemKind const staticKind;
  ImmBox<Str> path;
  Opt<ImmBox<int>> line = std::nullopt;
  Opt<ImmBox<Str>> searchTarget = std::nullopt;
  bool restrictToHeadlines = false;
  Opt<ImmBox<Str>> targetId = std::nullopt;
  Opt<ImmBox<Str>> regexp = std::nullopt;
};

struct ImmTextSeparator : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmTextSeparator() = default;
  static OrgSemKind const staticKind;
};

struct ImmInclude : public org::ImmOrg {
  using ImmOrg::ImmOrg;
  virtual ~ImmInclude() = default;
  struct Example {};

  struct Export {};

  struct Src {};

  struct OrgDocument {
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    Opt<ImmBox<int>> minLevel = std::nullopt;
  };

  using Data = std::variant<org::ImmInclude::Example, org::ImmInclude::Export, org::ImmInclude::Src, org::ImmInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  using variant_enum_type = org::ImmInclude::Kind;
  using variant_data_type = org::ImmInclude::Data;
  static OrgSemKind const staticKind;
  /// \brief Path to include
  ImmBox<Str> path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  Opt<ImmBox<int>> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  Opt<ImmBox<int>> lastLine = std::nullopt;
  org::ImmInclude::Data data;
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
  static OrgSemKind const staticKind;
};

}
/* clang-format on */