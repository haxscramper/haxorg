#pragma once

#include <hstd_cpp_lib/stdlib/Time.hpp>
#include <hstd_cpp_lib/stdlib/algorithms/reflection/reflection_visitor.hpp>

namespace hstd {

template <typename Tag>
struct ReflVisitor<cctz::civil_second, Tag>
    : ReflVisitorLeafType<cctz::civil_second, Tag> {};

template <typename Tag>
struct ReflVisitor<cctz::time_zone, Tag> : ReflVisitorLeafType<cctz::time_zone, Tag> {};

} // namespace hstd
