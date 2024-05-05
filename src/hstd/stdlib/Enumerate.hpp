#pragma once

#include <iterator>
#include <algorithm>

template <typename Iter>
class enumerator_impl {
  public:
    struct enumerate_iterator {
        using it_type = typename std::iterator_traits<
            Iter>::iterator_category;

        using it_reference = typename std::iterator_traits<
            Iter>::reference;

        int  idx;
        Iter it;
        int  skip_first = 0;
        int  skip_last  = 0;
        int  base_size  = 0;

        struct item {
            enumerate_iterator const& iterator_ref;

            bool         is_first() const { return index() == 0; }
            bool         is_last() const { return index() == size() - 1; }
            int          index() const { return iterator_ref.idx; }
            it_reference value() const { return *iterator_ref.it; }
            it_reference value() { return *iterator_ref.it; }

            int size() const {
                return iterator_ref.base_size - iterator_ref.skip_first
                     - iterator_ref.skip_last;
            }

            void check_offset(int offset) {
                int pos = index() + offset;
                if (pos < 0 || size() <= pos) {
                    throw std::domain_error(
                        "Current index - offset put the value outside of "
                        "the iteration range");
                }
            }

            it_reference prev(int offset = 1) const {
                check_offset(offset);
                return *(iterator_ref.it - offset);
            }

            it_reference next(int offset = 1) const {
                check_offset(offset);
                return *(iterator_ref.it + offset);
            }

            it_reference prev(int offset = 1) {
                check_offset(offset);
                return *(iterator_ref.it - offset);
            }

            it_reference next(int offset = 1) {
                check_offset(offset);
                return *(iterator_ref.it + offset);
            }


            int base_index() const {
                return index() + iterator_ref.skip_first;
            }
        };

        item operator*() const { return item{*this}; }

        enumerate_iterator& operator++() {
            ++it;
            ++idx;
            return *this;
        }

        bool operator!=(const enumerate_iterator& other) const {
            return it != other.it;
        }
    };

  private:
    Iter base_begin;
    Iter base_end;
    int  skip_first_base = 0;
    int  skip_last_base  = 0;

  public:
    enumerator_impl(Iter begin, Iter end)
        : base_begin(begin), base_end(end) {}

    enumerator_impl skip_first(int n) {
        skip_first_base = n;
        return *this;
    }

    enumerator_impl skip_last(int n) {
        skip_last_base = n;
        return *this;
    }

    int base_size() const { return std::distance(base_begin, base_end); }

    enumerate_iterator begin() {
        auto start   = base_begin;
        int  advance = std::clamp(skip_first_base, 0, base_size());
        std::advance(start, advance);
        return enumerate_iterator{
            .it         = start,
            .idx        = 0,
            .skip_first = skip_first_base,
            .skip_last  = skip_last_base,
            .base_size  = base_size(),
        };
    }

    enumerate_iterator end() {
        auto end = base_end;
        std::advance(end, -std::clamp(skip_last_base, 0, base_size()));
        return enumerate_iterator{
            .it         = end,
            .idx        = -1,
            .skip_first = skip_first_base,
            .skip_last  = skip_last_base,
            .base_size  = base_size(),
        };
    }
};

template <typename Sequence>
enumerator_impl<typename Sequence::const_iterator> enumerator(
    Sequence const& it) {
    return enumerator_impl<typename Sequence::const_iterator>(
        std::begin(it), std::end(it));
}
