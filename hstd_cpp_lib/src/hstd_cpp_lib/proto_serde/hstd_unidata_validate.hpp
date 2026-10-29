#pragma once

#include "hstd_cpp_lib/stdlib/Func.hpp"
#include "hstd_cpp_lib/stdlib/Str.hpp"
#include "hstd_cpp_lib/stdlib/containers/Map.hpp"
#include "hstd_cpp_lib/stdlib/containers/Opt.hpp"
#include "hstd_cpp_lib/stdlib/containers/Pair.hpp"
#include "hstd_cpp_lib/system/macros.hpp"
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <string>

namespace hstd::ext::unidata {
struct CheckResult {
    std::string tmp_result;
    DESC_FIELDS(CheckResult, (tmp_result));
};

struct QName {
    hstd::Str        name;
    hstd::Vec<QName> scope;
    DESC_FIELDS(QName, (name, scope));
};

struct VerifyResult {
    hstd::Vec<CheckResult> checks;
    DESC_FIELDS(VerifyResult, (checks));
};

struct VerifyContext;

using VerifyCb  = hstd::Func<CheckResult(VerifyContext const* ctx, void const* value)>;
using VerifyKey = hstd::Pair<QName, hstd::Opt<std::string>>;

struct VerifyContext {
    hstd::UnorderedMap<VerifyKey, hstd::Vec<VerifyCb>> checks;
};

}; // namespace hstd::ext::unidata
