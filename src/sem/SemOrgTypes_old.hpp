#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <functional>

#include <QDateTime>

#include <sem/SemOrgBase.hpp>

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
           of the field to be passed to the public members of the         \
           boost describe */                                              \
        (      /* < Extra wrapping paren, __get_field_name leaves out the \
            a,b,c,d,e list*/                                              \
         __drop_leading_comma EMPTY()(EXPAND(FOR_EACH_CALL_WITH_PASS(     \
             __get_field_name,                                            \
             () /* < Nothing to pass around */,                           \
             __VA_ARGS__)))),                                             \
        () /* For simplicity reasons, sem nodes have public fields and no \
              protected/private members */                                \
        ,                                                                 \
        ());

#define __extra_args_fields                                               \
    Vec<SemId> subnodes = {};                                             \
    SemId      parent   = SemId::Nil();

#define __extra_args_pass Org(args.parent, args.subnodes)


namespace sem {

#define DECL_KIND(Kind)                                                   \
    virtual OrgSemKind  getKind() const { return OrgSemKind::Kind; }      \
    static SemIdT<Kind> create(                                           \
        SemId parent, Opt<OrgAdapter> original = std::nullopt);           \
    static const OrgSemKind staticKind;


class Attached;

#define __extra_args_pass Org(args.parent, args.subnodes)
/// \brief Base class for all document-level entries. Note that some node
/// kinds might also have inline entries (examples include links, source
/// code blocks, call blocks)
struct Stmt : public Org {
    using Org::Org;
    Stmt() {}
    Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes)
        : Org(parent, subnodes), attached(attached) {}

    Vec<SemId> attached;
    Opt<SemId> getAttached(OrgSemKind kind);
    BOOST_DESCRIBE_CLASS(Stmt, (Org), (), (), ());
};

struct Inline : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Inline, (Org), (), (), ());
};

struct StmtList : public Org {
    using Org::Org;
    DECL_KIND(StmtList);
    DECL_FIELDS(StmtList, (Org));
};

struct Empty : public Org {
    using Org::Org;
    DECL_KIND(Empty);
    DECL_FIELDS(Empty, (Org));
};

struct Row : public Org {
    using Org::Org;
    DECL_KIND(Row);
    DECL_FIELDS(Row, (Org));
};

#define __extra_args_pass Stmt(args.parent, args.subnodes)
struct Table : public Stmt {
    using Stmt::Stmt;
    DECL_KIND(Table);
    DECL_FIELDS(Table, (Stmt), ((Vec<SemIdT<Row>>), rows, Rows, {}))
};

#define __extra_args_pass Inline(args.parent, args.subnodes)
struct HashTag : public Inline {
    using Inline::Inline;

    bool prefixMatch(CR<Vec<Str>> prefix) const;

    DECL_KIND(HashTag);
    DECL_FIELDS(
        HashTag,
        (Inline),
        ((Str), head, Head, ""),
        ((Vec<SemIdT<HashTag>>), subtags, Subtags, {}));
};

/// \brief Inline and regular footnote definition.
///
/// \note in-text link to the footnotes are implemented using `Link` nodes
struct Footnote : public Inline {
    using Inline::Inline;

    DECL_KIND(Footnote);
    DECL_FIELDS(
        Footnote,
        (Inline),
        ((Str), tag, Tag, ""),
        ((Opt<SemId>), definition, Definition, std::nullopt));
};

#define __extra_args_pass Inline(args.parent, args.subnodes)
/// \brief Completion status of the subtree or list element
struct Completion : public Inline {
    using Inline::Inline;
    DECL_KIND(Completion);
    DECL_FIELDS(
        Completion,
        (Inline),
        /// \brief Number of completed tasks
        ((int), done, Done, 0),
        /// \brief Full number of tasks
        ((int), full, Full, 0),
        ((bool), isPercent, IsPercent, false));
};


#define __extra_args_pass Stmt(args.parent, args.subnodes)

struct Paragraph : public Stmt {
    using Stmt::Stmt;
    DECL_KIND(Paragraph);
    DECL_FIELDS(Paragraph, (Stmt));

    bool isFootnoteDefinition() const {
        return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote);
    }
};

/// \brief Base class for branch of formatting node classes
struct Format : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Format, (Org), (), (), ());
};

#define __extra_args_pass Format(args.parent, args.subnodes)
/// \brief Center nested content in the exporrt
struct Center : public Format {
    using Format::Format;
    DECL_KIND(Center);
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


#define __extra_args_pass Attached(args.parent, args.subnodes)
/// \brief Caption annotation for any subsequent node
struct Caption : public Attached {
    using Attached::Attached;
    SemIdT<Paragraph> text = SemIdT<Paragraph>::Nil();
    DECL_KIND(Caption);
    DECL_FIELDS(Caption, (Attached));
};

#define __extra_args_pass Stmt(args.parent, args.subnodes)
/// \brief Multiple attachable commands will get grouped into this element
/// unless it is possible to attached them to some adjacent block command
struct CommandGroup : public Stmt {
    using Stmt::Stmt;
    DECL_KIND(CommandGroup);
    DECL_FIELDS(CommandGroup, (Stmt));
};

#define __extra_args_pass Command(args.parent, args.subnodes)
/// \brief Block command type
struct Block : public Command {
    using Command::Command;
    BOOST_DESCRIBE_CLASS(Block, (Command), (), (), ());
};

#define __extra_args_pass Block(args.parent, args.subnodes)
/// \brief Quotation block
struct Quote : public Block {
    using Block::Block;
    SemIdT<Paragraph> text = SemIdT<Paragraph>::Nil();
    DECL_KIND(Quote);
    DECL_FIELDS(Quote, (Block));
};

/// \brief Example block
struct Example : public Block {
    using Block::Block;
    DECL_KIND(Example);
    DECL_FIELDS(Example, (Block));
};

struct Export : public Block {
    using Block::Block;
    DECL_KIND(Export);
    DECL_DESCRIBED_ENUM(Format, Inline, Line, Block);

    DECL_FIELDS(
        Export,
        (Block),
        ((Format), format, Format, Format::Inline),
        ((QString), exporter, Exporter, ""),
        ((QString), content, Content, ""));
};

struct AdmonitionBlock : public Block {
    using Block::Block;
    DECL_KIND(AdmonitionBlock);
    DECL_FIELDS(AdmonitionBlock, (Block));
};

/// \brief Base class for all code blocks
struct Code : public Block {
    using Block::Block;
    DECL_KIND(Code);

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


#define __extra_args_pass Org(args.parent, args.subnodes)
/// \brief Single static or dynamic timestamp (active or inactive)
struct Time : public Org {
    DECL_KIND(Time);
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

    Time(CR<UserTime> time)
        : time(Static{.time = time}), Org(SemId::Nil(), OrgAdapter()) {}

    struct Static {
        Opt<Repeat> repeat;
        UserTime    time;
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

struct Symbol : public Org {
    DECL_KIND(Symbol);
    using Org::Org;
    struct Param {
        Opt<QString> key;
        QString      value;
    };

    DECL_FIELDS(
        Symbol,
        (Org),
        ((QString), name, Name, ""),
        ((Vec<Param>), parameters, Parameters, {}),
        ((Vec<SemId>), positional, Positiona, {}));
};

struct Macro : public Org {
    DECL_KIND(Macro);
    using Org::Org;
    DECL_FIELDS(
        Macro,
        (Org),
        ((QString), name, Name, ""),
        ((Vec<QString>), arguments, Arguments, {}));
};

/// Time range delimited by two points
struct TimeRange : public Org {
    DECL_KIND(TimeRange);
    using Org::Org;

    DECL_FIELDS(
        TimeRange,
        (Org),
        ((SemIdT<Time>), from, From, SemIdT<Time>::Nil()),
        ((SemIdT<Time>), to, To, SemIdT<Time>::Nil()));
};

struct SubtreeLog : public Org {
    DECL_KIND(SubtreeLog);
    using Org::Org;
    struct DecribedLog {
        Opt<SemIdT<StmtList>> desc = SemIdT<StmtList>::Nil();
    };

    struct Note : DecribedLog {
        SemIdT<Time> on = SemIdT<Time>::Nil();
    };

    struct Refile : DecribedLog {
        SemIdT<Time> on   = SemIdT<Time>::Nil();
        SemIdT<Link> from = SemIdT<Time>::Nil();
    };

    /// \brief Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30
    /// Sun 14:51:16] => 1:22`
    struct Clock {
        Variant<SemIdT<Time>, SemIdT<TimeRange>>
            range = SemIdT<Time>::Nil();
    };

    /// \brief Change of the subtree state -- `- State "WIP" from "TODO"
    /// [2023-04-30 Sun 13:29:04]`
    struct State : DecribedLog {
        OrgBigIdentKind from;
        OrgBigIdentKind to;
        SemIdT<Time>    on = SemIdT<Time>::Nil();
    };

    /// \brief Assign tag to the subtree `- Tag "project##haxorg" Added on
    /// [2023-04-30 Sun 13:29:06]`
    struct Tag : DecribedLog {
        SemIdT<Time>    on    = SemIdT<Time>::Nil();
        SemIdT<HashTag> tag   = SemIdT<HashTag>::Nil();
        bool            added = false;
    };

    void setDescription(SemIdT<StmtList> desc);

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

#define __extra_args_pass Org(args.parent, args.subnodes)
struct Subtree : public Org {
    DECL_KIND(Subtree);
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

        SemIdT<Time>& getTime() { return std::get<SemIdT<Time>>(period); }
        SemIdT<TimeRange>& getTimeRange() {
            return std::get<SemIdT<TimeRange>>(period);
        }

        Variant<SemIdT<Time>, SemIdT<TimeRange>> period;
        Kind                                     kind;
        Period(
            CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period,
            Kind                                         kind)
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

        struct Effort {
            int hours   = 0;
            int minutes = 0;
        };

        struct Visibility {
            DECL_DESCRIBED_ENUM(Level, Folded, Children, Content, All);
            Level level;
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
            SemIdT<Time> time = SemIdT<Time>::Nil();
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
            Visibility,
            Effort,
            Blocker,
            Unnumbered,
            Created);

        // Variant field is declared separately from the helper
        // definitions
        Data data;
        //! [declare variant field for subtree properties]

        Property(CR<Data> data) : data(data) {}

        bool matches(Kind kind, CR<QString> subkind = "") const;
    };


    DECL_FIELDS(
        Subtree,
        (Org),
        ((int), level, Level, 0),
        ((Opt<Str>), treeId, TreeId, std::nullopt),
        ((Opt<Str>), todo, Todo, std::nullopt),
        ((Opt<SemIdT<Completion>>), completion, Completion, std::nullopt),
        ((Vec<SemIdT<HashTag>>), tags, Tags, {}),
        ((SemIdT<Paragraph>), title, Title, SemIdT<Paragraph>::Nil()),
        ((Opt<SemIdT<Paragraph>>), description, Description, std::nullopt),
        ((Vec<SemIdT<SubtreeLog>>), logbook, Logbook, {}),
        ((Vec<Property>), properties, Properties, {}),
        ((Opt<SemIdT<Time>>), closed, Closed, std::nullopt),
        ((Opt<SemIdT<Time>>), deadline, Deadline, std::nullopt),
        ((Opt<SemIdT<Time>>), scheduled, Scheduled, std::nullopt));


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

#define __extra_args_pass LatexBody(args.parent, args.subnodes)
struct InlineMath : public LatexBody {
    using LatexBody::LatexBody;
    DECL_KIND(InlineMath);
    DECL_FIELDS(InlineMath, (LatexBody));
};


#define __extra_args_pass Org(args.parent, args.subnodes)
struct Leaf : public Org {
    using Org::Org;
    Leaf(SemId parent, CR<Str> text) : Org(parent), text(text) {}
    Str text = "";
    BOOST_DESCRIBE_CLASS(Leaf, (Org), (text), (), ());
};

#define __extra_args_fields                                               \
    Str   text   = "";                                                    \
    SemId parent = SemId::Nil();

#define __extra_args_pass Leaf(args.parent, args.text)

struct Escaped : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Escaped);
    DECL_FIELDS(Escaped, (Leaf));
};

struct Newline : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Newline);
    DECL_FIELDS(Newline, (Leaf));
};

struct Space : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Space);
    DECL_FIELDS(Space, (Leaf));
};

struct Word : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Word);
    DECL_FIELDS(Word, (Leaf));
};

struct AtMention : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(AtMention);
    DECL_FIELDS(AtMention, (Leaf));
};

struct RawText : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(RawText);
    DECL_FIELDS(RawText, (Leaf));
};

struct Punctuation : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Punctuation);
    DECL_FIELDS(Punctuation, (Leaf));
};

struct Placeholder : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(Placeholder);
    DECL_FIELDS(Placeholder, (Leaf));
};

struct BigIdent : public Leaf {
    using Leaf::Leaf;
    DECL_KIND(BigIdent);
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

#define __extra_args_fields                                               \
    Vec<SemId> subnodes = {};                                             \
    SemId      parent   = SemId::Nil();

#define __extra_args_pass Org(args.parent, args.subnodes)

struct Markup : public Org {
    using Org::Org;
    BOOST_DESCRIBE_CLASS(Markup, (Org), (), (), ());
};

#define __extra_args_pass Markup(args.parent, args.subnodes)

struct Bold : public Markup {
    using Markup::Markup;
    DECL_KIND(Bold);
    DECL_FIELDS(Bold, (Markup));
};

struct Underline : public Markup {
    using Markup::Markup;
    DECL_KIND(Underline);
    DECL_FIELDS(Underline, (Markup));
};

struct Monospace : public Markup {
    using Markup::Markup;
    DECL_KIND(Monospace);
    DECL_FIELDS(Monospace, (Markup));
};

struct MarkQuote : public Markup {
    using Markup::Markup;
    DECL_KIND(MarkQuote);
    DECL_FIELDS(MarkQuote, (Markup));
};

struct Verbatim : public Markup {
    using Markup::Markup;
    DECL_KIND(Verbatim);
    DECL_FIELDS(Verbatim, (Markup));
};

struct Italic : public Markup {
    using Markup::Markup;
    DECL_KIND(Italic);
    DECL_FIELDS(Italic, (Markup));
};

struct Strike : public Markup {
    using Markup::Markup;
    DECL_KIND(Strike);
    DECL_FIELDS(Strike, (Markup));
};

struct Par : public Markup {
    using Markup::Markup;
    DECL_KIND(Par);
    DECL_FIELDS(Par, (Markup));
};

#define __extra_args_pass Org(args.parent, args.subnodes)

struct List : public Org {
    using Org::Org;
    DECL_KIND(List);
    DECL_FIELDS(List, (Org));

    bool isDescriptionList() const;
};

struct ListItem : public Org {
    using Org::Org;
    DECL_KIND(ListItem);
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
        ((Opt<SemIdT<Paragraph>>), header, Header, std::nullopt));
};

struct Link : public Org {
    DECL_KIND(Link);
    using Org::Org;
    struct Raw {
        Str text;
    };

    struct Id {
        Str text;
    };

    struct Person {
        Str name;
    };

    struct Footnote {
        Str target;
    };

    struct File {
        Str file;
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getLinkKind,
        Raw,
        Footnote,
        Id,
        Person,
        File);

    DECL_FIELDS(
        Link,
        (Org),
        ((Data), data, Data, Raw{}),
        ((Opt<SemIdT<Paragraph>>),
         description,
         Description,
         std::nullopt));

    Opt<SemId> resolve(Document const& doc) const;
    Opt<SemId> resolve() const;
};

struct ParseError : public Org {
    using Org::Org;
    DECL_KIND(ParseError);
    DECL_FIELDS(ParseError, (Org));
};


struct FileTarget : public Org {
    using Org::Org;
    DECL_KIND(FileTarget);
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
    DECL_KIND(TextSeparator);
    DECL_FIELDS(TextSeparator, (Org));
};

struct Include : public Org {
    using Org::Org;
    DECL_KIND(Include);

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
        ((Opt<SemId>), includedDocument, IncludedDocument, std::nullopt));
};


struct DocumentOptions : public Org {
    using Org::Org;
    DECL_KIND(DocumentOptions);

    DECL_DESCRIBED_ENUM(BrokenLinks, Raise, Ignore, Mark);
    DECL_DESCRIBED_ENUM(
        Visibility,
        Overview,
        Content,
        ShowAll,
        Show2Levels,
        Show3Levels,
        Show4Levels,
        Show5Levels,
        ShowEverything);

    using TocExport = Variant<bool, int>;

    DECL_FIELDS(
        DocumentOptions,
        (Org),
        ((BrokenLinks), brokenLinks, BrokenLinks, BrokenLinks::Mark),
        ((Visibility),
         initialVisibility,
         InitialVisibility,
         Visibility::ShowEverything),
        /// Properties that can be shared by both subtree and document. Not
        /// all make sense in the document, but most do.
        ((Vec<Subtree::Property>), properties, Properties, {}),
        ((TocExport), tocExport, TocExport, false),
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

    Vec<Subtree::Property> getProperties(
        Subtree::Property::Kind kind,
        CR<QString>             subkind = "") const;
    Opt<Subtree::Property> getProperty(
        Subtree::Property::Kind kind,
        CR<QString>             subkind = "") const;
};

struct Document : public Org {
    using Org::Org;
    DECL_KIND(Document);


    DECL_FIELDS(
        Document,
        (Org),
        ((UnorderedMap<Str, SemId>), idTable, IdTable, {}),
        ((UnorderedMap<Str, SemId>), nameTable, NameTable, {}),
        ((UnorderedMap<Str, SemId>), anchorTable, AnchorTable, {}),
        ((UnorderedMap<Str, SemId>), footnoteTable, FootnoteTable, {}),
        ((Opt<SemIdT<Paragraph>>), title, Title, std::nullopt),
        ((Opt<SemIdT<Paragraph>>), author, Author, std::nullopt),
        ((Opt<SemIdT<Paragraph>>), creator, Creator, std::nullopt),
        ((Opt<SemIdT<RawText>>), email, Email, std::nullopt),
        ((Opt<Vec<Str>>), language, Language, std::nullopt),
        ((SemIdT<DocumentOptions>),
         options,
         Options,
         SemIdT<DocumentOptions>::Nil()),
        ((Opt<Str>), exportFileName, ExportFileName, std::nullopt));

    Vec<Subtree::Property> getProperties(
        Subtree::Property::Kind kind,
        CR<QString>             subkind = "") const;

    Opt<Subtree::Property> getProperty(
        Subtree::Property::Kind kind,
        CR<QString>             subkind = "") const;

    Opt<SemIdT<Subtree>> getSubtree(CR<Str> id) const;
    Opt<SemId>           resolve(CR<SemId> node) const;
};

struct DocumentGroup : public Org {
    using Org::Org;
    DECL_KIND(DocumentGroup);
    DECL_FIELDS(DocumentGroup, (Org));
};

} // namespace sem
