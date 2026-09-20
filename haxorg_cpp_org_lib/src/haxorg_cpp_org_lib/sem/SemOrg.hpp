#pragma once

#include <haxorg_cpp_org_lib/parse/OrgTypes.hpp>
#include <hstd_cpp_lib/stdlib/Func.hpp>
#include <hstd_cpp_lib/stdlib/Str.hpp>
#include <hstd_cpp_lib/stdlib/Time.hpp>
#include <hstd_cpp_lib/stdlib/containers/Opt.hpp>
#include <hstd_cpp_lib/stdlib/containers/Variant.hpp>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>

#include <boost/describe.hpp>
#include <hstd_cpp_lib/system/macros.hpp>

#include <haxorg_cpp_org_lib/sem/SemOrgBase.hpp>
#include <haxorg_cpp_org_lib/sem/SemOrgTypes.hpp>

namespace org::sem {
template <typename T>
concept NotOrg = !(
    std::derived_from<typename remove_sem_org<T>::type, sem::Org>
    || std::derived_from<T, Org>);

/// \brief  Compile-time check whether the element is an org-mode node or
/// an org-mode ID
template <typename T>
concept IsOrg = std::derived_from<typename remove_sem_org<T>::type, sem::Org>;

}; // namespace org::sem
