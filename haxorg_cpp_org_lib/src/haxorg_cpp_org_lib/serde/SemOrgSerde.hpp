#pragma once

#include <haxorg_cpp_org_lib/sem/SemOrg.hpp>
#include <hstd_cpp_lib/ext/hstd_serde.hpp>


#if ORG_BUILD_WITH_PROTOBUF && !ORG_BUILD_EMCC
#    include <concepts>
#    include <src/haxorg/serde/SemOrgProto.pb.h>

namespace hstd::serde {

namespace gpb = ::google::protobuf;

template <typename T>
struct proto_org_map {};

#    define _map(__Kind)                                                                 \
        template <>                                                                      \
        struct proto_org_map<::orgproto::__Kind> {                                       \
            using org_kind = org::sem::__Kind;                                           \
        };

EACH_SEM_ORG_KIND(_map)


#    undef _map

template <typename Var, int Field>
struct proto_variant_init<org::sem::SemId<org::sem::Org>, Var, Field> {
    static void init(Var& variant) {
        auto tmp = org::sem::SemId<org::sem::Org>::Nil();
        variant  = tmp;
    }
};

template <typename FieldType, typename Var, int Field>
struct proto_variant_init<org::sem::SemId<FieldType>, Var, Field> {
    static void init(Var& variant) {
        auto tmp = org::sem::SemId<FieldType>::Nil();
        variant  = tmp;
    }
};

template <>
struct proto_init<org::sem::SemId<org::sem::Org>> {
    static void init_default(org::sem::SemId<org::sem::Org>& value) {
        value = org::sem::SemId<org::sem::Org>::Nil();
    }
};

template <typename T>
struct proto_init<org::sem::SemId<T>> {
    static void init_default(org::sem::SemId<T>& value) {
        value = org::sem::SemId<T>::Nil();
    }
};

template <>
struct proto_init<hstd::Opt<org::sem::SemId<org::sem::Org>>> {
    static void init_default(hstd::Opt<org::sem::SemId<org::sem::Org>>& value) {
        value = org::sem::SemId<org::sem::Org>::Nil();
    }
};

template <typename T>
struct proto_init<hstd::Opt<org::sem::SemId<T>>> {
    static void init_default(hstd::Opt<org::sem::SemId<T>>& value) {
        value = org::sem::SemId<T>::Nil();
    }
};

// TODO: Extract this to the hstd/ext/hstd_serde.hpp file for general use.
// <<proto-serde-extract-to-general>>
template <>
struct proto_serde<
    gpb::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>,
    hstd::Vec<org::sem::Tblfm::Assign::Flag>> {
    using Proto = orgproto::Tblfm_Assign_Flag;
    using T     = org::sem::Tblfm::Assign::Flag;
    static void write(gpb::RepeatedPtrField<Proto>* out, hstd::Vec<T> const& in) {
        for (auto const& it : in) { out->Add(static_cast<Proto>(it)); }
    }

    static void write(gpb::RepeatedField<int>* out, hstd::Vec<T> const& in) {
        for (auto const& it : in) { out->Add(static_cast<int>(it)); }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const& out,
        proto_write_accessor<hstd::Vec<T>>  in) {
        in.get().reserve(out.size());
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            ref       = static_cast<T>(it);
        }
    }

    static void read(
        gpb::RepeatedField<int> const&     out,
        proto_write_accessor<hstd::Vec<T>> in) {
        in.get().reserve(out.size());
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            ref       = static_cast<T>(it);
        }
    }
};


template <typename Proto>
struct proto_serde<
    gpb::RepeatedPtrField<Proto>,
    hstd::Vec<org::sem::SemId<org::sem::Org>>> {
    static void write(
        gpb::RepeatedPtrField<Proto>*                    out,
        hstd::Vec<org::sem::SemId<org::sem::Org>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, org::sem::SemId<org::sem::Org>>::write(out->Add(), it);
        }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const&                             out,
        proto_write_accessor<hstd::Vec<org::sem::SemId<org::sem::Org>>> in) {
        for (auto const& it : out) {
            auto& items = in.get();
            items.emplace_back(org::sem::SemId<org::sem::Org>::Nil());
            proto_serde<Proto, org::sem::SemId<org::sem::Org>>::read(
                it,
                proto_write_accessor<org::sem::SemId<org::sem::Org>>{
                    [&in]() -> org::sem::SemId<org::sem::Org>& {
                        return in.get().back();
                    }});
        }
    }
};

template <typename Proto, typename T>
struct proto_serde<gpb::RepeatedPtrField<Proto>, hstd::Vec<org::sem::SemId<T>>> {
    static void write(
        gpb::RepeatedPtrField<Proto>*        out,
        hstd::Vec<org::sem::SemId<T>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, org::sem::SemId<org::sem::Org>>::write(
                out->Add(), it.asOrg());
        }
    }

    static void read(
        gpb::RepeatedPtrField<Proto> const&                 out,
        proto_write_accessor<hstd::Vec<org::sem::SemId<T>>> in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back(org::sem::SemId<T>::Nil());
            proto_serde<Proto, org::sem::SemId<T>>::read(
                it, proto_write_accessor<org::sem::SemId<T>>::for_ref(ref));
        }
    }
};


template <typename T>
struct proto_serde<gpb::RepeatedField<::int32_t>, hstd::Vec<T>> {
    static void write(gpb::RepeatedField<::int32_t>* out, hstd::Vec<T> const& in) {
        for (auto const& it : in) { out->Add(it); }
    }

    static void read(
        gpb::RepeatedField<::int32_t> const& out,
        proto_write_accessor<hstd::Vec<T>>   in) {
        for (auto const& it : out) { in.get().push_back(it); }
    }
};


template <>
struct proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>> {
    static void write(orgproto::AnyNode* out, org::sem::SemId<org::sem::Org> const& in);

    static void write(
        gpb::RepeatedPtrField<orgproto::AnyNode>*        out,
        hstd::Vec<org::sem::SemId<org::sem::Org>> const& in) {
        for (auto const& it : in) {
            proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(
                out->Add(), it);
        }
    }

    static void read(
        orgproto::AnyNode const&                             out,
        proto_write_accessor<org::sem::SemId<org::sem::Org>> in);

    static void read(
        gpb::RepeatedPtrField<orgproto::AnyNode> const&                 out,
        proto_write_accessor<hstd::Vec<org::sem::SemId<org::sem::Org>>> in) {
        logic_todo_impl();
    }
};

template <typename Proto>
struct proto_serde<Proto, org::sem::SemId<org::sem::Org>> {
    static void write(Proto* out, org::sem::SemId<org::sem::Org> const& in) {
        using org_type = proto_org_map<Proto>::org_kind;
        proto_serde<Proto, org_type>::write(out, *in.as<org_type>().get());
    }

    static void read(
        Proto const&                                         out,
        proto_write_accessor<org::sem::SemId<org::sem::Org>> in) {
        using org_type = proto_org_map<Proto>::org_kind;
        if (in.get().isNil()) { in.get() = org::sem::SemId<org_type>::New(); }
        org::sem::SemId<org::sem::Org> id = in.get();
        proto_serde<Proto, org_type>::read(
            out, proto_write_accessor<org_type>{[id]() -> org_type& {
                return *id.as<org_type>().get();
            }});
        LOGIC_ASSERTION_CHECK(!in.get().isNil(), "");
    }
};


template <typename T>
struct proto_serde<orgproto::AnyNode, org::sem::SemId<T>> {
    static void write(orgproto::AnyNode* out, org::sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(
            out, in.asOrg());
    }

    template <typename Proto>
    static void write(Proto* out, org::sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(
            out->Add(), in.asOrg());
    }

    template <typename Proto>
    static void write(
        gpb::RepeatedPtrField<Proto>*        out,
        hstd::Vec<org::sem::SemId<T>> const& in) {
        logic_todo_impl();
    }
};

template <typename Proto, typename T>
struct proto_serde<Proto, org::sem::SemId<T>> {
    static void write(orgproto::AnyNode* out, org::sem::SemId<T> const& in) {
        proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(
            out, in.asOrg());
    }

    static void write(Proto* out, org::sem::SemId<T> const& in) {
        proto_serde<Proto, org::sem::SemId<org::sem::Org>>::write(out, in.asOrg());
    }

    static void write(
        gpb::RepeatedPtrField<Proto>*        out,
        hstd::Vec<org::sem::SemId<T>> const& in) {
        for (auto const& it : in) {
            proto_serde<Proto, org::sem::SemId<org::sem::Org>>::write(
                out->Add(), it.asOrg());
        }
    }

    static void read(Proto const& out, proto_write_accessor<org::sem::SemId<T>> in) {
        org::sem::SemId<org::sem::Org> tmp = in.get().asOrg();
        proto_serde<Proto, org::sem::SemId<org::sem::Org>>::read(
            out, proto_write_accessor<org::sem::SemId<org::sem::Org>>::for_ref(tmp));
        in.get() = tmp.template as<T>();
        LOGIC_ASSERTION_CHECK(!in.get().isNil(), "");
    }

    static void read(
        orgproto::AnyNode const&                 out,
        proto_write_accessor<org::sem::SemId<T>> in) {
        org::sem::SemId tmp = in.get();
        proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::read(
            out, proto_write_accessor<org::sem::SemId<org::sem::Org>>::for_ref(tmp));
        in.get() = tmp.template as<T>();
        LOGIC_ASSERTION_CHECK(!in.get().isNil(), "");
    }
};


template <>
struct proto_serde<orgproto::org_parse::SourceLoc, org::parse::SourceLoc> {
    static void write(
        orgproto::org_parse::SourceLoc* out,
        org::parse::SourceLoc const&    in) {
        out->set_line(in.line);
        out->set_column(in.column);
        out->set_pos(in.pos);
        out->mutable_file()->set_id(in.file_id.getValue());
    }
    static void read(
        orgproto::org_parse::SourceLoc const&       out,
        proto_write_accessor<org::parse::SourceLoc> in) {
        in.get().pos     = out.pos();
        in.get().line    = out.line();
        in.get().column  = out.column();
        in.get().file_id = org::parse::SourceFileId::FromValue(out.file().id());
    }
};

template <typename Proto>
struct proto_serde<Proto, org::sem::Org> {
    static void write(Proto* out, org::sem::Org const& in) {
        proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(
            out->mutable_subnodes(), in.subnodes);
        out->set_statickind(static_cast<orgproto::OrgSemKind>(in.getKind()));
        if (in.loc) {
            proto_serde<orgproto::org_parse_SourceLoc, org::parse::SourceLoc>::write(
                out->mutable_loc(), in.loc.value());
        }
    }

    static void read(Proto const& out, proto_write_accessor<org::sem::Org> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<org::sem::SemId<org::sem::Org>>>::
            read(out.subnodes(), in.for_field(&org::sem::Org::subnodes));
        if (out.has_loc()) {
            proto_serde<
                hstd::Opt<orgproto::org_parse_SourceLoc>,
                hstd::Opt<org::parse::SourceLoc>>::
                read(out.loc(), in.for_field(&org::sem::Org::loc));
        }
    }
};

template <typename Proto>
struct proto_serde<Proto, org::sem::Stmt> {
    static void write(Proto* out, org::sem::Stmt const& in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<org::sem::SemId<org::sem::Org>>>::
            write(out->mutable_attached(), in.attached);
    }

    static void read(Proto const& out, proto_write_accessor<org::sem::Stmt> in) {
        proto_serde<
            gpb::RepeatedPtrField<orgproto::AnyNode>,
            hstd::Vec<org::sem::SemId<org::sem::Org>>>::
            read(out.attached(), in.for_field(&org::sem::Stmt::attached));
    }
};


template <typename Proto>
struct proto_serde<Proto, org::sem::Leaf> {
    static void write(Proto* out, org::sem::Leaf const& in) { out->set_text(in.text); }
    static void read(Proto const& out, proto_write_accessor<org::sem::Leaf> in) {
        in.get().text = out.text();
    }
};

template <typename Proto>
struct proto_serde<Proto, org::sem::Block> {
    static void write(Proto* out, org::sem::Block const& in);
    static void read(Proto const& out, proto_write_accessor<org::sem::Block> in);
};

template <typename Proto>
struct proto_serde<Proto, org::sem::Cmd> {
    static void write(Proto* out, org::sem::Cmd const& in);
    static void read(Proto const& out, proto_write_accessor<org::sem::Cmd> in);
};


template <>
struct proto_serde<::orgproto::OrgJson, org::sem::OrgJson> {
    static void read(
        ::orgproto::OrgJson const&              out,
        proto_write_accessor<org::sem::OrgJson> in);

    static void write(::orgproto::OrgJson* out, org::sem::OrgJson const& in);
};

// template <typename Proto>
// struct proto_serde<Proto, org::sem::SubtreeLog::DescribedLog> {
//     static void write(
//         Proto*                               out,
//         org::sem::SubtreeLog::DescribedLog const& in) {}
//     static void read(
//         Proto const&                                        out,
//         proto_write_accessor<org::sem::SubtreeLog::DescribedLog> in) {}
// };


inline int64_t civil_second_to_unix_timestamp(cctz::civil_second const& cs) {
    const auto tp = cctz::convert(cs, cctz::utc_time_zone());
    return std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch())
        .count();
}

inline cctz::civil_second unix_timestamp_to_civil_second(int64_t unix_timestamp) {
    const auto tp = std::chrono::system_clock::time_point{
        std::chrono::seconds{unix_timestamp}};
    return cctz::convert(tp, cctz::utc_time_zone());
}

template <>
struct proto_serde<orgproto::hstd::UserTime, hstd::UserTime> {
    static void write(orgproto::hstd::UserTime* out, hstd::UserTime const& in) {
        out->set_time(civil_second_to_unix_timestamp(in.time));
        if (in.zone) { out->set_zone(in.zone->name()); }
        out->set_align(static_cast<orgproto::Alignment>(in.align));
    }
    static void read(
        orgproto::hstd::UserTime const&      out,
        proto_write_accessor<hstd::UserTime> in) {
        in.get().time = unix_timestamp_to_civil_second(out.time());
        if (out.has_zone()) {
            cctz::time_zone tz;
            if (!cctz::load_time_zone(out.zone(), &tz)) {}
            in.get().zone = tz;
        }
        in.get().align = static_cast<hstd::UserTime::Alignment>(out.align());
    }
};

template <typename Out>
struct proto_serde<Out, org::sem::CmdInclude::IncludeBase> {
    static void write(Out* out, org::sem::CmdInclude::IncludeBase const& in) {}
    static void read(
        Out const&                                              out,
        proto_write_accessor<org::sem::CmdInclude::IncludeBase> in) {}
};


} // namespace hstd::serde

#endif
