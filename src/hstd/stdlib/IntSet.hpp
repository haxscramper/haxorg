#pragma once

#include <bitset>

#include <hstd/system/all.hpp>
#include <hstd/stdlib/Slice.hpp>
#include <hstd/stdlib/SetCommon.hpp>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/aux_templates.hpp>

template <typename T, typename InT>
concept ConvertibleToSet
    = (std::same_as<std::remove_cvref_t<InT>, T> //
       || std::same_as<std::remove_cvref_t<InT>, Slice<T>>);

template <typename T, typename... U>
concept AllConvertibleToSet = (ConvertibleToSet<T, U> && ...);

template <typename T>
T value_from_bitset_index(int index);

template <typename T>
T value_from_bitset_index(int index) {
    return static_cast<T>(index);
}

/*!
\brief Packet set of integral values

This type is mostly intended to be used types that have enum-like meaning
(regular enums, characters, small "state number" integers) instead of a
more general set solution.

This means that the API has been optimized for things like

```cpp
enum SomeFlags { flag1, flag2, flag3 };
IntSet<SomeFlags> flag;
flag.incl(flag1);
if (flag.contains(flag2)) {
  // do something
}
```

*/
template <typename T>
    requires(sizeof(T) <= sizeof(unsigned short))
// TODO explicitly specify size of the integral set and allow to offset the
// range of values in one direction or another. In some cases only a small
// subset of values from `low<T>..high<T>` need to be stored in the set,
// everything else is not needed. For example, I want to store values only
// in range of `-200..-9000`, but I want to use integer to avoid constant
// conversions all over the place. Or I'm using `char` sets, but I don't
// want to pay for the full size of the unicode code point.
struct IntSet : public SetBase<IntSet<T>, T> {
    // constrain the size of the object to avoid blowing up the set size.
    // 2-byte value has 8192 possible states and they all must be encoded
    // into the bitset, creating an 8kb object. 3 bytes will have a size of
    // 16777216 and I've decided it is a bit over the top for bitset. Maybe
    // in the future I will dispatch into different implementation bases
    // depending on the size/type of the value, but for now this check is
    // added purely for footgun reasons.
  private:
    constexpr static inline std::size_t toIdx(CR<T> value) {
        return value_domain<T>::ord(value);
    }

    constexpr void buildSet(Ref<IntSet<T>> result) {}

    template <typename ValueT>
    constexpr void buildSet(Ref<IntSet<T>> result, CR<ValueT> value)
        requires ConvertibleToSet<T, ValueT>
    {
        result.incl(value);
    }

    // Helper method to recurse into constructor argument list
    template <typename Value, typename... Args>
    constexpr void buildSet(
        Ref<IntSet<T>> result,
        CR<Value>      value,
        Args&&... tail)
        requires AllConvertibleToSet<T, Args...>
              && ConvertibleToSet<T, Value>
    {
        result.incl(value);
        buildSet(result, tail...);
    }


  public:
    using API = SetBase<IntSet<T>, T>;
    using API::excl;
    using API::incl;
    using API::operator-;
    using API::operator|;
    using API::operator+;
    using API::operator<;
    using API::operator<=;

    using BitsetT = std::bitset<pow_v<2, 8 * sizeof(T)>::res>;
    BitsetT values;

    constexpr bool contains(CR<T> value) const {
        return values.test(toIdx(value));
    }
    /// Check if one set is a proper subset of another -- \arg other
    /// contains all the values.
    constexpr bool contains(CR<IntSet<T>> other) const {
        return ((values & other.values) == other.values);
    }


    constexpr void incl(CR<IntSet<T>> other) { values |= other.values; }
    constexpr void excl(CR<IntSet<T>> other) { values &= ~other.values; }
    constexpr void incl(CR<T> value) { values.set(toIdx(value)); }
    constexpr void excl(CR<T> value) { values.reset(toIdx(value)); }

    bool operator==(CR<IntSet<T>> other) const {
        return values == other.values;
    }

    IntSet<T> operator^(CR<IntSet<T>> other) const {
        IntSet<T> result;
        result.values = this->values ^ other.values;
        return result;
    }

    IntSet<T> operator&(CR<IntSet<T>> other) const {
        IntSet<T> result;
        result.values = this->values & other.values;
        return result;
    }

    /// Return complement of the set that contains all values that were not
    /// placed in the original set.
    IntSet<T> operator~() { return {.values = ~values}; }

    int  size() const { return values.count(); }
    bool empty() const { return size() == 0; }

    /// Variadic constructor for the set type. It accepts only types that
    /// can be directly converted to the set
    template <typename... Args>
    constexpr IntSet(Args&&... args)
        requires AllConvertibleToSet<T, Args...>
    {
        buildSet(*this, args...);
    }

    class iterator {
      private:
        std::size_t    index;
        BitsetT const* base;

      public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef T*                        pointer;
        typedef T&                        reference;
        typedef std::ptrdiff_t            difference_type;


        iterator(std::size_t _index, BitsetT const* _base)
            : index(_index), base(_base) {
            // If starting position is empty, move over to the required
            // element.
            if (index < base->size() && !base->test(index)) {
                operator++();
            }
        }

        T operator*() { return value_from_bitset_index<T>(index); }

        iterator& operator++() {
            // If current value is ok, step over it once
            if (index < base->size() && base->test(index)) {
                ++index;
            }
            // Otherwise step over all empty values
            while (index < base->size() && !base->test(index)) {
                ++index;
            }
            return *this;
        }

        bool operator!=(const iterator& other) {
            return index != other.index;
        }
    };

    iterator begin() { return iterator(0, &values); }
    iterator end() { return iterator(values.size(), &values); }
    iterator begin() const { return iterator(0, &values); }
    iterator end() const { return iterator(values.size(), &values); }
};


template <typename T>
struct std::formatter<IntSet<T>> : std::formatter<std::string> {
    using FmtType = IntSet<T>;
    template <typename FormatContext>
    FormatContext::iterator format(FmtType const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        fmt.format("{", ctx);
        fmt.format(join(", ", p), ctx);
        return fmt.format("}", ctx);
    }
};
