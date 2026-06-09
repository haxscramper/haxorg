#pragma once

#include <hstd/stdlib/Json.hpp>

namespace google::protobuf {
class Struct;
class Value;
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

} // namespace hstd::serde
