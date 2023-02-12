#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Span.hpp>

#include <hstd/system/generator.hpp>

template <typename T, typename F>
Vec<Span<T const>> partition(
    const Vec<T>&  elements,
    Func<F(CR<T>)> callback) {
    Vec<Span<T const>> result;
    Span<T const>      currentSpan;
    F                  currentValue;
    T const*           max = &elements.back();
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
