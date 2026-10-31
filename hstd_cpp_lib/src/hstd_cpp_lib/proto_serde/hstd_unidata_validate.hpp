#pragma once

#include <cstring>
#include <functional>
#include <hstd_cpp_lib/logger/TraceBase.hpp>
#include <hstd_cpp_lib/stdlib/Func.hpp>
#include <hstd_cpp_lib/stdlib/Str.hpp>
#include <hstd_cpp_lib/stdlib/algorithms/reflection/reflection_visitor.hpp>
#include <hstd_cpp_lib/stdlib/containers/Map.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Pair.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/PairFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>
#include <hstd_cpp_lib/system/exceptions.hpp>
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

struct VerifyContext : public OperationsTracer {
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
VerifyResultCollection verify_all(
    T const&                      data,
    hstd::Opt<std::string> const& verify_debug_path = std::nullopt) {
    VerifyResultCollection    result;
    ReflRecursiveVisitContext ctx;
    VerifyContext             verfiy_ctx;

    if (verify_debug_path) { verfiy_ctx.setTraceFileStr(verify_debug_path.value()); }

    reflVisitAll<T, UnidataTag>(
        data,
        {},
        ctx,
        [&]<typename FieldType>(
            ReflValueAccessPath<UnidataTag>::VisitCtx const& path,
            FieldType const&                                 field) {
            UniValueAccessPath active_path = path.toPath();

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

struct ExprContext {
    VerifyContext const* ctx;
    char const*          file_basename;
    int                  file_line;
};

inline ExprContext get_context(
    VerifyContext const* ctx,
    char const*          file_basename,
    int                  file_line) {
    return ExprContext{
        .ctx           = ctx,
        .file_basename = file_basename,
        .file_line     = file_line,
    };
}


}; // namespace hstd::ext::unidata
