#pragma once

#include <functional>

/// \brief Trigger callback when exiting the scope. Ad-hoc RAII
/// implementation
struct finally {
    std::function<void(void)> action;
    explicit finally(std::function<void(void)> _action)
        : action(_action) {}

    template <typename T>
    static finally init(
        std::function<void(T const&)> _action,
        T const&                      value) {
        return finally([value, _action]() { _action(value); });
    }

    ~finally() { action(); }
};

/// \brief Overloading support for `std::visit`
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <typename T>
bool notNil(T* ptr) {
    return ptr != nullptr;
}

/// \brief Check if pointer is a null pointer
template <typename T>
bool isNil(T* ptr) {
    return ptr == nullptr;
}

/// \brief Helper base type for defining CRTP classes
template <typename T>
struct CRTP_this_method {
  protected:
    inline T*       _this() { return static_cast<T*>(this); }
    inline T const* _this() const { return static_cast<T const*>(this); }
};

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a##b


#define __ploc()                                                          \
    std::cout << __FILE__ << ":" << __LINE__ << " at " << __func__        \
              << std::endl;


template <typename T>
bool is_within_memory_block(
    T const*    ptr,
    T const*    start,
    std::size_t size) {
    // calculate the end of the memory block
    T const* end = start + size;

    // check if the pointer is within the memory block
    return start <= ptr && ptr < end;
}

template <typename T>
bool is_pointer_valid(T const* ptr, T const* start, std::size_t size) {
    // check if the pointer is null or not within the memory block
    return ptr != nullptr && is_within_memory_block(ptr, start, size);
}

template <typename T>
std::ptrdiff_t pointer_distance(T const* first, T const* last) {
    return last - first;
}


#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define __unpack_pars(...) __VA_ARGS__
#define __macro_aux(macro, pass, ...)                                     \
    macro(__unpack_pars pass, __VA_ARGS__)


#define __FOR_EACH_HELPER(macro, pass, a1, ...)                           \
    __macro_aux(macro, pass, a1)                                          \
        __VA_OPT__(__FOR_EACH_AGAIN PARENS(macro, pass, __VA_ARGS__))

#define __FOR_EACH_AGAIN() __FOR_EACH_HELPER

#define FOR_EACH_CALL_WITH_PASS(macro, pass, ...)                         \
    __VA_OPT__(EXPAND(__FOR_EACH_HELPER(macro, pass, __VA_ARGS__)))


/// \internal Generate getter methods for SUB_VARIANTS
#define __SUB_VARIANT_GETTER(fieldName, Type)                             \
    Type&       get##Type() { return std::get<Type>(fieldName); }         \
    Type const& get##Type() const { return std::get<Type>(fieldName); }

/// \internal Generate kind getter lambda for SUB_VARIANTS
#define __SUB_VARIANT_KIND_LAMBDA(EnumName, Type)                         \
    [](Type const&) -> EnumName { return EnumName::Type; },

/// \brief Declare enum \arg Name with all it's fields and pass them to
/// BOOST_DESCRIBE_NESTED_ENUM to generate reflection information.
#define DECL_DESCRIBED_ENUM(Name, ...)                                    \
    enum class Name                                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(Name, __VA_ARGS__);

/// \brief Helper macro for better API when working with discriminant
/// objects.
///
/// \arg EnumName name of the enumeration that is defined to list possible
///      variant values
/// \arg VariantName Name of the variant type for wrapping
///      all results
/// \arg fieldName Name of the field that is used to store
///      variant value for a type
/// \arg kindGetterName name of the method for getting kind from the field.
///      Also defines static function that can be used to access the kind
///      of the raw variant value.
///
/// \snippet sem/SemOrg.hpp declare variant field for subtree properties
///
/// This will generate `getKind()` and `static getKind(Data const&)`
/// methods, define `Data` as `std::variant<Ordered, ...>` and implement
/// `getOrdered()`, `getTrigger()` etc. for all provided types
#define SUB_VARIANTS(                                                     \
    EnumName, VariantName, fieldName, kindGetterName, ...)                \
    DECL_DESCRIBED_ENUM(EnumName, __VA_ARGS__)                            \
    using VariantName = std::variant<__VA_ARGS__>;                        \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __SUB_VARIANT_GETTER, (fieldName), __VA_ARGS__)                   \
    static EnumName kindGetterName(CR<VariantName> __input) {             \
        return std::visit(                                                \
            overloaded{FOR_EACH_CALL_WITH_PASS(                           \
                __SUB_VARIANT_KIND_LAMBDA, (EnumName), __VA_ARGS__)},     \
            __input);                                                     \
    }                                                                     \
    EnumName kindGetterName() const { return kindGetterName(fieldName); }


// Sub variant using union

#define __SUB_VARIANT_UNION_GETTER(fieldName, Type)                       \
    Type&       get##Type() { std::get<Type>(fieldName); }                \
    Type const& get##Type() const { std::get<Type>(fieldName); }

#define __SUB_VARIANT_UNION_KIND_LAMBDA(EnumName, Type)                   \
    [](Type const&) { return EnumName::Type; },

#define __SUB_VARIANT_UNION_DEFINE_UNION(_, Type) Type Type##_field;

#define __PACK_IDX0(it1, ...) it1
#define __PACK_IDX1(it1, it2, ...) it2
#define __PACK_IDX2(it1, it2, it3, ...) it3


#define __SUB_VARIANT_UNION_DEFINE_INNER_METHODS(Pass, Type)              \
    __PACK_IDX1(Pass)                                                     \
    (Type const& arg)                                                     \
        : kindValue(__PACK_IDX0(Pass)::Type), Type##_field(arg) {}


#define __SUB_VARIANT_UNION_DEFINE_METHODS(Pass, Type)                    \
    Type& get##Type() {                                                   \
        Q_ASSERT(__PACK_IDX1(Pass).kindValue == __PACK_IDX0(Pass)::Type); \
        return __PACK_IDX1(Pass).Type##_field;                            \
    }                                                                     \
                                                                          \
    Type const& get##Type() const {                                       \
        Q_ASSERT(__PACK_IDX1(Pass).kindValue == __PACK_IDX0(Pass)::Type); \
        return __PACK_IDX1(Pass).Type##_field;                            \
    }

#define __SUB_VARIANT_UNION_DEFINE_VISIT(EnumName, Type)                  \
    case __PACK_IDX0(EnumName)::Type:                                     \
        return cb(                                                        \
            Type##_field, std::forward<Args>(__PACK_IDX1(EnumName))...);

#define __SUB_VARIANT_UNION_DEFINE_FIELD_COPY(EnumName, Type)             \
    case __PACK_IDX0(EnumName)::Type:                                     \
        this->Type##_field = other.Type##_field;                          \
        break;

#define __SUB_VARIANT_UNION_DEFINE_FIELD_DESTROY(EnumName, Type)          \
    case __PACK_IDX0(EnumName)::Type:                                     \
        Type##_field.~Type();                                             \
        break;


#define __TAIL(Head, ...) __VA_ARGS__
#define __HEAD(Head, ...) Head


#define SUB_VARIANTS_UNION(                                               \
    EnumName, VariantName, fieldName, kindGetterName, ...)                \
                                                                          \
    DECL_DESCRIBED_ENUM(EnumName, __VA_ARGS__)                            \
                                                                          \
    struct VariantName {                                                  \
        EnumName kindValue;                                               \
                                                                          \
        union {                                                           \
            __HEAD(__VA_ARGS__)                                           \
            CONCAT(__HEAD(__VA_ARGS__), _field) = __HEAD(__VA_ARGS__)();  \
            FOR_EACH_CALL_WITH_PASS(                                      \
                __SUB_VARIANT_UNION_DEFINE_UNION,                         \
                (fieldName),                                              \
                __TAIL(__VA_ARGS__))                                      \
        };                                                                \
                                                                          \
        FOR_EACH_CALL_WITH_PASS(                                          \
            __SUB_VARIANT_UNION_DEFINE_INNER_METHODS,                     \
            (EnumName, VariantName),                                      \
            __VA_ARGS__)                                                  \
                                                                          \
        VariantName()                                                     \
            : kindValue(EnumName::__PACK_IDX0(__VA_ARGS__))               \
            , CONCAT(__PACK_IDX0(__VA_ARGS__), _field)(                   \
                  __PACK_IDX0(__VA_ARGS__)()) {}                          \
                                                                          \
                                                                          \
        VariantName(VariantName const& other)                             \
            : kindValue(other.kindValue) {                                \
            switch (kindValue) {                                          \
                FOR_EACH_CALL_WITH_PASS(                                  \
                    __SUB_VARIANT_UNION_DEFINE_FIELD_COPY,                \
                    (EnumName),                                           \
                    __VA_ARGS__)                                          \
            }                                                             \
        }                                                                 \
                                                                          \
        VariantName& operator=(VariantName const& other) {                \
            this->kindValue = other.kindValue;                            \
            switch (kindValue) {                                          \
                FOR_EACH_CALL_WITH_PASS(                                  \
                    __SUB_VARIANT_UNION_DEFINE_FIELD_COPY,                \
                    (EnumName),                                           \
                    __VA_ARGS__)                                          \
            }                                                             \
        }                                                                 \
                                                                          \
        ~VariantName() {                                                  \
            switch (kindValue) {                                          \
                FOR_EACH_CALL_WITH_PASS(                                  \
                    __SUB_VARIANT_UNION_DEFINE_FIELD_DESTROY,             \
                    (EnumName),                                           \
                    __VA_ARGS__)                                          \
            }                                                             \
        }                                                                 \
                                                                          \
        template <typename Func, typename... Args>                        \
        auto visit(Func const& cb, Args&&... args) {                      \
            switch (kindValue) {                                          \
                FOR_EACH_CALL_WITH_PASS(                                  \
                    __SUB_VARIANT_UNION_DEFINE_VISIT,                     \
                    (EnumName, args),                                     \
                    __VA_ARGS__)                                          \
            }                                                             \
        }                                                                 \
                                                                          \
        template <typename Func, typename... Args>                        \
        auto visit(Func const& cb, Args&&... args) const {                \
            switch (kindValue) {                                          \
                FOR_EACH_CALL_WITH_PASS(                                  \
                    __SUB_VARIANT_UNION_DEFINE_VISIT,                     \
                    (EnumName, args),                                     \
                    __VA_ARGS__)                                          \
            }                                                             \
        }                                                                 \
    };                                                                    \
                                                                          \
    EnumName kindGetterName() const { return fieldName.kindValue; }       \
                                                                          \
    FOR_EACH_CALL_WITH_PASS(                                              \
        __SUB_VARIANT_UNION_DEFINE_METHODS,                               \
        (EnumName, fieldName),                                            \
        __VA_ARGS__)                                                      \
                                                                          \
    static EnumName kindGetterName(VariantName const& dat) {              \
        return dat.kindValue;                                             \
    }
