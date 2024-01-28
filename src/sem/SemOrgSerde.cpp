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
    sem::ContextStore*               context,
    const orgproto::AnyNode&         out,
    proto_write_accessor<sem::SemId> in) {
#define _case(_fieldEnum, _field, __Kind)                                 \
    case orgproto::AnyNode::KindCase::_fieldEnum: {                       \
        if (in.get().isNil()) {                                           \
            in.get() = context->createIn(                                 \
                0, OrgSemKind::__Kind, sem::SemId::Nil());                \
            in.get().context = context;                                   \
        }                                                                 \
        sem::SemIdT<sem::__Kind> tmp_id = in.get().as<sem::__Kind>();     \
        proto_serde<orgproto::__Kind, sem::SemIdT<sem::__Kind>>::read(    \
            context,                                                      \
            out._field(),                                                 \
            proto_write_accessor<sem::SemIdT<sem::__Kind>>::for_ref(      \
                tmp_id));                                                 \
                                                                          \
        break;                                                            \
    }


    orgproto::AnyNode result;

    switch (out.kind_case()) {
        EACH_ANY_NODE_PROTO_FIELD(_case);
        default: {
            LOG(FATAL) << "Any node kind is not set";
        }
    }
    CHECK(!in.get().isNil());
    CHECK(in.get().context != nullptr);

#undef _case
}
