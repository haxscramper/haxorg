/* clang-format off */
#pragma once
#include <haxorg/sem/SemOrgEnums.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <haxorg/sem/SemOrgBaseSharedTypes.hpp>
#include <haxorg/sem/SemOrgEnums.hpp>
namespace org::sem {
struct SourceLocation {
  BOOST_DESCRIBE_CLASS(SourceLocation,
                       (),
                       (),
                       (),
                       (line, column, pos, file))
  int line = -1;
  int column = -1;
  int pos = -1;
  hstd::Opt<hstd::Str> file = std::nullopt;
  bool operator==(org::sem::SourceLocation const& other) const;
  SourceLocation() {  }
};

struct LispCode {
  struct Call {
    BOOST_DESCRIBE_CLASS(Call,
                         (),
                         (),
                         (),
                         (name, args))
    hstd::Str name = "";
    hstd::Vec<org::sem::LispCode> args = {};
    bool operator==(org::sem::LispCode::Call const& other) const;
    Call() {  }
  };

  struct List {
    BOOST_DESCRIBE_CLASS(List,
                         (),
                         (),
                         (),
                         (items))
    hstd::Vec<org::sem::LispCode> items = {};
    bool operator==(org::sem::LispCode::List const& other) const;
    List() {  }
  };

  struct KeyValue {
    BOOST_DESCRIBE_CLASS(KeyValue,
                         (),
                         (),
                         (),
                         (name, value))
    hstd::Str name = "";
    hstd::Vec<org::sem::LispCode> value = {};
    bool operator==(org::sem::LispCode::KeyValue const& other) const;
    KeyValue() {  }
  };

  struct Number {
    BOOST_DESCRIBE_CLASS(Number,
                         (),
                         (),
                         (),
                         (value))
    int value;
    bool operator==(org::sem::LispCode::Number const& other) const;
    Number() {  }
  };

  struct Text {
    BOOST_DESCRIBE_CLASS(Text,
                         (),
                         (),
                         (),
                         (value))
    hstd::Str value = "";
    bool operator==(org::sem::LispCode::Text const& other) const;
    Text() {  }
  };

  struct Ident {
    BOOST_DESCRIBE_CLASS(Ident,
                         (),
                         (),
                         (),
                         (name))
    hstd::Str name = "";
    bool operator==(org::sem::LispCode::Ident const& other) const;
    Ident() {  }
  };

  struct Boolean {
    BOOST_DESCRIBE_CLASS(Boolean,
                         (),
                         (),
                         (),
                         (value))
    bool value = false;
    bool operator==(org::sem::LispCode::Boolean const& other) const;
    Boolean() {  }
  };

  struct Real {
    BOOST_DESCRIBE_CLASS(Real,
                         (),
                         (),
                         (),
                         (value))
    float value;
    bool operator==(org::sem::LispCode::Real const& other) const;
    Real() {  }
  };

  using Data = std::variant<org::sem::LispCode::Call, org::sem::LispCode::List, org::sem::LispCode::KeyValue, org::sem::LispCode::Number, org::sem::LispCode::Text, org::sem::LispCode::Ident, org::sem::LispCode::Boolean, org::sem::LispCode::Real>;
  enum class Kind : short int { Call, List, KeyValue, Number, Text, Ident, Boolean, Real, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Call, List, KeyValue, Number, Text, Ident, Boolean, Real)
  using variant_enum_type = org::sem::LispCode::Kind;
  using variant_data_type = org::sem::LispCode::Data;
  BOOST_DESCRIBE_CLASS(LispCode,
                       (),
                       (),
                       (),
                       (data))
  org::sem::LispCode::Data data;
  bool operator==(org::sem::LispCode const& other) const;
  LispCode() {  }
  bool isCall() const { return getKind() == Kind::Call; }
  org::sem::LispCode::Call const& getCall() const { return hstd::variant_get<0>(data); }
  org::sem::LispCode::Call& getCall() { return hstd::variant_get<0>(data); }
  bool isList() const { return getKind() == Kind::List; }
  org::sem::LispCode::List const& getList() const { return hstd::variant_get<1>(data); }
  org::sem::LispCode::List& getList() { return hstd::variant_get<1>(data); }
  bool isKeyValue() const { return getKind() == Kind::KeyValue; }
  org::sem::LispCode::KeyValue const& getKeyValue() const { return hstd::variant_get<2>(data); }
  org::sem::LispCode::KeyValue& getKeyValue() { return hstd::variant_get<2>(data); }
  bool isNumber() const { return getKind() == Kind::Number; }
  org::sem::LispCode::Number const& getNumber() const { return hstd::variant_get<3>(data); }
  org::sem::LispCode::Number& getNumber() { return hstd::variant_get<3>(data); }
  bool isText() const { return getKind() == Kind::Text; }
  org::sem::LispCode::Text const& getText() const { return hstd::variant_get<4>(data); }
  org::sem::LispCode::Text& getText() { return hstd::variant_get<4>(data); }
  bool isIdent() const { return getKind() == Kind::Ident; }
  org::sem::LispCode::Ident const& getIdent() const { return hstd::variant_get<5>(data); }
  org::sem::LispCode::Ident& getIdent() { return hstd::variant_get<5>(data); }
  bool isBoolean() const { return getKind() == Kind::Boolean; }
  org::sem::LispCode::Boolean const& getBoolean() const { return hstd::variant_get<6>(data); }
  org::sem::LispCode::Boolean& getBoolean() { return hstd::variant_get<6>(data); }
  bool isReal() const { return getKind() == Kind::Real; }
  org::sem::LispCode::Real const& getReal() const { return hstd::variant_get<7>(data); }
  org::sem::LispCode::Real& getReal() { return hstd::variant_get<7>(data); }
  static org::sem::LispCode::Kind getKind(org::sem::LispCode::Data const& __input) { return static_cast<org::sem::LispCode::Kind>(__input.index()); }
  org::sem::LispCode::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::LispCode::Data const& sub_variant_get_data() const { return data; }
  org::sem::LispCode::Kind sub_variant_get_kind() const { return getKind(); }
};

struct Tblfm {
  struct Expr {
    struct AxisRef {
      struct Position {
        struct Index {
          Index () {}
          BOOST_DESCRIBE_CLASS(Index,
                               (),
                               (),
                               (),
                               (index))
          int index;
          bool operator==(org::sem::Tblfm::Expr::AxisRef::Position::Index const& other) const;
        };

        struct Name {
          Name () {}
          BOOST_DESCRIBE_CLASS(Name,
                               (),
                               (),
                               (),
                               (name))
          hstd::Str name = "";
          bool operator==(org::sem::Tblfm::Expr::AxisRef::Position::Name const& other) const;
        };

        using Data = std::variant<org::sem::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Name>;
        enum class Kind : short int { Index, Name, };
        BOOST_DESCRIBE_NESTED_ENUM(Kind, Index, Name)
        using variant_enum_type = org::sem::Tblfm::Expr::AxisRef::Position::Kind;
        using variant_data_type = org::sem::Tblfm::Expr::AxisRef::Position::Data;
        Position () {}
        BOOST_DESCRIBE_CLASS(Position,
                             (),
                             (),
                             (),
                             (data))
        org::sem::Tblfm::Expr::AxisRef::Position::Data data;
        bool operator==(org::sem::Tblfm::Expr::AxisRef::Position const& other) const;
        bool isIndex() const { return getKind() == Kind::Index; }
        org::sem::Tblfm::Expr::AxisRef::Position::Index const& getIndex() const { return hstd::variant_get<0>(data); }
        org::sem::Tblfm::Expr::AxisRef::Position::Index& getIndex() { return hstd::variant_get<0>(data); }
        bool isName() const { return getKind() == Kind::Name; }
        org::sem::Tblfm::Expr::AxisRef::Position::Name const& getName() const { return hstd::variant_get<1>(data); }
        org::sem::Tblfm::Expr::AxisRef::Position::Name& getName() { return hstd::variant_get<1>(data); }
        static org::sem::Tblfm::Expr::AxisRef::Position::Kind getKind(org::sem::Tblfm::Expr::AxisRef::Position::Data const& __input) { return static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(__input.index()); }
        org::sem::Tblfm::Expr::AxisRef::Position::Kind getKind() const { return getKind(data); }
        char const* sub_variant_get_name() const { return "data"; }
        org::sem::Tblfm::Expr::AxisRef::Position::Data const& sub_variant_get_data() const { return data; }
        org::sem::Tblfm::Expr::AxisRef::Position::Kind sub_variant_get_kind() const { return getKind(); }
      };

      BOOST_DESCRIBE_CLASS(AxisRef,
                           (),
                           (),
                           (),
                           (col, row))
      org::sem::Tblfm::Expr::AxisRef::Position col;
      hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position> row = std::nullopt;
      bool operator==(org::sem::Tblfm::Expr::AxisRef const& other) const;
    };

    struct AxisName {
      BOOST_DESCRIBE_CLASS(AxisName,
                           (),
                           (),
                           (),
                           (name))
      hstd::Str name = "";
      bool operator==(org::sem::Tblfm::Expr::AxisName const& other) const;
    };

    struct IntLiteral {
      BOOST_DESCRIBE_CLASS(IntLiteral,
                           (),
                           (),
                           (),
                           (value))
      int value;
      bool operator==(org::sem::Tblfm::Expr::IntLiteral const& other) const;
    };

    struct FloatLiteral {
      BOOST_DESCRIBE_CLASS(FloatLiteral,
                           (),
                           (),
                           (),
                           (value))
      float value;
      bool operator==(org::sem::Tblfm::Expr::FloatLiteral const& other) const;
    };

    struct RangeRef {
      BOOST_DESCRIBE_CLASS(RangeRef,
                           (),
                           (),
                           (),
                           (first, last))
      hstd::Opt<org::sem::Tblfm::Expr::AxisRef> first = std::nullopt;
      hstd::Opt<org::sem::Tblfm::Expr::AxisRef> last = std::nullopt;
      bool operator==(org::sem::Tblfm::Expr::RangeRef const& other) const;
    };

    struct Call {
      BOOST_DESCRIBE_CLASS(Call,
                           (),
                           (),
                           (),
                           (name, args))
      hstd::Str name = "";
      hstd::Vec<org::sem::Tblfm::Expr> args = {};
      bool operator==(org::sem::Tblfm::Expr::Call const& other) const;
    };

    struct Elisp {
      BOOST_DESCRIBE_CLASS(Elisp,
                           (),
                           (),
                           (),
                           (value))
      hstd::Str value = "";
      bool operator==(org::sem::Tblfm::Expr::Elisp const& other) const;
    };

    using Data = std::variant<org::sem::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Elisp>;
    enum class Kind : short int { AxisRef, AxisName, IntLiteral, FloatLiteral, RangeRef, Call, Elisp, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, AxisRef, AxisName, IntLiteral, FloatLiteral, RangeRef, Call, Elisp)
    using variant_enum_type = org::sem::Tblfm::Expr::Kind;
    using variant_data_type = org::sem::Tblfm::Expr::Data;
    BOOST_DESCRIBE_CLASS(Expr,
                         (),
                         (),
                         (),
                         (data))
    org::sem::Tblfm::Expr::Data data;
    bool operator==(org::sem::Tblfm::Expr const& other) const;
    bool isAxisRef() const { return getKind() == Kind::AxisRef; }
    org::sem::Tblfm::Expr::AxisRef const& getAxisRef() const { return hstd::variant_get<0>(data); }
    org::sem::Tblfm::Expr::AxisRef& getAxisRef() { return hstd::variant_get<0>(data); }
    bool isAxisName() const { return getKind() == Kind::AxisName; }
    org::sem::Tblfm::Expr::AxisName const& getAxisName() const { return hstd::variant_get<1>(data); }
    org::sem::Tblfm::Expr::AxisName& getAxisName() { return hstd::variant_get<1>(data); }
    bool isIntLiteral() const { return getKind() == Kind::IntLiteral; }
    org::sem::Tblfm::Expr::IntLiteral const& getIntLiteral() const { return hstd::variant_get<2>(data); }
    org::sem::Tblfm::Expr::IntLiteral& getIntLiteral() { return hstd::variant_get<2>(data); }
    bool isFloatLiteral() const { return getKind() == Kind::FloatLiteral; }
    org::sem::Tblfm::Expr::FloatLiteral const& getFloatLiteral() const { return hstd::variant_get<3>(data); }
    org::sem::Tblfm::Expr::FloatLiteral& getFloatLiteral() { return hstd::variant_get<3>(data); }
    bool isRangeRef() const { return getKind() == Kind::RangeRef; }
    org::sem::Tblfm::Expr::RangeRef const& getRangeRef() const { return hstd::variant_get<4>(data); }
    org::sem::Tblfm::Expr::RangeRef& getRangeRef() { return hstd::variant_get<4>(data); }
    bool isCall() const { return getKind() == Kind::Call; }
    org::sem::Tblfm::Expr::Call const& getCall() const { return hstd::variant_get<5>(data); }
    org::sem::Tblfm::Expr::Call& getCall() { return hstd::variant_get<5>(data); }
    bool isElisp() const { return getKind() == Kind::Elisp; }
    org::sem::Tblfm::Expr::Elisp const& getElisp() const { return hstd::variant_get<6>(data); }
    org::sem::Tblfm::Expr::Elisp& getElisp() { return hstd::variant_get<6>(data); }
    static org::sem::Tblfm::Expr::Kind getKind(org::sem::Tblfm::Expr::Data const& __input) { return static_cast<org::sem::Tblfm::Expr::Kind>(__input.index()); }
    org::sem::Tblfm::Expr::Kind getKind() const { return getKind(data); }
    char const* sub_variant_get_name() const { return "data"; }
    org::sem::Tblfm::Expr::Data const& sub_variant_get_data() const { return data; }
    org::sem::Tblfm::Expr::Kind sub_variant_get_kind() const { return getKind(); }
  };

  struct Assign {
    /// \brief Flags for table format expression cell formulas
    enum class Flag : short int {
      /// \brief Left-align the result
      CellLeftAlign,
      /// \brief Right-align the result
      CellRightAlign,
      /// \brief Center-align the result
      CellCenterAlign,
      /// \brief Convert result to number/currency format
      CellNumber,
      /// \brief Use exponential notation for numbers
      CellExponential,
      /// \brief Use floating point format
      CellFloating,
      /// \brief Unformat values before calculating
      CellUnformat,
      /// \brief Convert result to text
      CellText,
      /// \brief Display boolean values as t/nil
      CellBool,
      /// \brief Fixed format with specified decimal places (e.g., ;D2)
      CellDecimal,
      /// \brief Percentage format
      CellPercentage,
      /// \brief Convert to hours/minutes (HH:MM)
      CellHours,
      /// \brief Display zero as empty cell
      CellZero,
      /// \brief Mark field as invalid if conversion fails
      CellMarkInvalid,
      /// \brief Quote field contents
      CellQuote,
    };
    BOOST_DESCRIBE_NESTED_ENUM(Flag, CellLeftAlign, CellRightAlign, CellCenterAlign, CellNumber, CellExponential, CellFloating, CellUnformat, CellText, CellBool, CellDecimal, CellPercentage, CellHours, CellZero, CellMarkInvalid, CellQuote)
    BOOST_DESCRIBE_CLASS(Assign,
                         (),
                         (),
                         (),
                         (target, expr, flags))
    org::sem::Tblfm::Expr::AxisRef target;
    hstd::Vec<org::sem::Tblfm::Expr> expr = {};
    hstd::Vec<org::sem::Tblfm::Assign::Flag> flags = {};
    bool operator==(org::sem::Tblfm::Assign const& other) const;
  };

  BOOST_DESCRIBE_CLASS(Tblfm,
                       (),
                       (),
                       (),
                       (exprs))
  hstd::Vec<org::sem::Tblfm::Assign> exprs = {};
  bool operator==(org::sem::Tblfm const& other) const;
};

struct AttrValue {
  struct DimensionSpan {
    BOOST_DESCRIBE_CLASS(DimensionSpan,
                         (),
                         (),
                         (),
                         (first, last))
    int first;
    hstd::Opt<int> last = std::nullopt;
    DimensionSpan() {  }
    bool operator==(org::sem::AttrValue::DimensionSpan const& other) const;
  };

  struct TextValue {
    BOOST_DESCRIBE_CLASS(TextValue,
                         (),
                         (),
                         (),
                         (value))
    hstd::Str value = "";
    bool operator==(org::sem::AttrValue::TextValue const& other) const;
    TextValue() {  }
  };

  struct FileReference {
    BOOST_DESCRIBE_CLASS(FileReference,
                         (),
                         (),
                         (),
                         (file, reference))
    hstd::Str file = "";
    hstd::Str reference = "";
    FileReference() {  }
    bool operator==(org::sem::AttrValue::FileReference const& other) const;
  };

  struct LispValue {
    BOOST_DESCRIBE_CLASS(LispValue,
                         (),
                         (),
                         (),
                         (code))
    org::sem::LispCode code;
    bool operator==(org::sem::AttrValue::LispValue const& other) const;
    LispValue() {  }
  };

  using DataVariant = std::variant<org::sem::AttrValue::TextValue, org::sem::AttrValue::FileReference, org::sem::AttrValue::LispValue>;
  enum class Kind : short int { TextValue, FileReference, LispValue, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, TextValue, FileReference, LispValue)
  using variant_enum_type = org::sem::AttrValue::Kind;
  using variant_data_type = org::sem::AttrValue::DataVariant;
  BOOST_DESCRIBE_CLASS(AttrValue,
                       (),
                       (),
                       (),
                       (name,
                        varname,
                        span,
                        isQuoted,
                        data))
  hstd::Opt<hstd::Str> name = std::nullopt;
  hstd::Opt<hstd::Str> varname = std::nullopt;
  hstd::Vec<org::sem::AttrValue::DimensionSpan> span = {};
  /// \brief If the original value was explicitly quoted in the org-mode code
  bool isQuoted = false;
  org::sem::AttrValue::DataVariant data;
  hstd::Opt<bool> getBool() const;
  hstd::Opt<int> getInt() const;
  hstd::Str getString() const;
  hstd::Opt<double> getDouble() const;
  bool operator==(org::sem::AttrValue const& other) const;
  AttrValue() {  }
  bool isTextValue() const { return getKind() == Kind::TextValue; }
  org::sem::AttrValue::TextValue const& getTextValue() const { return hstd::variant_get<0>(data); }
  org::sem::AttrValue::TextValue& getTextValue() { return hstd::variant_get<0>(data); }
  bool isFileReference() const { return getKind() == Kind::FileReference; }
  org::sem::AttrValue::FileReference const& getFileReference() const { return hstd::variant_get<1>(data); }
  org::sem::AttrValue::FileReference& getFileReference() { return hstd::variant_get<1>(data); }
  bool isLispValue() const { return getKind() == Kind::LispValue; }
  org::sem::AttrValue::LispValue const& getLispValue() const { return hstd::variant_get<2>(data); }
  org::sem::AttrValue::LispValue& getLispValue() { return hstd::variant_get<2>(data); }
  static org::sem::AttrValue::Kind getKind(org::sem::AttrValue::DataVariant const& __input) { return static_cast<org::sem::AttrValue::Kind>(__input.index()); }
  org::sem::AttrValue::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::AttrValue::DataVariant const& sub_variant_get_data() const { return data; }
  org::sem::AttrValue::Kind sub_variant_get_kind() const { return getKind(); }
};

struct HashTagFlat {
  BOOST_DESCRIBE_CLASS(HashTagFlat,
                       (),
                       (),
                       (),
                       (tags))
  hstd::Vec<hstd::Str> tags = {};
  bool operator==(org::sem::HashTagFlat const& other) const;
  bool operator<(org::sem::HashTagFlat const& other) const;
};

struct TodoKeyword {
  enum class Transition : short int { None, NoteWithTimestamp, Timestamp, };
  BOOST_DESCRIBE_NESTED_ENUM(Transition, None, NoteWithTimestamp, Timestamp)
  BOOST_DESCRIBE_CLASS(TodoKeyword,
                       (),
                       (),
                       (),
                       (name, shortcut, onEnter, onLeave))
  hstd::Str name = "";
  hstd::Opt<hstd::Str> shortcut = std::nullopt;
  org::sem::TodoKeyword::Transition onEnter;
  org::sem::TodoKeyword::Transition onLeave;
  bool operator==(org::sem::TodoKeyword const& other) const;
};

/// \brief Single or nested inline hash-tag
struct HashTagText {
  BOOST_DESCRIBE_CLASS(HashTagText,
                       (),
                       (),
                       (),
                       (head,
                        subtags))
  /// \brief Main part of the tag
  hstd::Str head;
  /// \brief List of nested tags
  hstd::Vec<org::sem::HashTagText> subtags = {};
  bool operator==(org::sem::HashTagText const& other) const;
  /// \brief Check if list of tag names is a prefix for either of the nested hash tags in this one
  bool prefixMatch(hstd::Vec<hstd::Str> const& prefix) const;
  /// \brief Get flat list of expanded hashtags
  hstd::Vec<org::sem::HashTagFlat> getFlatHashes(bool withIntermediate = true) const;
};

struct SubtreePath {
  BOOST_DESCRIBE_CLASS(SubtreePath,
                       (),
                       (),
                       (),
                       (path))
  hstd::Vec<hstd::Str> path = {};
  bool operator==(org::sem::SubtreePath const& other) const;
};

struct LinkTarget {
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw,
                         (),
                         (),
                         (),
                         (text))
    hstd::Str text;
    bool operator==(org::sem::LinkTarget::Raw const& other) const;
  };

  struct Id {
    BOOST_DESCRIBE_CLASS(Id,
                         (),
                         (),
                         (),
                         (text))
    hstd::Str text;
    bool operator==(org::sem::LinkTarget::Id const& other) const;
  };

  struct CustomId {
    BOOST_DESCRIBE_CLASS(CustomId,
                         (),
                         (),
                         (),
                         (text))
    hstd::Str text;
    bool operator==(org::sem::LinkTarget::CustomId const& other) const;
  };

  struct SubtreeTitle {
    BOOST_DESCRIBE_CLASS(SubtreeTitle,
                         (),
                         (),
                         (),
                         (title, level))
    org::sem::SubtreePath title;
    int level;
    bool operator==(org::sem::LinkTarget::SubtreeTitle const& other) const;
  };

  struct Person {
    BOOST_DESCRIBE_CLASS(Person,
                         (),
                         (),
                         (),
                         (name))
    hstd::Str name;
    bool operator==(org::sem::LinkTarget::Person const& other) const;
  };

  struct UserProtocol {
    BOOST_DESCRIBE_CLASS(UserProtocol,
                         (),
                         (),
                         (),
                         (protocol, target))
    hstd::Str protocol;
    hstd::Str target;
    bool operator==(org::sem::LinkTarget::UserProtocol const& other) const;
  };

  struct Internal {
    BOOST_DESCRIBE_CLASS(Internal,
                         (),
                         (),
                         (),
                         (target))
    hstd::Str target;
    bool operator==(org::sem::LinkTarget::Internal const& other) const;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote,
                         (),
                         (),
                         (),
                         (target))
    hstd::Str target;
    bool operator==(org::sem::LinkTarget::Footnote const& other) const;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File,
                         (),
                         (),
                         (),
                         (file))
    hstd::Str file;
    bool operator==(org::sem::LinkTarget::File const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         (file))
    hstd::Str file;
    bool operator==(org::sem::LinkTarget::Attachment const& other) const;
  };

  using Data = std::variant<org::sem::LinkTarget::Raw, org::sem::LinkTarget::Id, org::sem::LinkTarget::CustomId, org::sem::LinkTarget::SubtreeTitle, org::sem::LinkTarget::Person, org::sem::LinkTarget::UserProtocol, org::sem::LinkTarget::Internal, org::sem::LinkTarget::Footnote, org::sem::LinkTarget::File, org::sem::LinkTarget::Attachment>;
  enum class Kind : short int { Raw, Id, CustomId, SubtreeTitle, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, CustomId, SubtreeTitle, Person, UserProtocol, Internal, Footnote, File, Attachment)
  using variant_enum_type = org::sem::LinkTarget::Kind;
  using variant_data_type = org::sem::LinkTarget::Data;
  BOOST_DESCRIBE_CLASS(LinkTarget,
                       (),
                       (),
                       (),
                       (data))
  org::sem::LinkTarget::Data data;
  bool operator==(org::sem::LinkTarget const& other) const;
  bool isRaw() const { return getKind() == Kind::Raw; }
  org::sem::LinkTarget::Raw const& getRaw() const { return hstd::variant_get<0>(data); }
  org::sem::LinkTarget::Raw& getRaw() { return hstd::variant_get<0>(data); }
  bool isId() const { return getKind() == Kind::Id; }
  org::sem::LinkTarget::Id const& getId() const { return hstd::variant_get<1>(data); }
  org::sem::LinkTarget::Id& getId() { return hstd::variant_get<1>(data); }
  bool isCustomId() const { return getKind() == Kind::CustomId; }
  org::sem::LinkTarget::CustomId const& getCustomId() const { return hstd::variant_get<2>(data); }
  org::sem::LinkTarget::CustomId& getCustomId() { return hstd::variant_get<2>(data); }
  bool isSubtreeTitle() const { return getKind() == Kind::SubtreeTitle; }
  org::sem::LinkTarget::SubtreeTitle const& getSubtreeTitle() const { return hstd::variant_get<3>(data); }
  org::sem::LinkTarget::SubtreeTitle& getSubtreeTitle() { return hstd::variant_get<3>(data); }
  bool isPerson() const { return getKind() == Kind::Person; }
  org::sem::LinkTarget::Person const& getPerson() const { return hstd::variant_get<4>(data); }
  org::sem::LinkTarget::Person& getPerson() { return hstd::variant_get<4>(data); }
  bool isUserProtocol() const { return getKind() == Kind::UserProtocol; }
  org::sem::LinkTarget::UserProtocol const& getUserProtocol() const { return hstd::variant_get<5>(data); }
  org::sem::LinkTarget::UserProtocol& getUserProtocol() { return hstd::variant_get<5>(data); }
  bool isInternal() const { return getKind() == Kind::Internal; }
  org::sem::LinkTarget::Internal const& getInternal() const { return hstd::variant_get<6>(data); }
  org::sem::LinkTarget::Internal& getInternal() { return hstd::variant_get<6>(data); }
  bool isFootnote() const { return getKind() == Kind::Footnote; }
  org::sem::LinkTarget::Footnote const& getFootnote() const { return hstd::variant_get<7>(data); }
  org::sem::LinkTarget::Footnote& getFootnote() { return hstd::variant_get<7>(data); }
  bool isFile() const { return getKind() == Kind::File; }
  org::sem::LinkTarget::File const& getFile() const { return hstd::variant_get<8>(data); }
  org::sem::LinkTarget::File& getFile() { return hstd::variant_get<8>(data); }
  bool isAttachment() const { return getKind() == Kind::Attachment; }
  org::sem::LinkTarget::Attachment const& getAttachment() const { return hstd::variant_get<9>(data); }
  org::sem::LinkTarget::Attachment& getAttachment() { return hstd::variant_get<9>(data); }
  static org::sem::LinkTarget::Kind getKind(org::sem::LinkTarget::Data const& __input) { return static_cast<org::sem::LinkTarget::Kind>(__input.index()); }
  org::sem::LinkTarget::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::LinkTarget::Data const& sub_variant_get_data() const { return data; }
  org::sem::LinkTarget::Kind sub_variant_get_kind() const { return getKind(); }
};

struct SubtreeLogHead {
  /// \brief Priority added
  struct Priority {
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
                         (),
                         (),
                         (),
                         (oldPriority, newPriority, on, action))
    /// \brief Previous priority for change and removal
    hstd::Opt<std::string> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    hstd::Opt<std::string> newPriority = std::nullopt;
    /// \brief When priority was changed
    hstd::UserTime on;
    /// \brief Which action taken
    org::sem::SubtreeLogHead::Priority::Action action;
    bool operator==(org::sem::SubtreeLogHead::Priority const& other) const;
  };

  /// \brief Timestamped note
  struct Note {
    Note() {}
    BOOST_DESCRIBE_CLASS(Note,
                         (),
                         (),
                         (),
                         (on))
    /// \brief Where log was taken
    hstd::UserTime on;
    bool operator==(org::sem::SubtreeLogHead::Note const& other) const;
  };

  /// \brief Refiling action
  struct Refile {
    Refile() {}
    BOOST_DESCRIBE_CLASS(Refile,
                         (),
                         (),
                         (),
                         (on, from))
    /// \brief When the refiling happened
    hstd::UserTime on;
    /// \brief Link to the original subtree
    org::sem::LinkTarget from;
    bool operator==(org::sem::SubtreeLogHead::Refile const& other) const;
  };

  /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`
  struct Clock {
    Clock() {}
    BOOST_DESCRIBE_CLASS(Clock,
                         (),
                         (),
                         (),
                         (from, to))
    /// \brief Clock start time
    hstd::UserTime from;
    /// \brief Optional end of the clock
    hstd::Opt<hstd::UserTime> to = std::nullopt;
    bool operator==(org::sem::SubtreeLogHead::Clock const& other) const;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State {
    State() {}
    BOOST_DESCRIBE_CLASS(State,
                         (),
                         (),
                         (),
                         (from, to, on))
    hstd::Str from;
    hstd::Str to;
    hstd::UserTime on;
    bool operator==(org::sem::SubtreeLogHead::State const& other) const;
  };

  /// \brief Change of the subtree deadline
  struct Deadline {
    Deadline() {}
    BOOST_DESCRIBE_CLASS(Deadline,
                         (),
                         (),
                         (),
                         (from, to, on))
    hstd::Opt<hstd::UserTime> from = std::nullopt;
    hstd::UserTime to;
    hstd::UserTime on;
    bool operator==(org::sem::SubtreeLogHead::Deadline const& other) const;
  };

  /// \brief Change of the subtree Schedule
  struct Schedule {
    Schedule() {}
    BOOST_DESCRIBE_CLASS(Schedule,
                         (),
                         (),
                         (),
                         (from, to, on))
    hstd::Opt<hstd::UserTime> from = std::nullopt;
    hstd::UserTime to;
    hstd::UserTime on;
    bool operator==(org::sem::SubtreeLogHead::Schedule const& other) const;
  };

  /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on [2023-04-30 Sun 13:29:06]`
  struct Tag {
    Tag() {}
    BOOST_DESCRIBE_CLASS(Tag,
                         (),
                         (),
                         (),
                         (on, tag, added))
    /// \brief When the log was assigned
    hstd::UserTime on;
    /// \brief Tag in question
    org::sem::HashTagText tag;
    /// \brief Added/removed?
    bool added = false;
    bool operator==(org::sem::SubtreeLogHead::Tag const& other) const;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown {
    Unknown() {}
    BOOST_DESCRIBE_CLASS(Unknown,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::SubtreeLogHead::Unknown const& other) const;
  };

  using LogEntry = std::variant<org::sem::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::State, org::sem::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Deadline, Schedule, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Deadline, Schedule, Tag, Unknown)
  using variant_enum_type = org::sem::SubtreeLogHead::Kind;
  using variant_data_type = org::sem::SubtreeLogHead::LogEntry;
  BOOST_DESCRIBE_CLASS(SubtreeLogHead,
                       (),
                       (),
                       (),
                       (log))
  org::sem::SubtreeLogHead::LogEntry log = Note{};
  bool operator==(org::sem::SubtreeLogHead const& other) const;
  bool isPriority() const { return getLogKind() == Kind::Priority; }
  org::sem::SubtreeLogHead::Priority const& getPriority() const { return hstd::variant_get<0>(log); }
  org::sem::SubtreeLogHead::Priority& getPriority() { return hstd::variant_get<0>(log); }
  bool isNote() const { return getLogKind() == Kind::Note; }
  org::sem::SubtreeLogHead::Note const& getNote() const { return hstd::variant_get<1>(log); }
  org::sem::SubtreeLogHead::Note& getNote() { return hstd::variant_get<1>(log); }
  bool isRefile() const { return getLogKind() == Kind::Refile; }
  org::sem::SubtreeLogHead::Refile const& getRefile() const { return hstd::variant_get<2>(log); }
  org::sem::SubtreeLogHead::Refile& getRefile() { return hstd::variant_get<2>(log); }
  bool isClock() const { return getLogKind() == Kind::Clock; }
  org::sem::SubtreeLogHead::Clock const& getClock() const { return hstd::variant_get<3>(log); }
  org::sem::SubtreeLogHead::Clock& getClock() { return hstd::variant_get<3>(log); }
  bool isState() const { return getLogKind() == Kind::State; }
  org::sem::SubtreeLogHead::State const& getState() const { return hstd::variant_get<4>(log); }
  org::sem::SubtreeLogHead::State& getState() { return hstd::variant_get<4>(log); }
  bool isDeadline() const { return getLogKind() == Kind::Deadline; }
  org::sem::SubtreeLogHead::Deadline const& getDeadline() const { return hstd::variant_get<5>(log); }
  org::sem::SubtreeLogHead::Deadline& getDeadline() { return hstd::variant_get<5>(log); }
  bool isSchedule() const { return getLogKind() == Kind::Schedule; }
  org::sem::SubtreeLogHead::Schedule const& getSchedule() const { return hstd::variant_get<6>(log); }
  org::sem::SubtreeLogHead::Schedule& getSchedule() { return hstd::variant_get<6>(log); }
  bool isTag() const { return getLogKind() == Kind::Tag; }
  org::sem::SubtreeLogHead::Tag const& getTag() const { return hstd::variant_get<7>(log); }
  org::sem::SubtreeLogHead::Tag& getTag() { return hstd::variant_get<7>(log); }
  bool isUnknown() const { return getLogKind() == Kind::Unknown; }
  org::sem::SubtreeLogHead::Unknown const& getUnknown() const { return hstd::variant_get<8>(log); }
  org::sem::SubtreeLogHead::Unknown& getUnknown() { return hstd::variant_get<8>(log); }
  static org::sem::SubtreeLogHead::Kind getLogKind(org::sem::SubtreeLogHead::LogEntry const& __input) { return static_cast<org::sem::SubtreeLogHead::Kind>(__input.index()); }
  org::sem::SubtreeLogHead::Kind getLogKind() const { return getLogKind(log); }
  char const* sub_variant_get_name() const { return "log"; }
  org::sem::SubtreeLogHead::LogEntry const& sub_variant_get_data() const { return log; }
  org::sem::SubtreeLogHead::Kind sub_variant_get_kind() const { return getLogKind(); }
};

/// \brief Completion status of the subtree list element
struct SubtreeCompletion {
  BOOST_DESCRIBE_CLASS(SubtreeCompletion,
                       (),
                       (),
                       (),
                       (done, full, isPercent))
  /// \brief Number of completed tasks
  int done = 0;
  /// \brief Full number of tasks
  int full = 0;
  /// \brief Use fraction or percent to display completion
  bool isPercent = false;
  bool operator==(org::sem::SubtreeCompletion const& other) const;
};

struct AttrList {
  BOOST_DESCRIBE_CLASS(AttrList,
                       (),
                       (),
                       (),
                       (items))
  hstd::Vec<org::sem::AttrValue> items = {};
  bool operator==(org::sem::AttrList const& other) const;
};

struct AttrGroup {
  BOOST_DESCRIBE_CLASS(AttrGroup,
                       (),
                       (),
                       (),
                       (positional,
                        named))
  /// \brief Positional arguments with no keys
  org::sem::AttrList positional;
  /// \brief Stored key-value mapping
  hstd::UnorderedMap<hstd::Str, org::sem::AttrList> named;
  hstd::Vec<org::sem::AttrValue> getFlatArgs() const;
  hstd::Vec<org::sem::AttrValue> getAttrs(hstd::Opt<hstd::Str> const& key = std::nullopt) const;
  void setNamedAttr(hstd::Str const& key, hstd::Vec<org::sem::AttrValue> const& attrs);
  void setPositionalAttr(hstd::Vec<org::sem::AttrValue> const& items);
  int getPositionalSize() const;
  int getNamedSize() const;
  bool isEmpty() const;
  org::sem::AttrList getAll() const;
  org::sem::AttrValue const& atPositional(int index) const;
  hstd::Opt<org::sem::AttrValue> getPositional(int index) const;
  org::sem::AttrList const& atNamed(hstd::Str const& index) const;
  hstd::Opt<org::sem::AttrList> getNamed(hstd::Str const& index) const;
  org::sem::AttrValue const& atFirstNamed(hstd::Str const& index) const;
  hstd::Opt<org::sem::AttrValue> getFirstNamed(hstd::Str const& index) const;
  org::sem::AttrList atVarNamed(hstd::Str const& index) const;
  hstd::Opt<org::sem::AttrList> getVarNamed(hstd::Str const& index) const;
  org::sem::AttrValue atFirstVarNamed(hstd::Str const& index) const;
  hstd::Opt<org::sem::AttrValue> getFirstVarNamed(hstd::Str const& index) const;
  bool operator==(org::sem::AttrGroup const& other) const;
};

struct OrgCodeEvalInput {
  struct Var {
    BOOST_DESCRIBE_CLASS(Var,
                         (),
                         (),
                         (),
                         (name, value))
    hstd::Str name = "";
    org::sem::OrgJson value;
    bool operator==(org::sem::OrgCodeEvalInput::Var const& other) const;
    Var() {  }
  };

  /// \brief What context to use for results
  enum class ResultType : short int {
    None,
    /// \brief Interpret the results as an Org table. If the result is a single value, create a table with one row and one column.
    Table,
    /// \brief Interpret the results as an Org list. If the result is a single value, create a list of one element.
    List,
    /// \brief Interpret literally and insert as quoted text. Do not create a table.
    Scalar,
    /// \brief Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it.
    SaveFile,
  };
  BOOST_DESCRIBE_NESTED_ENUM(ResultType, None, Table, List, Scalar, SaveFile)
  /// \brief How to interpret output from the script
  enum class ResultFormat : short int {
    None,
    /// \brief Interpreted as raw Org mode. Inserted directly into the buffer.
    Raw,
    /// \brief Result enclosed in a code block.
    Code,
    /// \brief Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing.
    Drawer,
    /// \brief Results enclosed in a ‘BEGIN_EXPORT’ block.
    ExportType,
    Link,
  };
  BOOST_DESCRIBE_NESTED_ENUM(ResultFormat, None, Raw, Code, Drawer, ExportType, Link)
  /// \brief What to do with the final evaluation results
  enum class ResultHandling : short int { None, Replace, Silent, Discard, Append, Prepend, };
  BOOST_DESCRIBE_NESTED_ENUM(ResultHandling, None, Replace, Silent, Discard, Append, Prepend)
  BOOST_DESCRIBE_CLASS(OrgCodeEvalInput,
                       (),
                       (),
                       (),
                       (blockAttrs,
                        tangledCode,
                        exportType,
                        resultType,
                        resultFormat,
                        resultHandling,
                        language,
                        argList))
  org::sem::AttrGroup blockAttrs;
  hstd::Str tangledCode;
  hstd::Opt<hstd::Str> exportType = std::nullopt;
  org::sem::OrgCodeEvalInput::ResultType resultType = ResultType::None;
  org::sem::OrgCodeEvalInput::ResultFormat resultFormat = ResultFormat::None;
  org::sem::OrgCodeEvalInput::ResultHandling resultHandling = ResultHandling::None;
  hstd::Str language = "";
  hstd::Vec<org::sem::OrgCodeEvalInput::Var> argList = {};
  bool operator==(org::sem::OrgCodeEvalInput const& other) const;
  hstd::Opt<org::sem::OrgCodeEvalInput::Var> getVariable(hstd::Str const& name) const;
};

/// \brief Single command/subprocess executed to evaluate org babel code entry
struct OrgCodeEvalOutput {
  BOOST_DESCRIBE_CLASS(OrgCodeEvalOutput,
                       (),
                       (),
                       (),
                       (stdoutText,
                        stderrText,
                        code,
                        cmd,
                        args,
                        cwd,
                        appliedHeaderArg))
  hstd::Str stdoutText = "";
  hstd::Str stderrText = "";
  int code;
  /// \brief Command evaluated, if none then eval output did not run CLI subprocess
  hstd::Opt<hstd::Str> cmd = std::nullopt;
  /// \brief Command line arguments provided for execution
  hstd::Vec<hstd::Str> args = {};
  /// \brief Working directory where command was executed
  hstd::Str cwd = "";
  /// \brief Final set of header arguments applied during evaluation
  org::sem::AttrGroup appliedHeaderArg;
  bool operator==(org::sem::OrgCodeEvalOutput const& other) const;
};

struct ColumnView {
  struct Summary {
    struct CheckboxAggregate {
      enum class Kind : short int { IfAllNested, AggregateFractionRec, AggregatePercentRec, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, IfAllNested, AggregateFractionRec, AggregatePercentRec)
      BOOST_DESCRIBE_CLASS(CheckboxAggregate,
                           (),
                           (),
                           (),
                           (kind))
      org::sem::ColumnView::Summary::CheckboxAggregate::Kind kind;
      bool operator==(org::sem::ColumnView::Summary::CheckboxAggregate const& other) const;
    };

    struct MathAggregate {
      enum class Kind : short int { Min, Max, Mean, Sum, LowHighEst, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Min, Max, Mean, Sum, LowHighEst)
      BOOST_DESCRIBE_CLASS(MathAggregate,
                           (),
                           (),
                           (),
                           (kind, formatDigits, formatPrecision))
      org::sem::ColumnView::Summary::MathAggregate::Kind kind;
      hstd::Opt<int> formatDigits = std::nullopt;
      hstd::Opt<int> formatPrecision = std::nullopt;
      bool operator==(org::sem::ColumnView::Summary::MathAggregate const& other) const;
    };

    using Data = std::variant<org::sem::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::MathAggregate>;
    enum class Kind : short int { CheckboxAggregate, MathAggregate, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, CheckboxAggregate, MathAggregate)
    using variant_enum_type = org::sem::ColumnView::Summary::Kind;
    using variant_data_type = org::sem::ColumnView::Summary::Data;
    BOOST_DESCRIBE_CLASS(Summary,
                         (),
                         (),
                         (),
                         (data))
    org::sem::ColumnView::Summary::Data data;
    bool operator==(org::sem::ColumnView::Summary const& other) const;
    bool isCheckboxAggregate() const { return getKind() == Kind::CheckboxAggregate; }
    org::sem::ColumnView::Summary::CheckboxAggregate const& getCheckboxAggregate() const { return hstd::variant_get<0>(data); }
    org::sem::ColumnView::Summary::CheckboxAggregate& getCheckboxAggregate() { return hstd::variant_get<0>(data); }
    bool isMathAggregate() const { return getKind() == Kind::MathAggregate; }
    org::sem::ColumnView::Summary::MathAggregate const& getMathAggregate() const { return hstd::variant_get<1>(data); }
    org::sem::ColumnView::Summary::MathAggregate& getMathAggregate() { return hstd::variant_get<1>(data); }
    static org::sem::ColumnView::Summary::Kind getKind(org::sem::ColumnView::Summary::Data const& __input) { return static_cast<org::sem::ColumnView::Summary::Kind>(__input.index()); }
    org::sem::ColumnView::Summary::Kind getKind() const { return getKind(data); }
    char const* sub_variant_get_name() const { return "data"; }
    org::sem::ColumnView::Summary::Data const& sub_variant_get_data() const { return data; }
    org::sem::ColumnView::Summary::Kind sub_variant_get_kind() const { return getKind(); }
  };

  struct Column {
    BOOST_DESCRIBE_CLASS(Column,
                         (),
                         (),
                         (),
                         (summary, width, property, propertyTitle))
    hstd::Opt<org::sem::ColumnView::Summary> summary = std::nullopt;
    hstd::Opt<int> width = std::nullopt;
    hstd::Opt<hstd::Str> property = std::nullopt;
    hstd::Opt<hstd::Str> propertyTitle = std::nullopt;
    bool operator==(org::sem::ColumnView::Column const& other) const;
  };

  BOOST_DESCRIBE_CLASS(ColumnView,
                       (),
                       (),
                       (),
                       (columns))
  hstd::Vec<org::sem::ColumnView::Column> columns = {};
  bool operator==(org::sem::ColumnView const& other) const;
};

struct BlockCodeLine {
  struct Part {
    struct Raw {
      BOOST_DESCRIBE_CLASS(Raw,
                           (),
                           (),
                           (),
                           (code))
      hstd::Str code;
      bool operator==(org::sem::BlockCodeLine::Part::Raw const& other) const;
    };

    struct Callout {
      BOOST_DESCRIBE_CLASS(Callout,
                           (),
                           (),
                           (),
                           (name))
      hstd::Str name;
      bool operator==(org::sem::BlockCodeLine::Part::Callout const& other) const;
    };

    struct Tangle {
      BOOST_DESCRIBE_CLASS(Tangle,
                           (),
                           (),
                           (),
                           (target))
      hstd::Str target;
      bool operator==(org::sem::BlockCodeLine::Part::Tangle const& other) const;
    };

    using Data = std::variant<org::sem::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Tangle>;
    enum class Kind : short int { Raw, Callout, Tangle, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
    using variant_enum_type = org::sem::BlockCodeLine::Part::Kind;
    using variant_data_type = org::sem::BlockCodeLine::Part::Data;
    BOOST_DESCRIBE_CLASS(Part,
                         (),
                         (),
                         (),
                         (data))
    org::sem::BlockCodeLine::Part::Data data;
    bool operator==(org::sem::BlockCodeLine::Part const& other) const;
    bool isRaw() const { return getKind() == Kind::Raw; }
    org::sem::BlockCodeLine::Part::Raw const& getRaw() const { return hstd::variant_get<0>(data); }
    org::sem::BlockCodeLine::Part::Raw& getRaw() { return hstd::variant_get<0>(data); }
    bool isCallout() const { return getKind() == Kind::Callout; }
    org::sem::BlockCodeLine::Part::Callout const& getCallout() const { return hstd::variant_get<1>(data); }
    org::sem::BlockCodeLine::Part::Callout& getCallout() { return hstd::variant_get<1>(data); }
    bool isTangle() const { return getKind() == Kind::Tangle; }
    org::sem::BlockCodeLine::Part::Tangle const& getTangle() const { return hstd::variant_get<2>(data); }
    org::sem::BlockCodeLine::Part::Tangle& getTangle() { return hstd::variant_get<2>(data); }
    static org::sem::BlockCodeLine::Part::Kind getKind(org::sem::BlockCodeLine::Part::Data const& __input) { return static_cast<org::sem::BlockCodeLine::Part::Kind>(__input.index()); }
    org::sem::BlockCodeLine::Part::Kind getKind() const { return getKind(data); }
    char const* sub_variant_get_name() const { return "data"; }
    org::sem::BlockCodeLine::Part::Data const& sub_variant_get_data() const { return data; }
    org::sem::BlockCodeLine::Part::Kind sub_variant_get_kind() const { return getKind(); }
  };

  BOOST_DESCRIBE_CLASS(BlockCodeLine,
                       (),
                       (),
                       (),
                       (parts))
  /// \brief parts of the single line
  hstd::Vec<org::sem::BlockCodeLine::Part> parts = {};
  bool operator==(org::sem::BlockCodeLine const& other) const;
};

struct DocumentExportConfig {
  struct TaskExport {
    BOOST_DESCRIBE_CLASS(TaskExport,
                         (),
                         (),
                         (),
                         (taskWhitelist))
    hstd::Vec<hstd::Str> taskWhitelist = {};
    bool operator==(org::sem::DocumentExportConfig::TaskExport const& other) const;
  };

  enum class TagExport : short int {
    None,
    All,
    /// \brief Export tags in subtree titles but not in the table of content
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
  enum class BrokenLinks : short int { None, Mark, Raise, Ignore, };
  BOOST_DESCRIBE_NESTED_ENUM(BrokenLinks, None, Mark, Raise, Ignore)
  /// \brief Configure how archived trees are exported
  enum class ArchivedTrees : short int {
    /// \brief Skip archived trees entirely
    Skip,
    /// \brief Export only headlines of archived trees
    Headline,
    /// \brief Export archived trees with full content
    All,
  };
  BOOST_DESCRIBE_NESTED_ENUM(ArchivedTrees, Skip, Headline, All)
  struct DoExport {
    BOOST_DESCRIBE_CLASS(DoExport,
                         (),
                         (),
                         (),
                         (exportToc))
    bool exportToc;
    bool operator==(org::sem::DocumentExportConfig::DoExport const& other) const;
  };

  struct ExportFixed {
    BOOST_DESCRIBE_CLASS(ExportFixed,
                         (),
                         (),
                         (),
                         (exportLevels))
    int exportLevels;
    bool operator==(org::sem::DocumentExportConfig::ExportFixed const& other) const;
  };

  using TocExport = std::variant<org::sem::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::ExportFixed>;
  enum class TocExportKind : short int { DoExport, ExportFixed, };
  BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
  using variant_enum_type = org::sem::DocumentExportConfig::TocExportKind;
  using variant_data_type = org::sem::DocumentExportConfig::TocExport;
  BOOST_DESCRIBE_CLASS(DocumentExportConfig,
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
                        smartQuotes,
                        fixedWidth,
                        timestamps,
                        preserveBreaks,
                        subSuperscripts,
                        expandLinks,
                        creator,
                        drawers,
                        date,
                        entities,
                        email,
                        sectionNumbers,
                        planning,
                        priority,
                        latex,
                        timestamp,
                        title,
                        tables,
                        headlineLevels,
                        brokenLinks,
                        tocExport,
                        tagExport,
                        taskFiltering,
                        archivedTrees,
                        data))
  /// \brief Toggle inclusion of inlinetasks
  hstd::Opt<bool> inlinetasks = std::nullopt;
  /// \brief Toggle the inclusion of footnotes
  hstd::Opt<bool> footnotes = std::nullopt;
  /// \brief Toggle inclusion of 'CLOCK' keywords
  hstd::Opt<bool> clock = std::nullopt;
  /// \brief Toggle inclusion of author name into exported file
  hstd::Opt<bool> author = std::nullopt;
  /// \brief Toggle emphasized text
  hstd::Opt<bool> emphasis = std::nullopt;
  /// \brief Toggle conversion of special strings
  hstd::Opt<bool> specialStrings = std::nullopt;
  /// \brief Toggle inclusion of property drawers
  hstd::Opt<bool> propertyDrawers = std::nullopt;
  /// \brief Toggle inclusion of statistics cookies
  hstd::Opt<bool> statisticsCookies = std::nullopt;
  /// \brief Toggle inclusion of TODO keywords into exported text
  hstd::Opt<bool> todoText = std::nullopt;
  /// \brief Toggle smart quotes
  hstd::Opt<bool> smartQuotes = std::nullopt;
  /// \brief Toggle fixed-width sections
  hstd::Opt<bool> fixedWidth = std::nullopt;
  /// \brief Toggle inclusion of time/date active/inactive stamps
  hstd::Opt<bool> timestamps = std::nullopt;
  /// \brief Toggles whether to preserve line breaks
  hstd::Opt<bool> preserveBreaks = std::nullopt;
  /// \brief Toggle TeX-like syntax for sub- and superscripts
  hstd::Opt<bool> subSuperscripts = std::nullopt;
  /// \brief Toggle expansion of environment variables in file paths
  hstd::Opt<bool> expandLinks = std::nullopt;
  /// \brief Toggle inclusion of creator information in the exported file
  hstd::Opt<bool> creator = std::nullopt;
  /// \brief Toggle inclusion of drawers
  hstd::Opt<bool> drawers = std::nullopt;
  /// \brief Toggle inclusion of a date into exported file
  hstd::Opt<bool> date = std::nullopt;
  /// \brief Toggle inclusion of entities
  hstd::Opt<bool> entities = std::nullopt;
  /// \brief Toggle inclusion of the author's e-mail into exported file
  hstd::Opt<bool> email = std::nullopt;
  /// \brief Toggle section-numbers
  hstd::Opt<bool> sectionNumbers = std::nullopt;
  /// \brief Toggle export of planning information
  hstd::Opt<bool> planning = std::nullopt;
  /// \brief Toggle inclusion of priority cookies
  hstd::Opt<bool> priority = std::nullopt;
  /// \brief Toggle LaTeX export
  hstd::Opt<bool> latex = std::nullopt;
  /// \brief Toggle inclusion of the creation time in the exported file
  hstd::Opt<bool> timestamp = std::nullopt;
  /// \brief Toggle inclusion of title
  hstd::Opt<bool> title = std::nullopt;
  /// \brief Toggle inclusion of tables
  hstd::Opt<bool> tables = std::nullopt;
  /// \brief Set the number of headline levels for export
  hstd::Opt<int> headlineLevels = std::nullopt;
  org::sem::DocumentExportConfig::BrokenLinks brokenLinks = sem::DocumentExportConfig::BrokenLinks::None;
  org::sem::DocumentExportConfig::TocExport tocExport;
  org::sem::DocumentExportConfig::TagExport tagExport = org::sem::DocumentExportConfig::TagExport::NotInToc;
  org::sem::DocumentExportConfig::TaskFiltering taskFiltering = org::sem::DocumentExportConfig::TaskFiltering::All;
  org::sem::DocumentExportConfig::ArchivedTrees archivedTrees = org::sem::DocumentExportConfig::ArchivedTrees::Headline;
  org::sem::DocumentExportConfig::TocExport data;
  bool operator==(org::sem::DocumentExportConfig const& other) const;
  bool isDoExport() const { return getTocExportKind() == TocExportKind::DoExport; }
  org::sem::DocumentExportConfig::DoExport const& getDoExport() const { return hstd::variant_get<0>(data); }
  org::sem::DocumentExportConfig::DoExport& getDoExport() { return hstd::variant_get<0>(data); }
  bool isExportFixed() const { return getTocExportKind() == TocExportKind::ExportFixed; }
  org::sem::DocumentExportConfig::ExportFixed const& getExportFixed() const { return hstd::variant_get<1>(data); }
  org::sem::DocumentExportConfig::ExportFixed& getExportFixed() { return hstd::variant_get<1>(data); }
  static org::sem::DocumentExportConfig::TocExportKind getTocExportKind(org::sem::DocumentExportConfig::TocExport const& __input) { return static_cast<org::sem::DocumentExportConfig::TocExportKind>(__input.index()); }
  org::sem::DocumentExportConfig::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::DocumentExportConfig::TocExport const& sub_variant_get_data() const { return data; }
  org::sem::DocumentExportConfig::TocExportKind sub_variant_get_kind() const { return getTocExportKind(); }
};

/// \brief Type of the subtree associated time periods
struct SubtreePeriod {
  SubtreePeriod() {}
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
  BOOST_DESCRIBE_CLASS(SubtreePeriod,
                       (),
                       (),
                       (),
                       (kind, from, to))
  /// \brief Time period kind -- not associated with point/range distinction
  org::sem::SubtreePeriod::Kind kind;
  /// \brief Clock start time
  hstd::UserTime from;
  /// \brief Optional end of the clock
  hstd::Opt<hstd::UserTime> to = std::nullopt;
  bool operator==(org::sem::SubtreePeriod const& other) const;
};

/// \brief Single subtree property
struct NamedProperty {
  NamedProperty() {}
  struct Nonblocking {
    Nonblocking() {}
    BOOST_DESCRIBE_CLASS(Nonblocking,
                         (),
                         (),
                         (),
                         (isBlocking))
    bool isBlocking;
    bool operator==(org::sem::NamedProperty::Nonblocking const& other) const;
  };

  struct ArchiveTime {
    ArchiveTime() {}
    BOOST_DESCRIBE_CLASS(ArchiveTime,
                         (),
                         (),
                         (),
                         (time))
    hstd::UserTime time;
    bool operator==(org::sem::NamedProperty::ArchiveTime const& other) const;
  };

  struct ArchiveFile {
    ArchiveFile() {}
    BOOST_DESCRIBE_CLASS(ArchiveFile,
                         (),
                         (),
                         (),
                         (file))
    hstd::Str file;
    bool operator==(org::sem::NamedProperty::ArchiveFile const& other) const;
  };

  struct ArchiveOlpath {
    ArchiveOlpath() {}
    BOOST_DESCRIBE_CLASS(ArchiveOlpath,
                         (),
                         (),
                         (),
                         (path))
    org::sem::SubtreePath path;
    bool operator==(org::sem::NamedProperty::ArchiveOlpath const& other) const;
  };

  struct ArchiveTarget {
    ArchiveTarget() {}
    BOOST_DESCRIBE_CLASS(ArchiveTarget,
                         (),
                         (),
                         (),
                         (path, pattern))
    org::sem::SubtreePath path;
    hstd::Str pattern;
    bool operator==(org::sem::NamedProperty::ArchiveTarget const& other) const;
  };

  struct ArchiveCategory {
    ArchiveCategory() {}
    BOOST_DESCRIBE_CLASS(ArchiveCategory,
                         (),
                         (),
                         (),
                         (category))
    hstd::Str category;
    bool operator==(org::sem::NamedProperty::ArchiveCategory const& other) const;
  };

  struct ArchiveTodo {
    ArchiveTodo() {}
    BOOST_DESCRIBE_CLASS(ArchiveTodo,
                         (),
                         (),
                         (),
                         (todo))
    hstd::Str todo;
    bool operator==(org::sem::NamedProperty::ArchiveTodo const& other) const;
  };

  struct Trigger {
    Trigger() {}
    BOOST_DESCRIBE_CLASS(Trigger,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::NamedProperty::Trigger const& other) const;
  };

  struct ExportLatexClass {
    ExportLatexClass() {}
    BOOST_DESCRIBE_CLASS(ExportLatexClass,
                         (),
                         (),
                         (),
                         (latexClass))
    hstd::Str latexClass;
    bool operator==(org::sem::NamedProperty::ExportLatexClass const& other) const;
  };

  /// \brief `:COOKIE_DATA:` for the subtree completion calculation
  struct CookieData {
    BOOST_DESCRIBE_CLASS(CookieData,
                         (),
                         (),
                         (),
                         (isRecursive, source))
    bool isRecursive;
    SubtreeTodoSource source;
    bool operator==(org::sem::NamedProperty::CookieData const& other) const;
  };

  struct ExportLatexClassOptions {
    ExportLatexClassOptions() {}
    BOOST_DESCRIBE_CLASS(ExportLatexClassOptions,
                         (),
                         (),
                         (),
                         (options))
    hstd::Vec<hstd::Str> options;
    bool operator==(org::sem::NamedProperty::ExportLatexClassOptions const& other) const;
  };

  struct ExportLatexHeader {
    ExportLatexHeader() {}
    BOOST_DESCRIBE_CLASS(ExportLatexHeader,
                         (),
                         (),
                         (),
                         (header))
    hstd::Str header;
    bool operator==(org::sem::NamedProperty::ExportLatexHeader const& other) const;
  };

  struct ExportLatexCompiler {
    ExportLatexCompiler() {}
    BOOST_DESCRIBE_CLASS(ExportLatexCompiler,
                         (),
                         (),
                         (),
                         (compiler))
    hstd::Str compiler;
    bool operator==(org::sem::NamedProperty::ExportLatexCompiler const& other) const;
  };

  struct Ordered {
    Ordered() {}
    BOOST_DESCRIBE_CLASS(Ordered,
                         (),
                         (),
                         (),
                         (isOrdered))
    bool isOrdered;
    bool operator==(org::sem::NamedProperty::Ordered const& other) const;
  };

  struct Effort {
    Effort() {}
    BOOST_DESCRIBE_CLASS(Effort,
                         (),
                         (),
                         (),
                         (hours, minutes))
    int hours = 0;
    int minutes = 0;
    bool operator==(org::sem::NamedProperty::Effort const& other) const;
  };

  struct Visibility {
    Visibility() {}
    enum class Level : short int { Folded, Children, Content, All, };
    BOOST_DESCRIBE_NESTED_ENUM(Level, Folded, Children, Content, All)
    BOOST_DESCRIBE_CLASS(Visibility,
                         (),
                         (),
                         (),
                         (level))
    org::sem::NamedProperty::Visibility::Level level;
    bool operator==(org::sem::NamedProperty::Visibility const& other) const;
  };

  struct ExportOptions {
    ExportOptions() {}
    BOOST_DESCRIBE_CLASS(ExportOptions,
                         (),
                         (),
                         (),
                         (backend, values))
    hstd::Str backend;
    hstd::UnorderedMap<hstd::Str, hstd::Str> values;
    bool operator==(org::sem::NamedProperty::ExportOptions const& other) const;
  };

  struct Blocker {
    Blocker() {}
    BOOST_DESCRIBE_CLASS(Blocker,
                         (),
                         (),
                         (),
                         (blockers))
    hstd::Vec<hstd::Str> blockers;
    bool operator==(org::sem::NamedProperty::Blocker const& other) const;
  };

  struct Unnumbered {
    Unnumbered() {}
    BOOST_DESCRIBE_CLASS(Unnumbered,
                         (),
                         (),
                         (),
                         ())
    bool operator==(org::sem::NamedProperty::Unnumbered const& other) const;
  };

  struct Created {
    Created() {}
    BOOST_DESCRIBE_CLASS(Created,
                         (),
                         (),
                         (),
                         (time))
    hstd::UserTime time;
    bool operator==(org::sem::NamedProperty::Created const& other) const;
  };

  /// \brief Radio target ID
  struct RadioId {
    RadioId() {}
    BOOST_DESCRIBE_CLASS(RadioId,
                         (),
                         (),
                         (),
                         (words))
    hstd::Vec<hstd::Str> words = {};
    bool operator==(org::sem::NamedProperty::RadioId const& other) const;
  };

  /// \brief Definition of a hashtag entry
  struct HashtagDef {
    HashtagDef() {}
    BOOST_DESCRIBE_CLASS(HashtagDef,
                         (),
                         (),
                         (),
                         (hashtag))
    org::sem::HashTagText hashtag;
    bool operator==(org::sem::NamedProperty::HashtagDef const& other) const;
  };

  /// \brief Custop property with unparsed arguments
  struct CustomArgs {
    CustomArgs() {}
    BOOST_DESCRIBE_CLASS(CustomArgs,
                         (),
                         (),
                         (),
                         (name, sub, attrs))
    /// \brief Original name of the property
    hstd::Str name = "";
    /// \brief Property target specialization
    hstd::Opt<hstd::Str> sub = std::nullopt;
    /// \brief Property parameters
    org::sem::AttrGroup attrs;
    bool operator==(org::sem::NamedProperty::CustomArgs const& other) const;
  };

  /// \brief Custom property with unparsed arguments
  struct CustomRaw {
    CustomRaw() {}
    BOOST_DESCRIBE_CLASS(CustomRaw,
                         (),
                         (),
                         (),
                         (name, value))
    /// \brief Original name of the property
    hstd::Str name = "";
    /// \brief Property value
    hstd::Str value = "";
    bool operator==(org::sem::NamedProperty::CustomRaw const& other) const;
  };

  /// \brief Custom property with unparsed arguments
  struct CustomId {
    CustomId() {}
    BOOST_DESCRIBE_CLASS(CustomId,
                         (),
                         (),
                         (),
                         (value))
    /// \brief Property value
    hstd::Str value = "";
    bool operator==(org::sem::NamedProperty::CustomId const& other) const;
  };

  /// \brief Free-form JSON
  struct CustomSubtreeJson {
    BOOST_DESCRIBE_CLASS(CustomSubtreeJson,
                         (),
                         (),
                         (),
                         (name, value))
    hstd::Str name;
    org::sem::OrgJson value;
    bool operator==(org::sem::NamedProperty::CustomSubtreeJson const& other) const;
  };

  /// \brief Free-form flags
  struct CustomSubtreeFlags {
    BOOST_DESCRIBE_CLASS(CustomSubtreeFlags,
                         (),
                         (),
                         (),
                         (name, value))
    hstd::Str name;
    org::sem::AttrGroup value;
    bool operator==(org::sem::NamedProperty::CustomSubtreeFlags const& other) const;
  };

  using Data = std::variant<org::sem::NamedProperty::Nonblocking, org::sem::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveTodo, org::sem::NamedProperty::Trigger, org::sem::NamedProperty::ExportLatexClass, org::sem::NamedProperty::CookieData, org::sem::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::Ordered, org::sem::NamedProperty::Effort, org::sem::NamedProperty::Visibility, org::sem::NamedProperty::ExportOptions, org::sem::NamedProperty::Blocker, org::sem::NamedProperty::Unnumbered, org::sem::NamedProperty::Created, org::sem::NamedProperty::RadioId, org::sem::NamedProperty::HashtagDef, org::sem::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomId, org::sem::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeFlags>;
  enum class Kind : short int { Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, CustomId, CustomSubtreeJson, CustomSubtreeFlags, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, CustomId, CustomSubtreeJson, CustomSubtreeFlags)
  using variant_enum_type = org::sem::NamedProperty::Kind;
  using variant_data_type = org::sem::NamedProperty::Data;
  NamedProperty(Data const& data) : data(data) {}
  BOOST_DESCRIBE_CLASS(NamedProperty,
                       (),
                       (),
                       (),
                       (data))
  org::sem::NamedProperty::Data data;
  /// \brief Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.
  bool isMatching(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
  /// \brief Get non-normalized name of the property (for built-in and user)
  hstd::Str getName() const;
  /// \brief Get non-normalized sub-kind for the property.
  hstd::Opt<hstd::Str> getSubKind() const;
  bool operator==(org::sem::NamedProperty const& other) const;
  bool isNonblocking() const { return getKind() == Kind::Nonblocking; }
  org::sem::NamedProperty::Nonblocking const& getNonblocking() const { return hstd::variant_get<0>(data); }
  org::sem::NamedProperty::Nonblocking& getNonblocking() { return hstd::variant_get<0>(data); }
  bool isArchiveTime() const { return getKind() == Kind::ArchiveTime; }
  org::sem::NamedProperty::ArchiveTime const& getArchiveTime() const { return hstd::variant_get<1>(data); }
  org::sem::NamedProperty::ArchiveTime& getArchiveTime() { return hstd::variant_get<1>(data); }
  bool isArchiveFile() const { return getKind() == Kind::ArchiveFile; }
  org::sem::NamedProperty::ArchiveFile const& getArchiveFile() const { return hstd::variant_get<2>(data); }
  org::sem::NamedProperty::ArchiveFile& getArchiveFile() { return hstd::variant_get<2>(data); }
  bool isArchiveOlpath() const { return getKind() == Kind::ArchiveOlpath; }
  org::sem::NamedProperty::ArchiveOlpath const& getArchiveOlpath() const { return hstd::variant_get<3>(data); }
  org::sem::NamedProperty::ArchiveOlpath& getArchiveOlpath() { return hstd::variant_get<3>(data); }
  bool isArchiveTarget() const { return getKind() == Kind::ArchiveTarget; }
  org::sem::NamedProperty::ArchiveTarget const& getArchiveTarget() const { return hstd::variant_get<4>(data); }
  org::sem::NamedProperty::ArchiveTarget& getArchiveTarget() { return hstd::variant_get<4>(data); }
  bool isArchiveCategory() const { return getKind() == Kind::ArchiveCategory; }
  org::sem::NamedProperty::ArchiveCategory const& getArchiveCategory() const { return hstd::variant_get<5>(data); }
  org::sem::NamedProperty::ArchiveCategory& getArchiveCategory() { return hstd::variant_get<5>(data); }
  bool isArchiveTodo() const { return getKind() == Kind::ArchiveTodo; }
  org::sem::NamedProperty::ArchiveTodo const& getArchiveTodo() const { return hstd::variant_get<6>(data); }
  org::sem::NamedProperty::ArchiveTodo& getArchiveTodo() { return hstd::variant_get<6>(data); }
  bool isTrigger() const { return getKind() == Kind::Trigger; }
  org::sem::NamedProperty::Trigger const& getTrigger() const { return hstd::variant_get<7>(data); }
  org::sem::NamedProperty::Trigger& getTrigger() { return hstd::variant_get<7>(data); }
  bool isExportLatexClass() const { return getKind() == Kind::ExportLatexClass; }
  org::sem::NamedProperty::ExportLatexClass const& getExportLatexClass() const { return hstd::variant_get<8>(data); }
  org::sem::NamedProperty::ExportLatexClass& getExportLatexClass() { return hstd::variant_get<8>(data); }
  bool isCookieData() const { return getKind() == Kind::CookieData; }
  org::sem::NamedProperty::CookieData const& getCookieData() const { return hstd::variant_get<9>(data); }
  org::sem::NamedProperty::CookieData& getCookieData() { return hstd::variant_get<9>(data); }
  bool isExportLatexClassOptions() const { return getKind() == Kind::ExportLatexClassOptions; }
  org::sem::NamedProperty::ExportLatexClassOptions const& getExportLatexClassOptions() const { return hstd::variant_get<10>(data); }
  org::sem::NamedProperty::ExportLatexClassOptions& getExportLatexClassOptions() { return hstd::variant_get<10>(data); }
  bool isExportLatexHeader() const { return getKind() == Kind::ExportLatexHeader; }
  org::sem::NamedProperty::ExportLatexHeader const& getExportLatexHeader() const { return hstd::variant_get<11>(data); }
  org::sem::NamedProperty::ExportLatexHeader& getExportLatexHeader() { return hstd::variant_get<11>(data); }
  bool isExportLatexCompiler() const { return getKind() == Kind::ExportLatexCompiler; }
  org::sem::NamedProperty::ExportLatexCompiler const& getExportLatexCompiler() const { return hstd::variant_get<12>(data); }
  org::sem::NamedProperty::ExportLatexCompiler& getExportLatexCompiler() { return hstd::variant_get<12>(data); }
  bool isOrdered() const { return getKind() == Kind::Ordered; }
  org::sem::NamedProperty::Ordered const& getOrdered() const { return hstd::variant_get<13>(data); }
  org::sem::NamedProperty::Ordered& getOrdered() { return hstd::variant_get<13>(data); }
  bool isEffort() const { return getKind() == Kind::Effort; }
  org::sem::NamedProperty::Effort const& getEffort() const { return hstd::variant_get<14>(data); }
  org::sem::NamedProperty::Effort& getEffort() { return hstd::variant_get<14>(data); }
  bool isVisibility() const { return getKind() == Kind::Visibility; }
  org::sem::NamedProperty::Visibility const& getVisibility() const { return hstd::variant_get<15>(data); }
  org::sem::NamedProperty::Visibility& getVisibility() { return hstd::variant_get<15>(data); }
  bool isExportOptions() const { return getKind() == Kind::ExportOptions; }
  org::sem::NamedProperty::ExportOptions const& getExportOptions() const { return hstd::variant_get<16>(data); }
  org::sem::NamedProperty::ExportOptions& getExportOptions() { return hstd::variant_get<16>(data); }
  bool isBlocker() const { return getKind() == Kind::Blocker; }
  org::sem::NamedProperty::Blocker const& getBlocker() const { return hstd::variant_get<17>(data); }
  org::sem::NamedProperty::Blocker& getBlocker() { return hstd::variant_get<17>(data); }
  bool isUnnumbered() const { return getKind() == Kind::Unnumbered; }
  org::sem::NamedProperty::Unnumbered const& getUnnumbered() const { return hstd::variant_get<18>(data); }
  org::sem::NamedProperty::Unnumbered& getUnnumbered() { return hstd::variant_get<18>(data); }
  bool isCreated() const { return getKind() == Kind::Created; }
  org::sem::NamedProperty::Created const& getCreated() const { return hstd::variant_get<19>(data); }
  org::sem::NamedProperty::Created& getCreated() { return hstd::variant_get<19>(data); }
  bool isRadioId() const { return getKind() == Kind::RadioId; }
  org::sem::NamedProperty::RadioId const& getRadioId() const { return hstd::variant_get<20>(data); }
  org::sem::NamedProperty::RadioId& getRadioId() { return hstd::variant_get<20>(data); }
  bool isHashtagDef() const { return getKind() == Kind::HashtagDef; }
  org::sem::NamedProperty::HashtagDef const& getHashtagDef() const { return hstd::variant_get<21>(data); }
  org::sem::NamedProperty::HashtagDef& getHashtagDef() { return hstd::variant_get<21>(data); }
  bool isCustomArgs() const { return getKind() == Kind::CustomArgs; }
  org::sem::NamedProperty::CustomArgs const& getCustomArgs() const { return hstd::variant_get<22>(data); }
  org::sem::NamedProperty::CustomArgs& getCustomArgs() { return hstd::variant_get<22>(data); }
  bool isCustomRaw() const { return getKind() == Kind::CustomRaw; }
  org::sem::NamedProperty::CustomRaw const& getCustomRaw() const { return hstd::variant_get<23>(data); }
  org::sem::NamedProperty::CustomRaw& getCustomRaw() { return hstd::variant_get<23>(data); }
  bool isCustomId() const { return getKind() == Kind::CustomId; }
  org::sem::NamedProperty::CustomId const& getCustomId() const { return hstd::variant_get<24>(data); }
  org::sem::NamedProperty::CustomId& getCustomId() { return hstd::variant_get<24>(data); }
  bool isCustomSubtreeJson() const { return getKind() == Kind::CustomSubtreeJson; }
  org::sem::NamedProperty::CustomSubtreeJson const& getCustomSubtreeJson() const { return hstd::variant_get<25>(data); }
  org::sem::NamedProperty::CustomSubtreeJson& getCustomSubtreeJson() { return hstd::variant_get<25>(data); }
  bool isCustomSubtreeFlags() const { return getKind() == Kind::CustomSubtreeFlags; }
  org::sem::NamedProperty::CustomSubtreeFlags const& getCustomSubtreeFlags() const { return hstd::variant_get<26>(data); }
  org::sem::NamedProperty::CustomSubtreeFlags& getCustomSubtreeFlags() { return hstd::variant_get<26>(data); }
  static org::sem::NamedProperty::Kind getKind(org::sem::NamedProperty::Data const& __input) { return static_cast<org::sem::NamedProperty::Kind>(__input.index()); }
  org::sem::NamedProperty::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::NamedProperty::Data const& sub_variant_get_data() const { return data; }
  org::sem::NamedProperty::Kind sub_variant_get_kind() const { return getKind(); }
};

/// \brief Structure to store all diagnostics data collected by the parser, sem, eval etc.
struct OrgDiagnostics {
  OrgDiagnostics() {}
  /// \brief Parser errors for situations when failure can be attributed to specific token
  struct ParseTokenError {
    ParseTokenError() {}
    BOOST_DESCRIBE_CLASS(ParseTokenError,
                         (),
                         (),
                         (),
                         (brief,
                          detail,
                          parserFunction,
                          parserLine,
                          tokenKind,
                          tokenText,
                          loc,
                          errName,
                          errCode))
    hstd::Str brief;
    hstd::Str detail;
    hstd::Str parserFunction;
    int parserLine;
    OrgTokenKind tokenKind;
    hstd::Str tokenText;
    org::sem::SourceLocation loc;
    hstd::Str errName;
    hstd::Str errCode;
    bool operator==(org::sem::OrgDiagnostics::ParseTokenError const& other) const;
  };

  /// \brief General parser errors
  struct ParseError {
    ParseError() {}
    BOOST_DESCRIBE_CLASS(ParseError,
                         (),
                         (),
                         (),
                         (brief,
                          detail,
                          parserFunction,
                          parserLine,
                          errName,
                          errCode,
                          loc))
    hstd::Str brief;
    hstd::Str detail;
    hstd::Str parserFunction;
    int parserLine;
    hstd::Str errName;
    hstd::Str errCode;
    hstd::Opt<org::sem::SourceLocation> loc = std::nullopt;
    bool operator==(org::sem::OrgDiagnostics::ParseError const& other) const;
  };

  /// \brief Cannot convert parsed tree into
  struct IncludeError {
    IncludeError() {}
    BOOST_DESCRIBE_CLASS(IncludeError,
                         (),
                         (),
                         (),
                         (brief, targetPath, workingFile))
    hstd::Str brief;
    hstd::Str targetPath;
    hstd::Str workingFile;
    bool operator==(org::sem::OrgDiagnostics::IncludeError const& other) const;
  };

  /// \brief Cannot convert parsed tree into
  struct ConvertError {
    ConvertError() {}
    BOOST_DESCRIBE_CLASS(ConvertError,
                         (),
                         (),
                         (),
                         (brief,
                          detail,
                          convertFunction,
                          convertLine,
                          convertFile,
                          errName,
                          errCode,
                          loc))
    hstd::Str brief;
    hstd::Str detail;
    hstd::Str convertFunction;
    int convertLine;
    hstd::Str convertFile;
    hstd::Str errName;
    hstd::Str errCode;
    hstd::Opt<org::sem::SourceLocation> loc = std::nullopt;
    bool operator==(org::sem::OrgDiagnostics::ConvertError const& other) const;
  };

  /// \brief Internal implementation error: should not be visible to the end-user.
  struct InternalError {
    InternalError() {}
    BOOST_DESCRIBE_CLASS(InternalError,
                         (),
                         (),
                         (),
                         (message, function, line, file, loc))
    hstd::Str message;
    hstd::Str function;
    int line;
    hstd::Str file;
    hstd::Opt<org::sem::SourceLocation> loc = std::nullopt;
    bool operator==(org::sem::OrgDiagnostics::InternalError const& other) const;
  };

  using Data = std::variant<org::sem::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::InternalError>;
  enum class Kind : short int { ParseTokenError, ParseError, IncludeError, ConvertError, InternalError, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, ParseTokenError, ParseError, IncludeError, ConvertError, InternalError)
  using variant_enum_type = org::sem::OrgDiagnostics::Kind;
  using variant_data_type = org::sem::OrgDiagnostics::Data;
  OrgDiagnostics(Data const& data) : data(data) {}
  BOOST_DESCRIBE_CLASS(OrgDiagnostics,
                       (),
                       (),
                       (),
                       (data))
  org::sem::OrgDiagnostics::Data data;
  bool operator==(org::sem::OrgDiagnostics const& other) const;
  bool isParseTokenError() const { return getKind() == Kind::ParseTokenError; }
  org::sem::OrgDiagnostics::ParseTokenError const& getParseTokenError() const { return hstd::variant_get<0>(data); }
  org::sem::OrgDiagnostics::ParseTokenError& getParseTokenError() { return hstd::variant_get<0>(data); }
  bool isParseError() const { return getKind() == Kind::ParseError; }
  org::sem::OrgDiagnostics::ParseError const& getParseError() const { return hstd::variant_get<1>(data); }
  org::sem::OrgDiagnostics::ParseError& getParseError() { return hstd::variant_get<1>(data); }
  bool isIncludeError() const { return getKind() == Kind::IncludeError; }
  org::sem::OrgDiagnostics::IncludeError const& getIncludeError() const { return hstd::variant_get<2>(data); }
  org::sem::OrgDiagnostics::IncludeError& getIncludeError() { return hstd::variant_get<2>(data); }
  bool isConvertError() const { return getKind() == Kind::ConvertError; }
  org::sem::OrgDiagnostics::ConvertError const& getConvertError() const { return hstd::variant_get<3>(data); }
  org::sem::OrgDiagnostics::ConvertError& getConvertError() { return hstd::variant_get<3>(data); }
  bool isInternalError() const { return getKind() == Kind::InternalError; }
  org::sem::OrgDiagnostics::InternalError const& getInternalError() const { return hstd::variant_get<4>(data); }
  org::sem::OrgDiagnostics::InternalError& getInternalError() { return hstd::variant_get<4>(data); }
  static org::sem::OrgDiagnostics::Kind getKind(org::sem::OrgDiagnostics::Data const& __input) { return static_cast<org::sem::OrgDiagnostics::Kind>(__input.index()); }
  org::sem::OrgDiagnostics::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::OrgDiagnostics::Data const& sub_variant_get_data() const { return data; }
  org::sem::OrgDiagnostics::Kind sub_variant_get_kind() const { return getKind(); }
};

}
/* clang-format on */