#pragma once

#include <memory>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>
#include <hstd/system/aux_utils.hpp>

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Json.hpp>

#include <QDateTime>


#define __define_field_aux(first, second, uppercase, third)               \
    __unpack_pars first second = third;

#define __per_field(class_bases_bases, field) __define_field(field)

#define __get_field_name_aux(a, fieldName, c, d) fieldName
#define __get_field_name(_, arg) , __get_field_name_aux arg
#define __drop_leading_comma(first, ...) __VA_ARGS__

#define __define_field(arg) __define_field_aux arg
#define __define_field_only(_, arg) __define_field_aux arg

#define __pass_args_field_aux(_1, fieldname, _2, _3)                      \
    fieldname(args.fieldname),
#define __pass_args_field(_, arg) __pass_args_field_aux arg

#define EMPTY()

#define DECL_FIELDS(classname, bases, ...)                                \
    FOR_EACH_CALL_WITH_PASS(__per_field, (classname, bases), __VA_ARGS__) \
    struct Args {                                                         \
        FOR_EACH_CALL_WITH_PASS(                                          \
            __define_field_only,                                          \
            (classname, bases),                                           \
            __VA_ARGS__)                                                  \
        __extra_args_fields                                               \
    };                                                                    \
                                                                          \
    inline classname(Args const& args)                                    \
        : FOR_EACH_CALL_WITH_PASS(__pass_args_field, (), __VA_ARGS__)     \
            __extra_args_pass /* This one must be non-empty: At least     \
                                 subnodes must be present*/               \
        {};                                                               \
                                                                          \
    BOOST_DESCRIBE_CLASS(                                                 \
        classname,                                                        \
        bases, /* Expand teh list of fields and leave only the the name   \
                  of the field to be passed to the public members of the  \
                  boost describe */                                       \
        (      /* < Extra wrapping paren, __get_field_name leaves out the \
                  a,b,c,d,e list*/                                        \
         __drop_leading_comma EMPTY()(EXPAND(FOR_EACH_CALL_WITH_PASS(     \
             __get_field_name,                                            \
             () /* < Nothing to pass around */,                           \
             __VA_ARGS__)))),                                             \
        () /* For simplicity reasons, sem nodes have public fields and no \
              protected/private members */                                \
        ,                                                                 \
        ());

#define __extra_args_fields Vec<Wrap<Org>> subnodes = {};
#define __extra_args_pass Org(args.subnodes)


namespace sem {

struct TreeId {
    Str id;
};

BOOST_DESCRIBE_STRUCT(TreeId, (), (id));

template <typename T>
using Wrap = std::shared_ptr<T>;

#define GET_KIND(Kind)                                                    \
    virtual OrgSemKind getKind() const { return OrgSemKind::Kind; }


// Forward-declare all node types so 'asVariant' can be defined directly
// as a part of `Org` API
#define forward_declare(__Kind) struct __Kind;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

#define COMMA ,
#define skip1(op, ...) __VA_ARGS__
#define skip(op, ...) skip1(op)
#define __id(I) , SPtr<I>
#define __variant() std::variant<skip(EACH_SEM_ORG_KIND(__id))>;

/// \brief Global variant of all sem node derivations
using OrgVariant = __variant();

#undef __id
#undef skip
#undef skip1
#undef COMMA
#undef __variant


/// \brief Base class for all org nodes. Provides essential baseline API
/// and information.
struct Org : public std::enable_shared_from_this<Org> {
    // TODO implement 'deepClone' function using visitator node to
    // completely replicate the tree on a structural level

    /// \brief Check if node has a parent pointer (for converted tree only
    /// top-level document should not have parent)
    inline bool hasParent() const { return parent != nullptr; }
    /// \brief Get parent pointer (might be null)
    Org*       getParent() { return parent; }
    Org const* getParent() const { return parent; }

    /// \brief Convert the node to corresponding variant type.
    ///
    /// Intented to be used with custom `std::visit` solutions instead of
    /// relying on the more heavyweight CRTP visitator.
    OrgVariant        asVariant(Ptr<Org> org);
    static OrgVariant fromKind(OrgSemKind kind);

    /// \brief Iteratively get all parent nodes for the subtree
    Vec<Org*> getParentChain(bool withSelf = false) const;
    /// \brief Get closest parent subtree (if it exists)
    Opt<Wrap<Subtree>> getParentSubtree() const;
    /// \brief Get the document wrapping the node (if such document node
    /// exists in hierarchy)
    Opt<Wrap<Document>> getDocument() const;

    /// \brief Pointer to the parent node in sem tree, might be null.
    Org* parent = nullptr;
    /// \brief Adapter to the original parsed node.
    ///
    /// Set by the conversion functions from linearized representation,
    /// will be missing for all generated node kinds.
    OrgAdapter original;

    inline Org(CVec<Wrap<Org>> subnodes = {}) : subnodes(subnodes) {}
    inline Org(Org* parent, OrgAdapter original)
        : parent(parent), original(original) {}

    /// \brief Get get kind of the original node.
    OrgNodeKind getOriginalKind() const { return original.getKind(); }
    /// \brief Get kind of this sem node
    virtual OrgSemKind getKind() const = 0;
    /// \brief Whether original node adapter is missing
    bool isGenerated() const { return original.empty(); }
    /// \brief Location of the node in the original source file
    Opt<LineCol> loc = std::nullopt;
    /// \brief List of subnodes.
    ///
    /// Some of the derived nodes don't make the use of subnode list
    /// (word, punctuation etc), but it was left on the top level of the
    /// hierarchy for conveinience purposes. It is not expected that 'any'
    /// node can have subnodes.
    Vec<Wrap<Org>> subnodes;

    void push_back(Wrap<Org>&& sub) { subnodes.push_back(std::move(sub)); }

    /// \brief Get subnode at specified index
    inline Wrap<Org> at(int idx) { return subnodes[idx]; }

    /// \brief Cast this node to the specified type and return the result.
    /// If the cast fails exception is thrown.
    template <typename T>
    Wrap<T> as() {
        Wrap<T> result = std::static_pointer_cast<T>(shared_from_this());
        Q_ASSERT_X(
            result.get() != nullptr,
            "org-base cast",
            "Could not convert $# to $#"
                % to_string_vec(getKind(), demangle(typeid(T).name())));
        return result;
    }

    /// \brief Overload for constant conversion
    template <typename T>
    Wrap<T> as() const {
        Wrap<T> result = std::static_pointer_cast<T>(shared_from_this());
        Q_ASSERT_X(
            result.get() != nullptr,
            "org-base cast",
            "Could not convert $# to $#"
                % to_string_vec(getKind(), demangle(typeid(T).name())));
        return result;
    }
};

class Attached;

/// \brief Base class for all document-level entries. Note that some node
/// kinds might also have inline entries (examples include links, source
/// code blocks, call blocks)
struct Stmt : public Org {
    using Org::Org;
    Stmt() {}
    Stmt(CVec<Wrap<Attached>> attached, CVec<Wrap<Org>> subnodes)
        : Org(subnodes), attached(attached) {}

    Vec<Wrap<Attached>> attached;
    json                attachedJson() const;

    template <typename T>
    Opt<Wrap<T>> getAttached(OrgSemKind kind);
};

struct Inline : public Org {
    using Org::Org;
};

struct StmtList : public Org {
    using Org::Org;
    GET_KIND(StmtList);
};


struct Row : public Org {
    using Org::Org;
    GET_KIND(Row);
};

struct Table : public Stmt {
    using Stmt::Stmt;
    Vec<Wrap<Row>> rows;
    GET_KIND(Table);
};

struct HashTag : public Inline {
    using Inline::Inline;
    Str                head;
    Vec<Wrap<HashTag>> subtags;
    bool               prefixMatch(CR<Vec<Str>> prefix) const;

    GET_KIND(HashTag);
};

/// \brief Completion status of the subtree or list element
struct Completion : public Inline {
    using Inline::Inline;
    /// \brief Number of completed tasks
    int done = 0;
    /// \brief Full number of tasks
    int  full      = 0;
    bool isPercent = false;

    GET_KIND(Completion);
};

BOOST_DESCRIBE_STRUCT(Completion, (), (done, full, isPercent));


struct Paragraph : public Stmt {
    using Stmt::Stmt;
    GET_KIND(Paragraph);
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {
    using Org::Org;
};

/// \brief Center nested content in the exporrt
struct Center : public Format {
    using Format::Format;
    GET_KIND(Center);
};

/// \brief Base class for block or line commands
struct Command : public Stmt {
    using Stmt::Stmt;
};

/// \brief Single-line commands
struct LineCommand : public Command {
    using Command::Command;
};

/// \brief Standalone line commands that can be placed individually on the
/// top level and don't have to be attached to any subsequent element
struct Standalone : public LineCommand {
    using LineCommand::LineCommand;
};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {
    using LineCommand::LineCommand;
};


/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
    using Attached::Attached;
    Wrap<Paragraph> text;
    GET_KIND(Caption);
};

/// \brief Multiple attachable commands will get grouped into this element
/// unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
    using Stmt::Stmt;
    GET_KIND(CommandGroup);
};

/// \brief Block command type
struct Block : public Command {
    using Command::Command;
};

/// \brief Quotation block
struct Quote : public Block {
    using Block::Block;
    Wrap<Paragraph> text;
    GET_KIND(Quote);
};

/// \brief Example block
struct Example : public Block {
    using Block::Block;
    GET_KIND(Example);
};

/// \brief Base class for all code blocks
struct Code : public Block {
    using Block::Block;
    GET_KIND(Code);

    /// \brief Extra configuration switches that can be used to control
    /// representation of the rendered code block. This field does not
    /// exactly correspond to the `-XX` parameters that can be passed
    /// directly in the field, but also works with attached `#+options`
    /// from the block
    struct Switch {
        /// \brief Enumerate code lines starting from `start` value
        /// instead of default indexing.
        struct LineStart {
            /// \brief First line number
            int start = 0;
            /// \brief  Continue numbering from the previous block instead
            /// of starting anew
            bool extendLast = false;
        };

        struct CalloutFormat {
            Str format;
        };

        struct RemoveCallout {
            bool remove = true;
        };

        /// \brief Emphasize single line -- can be repeated multiple times
        struct EmphasizeLine {
            int line;
        };

        struct Dedent {
            int value;
        };

        SUB_VARIANTS(
            Kind,
            Data,
            data,
            getKind,
            LineStart,
            CalloutFormat,
            RemoveCallout,
            EmphasizeLine,
            Dedent);

        Data data;
    };


    Vec<Switch> switches;

    /// Code language name -- does not have to be skipped, although in
    /// most cases it is actually used
    Opt<Str> lang;

    Opt<Str> session;
    enum class Results
    {
        Replace,
    };

    BOOST_DESCRIBE_NESTED_ENUM(Results, Replace);

    enum class Exports
    {
        None,
        Both,
        Code,
        Results
    };

    BOOST_DESCRIBE_NESTED_ENUM(Exports, None, Both, Code, Results);

    Exports exports = Exports::Both;
    bool    cache   = false;
    bool    eval    = false;
    bool    noweb   = false;
    bool    hlines  = false;
    bool    tangle  = false;
};


/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public Org {
    GET_KIND(Time);
    using Org::Org;

    /// Repetition for static time
    struct Repeat {
        enum class Mode
        {
            None,
            Exact,
            /// Repeat on the first matching day in the future
            FirstMatch,
            /// Repeat task on the same day next week/month/year etc.
            SameDay
        };
        BOOST_DESCRIBE_NESTED_ENUM(Mode, None, Exact, FirstMatch, SameDay);

        Mode mode;

        /// Repetition period. Temporary placeholder for now, until I
        /// figure out what would be the proper way to represent whatever
        /// org can do ... which is to be determined as well
        enum class Period
        {
            Year,
            Month,
            Week,
            Day,
            Hour,
            Minute,
        };

        BOOST_DESCRIBE_NESTED_ENUM(
            Period,
            Year,
            Month,
            Week,
            Day,
            Hour,
            Minute);

        Period period;
        int    count;
    };

    Time(CR<QDateTime> time)
        : time(Static{.time = time}), Org(nullptr, OrgAdapter()) {}

    struct Static {
        Opt<Repeat> repeat;
        QDateTime   time;
        /// Simplified time such as `12:20` can be used in subtree
        /// titles in conjunction with dynamic (diary) times.
        bool simpleTime;
    };
    /// Active timestamp with evaluatable code expression inside, also
    /// called diary time
    struct Dynamic {
        Str expr;
    };
    bool isActive = false;

    SUB_VARIANTS(
        TimeKind,
        TimeVariant,
        time,
        getTimeKind,
        Static,
        Dynamic);

    TimeVariant time;
    bool isStatic() const { return std::holds_alternative<Static>(time); }
};


/// Time range delimited by two points
struct TimeRange : public Org {
    GET_KIND(TimeRange);
    using Org::Org;
    Wrap<Time> from;
    Wrap<Time> to;
};

BOOST_DESCRIBE_STRUCT(TimeRange, (Org), (from, to));

struct SubtreeLog : public Org {
    GET_KIND(SubtreeLog);
    using Org::Org;
    struct Note {
        Wrap<Time> on;
    };

    struct Refile {
        Wrap<Time> on;
    };

    /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30
    /// Sun 14:51:16] => 1:22`
    struct Clock {
        Variant<Wrap<Time>, Wrap<TimeRange>> range;
    };

    /// \brief Change of the subtree state -- `- State "WIP" from "TODO"
    /// [2023-04-30 Sun 13:29:04]`
    struct State {
        OrgBigIdentKind from;
        OrgBigIdentKind to;
        Wrap<Time>      on;
    };

    /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on
    /// [2023-04-30 Sun 13:29:06]`
    struct Tag {
        Wrap<HashTag> tag;
        bool          added = false;
    };

    SUB_VARIANTS(
        Kind,
        LogEntry,
        log,
        getLogKind,
        Note,
        Refile,
        Clock,
        State,
        Tag);
    LogEntry log;
};

BOOST_DESCRIBE_STRUCT(SubtreeLog, (Org), (log));

struct Subtree : public Org {
    GET_KIND(Subtree);
    using Org::Org;

    struct Period {
        enum class Kind : short int
        {
            /// Time period of the task execution.
            Clocked,
            /// Date of task execution start plus it's estimated effort
            /// duration. If the latter one is missing then only a single
            /// time point is returned
            Scheduled,
            /// Single point or time range used in title. Single point can
            /// also be a simple time, such as `12:20`
            Titled,
            /// Date of task completion. Must be a single time point
            Deadline,
            /// When the subtree was created
            Created,
            /// Last repeat time of the recurring tasks
            Repeated,
        };

        Wrap<Time>&      getTime() { return std::get<Wrap<Time>>(period); }
        Wrap<TimeRange>& getTimeRange() {
            return std::get<Wrap<TimeRange>>(period);
        }

        Variant<Wrap<Time>, Wrap<TimeRange>> period;
        Kind                                 kind;
        Period(CR<Variant<Wrap<Time>, Wrap<TimeRange>>> period, Kind kind)
            : period(period), kind(kind) {}
    };

    Vec<Period> getTimePeriods(IntSet<Period::Kind> kinds);

    struct Property {
        struct Ordered {
            bool isOrdered;
        };

        struct ExportOptions {
            Str                    backend;
            UnorderedMap<Str, Str> values;
        };

        struct Nonblocking {
            bool isBlocking;
        };

        struct Trigger {
            struct Dependency {
                TreeId   id;
                Opt<Str> state;
            };
        };

        struct Blocker {
            Vec<Str> blockers;
        };

        struct Unnumbered {};

        struct Created {
            QDateTime time;
        };


        DECL_DESCRIBED_ENUM(SetMode, Override, Add, Subtract);
        DECL_DESCRIBED_ENUM(
            InheritanceMode,
            ThisAndSub,
            OnlyThis,
            OnlySub);

        SetMode         mainSetRule     = SetMode::Override;
        SetMode         subSetRule      = SetMode::Override;
        InheritanceMode inheritanceMode = InheritanceMode::ThisAndSub;

        //! [declare variant field for subtree properties]
        SUB_VARIANTS(
            Kind,    // Name of the property kind discriminant enum
            Data,    // Type of the value used to hold all the property
                     // variants
            data,    // Field itself
            getKind, // Method name to get the kind of the property
            Ordered, // List of nested structures -- it will be converted
                     // to list of defined enums etc.
            ExportOptions,
            Nonblocking,
            Trigger,
            Blocker,
            Unnumbered,
            Created);

        // Variant field is declared separately from the helper
        // definitions
        Data data;
        //! [declare variant field for subtree properties]

        Property(CR<Data> data) : data(data) {}
    };


    DECL_FIELDS(
        Subtree,
        (Org),
        ((int), level, Level, 0),
        ((Opt<Str>), id, Id, std::nullopt),
        ((Opt<Str>), todo, Todo, std::nullopt),
        ((Opt<Wrap<Completion>>), completion, Completion, std::nullopt),
        ((Vec<Wrap<HashTag>>), tags, Tags, {}),
        ((Wrap<Paragraph>), title, Title, nullptr),
        ((Opt<Wrap<Paragraph>>), description, Description, std::nullopt),
        ((Vec<Wrap<SubtreeLog>>), logbook, Logbook, {}),
        ((Vec<Property>), properties, Properties, {}),
        ((Opt<Wrap<Time>>), closed, Closed, std::nullopt),
        ((Opt<Wrap<Time>>), deadline, Deadline, std::nullopt),
        ((Opt<Wrap<Time>>), scheduled, Scheduled, std::nullopt));


    Vec<Property> getProperties(
        Property::Kind kind,
        CR<QString>    subkind = "") const;
    Opt<Property> getProperty(
        Property::Kind kind,
        CR<QString>    subkind = "") const;
    Vec<Property> getContextualProperties(
        Property::Kind kind,
        CR<QString>    subkind = "") const;
    Opt<Property> getContextualProperty(
        Property::Kind kind,
        CR<QString>    subkind = "") const;
};

struct LatexBody : public Org {
    using Org::Org;
};

struct InlineMath : public LatexBody {
    using LatexBody::LatexBody;
    GET_KIND(InlineMath);
};


struct Leaf : public Org {
    Str text;
    using Org::Org;
};

// clang-format off
struct Newline : public Leaf { GET_KIND(Newline); using Leaf::Leaf; };
struct Space : public Leaf { GET_KIND(Space); using Leaf::Leaf; };
struct Word : public Leaf { GET_KIND(Word); using Leaf::Leaf; };
struct RawText : public Leaf { GET_KIND(RawText); using Leaf::Leaf; };
struct Punctuation : public Leaf { GET_KIND(Punctuation); using Leaf::Leaf; };
struct Placeholder : public Leaf { GET_KIND(Placeholder); using Leaf::Leaf; };
struct BigIdent : public Leaf { GET_KIND(BigIdent); using Leaf::Leaf; };

// clang-format on

struct Markup : public Org {
    using Org::Org;
};

// clang-format off
struct Bold : public Markup { using Markup::Markup; GET_KIND(Bold); };
struct Monospace : public Markup { using Markup::Markup; GET_KIND(Monospace); };
struct MarkQuote : public Markup { using Markup::Markup; GET_KIND(MarkQuote); };
struct Verbatim : public Markup { using Markup::Markup; GET_KIND(Verbatim); };
struct Italic : public Markup { using Markup::Markup; GET_KIND(Italic); };
struct Strike : public Markup { using Markup::Markup; GET_KIND(Strike); };
struct Par : public Markup { using Markup::Markup; GET_KIND(Par); };
// clang-format on


struct List : public Org {
    using Org::Org;
    GET_KIND(List);
};

struct ListItem : public Org {
    using Org::Org;
    GET_KIND(ListItem);
    enum class Checkbox
    {
        None,
        Done,
        Empty
    };

    BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty);

    Checkbox checkbox;

    Opt<Wrap<Paragraph>> header;
};

struct Link : public Org {
    GET_KIND(Link);
    using Org::Org;
    struct Raw {
        Str text;
    };

    struct Id {
        Str text;
    };

    struct Footnote {
        Str target;
    };

    SUB_VARIANTS(Kind, Data, data, getLinkKind, Raw, Footnote, Id);
    Data data;

    Opt<Wrap<Paragraph>> description;
};


struct Document : public Org {
    using Org::Org;
    GET_KIND(Document);

    Opt<Wrap<Paragraph>> title;
    Opt<Wrap<Paragraph>> author;
    Opt<Wrap<Paragraph>> creator;
    Opt<Wrap<RawText>>   email;
    Opt<Vec<Str>>        language;
    Opt<Str>             exportFileName;

    struct Options {
        bool smartQuotes         = false;
        bool emphasizedText      = false;
        bool specialStrings      = false;
        bool fixedWidthSections  = false;
        bool includeTimestamps   = false;
        bool preserveLineBreaks  = false;
        bool plaintextSubscripts = false;
        bool exportArchived      = false;
        bool exportWithAuthor    = false;
        bool exportBrokenLinks   = false;
        bool exportWithClock     = false;
        bool exportWithCreator   = false;
    };

    UnorderedMap<Str, Wrap<Subtree>> idTable;
    UnorderedMap<Str, Org*>          nameTable;
    UnorderedMap<Str, Org*>          anchorTable;
    UnorderedMap<Str, Org*>          footnoteTable;

    Opt<Wrap<Subtree>> getSubtree(CR<Str> id) { return idTable.get(id); }
};

struct DocumentGroup : public Org {
    using Org::Org;
    GET_KIND(DocumentGroup);
};

template <typename T>
Opt<Wrap<T>> Stmt::getAttached(OrgSemKind kind) {
    for (const auto& sub : attached) {
        if (sub->getKind() == kind) {
            return sub->as<T>();
        }
    }

    return std::nullopt;
}


}; // namespace sem

#undef GET_KIND
#undef DECL_FIELDS
