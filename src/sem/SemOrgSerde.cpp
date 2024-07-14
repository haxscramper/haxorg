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
        if (in.get().isNil()) {                                           \
            in.get() = sem::SemId<sem::__Kind>::New();                    \
        }                                                                 \
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

template <typename Proto>
void proto_serde<Proto, sem::Command>::write(
    Proto*              out,
    const sem::Command& in) {
    if (in.parameters) {
        if (in.parameters) {
            proto_serde<
                orgproto::CmdArguments,
                sem::SemId<sem::CmdArguments>>::
                write(out->mutable_parameters(), *in.parameters);
        }
    }
}

template <typename Proto>
void proto_serde<Proto, sem::Command>::read(
    const Proto&                       out,
    proto_write_accessor<sem::Command> in) {
    if (out.has_parameters()) {
        proto_serde<
            Opt<orgproto::CmdArguments>,
            Opt<sem::SemId<sem::CmdArguments>>>::
            read(out.parameters(), in.for_field(&sem::Export::parameters));
    }
}

template <typename Proto>
void proto_serde<Proto, sem::Block>::write(
    Proto*            out,
    const sem::Block& in) {}

template <typename Proto>
void proto_serde<Proto, sem::Block>::read(
    const Proto&                     out,
    proto_write_accessor<sem::Block> in) {}


template class proto_serde<::orgproto::Verse, sem::Block>;
template class proto_serde<::orgproto::Export, sem::Block>;
template class proto_serde<::orgproto::AdmonitionBlock, sem::Block>;
template class proto_serde<::orgproto::Code, sem::Block>;
template class proto_serde<::orgproto::Example, sem::Block>;

template class proto_serde<orgproto::AdmonitionBlock, sem::Command>;
template class proto_serde<orgproto::Caption, sem::Command>;
template class proto_serde<orgproto::Cell, sem::Command>;
template class proto_serde<orgproto::CmdAttr, sem::Command>;
template class proto_serde<orgproto::CmdName, sem::Command>;
template class proto_serde<orgproto::CmdResults, sem::Command>;
template class proto_serde<orgproto::Code, sem::Command>;
template class proto_serde<orgproto::Example, sem::Command>;
template class proto_serde<orgproto::Export, sem::Command>;
template class proto_serde<orgproto::Row, sem::Command>;
template class proto_serde<orgproto::Table, sem::Command>;
template class proto_serde<orgproto::Tblfm, sem::Command>;
template class proto_serde<orgproto::Verse, sem::Command>;
template class proto_serde<orgproto::Quote, sem::Command>;
template class proto_serde<orgproto::CmdCustomArgs, sem::Command>;
