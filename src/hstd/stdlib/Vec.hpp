#pragma once

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <boost/container/small_vector.hpp>
#include <hstd/system/exceptions.hpp>


#include <vector>
#include <span>

namespace hstd {

template <typename T>
concept IsIterableRange = requires(T t) {
    { std::begin(t) } -> std::input_or_output_iterator;
    { std::end(t) } -> std::input_or_output_iterator;
};

template <typename LhsIndexable, typename RhsIndexable, typename Cmp>
bool itemwise_less_than(
    LhsIndexable const& lhs,
    RhsIndexable const& rhs,
    Cmp const&          cmp) {
    for (int i = 0; i < std::min(
                        static_cast<int>(lhs.size()),
                        static_cast<int>(rhs.size()) //
                    );
         ++i) {
        if (cmp(lhs.at(i), rhs.at(i))) { return true; }
    }
    return lhs.size() < rhs.size();
}

template <typename T, typename Container>
struct IndexedBase : public CRTP_this_method<Container> {
    using CRTP_this_method<Container>::_this;

    /// \brief helper assertion to fail if the vector is empty.
    void failEmpty() const {
        if (_this()->empty()) {
            throw out_of_range_error::init(
                "Operation does not work with an empty vector");
        }
    }

    void checkIdx(int idx) const {
        if (idx < 0) {
            throw out_of_range_error::init(
                "Operation does not support negative indices");
        } else if (!(idx < _this()->size())) {
            throw out_of_range_error::init(
                std::string("Value out of range. idx < size(): ")
                + std::to_string(idx) + std::string(" !< ")
                + std::to_string(_this()->size()));
        }
    }

    /// \brief Last accessible index of the vector, useful for slicing etc.
    int high() const { return _this()->size() - 1; }

    bool empty() const { return _this()->size() == 0; }

    /// \brief  Pointwise comparison between vector and any other indexable
    /// container.
    template <typename Indexable>
    bool operator==(CR<Indexable> other) const {
        if (_this()->size() == other.size()) {
            for (int i = 0; i < _this()->size(); ++i) {
                if (_this()->at(i) != other.at(i)) { return false; }
            }
            return true;
        } else {
            return false;
        }
    }

    /// \brief Check if vector has enough elements to access index \arg idx
    bool has(int idx) const { return 0 <= idx && idx < _this()->size(); }
    bool has(BackwardsIndex idx) const {
        return _this()->has(_this()->size() - idx.value);
    }


    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(int index) {
        if (_this()->has(index)) {
            return _this()->at(index);
        } else {
            return std::nullopt;
        }
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(int index) const {
        if (_this()->has(index)) {
            return _this()->at(index);
        } else {
            return std::nullopt;
        }
    }

    std::optional<T> get_copy(int index) const {
        if (_this()->has(index)) {
            return _this()->at(index);
        } else {
            return std::nullopt;
        }
    }

    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(BackwardsIndex idx) {
        return _this()->get(_this()->index(idx));
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(BackwardsIndex idx) const {
        return _this()->get(_this()->index(idx));
    }

    std::optional<T> get_copy(BackwardsIndex idx) const {
        return _this()->get_copy(_this()->index(idx));
    }

    template <typename A, typename B>
    Span<T> operator[](CR<HSlice<A, B>> s) {
#ifdef DEBUG
        return _this()->at(s, true);
#else
        return _this()->at(s, false);
#endif
    }

    template <typename A, typename B>
    Span<T> operator[](CR<HSlice<A, B>> s) const {
#ifdef DEBUG
        return _this()->at(s, true);
#else
        return _this()->at(s, false);
#endif
    }

    int index(BackwardsIndex idx) const {
        return _this()->size() - idx.value;
    }

    /// \brief Access vector value using backwards index, identical to
    /// `size() - <index value>`
    T& operator[](BackwardsIndex idx) { return (*_this())[index(idx)]; }

    /// \brief 'at' operation for accessing value using backwards indexing,
    /// recommended for use as it unconiditionally does the bound checking
    T& at(BackwardsIndex idx) { return _this()->at(_this()->index(idx)); }

    T const& at(BackwardsIndex idx) const {
        return _this()->at(index(idx));
    }

    T const& at_or(int idx, T const& fallback) const {
        if (_this()->has(idx)) {
            return _this()->at(idx);
        } else {
            return fallback;
        }
    }


    /// \brief Append elements from \arg other vector
    void append(CR<Container> other) {
        _this()->append(other.begin(), other.end());
    }

    /// \brief copy multiple elements referred to by span to the fector
    void append(CR<std::span<T>> other) {
        _this()->append(other.begin(), other.end());
    }


    T const& at_or(BackwardsIndex idx, T const& fallback) const {
        return _this()->at_or(_this()->index(idx), fallback);
    }

    template <typename Indexable>
    bool operator<(CR<Indexable> other) const {
        return lessThan(other, std::less<T>{});
    }

    template <typename Indexable, typename Cmp>
    bool lessThan(CR<Indexable> other, Cmp const& cmp) const {
        return itemwise_less_than(*_this(), other, cmp);
    }

    Container operator+(CR<T> other) const {
        auto result = *_this();
        result.push_back(other);
        return result;
    }

    Container operator+(CR<std::span<T>> other) const {
        auto result = *_this();
        result.append(other);
        return result;
    }

    Container operator+(CR<Container> other) const {
        auto result = *_this();
        result.append(other);
        return result;
    }

    /// \brief Get last value and pop it out of the vector itself
    T pop_back_v() {
        // QUESTION use `std::move` and rvalue to eject elements?
        _this()->failEmpty();
        auto result = _this()->back();
        _this()->pop_back();
        return result;
    }


    /// \brief Return the mutable reference to element at index, if the
    /// vector does not have enough elements, resize it to fit.
    T& resize_at(int idx) {
        if (_this()->high() < idx) { _this()->resize(idx + 1); }
        return _this()->at(idx);
    }

    /// \brief resize_at overload with default value to fill in
    T& resize_at(int idx, T const& value) {
        if (_this()->high() < idx) { _this()->resize(idx + 1, value); }
        return _this()->at(idx);
    }


    /// \brief Find item in the vector using default `==` check
    int indexOf(CR<T> item) const { return index_of(*_this(), item); }
    /// \brief Check if vector contains item, using `==`. \note \(O(n)\)
    /// operation, so better used only on small vectors.
    bool contains(CR<T> item) const {
        return _this()->indexOf(item) != -1;
    }

    int push_back_idx(CR<T> item) {
        int result = _this()->size();
        _this()->push_back(item);
        return result;
    }
};

/// \brief Derivation of the standard vector with better API for quick
/// operations. and added overloads for slicing and backwards indexing.
///
/// Data-structure-wise should be identical to the regular vector, but
/// provides some convienience operators such as `[]` for slices, *integer*
/// size (less `size() - 1` bugs), more extensive size checking for
/// accessors (no more `back()`-induced dangling references that fail five
/// layers down the call stack). Easier concatenation etc.
///
/// Performance was taken in consideration for these overloads, but only as
/// long as it did not hinder the useful functionality itself -- you can
/// append two vectors, check if it `contains()` someting and so on, even
/// though these operations are \(O(n)\)
template <typename T>
class Vec
    : public std::vector<T>
    , public IndexedBase<T, Vec<T>> {
  public:
    using Base = std::vector<T>;
    using API  = IndexedBase<T, Vec<T>>;

    using API::operator[];
    using API::append;
    using API::at;
    using API::at_or;
    using API::lessThan;
    using API::operator<;
    using API::checkIdx;
    using API::contains;
    using API::empty;
    using API::failEmpty;
    using API::get;
    using API::get_copy;
    using API::has;
    using API::high;
    using API::indexOf;
    using API::pop_back_v;
    using Base::Base;
    using Base::begin;
    using Base::end;
    using Base::insert;
    using Base::push_back;

    Vec(std::initializer_list<T> init) : std::vector<T>(init) {}
    Vec(Vec<T> const& init) : std::vector<T>(init) {}
    Vec(int size, const T& value) : std::vector<T>(size, value) {}
    Vec() {}
    explicit Vec(int size) : std::vector<T>(size) {}

    static Vec<T> FromValue(CR<Vec<T>> values) { return values; }
    int           size() const { return static_cast<int>(Base::size()); }


    /// \brief Construct vector from the span of elements.
    ///
    /// \note Made explicit to make it harder to do accidental
    /// low-performance copies of the whole data.
    explicit Vec(CR<Span<T>> values)
        : std::vector<T>(values.begin(), values.end()) {}

    /// \brief Implicit conversion to the base class
    operator Ref<std::vector<T>>() {
        return static_cast<std::vector<T>>(*this);
    }

    /// \brief implicit conversion to the base class
    operator CR<std::vector<T>>() const {
        return static_cast<std::vector<T>>(*this);
    }

    template <typename Iter>
    void append(Iter begin, Iter end) {
        insert(this->end(), begin, end);
    }


    T const& at(int idx) const {
        checkIdx(idx);
        return Base::at(idx);
    }

    T& at(int idx) {
        checkIdx(idx);
        return Base::at(idx);
    }

    T const& operator[](int idx) const {
        checkIdx(idx);
        return Base::operator[](idx);
    }

    T& operator[](int idx) {
        checkIdx(idx);
        return Base::operator[](idx);
    }


    /// \brief Access span of elements in mutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(this->data() + start, end - start + 1);
    }

    /// \brief  Access span of elements in immutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(
            const_cast<T*>(this->data() + start), end - start + 1);
    }

    /// \brief Reference to the last element. Checks for proper array size
    T& back() {
        // It will cause segfault anyway, just in a way that you least
        // expect, so easier to check things here than get absolutely
        // destroyed by some bug later on.
        failEmpty();
        return Base::back();
    }

    /// \brief constant reference to the last element, checks for vector
    /// size
    T const& back() const {
        failEmpty();
        return Base::back();
    }

    /// \brief Override of the 'back' accessor of the standard vector, but
    /// with check for proper size
    void pop_back() {
        failEmpty();
        Base::pop_back();
    }


    /// \brief Get span that extents for the whole vector content
    Span<T> toSpan() const {
        return Span<T>(const_cast<T*>(this->data()), size());
    }


    std::vector<T> const& toBase() const { return *this; }


    template <IsIterableRange Range>
    static void Splice_Impl1(std::vector<T>& result, Range&& range) {
        std::copy(
            std::begin(range),
            std::end(range),
            std::back_inserter(result));
    }

    static void Splice_Impl1(Vec<T>& result, T const& arg) {
        result.push_back(arg);
    }

    static void Splice_Impl1(Vec<T>& result, T&& arg) {
        result.push_back(std::forward<T>(arg));
    }

    static void Splice_Impl1(Vec<T>& result, Vec<T> const& arg) {
        result.append(std::forward<Vec<T>>(arg));
    }

    static void Splice_Impl1(Vec<T>& result, Vec<T>&& arg) {
        result.append(arg);
    }

    static void Splice_Impl(Vec<T>& result) {}

    template <typename... Rest>
    static void Splice_Impl(
        Vec<T>&  result,
        Vec<T>&& first,
        Rest&&... rest) {
        Splice_Impl1(result, std::forward<Vec<T>>(first));
        Splice_Impl(result, std::forward<Rest>(rest)...);
    }

    template <typename First, typename... Rest>
    static void Splice_Impl(
        Vec<T>& result,
        First&& first,
        Rest&&... rest) {
        Splice_Impl1(result, std::forward<First>(first));
        Splice_Impl(result, std::forward<Rest>(rest)...);
    }

    template <typename... Args>
    static Vec<T> Splice(Args&&... args) {
        Vec<T> result;
        Splice_Impl(result, std::forward<Args>(args)...);
        return result;
    }
};

template <typename T, int StartSize>
struct SmallVec
    : public boost::container::small_vector<T, StartSize>
    , public IndexedBase<T, SmallVec<T, StartSize>> {
    using Base = boost::container::small_vector<T, StartSize>;
    using API  = IndexedBase<T, SmallVec<T, StartSize>>;

    using API::operator[];
    using API::append;
    using API::at;
    using API::at_or;
    using API::lessThan;
    using API::operator<;
    using API::checkIdx;
    using API::contains;
    using API::empty;
    using API::failEmpty;
    using API::get;
    using API::get_copy;
    using API::has;
    using API::high;
    using API::indexOf;
    using API::pop_back_v;
    using Base::Base;
    using Base::begin;
    using Base::end;
    using Base::insert;
    using Base::push_back;

    SmallVec(std::initializer_list<T> init) : Base(init) {}
    SmallVec(SmallVec<T, StartSize> const& init) : Base(init) {}
    SmallVec(int size, const T& value) : Base(size, value) {}
    SmallVec() {}
    explicit SmallVec(int size) : Base(size) {}

    T const& operator[](int idx) const {
        checkIdx(idx);
        return Base::operator[](idx);
    }

    T& operator[](int idx) {
        checkIdx(idx);
        return Base::operator[](idx);
    }

    T const& at(int idx) const {
        checkIdx(idx);
        return Base::at(idx);
    }

    T& at(int idx) {
        checkIdx(idx);
        return Base::at(idx);
    }

    /// \brief constant reference to the last element, checks for vector
    /// size
    T const& back() const {
        failEmpty();
        return Base::back();
    }

    /// \brief Override of the 'back' accessor of the standard vector, but
    /// with check for proper size
    void pop_back() {
        failEmpty();
        Base::pop_back();
    }

    template <typename Iter>
    void append(Iter begin, Iter end) {
        insert(this->end(), begin, end);
    }

    int size() const { return static_cast<int>(Base::size()); }

    /// \brief Access span of elements in mutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(this->data() + start, end - start + 1);
    }

    /// \brief  Access span of elements in immutable vector
    template <typename A, typename B>
    Span<T> at(CR<HSlice<A, B>> s, bool checkRange = true) const {
        const auto [start, end] = getSpan(size(), s, checkRange);
        return Span<T>(
            const_cast<T*>(this->data() + start), end - start + 1);
    }
};

static_assert(
    sizeof(Vec<int>) == sizeof(std::vector<int>),
    "Vector size must be identical");

template <typename T, typename Container>
struct std_item_iterator_formatter : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(Container const& p, FormatContext& ctx)
        const {
        fmt_ctx("[", ctx);
        bool first = true;
        for (const auto& value : p) {
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("]", ctx);
    }
};


template <typename Indexable>
struct std_indexable_hash {
    std::size_t operator()(Indexable const& it) const noexcept {
        std::size_t result = 0;
        for (int i = 0; i < it.size(); ++i) {
            hax_hash_combine(result, i);
            hax_hash_combine(result, it.at(i));
        }
        return result;
    }
};


template <typename T>
using CVec = CR<Vec<T>>;

template <typename T>
struct value_metadata<Vec<T>> {
    static bool isEmpty(Vec<T> const& value) { return value.empty(); }
    static std::string typeName() {
        return std::string{"Vec<"} + value_metadata<T>::typeName()
             + std::string{">"};
    }
};

} // namespace hstd

/// \brief Vector formatting operator
template <typename T>
struct std::formatter<hstd::Vec<T>>
    : hstd::std_item_iterator_formatter<T, hstd::Vec<T>> {};

template <typename T>
struct std::formatter<std::vector<T>>
    : hstd::std_item_iterator_formatter<T, std::vector<T>> {};

template <typename T, int Size>
struct std::formatter<hstd::SmallVec<T, Size>>
    : hstd::std_item_iterator_formatter<T, hstd::SmallVec<T, Size>> {};


template <typename T>
struct std::hash<hstd::Vec<T>> : hstd::std_indexable_hash<hstd::Vec<T>> {};

template <typename T, int Size>
struct std::hash<hstd::SmallVec<T, Size>>
    : hstd::std_indexable_hash<hstd::SmallVec<T, Size>> {};
