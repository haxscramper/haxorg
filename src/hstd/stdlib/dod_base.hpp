#pragma once

#include <string>
#include <unordered_map>

#include <hstd/system/all.hpp>
#include <hstd/system/generator.hpp>

#include <hstd/stdlib/Vec.hpp>


/// \brief Data-oriented design primitives
///
/// This namespace provides implementation of the Data-orited design
/// primitives such as stores and ID type. The implementation is largely
/// based on my understanding of the DOD practices and as such might
/// contain some things that could be implemented differently or ones that
/// are not necessary at all.
namespace dod {
/// \brief DOD Id type
///
/// \note It does not have a default constructor, if you need co construct
/// a an empyt/nil value (not recommended) for some field/argument you can
/// use the static `::Nil` method defined in the derivations produced in
/// the `DECL_ID_TYPE` macro
///
/// \note ID types can be thought of as a pointers or indices into some
/// 'memory' container and as such should only be parametrized using
/// unsigned data types. They *do not* provide any sort of pointer-like
/// arithmentics or any other operations that might fail due to the
/// overflow. Container indices can be freely converted to the pointers.
template <std::integral IdType>
// TODO implement support for top ID masking via top bits of the value
struct [[nodiscard]] Id {
    using id_base_type = IdType;
    /// Create new ID value from the stored ID index.
    explicit Id(IdType in) : value(in + 1) {}

    /// Create new ID object from value, without preemptively incrementing
    /// it
    static auto FromValue(IdType in) -> Id {
        Id res{IdType{}};
        res.value = in;
        return res;
    }

    /// Check whether provided value is nil or not
    auto isNil() const noexcept -> bool { return value == IdType{}; }
    /// Get value stored in the ID  - this one should be used in cases
    /// where ID is converted in some different format (for example printed
    /// out or stored in the database)
    auto getValue() const noexcept -> IdType { return value; }
    /// Set value of the ID. This should be used for deserialization.
    ///
    /// \note This function allows setting ID to state with zero value,
    /// making it 'nil'
    void setValue(IdType arg) noexcept { value = arg; }
    /// Get index of the ID, for accessing the store.
    ///
    /// \warning in case of a 'nil' type this might return an invalid index
    /// (`<0`)
    auto getIndex() const noexcept -> IdType { return value - 1; }
    /// Get string representation of the ID value
    auto getStr() const -> std::string { return std::to_string(value); }

  protected:
    IdType value;
};

/// Declare new ID type, derived from the `dod::Id` with specified \arg
/// __type as a template parameter. Newly declared type will have a name
/// \arg __name and associated value type `__value`. All three parameters
/// must be specified in order for the definition to be sound.
///
/// Defined type provides implementation of the `::FromValue` and `::Nil`
/// static functions that can be used as an alternative construction
/// methods in various cases.
#define DECL_ID_TYPE(__value, __name, __type)                             \
    struct __value;                                                       \
    struct [[nodiscard]] __name : dod::Id<__type> {                       \
        using value_type = __value;                                       \
        static auto Nil() -> __name { return FromValue(0); };             \
        static auto FromValue(__type arg) -> __name {                     \
            __name res{__type{}};                                         \
            res.setValue(arg);                                            \
            return res;                                                   \
        }                                                                 \
        auto operator==(__name other) const -> bool {                     \
            return getValue() == other.getValue();                        \
        }                                                                 \
        explicit __name(__type arg) : dod::Id<__type>(arg) {}             \
    };


/// Concent for base ID type and all it's publcily derived types
template <typename D>
concept IsIdType = is_base_of_template_v<Id, D>;

/// Type trait for accessing value type of the ID type
template <typename T>
struct value_type {
    using type = typename T::value_type;
};

/// Helper alias for accessing value type of the type
template <typename T>
using value_type_t = typename value_type<T>::type;

/// Type trait tructure for inferring id type of the stored type
template <typename T>
struct id_type {
    using type = typename T::id_type;
};

/// Helper alias for accessing id type of the type
template <typename T>
using id_type_t = typename id_type<T>::type;

template <IsIdType Id, typename T>
/// \brief Store a collection of the value types
///
/// The main class in the DOD design - provideds an abstracted container
/// that allows user to put in a new object, returning ID, or get an
/// existing object from an ID.
struct Store {
    Store() = default;

    /// Add value to the storage and return newly created ID
    [[nodiscard]] auto add(const T& value) -> Id {
        int index = content.size();
        content.push_back(value);
        return Id(index);
    }

    /// Add new item to the store and return newly created ID
    [[nodiscard]] auto add(const T&& value) -> Id {
        int index = content.size();
        content.push_back(value);
        return Id(index);
    }

    auto atIndex(int index) -> T& { return content.at(index); }
    auto atIndex(int index) const -> CR<T> { return content.at(index); }


    /// Get a mutable reference to an object pointed to by the \arg id
    auto at(Id id) -> T& { return content.at(id.getIndex()); }
    /// Get a immutable reference to an object pointed to by the \arg id
    auto at(Id id) const -> CR<T> { return content.at(id.getIndex()); }
    /// Get a total number of the stored objects int the store
    auto size() const -> std::size_t { return content.size(); }

    /// Get genetator for all stored indices and pairs
    auto pairs() const -> generator<std::pair<Id, CP<T>>> {
        const int size = content.size();
        for (int i = 0; i < size; ++i) {
            co_yield {Id(i), &content.at(i)};
        }
    }

    /// Return generator for stored values
    auto items() const -> generator<CP<T>> {
        for (const auto& it : content) {
            co_yield &it;
        }
    }

    /// Iterate over mutable pointers to the items stored in the container
    auto items() -> generator<P<T>> {
        for (auto& it : content) {
            co_yield &it;
        }
    }

    /// Insert value into the store at position, either appending to the
    /// internal list or replacing an existing value.
    void insert(Id id, CR<T> value) {
        if (id.getIndex() == content.size()) {
            content.push_back(value);
        } else if (id.getIndex() < content.size()) {
            content[id.getIndex()] = value;
        } else {
            // IMPLEMENT either raise exception or come up with some other
            // way of handing
        }
    }

  private:
    Vec<T> content;
};


/// \brief Stores values with with automatic deduplication
///
/// Interned data store - for values that can be hashed for deduplication.
/// Provided type must be usable as a key for unordered associative
/// continer.
template <IsIdType Id, typename Val>
struct InternStore {
    InternStore() = default;

    std::unordered_map<Val, Id> id_map;
    dod::Store<Id, Val>         content;

    /// Add value to the store - if the value is already contained can
    /// return previous ID
    [[nodiscard]] auto add(CR<Val> in) -> Id {
        auto found = id_map.find(in);
        if (found != id_map.end()) {
            return found->second;
        } else {
            auto result = content.add(in);
            id_map.insert({in, result});
            return result;
        }
    }

    auto contains(CR<Val> in) const -> bool {
        return id_map.find(in) != id_map.end();
    }

    auto size() const -> std::size_t { return content.size(); }
    /// Get mutable reference at the content pointed at by the ID
    auto at(Id id) -> Val& { return content.at(id); }
    /// Get immutable references at the content pointed at by the ID
    auto at(Id id) const -> CR<Val> { return content.at(id); }

    void insert(Id id, CR<Val> value) {
        if (!contains(value)) {
            content.insert(id, value);
            id_map.insert({value, id});
        }
    }

    /// Return generator of the stored indices and values
    auto pairs() const -> generator<std::pair<Id, CP<Val>>> {
        return content.pairs();
    }

    /// Return generator of the stored values
    auto items() const -> generator<CP<Val>> { return content.items(); }
    auto items() -> generator<P<Val>> { return content.items(); }
};


/// \brief Wrapper for multiple different stores
///
/// Collecting of several different storage types, used as a boilerplate
/// reduction helper - instead of wrapping around multiple `Store<Id, Val>`
/// fields in the class, adding helper methods to access them via add/at
/// you can write a `MultiStore<>` and list all the required data in the
/// template parameter list. Supports both interned and non-interned
/// storage solutions.
template <typename... Args>
struct MultiStore {
    inline MultiStore() {}

    //// Get reference to the store that is associated with \param Val
    template <typename Val>
    requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() -> Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// An overload for the interned store case
    template <typename Val>
    requires is_in_pack_v<InternStore<id_type_t<Val>, Val>, Args...>
    auto store() -> InternStore<id_type_t<Val>, Val>& {
        return std::get<InternStore<id_type_t<Val>, Val>>(stores);
    }

    //// Get reference to the store that is associated with \param Val
    template <typename Val>
    requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() const -> const Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// An overload for the interned store case
    template <typename Val>
    requires is_in_pack_v<InternStore<id_type_t<Val>, Val>, Args...>
    auto store() const -> const InternStore<id_type_t<Val>, Val>& {
        return std::get<InternStore<id_type_t<Val>, Val>>(stores);
    }

    /// Push value on one of the stores, inferring which one based on the
    /// ID
    template <typename Val>
    [[nodiscard]] auto add(CR<Val> t) -> id_type_t<Val> {
        return store<Val>().add(t);
    }

    /// Get value at one of the associated stores, inferring which one
    /// based on the value type of the ID
    template <dod::IsIdType Id>
    auto at(Id id) -> value_type_t<Id>& {
        return store<value_type_t<Id>>().at(id);
    }

    template <dod::IsIdType Id>
    auto at(Id id) const -> CR<value_type_t<Id>> {
        return store<value_type_t<Id>>().at(id);
    }

    template <typename Id, typename Val>
    void insert(Id id, CR<Val> val) {
        return store<Val>().insert(id, val);
    }

  private:
    std::tuple<Args...> stores; /// List of associated storage contianers
};

}; // namespace dod

namespace std {
template <dod::IsIdType Id>
struct hash<Id> {
    auto operator()(Id it) const -> std::size_t {
        // Id uniquely identifies any entry it points to, by defintion, so
        // it can be used as a perfect hash
        return it.getValue();
    }
};
}; // namespace std
