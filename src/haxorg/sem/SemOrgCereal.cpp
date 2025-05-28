#include "SemOrgCereal.hpp"
#include "msgpack.hpp"

#include <hstd/system/reflection.hpp>

int level = 0;

// #define __trace_call()                                                    \
//     std::cerr << fmt(                                                     \
//         "{}Calling {}", hstd::Str{level++, ' '}, __PRETTY_FUNCTION__)     \
//               << std::endl;                                               \
//     auto __scope = hstd::finally{[&]() { --level; }};

#define __trace_call()

using namespace org::imm;


namespace msgpack {
inline namespace MSGPACK_DEFAULT_API_NS {
namespace adaptor {

template <typename T, typename Stream>
void pack_field(
    msgpack::packer<Stream>& o,
    std::string const&       name,
    T const&                 value) {
    o.pack(name);
    o.pack(value);
}

template <typename T>
void convert_field(msgpack::object_kv* p, T& value) {
    p->val.convert(value);
}

hstd::generator<msgpack::object_kv*> convert_map_pairs(
    msgpack::object const& o) {
    msgpack::object_kv*       p(o.via.map.ptr);
    msgpack::object_kv* const pend(o.via.map.ptr + o.via.map.size);
    for (; p != pend; ++p) { co_yield p; }
}

hstd::generator<msgpack::object*> convert_array_items(
    msgpack::object const& o) {
    msgpack::object*       p    = o.via.array.ptr;
    msgpack::object* const pend = o.via.array.ptr + o.via.array.size;
    for (; p != pend; ++p) { co_yield p; }
}

struct htype_error : hstd::CRTP_hexception<htype_error> {};


template <typename T>
void expect_map(
    msgpack::object const& o,
    int                    size     = -1,
    int                    line     = __builtin_LINE(),
    char const*            function = __builtin_FUNCTION(),
    char const*            file     = __builtin_FILE()) {
    if (o.type != msgpack::type::MAP) {
        throw htype_error::init(
            hstd::fmt(
                "expected array, got {} in {}",
                o.type,
                hstd::value_metadata<T>::typeName()),
            line,
            function);
    }
    if (size != -1) {
        if (o.via.map.size != size) {
            throw htype_error::init(
                hstd::fmt(
                    "map size does not match, expected {} got {} in {}",
                    size,
                    o.via.map.size,
                    hstd::value_metadata<T>::typeName()),
                line,
                function);
        }
    }
}

template <typename T>
void expect_array(
    msgpack::object const& o,
    int                    size,
    int                    line     = __builtin_LINE(),
    char const*            function = __builtin_FUNCTION(),
    char const*            file     = __builtin_FILE()) {
    if (o.type != msgpack::type::ARRAY) {
        throw htype_error::init(
            hstd::fmt(
                "expected map, got {} in {}",
                o.type,
                hstd::value_metadata<T>::typeName()),
            line,
            function);
    }
    if (size != -1) {
        if (o.via.array.size != size) {
            throw htype_error::init(
                hstd::fmt(
                    "array size does not match, expected {} got {} in {}",
                    size,
                    o.via.map.size,
                    hstd::value_metadata<T>::typeName()),
                line,
                function);
        }
    }
}

template <typename... Args>
struct convert<std::variant<Args...>> {
    using VT = std::variant<Args...>;
    msgpack::object const& operator()(
        msgpack::object const& o,
        std::variant<Args...>& v) const {
        expect_array<VT>(o, 2);

        VT result = hstd::variant_from_index<VT>(
            o.via.array.ptr[0].as<int>());
        std::visit(
            [&](auto& out) { o.via.array.ptr[1].convert(out); }, result);

        return o;
    }
};

template <typename... Args>
struct pack<std::variant<Args...>> {
    using VT = std::variant<Args...>;
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&     o,
        std::variant<Args...> const& v) const {
        o.pack_array(2);
        o.pack(v.index());
        std::visit([&](auto const& it) { o.pack(it); }, v);
        return o;
    }
};


template <hstd::IsEnum E>
struct convert<E> {
    msgpack::object const& operator()(msgpack::object const& o, E& v)
        const {
        if (o.type != msgpack::type::POSITIVE_INTEGER) {
            throw msgpack::type_error();
        }

        v = static_cast<E>(o.via.u64);
        return o;
    }
};

template <hstd::IsEnum E>
struct pack<E> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, E const& v)
        const {
        o.pack(static_cast<hstd::u64>(v));
        return o;
    }
};


template <>
struct convert<cctz::time_zone> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        cctz::time_zone&       v) const {
        expect_map<cctz::time_zone>(o, 1);
        std::string name;
        o.convert(name);
        cctz::load_time_zone(name, &v);
        return o;
    }
};

template <>
struct pack<cctz::time_zone> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        cctz::time_zone const&   v) const {
        o.pack_map(1);
        pack_field(o, "name", v.name());
        return o;
    }
};


template <>
struct convert<cctz::civil_second> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        cctz::civil_second&    v) const {
        expect_map<cctz::civil_second>(o, 6);
        int                 year{};
        int                 month{};
        int                 day{};
        int                 hour{};
        int                 minute{};
        int                 second{};
        msgpack::object_kv* p(o.via.map.ptr);
        convert_field(p, year);
        convert_field(p, month);
        convert_field(p, day);
        convert_field(p, hour);
        convert_field(p, minute);
        convert_field(p, second);
        v = cctz::civil_second{year, month, day, hour, minute, second};
        return o;
    }
};

template <>
struct pack<cctz::civil_second> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&  o,
        cctz::civil_second const& v) const {
        o.pack_map(6);
        pack_field(o, "year", v.year());
        pack_field(o, "month", v.month());
        pack_field(o, "day", v.day());
        pack_field(o, "hour", v.hour());
        pack_field(o, "minute", v.minute());
        pack_field(o, "second", v.second());
        return o;
    }
};

template <>
struct convert<hstd::Str> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        hstd::Str&             v) const {
        o.convert<std::string>(v);
        return o;
    }
};

template <>
struct pack<hstd::Str> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        hstd::Str const&         v) const {
        o.pack<std::string>(v);
        return o;
    }
};


template <>
struct convert<org::imm::ImmId> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        org::imm::ImmId&       v) const {
        typename org::imm::ImmId::IdType id_value{};
        o.convert(id_value);
        v = org::imm::ImmId::FromValue(id_value);
        return o;
    }
};

template <>
struct pack<org::imm::ImmId> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        org::imm::ImmId const&   v) const {
        o.pack(v.getValue());
        return o;
    }
};


template <typename T>
struct convert<org::imm::ImmIdT<T>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        org::imm::ImmIdT<T>&   v) const {
        typename org::imm::ImmIdT<T>::IdType id_value{};
        o.convert(id_value);
        v = org::imm::ImmIdT<T>::FromValue(id_value);
        return o;
    }
};

template <typename T>
struct pack<org::imm::ImmIdT<T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&   o,
        org::imm::ImmIdT<T> const& v) const {
        o.pack(v.getValue());
        return o;
    }
};


template <typename T>
struct convert<immer::box<T>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        immer::box<T>&         v) const {
        T tmp = hstd::SerdeDefaultProvider<T>::get();
        o.convert(tmp);
        v = tmp;
        return o;
    }
};

template <typename T>
struct pack<immer::box<T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        immer::box<T> const&     v) const {
        o.pack(v.get());
        return o;
    }
};


template <typename T>
struct convert<immer::flex_vector<T>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        immer::flex_vector<T>& v) const {
        if (o.type != msgpack::type::ARRAY) {
            throw msgpack::type_error();
        }

        immer::flex_vector_transient<T> tmp = v.transient();
        for (auto p : convert_array_items(o)) {
            T tmp_value = hstd::SerdeDefaultProvider<T>::get();
            p->convert(tmp_value);
            tmp.push_back(tmp_value);
        }

        v = tmp.persistent();

        return o;
    }
};

template <typename T>
struct pack<immer::flex_vector<T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&     o,
        immer::flex_vector<T> const& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for (auto const& it : v) { o.pack(it); }
        return o;
    }
};

template <typename T, typename Container>
struct convert_iterable_sequence {
    msgpack::object const& operator()(
        msgpack::object const& o,
        Container&             v) const {
        if (o.type != msgpack::type::ARRAY) {
            throw msgpack::type_error();
        }
        v.reserve(o.via.array.size);
        for (auto p : convert_array_items(o)) {
            T tmp = hstd::SerdeDefaultProvider<T>::get();
            p->convert(tmp);
            v.push_back(tmp);
        }

        return o;
    }
};

template <typename T>
struct convert<hstd::Vec<T>>
    : public convert_iterable_sequence<T, hstd::Vec<T>> {};


template <typename T>
struct pack<hstd::Vec<T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        hstd::Vec<T> const&      v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for (auto const& it : v) { o.pack(it); }
        return o;
    }
};

template <typename T, int Size>
struct convert<hstd::SmallVec<T, Size>>
    : convert_iterable_sequence<T, hstd::SmallVec<T, Size>> {};

template <typename T, int Size>
struct pack<hstd::SmallVec<T, Size>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&       o,
        hstd::SmallVec<T, Size> const& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for (auto const& it : v) { o.pack(it); }
        return o;
    }
};


template <typename K, typename V>
struct convert<immer::map<K, V>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        immer::map<K, V>&      v) const {
        if (o.type != msgpack::type::MAP) { throw msgpack::type_error(); }
        auto tmp = v.transient();
        for (auto p : convert_map_pairs(o)) {
            K key   = hstd::SerdeDefaultProvider<K>::get();
            V value = hstd::SerdeDefaultProvider<V>::get();
            p->key.convert(key);
            p->val.convert(value);
            tmp.set(key, value);
        }

        v = tmp.persistent();

        return o;
    }
};

template <typename K, typename V>
struct pack<immer::map<K, V>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        immer::map<K, V> const&  v) const {

        uint32_t size = checked_get_container_size(v.size());
        o.pack_map(size);
        for (auto const& [key, value] : v) {
            o.pack(key);
            o.pack(value);
        }

        return o;
    }
};


template <typename K, typename V>
struct convert<hstd::ext::ImmMap<K, V>> {
    msgpack::object const& operator()(
        msgpack::object const&   o,
        hstd::ext::ImmMap<K, V>& v) const {
        o.convert<immer::map<K, V>>(v);
        return o;
    }
};

template <typename K, typename V>
struct pack<hstd::ext::ImmMap<K, V>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&       o,
        hstd::ext::ImmMap<K, V> const& v) const {
        o.pack<immer::map<K, V>>(v);
        return o;
    }
};


template <typename K, typename V>
struct convert<hstd::UnorderedMap<K, V>> {
    msgpack::object const& operator()(
        msgpack::object const&    o,
        hstd::UnorderedMap<K, V>& v) const {
        o.convert<std::unordered_map<K, V>>(v);
        return o;
    }
};

template <typename K, typename V>
struct pack<hstd::UnorderedMap<K, V>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&        o,
        hstd::UnorderedMap<K, V> const& v) const {
        o.pack<std::unordered_map<K, V>>(v);
        return o;
    }
};


template <hstd::dod::IsIdType Id, typename T>
struct convert<hstd::dod::Store<Id, T>> {
    msgpack::object const& operator()(
        msgpack::object const&   o,
        hstd::dod::Store<Id, T>& v) const {
        msgpack::object_kv* p(o.via.map.ptr);
        p->val.convert(v.content);
        return o;
    }
};

template <hstd::dod::IsIdType Id, typename T>
struct pack<hstd::dod::Store<Id, T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&       o,
        hstd::dod::Store<Id, T> const& v) const {
        o.pack_map(1);
        pack_field(o, "content", v.content);
        return o;
    }
};


template <hstd::DescribedRecord T>
struct convert<T> {
    msgpack::object const& operator()(msgpack::object const& o, T& v)
        const {
        int size = 0;
        hstd::for_each_field_value_with_bases(
            v, [&](char const*, auto const& field) { ++size; });

        expect_map<T>(o, size);

        msgpack::object_kv*       p(o.via.map.ptr);
        msgpack::object_kv* const pend(o.via.map.ptr + o.via.map.size);
        hstd::for_each_field_value_with_bases(
            v, [&](char const*, auto& field) {
                p->val.convert(field);
                ++p;
            });
        return o;
    }
};

template <hstd::DescribedRecord T>
struct pack<T> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, T const& v)
        const {
        int size = 0;
        hstd::for_each_field_value_with_bases(
            v, [&](char const*, auto const& field) { ++size; });

        o.pack_map(size);
        hstd::for_each_field_value_with_bases(
            v, [&](char const* name, auto const& field) {
                pack_field(o, name, field);
            });
        return o;
    }
};

template <>
struct convert<ImmAstStore> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        ImmAstStore&           v) const {
#define _kind(__Kind) +1;
        constexpr int store_size = 0 EACH_SEM_ORG_KIND(_kind);
#undef _kind

        expect_map<ImmAstStore>(o, store_size);

#define _kind(__Kind) o.convert(v.store##__Kind);
        EACH_SEM_ORG_KIND(_kind);
#undef _kind
        return o;
    }
};

template <>
struct pack<ImmAstStore> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        ImmAstStore const&       v) const {
#define _kind(__Kind) +1;
        constexpr int store_size = 0 EACH_SEM_ORG_KIND(_kind);
#undef _kind

        o.pack_map(store_size);

#define _kind(__Kind) o.pack(v.store##__Kind);
        EACH_SEM_ORG_KIND(_kind);
#undef _kind
        return o;
    }
};

template <typename T>
struct pack<std::shared_ptr<T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&  o,
        std::shared_ptr<T> const& v) const {
        if (v) {
            return o.pack(*v);
        } else {
            return o.pack_nil();
        }
    }
};


template <>
struct convert<std::shared_ptr<ImmAstContext>> {
    msgpack::object const& operator()(
        msgpack::object const&          o,
        std::shared_ptr<ImmAstContext>& v) const {
        expect_map<std::shared_ptr<ImmAstContext>>(o, 2);
        msgpack::object_kv* p(o.via.map.ptr);
        convert_field(p, *v->store);
        convert_field(p, *v->currentTrack);
        return o;
    }
};

template <>
struct pack<std::shared_ptr<ImmAstContext>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&              o,
        std::shared_ptr<ImmAstContext> const& v) const {
        o.pack_map(2);
        pack_field(o, "store", *v->store);
        pack_field(o, "currentTrack", *v->currentTrack);
        return o;
    }
};


} // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

std::string org::imm::serializeToText(
    const std::shared_ptr<ImmAstContext>& store) {

    std::stringstream oss{};

    msgpack::pack(oss, store);
    oss.seekg(0);

    std::string tmp{oss.str()};

    return tmp;
}

void org::imm::serializeFromText(
    std::string const& binary,

    std::shared_ptr<ImmAstContext>& store) {
    msgpack::object_handle o = msgpack::unpack(
        binary.data(), binary.size());
    msgpack::object                              deserialized = o.get();
    msgpack::type::tuple<int, bool, std::string> dst;
    deserialized.convert(store);
}
