#pragma once

#include <sstream>
#include <variant>
#include <hstd/system/string_convert.hpp>

template <typename... Types>
using Variant = std::variant<Types...>;

// Does not conform to regular `ostream<<` implementation in order to avoid
// implicit conversion from value types. Not sure this can be circumvented
// by disallowing to-argument conversion in some way.
template <typename... Types>
QString variant_to_string(Variant<Types...> const& value) {
    QString     out;
    QTextStream os{&out};
    std::visit(
        [&os](const auto& value) {
            os << value;
            return 0;
        },
        value);
    return out;
}
