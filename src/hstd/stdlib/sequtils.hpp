#pragma once

#include <algorithm>

template <typename T, typename Ref>
struct EnumerateState {

    class iterator {
      private:
        T*  iter;
        int index = 0;

      public:
        typedef std::forward_iterator_tag iterator_category;

        typedef Pair<int, Ref>  value_type;
        typedef Pair<int, Ref>* pointer;
        typedef Pair<int, Ref>& reference;
        typedef std::ptrdiff_t  difference_type;

        iterator(T* it) : iter(it) {}

        Pair<int, Ref> operator*() { return {index, *(*iter)}; }

        iterator& operator++() {
            ++index;
            ++(*iter);
            return *this;
        }

        bool operator!=(const iterator& other) {
            return (*iter) != (*other.iter);
        }
    };


    iterator begin() { return iterator(&beginIterator); }
    iterator end() { return iterator(&endIterator); }

    EnumerateState(T begin, T end)
        : beginIterator(begin), endIterator(end) {}

  private:
    T beginIterator;
    T endIterator;
};

template <typename T>
EnumerateState<typename T::iterator, typename T::iterator::value_type> enumerate(
    Ref<T> value) {
    return EnumerateState<
        typename T::iterator,
        typename T::iterator::value_type>(value.begin(), value.end());
}


template <typename T>
EnumerateState<typename T::const_iterator, typename T::const_iterator::value_type> enumerate(
    CR<T> value) {
    return EnumerateState<
        typename T::const_iterator,
        typename T::const_iterator::value_type>(
        value.cbegin(), value.cend());
}


template <typename T, typename Container>
int index_of(CR<Container> container, CR<T> item) {
    auto pos = std::find(container.begin(), container.end(), item);
    if (pos != container.end()) {
        return std::distance(pos, container.begin());
    } else {
        return -1;
    }
}


template <typename T, typename Pred>
bool all_of(CR<T> seq, CR<Pred> pr) {
    return std::all_of(seq.begin(), seq.end(), pr);
}
