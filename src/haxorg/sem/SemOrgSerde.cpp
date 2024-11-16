#include <haxorg/sem/SemOrgSerde.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>

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
void proto_serde<Proto, sem::Cmd>::write(Proto* out, const sem::Cmd& in) {
    if (in.attrs) {
        if (in.attrs) {
            proto_serde<orgproto::AttrGroup, sem::AttrGroup>::write(
                out->mutable_attrs(), *in.attrs);
        }
    }
}

template <typename Proto>
void proto_serde<Proto, sem::Cmd>::read(
    const Proto&                   out,
    proto_write_accessor<sem::Cmd> in) {
    if (out.has_attrs()) {
        proto_serde<Opt<orgproto::AttrGroup>, Opt<sem::AttrGroup>>::read(
            out.attrs(), in.for_field(&sem::BlockExport::attrs));
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


template class proto_serde<::orgproto::BlockVerse, sem::Block>;
template class proto_serde<::orgproto::BlockExport, sem::Block>;
template class proto_serde<::orgproto::BlockAdmonition, sem::Block>;
template class proto_serde<::orgproto::BlockCode, sem::Block>;
template class proto_serde<::orgproto::BlockExample, sem::Block>;
template class proto_serde<::orgproto::BlockDynamicFallback, sem::Block>;

template class proto_serde<::orgproto::BlockAdmonition, sem::Cmd>;
template class proto_serde<::orgproto::CmdCaption, sem::Cmd>;
template class proto_serde<::orgproto::Cell, sem::Cmd>;
template class proto_serde<::orgproto::CmdAttr, sem::Cmd>;
template class proto_serde<::orgproto::CmdName, sem::Cmd>;
template class proto_serde<::orgproto::CmdResults, sem::Cmd>;
template class proto_serde<::orgproto::BlockCode, sem::Cmd>;
template class proto_serde<::orgproto::BlockExample, sem::Cmd>;
template class proto_serde<::orgproto::BlockCenter, sem::Cmd>;
template class proto_serde<::orgproto::BlockExport, sem::Cmd>;
template class proto_serde<::orgproto::BlockDynamicFallback, sem::Cmd>;
template class proto_serde<::orgproto::Row, sem::Cmd>;
template class proto_serde<::orgproto::Table, sem::Cmd>;
template class proto_serde<::orgproto::CmdTblfm, sem::Cmd>;
template class proto_serde<::orgproto::BlockVerse, sem::Cmd>;
template class proto_serde<::orgproto::BlockQuote, sem::Cmd>;
template class proto_serde<::orgproto::CmdCustomArgs, sem::Cmd>;
template class proto_serde<::orgproto::CmdColumns, sem::Cmd>;
template class proto_serde<::orgproto::CmdExport, sem::Cmd>;
