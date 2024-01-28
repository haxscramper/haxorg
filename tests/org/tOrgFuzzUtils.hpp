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
    SemSet     expand;
};

struct GenerateNodeOptions {
    int      line             = __builtin_LINE();
    Str      debugMessage     = "";
    int      minSubnodeCount  = 1;
    Opt<int> maxSubnodeCount  = std::nullopt;
    int      minAttachedCount = 0;
    int      maxAttachedCount = 0;
};

struct GenerateNodeContext {
    immer::vector<GenerateNodePath> steps;
    immer::box<GenerateNodeOptions> opts;

    GenerateNodeContext operator&(GenerateNodePath other) const {
        return GenerateNodeContext{
            .steps = steps.push_back(other),
            .opts  = opts,
        };
    }

    GenerateNodeContext withoutSubnodes() const {
        return GenerateNodeContext{
            .steps = steps,
            .opts  = opts.update([](GenerateNodeOptions opts) {
                opts.minSubnodeCount = 0;
                opts.maxSubnodeCount = 0;
                return opts;
            })};
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

    Domain<OrgSemKind> getDomain() const {
        SemSet result{sliceT<OrgSemKind>()};
        for (auto const& it : steps) {
            result.excl(it.kind);
            result.incl(it.expand);
            switch (it.kind) {
                case OrgSemKind::Document: {
                    result.excl(OrgSemKind::DocumentOptions);
                    result.excl(OrgSemKind::DocumentGroup);
                    break;
                }
                default: {
                }
            }
        }


        return GenerateEnumSet(result);
    }
};

inline auto AlwaysSet(auto domain) { return NonNull(OptionalOf(domain)); }

inline Domain<int> StaticCastEnum(auto domain) {
    return Map(
        [](auto value) -> int { return static_cast<int>(value); }, domain);
}

inline auto LowerIdent() { return StringOf(LowerChar()).WithMinSize(3); }


template <typename T>
auto VectorOfN(CR<T> values, int size) {
    return VectorOf(values).WithMinSize(size).WithMaxSize(size);
}
