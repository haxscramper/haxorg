#pragma once

#include "hstd/stdlib/Enumerate.hpp"
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

template <typename Tag>
struct ReflTypeTraits {
    using AnyFormatterType = AnyFormatter<Str>;
    using AnyHasherType    = AnyHasher<Str>;
    using AnyEqualType     = AnyEqual<Str>;
    // using ReflPathFormatter = ReflPathItemFormatter<Tag>;
};


template <typename Tag>
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
        Tag::field_name_type name;
        DESC_FIELDS(FieldName, (name));

        bool operator==(FieldName const& other) const {
            return name == other.name;
        }
    };

    struct Deref {
        DESC_FIELDS(Deref, ());
        bool operator==(Deref const& other) const { return true; }
    };

    ReflPathItem(const ReflPathItem& other) : kind(other.kind) {
        switch (kind) {
            case Kind::Index:
                new (&data.index) Index(other.data.index);
                break;
            case Kind::FieldName:
                new (&data.fieldName) FieldName(other.data.fieldName);
                break;
            case Kind::AnyKey:
                new (&data.anyKey) AnyKey(other.data.anyKey);
                break;
            case Kind::Deref:
                new (&data.deref) Deref(other.data.deref);
                break;
        }
    }

    void operator=(ReflPathItem const& other) {
        kind = other.kind;
        switch (kind) {
            case Kind::Index: data.index = other.data.index; break;
            case Kind::FieldName:
                data.fieldName = other.data.fieldName;
                break;
            case Kind::AnyKey: data.anyKey = other.data.anyKey; break;
            case Kind::Deref: data.deref = other.data.deref; break;
        }
    }

    ReflPathItem(const Index& idx) : kind(Kind::Index) {
        data.index = idx;
    }
    ReflPathItem(const FieldName& field) : kind(Kind::FieldName) {
        data.fieldName = field;
    }
    ReflPathItem(const AnyKey& key) : kind(Kind::AnyKey) {
        data.anyKey = key;
    }
    ReflPathItem(const Deref& ref) : kind(Kind::Deref) {
        data.deref = ref;
    }

    static ReflPathItem FromFieldName(Tag::field_name_type const& name) {
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

    union DataUnion {
        Index     index;
        FieldName fieldName;
        AnyKey    anyKey;
        Deref     deref;
        DataUnion() : index{Index{}} {}
        ~DataUnion() {}
    };

    ~ReflPathItem() {
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
    DESC_FIELDS(ReflPathItem, (data, kind));

    Kind      getKind() const { return kind; }
    Kind      kind;
    DataUnion data;

    using variant_enum_type = Kind;
    using variant_data_type = std::
        variant<Index, FieldName, AnyKey, Deref>;
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
        LOGIC_ASSERTION_CHECK(
            kind == k, "Expected kind {} but got {}", k, kind);
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


    bool operator==(ReflPathItem const& it) const {
        if (it.getKind() == getKind()) {
            switch (kind) {
                case Kind::AnyKey: return data.anyKey == it.data.anyKey;
                case Kind::FieldName:
                    return data.fieldName == it.data.fieldName;
                case Kind::Deref: return data.deref == it.data.deref;
                case Kind::Index: return data.index == it.data.index;
            }
        } else {
            return false;
        }
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


template <typename Tag>
struct ReflPathItemFormatter : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPathItem<Tag>& step, FormatContext& ctx) const {
        typename ReflTypeTraits<Tag>::AnyFormatterType anyFmt;
        if (step.isAnyKey()) {
            fmt_ctx(anyFmt(step.getAnyKey().key), ctx);
        } else {
            step.visit([&](auto const& it) { fmt_ctx(it, ctx); });
        }

        return fmt_ctx("", ctx);
    }
};


template <typename Tag>
struct std::formatter<ReflPathItem<Tag>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPathItem<Tag>& step, FormatContext& ctx) const {
        step.visit([&](auto const& it) { fmt_ctx(it, ctx); });
        return fmt_ctx("", ctx);
    }
};


template <typename Tag>
struct std::hash<ReflPathItem<Tag>> {
    std::size_t operator()(ReflPathItem<Tag> const& it) const noexcept {
        std::size_t result = 0;
        it.visit(overloaded{
            [&](ReflPathItem<Tag>::Deref) {},
            [&](ReflPathItem<Tag>::AnyKey value) {
                typename ReflTypeTraits<Tag>::AnyHasherType h;
                result = h(value.key);
            },
            [&](ReflPathItem<Tag>::Index value) {
                hax_hash_combine(result, value.index);
            },
            [&](ReflPathItem<Tag>::FieldName value) {
                hax_hash_combine(result, value.name);
            },
        });
        return result;
    }
};


template <typename Tag>
struct ReflPath {
    using Store = SmallVec<ReflPathItem<Tag>, 2>;
    Store path;
    DESC_FIELDS(ReflPath, (path));
    ReflPathItem<Tag> const& at(int idx) const { return path.at(idx); }

    using iterator = Vec<ReflPathItem<Tag>>::iterator;

    ReflPath() {}
    ReflPath(iterator begin, iterator end) : path{begin, end} {}
    ReflPath(Store path) : path{path} {}
    ReflPath(ReflPathItem<Tag> const& single) : path{{single}} {}

    bool isSingle() const { return path.size() == 1; }

    ReflPathItem<Tag> const& first() const { return path.at(0); }
    ReflPathItem<Tag> const& last() const { return path.back(); }

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

    Pair<ReflPathItem<Tag>, ReflPath> split() const {
        if (path.size() == 1) {
            return {path.front(), {}};
        } else {
            auto span = path.at(slice(1, 1_B));
            return Pair<ReflPathItem<Tag>, ReflPath>{
                path.front(), ReflPath{Store{span.begin(), span.end()}}};
        }
    }

    ReflPath addFieldName(Tag::field_name_type const& name) const {
        return add(ReflPathItem<Tag>{
            typename ReflPathItem<Tag>::FieldName{name}});
    }

    ReflPath add(ReflPath const& item) const {
        auto res = *this;
        res.path.append(item.path);
        return res;
    }

    ReflPath add(ReflPathItem<Tag> const& item) const {
        auto res = *this;
        res.path.push_back(item);
        return res;
    }

    bool empty() const { return path.empty(); }

    bool operator==(ReflPath const& other) const {
        return path.operator==(other.path);
    }

    template <typename Cmp>
    bool lessThan(ReflPath const& other, Cmp const& cmp) const {
        return path.lessThan(other.path, cmp);
    }

    bool operator<(ReflPath const& other) const {
        return path < other.path;
    }
};


template <typename Tag>
struct std::hash<ReflPath<Tag>> {
    std::size_t operator()(ReflPath<Tag> const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.path);
        return result;
    }
};

template <typename Tag>
struct ReflPathHasher {
    std::size_t operator()(ReflPath<Tag> const& it) const noexcept {
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
        ReflPath<Tag> const& lhs,
        ReflPath<Tag> const& rhs) const noexcept {
        std::size_t result = 0;

        typename ReflTypeTraits<Tag>::AnyEqualType anyEq;
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

template <typename Tag>
struct ReflPathFormatter : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPath<Tag>& step, FormatContext& ctx) const {
        ReflPathItemFormatter<Tag> fmt{};
        for (auto const& it : enumerator(step.path)) {
            if (!it.is_first()) { fmt_ctx(">>", ctx); }
            fmt.format(it.value(), ctx);
        }
        return fmt_ctx("", ctx);
    }
};

template <typename Tag>
struct std::formatter<ReflPath<Tag>> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ReflPath<Tag>& step, FormatContext& ctx) const {
        for (auto const& it : enumerator(step.path)) {
            if (!it.is_first()) { fmt_ctx(">>", ctx); }
            fmt_ctx(it.value(), ctx);
        }
        return fmt_ctx("", ctx);
    }
};

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
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        T const&                 value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isFieldName(), "{}", step.getKind());
        for_each_field_with_base_value<T>(
            value, [&]<typename B>(B const& base, auto const& ptr) {
                if (ReflTypeTraits<Tag>::InitFieldName(base, ptr)
                    == step.getFieldName().name) {
                    cb(value.*ptr.pointer);
                }
            });
    }


    static Vec<ReflPathItem<Tag>> subitems(T const& value) {
        Vec<ReflPathItem<Tag>> result;
        for_each_field_with_base_value(
            value, [&]<typename B>(B const& base, auto const& ptr) {
                result.push_back(ReflPathItem<Tag>::FromFieldName(
                    ReflTypeTraits<Tag>::InitFieldName(base, ptr)));
            });

        return result;
    }
};

template <typename K, typename V, typename Map, typename Tag>
struct ReflVisitorKeyValue {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Map const&               value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isAnyKey(), "{}", step.getKind());
        cb(value.at(step.getAnyKey().template get<K>()));
    }


    static Vec<ReflPathItem<Tag>> subitems(Map const& value) {
        Vec<ReflPathItem<Tag>> result;
        if constexpr (requires(K a, K b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            Vec<K> keys;
            for (auto const& [key, _] : value) { keys.push_back(key); }
            for (auto const& key : sorted(keys)) {
                result.push_back(ReflPathItem<Tag>::FromAnyKey(key));
            }
        } else {
            for (auto const& key : value.keys()) {
                result.push_back(ReflPathItem<Tag>::FromAnyKey(key));
            }
        }


        return result;
    }
};

template <typename T, typename Indexed, typename Tag>
struct ReflVisitorIndexed {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Indexed const&           value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        cb(value.at(step.getIndex().index));
    }


    static Vec<ReflPathItem<Tag>> subitems(Indexed const& value) {
        Vec<ReflPathItem<Tag>> result;
        for (int i = 0; i < value.size(); ++i) {
            result.push_back(ReflPathItem<Tag>::FromIndex(i));
        }

        return result;
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

    template <typename Func>
    static void visit(
        Unordered const&         value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        cb(getSorted(value).at(step.getIndex().index).get());
    }


    static Vec<ReflPathItem<Tag>> subitems(Unordered const& value) {
        Vec<ReflPathItem<Tag>> result;
        for (int i = 0; i < value.size(); ++i) {
            result.push_back(ReflPathItem<Tag>::FromIndex(i));
        }

        return result;
    }
};


template <typename T, typename Tag>
struct ReflVisitor<Opt<T>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Opt<T> const&            value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        cb(value.value());
    }


    static Vec<ReflPathItem<Tag>> subitems(Opt<T> const& value) {
        Vec<ReflPathItem<Tag>> result;
        if (value.has_value()) {
            result.push_back(ReflPathItem<Tag>::FromDeref());
        }

        return result;
    }
};

template <typename T, typename Tag>
struct ReflVisitor<std::shared_ptr<T>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::shared_ptr<T> const& value,
        ReflPathItem<Tag> const&  step,
        Func const&               cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(value.get() != nullptr, "");
        cb(*value.get());
    }


    static Vec<ReflPathItem<Tag>> subitems(
        std::shared_ptr<T> const& value) {
        Vec<ReflPathItem<Tag>> result;
        if (value.get() != nullptr) {
            result.push_back(ReflPathItem<Tag>::FromDeref());
        }

        return result;
    }
};

template <typename T, typename Tag>
struct ReflVisitor<std::unique_ptr<T>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::unique_ptr<T> const& value,
        ReflPathItem<Tag> const&  step,
        Func const&               cb) {
        LOGIC_ASSERTION_CHECK(step.isDeref(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(value.get() != nullptr, "");
        cb(*value.get());
    }


    static Vec<ReflPathItem<Tag>> subitems(
        std::unique_ptr<T> const& value) {
        Vec<ReflPathItem<Tag>> result;
        if (value.get() != nullptr) {
            result.push_back(ReflPathItem<Tag>::FromDeref());
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

template <typename... Args, typename Tag>
struct ReflVisitor<std::tuple<Args...>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        std::tuple<Args...> const& value,
        ReflPathItem<Tag> const&   step,
        Func const&                cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        apply_to_tuple(value, step.getIndex().index, cb);
    }


    static Vec<ReflPathItem<Tag>> subitems(
        std::tuple<Args...> const& value) {
        Vec<ReflPathItem<Tag>> result;
        for (int i = 0; i < std::tuple_size_v<std::tuple<Args...>>; ++i) {
            result.push_back(ReflPathItem<Tag>::FromIndex(i));
        }
        return result;
    }
};

template <typename T1, typename T2, typename Tag>
struct ReflVisitor<Pair<T1, T2>, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        Pair<T1, T2> const&      value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
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

    static Vec<ReflPathItem<Tag>> subitems(Pair<T1, T2> const& value) {
        Vec<ReflPathItem<Tag>> result;
        for (int i = 0; i < std::tuple_size_v<Pair<T1, T2>>; ++i) {
            result.push_back(ReflPathItem<Tag>::FromIndex(i));
        }
        return result;
    }
};

template <IsVariant T, typename Tag>
struct ReflVisitor<T, Tag> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        T const&                 value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        LOGIC_ASSERTION_CHECK(step.isIndex(), "{}", step.getKind());
        LOGIC_ASSERTION_CHECK(
            value.index() == step.getIndex().index, "{}", value.index());
        std::visit([&](auto const& it) { cb(it); }, value);
    }


    static Vec<ReflPathItem<Tag>> subitems(T const& value) {
        Vec<ReflPathItem<Tag>> result;
        result.push_back(ReflPathItem<Tag>::FromIndex(value.index()));
        return result;
    }
};

template <typename T, typename Tag>
struct ReflVisitor<Vec<T>, Tag> : ReflVisitorIndexed<T, Vec<T>, Tag> {};

template <typename T, typename Tag>
struct ReflVisitor<std::vector<T>, Tag>
    : ReflVisitorIndexed<T, std::vector<T>, Tag> {};

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
    template <typename Func>
    static void visit(
        T const&                 value,
        ReflPathItem<Tag> const& step,
        Func const&              cb) {
        throw refl_invalid_visit::init(
            fmt("Type {} cannot be indexed into using path step {}",
                demangle(typeid(T).name()),
                step));
    }


    static Vec<ReflPathItem<Tag>> subitems(T const& value) { return {}; }
};

template <typename Tag>
struct ReflVisitor<int, Tag> : ReflVisitorLeafType<int, Tag> {};

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
struct ReflVisitor<char const*, Tag>
    : ReflVisitorLeafType<char const*, Tag> {};

template <typename Tag>
struct ReflVisitor<std::string, Tag>
    : ReflVisitorLeafType<std::string, Tag> {};

template <typename Tag>
struct ReflVisitor<Str, Tag> : ReflVisitorLeafType<Str, Tag> {};

template <typename Tag>
struct ReflVisitor<std::nullptr_t, Tag>
    : ReflVisitorLeafType<std::nullptr_t, Tag> {};

template <typename T, typename Tag>
Vec<ReflPathItem<Tag>> reflSubItems(T const& item) {
    return ReflVisitor<T, Tag>::subitems(item);
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

template <typename T, typename Tag, typename Func>
void reflVisitAll(
    T const&                   value,
    ReflPath<Tag> const&       path,
    ReflRecursiveVisitContext& ctx,
    Func const&                cb) {
    cb(path, value);
    if (ctx.canRecurse(value)) {
        ctx.visit(value);
        for (auto const& step : ReflVisitor<T, Tag>::subitems(value)) {
            ReflVisitor<T, Tag>::visit(
                value, step, [&]<typename F>(F const& fieldValue) {
                    reflVisitAll<F>(fieldValue, path.add(step), ctx, cb);
                });
        }
    }
}

template <typename T, typename Func, typename Tag>
void reflVisitDirectItems(T const& value, Func const& cb) {
    for (auto const& step : ReflVisitor<T, Tag>::subitems(value)) {
        ReflVisitor<T, Tag>::visit(
            value, step, [&]<typename F>(F const& fieldValue) {
                cb(step, fieldValue);
            });
    }
}

template <typename T, typename Func, typename Tag>
void reflVisitPath(
    T const&             value,
    ReflPath<Tag> const& path,
    Func const&          cb) {
    if (path.empty()) {
        cb(value);
    } else {
        auto [head, tail] = path.split();
        ReflVisitor<T, Tag>::visit(
            value, head, [&]<typename F>(F const& fieldValue) {
                reflVisitPath<F>(fieldValue, tail, cb);
            });
    }
}
