#pragma once

#include "hstd_cpp_lib/stdlib/formatting/Formatter.hpp"
#include <hstd_cpp_lib/logger/TraceBase.hpp>
#include <hstd_cpp_lib/proto_serde/hstd_unidata_validate.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/MapFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/OptFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VariantFormatter.hpp>
#include <hstd_cpp_lib/stdlib/formatting/specializations/VecFormatter.hpp>
#include <hstd_cpp_lib/system/macros.hpp>

namespace hstd::ext::unidata {

DECL_DESCRIBED_ENUM_STANDALONE(
    OpId,
    THIS,
    VAR,
    CONST_INT,
    CONST_FLOAT,
    CONST_STR,
    CONST_BOOL,
    GET_FIELD,
    EQ,
    NE,
    LT,
    LE,
    ADD,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    NOT,
    COND,
    LET,
    ALL,
    EXISTS,
    EXISTS_ONE,
    MAP,
    FILTER,
    FILTER_MAP,
    TAKE_WHILE,
    GROUP_BY,
    FOLD,
    WALK,
    SUM,
    MIN,
    MAX,
    STR_SIZE,
    STR_MATCHES,
    STR_FORMAT,
    LIST_SIZE,
    LIST_CONTAINS,
    LIST_AT,
    LIST_SLICE,
    LIST_CONCAT,
    LIST_EMPTY,
    MAP_SIZE,
    MAP_CONTAINS,
    MAP_GET,
    MAP_INSERT,
    MAP_KEYS,
    MAP_VALUES,
    MAP_EMPTY,
    OPT_HAS_VALUE,
    OPT_VALUE,
    CASE_IS,
    CASE_WHICH,
    ENUM_IS,
    NTH_GET,
    IS_DERIVED,
    TYPE_COND,
    TYPE_CASE,
    PATH_OF,
    TYPE_OF,
    TYPE_TEXT,
    //
);

template <OpId Kind>
struct OpImpl {};

template <typename T>
using S = UniStatic<T>;

#define UNIDATA_SCOPE(__ctx, __file, __line, __expr_kind)                                \
    OP_TRACER_MESSAGE_SCOPE(__ctx, "{} {}:{}", __file, __line, __expr_kind);

template <OpId Kind, typename Res, typename Eval, typename... Args>
Res eval_op_traced(ExprContext const& expr_ctx, Eval&& eval, Args&&... args) {
    OP_TRACER_MESSAGE_SCOPE(
        expr_ctx.ctx,
        "Eval {} at {}:{} via {}:{}",
        Kind,
        expr_ctx.file_basename,
        expr_ctx.file_line,
        expr_ctx.call_function,
        expr_ctx.call_line);

    {
        int  index     = 0;
        auto trace_arg = [&](auto&& arg) {
            OP_TRACER_MESSAGE(
                expr_ctx.ctx,
                "[{}] @ {} = {}",
                index++,
                get_path(arg),
                hstd::fmt1_maybe(get_unpack(arg)));
        };
        (trace_arg(args), ...);
    }

    try {
        auto result = std::forward<Eval>(eval)();

        OP_TRACER_MESSAGE(expr_ctx.ctx, "-> {}", get_unpack(result));

        return result;
    } catch (std::exception const& err) {
        hstd::Str buf;
        int       index     = 0;
        auto      trace_arg = [&](auto&& arg) {
            buf.append(
                hstd::fmt(
                    "\n[{}] @ {} = {}",
                    index++,
                    get_path(arg),
                    hstd::fmt1_maybe(get_unpack(arg))));
        };
        (trace_arg(args), ...);


        throw fatal_expression_error::init(
            hstd::fmt(
                "Evaluation of operation {0} at {1}:{2} (codegen location {3}:{4}) "
                "failed with internal error {5} "
                "on provided arguments. This is a fatal error, validation was "
                "terminated, no model diagnostics provided. This is an issue with the "
                "structure of the validation checks; update the validation expression to "
                "perform guard check against malformed data in the `cond` validation. "
                "Args:{6}",
                /*1=*/Kind,
                /*2=*/expr_ctx.file_basename,
                /*3=*/expr_ctx.file_line,
                /*4=*/expr_ctx.call_function,
                /*5=*/expr_ctx.call_line,
                /*6=*/err.what(),
                /*7=*/buf //
                ));
    }
}

template <OpId Kind, typename Res, typename... TemplateArgs, typename... Args>
Res eval_op(ExprContext const& expr_ctx, Args&&... args) {
    return eval_op_traced<Kind, Res>(
        expr_ctx,
        [&]() {
            return OpImpl<Kind>::template eval<Res, TemplateArgs...>(
                std::forward<Args>(args)...);
        },
        args...);
}

template <OpId Kind, typename Res, int Index, typename... Args>
Res eval_op(ExprContext const& expr_ctx, Args&&... args) {
    return eval_op_traced<Kind, Res>(
        expr_ctx,
        [&]() {
            return OpImpl<Kind>::template eval<Res, Index>(std::forward<Args>(args)...);
        },
        args...);
}


template <>
struct OpImpl<OpId::WALK> {
    template <typename Res, typename T>
    static UniStatic<UniVec<UniDynamic>> eval(
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
                // result.push_back(
                //     UniDynamic{
                //         DynamicT::FromValue(field, data.owner()),
                //         data.path.add(path.toPath()),
                //     });
            });

        return UniStatic<UniVec<UniDynamic>>::SubExprNoContext(result, "walk");
    }
};

template <>
struct OpImpl<OpId::CASE_IS> {
    template <typename Res, typename T, typename... Args>
    static UniStatic<bool> eval(UniStatic<UniVariant<Args...>> const& values) {
        return UniStatic<bool>::SubExprNoContext(
            std::holds_alternative<T>(*values.get()), "holds_alternative");
    }
};

template <>
struct OpImpl<OpId::CASE_WHICH> {
    template <typename Res, typename... Args>
    static Res eval(UniStatic<UniVariant<Args...>> const& values) {
        // TODO: variant enums are always generated to match the index -- for now,
        // but in the future this part of the code might need reworking. See
        // [[unidata/direct-variant-data-field-access]] in the test model.
        return values.CallResult(
            static_cast<typename Res::value_type>(values.get()->index()), "index");
    }
};

template <>
struct OpImpl<OpId::STR_SIZE> {
    template <typename Res>
    static Res eval(UniStatic<UniStr> const& value) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(value.get()->size()), "str_size");
    }
};

template <>
struct OpImpl<OpId::PATH_OF> {
    template <typename Res, typename T>
    static UniStatic<UniPath> eval(EvalRuntime const&, UniValue<T> const& value) {
        return UniStatic<UniPath>::SubExprNoContext(value.path, "path");
    }
};


template <>
struct OpImpl<OpId::TYPE_OF> {
    template <typename Res, typename T>
    static Res eval(EvalRuntime const& runtime, UniStatic<T> const& value) {
        // return Res::SubExprNoContext(
        //     TypeText<T>::get_type_text(&runtime, *value.get()), "type_of");
    }

    template <typename Res>
    static Res eval(EvalRuntime const& runtime, UniDynamic const& value) {
        return Res::SubExprNoContext(value.value.type, "type_of");
    }
};

template <>
struct OpImpl<OpId::TYPE_TEXT> {
    template <typename Res>
    static Res eval(UniStatic<UniType> const& value) {
        return Res::SubExprNoContext(get_stored_value(value).format(), "type_text");
    }
};


template <>
struct OpImpl<OpId::EQ> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return UniStatic<bool>::SubExprNoContext(*lhs.get() == *rhs.get(), "==");
    }

    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, T2 const& rhs) {
        return UniStatic<bool>::SubExprNoContext(*lhs.get() == rhs, "==");
    }
};

template <>
struct OpImpl<OpId::LT> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return UniStatic<bool>::SubExprNoContext(*lhs.get() < *rhs.get(), "<");
    }
};

template <>
struct OpImpl<OpId::LE> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return UniStatic<bool>::SubExprNoContext(*lhs.get() <= *rhs.get(), "<=");
    }
};

template <>
struct OpImpl<OpId::NE> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return UniStatic<bool>::SubExprNoContext(!(*lhs.get() == *rhs.get()), "!=");
    }
};

template <>
struct OpImpl<OpId::COND> {
    template <typename Res, typename CondFunc, typename ThenFunc, typename ElseFunc>
    static Res eval(
        CondFunc const& cond_func,
        ThenFunc const& then_func,
        ElseFunc const& else_func) {
        if (get_stored_as_bool(cond_func())) {
            return then_func();
        } else {
            return else_func();
        }
    }
};

template <>
struct OpImpl<OpId::AND> {
    template <typename Res, typename... ArgFuncs>
    static Res eval(ArgFuncs&&... args) {
        return Res::SubExprNoContext((get_stored_as_bool(args()) && ...), "and");
    }
};

template <>
struct OpImpl<OpId::OR> {
    template <typename Res, typename... ArgFuncs>
    static Res eval(ArgFuncs&&... args) {
        return Res::SubExprNoContext((get_stored_as_bool(args()) || ...), "or");
    }
};


template <>
struct OpImpl<OpId::ADD> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(*lhs.get())
                + static_cast<typename Res::value_type>(*rhs.get()),
            "+");
    }
};

template <>
struct OpImpl<OpId::SUB> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(*lhs.get())
                - static_cast<typename Res::value_type>(*rhs.get()),
            "-");
    }
};

template <>
struct OpImpl<OpId::DIV> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(*lhs.get())
                / static_cast<typename Res::value_type>(*rhs.get()),
            "/");
    }
};

template <>
struct OpImpl<OpId::MUL> {
    template <typename Res, typename T1, typename T2>
    static Res eval(UniStatic<T1> const& lhs, UniStatic<T2> const& rhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(*lhs.get())
                * static_cast<typename Res::value_type>(*rhs.get()),
            "*");
    }
};

template <>
struct OpImpl<OpId::LIST_SIZE> {
    template <typename Res, typename T>
    static Res eval(UniStatic<T> const& lhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(lhs.get()->size()), "list_size");
    }
};

template <>
struct OpImpl<OpId::MAP_SIZE> {
    template <typename Res, typename T>
    static Res eval(UniStatic<T> const& lhs) {
        return Res::SubExprNoContext(
            static_cast<typename Res::value_type>(lhs.get()->size()), "map_size");
    }
};

template <>
struct OpImpl<OpId::MAP_EMPTY> {
    template <typename Res>
    static Res eval() {
        typename Res::value_type res{};
        return Res::SubExprNoContext(res, "map_empty");
    }
};

template <>
struct OpImpl<OpId::LIST_EMPTY> {
    template <typename Res>
    static Res eval() {
        typename Res::value_type res{};
        return Res::SubExprNoContext(res, "list_empty");
    }
};

template <>
struct OpImpl<OpId::MAP_CONTAINS> {
    template <typename Res, typename K, typename V>
    static Res eval(UniStatic<UniMap<K, V>> const& lhs, K const& rhs) {
        return Res::SubExprNoContext(lhs.get()->contains(rhs), "contains");
    }
};

template <>
struct OpImpl<OpId::MAP_GET> {
    template <typename Res, typename K, typename V>
    static Res eval(UniStatic<UniMap<K, V>> const& lhs, K const& rhs) {
        return lhs.get()->at(rhs);
    }
};

template <>
struct OpImpl<OpId::NTH_GET> {
    template <typename Res, int index, typename... Args>
    static Res eval(UniStatic<UniTuple<Args...>> const& lhs) {
        return lhs.AtIndex(&std::get<index>(*lhs.get()), index);
    }
};

template <>
struct OpImpl<OpId::OPT_HAS_VALUE> {
    template <typename Res, typename T>
    static Res eval(UniStatic<T> const& lhs) {
        return Res::SubExprNoContext(lhs.get()->has_value(), "opt_has_value");
    }
};

template <>
struct OpImpl<OpId::OPT_VALUE> {
    template <typename Res, typename T>
    static Res eval(UniStatic<UniOpt<T>> const& lhs) {
        return lift_expression_value(
            lhs, &lhs.get()->value(), lhs.path.add(UniAccessStep::FromDeref()));
    }
};

template <>
struct OpImpl<OpId::IS_DERIVED> {
    template <typename Res, typename Target, typename Source>
    static Res eval(EvalRuntime const& runtime, Source const& source) {
        return Res::SubExprNoContext(
            runtime.template try_as<Target>(source).has_value(), "is_derived");
    }
};

template <>
struct OpImpl<OpId::LIST_AT> {
    template <typename Res, typename T, typename IntType>
    static Res eval(UniStatic<UniVec<T>> const& lhs, UniStatic<IntType> const& rhs) {
        return lhs.AtIndex(&lhs.get()->at(*rhs.get()), *rhs.get());
    }
};

template <>
struct OpImpl<OpId::NOT> {
    template <typename Res>
    static UniStatic<bool> eval(UniStatic<bool> const& lhs) {
        return UniStatic<bool>::SubExprNoContext(!(*lhs.get()), "!");
    }
};

// Formatting expressions used in the DSL are a subset of C++ fmt expressions,
// so this backend can pass them through as a reference implementation.
#define eval_str_pattern(arg) ([]() constexpr { return fmt::string_view{arg}; })

template <>
struct OpImpl<OpId::STR_FORMAT> {
    template <typename Res, typename Pattern, typename... Args>
    [[nodiscard]] static Res eval(Pattern, Args&&... args) {
        constexpr auto
            format = fmt::format_string<decltype(get_unpack(std::declval<Args&>()))...>{
                Pattern{}()};

        auto unpacked = std::make_tuple(get_unpack(args)...);

        return std::apply(
            [&](auto&... values) {
                return Res::SubExprNoContext(
                    UniStr{fmt::vformat(format.get(), fmt::make_format_args(values...))},
                    "format");
            },
            unpacked);
    }
};

template <>
struct OpImpl<OpId::GET_FIELD> {
    template <typename Result, typename Value>
    static Result eval(UniStatic<Value> const& value, char const* field_name) {
        hstd::Opt<Result> result;

        using Fields = boost::describe::describe_members<
            Value,
            boost::describe::mod_any_access | boost::describe::mod_inherited>;

        boost::mp11::mp_for_each<Fields>([&](auto const& field) {
            using F = std::remove_cvref_t<decltype((*value.get()).*field.pointer)>;
            // FIXME: Not very efficient, but good enough for the initial POC.
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
    static Result eval(UniStatic<UniVariant<Args...>> const& variant, char const* field) {
        return std::visit(
            [&](auto const& item) -> Result {
                auto wrapped = lift_expression_value(variant, &item, variant.path);
                return OpImpl<OpId::GET_FIELD>::template eval<Result>(wrapped, field);
            },
            *variant.get());
    }
};

template <typename T>
hstd::generator<ExpressionStorageT<T>> iterate_list(
    UniStatic<UniVec<T>> const& collection) {
    for (int i = 0; i < collection.get()->size(); ++i) {
        co_yield collection.AtIndex(&collection.get()->at(i), i);
    }
}

template <>
struct OpImpl<OpId::ALL> {
    template <typename Res, typename Collection, typename Callback>
    static UniStatic<bool> eval(
        UniStatic<Collection> const& collection,
        Callback const&              callback) {
        for (auto const& it : iterate_list(collection)) {
            auto cb_res = callback(it);
            if (!(*cb_res.get())) { return collection.CallResult(false, "all"); }
        }

        return collection.CallResult(true, "all");
    }
};

template <>
struct OpImpl<OpId::EXISTS> {
    template <typename Res, typename Collection, typename Callback>
    static UniStatic<bool> eval(Collection const& collection, Callback const& callback) {
        for (auto const& it : iterate_list(collection)) {
            auto cb_res = callback(it);
            if (*cb_res.get()) { return collection.CallResult(true, "exists"); }
        }

        return collection.CallResult(false, "exists");
    }
};

template <>
struct OpImpl<OpId::EXISTS_ONE> {
    template <typename Res, typename Collection, typename Callback>
    static UniStatic<bool> eval(Collection const& collection, Callback const& callback) {
        int counter = 0;
        for (auto const& it : iterate_list(collection)) {
            auto cb_res = callback(it);
            if (*cb_res.get()) { ++counter; }
            if (1 < counter) { return collection.CallResult(false, "exists_one"); }
        }

        return collection.CallResult(counter == 1, "exists_one");
    }
};

template <>
struct OpImpl<OpId::MAP> {
    template <typename ResultType, typename T, typename Callback>
    static ResultType eval(
        UniStatic<hstd::Vec<T>> const& collection,
        Callback const&                callback) {
        typename ResultType::value_type res;
        for (auto const& it : iterate_list(collection)) { res.push_back(callback(it)); }
        return ResultType::SubExprNoContext(res, "map");
    }
};

template <>
struct OpImpl<OpId::FILTER> {
    template <typename ResultType, typename T, typename Callback>
    static ResultType eval(
        UniStatic<hstd::Vec<T>> const& collection,
        Callback const&                callback) {
        typename ResultType::value_type res;
        for (auto const& it : iterate_list(collection)) {
            auto cb_res = callback(it);
            if (*cb_res.get()) { res.push_back(it); }
        }

        return ResultType::SubExprNoContext(res, "filter");
    }
};

template <>
struct OpImpl<OpId::STR_MATCHES> {
    template <typename Result>
    static Result eval(UniStatic<UniStr> const& value, std::string const& pattern) {
        return Result::SubExprNoContext(
            std::regex_search(*value.get(), std::regex{pattern}), "str_matches");
    }
};

template <>
struct OpImpl<OpId::LIST_CONTAINS> {
    template <typename Result, typename Collection, typename T>
    static Result eval(UniStatic<Collection> const& collection, T const& value) {
        for (auto const& item : iterate_list(collection)) {
            if (item == value) { return Result::SubExprNoContext(true, "list_contains"); }
        }

        return Result::SubExprNoContext(false, "list_contains");
    }
};

template <>
struct OpImpl<OpId::LIST_CONCAT> {
    template <typename Result, typename First, typename Second>
    static Result eval(First const& first, Second const& second) {
        typename Result::value_type result;
        for (auto const& item : iterate_list(first)) { result.push_back(item); }
        for (auto const& item : iterate_list(second)) { result.push_back(item); }
        return Result::SubExprNoContext(result, "list_concat");
    }
};

template <>
struct OpImpl<OpId::MAP_INSERT> {
    template <typename Result, typename Map, typename Key, typename Value>
    static Result eval(Map const& map, Key const& key, Value const& value) {
        // FIXME: This performs a full copy of the map on each insert. Using it
        // while collecting results can lead to O(N^2) copies. This is sufficient
        // for the POC/tests; persistent immer types should replace it later.
        // No operation/expression mutates the input values.
        typename Result::value_type result{*map.get()};
        result.insert_or_assign(key, value);
        return Result::SubExprNoContext(result, "map_insert");
    }
};

template <>
struct OpImpl<OpId::MAP_KEYS> {
    template <typename Result, typename K, typename V>
    static Result eval(UniStatic<UniMap<K, V>> const& map) {
        typename Result::value_type result;
        for (auto const& [key, value] : *map.get()) { result.push_back(key); }
        return Result::SubExprNoContext(result, "map_keys");
    }
};

template <>
struct OpImpl<OpId::MAP_VALUES> {
    template <typename Result, typename K, typename V>
    static Result eval(UniStatic<UniMap<K, V>> const& map) {
        typename Result::value_type result;
        for (auto const& [key, value] : *map.get()) { result.push_back(value); }
        return Result::SubExprNoContext(result, "map_values");
    }
};

template <>
struct OpImpl<OpId::FILTER_MAP> {
    template <typename Result, typename Collection, typename Callback>
    static Result eval(Collection const& collection, Callback const& callback) {
        typename Result::value_type res;
        for (auto const& item : iterate_list(collection)) {
            auto mapped = callback(item);
            if (get_stored_as_bool(mapped)) {
                // Unpack optional value.
                res.push_back(get_value_ref(mapped));
            }
        }

        return Result::SubExprNoContext(res, "filter_map");
    }
};

template <>
struct OpImpl<OpId::TAKE_WHILE> {
    template <typename Result, typename Collection, typename Callback>
    static Result eval(Collection const& collection, Callback const& callback) {
        typename Result::value_type result;
        for (auto const& item : iterate_list(collection)) {
            if (!get_stored_as_bool(callback(item))) { break; }
            result.push_back(item);
        }

        return Result::SubExprNoContext(result, "take_while");
    }
};

template <>
struct OpImpl<OpId::GROUP_BY> {
    template <typename Result, typename Collection, typename Callback>
    static Result eval(Collection const& collection, Callback const& callback) {
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
};

template <>
struct OpImpl<OpId::FOLD> {
    template <typename Result, typename Collection, typename Callback>
    static Result eval(
        Collection const& collection,
        Result            initial,
        Callback const&   callback) {
        Result result = std::move(initial);

        for (auto const& item : iterate_list(collection)) {
            result = callback(result, item);
        }

        return result;
    }
};

template <>
struct OpImpl<OpId::SUM> {
    template <typename Result, typename Collection>
    static Result eval(Collection const& collection) {
        using Value = typename Result::value_type;
        Value result{};

        for (auto const& item : iterate_list(collection)) {
            result += static_cast<Value>(*item.get());
        }

        return Result::SubExprNoContext(result, "sum");
    }
};

template <>
struct OpImpl<OpId::MIN> {
    template <typename Result, typename Collection>
    static Result eval(UniStatic<Collection> const& collection) {
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
};

template <>
struct OpImpl<OpId::MAX> {
    template <typename Result, typename Collection>
    static Result eval(UniStatic<Collection> const& collection) {
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
};

template <>
struct OpImpl<OpId::LIST_SLICE> {
    /// Return the half-open slice [start, end), using Python slice bounds.
    template <typename Result, typename Collection, typename I1, typename I2>
    static Result eval(
        UniStatic<Collection> const& collection,
        UniStatic<I1>                start,
        UniStatic<I2>                end) {
        auto const size = collection.get()->size();

        auto normalize = [size](auto bound) -> std::size_t {
            if (std::cmp_less(bound, 0)) {
                // Avoid overflowing when bound is the minimum signed value.
                auto const offset = -(bound + 1);
                if (std::cmp_greater_equal(offset, size)) { return 0; }
                return size - static_cast<std::size_t>(offset) - 1;
            }

            if (std::cmp_greater_equal(bound, size)) { return size; }
            return static_cast<std::size_t>(bound);
        };

        auto const first = normalize(*start.get());
        auto const last  = normalize(*end.get());

        typename Result::value_type result;
        if (first < last) {
            std::size_t index = 0;
            for (auto const& value : iterate_list(collection)) {
                if (index == last) { break; }
                if (first <= index) { result.push_back(value); }
                ++index;
            }
        }

        return Result::SubExprNoContext(result, "list_slice");
    }
};


} // namespace hstd::ext::unidata
