#pragma once

#include "hstd_cpp_lib/stdlib/Func.hpp"
#include "hstd_cpp_lib/stdlib/Str.hpp"
#include "hstd_cpp_lib/stdlib/containers/Map.hpp"
#include "hstd_cpp_lib/stdlib/containers/Opt.hpp"
#include "hstd_cpp_lib/stdlib/containers/Pair.hpp"
#include "hstd_cpp_lib/system/macros.hpp"
#include "hstd_cpp_lib/system/reflection.hpp"
#include <functional>
#include <hstd_cpp_lib/stdlib/containers/Vec.hpp>
#include <string>

namespace hstd::ext::unidata {
struct QName {
    hstd::Str        name;
    hstd::Vec<QName> scope;
    DESC_FIELDS(QName, (name, scope));

    bool operator==(QName const& other) const {
        if (this->scope.size() != other.scope.size()) { return false; }
        for (int i = 0; i < scope.size(); ++i) {
            if (scope.at(i) != other.scope.at(i)) { return false; }
        }
        return this->name == other.name;
    }
};

struct VerifyResult {
    std::string message;
    bool        is_ok;

    static VerifyResult Ok();
    static VerifyResult Error(std::string const& failure);
    DESC_FIELDS(VerifyResult, (message, is_ok));
};

struct VerifyContext;

using VerifyCb = hstd::Func<VerifyResult(VerifyContext const* ctx, void const* value)>;
using VerifyCbList = hstd::Vec<VerifyCb>;
using VerifyKey    = hstd::Pair<QName, hstd::Opt<std::string>>;

} // namespace hstd::ext::unidata

template <>
struct std::hash<hstd::ext::unidata::QName> {
    std::size_t operator()(hstd::ext::unidata::QName const& it) const noexcept {
        std::size_t result = 0;
        ::hstd::hax_hash_combine(result, it.name);
        for (auto const& scope : it.scope) { ::hstd::hax_hash_combine(result, scope); }
        return result;
    }
};


namespace hstd::ext::unidata {

struct VerifyCheckCollection {
    hstd::UnorderedMap<VerifyKey, VerifyCbList> checks;
};

struct VerifyContext {};

inline int eval_str_size(std::string const* str) { return static_cast<int>(str->size()); }

}; // namespace hstd::ext::unidata
