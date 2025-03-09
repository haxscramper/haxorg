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
namespace org::sem {
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
  org::sem::LispCode::Call const& getCall() const { return std::get<0>(data); }
  org::sem::LispCode::Call& getCall() { return std::get<0>(data); }
  bool isList() const { return getKind() == Kind::List; }
  org::sem::LispCode::List const& getList() const { return std::get<1>(data); }
  org::sem::LispCode::List& getList() { return std::get<1>(data); }
  bool isKeyValue() const { return getKind() == Kind::KeyValue; }
  org::sem::LispCode::KeyValue const& getKeyValue() const { return std::get<2>(data); }
  org::sem::LispCode::KeyValue& getKeyValue() { return std::get<2>(data); }
  bool isNumber() const { return getKind() == Kind::Number; }
  org::sem::LispCode::Number const& getNumber() const { return std::get<3>(data); }
  org::sem::LispCode::Number& getNumber() { return std::get<3>(data); }
  bool isText() const { return getKind() == Kind::Text; }
  org::sem::LispCode::Text const& getText() const { return std::get<4>(data); }
  org::sem::LispCode::Text& getText() { return std::get<4>(data); }
  bool isIdent() const { return getKind() == Kind::Ident; }
  org::sem::LispCode::Ident const& getIdent() const { return std::get<5>(data); }
  org::sem::LispCode::Ident& getIdent() { return std::get<5>(data); }
  bool isBoolean() const { return getKind() == Kind::Boolean; }
  org::sem::LispCode::Boolean const& getBoolean() const { return std::get<6>(data); }
  org::sem::LispCode::Boolean& getBoolean() { return std::get<6>(data); }
  bool isReal() const { return getKind() == Kind::Real; }
  org::sem::LispCode::Real const& getReal() const { return std::get<7>(data); }
  org::sem::LispCode::Real& getReal() { return std::get<7>(data); }
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
        org::sem::Tblfm::Expr::AxisRef::Position::Index const& getIndex() const { return std::get<0>(data); }
        org::sem::Tblfm::Expr::AxisRef::Position::Index& getIndex() { return std::get<0>(data); }
        bool isName() const { return getKind() == Kind::Name; }
        org::sem::Tblfm::Expr::AxisRef::Position::Name const& getName() const { return std::get<1>(data); }
        org::sem::Tblfm::Expr::AxisRef::Position::Name& getName() { return std::get<1>(data); }
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
    org::sem::Tblfm::Expr::AxisRef const& getAxisRef() const { return std::get<0>(data); }
    org::sem::Tblfm::Expr::AxisRef& getAxisRef() { return std::get<0>(data); }
    bool isAxisName() const { return getKind() == Kind::AxisName; }
    org::sem::Tblfm::Expr::AxisName const& getAxisName() const { return std::get<1>(data); }
    org::sem::Tblfm::Expr::AxisName& getAxisName() { return std::get<1>(data); }
    bool isIntLiteral() const { return getKind() == Kind::IntLiteral; }
    org::sem::Tblfm::Expr::IntLiteral const& getIntLiteral() const { return std::get<2>(data); }
    org::sem::Tblfm::Expr::IntLiteral& getIntLiteral() { return std::get<2>(data); }
    bool isFloatLiteral() const { return getKind() == Kind::FloatLiteral; }
    org::sem::Tblfm::Expr::FloatLiteral const& getFloatLiteral() const { return std::get<3>(data); }
    org::sem::Tblfm::Expr::FloatLiteral& getFloatLiteral() { return std::get<3>(data); }
    bool isRangeRef() const { return getKind() == Kind::RangeRef; }
    org::sem::Tblfm::Expr::RangeRef const& getRangeRef() const { return std::get<4>(data); }
    org::sem::Tblfm::Expr::RangeRef& getRangeRef() { return std::get<4>(data); }
    bool isCall() const { return getKind() == Kind::Call; }
    org::sem::Tblfm::Expr::Call const& getCall() const { return std::get<5>(data); }
    org::sem::Tblfm::Expr::Call& getCall() { return std::get<5>(data); }
    bool isElisp() const { return getKind() == Kind::Elisp; }
    org::sem::Tblfm::Expr::Elisp const& getElisp() const { return std::get<6>(data); }
    org::sem::Tblfm::Expr::Elisp& getElisp() { return std::get<6>(data); }
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
  /// \brief Best-guess type of the attribute
  enum class Kind : short int { String, Boolean, Integer, Float, FileReference, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, String, Boolean, Integer, Float, FileReference)
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
  enum class DataKind : short int { TextValue, FileReference, LispValue, };
  BOOST_DESCRIBE_NESTED_ENUM(DataKind, TextValue, FileReference, LispValue)
  using variant_enum_type = org::sem::AttrValue::DataKind;
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
  hstd::Str getFile() const;
  hstd::Str getReference() const;
  hstd::Opt<double> getDouble() const;
  bool operator==(org::sem::AttrValue const& other) const;
  AttrValue() {  }
  bool isTextValue() const { return getDataKind() == DataKind::TextValue; }
  org::sem::AttrValue::TextValue const& getTextValue() const { return std::get<0>(data); }
  org::sem::AttrValue::TextValue& getTextValue() { return std::get<0>(data); }
  bool isFileReference() const { return getDataKind() == DataKind::FileReference; }
  org::sem::AttrValue::FileReference const& getFileReference() const { return std::get<1>(data); }
  org::sem::AttrValue::FileReference& getFileReference() { return std::get<1>(data); }
  bool isLispValue() const { return getDataKind() == DataKind::LispValue; }
  org::sem::AttrValue::LispValue const& getLispValue() const { return std::get<2>(data); }
  org::sem::AttrValue::LispValue& getLispValue() { return std::get<2>(data); }
  static org::sem::AttrValue::DataKind getDataKind(org::sem::AttrValue::DataVariant const& __input) { return static_cast<org::sem::AttrValue::DataKind>(__input.index()); }
  org::sem::AttrValue::DataKind getDataKind() const { return getDataKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::AttrValue::DataVariant const& sub_variant_get_data() const { return data; }
  org::sem::AttrValue::DataKind sub_variant_get_kind() const { return getDataKind(); }
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
  org::sem::LinkTarget::Raw const& getRaw() const { return std::get<0>(data); }
  org::sem::LinkTarget::Raw& getRaw() { return std::get<0>(data); }
  bool isId() const { return getKind() == Kind::Id; }
  org::sem::LinkTarget::Id const& getId() const { return std::get<1>(data); }
  org::sem::LinkTarget::Id& getId() { return std::get<1>(data); }
  bool isCustomId() const { return getKind() == Kind::CustomId; }
  org::sem::LinkTarget::CustomId const& getCustomId() const { return std::get<2>(data); }
  org::sem::LinkTarget::CustomId& getCustomId() { return std::get<2>(data); }
  bool isSubtreeTitle() const { return getKind() == Kind::SubtreeTitle; }
  org::sem::LinkTarget::SubtreeTitle const& getSubtreeTitle() const { return std::get<3>(data); }
  org::sem::LinkTarget::SubtreeTitle& getSubtreeTitle() { return std::get<3>(data); }
  bool isPerson() const { return getKind() == Kind::Person; }
  org::sem::LinkTarget::Person const& getPerson() const { return std::get<4>(data); }
  org::sem::LinkTarget::Person& getPerson() { return std::get<4>(data); }
  bool isUserProtocol() const { return getKind() == Kind::UserProtocol; }
  org::sem::LinkTarget::UserProtocol const& getUserProtocol() const { return std::get<5>(data); }
  org::sem::LinkTarget::UserProtocol& getUserProtocol() { return std::get<5>(data); }
  bool isInternal() const { return getKind() == Kind::Internal; }
  org::sem::LinkTarget::Internal const& getInternal() const { return std::get<6>(data); }
  org::sem::LinkTarget::Internal& getInternal() { return std::get<6>(data); }
  bool isFootnote() const { return getKind() == Kind::Footnote; }
  org::sem::LinkTarget::Footnote const& getFootnote() const { return std::get<7>(data); }
  org::sem::LinkTarget::Footnote& getFootnote() { return std::get<7>(data); }
  bool isFile() const { return getKind() == Kind::File; }
  org::sem::LinkTarget::File const& getFile() const { return std::get<8>(data); }
  org::sem::LinkTarget::File& getFile() { return std::get<8>(data); }
  bool isAttachment() const { return getKind() == Kind::Attachment; }
  org::sem::LinkTarget::Attachment const& getAttachment() const { return std::get<9>(data); }
  org::sem::LinkTarget::Attachment& getAttachment() { return std::get<9>(data); }
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
  org::sem::SubtreeLogHead::Priority const& getPriority() const { return std::get<0>(log); }
  org::sem::SubtreeLogHead::Priority& getPriority() { return std::get<0>(log); }
  bool isNote() const { return getLogKind() == Kind::Note; }
  org::sem::SubtreeLogHead::Note const& getNote() const { return std::get<1>(log); }
  org::sem::SubtreeLogHead::Note& getNote() { return std::get<1>(log); }
  bool isRefile() const { return getLogKind() == Kind::Refile; }
  org::sem::SubtreeLogHead::Refile const& getRefile() const { return std::get<2>(log); }
  org::sem::SubtreeLogHead::Refile& getRefile() { return std::get<2>(log); }
  bool isClock() const { return getLogKind() == Kind::Clock; }
  org::sem::SubtreeLogHead::Clock const& getClock() const { return std::get<3>(log); }
  org::sem::SubtreeLogHead::Clock& getClock() { return std::get<3>(log); }
  bool isState() const { return getLogKind() == Kind::State; }
  org::sem::SubtreeLogHead::State const& getState() const { return std::get<4>(log); }
  org::sem::SubtreeLogHead::State& getState() { return std::get<4>(log); }
  bool isDeadline() const { return getLogKind() == Kind::Deadline; }
  org::sem::SubtreeLogHead::Deadline const& getDeadline() const { return std::get<5>(log); }
  org::sem::SubtreeLogHead::Deadline& getDeadline() { return std::get<5>(log); }
  bool isSchedule() const { return getLogKind() == Kind::Schedule; }
  org::sem::SubtreeLogHead::Schedule const& getSchedule() const { return std::get<6>(log); }
  org::sem::SubtreeLogHead::Schedule& getSchedule() { return std::get<6>(log); }
  bool isTag() const { return getLogKind() == Kind::Tag; }
  org::sem::SubtreeLogHead::Tag const& getTag() const { return std::get<7>(log); }
  org::sem::SubtreeLogHead::Tag& getTag() { return std::get<7>(log); }
  bool isUnknown() const { return getLogKind() == Kind::Unknown; }
  org::sem::SubtreeLogHead::Unknown const& getUnknown() const { return std::get<8>(log); }
  org::sem::SubtreeLogHead::Unknown& getUnknown() { return std::get<8>(log); }
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
};

/// \brief Single command/subprocess executed to evaluate org babel code entry
struct OrgCodeEvalOutput {
  BOOST_DESCRIBE_CLASS(OrgCodeEvalOutput,
                       (),
                       (),
                       (),
                       (stdout,
                        stderr,
                        code,
                        cmd,
                        args,
                        cwd,
                        appliedHeaderArg))
  hstd::Str stdout = "";
  hstd::Str stderr = "";
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
    org::sem::ColumnView::Summary::CheckboxAggregate const& getCheckboxAggregate() const { return std::get<0>(data); }
    org::sem::ColumnView::Summary::CheckboxAggregate& getCheckboxAggregate() { return std::get<0>(data); }
    bool isMathAggregate() const { return getKind() == Kind::MathAggregate; }
    org::sem::ColumnView::Summary::MathAggregate const& getMathAggregate() const { return std::get<1>(data); }
    org::sem::ColumnView::Summary::MathAggregate& getMathAggregate() { return std::get<1>(data); }
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
    org::sem::BlockCodeLine::Part::Raw const& getRaw() const { return std::get<0>(data); }
    org::sem::BlockCodeLine::Part::Raw& getRaw() { return std::get<0>(data); }
    bool isCallout() const { return getKind() == Kind::Callout; }
    org::sem::BlockCodeLine::Part::Callout const& getCallout() const { return std::get<1>(data); }
    org::sem::BlockCodeLine::Part::Callout& getCallout() { return std::get<1>(data); }
    bool isTangle() const { return getKind() == Kind::Tangle; }
    org::sem::BlockCodeLine::Part::Tangle const& getTangle() const { return std::get<2>(data); }
    org::sem::BlockCodeLine::Part::Tangle& getTangle() { return std::get<2>(data); }
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
                        brokenLinks,
                        tocExport,
                        tagExport,
                        data))
  hstd::Opt<bool> inlinetasks = std::nullopt;
  hstd::Opt<bool> footnotes = std::nullopt;
  hstd::Opt<bool> clock = std::nullopt;
  hstd::Opt<bool> author = std::nullopt;
  hstd::Opt<bool> emphasis = std::nullopt;
  hstd::Opt<bool> specialStrings = std::nullopt;
  hstd::Opt<bool> propertyDrawers = std::nullopt;
  hstd::Opt<bool> statisticsCookies = std::nullopt;
  /// \brief Include todo keywords in export
  hstd::Opt<bool> todoText = std::nullopt;
  org::sem::DocumentExportConfig::BrokenLinks brokenLinks = sem::DocumentExportConfig::BrokenLinks::Mark;
  org::sem::DocumentExportConfig::TocExport tocExport;
  org::sem::DocumentExportConfig::TagExport tagExport = org::sem::DocumentExportConfig::TagExport::NotInToc;
  org::sem::DocumentExportConfig::TocExport data;
  bool operator==(org::sem::DocumentExportConfig const& other) const;
  bool isDoExport() const { return getTocExportKind() == TocExportKind::DoExport; }
  org::sem::DocumentExportConfig::DoExport const& getDoExport() const { return std::get<0>(data); }
  org::sem::DocumentExportConfig::DoExport& getDoExport() { return std::get<0>(data); }
  bool isExportFixed() const { return getTocExportKind() == TocExportKind::ExportFixed; }
  org::sem::DocumentExportConfig::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
  org::sem::DocumentExportConfig::ExportFixed& getExportFixed() { return std::get<1>(data); }
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
    /// \brief Where to take todo completion statistics from
    enum class TodoSource : short int {
      /// \brief Only count checkbox subnodes as a progress completion
      Checkbox,
      /// \brief Use subtrees with todo keywords
      Todo,
      /// \brief Use both subtrees and todo keywords
      Both,
    };
    BOOST_DESCRIBE_NESTED_ENUM(TodoSource, Checkbox, Todo, Both)
    BOOST_DESCRIBE_CLASS(CookieData,
                         (),
                         (),
                         (),
                         (isRecursive, source))
    bool isRecursive;
    org::sem::NamedProperty::CookieData::TodoSource source;
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

  using Data = std::variant<org::sem::NamedProperty::Nonblocking, org::sem::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveTodo, org::sem::NamedProperty::Trigger, org::sem::NamedProperty::ExportLatexClass, org::sem::NamedProperty::CookieData, org::sem::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::Ordered, org::sem::NamedProperty::Effort, org::sem::NamedProperty::Visibility, org::sem::NamedProperty::ExportOptions, org::sem::NamedProperty::Blocker, org::sem::NamedProperty::Unnumbered, org::sem::NamedProperty::Created, org::sem::NamedProperty::RadioId, org::sem::NamedProperty::HashtagDef, org::sem::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeFlags>;
  enum class Kind : short int { Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, CustomSubtreeJson, CustomSubtreeFlags, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, CustomSubtreeJson, CustomSubtreeFlags)
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
  org::sem::NamedProperty::Nonblocking const& getNonblocking() const { return std::get<0>(data); }
  org::sem::NamedProperty::Nonblocking& getNonblocking() { return std::get<0>(data); }
  bool isArchiveTime() const { return getKind() == Kind::ArchiveTime; }
  org::sem::NamedProperty::ArchiveTime const& getArchiveTime() const { return std::get<1>(data); }
  org::sem::NamedProperty::ArchiveTime& getArchiveTime() { return std::get<1>(data); }
  bool isArchiveFile() const { return getKind() == Kind::ArchiveFile; }
  org::sem::NamedProperty::ArchiveFile const& getArchiveFile() const { return std::get<2>(data); }
  org::sem::NamedProperty::ArchiveFile& getArchiveFile() { return std::get<2>(data); }
  bool isArchiveOlpath() const { return getKind() == Kind::ArchiveOlpath; }
  org::sem::NamedProperty::ArchiveOlpath const& getArchiveOlpath() const { return std::get<3>(data); }
  org::sem::NamedProperty::ArchiveOlpath& getArchiveOlpath() { return std::get<3>(data); }
  bool isArchiveTarget() const { return getKind() == Kind::ArchiveTarget; }
  org::sem::NamedProperty::ArchiveTarget const& getArchiveTarget() const { return std::get<4>(data); }
  org::sem::NamedProperty::ArchiveTarget& getArchiveTarget() { return std::get<4>(data); }
  bool isArchiveCategory() const { return getKind() == Kind::ArchiveCategory; }
  org::sem::NamedProperty::ArchiveCategory const& getArchiveCategory() const { return std::get<5>(data); }
  org::sem::NamedProperty::ArchiveCategory& getArchiveCategory() { return std::get<5>(data); }
  bool isArchiveTodo() const { return getKind() == Kind::ArchiveTodo; }
  org::sem::NamedProperty::ArchiveTodo const& getArchiveTodo() const { return std::get<6>(data); }
  org::sem::NamedProperty::ArchiveTodo& getArchiveTodo() { return std::get<6>(data); }
  bool isTrigger() const { return getKind() == Kind::Trigger; }
  org::sem::NamedProperty::Trigger const& getTrigger() const { return std::get<7>(data); }
  org::sem::NamedProperty::Trigger& getTrigger() { return std::get<7>(data); }
  bool isExportLatexClass() const { return getKind() == Kind::ExportLatexClass; }
  org::sem::NamedProperty::ExportLatexClass const& getExportLatexClass() const { return std::get<8>(data); }
  org::sem::NamedProperty::ExportLatexClass& getExportLatexClass() { return std::get<8>(data); }
  bool isCookieData() const { return getKind() == Kind::CookieData; }
  org::sem::NamedProperty::CookieData const& getCookieData() const { return std::get<9>(data); }
  org::sem::NamedProperty::CookieData& getCookieData() { return std::get<9>(data); }
  bool isExportLatexClassOptions() const { return getKind() == Kind::ExportLatexClassOptions; }
  org::sem::NamedProperty::ExportLatexClassOptions const& getExportLatexClassOptions() const { return std::get<10>(data); }
  org::sem::NamedProperty::ExportLatexClassOptions& getExportLatexClassOptions() { return std::get<10>(data); }
  bool isExportLatexHeader() const { return getKind() == Kind::ExportLatexHeader; }
  org::sem::NamedProperty::ExportLatexHeader const& getExportLatexHeader() const { return std::get<11>(data); }
  org::sem::NamedProperty::ExportLatexHeader& getExportLatexHeader() { return std::get<11>(data); }
  bool isExportLatexCompiler() const { return getKind() == Kind::ExportLatexCompiler; }
  org::sem::NamedProperty::ExportLatexCompiler const& getExportLatexCompiler() const { return std::get<12>(data); }
  org::sem::NamedProperty::ExportLatexCompiler& getExportLatexCompiler() { return std::get<12>(data); }
  bool isOrdered() const { return getKind() == Kind::Ordered; }
  org::sem::NamedProperty::Ordered const& getOrdered() const { return std::get<13>(data); }
  org::sem::NamedProperty::Ordered& getOrdered() { return std::get<13>(data); }
  bool isEffort() const { return getKind() == Kind::Effort; }
  org::sem::NamedProperty::Effort const& getEffort() const { return std::get<14>(data); }
  org::sem::NamedProperty::Effort& getEffort() { return std::get<14>(data); }
  bool isVisibility() const { return getKind() == Kind::Visibility; }
  org::sem::NamedProperty::Visibility const& getVisibility() const { return std::get<15>(data); }
  org::sem::NamedProperty::Visibility& getVisibility() { return std::get<15>(data); }
  bool isExportOptions() const { return getKind() == Kind::ExportOptions; }
  org::sem::NamedProperty::ExportOptions const& getExportOptions() const { return std::get<16>(data); }
  org::sem::NamedProperty::ExportOptions& getExportOptions() { return std::get<16>(data); }
  bool isBlocker() const { return getKind() == Kind::Blocker; }
  org::sem::NamedProperty::Blocker const& getBlocker() const { return std::get<17>(data); }
  org::sem::NamedProperty::Blocker& getBlocker() { return std::get<17>(data); }
  bool isUnnumbered() const { return getKind() == Kind::Unnumbered; }
  org::sem::NamedProperty::Unnumbered const& getUnnumbered() const { return std::get<18>(data); }
  org::sem::NamedProperty::Unnumbered& getUnnumbered() { return std::get<18>(data); }
  bool isCreated() const { return getKind() == Kind::Created; }
  org::sem::NamedProperty::Created const& getCreated() const { return std::get<19>(data); }
  org::sem::NamedProperty::Created& getCreated() { return std::get<19>(data); }
  bool isRadioId() const { return getKind() == Kind::RadioId; }
  org::sem::NamedProperty::RadioId const& getRadioId() const { return std::get<20>(data); }
  org::sem::NamedProperty::RadioId& getRadioId() { return std::get<20>(data); }
  bool isHashtagDef() const { return getKind() == Kind::HashtagDef; }
  org::sem::NamedProperty::HashtagDef const& getHashtagDef() const { return std::get<21>(data); }
  org::sem::NamedProperty::HashtagDef& getHashtagDef() { return std::get<21>(data); }
  bool isCustomArgs() const { return getKind() == Kind::CustomArgs; }
  org::sem::NamedProperty::CustomArgs const& getCustomArgs() const { return std::get<22>(data); }
  org::sem::NamedProperty::CustomArgs& getCustomArgs() { return std::get<22>(data); }
  bool isCustomRaw() const { return getKind() == Kind::CustomRaw; }
  org::sem::NamedProperty::CustomRaw const& getCustomRaw() const { return std::get<23>(data); }
  org::sem::NamedProperty::CustomRaw& getCustomRaw() { return std::get<23>(data); }
  bool isCustomSubtreeJson() const { return getKind() == Kind::CustomSubtreeJson; }
  org::sem::NamedProperty::CustomSubtreeJson const& getCustomSubtreeJson() const { return std::get<24>(data); }
  org::sem::NamedProperty::CustomSubtreeJson& getCustomSubtreeJson() { return std::get<24>(data); }
  bool isCustomSubtreeFlags() const { return getKind() == Kind::CustomSubtreeFlags; }
  org::sem::NamedProperty::CustomSubtreeFlags const& getCustomSubtreeFlags() const { return std::get<25>(data); }
  org::sem::NamedProperty::CustomSubtreeFlags& getCustomSubtreeFlags() { return std::get<25>(data); }
  static org::sem::NamedProperty::Kind getKind(org::sem::NamedProperty::Data const& __input) { return static_cast<org::sem::NamedProperty::Kind>(__input.index()); }
  org::sem::NamedProperty::Kind getKind() const { return getKind(data); }
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::NamedProperty::Data const& sub_variant_get_data() const { return data; }
  org::sem::NamedProperty::Kind sub_variant_get_kind() const { return getKind(); }
};

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
  };

  struct Static {
    BOOST_DESCRIBE_CLASS(Static, (), (), (), (repeat, time))
    hstd::Opt<org::sem::Time::Repeat> repeat;
    hstd::UserTime time;
  };

  struct Dynamic {
    BOOST_DESCRIBE_CLASS(Dynamic, (), (), (), (expr))
    hstd::Str expr;
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
  org::sem::Time::Static const& getStatic() const { return std::get<0>(time); }
  org::sem::Time::Static& getStatic() { return std::get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
  org::sem::Time::Dynamic const& getDynamic() const { return std::get<1>(time); }
  org::sem::Time::Dynamic& getDynamic() { return std::get<1>(time); }
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
                       (staticKind, from, to))
  static OrgSemKind const staticKind;
  /// \brief Starting time
  org::sem::SemId<org::sem::Time> from = sem::SemId<sem::Time>::Nil();
  /// \brief Finishing time
  org::sem::SemId<org::sem::Time> to = sem::SemId<sem::Time>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::TimeRange; }
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

/// \brief @mention
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

/// \brief ~<<target>>~
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

/// \brief ~<<<target>>>~
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
                        exports,
                        result,
                        lines,
                        cache,
                        eval,
                        noweb,
                        hlines,
                        tangle,
                        switches))
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  hstd::Opt<hstd::Str> lang = std::nullopt;
  /// \brief What to export
  BlockCodeExports exports = BlockCodeExports::Both;
  /// \brief Code evaluation results
  hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>> result = {};
  /// \brief Collected code lines
  hstd::Vec<org::sem::BlockCodeLine> lines = {};
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
  hstd::Opt<hstd::UserTime> closed = std::nullopt;
  /// \brief When is the deadline
  hstd::Opt<hstd::UserTime> deadline = std::nullopt;
  /// \brief When the event is scheduled
  hstd::Opt<hstd::UserTime> scheduled = std::nullopt;
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
                        columns))
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
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  hstd::Vec<org::sem::NamedProperty> getProperties(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
  hstd::Opt<org::sem::NamedProperty> getProperty(hstd::Str const& kind, hstd::Opt<hstd::Str> const& subKind = std::nullopt) const;
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
  char const* sub_variant_get_name() const { return "data"; }
  org::sem::CmdInclude::Data const& sub_variant_get_data() const { return data; }
  org::sem::CmdInclude::Kind sub_variant_get_kind() const { return getIncludeKind(); }
};

}
/* clang-format on */