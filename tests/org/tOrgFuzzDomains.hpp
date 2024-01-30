#pragma once
#include "tOrgFuzzUtils.hpp"

#define __TypeHasField(C, Field)                                                 \
    []() {                                                                       \
        return overloaded{                                                       \
            []<typename T>(int)                                                  \
                -> decltype(std::declval<T>().Field, void(), std::true_type()) { \
                return {};                                                       \
            },                                                                   \
            []<typename T>(...) { return std::false_type{}; }}                   \
            .template operator()<C>(0);                                          \
    }()

template <typename Node>
auto InitNode(CR<GenerateNodeContext> ctx) {
    json debug;
    to_json(
        debug,
        GenerateNodeDebug{
            .line    = ctx.opts.get().line,
            .message = ctx.opts.get().debugMessage,
        });

    auto tmp = Arbitrary<Node>() //
                   .WithFieldUnset("loc")
                   .WithStringField("debug", Just(debug.dump()))
                   .WithEnumField(
                       "staticKind",
                       Just(static_cast<int>(
                           proto_org_map<Node>::org_kind::staticKind)));


    if (!__TypeHasField(Node, attached)) {
        return std::move(tmp);
    } else {
        return std::move(tmp).WithRepeatedProtobufField(
            "attached",
            ctx.getSubnodeDomain(
                proto_org_map<Node>::org_kind::staticKind));
    }
}

template <typename Node>
auto InitLeaf(CR<GenerateNodeContext> ctx) {
    return InitNode<Node>(ctx) //
        .WithRepeatedFieldMaxSize("subnodes", 0);
}


template <typename Node>
Domain<Node> GenerateNode(CR<GenerateNodeContext> ctx);

#define _case(__Kind)                                                     \
    template <>                                                           \
    Domain<prt::__Kind> GenerateNode(CR<GenerateNodeContext> ctx);
EACH_SEM_ORG_KIND(_case)
#undef _case

template <typename NodeType>
prt::AnyNode ConvertAnyNode(NodeType const& subNode) {
    prt::AnyNode anyNode;

    // Use the macro to set the appropriate field on AnyNode
#define _case(_fieldEnum, _field, _Kind)                                  \
    if constexpr (std::is_same<NodeType, prt::_Kind>::value) {            \
        *anyNode.mutable_##_field() = subNode;                            \
    }

    EACH_ANY_NODE_PROTO_FIELD(_case)
#undef _case

    CHECK(anyNode.kind_case() != orgproto::AnyNode::KIND_NOT_SET)
        << demangle(typeid(subNode).name());

    return anyNode;
}

template <typename NodeType>
Domain<prt::AnyNode> GenerateAnyNodeWrapper(
    Domain<NodeType> nodeGenerator) {
    return Map(ConvertAnyNode<NodeType>, nodeGenerator);
}

Domain<prt::AnyNode> MapAnyNodeKind(
    OrgSemKind              kind,
    CR<GenerateNodeContext> ctx);

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      domain,
    CR<GenerateNodeContext> ctx);

Domain<std::vector<prt::AnyNode>> GenerateSpaceSeparatedNodes(
    CR<GenerateNodeContext> ctx);

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeContext> ctx);


inline Domain<OrgSemKind> GenerateKind(Vec<OrgSemKind> const& values) {
    return ElementOf<OrgSemKind>(values);
}

Domain<prt::AnyNode> MapAnyNodeKind(OrgSemKind kind);

Domain<std::vector<prt::AnyNode>> GenerateNodesKind(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeContext> ctx);

inline Domain<prt::AnyNode> GenerateDocumentNode(
    CR<GenerateNodeContext> ctx) {
    return GenerateAnyNodeWrapper(GenerateNode<prt::Document>(ctx));
}

Domain<prt::UserTime> GenerateUserTime();
