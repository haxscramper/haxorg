#include <sem/SemOrg.hpp>
#include <SemOrgProto.pb.h>

template <typename Proto, typename T>
struct proto_serde {};

template <typename Proto, typename T>
struct proto_serde<::google::protobuf::RepeatedPtrField<Proto>, Vec<T>> {
    static void write(
        ::google::protobuf::RepeatedPtrField<Proto>* out,
        Vec<T> const&                                in) {
        for (auto const& it : in) {
            proto_serde<Proto, T>::write(out->Add(), it);
        }
    }
};

template <typename T>
struct proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<T>> {
    static void write(
        ::google::protobuf::RepeatedField<::int32_t>* out,
        Vec<T> const&                                 in) {
        for (auto const& it : in) { out->Add(it); }
    }
};

// template <typename T>
// struct proto_serde<
//     ::google::protobuf::RepeatedField<std::string>,
//     Vec<T>> {
//     static void write(
//         ::google::protobuf::RepeatedField<std::string>* out,
//         Vec<T> const&                                   in) {
//         for (auto const& it : in) { out->Add(it); }
//     }
// };


template <typename ProtoKey, typename ProtoVal, typename K, typename V>
struct proto_serde<
    ::google::protobuf::Map<ProtoKey, ProtoVal>,
    UnorderedMap<K, V>> {
    static void write(
        ::google::protobuf::Map<ProtoKey, ProtoVal>* out,
        UnorderedMap<K, V> const&                    in) {
        for (auto const& [k, v] : in) {
            proto_serde<ProtoVal, V>::write(&out->operator[](k), v);
        }
    }
};

template <>
struct proto_serde<orgproto::AnyNode, sem::SemId> {
    static void write(orgproto::AnyNode* out, sem::SemId const& in) {}
    static void write(
        ::google::protobuf::RepeatedPtrField<orgproto::AnyNode>* out,
        Vec<sem::SemId> const&                                   in) {}
};

template <typename T>
struct proto_serde<orgproto::AnyNode, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {}

    template <typename Proto>
    static void write(Proto* out, sem::SemIdT<T> const& in) {}

    template <typename Proto>
    static void write(
        ::google::protobuf::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&                   in) {}
};

template <typename Proto, typename T>
struct proto_serde<Proto, sem::SemIdT<T>> {
    static void write(orgproto::AnyNode* out, sem::SemIdT<T> const& in) {}

    static void write(Proto* out, sem::SemIdT<T> const& in) {}

    static void write(
        ::google::protobuf::RepeatedPtrField<Proto>* out,
        Vec<sem::SemIdT<T>> const&                   in) {}
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

        // out->set_statickind(
        //     static_cast<::orgproto::OrgSemKind>(in.getKind()));
    }
};

template <typename Proto>
struct proto_serde<Proto, sem::Stmt> {
    static void write(Proto* out, sem::Stmt const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::LatexBody> {
    static void write(Proto* out, sem::LatexBody const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Leaf> {
    static void write(Proto* out, sem::Leaf const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Markup> {
    static void write(Proto* out, sem::Markup const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Format> {
    static void write(Proto* out, sem::Format const& in) {}
};


template <typename Proto>
struct proto_serde<Proto, sem::Attached> {
    static void write(Proto* out, sem::Attached const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Block> {
    static void write(Proto* out, sem::Block const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Inline> {
    static void write(Proto* out, sem::Inline const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::Command> {
    static void write(Proto* out, sem::Command const& in) {}
};

template <typename Proto>
struct proto_serde<Proto, sem::LineCommand> {
    static void write(Proto* out, sem::LineCommand const& in) {}
};

template <>
struct proto_serde<std::string, Str> {
    static void write(std::string* out, Str const& in) { *out = in; }
};


template <typename Proto>
struct proto_serde<Proto, sem::SubtreeLog::DescribedLog> {
    static void write(
        Proto*                               out,
        sem::SubtreeLog::DescribedLog const& in) {}
};


template <>
struct proto_serde<orgproto::UserTime, UserTime> {
    static void write(orgproto::UserTime* out, UserTime const& in) {}
};
