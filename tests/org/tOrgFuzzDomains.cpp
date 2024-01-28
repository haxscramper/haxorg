#include "tOrgFuzzUtils.hpp"
#include "tOrgFuzzDomains.hpp"

Domain<orgproto::UserTime> GenerateUserTime() {
    return Map(
        [](CR<UserTime> time) -> prt::UserTime {
            prt::UserTime result;
            proto_serde<prt::UserTime, UserTime>::write(&result, time);
            return result;
        },
        StructOf<UserTime>(
            Arbitrary<absl::Time>(),
            Just<absl::TimeZone>(absl::UTCTimeZone()),
            GenerateEnumSet<UserTime::Alignment>(
                sliceT<UserTime::Alignment>())));
}

Domain<std::vector<prt::AnyNode>> GenerateSpaceSeparatedNodes(
    CR<GenerateNodeContext> ctx) {
    return FlatMap(
        [ctx](int n) -> Domain<std::vector<prt::AnyNode>> {
            return VectorOfN(
                FlatMap(
                    [ctx, index = 0](int) -> Domain<prt::AnyNode> {
                        int start = index;
                        ++const_cast<int&>(index);
                        if (start % 2 == 0) {
                            return GenerateAnyNode(ctx.getDomain(), ctx);
                        } else {
                            return GenerateAnyNode(
                                GenerateKind({osk::Space}), ctx);
                        }
                    },
                    Just(0)),
                2 * n + 1)
                //
                ;
        },
        InRange(
            ctx.opts.get().minSubnodeCount,
            ctx.opts.get().maxSubnodeCount
                ? ctx.opts.get().maxSubnodeCount.value()
                : 16));
}

Domain<prt::AnyNode> MapAnyNodeKind(
    OrgSemKind              kind,
    CR<GenerateNodeContext> ctx) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return Map(                                                       \
            ConvertAnyNode<prt::__Kind>, GenerateNode<prt::__Kind>(ctx));

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}


Domain<std::vector<orgproto::AnyNode>> GenerateNodesKind(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeContext> ctx) {
    if (ctx.opts.get().maxSubnodeCount) {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.opts.get().minSubnodeCount)
            .WithMaxSize(ctx.opts.get().maxSubnodeCount.value());

    } else {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.opts.get().minSubnodeCount);
    }
}

Domain<orgproto::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      domain,
    CR<GenerateNodeContext> ctx) {
    return FlatMap(
        [ctx](OrgSemKind it) { return MapAnyNodeKind(it, ctx); }, domain);
}
