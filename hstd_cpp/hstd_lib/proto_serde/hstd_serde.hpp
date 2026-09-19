#pragma once

#if ORG_BUILD_WITH_PROTOBUF
#    include "google/protobuf/map.h"
#    include "hstd/stdlib/Filesystem.hpp"
#    include <fstream>
#    include <google/protobuf/any.pb.h>
#    include <google/protobuf/text_format.h>
#    include <google/protobuf/util/json_util.h>
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

struct write_error : public hstd::CRTP_hexception<write_error> {};
struct read_error : public hstd::CRTP_hexception<read_error> {};

template <typename Message>
google::protobuf::Any packMessage(Message const& message) {
    google::protobuf::Any result{};
    if (result.PackFrom(message)) {
        return result;
    } else {
        throw hstd::serde::write_error::init("Failed to pack protobuf message");
    }
}

template <typename Message>
Message unpackMessage(
    google::protobuf::Any const& payload,
    std::string const&           owner = "value") {
    Message result{};

    if (!payload.UnpackTo(&result)) {
        throw hstd::serde::read_error::init(
            hstd::fmt(
                "Payload on '{}' declares type '{}' but cannot be unpacked as '{}'",
                owner,
                payload.type_url(),
                Message::descriptor()->full_name()));
    }

    return result;
}


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

template <typename Proto, typename T>
void read_serde(Proto const& in, T& out) {
    hstd::serde::proto_serde<Proto, T>::read(in, &out);
}

template <typename T, typename Proto>
T read_serde(Proto const& value) {
    T result;
    hstd::serde::proto_serde<Proto, T>::read(value, &result);
    return result;
}

template <typename Proto, typename T>
Proto write_serde(T const& value) {
    Proto result;
    hstd::serde::proto_serde<Proto, T>::write(&result, value);
    return result;
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

    static void read(Proto const& out, T* in) { *in = static_cast<T>(out); }
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

template <>
struct proto_serde<double, double> {
    static void write(double* out, double const& in) { *out = in; }
    static void read(double const& out, proto_write_accessor<double> in) {
        in.get() = out;
    }
};

#    define CASE_PROTO_ENUM_SENTINEL(__enum_type)                                        \
        case __enum_type##_INT_MIN_SENTINEL_DO_NOT_USE_:                                 \
            throw logic_unreachable_error::init(                                         \
                "Unreachable protobuf enum sentinel " #__enum_type);                     \
        case __enum_type##_INT_MAX_SENTINEL_DO_NOT_USE_:                                 \
            throw logic_unreachable_error::init(                                         \
                "Unreachable protobuf enum sentinel " #__enum_type);


template <typename Enum>
std::string enum_name(Enum value) {
    auto const* descriptor      = google::protobuf::GetEnumDescriptor<Enum>();
    auto const* valueDescriptor = descriptor->FindValueByNumber(static_cast<int>(value));

    if (valueDescriptor == nullptr) {
        throw std::invalid_argument("Unknown protobuf enum value");
    }

    return std::string(valueDescriptor->name());
}


std::string getJString(google::protobuf::Message const& message);


DECL_DESCRIBED_ENUM_STANDALONE(ProtobufFileFormat, Binary, Json, Textproto);

template <typename T>
T read_message_from_binary_file(std::string const& file_path) {
    T             result;
    std::ifstream stream{file_path, std::ios::binary};
    if (!stream) {
        throw hstd::runtime_error::init("Failed to open input file: " + file_path);
    }
    if (!result.ParseFromIstream(&stream)) {
        throw hstd::runtime_error::init("Failed to parse protobuf input: " + file_path);
    }

    return result;
}

template <typename T>
T read_message_from_json_file(std::string const& file_path) {
    T    result;
    auto status = google::protobuf::util::JsonStringToMessage(
        hstd::strip_json_comments(hstd::readFile(file_path)), &result);

    if (!status.ok()) {
        throw hstd::runtime_error::init(
            "Failed to parse protobuf JSON input: " + file_path + ": "
            + status.ToString());
    }

    return result;
}

template <typename T>
T read_message_from_textproto_file(std::string const& file_path) {
    T result;

    if (!google::protobuf::TextFormat::ParseFromString(
            hstd::readFile(file_path), &result)) {
        throw hstd::runtime_error::init(
            "Failed to parse protobuf textproto input: " + file_path);
    }

    return result;
}

template <typename T>
T read_message_from_file(std::string const& file_path, ProtobufFileFormat format) {
    switch (format) {
        case ProtobufFileFormat::Binary:
            return read_message_from_binary_file<T>(file_path);
        case ProtobufFileFormat::Json: return read_message_from_json_file<T>(file_path);
        case ProtobufFileFormat::Textproto:
            return read_message_from_textproto_file<T>(file_path);
    }
}

void protovalidate_message(google::protobuf::Message const& message);


} // namespace hstd::serde
#endif
