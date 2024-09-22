#pragma once

#include "hstd/stdlib/Set.hpp"
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
struct AnyFormatter {
    std::string operator()(const std::any& a) const {
        return format_impl<Ts...>(a);
    }

  private:
    template <typename T, typename... Rest>
    std::string format_impl(const std::any& a) const {
        if (a.type() == typeid(T)) {
            return fmt1(*std::any_cast<T>(&a));
        } else if constexpr (sizeof...(Rest) > 0) {
            return format_impl<Rest...>(a);
        } else {
            throw std::bad_any_cast();
        }
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
    struct Index {
        int index;
        DESC_FIELDS(Index, (index));

        bool operator==(Index const& other) const {
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

    struct Deref {
        DESC_FIELDS(Deref, ());
        bool operator==(Deref const& other) const { return true; }
    };

    static ReflPathItem FromFieldName(std::string const& name) {
        return ReflPathItem{FieldName{.name = name}};
    }

    static ReflPathItem FromDeref() { return ReflPathItem{Deref{}}; }

    static ReflPathItem FromIndex(int const& name) {
        return ReflPathItem{Index{.index = name}};
    }

    template <typename K>
    static ReflPathItem FromAnyKey(K const& name) {
        return ReflPathItem{AnyKey{.key = std::any(name)}};
    }

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        Index,
        FieldName,
        AnyKey,
        Deref);
    Data data;
    DESC_FIELDS(ReflPathItem, (data));
    bool operator==(ReflPathItem const& it) const {
        return data == it.data;
    }

    bool operator<(ReflPathItem const& it) const {
        if (getKind() == it.getKind()) {
            switch (getKind()) {
                case Kind::AnyKey: {
                    return false;
                }
                case Kind::Index: {
                    return getIndex().index < it.getIndex().index;
                }
                case Kind::Deref: {
                    return false;
                }
                case Kind::FieldName: {
                    return getFieldName().name < it.getFieldName().name;
                }
            }
        } else {
            return getKind() < it.getKind();
        }
    }
};

template <>
struct std::hash<ReflPathItem::Deref> {
    std::size_t operator()(ReflPathItem::Deref const& it) const noexcept {
        std::size_t result = 0;
        return result;
    }
};

template <>
struct std::formatter<ReflPathItem::Deref> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPathItem::Deref& p, FormatContext& ctx) const {
        return fmt_ctx("*()", ctx);
    }
};

template <>
struct std::formatter<ReflPathItem::Index> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPathItem::Index& p, FormatContext& ctx) const {
        fmt_ctx("[", ctx);
        fmt_ctx(p.index, ctx);
        return fmt_ctx("]", ctx);
    }
};

template <>
struct std::hash<ReflPathItem::Index> {
    std::size_t operator()(ReflPathItem::Index const& it) const noexcept {
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
struct std::formatter<ReflPathItem::FieldName>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPathItem::FieldName& p, FormatContext& ctx)
        const {
        fmt_ctx(".", ctx);
        return fmt_ctx(p.name, ctx);
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
    DESC_FIELDS(ReflPath, (path));
    ReflPathItem const& at(int idx) const { return path.at(idx); }

    using iterator = Vec<ReflPathItem>::iterator;

    ReflPath() {}
    ReflPath(iterator begin, iterator end) : path{begin, end} {}
    ReflPath(Vec<ReflPathItem> path) : path{path} {}
    ReflPath(ReflPathItem const& single) : path{{single}} {}

    bool isSingle() const { return path.size() == 1; }

    ReflPathItem const& first() const { return path.at(0); }
    ReflPathItem const& last() const { return path.back(); }

    ReflPath dropPrefix(ReflPath const& other) {
        ReflPath result;
        for (int i = 0; i < path.size(); ++i) {
            if (i < other.path.size()) {
                LOGIC_ASSERTION_CHECK(other.path.at(i) == path.at(i), "");
            } else {
                result.path.push_back(path.at(i));
            }
        }
        return result;
    }

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

    ReflPath add(ReflPath const& item) const {
        auto res = *this;
        res.path.append(item.path);
        return res;
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

    template <typename Cmp>
    bool lessThan(ReflPath const& other, Cmp const& cmp) const {
        return path.lessThan(other.path, cmp);
    }

    bool operator<(ReflPath const& other) const {
        return path < other.path;
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

template <typename... AnyKeyTypes>
struct ReflPathHasher {
    std::size_t operator()(ReflPath const& it) const noexcept {
        std::size_t               result = 0;
        AnyHasher<AnyKeyTypes...> anyHasher;
        for (auto const& it : it.path) {
            if (it.isAnyKey()) {
                hax_hash_combine(result, anyHasher(it.getAnyKey().key));
            } else {
                hax_hash_combine(result, it);
            }
        }
        return result;
    }
};

template <typename... AnyKeyTypes>
struct ReflPathComparator {
    std::size_t operator()(ReflPath const& lhs, ReflPath const& rhs)
        const noexcept {
        std::size_t              result = 0;
        AnyEqual<AnyKeyTypes...> anyEq;
        if (lhs.path.size() == rhs.path.size()) {
            for (int i = 0; i < lhs.path.size(); ++i) {
                if (lhs.at(i).getKind() == rhs.at(i).getKind()) {
                    if (lhs.at(i).isAnyKey()) {
                        if (!anyEq(
                                lhs.at(i).getAnyKey().key,
                                rhs.at(i).getAnyKey().key)) {
                            return false;
                        }
                    } else {
                        if (lhs.at(i) != rhs.at(i)) { return false; }
                    }
                } else {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
};


template <typename T>
struct ReflVisitor {};


template <typename T>
struct ReflPointer {
    static Opt<u64> getPointerId(T const&) { return std::nullopt; }
};

template <typename T>
struct ReflPointer<T const*> {
    static Opt<u64> getPointerId(T const* ptr) { return (u64)(ptr); }
};

template <typename T>
struct ReflPointer<std::shared_ptr<T>> {
    static Opt<u64> getPointerId(std::shared_ptr<T> const& ptr) {
        return ReflPointer<T const*>::getPointerId(ptr.get());
    }
};


template <typename T>
struct ReflPointer<std::unique_ptr<T>> {
    static Opt<u64> getPointerId(std::unique_ptr<T> const& ptr) {
        return ReflPointer<T const*>::getPointerId(ptr.get());
    }
};

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

template <typename K, typename V, typename Map>
struct ReflVisitorKeyValue {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Map const&          value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isAnyKey(), "{}", step.getKind());
        cb(value.at(step.getAnyKey().get<K>()));
    }


    static Vec<ReflPathItem> subitems(Map const& value) {
        Vec<ReflPathItem> result;
        if constexpr (requires(K a, K b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            Vec<K> keys;
            for (auto const& [key, _] : value) { keys.push_back(key); }
            for (auto const& key : sorted(keys)) {
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

template <typename T, typename Indexed>
struct ReflVisitorIndexed {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Indexed const&      value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        cb(value.at(step.getIndex().index));
    }


    static Vec<ReflPathItem> subitems(Indexed const& value) {
        Vec<ReflPathItem> result;
        for (int i = 0; i < value.size(); ++i) {
            result.push_back(ReflPathItem::FromIndex(i));
        }

        return result;
    }
};


template <typename T, typename Unordered>
struct ReflVisitorUnorderedIndexed {
    static Vec<CRw<T>> getSorted(Unordered const& it) {
        Vec<CRw<T>> items;
        for (auto const& sub : it) { items.push_back(sub); }
        std::sort(items.begin(), items.end());
        return items;
    }

    template <typename Func>
    static void visit(
        Unordered const&    value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        cb(getSorted(value).at(step.getIndex().index).get());
    }


    static Vec<ReflPathItem> subitems(Unordered const& value) {
        Vec<ReflPathItem> result;
        for (int i = 0; i < value.size(); ++i) {
            result.push_back(ReflPathItem::FromIndex(i));
        }

        return result;
    }
};


template <typename T>
struct ReflVisitor<Opt<T>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Opt<T> const&       value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        cb(value.value());
    }


    static Vec<ReflPathItem> subitems(Opt<T> const& value) {
        Vec<ReflPathItem> result;
        if (value.has_value()) {
            result.push_back(ReflPathItem::FromDeref());
        }

        return result;
    }
};

template <typename T>
struct ReflVisitor<std::shared_ptr<T>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::shared_ptr<T> const& value,
        ReflPathItem const&       step,
        Func const&               cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(value.get() != nullptr, "");
        cb(*value.get());
    }


    static Vec<ReflPathItem> subitems(std::shared_ptr<T> const& value) {
        Vec<ReflPathItem> result;
        if (value.get() != nullptr) {
            result.push_back(ReflPathItem::FromDeref());
        }

        return result;
    }
};

template <typename T>
struct ReflVisitor<std::unique_ptr<T>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::unique_ptr<T> const& value,
        ReflPathItem const&       step,
        Func const&               cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(value.get() != nullptr, "");
        cb(*value.get());
    }


    static Vec<ReflPathItem> subitems(std::unique_ptr<T> const& value) {
        Vec<ReflPathItem> result;
        if (value.get() != nullptr) {
            result.push_back(ReflPathItem::FromDeref());
        }

        return result;
    }
};

template <typename Tuple, typename Func, std::size_t... Is>
void apply_to_tuple_impl(
    Tuple&&     t,
    std::size_t index,
    Func&&      func,
    std::index_sequence<Is...>) {
    ((Is == index ? (void)func(std::get<Is>(t)) : void()), ...);
}

template <typename Tuple, typename Func>
void apply_to_tuple(Tuple&& t, std::size_t index, Func&& func) {
    constexpr std::size_t size = std::tuple_size_v<std::decay_t<Tuple>>;
    if (index >= size) { throw std::out_of_range("Index out of range"); }
    apply_to_tuple_impl(
        std::forward<Tuple>(t),
        index,
        std::forward<Func>(func),
        std::make_index_sequence<size>{});
}

template <typename... Args>
struct ReflVisitor<std::tuple<Args...>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::tuple<Args...> const& value,
        ReflPathItem const&        step,
        Func const&                cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        apply_to_tuple(value, step.getIndex().index, cb);
    }


    static Vec<ReflPathItem> subitems(std::tuple<Args...> const& value) {
        Vec<ReflPathItem> result;
        for (int i = 0; i < std::tuple_size_v<std::tuple<Args...>>; ++i) {
            result.push_back(ReflPathItem::FromIndex(i));
        }
        return result;
    }
};

template <typename T1, typename T2>
struct ReflVisitor<Pair<T1, T2>> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Pair<T1, T2> const& value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(
            (0 <= step.getIndex().index && step.getIndex().index <= 1),
            "{}",
            step.getIndex().index);
        if (step.getIndex().index == 0) {
            cb(value.first);
        } else {
            cb(value.second);
        }
    }

    static Vec<ReflPathItem> subitems(Pair<T1, T2> const& value) {
        Vec<ReflPathItem> result;
        for (int i = 0; i < std::tuple_size_v<Pair<T1, T2>>; ++i) {
            result.push_back(ReflPathItem::FromIndex(i));
        }
        return result;
    }
};

template <IsVariant T>
struct ReflVisitor<T> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        T const&            value,
        ReflPathItem const& step,
        Func const&         cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(
            value.index() == step.getIndex().index, "{}", value.index());
        std::visit([&](auto const& it) { cb(it); }, value);
    }


    static Vec<ReflPathItem> subitems(T const& value) {
        Vec<ReflPathItem> result;
        result.push_back(ReflPathItem::FromIndex(value.index()));
        return result;
    }
};

template <typename T>
struct ReflVisitor<Vec<T>> : ReflVisitorIndexed<T, Vec<T>> {};

template <typename T>
struct ReflVisitor<std::vector<T>>
    : ReflVisitorIndexed<T, std::vector<T>> {};

template <typename K, typename V>
struct ReflVisitor<UnorderedMap<K, V>>
    : ReflVisitorKeyValue<K, V, UnorderedMap<K, V>> {};

template <typename K, typename V>
struct ReflVisitor<SortedMap<K, V>>
    : ReflVisitorKeyValue<K, V, SortedMap<K, V>> {};

template <typename K, typename V>
struct ReflVisitor<std::unordered_map<K, V>>
    : ReflVisitorKeyValue<K, V, std::unordered_map<K, V>> {};

template <typename K, typename V>
struct ReflVisitor<std::map<K, V>>
    : ReflVisitorKeyValue<K, V, std::map<K, V>> {};

template <typename T>
struct ReflVisitor<std::set<T>>
    : ReflVisitorUnorderedIndexed<T, std::set<T>> {};

template <typename T>
struct ReflVisitor<std::unordered_set<T>>
    : ReflVisitorUnorderedIndexed<T, std::unordered_set<T>> {};

template <typename T>
struct ReflVisitor<UnorderedSet<T>>
    : ReflVisitorUnorderedIndexed<T, UnorderedSet<T>> {};


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
struct ReflVisitor<float> : ReflVisitorLeafType<float> {};

template <>
struct ReflVisitor<double> : ReflVisitorLeafType<double> {};

template <>
struct ReflVisitor<bool> : ReflVisitorLeafType<bool> {};

template <IsEnum E>
struct ReflVisitor<E> : ReflVisitorLeafType<E> {};

template <>
struct ReflVisitor<char const*> : ReflVisitorLeafType<char const*> {};

template <>
struct ReflVisitor<std::string> : ReflVisitorLeafType<std::string> {};

template <>
struct ReflVisitor<Str> : ReflVisitorLeafType<Str> {};

template <>
struct ReflVisitor<std::nullptr_t>
    : ReflVisitorLeafType<std::nullptr_t> {};

template <typename T>
Vec<ReflPathItem> reflSubItems(T const& item) {
    return ReflVisitor<T>::subitems(item);
}

struct ReflRecursiveVisitContext {
    UnorderedSet<u64> visitedPointers;
    template <typename T>
    bool canRecurse(T const& item) const {
        Opt<u64> id = ReflPointer<T>::getPointerId(item);
        return !id.has_value() || !visitedPointers.contains(*id);
    }

    template <typename T>
    void visit(T const& item) {
        Opt<u64> id = ReflPointer<T>::getPointerId(item);
        if (id) { visitedPointers.incl(*id); }
    }
};

template <typename T, typename Func>
void reflVisitAll(
    T const&                   value,
    ReflPath const&            path,
    ReflRecursiveVisitContext& ctx,
    Func const&                cb) {
    cb(path, value);
    if (ctx.canRecurse(value)) {
        ctx.visit(value);
        for (auto const& step : ReflVisitor<T>::subitems(value)) {
            ReflVisitor<T>::visit(
                value, step, [&]<typename F>(F const& fieldValue) {
                    reflVisitAll<F>(fieldValue, path.add(step), ctx, cb);
                });
        }
    }
}

template <typename T, typename Func>
void reflVisitDirectItems(T const& value, Func const& cb) {
    for (auto const& step : ReflVisitor<T>::subitems(value)) {
        ReflVisitor<T>::visit(
            value, step, [&]<typename F>(F const& fieldValue) {
                cb(step, fieldValue);
            });
    }
}

template <typename T, typename Func>
void reflVisitPath(T const& value, ReflPath const& path, Func const& cb) {
    if (path.empty()) {
        cb(value);
    } else {
        auto [head, tail] = path.split();
        ReflVisitor<T>::visit(
            value, head, [&]<typename F>(F const& fieldValue) {
                reflVisitPath<F>(fieldValue, tail, cb);
            });
    }
}
