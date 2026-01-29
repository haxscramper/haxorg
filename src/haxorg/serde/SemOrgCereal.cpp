#include "SemOrgCereal.hpp"
#include <msgpack.hpp>
#include <string>
#include <format>
#include <nlohmann/json.hpp>
#include <functional>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/stdlib/ContainerAPI.hpp>

namespace {
int level = 0;
}

template <typename Tag>
struct hstd::SerdeDefaultProvider<hstd::ReflPathItem<Tag>> {
    static hstd::ReflPathItem<Tag> get() {
        return hstd::ReflPathItem<Tag>::FromDeref();
    }
};

// #define __trace_call()                                                    \
//     std::cerr << fmt( \
//         "{}Calling {}", \
//         hstd::Str{level++, ' '}, \
//         hstd::value_metadata<decltype(v)>::typeName()) \
//               << std::endl; \
//     auto __scope = hstd::finally{[&]() { --level; }};

#define __trace_call()

using namespace org::imm;

json msgpack_to_json(msgpack::object const& obj) {
    std::function<json(msgpack::object const&)> convert =
        [&](msgpack::object const& o) -> json {
        switch (o.type) {
            case msgpack::type::NIL: return json{};
            case msgpack::type::BOOLEAN: return o.via.boolean;
            case msgpack::type::POSITIVE_INTEGER: return o.via.u64;
            case msgpack::type::NEGATIVE_INTEGER: return o.via.i64;
            case msgpack::type::FLOAT32:
            case msgpack::type::FLOAT64: return o.via.f64;

            case msgpack::type::STR:
                return std::string{o.via.str.ptr, o.via.str.size};

            case msgpack::type::BIN: {
                std::vector<unsigned char> bin_data{
                    o.via.bin.ptr, o.via.bin.ptr + o.via.bin.size};
                return json::binary(bin_data);
            }

            case msgpack::type::ARRAY: {
                json arr = json::array();
                for (uint32_t i = 0; i < o.via.array.size; ++i) {
                    arr.push_back(convert(o.via.array.ptr[i]));
                }
                return arr;
            }

            case msgpack::type::MAP: {
                json obj_json = json::object();
                for (uint32_t i = 0; i < o.via.map.size; ++i) {
                    json value = convert(o.via.map.ptr[i].val);

                    if (o.via.map.ptr[i].key.type == msgpack::type::STR) {
                        obj_json[o.via.map.ptr[i].key.as<std::string>()] = value;
                    } else {
                        json key = convert(o.via.map.ptr[i].key);
                        obj_json[key.dump()] = value;
                    }
                }
                return obj_json;
            }

            case msgpack::type::EXT: {
                json ext_obj    = json::object();
                ext_obj["type"] = o.via.ext.type();
                std::vector<uint8_t> ext_data{
                    o.via.ext.data(), o.via.ext.data() + o.via.ext.size};
                ext_obj["data"] = ext_data;
                return ext_obj;
            }

            default: return json{};
        }
    };

    return convert(obj);
}


std::string format_msgpack_object_type(
    msgpack::type::object_type const& t) {
    switch (t) {
        case msgpack::type::NIL: return "NIL";
        case msgpack::type::BOOLEAN: return "BOOLEAN";
        case msgpack::type::POSITIVE_INTEGER: return "POSITIVE_INTEGER";
        case msgpack::type::NEGATIVE_INTEGER: return "NEGATIVE_INTEGER";
        case msgpack::type::FLOAT32: return "FLOAT32";
        case msgpack::type::FLOAT: return "FLOAT";
        case msgpack::type::STR: return "STR";
        case msgpack::type::BIN: return "BIN";
        case msgpack::type::ARRAY: return "ARRAY";
        case msgpack::type::MAP: return "MAP";
        case msgpack::type::EXT: return "EXT";
    }
}

std::string msgpack_object_to_tree(
    msgpack::object const& o,
    int                    depth = 0) {
    std::ostringstream ss;

    std::function<void(msgpack::object const&, int)> traverse =
        [&](msgpack::object const& obj, int d) {
            std::string indent(d * 2, ' ');

            switch (obj.type) {
                case msgpack::type::NIL:
                    ss << std::format("{}NIL\n", indent);
                    break;

                case msgpack::type::BOOLEAN:
                    ss << std::format(
                        "{}BOOLEAN: {}\n",
                        indent,
                        obj.via.boolean ? "true" : "false");
                    break;

                case msgpack::type::POSITIVE_INTEGER:
                    ss << std::format(
                        "{}POSITIVE_INTEGER: {}\n", indent, obj.via.u64);
                    break;

                case msgpack::type::NEGATIVE_INTEGER:
                    ss << std::format(
                        "{}NEGATIVE_INTEGER: {}\n", indent, obj.via.i64);
                    break;

                case msgpack::type::FLOAT32:
                    ss << std::format(
                        "{}FLOAT32: {}\n", indent, obj.via.f64);
                    break;

                case msgpack::type::FLOAT64:
                    ss << std::format(
                        "{}FLOAT64: {}\n", indent, obj.via.f64);
                    break;

                case msgpack::type::STR:
                    ss << std::format(
                        "{}STR[{}]: \"{}\"\n",
                        indent,
                        obj.via.str.size,
                        std::string(obj.via.str.ptr, obj.via.str.size));
                    break;

                case msgpack::type::BIN:
                    ss << std::format(
                        "{}BIN[{}]: <binary data>\n",
                        indent,
                        obj.via.bin.size);
                    break;

                case msgpack::type::ARRAY:
                    ss << std::format(
                        "{}ARRAY[{}]:\n", indent, obj.via.array.size);
                    for (uint32_t i = 0; i < obj.via.array.size; ++i) {
                        ss << std::format("{}  [{}]:\n", indent, i);
                        traverse(obj.via.array.ptr[i], d + 2);
                    }
                    break;

                case msgpack::type::MAP:
                    ss << std::format(
                        "{}MAP[{}]:\n", indent, obj.via.map.size);
                    for (uint32_t i = 0; i < obj.via.map.size; ++i) {
                        ss << std::format("{}  Key[{}]:\n", indent, i);
                        traverse(obj.via.map.ptr[i].key, d + 2);
                        ss << std::format("{}  Value[{}]:\n", indent, i);
                        traverse(obj.via.map.ptr[i].val, d + 2);
                    }
                    break;

                case msgpack::type::EXT:
                    ss << std::format(
                        "{}EXT[type={}, size={}]: <extension data>\n",
                        indent,
                        obj.via.ext.type(),
                        obj.via.ext.size);
                    break;

                default:
                    ss << std::format(
                        "{}UNKNOWN[type={}]\n",
                        indent,
                        static_cast<int>(obj.type));
                    break;
            }
        };

    traverse(o, depth);
    return ss.str();
}

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
void convert_field(msgpack::object_kv*& p, T& value) {
    p->val.convert(value);
    ++p;
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
                "expected map, got {} in {}",
                format_msgpack_object_type(o.type),
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
    int                    size     = -1,
    int                    line     = __builtin_LINE(),
    char const*            function = __builtin_FUNCTION(),
    char const*            file     = __builtin_FILE()) {
    if (o.type != msgpack::type::ARRAY) {
        throw htype_error::init(
            hstd::fmt(
                "expected array, got {} in {}",
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


template <typename T>
void expect_string(
    msgpack::object const& o,
    int                    line     = __builtin_LINE(),
    char const*            function = __builtin_FUNCTION(),
    char const*            file     = __builtin_FILE()) {
    if (o.type != msgpack::type::STR) {
        throw htype_error::init(
            hstd::fmt(
                "expected string, got {} in {} object is {}",
                o.type,
                hstd::value_metadata<T>::typeName(),
                msgpack_object_to_tree(o)),
            line,
            function);
    }
}


template <typename... Args>
struct convert<std::variant<Args...>> {
    using VT = std::variant<Args...>;
    msgpack::object const& operator()(
        msgpack::object const& o,
        std::variant<Args...>& v) const {
        __trace_call();
        expect_array<VT>(o, 2);

        v = hstd::variant_from_index<VT>(o.via.array.ptr[0].as<int>());
        std::visit([&](auto& out) { o.via.array.ptr[1].convert(out); }, v);

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
        __trace_call();
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
        __trace_call();
        expect_map<cctz::time_zone>(o, 1);
        msgpack::object_kv* p(o.via.map.ptr);
        std::string         name;
        convert_field(p, name);
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
        __trace_call();
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
        __trace_call();
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
        __trace_call();
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
        __trace_call();
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
        __trace_call();
        o.pack<std::string>(v);
        return o;
    }
};


template <>
struct convert<org::imm::ImmId> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        org::imm::ImmId&       v) const {
        __trace_call();
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
        __trace_call();
        o.pack(v.getValue());
        return o;
    }
};


template <typename T>
struct convert<org::imm::ImmIdT<T>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        org::imm::ImmIdT<T>&   v) const {
        __trace_call();
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
        __trace_call();
        o.pack(v.getValue());
        return o;
    }
};


template <typename T>
struct convert<immer::box<T>> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        immer::box<T>&         v) const {
        __trace_call();
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
        __trace_call();
        o.pack(v.get());
        return o;
    }
};

template <typename T, typename Container>
struct convert_sequential_container {
    msgpack::object const& operator()(
        msgpack::object const& o,
        Container&             v) const {
        __trace_call();
        expect_array<Container>(o);
        hstd::SequentialContainerAdapter<Container> a{&v};
        a.begin_insert();

        for (auto p : convert_array_items(o)) {
            T tmp_value = hstd::SerdeDefaultProvider<T>::get();
            p->convert(tmp_value);
            a.add(tmp_value);
        }

        a.end_insert();

        return o;
    }
};


template <typename T, typename Container>
struct pack_iterable_sequence {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        Container const&         v) const {
        __trace_call();
        hstd::SequentialContainerAdapter<Container> a{&v};
        uint32_t size = checked_get_container_size(a.size());
        o.pack_array(size);
        for (auto it = a.begin(); it != a.end(); ++it) { o.pack(*it); }
        return o;
    }
};

template <typename T>
struct convert<immer::flex_vector<T>>
    : convert_sequential_container<T, immer::flex_vector<T>> {};

template <typename T>
struct pack<immer::flex_vector<T>>
    : pack_iterable_sequence<T, immer::flex_vector<T>> {};

template <typename T>
struct convert<immer::vector<T>>
    : convert_sequential_container<T, immer::vector<T>> {};

template <typename T>
struct pack<immer::vector<T>>
    : pack_iterable_sequence<T, immer::vector<T>> {};

template <typename T>
struct convert<hstd::Vec<T>>
    : public convert_sequential_container<T, hstd::Vec<T>> {};

template <typename T>
struct pack<hstd::Vec<T>> : pack_iterable_sequence<T, hstd::Vec<T>> {};

template <typename T, int Size>
struct convert<hstd::SmallVec<T, Size>>
    : convert_sequential_container<T, hstd::SmallVec<T, Size>> {};

template <typename T, int Size>
struct pack<hstd::SmallVec<T, Size>>
    : pack_iterable_sequence<T, hstd::SmallVec<T, Size>> {};


template <typename K, typename V, typename Container>
struct convert_associative_container {
    msgpack::object const& operator()(
        msgpack::object const& o,
        Container&             v) const {
        __trace_call();
        expect_array<Container>(o);
        hstd::AssociativeContainerAdapter<Container> a{&v};

        a.begin_insert();
        a.clear();
        a.reserve(o.via.array.size);

        for (uint32_t i = 0; i < o.via.array.size; ++i) {
            msgpack::object const& pair_obj = o.via.array.ptr[i];
            expect_array<Container>(pair_obj, 2);

            K key   = hstd::SerdeDefaultProvider<K>::get();
            V value = hstd::SerdeDefaultProvider<V>::get();
            pair_obj.via.array.ptr[0].convert(key);
            pair_obj.via.array.ptr[1].convert(value);
            a.insert_or_assign(std::move(key), std::move(value));
        }
        a.end_insert();
        return o;
    }
};

template <typename K, typename V, typename Container>
struct pack_associative_container {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        Container const&         v) const {
        __trace_call();
        o.pack_array(v.size());
        hstd::AssociativeContainerAdapter<Container> a{&v};
        if constexpr (requires(const K& a, const K& b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            for (auto const& key : hstd::sorted(a.keys())) {
                o.pack_array(2);
                o.pack(key);
                o.pack(a.at(key));
            }
        } else {
            for (auto it = a.begin(); it != a.end(); ++it) {
                o.pack_array(2);
                o.pack(a.get_pair_key(*it));
                o.pack(a.get_pair_value(*it));
            }
        }


        return o;
    }
};

template <typename K, typename V>
struct convert<immer::map<K, V>>
    : convert_associative_container<K, V, immer::map<K, V>> {};

template <typename K, typename V>
struct pack<immer::map<K, V>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        immer::map<K, V> const&  v) const {
        __trace_call();

        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);

        if constexpr (requires(const K& a, const K& b) {
                          { a < b } -> std::convertible_to<bool>;
                      }) {
            hstd::Vec<K> keys;
            for (auto const& [key, value] : v) { keys.push_back(key); }
            for (auto const& key : hstd::sorted(keys)) {
                o.pack_array(2);
                o.pack(key);
                o.pack(v.at(key));
            }
        } else {
            for (auto const& [key, value] : v) {
                o.pack_array(2);
                o.pack(key);
                o.pack(value);
            }
        }

        return o;
    }
};


template <typename K, typename V>
struct convert<hstd::ext::ImmMap<K, V>>
    : convert_associative_container<K, V, hstd::ext::ImmMap<K, V>> {};

template <typename K, typename V>
struct pack<hstd::ext::ImmMap<K, V>>
    : pack_associative_container<K, V, hstd::ext::ImmMap<K, V>> {};

template <typename K, typename V>
struct convert<hstd::UnorderedMap<K, V>>
    : convert_associative_container<K, V, hstd::UnorderedMap<K, V>> {};

template <typename K, typename V>
struct pack<hstd::UnorderedMap<K, V>>
    : pack_associative_container<K, V, hstd::UnorderedMap<K, V>> {};


template <>
struct pack<json> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, json const& v)
        const {
        switch (v.type()) {
            case json::value_t::null: o.pack_nil(); break;
            case json::value_t::boolean: o.pack(v.get<bool>()); break;
            case json::value_t::number_integer:
                o.pack(v.get<int64_t>());
                break;
            case json::value_t::number_unsigned:
                o.pack(v.get<uint64_t>());
                break;
            case json::value_t::number_float:
                o.pack(v.get<double>());
                break;
            case json::value_t::string:
                o.pack(v.get<std::string>());
                break;
            case json::value_t::array:
                o.pack_array(v.size());
                for (auto const& item : v) { o.pack(item); }
                break;
            case json::value_t::object:
                o.pack_map(v.size());
                for (auto const& [key, value] : v.items()) {
                    o.pack(key);
                    o.pack(value);
                }
                break;

            case json::value_t::binary: {
                auto const& bin = v.get_binary();
                o.pack_bin(bin.size());
                o.pack_bin_body(
                    reinterpret_cast<const char*>(bin.data()), bin.size());
                break;
            }
            case json::value_t::discarded: o.pack_nil(); break;
        }

        return o;
    }
};

template <>
struct convert<json> {
    msgpack::object const& operator()(msgpack::object const& o, json& v)
        const {
        v = msgpack_to_json(o);
        return o;
    }
};

template <hstd::dod::IsIdType Id, typename T>
struct convert<hstd::dod::Store<Id, T>> {
    msgpack::object const& operator()(
        msgpack::object const&   o,
        hstd::dod::Store<Id, T>& v) const {
        __trace_call();
        msgpack::object_kv* p(o.via.map.ptr);
        convert_field(p, v.content);
        return o;
    }
};

template <hstd::dod::IsIdType Id, typename T>
struct pack<hstd::dod::Store<Id, T>> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>&       o,
        hstd::dod::Store<Id, T> const& v) const {
        __trace_call();
        o.pack_map(1);
        pack_field(o, "content", v.content);
        return o;
    }
};

template <>
struct pack<org::sem::OrgJson> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        org::sem::OrgJson const& v) const {
        o.pack_map(1);
        pack_field(o, "value", v.getValue());
        return o;
    }
};

template <>
struct convert<org::sem::OrgJson> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        org::sem::OrgJson&     v) const {
        __trace_call();
        expect_map<org::sem::OrgJson>(o, 1);
        msgpack::object_kv* p(o.via.map.ptr);
        json                value;
        convert_field(p, value);
        v = org::sem::OrgJson(value);
        return o;
    }
};


template <hstd::DescribedRecord T>
struct convert<T> {
    msgpack::object const& operator()(msgpack::object const& o, T& v)
        const {
        __trace_call();
        int size = 0;
        hstd::for_each_field_value_with_bases(
            v, [&](char const*, auto const& field) { ++size; });

        expect_map<T>(o, size);


        msgpack::object_kv*       p(o.via.map.ptr);
        msgpack::object_kv* const pend(o.via.map.ptr + o.via.map.size);
        hstd::for_each_field_value_with_bases(
            v, [&](char const*, auto& field) { convert_field(p, field); });

        return o;
    }
};


template <hstd::DescribedRecord T>
struct pack<T> {
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, T const& v)
        const {
        __trace_call();
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
struct pack<ImmReflFieldId> {
    template <typename Stream>
    packer<Stream>& operator()(
        msgpack::packer<Stream>& o,
        ImmReflFieldId const&    v) const {
        o.pack(v.getSerializableId());
        return o;
    }
};

template <>
struct convert<ImmReflFieldId> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        ImmReflFieldId&        v) const {
        std::uint64_t val;
        o.convert(val);
        v = ImmReflFieldId::fromSerializableId(val);
        return o;
    }
};

template <typename Tag, typename Stream>
void serialize_any_key(
    msgpack::packer<Stream>& o,
    std::any const&          anyKey) {
    using AnyTypeTuple = typename hstd::ReflTypeTraits<Tag>::AnyTypeTuple;

    bool        packed = false;
    std::size_t index  = 0;
    std::apply(
        [&]<typename... Args>(Args&&... types) {
            ((anyKey.type() == typeid(types)
                  ? (o.pack_array(2),
                     o.pack(index),
                     o.pack(std::any_cast<Args>(anyKey)),
                     packed = true)
                  : (++index, bool())),
             ...);
        },
        AnyTypeTuple{});

    if (!packed) { throw std::runtime_error("Unknown type in std::any"); }
}


template <typename Tag>
std::any deserialize_any_key(msgpack::object const& o) {
    using AnyTypeTuple = typename hstd::ReflTypeTraits<Tag>::AnyTypeTuple;
    expect_array<std::any>(o, 2);

    std::size_t type_index;
    o.via.array.ptr[0].convert(type_index);

    std::any    result;
    std::size_t current_index = 0;
    std::apply(
        [&]<typename... Args>(Args&&... types) {
            (void)((current_index++ == type_index
                        ? (result = std::any{o.via.array.ptr[1]
                                                 .as<Args>()},
                           true)
                        : false)
                   || ...);
        },
        AnyTypeTuple{});

    if (!result.has_value()) {
        throw std::runtime_error("Failed to deserialize std::any");
    }

    return result;
}

template <typename Tag>
struct pack<hstd::ReflPathItem<Tag>> {
    using RPI = hstd::ReflPathItem<Tag>;
    template <typename Stream>
    packer<Stream>& operator()(msgpack::packer<Stream>& o, RPI const& v)
        const {
        o.pack_array(2);
        o.pack(v.kind);
        switch (v.kind) {
            case RPI::Kind::Index: o.pack(v.data.index); break;
            case RPI::Kind::FieldName: o.pack(v.data.fieldName); break;
            case RPI::Kind::AnyKey:
                serialize_any_key<Tag>(o, v.data.anyKey.key);
                break;
            case RPI::Kind::Deref: o.pack(v.data.deref); break;
        }
        return o;
    }
};

template <typename Tag>
struct convert<hstd::ReflPathItem<Tag>> {
    using RPI  = hstd::ReflPathItem<Tag>;
    using Kind = RPI::Kind;
    msgpack::object const& operator()(msgpack::object const& o, RPI& v)
        const {
        expect_array<hstd::ReflPathItem<Tag>>(o, 2);
        o.via.array.ptr[0].convert(v.kind);

        switch (v.kind) {
            case Kind::Index: {
                typename RPI::Index index;
                o.via.array.ptr[1].convert(index);
                v = RPI{index};
                break;
            }
            case Kind::FieldName: {
                typename RPI::FieldName fieldName;
                o.via.array.ptr[1].convert(fieldName);
                v = RPI{fieldName};
                break;
            }
            case Kind::AnyKey: {
                typename RPI::AnyKey anyKey;
                anyKey.key = deserialize_any_key<Tag>(o.via.array.ptr[1]);
                v          = RPI{anyKey};
                break;
            }
            case Kind::Deref: {
                typename RPI::Deref deref;
                o.via.array.ptr[1].convert(deref);
                v = RPI{deref};
                break;
            }
        }

        return o;
    }
};

template <>
struct convert<ImmAstStore> {
    msgpack::object const& operator()(
        msgpack::object const& o,
        ImmAstStore&           v) const {
        __trace_call();
#define _kind(__Kind) +1
        constexpr int store_size = 0 EACH_SEM_ORG_KIND(_kind);
#undef _kind

        expect_map<ImmAstStore>(o, store_size);
        msgpack::object_kv* p(o.via.map.ptr);
#define _kind(__Kind) convert_field(p, v.store##__Kind);
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
        __trace_call();
#define _kind(__Kind) +1
        constexpr int store_size = 0 EACH_SEM_ORG_KIND(_kind);
#undef _kind

        o.pack_map(store_size);

#define _kind(__Kind) pack_field(o, "store" #__Kind, v.store##__Kind);
        EACH_SEM_ORG_KIND(_kind);
#undef _kind
        return o;
    }
};

template <typename T>
struct in_place_convert_shared_ptr {
    msgpack::object const& operator()(
        msgpack::object const& o,
        std::shared_ptr<T>&    v) const {
        if (o.is_nil()) {
            v.reset();
        } else {
            if (v.get() == nullptr) { v = std::make_shared<T>(); }
            msgpack::adaptor::convert<T>()(o, *v);
        }
        return o;
    }
};


template <>
struct convert<std::shared_ptr<org::graph::MapGraph>>
    : in_place_convert_shared_ptr<org::graph::MapGraph> {};

template <>
struct convert<std::shared_ptr<org::imm::ImmAstReplaceEpoch>>
    : in_place_convert_shared_ptr<org::imm::ImmAstReplaceEpoch> {};

template <>
struct convert<std::shared_ptr<ImmAstContext>> {
    msgpack::object const& operator()(
        msgpack::object const&          o,
        std::shared_ptr<ImmAstContext>& v) const {
        __trace_call();
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
        __trace_call();
        o.pack_map(2);
        pack_field(o, "store", *v->store);
        pack_field(o, "currentTrack", *v->currentTrack);
        return o;
    }
};


} // namespace adaptor
} // namespace MSGPACK_DEFAULT_API_NS
} // namespace msgpack

template <typename T>
std::string msgpack_to_text(T const& value) {
    std::stringstream oss{};
    msgpack::pack(oss, value);
    oss.seekg(0);
    std::string tmp{oss.str()};
    return tmp;
}

template <typename T>
void msgpack_from_text(std::string const& binary, T& value) {
    msgpack::object_handle o = msgpack::unpack(
        binary.data(), binary.size());
    msgpack::object deserialized = o.get();
    deserialized.convert(value);
}

std::string org::imm::serializeToText(
    const std::shared_ptr<ImmAstContext>& store) {
    auto tmp = msgpack_to_text(store);
    return tmp;
}

void org::imm::serializeFromText(
    std::string const&                    binary,
    const std::shared_ptr<ImmAstContext>& store) {
    auto tmp = store;
    msgpack_from_text(binary, tmp);
}

std::string org::imm::serializeToText(
    const std::shared_ptr<ImmAstReplaceEpoch>& store) {
    auto tmp = msgpack_to_text(store);
    return tmp;
}

void org::imm::serializeFromText(
    std::string const&                         binary,
    const std::shared_ptr<ImmAstReplaceEpoch>& store) {
    auto tmp = store;
    msgpack_from_text(binary, tmp);
}

json org::imm::serializeFromTextToJson(const std::string& binary) {
    msgpack::object_handle o = msgpack::unpack(
        binary.data(), binary.size());
    msgpack::object deserialized = o.get();
    return msgpack_to_json(deserialized);
}

std::string org::imm::serializeFromTextToTreeDump(
    const std::string& binary) {
    msgpack::object_handle o = msgpack::unpack(
        binary.data(), binary.size());
    msgpack::object deserialized = o.get();
    return msgpack_object_to_tree(deserialized);
}

std::string org::imm::serializeToText(
    const std::shared_ptr<org::graph::MapGraph>& store) {
    auto tmp = msgpack_to_text(store);
    return tmp;
}

void org::imm::serializeFromText(
    const std::string&                      binary,
    const std::shared_ptr<graph::MapGraph>& store) {
    auto tmp = store;
    LOGIC_ASSERTION_CHECK(tmp.get() == store.get(), "");
    msgpack_from_text(binary, tmp);
    LOGIC_ASSERTION_CHECK(tmp.get() == store.get(), "");
}
