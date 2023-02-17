#pragma once

#include <string>
#include <unordered_map>

#include <hstd/system/all.hpp>
#include <hstd/system/generator.hpp>

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Slice.hpp>


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
/// use the static `Id::Nil` method defined in the derivations produced in
/// the `DECL_ID_TYPE` macro
///
/// \note ID types can be thought of as a pointers or indices into some
/// 'memory' container and as such should only be parametrized using
/// unsigned data types. They *do not* provide any sort of pointer-like
/// arithmentics or any other operations that might fail due to the
/// overflow. Container indices can be freely converted to the pointers.
template <
    /// Base type that will be used for ID storage
    std::integral IdType,
    /// Return type of the mask bits, defaults to the store type for
    /// convenience, used only for in/out values, not stored anywhere
    std::integral MaskType = IdType,
    /// Number of bits in the ID type mask.
    typename MaskSizeT = std::integral_constant<MaskType, 0>
    //
    >
// TODO implement support for top ID masking via top bits of the value
struct [[nodiscard]] Id {
    /// \brief Base type used to store value
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


    /// \brief Start position of the least significant bit of the mask
    static const inline int mask_offset = (8 * sizeof(IdType))
                                        - MaskSizeT::value;

    /// \brief Number of bits allotted for the mask value
    static const inline int mask_size = MaskSizeT::value;

    /// \brief Create ID value from provided mask and underlying ID base
    static auto FromMasked(MaskType mask, IdType id) -> Id {
        Id res{IdType{}};
        res.value = id | (mask << mask_offset);
        return res;
    }

    /// \brief Get number of bits in the mask
    consteval int getMaskSize() const { return mask_size; }
    /// \brief Get unmasked *value* (do not confuse with index)
    inline IdType getUnmasked() const {
        return value & ~(~IdType(0) << mask_offset);
    }

    /// \brief Get mask value
    inline MaskType getMask() const {
        return (value & (~IdType(0) << mask_offset)) >> mask_offset;
    }

    /// \brief Get direct value of the mask, with right-padded zeroes that
    /// were occupied by the value.
    inline MaskType getMaskUnshifed() const {
        return (value & (~IdType(0) << mask_offset));
    }

    /// \brief Set unmasked portion of the value
    inline void setUnmasked(IdType base) { value = getMask() | base; }

    /// \brief Set mask for the ID
    inline void setMask(MaskType mask) {
        value = getUnmasked() | (mask << mask_offset);
    }

    /// \brief Check whether provided value is nil or not
    auto isNil() const noexcept -> bool { return value == IdType{}; }
    /// Get value stored in the ID  - this one should be used in cases
    /// where ID is converted in some different format (for example printed
    /// out or stored in the database)
    auto getValue() const noexcept -> IdType { return value; }
    /// \brief Set value of the ID. This should be used for
    /// deserialization.
    ///
    /// \note This function allows setting ID to state with zero value,
    /// making it 'nil'
    void setValue(IdType arg) noexcept { value = arg; }
    /// Get index of the ID, for accessing the store. Returned value is
    /// computated while accounting for masked bits so it can be different
    /// from the `getValue()`
    auto getIndex() const -> IdType {
        if (isNil()) {
            throw std::out_of_range(
                "Cannot get index for nil value of DOD ID");
        } else {
            return (getUnmasked() - 1);
        }
    }
    /// Get string representation of the ID value
    auto getStr() const -> std::string { return std::to_string(value); }

    /// Compare *unmasked* parts of the ID. Only unmasked part is compared
    /// because mask ordering is unlikely to be any of any relevance for
    /// ordering.
    bool operator<(Id other) const noexcept {
        return getUnmasked() < other.getUnmasked();
    }

    /// \brief Compare *unmasked* parts of the ID.
    bool operator<=(Id other) const noexcept {
        return getUnmasked() <= other.getUnmasked();
    }

    /// \brief Compare full ID value for equality.
    ///
    /// \note This handles internal value differently from `<` comparison
    bool operator==(Id other) const noexcept {
        return getValue() == other.getValue();
    }

    /// \brief  Compare full ID value for inequality
    bool operator!=(Id other) const noexcept {
        return getValue() == other.getValue();
    }

    /// \brief Write strig representation of the ID into output stream
    std::ostream& streamTo(
        std::ostream& os,
        std::string   name     = "dod::Id",
        bool          withMask = true) const {
        if (name.size() != 0) {
            os << name << "(";
        }

        if (withMask) {
            if (0 < mask_size) {
                os << getMask() << ":";
            }
        }

        if (isNil()) {
            os << "<nil>";
        } else {
            os << getIndex();
        }

        if (name.size() != 0) {
            os << ")";
        }

        return os;
    }

  protected:
    /// \brief Full value of the ID, including masked part
    IdType value;
};


#define DECL_ID_TYPE_MASKED(__value, __name, __type, __mask)              \
    struct __value;                                                       \
    struct [[nodiscard]] __name                                           \
        : dod::Id<                                                        \
              __type,                                                     \
              __type,                                                     \
              std::integral_constant<__type, __mask>> {                   \
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
        explicit __name(__type arg)                                       \
            : dod::Id<                                                    \
                __type,                                                   \
                __type,                                                   \
                std::integral_constant<__type, __mask>>(arg) {}           \
    };                                                                    \
                                                                          \
                                                                          \
    std::ostream& operator<<(std::ostream& os, __name const& value) {     \
        return value.streamTo(os, #__name);                               \
    }


/// Declare new ID type, derived from the `dod::Id` with specified \arg
/// __type as a template parameter. Newly declared type will have a name
/// \arg __name and associated value type `__value`. All three parameters
/// must be specified in order for the definition to be sound.
///
/// Defined type provides implementation of the `::FromValue` and `::Nil`
/// static functions that can be used as an alternative construction
/// methods in various cases.
#define DECL_ID_TYPE(__value, __name, __type)                             \
    DECL_ID_TYPE_MASKED(__value, __name, __type, 0)


/// Concent for base ID type and all it's publcily derived types
template <typename D>
concept IsIdType = is_base_of_template_v<Id, D>;

/// \brief Generic ostream template for the ID types
template <IsIdType Id>
std::ostream& operator<<(std::ostream& os, Id const& value) {
    return value.streamTo(os, demangle(typeid(Id).name()));
}


/// \brief Saturated (won't overflow, stops at zero) In-place decrement of
/// the ID
template <IsIdType Id>
Id& operator--(Id& id) {
    id.setValue(
        id.getMaskUnshifed() | saturating_sub(id.getUnmasked(), 1));
    return id;
}

/// \brief Saturated in-place post-decrement of the ID
template <IsIdType Id>
Id operator--(Id& id, int) {
    Id res = id;
    id.setValue(
        id.getMaskUnshifed() | saturating_sub(id.getUnmasked(), 1));
    return res;
}

/// \brief Saturated in-place pre-increment of the ID
template <IsIdType Id>
Id& operator++(Id& id) {
    id.setValue(
        id.getMaskUnshifed() | saturating_add(id.getUnmasked(), 1));
    return id;
}


/// \brief Increment ID value by \arg extent. Addition is saturated and
/// unmasked part won't overflow
template <IsIdType Id>
Id operator+(Id id, int extent) {
    return Id::FromValue(
        id.getMaskUnshifed() | saturating_add(id.getUnmasked(), extent));
}

/// \brief Saturated in-place post-increment of the ID
template <IsIdType Id>
Id operator++(Id& id, int) {
    Id res = id;
    id.setValue(
        id.getMaskUnshifed() | saturating_add(id.getUnmasked(), 1));
    return res;
}

/// \brief Get distance between two IDs.
///
/// \note Masked portions are ignored, only unmasked indices are compared
template <IsIdType Id>
typename Id::id_base_type distance(CR<Id> first, CR<Id> last) {
    return saturating_sub(last.getUnmasked(), first.getUnmasked());
}

/// \brief Get number of elements that slice refers to
template <IsIdType Id>
typename Id::id_base_type size(Slice<Id> slice) {
    return distance(slice.first, slice.last) + 1;
}


/// Type trait for accessing value type of the ID type
template <typename T>
struct value_type {
    /// \brief ID value type typedef
    using type = typename T::value_type;
};

/// Helper alias for accessing value type of the type
template <typename T>
using value_type_t = typename value_type<T>::type;

/// Type trait tructure for inferring id type of the stored type
template <typename T>
struct id_type {
    /// \brief Stored value ID type
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
    Vec<T> content;

    Store() = default;
    void resize(int size, T const& value = T()) {
        content.resize(size, value);
    }

    void reserve(int size) { content.reserve(size); }

    /// Add value to the storage and return newly created ID
    [[nodiscard]] auto add(const T& value) -> Id {
        int index = content.size();
        content.push_back(value);
        return Id(index);
    }

    /// \brief Add new item to the store and return newly created ID
    [[nodiscard]] auto add(const T&& value) -> Id {
        int index = content.size();
        content.push_back(value);
        return Id(index);
    }

    /// \brief Last element stored in the store (by index)
    Id back() const { return Id::FromValue(content.size()); }

    /// \brief Mutable reference of the value at specific *index* (don't
    /// confuse with ID)
    auto atIndex(int index) -> T& { return content.at(index); }
    /// \brief Immutable reference
    auto atIndex(int index) const -> CR<T> { return content.at(index); }

    /// \brief Span view over multiple values referenced by slice.
    ///
    /// \note Both start and end ID should ideally have the same store
    /// index, otherwise this method does not make a lot of sense.
    std::span<T> at(HSlice<Id, Id> slice) {
        return content.at(
            slice(slice.first.getIndex(), slice.last.getIndex()));
    }


    /// \brief Get a mutable reference to an object pointed to by the \arg
    /// id
    auto at(Id id) -> T& { return content.at(id.getIndex()); }
    /// \brief Get a immutable reference to an object pointed to by the
    /// \arg id
    auto at(Id id) const -> CR<T> { return content.at(id.getIndex()); }
    /// \brief Get a total number of the stored objects int the store
    auto size() const -> std::size_t { return content.size(); }

    /// \brief Get genetator for all stored indices and pairs
    auto pairs() const -> generator<std::pair<Id, CP<T>>> {
        const int size = content.size();
        for (int i = 0; i < size; ++i) {
            co_yield {Id(i), &content.at(i)};
        }
    }

    /// \brief Return generator for stored values
    auto items() const -> generator<CP<T>> {
        for (const auto& it : content) {
            co_yield &it;
        }
    }

    /// \brief Iterate over mutable pointers to the items stored in the
    /// container
    auto items() -> generator<Ptr<T>> {
        for (auto& it : content) {
            co_yield &it;
        }
    }

    /// \brief Insert value into the store at position, either appending to
    /// the internal list or replacing an existing value.
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
};


/// \brief Stores values with with automatic deduplication
///
/// Interned data store - for values that can be hashed for deduplication.
/// Provided type must be usable as a key for unordered associative
/// continer.
template <IsIdType Id, typename Val>
struct InternStore {
    InternStore() = default;

    /// \brief Reverse ID mapping store
    std::unordered_map<Val, Id> id_map;
    /// \brief Underlying store for values
    dod::Store<Id, Val> content;

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

    /// \brief Value has already been interned in the store
    auto contains(CR<Val> in) const -> bool {
        return id_map.find(in) != id_map.end();
    }

    /// \brief Number of elements
    auto size() const -> std::size_t { return content.size(); }
    /// \brief Get mutable reference at the content pointed at by the ID
    auto at(Id id) -> Val& { return content.at(id); }
    /// \brief Get immutable references at the content pointed at by the ID
    auto at(Id id) const -> CR<Val> { return content.at(id); }

    /// \brief Insert new value to the store if it has not already been
    /// interned
    ///
    /// \copydoc Store::insert
    void insert(Id id, CR<Val> value) {
        if (!contains(value)) {
            content.insert(id, value);
            id_map.insert({value, id});
        }
    }

    /// \brief Return generator of the stored indices and values
    auto pairs() const -> generator<std::pair<Id, CP<Val>>> {
        return content.pairs();
    }

    /// \copydoc Store::items
    auto items() const -> generator<CP<Val>> { return content.items(); }
    /// \copydoc Store::items
    auto items() -> generator<Ptr<Val>> { return content.items(); }
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

    //// \brief Get reference to the store that is associated with \tparam
    /// Val
    template <typename Val>
        requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() -> Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// \brief An overload for the interned store case
    template <typename Val>
        requires is_in_pack_v<InternStore<id_type_t<Val>, Val>, Args...>
    auto store() -> InternStore<id_type_t<Val>, Val>& {
        return std::get<InternStore<id_type_t<Val>, Val>>(stores);
    }

    /// \brief Get reference to the store that is associated with \tparam
    /// Val
    template <typename Val>
        requires is_in_pack_v<Store<id_type_t<Val>, Val>, Args...>
    auto store() const -> const Store<id_type_t<Val>, Val>& {
        return std::get<Store<id_type_t<Val>, Val>>(stores);
    }

    /// \brief An overload for the interned store case
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

    /// \copydoc Store::at
    template <dod::IsIdType Id>
    auto at(Id id) const -> CR<value_type_t<Id>> {
        return store<value_type_t<Id>>().at(id);
    }

    /// \copydoc Store::insert
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
    /// \brief Get hash (ID value)
    auto operator()(Id it) const -> std::size_t {
        // Id uniquely identifies any entry it points to, by defintion, so
        // it can be used as a perfect hash
        return it.getValue();
    }
};
}; // namespace std
