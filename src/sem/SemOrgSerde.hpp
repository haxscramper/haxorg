#pragma once

#include <sem/SemOrg.hpp>
#include <SemOrgProto.pb.h>
#include <concepts>

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
struct is_std_optional : std::false_type {};

template <typename T>
struct is_std_optional<std::optional<T>> : std::true_type {};

template <typename T, typename Derived>
struct proto_write_accessor_base {
    std::function<T&()> impl;
    T&                  get() { return impl(); }

    static Derived for_ref(T& item) {
        return Derived{{.impl = [&item]() -> T& { return item; }}};
    }
};

template <typename T>
struct proto_write_accessor
    : proto_write_accessor_base<T, proto_write_accessor<T>> {};

template <typename T>
struct proto_write_accessor<Opt<T>>
    : proto_write_accessor_base<Opt<T>, proto_write_accessor<Opt<T>>> {

    proto_write_accessor<T> for_value() {
        return proto_write_accessor<T>{
            [impl = this->impl]() -> T& { return impl().value(); }};
    }
};


template <IsRecord T>
struct proto_write_accessor<T>
    : proto_write_accessor_base<T, proto_write_accessor<T>> {

    template <typename T1>
    proto_write_accessor<T1> as() {
        return proto_write_accessor<T1>{
            [impl = this->impl]() -> T1& { return impl(); }};
    }

    template <typename F>
    proto_write_accessor<F> for_field(F T::*field) {
        return proto_write_accessor<F>{
            [impl = this->impl, field]() -> F& { return impl().*field; }};
    }

    template <typename FieldType, typename Var, int Field>
    struct variant_init {
        static void init(sem::ContextStore* context, Var& variant) {
            variant = variant_from_index<Var>(Field);
        }
    };

    template <typename Var, int Field>
    struct variant_init<sem::SemId, Var, Field> {
        static void init(sem::ContextStore* context, Var& variant) {
            auto tmp    = sem::SemId::Nil();
            tmp.context = context;
            variant     = tmp;
        }
    };

    template <typename FieldType, typename Var, int Field>
    struct variant_init<sem::SemIdT<FieldType>, Var, Field> {
        static void init(sem::ContextStore* context, Var& variant) {
            auto tmp    = sem::SemIdT<FieldType>::Nil();
            tmp.context = context;
            variant     = tmp;
        }
    };

    template <
        int N,
        typename F,
        typename VarType = std::variant_alternative_t<N, F>>
    proto_write_accessor<VarType> for_field_variant(
        sem::ContextStore* context,
        F T::*field) {
        return proto_write_accessor<VarType>{
            [impl = this->impl, field, context]() -> VarType& {
                if ((impl().*field).index() != N) {
                    variant_init<VarType, F, N>::init(
                        context, impl().*field);
                }
                return std::get<VarType>(impl().*field);
            }};
    }
};

template <typename T>
struct proto_init {
    static void init_default(sem::ContextStore* context, T& value) {}
};

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
struct proto_serde<Opt<Proto>, Opt<T>> {
    static void write(Proto* out, Opt<T> const& in) {
        proto_serde<Proto, T>::write(out, in.value());
    }

    static void read(
        sem::ContextStore*           context,
        Proto const&                 out,
        proto_write_accessor<Opt<T>> in) {
        proto_init<Opt<T>>::init_default(context, in.get());
        proto_serde<Proto, T>::read(context, out, in.for_value());
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
        proto_write_accessor<Vec<T>>        in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            proto_serde<Proto, T>::read(
                context, it, proto_write_accessor<T>::for_ref(ref));
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
        sem::ContextStore*                    context,
        gpb::RepeatedPtrField<Proto> const&   out,
        proto_write_accessor<Vec<sem::SemId>> in) {
        for (auto const& it : out) {
            auto& items = in.get();
            items.emplace_back(sem::SemId::Nil());
            proto_serde<Proto, sem::SemId>::read(
                context,
                it,
                proto_write_accessor<sem::SemId>{
                    [&in]() -> sem::SemId& { return in.get().back(); }});
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
        sem::ContextStore*                        context,
        gpb::RepeatedPtrField<Proto> const&       out,
        proto_write_accessor<Vec<sem::SemIdT<T>>> in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back(sem::SemIdT<T>::Nil());
            proto_serde<Proto, sem::SemIdT<T>>::read(
                context,
                it,
                proto_write_accessor<sem::SemIdT<T>>::for_ref(ref));
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
        proto_write_accessor<Vec<T>>         in) {
        for (auto const& it : out) { in.get().push_back(it); }
    }
};

template <class T>
concept IsDefaultConstructible = std::is_default_constructible_v<T>;

template <class T>
concept NonDefaultConstructible = !IsDefaultConstructible<T>;

template <typename ProtoKey, typename ProtoVal, typename K, typename V>
struct proto_serde<gpb::Map<ProtoKey, ProtoVal>, UnorderedMap<K, V>> {
    static void write(
        gpb::Map<ProtoKey, ProtoVal>* out,
        UnorderedMap<K, V> const&     in) {
        for (auto const& [k, v] : in) {
            proto_serde<ProtoVal, V>::write(&out->operator[](k), v);
        }
    }

    template <sem::IsOrgId U = V>
    static void read(
        sem::ContextStore*                       context,
        gpb::Map<ProtoKey, ProtoVal> const&      out,
        proto_write_accessor<UnorderedMap<K, U>> in) {
        for (auto const& [key, val] : out) {
            in.get().insert_or_assign(key, U::Nil());
            proto_serde<ProtoVal, V>::read(
                context, val, proto_write_accessor<V>{[&in, &key]() -> V& {
                    return in.get().at(key);
                }});
        }
    }

    template <IsDefaultConstructible U = V>
    static void read(
        sem::ContextStore*                       context,
        gpb::Map<ProtoKey, ProtoVal> const&      out,
        proto_write_accessor<UnorderedMap<K, V>> in) {
        for (auto const& [key, val] : out) {
            in.get().insert_or_assign(key, SerdeDefaultProvider<V>::get());
            proto_serde<ProtoVal, V>::read(
                context, val, proto_write_accessor<V>{[&in, &key]() -> V& {
                    return in.get().at(key);
                }});
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
        sem::ContextStore*               context,
        orgproto::AnyNode const&         out,
        proto_write_accessor<sem::SemId> in);

    static void read(
        sem::ContextStore*                              context,
        gpb::RepeatedPtrField<orgproto::AnyNode> const& out,
        proto_write_accessor<Vec<sem::SemId>>           in) {
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
        sem::ContextStore*               context,
        Proto const&                     out,
        proto_write_accessor<sem::SemId> in) {
        using org_type = proto_org_map<Proto>::org_kind;
        if (in.get().isNil()) {
            in.get() = context->createIn(
                0, org_type::staticKind, sem::SemId::Nil());
            in.get().context = context;
        }
        sem::SemId id = in.get();
        proto_serde<Proto, org_type>::read(
            context,
            out,
            proto_write_accessor<org_type>{
                [id]() -> org_type& { return *id.as<org_type>().get(); }});
        CHECK(!in.get().isNil());
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
        sem::ContextStore*                   context,
        Proto const&                         out,
        proto_write_accessor<sem::SemIdT<T>> in) {
        sem::SemId tmp = in.get();
        proto_serde<Proto, sem::SemId>::read(
            context, out, proto_write_accessor<sem::SemId>::for_ref(tmp));
        in.get() = tmp.as<T>();
        CHECK(!in.get().isNil());
    }

    static void read(
        sem::ContextStore*                   context,
        orgproto::AnyNode const&             out,
        proto_write_accessor<sem::SemIdT<T>> in) {
        sem::SemId tmp = in.get();
        proto_serde<orgproto::AnyNode, sem::SemId>::read(
            context, out, proto_write_accessor<sem::SemId>::for_ref(tmp));
        in.get() = tmp.as<T>();
        CHECK(!in.get().isNil());
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Org> {
    static void write(Proto* out, sem::Org const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId>::write(
            out->mutable_subnodes(), in.subnodes);
        out->set_statickind(
            static_cast<orgproto::OrgSemKind>(in.getKind()));
    }

    static void read(
        sem::ContextStore*             context,
        Proto const&                   out,
        proto_write_accessor<sem::Org> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            Vec<sem::SemId>>::
            read(
                context,
                out.subnodes(),
                in.for_field(&sem::Org::subnodes));
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
        sem::ContextStore*              context,
        Proto const&                    out,
        proto_write_accessor<sem::Stmt> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            Vec<sem::SemId>>::
            read(
                context,
                out.attached(),
                in.for_field(&sem::Stmt::attached));
    }
};


template <typename Proto>
struct proto_serde<Proto, sem::Leaf> {
    static void write(Proto* out, sem::Leaf const& in) {
        out->set_text(in.text);
    }
    static void read(
        sem::ContextStore*              context,
        Proto const&                    out,
        proto_write_accessor<sem::Leaf> in) {
        in.get().text = out.text();
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
        sem::ContextStore*            context,
        orgproto::LineCol const&      out,
        proto_write_accessor<LineCol> in) {
        in.get().pos    = out.pos();
        in.get().line   = out.line();
        in.get().column = out.column();
    }
};

template <>
struct proto_serde<std::string, Str> {
    static void write(std::string* out, Str const& in) { *out = in; }
    static void read(
        sem::ContextStore*        context,
        std::string const&        out,
        proto_write_accessor<Str> in) {
        in.get() = out;
    }
};

template <>
struct proto_serde<std::string, std::string> {
    static void read(
        sem::ContextStore*                context,
        std::string const&                out,
        proto_write_accessor<std::string> in) {
        in.get() = out;
    }
};


template <>
struct proto_serde<int, int> {
    static void read(
        sem::ContextStore*        context,
        int const&                out,
        proto_write_accessor<int> in) {
        in.get() = out;
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::SubtreeLog::DescribedLog> {
    static void write(
        Proto*                               out,
        sem::SubtreeLog::DescribedLog const& in) {}
    static void read(
        sem::ContextStore*                                  context,
        Proto const&                                        out,
        proto_write_accessor<sem::SubtreeLog::DescribedLog> in) {}
};


template <>
struct proto_serde<orgproto::UserTime, UserTime> {
    static void write(orgproto::UserTime* out, UserTime const& in) {
        out->set_time(absl::ToUnixSeconds(in.time));
        out->set_zone(in.zone.name());
        out->set_align(static_cast<orgproto::Alignment>(in.align));
    }
    static void read(
        sem::ContextStore*             context,
        orgproto::UserTime const&      out,
        proto_write_accessor<UserTime> in) {
        in.get().time = absl::FromUnixSeconds(out.time());
        absl::TimeZone tz;
        if (!absl::LoadTimeZone(out.zone(), &tz)) {}
        in.get().zone  = tz;
        in.get().align = static_cast<UserTime::Alignment>(out.align());
    }
};
