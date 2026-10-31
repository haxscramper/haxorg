#pragma once

#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>

namespace hstd::ext::unidata {

template <typename T>
UniStatic<UniVec<UniDynamic>> eval_walk(
    ExprContext const& expr_ctx,
    EvalRuntime const&,
    UniStatic<T> const& data) {
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
Res eval_variant_index(
    ExprContext const&                    expr_ctx,
    UniStatic<UniVariant<Args...>> const& values) {
    // TODO: variant enums are always generated to match the index -- for now,
    // but in the future this part of the code might need reworking. See
    // [[unidata/direct-variant-data-field-access]] in the test model.
    return values.CallResult(
        static_cast<Res::value_type>(values.get()->index()), "index");
}

template <typename Res>
Res eval_str_size(ExprContext const& expr_ctx, UniStatic<UniStr> const& value) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(value.get()->size()), "str_size");
}

template <typename Res, typename T>
UniStatic<UniPath> eval_path_of(
    ExprContext const& expr_ctx,
    EvalRuntime const&,
    UniValue<T> const& value) {
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
Res eval_type_of(
    ExprContext const&  expr_ctx,
    EvalRuntime const&  runtime,
    UniStatic<T> const& value) {
    return Res::SubExprNoContext(
        hstd::Str{TypeText<T>::get_type_text(&runtime)}, "type_of");
}

template <typename Res>
Res eval_type_of(
    ExprContext const& expr_ctx,
    EvalRuntime const& runtime,
    UniDynamic const&  value) {
    return Res::SubExprNoContext(
        hstd::Str{runtime.get_type_name_dynamic(value)}, "type_of");
}

template <typename Res, typename T1, typename T2>
Res eval_eq(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() == *rhs.get(), "==");
}

template <typename Res, typename T1, typename T2>
Res eval_eq(ExprContext const& expr_ctx, UniStatic<T1> const& lhs, T2 const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() == rhs, "==");
}

template <typename Res, typename T1, typename T2>
Res eval_lt(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() < *rhs.get(), "<");
}

template <typename Res, typename T1, typename T2>
Res eval_le(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(*lhs.get() <= *rhs.get(), "<=");
}

template <typename Res, typename T1, typename T2>
Res eval_ne(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return UniStatic<bool>::SubExprNoContext(!(*lhs.get() == *rhs.get()), "!=");
}

template <typename Res, typename T1, typename T2>
Res eval_add(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            + static_cast<Res::value_type>(*rhs.get()),
        "+");
}

template <typename Res, typename T1, typename T2>
Res eval_sub(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            - static_cast<Res::value_type>(*rhs.get()),
        "-");
}

template <typename Res, typename T1, typename T2>
Res eval_div(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            / static_cast<Res::value_type>(*rhs.get()),
        "/");
}

template <typename Res, typename T1, typename T2>
Res eval_mul(
    ExprContext const&   expr_ctx,
    UniStatic<T1> const& lhs,
    UniStatic<T2> const& rhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(*lhs.get())
            * static_cast<Res::value_type>(*rhs.get()),
        "*");
}

template <typename Res, typename T>
Res eval_list_size(ExprContext const& expr_ctx, UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(
        static_cast<Res::value_type>(lhs.get()->size()), "list_size");
}

template <typename Res, typename T>
Res eval_map_size(ExprContext const& expr_ctx, UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(
        static_cast<typename Res::value_type>(lhs.get()->size()), "map_size");
}

template <typename Res>
Res eval_map_empty(ExprContext const& expr_ctx) {
    typename Res::value_type res{};
    return Res::SubExprNoContext(res, "map_empty");
}

template <typename Res>
Res eval_list_empty(ExprContext const& expr_ctx) {
    typename Res::value_type res{};
    return Res::SubExprNoContext(res, "list_empty");
}


template <typename Res, typename K, typename V>
Res eval_map_contains(
    ExprContext const&             expr_ctx,
    UniStatic<UniMap<K, V>> const& lhs,
    K const&                       rhs) {
    return Res::SubExprNoContext(lhs.get()->contains(rhs), "contains");
}

template <typename Res, typename K, typename V>
Res eval_map_get(
    ExprContext const&             expr_ctx,
    UniStatic<UniMap<K, V>> const& lhs,
    K const&                       rhs) {
    return lhs.get()->at(rhs);
}


template <typename Res, int index, typename... Args>
Res eval_nth_get(ExprContext const& expr_ctx, UniStatic<UniTuple<Args...>> const& lhs) {
    return lhs.AtIndex(&std::get<index>(*lhs.get()), index);
}

template <typename Res, typename T>
Res eval_opt_has_value(ExprContext const& expr_ctx, UniStatic<T> const& lhs) {
    return Res::SubExprNoContext(lhs.get()->has_value(), "opt_has_value");
}

template <typename Res, typename T>
Res eval_opt_value(ExprContext const& expr_ctx, UniStatic<UniOpt<T>> const& lhs) {
    return lift_expression_value(
        lhs, &lhs.get()->value(), lhs.path.add(UniAccessStep::FromDeref()));
}

template <typename Res, typename Target, typename Source>
Res eval_is_derived(
    ExprContext const& expr_ctx,
    EvalRuntime const& runtime,
    Source const&      source) {
    return Res::SubExprNoContext(
        runtime.template try_as<Target>(source).has_value(), "is_derived");
}


template <typename Res, typename T, typename IntType>
Res eval_list_at(
    ExprContext const&          expr_ctx,
    UniStatic<UniVec<T>> const& lhs,
    UniStatic<IntType> const&   rhs) {
    return lhs.AtIndex(&lhs.get()->at(*rhs.get()), *rhs.get());
}


template <typename Res>
UniStatic<bool> eval_not(ExprContext const& expr_ctx, UniStatic<bool> const& lhs) {
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
    ExprContext const&                                                 expr_ctx,
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
Result eval_get_field(
    ExprContext const&      expr_ctx,
    UniStatic<Value> const& value,
    char const*             field_name) {
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
Result eval_get_field(
    ExprContext const&                    expr_ctx,
    UniStatic<UniVariant<Args...>> const& variant,
    char const*                           field) {
    return std::visit(
        [&](auto const& item) -> Result {
            auto wrapped = lift_expression_value(variant, &item, variant.path);
            return eval_get_field<Result>(expr_ctx, wrapped, field);
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
    ExprContext const&           expr_ctx,
    UniStatic<Collection> const& collection,
    Callback const&              callback) {
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (!(*cb_res.get())) { return collection.CallResult(false, "all"); }
    }

    return collection.CallResult(true, "all");
}

template <typename Res, typename Collection, typename Callback>
UniStatic<bool> eval_exists(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Callback const&    callback) {
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (*cb_res.get()) { return collection.CallResult(true, "exists"); }
    }

    return collection.CallResult(false, "exists");
}

template <typename Res, typename Collection, typename Callback>
UniStatic<bool> eval_exists_one(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Callback const&    callback) {
    int counter = 0;
    for (auto const& it : iterate_list(collection)) {
        auto cb_res = callback(it);
        if (*cb_res.get()) { ++counter; }
        if (1 < counter) { return collection.CallResult(false, "exists_one"); }
    }

    return collection.CallResult(counter == 1, "exists_one");
}

template <typename ResultType, typename T, typename Callback>
ResultType eval_map(
    ExprContext const&             expr_ctx,
    UniStatic<hstd::Vec<T>> const& collection,
    Callback const&                callback) {
    typename ResultType::value_type res;
    for (auto const& it : iterate_list(collection)) { res.push_back(callback(it)); }
    return ResultType::SubExprNoContext(res, "map");
}

template <typename ResultType, typename T, typename Callback>
ResultType eval_filter(
    ExprContext const&             expr_ctx,
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
Result eval_str_matches(
    ExprContext const&       expr_ctx,
    UniStatic<UniStr> const& value,
    std::string const&       pattern) {
    return Result::SubExprNoContext(
        std::regex_search(*value.get(), std::regex{pattern}), "str_matches");
}

template <typename Result, typename Collection, typename T>
Result eval_list_contains(
    ExprContext const&           expr_ctx,
    UniStatic<Collection> const& collection,
    T const&                     value) {
    for (auto const& item : iterate_list(collection)) {
        if (item == value) { return Result::SubExprNoContext(true, "list_contains"); }
    }

    return Result::SubExprNoContext(false, "list_contains");
}

template <typename Result, typename First, typename Second>
Result eval_list_concat(
    ExprContext const& expr_ctx,
    First const&       first,
    Second const&      second) {
    typename Result::value_type result;
    for (auto const& item : iterate_list(first)) { result.push_back(item); }
    for (auto const& item : iterate_list(second)) { result.push_back(item); }
    return Result::SubExprNoContext(result, "list_concat");
}

template <typename Result, typename Map, typename Key, typename Value>
Result eval_map_insert(
    ExprContext const& expr_ctx,
    Map const&         map,
    Key const&         key,
    Value const&       value) {
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
Result eval_map_keys(ExprContext const& expr_ctx, UniStatic<UniMap<K, V>> const& map) {
    typename Result::value_type result;
    for (auto const& [key, value] : *map.get()) { result.push_back(key); }
    return Result::SubExprNoContext(result, "map_keys");
}

template <typename Result, typename K, typename V>
Result eval_map_values(ExprContext const& expr_ctx, UniStatic<UniMap<K, V>> const& map) {
    typename Result::value_type result;
    for (auto const& [key, value] : *map.get()) { result.push_back(value); }
    return Result::SubExprNoContext(result, "map_values");
}


template <typename Result, typename Collection, typename Callback>
Result eval_filter_map(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Callback const&    callback) {
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
Result eval_take_while(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Callback const&    callback) {
    typename Result::value_type result;
    for (auto const& item : iterate_list(collection)) {
        if (!get_stored_as_bool(callback(item))) { break; }
        result.push_back(item);
    }

    return Result::SubExprNoContext(result, "take_while");
}

template <typename Result, typename Collection, typename Callback>
Result eval_group_by(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Callback const&    callback) {
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
Result eval_fold(
    ExprContext const& expr_ctx,
    Collection const&  collection,
    Result             initial,
    Callback const&    callback) {
    Result result = std::move(initial);

    for (auto const& item : iterate_list(collection)) { result = callback(result, item); }

    return result;
}


template <typename Result, typename Collection>
Result eval_sum(ExprContext const& expr_ctx, Collection const& collection) {
    using Value = typename Result::value_type;
    Value result{};

    for (auto const& item : iterate_list(collection)) {
        result += static_cast<Value>(*item.get());
    }

    return Result::SubExprNoContext(result, "sum");
}

template <typename Result, typename Collection>
Result eval_min(ExprContext const& expr_ctx, UniStatic<Collection> const& collection) {
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
Result eval_max(ExprContext const& expr_ctx, UniStatic<Collection> const& collection) {
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
    ExprContext const&           expr_ctx,
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

} // namespace hstd::ext::unidata
