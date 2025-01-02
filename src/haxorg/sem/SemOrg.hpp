#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Func.hpp>
#include <haxorg/parse/OrgTypes.hpp>

#include <boost/describe.hpp>
#include <hstd/system/macros.hpp>
#include <functional>


#include <haxorg/sem/SemOrgBase.hpp>

//#include <haxorg/sem/SemOrgTypes_old.hpp>
#include <haxorg/sem/SemOrgTypes.hpp>

namespace sem {
template <typename T>
concept NotOrg = !(
    std::derived_from<typename remove_sem_org<T>::type, sem::Org>
    || std::derived_from<T, Org>);

/// \brief  Compile-time check whether the element is an org-mode node or
/// an org-mode ID
template <typename T>
concept IsOrg = std::
    derived_from<typename remove_sem_org<T>::type, sem::Org>;

}; // namespace sem
