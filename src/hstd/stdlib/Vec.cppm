module;

import hstd.system.all;
import hstd.stdlib.Slice;
import hstd.stdlib.Span;
import hstd.stdlib.sequtils;


export module hstd.stdlib.Vec;

export {
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
class Vec : public std::vector<T> {
  public:
    using Base = std::vector<T>;
    Vec(std::initializer_list<T> init) : std::vector<T>(init) {}
    Vec(Vec<T> const& init) : std::vector<T>(init) {}

    using Base::at;
    using Base::operator[];
    using Base::begin;
    using Base::end;
    using Base::insert;
    using Base::push_back;

    static Vec<T> FromValue(CR<Vec<T>> values) { return values; }


    int  size() const { return static_cast<int>(Base::size()); }
    bool empty() const { return size() == 0; }

    Vec() {}
    explicit Vec(int size) : std::vector<T>(size) {}
    Vec(int size, const T& value) : std::vector<T>(size, value) {}
    /// \brief Construct vector from the span of elements.
    ///
    /// \note Made explicit to make it harder to do accidental
    /// low-performance copies of the whole data.
    explicit Vec(CR<Span<T>> values)
        : std::vector<T>(values.begin(), values.end()) {}

    /// \brief Append elements from \arg other vector
    void append(CR<Vec<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    /// \brief copy multiple elements referred to by span to the fector
    void append(CR<std::span<T>> other) {
        insert(end(), other.begin(), other.end());
    }

    /// \brief  Pointwise comparison between vector and any other indexable
    /// container.
    template <typename Indexable>
    bool operator==(CR<Indexable> other) const {
        if (this->size() == other.size()) {
            for (int i = 0; i < size(); ++i) {
                if (at(i) != other.at(i)) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }

    Vec<T> operator+(CR<T> other) const {
        auto result = *this;
        result.push_back(other);
        return result;
    }

    Vec<T> operator+(CR<std::span<T>> other) const {
        auto result = *this;
        result.append(other);
        return result;
    }

    Vec<T> operator+(CR<Vec<T>> other) const {
        auto result = *this;
        result.append(other);
        return result;
    }

    /// \brief Implicit conversion to the base class
    operator Ref<std::vector<T>>() {
        return static_cast<std::vector<T>>(*this);
    }

    /// \brief implicit conversion to the base class
    operator CR<std::vector<T>>() const {
        return static_cast<std::vector<T>>(*this);
    }

    /// \brief Check if vector has enough elements to access index \arg idx
    bool has(int idx) const { return 0 <= idx && idx < size(); }
    bool has(BackwardsIndex idx) const { return has(size() - idx.value); }

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

    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(int index) {
        if (has(index)) {
            return at(index);
        } else {
            return std::nullopt;
        }
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(int index) const {
        if (has(index)) {
            return at(index);
        } else {
            return std::nullopt;
        }
    }

    /// \brief Get reference wrapper to a value at specified index or empty
    /// option if the index is out of range
    std::optional<Rw<T>> get(BackwardsIndex idx) {
        return get(index(idx));
    }

    /// \brief Overload for constant vector
    std::optional<CRw<T>> get(BackwardsIndex idx) const {
        return get(index(idx));
    }

    template <typename A, typename B>
    Span<T> operator[](CR<HSlice<A, B>> s) {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    template <typename A, typename B>
    Span<T> operator[](CR<HSlice<A, B>> s) const {
#ifdef DEBUG
        return at(s, true);
#else
        return at(s, false);
#endif
    }

    int index(BackwardsIndex idx) const {
        return this->size() - idx.value;
    }

    /// \brief Access vector value using backwards index, identical to
    /// `size() - <index value>`
    T& operator[](BackwardsIndex idx) { return (*this)[index(idx)]; }

    /// \brief 'at' operation for accessing value using backwards indexing,
    /// recommended for use as it unconiditionally does the bound checking
    T& at(BackwardsIndex idx) { return this->at(index(idx)); }

    T const& at(BackwardsIndex idx) const { return this->at(index(idx)); }

    void failEmpty() const {
        if (empty()) {
            throw std::out_of_range(
                "Operation does not work with an empty vector");
        }
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

    /// \brief Get last value and pop it out of the vector itself
    T pop_back_v() {
        // QUESTION use `std::move` and rvalue to eject elements?
        failEmpty();
        auto result = back();
        pop_back();
        return result;
    }

    /// \brief Last accessible index of the vector, useful for slicing etc.
    int high() const { return size() - 1; }

    /// \brief Find item in the vector using default `==` check
    int indexOf(CR<T> item) const { return index_of(*this, item); }
    /// \brief Check if vector contains item, using `==`. \note \(O(n)\)
    /// operation, so better used only on small vectors.
    bool contains(CR<T> item) const { return indexOf(item) != -1; }

    /// \brief Get span that extents for the whole vector content
    Span<T> toSpan() const {
        return Span<T>(const_cast<T*>(this->data()), size());
    }


    std::vector<T> const& toBase() const { return *this; }
};

static_assert(
    sizeof(Vec<int>) == sizeof(std::vector<int>),
    "Vector size must be identical");

/// \brief Vector formatting operator
template <typename T>
struct std::formatter<Vec<T>> : std::formatter<std::string> {
    using FmtType = Vec<T>;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("]", ctx);
    }
};

template <typename T>
struct std::formatter<std::vector<T>> : std::formatter<std::string> {
    using FmtType = std::vector<T>;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("[", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("]", ctx);
    }
};


template <typename T>
using CVec = CR<Vec<T>>;
}
