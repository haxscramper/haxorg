#pragma once

#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/strutils.hpp>

namespace hstd::log {
template <hstd::DescribedRecord Rec>
hstd::log::log_record log_described_record(
    Rec const&  items,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION(),
    char const* file     = __builtin_FILE()) {
    auto res = ::hstd::log::log_record{}.set_callsite(line, function, file);
    res.fmt_message("{}:", hstd::value_metadata<Rec>::typeName());

    int field_name_align = 0;

    hstd::for_each_field_value_with_bases(
        items, [&](char const* fieldName, auto const& value) {
            field_name_align = std::max<int>(
                field_name_align, std::string_view{fieldName}.size());
        });


    hstd::for_each_field_value_with_bases(
        items, [&](char const* fieldName, auto const& value) {
            res.fmt_message(
                "\n  {} = {}",
                hstd::left_aligned(fieldName, field_name_align),
                hstd::escape_literal(hstd::fmt1(format_logger_argument1(value))));
        });

    return res;
}

} // namespace hstd::log
