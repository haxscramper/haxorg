#pragma once

#if ORG_BUILD_WITH_PROTOBUF
#    include "google/protobuf/map.h"
#    include <google/protobuf/any.pb.h>
#    include <hstd/stdlib/Json.hpp>
#    include <hstd/stdlib/Map.hpp>
#    include <hstd/stdlib/Opt.hpp>
#    include <hstd/stdlib/Str.hpp>
#    include <hstd/stdlib/Variant.hpp>
#    include <hstd/stdlib/Vec.hpp>

namespace google::protobuf {
class Struct;
class Value;
class Message;
} // namespace google::protobuf


namespace hstd::serde {

template <typename Proto, typename T>
struct proto_serde {};

void json_to_value(json const& in, ::google::protobuf::Value* out);
void json_to_struct(json const& in, ::google::protobuf::Struct* out);

json value_to_json(::google::protobuf::Value const& in);
json struct_to_json(::google::protobuf::Struct const& in);

template <typename Proto, typename T>
void write_serde(Proto* out, T const& in) {
    hstd::serde::proto_serde<Proto, T>::write(out, in);
}

template <typename Proto, typename T>
void read_serde(Proto const& in, T* out) {
    hstd::serde::proto_serde<Proto, T>::read(in, out);
}


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
struct proto_write_accessor : proto_write_accessor_base<T, proto_write_accessor<T>> {};

template <typename T>
struct proto_write_accessor<hstd::Opt<T>>
    : proto_write_accessor_base<hstd::Opt<T>, proto_write_accessor<hstd::Opt<T>>> {

    proto_write_accessor<T> for_value() {
        return proto_write_accessor<T>{
            [impl = this->impl]() -> T& { return impl().value(); }};
    }
};


template <typename FieldType, typename Var, int Field>
struct proto_variant_init {
    static void init(Var& variant) { variant = hstd::variant_from_index<Var>(Field); }
};


template <hstd::IsRecord T>
struct proto_write_accessor<T> : proto_write_accessor_base<T, proto_write_accessor<T>> {

    template <typename T1>
    proto_write_accessor<T1> as() {
        return proto_write_accessor<T1>{[impl = this->impl]() -> T1& { return impl(); }};
    }

    template <typename F>
    proto_write_accessor<F> for_field(F T::* field) {
        return proto_write_accessor<F>{
            [impl = this->impl, field]() -> F& { return impl().*field; }};
    }


    template <int N, typename F, typename VarType = std::variant_alternative_t<N, F>>
    proto_write_accessor<VarType> for_field_variant(F T::* field) {
        return proto_write_accessor<VarType>{[impl = this->impl, field]() -> VarType& {
            if ((impl().*field).index() != N) {
                hstd::serde::proto_variant_init<VarType, F, N>::init(impl().*field);
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


template <class T>
concept IsDefaultConstructible = std::is_default_constructible_v<T>;

template <class T>
concept NonDefaultConstructible = !IsDefaultConstructible<T>;

template <typename ProtoKey, typename ProtoVal, typename K, typename V>
struct proto_serde<google::protobuf::Map<ProtoKey, ProtoVal>, hstd::UnorderedMap<K, V>> {
    static void write(
        google::protobuf::Map<ProtoKey, ProtoVal>* out,
        hstd::UnorderedMap<K, V> const&            in) {
        for (auto const& [k, v] : in) {
            proto_serde<ProtoVal, V>::write(&out->operator[](k), v);
        }
    }

    template <IsDefaultConstructible U = V>
    static void read(
        google::protobuf::Map<ProtoKey, ProtoVal> const& out,
        proto_write_accessor<hstd::UnorderedMap<K, V>>   in) {
        for (auto const& [key, val] : out) {
            in.get().insert_or_assign(key, hstd::SerdeDefaultProvider<V>::get());
            proto_serde<ProtoVal, V>::read(
                val, proto_write_accessor<V>{[&in, &key]() -> V& {
                    return in.get().at(key);
                }});
        }
    }
};

template <typename Proto, hstd::DescribedEnum T>
struct proto_serde<Proto, T> {
    static void write(Proto* out, T const& in) { *out = static_cast<Proto>(in.value); }

    static void read(Proto const& out, proto_write_accessor<T> in) {
        in.get() = static_cast<T>(out);
    }
};

template <typename Proto, typename T>
struct proto_serde<hstd::Opt<Proto>, hstd::Opt<T>> {
    static void write(Proto* out, hstd::Opt<T> const& in) {
        proto_serde<Proto, T>::write(out, in.value());
    }

    static void read(Proto const& out, proto_write_accessor<hstd::Opt<T>> in) {
        proto_init<hstd::Opt<T>>::init_default(in.get());
        proto_serde<Proto, T>::read(out, in.for_value());
    }
};

template <typename Proto, typename T>
struct proto_serde<google::protobuf::RepeatedPtrField<Proto>, hstd::Vec<T>> {
    static void write(
        google::protobuf::RepeatedPtrField<Proto>* out,
        hstd::Vec<T> const&                        in) {
        for (auto const& it : in) { proto_serde<Proto, T>::write(out->Add(), it); }
    }

    static void read(
        google::protobuf::RepeatedPtrField<Proto> const& out,
        proto_write_accessor<hstd::Vec<T>>               in) {
        for (auto const& it : out) {
            auto& ref = in.get().emplace_back();
            proto_serde<Proto, T>::read(it, proto_write_accessor<T>::for_ref(ref));
        }
    }
};


template <>
struct proto_serde<std::string, hstd::Str> {
    static void write(std::string* out, hstd::Str const& in) { *out = in; }
    static void read(std::string const& out, proto_write_accessor<hstd::Str> in) {
        in.get() = out;
    }
};

template <>
struct proto_serde<std::string, std::string> {
    static void read(std::string const& out, proto_write_accessor<std::string> in) {
        in.get() = out;
    }
};

template <>
struct proto_serde<bool, bool> {
    static void read(bool const& out, proto_write_accessor<bool> in) { in.get() = out; }
};

template <>
struct proto_serde<int, int> {
    static void read(int const& out, proto_write_accessor<int> in) { in.get() = out; }
};

template <>
struct proto_serde<float, float> {
    static void write(float* out, float const& in) { *out = in; }
    static void read(float const& out, proto_write_accessor<float> in) { in.get() = out; }
};


std::string getJString(google::protobuf::Message const& message);

template <typename T>
T unpack_attr_payload(google::protobuf::Any const& in) {
    T payload;
    if (!in.UnpackTo(&payload)) {
        throw hstd::logic_error::init(
            hstd::fmt(
                "Failed to unpack attribute payload: does not match the target type {}",
                T::descriptor()->full_name()));
    }
    return payload;
}


} // namespace hstd::serde
#endif
