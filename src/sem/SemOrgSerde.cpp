#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>

void proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
    orgproto::AnyNode*          out,
    const sem::SemId<sem::Org>& in) {

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

void proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
    const orgproto::AnyNode&                   out,
    proto_write_accessor<sem::SemId<sem::Org>> in) {
#define _case(_fieldEnum, _field, __Kind)                                 \
    case orgproto::AnyNode::KindCase::_fieldEnum: {                       \
        if (in.get().isNil()) { in.get() = sem::SemId<sem::Org>::New(); } \
        sem::SemId<sem::__Kind> tmp_id = in.get().as<sem::__Kind>();      \
        proto_serde<orgproto::__Kind, sem::SemId<sem::__Kind>>::read(     \
            out._field(),                                                 \
            proto_write_accessor<sem::SemId<sem::__Kind>>::for_ref(       \
                tmp_id));                                                 \
                                                                          \
        break;                                                            \
    }


    orgproto::AnyNode result;

    switch (out.kind_case()) {
        EACH_ANY_NODE_PROTO_FIELD(_case);
        default: {
            LOG(FATAL)
                << "Cannot read protobuf 'AnyNode' with no subfields set. "
                   "At least one of the sub-fields must be specified so "
                   "the node type can be determined.";
        }
    }
    CHECK(!in.get().isNil());

#undef _case
}
