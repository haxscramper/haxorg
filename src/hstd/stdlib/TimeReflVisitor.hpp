#pragma once

#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/reflection_visitor.hpp>

namespace hstd {

template <typename Tag>
struct ReflVisitor<cctz::civil_second, Tag>
    : ReflVisitorLeafType<cctz::civil_second, Tag> {};

template <typename Tag>
struct ReflVisitor<cctz::time_zone, Tag>
    : ReflVisitorLeafType<cctz::time_zone, Tag> {};

} // namespace hstd
