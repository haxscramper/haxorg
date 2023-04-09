#pragma once

#include <memory>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Json.hpp>

#include <QDateTime>


namespace sem {

struct TreeId {
    Str id;
};

BOOST_DESCRIBE_STRUCT(TreeId, (), (id));

template <typename T>
using Wrap = std::shared_ptr<T>;

#define GET_KIND(Kind)                                                    \
    virtual OrgSemKind getKind() const { return OrgSemKind::Kind; }

class Subtree;
class Document;

struct Org : public std::enable_shared_from_this<Org> {
    inline bool hasParent() const { return parent != nullptr; }
    Org*        getParent() { return parent; }
    Org const*  getParent() const { return parent; }

    Vec<Org*>           getParentChain(bool withSelf = false) const;
    Opt<Wrap<Subtree>>  getParentSubtree() const;
    Opt<Wrap<Document>> getDocument() const;

    /// Pointer to the parent node in sem tree, might be null.
    Org* parent = nullptr;
    /// Adapter to the original parsed node.
    OrgAdapter original;

    inline Org(Org* parent, OrgAdapter original)
        : parent(parent), original(original) {}

    // TODO replace with custom list of kinds -- place enum in the
    // `enums.hpp`
    OrgNodeKind getOriginalKind() const { return original.getKind(); }
    virtual OrgSemKind getKind() const = 0;
    bool               isGenerated() const { return original.empty(); }
    Opt<LineCol>       loc = std::nullopt;
    Vec<Wrap<Org>>     subnodes;

    void push_back(Wrap<Org>&& sub) { subnodes.push_back(std::move(sub)); }

    struct TreeReprConf {
        bool withLineCol    = true;
        bool withOriginalId = true;
        bool withSubnodeIdx = true;

        SemSet skipNodes;
        SemSet skipSubnodesOf;

        bool doSkipSubnodesOf(Org const* org) const {
            return skipSubnodesOf.contains(org->getKind());
        }

        bool doSkip(Org const* org) const {
            return skipNodes.contains(org->getKind());
        }
    };

    struct TreeReprCtx {
        int level      = 0;
        int subnodeIdx = -1;
    };

    virtual void treeRepr(ColStream& os, CR<TreeReprConf>, TreeReprCtx)
        const;

    inline Wrap<Org> at(int idx) { return subnodes[idx]; }


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
    Vec<Row> rows;
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


struct Format : public Org {
    using Org::Org;
};

struct Center : public Format {
    using Format::Format;
    GET_KIND(Center);
};

/// \brief Base class for block or line commands
struct Command : public Stmt {
    using Stmt::Stmt;
};

struct LineCommand : public Command {
    using Command::Command;
};

struct Standalone : public LineCommand {
    using LineCommand::LineCommand;
};

/// \brief Line command that might get attached to some block element
struct Attached : public LineCommand {
    using LineCommand::LineCommand;
};


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

struct Quote : public Block {
    using Block::Block;
    Wrap<Paragraph> text;
    GET_KIND(Quote);
};

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
    struct Switches {
        /// \brief Enumerate code lines starting from `start` value instead
        /// of default indexing.
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
    };

    using Switch = Variant<
        Switches::LineStart,
        Switches::CalloutFormat,
        Switches::EmphasizeLine,
        Switches::Dedent,
        Switches::RemoveCallout>;

    Vec<Switch> switches;

    /// Code language name -- does not have to be skipped, although in most
    /// cases it is actually used
    Opt<Str> lang;

    Opt<Str> session;
    enum class Results
    {
        Replace,
    };

    enum class Exports
    {
        None,
        Both,
        Code,
        Results
    };

    Exports exports = Exports::Both;
    bool    cache   = false;
    bool    eval    = false;
    bool    noweb   = false;
    bool    hlines  = false;
    bool    tangle  = false;
};


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

        Period period;
        int    count;
    };

    struct Static {
        Opt<Repeat> repeat;
        QDateTime   time;
    };
    /// Active timestamp with evaluatable code expression inside, also
    /// called diary time
    struct Dynamic {
        Str expr;
    };
    Variant<Static, Dynamic> time;
    bool isStatic() const { return std::holds_alternative<Static>(time); }
    Static&        getStatic() { return std::get<Static>(time); }
    Dynamic&       getDynamic() { return std::get<Dynamic>(time); }
    Static const&  getStatic() const { return std::get<Static>(time); }
    Dynamic const& getDynamic() const { return std::get<Dynamic>(time); }

    bool isActive; /// Active `<time>` or passive `[time]`
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
        Time on;
    };

    struct Refile {
        Time on;
    };

    struct Clock {
        Variant<Time, TimeRange> range;
    };

    struct State {
        OrgBigIdentKind from;
        OrgBigIdentKind to;
        Time            on;
    };

    enum class Kind
    {
        Note,
        Refile,
        Clock,
        State
    };

    Variant<Note, Refile, Clock, State> log;
};

BOOST_DESCRIBE_STRUCT(SubtreeLog, (Org), (log));

struct Subtree : public Org {
    GET_KIND(Subtree);
    using Org::Org;

    struct Properties {
        enum class PropertyKind
        {
            Ordered,
            Nonblocking,
            Trigger,
            Blocker,
            Unnumbered,
            Created,
            ExportOptions,
        };

        BOOST_DESCRIBE_NESTED_ENUM(
            PropertyKind,
            Ordered,
            Nonblocking,
            Trigger,
            Blocker,
            Unnumbered,
            Created,
            ExportOptions);

#define PROP_KIND(Kind)                                                   \
    PropertyKind getKind() const { return PropertyKind::Kind; }

        struct Ordered {
            bool isOrdered;
            PROP_KIND(Ordered);
        };

        struct ExportOptions {
            Str                    backend;
            UnorderedMap<Str, Str> values;
            PROP_KIND(ExportOptions);
        };

        struct Nonblocking {
            bool isBlocking;
            PROP_KIND(Nonblocking);
        };

        struct Trigger {
            PROP_KIND(Trigger);
            struct Dependency {
                TreeId   id;
                Opt<Str> state;
            };
        };

        struct Blocker {
            PROP_KIND(Blocker);
            Vec<Str> blockers;
        };

        struct Unnumbered {
            PROP_KIND(Unnumbered);
        };
        struct Created {
            PROP_KIND(Created);
            QDateTime time;
        };

        using Property = Variant<
            //
            Ordered,
            Nonblocking,
            Trigger,
            Blocker,
            Unnumbered,
            Created,
            ExportOptions
            //
            >;

        template <typename T>
        static T& as(Property& prop) {
            return std::get<T>(prop);
        }

        template <typename T>
        static T const& as(Property const& prop) {
            return std::get<T>(prop);
        }

        static PropertyKind kind(CR<Property> prop) {
            return std::visit(
                [](auto const& it) -> PropertyKind {
                    return it.getKind();
                },
                prop);
        }
    };


    int                       level = 0;
    Opt<Str>                  id;
    Opt<Str>                  todo;
    Opt<Wrap<Completion>>     completion;
    Vec<Wrap<HashTag>>        tags;
    Wrap<Paragraph>           title;
    Opt<Wrap<Paragraph>>      description;
    Vec<Wrap<SubtreeLog>>     logbook;
    Vec<Properties::Property> properties;

    Opt<Wrap<Time>> closed;
    Opt<Wrap<Time>> deadline;
    Opt<Wrap<Time>> scheduled;

    using PropKind = Properties::PropertyKind;

    inline Opt<QDateTime> getCreated() const {
        if (auto created = getProperty(PropKind::Created)) {
            return std::get<Properties::Created>(created.value()).time;
        } else {
            return std::nullopt;
        }
    }

    Opt<Wrap<Time>> getStart() const;
    Opt<Wrap<Time>> getEnd() const;


    Vec<Properties::Property> getProperties(
        PropKind    kind,
        CR<QString> subkind = "") const;
    Opt<Properties::Property> getProperty(
        PropKind    kind,
        CR<QString> subkind = "") const;
    Vec<Properties::Property> getContextualProperties(
        PropKind    kind,
        CR<QString> subkind = "") const;
    Opt<Properties::Property> getContextualProperty(
        PropKind    kind,
        CR<QString> subkind = "") const;

    virtual void treeRepr(ColStream&, CR<TreeReprConf>, TreeReprCtx)
        const override;
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
    virtual void treeRepr(ColStream&, CR<TreeReprConf>, TreeReprCtx)
        const override;
};

// clang-format off
struct Newline : public Leaf { GET_KIND(Newline); using Leaf::Leaf; };
struct Space : public Leaf { GET_KIND(Space); using Leaf::Leaf; };
struct Word : public Leaf { GET_KIND(Word); using Leaf::Leaf; };
struct RawText : public Leaf { GET_KIND(RawText); using Leaf::Leaf; };
struct Punctuation : public Leaf { GET_KIND(Punctuation); using Leaf::Leaf; };
struct Placeholder : public Leaf { GET_KIND(Placeholder); using Leaf::Leaf; };
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

    using Data = Variant<Raw, Footnote, Id>;

    Data data;

    Raw&       getRaw() { return std::get<Raw>(data); }
    Raw const& getRaw() const { return std::get<Raw>(data); }


    Opt<Wrap<Paragraph>> description;
};

struct BigIdent : public Leaf {
    GET_KIND(BigIdent);
    using Leaf::Leaf;
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
