#pragma once

#include <string.h>

#include <types/enums.hpp>
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/basic_templates.hpp>

namespace org_impl {
#define IN_NAMESPACE
#include <autogen_enum_help.cpp>
#undef IN_NAMESPACE
} // namespace org_impl

#include <autogen_enum_help.cpp>
