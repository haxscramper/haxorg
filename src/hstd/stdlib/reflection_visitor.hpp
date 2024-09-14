#pragma once

#include <hstd/system/aux_utils.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Map.hpp>
#include <any>
#include <hstd/stdlib/algorithms.hpp>

template <>
struct std::formatter<std::any> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const std::any& p, FormatContext& ctx) const {
        return fmt_ctx(p.type().name(), ctx);
    }
};

template <typename... Ts>
struct AnyHasher {
    std::size_t operator()(const std::any& a) const {
        return hash_impl<Ts...>(a);
    }

  private:
    template <typename T, typename... Rest>
    std::size_t hash_impl(const std::any& a) const {
        if (a.type() == typeid(T)) {
            return std::hash<T>{}(*std::any_cast<T>(&a));
        } else if constexpr (sizeof...(Rest) > 0) {
            return hash_impl<Rest...>(a);
        } else {
            throw std::bad_any_cast();
        }
    }
};

template <typename... Ts>
struct AnyEqual {
    bool operator()(const std::any& a, const std::any& b) const {
        return equal_impl<Ts...>(a, b);
    }

  private:
    template <typename T, typename... Rest>
    bool equal_impl(const std::any& a, const std::any& b) const {
        if (a.type() == typeid(T) && b.type() == typeid(T)) {
            return *std::any_cast<T>(&a) == *std::any_cast<T>(&b);
        } else if constexpr (sizeof...(Rest) > 0) {
            return equal_impl<Rest...>(a, b);
        } else {
            throw std::bad_any_cast();
        }
    }
};


struct ReflPathItem {
    /// \brief Target field is a vector.
    struct SubIndex {
        int index;
        DESC_FIELDS(SubIndex, (index));

        bool operator==(SubIndex const& other) const {
            return index == other.index;
        }
    };

    struct AnyKey {
        std::any key;
        DESC_FIELDS(AnyKey, (key));
        bool operator==(AnyKey const& other) const { return false; }

        template <typename T>
        T const& get() const {
            return *std::any_cast<T>(&key);
        }
    };

    struct FieldName {
        std::string name;
        DESC_FIELDS(FieldName, (name));

        bool operator==(FieldName const& other) const {
            return name == other.name;
        }
    };

    static ReflPathItem FromFieldName(std::string const& name) {
        return ReflPathItem{FieldName{.name = name}};
    }

    template <typename K>
    static ReflPathItem FromAnyKey(K const& name) {
        return ReflPathItem{AnyKey{.key = std::any(name)}};
    }

    SUB_VARIANTS(Kind, Data, data, getKind, SubIndex, FieldName, AnyKey);
    Data data;
    DESC_FIELDS(ReflPathItem, (data));
    bool operator==(ReflPathItem const& it) const {
        return data == it.data;
    }
};


template <>
struct std::hash<ReflPathItem::SubIndex> {
    std::size_t operator()(
        ReflPathItem::SubIndex const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.index);
        return result;
    }
};

template <>
struct std::hash<ReflPathItem::FieldName> {
    std::size_t operator()(
        ReflPathItem::FieldName const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.name);
        return result;
    }
};

template <>
struct std::hash<ReflPathItem::AnyKey> {
    std::size_t operator()(ReflPathItem::AnyKey const& it) const noexcept {
        std::size_t result = 0;
        // hax_hash_combine(result, it.key);
        return result;
    }
};


template <>
struct std::hash<ReflPathItem> {
    std::size_t operator()(ReflPathItem const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.data);
        return result;
    }
};


struct ReflPath {
    Vec<ReflPathItem> path;

    Pair<ReflPathItem, ReflPath> split() const {
        if (path.size() == 1) {
            return {path.front(), {}};
        } else {
            auto span = path.at(slice(1, 1_B));
            return Pair<ReflPathItem, ReflPath>{
                path.front(),
                ReflPath{Vec<ReflPathItem>{span.begin(), span.end()}}};
        }
    }

    ReflPath addFieldName(std::string const& name) const {
        return add(ReflPathItem{ReflPathItem::FieldName{name}});
    }

    ReflPath add(ReflPathItem const& item) const {
        auto res = *this;
        res.path.push_back(item);
        return res;
    }

    bool empty() const { return path.empty(); }

    bool operator==(ReflPath const& other) const {
        return path == other.path;
    }
};

template <>
struct std::hash<ReflPath> {
    std::size_t operator()(ReflPath const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.path);
        return result;
    }
};


template <typename T>
struct ReflVisitor {};


struct refl_invalid_visit : CRTP_hexception<refl_invalid_visit> {};

template <DescribedRecord T>
struct ReflVisitor<T> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        T const&            value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isFieldName(), "{}", step.getKind());
        for_each_field_value_with_bases<T>(
            value, [&]<typename F>(char const* name, F const& value) {
                if (Str{name} == step.getFieldName().name) { cb(value); }
            });
    }


    static Vec<ReflPathItem> subitems(T const& value) {
        Vec<ReflPathItem> result;
        for_each_field_value_with_bases(
            value, [&]<typename F>(char const* name, F const& value) {
                result.push_back(ReflPathItem::FromFieldName(name));
            });

        return result;
    }
};

template <typename K, typename V>
struct ReflVisitor<UnorderedMap<K, V>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        UnorderedMap<K, V> const& value,
        ReflPathItem const&       step,
        Func const&               cb) {
        LOGIC_ASSERTION_CHECK(step.isAnyKey(), "{}", step.getKind());
        cb(value.at(step.getAnyKey().get<K>()));
    }


    static Vec<ReflPathItem> subitems(UnorderedMap<K, V> const& value) {
        Vec<ReflPathItem> result;
        if constexpr (requires(K a, K b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            for (auto const& key : sorted(value.keys())) {
                result.push_back(ReflPathItem::FromAnyKey(key));
            }
        } else {
            for (auto const& key : value.keys()) {
                result.push_back(ReflPathItem::FromAnyKey(key));
            }
        }


        return result;
    }
};

template <typename T>
struct ReflVisitorLeafType {
    template <typename Func>
    static void visit(
        T const&            value,
        ReflPathItem const& step,
        Func const&         cb) {
        throw refl_invalid_visit::init(
            fmt("Type {} cannot be indexed into using path step {}",
                demangle(typeid(T).name()),
                step));
    }


    static Vec<ReflPathItem> subitems(T const& value) { return {}; }
};

template <>
struct ReflVisitor<int> : ReflVisitorLeafType<int> {};

template <>
struct ReflVisitor<char> : ReflVisitorLeafType<char> {};

template <>
struct ReflVisitor<std::string> : ReflVisitorLeafType<std::string> {};


template <typename T>
Vec<ReflPathItem> reflSubItems(T const& item) {
    return ReflVisitor<T>::subitems(item);
}

template <typename T, typename Func>
void reflVisitAll(T const& value, ReflPath const& path, Func const& cb) {
    cb(path, value);
    for (auto const& step : ReflVisitor<T>::subitems(value)) {
        ReflVisitor<T>::visit(
            value, step, [&]<typename F>(F const& fieldValue) {
                reflVisitAll<F>(fieldValue, path.add(step), cb);
            });
    }
}
