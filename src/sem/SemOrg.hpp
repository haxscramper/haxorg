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
                                                                          \
    /* For named arguments and aggregate initialization of any type */    \
    struct Args {                                                         \
        FOR_EACH_CALL_WITH_PASS(                                          \
            __define_field_only,                                          \
            (classname, bases),                                           \
            __VA_ARGS__)                                                  \
        __extra_args_fields                                               \
    };                                                                    \
                                                                          \
    /* Declare shared pointer constructor  */                             \
    static inline Wrap<classname> shared(Args const& args) {              \
        return std::make_shared<classname>(args);                         \
    }                                                                     \
                                                                          \
    /* Constructor accepting aux 'args' object */                         \
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
    virtual OrgSemKind getKind() const { return OrgSemKind::Kind; }       \
    using Ptr = Wrap<Kind>;


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
    using Ptr = Wrap<Org>;

    /// \brief Convert the node to corresponding variant type.
    ///
    /// Intented to be used with custom `std::visit` solutions instead of
    /// relying on the more heavyweight CRTP visitator.
    OrgVariant        asVariant();
    static OrgVariant fromKind(OrgSemKind kind);

    using SubnodeVisitor = Func<void(Wrap<Org>)>;
    /// \brief Recursively visit each subnode in the tree and apply the
    /// provided callback
    void eachSubnodeRec(SubnodeVisitor cb);

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
    /// \brief Extra ID assigned to the org nodes.
    Opt<int> id = std::nullopt;
    /// \brief Recursively walk the tree and assign new ID values to every
    /// node
    void assignIds();
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

    bool is(OrgSemKind kind) const { return getKind() == kind; }
    bool is(CR<SemSet> kinds) const { return kinds.contains(getKind()); }

    BOOST_DESCRIBE_CLASS(Org, (), (subnodes), (), ());
};

class Attached;

#define __extra_args_pass Org(args.subnodes)
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
    BOOST_DESCRIBE_CLASS(Stmt, (Org), (), (), ());
};

struct Inline : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Inline, (Org), (), (), ());
};

struct StmtList : public Org {
    using Org::Org;
    GET_KIND(StmtList);
    DECL_FIELDS(StmtList, (Org));
};

struct Empty : public Org {
    using Org::Org;
    GET_KIND(Empty);
    DECL_FIELDS(Empty, (Org));
};

struct Row : public Org {
    using Org::Org;
    GET_KIND(Row);
    DECL_FIELDS(Row, (Org));
};

#define __extra_args_pass Stmt(args.subnodes)
struct Table : public Stmt {
    using Stmt::Stmt;
    GET_KIND(Table);
    DECL_FIELDS(Table, (Stmt), ((Vec<Wrap<Row>>), rows, Rows, {}))
};

#define __extra_args_pass Inline(args.subnodes)
struct HashTag : public Inline {
    using Inline::Inline;

    bool prefixMatch(CR<Vec<Str>> prefix) const;

    GET_KIND(HashTag);
    DECL_FIELDS(
        HashTag,
        (Inline),
        ((Str), head, Head, ""),
        ((Vec<Wrap<HashTag>>), subtags, Subtags, {}));
};

struct Footnote : public Inline {
    using Inline::Inline;

    GET_KIND(Footnote);
    DECL_FIELDS(
        Footnote,
        (Inline),
        ((Str), tag, Tag, ""),
        ((Opt<Org::Ptr>), definition, Definition, std::nullopt));
};

#define __extra_args_pass Inline(args.subnodes)
/// \brief Completion status of the subtree or list element
struct Completion : public Inline {
    using Inline::Inline;
    GET_KIND(Completion);
    DECL_FIELDS(
        Completion,
        (Inline),
        /// \brief Number of completed tasks
        ((int), done, Done, 0),
        /// \brief Full number of tasks
        ((int), full, Full, 0),
        ((bool), isPercent, IsPercent, false));
};


#define __extra_args_pass Stmt(args.subnodes)
struct Paragraph : public Stmt {
    using Stmt::Stmt;
    GET_KIND(Paragraph);
    DECL_FIELDS(Paragraph, (Stmt));

    bool isFootnoteDefinition() const {
        return !subnodes.empty() && subnodes[0]->is(OrgSemKind::Footnote);
    }
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Format, (Org), (), (), ());
};

#define __extra_args_pass Format(args.subnodes)
/// \brief Center nested content in the exporrt
struct Center : public Format {
    using Format::Format;
    GET_KIND(Center);
    DECL_FIELDS(Center, (Format));
};

/// \brief Base class for block or line commands
struct Command : public Stmt {
    using Stmt::Stmt;
    BOOST_DESCRIBE_CLASS(Command, (Stmt), (), (), ());
};

/// \brief Single-line commands
struct LineCommand : public Command {
    using Command::Command;
    BOOST_DESCRIBE_CLASS(LineCommand, (Command), (), (), ());
};


/// \brief Standalone line commands that can be placed individually on the
/// top level and don't have to be attached to any subsequent element
struct Standalone : public LineCommand {
    using LineCommand::LineCommand;
    BOOST_DESCRIBE_CLASS(Standalone, (LineCommand), (), (), ());
};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {
    using LineCommand::LineCommand;
    BOOST_DESCRIBE_CLASS(Attached, (LineCommand), (), (), ());
};


#define __extra_args_pass Attached(args.subnodes)
/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
    using Attached::Attached;
    Wrap<Paragraph> text;
    GET_KIND(Caption);
    DECL_FIELDS(Caption, (Attached));
};

#define __extra_args_pass Stmt(args.subnodes)
/// \brief Multiple attachable commands will get grouped into this element
/// unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
    using Stmt::Stmt;
    GET_KIND(CommandGroup);
    DECL_FIELDS(CommandGroup, (Stmt));
};

#define __extra_args_pass Command(args.subnodes)
/// \brief Block command type
struct Block : public Command {
    using Command::Command;
    BOOST_DESCRIBE_CLASS(Block, (Command), (), (), ());
};

#define __extra_args_pass Block(args.subnodes)
/// \brief Quotation block
struct Quote : public Block {
    using Block::Block;
    Wrap<Paragraph> text;
    GET_KIND(Quote);
    DECL_FIELDS(Quote, (Block));
};

/// \brief Example block
struct Example : public Block {
    using Block::Block;
    GET_KIND(Example);
    DECL_FIELDS(Example, (Block));
};

struct AdmonitionBlock : public Block {
    using Block::Block;
    GET_KIND(AdmonitionBlock);
    DECL_FIELDS(AdmonitionBlock, (Block));
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


    DECL_FIELDS(
        Code,
        (Org),
        /// Code language name -- does not have to be skipped, although in
        /// most cases it is actually used
        ((Opt<Str>), lang, Lang, std::nullopt),
        ((Vec<Switch>), switches, Switches, {}),
        ((Opt<Str>), session, Session, std::nullopt),
        ((Exports), exports, Exports, Exports::Both),
        ((bool), cache, Cache, false),
        ((bool), eval, Eval, false),
        ((bool), noweb, Noweb, false),
        ((bool), hlines, Hlines, false),
        ((bool), tangle, Tangle, false), );
};


#define __extra_args_pass Org(args.subnodes)
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

    SUB_VARIANTS(
        TimeKind,
        TimeVariant,
        time,
        getTimeKind,
        Static,
        Dynamic);

    DECL_FIELDS(
        Time,
        (Org),
        ((TimeVariant), time, Time, Static{}),
        ((bool), isActive, IsActive, false));

    bool isStatic() const { return std::holds_alternative<Static>(time); }
};


/// Time range delimited by two points
struct TimeRange : public Org {
    GET_KIND(TimeRange);
    using Org::Org;

    DECL_FIELDS(
        TimeRange,
        (Org),
        ((Wrap<Time>), from, From, nullptr),
        ((Wrap<Time>), to, To, nullptr));
};

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

    DECL_FIELDS(
        SubtreeLog,
        (Org), //
        ((LogEntry), log, Log, Note{}));
};

#define __extra_args_pass Org(args.subnodes)
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
        struct ExportLatexClass {
            QString latexClass;
        };

        struct ExportLatexHeader {
            QString header;
        };

        struct ExportLatexCompiler {
            QString compiler;
        };

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

        struct Origin {
            QString text;
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
            Origin,
            ExportLatexHeader,
            ExportLatexCompiler,
            ExportLatexClass,
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
        ((Opt<Str>), treeId, TreeId, std::nullopt),
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
    BOOST_DESCRIBE_CLASS(LatexBody, (Org), (), (), ());
};

#define __extra_args_pass LatexBody(args.subnodes)
struct InlineMath : public LatexBody {
    using LatexBody::LatexBody;
    GET_KIND(InlineMath);
    DECL_FIELDS(InlineMath, (LatexBody));
};


#define __extra_args_pass Org(args.subnodes)
struct Leaf : public Org {
    using Org::Org;
    Leaf(CR<Str> text) : text(text) {}
    Str text = "";
    BOOST_DESCRIBE_CLASS(Leaf, (Org), (text), (), ());
};

#define __extra_args_fields Str text = "";
#define __extra_args_pass Leaf(args.text)

struct Escaped : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Escaped);
    DECL_FIELDS(Escaped, (Leaf));
};

struct Newline : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Newline);
    DECL_FIELDS(Newline, (Leaf));
};

struct Space : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Space);
    DECL_FIELDS(Space, (Leaf));
};

struct Word : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Word);
    DECL_FIELDS(Word, (Leaf));
};

struct AtMention : public Leaf {
    using Leaf::Leaf;
    GET_KIND(AtMention);
    DECL_FIELDS(AtMention, (Leaf));
};

struct RawText : public Leaf {
    using Leaf::Leaf;
    GET_KIND(RawText);
    DECL_FIELDS(RawText, (Leaf));
};

struct Punctuation : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Punctuation);
    DECL_FIELDS(Punctuation, (Leaf));
};

struct Placeholder : public Leaf {
    using Leaf::Leaf;
    GET_KIND(Placeholder);
    DECL_FIELDS(Placeholder, (Leaf));
};

struct BigIdent : public Leaf {
    using Leaf::Leaf;
    GET_KIND(BigIdent);
    DECL_FIELDS(BigIdent, (Leaf));
};


#define EACH_SEM_ORG_LEAF_KIND(__IMPL)                                    \
    __IMPL(Newline)                                                       \
    __IMPL(Space)                                                         \
    __IMPL(Word)                                                          \
    __IMPL(RawText)                                                       \
    __IMPL(Punctuation)                                                   \
    __IMPL(Placeholder)                                                   \
    __IMPL(BigIdent)

#define __extra_args_fields Vec<Wrap<Org>> subnodes = {};
#define __extra_args_pass Org(args.subnodes)

struct Markup : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Markup, (Org), (), (), ());
};

#define __extra_args_pass Markup(args.subnodes)

struct Bold : public Markup {
    using Markup::Markup;
    GET_KIND(Bold);
    DECL_FIELDS(Bold, (Markup));
};

struct Underline : public Markup {
    using Markup::Markup;
    GET_KIND(Underline);
    DECL_FIELDS(Underline, (Markup));
};

struct Monospace : public Markup {
    using Markup::Markup;
    GET_KIND(Monospace);
    DECL_FIELDS(Monospace, (Markup));
};

struct MarkQuote : public Markup {
    using Markup::Markup;
    GET_KIND(MarkQuote);
    DECL_FIELDS(MarkQuote, (Markup));
};

struct Verbatim : public Markup {
    using Markup::Markup;
    GET_KIND(Verbatim);
    DECL_FIELDS(Verbatim, (Markup));
};

struct Italic : public Markup {
    using Markup::Markup;
    GET_KIND(Italic);
    DECL_FIELDS(Italic, (Markup));
};

struct Strike : public Markup {
    using Markup::Markup;
    GET_KIND(Strike);
    DECL_FIELDS(Strike, (Markup));
};

struct Par : public Markup {
    using Markup::Markup;
    GET_KIND(Par);
    DECL_FIELDS(Par, (Markup));
};

#define __extra_args_pass Org(args.subnodes)

struct List : public Org {
    using Org::Org;
    GET_KIND(List);
    DECL_FIELDS(List, (Org));

    bool isDescriptionList() const;
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

    bool isDescriptionItem() { return header.has_value(); }

    BOOST_DESCRIBE_NESTED_ENUM(Checkbox, None, Done, Empty);

    DECL_FIELDS(
        ListItem,
        (Org),
        ((Checkbox), checkbox, Checkbox, Checkbox::None),
        ((Opt<Wrap<Paragraph>>), header, Header, std::nullopt));
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

    DECL_FIELDS(
        Link,
        (Org),
        ((Data), data, Data, Raw{}),
        ((Opt<Wrap<Paragraph>>), description, Description, std::nullopt));
};

struct ParseError : public Org {
    using Org::Org;
    GET_KIND(ParseError);
    DECL_FIELDS(ParseError, (Org));
};


struct FileTarget : public Org {
    using Org::Org;
    GET_KIND(FileTarget);
    DECL_FIELDS(
        FileTarget,
        (Org),
        ((QString), path, Path, ""),
        ((Opt<int>), line, Line, std::nullopt),
        ((Opt<QString>), searchTarget, SearchTarget, std::nullopt),
        ((bool), restrictToHeadlines, RestrictToHeadlines, false),
        ((Opt<QString>), targetId, TargetId, std::nullopt),
        ((Opt<QString>), regexp, Regexp, std::nullopt));
};

struct TextSeparator : public Org {
    using Org::Org;
    GET_KIND(TextSeparator);
    DECL_FIELDS(TextSeparator, (Org));
};

struct Include : public Org {
    using Org::Org;
    GET_KIND(Include);

    struct Example {};
    struct Export {};
    struct Src {};
    struct OrgDocument {};

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getIncludeKind,
        Example,
        Export,
        Src,
        OrgDocument);

    DECL_FIELDS(
        Include,
        (Org),
        ((Data), data, Data, OrgDocument{}),
        ((Opt<Wrap<Org>>),
         includedDocument,
         IncludedDocument,
         std::nullopt));
};


struct DocumentOptions : public Org {
    using Org::Org;
    GET_KIND(DocumentOptions);

    DECL_DESCRIBED_ENUM(BrokenLinks, Raise, Ignore, Mark);

    DECL_FIELDS(
        DocumentOptions,
        (Org),
        ((BrokenLinks), brokenLinks, BrokenLinks, BrokenLinks::Mark),
        /// Properties that can be shared by both subtree and document. Not
        /// all make sense in the document, but most do.
        ((Vec<Subtree::Property>), properties, Properties, {}),
        ((bool), smartQuotes, SmartQuotes, false),
        ((bool), emphasizedText, EmphasizedText, false),
        ((bool), specialStrings, SpecialStrings, false),
        ((bool), fixedWidthSections, FixedWidthSections, false),
        ((bool), includeTimestamps, IncludeTimestamps, false),
        ((bool), preserveLineBreaks, PreserveLineBreaks, false),
        ((bool), plaintextSubscripts, PlaintextSubscripts, false),
        ((bool), exportArchived, ExportArchived, false),
        ((bool), exportWithAuthor, ExportWithAuthor, false),
        ((bool), exportBrokenLinks, ExportBrokenLinks, false),
        ((bool), exportWithClock, ExportWithClock, false),
        ((bool), exportWithCreator, ExportWithCreator, false));
};

struct Document : public Org {
    using Org::Org;
    GET_KIND(Document);


    DECL_FIELDS(
        Document,
        (Org),
        ((UnorderedMap<int, Wrap<Org>>), backPtr, BackPtr, {}),
        ((UnorderedMap<Str, int>), idTable, IdTable, {}),
        ((UnorderedMap<Str, int>), nameTable, NameTable, {}),
        ((UnorderedMap<Str, int>), anchorTable, AnchorTable, {}),
        ((UnorderedMap<Str, int>), footnoteTable, FootnoteTable, {}),
        ((Opt<Wrap<Paragraph>>), title, Title, std::nullopt),
        ((Opt<Wrap<Paragraph>>), author, Author, std::nullopt),
        ((Opt<Wrap<Paragraph>>), creator, Creator, std::nullopt),
        ((Opt<Wrap<RawText>>), email, Email, std::nullopt),
        ((Opt<Vec<Str>>), language, Language, std::nullopt),
        ((Wrap<DocumentOptions>), options, Options, nullptr),
        ((Opt<Str>), exportFileName, ExportFileName, std::nullopt));


    Opt<Wrap<Org>>     getTree(int id) { return backPtr.get(id); }
    Opt<Wrap<Subtree>> getSubtree(CR<Str> id);
    Opt<Wrap<Org>>     resolve(CR<Wrap<Org>> node);
};

struct DocumentGroup : public Org {
    using Org::Org;
    GET_KIND(DocumentGroup);
    DECL_FIELDS(DocumentGroup, (Org));
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

template <typename T>
concept NotOrg = !
std::derived_from<typename remove_smart_pointer<T>::type, sem::Org>;

template <typename T>
concept IsOrg = std::
    derived_from<typename remove_smart_pointer<T>::type, sem::Org>;

}; // namespace sem

#undef GET_KIND
#undef DECL_FIELDS
