#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <SemOrgProto.pb.h>
#include <concepts>


template <>
struct hstd::SerdeDefaultProvider<
    org::sem::BlockCodeEvalResult::OrgValue> {
    static org::sem::BlockCodeEvalResult::OrgValue get() {
        return org::sem::BlockCodeEvalResult::OrgValue{};
    }
};

template <>
struct hstd::SerdeDefaultProvider<org::sem::BlockCodeEvalResult> {
    static org::sem::BlockCodeEvalResult get() {
        return org::sem::BlockCodeEvalResult{
            org::sem::BlockCodeEvalResult::OrgValue{}};
    }
};

namespace org::algo {

template <typename Proto, typename T>
struct proto_serde {};

namespace gpb = ::google::protobuf;

template <typename T>
struct proto_org_map {};

#define _map(__Kind)                                                      \
    template <>                                                           \
    struct proto_org_map<::orgproto::__Kind> {                            \
        using org_kind = org::sem::__Kind;                                \
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
struct proto_write_accessor<hstd::Opt<T>>
    : proto_write_accessor_base<
          hstd::Opt<T>,
          proto_write_accessor<hstd::Opt<T>>> {

    proto_write_accessor<T> for_value() {
        return proto_write_accessor<T>{
            [impl = this->impl]() -> T& { return impl().value(); }};
    }
};


template <hstd::IsRecord T>
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
        static void init(Var& variant) {
            variant = variant_from_index<Var>(Field);
        }
    };

    template <typename Var, int Field>
    struct variant_init<sem::SemId<sem::Org>, Var, Field> {
        static void init(Var& variant) {
            auto tmp = sem::SemId<sem::Org>::Nil();
            variant  = tmp;
        }
    };

    template <typename FieldType, typename Var, int Field>
    struct variant_init<sem::SemId<FieldType>, Var, Field> {
        static void init(Var& variant) {
            auto tmp = sem::SemId<FieldType>::Nil();
            variant  = tmp;
        }
    };

    template <
        int N,
        typename F,
        typename VarType = std::variant_alternative_t<N, F>>
    proto_write_accessor<VarType> for_field_variant(F T::*field) {
        return proto_write_accessor<VarType>{
            [impl = this->impl, field]() -> VarType& {
                if ((impl().*field).index() != N) {
                    variant_init<VarType, F, N>::init(impl().*field);
                }
                return std::get<VarType>(impl().*field);
            }};
    }
};


template <typename T>
struct proto_init {
    static void init_default(T& value) {}
};

template <typename T>
struct proto_init<hstd::Opt<T>> {
    static void init_default(hstd::Opt<T>& value) {
        value = hstd::SerdeDefaultProvider<T>::get();
    }
};


template <>
struct proto_init<sem::SemId<sem::Org>> {
    static void init_default(

        sem::SemId<sem::Org>& value) {
        value = sem::SemId<sem::Org>::Nil();
    }
};

template <typename T>
struct proto_init<sem::SemId<T>> {
    static void init_default(sem::SemId<T>& value) {
        value = sem::SemId<T>::Nil();
    }
};

template <>
struct proto_init<hstd::Opt<sem::SemId<sem::Org>>> {
    static void init_default(hstd::Opt<sem::SemId<sem::Org>>& value) {
        value = sem::SemId<sem::Org>::Nil();
    }
};

template <typename T>
struct proto_init<hstd::Opt<sem::SemId<T>>> {
    static void init_default(hstd::Opt<sem::SemId<T>>& value) {
        value = sem::SemId<T>::Nil();
    }
};

template <typename Proto, typename T>
struct proto_serde<hstd::Opt<Proto>, hstd::Opt<T>> {
    static void write(Proto* out, hstd::Opt<T> const& in) {
        proto_serde<Proto, T>::write(out, in.value());
    }

    static void read(
        Proto const&                       out,
        proto_write_accessor<hstd::Opt<T>> in) {
        proto_init<hstd::Opt<T>>::init_default(in.get());
        proto_serde<Proto, T>::read(out, in.for_value());
    }
};

template <>
struct proto_serde<
    gpb::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>,
    hstd::Vec<sem::Tblfm::Assign::Flag>> {
    using Proto = orgproto::Tblfm_Assign_Flag;
    using T     = sem::Tblfm::Assign::Flag;
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        hstd::Vec<T> const&           in) {
        for (auto const& it : in) { out->Add(static_cast<Proto>(it)); }
    }

    static void write(
        gpb::RepeatedField<int>* out,
        hstd::Vec<T> const&      in) {
        for (auto const& it : in) { out->Add(static_cast<int>(it)); }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const& out,
        proto_write_accessor<hstd::Vec<T>>  in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            ref       = static_cast<T>(it);
        }
    }

    static void read(
        gpb::RepeatedField<int> const&     out,
        proto_write_accessor<hstd::Vec<T>> in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            ref       = static_cast<T>(it);
        }
    }
};

template <typename Proto, typename T>
struct proto_serde<gpb::RepeatedPtrField<Proto>, hstd::Vec<T>> {
    static void write(
        gpb::RepeatedPtrField<Proto>* out,
        hstd::Vec<T> const&           in) {
        for (auto const& it : in) {
            proto_serde<Proto, T>::write(out->Add(), it);
        }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const& out,
        proto_write_accessor<hstd::Vec<T>>  in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            proto_serde<Proto, T>::read(
                it, proto_write_accessor<T>::for_ref(ref));
        }
    }
};

template <typename Proto>
struct proto_serde<
    gpb::RepeatedPtrField<Proto>,
    hstd::Vec<sem::SemId<sem::Org>>> {
    static void write(
        gpb::RepeatedPtrField<Proto>*          out,
        hstd::Vec<sem::SemId<sem::Org>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId<sem::Org>>::write(
                out->Add(), it);
        }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const&                   out,
        proto_write_accessor<hstd::Vec<sem::SemId<sem::Org>>> in) {
        for (auto const& it : out) {
            auto& items = in.get();
            items.emplace_back(sem::SemId<sem::Org>::Nil());
            proto_serde<Proto, sem::SemId<sem::Org>>::read(
                it,
                proto_write_accessor<sem::SemId<sem::Org>>{
                    [&in]() -> sem::SemId<sem::Org>& {
                        return in.get().back();
                    }});
        }
    }
};

template <typename Proto, typename T>
struct proto_serde<
    gpb::RepeatedPtrField<Proto>,
    hstd::Vec<sem::SemId<T>>> {
    static void write(
        gpb::RepeatedPtrField<Proto>*   out,
        hstd::Vec<sem::SemId<T>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId<sem::Org>>::write(
                out->Add(), it.asOrg());
        }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const&            out,
        proto_write_accessor<hstd::Vec<sem::SemId<T>>> in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back(sem::SemId<T>::Nil());
            proto_serde<Proto, sem::SemId<T>>::read(
                it, proto_write_accessor<sem::SemId<T>>::for_ref(ref));
        }
    }
};


template <typename T>
struct proto_serde<gpb::RepeatedField<::int32_t>, hstd::Vec<T>> {
    static void write(
        gpb::RepeatedField<::int32_t>* out,
        hstd::Vec<T> const&            in) {
        for (auto const& it : in) { out->Add(it); }
    }

    static void read(
        gpb::RepeatedField<::int32_t> const& out,
        proto_write_accessor<hstd::Vec<T>>   in) {
        for (auto const& it : out) { in.get().push_back(it); }
    }
};

template <class T>
concept IsDefaultConstructible = std::is_default_constructible_v<T>;

template <class T>
concept NonDefaultConstructible = !IsDefaultConstructible<T>;

template <typename ProtoKey, typename ProtoVal, typename K, typename V>
struct proto_serde<
    gpb::Map<ProtoKey, ProtoVal>,
    hstd::UnorderedMap<K, V>> {
    static void write(
        gpb::Map<ProtoKey, ProtoVal>*   out,
        hstd::UnorderedMap<K, V> const& in) {
        for (auto const& [k, v] : in) {
            proto_serde<ProtoVal, V>::write(&out->operator[](k), v);
        }
    }

    template <IsDefaultConstructible U = V>
    static void read(
        gpb::Map<ProtoKey, ProtoVal> const&            out,
        proto_write_accessor<hstd::UnorderedMap<K, V>> in) {
        for (auto const& [key, val] : out) {
            in.get().insert_or_assign(
                key, hstd::SerdeDefaultProvider<V>::get());
            proto_serde<ProtoVal, V>::read(
                val, proto_write_accessor<V>{[&in, &key]() -> V& {
                    return in.get().at(key);
                }});
        }
    }
};

template <>
struct proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>> {
    static void write(
        orgproto::AnyNode*          out,
        sem::SemId<sem::Org> const& in);

    static void write(
        gpb::RepeatedPtrField<orgproto::AnyNode>* out,
        hstd::Vec<sem::SemId<sem::Org>> const&    in) {
        for (auto const& it : in) {
            proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
                out->Add(), it);
        }
    }

    static void read(
        orgproto::AnyNode const&                   out,
        proto_write_accessor<sem::SemId<sem::Org>> in);

    static void read(
        gpb::RepeatedPtrField<orgproto::AnyNode> const&       out,
        proto_write_accessor<hstd::Vec<sem::SemId<sem::Org>>> in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::SemId<sem::Org>> {
    static void write(Proto* out, sem::SemId<sem::Org> const& in) {
        using org_type = proto_org_map<Proto>::org_kind;
        proto_serde<Proto, org_type>::write(out, *in.as<org_type>().get());
    }

    static void read(
        Proto const&                               out,
        proto_write_accessor<sem::SemId<sem::Org>> in) {
        using org_type = proto_org_map<Proto>::org_kind;
        if (in.get().isNil()) { in.get() = sem::SemId<org_type>::New(); }
        sem::SemId<sem::Org> id = in.get();
        proto_serde<Proto, org_type>::read(
            out, proto_write_accessor<org_type>{[id]() -> org_type& {
                return *id.as<org_type>().get();
            }});
        CHECK(!in.get().isNil());
    }
};


template <typename T>
struct proto_serde<orgproto::AnyNode, sem::SemId<T>> {
    static void write(orgproto::AnyNode* out, sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
            out, in.asOrg());
    }

    template <typename Proto>
    static void write(Proto* out, sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
            out->Add(), in.asOrg());
    }

    template <typename Proto>
    static void write(
        gpb::RepeatedPtrField<Proto>*   out,
        hstd::Vec<sem::SemId<T>> const& in) {
        LOG(FATAL) << "??";
    }
};

template <typename Proto, typename T>
struct proto_serde<Proto, sem::SemId<T>> {
    static void write(orgproto::AnyNode* out, sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
            out, in.asOrg());
    }

    static void write(Proto* out, sem::SemId<T> const& in) {
        proto_serde<Proto, sem::SemId<sem::Org>>::write(out, in.asOrg());
    }

    static void write(
        gpb::RepeatedPtrField<Proto>*   out,
        hstd::Vec<sem::SemId<T>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, sem::SemId<sem::Org>>::write(
                out->Add(), it.asOrg());
        }
    }

    static void read(
        Proto const&                        out,
        proto_write_accessor<sem::SemId<T>> in) {
        sem::SemId<sem::Org> tmp = in.get().asOrg();
        proto_serde<Proto, sem::SemId<sem::Org>>::read(
            out, proto_write_accessor<sem::SemId<sem::Org>>::for_ref(tmp));
        in.get() = tmp.template as<T>();
        CHECK(!in.get().isNil());
    }

    static void read(
        orgproto::AnyNode const&            out,
        proto_write_accessor<sem::SemId<T>> in) {
        sem::SemId tmp = in.get();
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
            out, proto_write_accessor<sem::SemId<sem::Org>>::for_ref(tmp));
        in.get() = tmp.template as<T>();
        CHECK(!in.get().isNil());
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Org> {
    static void write(Proto* out, sem::Org const& in) {
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
            out->mutable_subnodes(), in.subnodes);
        out->set_statickind(
            static_cast<orgproto::OrgSemKind>(in.getKind()));
    }

    static void read(Proto const& out, proto_write_accessor<sem::Org> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<sem::SemId<sem::Org>>>::
            read(out.subnodes(), in.for_field(&sem::Org::subnodes));
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Stmt> {
    static void write(Proto* out, sem::Stmt const& in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<sem::SemId<sem::Org>>>::
            write(out->mutable_attached(), in.attached);
    }

    static void read(
        Proto const&                    out,
        proto_write_accessor<sem::Stmt> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<sem::SemId<sem::Org>>>::
            read(out.attached(), in.for_field(&sem::Stmt::attached));
    }
};


template <typename Proto>
struct proto_serde<Proto, sem::Leaf> {
    static void write(Proto* out, sem::Leaf const& in) {
        out->set_text(in.text);
    }
    static void read(
        Proto const&                    out,
        proto_write_accessor<sem::Leaf> in) {
        in.get().text = out.text();
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Block> {
    static void write(Proto* out, sem::Block const& in);
    static void read(
        Proto const&                     out,
        proto_write_accessor<sem::Block> in);
};

template <typename Proto>
struct proto_serde<Proto, sem::Cmd> {
    static void write(Proto* out, sem::Cmd const& in);
    static void read(Proto const& out, proto_write_accessor<sem::Cmd> in);
};

template <>
struct proto_serde<orgproto::LineCol, org::parse::LineCol> {
    static void write(
        orgproto::LineCol*         out,
        org::parse::LineCol const& in) {
        out->set_line(in.line);
        out->set_column(in.column);
        out->set_pos(in.pos);
    }
    static void read(
        orgproto::LineCol const&                  out,
        proto_write_accessor<org::parse::LineCol> in) {
        in.get().pos    = out.pos();
        in.get().line   = out.line();
        in.get().column = out.column();
    }
};

template <>
struct proto_serde<std::string, hstd::Str> {
    static void write(std::string* out, hstd::Str const& in) { *out = in; }
    static void read(
        std::string const&              out,
        proto_write_accessor<hstd::Str> in) {
        in.get() = out;
    }
};

template <>
struct proto_serde<std::string, std::string> {
    static void read(
        std::string const&                out,
        proto_write_accessor<std::string> in) {
        in.get() = out;
    }
};


template <>
struct proto_serde<bool, bool> {
    static void read(bool const& out, proto_write_accessor<bool> in) {
        in.get() = out;
    }
};


template <>
struct proto_serde<::orgproto::OrgJson, org::sem::OrgJson> {
    static void read(
        ::orgproto::OrgJson const&         out,
        proto_write_accessor<sem::OrgJson> in) {
        in.get().value = json::parse(out.raw());
    }

    static void write(::orgproto::OrgJson* out, sem::OrgJson const& in) {
        out->set_raw(in.getRef().dump());
    }
};

template <>
struct proto_serde<int, int> {
    static void read(int const& out, proto_write_accessor<int> in) {
        in.get() = out;
    }
};

template <>
struct proto_serde<float, float> {
    static void write(float* out, float const& in) { *out = in; }
    static void read(float const& out, proto_write_accessor<float> in) {
        in.get() = out;
    }
};


// template <typename Proto>
// struct proto_serde<Proto, sem::SubtreeLog::DescribedLog> {
//     static void write(
//         Proto*                               out,
//         sem::SubtreeLog::DescribedLog const& in) {}
//     static void read(
//         Proto const&                                        out,
//         proto_write_accessor<sem::SubtreeLog::DescribedLog> in) {}
// };


template <>
struct proto_serde<orgproto::hstd::UserTime, hstd::UserTime> {
    static void write(
        orgproto::hstd::UserTime* out,
        hstd::UserTime const&     in) {
        out->set_time(absl::ToUnixSeconds(in.time));
        if (in.zone) { out->set_zone(in.zone->name()); }
        out->set_align(static_cast<orgproto::Alignment>(in.align));
    }
    static void read(
        orgproto::hstd::UserTime const&      out,
        proto_write_accessor<hstd::UserTime> in) {
        in.get().time = absl::FromUnixSeconds(out.time());
        if (out.has_zone()) {
            absl::TimeZone tz;
            if (!absl::LoadTimeZone(out.zone(), &tz)) {}
            in.get().zone = tz;
        }
        in.get().align = static_cast<hstd::UserTime::Alignment>(
            out.align());
    }
};

template <typename Out>
struct proto_serde<Out, sem::CmdInclude::IncludeBase> {
    static void write(Out* out, sem::CmdInclude::IncludeBase const& in) {}
    static void read(
        Out const&                                         out,
        proto_write_accessor<sem::CmdInclude::IncludeBase> in) {}
};

} // namespace org::algo
