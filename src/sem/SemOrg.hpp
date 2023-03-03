#pragma once

#include <memory>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <parse/OrgTypes.hpp>

#include <boost/describe.hpp>

#include <hstd/stdlib/Json.hpp>

namespace sem {

struct TreeId {
    Str id;
};

BOOST_DESCRIBE_STRUCT(TreeId, (), (id));

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


struct Org {
    /// Pointer to the parent node in sem tree, might be null.
    Org* parent;
    /// Adapter to the original parsed node.
    OrgAdapter original;

    inline Org(Org* parent, OrgAdapter original)
        : parent(parent), original(original) {}

    OrgNodeKind getKind() const { return original.getKind(); }
    bool        isGenerated() const { return original.empty(); }
    Vec<std::unique_ptr<Org>> subnodes;
    Vec<properties::Property> properties;

    virtual json toJson() const = 0;
};

BOOST_DESCRIBE_STRUCT(Org, (), (parent, subnodes, properties));

struct Row : public Org {
    using Org::Org;
    virtual json toJson() const override;
};

BOOST_DESCRIBE_STRUCT(Row, (Org), ());

struct Table : public Org {
    using Org::Org;
    Vec<Row>     rows;
    virtual json toJson() const override;
};

BOOST_DESCRIBE_STRUCT(Table, (Org), (rows));

struct HashTag : public Org {
    using Org::Org;
    Str          head;
    Vec<HashTag> subtags;

    virtual json toJson() const override;
};

BOOST_DESCRIBE_STRUCT(HashTag, (), (head, subtags));

// template <typename T>
// json to_json(CR<T> it);


template <typename T>
concept DescribedMembers = boost::describe::has_describe_members<T>::value;


template <
    DescribedMembers T,
    class D1 = boost::describe::describe_members<
        T,
        boost::describe::mod_public | boost::describe::mod_protected>>
json to_json(T const& t) {
    json obj;
    boost::mp11::mp_for_each<D1>(
        [&](auto D) { obj[D.name] = to_json(t.*D.pointer); });
    return obj;
}

inline json Table::toJson() const { return to_json(*this); }
inline json Row::toJson() const { return to_json(*this); }
inline json HashTag::toJson() const { return to_json(*this); }
}; // namespace sem
