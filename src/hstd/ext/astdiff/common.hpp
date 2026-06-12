#pragma once

#include <hstd/stdlib/Str.hpp>

namespace hstd::ext::diff {


/// \brief Within a tree, this identifies a node by its preorder offset.
///
/// Internally this is an index into a flat structure that holds syntax
/// tree nodes. Access to the target node is performed via vector indexing.
struct NodeIdx {
  private:
    static constexpr int InvalidNodeOffset = -1;

  public:
    int Offset; /// Offset in the postorder iteratio
    inline NodeIdx() : Offset(InvalidNodeOffset) {}
    inline NodeIdx(int Offset) : Offset(Offset) {}

    inline          operator int() const { return Offset; }
    inline NodeIdx& operator++() { return ++Offset, *this; }
    inline NodeIdx& operator--() { return --Offset, *this; }
    /// Support defining iterators on NodeIdx.
    inline NodeIdx& operator*() { return *this; }
    inline bool     isValid() const { return Offset != InvalidNodeOffset; }
    inline bool isInvalid() const { return Offset == InvalidNodeOffset; }

    inline void assertValid(std::string const& msg) const {
        if (isInvalid()) {
            throw std::domain_error(
                "non-valid (-1) node found for " + msg);
        }
    }

    DESC_FIELDS(NodeIdx, (Offset));
};


struct ASTNodeKind {
    int value = 0;
    ASTNodeKind(int kind) : value(kind) {}
    bool operator==(ASTNodeKind const& other) const {
        return value == other.value;
    }

    DESC_FIELDS(ASTNodeKind, (value));
};

struct NodeStore {
    struct Id {
        i64 id = -1;

        template <typename T>
        static Id FromPtr(T const* value) {
            return Id{.id = reinterpret_cast<i64>(value)};
        }

        template <typename T>
        T* ToPtr() {
            return static_cast<T*>(id);
        }

        template <typename T>
        T const* ToPtr() const {
            return reinterpret_cast<T const*>(
                static_cast<std::intptr_t>(id));
        }

        static Id FromNumber(i64 id) { return Id{.id = id}; }
        i64       ToNumber() const { return id; }

        bool operator==(NodeStore::Id const& other) const {
            return id == other.id;
        }
    };

    virtual int         getSubnodeCount(Id const& id)           = 0;
    virtual Id          getSubnodeAt(Id const& node, int index) = 0;
    virtual Id          getRoot()                               = 0;
    virtual ASTNodeKind getNodeKind(Id const& node) const       = 0;
    virtual bool isMatchingAllowed(Id const& src, Id const& dst) const {
        return getNodeKind(src) == getNodeKind(dst);
    }
};

} // namespace hstd::ext::diff

template <>
struct std::hash<hstd::ext::diff::NodeStore::Id> {
    std::size_t operator()(
        hstd::ext::diff::NodeStore::Id const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.id);
        return result;
    }
};
