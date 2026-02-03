#pragma once

#include <memory>
#include <variant>
#include <type_traits>
#include <memory>
#include <variant>
#include <type_traits>
#include <boost/mp11.hpp>
#include <hstd/system/macros.hpp>
#include <boost/describe.hpp>

namespace hstd {

namespace detail::variant {

template <std::size_t I, typename Tuple>
using type_at_index_t = boost::mp11::mp_at_c<Tuple, I>;

template <typename T, typename Tuple>
constexpr std::size_t type_index_v = boost::mp11::mp_find<Tuple, T>::value;

} // namespace detail::variant

template <typename... Ts>
struct type_list_t {};

template <typename Tag>
struct dyn_variant {
    using base_class = typename Tag::base_class;
    using kind_type  = typename Tag::kind_type;
    using type_list  = typename Tag::type_list;

    std::shared_ptr<base_class> data;

    dyn_variant() = default;

    template <typename T>
    dyn_variant(std::shared_ptr<T> ptr) : data{std::move(ptr)} {}

    template <typename T, typename... Args>
    static dyn_variant make(Args&&... args) {
        return dyn_variant{
            std::make_shared<T>(std::forward<Args>(args)...)};
    }

    kind_type kind() const { return Tag::get_kind(data.get()); }

    int index() const { return static_cast<int>(kind()); }

    bool valueless_by_exception() const noexcept {
        return data == nullptr;
    }

    explicit operator bool() const noexcept { return data != nullptr; }

    base_class* get() const { return data.get(); }

    template <typename T>
    T* get_if() const {
        if (!data) { return nullptr; }
        if (kind() != T::staticKind) { return nullptr; }
        return static_cast<T*>(data.get());
    }
};

template <typename T, typename Tag>
T* get_if(dyn_variant<Tag>* v) {
    if (!v || !v->data) { return nullptr; }
    if (v->kind() != T::staticKind) { return nullptr; }
    return static_cast<T*>(v->data.get());
}

template <typename T, typename Tag>
T const* get_if(dyn_variant<Tag> const* v) {
    if (!v || !v->data) { return nullptr; }
    if (v->kind() != T::staticKind) { return nullptr; }
    return static_cast<T const*>(v->data.get());
}

template <typename T, typename Tag>
T& get(dyn_variant<Tag>& v) {
    T* ptr = get_if<T>(&v);
    if (!ptr) { throw std::bad_variant_access{}; }
    return *ptr;
}

template <typename T, typename Tag>
T const& get(dyn_variant<Tag> const& v) {
    T const* ptr = get_if<T>(&v);
    if (!ptr) { throw std::bad_variant_access{}; }
    return *ptr;
}

template <typename T, typename Tag>
bool holds_alternative(dyn_variant<Tag> const& v) {
    if (!v.data) { return false; }
    return v.kind() == T::staticKind;
}

namespace detail::variant {

template <typename Visitor, typename Tag, std::size_t I>
decltype(auto) dyn_visit_impl_single_const(
    Visitor&&               vis,
    dyn_variant<Tag> const& v) {
    using type = type_at_index_t<I, typename Tag::types>;
    return std::forward<Visitor>(vis)(
        std::dynamic_pointer_cast<type>(v.data));
}

template <typename Visitor, typename Tag, std::size_t... Is>
decltype(auto) dyn_visit_impl_const(
    Visitor&&               vis,
    dyn_variant<Tag> const& v,
    std::index_sequence<Is...>) {
    using return_type = decltype(dyn_visit_impl_single_const<
                                 Visitor,
                                 Tag,
                                 0>(std::forward<Visitor>(vis), v));
    using func_type = return_type (*)(Visitor&&, dyn_variant<Tag> const&);

    static constexpr func_type table[] = {
        &dyn_visit_impl_single_const<Visitor, Tag, Is>...};

    return table[v.index()](std::forward<Visitor>(vis), v);
}

} // namespace detail::variant


template <typename Visitor, typename Tag>
decltype(auto) dyn_visit(Visitor&& vis, dyn_variant<Tag> const& v) {
    if (!v.data) { throw std::bad_variant_access{}; }
    return detail::variant::dyn_visit_impl_const(
        std::forward<Visitor>(vis),
        v,
        std::make_index_sequence<Tag::type_count>{});
}

template <typename Tag, typename Factory, int... Is>
dyn_variant<Tag> from_index_impl(
    int       index,
    Factory&& factory,
    std::index_sequence<Is...>) {
    using variant_type = dyn_variant<Tag>;
    using func_type    = variant_type (*)(Factory&&);

    static constexpr auto make_func =
        []<int I>(std::integral_constant<int, I>) {
            return +[](Factory&& f) -> variant_type {
                using type = detail::variant::
                    type_at_index_t<I, typename Tag::types>;
                return variant_type{std::make_shared<type>(
                    std::forward<Factory>(f).template operator()<type>())};
            };
        };

    static constexpr func_type table[] = {
        make_func(std::integral_constant<int, Is>{})...};

    return table[index](std::forward<Factory>(factory));
}

template <typename Tag, typename Factory>
dyn_variant<Tag> from_index(Tag, int index, Factory&& factory) {
    return from_index_impl<Tag>(
        index,
        std::forward<Factory>(factory),
        std::make_index_sequence<Tag::type_count>{});
}

template <typename Tag>
dyn_variant<Tag> from_index(Tag, int index) {
    auto default_factory = []<typename T>() { return T{}; };
    return from_index_impl<Tag>(
        index,
        default_factory,
        std::make_index_sequence<Tag::type_count>{});
}

} // namespace hstd

#define DEFINE_DYN_VARIANT_BASE_TYPE_BODY(                                \
    BaseType, KindEnumName, __get_kind, ...)                              \
    DECL_DESCRIBED_ENUM(KindEnumName, __VA_ARGS__);                       \
    virtual KindEnumName __get_kind() const = 0;                          \
    virtual ~BaseType()                     = default;

#define DEFINE_DYN_VARIANT_DERIVED_TYPE_BODY(                             \
    DerivedTypeName, KindEnumName, __get_kind)                            \
    static constexpr KindEnumName staticKind = KindEnumName::             \
        DerivedTypeName;                                                  \
    Kind __get_kind() const override { return staticKind; }

#define DEFINE_DYN_VARIANT_TAG(                                           \
    TagName, BaseClass, KindEnum, GetKindExpr, ...)                       \
    struct TagName {                                                      \
        using base_class                = BaseClass;                      \
        using kind_type                 = KindEnum;                       \
        using type_list                 = hstd::type_list_t<__VA_ARGS__>; \
        using types                     = std::tuple<__VA_ARGS__>;        \
        static constexpr int type_count = std::tuple_size_v<types>;       \
        static kind_type     get_kind(base_class const* ptr) {            \
            return GetKindExpr;                                       \
        }                                                                 \
    };
