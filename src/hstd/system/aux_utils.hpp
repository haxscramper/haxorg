#pragma once

#include <functional>

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

template <typename T>
bool isNil(T* ptr) {
    return ptr == nullptr;
}

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


#define __SUB_VARIANT_GETTER(fieldName, Type)                             \
    Type&       get##Type() { return std::get<Type>(fieldName); }         \
    Type const& get##Type() const { return std::get<Type>(fieldName); }

#define __SUB_VARIANT_KIND_LAMBDA(EnumName, Type)                         \
    [](Type const&) -> EnumName { return EnumName::Type; },

#define DECL_DESCRIBED_ENUM(Name, ...)                                    \
    enum class Name                                                       \
    {                                                                     \
        __VA_ARGS__                                                       \
    };                                                                    \
    BOOST_DESCRIBE_NESTED_ENUM(Name, __VA_ARGS__);

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
