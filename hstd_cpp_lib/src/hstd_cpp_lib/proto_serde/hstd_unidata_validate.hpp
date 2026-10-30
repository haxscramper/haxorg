#pragma once

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
#include <hstd_cpp_lib/system/macros.hpp>
#include <hstd_cpp_lib/system/reflection.hpp>
#include <optional>
#include <regex>
#include <string>
#include <type_traits>
#include <typeinfo>
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

struct VerifyContext {};

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

struct UnidataTag {
    // TODO: string for now, later might use faster solution from the immutable AST
    using field_name_type = std::string;
};

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


namespace hstd::ext::unidata {

template <typename T>
VerifyResultCollection verify_all(T const& data) {
    VerifyResultCollection result;
    VerifyContext          verfiy_ctx;

    ReflRecursiveVisitContext ctx;
    reflVisitAll<T, UnidataTag>(
        data,
        {},
        ctx,
        [&]<typename FieldType>(
            ReflValueAccessPath<UnidataTag>::VisitCtx const& path,
            FieldType const&                                 field) {
            result.results.append(verify_one_with_bases(verfiy_ctx, field));
        });

    return result;
}

struct EvalDynamic {
    void const*    data;
    std::type_info type;

    template <typename T>
    static EvalDynamic FromValue(T const& value) {
        return EvalDynamic{.data = &value, .type = typeid(std::remove_cvref_t<T>)};
    }

    DESC_FIELDS(EvalDynamic, (data, type));
};

struct EvalRuntime {
    VerifyContext const* ctx;

    template <typename Base, typename Derived>
    Base const* try_as(Derived const& value) {
        return dynamic_cast<Base const*>(&value);
    }
};

template <typename T>
hstd::Vec<EvalDynamic> eval_walk(EvalRuntime const& runtime, T const& data) {
    hstd::Vec<EvalDynamic> result;

    ReflRecursiveVisitContext ctx;
    reflVisitAll<T, UnidataTag>(
        data,
        {},
        ctx,
        [&]<typename FieldType>(
            ReflValueAccessPath<UnidataTag>::VisitCtx const& path,
            FieldType const& field) { result.push_back(EvalDynamic::FromValue(field)); });

    return result;
}

inline int eval_str_size(std::string const* str) { return static_cast<int>(str->size()); }

template <typename T1, typename T2>
bool eval_equal(T1 const& lhs, T2 const& rhs) {
    return lhs == rhs;
}

struct str_format_pattern {};

consteval str_format_pattern eval_str_pattern(char const* pattern) {
    return str_format_pattern{};
}

template <typename... Args>
bool eval_str_format(str_format_pattern const& pattern, Args&&... args) {}

template <typename T, typename Value>
T const& eval_get_field(Value const& value, char const* field_name) {
    T const* result = nullptr;
    // FIXME: Not verify efficient, but good enough for the initial POC solution
    hstd::for_each_field_no_base<T>([&](auto const& field) {
        if (std::strcmp(field.name, field_name) == 0) {
            result = &(value.*field.pointer);
        }
    });

    LOGIC_ASSERTION_CHECK(
        result != nullptr, "Runtime logic error, could not find target field");

    return *result;
}

template <typename T, typename... Args>
T const& eval_get_field(std::variant<Args...> const& variant, char const* field) {
    return std::visit(
        [&](auto const& item) { return eval_get_field<T>(item, field); }, variant);
}

template <typename Collection, typename Callback>
bool eval_all(Collection const& collection, Callback const& callback) {
    for (auto const& it : collection) {
        if (!callback(it)) { return false; }
    }

    return true;
}

template <typename Collection, typename Callback>
bool eval_exists(Collection const& collection, Callback const& callback) {
    for (auto const& it : collection) {
        if (callback(it)) { return true; }
    }

    return false;
}

template <typename Collection, typename Callback>
bool eval_exists_one(Collection const& collection, Callback const& callback) {
    int counter = 0;
    for (auto const& it : collection) {
        if (callback(it)) { ++counter; }
        if (1 < counter) { return false; }
    }

    return counter == 1;
}

template <typename ResultType, typename T, typename Callback>
hstd::Vec<ResultType> eval_map(hstd::Vec<T> const& collection, Callback const& callback) {
    hstd::Vec<ResultType> res;
    for (auto const& it : collection) { res.push_back(callback(it)); }

    return res;
}

template <typename T, typename Callback>
hstd::Vec<T> eval_filter(hstd::Vec<T> const& collection, Callback const& callback) {
    hstd::Vec<T> res;
    for (auto const& it : collection) {
        if (callback(it)) { res.push_back(it); }
    }

    return res;
}


inline bool eval_str_matches(std::string const& value, std::string const& pattern) {
    return std::regex_search(value, std::regex{pattern});
}

template <typename Collection, typename T>
bool eval_list_contains(Collection const& collection, T const& value) {
    for (auto const& item : collection) {
        if (item == value) { return true; }
    }

    return false;
}

/// Return the half-open slice [start, end).
template <typename Result, typename Collection>
Result eval_list_slice(
    Collection const& collection,
    std::ptrdiff_t    start,
    std::ptrdiff_t    end) {
    if (start < 0 || end < start || std::cmp_greater(end, collection.size())) {
        throw std::out_of_range{"Invalid list slice bounds"};
    }

    Result result;
    auto   it = std::next(std::begin(collection), start);
    for (auto index = start; index < end; ++index, ++it) { result.push_back(*it); }

    return result;
}

template <typename Result, typename First, typename Second>
Result eval_list_concat(First const& first, Second const& second) {
    Result result;
    for (auto const& item : first) { result.push_back(item); }
    for (auto const& item : second) { result.push_back(item); }
    return result;
}

template <typename Result, typename Map, typename Key, typename Value>
Result eval_map_insert(Map const& map, Key const& key, Value const& value) {
    Result result{map};
    result.insert_or_assign(key, value);
    return result;
}

template <typename Result, typename Map>
Result eval_map_keys(Map const& map) {
    Result result;
    for (auto const& entry : map) { result.push_back(entry.first); }

    return result;
}

template <typename Result, typename Map>
Result eval_map_values(Map const& map) {
    Result result;
    for (auto const& entry : map) { result.push_back(entry.second); }

    return result;
}

template <typename Result, typename Collection, typename Callback>
Result eval_filter_map(Collection const& collection, Callback const& callback) {
    Result result;
    for (auto const& item : collection) {
        auto mapped = callback(item);
        if (mapped) { result.push_back(std::move(*mapped)); }
    }

    return result;
}

template <typename Result, typename Collection, typename Callback>
Result eval_take_while(Collection const& collection, Callback const& callback) {
    Result result;
    for (auto const& item : collection) {
        if (!callback(item)) { break; }
        result.push_back(item);
    }

    return result;
}

template <typename Result, typename Collection, typename Callback>
Result eval_group_by(Collection const& collection, Callback const& callback) {
    Result result;
    for (auto const& item : collection) { result[callback(item)].push_back(item); }

    return result;
}

template <typename Result, typename Collection, typename Callback>
Result eval_fold(Collection const& collection, Result initial, Callback const& callback) {
    for (auto const& item : collection) { initial = callback(std::move(initial), item); }

    return initial;
}

template <typename Result, typename Collection>
Result eval_sum(Collection const& collection) {
    Result result{};
    for (auto const& item : collection) { result += item; }
    return result;
}

template <typename Result, typename Collection>
Result eval_min(Collection const& collection) {
    auto it  = std::begin(collection);
    auto end = std::end(collection);
    if (it == end) {
        throw std::invalid_argument{"eval_min requires a nonempty collection"};
    }

    Result result{*it};
    for (++it; it != end; ++it) {
        if (*it < result) { result = *it; }
    }

    return result;
}

template <typename Result, typename Collection>
Result eval_max(Collection const& collection) {
    auto it  = std::begin(collection);
    auto end = std::end(collection);
    if (it == end) {
        throw std::invalid_argument{"eval_max requires a nonempty collection"};
    }

    Result result{*it};
    for (++it; it != end; ++it) {
        if (result < *it) { result = *it; }
    }

    return result;
}

}; // namespace hstd::ext::unidata
