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
    ctx.debug(__PRETTY_FUNCTION__);
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
            ctx.getMinSubnodeCount(),
            ctx.getMaxSubnodeCount() ? ctx.getMaxSubnodeCount().value()
                                     : 4));
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
    if (ctx.getMaxSubnodeCount()) {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.getMinSubnodeCount())
            .WithMaxSize(ctx.getMaxSubnodeCount().value());

    } else {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.getMinSubnodeCount());
    }
}

Domain<orgproto::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      domain,
    CR<GenerateNodeContext> ctx) {
    return FlatMap(
        [ctx](OrgSemKind it) { return MapAnyNodeKind(it, ctx); }, domain);
}
