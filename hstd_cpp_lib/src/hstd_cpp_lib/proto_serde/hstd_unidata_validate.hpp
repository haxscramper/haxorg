#pragma once

#include "hstd_cpp_lib/stdlib/formatting/Formatter.hpp"
#include "hstd_cpp_lib/system/exceptions.hpp"
#include <cstring>
#include <functional>
#include <hstd_cpp_lib/stdlib/Func.hpp>
#include <hstd_cpp_lib/stdlib/Str.hpp>
#include <hstd_cpp_lib/stdlib/algorithms/reflection/reflection_visitor.hpp>
#include <hstd_cpp_lib/stdlib/containers/Map.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Pair.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/PairFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>
#include <hstd_cpp_lib/system/macros.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <memory>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <variant>


namespace hstd::ext::unidata {
struct QName {
    hstd::Str        name;
    hstd::Vec<QName> scope;
    DESC_FIELDS(QName, (name, scope));

    bool operator==(QName const& other) const {
        if (this->scope.size() != other.scope.size()) { return false; }
        for (int i = 0; i < scope.size(); ++i) {
            if (scope.at(i) != other.scope.at(i)) { return false; }
        }
        return this->name == other.name;
    }
};

struct VerifyResult {
    std::string message;
    bool        is_ok;

    static VerifyResult Ok();
    static VerifyResult Error(std::string const& failure);
    DESC_FIELDS(VerifyResult, (message, is_ok));
};

struct VerifyContext;

using VerifyCb = hstd::Func<VerifyResult(VerifyContext const* ctx, void const* value)>;
using VerifyCbList = hstd::Vec<VerifyCb>;
using VerifyKey    = hstd::Pair<QName, hstd::Opt<std::string>>;

} // namespace hstd::ext::unidata

template <>
struct std::hash<hstd::ext::unidata::QName> {
    std::size_t operator()(hstd::ext::unidata::QName const& it) const noexcept {
        std::size_t result = 0;
        ::hstd::hax_hash_combine(result, it.name);
        for (auto const& scope : it.scope) { ::hstd::hax_hash_combine(result, scope); }
        return result;
    }
};


namespace hstd::ext::unidata {

struct VerifyCheckCollection {
    hstd::UnorderedMap<VerifyKey, VerifyCbList> checks;
};


struct VerifyResultCollection {
    hstd::Vec<VerifyResult> results;

    hstd::Vec<VerifyResult> getFail() const {
        hstd::Vec<VerifyResult> res;
        for (auto const& it : results) {
            if (!it.is_ok) { res.push_back(it); }
        }
        return res;
    }
};


template <typename T>
concept IsUnidataClass = requires(T& value) {
    { value.get_unidata_checks() } -> std::same_as<VerifyCheckCollection const*>;

    requires std::same_as<std::remove_cv_t<decltype(T::unidata_id)>, std::string>;

    requires std::is_pointer_v<decltype(&T::unidata_id)>;
};


struct UnidataTag {
    // TODO: string for now, later might use faster solution from the immutable AST
    using field_name_type = std::string;
};

using UniAccessStep      = hstd::ReflAccessStep<UnidataTag>;
using UniValueAccessPath = hstd::ReflValueAccessPath<UnidataTag>;

} // namespace hstd::ext::unidata

template <>
struct ::hstd::ReflTypeTraits<hstd::ext::unidata::UnidataTag> {
    using AnyTypeTuple     = std::tuple<Str, std::string>;
    using AnyFormatterType = AnyFormatter<Str, std::string>;
    using AnyHasherType    = AnyHasher<Str, std::string>;
    using AnyEqualType     = AnyEqual<Str, std::string>;

    using ReflPathStoreType = SmallVec<ReflAccessStep<hstd::ext::unidata::UnidataTag>, 2>;

    template <typename T>
    static Str InitFieldName(T const& value, auto const& field) {
        return field.name;
    }

    static ReflValueAccessPath<hstd::ext::unidata::UnidataTag> AddPathItem(
        ReflValueAccessPath<hstd::ext::unidata::UnidataTag> res,
        ReflAccessStep<hstd::ext::unidata::UnidataTag>      item) {
        res.path.push_back(item);
        return res;
    }
};

template <>
struct fmt::formatter<hstd::ext::unidata::UniAccessStep::FieldName> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::unidata::UniAccessStep::FieldName const& path,
        fmt::format_context&                                ctx) const {
        return hstd::fmt_ctx(path.name, ctx);
    }
};


template <>
struct fmt::formatter<hstd::ext::unidata::UniAccessStep::Index> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::unidata::UniAccessStep::Index const& path,
        fmt::format_context&                            ctx) const {
        return hstd::fmt_ctx(path.index, ctx);
    }
};


template <>
struct fmt::formatter<hstd::ext::unidata::UniAccessStep::Deref> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::unidata::UniAccessStep::Deref const& path,
        fmt::format_context&                            ctx) const {
        return hstd::fmt_ctx("*", ctx);
    }
};

template <>
struct fmt::formatter<hstd::ext::unidata::UniValueAccessPath> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ext::unidata::UniValueAccessPath const& path,
        fmt::format_context&                          ctx) const {
        for (auto const& it : path.path) {
            ::hstd::fmt_ctx("/", ctx);
            ::hstd::fmt_ctx(it, ctx);
        }
        return ::hstd::fmt_ctx("", ctx);
    }
};


namespace hstd::ext::unidata {

struct VerifyContext {
    UniValueAccessPath const* active_path;

    UniValueAccessPath const& getPath() const { return *active_path; }
};


template <typename T>
hstd::Vec<VerifyResult> verify_one_with_bases(VerifyContext const& ctx, T const& data) {
    if constexpr (IsUnidataClass<std::remove_cvref_t<T>>) {
        std::string const&      class_id{T::unidata_id};
        hstd::Vec<VerifyResult> result;
        VerifyKey               class_key{class_id, std::nullopt};
        auto const&             check_map = data.get_unidata_checks()->checks;
        if (check_map.contains(class_key)) {
            for (VerifyCb const& check : check_map.at(class_key)) {
                result.push_back(check(&ctx, (void const*)&data));
            }
        }

        hstd::for_each_field_no_base<T>([&](auto const& field) {
            VerifyKey field_key{class_id, field.name};
            if (check_map.contains(field_key)) {
                for (VerifyCb const& check : check_map.at(field_key)) {
                    result.push_back(check(&ctx, (void const*)&data));
                }
            }
        });

        return result;

    } else {
        return {};
    }
}

template <typename T>
VerifyResultCollection verify_all(T const& data) {
    VerifyResultCollection result;


    ReflRecursiveVisitContext ctx;
    reflVisitAll<T, UnidataTag>(
        data,
        {},
        ctx,
        [&]<typename FieldType>(
            ReflValueAccessPath<UnidataTag>::VisitCtx const& path,
            FieldType const&                                 field) {
            UniValueAccessPath active_path = path.toPath();
            VerifyContext      verfiy_ctx;
            verfiy_ctx.active_path = &active_path;
            result.results.append(verify_one_with_bases(verfiy_ctx, field));
        });

    return result;
}

struct DynamicT;

template <typename T>
struct IsStaticT : std::false_type {};

template <typename T>
concept NonWrapperArg = !IsStaticT<std::remove_cvref_t<T>>::value
                     && !std::same_as<std::remove_cvref_t<T>, DynamicT>;

template <NonWrapperArg T>
struct StaticT;

template <NonWrapperArg T>
struct IsStaticT<StaticT<T>> : std::true_type {};

template <typename T>
concept IsWrapperArg = IsStaticT<std::remove_cvref_t<T>>::value
                    || std::same_as<std::remove_cvref_t<T>, DynamicT>;

struct DynamicT {
    void const*        data;
    std::type_index    type;
    UniValueAccessPath path;

    using value_type = DynamicT;

    template <typename Res>
    Res const* get_as() const {
        LOGIC_ASSERTION_CHECK(typeid(std::remove_cvref_t<Res>) == type, "");
        return static_cast<Res const*>(data);
    }

    std::shared_ptr<void const> anchor;

    std::shared_ptr<void const> owner() const { return anchor; }

    template <typename T>
    static DynamicT FromValue(
        T const&                           value,
        std::shared_ptr<void const> const& owner = {}) {
        return DynamicT{
            .data   = &value,
            .type   = typeid(std::remove_cvref_t<T>),
            .path   = {},
            .anchor = owner,
        };
    }


    DESC_FIELDS(DynamicT, (data, type, path));
};

template <NonWrapperArg T>
struct StaticT {
  private:
    std::shared_ptr<T const> value;
    StaticT(std::shared_ptr<T const> const& value) : value{value} {}

  public:
    static StaticT<T> FromLValue(T const* value) {
        return std::shared_ptr<T const>(value, [](T const*) {});
    }

    static StaticT<T> FromRValue(T const& value) {
        return std::make_shared<T const>(value);
    }

    using value_type = T;

    template <typename Res>
    Res const* get_as() const {
        static_assert(std::same_as<Res, T>);
        return value.get();
    }

    std::shared_ptr<void const> owner() const { return value; }

    static StaticT<T> FromAlias(T const* item, std::shared_ptr<void const> const& owner) {
        return StaticT<T>{std::shared_ptr<T const>{owner, item}};
    }
};


template <typename Parent, typename Item>
auto lift_expression_value(
    Parent const&             parent,
    Item const*               item,
    UniValueAccessPath const& path);

/// \brief Single materialized value with additional path context
template <IsWrapperArg T>
struct UniValue {
    T                  value;
    UniValueAccessPath path;
    DESC_FIELDS(UniValue, (value, path));

    using value_type = typename T::value_type;

    std::shared_ptr<void const> owner() const { return value.owner(); }


    template <typename Res>
    Res const* get_as() const {
        return value.template get_as<Res>();
    }

    T::value_type const* get() const {
        if constexpr (std::is_same_v<T, DynamicT>) {
            return &value;
        } else {
            return value.template get_as<typename T::value_type>();
        }
    }

    template <NonWrapperArg SubItem>
    static UniValue<StaticT<SubItem>> RootValue(
        SubItem const*            value,
        UniValueAccessPath const& supath) {
        return UniValue<StaticT<SubItem>>(StaticT<SubItem>::FromLValue(value), supath);
    }

    template <NonWrapperArg SubItem>
    static UniValue<StaticT<SubItem>> SubExprNoContext(
        SubItem const&     value,
        std::string const& func_name) {
        return UniValue<StaticT<SubItem>>(
            StaticT<SubItem>::FromRValue(value),
            UniValueAccessPath(UniAccessStep::FieldName(func_name)));
    }

    template <NonWrapperArg SubItem>
    static UniValue<StaticT<SubItem>> SubExprTemporaryPass(SubItem const& value) {
        return UniValue<StaticT<SubItem>>(
            StaticT<SubItem>::FromRValue(value), UniValueAccessPath());
    }


    UniValue<DynamicT> FromDynamic(
        DynamicT const&           value,
        UniValueAccessPath const& supath) {
        return UniValue<DynamicT>(value, path.add(supath));
    }


    template <NonWrapperArg SubItem>
    UniValue<StaticT<SubItem>> CallResult(
        SubItem const&     value,
        std::string const& func_name) const {
        return UniValue<StaticT<SubItem>>(
            StaticT<SubItem>::FromRValue(value),
            path.add(UniAccessStep::FieldName(hstd::fmt("{}()", func_name))));
    }

    template <typename SubItem>
    auto Field(SubItem const* value, char const* field) const {
        return lift_expression_value(
            *this, value, path.add(UniAccessStep::FromFieldName(field)));
    }


    template <typename SubItem, typename Key>
    auto AtMap(SubItem const* value, Key const* key) const {
        return lift_expression_value(
            *this, value, path.add(UniAccessStep::FromAnyKey(*key)));
    }


    template <typename SubItem, typename Key>
    auto AtIndex(SubItem const* value, Key const& key) const {
        return lift_expression_value(
            *this, value, path.add(UniAccessStep::FromIndex(static_cast<int>(key))));
    }


    template <NonWrapperArg SubItem, NonWrapperArg Key>
    UniValue<StaticT<SubItem>> AtIndex(StaticT<SubItem> const& value, Key const& key)
        const {
        return UniValue<StaticT<SubItem>>(value, path.add(UniAccessStep::Index(key)));
    }


    template <NonWrapperArg Key>
    UniValue<DynamicT> AtIndex(DynamicT const& value, Key const& key) const {
        return UniValue<DynamicT>(value, path.add(UniAccessStep::Index(key)));
    }

    template <typename SubItem>
    auto Path(SubItem const* value, UniValueAccessPath const& supath) const {
        return lift_expression_value(*this, value, path.add(supath));
    }


    template <typename Other>
    static UniValue<T> FromConst(Other const& value, std::string const& expr_value) {
        return UniValue<T>(
            T::FromRValue(value),
            UniAccessStep{UniAccessStep::FieldName(hstd::fmt("<{}>", expr_value))});
    }
};

template <typename... Args>
using UniTuple = hstd::Tuple<Args...>;

template <typename... Args>
using UniVariant = hstd::Variant<Args...>;

using UniPath = UniValueAccessPath;

template <typename K, typename V>
using UniMap = hstd::UnorderedMap<K, V>;

using UniStr = hstd::Str;

template <typename T>
using UniVec = hstd::Vec<T>;

template <typename T>
using UniOpt = hstd::Opt<T>;

template <typename T>
using UniStatic = UniValue<StaticT<T>>;

using UniDynamic = UniValue<DynamicT>;

template <typename L, typename R>
bool operator==(UniStatic<L> const& lhs, UniStatic<R> const& rhs) {
    return *lhs.get() == *rhs.get();
}

} // namespace hstd::ext::unidata

namespace std {

template <typename T>
struct hash<hstd::ext::unidata::UniValue<hstd::ext::unidata::StaticT<T>>> {
    std::size_t operator()(hstd::ext::unidata::UniStatic<T> const& value) const {
        return std::hash<T>{}(*value.get());
    }
};

} // namespace std

namespace hstd::ext::unidata {

/// Materialized expression type corresponding to a native stored type.
template <typename T>
struct ExpressionStorage {
    using type = UniStatic<T>;
};

/// Lifting an existing expression value is idempotent.
template <IsWrapperArg T>
struct ExpressionStorage<UniValue<T>> {
    using type = UniValue<T>;
};

template <typename T>
struct ExpressionStorage<UniVec<T>> {
    using type = UniStatic<UniVec<typename ExpressionStorage<T>::type>>;
};

template <typename K, typename V>
struct ExpressionStorage<UniMap<K, V>> {
    using type = UniStatic<
        UniMap<typename ExpressionStorage<K>::type, typename ExpressionStorage<V>::type>>;
};

template <typename T>
struct ExpressionStorage<UniOpt<T>> {
    using type = UniStatic<UniOpt<typename ExpressionStorage<T>::type>>;
};

template <typename... T>
struct ExpressionStorage<UniTuple<T...>> {
    using type = UniStatic<UniTuple<typename ExpressionStorage<T>::type...>>;
};

template <typename T>
using ExpressionStorageT = typename ExpressionStorage<T>::type;

template <typename T>
struct ExpressionLift {
    template <typename Parent>
    static ExpressionStorageT<T> run(
        Parent const&             parent,
        T const*                  item,
        UniValueAccessPath const& path) {
        return {
            StaticT<T>::FromAlias(item, parent.owner()),
            path,
        };
    }
};

template <IsWrapperArg T>
struct ExpressionLift<UniValue<T>> {
    template <typename Parent>
    static UniValue<T> run(
        Parent const&,
        UniValue<T> const* item,
        UniValueAccessPath const&) {
        // Existing expression values retain their original paths.
        return *item;
    }
};

template <typename T>
struct ExpressionLift<UniVec<T>> {
    template <typename Parent>
    static ExpressionStorageT<UniVec<T>> run(
        Parent const&             parent,
        UniVec<T> const*          items,
        UniValueAccessPath const& path) {
        using Result = ExpressionStorageT<UniVec<T>>;
        typename Result::value_type result;

        for (int i = 0; i < items->size(); ++i) {
            result.push_back(lift_expression_value(
                parent, &items->at(i), path.add(UniAccessStep::FromIndex(i))));
        }

        return {
            StaticT<typename Result::value_type>::FromRValue(result),
            path,
        };
    }
};

template <typename K, typename V>
struct ExpressionLift<UniMap<K, V>> {
    template <typename Parent>
    static ExpressionStorageT<UniMap<K, V>> run(
        Parent const&             parent,
        UniMap<K, V> const*       items,
        UniValueAccessPath const& path) {
        using Result = ExpressionStorageT<UniMap<K, V>>;
        typename Result::value_type result;

        for (auto const& [key, value] : *items) {
            auto item_path = path.add(UniAccessStep::FromAnyKey(key));
            result.emplace(
                lift_expression_value(parent, &key, item_path),
                lift_expression_value(parent, &value, item_path));
        }

        return {
            StaticT<typename Result::value_type>::FromRValue(result),
            path,
        };
    }
};

template <typename T>
struct ExpressionLift<UniOpt<T>> {
    template <typename Parent>
    static ExpressionStorageT<UniOpt<T>> run(
        Parent const&             parent,
        UniOpt<T> const*          item,
        UniValueAccessPath const& path) {
        using Result = ExpressionStorageT<UniOpt<T>>;
        typename Result::value_type result;

        if (item->has_value()) {
            result.emplace(lift_expression_value(
                parent, &item->value(), path.add(UniAccessStep::FromDeref())));
        }

        return {
            StaticT<typename Result::value_type>::FromRValue(result),
            path,
        };
    }
};

template <typename... T>
struct ExpressionLift<UniTuple<T...>> {
    template <typename Parent, std::size_t... I>
    static ExpressionStorageT<UniTuple<T...>> run_impl(
        Parent const&             parent,
        UniTuple<T...> const*     item,
        UniValueAccessPath const& path,
        std::index_sequence<I...>) {
        using Result = ExpressionStorageT<UniTuple<T...>>;
        typename Result::value_type result{
            lift_expression_value(
                parent,
                &std::get<I>(*item),
                path.add(UniAccessStep::FromIndex(static_cast<int>(I))))...,
        };

        return {
            StaticT<typename Result::value_type>::FromRValue(result),
            path,
        };
    }

    template <typename Parent>
    static ExpressionStorageT<UniTuple<T...>> run(
        Parent const&             parent,
        UniTuple<T...> const*     item,
        UniValueAccessPath const& path) {
        return run_impl(parent, item, path, std::index_sequence_for<T...>{});
    }
};

template <typename Parent, typename Item>
auto lift_expression_value(
    Parent const&             parent,
    Item const*               item,
    UniValueAccessPath const& path) {
    return ExpressionLift<std::remove_cv_t<Item>>::run(parent, item, path);
}

struct EvalRuntime {
    using Conversion = void const* (*)(void const*);

    VerifyContext const* ctx;

    hstd::UnorderedMap<std::type_index, hstd::UnorderedMap<std::type_index, Conversion>>
        conversions;

    hstd::UnorderedMap<std::type_index, std::string> type_names;

    template <typename T>
    void register_type(std::string const& name) {
        conversions[typeid(T)].insert_or_assign(
            typeid(T), +[](void const* value) -> void const* {
                return static_cast<T const*>(value);
            });

        type_names[typeid(T)] = name;
    }


    template <typename T>
    std::string const& get_type_name_static() const {
        return type_names.at(typeid(T));
    }

    std::string const& get_type_name_dynamic(UniDynamic const& value) const {
        return type_names.at(value.value.type);
    }

    template <typename Derived, typename Base>
    void register_base() {
        static_assert(std::is_base_of_v<Base, Derived>);

        conversions[typeid(Derived)].insert_or_assign(
            typeid(Base), +[](void const* value) -> void const* {
                return static_cast<Base const*>(static_cast<Derived const*>(value));
            });

        if constexpr (std::is_polymorphic_v<Base>) {
            conversions[typeid(Base)].insert_or_assign(
                typeid(Derived), +[](void const* value) -> void const* {
                    return dynamic_cast<Derived const*>(static_cast<Base const*>(value));
                });
        }
    }

    template <typename Target>
    hstd::Opt<UniStatic<Target>> try_as(UniDynamic const& source) const {
        DynamicT const& erased = *source.get();
        Target const*   result = nullptr;

        if (erased.type == typeid(Target)) {
            result = static_cast<Target const*>(erased.data);
        } else {
            auto source_types = conversions.find(erased.type);

            if (source_types != conversions.end()) {
                auto conversion = source_types->second.find(typeid(Target));

                if (conversion != source_types->second.end()) {
                    result = static_cast<Target const*>(conversion->second(erased.data));
                }
            }
        }

        if (result == nullptr) { return std::nullopt; }

        return UniStatic<Target>{
            StaticT<Target>::FromAlias(result, source.owner()),
            source.path,
        };
    }

    template <typename Target, typename Source>
    hstd::Opt<UniStatic<Target>> try_as(UniStatic<Source> const& source) const {
        Target const* result = nullptr;

        if constexpr (std::is_convertible_v<Source const*, Target const*>) {
            result = static_cast<Target const*>(source.get());
        } else if constexpr (std::is_polymorphic_v<Source>) {
            result = dynamic_cast<Target const*>(source.get());
        }

        if (result == nullptr) { return std::nullopt; }

        return UniStatic<Target>{
            StaticT<Target>::FromAlias(result, source.owner()),
            source.path,
        };
    }
};


template <typename Target, typename Source>
    requires std::same_as<Target, Source>
void set_value(UniStatic<Target>& target, UniStatic<Source> const& source) {
    target = source;
}

template <typename Target, typename Source>
    requires std::constructible_from<Target, Source const&>
void set_value(UniStatic<UniOpt<Target>>& target, Source const& source) {
    UniOpt<Target> result{std::in_place, source};

    target = {
        StaticT<UniOpt<Target>>::FromRValue(result),
        target.path,
    };
}


template <typename Target>
UniStatic<Target> get_value_ref(UniStatic<Target>& target) {
    return target;
}

template <typename Target>
Target const& get_value_ref(UniStatic<UniOpt<Target>>& target) {
    return target.get()->value();
}

template <typename Target>
Target const& get_stored_value(UniStatic<Target> const& target) {
    return *target.get();
}

inline bool get_stored_as_bool(UniStatic<bool> const& target) {
    return get_stored_value(target);
}

template <typename Target>
inline bool get_stored_as_bool(UniStatic<UniOpt<Target>> const& target) {
    return get_stored_value(target).has_value();
}

template <typename T>
UniStatic<UniVec<UniDynamic>> eval_walk(EvalRuntime const&, UniStatic<T> const& data) {
    UniVec<UniDynamic> result;

    ReflRecursiveVisitContext ctx;

    reflVisitAll<T, UnidataTag>(
        *data.get(),
        {},
        ctx,
        [&]<typename FieldType>(
            ReflValueAccessPath<UnidataTag>::VisitCtx const& path,
            FieldType const&                                 field) {
            result.push_back(
                UniDynamic{
                    DynamicT::FromValue(field, data.owner()),
                    data.path.add(path.toPath()),
                });
        });

    return UniStatic<UniVec<UniDynamic>>::SubExprNoContext(result, "walk");
}

template <typename T, typename... Args>
UniStatic<bool> eval_holds_alternative(UniStatic<UniVariant<Args...>> const& values) {
    return UniStatic<bool>::SubExprNoContext(
        std::holds_alternative<T>(*values.get()), "holds_alternative");
}

template <typename Res, typename... Args>
Res eval_variant_index(UniStatic<UniVariant<Args...>> const& values) {
    // TODO: variant enums are always generated to match the index -- for now,
    // but in the future this part of the code might need reworking. See
    // [[unidata/direct-variant-data-field-access]] in the test model.
    return values.CallResult(
        static_cast<Res::value_type>(values.get()->index()), "index");
}

template <typename Res>
Res eval_str_size(UniStatic<UniStr> const& value) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(value.get()->size()), "str_size");
}

template <typename Res, typename T>
UniStatic<UniPath> eval_path_of(EvalRuntime const&, UniValue<T> const& value) {
    return UniStatic<UniPath>::SubExprNoContext(value.path, "path");
}

template <typename T>
struct TypeText {};

template <typename Derived, typename... Parameters>
struct TypeTextBase {
    static std::string get_type_text(EvalRuntime const* runtime, std::string_view name) {
        std::string result{name};
        result += '<';

        bool first  = true;
        auto append = [&](std::string const& text) {
            if (!first) { result += ", "; }
            first = false;
            result += text;
        };

        (append(TypeText<Parameters>::get_type_text(runtime)), ...);

        result += '>';
        return result;
    }
};

template <typename E>
struct TypeText<UniVec<E>> : TypeTextBase<TypeText<UniVec<E>>, E> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return TypeTextBase<TypeText<UniVec<E>>, E>::get_type_text(runtime, "list");
    }
};

template <typename E, std::size_t N>
struct TypeText<std::array<E, N>> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return "array<" + TypeText<E>::get_type_text(runtime) + ", " + std::to_string(N)
             + ">";
    }
};

template <typename K, typename V>
struct TypeText<UniMap<K, V>> : TypeTextBase<TypeText<UniMap<K, V>>, K, V> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return TypeTextBase<TypeText<UniMap<K, V>>, K, V>::get_type_text(runtime, "map");
    }
};

template <typename E>
struct TypeText<UniOpt<E>> : TypeTextBase<TypeText<UniOpt<E>>, E> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return TypeTextBase<TypeText<UniOpt<E>>, E>::get_type_text(runtime, "optional");
    }
};

template <typename... Elements>
struct TypeText<UniTuple<Elements...>>
    : TypeTextBase<TypeText<UniTuple<Elements...>>, Elements...> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return TypeTextBase<TypeText<UniTuple<Elements...>>, Elements...>::get_type_text(
            runtime, "tuple");
    }
};

template <typename... Elements>
struct TypeText<UniVariant<Elements...>>
    : TypeTextBase<TypeText<UniVariant<Elements...>>, Elements...> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return TypeTextBase<TypeText<UniVariant<Elements...>>, Elements...>::
            get_type_text(runtime, "variant");
    }
};

template <IsUnidataClass T>
struct TypeText<T> {
    static std::string get_type_text(EvalRuntime const* runtime) {
        return runtime->get_type_name_static<T>();
    }
};


template <typename Res, typename T>
Res eval_type_of(EvalRuntime const& runtime, UniStatic<T> const& value) {
    return Res::SubExprNoContext(
        hstd::Str{TypeText<T>::get_type_text(&runtime)}, "type_of");
}

template <typename Res>
Res eval_type_of(EvalRuntime const& runtime, UniDynamic const& value) {
    return Res::SubExprNoContext(
        hstd::Str{runtime.get_type_name_dynamic(value)}, "type_of");
}

template <typename Res, typename T1, typename T2>
Res eval_eq(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() == *rhs.get(), "==");
}

template <typename Res, typename T1, typename T2>
Res eval_eq(UniStatic<T1> const& lhs, T2 const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() == rhs, "==");
}

template <typename Res, typename T1, typename T2>
Res eval_lt(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() < *rhs.get(), "<");
}

template <typename Res, typename T1, typename T2>
Res eval_le(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() <= *rhs.get(), "<=");
}

template <typename Res, typename T1, typename T2>
Res eval_ne(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(!(*lhs.get() == *rhs.get()), "!=");
}

template <typename Res, typename T1, typename T2>
Res eval_add(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            + static_cast<Res::value_type>(*rhs.get()),
        "+");
}

template <typename Res, typename T1, typename T2>
Res eval_sub(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            - static_cast<Res::value_type>(*rhs.get()),
        "-");
}

template <typename Res, typename T1, typename T2>
Res eval_div(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            / static_cast<Res::value_type>(*rhs.get()),
        "/");
}

template <typename Res, typename T1, typename T2>
Res eval_mul(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            * static_cast<Res::value_type>(*rhs.get()),
        "*");
}

template <typename Res, typename T>
Res eval_list_size(UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(lhs.get()->size()), "list_size");
}

template <typename Res, typename T>
Res eval_map_size(UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(
        static_cast<typename Res::value_type>(lhs.get()->size()), "map_size");
}

template <typename Res>
Res eval_map_empty() {
    typename Res::value_type res{};
    return Res::SubExprNoContext(res, "map_empty");
}

template <typename Res>
Res eval_list_empty() {
    typename Res::value_type res{};
    return Res::SubExprNoContext(res, "list_empty");
}


template <typename Res, typename K, typename V>
Res eval_map_contains(UniStatic<UniMap<K, V>> const& lhs, K const& rhs) {
    return Res::SubExprNoContext(lhs.get()->contains(rhs), "contains");
}

template <typename Res, typename K, typename V>
Res eval_map_get(UniStatic<UniMap<K, V>> const& lhs, K const& rhs) {
    return lhs.get()->at(rhs);
}


template <typename Res, int index, typename... Args>
Res eval_nth_get(UniStatic<UniTuple<Args...>> const& lhs) {
    return lhs.AtIndex(&std::get<index>(*lhs.get()), index);
}

template <typename Res, typename T>
Res eval_opt_has_value(UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(lhs.get()->has_value(), "opt_has_value");
}

template <typename Res, typename T>
Res eval_opt_value(UniStatic<UniOpt<T>> const& lhs) {
    return lift_expression_value(
        lhs, &lhs.get()->value(), lhs.path.add(UniAccessStep::FromDeref()));
}

template <typename Res, typename Target, typename Source>
Res eval_is_derived(EvalRuntime const& runtime, Source const& source) {
    return Res::SubExprNoContext(
        runtime.template try_as<Target>(source).has_value(), "is_derived");
}


template <typename Res, typename T, typename IntType>
Res eval_list_at(UniStatic<UniVec<T>> const& lhs, UniStatic<IntType> const& rhs) {
    return lhs.AtIndex(&lhs.get()->at(*rhs.get()), *rhs.get());
}


template <typename Res>
UniStatic<bool> eval_not(UniStatic<bool> const& lhs) {
    return UniStatic<bool>::SubExprNoContext(!(*lhs.get()), "!");
}

template <typename T>
struct rec_unpack_value {};

template <typename T>
auto get_unpack(T const& value) {
    return rec_unpack_value<T>::get(value);
}

template <typename T>
struct rec_unpack_value<UniStatic<T>> {
    static T get(UniStatic<T> const& value) { return get_stored_value(value); }
};


template <typename T>
struct rec_unpack_value<UniStatic<UniVec<T>>> {
    static auto get(UniStatic<UniVec<T>> const& value) {
        using Element = decltype(get_unpack(std::declval<T const&>()));

        UniVec<Element> result;
        for (auto const& it : get_stored_value(value)) {
            result.push_back(get_unpack(it));
        }
        return result;
    }
};


// formatting expression used in the DSL is a subset of the C++ fmt
// expression, so for this backend it is possible to just pass it through
// as is, and use it as a reference formatting implemenetation that is
// not dependant on my specific internal bugs.
#define eval_str_pattern(arg) FMT_STRING(arg)

template <typename Res, typename... Args>
[[nodiscard]] Res eval_str_format(
    fmt::format_string<decltype(get_unpack(std::declval<Args&>()))...> format,
    Args&&... args) {
    auto unpacked = std::make_tuple(get_unpack(args)...);

    return std::apply(
        [&](auto&... values) {
            return Res::SubExprNoContext(
                UniStr{fmt::vformat(format.get(), fmt::make_format_args(values...))},
                "format");
        },
        unpacked);
}


template <typename Result, typename Value>
Result eval_get_field(UniStatic<Value> const& value, char const* field_name) {
    hstd::Opt<Result> result;

    using Fields = boost::describe::describe_members<
        Value,
        boost::describe::mod_any_access | boost::describe::mod_inherited>;

    boost::mp11::mp_for_each<Fields>([&](auto const& field) {
        using F = std::remove_cvref_t<decltype((*value.get()).*field.pointer)>;
        // FIXME: Not verify efficient, but good enough for the initial POC solution
        if constexpr (std::same_as<ExpressionStorageT<F>, Result>) {
            if (std::strcmp(field.name, field_name) == 0) {
                result = value.Field(&((*value.get()).*field.pointer), field_name);
            }
        }
    });

    if (!result.has_value()) {
        throw std::runtime_error{
            std::string{"Cannot access reflected field: "} + field_name};
    }

    return *result;
}

template <typename Result, typename... Args>
Result eval_get_field(UniStatic<UniVariant<Args...>> const& variant, char const* field) {
    return std::visit(
        [&](auto const& item) -> Result {
            auto wrapped = lift_expression_value(variant, &item, variant.path);
            return eval_get_field<Result>(wrapped, field);
        },
        *variant.get());
}


template <typename T>
hstd::generator<ExpressionStorageT<T>> iterate_list(
    UniStatic<UniVec<T>> const& collection) {
    for (int i = 0; i < collection.get()->size(); ++i) {
        co_yield collection.AtIndex(&collection.get()->at(i), i);
    }
}

template <typename Res, typename Collection, typename Callback>
UniStatic<bool> eval_all(
    UniStatic<Collection> const& collection,
    Callback const&              callback) {
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (!(*cb_res.get())) { return collection.CallResult(false, "all"); }
    }

    return collection.CallResult(true, "all");
}

template <typename Res, typename Collection, typename Callback>
UniStatic<bool> eval_exists(Collection const& collection, Callback const& callback) {
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (*cb_res.get()) { return collection.CallResult(true, "exists"); }
    }

    return collection.CallResult(false, "exists");
}

template <typename Res, typename Collection, typename Callback>
UniStatic<bool> eval_exists_one(Collection const& collection, Callback const& callback) {
    int counter = 0;
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (*cb_res.get()) { ++counter; }
        if (1 < counter) { return collection.CallResult(false, "exists_one"); }
    }

    return collection.CallResult(counter == 1, "exists_one");
}

template <typename ResultType, typename T, typename Callback>
ResultType eval_map(UniStatic<hstd::Vec<T>> const& collection, Callback const& callback) {
    typename ResultType::value_type res;
    for (auto const& it : iterate_list(collection)) { res.push_back(callback(it)); }
    return ResultType::SubExprNoContext(res, "map");
}

template <typename ResultType, typename T, typename Callback>
ResultType eval_filter(
    UniStatic<hstd::Vec<T>> const& collection,
    Callback const&                callback) {
    typename ResultType::value_type res;
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (*cb_res.get()) { res.push_back(it); }
    }

    return ResultType::SubExprNoContext(res, "filter");
}

template <typename Result>
Result eval_str_matches(UniStatic<UniStr> const& value, std::string const& pattern) {
    return Result::SubExprNoContext(
        std::regex_search(*value.get(), std::regex{pattern}), "str_matches");
}

template <typename Result, typename Collection, typename T>
Result eval_list_contains(UniStatic<Collection> const& collection, T const& value) {
    for (auto const& item : iterate_list(collection)) {
        if (item == value) { return Result::SubExprNoContext(true, "list_contains"); }
    }

    return Result::SubExprNoContext(false, "list_contains");
}

template <typename Result, typename First, typename Second>
Result eval_list_concat(First const& first, Second const& second) {
    typename Result::value_type result;
    for (auto const& item : iterate_list(first)) { result.push_back(item); }
    for (auto const& item : iterate_list(second)) { result.push_back(item); }
    return Result::SubExprNoContext(result, "list_concat");
}

template <typename Result, typename Map, typename Key, typename Value>
Result eval_map_insert(Map const& map, Key const& key, Value const& value) {
    // FIXME: This will perform a full copy of the map on each insert -- if this is used
    // with operation that iterates over the whole tree, or used to collect the return
    // into the list (e.g. map+fold+insert), this can easily lead to the O(N^2) copies
    // for the POC/tests this implementation is good enough, but later on all of this
    // should be replaced with the immer types. No operation/expression mutates the values
    typename Result::value_type result{*map.get()};
    result.insert_or_assign(key, value);
    return Result::SubExprNoContext(result, "map_insert");
}

template <typename Result, typename K, typename V>
Result eval_map_keys(UniStatic<UniMap<K, V>> const& map) {
    typename Result::value_type result;
    for (auto const& [key, value] : *map.get()) { result.push_back(key); }
    return Result::SubExprNoContext(result, "map_keys");
}

template <typename Result, typename K, typename V>
Result eval_map_values(UniStatic<UniMap<K, V>> const& map) {
    typename Result::value_type result;
    for (auto const& [key, value] : *map.get()) { result.push_back(value); }
    return Result::SubExprNoContext(result, "map_values");
}


template <typename Result, typename Collection, typename Callback>
Result eval_filter_map(Collection const& collection, Callback const& callback) {
    typename Result::value_type res;
    for (auto const& item : iterate_list(collection)) {
        auto mapped = callback(item);
        if (get_stored_as_bool(mapped)) {
            // unpack optional value
            res.push_back(get_value_ref(mapped));
        }
    }

    return Result::SubExprNoContext(res, "filter_map");
}

template <typename Result, typename Collection, typename Callback>
Result eval_take_while(Collection const& collection, Callback const& callback) {
    typename Result::value_type result;
    for (auto const& item : iterate_list(collection)) {
        if (!get_stored_as_bool(callback(item))) { break; }
        result.push_back(item);
    }

    return Result::SubExprNoContext(result, "take_while");
}

template <typename Result, typename Collection, typename Callback>
Result eval_group_by(Collection const& collection, Callback const& callback) {
    using Map    = typename Result::value_type;
    using Key    = typename Map::key_type;
    using Bucket = typename Map::mapped_type;
    using Items  = typename Bucket::value_type;

    // Build mutable buckets locally; expression values remain immutable.
    UniMap<Key, Items> groups;

    for (auto const& item : iterate_list(collection)) {
        auto key = callback(item);
        groups[key].push_back(item);
    }

    Map result;

    for (auto const& [key, items] : groups) {
        result.emplace(key, Bucket::SubExprNoContext(items, "group"));
    }

    return Result::SubExprNoContext(result, "map");
}

template <typename Result, typename Collection, typename Callback>
Result eval_fold(Collection const& collection, Result initial, Callback const& callback) {
    Result result = std::move(initial);

    for (auto const& item : iterate_list(collection)) { result = callback(result, item); }

    return result;
}


template <typename Result, typename Collection>
Result eval_sum(Collection const& collection) {
    using Value = typename Result::value_type;
    Value result{};

    for (auto const& item : iterate_list(collection)) {
        result += static_cast<Value>(*item.get());
    }

    return Result::SubExprNoContext(result, "sum");
}

template <typename Result, typename Collection>
Result eval_min(UniStatic<Collection> const& collection) {
    auto values = iterate_list(collection);
    auto it     = values.begin();
    auto end    = values.end();
    if (it == end) {
        throw std::invalid_argument{"eval_min requires a nonempty collection"};
    }

    Result result = *it;

    for (++it; it != end; ++it) {
        auto const& candidate = *it;
        if (*candidate.get() < *result.get()) { result = candidate; }
    }

    return result;
}

template <typename Result, typename Collection>
Result eval_max(UniStatic<Collection> const& collection) {
    auto values = iterate_list(collection);
    auto it     = values.begin();
    auto end    = values.end();
    if (it == end) {
        throw std::invalid_argument{"eval_max requires a nonempty collection"};
    }

    Result result = *it;

    for (++it; it != end; ++it) {
        auto const& candidate = *it;
        if (*result.get() < *candidate.get()) { result = candidate; }
    }

    return result;
}

/// Return the half-open slice [start, end).
template <typename Result, typename Collection, typename I1, typename I2>
Result eval_list_slice(
    UniStatic<Collection> const& collection,
    UniStatic<I1>                start,
    UniStatic<I2>                end) {
    auto const first = *start.get();
    auto const last  = *end.get();
    if (std::cmp_less(first, 0) || std::cmp_less(last, first)
        || std::cmp_greater(last, collection.get()->size())) {
        throw std::out_of_range{"Invalid list slice bounds"};
    }

    typename Result::value_type result;
    std::size_t                 index = 0;
    for (auto const& value : iterate_list(collection)) {
        if (std::cmp_equal(index, last)) { break; }
        if (!std::cmp_less(index, first)) { result.push_back(value); }
        ++index;
    }

    return Result::SubExprNoContext(result, "list_slice");
}


}; // namespace hstd::ext::unidata
