#pragma once

#include "hstd/stdlib/Json.hpp"
#include <gtest/gtest.h>
#include <fuzztest/fuzztest.h>
#include <absl/log/log.h>
#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgFormat.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include <sem/SemOrgSerdeDeclarations.hpp>
#include <immer/vector.hpp>
#include <immer/box.hpp>

namespace prt = orgproto;
namespace gpb = ::google::protobuf;
using osk     = OrgSemKind;
using namespace fuzztest;

void PrintMessageWithTypeName(
    const gpb::Message& message,
    std::ostringstream& oss,
    int                 depth);

std::string PrintWithTypeName(const gpb::Message& message);


template <typename T>
Domain<T> GenerateEnumSet(Slice<T> const& values) {
    std::vector<T> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<T>(items);
}

template <typename T>
Domain<T> GenerateEnumSet(IntSet<T> const& values) {
    std::vector<T> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<T>(items);
}

struct GenerateNodeDebug {
    DECL_FIELDS(
        GenerateNodeDebug,
        (),
        ((int), line, __builtin_LINE()),
        ((Str), message, ""));
};

struct GenerateNodePath {
    OrgSemKind kind;
    int        line = __builtin_LINE();
};

struct GenerateNodeOptions {
    int      line              = __builtin_LINE();
    Str      debugMessage      = "";
    int      minSubnodeCount   = 1;
    Opt<int> maxSubnodeCount   = std::nullopt;
    int      minAttachedCount  = 0;
    int      maxAttachedCount  = 0;
    int      maxRecursionDepth = 16;
    bool     enableTrace       = false;
};

struct GenerateNodeContext {
    immer::vector<GenerateNodePath> steps;
    immer::box<GenerateNodeOptions> opts;

    std::string format() const;
    std::string indent() const;
    void        debug(
               const char* function,
               std::string msg  = "",
               int         line = __builtin_LINE()) const;

    int count(OrgSemKind contexts) const;

    bool isAtRecursionLimit() const {
        return opts.get().maxRecursionDepth <= steps.size();
    }

    int getMinSubnodeCount() const {
        return isAtRecursionLimit() ? 0 : opts.get().minSubnodeCount;
    }

    Opt<int> getMaxSubnodeCount() const {
        return isAtRecursionLimit() ? 0 : opts.get().maxSubnodeCount;
    }

    GenerateNodeContext rec(OrgSemKind kind, int line = __builtin_LINE())
        const {
        return (*this) & GenerateNodePath{.kind = kind, .line = line};
    }

    GenerateNodeContext rec(
        GenerateNodePath sub = GenerateNodePath{
            .kind = OrgSemKind::Empty}) const {
        return (*this) & sub;
    }

    GenerateNodeContext operator&(GenerateNodePath other) const {
        return GenerateNodeContext{
            .steps = steps.push_back(other),
            .opts  = opts,
        };
    }

    GenerateNodeContext withOptsUpdate(
        Func<GenerateNodeOptions(GenerateNodeOptions)> update) const {
        return GenerateNodeContext{
            .steps = steps,
            .opts  = opts.update(update),
        };
    }

    GenerateNodeContext withMaxSubnodes(int max) const {
        return withOptsUpdate([max](GenerateNodeOptions opts) {
            opts.maxSubnodeCount = max;
            return opts;
        });
    }

    GenerateNodeContext withoutSubnodes() const {
        return withOptsUpdate([](GenerateNodeOptions opts) {
            opts.minSubnodeCount = 0;
            opts.maxSubnodeCount = 0;
            return opts;
        });
    }

    auto getSubnodeDomain(auto filler) const {
        if (opts->maxSubnodeCount) {
            return VectorOf(filler)
                .WithMinSize(opts->minSubnodeCount)
                .WithMaxSize(*opts->maxSubnodeCount);
        } else {
            return VectorOf(filler).WithMinSize(opts->minSubnodeCount);
        }
    }

    SemSet getDomainSet() const;

    Domain<OrgSemKind> getDomain() const {
        return GenerateEnumSet(getDomainSet());
    }

    Domain<std::vector<orgproto::AnyNode>> getSubnodeDomain(
        OrgSemKind kind) const;
};

inline auto AlwaysSet(auto domain) { return NonNull(OptionalOf(domain)); }

inline Domain<int> StaticCastEnum(auto domain) {
    return Map(
        [](auto value) -> int { return static_cast<int>(value); }, domain);
}

inline auto LowerIdent() { return StringOf(LowerChar()).WithMinSize(3); }


template <typename T>
auto VectorOfN(CR<T> values, int size) {
    return VectorOf(values).WithSize(size);
}
