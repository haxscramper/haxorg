#pragma once

#include <sstream>
#include <swl/variant.hpp>
#include <hstd/system/string_convert.hpp>

template <typename... Types>
using Variant = swl::variant<Types...>;

// Does not conform to regular `ostream<<` implementation in order to avoid
// implicit conversion from value types. Not sure this can be circumvented
// by disallowing to-argument conversion in some way.
template <typename... Types>
QString variant_to_string(Variant<Types...> const& value) {
    QString     out;
    QTextStream os{&out};
    swl::visit(
        [&os](const auto& value) {
            os << value;
            return 0;
        },
        value);
    return out;
}
