#pragma once

#include "hstd/stdlib/Enumerate.hpp"
#include "hstd/stdlib/Set.hpp"
#include <any>
#include <boost/preprocessor.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/system/aux_utils.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <set>
#include <typeindex>

template <>
struct fmt::formatter<std::any> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(std::any const& p, fmt::format_context& ctx) const {
        return ::hstd::fmt_ctx(p.type().name(), ctx);
    }
};

namespace hstd {

template <typename... Ts>
struct AnyFormatter {
    std::string operator()(std::any const& a) const { return format_impl<Ts...>(a); }

  private:
    template <typename T, typename... Rest>
    std::string format_impl(std::any const& a) const {
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
    std::size_t operator()(std::any const& a) const { return hash_impl<Ts...>(a); }

  private:
    template <typename T, typename... Rest>
    std::size_t hash_impl(std::any const& a) const {
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
    bool operator()(std::any const& a, std::any const& b) const {
        return equal_impl<Ts...>(a, b);
    }

  private:
    template <typename T, typename... Rest>
    bool equal_impl(std::any const& a, std::any const& b) const {
        if (a.type() == typeid(T) && b.type() == typeid(T)) {
            return *std::any_cast<T>(&a) == *std::any_cast<T>(&b);
        } else if constexpr (sizeof...(Rest) > 0) {
            return equal_impl<Rest...>(a, b);
        } else {
            throw std::bad_any_cast();
        }
    }
};

template <typename Tag>
struct ReflTypeTraits {
    using AnyFormatterType = AnyFormatter<Str>;
    using AnyHasherType    = AnyHasher<Str>;
    using AnyEqualType     = AnyEqual<Str>;
    // using ReflPathFormatter = ReflPathItemFormatter<Tag>;
};


/// \brief Single step to access sub-element in the target reflection value.
template <typename Tag>
struct ReflAccessStep {
    /// \brief Target field is a vector.
    struct Index {
        int index;
        DESC_FIELDS(Index, (index));

        bool operator==(Index const& other) const { return index == other.index; }
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
        Tag::field_name_type name;
        DESC_FIELDS(FieldName, (name));

        bool operator==(FieldName const& other) const { return name == other.name; }
    };

    struct Deref {
        DESC_FIELDS(Deref, ());
        bool operator==(Deref const& other) const { return true; }
    };

    ReflAccessStep(ReflAccessStep const& other) : kind(other.kind) {
        switch (kind) {
            case Kind::Index: new (&data.index) Index(other.data.index); break;
            case Kind::FieldName:
                new (&data.fieldName) FieldName(other.data.fieldName);
                break;
            case Kind::AnyKey: new (&data.anyKey) AnyKey(other.data.anyKey); break;
            case Kind::Deref: new (&data.deref) Deref(other.data.deref); break;
        }
    }

    void operator=(ReflAccessStep const& other) {
        kind = other.kind;
        switch (kind) {
            case Kind::Index: data.index = other.data.index; break;
            case Kind::FieldName: data.fieldName = other.data.fieldName; break;
            case Kind::AnyKey: data.anyKey = other.data.anyKey; break;
            case Kind::Deref: data.deref = other.data.deref; break;
        }
    }

    ReflAccessStep(Index const& idx) : kind(Kind::Index), data(idx) {}
    ReflAccessStep(FieldName const& field) : kind(Kind::FieldName), data(field) {}
    ReflAccessStep(AnyKey const& key) : kind(Kind::AnyKey), data(key) {}
    ReflAccessStep(Deref const& ref) : kind(Kind::Deref), data(ref) {}

    static ReflAccessStep FromFieldName(Tag::field_name_type const& name) {
        return ReflAccessStep{FieldName{.name = name}};
    }

    static ReflAccessStep FromDeref() { return ReflAccessStep{Deref{}}; }

    static ReflAccessStep FromIndex(int const& name) {
        return ReflAccessStep{Index{.index = name}};
    }

    template <typename K>
    static ReflAccessStep FromAnyKey(K const& name) {
        return ReflAccessStep{AnyKey{.key = std::any(name)}};
    }

    // Using union instead of std::variant because the former one is at
    // least 30% faster for the immutable AST iteration -- running full
    // tree walk on test document goes from 350ms to under 200ms.
    union DataUnion {
        Index     index;
        FieldName fieldName;
        AnyKey    anyKey;
        Deref     deref;
        DataUnion(Index const& d) : index{d} {}
        DataUnion(FieldName const& f) : fieldName{f} {}
        DataUnion(AnyKey const& k) : anyKey{k} {}
        DataUnion(Deref const& d) : deref{d} {}
        DataUnion() : index{Index{}} {}
        ~DataUnion() {}
    };

    ~ReflAccessStep() {
        switch (kind) {
            case Kind::Index: data.index.~Index(); break;
            case Kind::FieldName: data.fieldName.~FieldName(); break;
            case Kind::AnyKey: data.anyKey.~AnyKey(); break;
            case Kind::Deref: data.deref.~Deref(); break;
        }
    }

    template <typename Func>
    void visit(Func cb) {
        switch (kind) {
            case Kind::Index: cb(getIndex()); break;
            case Kind::FieldName: cb(getFieldName()); break;
            case Kind::Deref: cb(getDeref()); break;
            case Kind::AnyKey: cb(getAnyKey()); break;
        }
    }

    template <typename Func>
    void visit(Func cb) const {
        switch (kind) {
            case Kind::Index: cb(getIndex()); break;
            case Kind::FieldName: cb(getFieldName()); break;
            case Kind::Deref: cb(getDeref()); break;
            case Kind::AnyKey: cb(getAnyKey()); break;
        }
    }


    DECL_DESCRIBED_ENUM(Kind, Index, FieldName, AnyKey, Deref);
    DESC_FIELDS(ReflAccessStep, (data, kind));

    Kind      getKind() const { return kind; }
    Kind      kind;
    DataUnion data;

    using variant_enum_type = Kind;
    using variant_data_type = std::variant<Index, FieldName, AnyKey, Deref>;
    Kind                     sub_variant_get_kind() const { return kind; }
    variant_data_type const& sub_variant_get_data() const {
        switch (kind) {
            case Kind::Index: return getIndex();
            case Kind::FieldName: return getFieldName();
            case Kind::AnyKey: return getAnyKey();
            case Kind::Deref: return getDeref();
        }
    }
    char const* sub_variant_get_name() const { return "data"; }

    void expectKind(Kind k) const {
        LOGIC_ASSERTION_CHECK_FMT(kind == k, "Expected kind {} but got {}", k, kind);
    }

    Index& getIndex() {
        expectKind(Kind::Index);
        return data.index;
    }

    Index const& getIndex() const {
        expectKind(Kind::Index);
        return data.index;
    }

    bool isIndex() const { return kind == Kind::Index; }
    bool isFieldName() const { return kind == Kind::FieldName; }
    bool isDeref() const { return kind == Kind::Deref; }
    bool isAnyKey() const { return kind == Kind::AnyKey; }

    FieldName& getFieldName() { return data.fieldName; }

    FieldName const& getFieldName() const {
        expectKind(Kind::FieldName);
        return data.fieldName;
    }

    AnyKey& getAnyKey() {
        expectKind(Kind::AnyKey);
        return data.anyKey;
    }

    AnyKey const& getAnyKey() const {
        expectKind(Kind::AnyKey);
        return data.anyKey;
    }


    Deref& getDeref() {
        expectKind(Kind::Deref);
        return data.deref;
    }

    Deref const& getDeref() const {
        expectKind(Kind::Deref);
        return data.deref;
    }


    bool operator==(ReflAccessStep const& it) const {
        if (it.getKind() == getKind()) {
            switch (kind) {
                case Kind::AnyKey: return data.anyKey == it.data.anyKey;
                case Kind::FieldName: return data.fieldName == it.data.fieldName;
                case Kind::Deref: return data.deref == it.data.deref;
                case Kind::Index: return data.index == it.data.index;
            }
        } else {
            return false;
        }
    }

    bool operator<(ReflAccessStep const& it) const {
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


template <typename Tag>
struct ReflPathItemFormatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(ReflAccessStep<Tag> const& step, fmt::format_context& ctx)
        const {
        typename ReflTypeTraits<Tag>::AnyFormatterType anyFmt;
        if (step.isAnyKey()) {
            fmt_ctx(anyFmt(step.getAnyKey().key), ctx);
        } else {
            step.visit([&](auto const& it) { fmt_ctx(it, ctx); });
        }

        return fmt_ctx("", ctx);
    }
};


/// \brief Sequence of steps to access direct or nested sub-element of the target type.
template <typename Tag>
struct ReflValueAccessPath {
    using Store = ReflTypeTraits<Tag>::ReflPathStoreType;
    Store path;
    DESC_FIELDS(ReflValueAccessPath, (path));
    ReflAccessStep<Tag> const& at(int idx) const { return path.at(idx); }

    struct VisitCtx {
        Vec<ReflAccessStep<Tag>> steps;
        using StepStore = Vec<ReflAccessStep<Tag>>;

        ReflValueAccessPath toPath() const {
            if constexpr (std::is_same_v<std::remove_cvref_t<Store>, VisitCtx>) {
                return ReflValueAccessPath(steps);
            } else {
                return ReflValueAccessPath{Store{steps.begin(), steps.end()}};
            }
        }

        void push_back(ReflAccessStep<Tag> const& item) { steps.push_back(item); }
        void pop_back() { steps.pop_back(); }
    };

    using iterator = VisitCtx::StepStore::iterator;

    ReflValueAccessPath() {}
    ReflValueAccessPath(iterator begin, iterator end) : path{begin, end} {}
    ReflValueAccessPath(Store path) : path{path} {}

    ReflValueAccessPath(ReflAccessStep<Tag> const& single) : path{{single}} {}

    bool isSingle() const { return path.size() == 1; }

    ReflAccessStep<Tag> const& first() const { return path.at(0); }
    ReflAccessStep<Tag> const& last() const { return path.back(); }

    ReflValueAccessPath dropPrefix(ReflValueAccessPath const& other) {
        auto begin = path.begin();
        for (int i = 0; i < path.size(); ++i) {
            if (i < other.path.size()) {
                LOGIC_ASSERTION_CHECK_FMT(other.path.at(i) == path.at(i), "");
                ++begin;
            }
        }
        return ReflValueAccessPath{Store{begin, path.end()}};
    }

    Pair<ReflAccessStep<Tag>, ReflValueAccessPath> split() const {
        if (path.size() == 1) {
            return {path.front(), {}};
        } else {
            return Pair<ReflAccessStep<Tag>, ReflValueAccessPath>{
                path.front(), ReflValueAccessPath{Store{path.begin() + 1, path.end()}}};
        }
    }

    ReflValueAccessPath addFieldName(Tag::field_name_type const& name) const {
        return add(ReflAccessStep<Tag>{typename ReflAccessStep<Tag>::FieldName{name}});
    }

    ReflValueAccessPath add(ReflValueAccessPath const& item) const {
        auto res = *this;
        res.path.append(item.path);
        return res;
    }

    ReflValueAccessPath add(ReflAccessStep<Tag> const& item) const {
        return ReflTypeTraits<Tag>::AddPathItem(*this, item);
    }

    bool empty() const { return path.empty(); }

    bool operator==(ReflValueAccessPath const& other) const {
        return path.operator==(other.path);
    }

    template <typename Cmp>
    bool lessThan(ReflValueAccessPath const& other, Cmp const& cmp) const {
        return itemwise_less_than(path, other.path, cmp);
    }

    bool operator<(ReflValueAccessPath const& other) const { return path < other.path; }
};


template <typename Tag>
struct ReflPathHasher {
    std::size_t operator()(ReflValueAccessPath<Tag> const& it) const noexcept {
        std::size_t                                 result = 0;
        typename ReflTypeTraits<Tag>::AnyHasherType anyHasher;
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

template <typename Tag>
struct ReflPathComparator {
    std::size_t operator()(
        ReflValueAccessPath<Tag> const& lhs,
        ReflValueAccessPath<Tag> const& rhs) const noexcept {
        typename ReflTypeTraits<Tag>::AnyEqualType anyEq;
        if (lhs.path.size() == rhs.path.size()) {
            for (int i = 0; i < lhs.path.size(); ++i) {
                if (lhs.at(i).getKind() == rhs.at(i).getKind()) {
                    if (lhs.at(i).isAnyKey()) {
                        if (!anyEq(
                                lhs.at(i).getAnyKey().key, rhs.at(i).getAnyKey().key)) {
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

template <typename Tag>
struct ReflPathFormatter {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(ReflValueAccessPath<Tag> const& step, fmt::format_context& ctx)
        const {
        ReflPathItemFormatter<Tag> fmt{};
        for (auto const& it : enumerator(step.path)) {
            if (!it.is_first()) { fmt_ctx(">>", ctx); }
            fmt.format(it.value(), ctx);
        }
        return fmt_ctx("", ctx);
    }
};


/// \brief Compile-time dispatch table for reflection traversal of a
/// concrete value type. Each specialization describes how to enumerate
/// the immediate sub-elements of `T` together with their path items.
/// Customizations can inherit from one of the key-value, indexed,
/// unordered-indexed or pass-through helper bases.
///
/// \brief Specializations must define `static void visitEach(T const&, Func const&)`
/// which would Invoke `cb(step, field)` for every immediate sub-element of `value`, in
/// deterministic order. `step` describes how to reach the field, `field` is a const
/// reference to it.
template <typename T, typename Tag>
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

template <DescribedRecord T, typename Tag>
struct ReflVisitor<T, Tag> {
    /// \brief Enumerate record fields (including base class fields) in
    /// declaration order. Step is a field name, field is `value.*ptr`.
    template <typename Func>
    static void visitEach(T const& value, Func const& cb) {
        for_each_field_with_base_value<T>(
            value, [&]<typename B>(B const& base, auto const& ptr) {
                cb(ReflAccessStep<Tag>::FromFieldName(
                       ReflTypeTraits<Tag>::InitFieldName(base, ptr)),
                   value.*ptr.pointer);
            });
    }
};


template <typename K, typename V, typename Map, typename Tag>
struct ReflVisitorKeyValue {
    /// \brief Enumerate map entries ordered by key when the key type
    /// supports `<`, otherwise in the order given by `Map::keys()`.
    template <typename Func>
    static void visitEach(Map const& value, Func const& cb) {
        if constexpr (requires(K a, K b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            Vec<K> keys;
            for (auto const& [key, _] : value) { keys.push_back(key); }
            for (auto const& key : sorted(keys)) {
                cb(ReflAccessStep<Tag>::FromAnyKey(key), value.at(key));
            }
        } else {
            for (auto const& key : value.keys()) {
                cb(ReflAccessStep<Tag>::FromAnyKey(key), value.at(key));
            }
        }
    }
};


template <typename T, typename Indexed, typename Tag>
struct ReflVisitorIndexed {
    /// \brief Enumerate elements of the indexed container in index order.
    /// Step is an integer position, field is `value.at(index)`.
    template <typename Func>
    static void visitEach(Indexed const& value, Func const& cb) {
        for (int i = 0; i < value.size(); ++i) {
            cb(ReflAccessStep<Tag>::FromIndex(i), value.at(i));
        }
    }
};


template <typename T, typename Unordered, typename Tag>
struct ReflVisitorUnorderedIndexed {
    static Vec<CRw<T>> getSorted(Unordered const& it) {
        Vec<CRw<T>> items;
        for (auto const& sub : it) { items.push_back(sub); }
        std::sort(items.begin(), items.end());
        return items;
    }

    /// \brief Enumerate elements of an unordered container in a
    /// deterministic sorted order, assigning sequential index steps.
    template <typename Func>
    static void visitEach(Unordered const& value, Func const& cb) {
        int index = 0;
        for (auto const& item : getSorted(value)) {
            cb(ReflAccessStep<Tag>::FromIndex(index++), item);
        }
    }
};


template <typename T, typename Tag>
struct ReflVisitor<Opt<T>, Tag> {
    /// \brief Enumerate the single contained value of an optional when it
    /// is engaged, using a deref step. Empty optionals yield no elements.
    template <typename Func>
    static void visitEach(Opt<T> const& value, Func const& cb) {
        if (value.has_value()) { cb(ReflAccessStep<Tag>::FromDeref(), value.value()); }
    }
};

template <typename T, typename Tag>
struct ReflVisitor<std::reference_wrapper<T>, Tag> {
    /// \brief Enumerate the single contained value of an optional when it
    /// is engaged, using a deref step. Empty optionals yield no elements.
    template <typename Func>
    static void visitEach(std::reference_wrapper<T> const& value, Func const& cb) {
        ReflVisitor<std::remove_cvref_t<T>, Tag>::visitEach(value.get(), cb);
    }
};


template <typename T, typename Tag>
struct ReflVisitor<std::shared_ptr<T>, Tag> {
    /// \brief Enumerate the pointee of a non-null shared pointer using a
    /// deref step. Null pointers yield no elements.
    template <typename Func>
    static void visitEach(std::shared_ptr<T> const& value, Func const& cb) {
        if (value) { cb(ReflAccessStep<Tag>::FromDeref(), *value); }
    }
};

template <typename T, typename Tag>
struct ReflVisitor<std::unique_ptr<T>, Tag> {
    template <typename Func>
    static void visitEach(std::unique_ptr<T> const& value, Func const& cb) {
        if (value) { cb(ReflAccessStep<Tag>::FromDeref(), *value); }
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
    if (size <= index) { throw std::out_of_range("Index out of range"); }
    apply_to_tuple_impl(
        std::forward<Tuple>(t),
        index,
        std::forward<Func>(func),
        std::make_index_sequence<size>{});
}

template <typename... Args, typename Tag>
struct ReflVisitor<std::tuple<Args...>, Tag> {
    /// \brief Enumerate tuple elements in index order. Step is a
    /// numeric index, field is the tuple element at that index.
    template <typename Func>
    static void visitEach(std::tuple<Args...> const& value, Func const& cb) {
        [&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
            (cb(ReflAccessStep<Tag>::FromIndex(int(Idx)), std::get<Idx>(value)), ...);
        }(std::index_sequence_for<Args...>{});
    }
};

template <typename T1, typename T2, typename Tag>
struct ReflVisitor<Pair<T1, T2>, Tag> {
    /// \brief Enumerate `first` at index 0 and `second` at index 1.
    template <typename Func>
    static void visitEach(Pair<T1, T2> const& value, Func const& cb) {
        cb(ReflAccessStep<Tag>::FromIndex(0), value.first);
        cb(ReflAccessStep<Tag>::FromIndex(1), value.second);
    }
};

template <IsVariant T, typename Tag>
struct ReflVisitor<T, Tag> {
    /// \brief Enumerate the currently held variant alternative using an
    /// index step matching `value.index()`.
    template <typename Func>
    static void visitEach(T const& value, Func const& cb) {
        std::visit(
            [&](auto const& it) {
                cb(ReflAccessStep<Tag>::FromIndex(value.index()), it);
            },
            value);
    }
};

template <typename T, typename Tag>
struct ReflVisitor<Vec<T>, Tag> : ReflVisitorIndexed<T, Vec<T>, Tag> {};

template <typename T, typename Tag>
struct ReflVisitor<std::vector<T>, Tag> : ReflVisitorIndexed<T, std::vector<T>, Tag> {};

template <typename K, typename V, typename Tag>
struct ReflVisitor<UnorderedMap<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, UnorderedMap<K, V>, Tag> {};

template <typename K, typename V, typename Tag>
struct ReflVisitor<SortedMap<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, SortedMap<K, V>, Tag> {};

template <typename K, typename V, typename Tag>
struct ReflVisitor<std::unordered_map<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, std::unordered_map<K, V>, Tag> {};

template <typename K, typename V, typename Tag>
struct ReflVisitor<std::map<K, V>, Tag>
    : ReflVisitorKeyValue<K, V, std::map<K, V>, Tag> {};

template <typename T, typename Tag>
struct ReflVisitor<std::set<T>, Tag>
    : ReflVisitorUnorderedIndexed<T, std::set<T>, Tag> {};

template <typename T, typename Tag>
struct ReflVisitor<std::unordered_set<T>, Tag>
    : ReflVisitorUnorderedIndexed<T, std::unordered_set<T>, Tag> {};

template <typename T, typename Tag>
struct ReflVisitor<UnorderedSet<T>, Tag>
    : ReflVisitorUnorderedIndexed<T, UnorderedSet<T>, Tag> {};


template <typename T, typename Tag>
struct ReflVisitorLeafType {
    /// \brief Leaf values are terminal nodes in the traversal; no step
    /// callback is invoked. Attempting further indexed navigation is
    /// rejected in `reflVisitPath` via `refl_has_sub_path`.
    template <typename Func>
    static void visitEach(T const& value, Func const& cb) {}
};


template <typename Tag>
struct ReflVisitor<int, Tag> : ReflVisitorLeafType<int, Tag> {};

template <typename Tag>
struct ReflVisitor<hstd::u32, Tag> : ReflVisitorLeafType<hstd::u32, Tag> {};

template <typename Tag>
struct ReflVisitor<hstd::u16, Tag> : ReflVisitorLeafType<hstd::u16, Tag> {};

template <typename Tag>
struct ReflVisitor<char, Tag> : ReflVisitorLeafType<char, Tag> {};

template <typename Tag>
struct ReflVisitor<float, Tag> : ReflVisitorLeafType<float, Tag> {};

template <typename Tag>
struct ReflVisitor<double, Tag> : ReflVisitorLeafType<double, Tag> {};

template <typename Tag>
struct ReflVisitor<bool, Tag> : ReflVisitorLeafType<bool, Tag> {};

template <IsEnum E, typename Tag>
struct ReflVisitor<E, Tag> : ReflVisitorLeafType<E, Tag> {};

template <typename Tag>
struct ReflVisitor<char const*, Tag> : ReflVisitorLeafType<char const*, Tag> {};

template <typename Tag>
struct ReflVisitor<std::string, Tag> : ReflVisitorLeafType<std::string, Tag> {};

template <typename Tag>
struct ReflVisitor<Str, Tag> : ReflVisitorLeafType<Str, Tag> {};

template <typename Tag>
struct ReflVisitor<std::nullptr_t, Tag> : ReflVisitorLeafType<std::nullptr_t, Tag> {};

/// \brief Collect enumeration steps of the immediate sub-elements of
/// `item` into a vector. Retained for callers that materialize the list.
template <typename T, typename Tag>
Vec<ReflAccessStep<Tag>> reflSubItems(T const& item) {
    Vec<ReflAccessStep<Tag>> result;
    ReflVisitor<T, Tag>::visitEach(
        item, [&]<typename F>(ReflAccessStep<Tag> const& step, F const&) {
            result.push_back(step);
        });
    return result;
}


struct ReflRecursiveVisitContext {
    hstd::UnorderedSet<u64> visitedPointers;
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

namespace details {
template <typename T, typename Tag, typename Func>
void reflVisitAll(
    T const&                                     value,
    typename ReflValueAccessPath<Tag>::VisitCtx& step_context,
    ReflRecursiveVisitContext&                   ctx,
    Func const&                                  cb) {
    cb(std::as_const(step_context), value);
    if (ctx.canRecurse(value)) {
        ctx.visit(value);
        ReflVisitor<std::remove_cvref_t<T>, Tag>::visitEach(
            value, [&]<typename F>(ReflAccessStep<Tag> const& step, F const& fieldValue) {
                step_context.push_back(step);
                details::reflVisitAll<F, Tag>(fieldValue, step_context, ctx, cb);
                step_context.pop_back();
            });
    }
}

} // namespace details

template <typename T, typename Tag, typename Func>
void reflVisitAll(
    T const&                        value,
    ReflValueAccessPath<Tag> const& path,
    ReflRecursiveVisitContext&      ctx,
    Func const&                     cb) {
    typename ReflValueAccessPath<Tag>::VisitCtx step_context;
    for (auto const& it : path.path) { step_context.steps.push_back(it); }
    details::reflVisitAll<std::remove_cvref_t<T>, Tag, Func>(
        value, step_context, ctx, cb);
}


template <typename T, typename Func, typename Tag>
void reflVisitDirectItems(T const& value, Func const& cb) {
    ReflVisitor<T, Tag>::visitEach(
        value, [&]<typename F>(ReflAccessStep<Tag> const& step, F const& fieldValue) {
            cb(step, fieldValue);
        });
}


template <typename T, typename Func, typename Tag>
void reflVisitPath(T const& value, ReflValueAccessPath<Tag> const& path, Func const& cb) {
    if (path.empty()) {
        cb(value);
    } else {
        auto [head, tail] = path.split();
        ReflVisitor<T, Tag>::visitEach(
            value, [&]<typename F>(ReflAccessStep<Tag> const& step, F const& fieldValue) {
                if (step == head) { reflVisitPath<F>(fieldValue, tail, cb); }
            });
    }
}


// Runtime registry for field information
class TypeFieldNameRegistry {
  public:
    struct TypeInfo {
        std::string              type_name;
        std::vector<std::string> field_names;
        std::size_t              field_count;
    };

  private:
    static std::unordered_map<std::type_index, TypeInfo>& get_registry() {
        static std::unordered_map<std::type_index, TypeInfo> registry;
        return registry;
    }

  public:
    template <typename T>
    static void register_type() {
        std::type_index type_id  = std::type_index(typeid(T));
        auto&           registry = get_registry();

        if (registry.find(type_id) != registry.end()) { return; }

        TypeInfo info;
        info.type_name = hstd::demangle(type_id.name());
        collect_field_names<T>(info.field_names);
        info.field_count = info.field_names.size();

        registry[type_id] = std::move(info);
    }

    static std::string get_field_name(std::type_index type_id, std::size_t field_index);

    static std::size_t get_field_count(std::type_index type_id);

  private:
    template <typename T>
    static void collect_field_names(std::vector<std::string>& names) {
        // First collect base class fields
        if constexpr (boost::describe::has_describe_bases<T>::value) {
            using bases = boost::describe::
                describe_bases<T, boost::describe::mod_any_access>;
            boost::mp11::mp_for_each<bases>([&](auto base_desc) {
                using base_type = typename decltype(base_desc)::type;
                collect_field_names<base_type>(names);
            });
        }

        // Then collect own fields
        if constexpr (boost::describe::has_describe_members<T>::value) {
            using own_members = boost::describe::
                describe_members<T, boost::describe::mod_any_access>;
            boost::mp11::mp_for_each<own_members>(
                [&](auto member_desc) { names.emplace_back(member_desc.name); });
        }
    }
};

// Auto-registration helper
template <typename T>
struct AutoRegisterType {
    AutoRegisterType() { TypeFieldNameRegistry::register_type<T>(); }
};

// clang-format off
#define HSTD_REGISTER_TYPE_FIELD_NAMES(T)                                 \
    namespace {                                                           \
    static ::hstd::AutoRegisterType<T> BOOST_PP_CAT(auto_register, __COUNTER__); \
    }

// clang-format on

// Convenience functions
template <typename T>
std::string get_registered_field_name(std::size_t field_index) {
    TypeFieldNameRegistry::register_type<T>(); // Ensure registered
    return TypeFieldNameRegistry::get_field_name(std::type_index(typeid(T)), field_index);
}

inline std::string get_registered_field_name(
    std::type_index type_id,
    std::size_t     field_index) {
    return TypeFieldNameRegistry::get_field_name(type_id, field_index);
}

template <typename T>
std::size_t get_registered_field_count() {
    TypeFieldNameRegistry::register_type<T>(); // Ensure registered
    return TypeFieldNameRegistry::get_field_count(std::type_index(typeid(T)));
}

inline std::size_t get_registered_field_count(std::type_index type_id) {
    return TypeFieldNameRegistry::get_field_count(type_id);
}


} // namespace hstd


template <typename Tag>
struct fmt::formatter<hstd::ReflValueAccessPath<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(
        hstd::ReflValueAccessPath<Tag> const& step,
        fmt::format_context&                  ctx) const {
        for (auto const& it : enumerator(step.path)) {
            if (!it.is_first()) { ::hstd::fmt_ctx(">>", ctx); }
            ::hstd::fmt_ctx(it.value(), ctx);
        }
        return ::hstd::fmt_ctx("", ctx);
    }
};


template <typename Tag>
struct std::hash<hstd::ReflValueAccessPath<Tag>> {
    std::size_t operator()(hstd::ReflValueAccessPath<Tag> const& it) const noexcept {
        std::size_t result = 0;
        ::hstd::hax_hash_combine(result, it.path);
        return result;
    }
};

template <typename Tag>
struct fmt::formatter<hstd::ReflAccessStep<Tag>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(hstd::ReflAccessStep<Tag> const& step, fmt::format_context& ctx)
        const {
        step.visit([&](auto const& it) { ::hstd::fmt_ctx(it, ctx); });
        return ::hstd::fmt_ctx("", ctx);
    }
};


template <typename Tag>
struct std::hash<hstd::ReflAccessStep<Tag>> {
    std::size_t operator()(hstd::ReflAccessStep<Tag> const& it) const noexcept {
        std::size_t result = 0;
        it.visit(
            ::hstd::overloaded{
                [&](hstd::ReflAccessStep<Tag>::Deref) {},
                [&](hstd::ReflAccessStep<Tag>::AnyKey value) {
                    typename hstd::ReflTypeTraits<Tag>::AnyHasherType h;
                    result = h(value.key);
                },
                [&](hstd::ReflAccessStep<Tag>::Index value) {
                    ::hstd::hax_hash_combine(result, value.index);
                },
                [&](hstd::ReflAccessStep<Tag>::FieldName value) {
                    ::hstd::hax_hash_combine(result, value.name);
                },
            });
        return result;
    }
};
