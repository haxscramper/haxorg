#pragma once

#include <sem/SemOrg.hpp>
#include <SemOrgProto.pb.h>

template <typename Proto, typename T>
struct proto_serde {};

namespace gpb = ::google::protobuf;

template <typename Proto, typename T>
struct proto_serde<gpb::RepeatedPtrField<Proto>, Vec<T>> {
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<T> const&                 in) {
        for (auto const& it : in) {
            proto_serde<Proto, T>::write(out->Add(), it);
        }
    }

    static void read(
        sem::ContextStore*                  context,
        gpb::RepeatedPtrField<Proto> const& out,
        Vec<T>&                             in) {}
};


template <typename T>
struct proto_serde<gpb::RepeatedField<::int32_t>, Vec<T>> {
    static void write(
        gpb::RepeatedField<::int32_t>* out,
        Vec<T> const&                  in) {
        for (auto const& it : in) { out->Add(it); }
    }
    static void read(
        sem::ContextStore*                   context,
        gpb::RepeatedField<::int32_t> const& out,
        Vec<T>&                              in) {}
};

template <typename ProtoKey, typename ProtoVal, typename K, typename V>
struct proto_serde<gpb::Map<ProtoKey, ProtoVal>, UnorderedMap<K, V>> {
    static void write(
        gpb::Map<ProtoKey, ProtoVal>* out,
        UnorderedMap<K, V> const&     in) {
        for (auto const& [k, v] : in) {
            proto_serde<ProtoVal, V>::write(&out->operator[](k), v);
        }
    }

    static void read(
        sem::ContextStore*                  context,
        gpb::Map<ProtoKey, ProtoVal> const& out,
        UnorderedMap<K, V>&                 in) {}
};

template <>
struct proto_serde<orgproto::AnyNode, sem::SemId> {
    static void write(orgproto::AnyNode* out, sem::SemId const& in);

    static void write(
        gpb::RepeatedPtrField<orgproto::AnyNode>* out,
        Vec<sem::SemId> const&                    in) {}

    static void read(
        sem::ContextStore*       context,
        orgproto::AnyNode const& out,
        sem::SemId&              in) {}
    static void read(
        sem::ContextStore*                              context,
        gpb::RepeatedPtrField<orgproto::AnyNode> const& out,
        Vec<sem::SemId>&                                in) {}
};

template <typename T>
struct proto_serde<orgproto::AnyNode, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {}

    template <typename Proto>
    static void write(Proto* out, sem::SemIdT<T> const& in) {}

    template <typename Proto>
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&    in) {}
};

template <typename Proto, typename T>
struct proto_serde<Proto, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {}

    static void write(Proto* out, sem::SemIdT<T> const& in) {}

    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&    in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Org> {
    static void write(Proto* out, sem::Org const& in) {
        if (in.placementContext) {
            out->set_placementcontext(
                static_cast<::orgproto::OrgSemPlacement>(
                    *in.placementContext));
        }

        proto_serde<orgproto::AnyNode, sem::SemId>::write(
            out->mutable_subnodes(), in.subnodes);
    }

    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Org&          in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Stmt> {
    static void write(Proto* out, sem::Stmt const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Stmt&         in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::LatexBody> {
    static void write(Proto* out, sem::LatexBody const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::LatexBody&    in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Leaf> {
    static void write(Proto* out, sem::Leaf const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Leaf&         in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Markup> {
    static void write(Proto* out, sem::Markup const& in) {}
    static void write(Proto const& out, sem::Markup& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Format> {
    static void write(Proto* out, sem::Format const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Format&       in) {}
};


template <typename Proto>
struct proto_serde<Proto, sem::Attached> {
    static void write(Proto* out, sem::Attached const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Attached&     in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Block> {
    static void write(Proto* out, sem::Block const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Block&        in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Inline> {
    static void write(Proto* out, sem::Inline const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Inline&       in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Command> {
    static void write(Proto* out, sem::Command const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Command&      in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::LineCommand> {
    static void write(Proto* out, sem::LineCommand const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::LineCommand&  in) {}
};

template <>
struct proto_serde<std::string, Str> {
    static void write(std::string* out, Str const& in) { *out = in; }
    static void read(
        sem::ContextStore* context,
        std::string const& out,
        Str&               in) {
        in = out;
    }
};


template <typename Proto>
struct proto_serde<Proto, sem::SubtreeLog::DescribedLog> {
    static void write(
        Proto*                               out,
        sem::SubtreeLog::DescribedLog const& in) {}
    static void read(
        sem::ContextStore*             context,
        Proto const&                   out,
        sem::SubtreeLog::DescribedLog& in) {}
};


template <>
struct proto_serde<orgproto::UserTime, UserTime> {
    static void write(orgproto::UserTime* out, UserTime const& in) {}
    static void read(
        sem::ContextStore*        context,
        orgproto::UserTime const& out,
        UserTime&                 in) {}
};


template <typename T>
struct proto_init {};

template <typename T>
struct proto_init<Opt<T>> {
    static void init_default(sem::ContextStore* context, Opt<T>& value) {
        value = SerdeDefaultProvider<T>::get();
    }
};


template <>
struct proto_init<sem::SemId> {
    static void init_default(
        sem::ContextStore* context,
        sem::SemId&        value) {
        value         = sem::SemId::Nil();
        value.context = context;
    }
};

template <typename T>
struct proto_init<sem::SemIdT<T>> {
    static void init_default(
        sem::ContextStore* context,
        sem::SemIdT<T>&    value) {
        value         = sem::SemIdT<T>::Nil();
        value.context = context;
    }
};

template <>
struct proto_init<Opt<sem::SemId>> {
    static void init_default(
        sem::ContextStore* context,
        Opt<sem::SemId>&   value) {
        value          = sem::SemId::Nil();
        value->context = context;
    }
};

template <typename T>
struct proto_init<Opt<sem::SemIdT<T>>> {
    static void init_default(
        sem::ContextStore*   context,
        Opt<sem::SemIdT<T>>& value) {
        value          = sem::SemId::Nil();
        value->context = context;
    }
};
