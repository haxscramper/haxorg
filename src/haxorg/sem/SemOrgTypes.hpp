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
namespace sem{
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
          bool operator==(sem::Tblfm::Expr::AxisRef::Position::Index const& other) const;
        };

        struct Name {
          Name () {}
          BOOST_DESCRIBE_CLASS(Name,
                               (),
                               (),
                               (),
                               (name))
          Str name = "";
          bool operator==(sem::Tblfm::Expr::AxisRef::Position::Name const& other) const;
        };

        using Data = std::variant<sem::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Name>;
        enum class Kind : short int { Index, Name, };
        BOOST_DESCRIBE_NESTED_ENUM(Kind, Index, Name)
        using variant_enum_type = sem::Tblfm::Expr::AxisRef::Position::Kind;
        using variant_data_type = sem::Tblfm::Expr::AxisRef::Position::Data;
        Position () {}
        BOOST_DESCRIBE_CLASS(Position,
                             (),
                             (),
                             (),
                             (data))
        sem::Tblfm::Expr::AxisRef::Position::Data data;
        bool operator==(sem::Tblfm::Expr::AxisRef::Position const& other) const;
        bool isIndex() const { return getKind() == Kind::Index; }
        sem::Tblfm::Expr::AxisRef::Position::Index const& getIndex() const { return std::get<0>(data); }
        sem::Tblfm::Expr::AxisRef::Position::Index& getIndex() { return std::get<0>(data); }
        bool isName() const { return getKind() == Kind::Name; }
        sem::Tblfm::Expr::AxisRef::Position::Name const& getName() const { return std::get<1>(data); }
        sem::Tblfm::Expr::AxisRef::Position::Name& getName() { return std::get<1>(data); }
        static sem::Tblfm::Expr::AxisRef::Position::Kind getKind(sem::Tblfm::Expr::AxisRef::Position::Data const& __input) { return static_cast<sem::Tblfm::Expr::AxisRef::Position::Kind>(__input.index()); }
        sem::Tblfm::Expr::AxisRef::Position::Kind getKind() const { return getKind(data); }
      };

      BOOST_DESCRIBE_CLASS(AxisRef,
                           (),
                           (),
                           (),
                           (col, row))
      sem::Tblfm::Expr::AxisRef::Position col;
      Opt<sem::Tblfm::Expr::AxisRef::Position> row = std::nullopt;
      bool operator==(sem::Tblfm::Expr::AxisRef const& other) const;
    };

    struct AxisName {
      BOOST_DESCRIBE_CLASS(AxisName,
                           (),
                           (),
                           (),
                           (name))
      Str name = "";
      bool operator==(sem::Tblfm::Expr::AxisName const& other) const;
    };

    struct IntLiteral {
      BOOST_DESCRIBE_CLASS(IntLiteral,
                           (),
                           (),
                           (),
                           (value))
      int value;
      bool operator==(sem::Tblfm::Expr::IntLiteral const& other) const;
    };

    struct FloatLiteral {
      BOOST_DESCRIBE_CLASS(FloatLiteral,
                           (),
                           (),
                           (),
                           (value))
      float value;
      bool operator==(sem::Tblfm::Expr::FloatLiteral const& other) const;
    };

    struct RangeRef {
      BOOST_DESCRIBE_CLASS(RangeRef,
                           (),
                           (),
                           (),
                           (first, last))
      Opt<sem::Tblfm::Expr::AxisRef> first = std::nullopt;
      Opt<sem::Tblfm::Expr::AxisRef> last = std::nullopt;
      bool operator==(sem::Tblfm::Expr::RangeRef const& other) const;
    };

    struct Call {
      BOOST_DESCRIBE_CLASS(Call,
                           (),
                           (),
                           (),
                           (name, args))
      Str name = "";
      Vec<sem::Tblfm::Expr> args = {};
      bool operator==(sem::Tblfm::Expr::Call const& other) const;
    };

    struct Elisp {
      BOOST_DESCRIBE_CLASS(Elisp,
                           (),
                           (),
                           (),
                           (value))
      Str value = "";
      bool operator==(sem::Tblfm::Expr::Elisp const& other) const;
    };

    using Data = std::variant<sem::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisName, sem::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::Call, sem::Tblfm::Expr::Elisp>;
    enum class Kind : short int { AxisRef, AxisName, IntLiteral, FloatLiteral, RangeRef, Call, Elisp, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, AxisRef, AxisName, IntLiteral, FloatLiteral, RangeRef, Call, Elisp)
    using variant_enum_type = sem::Tblfm::Expr::Kind;
    using variant_data_type = sem::Tblfm::Expr::Data;
    BOOST_DESCRIBE_CLASS(Expr,
                         (),
                         (),
                         (),
                         (data))
    sem::Tblfm::Expr::Data data;
    bool operator==(sem::Tblfm::Expr const& other) const;
    bool isAxisRef() const { return getKind() == Kind::AxisRef; }
    sem::Tblfm::Expr::AxisRef const& getAxisRef() const { return std::get<0>(data); }
    sem::Tblfm::Expr::AxisRef& getAxisRef() { return std::get<0>(data); }
    bool isAxisName() const { return getKind() == Kind::AxisName; }
    sem::Tblfm::Expr::AxisName const& getAxisName() const { return std::get<1>(data); }
    sem::Tblfm::Expr::AxisName& getAxisName() { return std::get<1>(data); }
    bool isIntLiteral() const { return getKind() == Kind::IntLiteral; }
    sem::Tblfm::Expr::IntLiteral const& getIntLiteral() const { return std::get<2>(data); }
    sem::Tblfm::Expr::IntLiteral& getIntLiteral() { return std::get<2>(data); }
    bool isFloatLiteral() const { return getKind() == Kind::FloatLiteral; }
    sem::Tblfm::Expr::FloatLiteral const& getFloatLiteral() const { return std::get<3>(data); }
    sem::Tblfm::Expr::FloatLiteral& getFloatLiteral() { return std::get<3>(data); }
    bool isRangeRef() const { return getKind() == Kind::RangeRef; }
    sem::Tblfm::Expr::RangeRef const& getRangeRef() const { return std::get<4>(data); }
    sem::Tblfm::Expr::RangeRef& getRangeRef() { return std::get<4>(data); }
    bool isCall() const { return getKind() == Kind::Call; }
    sem::Tblfm::Expr::Call const& getCall() const { return std::get<5>(data); }
    sem::Tblfm::Expr::Call& getCall() { return std::get<5>(data); }
    bool isElisp() const { return getKind() == Kind::Elisp; }
    sem::Tblfm::Expr::Elisp const& getElisp() const { return std::get<6>(data); }
    sem::Tblfm::Expr::Elisp& getElisp() { return std::get<6>(data); }
    static sem::Tblfm::Expr::Kind getKind(sem::Tblfm::Expr::Data const& __input) { return static_cast<sem::Tblfm::Expr::Kind>(__input.index()); }
    sem::Tblfm::Expr::Kind getKind() const { return getKind(data); }
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
    sem::Tblfm::Expr::AxisRef target;
    Vec<sem::Tblfm::Expr> expr = {};
    Vec<sem::Tblfm::Assign::Flag> flags = {};
    bool operator==(sem::Tblfm::Assign const& other) const;
  };

  BOOST_DESCRIBE_CLASS(Tblfm,
                       (),
                       (),
                       (),
                       (exprs))
  Vec<sem::Tblfm::Assign> exprs = {};
  bool operator==(sem::Tblfm const& other) const;
};

struct AttrValue {
  BOOST_DESCRIBE_CLASS(AttrValue,
                       (),
                       (),
                       (),
                       (name,
                        varname,
                        value))
  Opt<Str> name = std::nullopt;
  Opt<Str> varname = std::nullopt;
  Str value = "";
  Opt<bool> getBool() const;
  Opt<int> getInt() const;
  Str getString() const;
  bool operator==(sem::AttrValue const& other) const;
};

struct HashTagFlat {
  BOOST_DESCRIBE_CLASS(HashTagFlat,
                       (),
                       (),
                       (),
                       (tags))
  Vec<Str> tags = {};
  bool operator==(sem::HashTagFlat const& other) const;
  bool operator<(sem::HashTagFlat const& other) const;
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
  Str head;
  /// \brief List of nested tags
  Vec<sem::HashTagText> subtags = {};
  bool operator==(sem::HashTagText const& other) const;
  /// \brief Check if list of tag names is a prefix for either of the nested hash tags in this one
  bool prefixMatch(Vec<Str> const& prefix) const;
  /// \brief Get flat list of expanded hashtags
  Vec<sem::HashTagFlat> getFlatHashes(bool withIntermediate = true) const;
};

struct SubtreePath {
  BOOST_DESCRIBE_CLASS(SubtreePath,
                       (),
                       (),
                       (),
                       (path))
  Vec<Str> path = {};
  bool operator==(sem::SubtreePath const& other) const;
};

struct LinkTarget {
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw,
                         (),
                         (),
                         (),
                         (text))
    Str text;
    bool operator==(sem::LinkTarget::Raw const& other) const;
  };

  struct Id {
    BOOST_DESCRIBE_CLASS(Id,
                         (),
                         (),
                         (),
                         (text))
    Str text;
    bool operator==(sem::LinkTarget::Id const& other) const;
  };

  struct CustomId {
    BOOST_DESCRIBE_CLASS(CustomId,
                         (),
                         (),
                         (),
                         (text))
    Str text;
    bool operator==(sem::LinkTarget::CustomId const& other) const;
  };

  struct SubtreeTitle {
    BOOST_DESCRIBE_CLASS(SubtreeTitle,
                         (),
                         (),
                         (),
                         (title, level))
    sem::SubtreePath title;
    int level;
    bool operator==(sem::LinkTarget::SubtreeTitle const& other) const;
  };

  struct Person {
    BOOST_DESCRIBE_CLASS(Person,
                         (),
                         (),
                         (),
                         (name))
    Str name;
    bool operator==(sem::LinkTarget::Person const& other) const;
  };

  struct UserProtocol {
    BOOST_DESCRIBE_CLASS(UserProtocol,
                         (),
                         (),
                         (),
                         (protocol, target))
    Str protocol;
    Str target;
    bool operator==(sem::LinkTarget::UserProtocol const& other) const;
  };

  struct Internal {
    BOOST_DESCRIBE_CLASS(Internal,
                         (),
                         (),
                         (),
                         (target))
    Str target;
    bool operator==(sem::LinkTarget::Internal const& other) const;
  };

  struct Footnote {
    BOOST_DESCRIBE_CLASS(Footnote,
                         (),
                         (),
                         (),
                         (target))
    Str target;
    bool operator==(sem::LinkTarget::Footnote const& other) const;
  };

  struct File {
    BOOST_DESCRIBE_CLASS(File,
                         (),
                         (),
                         (),
                         (file))
    Str file;
    bool operator==(sem::LinkTarget::File const& other) const;
  };

  struct Attachment {
    BOOST_DESCRIBE_CLASS(Attachment,
                         (),
                         (),
                         (),
                         (file))
    Str file;
    bool operator==(sem::LinkTarget::Attachment const& other) const;
  };

  using Data = std::variant<sem::LinkTarget::Raw, sem::LinkTarget::Id, sem::LinkTarget::CustomId, sem::LinkTarget::SubtreeTitle, sem::LinkTarget::Person, sem::LinkTarget::UserProtocol, sem::LinkTarget::Internal, sem::LinkTarget::Footnote, sem::LinkTarget::File, sem::LinkTarget::Attachment>;
  enum class Kind : short int { Raw, Id, CustomId, SubtreeTitle, Person, UserProtocol, Internal, Footnote, File, Attachment, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Id, CustomId, SubtreeTitle, Person, UserProtocol, Internal, Footnote, File, Attachment)
  using variant_enum_type = sem::LinkTarget::Kind;
  using variant_data_type = sem::LinkTarget::Data;
  BOOST_DESCRIBE_CLASS(LinkTarget,
                       (),
                       (),
                       (),
                       (data))
  sem::LinkTarget::Data data;
  bool operator==(sem::LinkTarget const& other) const;
  bool isRaw() const { return getKind() == Kind::Raw; }
  sem::LinkTarget::Raw const& getRaw() const { return std::get<0>(data); }
  sem::LinkTarget::Raw& getRaw() { return std::get<0>(data); }
  bool isId() const { return getKind() == Kind::Id; }
  sem::LinkTarget::Id const& getId() const { return std::get<1>(data); }
  sem::LinkTarget::Id& getId() { return std::get<1>(data); }
  bool isCustomId() const { return getKind() == Kind::CustomId; }
  sem::LinkTarget::CustomId const& getCustomId() const { return std::get<2>(data); }
  sem::LinkTarget::CustomId& getCustomId() { return std::get<2>(data); }
  bool isSubtreeTitle() const { return getKind() == Kind::SubtreeTitle; }
  sem::LinkTarget::SubtreeTitle const& getSubtreeTitle() const { return std::get<3>(data); }
  sem::LinkTarget::SubtreeTitle& getSubtreeTitle() { return std::get<3>(data); }
  bool isPerson() const { return getKind() == Kind::Person; }
  sem::LinkTarget::Person const& getPerson() const { return std::get<4>(data); }
  sem::LinkTarget::Person& getPerson() { return std::get<4>(data); }
  bool isUserProtocol() const { return getKind() == Kind::UserProtocol; }
  sem::LinkTarget::UserProtocol const& getUserProtocol() const { return std::get<5>(data); }
  sem::LinkTarget::UserProtocol& getUserProtocol() { return std::get<5>(data); }
  bool isInternal() const { return getKind() == Kind::Internal; }
  sem::LinkTarget::Internal const& getInternal() const { return std::get<6>(data); }
  sem::LinkTarget::Internal& getInternal() { return std::get<6>(data); }
  bool isFootnote() const { return getKind() == Kind::Footnote; }
  sem::LinkTarget::Footnote const& getFootnote() const { return std::get<7>(data); }
  sem::LinkTarget::Footnote& getFootnote() { return std::get<7>(data); }
  bool isFile() const { return getKind() == Kind::File; }
  sem::LinkTarget::File const& getFile() const { return std::get<8>(data); }
  sem::LinkTarget::File& getFile() { return std::get<8>(data); }
  bool isAttachment() const { return getKind() == Kind::Attachment; }
  sem::LinkTarget::Attachment const& getAttachment() const { return std::get<9>(data); }
  sem::LinkTarget::Attachment& getAttachment() { return std::get<9>(data); }
  static sem::LinkTarget::Kind getKind(sem::LinkTarget::Data const& __input) { return static_cast<sem::LinkTarget::Kind>(__input.index()); }
  sem::LinkTarget::Kind getKind() const { return getKind(data); }
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
    Opt<std::string> oldPriority = std::nullopt;
    /// \brief New priority for change and addition
    Opt<std::string> newPriority = std::nullopt;
    /// \brief When priority was changed
    UserTime on;
    /// \brief Which action taken
    sem::SubtreeLogHead::Priority::Action action;
    bool operator==(sem::SubtreeLogHead::Priority const& other) const;
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
    UserTime on;
    bool operator==(sem::SubtreeLogHead::Note const& other) const;
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
    UserTime on;
    /// \brief Link to the original subtree
    sem::LinkTarget from;
    bool operator==(sem::SubtreeLogHead::Refile const& other) const;
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
    UserTime from;
    /// \brief Optional end of the clock
    Opt<UserTime> to = std::nullopt;
    bool operator==(sem::SubtreeLogHead::Clock const& other) const;
  };

  /// \brief Change of the subtree state -- `- State "WIP" from "TODO" [2023-04-30 Sun 13:29:04]`
  struct State {
    State() {}
    BOOST_DESCRIBE_CLASS(State,
                         (),
                         (),
                         (),
                         (from, to, on))
    Str from;
    Str to;
    UserTime on;
    bool operator==(sem::SubtreeLogHead::State const& other) const;
  };

  /// \brief Change of the subtree deadline
  struct Deadline {
    Deadline() {}
    BOOST_DESCRIBE_CLASS(Deadline,
                         (),
                         (),
                         (),
                         (from, to, on))
    Opt<UserTime> from = std::nullopt;
    UserTime to;
    UserTime on;
    bool operator==(sem::SubtreeLogHead::Deadline const& other) const;
  };

  /// \brief Change of the subtree Schedule
  struct Schedule {
    Schedule() {}
    BOOST_DESCRIBE_CLASS(Schedule,
                         (),
                         (),
                         (),
                         (from, to, on))
    Opt<UserTime> from = std::nullopt;
    UserTime to;
    UserTime on;
    bool operator==(sem::SubtreeLogHead::Schedule const& other) const;
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
    UserTime on;
    /// \brief Tag in question
    sem::HashTagText tag;
    /// \brief Added/removed?
    bool added = false;
    bool operator==(sem::SubtreeLogHead::Tag const& other) const;
  };

  /// \brief Unknown subtree log entry kind
  struct Unknown {
    Unknown() {}
    BOOST_DESCRIBE_CLASS(Unknown,
                         (),
                         (),
                         (),
                         ())
    bool operator==(sem::SubtreeLogHead::Unknown const& other) const;
  };

  using LogEntry = std::variant<sem::SubtreeLogHead::Priority, sem::SubtreeLogHead::Note, sem::SubtreeLogHead::Refile, sem::SubtreeLogHead::Clock, sem::SubtreeLogHead::State, sem::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Tag, sem::SubtreeLogHead::Unknown>;
  enum class Kind : short int { Priority, Note, Refile, Clock, State, Deadline, Schedule, Tag, Unknown, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Priority, Note, Refile, Clock, State, Deadline, Schedule, Tag, Unknown)
  using variant_enum_type = sem::SubtreeLogHead::Kind;
  using variant_data_type = sem::SubtreeLogHead::LogEntry;
  BOOST_DESCRIBE_CLASS(SubtreeLogHead,
                       (),
                       (),
                       (),
                       (log))
  sem::SubtreeLogHead::LogEntry log = Note{};
  bool operator==(sem::SubtreeLogHead const& other) const;
  bool isPriority() const { return getLogKind() == Kind::Priority; }
  sem::SubtreeLogHead::Priority const& getPriority() const { return std::get<0>(log); }
  sem::SubtreeLogHead::Priority& getPriority() { return std::get<0>(log); }
  bool isNote() const { return getLogKind() == Kind::Note; }
  sem::SubtreeLogHead::Note const& getNote() const { return std::get<1>(log); }
  sem::SubtreeLogHead::Note& getNote() { return std::get<1>(log); }
  bool isRefile() const { return getLogKind() == Kind::Refile; }
  sem::SubtreeLogHead::Refile const& getRefile() const { return std::get<2>(log); }
  sem::SubtreeLogHead::Refile& getRefile() { return std::get<2>(log); }
  bool isClock() const { return getLogKind() == Kind::Clock; }
  sem::SubtreeLogHead::Clock const& getClock() const { return std::get<3>(log); }
  sem::SubtreeLogHead::Clock& getClock() { return std::get<3>(log); }
  bool isState() const { return getLogKind() == Kind::State; }
  sem::SubtreeLogHead::State const& getState() const { return std::get<4>(log); }
  sem::SubtreeLogHead::State& getState() { return std::get<4>(log); }
  bool isDeadline() const { return getLogKind() == Kind::Deadline; }
  sem::SubtreeLogHead::Deadline const& getDeadline() const { return std::get<5>(log); }
  sem::SubtreeLogHead::Deadline& getDeadline() { return std::get<5>(log); }
  bool isSchedule() const { return getLogKind() == Kind::Schedule; }
  sem::SubtreeLogHead::Schedule const& getSchedule() const { return std::get<6>(log); }
  sem::SubtreeLogHead::Schedule& getSchedule() { return std::get<6>(log); }
  bool isTag() const { return getLogKind() == Kind::Tag; }
  sem::SubtreeLogHead::Tag const& getTag() const { return std::get<7>(log); }
  sem::SubtreeLogHead::Tag& getTag() { return std::get<7>(log); }
  bool isUnknown() const { return getLogKind() == Kind::Unknown; }
  sem::SubtreeLogHead::Unknown const& getUnknown() const { return std::get<8>(log); }
  sem::SubtreeLogHead::Unknown& getUnknown() { return std::get<8>(log); }
  static sem::SubtreeLogHead::Kind getLogKind(sem::SubtreeLogHead::LogEntry const& __input) { return static_cast<sem::SubtreeLogHead::Kind>(__input.index()); }
  sem::SubtreeLogHead::Kind getLogKind() const { return getLogKind(log); }
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
  bool operator==(sem::SubtreeCompletion const& other) const;
};

struct AttrList {
  BOOST_DESCRIBE_CLASS(AttrList,
                       (),
                       (),
                       (),
                       (items))
  Vec<sem::AttrValue> items = {};
  bool operator==(sem::AttrList const& other) const;
};

struct AttrGroup {
  BOOST_DESCRIBE_CLASS(AttrGroup,
                       (),
                       (),
                       (),
                       (positional,
                        named))
  /// \brief Positional arguments with no keys
  sem::AttrList positional;
  /// \brief Stored key-value mapping
  UnorderedMap<Str, sem::AttrList> named;
  Vec<sem::AttrValue> getFlatArgs() const;
  Vec<sem::AttrValue> getAttrs(Opt<Str> const& key = std::nullopt) const;
  void setNamedAttr(Str const& key, Vec<sem::AttrValue> const& attrs);
  void setPositionalAttr(Vec<sem::AttrValue> const& items);
  bool operator==(sem::AttrGroup const& other) const;
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
      sem::ColumnView::Summary::CheckboxAggregate::Kind kind;
      bool operator==(sem::ColumnView::Summary::CheckboxAggregate const& other) const;
    };

    struct MathAggregate {
      enum class Kind : short int { Min, Max, Mean, Sum, LowHighEst, };
      BOOST_DESCRIBE_NESTED_ENUM(Kind, Min, Max, Mean, Sum, LowHighEst)
      BOOST_DESCRIBE_CLASS(MathAggregate,
                           (),
                           (),
                           (),
                           (kind, formatDigits, formatPrecision))
      sem::ColumnView::Summary::MathAggregate::Kind kind;
      Opt<int> formatDigits = std::nullopt;
      Opt<int> formatPrecision = std::nullopt;
      bool operator==(sem::ColumnView::Summary::MathAggregate const& other) const;
    };

    using Data = std::variant<sem::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::MathAggregate>;
    enum class Kind : short int { CheckboxAggregate, MathAggregate, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, CheckboxAggregate, MathAggregate)
    using variant_enum_type = sem::ColumnView::Summary::Kind;
    using variant_data_type = sem::ColumnView::Summary::Data;
    BOOST_DESCRIBE_CLASS(Summary,
                         (),
                         (),
                         (),
                         (data))
    sem::ColumnView::Summary::Data data;
    bool operator==(sem::ColumnView::Summary const& other) const;
    bool isCheckboxAggregate() const { return getKind() == Kind::CheckboxAggregate; }
    sem::ColumnView::Summary::CheckboxAggregate const& getCheckboxAggregate() const { return std::get<0>(data); }
    sem::ColumnView::Summary::CheckboxAggregate& getCheckboxAggregate() { return std::get<0>(data); }
    bool isMathAggregate() const { return getKind() == Kind::MathAggregate; }
    sem::ColumnView::Summary::MathAggregate const& getMathAggregate() const { return std::get<1>(data); }
    sem::ColumnView::Summary::MathAggregate& getMathAggregate() { return std::get<1>(data); }
    static sem::ColumnView::Summary::Kind getKind(sem::ColumnView::Summary::Data const& __input) { return static_cast<sem::ColumnView::Summary::Kind>(__input.index()); }
    sem::ColumnView::Summary::Kind getKind() const { return getKind(data); }
  };

  struct Column {
    BOOST_DESCRIBE_CLASS(Column,
                         (),
                         (),
                         (),
                         (summary, width, property, propertyTitle))
    Opt<sem::ColumnView::Summary> summary = std::nullopt;
    Opt<int> width = std::nullopt;
    Opt<Str> property = std::nullopt;
    Opt<Str> propertyTitle = std::nullopt;
    bool operator==(sem::ColumnView::Column const& other) const;
  };

  BOOST_DESCRIBE_CLASS(ColumnView,
                       (),
                       (),
                       (),
                       (columns))
  Vec<sem::ColumnView::Column> columns = {};
  bool operator==(sem::ColumnView const& other) const;
};

struct BlockCodeLine {
  struct Part {
    struct Raw {
      BOOST_DESCRIBE_CLASS(Raw,
                           (),
                           (),
                           (),
                           (code))
      Str code;
      bool operator==(sem::BlockCodeLine::Part::Raw const& other) const;
    };

    struct Callout {
      BOOST_DESCRIBE_CLASS(Callout,
                           (),
                           (),
                           (),
                           (name))
      Str name;
      bool operator==(sem::BlockCodeLine::Part::Callout const& other) const;
    };

    struct Tangle {
      BOOST_DESCRIBE_CLASS(Tangle,
                           (),
                           (),
                           (),
                           (target))
      Str target;
      bool operator==(sem::BlockCodeLine::Part::Tangle const& other) const;
    };

    using Data = std::variant<sem::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Tangle>;
    enum class Kind : short int { Raw, Callout, Tangle, };
    BOOST_DESCRIBE_NESTED_ENUM(Kind, Raw, Callout, Tangle)
    using variant_enum_type = sem::BlockCodeLine::Part::Kind;
    using variant_data_type = sem::BlockCodeLine::Part::Data;
    BOOST_DESCRIBE_CLASS(Part,
                         (),
                         (),
                         (),
                         (data))
    sem::BlockCodeLine::Part::Data data;
    bool operator==(sem::BlockCodeLine::Part const& other) const;
    bool isRaw() const { return getKind() == Kind::Raw; }
    sem::BlockCodeLine::Part::Raw const& getRaw() const { return std::get<0>(data); }
    sem::BlockCodeLine::Part::Raw& getRaw() { return std::get<0>(data); }
    bool isCallout() const { return getKind() == Kind::Callout; }
    sem::BlockCodeLine::Part::Callout const& getCallout() const { return std::get<1>(data); }
    sem::BlockCodeLine::Part::Callout& getCallout() { return std::get<1>(data); }
    bool isTangle() const { return getKind() == Kind::Tangle; }
    sem::BlockCodeLine::Part::Tangle const& getTangle() const { return std::get<2>(data); }
    sem::BlockCodeLine::Part::Tangle& getTangle() { return std::get<2>(data); }
    static sem::BlockCodeLine::Part::Kind getKind(sem::BlockCodeLine::Part::Data const& __input) { return static_cast<sem::BlockCodeLine::Part::Kind>(__input.index()); }
    sem::BlockCodeLine::Part::Kind getKind() const { return getKind(data); }
  };

  BOOST_DESCRIBE_CLASS(BlockCodeLine,
                       (),
                       (),
                       (),
                       (parts))
  /// \brief parts of the single line
  Vec<sem::BlockCodeLine::Part> parts = {};
  bool operator==(sem::BlockCodeLine const& other) const;
};

/// \brief Extra configuration switches that can be used to control representation of the rendered code block. This field does not exactly correspond to the `-XX` parameters that can be passed directly in the field, but also works with attached `#+options` from the block
struct BlockCodeSwitch {
  BlockCodeSwitch() {}
  /// \brief Enumerate code lines starting from `start` value instead of default indexing.
  struct LineStart {
    LineStart() {}
    BOOST_DESCRIBE_CLASS(LineStart,
                         (),
                         (),
                         (),
                         (start, extendLast))
    /// \brief First line number
    int start;
    /// \brief Continue numbering from the previous block nstead of starting anew
    bool extendLast = false;
    bool operator==(sem::BlockCodeSwitch::LineStart const& other) const;
  };

  struct CalloutFormat {
    CalloutFormat() {}
    BOOST_DESCRIBE_CLASS(CalloutFormat,
                         (),
                         (),
                         (),
                         (format))
    Str format = "";
    bool operator==(sem::BlockCodeSwitch::CalloutFormat const& other) const;
  };

  struct RemoveCallout {
    RemoveCallout() {}
    BOOST_DESCRIBE_CLASS(RemoveCallout,
                         (),
                         (),
                         (),
                         (remove))
    bool remove = true;
    bool operator==(sem::BlockCodeSwitch::RemoveCallout const& other) const;
  };

  /// \brief Emphasize single line -- can be repeated multiple times
  struct EmphasizeLine {
    EmphasizeLine() {}
    BOOST_DESCRIBE_CLASS(EmphasizeLine,
                         (),
                         (),
                         (),
                         (line))
    Vec<int> line = {};
    bool operator==(sem::BlockCodeSwitch::EmphasizeLine const& other) const;
  };

  struct Dedent {
    Dedent() {}
    BOOST_DESCRIBE_CLASS(Dedent,
                         (),
                         (),
                         (),
                         (value))
    int value = 0;
    bool operator==(sem::BlockCodeSwitch::Dedent const& other) const;
  };

  using Data = std::variant<sem::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::Dedent>;
  enum class Kind : short int { LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, LineStart, CalloutFormat, RemoveCallout, EmphasizeLine, Dedent)
  using variant_enum_type = sem::BlockCodeSwitch::Kind;
  using variant_data_type = sem::BlockCodeSwitch::Data;
  BOOST_DESCRIBE_CLASS(BlockCodeSwitch,
                       (),
                       (),
                       (),
                       (data))
  sem::BlockCodeSwitch::Data data;
  bool operator==(sem::BlockCodeSwitch const& other) const;
  bool isLineStart() const { return getKind() == Kind::LineStart; }
  sem::BlockCodeSwitch::LineStart const& getLineStart() const { return std::get<0>(data); }
  sem::BlockCodeSwitch::LineStart& getLineStart() { return std::get<0>(data); }
  bool isCalloutFormat() const { return getKind() == Kind::CalloutFormat; }
  sem::BlockCodeSwitch::CalloutFormat const& getCalloutFormat() const { return std::get<1>(data); }
  sem::BlockCodeSwitch::CalloutFormat& getCalloutFormat() { return std::get<1>(data); }
  bool isRemoveCallout() const { return getKind() == Kind::RemoveCallout; }
  sem::BlockCodeSwitch::RemoveCallout const& getRemoveCallout() const { return std::get<2>(data); }
  sem::BlockCodeSwitch::RemoveCallout& getRemoveCallout() { return std::get<2>(data); }
  bool isEmphasizeLine() const { return getKind() == Kind::EmphasizeLine; }
  sem::BlockCodeSwitch::EmphasizeLine const& getEmphasizeLine() const { return std::get<3>(data); }
  sem::BlockCodeSwitch::EmphasizeLine& getEmphasizeLine() { return std::get<3>(data); }
  bool isDedent() const { return getKind() == Kind::Dedent; }
  sem::BlockCodeSwitch::Dedent const& getDedent() const { return std::get<4>(data); }
  sem::BlockCodeSwitch::Dedent& getDedent() { return std::get<4>(data); }
  static sem::BlockCodeSwitch::Kind getKind(sem::BlockCodeSwitch::Data const& __input) { return static_cast<sem::BlockCodeSwitch::Kind>(__input.index()); }
  sem::BlockCodeSwitch::Kind getKind() const { return getKind(data); }
};

struct BlockCodeEvalResult {
  /// \brief Default value
  struct None {
    BOOST_DESCRIBE_CLASS(None,
                         (),
                         (),
                         (),
                         ())
    bool operator==(sem::BlockCodeEvalResult::None const& other) const;
  };

  /// \brief Source code block evaluated to an org-mode node element
  struct OrgValue {
    BOOST_DESCRIBE_CLASS(OrgValue,
                         (),
                         (),
                         (),
                         (value))
    /// \brief Evaluation result
    Str value = "";
    bool operator==(sem::BlockCodeEvalResult::OrgValue const& other) const;
  };

  /// \brief Output evaluation results to a file
  struct File {
    BOOST_DESCRIBE_CLASS(File,
                         (),
                         (),
                         (),
                         (path))
    Str path;
    bool operator==(sem::BlockCodeEvalResult::File const& other) const;
  };

  /// \brief Evaluation output is a raw text
  struct Raw {
    BOOST_DESCRIBE_CLASS(Raw,
                         (),
                         (),
                         (),
                         (text))
    Str text;
    bool operator==(sem::BlockCodeEvalResult::Raw const& other) const;
  };

  using Data = std::variant<sem::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::Raw>;
  enum class Kind : short int { None, OrgValue, File, Raw, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, None, OrgValue, File, Raw)
  using variant_enum_type = sem::BlockCodeEvalResult::Kind;
  using variant_data_type = sem::BlockCodeEvalResult::Data;
  BOOST_DESCRIBE_CLASS(BlockCodeEvalResult,
                       (),
                       (),
                       (),
                       (data))
  sem::BlockCodeEvalResult::Data data;
  bool operator==(sem::BlockCodeEvalResult const& other) const;
  bool isNone() const { return getKind() == Kind::None; }
  sem::BlockCodeEvalResult::None const& getNone() const { return std::get<0>(data); }
  sem::BlockCodeEvalResult::None& getNone() { return std::get<0>(data); }
  bool isOrgValue() const { return getKind() == Kind::OrgValue; }
  sem::BlockCodeEvalResult::OrgValue const& getOrgValue() const { return std::get<1>(data); }
  sem::BlockCodeEvalResult::OrgValue& getOrgValue() { return std::get<1>(data); }
  bool isFile() const { return getKind() == Kind::File; }
  sem::BlockCodeEvalResult::File const& getFile() const { return std::get<2>(data); }
  sem::BlockCodeEvalResult::File& getFile() { return std::get<2>(data); }
  bool isRaw() const { return getKind() == Kind::Raw; }
  sem::BlockCodeEvalResult::Raw const& getRaw() const { return std::get<3>(data); }
  sem::BlockCodeEvalResult::Raw& getRaw() { return std::get<3>(data); }
  static sem::BlockCodeEvalResult::Kind getKind(sem::BlockCodeEvalResult::Data const& __input) { return static_cast<sem::BlockCodeEvalResult::Kind>(__input.index()); }
  sem::BlockCodeEvalResult::Kind getKind() const { return getKind(data); }
};

struct DocumentExportConfig {
  struct TaskExport {
    BOOST_DESCRIBE_CLASS(TaskExport,
                         (),
                         (),
                         (),
                         (taskWhitelist))
    Vec<Str> taskWhitelist = {};
    bool operator==(sem::DocumentExportConfig::TaskExport const& other) const;
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
    bool operator==(sem::DocumentExportConfig::DoExport const& other) const;
  };

  struct ExportFixed {
    BOOST_DESCRIBE_CLASS(ExportFixed,
                         (),
                         (),
                         (),
                         (exportLevels))
    int exportLevels;
    bool operator==(sem::DocumentExportConfig::ExportFixed const& other) const;
  };

  using TocExport = std::variant<sem::DocumentExportConfig::DoExport, sem::DocumentExportConfig::ExportFixed>;
  enum class TocExportKind : short int { DoExport, ExportFixed, };
  BOOST_DESCRIBE_NESTED_ENUM(TocExportKind, DoExport, ExportFixed)
  using variant_enum_type = sem::DocumentExportConfig::TocExportKind;
  using variant_data_type = sem::DocumentExportConfig::TocExport;
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
  sem::DocumentExportConfig::BrokenLinks brokenLinks = sem::DocumentExportConfig::BrokenLinks::Mark;
  sem::DocumentExportConfig::TocExport tocExport;
  sem::DocumentExportConfig::TagExport tagExport = sem::DocumentExportConfig::TagExport::NotInToc;
  sem::DocumentExportConfig::TocExport data;
  bool operator==(sem::DocumentExportConfig const& other) const;
  bool isDoExport() const { return getTocExportKind() == TocExportKind::DoExport; }
  sem::DocumentExportConfig::DoExport const& getDoExport() const { return std::get<0>(data); }
  sem::DocumentExportConfig::DoExport& getDoExport() { return std::get<0>(data); }
  bool isExportFixed() const { return getTocExportKind() == TocExportKind::ExportFixed; }
  sem::DocumentExportConfig::ExportFixed const& getExportFixed() const { return std::get<1>(data); }
  sem::DocumentExportConfig::ExportFixed& getExportFixed() { return std::get<1>(data); }
  static sem::DocumentExportConfig::TocExportKind getTocExportKind(sem::DocumentExportConfig::TocExport const& __input) { return static_cast<sem::DocumentExportConfig::TocExportKind>(__input.index()); }
  sem::DocumentExportConfig::TocExportKind getTocExportKind() const { return getTocExportKind(data); }
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
  sem::SubtreePeriod::Kind kind;
  /// \brief Clock start time
  UserTime from;
  /// \brief Optional end of the clock
  Opt<UserTime> to = std::nullopt;
  bool operator==(sem::SubtreePeriod const& other) const;
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
    bool operator==(sem::NamedProperty::Nonblocking const& other) const;
  };

  struct ArchiveTime {
    ArchiveTime() {}
    BOOST_DESCRIBE_CLASS(ArchiveTime,
                         (),
                         (),
                         (),
                         (time))
    UserTime time;
    bool operator==(sem::NamedProperty::ArchiveTime const& other) const;
  };

  struct ArchiveFile {
    ArchiveFile() {}
    BOOST_DESCRIBE_CLASS(ArchiveFile,
                         (),
                         (),
                         (),
                         (file))
    Str file;
    bool operator==(sem::NamedProperty::ArchiveFile const& other) const;
  };

  struct ArchiveOlpath {
    ArchiveOlpath() {}
    BOOST_DESCRIBE_CLASS(ArchiveOlpath,
                         (),
                         (),
                         (),
                         (path))
    sem::SubtreePath path;
    bool operator==(sem::NamedProperty::ArchiveOlpath const& other) const;
  };

  struct ArchiveTarget {
    ArchiveTarget() {}
    BOOST_DESCRIBE_CLASS(ArchiveTarget,
                         (),
                         (),
                         (),
                         (path, pattern))
    sem::SubtreePath path;
    Str pattern;
    bool operator==(sem::NamedProperty::ArchiveTarget const& other) const;
  };

  struct ArchiveCategory {
    ArchiveCategory() {}
    BOOST_DESCRIBE_CLASS(ArchiveCategory,
                         (),
                         (),
                         (),
                         (category))
    Str category;
    bool operator==(sem::NamedProperty::ArchiveCategory const& other) const;
  };

  struct ArchiveTodo {
    ArchiveTodo() {}
    BOOST_DESCRIBE_CLASS(ArchiveTodo,
                         (),
                         (),
                         (),
                         (todo))
    Str todo;
    bool operator==(sem::NamedProperty::ArchiveTodo const& other) const;
  };

  struct Trigger {
    Trigger() {}
    BOOST_DESCRIBE_CLASS(Trigger,
                         (),
                         (),
                         (),
                         ())
    bool operator==(sem::NamedProperty::Trigger const& other) const;
  };

  struct ExportLatexClass {
    ExportLatexClass() {}
    BOOST_DESCRIBE_CLASS(ExportLatexClass,
                         (),
                         (),
                         (),
                         (latexClass))
    Str latexClass;
    bool operator==(sem::NamedProperty::ExportLatexClass const& other) const;
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
    sem::NamedProperty::CookieData::TodoSource source;
    bool operator==(sem::NamedProperty::CookieData const& other) const;
  };

  struct ExportLatexClassOptions {
    ExportLatexClassOptions() {}
    BOOST_DESCRIBE_CLASS(ExportLatexClassOptions,
                         (),
                         (),
                         (),
                         (options))
    Vec<Str> options;
    bool operator==(sem::NamedProperty::ExportLatexClassOptions const& other) const;
  };

  struct ExportLatexHeader {
    ExportLatexHeader() {}
    BOOST_DESCRIBE_CLASS(ExportLatexHeader,
                         (),
                         (),
                         (),
                         (header))
    Str header;
    bool operator==(sem::NamedProperty::ExportLatexHeader const& other) const;
  };

  struct ExportLatexCompiler {
    ExportLatexCompiler() {}
    BOOST_DESCRIBE_CLASS(ExportLatexCompiler,
                         (),
                         (),
                         (),
                         (compiler))
    Str compiler;
    bool operator==(sem::NamedProperty::ExportLatexCompiler const& other) const;
  };

  struct Ordered {
    Ordered() {}
    BOOST_DESCRIBE_CLASS(Ordered,
                         (),
                         (),
                         (),
                         (isOrdered))
    bool isOrdered;
    bool operator==(sem::NamedProperty::Ordered const& other) const;
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
    bool operator==(sem::NamedProperty::Effort const& other) const;
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
    sem::NamedProperty::Visibility::Level level;
    bool operator==(sem::NamedProperty::Visibility const& other) const;
  };

  struct ExportOptions {
    ExportOptions() {}
    BOOST_DESCRIBE_CLASS(ExportOptions,
                         (),
                         (),
                         (),
                         (backend, values))
    Str backend;
    UnorderedMap<Str, Str> values;
    bool operator==(sem::NamedProperty::ExportOptions const& other) const;
  };

  struct Blocker {
    Blocker() {}
    BOOST_DESCRIBE_CLASS(Blocker,
                         (),
                         (),
                         (),
                         (blockers))
    Vec<Str> blockers;
    bool operator==(sem::NamedProperty::Blocker const& other) const;
  };

  struct Unnumbered {
    Unnumbered() {}
    BOOST_DESCRIBE_CLASS(Unnumbered,
                         (),
                         (),
                         (),
                         ())
    bool operator==(sem::NamedProperty::Unnumbered const& other) const;
  };

  struct Created {
    Created() {}
    BOOST_DESCRIBE_CLASS(Created,
                         (),
                         (),
                         (),
                         (time))
    UserTime time;
    bool operator==(sem::NamedProperty::Created const& other) const;
  };

  /// \brief Radio target ID
  struct RadioId {
    RadioId() {}
    BOOST_DESCRIBE_CLASS(RadioId,
                         (),
                         (),
                         (),
                         (words))
    Vec<Str> words = {};
    bool operator==(sem::NamedProperty::RadioId const& other) const;
  };

  /// \brief Definition of a hashtag entry
  struct HashtagDef {
    HashtagDef() {}
    BOOST_DESCRIBE_CLASS(HashtagDef,
                         (),
                         (),
                         (),
                         (hashtag))
    sem::HashTagText hashtag;
    bool operator==(sem::NamedProperty::HashtagDef const& other) const;
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
    Str name = "";
    /// \brief Property target specialization
    Opt<Str> sub = std::nullopt;
    /// \brief Property parameters
    sem::AttrGroup attrs;
    bool operator==(sem::NamedProperty::CustomArgs const& other) const;
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
    Str name = "";
    /// \brief Property value
    Str value = "";
    bool operator==(sem::NamedProperty::CustomRaw const& other) const;
  };

  using Data = std::variant<sem::NamedProperty::Nonblocking, sem::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveTodo, sem::NamedProperty::Trigger, sem::NamedProperty::ExportLatexClass, sem::NamedProperty::CookieData, sem::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexCompiler, sem::NamedProperty::Ordered, sem::NamedProperty::Effort, sem::NamedProperty::Visibility, sem::NamedProperty::ExportOptions, sem::NamedProperty::Blocker, sem::NamedProperty::Unnumbered, sem::NamedProperty::Created, sem::NamedProperty::RadioId, sem::NamedProperty::HashtagDef, sem::NamedProperty::CustomArgs, sem::NamedProperty::CustomRaw>;
  enum class Kind : short int { Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Nonblocking, ArchiveTime, ArchiveFile, ArchiveOlpath, ArchiveTarget, ArchiveCategory, ArchiveTodo, Trigger, ExportLatexClass, CookieData, ExportLatexClassOptions, ExportLatexHeader, ExportLatexCompiler, Ordered, Effort, Visibility, ExportOptions, Blocker, Unnumbered, Created, RadioId, HashtagDef, CustomArgs, CustomRaw)
  using variant_enum_type = sem::NamedProperty::Kind;
  using variant_data_type = sem::NamedProperty::Data;
  NamedProperty(CR<Data> data) : data(data) {}
  BOOST_DESCRIBE_CLASS(NamedProperty,
                       (),
                       (),
                       (),
                       (data))
  sem::NamedProperty::Data data;
  /// \brief Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.
  bool isMatching(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
  /// \brief Get non-normalized name of the property (for built-in and user)
  Str getName() const;
  /// \brief Get non-normalized sub-kind for the property.
  Opt<Str> getSubKind() const;
  bool operator==(sem::NamedProperty const& other) const;
  bool isNonblocking() const { return getKind() == Kind::Nonblocking; }
  sem::NamedProperty::Nonblocking const& getNonblocking() const { return std::get<0>(data); }
  sem::NamedProperty::Nonblocking& getNonblocking() { return std::get<0>(data); }
  bool isArchiveTime() const { return getKind() == Kind::ArchiveTime; }
  sem::NamedProperty::ArchiveTime const& getArchiveTime() const { return std::get<1>(data); }
  sem::NamedProperty::ArchiveTime& getArchiveTime() { return std::get<1>(data); }
  bool isArchiveFile() const { return getKind() == Kind::ArchiveFile; }
  sem::NamedProperty::ArchiveFile const& getArchiveFile() const { return std::get<2>(data); }
  sem::NamedProperty::ArchiveFile& getArchiveFile() { return std::get<2>(data); }
  bool isArchiveOlpath() const { return getKind() == Kind::ArchiveOlpath; }
  sem::NamedProperty::ArchiveOlpath const& getArchiveOlpath() const { return std::get<3>(data); }
  sem::NamedProperty::ArchiveOlpath& getArchiveOlpath() { return std::get<3>(data); }
  bool isArchiveTarget() const { return getKind() == Kind::ArchiveTarget; }
  sem::NamedProperty::ArchiveTarget const& getArchiveTarget() const { return std::get<4>(data); }
  sem::NamedProperty::ArchiveTarget& getArchiveTarget() { return std::get<4>(data); }
  bool isArchiveCategory() const { return getKind() == Kind::ArchiveCategory; }
  sem::NamedProperty::ArchiveCategory const& getArchiveCategory() const { return std::get<5>(data); }
  sem::NamedProperty::ArchiveCategory& getArchiveCategory() { return std::get<5>(data); }
  bool isArchiveTodo() const { return getKind() == Kind::ArchiveTodo; }
  sem::NamedProperty::ArchiveTodo const& getArchiveTodo() const { return std::get<6>(data); }
  sem::NamedProperty::ArchiveTodo& getArchiveTodo() { return std::get<6>(data); }
  bool isTrigger() const { return getKind() == Kind::Trigger; }
  sem::NamedProperty::Trigger const& getTrigger() const { return std::get<7>(data); }
  sem::NamedProperty::Trigger& getTrigger() { return std::get<7>(data); }
  bool isExportLatexClass() const { return getKind() == Kind::ExportLatexClass; }
  sem::NamedProperty::ExportLatexClass const& getExportLatexClass() const { return std::get<8>(data); }
  sem::NamedProperty::ExportLatexClass& getExportLatexClass() { return std::get<8>(data); }
  bool isCookieData() const { return getKind() == Kind::CookieData; }
  sem::NamedProperty::CookieData const& getCookieData() const { return std::get<9>(data); }
  sem::NamedProperty::CookieData& getCookieData() { return std::get<9>(data); }
  bool isExportLatexClassOptions() const { return getKind() == Kind::ExportLatexClassOptions; }
  sem::NamedProperty::ExportLatexClassOptions const& getExportLatexClassOptions() const { return std::get<10>(data); }
  sem::NamedProperty::ExportLatexClassOptions& getExportLatexClassOptions() { return std::get<10>(data); }
  bool isExportLatexHeader() const { return getKind() == Kind::ExportLatexHeader; }
  sem::NamedProperty::ExportLatexHeader const& getExportLatexHeader() const { return std::get<11>(data); }
  sem::NamedProperty::ExportLatexHeader& getExportLatexHeader() { return std::get<11>(data); }
  bool isExportLatexCompiler() const { return getKind() == Kind::ExportLatexCompiler; }
  sem::NamedProperty::ExportLatexCompiler const& getExportLatexCompiler() const { return std::get<12>(data); }
  sem::NamedProperty::ExportLatexCompiler& getExportLatexCompiler() { return std::get<12>(data); }
  bool isOrdered() const { return getKind() == Kind::Ordered; }
  sem::NamedProperty::Ordered const& getOrdered() const { return std::get<13>(data); }
  sem::NamedProperty::Ordered& getOrdered() { return std::get<13>(data); }
  bool isEffort() const { return getKind() == Kind::Effort; }
  sem::NamedProperty::Effort const& getEffort() const { return std::get<14>(data); }
  sem::NamedProperty::Effort& getEffort() { return std::get<14>(data); }
  bool isVisibility() const { return getKind() == Kind::Visibility; }
  sem::NamedProperty::Visibility const& getVisibility() const { return std::get<15>(data); }
  sem::NamedProperty::Visibility& getVisibility() { return std::get<15>(data); }
  bool isExportOptions() const { return getKind() == Kind::ExportOptions; }
  sem::NamedProperty::ExportOptions const& getExportOptions() const { return std::get<16>(data); }
  sem::NamedProperty::ExportOptions& getExportOptions() { return std::get<16>(data); }
  bool isBlocker() const { return getKind() == Kind::Blocker; }
  sem::NamedProperty::Blocker const& getBlocker() const { return std::get<17>(data); }
  sem::NamedProperty::Blocker& getBlocker() { return std::get<17>(data); }
  bool isUnnumbered() const { return getKind() == Kind::Unnumbered; }
  sem::NamedProperty::Unnumbered const& getUnnumbered() const { return std::get<18>(data); }
  sem::NamedProperty::Unnumbered& getUnnumbered() { return std::get<18>(data); }
  bool isCreated() const { return getKind() == Kind::Created; }
  sem::NamedProperty::Created const& getCreated() const { return std::get<19>(data); }
  sem::NamedProperty::Created& getCreated() { return std::get<19>(data); }
  bool isRadioId() const { return getKind() == Kind::RadioId; }
  sem::NamedProperty::RadioId const& getRadioId() const { return std::get<20>(data); }
  sem::NamedProperty::RadioId& getRadioId() { return std::get<20>(data); }
  bool isHashtagDef() const { return getKind() == Kind::HashtagDef; }
  sem::NamedProperty::HashtagDef const& getHashtagDef() const { return std::get<21>(data); }
  sem::NamedProperty::HashtagDef& getHashtagDef() { return std::get<21>(data); }
  bool isCustomArgs() const { return getKind() == Kind::CustomArgs; }
  sem::NamedProperty::CustomArgs const& getCustomArgs() const { return std::get<22>(data); }
  sem::NamedProperty::CustomArgs& getCustomArgs() { return std::get<22>(data); }
  bool isCustomRaw() const { return getKind() == Kind::CustomRaw; }
  sem::NamedProperty::CustomRaw const& getCustomRaw() const { return std::get<23>(data); }
  sem::NamedProperty::CustomRaw& getCustomRaw() { return std::get<23>(data); }
  static sem::NamedProperty::Kind getKind(sem::NamedProperty::Data const& __input) { return static_cast<sem::NamedProperty::Kind>(__input.index()); }
  sem::NamedProperty::Kind getKind() const { return getKind(data); }
};

/// \brief No node
struct None : public sem::Org {
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

struct ErrorItem : public sem::Org {
  using Org::Org;
  virtual ~ErrorItem() = default;
  BOOST_DESCRIBE_CLASS(ErrorItem,
                       (Org),
                       (),
                       (),
                       (staticKind, message, function, line))
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
                       (staticKind, diagnostics, function, line))
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
                       (attached))
  Vec<sem::SemId<sem::Org>> attached;
  /// \brief Return attached nodes of a specific kinds or all attached (if kind is nullopt)
  Vec<sem::SemId<sem::Org>> getAttached(Opt<Str> const& kind = std::nullopt) const;
  Vec<sem::SemId<sem::Org>> getCaption() const;
  Vec<Str> getName() const;
  /// \brief Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.
  virtual Vec<sem::AttrValue> getAttrs(Opt<Str> const& kind = std::nullopt) const;
  /// \brief Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities
  virtual Opt<sem::AttrValue> getFirstAttr(Str const& kind) const;
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
                       (staticKind))
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
                       (staticKind))
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
                       (attrs))
  /// \brief Additional parameters aside from 'exporter',
  Opt<sem::AttrGroup> attrs = std::nullopt;
  /// \brief Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.
  virtual Vec<sem::AttrValue> getAttrs(Opt<Str> const& key = std::nullopt) const override;
  /// \brief Override of the base statement argument get, prioritizing the explicit command parameters
  virtual Opt<sem::AttrValue> getFirstAttr(Str const& kind) const override;
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
  BOOST_DESCRIBE_CLASS(Leaf,
                       (Org),
                       (),
                       (),
                       (text))
  /// \brief Final leaf value
  Str text = "";
  Str getText() const { return text; }
};

/// \brief Caption annotation for any subsequent node
struct CmdCaption : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdCaption() = default;
  BOOST_DESCRIBE_CLASS(CmdCaption,
                       (Attached),
                       (),
                       (),
                       (staticKind, text))
  static OrgSemKind const staticKind;
  /// \brief Content description
  sem::SemId<sem::Paragraph> text = sem::SemId<sem::Paragraph>::Nil();
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdCaption; }
};

/// \brief Caption annotation for any subsequent node
struct CmdColumns : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdColumns() = default;
  BOOST_DESCRIBE_CLASS(CmdColumns,
                       (Attached),
                       (),
                       (),
                       (staticKind, view))
  static OrgSemKind const staticKind;
  sem::ColumnView view;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdColumns; }
};

/// \brief Name identifier for the statement elements.
struct CmdName : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdName() = default;
  BOOST_DESCRIBE_CLASS(CmdName,
                       (Attached),
                       (),
                       (),
                       (staticKind, name))
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
                       (staticKind, name, isAttached))
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
                       (staticKind, name, isAttached, text))
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
                       (staticKind, name, isAttached, text))
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
                       (staticKind))
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
                       (staticKind, expr))
  static OrgSemKind const staticKind;
  sem::Tblfm expr;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdTblfm; }
};

struct HashTag : public sem::Inline {
  using Inline::Inline;
  virtual ~HashTag() = default;
  BOOST_DESCRIBE_CLASS(HashTag,
                       (Inline),
                       (),
                       (),
                       (staticKind, text))
  static OrgSemKind const staticKind;
  sem::HashTagText text;
  virtual OrgSemKind getKind() const { return OrgSemKind::HashTag; }
};

/// \brief Inline footnote definition
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct InlineFootnote : public sem::Inline {
  using Inline::Inline;
  virtual ~InlineFootnote() = default;
  BOOST_DESCRIBE_CLASS(InlineFootnote,
                       (Inline),
                       (),
                       (),
                       (staticKind, tag, definition))
  static OrgSemKind const staticKind;
  /// \brief Footnote text target name
  Str tag = "";
  /// \brief Link to possibly resolved definition
  Opt<sem::SemId<sem::Org>> definition = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineFootnote; }
};

/// \brief Inline export
struct InlineExport : public sem::Inline {
  using Inline::Inline;
  virtual ~InlineExport() = default;
  BOOST_DESCRIBE_CLASS(InlineExport,
                       (Inline),
                       (),
                       (),
                       (staticKind, exporter, content))
  static OrgSemKind const staticKind;
  Str exporter = "";
  Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::InlineExport; }
};

/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public sem::Org {
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
                        time))
  static OrgSemKind const staticKind;
  /// \brief <active> vs [inactive]
  bool isActive = false;
  sem::Time::TimeVariant time;
  virtual OrgSemKind getKind() const { return OrgSemKind::Time; }
  Opt<int> getYear() const;
  Opt<int> getMonth() const;
  Opt<int> getDay() const;
  Opt<int> getHour() const;
  Opt<int> getMinute() const;
  Opt<int> getSecond() const;
  UserTime getStaticTime() const;
  bool isStatic() const { return getTimeKind() == TimeKind::Static; }
  sem::Time::Static const& getStatic() const { return std::get<0>(time); }
  sem::Time::Static& getStatic() { return std::get<0>(time); }
  bool isDynamic() const { return getTimeKind() == TimeKind::Dynamic; }
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
                       (staticKind, from, to))
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
                       (staticKind, name, attrs))
  static OrgSemKind const staticKind;
  /// \brief Macro name
  Str name = "";
  /// \brief Additional parameters aside from 'exporter',
  sem::AttrGroup attrs;
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
                       (staticKind, name, parameters, positional))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::BigIdent; }
};

/// \brief ~<<target>>~
struct TextTarget : public sem::Leaf {
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Par; }
};

/// \brief ~<<<target>>>~
struct RadioTarget : public sem::Org {
  using Org::Org;
  virtual ~RadioTarget() = default;
  BOOST_DESCRIBE_CLASS(RadioTarget,
                       (Org),
                       (),
                       (),
                       (staticKind, words))
  static OrgSemKind const staticKind;
  Vec<Str> words = {};
  virtual OrgSemKind getKind() const { return OrgSemKind::RadioTarget; }
};

/// \brief Latex code body
struct Latex : public sem::Org {
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

struct Link : public sem::Stmt {
  using Stmt::Stmt;
  virtual ~Link() = default;
  BOOST_DESCRIBE_CLASS(Link,
                       (Stmt),
                       (),
                       (),
                       (staticKind, description, target))
  static OrgSemKind const staticKind;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  sem::LinkTarget target;
  virtual OrgSemKind getKind() const { return OrgSemKind::Link; }
};

/// \brief Center nested content in export
struct BlockCenter : public sem::Block {
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
struct BlockQuote : public sem::Block {
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
struct BlockComment : public sem::Stmt {
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
struct BlockVerse : public sem::Block {
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

struct BlockDynamicFallback : public sem::Block {
  using Block::Block;
  virtual ~BlockDynamicFallback() = default;
  BOOST_DESCRIBE_CLASS(BlockDynamicFallback,
                       (Block),
                       (),
                       (),
                       (staticKind, name))
  static OrgSemKind const staticKind;
  Str name = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockDynamicFallback; }
};

/// \brief Example block
struct BlockExample : public sem::Block {
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
struct BlockExport : public sem::Block {
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
  Str exporter = "";
  Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::BlockExport; }
  /// \brief Return value of the :placement attribute if present
  Opt<Str> getPlacement() const;
};

/// \brief Block of text with admonition tag: 'note',', 'warning','
struct BlockAdmonition : public sem::Block {
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

/// \brief Base class for all code blocks
struct BlockCode : public sem::Block {
  using Block::Block;
  virtual ~BlockCode() = default;
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
                        tangle))
  static OrgSemKind const staticKind;
  /// \brief Code block language name
  Opt<Str> lang = std::nullopt;
  /// \brief Switch options for block
  Vec<sem::BlockCodeSwitch> switches = {};
  /// \brief What to export
  BlockCodeExports exports = BlockCodeExports::Both;
  /// \brief Code evaluation results
  Opt<sem::BlockCodeEvalResult> result = std::nullopt;
  /// \brief Collected code lines
  Vec<sem::BlockCodeLine> lines = {};
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
  BOOST_DESCRIBE_CLASS(SubtreeLog,
                       (Org),
                       (),
                       (),
                       (staticKind,
                        head,
                        desc))
  static OrgSemKind const staticKind;
  sem::SubtreeLogHead head;
  /// \brief Optional description of the log entry
  Opt<sem::SemId<sem::StmtList>> desc = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::SubtreeLog; }
  void setDescription(sem::SemId<sem::StmtList> desc);
};

/// \brief Subtree
struct Subtree : public sem::Org {
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
  Opt<Str> treeId = std::nullopt;
  /// \brief Todo state of the tree
  Opt<Str> todo = std::nullopt;
  /// \brief Task completion state
  Opt<sem::SubtreeCompletion> completion = std::nullopt;
  Opt<sem::SemId<sem::Paragraph>> description = std::nullopt;
  /// \brief Trailing tags
  Vec<sem::SemId<sem::HashTag>> tags = {};
  /// \brief Main title
  sem::SemId<sem::Paragraph> title = sem::SemId<sem::Paragraph>::Nil();
  /// \brief Associated subtree log
  Vec<sem::SemId<sem::SubtreeLog>> logbook = {};
  /// \brief Immediate properties
  Vec<sem::NamedProperty> properties = {};
  /// \brief When subtree was marked as closed
  Opt<UserTime> closed = std::nullopt;
  /// \brief When is the deadline
  Opt<UserTime> deadline = std::nullopt;
  /// \brief When the event is scheduled
  Opt<UserTime> scheduled = std::nullopt;
  /// \brief Subtree is annotated with the COMMENT keyword
  bool isComment = false;
  /// \brief Subtree is tagged with `:ARCHIVE:` tag
  bool isArchived = false;
  Opt<Str> priority = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::Subtree; }
  Vec<sem::SubtreePeriod> getTimePeriods(IntSet<sem::SubtreePeriod::Kind> kinds) const;
  Vec<sem::NamedProperty> getProperties(Str const& kind, Opt<Str> const& subkind = std::nullopt) const;
  Opt<sem::NamedProperty> getProperty(Str const& kind, Opt<Str> const& subkind = std::nullopt) const;
  /// \brief Remove all instances of the property with matching kind/subkind from the property list
  void removeProperty(Str const& kind, Opt<Str> const& subkind = std::nullopt);
  /// \brief Create or override existing property value in the subtree property list
  void setProperty(sem::NamedProperty const& value);
  /// \brief Assign a raw string literal to a property.
  ///
  /// This function will not do the conversion or parsing of the assigned value, so if it is a 'created' or some other property with a typed value, it will still remain as string until the file is written and then parsed back from scratch.
  void setPropertyStrValue(Str const& value, Str const& kind, Opt<Str> const& subkind = std::nullopt);
  /// \brief Get subtree title as a flat string, without markup nodes, but with all left strings
  Str getCleanTitle() const;
};

/// \brief Table cell
struct Cell : public sem::Cmd {
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
struct Row : public sem::Cmd {
  using Cmd::Cmd;
  virtual ~Row() = default;
  BOOST_DESCRIBE_CLASS(Row,
                       (Cmd),
                       (),
                       (),
                       (staticKind, cells, isBlock))
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
                       (staticKind, rows, isBlock))
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::Paragraph; }
  bool isFootnoteDefinition() const;
  Opt<Str> getFootnoteName() const;
  bool hasAdmonition() const;
  Vec<Str> getAdmonitions() const;
  Vec<sem::SemId<sem::BigIdent>> getAdmonitionNodes() const;
  bool hasTimestamp() const;
  Vec<UserTime> getTimestamps() const;
  Vec<sem::SemId<sem::Time>> getTimestampNodes() const;
  bool hasLeadHashtags() const;
  Vec<sem::SemId<sem::HashTag>> getLeadHashtags() const;
  /// \brief Return content of the paragraph, without prefix idents, hashtags, footnotes etc.
  Vec<sem::SemId<sem::Org>> getBody() const;
};

/// \brief Shortened colon example block
struct ColonExample : public sem::Org {
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
struct CmdAttr : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdAttr() = default;
  BOOST_DESCRIBE_CLASS(CmdAttr,
                       (Attached),
                       (),
                       (),
                       (staticKind, target))
  static OrgSemKind const staticKind;
  Str target;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdAttr; }
};

/// \brief Single line of passthrough code
struct CmdExport : public sem::Attached {
  using Attached::Attached;
  virtual ~CmdExport() = default;
  BOOST_DESCRIBE_CLASS(CmdExport,
                       (Attached),
                       (),
                       (),
                       (staticKind, exporter, content))
  static OrgSemKind const staticKind;
  Str exporter = "";
  Str content = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdExport; }
};

/// \brief Inline, statement or block call
struct Call : public sem::Org {
  using Org::Org;
  virtual ~Call() = default;
  BOOST_DESCRIBE_CLASS(Call,
                       (Org),
                       (),
                       (),
                       (staticKind, name, attrs, isCommand))
  static OrgSemKind const staticKind;
  /// \brief Call target name
  Str name;
  /// \brief Additional parameters aside from 'exporter',
  sem::AttrGroup attrs;
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::List; }
  Vec<sem::AttrValue> getListAttrs(Str const& key) const;
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
                        bullet))
  static OrgSemKind const staticKind;
  sem::ListItem::Checkbox checkbox = Checkbox::None;
  /// \brief Description list item header
  Opt<sem::SemId<sem::Paragraph>> header = std::nullopt;
  /// \brief Full text of the numbered list item, e.g. `a)`, `a.`
  Opt<Str> bullet = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::ListItem; }
  bool isDescriptionItem() const;
  /// \brief Return flat text for the description list header
  Opt<Str> getCleanHeader() const;
};

struct DocumentOptions : public sem::Org {
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
  Vec<sem::NamedProperty> properties = {};
  sem::DocumentExportConfig exportConfig;
  Opt<bool> fixedWidthSections = std::nullopt;
  Opt<bool> startupIndented = std::nullopt;
  Opt<Str> category = std::nullopt;
  Opt<Str> setupfile = std::nullopt;
  Opt<int> maxSubtreeLevelExport = std::nullopt;
  Opt<sem::ColumnView> columns = std::nullopt;
  virtual OrgSemKind getKind() const { return OrgSemKind::DocumentOptions; }
  Vec<sem::NamedProperty> getProperties(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
  Opt<sem::NamedProperty> getProperty(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
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
                        exportFileName))
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
  Vec<sem::NamedProperty> getProperties(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
  Opt<sem::NamedProperty> getProperty(Str const& kind, Opt<Str> const& subKind = std::nullopt) const;
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
                        regexp))
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
                       (staticKind))
  static OrgSemKind const staticKind;
  virtual OrgSemKind getKind() const { return OrgSemKind::TextSeparator; }
};

struct DocumentGroup : public sem::Org {
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

struct File : public sem::Org {
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

  using Data = std::variant<sem::File::Document, sem::File::Attachment, sem::File::Source>;
  enum class Kind : short int { Document, Attachment, Source, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Document, Attachment, Source)
  using variant_enum_type = sem::File::Kind;
  using variant_data_type = sem::File::Data;
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
  Str relPath = "";
  /// \brief Absolute resolved path to physical file
  Str absPath = "";
  sem::File::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::File; }
  bool isDocument() const { return getFileKind() == Kind::Document; }
  sem::File::Document const& getDocument() const { return std::get<0>(data); }
  sem::File::Document& getDocument() { return std::get<0>(data); }
  bool isAttachment() const { return getFileKind() == Kind::Attachment; }
  sem::File::Attachment const& getAttachment() const { return std::get<1>(data); }
  sem::File::Attachment& getAttachment() { return std::get<1>(data); }
  bool isSource() const { return getFileKind() == Kind::Source; }
  sem::File::Source const& getSource() const { return std::get<2>(data); }
  sem::File::Source& getSource() { return std::get<2>(data); }
  static sem::File::Kind getFileKind(sem::File::Data const& __input) { return static_cast<sem::File::Kind>(__input.index()); }
  sem::File::Kind getFileKind() const { return getFileKind(data); }
};

struct Directory : public sem::Org {
  using Org::Org;
  virtual ~Directory() = default;
  BOOST_DESCRIBE_CLASS(Directory,
                       (Org),
                       (),
                       (),
                       (staticKind, relPath, absPath))
  static OrgSemKind const staticKind;
  /// \brief Relative path from the root directory, empty if this is the root directory
  Str relPath = "";
  /// \brief Absolute resolved path to physical directory
  Str absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Directory; }
};

struct Symlink : public sem::Org {
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
  Str absPath = "";
  virtual OrgSemKind getKind() const { return OrgSemKind::Symlink; }
};

struct CmdInclude : public sem::Org {
  using Org::Org;
  virtual ~CmdInclude() = default;
  struct IncludeBase {
    BOOST_DESCRIBE_CLASS(IncludeBase, (), (), (), (minLineRange, maxLineRange))
    /// \brief No not include nodes with position before specified line.
    Opt<int> minLineRange = std::nullopt;
    /// \brief Do not include nodes with position after specified line.
    Opt<int> maxLineRange = std::nullopt;
    IncludeBase() {  }
  };

  struct Example : public sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Example, (IncludeBase), (), (), ())
    Example() {  }
  };

  struct Export : public sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Export, (IncludeBase), (), (), ())
    Export() {  }
  };

  struct Src : public sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(Src, (IncludeBase), (), (), ())
    Src() {  }
  };

  struct OrgDocument : public sem::CmdInclude::IncludeBase {
    BOOST_DESCRIBE_CLASS(OrgDocument, (IncludeBase), (), (), (subtreePath, minLevel, customIdTarget))
    /// \brief Include first subtree matching path with `file.org::* tree`
    Opt<Str> subtreePath = std::nullopt;
    /// \brief The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.
    Opt<int> minLevel = std::nullopt;
    /// \brief Include target subtree content with `file.org::#custom`
    Opt<Str> customIdTarget = std::nullopt;
    OrgDocument() {  }
  };

  using Data = std::variant<sem::CmdInclude::Example, sem::CmdInclude::Export, sem::CmdInclude::Src, sem::CmdInclude::OrgDocument>;
  enum class Kind : short int { Example, Export, Src, OrgDocument, };
  BOOST_DESCRIBE_NESTED_ENUM(Kind, Example, Export, Src, OrgDocument)
  using variant_enum_type = sem::CmdInclude::Kind;
  using variant_data_type = sem::CmdInclude::Data;
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
  Str path;
  /// \brief 0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text
  Opt<int> firstLine = std::nullopt;
  /// \brief 0-based index of the last line to include
  Opt<int> lastLine = std::nullopt;
  sem::CmdInclude::Data data;
  virtual OrgSemKind getKind() const { return OrgSemKind::CmdInclude; }
  bool isExample() const { return getIncludeKind() == Kind::Example; }
  sem::CmdInclude::Example const& getExample() const { return std::get<0>(data); }
  sem::CmdInclude::Example& getExample() { return std::get<0>(data); }
  bool isExport() const { return getIncludeKind() == Kind::Export; }
  sem::CmdInclude::Export const& getExport() const { return std::get<1>(data); }
  sem::CmdInclude::Export& getExport() { return std::get<1>(data); }
  bool isSrc() const { return getIncludeKind() == Kind::Src; }
  sem::CmdInclude::Src const& getSrc() const { return std::get<2>(data); }
  sem::CmdInclude::Src& getSrc() { return std::get<2>(data); }
  bool isOrgDocument() const { return getIncludeKind() == Kind::OrgDocument; }
  sem::CmdInclude::OrgDocument const& getOrgDocument() const { return std::get<3>(data); }
  sem::CmdInclude::OrgDocument& getOrgDocument() { return std::get<3>(data); }
  static sem::CmdInclude::Kind getIncludeKind(sem::CmdInclude::Data const& __input) { return static_cast<sem::CmdInclude::Kind>(__input.index()); }
  sem::CmdInclude::Kind getIncludeKind() const { return getIncludeKind(data); }
};

}
/* clang-format on */