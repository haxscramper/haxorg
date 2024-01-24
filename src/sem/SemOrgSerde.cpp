#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>

void proto_serde<orgproto::AnyNode, sem::SemId>::write(
    orgproto::AnyNode* out,
    const sem::SemId&  in) {

#define _case(_field, __Kind)                                             \
    case OrgSemKind::__Kind: {                                            \
        proto_serde<orgproto::__Kind, sem::__Kind>::write(                \
            out->mutable_##_field(), *in.getAs<sem::__Kind>());           \
        break;                                                            \
    }


    orgproto::AnyNode result;
    switch (in->getKind()) { EACH_ANY_NODE_PROTO_FIELD(_case); }

#undef _case
}
