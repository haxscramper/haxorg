#pragma once

#include <sem/SemOrg.hpp>
#include <SemOrgProto.pb.h>

template <typename Proto, typename T>
struct proto_serde {};

namespace gpb = ::google::protobuf;

template <typename T>
struct proto_org_map {};

#define _map(__Kind)                                                      \
    template <>                                                           \
    struct proto_org_map<::orgproto::__Kind> {                            \
        using org_kind = sem::__Kind;                                     \
    };

EACH_SEM_ORG_KIND(_map)


#undef _map

template <typename T>
struct SerdeDefaultProvider<sem::SemIdT<T>> {
    static sem::SemIdT<T> get() { return sem::SemIdT<T>::Nil(); }
};

template <>
struct SerdeDefaultProvider<sem::SemId> {
    static sem::SemId get() { return sem::SemId::Nil(); }
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
        Vec<T>&                             in) {
        for (auto const& it : out) {
            proto_serde<Proto, T>::read(context, it, in.emplace_back());
        }
    }
};

template <typename Proto>
struct proto_serde<gpb::RepeatedPtrField<Proto>, Vec<sem::SemId>> {
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemId> const&        in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId>::write(out->Add(), it);
        }
    }

    static void read(
        sem::ContextStore*                  context,
        gpb::RepeatedPtrField<Proto> const& out,
        Vec<sem::SemId>&                    in) {
        for (auto const& it : out) {
            proto_serde<Proto, sem::SemId>::read(
                context, it, in.emplace_back(sem::SemId::Nil()));
        }
    }
};

template <typename Proto, typename T>
struct proto_serde<gpb::RepeatedPtrField<Proto>, Vec<sem::SemIdT<T>>> {
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&    in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId>::write(out->Add(), it.toId());
        }
    }

    static void read(
        sem::ContextStore*                  context,
        gpb::RepeatedPtrField<Proto> const& out,
        Vec<sem::SemIdT<T>>&                in) {
        for (auto const& it : out) {
            proto_serde<Proto, sem::SemIdT<T>>::read(
                context, it, in.emplace_back(sem::SemIdT<T>::Nil()));
        }
    }
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
        Vec<T>&                              in) {
        for (auto const& it : out) { in.push_back(it); }
    }
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
        UnorderedMap<K, V>&                 in) {
        for (auto const& [key, val] : out) {
            in.insert_or_assign(key, SerdeDefaultProvider<V>::get());
            proto_serde<ProtoVal, V>::read(context, val, in.at(key));
        }
    }
};

template <>
struct proto_serde<orgproto::AnyNode, sem::SemId> {
    static void write(orgproto::AnyNode* out, sem::SemId const& in);

    static void write(
        gpb::RepeatedPtrField<orgproto::AnyNode>* out,
        Vec<sem::SemId> const&                    in) {
        for (auto const& it : in) {
            proto_serde<orgproto::AnyNode, sem::SemId>::write(
                out->Add(), it);
        }
    }

    static void read(
        sem::ContextStore*       context,
        orgproto::AnyNode const& out,
        sem::SemId&              in);

    static void read(
        sem::ContextStore*                              context,
        gpb::RepeatedPtrField<orgproto::AnyNode> const& out,
        Vec<sem::SemId>&                                in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::SemId> {
    static void write(Proto* out, sem::SemId const& in) {
        using org_type = proto_org_map<Proto>::org_kind;
        proto_serde<Proto, org_type>::write(out, *in.as<org_type>().get());
    }

    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::SemId&        in) {
        using org_type = proto_org_map<Proto>::org_kind;
        in = context->createIn(0, org_type::staticKind, sem::SemId::Nil());
        proto_serde<Proto, org_type>::read(
            context, out, *in.as<org_type>().get());
    }
};


template <typename T>
struct proto_serde<orgproto::AnyNode, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId>::write(out, in.toId());
    }

    template <typename Proto>
    static void write(Proto* out, sem::SemIdT<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId>::write(
            out->Add(), in.toId());
    }

    template <typename Proto>
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&    in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto, typename T>
struct proto_serde<Proto, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId>::write(out, in.toId());
    }

    static void write(Proto* out, sem::SemIdT<T> const& in) {
        proto_serde<Proto, sem::SemId>::write(out, in.toId());
    }

    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&    in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId>::write(out->Add(), it.toId());
        }
    }

    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::SemIdT<T>&    in) {
        sem::SemId tmp = sem::SemId::Nil();
        proto_serde<Proto, sem::SemId>::read(context, out, tmp);
        in = tmp.as<T>();
    }

    static void read(
        sem::ContextStore*       context,
        orgproto::AnyNode const& out,
        sem::SemIdT<T>&          in) {
        sem::SemId tmp = sem::SemId::Nil();
        proto_serde<orgproto::AnyNode, sem::SemId>::read(
            context, out, tmp);
        in = tmp.as<T>();
    }
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
        out->set_statickind(
            static_cast<orgproto::OrgSemKind>(in.getKind()));
        if (in.placementContext) {
            out->set_placementcontext(
                static_cast<orgproto::OrgSemPlacement>(
                    *in.placementContext));
        }

        // if (in.loc) {
        //     auto loc = out->mutable_loc();
        //     loc->set_col(in.loc->column);
        //     loc->set_line(in.loc->line);
        // }
    }

    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Org&          in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            Vec<sem::SemId>>::read(context, out.subnodes(), in.subnodes);
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Stmt> {
    static void write(Proto* out, sem::Stmt const& in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            Vec<sem::SemId>>::write(out->mutable_attached(), in.attached);
    }

    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Stmt&         in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            Vec<sem::SemId>>::read(context, out.attached(), in.attached);
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::LatexBody> {
    static void write(Proto* out, sem::LatexBody const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::LatexBody&    in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Leaf> {
    static void write(Proto* out, sem::Leaf const& in) {
        out->set_text(in.text);
    }
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Leaf&         in) {
        in.text = out.text();
    }
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
        sem::Format&       in) {
        LOG(FATAL) << "??";
    }
};


template <typename Proto>
struct proto_serde<Proto, sem::Attached> {
    static void write(Proto* out, sem::Attached const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Attached&     in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Block> {
    static void write(Proto* out, sem::Block const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Block&        in) {
        LOG(FATAL) << "??";
    }
};

template <>
struct proto_serde<orgproto::LineCol, LineCol> {
    static void write(orgproto::LineCol* out, LineCol const& in) {
        out->set_line(in.line);
        out->set_column(in.column);
        out->set_pos(in.pos);
    }
    static void read(
        sem::ContextStore*       context,
        orgproto::LineCol const& out,
        LineCol&                 in) {
        in.pos    = out.pos();
        in.line   = out.line();
        in.column = out.column();
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Inline> {
    static void write(Proto* out, sem::Inline const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Inline&       in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Command> {
    static void write(Proto* out, sem::Command const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::Command&      in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::LineCommand> {
    static void write(Proto* out, sem::LineCommand const& in) {}
    static void read(
        sem::ContextStore* context,
        Proto const&       out,
        sem::LineCommand&  in) {
        LOG(FATAL) << "??";
    }
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
        sem::SubtreeLog::DescribedLog& in) {
        LOG(FATAL) << "??";
    }
};


template <>
struct proto_serde<orgproto::UserTime, UserTime> {
    static void write(orgproto::UserTime* out, UserTime const& in) {}
    static void read(
        sem::ContextStore*        context,
        orgproto::UserTime const& out,
        UserTime&                 in) {}
};
