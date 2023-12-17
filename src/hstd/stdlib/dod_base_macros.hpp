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