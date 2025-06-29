#pragma once

#include <string>
#include <unordered_map>

#include <hstd/system/all.hpp>
#include <hstd/system/generator.hpp>
#include <hstd/stdlib/Exception.hpp>

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/Map.hpp>


/// \brief Data-oriented design primitives
///
/// This namespace provides implementation of the Data-orited design
/// primitives such as stores and ID type. The implementation is largely
/// based on my understanding of the DOD practices and as such might
/// contain some things that could be implemented differently or ones that
/// are not necessary at all.
///
/// The main types in the namespace are `dod::Store` (flat sequence of
/// values, adressable by the ID), `dod::InternStore` (de-duplicate stored
/// values using hashing) and `dod::Id` (base type for the ID).
///
/// `dod::MultiStore` is an additional helper type to simplify management
/// of multiple stores.
namespace hstd::dod {
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
///
/// \note Store only uses the index part of the ID -- mask bytes are
/// reserved for additional metadata that developer might use. All `.add()`
/// operations return the ID constructed without any mask set, and
/// accessing the content in the store using ID will only read index.
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
    using id_mask_type = MaskType;
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

    static Id FromIndex(IdType id) { return Id{id}; }

    /// \brief Create ID value from provided mask and underlying ID base
    static auto FromMaskedIdx(IdType id, MaskType mask) -> Id {
        Id res = FromIndex(id);
        res.setMask(mask);
        return res;
    }

    /// \brief Get number of bits in the mask
    consteval int getMaskSize() const { return mask_size; }
    /// \brief Get unmasked *value* (do not confuse with index)
    inline IdType getUnmasked() const {
        if (mask_size == 0) {
            return value;
        } else {
            return value & ~(~IdType(0) << mask_offset);
        }
    }


    /// \brief Get mask value
    inline MaskType getMask() const {
#pragma clang diagnostic ignored "-Wshift-count-overflow"
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
        uint64_t mask_check = (1ULL << mask_size) - 1;
        if ((mask & ~mask_check) != 0) {
            throw std::logic_error(fmt(
                R"(ID Mask must have bits set in range [{0}..0], but provided value {1:016X} {1:064b} has higher bits set:
mask:  {1:064b}
check: {2:064b}
)",
                mask_size,
                mask,
                mask_check));
        }

        LOGIC_ASSERTION_CHECK(
            mask_offset < sizeof(decltype(mask)) * 8,
            "Shift count exceeds type width");
        auto shift = mask << mask_offset;
        value      = getUnmasked() | shift;
    }

    /// \brief Check whether provided value is nil or not
    auto isNil() const noexcept -> bool { return getUnmasked() == 0; }
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
            throw RangeError::init(
                "Cannot get index for nil value of DOD ID");
        } else {
            return (getUnmasked() - 1);
        }
    }

    int getIntIndex() const { return static_cast<int>(getIndex()); }
    long long int getLongIntIndex() const {
        return static_cast<long long int>(getIndex());
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
        return getValue() != other.getValue();
    }

    /// \brief Write strig representation of the ID into output stream
    std::string format(std::string name = "Id", bool withMask = true)
        const {
        std::string result;
        if (name.size() != 0) { result += name + "("; }

        if (withMask) {
            if (0 < mask_size) {
                result += std::to_string(getMask()) + ":";
            }
        }

        if (isNil()) {
            result += "<nil>";
        } else {
            result += std::to_string(getIndex());
        }

        if (name.size() != 0) { result += ")"; }

        return result;
    }

  public:
    /// \brief Full value of the ID, including masked part
    IdType value;

    BOOST_DESCRIBE_CLASS(Id, (), (value), (), ());
};


#define DECL_ID_TYPE_MASKED(__value, __name, __type, __mask)              \
    struct __value;                                                       \
    using __name##BaseId = ::hstd::dod::                                  \
        Id<__type, __type, std::integral_constant<__type, __mask>>;       \
    struct [[nodiscard]] __name : public __name##BaseId {                 \
        BOOST_DESCRIBE_CLASS(__name, (__name##BaseId), (), (), ());       \
        using value_type = __value;                                       \
                                                                          \
        static auto Nil() -> __name { return FromValue(0); };             \
                                                                          \
        static auto FromValue(__type arg) -> __name {                     \
            __name res{__type{}};                                         \
            res.setValue(arg);                                            \
            return res;                                                   \
        }                                                                 \
                                                                          \
        auto operator==(__name other) const -> bool {                     \
            return getValue() == other.getValue();                        \
        }                                                                 \
                                                                          \
        __name(__name##BaseId const& arg) : __name##BaseId(arg) {}        \
                                                                          \
        explicit __name(__type arg) : __name##BaseId(arg) {}              \
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
    DECL_ID_TYPE_MASKED(__value, __name, __type, 0)


/// Concent for base ID type and all it's publcily derived types
template <typename D>
concept IsIdType = is_base_of_template_v<Id, D>;

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

template <IsIdType Id>
auto operator-(Id lhs, Id rhs) {
    return lhs.getUnmasked() - rhs.getUnmasked();
}

/// \brief Increment ID value by \arg extent. Addition is saturated and
/// unmasked part won't overflow
template <IsIdType Id>
Id operator+(Id id, int extent) {
    return Id::FromValue(
        id.getMaskUnshifed()
        | saturating_add_any(id.getUnmasked(), extent));
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
    DESC_FIELDS(Store, (content));
    using ContentT = Vec<T>;

    Store() = default;
    void resize(int size, T const& value = T()) {
        content.resize(size, value);
    }

    void reserve(int size) { content.reserve(size); }


    bool contains(Id id) const {
        // TODO add support for dedicated store mask that will be compared
        // in order to get better checking. Implement checking using
        // `sameMask()` method that could be called separately.
        return !id.isNil() && id.getIndex() < content.size();
    }

    /// Add value to the storage and return newly created ID
    [[nodiscard]] auto add(const T& value, Id::id_mask_type mask) -> Id {
        int index = content.size();
        content.push_back(value);
        auto result = Id::FromMaskedIdx(index, mask);
        LOGIC_ASSERTION_CHECK(
            !result.isNil(),
            "Implementation error, added ID cannot be nil");
        return result;
    }

    /// \brief Add new item to the store and return newly created ID
    [[nodiscard]] auto add(const T&& value, Id::id_mask_type mask) -> Id {
        int index = content.size();
        content.push_back(value);
        auto result = Id::FromMaskedIdx(index, mask);
        LOGIC_ASSERTION_CHECK(
            !result.isNil(),
            "Implementation error, added ID cannot be nil");
        return result;
    }

    /// Add value to the storage and return newly created ID
    [[nodiscard]] auto add(const T& value) -> Id {
        int index = content.size();
        content.push_back(value);
        auto result = Id::FromIndex(index);
        LOGIC_ASSERTION_CHECK(
            !result.isNil(),
            "Implementation error, added ID cannot be nil");
        return result;
    }

    /// \brief Add new item to the store and return newly created ID
    [[nodiscard]] auto add(const T&& value) -> Id {
        int index = content.size();
        content.push_back(value);
        auto result = Id::FromIndex(index);
        LOGIC_ASSERTION_CHECK(
            !result.isNil(),
            "Implementation error, added ID cannot be nil");
        return result;
    }

    /// \brief Last element stored in the store (by index)
    Id back() const { return Id::FromValue(content.size()); }
    Id high() const { return Id::FromValue(content.size() - 1); }

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
    auto size() const -> int { return content.size(); }
    bool empty() const { return size() == 0; }

    /// \brief Get generator for all stored indices and pairs
    auto pairs() const -> generator<std::pair<Id, CP<T>>> {
        const int size = content.size();
        for (int i = 0; i < size; ++i) {
            co_yield {Id::FromIndex(i), &content.at(i)};
        }
    }

    /// \brief Return generator for stored values
    auto items() const -> generator<CP<T>> {
        for (const auto& it : content) { co_yield &it; }
    }

    /// \brief Iterate over mutable pointers to the items stored in the
    /// container
    auto items() -> generator<Ptr<T>> {
        for (auto& it : content) { co_yield &it; }
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
    hstd::UnorderedMap<Val, Id> id_map;
    /// \brief Underlying store for values
    dod::Store<Id, Val> content;

    DESC_FIELDS(InternStore, (id_map, content))

    /// Add value to the store - if the value is already contained can
    /// return previous ID
    [[nodiscard]] auto add(
        CR<Val>                                  in,
        std::optional<typename Id::id_mask_type> mask = std::nullopt)
        -> Id {
        auto found = id_map.find(in);
        if (found != id_map.end()) {
            LOGIC_ASSERTION_CHECK(
                !found->second.isNil(),
                "Implementation error, added ID cannot be nil");
            return found->second;
        } else {
            auto result = mask.has_value() ? content.add(in, mask.value())
                                           : content.add(in);
            id_map.insert({in, result});
            LOGIC_ASSERTION_CHECK(
                !result.isNil(),
                "Implementation error, added ID cannot be nil");
            return result;
        }
    }

    /// \brief Value has already been interned in the store
    auto contains(CR<Val> in) const -> bool {
        return id_map.find(in) != id_map.end();
    }

    bool empty() const { return size() == 0; }

    /// \brief Number of elements
    auto size() const -> int { return content.size(); }
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
            LOGIC_ASSERTION_CHECK(
                !id.isNil(), "cannot use nil ID for interned store key");
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

    //// \brief Get reference to the store that is associated with
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

    /// \brief Get reference to the store that is associated with
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

}; // namespace hstd::dod

namespace std {
template <hstd::dod::IsIdType Id>
struct hash<Id> {
    /// \brief Get hash (ID value)
    auto operator()(Id it) const -> std::size_t {
        // Id uniquely identifies any entry it points to, by defintion, so
        // it can be used as a perfect hash
        return it.getValue();
    }
};
}; // namespace std


namespace hstd::dod {
template <typename T>
concept IsDescribedDodIdType = hstd::dod::IsIdType<T>
                            && hstd::DescribedRecord<T>;
}

template <hstd::dod::IsDescribedDodIdType Id>
struct std::formatter<Id> : std::formatter<std::string> {
    using FmtType = Id;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(p.format(), ctx);
    }
};
