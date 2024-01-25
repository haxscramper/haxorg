#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>

void proto_serde<orgproto::AnyNode, sem::SemId>::write(
    orgproto::AnyNode* out,
    const sem::SemId&  in) {

#define _case(_fieldEnum, _field, __Kind)                                 \
    case OrgSemKind::__Kind: {                                            \
        proto_serde<orgproto::__Kind, sem::__Kind>::write(                \
            out->mutable_##_field(), *in.getAs<sem::__Kind>());           \
        break;                                                            \
    }


    orgproto::AnyNode result;
    switch (in->getKind()) { EACH_ANY_NODE_PROTO_FIELD(_case); }

#undef _case
}

void proto_serde<orgproto::AnyNode, sem::SemId>::read(
    sem::ContextStore*       context,
    const orgproto::AnyNode& out,
    sem::SemId&              in) {
#define _case(_fieldEnum, _field, __Kind)                                 \
    case orgproto::AnyNode::KindCase::_fieldEnum: {                       \
        in = context->createIn(0, OrgSemKind::__Kind, sem::SemId::Nil()); \
        proto_serde<orgproto::__Kind, sem::__Kind>::read(                 \
            context, out._field(), *in.getAs<sem::__Kind>());             \
                                                                          \
        break;                                                            \
    }


    orgproto::AnyNode result;
    proto_init<sem::SemId>::init_default(context, in);
    switch (out.kind_case()) { EACH_ANY_NODE_PROTO_FIELD(_case); }

#undef _case
}
