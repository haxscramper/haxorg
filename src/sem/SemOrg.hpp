#pragma once

#include <memory>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>

namespace sem {

struct TreeId {
    Str id;
};

namespace properties {
    struct Ordered {
        bool isOrdered;
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

    struct Created {};

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


class Org {
    /// Pointer to the parent node in sem tree, might be null.
    Org* parent;
    /// Adapter to the original parsed node.
    NodeAdapter<OrgNodeKind, OrgTokenKind> original;

    OrgNodeKind getKind() const { return original.getKind(); }
    bool        isGenerated() const { return original.empty(); }
    Vec<std::unique_ptr<Org>> subnodes;
    Vec<properties::Property> properties;
};

class Row : public Org {};

class Table : public Org {
    Vec<Row> rows;
};
}; // namespace sem
