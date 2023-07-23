#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Func.hpp>

#include <hstd/system/generator.hpp>


/// \brief In-place reverse of the vector content
template <typename T>
void reverse(Vec<T>& vec) {
    std::reverse(vec.begin(), vec.end());
}

/// \brief In-place sort of the vector content
template <typename T>
void sort(Vec<T>& vec, Func<bool(CR<T>, CR<T>)> cmp) {
    std::sort(vec.begin(), vec.end(), cmp);
}

/// \brief Return reversed copy of the vector
template <typename T>
Vec<T> reversed(CR<Vec<T>> vec) {
    Vec<T> result = vec;
    reverse(result);
    return result;
}

/// \brief Return sorted copy of the vector
template <typename T>
Vec<T> sorted(CR<Vec<T>> vec, Func<bool(CR<T>, CR<T>)> cmp) {
    Vec<T> result = vec;
    sort(result, cmp);
    return result;
}

template <typename T>
Vec<T> sorted(CR<Vec<T>> vec) {
    Vec<T> result = vec;
    sort(result, [](CR<T> lhs, CR<T> rhs) { return lhs < rhs; });
    return result;
}


template <typename T, typename F>
auto map(T const& vec, F cb) {
    Vec<decltype(cb(vec[0]))> result;
    for (const auto& it : vec) {
        result.push_back(cb(it));
    }
    return result;
}

template <typename T, typename F>
Vec<Span<T const>> partition(
    const Vec<T>&  elements,
    Func<F(CR<T>)> callback) {
    Vec<Span<T const>> result;
    if (!elements.empty()) {
        Span<T const> currentSpan;
        F             currentValue;
        T const*      max = &elements.back();

        for (int i = 0; i < elements.size(); ++i) {
            F newValue = callback(elements[i]);
            if (currentSpan.empty() || currentValue != newValue) {
                if (!currentSpan.empty()) {
                    result.push_back(currentSpan);
                }
                currentSpan  = elements[slice(i, i)];
                currentValue = newValue;
            } else {
                currentSpan.moveEnd(1, max);
            }
        }
        if (!currentSpan.empty()) {
            result.push_back(currentSpan);
        }
    }
    return result;
}

template <typename A, typename B>
generator<Pair<typename A::value_type const*, typename B::value_type const*>> carthesian(
    CR<A> lhs,
    CR<B> rhs) {
    for (const auto& lhsIt : lhs) {
        for (const auto& rhsIt : rhs) {
            co_yield {&lhsIt, &rhsIt};
        }
    }
}
