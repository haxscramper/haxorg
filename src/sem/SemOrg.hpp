#pragma once

#include <memory>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>

#include <hstd/stdlib/Json.hpp>

#include <QDateTime>

namespace sem {

struct TreeId {
    Str id;
};

BOOST_DESCRIBE_STRUCT(TreeId, (), (id));

template <typename T>
using Wrap = std::shared_ptr<T>;

namespace properties {
    struct Ordered {
        bool isOrdered;
    };

    BOOST_DESCRIBE_STRUCT(Ordered, (), (isOrdered));

    struct Nonblocking {
        bool isBlocking;
    };

    BOOST_DESCRIBE_STRUCT(Nonblocking, (), (isBlocking));

    struct Trigger {
        struct Dependency {
            TreeId   id;
            Opt<Str> state;
        };
    };

    struct Blocker {
        Vec<Str> blockers;
    };

    BOOST_DESCRIBE_STRUCT(Blocker, (), (blockers));

    struct Unnumbered {};
    BOOST_DESCRIBE_STRUCT(Unnumbered, (), ());

    struct Created {};
    BOOST_DESCRIBE_STRUCT(Created, (), ());

    using Property = Variant<
        //
        Ordered,
        Nonblocking,
        Trigger,
        Blocker,
        Unnumbered,
        Created
        //
        >;

} // namespace properties


#define GET_KIND(Kind)                                                    \
    virtual OrgSemKind getKind() const { return OrgSemKind::Kind; }

struct Org {
    /// Pointer to the parent node in sem tree, might be null.
    Org* parent;
    /// Adapter to the original parsed node.
    OrgAdapter original;

    inline Org(Org* parent, OrgAdapter original)
        : parent(parent), original(original) {}

    // TODO replace with custom list of kinds -- place enum in the
    // `enums.hpp`
    OrgNodeKind getOriginalKind() const { return original.getKind(); }
    virtual OrgSemKind getKind() const = 0;
    bool               isGenerated() const { return original.empty(); }
    Vec<Wrap<Org>>     subnodes;
    Vec<properties::Property> properties;

    virtual json toJson() const = 0;

    void push_back(Wrap<Org>&& sub) { subnodes.push_back(std::move(sub)); }

    json newJson() const {
        json res;
        res["kind"] = to_string(getKind());
        return res;
    }

    void subnodesJson(json& res) const {
        if (!subnodes.empty()) {
            json tmp = json::array();
            for (const auto& sub : subnodes) {
                tmp.push_back(sub->toJson());
            }
            res["subnodes"] = tmp;
        }
    }
};

BOOST_DESCRIBE_STRUCT(Org, (), (parent, subnodes, properties));

struct StmtList : public Org {
    using Org::Org;
    virtual json toJson() const override;
    GET_KIND(StmtList);
};

BOOST_DESCRIBE_STRUCT(StmtList, (Org), ());

struct Row : public Org {
    using Org::Org;
    virtual json toJson() const override;
    GET_KIND(Row);
};

BOOST_DESCRIBE_STRUCT(Row, (Org), ());

struct Table : public Org {
    using Org::Org;
    Vec<Row>     rows;
    virtual json toJson() const override;
    GET_KIND(Table);
};

BOOST_DESCRIBE_STRUCT(Table, (Org), (rows));

struct HashTag : public Org {
    using Org::Org;
    Str          head;
    Vec<HashTag> subtags;

    virtual json toJson() const override;
    GET_KIND(HashTag);
};

BOOST_DESCRIBE_STRUCT(HashTag, (), (head, subtags));

/// \brief Completion status of the subtree or list element
struct Completion : Org {
    using Org::Org;
    /// \brief Number of completed tasks
    int done = 0;
    /// \brief Full number of tasks
    int  full      = 0;
    bool isPercent = false;

    virtual json toJson() const override;
    GET_KIND(Completion);
};
BOOST_DESCRIBE_STRUCT(Completion, (), (done, full, isPercent));


struct Paragraph : public Org {
    using Org::Org;
    virtual json toJson() const override;
    GET_KIND(Paragraph);
};

struct Markup : public Org {
    using Org::Org;
};

struct Bold : public Markup {
    using Markup::Markup;
    virtual json toJson() const override;
    GET_KIND(Bold);
};


struct Italic : public Markup {
    using Markup::Markup;
    virtual json toJson() const override;
    GET_KIND(Italic);
};


struct Strike : public Markup {
    using Markup::Markup;
    virtual json toJson() const override;
    GET_KIND(Strike);
};

struct Format : public Org {
    using Org::Org;
};

struct Center : public Format {
    using Format::Format;
    virtual json toJson() const override;
    GET_KIND(Center);
};

struct Block : public Org {
    using Org::Org;
    Opt<Wrap<Org>> caption;
};

struct Quote : public Block {
    using Block::Block;
    virtual json toJson() const override;
    GET_KIND(Quote);
};

struct Example : public Block {
    using Block::Block;
    virtual json toJson() const override;
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

    bool         isActive; /// Active `<time>` or passive `[time]`
    virtual json toJson() const override;
};


/// Time range delimited by two points
struct TimeRange : public Org {
    GET_KIND(TimeRange);
    using Org::Org;
    Wrap<Time>   from;
    Wrap<Time>   to;
    virtual json toJson() const override;
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

    virtual json toJson() const override;
};

BOOST_DESCRIBE_STRUCT(SubtreeLog, (Org), (log));

struct Subtree : public Org {
    GET_KIND(Subtree);
    using Org::Org;
    int                   level;
    Opt<Str>              todo;
    Opt<Wrap<Completion>> completion;
    Vec<Wrap<HashTag>>    tags;
    Wrap<Org>             title;
    Opt<Wrap<Org>>        description;
    Vec<Wrap<SubtreeLog>> logbook;

    virtual json toJson() const override;
};

BOOST_DESCRIBE_STRUCT(
    Subtree,
    (),
    (level, todo, completion, tags, title, description, logbook));

struct Leaf : public Org {
    Str text;
    using Org::Org;
    virtual json toJson() const override {
        json res;
        res["text"] = text;
        return res;
    }
};

struct SkipNewline : public Leaf {
    GET_KIND(SkipNewline);
    using Leaf::Leaf;
};

struct SkipSpace : public Leaf {
    GET_KIND(SkipSpace);
    using Leaf::Leaf;
};

struct Space : public Leaf {
    GET_KIND(Space);
    using Leaf::Leaf;
};

struct Word : public Leaf {
    GET_KIND(Word);
    using Leaf::Leaf;
};

struct Punctuation : public Leaf {
    GET_KIND(Punctuation);
    using Leaf::Leaf;
};

struct Link : public Org {
    GET_KIND(Link);
    using Org::Org;
    virtual json toJson() const override;
};

struct BigIdent : public Leaf {
    GET_KIND(BigIdent);
    using Leaf::Leaf;
};

}; // namespace sem

#undef GET_KIND
