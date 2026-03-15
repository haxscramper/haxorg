#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/api/ParseContext.hpp>
#include <wrappers/c/haxorg_c_api.h>
#include <hstd/stdlib/RangeSegmentation.hpp>
#include <haxorg/serde/SemOrgCereal.hpp>

template <typename ReturnType, typename Func, typename... Args>
ReturnType convert_cpp_execution(
    Func const& func,
    OrgContext* ctx,
    Args const&... args) {}


template <typename BaseType, typename WrappedType>
void execute_destroy(WrappedType* type) {}
