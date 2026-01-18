/* clang-format off */
#if ORG_DEPS_USE_PROTOBUF && !ORG_EMCC_BUILD
#include <haxorg/serde/SemOrgSerde.hpp>
#include <haxorg/serde/SemOrgSerdeDeclarations.hpp>
void org::algo::proto_serde<::orgproto::LispCode::Call, org::sem::LispCode::Call>::write(::orgproto::LispCode::Call* out, org::sem::LispCode::Call const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::write(out->mutable_args(), in.args);
}

void org::algo::proto_serde<::orgproto::LispCode::Call, org::sem::LispCode::Call>::read(::orgproto::LispCode::Call const& out, proto_write_accessor<org::sem::LispCode::Call> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::LispCode::Call::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::read(out.args(), in.for_field(&org::sem::LispCode::Call::args));
}

void org::algo::proto_serde<::orgproto::LispCode::List, org::sem::LispCode::List>::write(::orgproto::LispCode::List* out, org::sem::LispCode::List const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::write(out->mutable_items(), in.items);
}

void org::algo::proto_serde<::orgproto::LispCode::List, org::sem::LispCode::List>::read(::orgproto::LispCode::List const& out, proto_write_accessor<org::sem::LispCode::List> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::read(out.items(), in.for_field(&org::sem::LispCode::List::items));
}

void org::algo::proto_serde<::orgproto::LispCode::KeyValue, org::sem::LispCode::KeyValue>::write(::orgproto::LispCode::KeyValue* out, org::sem::LispCode::KeyValue const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::LispCode::KeyValue, org::sem::LispCode::KeyValue>::read(::orgproto::LispCode::KeyValue const& out, proto_write_accessor<org::sem::LispCode::KeyValue> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::LispCode::KeyValue::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::LispCode>, hstd::Vec<org::sem::LispCode>>::read(out.value(), in.for_field(&org::sem::LispCode::KeyValue::value));
}

void org::algo::proto_serde<::orgproto::LispCode::Number, org::sem::LispCode::Number>::write(::orgproto::LispCode::Number* out, org::sem::LispCode::Number const& in) {
  out->set_value(in.value);
}

void org::algo::proto_serde<::orgproto::LispCode::Number, org::sem::LispCode::Number>::read(::orgproto::LispCode::Number const& out, proto_write_accessor<org::sem::LispCode::Number> in) {
  in.for_field(&org::sem::LispCode::Number::value).get() = out.value();
}

void org::algo::proto_serde<::orgproto::LispCode::Text, org::sem::LispCode::Text>::write(::orgproto::LispCode::Text* out, org::sem::LispCode::Text const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::LispCode::Text, org::sem::LispCode::Text>::read(::orgproto::LispCode::Text const& out, proto_write_accessor<org::sem::LispCode::Text> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::LispCode::Text::value));
}

void org::algo::proto_serde<::orgproto::LispCode::Ident, org::sem::LispCode::Ident>::write(::orgproto::LispCode::Ident* out, org::sem::LispCode::Ident const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::LispCode::Ident, org::sem::LispCode::Ident>::read(::orgproto::LispCode::Ident const& out, proto_write_accessor<org::sem::LispCode::Ident> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::LispCode::Ident::name));
}

void org::algo::proto_serde<::orgproto::LispCode::Boolean, org::sem::LispCode::Boolean>::write(::orgproto::LispCode::Boolean* out, org::sem::LispCode::Boolean const& in) {
  out->set_value(in.value);
}

void org::algo::proto_serde<::orgproto::LispCode::Boolean, org::sem::LispCode::Boolean>::read(::orgproto::LispCode::Boolean const& out, proto_write_accessor<org::sem::LispCode::Boolean> in) {
  in.for_field(&org::sem::LispCode::Boolean::value).get() = out.value();
}

void org::algo::proto_serde<::orgproto::LispCode::Real, org::sem::LispCode::Real>::write(::orgproto::LispCode::Real* out, org::sem::LispCode::Real const& in) {
  out->set_value(in.value);
}

void org::algo::proto_serde<::orgproto::LispCode::Real, org::sem::LispCode::Real>::read(::orgproto::LispCode::Real const& out, proto_write_accessor<org::sem::LispCode::Real> in) {
  in.for_field(&org::sem::LispCode::Real::value).get() = out.value();
}

void org::algo::proto_serde<::orgproto::LispCode, org::sem::LispCode>::write(::orgproto::LispCode* out, org::sem::LispCode const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::LispCode::Call, org::sem::LispCode::Call>::write(out->mutable_data()->mutable_call(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::LispCode::List, org::sem::LispCode::List>::write(out->mutable_data()->mutable_list(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::LispCode::KeyValue, org::sem::LispCode::KeyValue>::write(out->mutable_data()->mutable_keyvalue(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::LispCode::Number, org::sem::LispCode::Number>::write(out->mutable_data()->mutable_number(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::LispCode::Text, org::sem::LispCode::Text>::write(out->mutable_data()->mutable_text(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::LispCode::Ident, org::sem::LispCode::Ident>::write(out->mutable_data()->mutable_ident(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::LispCode::Boolean, org::sem::LispCode::Boolean>::write(out->mutable_data()->mutable_boolean(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::LispCode::Real, org::sem::LispCode::Real>::write(out->mutable_data()->mutable_real(), std::get<7>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::LispCode, org::sem::LispCode>::read(::orgproto::LispCode const& out, proto_write_accessor<org::sem::LispCode> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::LispCode::Data::kCall:
      in.for_field_variant<0>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Call, org::sem::LispCode::Call>::read(out.data().call(), in.for_field_variant<0>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kList:
      in.for_field_variant<1>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::List, org::sem::LispCode::List>::read(out.data().list(), in.for_field_variant<1>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kKeyvalue:
      in.for_field_variant<2>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::KeyValue, org::sem::LispCode::KeyValue>::read(out.data().keyvalue(), in.for_field_variant<2>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kNumber:
      in.for_field_variant<3>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Number, org::sem::LispCode::Number>::read(out.data().number(), in.for_field_variant<3>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kText:
      in.for_field_variant<4>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Text, org::sem::LispCode::Text>::read(out.data().text(), in.for_field_variant<4>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kIdent:
      in.for_field_variant<5>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Ident, org::sem::LispCode::Ident>::read(out.data().ident(), in.for_field_variant<5>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kBoolean:
      in.for_field_variant<6>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Boolean, org::sem::LispCode::Boolean>::read(out.data().boolean(), in.for_field_variant<6>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::kReal:
      in.for_field_variant<7>(&org::sem::LispCode::data).get();
      proto_serde<orgproto::LispCode::Real, org::sem::LispCode::Real>::read(out.data().real(), in.for_field_variant<7>(&org::sem::LispCode::data));
      break;
    case ::orgproto::LispCode::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::write(::orgproto::Tblfm::Expr::AxisRef::Position::Index* out, org::sem::Tblfm::Expr::AxisRef::Position::Index const& in) {
  out->set_index(in.index);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::read(::orgproto::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Index> in) {
  in.for_field(&org::sem::Tblfm::Expr::AxisRef::Position::Index::index).get() = out.index();
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::write(::orgproto::Tblfm::Expr::AxisRef::Position::Name* out, org::sem::Tblfm::Expr::AxisRef::Position::Name const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::read(::orgproto::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Name> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::Position::Name::name));
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(::orgproto::Tblfm::Expr::AxisRef::Position* out, org::sem::Tblfm::Expr::AxisRef::Position const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::write(out->mutable_data()->mutable_index(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::write(out->mutable_data()->mutable_name(), std::get<1>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::read(::orgproto::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Tblfm::Expr::AxisRef::Position::Data::kIndex:
      in.for_field_variant<0>(&org::sem::Tblfm::Expr::AxisRef::Position::data).get();
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::read(out.data().index(), in.for_field_variant<0>(&org::sem::Tblfm::Expr::AxisRef::Position::data));
      break;
    case ::orgproto::Tblfm::Expr::AxisRef::Position::Data::kName:
      in.for_field_variant<1>(&org::sem::Tblfm::Expr::AxisRef::Position::data).get();
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::read(out.data().name(), in.for_field_variant<1>(&org::sem::Tblfm::Expr::AxisRef::Position::data));
      break;
    case ::orgproto::Tblfm::Expr::AxisRef::Position::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(::orgproto::Tblfm::Expr::AxisRef* out, org::sem::Tblfm::Expr::AxisRef const& in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_col(), in.col);
  if (in.row) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_row(), *in.row);
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(::orgproto::Tblfm::Expr::AxisRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef> in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::read(out.col(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::col));
  if (out.has_row()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef::Position>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>>::read(out.row(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::row));
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::write(::orgproto::Tblfm::Expr::AxisName* out, org::sem::Tblfm::Expr::AxisName const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::read(::orgproto::Tblfm::Expr::AxisName const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisName> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::AxisName::name));
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::write(::orgproto::Tblfm::Expr::IntLiteral* out, org::sem::Tblfm::Expr::IntLiteral const& in) {
  out->set_value(in.value);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::read(::orgproto::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::IntLiteral> in) {
  in.for_field(&org::sem::Tblfm::Expr::IntLiteral::value).get() = out.value();
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::write(::orgproto::Tblfm::Expr::FloatLiteral* out, org::sem::Tblfm::Expr::FloatLiteral const& in) {
  out->set_value(in.value);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::read(::orgproto::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::FloatLiteral> in) {
  in.for_field(&org::sem::Tblfm::Expr::FloatLiteral::value).get() = out.value();
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::write(::orgproto::Tblfm::Expr::RangeRef* out, org::sem::Tblfm::Expr::RangeRef const& in) {
  if (in.first) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_first(), *in.first);
  }
  if (in.last) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_last(), *in.last);
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::read(::orgproto::Tblfm::Expr::RangeRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::RangeRef> in) {
  if (out.has_first()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::read(out.first(), in.for_field(&org::sem::Tblfm::Expr::RangeRef::first));
  }
  if (out.has_last()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::read(out.last(), in.for_field(&org::sem::Tblfm::Expr::RangeRef::last));
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::write(::orgproto::Tblfm::Expr::Call* out, org::sem::Tblfm::Expr::Call const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::write(out->mutable_args(), in.args);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::read(::orgproto::Tblfm::Expr::Call const& out, proto_write_accessor<org::sem::Tblfm::Expr::Call> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::Call::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::read(out.args(), in.for_field(&org::sem::Tblfm::Expr::Call::args));
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::write(::orgproto::Tblfm::Expr::Elisp* out, org::sem::Tblfm::Expr::Elisp const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::read(::orgproto::Tblfm::Expr::Elisp const& out, proto_write_accessor<org::sem::Tblfm::Expr::Elisp> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::Tblfm::Expr::Elisp::value));
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr, org::sem::Tblfm::Expr>::write(::orgproto::Tblfm::Expr* out, org::sem::Tblfm::Expr const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_data()->mutable_axisref(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::write(out->mutable_data()->mutable_axisname(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::write(out->mutable_data()->mutable_intliteral(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::write(out->mutable_data()->mutable_floatliteral(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::write(out->mutable_data()->mutable_rangeref(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::write(out->mutable_data()->mutable_call(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::write(out->mutable_data()->mutable_elisp(), std::get<6>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Expr, org::sem::Tblfm::Expr>::read(::orgproto::Tblfm::Expr const& out, proto_write_accessor<org::sem::Tblfm::Expr> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Tblfm::Expr::Data::kAxisref:
      in.for_field_variant<0>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(out.data().axisref(), in.for_field_variant<0>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kAxisname:
      in.for_field_variant<1>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::read(out.data().axisname(), in.for_field_variant<1>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kIntliteral:
      in.for_field_variant<2>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::read(out.data().intliteral(), in.for_field_variant<2>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kFloatliteral:
      in.for_field_variant<3>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::read(out.data().floatliteral(), in.for_field_variant<3>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kRangeref:
      in.for_field_variant<4>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::read(out.data().rangeref(), in.for_field_variant<4>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kCall:
      in.for_field_variant<5>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::read(out.data().call(), in.for_field_variant<5>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kElisp:
      in.for_field_variant<6>(&org::sem::Tblfm::Expr::data).get();
      proto_serde<orgproto::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::read(out.data().elisp(), in.for_field_variant<6>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::Tblfm::Assign, org::sem::Tblfm::Assign>::write(::orgproto::Tblfm::Assign* out, org::sem::Tblfm::Assign const& in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_target(), in.target);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::write(out->mutable_expr(), in.expr);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>, hstd::Vec<org::sem::Tblfm::Assign::Flag>>::write(out->mutable_flags(), in.flags);
}

void org::algo::proto_serde<::orgproto::Tblfm::Assign, org::sem::Tblfm::Assign>::read(::orgproto::Tblfm::Assign const& out, proto_write_accessor<org::sem::Tblfm::Assign> in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(out.target(), in.for_field(&org::sem::Tblfm::Assign::target));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::read(out.expr(), in.for_field(&org::sem::Tblfm::Assign::expr));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>, hstd::Vec<org::sem::Tblfm::Assign::Flag>>::read(out.flags(), in.for_field(&org::sem::Tblfm::Assign::flags));
}

void org::algo::proto_serde<::orgproto::Tblfm, org::sem::Tblfm>::write(::orgproto::Tblfm* out, org::sem::Tblfm const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Assign>, hstd::Vec<org::sem::Tblfm::Assign>>::write(out->mutable_exprs(), in.exprs);
}

void org::algo::proto_serde<::orgproto::Tblfm, org::sem::Tblfm>::read(::orgproto::Tblfm const& out, proto_write_accessor<org::sem::Tblfm> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Assign>, hstd::Vec<org::sem::Tblfm::Assign>>::read(out.exprs(), in.for_field(&org::sem::Tblfm::exprs));
}

void org::algo::proto_serde<::orgproto::AttrValue::DimensionSpan, org::sem::AttrValue::DimensionSpan>::write(::orgproto::AttrValue::DimensionSpan* out, org::sem::AttrValue::DimensionSpan const& in) {
  out->set_first(in.first);
  if (in.last) {
    out->set_last(*in.last);
  }
}

void org::algo::proto_serde<::orgproto::AttrValue::DimensionSpan, org::sem::AttrValue::DimensionSpan>::read(::orgproto::AttrValue::DimensionSpan const& out, proto_write_accessor<org::sem::AttrValue::DimensionSpan> in) {
  in.for_field(&org::sem::AttrValue::DimensionSpan::first).get() = out.first();
  if (out.has_last()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.last(), in.for_field(&org::sem::AttrValue::DimensionSpan::last));
  }
}

void org::algo::proto_serde<::orgproto::AttrValue::TextValue, org::sem::AttrValue::TextValue>::write(::orgproto::AttrValue::TextValue* out, org::sem::AttrValue::TextValue const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::AttrValue::TextValue, org::sem::AttrValue::TextValue>::read(::orgproto::AttrValue::TextValue const& out, proto_write_accessor<org::sem::AttrValue::TextValue> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::AttrValue::TextValue::value));
}

void org::algo::proto_serde<::orgproto::AttrValue::FileReference, org::sem::AttrValue::FileReference>::write(::orgproto::AttrValue::FileReference* out, org::sem::AttrValue::FileReference const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
  proto_serde<std::string, hstd::Str>::write(out->mutable_reference(), in.reference);
}

void org::algo::proto_serde<::orgproto::AttrValue::FileReference, org::sem::AttrValue::FileReference>::read(::orgproto::AttrValue::FileReference const& out, proto_write_accessor<org::sem::AttrValue::FileReference> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::AttrValue::FileReference::file));
  proto_serde<std::string, hstd::Str>::read(out.reference(), in.for_field(&org::sem::AttrValue::FileReference::reference));
}

void org::algo::proto_serde<::orgproto::AttrValue::LispValue, org::sem::AttrValue::LispValue>::write(::orgproto::AttrValue::LispValue* out, org::sem::AttrValue::LispValue const& in) {
  proto_serde<orgproto::LispCode, org::sem::LispCode>::write(out->mutable_code(), in.code);
}

void org::algo::proto_serde<::orgproto::AttrValue::LispValue, org::sem::AttrValue::LispValue>::read(::orgproto::AttrValue::LispValue const& out, proto_write_accessor<org::sem::AttrValue::LispValue> in) {
  proto_serde<orgproto::LispCode, org::sem::LispCode>::read(out.code(), in.for_field(&org::sem::AttrValue::LispValue::code));
}

void org::algo::proto_serde<::orgproto::AttrValue, org::sem::AttrValue>::write(::orgproto::AttrValue* out, org::sem::AttrValue const& in) {
  if (in.name) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_name(), *in.name);
  }
  if (in.varname) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_varname(), *in.varname);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue::DimensionSpan>, hstd::Vec<org::sem::AttrValue::DimensionSpan>>::write(out->mutable_span(), in.span);
  out->set_isquoted(in.isQuoted);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::AttrValue::TextValue, org::sem::AttrValue::TextValue>::write(out->mutable_data()->mutable_textvalue(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::AttrValue::FileReference, org::sem::AttrValue::FileReference>::write(out->mutable_data()->mutable_filereference(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::AttrValue::LispValue, org::sem::AttrValue::LispValue>::write(out->mutable_data()->mutable_lispvalue(), std::get<2>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::AttrValue, org::sem::AttrValue>::read(::orgproto::AttrValue const& out, proto_write_accessor<org::sem::AttrValue> in) {
  if (out.has_name()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.name(), in.for_field(&org::sem::AttrValue::name));
  }
  if (out.has_varname()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.varname(), in.for_field(&org::sem::AttrValue::varname));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue::DimensionSpan>, hstd::Vec<org::sem::AttrValue::DimensionSpan>>::read(out.span(), in.for_field(&org::sem::AttrValue::span));
  in.for_field(&org::sem::AttrValue::isQuoted).get() = out.isquoted();
  switch (out.data().kind_case()) {
    case ::orgproto::AttrValue::DataVariant::kTextvalue:
      in.for_field_variant<0>(&org::sem::AttrValue::data).get();
      proto_serde<orgproto::AttrValue::TextValue, org::sem::AttrValue::TextValue>::read(out.data().textvalue(), in.for_field_variant<0>(&org::sem::AttrValue::data));
      break;
    case ::orgproto::AttrValue::DataVariant::kFilereference:
      in.for_field_variant<1>(&org::sem::AttrValue::data).get();
      proto_serde<orgproto::AttrValue::FileReference, org::sem::AttrValue::FileReference>::read(out.data().filereference(), in.for_field_variant<1>(&org::sem::AttrValue::data));
      break;
    case ::orgproto::AttrValue::DataVariant::kLispvalue:
      in.for_field_variant<2>(&org::sem::AttrValue::data).get();
      proto_serde<orgproto::AttrValue::LispValue, org::sem::AttrValue::LispValue>::read(out.data().lispvalue(), in.for_field_variant<2>(&org::sem::AttrValue::data));
      break;
    case ::orgproto::AttrValue::DataVariant::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::HashTagFlat, org::sem::HashTagFlat>::write(::orgproto::HashTagFlat* out, org::sem::HashTagFlat const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_tags(), in.tags);
}

void org::algo::proto_serde<::orgproto::HashTagFlat, org::sem::HashTagFlat>::read(::orgproto::HashTagFlat const& out, proto_write_accessor<org::sem::HashTagFlat> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.tags(), in.for_field(&org::sem::HashTagFlat::tags));
}

void org::algo::proto_serde<::orgproto::TodoKeyword, org::sem::TodoKeyword>::write(::orgproto::TodoKeyword* out, org::sem::TodoKeyword const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  if (in.shortcut) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_shortcut(), *in.shortcut);
  }
  out->set_onenter(static_cast<orgproto::TodoKeyword_Transition>(in.onEnter));
  out->set_onleave(static_cast<orgproto::TodoKeyword_Transition>(in.onLeave));
}

void org::algo::proto_serde<::orgproto::TodoKeyword, org::sem::TodoKeyword>::read(::orgproto::TodoKeyword const& out, proto_write_accessor<org::sem::TodoKeyword> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::TodoKeyword::name));
  if (out.has_shortcut()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.shortcut(), in.for_field(&org::sem::TodoKeyword::shortcut));
  }
  in.for_field(&org::sem::TodoKeyword::onEnter).get() = static_cast<org::sem::TodoKeyword::Transition>(out.onenter());
  in.for_field(&org::sem::TodoKeyword::onLeave).get() = static_cast<org::sem::TodoKeyword::Transition>(out.onleave());
}

void org::algo::proto_serde<::orgproto::HashTagText, org::sem::HashTagText>::write(::orgproto::HashTagText* out, org::sem::HashTagText const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTagText>, hstd::Vec<org::sem::HashTagText>>::write(out->mutable_subtags(), in.subtags);
}

void org::algo::proto_serde<::orgproto::HashTagText, org::sem::HashTagText>::read(::orgproto::HashTagText const& out, proto_write_accessor<org::sem::HashTagText> in) {
  proto_serde<std::string, hstd::Str>::read(out.head(), in.for_field(&org::sem::HashTagText::head));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTagText>, hstd::Vec<org::sem::HashTagText>>::read(out.subtags(), in.for_field(&org::sem::HashTagText::subtags));
}

void org::algo::proto_serde<::orgproto::SubtreePath, org::sem::SubtreePath>::write(::orgproto::SubtreePath* out, org::sem::SubtreePath const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_path(), in.path);
}

void org::algo::proto_serde<::orgproto::SubtreePath, org::sem::SubtreePath>::read(::orgproto::SubtreePath const& out, proto_write_accessor<org::sem::SubtreePath> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.path(), in.for_field(&org::sem::SubtreePath::path));
}

void org::algo::proto_serde<::orgproto::LinkTarget::Raw, org::sem::LinkTarget::Raw>::write(::orgproto::LinkTarget::Raw* out, org::sem::LinkTarget::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Raw, org::sem::LinkTarget::Raw>::read(::orgproto::LinkTarget::Raw const& out, proto_write_accessor<org::sem::LinkTarget::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::Raw::text));
}

void org::algo::proto_serde<::orgproto::LinkTarget::Id, org::sem::LinkTarget::Id>::write(::orgproto::LinkTarget::Id* out, org::sem::LinkTarget::Id const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Id, org::sem::LinkTarget::Id>::read(::orgproto::LinkTarget::Id const& out, proto_write_accessor<org::sem::LinkTarget::Id> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::Id::text));
}

void org::algo::proto_serde<::orgproto::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::write(::orgproto::LinkTarget::CustomId* out, org::sem::LinkTarget::CustomId const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::read(::orgproto::LinkTarget::CustomId const& out, proto_write_accessor<org::sem::LinkTarget::CustomId> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::CustomId::text));
}

void org::algo::proto_serde<::orgproto::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::write(::orgproto::LinkTarget::SubtreeTitle* out, org::sem::LinkTarget::SubtreeTitle const& in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::write(out->mutable_title(), in.title);
  out->set_level(in.level);
}

void org::algo::proto_serde<::orgproto::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::read(::orgproto::LinkTarget::SubtreeTitle const& out, proto_write_accessor<org::sem::LinkTarget::SubtreeTitle> in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::read(out.title(), in.for_field(&org::sem::LinkTarget::SubtreeTitle::title));
  in.for_field(&org::sem::LinkTarget::SubtreeTitle::level).get() = out.level();
}

void org::algo::proto_serde<::orgproto::LinkTarget::Person, org::sem::LinkTarget::Person>::write(::orgproto::LinkTarget::Person* out, org::sem::LinkTarget::Person const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Person, org::sem::LinkTarget::Person>::read(::orgproto::LinkTarget::Person const& out, proto_write_accessor<org::sem::LinkTarget::Person> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::LinkTarget::Person::name));
}

void org::algo::proto_serde<::orgproto::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::write(::orgproto::LinkTarget::UserProtocol* out, org::sem::LinkTarget::UserProtocol const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_protocol(), in.protocol);
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::read(::orgproto::LinkTarget::UserProtocol const& out, proto_write_accessor<org::sem::LinkTarget::UserProtocol> in) {
  proto_serde<std::string, hstd::Str>::read(out.protocol(), in.for_field(&org::sem::LinkTarget::UserProtocol::protocol));
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::UserProtocol::target));
}

void org::algo::proto_serde<::orgproto::LinkTarget::Internal, org::sem::LinkTarget::Internal>::write(::orgproto::LinkTarget::Internal* out, org::sem::LinkTarget::Internal const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Internal, org::sem::LinkTarget::Internal>::read(::orgproto::LinkTarget::Internal const& out, proto_write_accessor<org::sem::LinkTarget::Internal> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::Internal::target));
}

void org::algo::proto_serde<::orgproto::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::write(::orgproto::LinkTarget::Footnote* out, org::sem::LinkTarget::Footnote const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::read(::orgproto::LinkTarget::Footnote const& out, proto_write_accessor<org::sem::LinkTarget::Footnote> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::Footnote::target));
}

void org::algo::proto_serde<::orgproto::LinkTarget::File, org::sem::LinkTarget::File>::write(::orgproto::LinkTarget::File* out, org::sem::LinkTarget::File const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void org::algo::proto_serde<::orgproto::LinkTarget::File, org::sem::LinkTarget::File>::read(::orgproto::LinkTarget::File const& out, proto_write_accessor<org::sem::LinkTarget::File> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::LinkTarget::File::file));
}

void org::algo::proto_serde<::orgproto::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::write(::orgproto::LinkTarget::Attachment* out, org::sem::LinkTarget::Attachment const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void org::algo::proto_serde<::orgproto::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::read(::orgproto::LinkTarget::Attachment const& out, proto_write_accessor<org::sem::LinkTarget::Attachment> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::LinkTarget::Attachment::file));
}

void org::algo::proto_serde<::orgproto::LinkTarget, org::sem::LinkTarget>::write(::orgproto::LinkTarget* out, org::sem::LinkTarget const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::LinkTarget::Raw, org::sem::LinkTarget::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::LinkTarget::Id, org::sem::LinkTarget::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::write(out->mutable_data()->mutable_customid(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::write(out->mutable_data()->mutable_subtreetitle(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::LinkTarget::Person, org::sem::LinkTarget::Person>::write(out->mutable_data()->mutable_person(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::write(out->mutable_data()->mutable_userprotocol(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::LinkTarget::Internal, org::sem::LinkTarget::Internal>::write(out->mutable_data()->mutable_internal(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::LinkTarget::File, org::sem::LinkTarget::File>::write(out->mutable_data()->mutable_file(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<9>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::LinkTarget, org::sem::LinkTarget>::read(::orgproto::LinkTarget const& out, proto_write_accessor<org::sem::LinkTarget> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::LinkTarget::Data::kRaw:
      in.for_field_variant<0>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Raw, org::sem::LinkTarget::Raw>::read(out.data().raw(), in.for_field_variant<0>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kId:
      in.for_field_variant<1>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Id, org::sem::LinkTarget::Id>::read(out.data().id(), in.for_field_variant<1>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kCustomid:
      in.for_field_variant<2>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::read(out.data().customid(), in.for_field_variant<2>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kSubtreetitle:
      in.for_field_variant<3>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::read(out.data().subtreetitle(), in.for_field_variant<3>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kPerson:
      in.for_field_variant<4>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Person, org::sem::LinkTarget::Person>::read(out.data().person(), in.for_field_variant<4>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kUserprotocol:
      in.for_field_variant<5>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::read(out.data().userprotocol(), in.for_field_variant<5>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kInternal:
      in.for_field_variant<6>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Internal, org::sem::LinkTarget::Internal>::read(out.data().internal(), in.for_field_variant<6>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kFootnote:
      in.for_field_variant<7>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::read(out.data().footnote(), in.for_field_variant<7>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kFile:
      in.for_field_variant<8>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::File, org::sem::LinkTarget::File>::read(out.data().file(), in.for_field_variant<8>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kAttachment:
      in.for_field_variant<9>(&org::sem::LinkTarget::data).get();
      proto_serde<orgproto::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::read(out.data().attachment(), in.for_field_variant<9>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::write(::orgproto::SubtreeLogHead::Priority* out, org::sem::SubtreeLogHead::Priority const& in) {
  if (in.oldPriority) {
    out->set_oldpriority(*in.oldPriority);
  }
  if (in.newPriority) {
    out->set_newpriority(*in.newPriority);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  out->set_action(static_cast<orgproto::SubtreeLogHead_Priority_Action>(in.action));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::read(::orgproto::SubtreeLogHead::Priority const& out, proto_write_accessor<org::sem::SubtreeLogHead::Priority> in) {
  if (out.has_oldpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.oldpriority(), in.for_field(&org::sem::SubtreeLogHead::Priority::oldPriority));
  }
  if (out.has_newpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.newpriority(), in.for_field(&org::sem::SubtreeLogHead::Priority::newPriority));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Priority::on));
  in.for_field(&org::sem::SubtreeLogHead::Priority::action).get() = static_cast<org::sem::SubtreeLogHead::Priority::Action>(out.action());
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::write(::orgproto::SubtreeLogHead::Note* out, org::sem::SubtreeLogHead::Note const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::read(::orgproto::SubtreeLogHead::Note const& out, proto_write_accessor<org::sem::SubtreeLogHead::Note> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Note::on));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::write(::orgproto::SubtreeLogHead::Refile* out, org::sem::SubtreeLogHead::Refile const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::LinkTarget, org::sem::LinkTarget>::write(out->mutable_from(), in.from);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::read(::orgproto::SubtreeLogHead::Refile const& out, proto_write_accessor<org::sem::SubtreeLogHead::Refile> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Refile::on));
  proto_serde<orgproto::LinkTarget, org::sem::LinkTarget>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Refile::from));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::write(::orgproto::SubtreeLogHead::Clock* out, org::sem::SubtreeLogHead::Clock const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), *in.to);
  }
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::read(::orgproto::SubtreeLogHead::Clock const& out, proto_write_accessor<org::sem::SubtreeLogHead::Clock> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Clock::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Clock::to));
  }
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::write(::orgproto::SubtreeLogHead::State* out, org::sem::SubtreeLogHead::State const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_from(), in.from);
  proto_serde<std::string, hstd::Str>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::read(::orgproto::SubtreeLogHead::State const& out, proto_write_accessor<org::sem::SubtreeLogHead::State> in) {
  proto_serde<std::string, hstd::Str>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::State::from));
  proto_serde<std::string, hstd::Str>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::State::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::State::on));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::write(::orgproto::SubtreeLogHead::Deadline* out, org::sem::SubtreeLogHead::Deadline const& in) {
  if (in.from) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::read(::orgproto::SubtreeLogHead::Deadline const& out, proto_write_accessor<org::sem::SubtreeLogHead::Deadline> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Deadline::from));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Deadline::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Deadline::on));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::write(::orgproto::SubtreeLogHead::Schedule* out, org::sem::SubtreeLogHead::Schedule const& in) {
  if (in.from) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::read(::orgproto::SubtreeLogHead::Schedule const& out, proto_write_accessor<org::sem::SubtreeLogHead::Schedule> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Schedule::from));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Schedule::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Schedule::on));
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::write(::orgproto::SubtreeLogHead::Tag* out, org::sem::SubtreeLogHead::Tag const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::write(out->mutable_tag(), in.tag);
  out->set_added(in.added);
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::read(::orgproto::SubtreeLogHead::Tag const& out, proto_write_accessor<org::sem::SubtreeLogHead::Tag> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Tag::on));
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::read(out.tag(), in.for_field(&org::sem::SubtreeLogHead::Tag::tag));
  in.for_field(&org::sem::SubtreeLogHead::Tag::added).get() = out.added();
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::write(::orgproto::SubtreeLogHead::Unknown* out, org::sem::SubtreeLogHead::Unknown const& in) {

}

void org::algo::proto_serde<::orgproto::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::read(::orgproto::SubtreeLogHead::Unknown const& out, proto_write_accessor<org::sem::SubtreeLogHead::Unknown> in) {

}

void org::algo::proto_serde<::orgproto::SubtreeLogHead, org::sem::SubtreeLogHead>::write(::orgproto::SubtreeLogHead* out, org::sem::SubtreeLogHead const& in) {
  switch (in.log.index()) {
    case 0:
      proto_serde<orgproto::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log));
      break;
    case 1:
      proto_serde<orgproto::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log));
      break;
    case 2:
      proto_serde<orgproto::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log));
      break;
    case 3:
      proto_serde<orgproto::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log));
      break;
    case 4:
      proto_serde<orgproto::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log));
      break;
    case 5:
      proto_serde<orgproto::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::write(out->mutable_log()->mutable_deadline(), std::get<5>(in.log));
      break;
    case 6:
      proto_serde<orgproto::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::write(out->mutable_log()->mutable_schedule(), std::get<6>(in.log));
      break;
    case 7:
      proto_serde<orgproto::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::write(out->mutable_log()->mutable_tag(), std::get<7>(in.log));
      break;
    case 8:
      proto_serde<orgproto::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::write(out->mutable_log()->mutable_unknown(), std::get<8>(in.log));
      break;
  }
}

void org::algo::proto_serde<::orgproto::SubtreeLogHead, org::sem::SubtreeLogHead>::read(::orgproto::SubtreeLogHead const& out, proto_write_accessor<org::sem::SubtreeLogHead> in) {
  switch (out.log().kind_case()) {
    case ::orgproto::SubtreeLogHead::LogEntry::kPriority:
      in.for_field_variant<0>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::read(out.log().priority(), in.for_field_variant<0>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kNote:
      in.for_field_variant<1>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::read(out.log().note(), in.for_field_variant<1>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kRefile:
      in.for_field_variant<2>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::read(out.log().refile(), in.for_field_variant<2>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kClock:
      in.for_field_variant<3>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::read(out.log().clock(), in.for_field_variant<3>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kState:
      in.for_field_variant<4>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::read(out.log().state(), in.for_field_variant<4>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kDeadline:
      in.for_field_variant<5>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::read(out.log().deadline(), in.for_field_variant<5>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kSchedule:
      in.for_field_variant<6>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::read(out.log().schedule(), in.for_field_variant<6>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kTag:
      in.for_field_variant<7>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::read(out.log().tag(), in.for_field_variant<7>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kUnknown:
      in.for_field_variant<8>(&org::sem::SubtreeLogHead::log).get();
      proto_serde<orgproto::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::read(out.log().unknown(), in.for_field_variant<8>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::SubtreeCompletion, org::sem::SubtreeCompletion>::write(::orgproto::SubtreeCompletion* out, org::sem::SubtreeCompletion const& in) {
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void org::algo::proto_serde<::orgproto::SubtreeCompletion, org::sem::SubtreeCompletion>::read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<org::sem::SubtreeCompletion> in) {
  in.for_field(&org::sem::SubtreeCompletion::done).get() = out.done();
  in.for_field(&org::sem::SubtreeCompletion::full).get() = out.full();
  in.for_field(&org::sem::SubtreeCompletion::isPercent).get() = out.ispercent();
}

void org::algo::proto_serde<::orgproto::AttrList, org::sem::AttrList>::write(::orgproto::AttrList* out, org::sem::AttrList const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue>, hstd::Vec<org::sem::AttrValue>>::write(out->mutable_items(), in.items);
}

void org::algo::proto_serde<::orgproto::AttrList, org::sem::AttrList>::read(::orgproto::AttrList const& out, proto_write_accessor<org::sem::AttrList> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue>, hstd::Vec<org::sem::AttrValue>>::read(out.items(), in.for_field(&org::sem::AttrList::items));
}

void org::algo::proto_serde<::orgproto::AttrGroup, org::sem::AttrGroup>::write(::orgproto::AttrGroup* out, org::sem::AttrGroup const& in) {
  proto_serde<orgproto::AttrList, org::sem::AttrList>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AttrList>, hstd::UnorderedMap<hstd::Str, org::sem::AttrList>>::write(out->mutable_named(), in.named);
}

void org::algo::proto_serde<::orgproto::AttrGroup, org::sem::AttrGroup>::read(::orgproto::AttrGroup const& out, proto_write_accessor<org::sem::AttrGroup> in) {
  proto_serde<orgproto::AttrList, org::sem::AttrList>::read(out.positional(), in.for_field(&org::sem::AttrGroup::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::AttrList>, hstd::UnorderedMap<hstd::Str, org::sem::AttrList>>::read(out.named(), in.for_field(&org::sem::AttrGroup::named));
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalInput::Var, org::sem::OrgCodeEvalInput::Var>::write(::orgproto::OrgCodeEvalInput::Var* out, org::sem::OrgCodeEvalInput::Var const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::OrgJson, org::sem::OrgJson>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalInput::Var, org::sem::OrgCodeEvalInput::Var>::read(::orgproto::OrgCodeEvalInput::Var const& out, proto_write_accessor<org::sem::OrgCodeEvalInput::Var> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::OrgCodeEvalInput::Var::name));
  proto_serde<orgproto::OrgJson, org::sem::OrgJson>::read(out.value(), in.for_field(&org::sem::OrgCodeEvalInput::Var::value));
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalInput, org::sem::OrgCodeEvalInput>::write(::orgproto::OrgCodeEvalInput* out, org::sem::OrgCodeEvalInput const& in) {
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_blockattrs(), in.blockAttrs);
  proto_serde<std::string, hstd::Str>::write(out->mutable_tangledcode(), in.tangledCode);
  if (in.exportType) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_exporttype(), *in.exportType);
  }
  out->set_resulttype(static_cast<orgproto::OrgCodeEvalInput_ResultType>(in.resultType));
  out->set_resultformat(static_cast<orgproto::OrgCodeEvalInput_ResultFormat>(in.resultFormat));
  out->set_resulthandling(static_cast<orgproto::OrgCodeEvalInput_ResultHandling>(in.resultHandling));
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::OrgCodeEvalInput::Var>, hstd::Vec<org::sem::OrgCodeEvalInput::Var>>::write(out->mutable_arglist(), in.argList);
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalInput, org::sem::OrgCodeEvalInput>::read(::orgproto::OrgCodeEvalInput const& out, proto_write_accessor<org::sem::OrgCodeEvalInput> in) {
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.blockattrs(), in.for_field(&org::sem::OrgCodeEvalInput::blockAttrs));
  proto_serde<std::string, hstd::Str>::read(out.tangledcode(), in.for_field(&org::sem::OrgCodeEvalInput::tangledCode));
  if (out.has_exporttype()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.exporttype(), in.for_field(&org::sem::OrgCodeEvalInput::exportType));
  }
  in.for_field(&org::sem::OrgCodeEvalInput::resultType).get() = static_cast<org::sem::OrgCodeEvalInput::ResultType>(out.resulttype());
  in.for_field(&org::sem::OrgCodeEvalInput::resultFormat).get() = static_cast<org::sem::OrgCodeEvalInput::ResultFormat>(out.resultformat());
  in.for_field(&org::sem::OrgCodeEvalInput::resultHandling).get() = static_cast<org::sem::OrgCodeEvalInput::ResultHandling>(out.resulthandling());
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&org::sem::OrgCodeEvalInput::language));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::OrgCodeEvalInput::Var>, hstd::Vec<org::sem::OrgCodeEvalInput::Var>>::read(out.arglist(), in.for_field(&org::sem::OrgCodeEvalInput::argList));
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalOutput, org::sem::OrgCodeEvalOutput>::write(::orgproto::OrgCodeEvalOutput* out, org::sem::OrgCodeEvalOutput const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_stdouttext(), in.stdoutText);
  proto_serde<std::string, hstd::Str>::write(out->mutable_stderrtext(), in.stderrText);
  out->set_code(in.code);
  if (in.cmd) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_cmd(), *in.cmd);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_args(), in.args);
  proto_serde<std::string, hstd::Str>::write(out->mutable_cwd(), in.cwd);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_appliedheaderarg(), in.appliedHeaderArg);
}

void org::algo::proto_serde<::orgproto::OrgCodeEvalOutput, org::sem::OrgCodeEvalOutput>::read(::orgproto::OrgCodeEvalOutput const& out, proto_write_accessor<org::sem::OrgCodeEvalOutput> in) {
  proto_serde<std::string, hstd::Str>::read(out.stdouttext(), in.for_field(&org::sem::OrgCodeEvalOutput::stdoutText));
  proto_serde<std::string, hstd::Str>::read(out.stderrtext(), in.for_field(&org::sem::OrgCodeEvalOutput::stderrText));
  in.for_field(&org::sem::OrgCodeEvalOutput::code).get() = out.code();
  if (out.has_cmd()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.cmd(), in.for_field(&org::sem::OrgCodeEvalOutput::cmd));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.args(), in.for_field(&org::sem::OrgCodeEvalOutput::args));
  proto_serde<std::string, hstd::Str>::read(out.cwd(), in.for_field(&org::sem::OrgCodeEvalOutput::cwd));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.appliedheaderarg(), in.for_field(&org::sem::OrgCodeEvalOutput::appliedHeaderArg));
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::write(::orgproto::ColumnView::Summary::CheckboxAggregate* out, org::sem::ColumnView::Summary::CheckboxAggregate const& in) {
  out->set_kind(static_cast<orgproto::ColumnView_Summary_CheckboxAggregate_Kind>(in.kind));
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::read(::orgproto::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::CheckboxAggregate> in) {
  in.for_field(&org::sem::ColumnView::Summary::CheckboxAggregate::kind).get() = static_cast<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(out.kind());
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::write(::orgproto::ColumnView::Summary::MathAggregate* out, org::sem::ColumnView::Summary::MathAggregate const& in) {
  out->set_kind(static_cast<orgproto::ColumnView_Summary_MathAggregate_Kind>(in.kind));
  if (in.formatDigits) {
    out->set_formatdigits(*in.formatDigits);
  }
  if (in.formatPrecision) {
    out->set_formatprecision(*in.formatPrecision);
  }
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::read(::orgproto::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::MathAggregate> in) {
  in.for_field(&org::sem::ColumnView::Summary::MathAggregate::kind).get() = static_cast<org::sem::ColumnView::Summary::MathAggregate::Kind>(out.kind());
  if (out.has_formatdigits()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatdigits(), in.for_field(&org::sem::ColumnView::Summary::MathAggregate::formatDigits));
  }
  if (out.has_formatprecision()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatprecision(), in.for_field(&org::sem::ColumnView::Summary::MathAggregate::formatPrecision));
  }
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary, org::sem::ColumnView::Summary>::write(::orgproto::ColumnView::Summary* out, org::sem::ColumnView::Summary const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::write(out->mutable_data()->mutable_checkboxaggregate(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::write(out->mutable_data()->mutable_mathaggregate(), std::get<1>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::ColumnView::Summary, org::sem::ColumnView::Summary>::read(::orgproto::ColumnView::Summary const& out, proto_write_accessor<org::sem::ColumnView::Summary> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::ColumnView::Summary::Data::kCheckboxaggregate:
      in.for_field_variant<0>(&org::sem::ColumnView::Summary::data).get();
      proto_serde<orgproto::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::read(out.data().checkboxaggregate(), in.for_field_variant<0>(&org::sem::ColumnView::Summary::data));
      break;
    case ::orgproto::ColumnView::Summary::Data::kMathaggregate:
      in.for_field_variant<1>(&org::sem::ColumnView::Summary::data).get();
      proto_serde<orgproto::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::read(out.data().mathaggregate(), in.for_field_variant<1>(&org::sem::ColumnView::Summary::data));
      break;
    case ::orgproto::ColumnView::Summary::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::ColumnView::Column, org::sem::ColumnView::Column>::write(::orgproto::ColumnView::Column* out, org::sem::ColumnView::Column const& in) {
  if (in.summary) {
    proto_serde<orgproto::ColumnView::Summary, org::sem::ColumnView::Summary>::write(out->mutable_summary(), *in.summary);
  }
  if (in.width) {
    out->set_width(*in.width);
  }
  if (in.property) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_property(), *in.property);
  }
  if (in.propertyTitle) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_propertytitle(), *in.propertyTitle);
  }
}

void org::algo::proto_serde<::orgproto::ColumnView::Column, org::sem::ColumnView::Column>::read(::orgproto::ColumnView::Column const& out, proto_write_accessor<org::sem::ColumnView::Column> in) {
  if (out.has_summary()) {
    proto_serde<hstd::Opt<orgproto::ColumnView::Summary>, hstd::Opt<org::sem::ColumnView::Summary>>::read(out.summary(), in.for_field(&org::sem::ColumnView::Column::summary));
  }
  if (out.has_width()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.width(), in.for_field(&org::sem::ColumnView::Column::width));
  }
  if (out.has_property()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.property(), in.for_field(&org::sem::ColumnView::Column::property));
  }
  if (out.has_propertytitle()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.propertytitle(), in.for_field(&org::sem::ColumnView::Column::propertyTitle));
  }
}

void org::algo::proto_serde<::orgproto::ColumnView, org::sem::ColumnView>::write(::orgproto::ColumnView* out, org::sem::ColumnView const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ColumnView::Column>, hstd::Vec<org::sem::ColumnView::Column>>::write(out->mutable_columns(), in.columns);
}

void org::algo::proto_serde<::orgproto::ColumnView, org::sem::ColumnView>::read(::orgproto::ColumnView const& out, proto_write_accessor<org::sem::ColumnView> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ColumnView::Column>, hstd::Vec<org::sem::ColumnView::Column>>::read(out.columns(), in.for_field(&org::sem::ColumnView::columns));
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::write(::orgproto::BlockCodeLine::Part::Raw* out, org::sem::BlockCodeLine::Part::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_code(), in.code);
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::read(::orgproto::BlockCodeLine::Part::Raw const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.code(), in.for_field(&org::sem::BlockCodeLine::Part::Raw::code));
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::write(::orgproto::BlockCodeLine::Part::Callout* out, org::sem::BlockCodeLine::Part::Callout const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::read(::orgproto::BlockCodeLine::Part::Callout const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Callout> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::BlockCodeLine::Part::Callout::name));
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::write(::orgproto::BlockCodeLine::Part::Tangle* out, org::sem::BlockCodeLine::Part::Tangle const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::read(::orgproto::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Tangle> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::BlockCodeLine::Part::Tangle::target));
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part, org::sem::BlockCodeLine::Part>::write(::orgproto::BlockCodeLine::Part* out, org::sem::BlockCodeLine::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::BlockCodeLine::Part, org::sem::BlockCodeLine::Part>::read(::orgproto::BlockCodeLine::Part const& out, proto_write_accessor<org::sem::BlockCodeLine::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCodeLine::Part::Data::kRaw:
      in.for_field_variant<0>(&org::sem::BlockCodeLine::Part::data).get();
      proto_serde<orgproto::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&org::sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::BlockCodeLine::Part::Data::kCallout:
      in.for_field_variant<1>(&org::sem::BlockCodeLine::Part::data).get();
      proto_serde<orgproto::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&org::sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::BlockCodeLine::Part::Data::kTangle:
      in.for_field_variant<2>(&org::sem::BlockCodeLine::Part::data).get();
      proto_serde<orgproto::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&org::sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::BlockCodeLine::Part::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::BlockCodeLine, org::sem::BlockCodeLine>::write(::orgproto::BlockCodeLine* out, org::sem::BlockCodeLine const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine::Part>, hstd::Vec<org::sem::BlockCodeLine::Part>>::write(out->mutable_parts(), in.parts);
}

void org::algo::proto_serde<::orgproto::BlockCodeLine, org::sem::BlockCodeLine>::read(::orgproto::BlockCodeLine const& out, proto_write_accessor<org::sem::BlockCodeLine> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine::Part>, hstd::Vec<org::sem::BlockCodeLine::Part>>::read(out.parts(), in.for_field(&org::sem::BlockCodeLine::parts));
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport>::write(::orgproto::DocumentExportConfig::TaskExport* out, org::sem::DocumentExportConfig::TaskExport const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_taskwhitelist(), in.taskWhitelist);
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport>::read(::orgproto::DocumentExportConfig::TaskExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::TaskExport> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.taskwhitelist(), in.for_field(&org::sem::DocumentExportConfig::TaskExport::taskWhitelist));
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(::orgproto::DocumentExportConfig::DoExport* out, org::sem::DocumentExportConfig::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(::orgproto::DocumentExportConfig::DoExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::DoExport> in) {
  in.for_field(&org::sem::DocumentExportConfig::DoExport::exportToc).get() = out.exporttoc();
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(::orgproto::DocumentExportConfig::ExportFixed* out, org::sem::DocumentExportConfig::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(::orgproto::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<org::sem::DocumentExportConfig::ExportFixed> in) {
  in.for_field(&org::sem::DocumentExportConfig::ExportFixed::exportLevels).get() = out.exportlevels();
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig, org::sem::DocumentExportConfig>::write(::orgproto::DocumentExportConfig* out, org::sem::DocumentExportConfig const& in) {
  if (in.inlinetasks) {
    out->set_inlinetasks(*in.inlinetasks);
  }
  if (in.footnotes) {
    out->set_footnotes(*in.footnotes);
  }
  if (in.clock) {
    out->set_clock(*in.clock);
  }
  if (in.author) {
    out->set_author(*in.author);
  }
  if (in.emphasis) {
    out->set_emphasis(*in.emphasis);
  }
  if (in.specialStrings) {
    out->set_specialstrings(*in.specialStrings);
  }
  if (in.propertyDrawers) {
    out->set_propertydrawers(*in.propertyDrawers);
  }
  if (in.statisticsCookies) {
    out->set_statisticscookies(*in.statisticsCookies);
  }
  if (in.todoText) {
    out->set_todotext(*in.todoText);
  }
  if (in.smartQuotes) {
    out->set_smartquotes(*in.smartQuotes);
  }
  if (in.fixedWidth) {
    out->set_fixedwidth(*in.fixedWidth);
  }
  if (in.timestamps) {
    out->set_timestamps(*in.timestamps);
  }
  if (in.preserveBreaks) {
    out->set_preservebreaks(*in.preserveBreaks);
  }
  if (in.subSuperscripts) {
    out->set_subsuperscripts(*in.subSuperscripts);
  }
  if (in.expandLinks) {
    out->set_expandlinks(*in.expandLinks);
  }
  if (in.creator) {
    out->set_creator(*in.creator);
  }
  if (in.drawers) {
    out->set_drawers(*in.drawers);
  }
  if (in.date) {
    out->set_date(*in.date);
  }
  if (in.entities) {
    out->set_entities(*in.entities);
  }
  if (in.email) {
    out->set_email(*in.email);
  }
  if (in.sectionNumbers) {
    out->set_sectionnumbers(*in.sectionNumbers);
  }
  if (in.planning) {
    out->set_planning(*in.planning);
  }
  if (in.priority) {
    out->set_priority(*in.priority);
  }
  if (in.latex) {
    out->set_latex(*in.latex);
  }
  if (in.timestamp) {
    out->set_timestamp(*in.timestamp);
  }
  if (in.title) {
    out->set_title(*in.title);
  }
  if (in.tables) {
    out->set_tables(*in.tables);
  }
  if (in.headlineLevels) {
    out->set_headlinelevels(*in.headlineLevels);
  }
  out->set_brokenlinks(static_cast<orgproto::DocumentExportConfig_BrokenLinks>(in.brokenLinks));
  switch (in.tocExport.index()) {
    case 0:
      proto_serde<orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(out->mutable_tocexport()->mutable_doexport(), std::get<0>(in.tocExport));
      break;
    case 1:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(out->mutable_tocexport()->mutable_exportfixed(), std::get<1>(in.tocExport));
      break;
  }
  out->set_tagexport(static_cast<orgproto::DocumentExportConfig_TagExport>(in.tagExport));
  out->set_taskfiltering(static_cast<orgproto::DocumentExportConfig_TaskFiltering>(in.taskFiltering));
  out->set_archivedtrees(static_cast<orgproto::DocumentExportConfig_ArchivedTrees>(in.archivedTrees));
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::DocumentExportConfig, org::sem::DocumentExportConfig>::read(::orgproto::DocumentExportConfig const& out, proto_write_accessor<org::sem::DocumentExportConfig> in) {
  if (out.has_inlinetasks()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.inlinetasks(), in.for_field(&org::sem::DocumentExportConfig::inlinetasks));
  }
  if (out.has_footnotes()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.footnotes(), in.for_field(&org::sem::DocumentExportConfig::footnotes));
  }
  if (out.has_clock()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.clock(), in.for_field(&org::sem::DocumentExportConfig::clock));
  }
  if (out.has_author()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.author(), in.for_field(&org::sem::DocumentExportConfig::author));
  }
  if (out.has_emphasis()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.emphasis(), in.for_field(&org::sem::DocumentExportConfig::emphasis));
  }
  if (out.has_specialstrings()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.specialstrings(), in.for_field(&org::sem::DocumentExportConfig::specialStrings));
  }
  if (out.has_propertydrawers()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.propertydrawers(), in.for_field(&org::sem::DocumentExportConfig::propertyDrawers));
  }
  if (out.has_statisticscookies()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.statisticscookies(), in.for_field(&org::sem::DocumentExportConfig::statisticsCookies));
  }
  if (out.has_todotext()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.todotext(), in.for_field(&org::sem::DocumentExportConfig::todoText));
  }
  if (out.has_smartquotes()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.smartquotes(), in.for_field(&org::sem::DocumentExportConfig::smartQuotes));
  }
  if (out.has_fixedwidth()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.fixedwidth(), in.for_field(&org::sem::DocumentExportConfig::fixedWidth));
  }
  if (out.has_timestamps()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.timestamps(), in.for_field(&org::sem::DocumentExportConfig::timestamps));
  }
  if (out.has_preservebreaks()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.preservebreaks(), in.for_field(&org::sem::DocumentExportConfig::preserveBreaks));
  }
  if (out.has_subsuperscripts()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.subsuperscripts(), in.for_field(&org::sem::DocumentExportConfig::subSuperscripts));
  }
  if (out.has_expandlinks()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.expandlinks(), in.for_field(&org::sem::DocumentExportConfig::expandLinks));
  }
  if (out.has_creator()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.creator(), in.for_field(&org::sem::DocumentExportConfig::creator));
  }
  if (out.has_drawers()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.drawers(), in.for_field(&org::sem::DocumentExportConfig::drawers));
  }
  if (out.has_date()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.date(), in.for_field(&org::sem::DocumentExportConfig::date));
  }
  if (out.has_entities()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.entities(), in.for_field(&org::sem::DocumentExportConfig::entities));
  }
  if (out.has_email()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.email(), in.for_field(&org::sem::DocumentExportConfig::email));
  }
  if (out.has_sectionnumbers()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.sectionnumbers(), in.for_field(&org::sem::DocumentExportConfig::sectionNumbers));
  }
  if (out.has_planning()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.planning(), in.for_field(&org::sem::DocumentExportConfig::planning));
  }
  if (out.has_priority()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.priority(), in.for_field(&org::sem::DocumentExportConfig::priority));
  }
  if (out.has_latex()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.latex(), in.for_field(&org::sem::DocumentExportConfig::latex));
  }
  if (out.has_timestamp()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.timestamp(), in.for_field(&org::sem::DocumentExportConfig::timestamp));
  }
  if (out.has_title()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.title(), in.for_field(&org::sem::DocumentExportConfig::title));
  }
  if (out.has_tables()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.tables(), in.for_field(&org::sem::DocumentExportConfig::tables));
  }
  if (out.has_headlinelevels()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.headlinelevels(), in.for_field(&org::sem::DocumentExportConfig::headlineLevels));
  }
  in.for_field(&org::sem::DocumentExportConfig::brokenLinks).get() = static_cast<org::sem::DocumentExportConfig::BrokenLinks>(out.brokenlinks());
  switch (out.tocexport().kind_case()) {
    case ::orgproto::DocumentExportConfig::TocExport::kDoexport:
      in.for_field_variant<0>(&org::sem::DocumentExportConfig::tocExport).get();
      proto_serde<orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(out.tocexport().doexport(), in.for_field_variant<0>(&org::sem::DocumentExportConfig::tocExport));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::kExportfixed:
      in.for_field_variant<1>(&org::sem::DocumentExportConfig::tocExport).get();
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(out.tocexport().exportfixed(), in.for_field_variant<1>(&org::sem::DocumentExportConfig::tocExport));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
  in.for_field(&org::sem::DocumentExportConfig::tagExport).get() = static_cast<org::sem::DocumentExportConfig::TagExport>(out.tagexport());
  in.for_field(&org::sem::DocumentExportConfig::taskFiltering).get() = static_cast<org::sem::DocumentExportConfig::TaskFiltering>(out.taskfiltering());
  in.for_field(&org::sem::DocumentExportConfig::archivedTrees).get() = static_cast<org::sem::DocumentExportConfig::ArchivedTrees>(out.archivedtrees());
  switch (out.data().kind_case()) {
    case ::orgproto::DocumentExportConfig::TocExport::kDoexport:
      in.for_field_variant<0>(&org::sem::DocumentExportConfig::data).get();
      proto_serde<orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&org::sem::DocumentExportConfig::data));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::kExportfixed:
      in.for_field_variant<1>(&org::sem::DocumentExportConfig::data).get();
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&org::sem::DocumentExportConfig::data));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::SubtreePeriod, org::sem::SubtreePeriod>::write(::orgproto::SubtreePeriod* out, org::sem::SubtreePeriod const& in) {
  out->set_kind(static_cast<orgproto::SubtreePeriod_Kind>(in.kind));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), *in.to);
  }
}

void org::algo::proto_serde<::orgproto::SubtreePeriod, org::sem::SubtreePeriod>::read(::orgproto::SubtreePeriod const& out, proto_write_accessor<org::sem::SubtreePeriod> in) {
  in.for_field(&org::sem::SubtreePeriod::kind).get() = static_cast<org::sem::SubtreePeriod::Kind>(out.kind());
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.from(), in.for_field(&org::sem::SubtreePeriod::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.to(), in.for_field(&org::sem::SubtreePeriod::to));
  }
}

void org::algo::proto_serde<::orgproto::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::write(::orgproto::NamedProperty::Nonblocking* out, org::sem::NamedProperty::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void org::algo::proto_serde<::orgproto::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::read(::orgproto::NamedProperty::Nonblocking const& out, proto_write_accessor<org::sem::NamedProperty::Nonblocking> in) {
  in.for_field(&org::sem::NamedProperty::Nonblocking::isBlocking).get() = out.isblocking();
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::write(::orgproto::NamedProperty::ArchiveTime* out, org::sem::NamedProperty::ArchiveTime const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::read(::orgproto::NamedProperty::ArchiveTime const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTime> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::NamedProperty::ArchiveTime::time));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::write(::orgproto::NamedProperty::ArchiveFile* out, org::sem::NamedProperty::ArchiveFile const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::read(::orgproto::NamedProperty::ArchiveFile const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveFile> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::NamedProperty::ArchiveFile::file));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::write(::orgproto::NamedProperty::ArchiveOlpath* out, org::sem::NamedProperty::ArchiveOlpath const& in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::write(out->mutable_path(), in.path);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::read(::orgproto::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveOlpath> in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::read(out.path(), in.for_field(&org::sem::NamedProperty::ArchiveOlpath::path));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::write(::orgproto::NamedProperty::ArchiveTarget* out, org::sem::NamedProperty::ArchiveTarget const& in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::write(out->mutable_path(), in.path);
  proto_serde<std::string, hstd::Str>::write(out->mutable_pattern(), in.pattern);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::read(::orgproto::NamedProperty::ArchiveTarget const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTarget> in) {
  proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::read(out.path(), in.for_field(&org::sem::NamedProperty::ArchiveTarget::path));
  proto_serde<std::string, hstd::Str>::read(out.pattern(), in.for_field(&org::sem::NamedProperty::ArchiveTarget::pattern));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::write(::orgproto::NamedProperty::ArchiveCategory* out, org::sem::NamedProperty::ArchiveCategory const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_category(), in.category);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::read(::orgproto::NamedProperty::ArchiveCategory const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveCategory> in) {
  proto_serde<std::string, hstd::Str>::read(out.category(), in.for_field(&org::sem::NamedProperty::ArchiveCategory::category));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::write(::orgproto::NamedProperty::ArchiveTodo* out, org::sem::NamedProperty::ArchiveTodo const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_todo(), in.todo);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::read(::orgproto::NamedProperty::ArchiveTodo const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTodo> in) {
  proto_serde<std::string, hstd::Str>::read(out.todo(), in.for_field(&org::sem::NamedProperty::ArchiveTodo::todo));
}

void org::algo::proto_serde<::orgproto::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::write(::orgproto::NamedProperty::Trigger* out, org::sem::NamedProperty::Trigger const& in) {

}

void org::algo::proto_serde<::orgproto::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::read(::orgproto::NamedProperty::Trigger const& out, proto_write_accessor<org::sem::NamedProperty::Trigger> in) {

}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::write(::orgproto::NamedProperty::ExportLatexClass* out, org::sem::NamedProperty::ExportLatexClass const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_latexclass(), in.latexClass);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::read(::orgproto::NamedProperty::ExportLatexClass const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClass> in) {
  proto_serde<std::string, hstd::Str>::read(out.latexclass(), in.for_field(&org::sem::NamedProperty::ExportLatexClass::latexClass));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::write(::orgproto::NamedProperty::CookieData* out, org::sem::NamedProperty::CookieData const& in) {
  out->set_isrecursive(in.isRecursive);
  out->set_source(static_cast<orgproto::SubtreeTodoSource>(in.source));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::read(::orgproto::NamedProperty::CookieData const& out, proto_write_accessor<org::sem::NamedProperty::CookieData> in) {
  in.for_field(&org::sem::NamedProperty::CookieData::isRecursive).get() = out.isrecursive();
  in.for_field(&org::sem::NamedProperty::CookieData::source).get() = static_cast<SubtreeTodoSource>(out.source());
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::write(::orgproto::NamedProperty::ExportLatexClassOptions* out, org::sem::NamedProperty::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_options(), in.options);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::read(::orgproto::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClassOptions> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.options(), in.for_field(&org::sem::NamedProperty::ExportLatexClassOptions::options));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::write(::orgproto::NamedProperty::ExportLatexHeader* out, org::sem::NamedProperty::ExportLatexHeader const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_header(), in.header);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::read(::orgproto::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexHeader> in) {
  proto_serde<std::string, hstd::Str>::read(out.header(), in.for_field(&org::sem::NamedProperty::ExportLatexHeader::header));
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::write(::orgproto::NamedProperty::ExportLatexCompiler* out, org::sem::NamedProperty::ExportLatexCompiler const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_compiler(), in.compiler);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::read(::orgproto::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexCompiler> in) {
  proto_serde<std::string, hstd::Str>::read(out.compiler(), in.for_field(&org::sem::NamedProperty::ExportLatexCompiler::compiler));
}

void org::algo::proto_serde<::orgproto::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::write(::orgproto::NamedProperty::Ordered* out, org::sem::NamedProperty::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void org::algo::proto_serde<::orgproto::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::read(::orgproto::NamedProperty::Ordered const& out, proto_write_accessor<org::sem::NamedProperty::Ordered> in) {
  in.for_field(&org::sem::NamedProperty::Ordered::isOrdered).get() = out.isordered();
}

void org::algo::proto_serde<::orgproto::NamedProperty::Effort, org::sem::NamedProperty::Effort>::write(::orgproto::NamedProperty::Effort* out, org::sem::NamedProperty::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void org::algo::proto_serde<::orgproto::NamedProperty::Effort, org::sem::NamedProperty::Effort>::read(::orgproto::NamedProperty::Effort const& out, proto_write_accessor<org::sem::NamedProperty::Effort> in) {
  in.for_field(&org::sem::NamedProperty::Effort::hours).get() = out.hours();
  in.for_field(&org::sem::NamedProperty::Effort::minutes).get() = out.minutes();
}

void org::algo::proto_serde<::orgproto::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::write(::orgproto::NamedProperty::Visibility* out, org::sem::NamedProperty::Visibility const& in) {
  out->set_level(static_cast<orgproto::NamedProperty_Visibility_Level>(in.level));
}

void org::algo::proto_serde<::orgproto::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::read(::orgproto::NamedProperty::Visibility const& out, proto_write_accessor<org::sem::NamedProperty::Visibility> in) {
  in.for_field(&org::sem::NamedProperty::Visibility::level).get() = static_cast<org::sem::NamedProperty::Visibility::Level>(out.level());
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::write(::orgproto::NamedProperty::ExportOptions* out, org::sem::NamedProperty::ExportOptions const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, hstd::UnorderedMap<hstd::Str, hstd::Str>>::write(out->mutable_values(), in.values);
}

void org::algo::proto_serde<::orgproto::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::read(::orgproto::NamedProperty::ExportOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportOptions> in) {
  proto_serde<std::string, hstd::Str>::read(out.backend(), in.for_field(&org::sem::NamedProperty::ExportOptions::backend));
  proto_serde<::google::protobuf::Map<std::string, std::string>, hstd::UnorderedMap<hstd::Str, hstd::Str>>::read(out.values(), in.for_field(&org::sem::NamedProperty::ExportOptions::values));
}

void org::algo::proto_serde<::orgproto::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::write(::orgproto::NamedProperty::Blocker* out, org::sem::NamedProperty::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_blockers(), in.blockers);
}

void org::algo::proto_serde<::orgproto::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::read(::orgproto::NamedProperty::Blocker const& out, proto_write_accessor<org::sem::NamedProperty::Blocker> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.blockers(), in.for_field(&org::sem::NamedProperty::Blocker::blockers));
}

void org::algo::proto_serde<::orgproto::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::write(::orgproto::NamedProperty::Unnumbered* out, org::sem::NamedProperty::Unnumbered const& in) {

}

void org::algo::proto_serde<::orgproto::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::read(::orgproto::NamedProperty::Unnumbered const& out, proto_write_accessor<org::sem::NamedProperty::Unnumbered> in) {

}

void org::algo::proto_serde<::orgproto::NamedProperty::Created, org::sem::NamedProperty::Created>::write(::orgproto::NamedProperty::Created* out, org::sem::NamedProperty::Created const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void org::algo::proto_serde<::orgproto::NamedProperty::Created, org::sem::NamedProperty::Created>::read(::orgproto::NamedProperty::Created const& out, proto_write_accessor<org::sem::NamedProperty::Created> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::NamedProperty::Created::time));
}

void org::algo::proto_serde<::orgproto::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::write(::orgproto::NamedProperty::RadioId* out, org::sem::NamedProperty::RadioId const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_words(), in.words);
}

void org::algo::proto_serde<::orgproto::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::read(::orgproto::NamedProperty::RadioId const& out, proto_write_accessor<org::sem::NamedProperty::RadioId> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.words(), in.for_field(&org::sem::NamedProperty::RadioId::words));
}

void org::algo::proto_serde<::orgproto::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::write(::orgproto::NamedProperty::HashtagDef* out, org::sem::NamedProperty::HashtagDef const& in) {
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::write(out->mutable_hashtag(), in.hashtag);
}

void org::algo::proto_serde<::orgproto::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::read(::orgproto::NamedProperty::HashtagDef const& out, proto_write_accessor<org::sem::NamedProperty::HashtagDef> in) {
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::read(out.hashtag(), in.for_field(&org::sem::NamedProperty::HashtagDef::hashtag));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::write(::orgproto::NamedProperty::CustomArgs* out, org::sem::NamedProperty::CustomArgs const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  if (in.sub) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_sub(), *in.sub);
  }
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::read(::orgproto::NamedProperty::CustomArgs const& out, proto_write_accessor<org::sem::NamedProperty::CustomArgs> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomArgs::name));
  if (out.has_sub()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.sub(), in.for_field(&org::sem::NamedProperty::CustomArgs::sub));
  }
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::NamedProperty::CustomArgs::attrs));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::write(::orgproto::NamedProperty::CustomRaw* out, org::sem::NamedProperty::CustomRaw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::read(::orgproto::NamedProperty::CustomRaw const& out, proto_write_accessor<org::sem::NamedProperty::CustomRaw> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomRaw::name));
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomRaw::value));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomId, org::sem::NamedProperty::CustomId>::write(::orgproto::NamedProperty::CustomId* out, org::sem::NamedProperty::CustomId const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomId, org::sem::NamedProperty::CustomId>::read(::orgproto::NamedProperty::CustomId const& out, proto_write_accessor<org::sem::NamedProperty::CustomId> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomId::value));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::write(::orgproto::NamedProperty::CustomSubtreeJson* out, org::sem::NamedProperty::CustomSubtreeJson const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::OrgJson, org::sem::OrgJson>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::read(::orgproto::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeJson> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomSubtreeJson::name));
  proto_serde<orgproto::OrgJson, org::sem::OrgJson>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomSubtreeJson::value));
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::write(::orgproto::NamedProperty::CustomSubtreeFlags* out, org::sem::NamedProperty::CustomSubtreeFlags const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::read(::orgproto::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeFlags> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomSubtreeFlags::name));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomSubtreeFlags::value));
}

void org::algo::proto_serde<::orgproto::NamedProperty, org::sem::NamedProperty>::write(::orgproto::NamedProperty* out, org::sem::NamedProperty const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::write(out->mutable_data()->mutable_archivetime(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::write(out->mutable_data()->mutable_archivefile(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::write(out->mutable_data()->mutable_archiveolpath(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::write(out->mutable_data()->mutable_archivetarget(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::write(out->mutable_data()->mutable_archivecategory(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::write(out->mutable_data()->mutable_archivetodo(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::write(out->mutable_data()->mutable_cookiedata(), std::get<9>(in.data));
      break;
    case 10:
      proto_serde<orgproto::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<10>(in.data));
      break;
    case 11:
      proto_serde<orgproto::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<11>(in.data));
      break;
    case 12:
      proto_serde<orgproto::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<12>(in.data));
      break;
    case 13:
      proto_serde<orgproto::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<13>(in.data));
      break;
    case 14:
      proto_serde<orgproto::NamedProperty::Effort, org::sem::NamedProperty::Effort>::write(out->mutable_data()->mutable_effort(), std::get<14>(in.data));
      break;
    case 15:
      proto_serde<orgproto::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<15>(in.data));
      break;
    case 16:
      proto_serde<orgproto::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<16>(in.data));
      break;
    case 17:
      proto_serde<orgproto::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<17>(in.data));
      break;
    case 18:
      proto_serde<orgproto::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<18>(in.data));
      break;
    case 19:
      proto_serde<orgproto::NamedProperty::Created, org::sem::NamedProperty::Created>::write(out->mutable_data()->mutable_created(), std::get<19>(in.data));
      break;
    case 20:
      proto_serde<orgproto::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::write(out->mutable_data()->mutable_radioid(), std::get<20>(in.data));
      break;
    case 21:
      proto_serde<orgproto::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::write(out->mutable_data()->mutable_hashtagdef(), std::get<21>(in.data));
      break;
    case 22:
      proto_serde<orgproto::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::write(out->mutable_data()->mutable_customargs(), std::get<22>(in.data));
      break;
    case 23:
      proto_serde<orgproto::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::write(out->mutable_data()->mutable_customraw(), std::get<23>(in.data));
      break;
    case 24:
      proto_serde<orgproto::NamedProperty::CustomId, org::sem::NamedProperty::CustomId>::write(out->mutable_data()->mutable_customid(), std::get<24>(in.data));
      break;
    case 25:
      proto_serde<orgproto::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::write(out->mutable_data()->mutable_customsubtreejson(), std::get<25>(in.data));
      break;
    case 26:
      proto_serde<orgproto::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::write(out->mutable_data()->mutable_customsubtreeflags(), std::get<26>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::NamedProperty, org::sem::NamedProperty>::read(::orgproto::NamedProperty const& out, proto_write_accessor<org::sem::NamedProperty> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::NamedProperty::Data::kNonblocking:
      in.for_field_variant<0>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::read(out.data().nonblocking(), in.for_field_variant<0>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetime:
      in.for_field_variant<1>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::read(out.data().archivetime(), in.for_field_variant<1>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivefile:
      in.for_field_variant<2>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::read(out.data().archivefile(), in.for_field_variant<2>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchiveolpath:
      in.for_field_variant<3>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::read(out.data().archiveolpath(), in.for_field_variant<3>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetarget:
      in.for_field_variant<4>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::read(out.data().archivetarget(), in.for_field_variant<4>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivecategory:
      in.for_field_variant<5>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::read(out.data().archivecategory(), in.for_field_variant<5>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetodo:
      in.for_field_variant<6>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::read(out.data().archivetodo(), in.for_field_variant<6>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kTrigger:
      in.for_field_variant<7>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::read(out.data().trigger(), in.for_field_variant<7>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexclass:
      in.for_field_variant<8>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::read(out.data().exportlatexclass(), in.for_field_variant<8>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCookiedata:
      in.for_field_variant<9>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::read(out.data().cookiedata(), in.for_field_variant<9>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexclassoptions:
      in.for_field_variant<10>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::read(out.data().exportlatexclassoptions(), in.for_field_variant<10>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexheader:
      in.for_field_variant<11>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::read(out.data().exportlatexheader(), in.for_field_variant<11>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexcompiler:
      in.for_field_variant<12>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::read(out.data().exportlatexcompiler(), in.for_field_variant<12>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kOrdered:
      in.for_field_variant<13>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::read(out.data().ordered(), in.for_field_variant<13>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kEffort:
      in.for_field_variant<14>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Effort, org::sem::NamedProperty::Effort>::read(out.data().effort(), in.for_field_variant<14>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kVisibility:
      in.for_field_variant<15>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::read(out.data().visibility(), in.for_field_variant<15>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportoptions:
      in.for_field_variant<16>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::read(out.data().exportoptions(), in.for_field_variant<16>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kBlocker:
      in.for_field_variant<17>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::read(out.data().blocker(), in.for_field_variant<17>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kUnnumbered:
      in.for_field_variant<18>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::read(out.data().unnumbered(), in.for_field_variant<18>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCreated:
      in.for_field_variant<19>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::Created, org::sem::NamedProperty::Created>::read(out.data().created(), in.for_field_variant<19>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kRadioid:
      in.for_field_variant<20>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::read(out.data().radioid(), in.for_field_variant<20>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kHashtagdef:
      in.for_field_variant<21>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::read(out.data().hashtagdef(), in.for_field_variant<21>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomargs:
      in.for_field_variant<22>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::read(out.data().customargs(), in.for_field_variant<22>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomraw:
      in.for_field_variant<23>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::read(out.data().customraw(), in.for_field_variant<23>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomid:
      in.for_field_variant<24>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CustomId, org::sem::NamedProperty::CustomId>::read(out.data().customid(), in.for_field_variant<24>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomsubtreejson:
      in.for_field_variant<25>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::read(out.data().customsubtreejson(), in.for_field_variant<25>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomsubtreeflags:
      in.for_field_variant<26>(&org::sem::NamedProperty::data).get();
      proto_serde<orgproto::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::read(out.data().customsubtreeflags(), in.for_field_variant<26>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseTokenError>::write(::orgproto::OrgDiagnostics::ParseTokenError* out, org::sem::OrgDiagnostics::ParseTokenError const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_brief(), in.brief);
  proto_serde<std::string, hstd::Str>::write(out->mutable_detail(), in.detail);
  proto_serde<std::string, hstd::Str>::write(out->mutable_parserfunction(), in.parserFunction);
  out->set_parserline(in.parserLine);
  out->set_tokenkind(static_cast<orgproto::OrgTokenKind>(in.tokenKind));
  proto_serde<std::string, hstd::Str>::write(out->mutable_tokentext(), in.tokenText);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errname(), in.errName);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errcode(), in.errCode);
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseTokenError>::read(::orgproto::OrgDiagnostics::ParseTokenError const& out, proto_write_accessor<org::sem::OrgDiagnostics::ParseTokenError> in) {
  proto_serde<std::string, hstd::Str>::read(out.brief(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::brief));
  proto_serde<std::string, hstd::Str>::read(out.detail(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::detail));
  proto_serde<std::string, hstd::Str>::read(out.parserfunction(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::parserFunction));
  in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::parserLine).get() = out.parserline();
  in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::tokenKind).get() = static_cast<OrgTokenKind>(out.tokenkind());
  proto_serde<std::string, hstd::Str>::read(out.tokentext(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::tokenText));
  proto_serde<std::string, hstd::Str>::read(out.errname(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::errName));
  proto_serde<std::string, hstd::Str>::read(out.errcode(), in.for_field(&org::sem::OrgDiagnostics::ParseTokenError::errCode));
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::ParseError>::write(::orgproto::OrgDiagnostics::ParseError* out, org::sem::OrgDiagnostics::ParseError const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_brief(), in.brief);
  proto_serde<std::string, hstd::Str>::write(out->mutable_detail(), in.detail);
  proto_serde<std::string, hstd::Str>::write(out->mutable_parserfunction(), in.parserFunction);
  out->set_parserline(in.parserLine);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errname(), in.errName);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errcode(), in.errCode);
  if (in.loc) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::ParseError>::read(::orgproto::OrgDiagnostics::ParseError const& out, proto_write_accessor<org::sem::OrgDiagnostics::ParseError> in) {
  proto_serde<std::string, hstd::Str>::read(out.brief(), in.for_field(&org::sem::OrgDiagnostics::ParseError::brief));
  proto_serde<std::string, hstd::Str>::read(out.detail(), in.for_field(&org::sem::OrgDiagnostics::ParseError::detail));
  proto_serde<std::string, hstd::Str>::read(out.parserfunction(), in.for_field(&org::sem::OrgDiagnostics::ParseError::parserFunction));
  in.for_field(&org::sem::OrgDiagnostics::ParseError::parserLine).get() = out.parserline();
  proto_serde<std::string, hstd::Str>::read(out.errname(), in.for_field(&org::sem::OrgDiagnostics::ParseError::errName));
  proto_serde<std::string, hstd::Str>::read(out.errcode(), in.for_field(&org::sem::OrgDiagnostics::ParseError::errCode));
  if (out.has_loc()) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::IncludeError>::write(::orgproto::OrgDiagnostics::IncludeError* out, org::sem::OrgDiagnostics::IncludeError const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_brief(), in.brief);
  proto_serde<std::string, hstd::Str>::write(out->mutable_targetpath(), in.targetPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_workingfile(), in.workingFile);
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::IncludeError>::read(::orgproto::OrgDiagnostics::IncludeError const& out, proto_write_accessor<org::sem::OrgDiagnostics::IncludeError> in) {
  proto_serde<std::string, hstd::Str>::read(out.brief(), in.for_field(&org::sem::OrgDiagnostics::IncludeError::brief));
  proto_serde<std::string, hstd::Str>::read(out.targetpath(), in.for_field(&org::sem::OrgDiagnostics::IncludeError::targetPath));
  proto_serde<std::string, hstd::Str>::read(out.workingfile(), in.for_field(&org::sem::OrgDiagnostics::IncludeError::workingFile));
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::ConvertError>::write(::orgproto::OrgDiagnostics::ConvertError* out, org::sem::OrgDiagnostics::ConvertError const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_brief(), in.brief);
  proto_serde<std::string, hstd::Str>::write(out->mutable_detail(), in.detail);
  proto_serde<std::string, hstd::Str>::write(out->mutable_convertfunction(), in.convertFunction);
  out->set_convertline(in.convertLine);
  proto_serde<std::string, hstd::Str>::write(out->mutable_convertfile(), in.convertFile);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errname(), in.errName);
  proto_serde<std::string, hstd::Str>::write(out->mutable_errcode(), in.errCode);
  if (in.loc) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::ConvertError>::read(::orgproto::OrgDiagnostics::ConvertError const& out, proto_write_accessor<org::sem::OrgDiagnostics::ConvertError> in) {
  proto_serde<std::string, hstd::Str>::read(out.brief(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::brief));
  proto_serde<std::string, hstd::Str>::read(out.detail(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::detail));
  proto_serde<std::string, hstd::Str>::read(out.convertfunction(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::convertFunction));
  in.for_field(&org::sem::OrgDiagnostics::ConvertError::convertLine).get() = out.convertline();
  proto_serde<std::string, hstd::Str>::read(out.convertfile(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::convertFile));
  proto_serde<std::string, hstd::Str>::read(out.errname(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::errName));
  proto_serde<std::string, hstd::Str>::read(out.errcode(), in.for_field(&org::sem::OrgDiagnostics::ConvertError::errCode));
  if (out.has_loc()) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::InternalError, org::sem::OrgDiagnostics::InternalError>::write(::orgproto::OrgDiagnostics::InternalError* out, org::sem::OrgDiagnostics::InternalError const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_message(), in.message);
  proto_serde<std::string, hstd::Str>::write(out->mutable_function(), in.function);
  out->set_line(in.line);
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
  if (in.loc) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics::InternalError, org::sem::OrgDiagnostics::InternalError>::read(::orgproto::OrgDiagnostics::InternalError const& out, proto_write_accessor<org::sem::OrgDiagnostics::InternalError> in) {
  proto_serde<std::string, hstd::Str>::read(out.message(), in.for_field(&org::sem::OrgDiagnostics::InternalError::message));
  proto_serde<std::string, hstd::Str>::read(out.function(), in.for_field(&org::sem::OrgDiagnostics::InternalError::function));
  in.for_field(&org::sem::OrgDiagnostics::InternalError::line).get() = out.line();
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::OrgDiagnostics::InternalError::file));
  if (out.has_loc()) {
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics, org::sem::OrgDiagnostics>::write(::orgproto::OrgDiagnostics* out, org::sem::OrgDiagnostics const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseTokenError>::write(out->mutable_data()->mutable_parsetokenerror(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::ParseError>::write(out->mutable_data()->mutable_parseerror(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::IncludeError>::write(out->mutable_data()->mutable_includeerror(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::ConvertError>::write(out->mutable_data()->mutable_converterror(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::OrgDiagnostics::InternalError, org::sem::OrgDiagnostics::InternalError>::write(out->mutable_data()->mutable_internalerror(), std::get<4>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::OrgDiagnostics, org::sem::OrgDiagnostics>::read(::orgproto::OrgDiagnostics const& out, proto_write_accessor<org::sem::OrgDiagnostics> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::OrgDiagnostics::Data::kParsetokenerror:
      in.for_field_variant<0>(&org::sem::OrgDiagnostics::data).get();
      proto_serde<orgproto::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseTokenError>::read(out.data().parsetokenerror(), in.for_field_variant<0>(&org::sem::OrgDiagnostics::data));
      break;
    case ::orgproto::OrgDiagnostics::Data::kParseerror:
      in.for_field_variant<1>(&org::sem::OrgDiagnostics::data).get();
      proto_serde<orgproto::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::ParseError>::read(out.data().parseerror(), in.for_field_variant<1>(&org::sem::OrgDiagnostics::data));
      break;
    case ::orgproto::OrgDiagnostics::Data::kIncludeerror:
      in.for_field_variant<2>(&org::sem::OrgDiagnostics::data).get();
      proto_serde<orgproto::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::IncludeError>::read(out.data().includeerror(), in.for_field_variant<2>(&org::sem::OrgDiagnostics::data));
      break;
    case ::orgproto::OrgDiagnostics::Data::kConverterror:
      in.for_field_variant<3>(&org::sem::OrgDiagnostics::data).get();
      proto_serde<orgproto::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::ConvertError>::read(out.data().converterror(), in.for_field_variant<3>(&org::sem::OrgDiagnostics::data));
      break;
    case ::orgproto::OrgDiagnostics::Data::kInternalerror:
      in.for_field_variant<4>(&org::sem::OrgDiagnostics::data).get();
      proto_serde<orgproto::OrgDiagnostics::InternalError, org::sem::OrgDiagnostics::InternalError>::read(out.data().internalerror(), in.for_field_variant<4>(&org::sem::OrgDiagnostics::data));
      break;
    case ::orgproto::OrgDiagnostics::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::NoNode, org::sem::NoNode>::write(::orgproto::NoNode* out, org::sem::NoNode const& in) {
  org::algo::proto_serde<::orgproto::NoNode, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::NoNode, org::sem::NoNode>::read(::orgproto::NoNode const& out, proto_write_accessor<org::sem::NoNode> in) {
  org::algo::proto_serde<::orgproto::NoNode, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::ErrorItem, org::sem::ErrorItem>::write(::orgproto::ErrorItem* out, org::sem::ErrorItem const& in) {
  org::algo::proto_serde<::orgproto::ErrorItem, org::sem::Org>::write(out, in);
  proto_serde<orgproto::OrgDiagnostics, org::sem::OrgDiagnostics>::write(out->mutable_diag(), in.diag);
}

void org::algo::proto_serde<::orgproto::ErrorItem, org::sem::ErrorItem>::read(::orgproto::ErrorItem const& out, proto_write_accessor<org::sem::ErrorItem> in) {
  org::algo::proto_serde<::orgproto::ErrorItem, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::OrgDiagnostics, org::sem::OrgDiagnostics>::read(out.diag(), in.for_field(&org::sem::ErrorItem::diag));
}

void org::algo::proto_serde<::orgproto::ErrorGroup, org::sem::ErrorGroup>::write(::orgproto::ErrorGroup* out, org::sem::ErrorGroup const& in) {
  org::algo::proto_serde<::orgproto::ErrorGroup, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::write(out->mutable_diagnostics(), in.diagnostics);
}

void org::algo::proto_serde<::orgproto::ErrorGroup, org::sem::ErrorGroup>::read(::orgproto::ErrorGroup const& out, proto_write_accessor<org::sem::ErrorGroup> in) {
  org::algo::proto_serde<::orgproto::ErrorGroup, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::read(out.diagnostics(), in.for_field(&org::sem::ErrorGroup::diagnostics));
}

void org::algo::proto_serde<::orgproto::StmtList, org::sem::StmtList>::write(::orgproto::StmtList* out, org::sem::StmtList const& in) {
  org::algo::proto_serde<::orgproto::StmtList, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::StmtList, org::sem::StmtList>::read(::orgproto::StmtList const& out, proto_write_accessor<org::sem::StmtList> in) {
  org::algo::proto_serde<::orgproto::StmtList, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Empty, org::sem::Empty>::write(::orgproto::Empty* out, org::sem::Empty const& in) {
  org::algo::proto_serde<::orgproto::Empty, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Empty, org::sem::Empty>::read(::orgproto::Empty const& out, proto_write_accessor<org::sem::Empty> in) {
  org::algo::proto_serde<::orgproto::Empty, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::CmdCaption, org::sem::CmdCaption>::write(::orgproto::CmdCaption* out, org::sem::CmdCaption const& in) {
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void org::algo::proto_serde<::orgproto::CmdCaption, org::sem::CmdCaption>::read(::orgproto::CmdCaption const& out, proto_write_accessor<org::sem::CmdCaption> in) {
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCaption, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdCaption::text));
}

void org::algo::proto_serde<::orgproto::CmdCreator, org::sem::CmdCreator>::write(::orgproto::CmdCreator* out, org::sem::CmdCreator const& in) {
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void org::algo::proto_serde<::orgproto::CmdCreator, org::sem::CmdCreator>::read(::orgproto::CmdCreator const& out, proto_write_accessor<org::sem::CmdCreator> in) {
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCreator, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdCreator::text));
}

void org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::CmdAuthor>::write(::orgproto::CmdAuthor* out, org::sem::CmdAuthor const& in) {
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::CmdAuthor>::read(::orgproto::CmdAuthor const& out, proto_write_accessor<org::sem::CmdAuthor> in) {
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdAuthor, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdAuthor::text));
}

void org::algo::proto_serde<::orgproto::CmdEmail, org::sem::CmdEmail>::write(::orgproto::CmdEmail* out, org::sem::CmdEmail const& in) {
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::CmdEmail, org::sem::CmdEmail>::read(::orgproto::CmdEmail const& out, proto_write_accessor<org::sem::CmdEmail> in) {
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdEmail, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::CmdEmail::text));
}

void org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::CmdLanguage>::write(::orgproto::CmdLanguage* out, org::sem::CmdLanguage const& in) {
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::CmdLanguage>::read(::orgproto::CmdLanguage const& out, proto_write_accessor<org::sem::CmdLanguage> in) {
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdLanguage, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::CmdLanguage::text));
}

void org::algo::proto_serde<::orgproto::CmdColumns, org::sem::CmdColumns>::write(::orgproto::CmdColumns* out, org::sem::CmdColumns const& in) {
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Org>::write(out, in);
  proto_serde<orgproto::ColumnView, org::sem::ColumnView>::write(out->mutable_view(), in.view);
}

void org::algo::proto_serde<::orgproto::CmdColumns, org::sem::CmdColumns>::read(::orgproto::CmdColumns const& out, proto_write_accessor<org::sem::CmdColumns> in) {
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdColumns, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::ColumnView, org::sem::ColumnView>::read(out.view(), in.for_field(&org::sem::CmdColumns::view));
}

void org::algo::proto_serde<::orgproto::CmdName, org::sem::CmdName>::write(::orgproto::CmdName* out, org::sem::CmdName const& in) {
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::CmdName, org::sem::CmdName>::read(::orgproto::CmdName const& out, proto_write_accessor<org::sem::CmdName> in) {
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdName, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdName::name));
}

void org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::CmdCustomArgs>::write(::orgproto::CmdCustomArgs* out, org::sem::CmdCustomArgs const& in) {
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
}

void org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::CmdCustomArgs>::read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<org::sem::CmdCustomArgs> in) {
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomArgs::name));
  in.for_field(&org::sem::CmdCustomArgs::isAttached).get() = out.isattached();
}

void org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::CmdCustomRaw>::write(::orgproto::CmdCustomRaw* out, org::sem::CmdCustomRaw const& in) {
  org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::CmdCustomRaw>::read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<org::sem::CmdCustomRaw> in) {
  org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomRaw::name));
  in.for_field(&org::sem::CmdCustomRaw::isAttached).get() = out.isattached();
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::CmdCustomRaw::text));
}

void org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::CmdCustomText>::write(::orgproto::CmdCustomText* out, org::sem::CmdCustomText const& in) {
  org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::CmdCustomText>::read(::orgproto::CmdCustomText const& out, proto_write_accessor<org::sem::CmdCustomText> in) {
  org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomText::name));
  in.for_field(&org::sem::CmdCustomText::isAttached).get() = out.isattached();
  proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdCustomText::text));
}

void org::algo::proto_serde<::orgproto::CmdCall, org::sem::CmdCall>::write(::orgproto::CmdCall* out, org::sem::CmdCall const& in) {
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  if (in.fileName) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_filename(), *in.fileName);
  }
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_insideheaderattrs(), in.insideHeaderAttrs);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_callattrs(), in.callAttrs);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_endheaderattrs(), in.endHeaderAttrs);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeEvalResult>, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::write(out->mutable_result(), in.result);
}

void org::algo::proto_serde<::orgproto::CmdCall, org::sem::CmdCall>::read(::orgproto::CmdCall const& out, proto_write_accessor<org::sem::CmdCall> in) {
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdCall, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCall::name));
  if (out.has_filename()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.filename(), in.for_field(&org::sem::CmdCall::fileName));
  }
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.insideheaderattrs(), in.for_field(&org::sem::CmdCall::insideHeaderAttrs));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.callattrs(), in.for_field(&org::sem::CmdCall::callAttrs));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.endheaderattrs(), in.for_field(&org::sem::CmdCall::endHeaderAttrs));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeEvalResult>, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::read(out.result(), in.for_field(&org::sem::CmdCall::result));
}

void org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::CmdTblfm>::write(::orgproto::CmdTblfm* out, org::sem::CmdTblfm const& in) {
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Org>::write(out, in);
  proto_serde<orgproto::Tblfm, org::sem::Tblfm>::write(out->mutable_expr(), in.expr);
}

void org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::CmdTblfm>::read(::orgproto::CmdTblfm const& out, proto_write_accessor<org::sem::CmdTblfm> in) {
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Tblfm, org::sem::Tblfm>::read(out.expr(), in.for_field(&org::sem::CmdTblfm::expr));
}

void org::algo::proto_serde<::orgproto::HashTag, org::sem::HashTag>::write(::orgproto::HashTag* out, org::sem::HashTag const& in) {
  org::algo::proto_serde<::orgproto::HashTag, org::sem::Org>::write(out, in);
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::write(out->mutable_text(), in.text);
}

void org::algo::proto_serde<::orgproto::HashTag, org::sem::HashTag>::read(::orgproto::HashTag const& out, proto_write_accessor<org::sem::HashTag> in) {
  org::algo::proto_serde<::orgproto::HashTag, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::HashTagText, org::sem::HashTagText>::read(out.text(), in.for_field(&org::sem::HashTag::text));
}

void org::algo::proto_serde<::orgproto::InlineFootnote, org::sem::InlineFootnote>::write(::orgproto::InlineFootnote* out, org::sem::InlineFootnote const& in) {
  org::algo::proto_serde<::orgproto::InlineFootnote, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(out->mutable_definition(), *in.definition);
  }
}

void org::algo::proto_serde<::orgproto::InlineFootnote, org::sem::InlineFootnote>::read(::orgproto::InlineFootnote const& out, proto_write_accessor<org::sem::InlineFootnote> in) {
  org::algo::proto_serde<::orgproto::InlineFootnote, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.tag(), in.for_field(&org::sem::InlineFootnote::tag));
  if (out.has_definition()) {
    proto_serde<hstd::Opt<orgproto::AnyNode>, hstd::Opt<org::sem::SemId<org::sem::Org>>>::read(out.definition(), in.for_field(&org::sem::InlineFootnote::definition));
  }
}

void org::algo::proto_serde<::orgproto::InlineExport, org::sem::InlineExport>::write(::orgproto::InlineExport* out, org::sem::InlineExport const& in) {
  org::algo::proto_serde<::orgproto::InlineExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void org::algo::proto_serde<::orgproto::InlineExport, org::sem::InlineExport>::read(::orgproto::InlineExport const& out, proto_write_accessor<org::sem::InlineExport> in) {
  org::algo::proto_serde<::orgproto::InlineExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::InlineExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::InlineExport::content));
}

void org::algo::proto_serde<::orgproto::Time::Repeat, org::sem::Time::Repeat>::write(::orgproto::Time::Repeat* out, org::sem::Time::Repeat const& in) {
  out->set_mode(static_cast<orgproto::Time_Repeat_Mode>(in.mode));
  out->set_period(static_cast<orgproto::Time_Repeat_Period>(in.period));
  out->set_count(in.count);
}

void org::algo::proto_serde<::orgproto::Time::Repeat, org::sem::Time::Repeat>::read(::orgproto::Time::Repeat const& out, proto_write_accessor<org::sem::Time::Repeat> in) {
  in.for_field(&org::sem::Time::Repeat::mode).get() = static_cast<org::sem::Time::Repeat::Mode>(out.mode());
  in.for_field(&org::sem::Time::Repeat::period).get() = static_cast<org::sem::Time::Repeat::Period>(out.period());
  in.for_field(&org::sem::Time::Repeat::count).get() = out.count();
}

void org::algo::proto_serde<::orgproto::Time::Static, org::sem::Time::Static>::write(::orgproto::Time::Static* out, org::sem::Time::Static const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Time::Repeat>, hstd::Vec<org::sem::Time::Repeat>>::write(out->mutable_repeat(), in.repeat);
  if (in.warn) {
    proto_serde<orgproto::Time::Repeat, org::sem::Time::Repeat>::write(out->mutable_warn(), *in.warn);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void org::algo::proto_serde<::orgproto::Time::Static, org::sem::Time::Static>::read(::orgproto::Time::Static const& out, proto_write_accessor<org::sem::Time::Static> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Time::Repeat>, hstd::Vec<org::sem::Time::Repeat>>::read(out.repeat(), in.for_field(&org::sem::Time::Static::repeat));
  if (out.has_warn()) {
    proto_serde<hstd::Opt<orgproto::Time::Repeat>, hstd::Opt<org::sem::Time::Repeat>>::read(out.warn(), in.for_field(&org::sem::Time::Static::warn));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::Time::Static::time));
}

void org::algo::proto_serde<::orgproto::Time::Dynamic, org::sem::Time::Dynamic>::write(::orgproto::Time::Dynamic* out, org::sem::Time::Dynamic const& in) {
  proto_serde<orgproto::LispCode, org::sem::LispCode>::write(out->mutable_expr(), in.expr);
}

void org::algo::proto_serde<::orgproto::Time::Dynamic, org::sem::Time::Dynamic>::read(::orgproto::Time::Dynamic const& out, proto_write_accessor<org::sem::Time::Dynamic> in) {
  proto_serde<orgproto::LispCode, org::sem::LispCode>::read(out.expr(), in.for_field(&org::sem::Time::Dynamic::expr));
}

void org::algo::proto_serde<::orgproto::Time, org::sem::Time>::write(::orgproto::Time* out, org::sem::Time const& in) {
  org::algo::proto_serde<::orgproto::Time, org::sem::Org>::write(out, in);
  out->set_isactive(in.isActive);
  switch (in.time.index()) {
    case 0:
      proto_serde<orgproto::Time::Static, org::sem::Time::Static>::write(out->mutable_time()->mutable_static_(), std::get<0>(in.time));
      break;
    case 1:
      proto_serde<orgproto::Time::Dynamic, org::sem::Time::Dynamic>::write(out->mutable_time()->mutable_dynamic(), std::get<1>(in.time));
      break;
  }
}

void org::algo::proto_serde<::orgproto::Time, org::sem::Time>::read(::orgproto::Time const& out, proto_write_accessor<org::sem::Time> in) {
  org::algo::proto_serde<::orgproto::Time, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Time::isActive).get() = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::Time::TimeVariant::kStatic:
      in.for_field_variant<0>(&org::sem::Time::time).get();
      proto_serde<orgproto::Time::Static, org::sem::Time::Static>::read(out.time().static_(), in.for_field_variant<0>(&org::sem::Time::time));
      break;
    case ::orgproto::Time::TimeVariant::kDynamic:
      in.for_field_variant<1>(&org::sem::Time::time).get();
      proto_serde<orgproto::Time::Dynamic, org::sem::Time::Dynamic>::read(out.time().dynamic(), in.for_field_variant<1>(&org::sem::Time::time));
      break;
    case ::orgproto::Time::TimeVariant::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::TimeRange, org::sem::TimeRange>::write(::orgproto::TimeRange* out, org::sem::TimeRange const& in) {
  org::algo::proto_serde<::orgproto::TimeRange, org::sem::Org>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (!in.to.isNil()) {
    proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_to(), in.to);
  }
}

void org::algo::proto_serde<::orgproto::TimeRange, org::sem::TimeRange>::read(::orgproto::TimeRange const& out, proto_write_accessor<org::sem::TimeRange> in) {
  org::algo::proto_serde<::orgproto::TimeRange, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::read(out.from(), in.for_field(&org::sem::TimeRange::from));
  proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::read(out.to(), in.for_field(&org::sem::TimeRange::to));
}

void org::algo::proto_serde<::orgproto::Macro, org::sem::Macro>::write(::orgproto::Macro* out, org::sem::Macro const& in) {
  org::algo::proto_serde<::orgproto::Macro, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void org::algo::proto_serde<::orgproto::Macro, org::sem::Macro>::read(::orgproto::Macro const& out, proto_write_accessor<org::sem::Macro> in) {
  org::algo::proto_serde<::orgproto::Macro, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Macro::name));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Macro::attrs));
}

void org::algo::proto_serde<::orgproto::Symbol::Param, org::sem::Symbol::Param>::write(::orgproto::Symbol::Param* out, org::sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void org::algo::proto_serde<::orgproto::Symbol::Param, org::sem::Symbol::Param>::read(::orgproto::Symbol::Param const& out, proto_write_accessor<org::sem::Symbol::Param> in) {
  if (out.has_key()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.key(), in.for_field(&org::sem::Symbol::Param::key));
  }
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::Symbol::Param::value));
}

void org::algo::proto_serde<::orgproto::Symbol, org::sem::Symbol>::write(::orgproto::Symbol* out, org::sem::Symbol const& in) {
  org::algo::proto_serde<::orgproto::Symbol, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, hstd::Vec<org::sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, hstd::Vec<org::sem::SemId<org::sem::Org>>>::write(out->mutable_positional(), in.positional);
}

void org::algo::proto_serde<::orgproto::Symbol, org::sem::Symbol>::read(::orgproto::Symbol const& out, proto_write_accessor<org::sem::Symbol> in) {
  org::algo::proto_serde<::orgproto::Symbol, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Symbol::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, hstd::Vec<org::sem::Symbol::Param>>::read(out.parameters(), in.for_field(&org::sem::Symbol::parameters));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, hstd::Vec<org::sem::SemId<org::sem::Org>>>::read(out.positional(), in.for_field(&org::sem::Symbol::positional));
}

void org::algo::proto_serde<::orgproto::Escaped, org::sem::Escaped>::write(::orgproto::Escaped* out, org::sem::Escaped const& in) {
  org::algo::proto_serde<::orgproto::Escaped, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Escaped, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Escaped, org::sem::Escaped>::read(::orgproto::Escaped const& out, proto_write_accessor<org::sem::Escaped> in) {
  org::algo::proto_serde<::orgproto::Escaped, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Escaped, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Newline, org::sem::Newline>::write(::orgproto::Newline* out, org::sem::Newline const& in) {
  org::algo::proto_serde<::orgproto::Newline, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Newline, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Newline, org::sem::Newline>::read(::orgproto::Newline const& out, proto_write_accessor<org::sem::Newline> in) {
  org::algo::proto_serde<::orgproto::Newline, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Newline, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Space, org::sem::Space>::write(::orgproto::Space* out, org::sem::Space const& in) {
  org::algo::proto_serde<::orgproto::Space, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Space, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Space, org::sem::Space>::read(::orgproto::Space const& out, proto_write_accessor<org::sem::Space> in) {
  org::algo::proto_serde<::orgproto::Space, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Space, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Word, org::sem::Word>::write(::orgproto::Word* out, org::sem::Word const& in) {
  org::algo::proto_serde<::orgproto::Word, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Word, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Word, org::sem::Word>::read(::orgproto::Word const& out, proto_write_accessor<org::sem::Word> in) {
  org::algo::proto_serde<::orgproto::Word, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Word, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::AtMention, org::sem::AtMention>::write(::orgproto::AtMention* out, org::sem::AtMention const& in) {
  org::algo::proto_serde<::orgproto::AtMention, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::AtMention, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::AtMention, org::sem::AtMention>::read(::orgproto::AtMention const& out, proto_write_accessor<org::sem::AtMention> in) {
  org::algo::proto_serde<::orgproto::AtMention, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::AtMention, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::RawText, org::sem::RawText>::write(::orgproto::RawText* out, org::sem::RawText const& in) {
  org::algo::proto_serde<::orgproto::RawText, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::RawText, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::RawText, org::sem::RawText>::read(::orgproto::RawText const& out, proto_write_accessor<org::sem::RawText> in) {
  org::algo::proto_serde<::orgproto::RawText, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::RawText, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Punctuation, org::sem::Punctuation>::write(::orgproto::Punctuation* out, org::sem::Punctuation const& in) {
  org::algo::proto_serde<::orgproto::Punctuation, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Punctuation, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Punctuation, org::sem::Punctuation>::read(::orgproto::Punctuation const& out, proto_write_accessor<org::sem::Punctuation> in) {
  org::algo::proto_serde<::orgproto::Punctuation, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Punctuation, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Placeholder, org::sem::Placeholder>::write(::orgproto::Placeholder* out, org::sem::Placeholder const& in) {
  org::algo::proto_serde<::orgproto::Placeholder, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::Placeholder, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Placeholder, org::sem::Placeholder>::read(::orgproto::Placeholder const& out, proto_write_accessor<org::sem::Placeholder> in) {
  org::algo::proto_serde<::orgproto::Placeholder, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::Placeholder, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BigIdent, org::sem::BigIdent>::write(::orgproto::BigIdent* out, org::sem::BigIdent const& in) {
  org::algo::proto_serde<::orgproto::BigIdent, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::BigIdent, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BigIdent, org::sem::BigIdent>::read(::orgproto::BigIdent const& out, proto_write_accessor<org::sem::BigIdent> in) {
  org::algo::proto_serde<::orgproto::BigIdent, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::BigIdent, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::TextTarget, org::sem::TextTarget>::write(::orgproto::TextTarget* out, org::sem::TextTarget const& in) {
  org::algo::proto_serde<::orgproto::TextTarget, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::TextTarget, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::TextTarget, org::sem::TextTarget>::read(::orgproto::TextTarget const& out, proto_write_accessor<org::sem::TextTarget> in) {
  org::algo::proto_serde<::orgproto::TextTarget, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::TextTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::ErrorSkipToken>::write(::orgproto::ErrorSkipToken* out, org::sem::ErrorSkipToken const& in) {
  org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::Leaf>::write(out, in);
  org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::ErrorSkipToken>::read(::orgproto::ErrorSkipToken const& out, proto_write_accessor<org::sem::ErrorSkipToken> in) {
  org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  org::algo::proto_serde<::orgproto::ErrorSkipToken, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::ErrorSkipGroup, org::sem::ErrorSkipGroup>::write(::orgproto::ErrorSkipGroup* out, org::sem::ErrorSkipGroup const& in) {
  org::algo::proto_serde<::orgproto::ErrorSkipGroup, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorSkipToken>, hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>::write(out->mutable_skipped(), in.skipped);
}

void org::algo::proto_serde<::orgproto::ErrorSkipGroup, org::sem::ErrorSkipGroup>::read(::orgproto::ErrorSkipGroup const& out, proto_write_accessor<org::sem::ErrorSkipGroup> in) {
  org::algo::proto_serde<::orgproto::ErrorSkipGroup, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorSkipToken>, hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>::read(out.skipped(), in.for_field(&org::sem::ErrorSkipGroup::skipped));
}

void org::algo::proto_serde<::orgproto::Bold, org::sem::Bold>::write(::orgproto::Bold* out, org::sem::Bold const& in) {
  org::algo::proto_serde<::orgproto::Bold, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Bold, org::sem::Bold>::read(::orgproto::Bold const& out, proto_write_accessor<org::sem::Bold> in) {
  org::algo::proto_serde<::orgproto::Bold, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Underline, org::sem::Underline>::write(::orgproto::Underline* out, org::sem::Underline const& in) {
  org::algo::proto_serde<::orgproto::Underline, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Underline, org::sem::Underline>::read(::orgproto::Underline const& out, proto_write_accessor<org::sem::Underline> in) {
  org::algo::proto_serde<::orgproto::Underline, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Monospace, org::sem::Monospace>::write(::orgproto::Monospace* out, org::sem::Monospace const& in) {
  org::algo::proto_serde<::orgproto::Monospace, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Monospace, org::sem::Monospace>::read(::orgproto::Monospace const& out, proto_write_accessor<org::sem::Monospace> in) {
  org::algo::proto_serde<::orgproto::Monospace, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::MarkQuote, org::sem::MarkQuote>::write(::orgproto::MarkQuote* out, org::sem::MarkQuote const& in) {
  org::algo::proto_serde<::orgproto::MarkQuote, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::MarkQuote, org::sem::MarkQuote>::read(::orgproto::MarkQuote const& out, proto_write_accessor<org::sem::MarkQuote> in) {
  org::algo::proto_serde<::orgproto::MarkQuote, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Verbatim, org::sem::Verbatim>::write(::orgproto::Verbatim* out, org::sem::Verbatim const& in) {
  org::algo::proto_serde<::orgproto::Verbatim, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Verbatim, org::sem::Verbatim>::read(::orgproto::Verbatim const& out, proto_write_accessor<org::sem::Verbatim> in) {
  org::algo::proto_serde<::orgproto::Verbatim, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Italic, org::sem::Italic>::write(::orgproto::Italic* out, org::sem::Italic const& in) {
  org::algo::proto_serde<::orgproto::Italic, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Italic, org::sem::Italic>::read(::orgproto::Italic const& out, proto_write_accessor<org::sem::Italic> in) {
  org::algo::proto_serde<::orgproto::Italic, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Strike, org::sem::Strike>::write(::orgproto::Strike* out, org::sem::Strike const& in) {
  org::algo::proto_serde<::orgproto::Strike, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Strike, org::sem::Strike>::read(::orgproto::Strike const& out, proto_write_accessor<org::sem::Strike> in) {
  org::algo::proto_serde<::orgproto::Strike, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Par, org::sem::Par>::write(::orgproto::Par* out, org::sem::Par const& in) {
  org::algo::proto_serde<::orgproto::Par, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Par, org::sem::Par>::read(::orgproto::Par const& out, proto_write_accessor<org::sem::Par> in) {
  org::algo::proto_serde<::orgproto::Par, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::RadioTarget, org::sem::RadioTarget>::write(::orgproto::RadioTarget* out, org::sem::RadioTarget const& in) {
  org::algo::proto_serde<::orgproto::RadioTarget, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_words(), in.words);
}

void org::algo::proto_serde<::orgproto::RadioTarget, org::sem::RadioTarget>::read(::orgproto::RadioTarget const& out, proto_write_accessor<org::sem::RadioTarget> in) {
  org::algo::proto_serde<::orgproto::RadioTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.words(), in.for_field(&org::sem::RadioTarget::words));
}

void org::algo::proto_serde<::orgproto::Latex, org::sem::Latex>::write(::orgproto::Latex* out, org::sem::Latex const& in) {
  org::algo::proto_serde<::orgproto::Latex, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Latex, org::sem::Latex>::read(::orgproto::Latex const& out, proto_write_accessor<org::sem::Latex> in) {
  org::algo::proto_serde<::orgproto::Latex, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::Link, org::sem::Link>::write(::orgproto::Link* out, org::sem::Link const& in) {
  org::algo::proto_serde<::orgproto::Link, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::Link, org::sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<orgproto::LinkTarget, org::sem::LinkTarget>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::Link, org::sem::Link>::read(::orgproto::Link const& out, proto_write_accessor<org::sem::Link> in) {
  org::algo::proto_serde<::orgproto::Link, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::Link, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Link::description));
  }
  proto_serde<orgproto::LinkTarget, org::sem::LinkTarget>::read(out.target(), in.for_field(&org::sem::Link::target));
}

void org::algo::proto_serde<::orgproto::BlockCenter, org::sem::BlockCenter>::write(::orgproto::BlockCenter* out, org::sem::BlockCenter const& in) {
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockCenter, org::sem::BlockCenter>::read(::orgproto::BlockCenter const& out, proto_write_accessor<org::sem::BlockCenter> in) {
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockCenter, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockQuote, org::sem::BlockQuote>::write(::orgproto::BlockQuote* out, org::sem::BlockQuote const& in) {
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockQuote, org::sem::BlockQuote>::read(::orgproto::BlockQuote const& out, proto_write_accessor<org::sem::BlockQuote> in) {
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockQuote, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockComment, org::sem::BlockComment>::write(::orgproto::BlockComment* out, org::sem::BlockComment const& in) {
  org::algo::proto_serde<::orgproto::BlockComment, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockComment, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockComment, org::sem::BlockComment>::read(::orgproto::BlockComment const& out, proto_write_accessor<org::sem::BlockComment> in) {
  org::algo::proto_serde<::orgproto::BlockComment, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockComment, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockVerse, org::sem::BlockVerse>::write(::orgproto::BlockVerse* out, org::sem::BlockVerse const& in) {
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockVerse, org::sem::BlockVerse>::read(::orgproto::BlockVerse const& out, proto_write_accessor<org::sem::BlockVerse> in) {
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockVerse, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::BlockDynamicFallback>::write(::orgproto::BlockDynamicFallback* out, org::sem::BlockDynamicFallback const& in) {
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::BlockDynamicFallback>::read(::orgproto::BlockDynamicFallback const& out, proto_write_accessor<org::sem::BlockDynamicFallback> in) {
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::BlockDynamicFallback::name));
}

void org::algo::proto_serde<::orgproto::BlockExample, org::sem::BlockExample>::write(::orgproto::BlockExample* out, org::sem::BlockExample const& in) {
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockExample, org::sem::BlockExample>::read(::orgproto::BlockExample const& out, proto_write_accessor<org::sem::BlockExample> in) {
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockExample, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockExport, org::sem::BlockExport>::write(::orgproto::BlockExport* out, org::sem::BlockExport const& in) {
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void org::algo::proto_serde<::orgproto::BlockExport, org::sem::BlockExport>::read(::orgproto::BlockExport const& out, proto_write_accessor<org::sem::BlockExport> in) {
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::BlockExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::BlockExport::content));
}

void org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::BlockAdmonition>::write(::orgproto::BlockAdmonition* out, org::sem::BlockAdmonition const& in) {
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::BlockAdmonition>::read(::orgproto::BlockAdmonition const& out, proto_write_accessor<org::sem::BlockAdmonition> in) {
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::BlockCodeEvalResult>::write(::orgproto::BlockCodeEvalResult* out, org::sem::BlockCodeEvalResult const& in) {
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::OrgCodeEvalOutput>, hstd::Vec<org::sem::OrgCodeEvalOutput>>::write(out->mutable_raw(), in.raw);
  if (!in.node.isNil()) {
    proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(out->mutable_node(), in.node);
  }
}

void org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::BlockCodeEvalResult>::read(::orgproto::BlockCodeEvalResult const& out, proto_write_accessor<org::sem::BlockCodeEvalResult> in) {
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::OrgCodeEvalOutput>, hstd::Vec<org::sem::OrgCodeEvalOutput>>::read(out.raw(), in.for_field(&org::sem::BlockCodeEvalResult::raw));
  proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::read(out.node(), in.for_field(&org::sem::BlockCodeEvalResult::node));
}

void org::algo::proto_serde<::orgproto::BlockCode, org::sem::BlockCode>::write(::orgproto::BlockCode* out, org::sem::BlockCode const& in) {
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeEvalResult>, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::write(out->mutable_result(), in.result);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine>, hstd::Vec<org::sem::BlockCodeLine>>::write(out->mutable_lines(), in.lines);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_switches(), in.switches);
}

void org::algo::proto_serde<::orgproto::BlockCode, org::sem::BlockCode>::read(::orgproto::BlockCode const& out, proto_write_accessor<org::sem::BlockCode> in) {
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::BlockCode, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_lang()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.lang(), in.for_field(&org::sem::BlockCode::lang));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeEvalResult>, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>::read(out.result(), in.for_field(&org::sem::BlockCode::result));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine>, hstd::Vec<org::sem::BlockCodeLine>>::read(out.lines(), in.for_field(&org::sem::BlockCode::lines));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.switches(), in.for_field(&org::sem::BlockCode::switches));
}

void org::algo::proto_serde<::orgproto::SubtreeLog, org::sem::SubtreeLog>::write(::orgproto::SubtreeLog* out, org::sem::SubtreeLog const& in) {
  org::algo::proto_serde<::orgproto::SubtreeLog, org::sem::Org>::write(out, in);
  proto_serde<orgproto::SubtreeLogHead, org::sem::SubtreeLogHead>::write(out->mutable_head(), in.head);
  if (in.desc) {
    proto_serde<orgproto::StmtList, org::sem::SemId<org::sem::StmtList>>::write(out->mutable_desc(), *in.desc);
  }
}

void org::algo::proto_serde<::orgproto::SubtreeLog, org::sem::SubtreeLog>::read(::orgproto::SubtreeLog const& out, proto_write_accessor<org::sem::SubtreeLog> in) {
  org::algo::proto_serde<::orgproto::SubtreeLog, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::SubtreeLogHead, org::sem::SubtreeLogHead>::read(out.head(), in.for_field(&org::sem::SubtreeLog::head));
  if (out.has_desc()) {
    proto_serde<hstd::Opt<orgproto::StmtList>, hstd::Opt<org::sem::SemId<org::sem::StmtList>>>::read(out.desc(), in.for_field(&org::sem::SubtreeLog::desc));
  }
}

void org::algo::proto_serde<::orgproto::Subtree, org::sem::Subtree>::write(::orgproto::Subtree* out, org::sem::Subtree const& in) {
  org::algo::proto_serde<::orgproto::Subtree, org::sem::Org>::write(out, in);
  out->set_level(in.level);
  if (in.treeId) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_treeid(), *in.treeId);
  }
  if (in.todo) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_todo(), *in.todo);
  }
  if (in.completion) {
    proto_serde<orgproto::SubtreeCompletion, org::sem::SubtreeCompletion>::write(out->mutable_completion(), *in.completion);
  }
  if (in.description) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::write(out->mutable_tags(), in.tags);
  if (!in.title.isNil()) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_title(), in.title);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::write(out->mutable_logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  if (in.closed) {
    proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_closed(), *in.closed);
  }
  if (in.deadline) {
    proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_deadline(), *in.deadline);
  }
  if (in.scheduled) {
    proto_serde<orgproto::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_scheduled(), *in.scheduled);
  }
  out->set_iscomment(in.isComment);
  out->set_isarchived(in.isArchived);
  if (in.priority) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_priority(), *in.priority);
  }
}

void org::algo::proto_serde<::orgproto::Subtree, org::sem::Subtree>::read(::orgproto::Subtree const& out, proto_write_accessor<org::sem::Subtree> in) {
  org::algo::proto_serde<::orgproto::Subtree, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Subtree::level).get() = out.level();
  if (out.has_treeid()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.treeid(), in.for_field(&org::sem::Subtree::treeId));
  }
  if (out.has_todo()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.todo(), in.for_field(&org::sem::Subtree::todo));
  }
  if (out.has_completion()) {
    proto_serde<hstd::Opt<orgproto::SubtreeCompletion>, hstd::Opt<org::sem::SubtreeCompletion>>::read(out.completion(), in.for_field(&org::sem::Subtree::completion));
  }
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Subtree::description));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::read(out.tags(), in.for_field(&org::sem::Subtree::tags));
  proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.title(), in.for_field(&org::sem::Subtree::title));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::read(out.logbook(), in.for_field(&org::sem::Subtree::logbook));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::Subtree::properties));
  if (out.has_closed()) {
    proto_serde<hstd::Opt<orgproto::Time>, hstd::Opt<org::sem::SemId<org::sem::Time>>>::read(out.closed(), in.for_field(&org::sem::Subtree::closed));
  }
  if (out.has_deadline()) {
    proto_serde<hstd::Opt<orgproto::Time>, hstd::Opt<org::sem::SemId<org::sem::Time>>>::read(out.deadline(), in.for_field(&org::sem::Subtree::deadline));
  }
  if (out.has_scheduled()) {
    proto_serde<hstd::Opt<orgproto::Time>, hstd::Opt<org::sem::SemId<org::sem::Time>>>::read(out.scheduled(), in.for_field(&org::sem::Subtree::scheduled));
  }
  in.for_field(&org::sem::Subtree::isComment).get() = out.iscomment();
  in.for_field(&org::sem::Subtree::isArchived).get() = out.isarchived();
  if (out.has_priority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.priority(), in.for_field(&org::sem::Subtree::priority));
  }
}

void org::algo::proto_serde<::orgproto::Cell, org::sem::Cell>::write(::orgproto::Cell* out, org::sem::Cell const& in) {
  org::algo::proto_serde<::orgproto::Cell, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::Cell, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::Cell, org::sem::Org>::write(out, in);
  out->set_isblock(in.isBlock);
}

void org::algo::proto_serde<::orgproto::Cell, org::sem::Cell>::read(::orgproto::Cell const& out, proto_write_accessor<org::sem::Cell> in) {
  org::algo::proto_serde<::orgproto::Cell, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::Cell, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::Cell, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Cell::isBlock).get() = out.isblock();
}

void org::algo::proto_serde<::orgproto::Row, org::sem::Row>::write(::orgproto::Row* out, org::sem::Row const& in) {
  org::algo::proto_serde<::orgproto::Row, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::Row, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::Row, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, hstd::Vec<org::sem::SemId<org::sem::Cell>>>::write(out->mutable_cells(), in.cells);
  out->set_isblock(in.isBlock);
}

void org::algo::proto_serde<::orgproto::Row, org::sem::Row>::read(::orgproto::Row const& out, proto_write_accessor<org::sem::Row> in) {
  org::algo::proto_serde<::orgproto::Row, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::Row, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::Row, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, hstd::Vec<org::sem::SemId<org::sem::Cell>>>::read(out.cells(), in.for_field(&org::sem::Row::cells));
  in.for_field(&org::sem::Row::isBlock).get() = out.isblock();
}

void org::algo::proto_serde<::orgproto::Table, org::sem::Table>::write(::orgproto::Table* out, org::sem::Table const& in) {
  org::algo::proto_serde<::orgproto::Table, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::Table, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::Table, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, hstd::Vec<org::sem::SemId<org::sem::Row>>>::write(out->mutable_rows(), in.rows);
  out->set_isblock(in.isBlock);
}

void org::algo::proto_serde<::orgproto::Table, org::sem::Table>::read(::orgproto::Table const& out, proto_write_accessor<org::sem::Table> in) {
  org::algo::proto_serde<::orgproto::Table, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::Table, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::Table, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, hstd::Vec<org::sem::SemId<org::sem::Row>>>::read(out.rows(), in.for_field(&org::sem::Table::rows));
  in.for_field(&org::sem::Table::isBlock).get() = out.isblock();
}

void org::algo::proto_serde<::orgproto::Paragraph, org::sem::Paragraph>::write(::orgproto::Paragraph* out, org::sem::Paragraph const& in) {
  org::algo::proto_serde<::orgproto::Paragraph, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::Paragraph, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::Paragraph, org::sem::Paragraph>::read(::orgproto::Paragraph const& out, proto_write_accessor<org::sem::Paragraph> in) {
  org::algo::proto_serde<::orgproto::Paragraph, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::Paragraph, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::ColonExample, org::sem::ColonExample>::write(::orgproto::ColonExample* out, org::sem::ColonExample const& in) {
  org::algo::proto_serde<::orgproto::ColonExample, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::ColonExample, org::sem::ColonExample>::read(::orgproto::ColonExample const& out, proto_write_accessor<org::sem::ColonExample> in) {
  org::algo::proto_serde<::orgproto::ColonExample, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::CmdAttr, org::sem::CmdAttr>::write(::orgproto::CmdAttr* out, org::sem::CmdAttr const& in) {
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void org::algo::proto_serde<::orgproto::CmdAttr, org::sem::CmdAttr>::read(::orgproto::CmdAttr const& out, proto_write_accessor<org::sem::CmdAttr> in) {
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdAttr, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::CmdAttr::target));
}

void org::algo::proto_serde<::orgproto::CmdExport, org::sem::CmdExport>::write(::orgproto::CmdExport* out, org::sem::CmdExport const& in) {
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Cmd>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void org::algo::proto_serde<::orgproto::CmdExport, org::sem::CmdExport>::read(::orgproto::CmdExport const& out, proto_write_accessor<org::sem::CmdExport> in) {
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::CmdExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::CmdExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::CmdExport::content));
}

void org::algo::proto_serde<::orgproto::Call, org::sem::Call>::write(::orgproto::Call* out, org::sem::Call const& in) {
  org::algo::proto_serde<::orgproto::Call, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
  out->set_iscommand(in.isCommand);
}

void org::algo::proto_serde<::orgproto::Call, org::sem::Call>::read(::orgproto::Call const& out, proto_write_accessor<org::sem::Call> in) {
  org::algo::proto_serde<::orgproto::Call, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Call::name));
  proto_serde<orgproto::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Call::attrs));
  in.for_field(&org::sem::Call::isCommand).get() = out.iscommand();
}

void org::algo::proto_serde<::orgproto::List, org::sem::List>::write(::orgproto::List* out, org::sem::List const& in) {
  org::algo::proto_serde<::orgproto::List, org::sem::Stmt>::write(out, in);
  org::algo::proto_serde<::orgproto::List, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::List, org::sem::List>::read(::orgproto::List const& out, proto_write_accessor<org::sem::List> in) {
  org::algo::proto_serde<::orgproto::List, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  org::algo::proto_serde<::orgproto::List, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::ListItem, org::sem::ListItem>::write(::orgproto::ListItem* out, org::sem::ListItem const& in) {
  org::algo::proto_serde<::orgproto::ListItem, org::sem::Org>::write(out, in);
  out->set_checkbox(static_cast<orgproto::CheckboxState>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
  if (in.bullet) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_bullet(), *in.bullet);
  }
}

void org::algo::proto_serde<::orgproto::ListItem, org::sem::ListItem>::read(::orgproto::ListItem const& out, proto_write_accessor<org::sem::ListItem> in) {
  org::algo::proto_serde<::orgproto::ListItem, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::ListItem::checkbox).get() = static_cast<CheckboxState>(out.checkbox());
  if (out.has_header()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.header(), in.for_field(&org::sem::ListItem::header));
  }
  if (out.has_bullet()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.bullet(), in.for_field(&org::sem::ListItem::bullet));
  }
}

void org::algo::proto_serde<::orgproto::DocumentOptions, org::sem::DocumentOptions>::write(::orgproto::DocumentOptions* out, org::sem::DocumentOptions const& in) {
  org::algo::proto_serde<::orgproto::DocumentOptions, org::sem::Org>::write(out, in);
  out->set_initialvisibility(static_cast<orgproto::InitialSubtreeVisibility>(in.initialVisibility));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  proto_serde<orgproto::DocumentExportConfig, org::sem::DocumentExportConfig>::write(out->mutable_exportconfig(), in.exportConfig);
  if (in.fixedWidthSections) {
    out->set_fixedwidthsections(*in.fixedWidthSections);
  }
  if (in.startupIndented) {
    out->set_startupindented(*in.startupIndented);
  }
  if (in.category) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_category(), *in.category);
  }
  if (in.setupfile) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_setupfile(), *in.setupfile);
  }
  if (in.maxSubtreeLevelExport) {
    out->set_maxsubtreelevelexport(*in.maxSubtreeLevelExport);
  }
  if (in.columns) {
    proto_serde<orgproto::ColumnView, org::sem::ColumnView>::write(out->mutable_columns(), *in.columns);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::TodoKeyword>, hstd::Vec<org::sem::TodoKeyword>>::write(out->mutable_todokeywords(), in.todoKeywords);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::TodoKeyword>, hstd::Vec<org::sem::TodoKeyword>>::write(out->mutable_donekeywords(), in.doneKeywords);
}

void org::algo::proto_serde<::orgproto::DocumentOptions, org::sem::DocumentOptions>::read(::orgproto::DocumentOptions const& out, proto_write_accessor<org::sem::DocumentOptions> in) {
  org::algo::proto_serde<::orgproto::DocumentOptions, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::DocumentOptions::initialVisibility).get() = static_cast<InitialSubtreeVisibility>(out.initialvisibility());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::DocumentOptions::properties));
  proto_serde<orgproto::DocumentExportConfig, org::sem::DocumentExportConfig>::read(out.exportconfig(), in.for_field(&org::sem::DocumentOptions::exportConfig));
  if (out.has_fixedwidthsections()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.fixedwidthsections(), in.for_field(&org::sem::DocumentOptions::fixedWidthSections));
  }
  if (out.has_startupindented()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.startupindented(), in.for_field(&org::sem::DocumentOptions::startupIndented));
  }
  if (out.has_category()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.category(), in.for_field(&org::sem::DocumentOptions::category));
  }
  if (out.has_setupfile()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.setupfile(), in.for_field(&org::sem::DocumentOptions::setupfile));
  }
  if (out.has_maxsubtreelevelexport()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.maxsubtreelevelexport(), in.for_field(&org::sem::DocumentOptions::maxSubtreeLevelExport));
  }
  if (out.has_columns()) {
    proto_serde<hstd::Opt<orgproto::ColumnView>, hstd::Opt<org::sem::ColumnView>>::read(out.columns(), in.for_field(&org::sem::DocumentOptions::columns));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::TodoKeyword>, hstd::Vec<org::sem::TodoKeyword>>::read(out.todokeywords(), in.for_field(&org::sem::DocumentOptions::todoKeywords));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::TodoKeyword>, hstd::Vec<org::sem::TodoKeyword>>::read(out.donekeywords(), in.for_field(&org::sem::DocumentOptions::doneKeywords));
}

void org::algo::proto_serde<::orgproto::DocumentFragment, org::sem::DocumentFragment>::write(::orgproto::DocumentFragment* out, org::sem::DocumentFragment const& in) {
  org::algo::proto_serde<::orgproto::DocumentFragment, org::sem::Org>::write(out, in);
  out->set_baseline(in.baseLine);
  out->set_basecol(in.baseCol);
}

void org::algo::proto_serde<::orgproto::DocumentFragment, org::sem::DocumentFragment>::read(::orgproto::DocumentFragment const& out, proto_write_accessor<org::sem::DocumentFragment> in) {
  org::algo::proto_serde<::orgproto::DocumentFragment, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::DocumentFragment::baseLine).get() = out.baseline();
  in.for_field(&org::sem::DocumentFragment::baseCol).get() = out.basecol();
}

void org::algo::proto_serde<::orgproto::CriticMarkup, org::sem::CriticMarkup>::write(::orgproto::CriticMarkup* out, org::sem::CriticMarkup const& in) {
  org::algo::proto_serde<::orgproto::CriticMarkup, org::sem::Org>::write(out, in);
  out->set_kind(static_cast<orgproto::CriticMarkup_Kind>(in.kind));
}

void org::algo::proto_serde<::orgproto::CriticMarkup, org::sem::CriticMarkup>::read(::orgproto::CriticMarkup const& out, proto_write_accessor<org::sem::CriticMarkup> in) {
  org::algo::proto_serde<::orgproto::CriticMarkup, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::CriticMarkup::kind).get() = static_cast<org::sem::CriticMarkup::Kind>(out.kind());
}

void org::algo::proto_serde<::orgproto::Document, org::sem::Document>::write(::orgproto::Document* out, org::sem::Document const& in) {
  org::algo::proto_serde<::orgproto::Document, org::sem::Org>::write(out, in);
  if (in.title) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_title(), *in.title);
  }
  if (in.author) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_author(), *in.author);
  }
  if (in.creator) {
    proto_serde<orgproto::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_creator(), *in.creator);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::write(out->mutable_filetags(), in.filetags);
  if (in.email) {
    proto_serde<orgproto::RawText, org::sem::SemId<org::sem::RawText>>::write(out->mutable_email(), *in.email);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_language(), in.language);
  if (!in.options.isNil()) {
    proto_serde<orgproto::DocumentOptions, org::sem::SemId<org::sem::DocumentOptions>>::write(out->mutable_options(), in.options);
  }
  if (in.exportFileName) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_exportfilename(), *in.exportFileName);
  }
}

void org::algo::proto_serde<::orgproto::Document, org::sem::Document>::read(::orgproto::Document const& out, proto_write_accessor<org::sem::Document> in) {
  org::algo::proto_serde<::orgproto::Document, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_title()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.title(), in.for_field(&org::sem::Document::title));
  }
  if (out.has_author()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.author(), in.for_field(&org::sem::Document::author));
  }
  if (out.has_creator()) {
    proto_serde<hstd::Opt<orgproto::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.creator(), in.for_field(&org::sem::Document::creator));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::read(out.filetags(), in.for_field(&org::sem::Document::filetags));
  if (out.has_email()) {
    proto_serde<hstd::Opt<orgproto::RawText>, hstd::Opt<org::sem::SemId<org::sem::RawText>>>::read(out.email(), in.for_field(&org::sem::Document::email));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.language(), in.for_field(&org::sem::Document::language));
  proto_serde<orgproto::DocumentOptions, org::sem::SemId<org::sem::DocumentOptions>>::read(out.options(), in.for_field(&org::sem::Document::options));
  if (out.has_exportfilename()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.exportfilename(), in.for_field(&org::sem::Document::exportFileName));
  }
}

void org::algo::proto_serde<::orgproto::FileTarget, org::sem::FileTarget>::write(::orgproto::FileTarget* out, org::sem::FileTarget const& in) {
  org::algo::proto_serde<::orgproto::FileTarget, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_path(), in.path);
  if (in.line) {
    out->set_line(*in.line);
  }
  if (in.searchTarget) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_searchtarget(), *in.searchTarget);
  }
  out->set_restricttoheadlines(in.restrictToHeadlines);
  if (in.targetId) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_targetid(), *in.targetId);
  }
  if (in.regexp) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_regexp(), *in.regexp);
  }
}

void org::algo::proto_serde<::orgproto::FileTarget, org::sem::FileTarget>::read(::orgproto::FileTarget const& out, proto_write_accessor<org::sem::FileTarget> in) {
  org::algo::proto_serde<::orgproto::FileTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.path(), in.for_field(&org::sem::FileTarget::path));
  if (out.has_line()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.line(), in.for_field(&org::sem::FileTarget::line));
  }
  if (out.has_searchtarget()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.searchtarget(), in.for_field(&org::sem::FileTarget::searchTarget));
  }
  in.for_field(&org::sem::FileTarget::restrictToHeadlines).get() = out.restricttoheadlines();
  if (out.has_targetid()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.targetid(), in.for_field(&org::sem::FileTarget::targetId));
  }
  if (out.has_regexp()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.regexp(), in.for_field(&org::sem::FileTarget::regexp));
  }
}

void org::algo::proto_serde<::orgproto::TextSeparator, org::sem::TextSeparator>::write(::orgproto::TextSeparator* out, org::sem::TextSeparator const& in) {
  org::algo::proto_serde<::orgproto::TextSeparator, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::TextSeparator, org::sem::TextSeparator>::read(::orgproto::TextSeparator const& out, proto_write_accessor<org::sem::TextSeparator> in) {
  org::algo::proto_serde<::orgproto::TextSeparator, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::DocumentGroup, org::sem::DocumentGroup>::write(::orgproto::DocumentGroup* out, org::sem::DocumentGroup const& in) {
  org::algo::proto_serde<::orgproto::DocumentGroup, org::sem::Org>::write(out, in);
}

void org::algo::proto_serde<::orgproto::DocumentGroup, org::sem::DocumentGroup>::read(::orgproto::DocumentGroup const& out, proto_write_accessor<org::sem::DocumentGroup> in) {
  org::algo::proto_serde<::orgproto::DocumentGroup, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void org::algo::proto_serde<::orgproto::File::Document, org::sem::File::Document>::write(::orgproto::File::Document* out, org::sem::File::Document const& in) {

}

void org::algo::proto_serde<::orgproto::File::Document, org::sem::File::Document>::read(::orgproto::File::Document const& out, proto_write_accessor<org::sem::File::Document> in) {

}

void org::algo::proto_serde<::orgproto::File::Attachment, org::sem::File::Attachment>::write(::orgproto::File::Attachment* out, org::sem::File::Attachment const& in) {

}

void org::algo::proto_serde<::orgproto::File::Attachment, org::sem::File::Attachment>::read(::orgproto::File::Attachment const& out, proto_write_accessor<org::sem::File::Attachment> in) {

}

void org::algo::proto_serde<::orgproto::File::Source, org::sem::File::Source>::write(::orgproto::File::Source* out, org::sem::File::Source const& in) {

}

void org::algo::proto_serde<::orgproto::File::Source, org::sem::File::Source>::read(::orgproto::File::Source const& out, proto_write_accessor<org::sem::File::Source> in) {

}

void org::algo::proto_serde<::orgproto::File, org::sem::File>::write(::orgproto::File* out, org::sem::File const& in) {
  org::algo::proto_serde<::orgproto::File, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_relpath(), in.relPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::File::Document, org::sem::File::Document>::write(out->mutable_data()->mutable_document(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::File::Attachment, org::sem::File::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::File::Source, org::sem::File::Source>::write(out->mutable_data()->mutable_source(), std::get<2>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::File, org::sem::File>::read(::orgproto::File const& out, proto_write_accessor<org::sem::File> in) {
  org::algo::proto_serde<::orgproto::File, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.relpath(), in.for_field(&org::sem::File::relPath));
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::File::absPath));
  switch (out.data().kind_case()) {
    case ::orgproto::File::Data::kDocument:
      in.for_field_variant<0>(&org::sem::File::data).get();
      proto_serde<orgproto::File::Document, org::sem::File::Document>::read(out.data().document(), in.for_field_variant<0>(&org::sem::File::data));
      break;
    case ::orgproto::File::Data::kAttachment:
      in.for_field_variant<1>(&org::sem::File::data).get();
      proto_serde<orgproto::File::Attachment, org::sem::File::Attachment>::read(out.data().attachment(), in.for_field_variant<1>(&org::sem::File::data));
      break;
    case ::orgproto::File::Data::kSource:
      in.for_field_variant<2>(&org::sem::File::data).get();
      proto_serde<orgproto::File::Source, org::sem::File::Source>::read(out.data().source(), in.for_field_variant<2>(&org::sem::File::data));
      break;
    case ::orgproto::File::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

void org::algo::proto_serde<::orgproto::Directory, org::sem::Directory>::write(::orgproto::Directory* out, org::sem::Directory const& in) {
  org::algo::proto_serde<::orgproto::Directory, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_relpath(), in.relPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
}

void org::algo::proto_serde<::orgproto::Directory, org::sem::Directory>::read(::orgproto::Directory const& out, proto_write_accessor<org::sem::Directory> in) {
  org::algo::proto_serde<::orgproto::Directory, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.relpath(), in.for_field(&org::sem::Directory::relPath));
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::Directory::absPath));
}

void org::algo::proto_serde<::orgproto::Symlink, org::sem::Symlink>::write(::orgproto::Symlink* out, org::sem::Symlink const& in) {
  org::algo::proto_serde<::orgproto::Symlink, org::sem::Org>::write(out, in);
  out->set_isdirectory(in.isDirectory);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
}

void org::algo::proto_serde<::orgproto::Symlink, org::sem::Symlink>::read(::orgproto::Symlink const& out, proto_write_accessor<org::sem::Symlink> in) {
  org::algo::proto_serde<::orgproto::Symlink, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Symlink::isDirectory).get() = out.isdirectory();
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::Symlink::absPath));
}

void org::algo::proto_serde<::orgproto::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase>::write(::orgproto::CmdInclude::IncludeBase* out, org::sem::CmdInclude::IncludeBase const& in) {

}

void org::algo::proto_serde<::orgproto::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase>::read(::orgproto::CmdInclude::IncludeBase const& out, proto_write_accessor<org::sem::CmdInclude::IncludeBase> in) {

}

void org::algo::proto_serde<::orgproto::CmdInclude::Example, org::sem::CmdInclude::Example>::write(::orgproto::CmdInclude::Example* out, org::sem::CmdInclude::Example const& in) {

}

void org::algo::proto_serde<::orgproto::CmdInclude::Example, org::sem::CmdInclude::Example>::read(::orgproto::CmdInclude::Example const& out, proto_write_accessor<org::sem::CmdInclude::Example> in) {

}

void org::algo::proto_serde<::orgproto::CmdInclude::Export, org::sem::CmdInclude::Export>::write(::orgproto::CmdInclude::Export* out, org::sem::CmdInclude::Export const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void org::algo::proto_serde<::orgproto::CmdInclude::Export, org::sem::CmdInclude::Export>::read(::orgproto::CmdInclude::Export const& out, proto_write_accessor<org::sem::CmdInclude::Export> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&org::sem::CmdInclude::Export::language));
}

void org::algo::proto_serde<::orgproto::CmdInclude::Custom, org::sem::CmdInclude::Custom>::write(::orgproto::CmdInclude::Custom* out, org::sem::CmdInclude::Custom const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_blockname(), in.blockName);
}

void org::algo::proto_serde<::orgproto::CmdInclude::Custom, org::sem::CmdInclude::Custom>::read(::orgproto::CmdInclude::Custom const& out, proto_write_accessor<org::sem::CmdInclude::Custom> in) {
  proto_serde<std::string, hstd::Str>::read(out.blockname(), in.for_field(&org::sem::CmdInclude::Custom::blockName));
}

void org::algo::proto_serde<::orgproto::CmdInclude::Src, org::sem::CmdInclude::Src>::write(::orgproto::CmdInclude::Src* out, org::sem::CmdInclude::Src const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void org::algo::proto_serde<::orgproto::CmdInclude::Src, org::sem::CmdInclude::Src>::read(::orgproto::CmdInclude::Src const& out, proto_write_accessor<org::sem::CmdInclude::Src> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&org::sem::CmdInclude::Src::language));
}

void org::algo::proto_serde<::orgproto::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::write(::orgproto::CmdInclude::OrgDocument* out, org::sem::CmdInclude::OrgDocument const& in) {
  if (in.onlyContent) {
    out->set_onlycontent(*in.onlyContent);
  }
  if (in.subtreePath) {
    proto_serde<orgproto::SubtreePath, org::sem::SubtreePath>::write(out->mutable_subtreepath(), *in.subtreePath);
  }
  if (in.minLevel) {
    out->set_minlevel(*in.minLevel);
  }
  if (in.customIdTarget) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_customidtarget(), *in.customIdTarget);
  }
}

void org::algo::proto_serde<::orgproto::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::read(::orgproto::CmdInclude::OrgDocument const& out, proto_write_accessor<org::sem::CmdInclude::OrgDocument> in) {
  if (out.has_onlycontent()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.onlycontent(), in.for_field(&org::sem::CmdInclude::OrgDocument::onlyContent));
  }
  if (out.has_subtreepath()) {
    proto_serde<hstd::Opt<orgproto::SubtreePath>, hstd::Opt<org::sem::SubtreePath>>::read(out.subtreepath(), in.for_field(&org::sem::CmdInclude::OrgDocument::subtreePath));
  }
  if (out.has_minlevel()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.minlevel(), in.for_field(&org::sem::CmdInclude::OrgDocument::minLevel));
  }
  if (out.has_customidtarget()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.customidtarget(), in.for_field(&org::sem::CmdInclude::OrgDocument::customIdTarget));
  }
}

void org::algo::proto_serde<::orgproto::CmdInclude, org::sem::CmdInclude>::write(::orgproto::CmdInclude* out, org::sem::CmdInclude const& in) {
  org::algo::proto_serde<::orgproto::CmdInclude, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_path(), in.path);
  if (in.firstLine) {
    out->set_firstline(*in.firstLine);
  }
  if (in.lastLine) {
    out->set_lastline(*in.lastLine);
  }
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::CmdInclude::Example, org::sem::CmdInclude::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::CmdInclude::Export, org::sem::CmdInclude::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::CmdInclude::Custom, org::sem::CmdInclude::Custom>::write(out->mutable_data()->mutable_custom(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::CmdInclude::Src, org::sem::CmdInclude::Src>::write(out->mutable_data()->mutable_src(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<4>(in.data));
      break;
  }
}

void org::algo::proto_serde<::orgproto::CmdInclude, org::sem::CmdInclude>::read(::orgproto::CmdInclude const& out, proto_write_accessor<org::sem::CmdInclude> in) {
  org::algo::proto_serde<::orgproto::CmdInclude, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.path(), in.for_field(&org::sem::CmdInclude::path));
  if (out.has_firstline()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.firstline(), in.for_field(&org::sem::CmdInclude::firstLine));
  }
  if (out.has_lastline()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.lastline(), in.for_field(&org::sem::CmdInclude::lastLine));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::CmdInclude::Data::kExample:
      in.for_field_variant<0>(&org::sem::CmdInclude::data).get();
      proto_serde<orgproto::CmdInclude::Example, org::sem::CmdInclude::Example>::read(out.data().example(), in.for_field_variant<0>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::CmdInclude::Data::kExport:
      in.for_field_variant<1>(&org::sem::CmdInclude::data).get();
      proto_serde<orgproto::CmdInclude::Export, org::sem::CmdInclude::Export>::read(out.data().export_(), in.for_field_variant<1>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::CmdInclude::Data::kCustom:
      in.for_field_variant<2>(&org::sem::CmdInclude::data).get();
      proto_serde<orgproto::CmdInclude::Custom, org::sem::CmdInclude::Custom>::read(out.data().custom(), in.for_field_variant<2>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::CmdInclude::Data::kSrc:
      in.for_field_variant<3>(&org::sem::CmdInclude::data).get();
      proto_serde<orgproto::CmdInclude::Src, org::sem::CmdInclude::Src>::read(out.data().src(), in.for_field_variant<3>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::CmdInclude::Data::kOrgdocument:
      in.for_field_variant<4>(&org::sem::CmdInclude::data).get();
      proto_serde<orgproto::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::read(out.data().orgdocument(), in.for_field_variant<4>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::CmdInclude::Data::KIND_NOT_SET: {
      throw ::hstd::logic_assertion_error::init("Invalid incoming data -- KIND_NOT_SET for parsing variant field");
      break;
    }
  }
}

#endif
/* clang-format on */
