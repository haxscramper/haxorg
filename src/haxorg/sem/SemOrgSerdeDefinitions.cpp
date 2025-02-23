/* clang-format off */
#include <haxorg/sem/SemOrgSerde.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>
void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::write(::orgproto::org::Tblfm::Expr::AxisRef::Position::Index* out, org::sem::Tblfm::Expr::AxisRef::Position::Index const& in) {
  out->set_index(in.index);
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::read(::orgproto::org::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Index> in) {
  in.for_field(&org::sem::Tblfm::Expr::AxisRef::Position::Index::index).get() = out.index();
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::write(::orgproto::org::Tblfm::Expr::AxisRef::Position::Name* out, org::sem::Tblfm::Expr::AxisRef::Position::Name const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::read(::orgproto::org::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Name> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::Position::Name::name));
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(::orgproto::org::Tblfm::Expr::AxisRef::Position* out, org::sem::Tblfm::Expr::AxisRef::Position const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::write(out->mutable_data()->mutable_index(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::write(out->mutable_data()->mutable_name(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::read(::orgproto::org::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::Tblfm::Expr::AxisRef::Position::Data::kIndex:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index>::read(out.data().index(), in.for_field_variant<0>(&org::sem::Tblfm::Expr::AxisRef::Position::data));
      break;
    case ::orgproto::org::Tblfm::Expr::AxisRef::Position::Data::kName:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name>::read(out.data().name(), in.for_field_variant<1>(&org::sem::Tblfm::Expr::AxisRef::Position::data));
      break;
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(::orgproto::org::Tblfm::Expr::AxisRef* out, org::sem::Tblfm::Expr::AxisRef const& in) {
  proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_col(), in.col);
  if (in.row) {
    proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_row(), *in.row);
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(::orgproto::org::Tblfm::Expr::AxisRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef> in) {
  proto_serde<orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position>::read(out.col(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::col));
  if (out.has_row()) {
    proto_serde<hstd::Opt<orgproto::org::Tblfm::Expr::AxisRef::Position>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>>::read(out.row(), in.for_field(&org::sem::Tblfm::Expr::AxisRef::row));
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::write(::orgproto::org::Tblfm::Expr::AxisName* out, org::sem::Tblfm::Expr::AxisName const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::read(::orgproto::org::Tblfm::Expr::AxisName const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisName> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::AxisName::name));
}

void proto_serde<::orgproto::org::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::write(::orgproto::org::Tblfm::Expr::IntLiteral* out, org::sem::Tblfm::Expr::IntLiteral const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::org::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::read(::orgproto::org::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::IntLiteral> in) {
  in.for_field(&org::sem::Tblfm::Expr::IntLiteral::value).get() = out.value();
}

void proto_serde<::orgproto::org::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::write(::orgproto::org::Tblfm::Expr::FloatLiteral* out, org::sem::Tblfm::Expr::FloatLiteral const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::org::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::read(::orgproto::org::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::FloatLiteral> in) {
  in.for_field(&org::sem::Tblfm::Expr::FloatLiteral::value).get() = out.value();
}

void proto_serde<::orgproto::org::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::write(::orgproto::org::Tblfm::Expr::RangeRef* out, org::sem::Tblfm::Expr::RangeRef const& in) {
  if (in.first) {
    proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_first(), *in.first);
  }
  if (in.last) {
    proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_last(), *in.last);
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::read(::orgproto::org::Tblfm::Expr::RangeRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::RangeRef> in) {
  if (out.has_first()) {
    proto_serde<hstd::Opt<orgproto::org::Tblfm::Expr::AxisRef>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::read(out.first(), in.for_field(&org::sem::Tblfm::Expr::RangeRef::first));
  }
  if (out.has_last()) {
    proto_serde<hstd::Opt<orgproto::org::Tblfm::Expr::AxisRef>, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>>::read(out.last(), in.for_field(&org::sem::Tblfm::Expr::RangeRef::last));
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::write(::orgproto::org::Tblfm::Expr::Call* out, org::sem::Tblfm::Expr::Call const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::write(out->mutable_args(), in.args);
}

void proto_serde<::orgproto::org::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::read(::orgproto::org::Tblfm::Expr::Call const& out, proto_write_accessor<org::sem::Tblfm::Expr::Call> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Tblfm::Expr::Call::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::read(out.args(), in.for_field(&org::sem::Tblfm::Expr::Call::args));
}

void proto_serde<::orgproto::org::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::write(::orgproto::org::Tblfm::Expr::Elisp* out, org::sem::Tblfm::Expr::Elisp const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::read(::orgproto::org::Tblfm::Expr::Elisp const& out, proto_write_accessor<org::sem::Tblfm::Expr::Elisp> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::Tblfm::Expr::Elisp::value));
}

void proto_serde<::orgproto::org::Tblfm::Expr, org::sem::Tblfm::Expr>::write(::orgproto::org::Tblfm::Expr* out, org::sem::Tblfm::Expr const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_data()->mutable_axisref(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::write(out->mutable_data()->mutable_axisname(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::write(out->mutable_data()->mutable_intliteral(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::write(out->mutable_data()->mutable_floatliteral(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::org::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::write(out->mutable_data()->mutable_rangeref(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::org::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::write(out->mutable_data()->mutable_call(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::org::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::write(out->mutable_data()->mutable_elisp(), std::get<6>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::Tblfm::Expr, org::sem::Tblfm::Expr>::read(::orgproto::org::Tblfm::Expr const& out, proto_write_accessor<org::sem::Tblfm::Expr> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::Tblfm::Expr::Data::kAxisref:
      proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(out.data().axisref(), in.for_field_variant<0>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kAxisname:
      proto_serde<orgproto::org::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName>::read(out.data().axisname(), in.for_field_variant<1>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kIntliteral:
      proto_serde<orgproto::org::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral>::read(out.data().intliteral(), in.for_field_variant<2>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kFloatliteral:
      proto_serde<orgproto::org::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral>::read(out.data().floatliteral(), in.for_field_variant<3>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kRangeref:
      proto_serde<orgproto::org::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef>::read(out.data().rangeref(), in.for_field_variant<4>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kCall:
      proto_serde<orgproto::org::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call>::read(out.data().call(), in.for_field_variant<5>(&org::sem::Tblfm::Expr::data));
      break;
    case ::orgproto::org::Tblfm::Expr::Data::kElisp:
      proto_serde<orgproto::org::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp>::read(out.data().elisp(), in.for_field_variant<6>(&org::sem::Tblfm::Expr::data));
      break;
  }
}

void proto_serde<::orgproto::org::Tblfm::Assign, org::sem::Tblfm::Assign>::write(::orgproto::org::Tblfm::Assign* out, org::sem::Tblfm::Assign const& in) {
  proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::write(out->mutable_target(), in.target);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::write(out->mutable_expr(), in.expr);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org_Tblfm_Assign_Flag>, hstd::Vec<org::sem::Tblfm::Assign::Flag>>::write(out->mutable_flags(), in.flags);
}

void proto_serde<::orgproto::org::Tblfm::Assign, org::sem::Tblfm::Assign>::read(::orgproto::org::Tblfm::Assign const& out, proto_write_accessor<org::sem::Tblfm::Assign> in) {
  proto_serde<orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef>::read(out.target(), in.for_field(&org::sem::Tblfm::Assign::target));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Expr>, hstd::Vec<org::sem::Tblfm::Expr>>::read(out.expr(), in.for_field(&org::sem::Tblfm::Assign::expr));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org_Tblfm_Assign_Flag>, hstd::Vec<org::sem::Tblfm::Assign::Flag>>::read(out.flags(), in.for_field(&org::sem::Tblfm::Assign::flags));
}

void proto_serde<::orgproto::org::Tblfm, org::sem::Tblfm>::write(::orgproto::org::Tblfm* out, org::sem::Tblfm const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Assign>, hstd::Vec<org::sem::Tblfm::Assign>>::write(out->mutable_exprs(), in.exprs);
}

void proto_serde<::orgproto::org::Tblfm, org::sem::Tblfm>::read(::orgproto::org::Tblfm const& out, proto_write_accessor<org::sem::Tblfm> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Tblfm::Assign>, hstd::Vec<org::sem::Tblfm::Assign>>::read(out.exprs(), in.for_field(&org::sem::Tblfm::exprs));
}

void proto_serde<::orgproto::org::AttrValue, org::sem::AttrValue>::write(::orgproto::org::AttrValue* out, org::sem::AttrValue const& in) {
  if (in.name) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_name(), *in.name);
  }
  if (in.varname) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_varname(), *in.varname);
  }
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
  out->set_isquoted(in.isQuoted);
}

void proto_serde<::orgproto::org::AttrValue, org::sem::AttrValue>::read(::orgproto::org::AttrValue const& out, proto_write_accessor<org::sem::AttrValue> in) {
  if (out.has_name()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.name(), in.for_field(&org::sem::AttrValue::name));
  }
  if (out.has_varname()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.varname(), in.for_field(&org::sem::AttrValue::varname));
  }
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::AttrValue::value));
  in.for_field(&org::sem::AttrValue::isQuoted).get() = out.isquoted();
}

void proto_serde<::orgproto::org::HashTagFlat, org::sem::HashTagFlat>::write(::orgproto::org::HashTagFlat* out, org::sem::HashTagFlat const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_tags(), in.tags);
}

void proto_serde<::orgproto::org::HashTagFlat, org::sem::HashTagFlat>::read(::orgproto::org::HashTagFlat const& out, proto_write_accessor<org::sem::HashTagFlat> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.tags(), in.for_field(&org::sem::HashTagFlat::tags));
}

void proto_serde<::orgproto::org::HashTagText, org::sem::HashTagText>::write(::orgproto::org::HashTagText* out, org::sem::HashTagText const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTagText>, hstd::Vec<org::sem::HashTagText>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::org::HashTagText, org::sem::HashTagText>::read(::orgproto::org::HashTagText const& out, proto_write_accessor<org::sem::HashTagText> in) {
  proto_serde<std::string, hstd::Str>::read(out.head(), in.for_field(&org::sem::HashTagText::head));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTagText>, hstd::Vec<org::sem::HashTagText>>::read(out.subtags(), in.for_field(&org::sem::HashTagText::subtags));
}

void proto_serde<::orgproto::org::SubtreePath, org::sem::SubtreePath>::write(::orgproto::org::SubtreePath* out, org::sem::SubtreePath const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::org::SubtreePath, org::sem::SubtreePath>::read(::orgproto::org::SubtreePath const& out, proto_write_accessor<org::sem::SubtreePath> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.path(), in.for_field(&org::sem::SubtreePath::path));
}

void proto_serde<::orgproto::org::LinkTarget::Raw, org::sem::LinkTarget::Raw>::write(::orgproto::org::LinkTarget::Raw* out, org::sem::LinkTarget::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::LinkTarget::Raw, org::sem::LinkTarget::Raw>::read(::orgproto::org::LinkTarget::Raw const& out, proto_write_accessor<org::sem::LinkTarget::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::Raw::text));
}

void proto_serde<::orgproto::org::LinkTarget::Id, org::sem::LinkTarget::Id>::write(::orgproto::org::LinkTarget::Id* out, org::sem::LinkTarget::Id const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::LinkTarget::Id, org::sem::LinkTarget::Id>::read(::orgproto::org::LinkTarget::Id const& out, proto_write_accessor<org::sem::LinkTarget::Id> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::Id::text));
}

void proto_serde<::orgproto::org::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::write(::orgproto::org::LinkTarget::CustomId* out, org::sem::LinkTarget::CustomId const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::read(::orgproto::org::LinkTarget::CustomId const& out, proto_write_accessor<org::sem::LinkTarget::CustomId> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::LinkTarget::CustomId::text));
}

void proto_serde<::orgproto::org::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::write(::orgproto::org::LinkTarget::SubtreeTitle* out, org::sem::LinkTarget::SubtreeTitle const& in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::write(out->mutable_title(), in.title);
  out->set_level(in.level);
}

void proto_serde<::orgproto::org::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::read(::orgproto::org::LinkTarget::SubtreeTitle const& out, proto_write_accessor<org::sem::LinkTarget::SubtreeTitle> in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::read(out.title(), in.for_field(&org::sem::LinkTarget::SubtreeTitle::title));
  in.for_field(&org::sem::LinkTarget::SubtreeTitle::level).get() = out.level();
}

void proto_serde<::orgproto::org::LinkTarget::Person, org::sem::LinkTarget::Person>::write(::orgproto::org::LinkTarget::Person* out, org::sem::LinkTarget::Person const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::LinkTarget::Person, org::sem::LinkTarget::Person>::read(::orgproto::org::LinkTarget::Person const& out, proto_write_accessor<org::sem::LinkTarget::Person> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::LinkTarget::Person::name));
}

void proto_serde<::orgproto::org::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::write(::orgproto::org::LinkTarget::UserProtocol* out, org::sem::LinkTarget::UserProtocol const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_protocol(), in.protocol);
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::read(::orgproto::org::LinkTarget::UserProtocol const& out, proto_write_accessor<org::sem::LinkTarget::UserProtocol> in) {
  proto_serde<std::string, hstd::Str>::read(out.protocol(), in.for_field(&org::sem::LinkTarget::UserProtocol::protocol));
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::UserProtocol::target));
}

void proto_serde<::orgproto::org::LinkTarget::Internal, org::sem::LinkTarget::Internal>::write(::orgproto::org::LinkTarget::Internal* out, org::sem::LinkTarget::Internal const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::LinkTarget::Internal, org::sem::LinkTarget::Internal>::read(::orgproto::org::LinkTarget::Internal const& out, proto_write_accessor<org::sem::LinkTarget::Internal> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::Internal::target));
}

void proto_serde<::orgproto::org::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::write(::orgproto::org::LinkTarget::Footnote* out, org::sem::LinkTarget::Footnote const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::read(::orgproto::org::LinkTarget::Footnote const& out, proto_write_accessor<org::sem::LinkTarget::Footnote> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::LinkTarget::Footnote::target));
}

void proto_serde<::orgproto::org::LinkTarget::File, org::sem::LinkTarget::File>::write(::orgproto::org::LinkTarget::File* out, org::sem::LinkTarget::File const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::org::LinkTarget::File, org::sem::LinkTarget::File>::read(::orgproto::org::LinkTarget::File const& out, proto_write_accessor<org::sem::LinkTarget::File> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::LinkTarget::File::file));
}

void proto_serde<::orgproto::org::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::write(::orgproto::org::LinkTarget::Attachment* out, org::sem::LinkTarget::Attachment const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::org::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::read(::orgproto::org::LinkTarget::Attachment const& out, proto_write_accessor<org::sem::LinkTarget::Attachment> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::LinkTarget::Attachment::file));
}

void proto_serde<::orgproto::org::LinkTarget, org::sem::LinkTarget>::write(::orgproto::org::LinkTarget* out, org::sem::LinkTarget const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::LinkTarget::Raw, org::sem::LinkTarget::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::LinkTarget::Id, org::sem::LinkTarget::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::write(out->mutable_data()->mutable_customid(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::write(out->mutable_data()->mutable_subtreetitle(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::org::LinkTarget::Person, org::sem::LinkTarget::Person>::write(out->mutable_data()->mutable_person(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::org::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::write(out->mutable_data()->mutable_userprotocol(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::org::LinkTarget::Internal, org::sem::LinkTarget::Internal>::write(out->mutable_data()->mutable_internal(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::org::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::org::LinkTarget::File, org::sem::LinkTarget::File>::write(out->mutable_data()->mutable_file(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::org::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<9>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::LinkTarget, org::sem::LinkTarget>::read(::orgproto::org::LinkTarget const& out, proto_write_accessor<org::sem::LinkTarget> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::LinkTarget::Data::kRaw:
      proto_serde<orgproto::org::LinkTarget::Raw, org::sem::LinkTarget::Raw>::read(out.data().raw(), in.for_field_variant<0>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kId:
      proto_serde<orgproto::org::LinkTarget::Id, org::sem::LinkTarget::Id>::read(out.data().id(), in.for_field_variant<1>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kCustomid:
      proto_serde<orgproto::org::LinkTarget::CustomId, org::sem::LinkTarget::CustomId>::read(out.data().customid(), in.for_field_variant<2>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kSubtreetitle:
      proto_serde<orgproto::org::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle>::read(out.data().subtreetitle(), in.for_field_variant<3>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kPerson:
      proto_serde<orgproto::org::LinkTarget::Person, org::sem::LinkTarget::Person>::read(out.data().person(), in.for_field_variant<4>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kUserprotocol:
      proto_serde<orgproto::org::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol>::read(out.data().userprotocol(), in.for_field_variant<5>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kInternal:
      proto_serde<orgproto::org::LinkTarget::Internal, org::sem::LinkTarget::Internal>::read(out.data().internal(), in.for_field_variant<6>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kFootnote:
      proto_serde<orgproto::org::LinkTarget::Footnote, org::sem::LinkTarget::Footnote>::read(out.data().footnote(), in.for_field_variant<7>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kFile:
      proto_serde<orgproto::org::LinkTarget::File, org::sem::LinkTarget::File>::read(out.data().file(), in.for_field_variant<8>(&org::sem::LinkTarget::data));
      break;
    case ::orgproto::org::LinkTarget::Data::kAttachment:
      proto_serde<orgproto::org::LinkTarget::Attachment, org::sem::LinkTarget::Attachment>::read(out.data().attachment(), in.for_field_variant<9>(&org::sem::LinkTarget::data));
      break;
  }
}

void proto_serde<::orgproto::org::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::write(::orgproto::org::SubtreeLogHead::Priority* out, org::sem::SubtreeLogHead::Priority const& in) {
  if (in.oldPriority) {
    out->set_oldpriority(*in.oldPriority);
  }
  if (in.newPriority) {
    out->set_newpriority(*in.newPriority);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  out->set_action(static_cast<orgproto::org_SubtreeLogHead_Priority_Action>(in.action));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::read(::orgproto::org::SubtreeLogHead::Priority const& out, proto_write_accessor<org::sem::SubtreeLogHead::Priority> in) {
  if (out.has_oldpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.oldpriority(), in.for_field(&org::sem::SubtreeLogHead::Priority::oldPriority));
  }
  if (out.has_newpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.newpriority(), in.for_field(&org::sem::SubtreeLogHead::Priority::newPriority));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Priority::on));
  in.for_field(&org::sem::SubtreeLogHead::Priority::action).get() = static_cast<org::sem::SubtreeLogHead::Priority::Action>(out.action());
}

void proto_serde<::orgproto::org::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::write(::orgproto::org::SubtreeLogHead::Note* out, org::sem::SubtreeLogHead::Note const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::org::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::read(::orgproto::org::SubtreeLogHead::Note const& out, proto_write_accessor<org::sem::SubtreeLogHead::Note> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Note::on));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::write(::orgproto::org::SubtreeLogHead::Refile* out, org::sem::SubtreeLogHead::Refile const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::org::LinkTarget, org::sem::LinkTarget>::write(out->mutable_from(), in.from);
}

void proto_serde<::orgproto::org::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::read(::orgproto::org::SubtreeLogHead::Refile const& out, proto_write_accessor<org::sem::SubtreeLogHead::Refile> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Refile::on));
  proto_serde<orgproto::org::LinkTarget, org::sem::LinkTarget>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Refile::from));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::write(::orgproto::org::SubtreeLogHead::Clock* out, org::sem::SubtreeLogHead::Clock const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::org::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::read(::orgproto::org::SubtreeLogHead::Clock const& out, proto_write_accessor<org::sem::SubtreeLogHead::Clock> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Clock::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Clock::to));
  }
}

void proto_serde<::orgproto::org::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::write(::orgproto::org::SubtreeLogHead::State* out, org::sem::SubtreeLogHead::State const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_from(), in.from);
  proto_serde<std::string, hstd::Str>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::org::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::read(::orgproto::org::SubtreeLogHead::State const& out, proto_write_accessor<org::sem::SubtreeLogHead::State> in) {
  proto_serde<std::string, hstd::Str>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::State::from));
  proto_serde<std::string, hstd::Str>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::State::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::State::on));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::write(::orgproto::org::SubtreeLogHead::Deadline* out, org::sem::SubtreeLogHead::Deadline const& in) {
  if (in.from) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::org::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::read(::orgproto::org::SubtreeLogHead::Deadline const& out, proto_write_accessor<org::sem::SubtreeLogHead::Deadline> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Deadline::from));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Deadline::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Deadline::on));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::write(::orgproto::org::SubtreeLogHead::Schedule* out, org::sem::SubtreeLogHead::Schedule const& in) {
  if (in.from) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::org::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::read(::orgproto::org::SubtreeLogHead::Schedule const& out, proto_write_accessor<org::sem::SubtreeLogHead::Schedule> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.from(), in.for_field(&org::sem::SubtreeLogHead::Schedule::from));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.to(), in.for_field(&org::sem::SubtreeLogHead::Schedule::to));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Schedule::on));
}

void proto_serde<::orgproto::org::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::write(::orgproto::org::SubtreeLogHead::Tag* out, org::sem::SubtreeLogHead::Tag const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::write(out->mutable_tag(), in.tag);
  out->set_added(in.added);
}

void proto_serde<::orgproto::org::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::read(::orgproto::org::SubtreeLogHead::Tag const& out, proto_write_accessor<org::sem::SubtreeLogHead::Tag> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.on(), in.for_field(&org::sem::SubtreeLogHead::Tag::on));
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::read(out.tag(), in.for_field(&org::sem::SubtreeLogHead::Tag::tag));
  in.for_field(&org::sem::SubtreeLogHead::Tag::added).get() = out.added();
}

void proto_serde<::orgproto::org::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::write(::orgproto::org::SubtreeLogHead::Unknown* out, org::sem::SubtreeLogHead::Unknown const& in) {

}

void proto_serde<::orgproto::org::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::read(::orgproto::org::SubtreeLogHead::Unknown const& out, proto_write_accessor<org::sem::SubtreeLogHead::Unknown> in) {

}

void proto_serde<::orgproto::org::SubtreeLogHead, org::sem::SubtreeLogHead>::write(::orgproto::org::SubtreeLogHead* out, org::sem::SubtreeLogHead const& in) {
  switch (in.log.index()) {
    case 0:
      proto_serde<orgproto::org::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log));
      break;
    case 1:
      proto_serde<orgproto::org::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log));
      break;
    case 2:
      proto_serde<orgproto::org::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log));
      break;
    case 3:
      proto_serde<orgproto::org::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log));
      break;
    case 4:
      proto_serde<orgproto::org::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log));
      break;
    case 5:
      proto_serde<orgproto::org::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::write(out->mutable_log()->mutable_deadline(), std::get<5>(in.log));
      break;
    case 6:
      proto_serde<orgproto::org::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::write(out->mutable_log()->mutable_schedule(), std::get<6>(in.log));
      break;
    case 7:
      proto_serde<orgproto::org::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::write(out->mutable_log()->mutable_tag(), std::get<7>(in.log));
      break;
    case 8:
      proto_serde<orgproto::org::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::write(out->mutable_log()->mutable_unknown(), std::get<8>(in.log));
      break;
  }
}

void proto_serde<::orgproto::org::SubtreeLogHead, org::sem::SubtreeLogHead>::read(::orgproto::org::SubtreeLogHead const& out, proto_write_accessor<org::sem::SubtreeLogHead> in) {
  switch (out.log().kind_case()) {
    case ::orgproto::org::SubtreeLogHead::LogEntry::kPriority:
      proto_serde<orgproto::org::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority>::read(out.log().priority(), in.for_field_variant<0>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kNote:
      proto_serde<orgproto::org::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note>::read(out.log().note(), in.for_field_variant<1>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kRefile:
      proto_serde<orgproto::org::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile>::read(out.log().refile(), in.for_field_variant<2>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kClock:
      proto_serde<orgproto::org::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock>::read(out.log().clock(), in.for_field_variant<3>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kState:
      proto_serde<orgproto::org::SubtreeLogHead::State, org::sem::SubtreeLogHead::State>::read(out.log().state(), in.for_field_variant<4>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kDeadline:
      proto_serde<orgproto::org::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline>::read(out.log().deadline(), in.for_field_variant<5>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kSchedule:
      proto_serde<orgproto::org::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule>::read(out.log().schedule(), in.for_field_variant<6>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kTag:
      proto_serde<orgproto::org::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag>::read(out.log().tag(), in.for_field_variant<7>(&org::sem::SubtreeLogHead::log));
      break;
    case ::orgproto::org::SubtreeLogHead::LogEntry::kUnknown:
      proto_serde<orgproto::org::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown>::read(out.log().unknown(), in.for_field_variant<8>(&org::sem::SubtreeLogHead::log));
      break;
  }
}

void proto_serde<::orgproto::org::SubtreeCompletion, org::sem::SubtreeCompletion>::write(::orgproto::org::SubtreeCompletion* out, org::sem::SubtreeCompletion const& in) {
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::org::SubtreeCompletion, org::sem::SubtreeCompletion>::read(::orgproto::org::SubtreeCompletion const& out, proto_write_accessor<org::sem::SubtreeCompletion> in) {
  in.for_field(&org::sem::SubtreeCompletion::done).get() = out.done();
  in.for_field(&org::sem::SubtreeCompletion::full).get() = out.full();
  in.for_field(&org::sem::SubtreeCompletion::isPercent).get() = out.ispercent();
}

void proto_serde<::orgproto::org::AttrList, org::sem::AttrList>::write(::orgproto::org::AttrList* out, org::sem::AttrList const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::AttrValue>, hstd::Vec<org::sem::AttrValue>>::write(out->mutable_items(), in.items);
}

void proto_serde<::orgproto::org::AttrList, org::sem::AttrList>::read(::orgproto::org::AttrList const& out, proto_write_accessor<org::sem::AttrList> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::AttrValue>, hstd::Vec<org::sem::AttrValue>>::read(out.items(), in.for_field(&org::sem::AttrList::items));
}

void proto_serde<::orgproto::org::AttrGroup, org::sem::AttrGroup>::write(::orgproto::org::AttrGroup* out, org::sem::AttrGroup const& in) {
  proto_serde<orgproto::org::AttrList, org::sem::AttrList>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::org::AttrList>, hstd::UnorderedMap<hstd::Str, org::sem::AttrList>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::org::AttrGroup, org::sem::AttrGroup>::read(::orgproto::org::AttrGroup const& out, proto_write_accessor<org::sem::AttrGroup> in) {
  proto_serde<orgproto::org::AttrList, org::sem::AttrList>::read(out.positional(), in.for_field(&org::sem::AttrGroup::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::org::AttrList>, hstd::UnorderedMap<hstd::Str, org::sem::AttrList>>::read(out.named(), in.for_field(&org::sem::AttrGroup::named));
}

void proto_serde<::orgproto::org::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::write(::orgproto::org::ColumnView::Summary::CheckboxAggregate* out, org::sem::ColumnView::Summary::CheckboxAggregate const& in) {
  out->set_kind(static_cast<orgproto::org_ColumnView_Summary_CheckboxAggregate_Kind>(in.kind));
}

void proto_serde<::orgproto::org::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::read(::orgproto::org::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::CheckboxAggregate> in) {
  in.for_field(&org::sem::ColumnView::Summary::CheckboxAggregate::kind).get() = static_cast<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(out.kind());
}

void proto_serde<::orgproto::org::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::write(::orgproto::org::ColumnView::Summary::MathAggregate* out, org::sem::ColumnView::Summary::MathAggregate const& in) {
  out->set_kind(static_cast<orgproto::org_ColumnView_Summary_MathAggregate_Kind>(in.kind));
  if (in.formatDigits) {
    out->set_formatdigits(*in.formatDigits);
  }
  if (in.formatPrecision) {
    out->set_formatprecision(*in.formatPrecision);
  }
}

void proto_serde<::orgproto::org::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::read(::orgproto::org::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::MathAggregate> in) {
  in.for_field(&org::sem::ColumnView::Summary::MathAggregate::kind).get() = static_cast<org::sem::ColumnView::Summary::MathAggregate::Kind>(out.kind());
  if (out.has_formatdigits()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatdigits(), in.for_field(&org::sem::ColumnView::Summary::MathAggregate::formatDigits));
  }
  if (out.has_formatprecision()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatprecision(), in.for_field(&org::sem::ColumnView::Summary::MathAggregate::formatPrecision));
  }
}

void proto_serde<::orgproto::org::ColumnView::Summary, org::sem::ColumnView::Summary>::write(::orgproto::org::ColumnView::Summary* out, org::sem::ColumnView::Summary const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::write(out->mutable_data()->mutable_checkboxaggregate(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::write(out->mutable_data()->mutable_mathaggregate(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::ColumnView::Summary, org::sem::ColumnView::Summary>::read(::orgproto::org::ColumnView::Summary const& out, proto_write_accessor<org::sem::ColumnView::Summary> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::ColumnView::Summary::Data::kCheckboxaggregate:
      proto_serde<orgproto::org::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate>::read(out.data().checkboxaggregate(), in.for_field_variant<0>(&org::sem::ColumnView::Summary::data));
      break;
    case ::orgproto::org::ColumnView::Summary::Data::kMathaggregate:
      proto_serde<orgproto::org::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate>::read(out.data().mathaggregate(), in.for_field_variant<1>(&org::sem::ColumnView::Summary::data));
      break;
  }
}

void proto_serde<::orgproto::org::ColumnView::Column, org::sem::ColumnView::Column>::write(::orgproto::org::ColumnView::Column* out, org::sem::ColumnView::Column const& in) {
  if (in.summary) {
    proto_serde<orgproto::org::ColumnView::Summary, org::sem::ColumnView::Summary>::write(out->mutable_summary(), *in.summary);
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

void proto_serde<::orgproto::org::ColumnView::Column, org::sem::ColumnView::Column>::read(::orgproto::org::ColumnView::Column const& out, proto_write_accessor<org::sem::ColumnView::Column> in) {
  if (out.has_summary()) {
    proto_serde<hstd::Opt<orgproto::org::ColumnView::Summary>, hstd::Opt<org::sem::ColumnView::Summary>>::read(out.summary(), in.for_field(&org::sem::ColumnView::Column::summary));
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

void proto_serde<::orgproto::org::ColumnView, org::sem::ColumnView>::write(::orgproto::org::ColumnView* out, org::sem::ColumnView const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::ColumnView::Column>, hstd::Vec<org::sem::ColumnView::Column>>::write(out->mutable_columns(), in.columns);
}

void proto_serde<::orgproto::org::ColumnView, org::sem::ColumnView>::read(::orgproto::org::ColumnView const& out, proto_write_accessor<org::sem::ColumnView> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::ColumnView::Column>, hstd::Vec<org::sem::ColumnView::Column>>::read(out.columns(), in.for_field(&org::sem::ColumnView::columns));
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::write(::orgproto::org::BlockCodeLine::Part::Raw* out, org::sem::BlockCodeLine::Part::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_code(), in.code);
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::read(::orgproto::org::BlockCodeLine::Part::Raw const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.code(), in.for_field(&org::sem::BlockCodeLine::Part::Raw::code));
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::write(::orgproto::org::BlockCodeLine::Part::Callout* out, org::sem::BlockCodeLine::Part::Callout const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::read(::orgproto::org::BlockCodeLine::Part::Callout const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Callout> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::BlockCodeLine::Part::Callout::name));
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::write(::orgproto::org::BlockCodeLine::Part::Tangle* out, org::sem::BlockCodeLine::Part::Tangle const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::read(::orgproto::org::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Tangle> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::BlockCodeLine::Part::Tangle::target));
}

void proto_serde<::orgproto::org::BlockCodeLine::Part, org::sem::BlockCodeLine::Part>::write(::orgproto::org::BlockCodeLine::Part* out, org::sem::BlockCodeLine::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::BlockCodeLine::Part, org::sem::BlockCodeLine::Part>::read(::orgproto::org::BlockCodeLine::Part const& out, proto_write_accessor<org::sem::BlockCodeLine::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::BlockCodeLine::Part::Data::kRaw:
      proto_serde<orgproto::org::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&org::sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::org::BlockCodeLine::Part::Data::kCallout:
      proto_serde<orgproto::org::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&org::sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::org::BlockCodeLine::Part::Data::kTangle:
      proto_serde<orgproto::org::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&org::sem::BlockCodeLine::Part::data));
      break;
  }
}

void proto_serde<::orgproto::org::BlockCodeLine, org::sem::BlockCodeLine>::write(::orgproto::org::BlockCodeLine* out, org::sem::BlockCodeLine const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeLine::Part>, hstd::Vec<org::sem::BlockCodeLine::Part>>::write(out->mutable_parts(), in.parts);
}

void proto_serde<::orgproto::org::BlockCodeLine, org::sem::BlockCodeLine>::read(::orgproto::org::BlockCodeLine const& out, proto_write_accessor<org::sem::BlockCodeLine> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeLine::Part>, hstd::Vec<org::sem::BlockCodeLine::Part>>::read(out.parts(), in.for_field(&org::sem::BlockCodeLine::parts));
}

void proto_serde<::orgproto::org::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart>::write(::orgproto::org::BlockCodeSwitch::LineStart* out, org::sem::BlockCodeSwitch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::org::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart>::read(::orgproto::org::BlockCodeSwitch::LineStart const& out, proto_write_accessor<org::sem::BlockCodeSwitch::LineStart> in) {
  in.for_field(&org::sem::BlockCodeSwitch::LineStart::start).get() = out.start();
  in.for_field(&org::sem::BlockCodeSwitch::LineStart::extendLast).get() = out.extendlast();
}

void proto_serde<::orgproto::org::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat>::write(::orgproto::org::BlockCodeSwitch::CalloutFormat* out, org::sem::BlockCodeSwitch::CalloutFormat const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::org::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat>::read(::orgproto::org::BlockCodeSwitch::CalloutFormat const& out, proto_write_accessor<org::sem::BlockCodeSwitch::CalloutFormat> in) {
  proto_serde<std::string, hstd::Str>::read(out.format(), in.for_field(&org::sem::BlockCodeSwitch::CalloutFormat::format));
}

void proto_serde<::orgproto::org::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout>::write(::orgproto::org::BlockCodeSwitch::RemoveCallout* out, org::sem::BlockCodeSwitch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::org::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout>::read(::orgproto::org::BlockCodeSwitch::RemoveCallout const& out, proto_write_accessor<org::sem::BlockCodeSwitch::RemoveCallout> in) {
  in.for_field(&org::sem::BlockCodeSwitch::RemoveCallout::remove).get() = out.remove();
}

void proto_serde<::orgproto::org::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine>::write(::orgproto::org::BlockCodeSwitch::EmphasizeLine* out, org::sem::BlockCodeSwitch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, hstd::Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::org::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine>::read(::orgproto::org::BlockCodeSwitch::EmphasizeLine const& out, proto_write_accessor<org::sem::BlockCodeSwitch::EmphasizeLine> in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, hstd::Vec<int>>::read(out.line(), in.for_field(&org::sem::BlockCodeSwitch::EmphasizeLine::line));
}

void proto_serde<::orgproto::org::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent>::write(::orgproto::org::BlockCodeSwitch::Dedent* out, org::sem::BlockCodeSwitch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::org::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent>::read(::orgproto::org::BlockCodeSwitch::Dedent const& out, proto_write_accessor<org::sem::BlockCodeSwitch::Dedent> in) {
  in.for_field(&org::sem::BlockCodeSwitch::Dedent::value).get() = out.value();
}

void proto_serde<::orgproto::org::BlockCodeSwitch, org::sem::BlockCodeSwitch>::write(::orgproto::org::BlockCodeSwitch* out, org::sem::BlockCodeSwitch const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::org::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::BlockCodeSwitch, org::sem::BlockCodeSwitch>::read(::orgproto::org::BlockCodeSwitch const& out, proto_write_accessor<org::sem::BlockCodeSwitch> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::BlockCodeSwitch::Data::kLinestart:
      proto_serde<orgproto::org::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart>::read(out.data().linestart(), in.for_field_variant<0>(&org::sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::org::BlockCodeSwitch::Data::kCalloutformat:
      proto_serde<orgproto::org::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat>::read(out.data().calloutformat(), in.for_field_variant<1>(&org::sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::org::BlockCodeSwitch::Data::kRemovecallout:
      proto_serde<orgproto::org::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout>::read(out.data().removecallout(), in.for_field_variant<2>(&org::sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::org::BlockCodeSwitch::Data::kEmphasizeline:
      proto_serde<orgproto::org::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine>::read(out.data().emphasizeline(), in.for_field_variant<3>(&org::sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::org::BlockCodeSwitch::Data::kDedent:
      proto_serde<orgproto::org::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent>::read(out.data().dedent(), in.for_field_variant<4>(&org::sem::BlockCodeSwitch::data));
      break;
  }
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::None, org::sem::BlockCodeEvalResult::None>::write(::orgproto::org::BlockCodeEvalResult::None* out, org::sem::BlockCodeEvalResult::None const& in) {

}

void proto_serde<::orgproto::org::BlockCodeEvalResult::None, org::sem::BlockCodeEvalResult::None>::read(::orgproto::org::BlockCodeEvalResult::None const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::None> in) {

}

void proto_serde<::orgproto::org::BlockCodeEvalResult::OrgValue, org::sem::BlockCodeEvalResult::OrgValue>::write(::orgproto::org::BlockCodeEvalResult::OrgValue* out, org::sem::BlockCodeEvalResult::OrgValue const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::OrgValue, org::sem::BlockCodeEvalResult::OrgValue>::read(::orgproto::org::BlockCodeEvalResult::OrgValue const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::OrgValue> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::BlockCodeEvalResult::OrgValue::value));
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::File, org::sem::BlockCodeEvalResult::File>::write(::orgproto::org::BlockCodeEvalResult::File* out, org::sem::BlockCodeEvalResult::File const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::File, org::sem::BlockCodeEvalResult::File>::read(::orgproto::org::BlockCodeEvalResult::File const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::File> in) {
  proto_serde<std::string, hstd::Str>::read(out.path(), in.for_field(&org::sem::BlockCodeEvalResult::File::path));
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::Raw, org::sem::BlockCodeEvalResult::Raw>::write(::orgproto::org::BlockCodeEvalResult::Raw* out, org::sem::BlockCodeEvalResult::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::BlockCodeEvalResult::Raw, org::sem::BlockCodeEvalResult::Raw>::read(::orgproto::org::BlockCodeEvalResult::Raw const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::BlockCodeEvalResult::Raw::text));
}

void proto_serde<::orgproto::org::BlockCodeEvalResult, org::sem::BlockCodeEvalResult>::write(::orgproto::org::BlockCodeEvalResult* out, org::sem::BlockCodeEvalResult const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::BlockCodeEvalResult::None, org::sem::BlockCodeEvalResult::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::BlockCodeEvalResult::OrgValue, org::sem::BlockCodeEvalResult::OrgValue>::write(out->mutable_data()->mutable_orgvalue(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::BlockCodeEvalResult::File, org::sem::BlockCodeEvalResult::File>::write(out->mutable_data()->mutable_file(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::BlockCodeEvalResult::Raw, org::sem::BlockCodeEvalResult::Raw>::write(out->mutable_data()->mutable_raw(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::BlockCodeEvalResult, org::sem::BlockCodeEvalResult>::read(::orgproto::org::BlockCodeEvalResult const& out, proto_write_accessor<org::sem::BlockCodeEvalResult> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::BlockCodeEvalResult::Data::kNone:
      proto_serde<orgproto::org::BlockCodeEvalResult::None, org::sem::BlockCodeEvalResult::None>::read(out.data().none(), in.for_field_variant<0>(&org::sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::org::BlockCodeEvalResult::Data::kOrgvalue:
      proto_serde<orgproto::org::BlockCodeEvalResult::OrgValue, org::sem::BlockCodeEvalResult::OrgValue>::read(out.data().orgvalue(), in.for_field_variant<1>(&org::sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::org::BlockCodeEvalResult::Data::kFile:
      proto_serde<orgproto::org::BlockCodeEvalResult::File, org::sem::BlockCodeEvalResult::File>::read(out.data().file(), in.for_field_variant<2>(&org::sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::org::BlockCodeEvalResult::Data::kRaw:
      proto_serde<orgproto::org::BlockCodeEvalResult::Raw, org::sem::BlockCodeEvalResult::Raw>::read(out.data().raw(), in.for_field_variant<3>(&org::sem::BlockCodeEvalResult::data));
      break;
  }
}

void proto_serde<::orgproto::org::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport>::write(::orgproto::org::DocumentExportConfig::TaskExport* out, org::sem::DocumentExportConfig::TaskExport const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_taskwhitelist(), in.taskWhitelist);
}

void proto_serde<::orgproto::org::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport>::read(::orgproto::org::DocumentExportConfig::TaskExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::TaskExport> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.taskwhitelist(), in.for_field(&org::sem::DocumentExportConfig::TaskExport::taskWhitelist));
}

void proto_serde<::orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(::orgproto::org::DocumentExportConfig::DoExport* out, org::sem::DocumentExportConfig::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(::orgproto::org::DocumentExportConfig::DoExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::DoExport> in) {
  in.for_field(&org::sem::DocumentExportConfig::DoExport::exportToc).get() = out.exporttoc();
}

void proto_serde<::orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(::orgproto::org::DocumentExportConfig::ExportFixed* out, org::sem::DocumentExportConfig::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(::orgproto::org::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<org::sem::DocumentExportConfig::ExportFixed> in) {
  in.for_field(&org::sem::DocumentExportConfig::ExportFixed::exportLevels).get() = out.exportlevels();
}

void proto_serde<::orgproto::org::DocumentExportConfig, org::sem::DocumentExportConfig>::write(::orgproto::org::DocumentExportConfig* out, org::sem::DocumentExportConfig const& in) {
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
  out->set_brokenlinks(static_cast<orgproto::org_DocumentExportConfig_BrokenLinks>(in.brokenLinks));
  switch (in.tocExport.index()) {
    case 0:
      proto_serde<orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(out->mutable_tocexport()->mutable_doexport(), std::get<0>(in.tocExport));
      break;
    case 1:
      proto_serde<orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(out->mutable_tocexport()->mutable_exportfixed(), std::get<1>(in.tocExport));
      break;
  }
  out->set_tagexport(static_cast<orgproto::org_DocumentExportConfig_TagExport>(in.tagExport));
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::DocumentExportConfig, org::sem::DocumentExportConfig>::read(::orgproto::org::DocumentExportConfig const& out, proto_write_accessor<org::sem::DocumentExportConfig> in) {
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
  in.for_field(&org::sem::DocumentExportConfig::brokenLinks).get() = static_cast<org::sem::DocumentExportConfig::BrokenLinks>(out.brokenlinks());
  switch (out.tocexport().kind_case()) {
    case ::orgproto::org::DocumentExportConfig::TocExport::kDoexport:
      proto_serde<orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(out.tocexport().doexport(), in.for_field_variant<0>(&org::sem::DocumentExportConfig::tocExport));
      break;
    case ::orgproto::org::DocumentExportConfig::TocExport::kExportfixed:
      proto_serde<orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(out.tocexport().exportfixed(), in.for_field_variant<1>(&org::sem::DocumentExportConfig::tocExport));
      break;
  }
  in.for_field(&org::sem::DocumentExportConfig::tagExport).get() = static_cast<org::sem::DocumentExportConfig::TagExport>(out.tagexport());
  switch (out.data().kind_case()) {
    case ::orgproto::org::DocumentExportConfig::TocExport::kDoexport:
      proto_serde<orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&org::sem::DocumentExportConfig::data));
      break;
    case ::orgproto::org::DocumentExportConfig::TocExport::kExportfixed:
      proto_serde<orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&org::sem::DocumentExportConfig::data));
      break;
  }
}

void proto_serde<::orgproto::org::SubtreePeriod, org::sem::SubtreePeriod>::write(::orgproto::org::SubtreePeriod* out, org::sem::SubtreePeriod const& in) {
  out->set_kind(static_cast<orgproto::org_SubtreePeriod_Kind>(in.kind));
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::org::SubtreePeriod, org::sem::SubtreePeriod>::read(::orgproto::org::SubtreePeriod const& out, proto_write_accessor<org::sem::SubtreePeriod> in) {
  in.for_field(&org::sem::SubtreePeriod::kind).get() = static_cast<org::sem::SubtreePeriod::Kind>(out.kind());
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.from(), in.for_field(&org::sem::SubtreePeriod::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.to(), in.for_field(&org::sem::SubtreePeriod::to));
  }
}

void proto_serde<::orgproto::org::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::write(::orgproto::org::NamedProperty::Nonblocking* out, org::sem::NamedProperty::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::org::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::read(::orgproto::org::NamedProperty::Nonblocking const& out, proto_write_accessor<org::sem::NamedProperty::Nonblocking> in) {
  in.for_field(&org::sem::NamedProperty::Nonblocking::isBlocking).get() = out.isblocking();
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::write(::orgproto::org::NamedProperty::ArchiveTime* out, org::sem::NamedProperty::ArchiveTime const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::read(::orgproto::org::NamedProperty::ArchiveTime const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTime> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::NamedProperty::ArchiveTime::time));
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::write(::orgproto::org::NamedProperty::ArchiveFile* out, org::sem::NamedProperty::ArchiveFile const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::read(::orgproto::org::NamedProperty::ArchiveFile const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveFile> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&org::sem::NamedProperty::ArchiveFile::file));
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::write(::orgproto::org::NamedProperty::ArchiveOlpath* out, org::sem::NamedProperty::ArchiveOlpath const& in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::read(::orgproto::org::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveOlpath> in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::read(out.path(), in.for_field(&org::sem::NamedProperty::ArchiveOlpath::path));
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::write(::orgproto::org::NamedProperty::ArchiveTarget* out, org::sem::NamedProperty::ArchiveTarget const& in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::write(out->mutable_path(), in.path);
  proto_serde<std::string, hstd::Str>::write(out->mutable_pattern(), in.pattern);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::read(::orgproto::org::NamedProperty::ArchiveTarget const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTarget> in) {
  proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::read(out.path(), in.for_field(&org::sem::NamedProperty::ArchiveTarget::path));
  proto_serde<std::string, hstd::Str>::read(out.pattern(), in.for_field(&org::sem::NamedProperty::ArchiveTarget::pattern));
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::write(::orgproto::org::NamedProperty::ArchiveCategory* out, org::sem::NamedProperty::ArchiveCategory const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_category(), in.category);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::read(::orgproto::org::NamedProperty::ArchiveCategory const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveCategory> in) {
  proto_serde<std::string, hstd::Str>::read(out.category(), in.for_field(&org::sem::NamedProperty::ArchiveCategory::category));
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::write(::orgproto::org::NamedProperty::ArchiveTodo* out, org::sem::NamedProperty::ArchiveTodo const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_todo(), in.todo);
}

void proto_serde<::orgproto::org::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::read(::orgproto::org::NamedProperty::ArchiveTodo const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTodo> in) {
  proto_serde<std::string, hstd::Str>::read(out.todo(), in.for_field(&org::sem::NamedProperty::ArchiveTodo::todo));
}

void proto_serde<::orgproto::org::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::write(::orgproto::org::NamedProperty::Trigger* out, org::sem::NamedProperty::Trigger const& in) {

}

void proto_serde<::orgproto::org::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::read(::orgproto::org::NamedProperty::Trigger const& out, proto_write_accessor<org::sem::NamedProperty::Trigger> in) {

}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::write(::orgproto::org::NamedProperty::ExportLatexClass* out, org::sem::NamedProperty::ExportLatexClass const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::read(::orgproto::org::NamedProperty::ExportLatexClass const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClass> in) {
  proto_serde<std::string, hstd::Str>::read(out.latexclass(), in.for_field(&org::sem::NamedProperty::ExportLatexClass::latexClass));
}

void proto_serde<::orgproto::org::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::write(::orgproto::org::NamedProperty::CookieData* out, org::sem::NamedProperty::CookieData const& in) {
  out->set_isrecursive(in.isRecursive);
  out->set_source(static_cast<orgproto::org_NamedProperty_CookieData_TodoSource>(in.source));
}

void proto_serde<::orgproto::org::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::read(::orgproto::org::NamedProperty::CookieData const& out, proto_write_accessor<org::sem::NamedProperty::CookieData> in) {
  in.for_field(&org::sem::NamedProperty::CookieData::isRecursive).get() = out.isrecursive();
  in.for_field(&org::sem::NamedProperty::CookieData::source).get() = static_cast<org::sem::NamedProperty::CookieData::TodoSource>(out.source());
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::write(::orgproto::org::NamedProperty::ExportLatexClassOptions* out, org::sem::NamedProperty::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::read(::orgproto::org::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClassOptions> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.options(), in.for_field(&org::sem::NamedProperty::ExportLatexClassOptions::options));
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::write(::orgproto::org::NamedProperty::ExportLatexHeader* out, org::sem::NamedProperty::ExportLatexHeader const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::read(::orgproto::org::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexHeader> in) {
  proto_serde<std::string, hstd::Str>::read(out.header(), in.for_field(&org::sem::NamedProperty::ExportLatexHeader::header));
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::write(::orgproto::org::NamedProperty::ExportLatexCompiler* out, org::sem::NamedProperty::ExportLatexCompiler const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::org::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::read(::orgproto::org::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexCompiler> in) {
  proto_serde<std::string, hstd::Str>::read(out.compiler(), in.for_field(&org::sem::NamedProperty::ExportLatexCompiler::compiler));
}

void proto_serde<::orgproto::org::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::write(::orgproto::org::NamedProperty::Ordered* out, org::sem::NamedProperty::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::org::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::read(::orgproto::org::NamedProperty::Ordered const& out, proto_write_accessor<org::sem::NamedProperty::Ordered> in) {
  in.for_field(&org::sem::NamedProperty::Ordered::isOrdered).get() = out.isordered();
}

void proto_serde<::orgproto::org::NamedProperty::Effort, org::sem::NamedProperty::Effort>::write(::orgproto::org::NamedProperty::Effort* out, org::sem::NamedProperty::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::org::NamedProperty::Effort, org::sem::NamedProperty::Effort>::read(::orgproto::org::NamedProperty::Effort const& out, proto_write_accessor<org::sem::NamedProperty::Effort> in) {
  in.for_field(&org::sem::NamedProperty::Effort::hours).get() = out.hours();
  in.for_field(&org::sem::NamedProperty::Effort::minutes).get() = out.minutes();
}

void proto_serde<::orgproto::org::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::write(::orgproto::org::NamedProperty::Visibility* out, org::sem::NamedProperty::Visibility const& in) {
  out->set_level(static_cast<orgproto::org_NamedProperty_Visibility_Level>(in.level));
}

void proto_serde<::orgproto::org::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::read(::orgproto::org::NamedProperty::Visibility const& out, proto_write_accessor<org::sem::NamedProperty::Visibility> in) {
  in.for_field(&org::sem::NamedProperty::Visibility::level).get() = static_cast<org::sem::NamedProperty::Visibility::Level>(out.level());
}

void proto_serde<::orgproto::org::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::write(::orgproto::org::NamedProperty::ExportOptions* out, org::sem::NamedProperty::ExportOptions const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, hstd::UnorderedMap<hstd::Str, hstd::Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::org::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::read(::orgproto::org::NamedProperty::ExportOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportOptions> in) {
  proto_serde<std::string, hstd::Str>::read(out.backend(), in.for_field(&org::sem::NamedProperty::ExportOptions::backend));
  proto_serde<::google::protobuf::Map<std::string, std::string>, hstd::UnorderedMap<hstd::Str, hstd::Str>>::read(out.values(), in.for_field(&org::sem::NamedProperty::ExportOptions::values));
}

void proto_serde<::orgproto::org::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::write(::orgproto::org::NamedProperty::Blocker* out, org::sem::NamedProperty::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::org::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::read(::orgproto::org::NamedProperty::Blocker const& out, proto_write_accessor<org::sem::NamedProperty::Blocker> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.blockers(), in.for_field(&org::sem::NamedProperty::Blocker::blockers));
}

void proto_serde<::orgproto::org::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::write(::orgproto::org::NamedProperty::Unnumbered* out, org::sem::NamedProperty::Unnumbered const& in) {

}

void proto_serde<::orgproto::org::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::read(::orgproto::org::NamedProperty::Unnumbered const& out, proto_write_accessor<org::sem::NamedProperty::Unnumbered> in) {

}

void proto_serde<::orgproto::org::NamedProperty::Created, org::sem::NamedProperty::Created>::write(::orgproto::org::NamedProperty::Created* out, org::sem::NamedProperty::Created const& in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::org::NamedProperty::Created, org::sem::NamedProperty::Created>::read(::orgproto::org::NamedProperty::Created const& out, proto_write_accessor<org::sem::NamedProperty::Created> in) {
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::NamedProperty::Created::time));
}

void proto_serde<::orgproto::org::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::write(::orgproto::org::NamedProperty::RadioId* out, org::sem::NamedProperty::RadioId const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_words(), in.words);
}

void proto_serde<::orgproto::org::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::read(::orgproto::org::NamedProperty::RadioId const& out, proto_write_accessor<org::sem::NamedProperty::RadioId> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.words(), in.for_field(&org::sem::NamedProperty::RadioId::words));
}

void proto_serde<::orgproto::org::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::write(::orgproto::org::NamedProperty::HashtagDef* out, org::sem::NamedProperty::HashtagDef const& in) {
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::write(out->mutable_hashtag(), in.hashtag);
}

void proto_serde<::orgproto::org::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::read(::orgproto::org::NamedProperty::HashtagDef const& out, proto_write_accessor<org::sem::NamedProperty::HashtagDef> in) {
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::read(out.hashtag(), in.for_field(&org::sem::NamedProperty::HashtagDef::hashtag));
}

void proto_serde<::orgproto::org::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::write(::orgproto::org::NamedProperty::CustomArgs* out, org::sem::NamedProperty::CustomArgs const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  if (in.sub) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_sub(), *in.sub);
  }
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void proto_serde<::orgproto::org::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::read(::orgproto::org::NamedProperty::CustomArgs const& out, proto_write_accessor<org::sem::NamedProperty::CustomArgs> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomArgs::name));
  if (out.has_sub()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.sub(), in.for_field(&org::sem::NamedProperty::CustomArgs::sub));
  }
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::NamedProperty::CustomArgs::attrs));
}

void proto_serde<::orgproto::org::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::write(::orgproto::org::NamedProperty::CustomRaw* out, org::sem::NamedProperty::CustomRaw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::read(::orgproto::org::NamedProperty::CustomRaw const& out, proto_write_accessor<org::sem::NamedProperty::CustomRaw> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomRaw::name));
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomRaw::value));
}

void proto_serde<::orgproto::org::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::write(::orgproto::org::NamedProperty::CustomSubtreeJson* out, org::sem::NamedProperty::CustomSubtreeJson const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::org::OrgJson, org::sem::OrgJson>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::read(::orgproto::org::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeJson> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomSubtreeJson::name));
  proto_serde<orgproto::org::OrgJson, org::sem::OrgJson>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomSubtreeJson::value));
}

void proto_serde<::orgproto::org::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::write(::orgproto::org::NamedProperty::CustomSubtreeFlags* out, org::sem::NamedProperty::CustomSubtreeFlags const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::read(::orgproto::org::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeFlags> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::NamedProperty::CustomSubtreeFlags::name));
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::read(out.value(), in.for_field(&org::sem::NamedProperty::CustomSubtreeFlags::value));
}

void proto_serde<::orgproto::org::NamedProperty, org::sem::NamedProperty>::write(::orgproto::org::NamedProperty* out, org::sem::NamedProperty const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::write(out->mutable_data()->mutable_archivetime(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::write(out->mutable_data()->mutable_archivefile(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::write(out->mutable_data()->mutable_archiveolpath(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::org::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::write(out->mutable_data()->mutable_archivetarget(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::org::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::write(out->mutable_data()->mutable_archivecategory(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::org::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::write(out->mutable_data()->mutable_archivetodo(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::org::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::org::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::org::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::write(out->mutable_data()->mutable_cookiedata(), std::get<9>(in.data));
      break;
    case 10:
      proto_serde<orgproto::org::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<10>(in.data));
      break;
    case 11:
      proto_serde<orgproto::org::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<11>(in.data));
      break;
    case 12:
      proto_serde<orgproto::org::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<12>(in.data));
      break;
    case 13:
      proto_serde<orgproto::org::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<13>(in.data));
      break;
    case 14:
      proto_serde<orgproto::org::NamedProperty::Effort, org::sem::NamedProperty::Effort>::write(out->mutable_data()->mutable_effort(), std::get<14>(in.data));
      break;
    case 15:
      proto_serde<orgproto::org::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<15>(in.data));
      break;
    case 16:
      proto_serde<orgproto::org::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<16>(in.data));
      break;
    case 17:
      proto_serde<orgproto::org::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<17>(in.data));
      break;
    case 18:
      proto_serde<orgproto::org::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<18>(in.data));
      break;
    case 19:
      proto_serde<orgproto::org::NamedProperty::Created, org::sem::NamedProperty::Created>::write(out->mutable_data()->mutable_created(), std::get<19>(in.data));
      break;
    case 20:
      proto_serde<orgproto::org::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::write(out->mutable_data()->mutable_radioid(), std::get<20>(in.data));
      break;
    case 21:
      proto_serde<orgproto::org::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::write(out->mutable_data()->mutable_hashtagdef(), std::get<21>(in.data));
      break;
    case 22:
      proto_serde<orgproto::org::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::write(out->mutable_data()->mutable_customargs(), std::get<22>(in.data));
      break;
    case 23:
      proto_serde<orgproto::org::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::write(out->mutable_data()->mutable_customraw(), std::get<23>(in.data));
      break;
    case 24:
      proto_serde<orgproto::org::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::write(out->mutable_data()->mutable_customsubtreejson(), std::get<24>(in.data));
      break;
    case 25:
      proto_serde<orgproto::org::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::write(out->mutable_data()->mutable_customsubtreeflags(), std::get<25>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::NamedProperty, org::sem::NamedProperty>::read(::orgproto::org::NamedProperty const& out, proto_write_accessor<org::sem::NamedProperty> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::org::NamedProperty::Data::kNonblocking:
      proto_serde<orgproto::org::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking>::read(out.data().nonblocking(), in.for_field_variant<0>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchivetime:
      proto_serde<orgproto::org::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime>::read(out.data().archivetime(), in.for_field_variant<1>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchivefile:
      proto_serde<orgproto::org::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile>::read(out.data().archivefile(), in.for_field_variant<2>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchiveolpath:
      proto_serde<orgproto::org::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath>::read(out.data().archiveolpath(), in.for_field_variant<3>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchivetarget:
      proto_serde<orgproto::org::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget>::read(out.data().archivetarget(), in.for_field_variant<4>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchivecategory:
      proto_serde<orgproto::org::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory>::read(out.data().archivecategory(), in.for_field_variant<5>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kArchivetodo:
      proto_serde<orgproto::org::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo>::read(out.data().archivetodo(), in.for_field_variant<6>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kTrigger:
      proto_serde<orgproto::org::NamedProperty::Trigger, org::sem::NamedProperty::Trigger>::read(out.data().trigger(), in.for_field_variant<7>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kExportlatexclass:
      proto_serde<orgproto::org::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass>::read(out.data().exportlatexclass(), in.for_field_variant<8>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCookiedata:
      proto_serde<orgproto::org::NamedProperty::CookieData, org::sem::NamedProperty::CookieData>::read(out.data().cookiedata(), in.for_field_variant<9>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kExportlatexclassoptions:
      proto_serde<orgproto::org::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions>::read(out.data().exportlatexclassoptions(), in.for_field_variant<10>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kExportlatexheader:
      proto_serde<orgproto::org::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader>::read(out.data().exportlatexheader(), in.for_field_variant<11>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kExportlatexcompiler:
      proto_serde<orgproto::org::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler>::read(out.data().exportlatexcompiler(), in.for_field_variant<12>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kOrdered:
      proto_serde<orgproto::org::NamedProperty::Ordered, org::sem::NamedProperty::Ordered>::read(out.data().ordered(), in.for_field_variant<13>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kEffort:
      proto_serde<orgproto::org::NamedProperty::Effort, org::sem::NamedProperty::Effort>::read(out.data().effort(), in.for_field_variant<14>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kVisibility:
      proto_serde<orgproto::org::NamedProperty::Visibility, org::sem::NamedProperty::Visibility>::read(out.data().visibility(), in.for_field_variant<15>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kExportoptions:
      proto_serde<orgproto::org::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions>::read(out.data().exportoptions(), in.for_field_variant<16>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kBlocker:
      proto_serde<orgproto::org::NamedProperty::Blocker, org::sem::NamedProperty::Blocker>::read(out.data().blocker(), in.for_field_variant<17>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kUnnumbered:
      proto_serde<orgproto::org::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered>::read(out.data().unnumbered(), in.for_field_variant<18>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCreated:
      proto_serde<orgproto::org::NamedProperty::Created, org::sem::NamedProperty::Created>::read(out.data().created(), in.for_field_variant<19>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kRadioid:
      proto_serde<orgproto::org::NamedProperty::RadioId, org::sem::NamedProperty::RadioId>::read(out.data().radioid(), in.for_field_variant<20>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kHashtagdef:
      proto_serde<orgproto::org::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef>::read(out.data().hashtagdef(), in.for_field_variant<21>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCustomargs:
      proto_serde<orgproto::org::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs>::read(out.data().customargs(), in.for_field_variant<22>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCustomraw:
      proto_serde<orgproto::org::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw>::read(out.data().customraw(), in.for_field_variant<23>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCustomsubtreejson:
      proto_serde<orgproto::org::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson>::read(out.data().customsubtreejson(), in.for_field_variant<24>(&org::sem::NamedProperty::data));
      break;
    case ::orgproto::org::NamedProperty::Data::kCustomsubtreeflags:
      proto_serde<orgproto::org::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags>::read(out.data().customsubtreeflags(), in.for_field_variant<25>(&org::sem::NamedProperty::data));
      break;
  }
}

void proto_serde<::orgproto::org::None, org::sem::None>::write(::orgproto::org::None* out, org::sem::None const& in) {
  proto_serde<::orgproto::org::None, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::None, org::sem::None>::read(::orgproto::org::None const& out, proto_write_accessor<org::sem::None> in) {
  proto_serde<::orgproto::org::None, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::ErrorItem, org::sem::ErrorItem>::write(::orgproto::org::ErrorItem* out, org::sem::ErrorItem const& in) {
  proto_serde<::orgproto::org::ErrorItem, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_message(), in.message);
  if (in.function) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    out->set_line(*in.line);
  }
}

void proto_serde<::orgproto::org::ErrorItem, org::sem::ErrorItem>::read(::orgproto::org::ErrorItem const& out, proto_write_accessor<org::sem::ErrorItem> in) {
  proto_serde<::orgproto::org::ErrorItem, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.message(), in.for_field(&org::sem::ErrorItem::message));
  if (out.has_function()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.function(), in.for_field(&org::sem::ErrorItem::function));
  }
  if (out.has_line()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.line(), in.for_field(&org::sem::ErrorItem::line));
  }
}

void proto_serde<::orgproto::org::ErrorGroup, org::sem::ErrorGroup>::write(::orgproto::org::ErrorGroup* out, org::sem::ErrorGroup const& in) {
  proto_serde<::orgproto::org::ErrorGroup, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::ErrorItem>, hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::write(out->mutable_diagnostics(), in.diagnostics);
  if (in.function) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    out->set_line(*in.line);
  }
}

void proto_serde<::orgproto::org::ErrorGroup, org::sem::ErrorGroup>::read(::orgproto::org::ErrorGroup const& out, proto_write_accessor<org::sem::ErrorGroup> in) {
  proto_serde<::orgproto::org::ErrorGroup, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::ErrorItem>, hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>::read(out.diagnostics(), in.for_field(&org::sem::ErrorGroup::diagnostics));
  if (out.has_function()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.function(), in.for_field(&org::sem::ErrorGroup::function));
  }
  if (out.has_line()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.line(), in.for_field(&org::sem::ErrorGroup::line));
  }
}

void proto_serde<::orgproto::org::StmtList, org::sem::StmtList>::write(::orgproto::org::StmtList* out, org::sem::StmtList const& in) {
  proto_serde<::orgproto::org::StmtList, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::StmtList, org::sem::StmtList>::read(::orgproto::org::StmtList const& out, proto_write_accessor<org::sem::StmtList> in) {
  proto_serde<::orgproto::org::StmtList, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Empty, org::sem::Empty>::write(::orgproto::org::Empty* out, org::sem::Empty const& in) {
  proto_serde<::orgproto::org::Empty, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Empty, org::sem::Empty>::read(::orgproto::org::Empty const& out, proto_write_accessor<org::sem::Empty> in) {
  proto_serde<::orgproto::org::Empty, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::CmdCaption, org::sem::CmdCaption>::write(::orgproto::org::CmdCaption* out, org::sem::CmdCaption const& in) {
  proto_serde<::orgproto::org::CmdCaption, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdCaption, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdCaption, org::sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::org::CmdCaption, org::sem::CmdCaption>::read(::orgproto::org::CmdCaption const& out, proto_write_accessor<org::sem::CmdCaption> in) {
  proto_serde<::orgproto::org::CmdCaption, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdCaption, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdCaption, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdCaption::text));
}

void proto_serde<::orgproto::org::CmdColumns, org::sem::CmdColumns>::write(::orgproto::org::CmdColumns* out, org::sem::CmdColumns const& in) {
  proto_serde<::orgproto::org::CmdColumns, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdColumns, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdColumns, org::sem::Org>::write(out, in);
  proto_serde<orgproto::org::ColumnView, org::sem::ColumnView>::write(out->mutable_view(), in.view);
}

void proto_serde<::orgproto::org::CmdColumns, org::sem::CmdColumns>::read(::orgproto::org::CmdColumns const& out, proto_write_accessor<org::sem::CmdColumns> in) {
  proto_serde<::orgproto::org::CmdColumns, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdColumns, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdColumns, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::ColumnView, org::sem::ColumnView>::read(out.view(), in.for_field(&org::sem::CmdColumns::view));
}

void proto_serde<::orgproto::org::CmdName, org::sem::CmdName>::write(::orgproto::org::CmdName* out, org::sem::CmdName const& in) {
  proto_serde<::orgproto::org::CmdName, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdName, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdName, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::CmdName, org::sem::CmdName>::read(::orgproto::org::CmdName const& out, proto_write_accessor<org::sem::CmdName> in) {
  proto_serde<::orgproto::org::CmdName, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdName, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdName, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdName::name));
}

void proto_serde<::orgproto::org::CmdCustomArgs, org::sem::CmdCustomArgs>::write(::orgproto::org::CmdCustomArgs* out, org::sem::CmdCustomArgs const& in) {
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
}

void proto_serde<::orgproto::org::CmdCustomArgs, org::sem::CmdCustomArgs>::read(::orgproto::org::CmdCustomArgs const& out, proto_write_accessor<org::sem::CmdCustomArgs> in) {
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdCustomArgs, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomArgs::name));
  in.for_field(&org::sem::CmdCustomArgs::isAttached).get() = out.isattached();
}

void proto_serde<::orgproto::org::CmdCustomRaw, org::sem::CmdCustomRaw>::write(::orgproto::org::CmdCustomRaw* out, org::sem::CmdCustomRaw const& in) {
  proto_serde<::orgproto::org::CmdCustomRaw, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdCustomRaw, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::CmdCustomRaw, org::sem::CmdCustomRaw>::read(::orgproto::org::CmdCustomRaw const& out, proto_write_accessor<org::sem::CmdCustomRaw> in) {
  proto_serde<::orgproto::org::CmdCustomRaw, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdCustomRaw, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomRaw::name));
  in.for_field(&org::sem::CmdCustomRaw::isAttached).get() = out.isattached();
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&org::sem::CmdCustomRaw::text));
}

void proto_serde<::orgproto::org::CmdCustomText, org::sem::CmdCustomText>::write(::orgproto::org::CmdCustomText* out, org::sem::CmdCustomText const& in) {
  proto_serde<::orgproto::org::CmdCustomText, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdCustomText, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  if (!in.text.isNil()) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::org::CmdCustomText, org::sem::CmdCustomText>::read(::orgproto::org::CmdCustomText const& out, proto_write_accessor<org::sem::CmdCustomText> in) {
  proto_serde<::orgproto::org::CmdCustomText, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdCustomText, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::CmdCustomText::name));
  in.for_field(&org::sem::CmdCustomText::isAttached).get() = out.isattached();
  proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.text(), in.for_field(&org::sem::CmdCustomText::text));
}

void proto_serde<::orgproto::org::CmdResults, org::sem::CmdResults>::write(::orgproto::org::CmdResults* out, org::sem::CmdResults const& in) {
  proto_serde<::orgproto::org::CmdResults, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdResults, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdResults, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::CmdResults, org::sem::CmdResults>::read(::orgproto::org::CmdResults const& out, proto_write_accessor<org::sem::CmdResults> in) {
  proto_serde<::orgproto::org::CmdResults, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdResults, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdResults, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::CmdTblfm, org::sem::CmdTblfm>::write(::orgproto::org::CmdTblfm* out, org::sem::CmdTblfm const& in) {
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Org>::write(out, in);
  proto_serde<orgproto::org::Tblfm, org::sem::Tblfm>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::org::CmdTblfm, org::sem::CmdTblfm>::read(::orgproto::org::CmdTblfm const& out, proto_write_accessor<org::sem::CmdTblfm> in) {
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::Tblfm, org::sem::Tblfm>::read(out.expr(), in.for_field(&org::sem::CmdTblfm::expr));
}

void proto_serde<::orgproto::org::HashTag, org::sem::HashTag>::write(::orgproto::org::HashTag* out, org::sem::HashTag const& in) {
  proto_serde<::orgproto::org::HashTag, org::sem::Org>::write(out, in);
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::HashTag, org::sem::HashTag>::read(::orgproto::org::HashTag const& out, proto_write_accessor<org::sem::HashTag> in) {
  proto_serde<::orgproto::org::HashTag, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::HashTagText, org::sem::HashTagText>::read(out.text(), in.for_field(&org::sem::HashTag::text));
}

void proto_serde<::orgproto::org::InlineFootnote, org::sem::InlineFootnote>::write(::orgproto::org::InlineFootnote* out, org::sem::InlineFootnote const& in) {
  proto_serde<::orgproto::org::InlineFootnote, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, org::sem::SemId<org::sem::Org>>::write(out->mutable_definition(), *in.definition);
  }
}

void proto_serde<::orgproto::org::InlineFootnote, org::sem::InlineFootnote>::read(::orgproto::org::InlineFootnote const& out, proto_write_accessor<org::sem::InlineFootnote> in) {
  proto_serde<::orgproto::org::InlineFootnote, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.tag(), in.for_field(&org::sem::InlineFootnote::tag));
  if (out.has_definition()) {
    proto_serde<hstd::Opt<orgproto::AnyNode>, hstd::Opt<org::sem::SemId<org::sem::Org>>>::read(out.definition(), in.for_field(&org::sem::InlineFootnote::definition));
  }
}

void proto_serde<::orgproto::org::InlineExport, org::sem::InlineExport>::write(::orgproto::org::InlineExport* out, org::sem::InlineExport const& in) {
  proto_serde<::orgproto::org::InlineExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::org::InlineExport, org::sem::InlineExport>::read(::orgproto::org::InlineExport const& out, proto_write_accessor<org::sem::InlineExport> in) {
  proto_serde<::orgproto::org::InlineExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::InlineExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::InlineExport::content));
}

void proto_serde<::orgproto::org::Time::Repeat, org::sem::Time::Repeat>::write(::orgproto::org::Time::Repeat* out, org::sem::Time::Repeat const& in) {
  out->set_mode(static_cast<orgproto::org_Time_Repeat_Mode>(in.mode));
  out->set_period(static_cast<orgproto::org_Time_Repeat_Period>(in.period));
  out->set_count(in.count);
}

void proto_serde<::orgproto::org::Time::Repeat, org::sem::Time::Repeat>::read(::orgproto::org::Time::Repeat const& out, proto_write_accessor<org::sem::Time::Repeat> in) {
  in.for_field(&org::sem::Time::Repeat::mode).get() = static_cast<org::sem::Time::Repeat::Mode>(out.mode());
  in.for_field(&org::sem::Time::Repeat::period).get() = static_cast<org::sem::Time::Repeat::Period>(out.period());
  in.for_field(&org::sem::Time::Repeat::count).get() = out.count();
}

void proto_serde<::orgproto::org::Time::Static, org::sem::Time::Static>::write(::orgproto::org::Time::Static* out, org::sem::Time::Static const& in) {
  if (in.repeat) {
    proto_serde<orgproto::org::Time::Repeat, org::sem::Time::Repeat>::write(out->mutable_repeat(), *in.repeat);
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::org::Time::Static, org::sem::Time::Static>::read(::orgproto::org::Time::Static const& out, proto_write_accessor<org::sem::Time::Static> in) {
  if (out.has_repeat()) {
    proto_serde<hstd::Opt<orgproto::org::Time::Repeat>, hstd::Opt<org::sem::Time::Repeat>>::read(out.repeat(), in.for_field(&org::sem::Time::Static::repeat));
  }
  proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::read(out.time(), in.for_field(&org::sem::Time::Static::time));
}

void proto_serde<::orgproto::org::Time::Dynamic, org::sem::Time::Dynamic>::write(::orgproto::org::Time::Dynamic* out, org::sem::Time::Dynamic const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::org::Time::Dynamic, org::sem::Time::Dynamic>::read(::orgproto::org::Time::Dynamic const& out, proto_write_accessor<org::sem::Time::Dynamic> in) {
  proto_serde<std::string, hstd::Str>::read(out.expr(), in.for_field(&org::sem::Time::Dynamic::expr));
}

void proto_serde<::orgproto::org::Time, org::sem::Time>::write(::orgproto::org::Time* out, org::sem::Time const& in) {
  proto_serde<::orgproto::org::Time, org::sem::Org>::write(out, in);
  out->set_isactive(in.isActive);
  switch (in.time.index()) {
    case 0:
      proto_serde<orgproto::org::Time::Static, org::sem::Time::Static>::write(out->mutable_time()->mutable_static_(), std::get<0>(in.time));
      break;
    case 1:
      proto_serde<orgproto::org::Time::Dynamic, org::sem::Time::Dynamic>::write(out->mutable_time()->mutable_dynamic(), std::get<1>(in.time));
      break;
  }
}

void proto_serde<::orgproto::org::Time, org::sem::Time>::read(::orgproto::org::Time const& out, proto_write_accessor<org::sem::Time> in) {
  proto_serde<::orgproto::org::Time, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Time::isActive).get() = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::org::Time::TimeVariant::kStatic:
      proto_serde<orgproto::org::Time::Static, org::sem::Time::Static>::read(out.time().static_(), in.for_field_variant<0>(&org::sem::Time::time));
      break;
    case ::orgproto::org::Time::TimeVariant::kDynamic:
      proto_serde<orgproto::org::Time::Dynamic, org::sem::Time::Dynamic>::read(out.time().dynamic(), in.for_field_variant<1>(&org::sem::Time::time));
      break;
  }
}

void proto_serde<::orgproto::org::TimeRange, org::sem::TimeRange>::write(::orgproto::org::TimeRange* out, org::sem::TimeRange const& in) {
  proto_serde<::orgproto::org::TimeRange, org::sem::Org>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::org::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (!in.to.isNil()) {
    proto_serde<orgproto::org::Time, org::sem::SemId<org::sem::Time>>::write(out->mutable_to(), in.to);
  }
}

void proto_serde<::orgproto::org::TimeRange, org::sem::TimeRange>::read(::orgproto::org::TimeRange const& out, proto_write_accessor<org::sem::TimeRange> in) {
  proto_serde<::orgproto::org::TimeRange, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::Time, org::sem::SemId<org::sem::Time>>::read(out.from(), in.for_field(&org::sem::TimeRange::from));
  proto_serde<orgproto::org::Time, org::sem::SemId<org::sem::Time>>::read(out.to(), in.for_field(&org::sem::TimeRange::to));
}

void proto_serde<::orgproto::org::Macro, org::sem::Macro>::write(::orgproto::org::Macro* out, org::sem::Macro const& in) {
  proto_serde<::orgproto::org::Macro, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void proto_serde<::orgproto::org::Macro, org::sem::Macro>::read(::orgproto::org::Macro const& out, proto_write_accessor<org::sem::Macro> in) {
  proto_serde<::orgproto::org::Macro, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Macro::name));
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Macro::attrs));
}

void proto_serde<::orgproto::org::Symbol::Param, org::sem::Symbol::Param>::write(::orgproto::org::Symbol::Param* out, org::sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::org::Symbol::Param, org::sem::Symbol::Param>::read(::orgproto::org::Symbol::Param const& out, proto_write_accessor<org::sem::Symbol::Param> in) {
  if (out.has_key()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.key(), in.for_field(&org::sem::Symbol::Param::key));
  }
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&org::sem::Symbol::Param::value));
}

void proto_serde<::orgproto::org::Symbol, org::sem::Symbol>::write(::orgproto::org::Symbol* out, org::sem::Symbol const& in) {
  proto_serde<::orgproto::org::Symbol, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Symbol::Param>, hstd::Vec<org::sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, hstd::Vec<org::sem::SemId<org::sem::Org>>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::org::Symbol, org::sem::Symbol>::read(::orgproto::org::Symbol const& out, proto_write_accessor<org::sem::Symbol> in) {
  proto_serde<::orgproto::org::Symbol, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Symbol::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Symbol::Param>, hstd::Vec<org::sem::Symbol::Param>>::read(out.parameters(), in.for_field(&org::sem::Symbol::parameters));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, hstd::Vec<org::sem::SemId<org::sem::Org>>>::read(out.positional(), in.for_field(&org::sem::Symbol::positional));
}

void proto_serde<::orgproto::org::Escaped, org::sem::Escaped>::write(::orgproto::org::Escaped* out, org::sem::Escaped const& in) {
  proto_serde<::orgproto::org::Escaped, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Escaped, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Escaped, org::sem::Escaped>::read(::orgproto::org::Escaped const& out, proto_write_accessor<org::sem::Escaped> in) {
  proto_serde<::orgproto::org::Escaped, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Escaped, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Newline, org::sem::Newline>::write(::orgproto::org::Newline* out, org::sem::Newline const& in) {
  proto_serde<::orgproto::org::Newline, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Newline, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Newline, org::sem::Newline>::read(::orgproto::org::Newline const& out, proto_write_accessor<org::sem::Newline> in) {
  proto_serde<::orgproto::org::Newline, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Newline, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Space, org::sem::Space>::write(::orgproto::org::Space* out, org::sem::Space const& in) {
  proto_serde<::orgproto::org::Space, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Space, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Space, org::sem::Space>::read(::orgproto::org::Space const& out, proto_write_accessor<org::sem::Space> in) {
  proto_serde<::orgproto::org::Space, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Space, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Word, org::sem::Word>::write(::orgproto::org::Word* out, org::sem::Word const& in) {
  proto_serde<::orgproto::org::Word, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Word, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Word, org::sem::Word>::read(::orgproto::org::Word const& out, proto_write_accessor<org::sem::Word> in) {
  proto_serde<::orgproto::org::Word, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Word, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::AtMention, org::sem::AtMention>::write(::orgproto::org::AtMention* out, org::sem::AtMention const& in) {
  proto_serde<::orgproto::org::AtMention, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::AtMention, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::AtMention, org::sem::AtMention>::read(::orgproto::org::AtMention const& out, proto_write_accessor<org::sem::AtMention> in) {
  proto_serde<::orgproto::org::AtMention, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::AtMention, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::RawText, org::sem::RawText>::write(::orgproto::org::RawText* out, org::sem::RawText const& in) {
  proto_serde<::orgproto::org::RawText, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::RawText, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::RawText, org::sem::RawText>::read(::orgproto::org::RawText const& out, proto_write_accessor<org::sem::RawText> in) {
  proto_serde<::orgproto::org::RawText, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::RawText, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Punctuation, org::sem::Punctuation>::write(::orgproto::org::Punctuation* out, org::sem::Punctuation const& in) {
  proto_serde<::orgproto::org::Punctuation, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Punctuation, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Punctuation, org::sem::Punctuation>::read(::orgproto::org::Punctuation const& out, proto_write_accessor<org::sem::Punctuation> in) {
  proto_serde<::orgproto::org::Punctuation, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Punctuation, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Placeholder, org::sem::Placeholder>::write(::orgproto::org::Placeholder* out, org::sem::Placeholder const& in) {
  proto_serde<::orgproto::org::Placeholder, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::Placeholder, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Placeholder, org::sem::Placeholder>::read(::orgproto::org::Placeholder const& out, proto_write_accessor<org::sem::Placeholder> in) {
  proto_serde<::orgproto::org::Placeholder, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::Placeholder, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BigIdent, org::sem::BigIdent>::write(::orgproto::org::BigIdent* out, org::sem::BigIdent const& in) {
  proto_serde<::orgproto::org::BigIdent, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::BigIdent, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BigIdent, org::sem::BigIdent>::read(::orgproto::org::BigIdent const& out, proto_write_accessor<org::sem::BigIdent> in) {
  proto_serde<::orgproto::org::BigIdent, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::BigIdent, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::TextTarget, org::sem::TextTarget>::write(::orgproto::org::TextTarget* out, org::sem::TextTarget const& in) {
  proto_serde<::orgproto::org::TextTarget, org::sem::Leaf>::write(out, in);
  proto_serde<::orgproto::org::TextTarget, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::TextTarget, org::sem::TextTarget>::read(::orgproto::org::TextTarget const& out, proto_write_accessor<org::sem::TextTarget> in) {
  proto_serde<::orgproto::org::TextTarget, org::sem::Leaf>::read(out, in.as<org::sem::Leaf>());
  proto_serde<::orgproto::org::TextTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Bold, org::sem::Bold>::write(::orgproto::org::Bold* out, org::sem::Bold const& in) {
  proto_serde<::orgproto::org::Bold, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Bold, org::sem::Bold>::read(::orgproto::org::Bold const& out, proto_write_accessor<org::sem::Bold> in) {
  proto_serde<::orgproto::org::Bold, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Underline, org::sem::Underline>::write(::orgproto::org::Underline* out, org::sem::Underline const& in) {
  proto_serde<::orgproto::org::Underline, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Underline, org::sem::Underline>::read(::orgproto::org::Underline const& out, proto_write_accessor<org::sem::Underline> in) {
  proto_serde<::orgproto::org::Underline, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Monospace, org::sem::Monospace>::write(::orgproto::org::Monospace* out, org::sem::Monospace const& in) {
  proto_serde<::orgproto::org::Monospace, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Monospace, org::sem::Monospace>::read(::orgproto::org::Monospace const& out, proto_write_accessor<org::sem::Monospace> in) {
  proto_serde<::orgproto::org::Monospace, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::MarkQuote, org::sem::MarkQuote>::write(::orgproto::org::MarkQuote* out, org::sem::MarkQuote const& in) {
  proto_serde<::orgproto::org::MarkQuote, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::MarkQuote, org::sem::MarkQuote>::read(::orgproto::org::MarkQuote const& out, proto_write_accessor<org::sem::MarkQuote> in) {
  proto_serde<::orgproto::org::MarkQuote, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Verbatim, org::sem::Verbatim>::write(::orgproto::org::Verbatim* out, org::sem::Verbatim const& in) {
  proto_serde<::orgproto::org::Verbatim, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Verbatim, org::sem::Verbatim>::read(::orgproto::org::Verbatim const& out, proto_write_accessor<org::sem::Verbatim> in) {
  proto_serde<::orgproto::org::Verbatim, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Italic, org::sem::Italic>::write(::orgproto::org::Italic* out, org::sem::Italic const& in) {
  proto_serde<::orgproto::org::Italic, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Italic, org::sem::Italic>::read(::orgproto::org::Italic const& out, proto_write_accessor<org::sem::Italic> in) {
  proto_serde<::orgproto::org::Italic, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Strike, org::sem::Strike>::write(::orgproto::org::Strike* out, org::sem::Strike const& in) {
  proto_serde<::orgproto::org::Strike, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Strike, org::sem::Strike>::read(::orgproto::org::Strike const& out, proto_write_accessor<org::sem::Strike> in) {
  proto_serde<::orgproto::org::Strike, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Par, org::sem::Par>::write(::orgproto::org::Par* out, org::sem::Par const& in) {
  proto_serde<::orgproto::org::Par, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Par, org::sem::Par>::read(::orgproto::org::Par const& out, proto_write_accessor<org::sem::Par> in) {
  proto_serde<::orgproto::org::Par, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::RadioTarget, org::sem::RadioTarget>::write(::orgproto::org::RadioTarget* out, org::sem::RadioTarget const& in) {
  proto_serde<::orgproto::org::RadioTarget, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_words(), in.words);
}

void proto_serde<::orgproto::org::RadioTarget, org::sem::RadioTarget>::read(::orgproto::org::RadioTarget const& out, proto_write_accessor<org::sem::RadioTarget> in) {
  proto_serde<::orgproto::org::RadioTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.words(), in.for_field(&org::sem::RadioTarget::words));
}

void proto_serde<::orgproto::org::Latex, org::sem::Latex>::write(::orgproto::org::Latex* out, org::sem::Latex const& in) {
  proto_serde<::orgproto::org::Latex, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Latex, org::sem::Latex>::read(::orgproto::org::Latex const& out, proto_write_accessor<org::sem::Latex> in) {
  proto_serde<::orgproto::org::Latex, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::Link, org::sem::Link>::write(::orgproto::org::Link* out, org::sem::Link const& in) {
  proto_serde<::orgproto::org::Link, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::Link, org::sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<orgproto::org::LinkTarget, org::sem::LinkTarget>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::Link, org::sem::Link>::read(::orgproto::org::Link const& out, proto_write_accessor<org::sem::Link> in) {
  proto_serde<::orgproto::org::Link, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Link, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Link::description));
  }
  proto_serde<orgproto::org::LinkTarget, org::sem::LinkTarget>::read(out.target(), in.for_field(&org::sem::Link::target));
}

void proto_serde<::orgproto::org::BlockCenter, org::sem::BlockCenter>::write(::orgproto::org::BlockCenter* out, org::sem::BlockCenter const& in) {
  proto_serde<::orgproto::org::BlockCenter, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockCenter, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockCenter, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockCenter, org::sem::BlockCenter>::read(::orgproto::org::BlockCenter const& out, proto_write_accessor<org::sem::BlockCenter> in) {
  proto_serde<::orgproto::org::BlockCenter, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockCenter, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockCenter, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockQuote, org::sem::BlockQuote>::write(::orgproto::org::BlockQuote* out, org::sem::BlockQuote const& in) {
  proto_serde<::orgproto::org::BlockQuote, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockQuote, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockQuote, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockQuote, org::sem::BlockQuote>::read(::orgproto::org::BlockQuote const& out, proto_write_accessor<org::sem::BlockQuote> in) {
  proto_serde<::orgproto::org::BlockQuote, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockQuote, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockQuote, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockComment, org::sem::BlockComment>::write(::orgproto::org::BlockComment* out, org::sem::BlockComment const& in) {
  proto_serde<::orgproto::org::BlockComment, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockComment, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockComment, org::sem::BlockComment>::read(::orgproto::org::BlockComment const& out, proto_write_accessor<org::sem::BlockComment> in) {
  proto_serde<::orgproto::org::BlockComment, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockComment, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockVerse, org::sem::BlockVerse>::write(::orgproto::org::BlockVerse* out, org::sem::BlockVerse const& in) {
  proto_serde<::orgproto::org::BlockVerse, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockVerse, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockVerse, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockVerse, org::sem::BlockVerse>::read(::orgproto::org::BlockVerse const& out, proto_write_accessor<org::sem::BlockVerse> in) {
  proto_serde<::orgproto::org::BlockVerse, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockVerse, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockVerse, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::BlockDynamicFallback>::write(::orgproto::org::BlockDynamicFallback* out, org::sem::BlockDynamicFallback const& in) {
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::BlockDynamicFallback>::read(::orgproto::org::BlockDynamicFallback const& out, proto_write_accessor<org::sem::BlockDynamicFallback> in) {
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::BlockDynamicFallback::name));
}

void proto_serde<::orgproto::org::BlockExample, org::sem::BlockExample>::write(::orgproto::org::BlockExample* out, org::sem::BlockExample const& in) {
  proto_serde<::orgproto::org::BlockExample, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockExample, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockExample, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockExample, org::sem::BlockExample>::read(::orgproto::org::BlockExample const& out, proto_write_accessor<org::sem::BlockExample> in) {
  proto_serde<::orgproto::org::BlockExample, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockExample, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockExample, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockExport, org::sem::BlockExport>::write(::orgproto::org::BlockExport* out, org::sem::BlockExport const& in) {
  proto_serde<::orgproto::org::BlockExport, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockExport, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::org::BlockExport, org::sem::BlockExport>::read(::orgproto::org::BlockExport const& out, proto_write_accessor<org::sem::BlockExport> in) {
  proto_serde<::orgproto::org::BlockExport, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockExport, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::BlockExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::BlockExport::content));
}

void proto_serde<::orgproto::org::BlockAdmonition, org::sem::BlockAdmonition>::write(::orgproto::org::BlockAdmonition* out, org::sem::BlockAdmonition const& in) {
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::BlockAdmonition, org::sem::BlockAdmonition>::read(::orgproto::org::BlockAdmonition const& out, proto_write_accessor<org::sem::BlockAdmonition> in) {
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockAdmonition, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::BlockCode, org::sem::BlockCode>::write(::orgproto::org::BlockCode* out, org::sem::BlockCode const& in) {
  proto_serde<::orgproto::org::BlockCode, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::BlockCode, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::BlockCode, org::sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeSwitch>, hstd::Vec<org::sem::BlockCodeSwitch>>::write(out->mutable_switches(), in.switches);
  out->set_exports(static_cast<orgproto::BlockCodeExports>(in.exports));
  if (in.result) {
    proto_serde<orgproto::org::BlockCodeEvalResult, org::sem::BlockCodeEvalResult>::write(out->mutable_result(), *in.result);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeLine>, hstd::Vec<org::sem::BlockCodeLine>>::write(out->mutable_lines(), in.lines);
  out->set_cache(in.cache);
  out->set_eval(in.eval);
  out->set_noweb(in.noweb);
  out->set_hlines(in.hlines);
  out->set_tangle(in.tangle);
}

void proto_serde<::orgproto::org::BlockCode, org::sem::BlockCode>::read(::orgproto::org::BlockCode const& out, proto_write_accessor<org::sem::BlockCode> in) {
  proto_serde<::orgproto::org::BlockCode, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::BlockCode, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::BlockCode, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_lang()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.lang(), in.for_field(&org::sem::BlockCode::lang));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeSwitch>, hstd::Vec<org::sem::BlockCodeSwitch>>::read(out.switches(), in.for_field(&org::sem::BlockCode::switches));
  in.for_field(&org::sem::BlockCode::exports).get() = static_cast<BlockCodeExports>(out.exports());
  if (out.has_result()) {
    proto_serde<hstd::Opt<orgproto::org::BlockCodeEvalResult>, hstd::Opt<org::sem::BlockCodeEvalResult>>::read(out.result(), in.for_field(&org::sem::BlockCode::result));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::BlockCodeLine>, hstd::Vec<org::sem::BlockCodeLine>>::read(out.lines(), in.for_field(&org::sem::BlockCode::lines));
  in.for_field(&org::sem::BlockCode::cache).get() = out.cache();
  in.for_field(&org::sem::BlockCode::eval).get() = out.eval();
  in.for_field(&org::sem::BlockCode::noweb).get() = out.noweb();
  in.for_field(&org::sem::BlockCode::hlines).get() = out.hlines();
  in.for_field(&org::sem::BlockCode::tangle).get() = out.tangle();
}

void proto_serde<::orgproto::org::SubtreeLog, org::sem::SubtreeLog>::write(::orgproto::org::SubtreeLog* out, org::sem::SubtreeLog const& in) {
  proto_serde<::orgproto::org::SubtreeLog, org::sem::Org>::write(out, in);
  proto_serde<orgproto::org::SubtreeLogHead, org::sem::SubtreeLogHead>::write(out->mutable_head(), in.head);
  if (in.desc) {
    proto_serde<orgproto::org::StmtList, org::sem::SemId<org::sem::StmtList>>::write(out->mutable_desc(), *in.desc);
  }
}

void proto_serde<::orgproto::org::SubtreeLog, org::sem::SubtreeLog>::read(::orgproto::org::SubtreeLog const& out, proto_write_accessor<org::sem::SubtreeLog> in) {
  proto_serde<::orgproto::org::SubtreeLog, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::org::SubtreeLogHead, org::sem::SubtreeLogHead>::read(out.head(), in.for_field(&org::sem::SubtreeLog::head));
  if (out.has_desc()) {
    proto_serde<hstd::Opt<orgproto::org::StmtList>, hstd::Opt<org::sem::SemId<org::sem::StmtList>>>::read(out.desc(), in.for_field(&org::sem::SubtreeLog::desc));
  }
}

void proto_serde<::orgproto::org::Subtree, org::sem::Subtree>::write(::orgproto::org::Subtree* out, org::sem::Subtree const& in) {
  proto_serde<::orgproto::org::Subtree, org::sem::Org>::write(out, in);
  out->set_level(in.level);
  if (in.treeId) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_treeid(), *in.treeId);
  }
  if (in.todo) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_todo(), *in.todo);
  }
  if (in.completion) {
    proto_serde<orgproto::org::SubtreeCompletion, org::sem::SubtreeCompletion>::write(out->mutable_completion(), *in.completion);
  }
  if (in.description) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::write(out->mutable_tags(), in.tags);
  if (!in.title.isNil()) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_title(), in.title);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::write(out->mutable_logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  if (in.closed) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_closed(), *in.closed);
  }
  if (in.deadline) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_deadline(), *in.deadline);
  }
  if (in.scheduled) {
    proto_serde<orgproto::hstd::UserTime, hstd::UserTime>::write(out->mutable_scheduled(), *in.scheduled);
  }
  out->set_iscomment(in.isComment);
  out->set_isarchived(in.isArchived);
  if (in.priority) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_priority(), *in.priority);
  }
}

void proto_serde<::orgproto::org::Subtree, org::sem::Subtree>::read(::orgproto::org::Subtree const& out, proto_write_accessor<org::sem::Subtree> in) {
  proto_serde<::orgproto::org::Subtree, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Subtree::level).get() = out.level();
  if (out.has_treeid()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.treeid(), in.for_field(&org::sem::Subtree::treeId));
  }
  if (out.has_todo()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.todo(), in.for_field(&org::sem::Subtree::todo));
  }
  if (out.has_completion()) {
    proto_serde<hstd::Opt<orgproto::org::SubtreeCompletion>, hstd::Opt<org::sem::SubtreeCompletion>>::read(out.completion(), in.for_field(&org::sem::Subtree::completion));
  }
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Subtree::description));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::read(out.tags(), in.for_field(&org::sem::Subtree::tags));
  proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.title(), in.for_field(&org::sem::Subtree::title));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::read(out.logbook(), in.for_field(&org::sem::Subtree::logbook));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::Subtree::properties));
  if (out.has_closed()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.closed(), in.for_field(&org::sem::Subtree::closed));
  }
  if (out.has_deadline()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.deadline(), in.for_field(&org::sem::Subtree::deadline));
  }
  if (out.has_scheduled()) {
    proto_serde<hstd::Opt<orgproto::hstd::UserTime>, hstd::Opt<hstd::UserTime>>::read(out.scheduled(), in.for_field(&org::sem::Subtree::scheduled));
  }
  in.for_field(&org::sem::Subtree::isComment).get() = out.iscomment();
  in.for_field(&org::sem::Subtree::isArchived).get() = out.isarchived();
  if (out.has_priority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.priority(), in.for_field(&org::sem::Subtree::priority));
  }
}

void proto_serde<::orgproto::org::Cell, org::sem::Cell>::write(::orgproto::org::Cell* out, org::sem::Cell const& in) {
  proto_serde<::orgproto::org::Cell, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::Cell, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::Cell, org::sem::Org>::write(out, in);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::org::Cell, org::sem::Cell>::read(::orgproto::org::Cell const& out, proto_write_accessor<org::sem::Cell> in) {
  proto_serde<::orgproto::org::Cell, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::Cell, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Cell, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Cell::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::org::Row, org::sem::Row>::write(::orgproto::org::Row* out, org::sem::Row const& in) {
  proto_serde<::orgproto::org::Row, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::Row, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::Row, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Cell>, hstd::Vec<org::sem::SemId<org::sem::Cell>>>::write(out->mutable_cells(), in.cells);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::org::Row, org::sem::Row>::read(::orgproto::org::Row const& out, proto_write_accessor<org::sem::Row> in) {
  proto_serde<::orgproto::org::Row, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::Row, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Row, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Cell>, hstd::Vec<org::sem::SemId<org::sem::Cell>>>::read(out.cells(), in.for_field(&org::sem::Row::cells));
  in.for_field(&org::sem::Row::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::org::Table, org::sem::Table>::write(::orgproto::org::Table* out, org::sem::Table const& in) {
  proto_serde<::orgproto::org::Table, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::Table, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::Table, org::sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Row>, hstd::Vec<org::sem::SemId<org::sem::Row>>>::write(out->mutable_rows(), in.rows);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::org::Table, org::sem::Table>::read(::orgproto::org::Table const& out, proto_write_accessor<org::sem::Table> in) {
  proto_serde<::orgproto::org::Table, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::Table, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Table, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::Row>, hstd::Vec<org::sem::SemId<org::sem::Row>>>::read(out.rows(), in.for_field(&org::sem::Table::rows));
  in.for_field(&org::sem::Table::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::org::Paragraph, org::sem::Paragraph>::write(::orgproto::org::Paragraph* out, org::sem::Paragraph const& in) {
  proto_serde<::orgproto::org::Paragraph, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::Paragraph, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::Paragraph, org::sem::Paragraph>::read(::orgproto::org::Paragraph const& out, proto_write_accessor<org::sem::Paragraph> in) {
  proto_serde<::orgproto::org::Paragraph, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Paragraph, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::ColonExample, org::sem::ColonExample>::write(::orgproto::org::ColonExample* out, org::sem::ColonExample const& in) {
  proto_serde<::orgproto::org::ColonExample, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::ColonExample, org::sem::ColonExample>::read(::orgproto::org::ColonExample const& out, proto_write_accessor<org::sem::ColonExample> in) {
  proto_serde<::orgproto::org::ColonExample, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::CmdAttr, org::sem::CmdAttr>::write(::orgproto::org::CmdAttr* out, org::sem::CmdAttr const& in) {
  proto_serde<::orgproto::org::CmdAttr, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdAttr, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdAttr, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::CmdAttr, org::sem::CmdAttr>::read(::orgproto::org::CmdAttr const& out, proto_write_accessor<org::sem::CmdAttr> in) {
  proto_serde<::orgproto::org::CmdAttr, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdAttr, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdAttr, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&org::sem::CmdAttr::target));
}

void proto_serde<::orgproto::org::CmdExport, org::sem::CmdExport>::write(::orgproto::org::CmdExport* out, org::sem::CmdExport const& in) {
  proto_serde<::orgproto::org::CmdExport, org::sem::Cmd>::write(out, in);
  proto_serde<::orgproto::org::CmdExport, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::CmdExport, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<std::string, hstd::Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::org::CmdExport, org::sem::CmdExport>::read(::orgproto::org::CmdExport const& out, proto_write_accessor<org::sem::CmdExport> in) {
  proto_serde<::orgproto::org::CmdExport, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdExport, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdExport, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.exporter(), in.for_field(&org::sem::CmdExport::exporter));
  proto_serde<std::string, hstd::Str>::read(out.content(), in.for_field(&org::sem::CmdExport::content));
}

void proto_serde<::orgproto::org::Call, org::sem::Call>::write(::orgproto::org::Call* out, org::sem::Call const& in) {
  proto_serde<::orgproto::org::Call, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
  out->set_iscommand(in.isCommand);
}

void proto_serde<::orgproto::org::Call, org::sem::Call>::read(::orgproto::org::Call const& out, proto_write_accessor<org::sem::Call> in) {
  proto_serde<::orgproto::org::Call, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Call::name));
  proto_serde<orgproto::org::AttrGroup, org::sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Call::attrs));
  in.for_field(&org::sem::Call::isCommand).get() = out.iscommand();
}

void proto_serde<::orgproto::org::List, org::sem::List>::write(::orgproto::org::List* out, org::sem::List const& in) {
  proto_serde<::orgproto::org::List, org::sem::Stmt>::write(out, in);
  proto_serde<::orgproto::org::List, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::List, org::sem::List>::read(::orgproto::org::List const& out, proto_write_accessor<org::sem::List> in) {
  proto_serde<::orgproto::org::List, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::List, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::ListItem, org::sem::ListItem>::write(::orgproto::org::ListItem* out, org::sem::ListItem const& in) {
  proto_serde<::orgproto::org::ListItem, org::sem::Org>::write(out, in);
  out->set_checkbox(static_cast<orgproto::org_ListItem_Checkbox>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
  if (in.bullet) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_bullet(), *in.bullet);
  }
}

void proto_serde<::orgproto::org::ListItem, org::sem::ListItem>::read(::orgproto::org::ListItem const& out, proto_write_accessor<org::sem::ListItem> in) {
  proto_serde<::orgproto::org::ListItem, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::ListItem::checkbox).get() = static_cast<org::sem::ListItem::Checkbox>(out.checkbox());
  if (out.has_header()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.header(), in.for_field(&org::sem::ListItem::header));
  }
  if (out.has_bullet()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.bullet(), in.for_field(&org::sem::ListItem::bullet));
  }
}

void proto_serde<::orgproto::org::DocumentOptions, org::sem::DocumentOptions>::write(::orgproto::org::DocumentOptions* out, org::sem::DocumentOptions const& in) {
  proto_serde<::orgproto::org::DocumentOptions, org::sem::Org>::write(out, in);
  out->set_initialvisibility(static_cast<orgproto::InitialSubtreeVisibility>(in.initialVisibility));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  proto_serde<orgproto::org::DocumentExportConfig, org::sem::DocumentExportConfig>::write(out->mutable_exportconfig(), in.exportConfig);
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
    proto_serde<orgproto::org::ColumnView, org::sem::ColumnView>::write(out->mutable_columns(), *in.columns);
  }
}

void proto_serde<::orgproto::org::DocumentOptions, org::sem::DocumentOptions>::read(::orgproto::org::DocumentOptions const& out, proto_write_accessor<org::sem::DocumentOptions> in) {
  proto_serde<::orgproto::org::DocumentOptions, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::DocumentOptions::initialVisibility).get() = static_cast<InitialSubtreeVisibility>(out.initialvisibility());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::NamedProperty>, hstd::Vec<org::sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::DocumentOptions::properties));
  proto_serde<orgproto::org::DocumentExportConfig, org::sem::DocumentExportConfig>::read(out.exportconfig(), in.for_field(&org::sem::DocumentOptions::exportConfig));
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
    proto_serde<hstd::Opt<orgproto::org::ColumnView>, hstd::Opt<org::sem::ColumnView>>::read(out.columns(), in.for_field(&org::sem::DocumentOptions::columns));
  }
}

void proto_serde<::orgproto::org::Document, org::sem::Document>::write(::orgproto::org::Document* out, org::sem::Document const& in) {
  proto_serde<::orgproto::org::Document, org::sem::Org>::write(out, in);
  if (in.title) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_title(), *in.title);
  }
  if (in.author) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_author(), *in.author);
  }
  if (in.creator) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_creator(), *in.creator);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::write(out->mutable_filetags(), in.filetags);
  if (in.email) {
    proto_serde<orgproto::org::RawText, org::sem::SemId<org::sem::RawText>>::write(out->mutable_email(), *in.email);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_language(), in.language);
  if (!in.options.isNil()) {
    proto_serde<orgproto::org::DocumentOptions, org::sem::SemId<org::sem::DocumentOptions>>::write(out->mutable_options(), in.options);
  }
  if (in.exportFileName) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_exportfilename(), *in.exportFileName);
  }
}

void proto_serde<::orgproto::org::Document, org::sem::Document>::read(::orgproto::org::Document const& out, proto_write_accessor<org::sem::Document> in) {
  proto_serde<::orgproto::org::Document, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_title()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.title(), in.for_field(&org::sem::Document::title));
  }
  if (out.has_author()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.author(), in.for_field(&org::sem::Document::author));
  }
  if (out.has_creator()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.creator(), in.for_field(&org::sem::Document::creator));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::read(out.filetags(), in.for_field(&org::sem::Document::filetags));
  if (out.has_email()) {
    proto_serde<hstd::Opt<orgproto::org::RawText>, hstd::Opt<org::sem::SemId<org::sem::RawText>>>::read(out.email(), in.for_field(&org::sem::Document::email));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.language(), in.for_field(&org::sem::Document::language));
  proto_serde<orgproto::org::DocumentOptions, org::sem::SemId<org::sem::DocumentOptions>>::read(out.options(), in.for_field(&org::sem::Document::options));
  if (out.has_exportfilename()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.exportfilename(), in.for_field(&org::sem::Document::exportFileName));
  }
}

void proto_serde<::orgproto::org::FileTarget, org::sem::FileTarget>::write(::orgproto::org::FileTarget* out, org::sem::FileTarget const& in) {
  proto_serde<::orgproto::org::FileTarget, org::sem::Org>::write(out, in);
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

void proto_serde<::orgproto::org::FileTarget, org::sem::FileTarget>::read(::orgproto::org::FileTarget const& out, proto_write_accessor<org::sem::FileTarget> in) {
  proto_serde<::orgproto::org::FileTarget, org::sem::Org>::read(out, in.as<org::sem::Org>());
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

void proto_serde<::orgproto::org::TextSeparator, org::sem::TextSeparator>::write(::orgproto::org::TextSeparator* out, org::sem::TextSeparator const& in) {
  proto_serde<::orgproto::org::TextSeparator, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::TextSeparator, org::sem::TextSeparator>::read(::orgproto::org::TextSeparator const& out, proto_write_accessor<org::sem::TextSeparator> in) {
  proto_serde<::orgproto::org::TextSeparator, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::DocumentGroup, org::sem::DocumentGroup>::write(::orgproto::org::DocumentGroup* out, org::sem::DocumentGroup const& in) {
  proto_serde<::orgproto::org::DocumentGroup, org::sem::Org>::write(out, in);
}

void proto_serde<::orgproto::org::DocumentGroup, org::sem::DocumentGroup>::read(::orgproto::org::DocumentGroup const& out, proto_write_accessor<org::sem::DocumentGroup> in) {
  proto_serde<::orgproto::org::DocumentGroup, org::sem::Org>::read(out, in.as<org::sem::Org>());
}

void proto_serde<::orgproto::org::File::Document, org::sem::File::Document>::write(::orgproto::org::File::Document* out, org::sem::File::Document const& in) {

}

void proto_serde<::orgproto::org::File::Document, org::sem::File::Document>::read(::orgproto::org::File::Document const& out, proto_write_accessor<org::sem::File::Document> in) {

}

void proto_serde<::orgproto::org::File::Attachment, org::sem::File::Attachment>::write(::orgproto::org::File::Attachment* out, org::sem::File::Attachment const& in) {

}

void proto_serde<::orgproto::org::File::Attachment, org::sem::File::Attachment>::read(::orgproto::org::File::Attachment const& out, proto_write_accessor<org::sem::File::Attachment> in) {

}

void proto_serde<::orgproto::org::File::Source, org::sem::File::Source>::write(::orgproto::org::File::Source* out, org::sem::File::Source const& in) {

}

void proto_serde<::orgproto::org::File::Source, org::sem::File::Source>::read(::orgproto::org::File::Source const& out, proto_write_accessor<org::sem::File::Source> in) {

}

void proto_serde<::orgproto::org::File, org::sem::File>::write(::orgproto::org::File* out, org::sem::File const& in) {
  proto_serde<::orgproto::org::File, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_relpath(), in.relPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::File::Document, org::sem::File::Document>::write(out->mutable_data()->mutable_document(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::File::Attachment, org::sem::File::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::File::Source, org::sem::File::Source>::write(out->mutable_data()->mutable_source(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::File, org::sem::File>::read(::orgproto::org::File const& out, proto_write_accessor<org::sem::File> in) {
  proto_serde<::orgproto::org::File, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.relpath(), in.for_field(&org::sem::File::relPath));
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::File::absPath));
  switch (out.data().kind_case()) {
    case ::orgproto::org::File::Data::kDocument:
      proto_serde<orgproto::org::File::Document, org::sem::File::Document>::read(out.data().document(), in.for_field_variant<0>(&org::sem::File::data));
      break;
    case ::orgproto::org::File::Data::kAttachment:
      proto_serde<orgproto::org::File::Attachment, org::sem::File::Attachment>::read(out.data().attachment(), in.for_field_variant<1>(&org::sem::File::data));
      break;
    case ::orgproto::org::File::Data::kSource:
      proto_serde<orgproto::org::File::Source, org::sem::File::Source>::read(out.data().source(), in.for_field_variant<2>(&org::sem::File::data));
      break;
  }
}

void proto_serde<::orgproto::org::Directory, org::sem::Directory>::write(::orgproto::org::Directory* out, org::sem::Directory const& in) {
  proto_serde<::orgproto::org::Directory, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_relpath(), in.relPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
}

void proto_serde<::orgproto::org::Directory, org::sem::Directory>::read(::orgproto::org::Directory const& out, proto_write_accessor<org::sem::Directory> in) {
  proto_serde<::orgproto::org::Directory, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.relpath(), in.for_field(&org::sem::Directory::relPath));
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::Directory::absPath));
}

void proto_serde<::orgproto::org::Symlink, org::sem::Symlink>::write(::orgproto::org::Symlink* out, org::sem::Symlink const& in) {
  proto_serde<::orgproto::org::Symlink, org::sem::Org>::write(out, in);
  out->set_isdirectory(in.isDirectory);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
}

void proto_serde<::orgproto::org::Symlink, org::sem::Symlink>::read(::orgproto::org::Symlink const& out, proto_write_accessor<org::sem::Symlink> in) {
  proto_serde<::orgproto::org::Symlink, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Symlink::isDirectory).get() = out.isdirectory();
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::Symlink::absPath));
}

void proto_serde<::orgproto::org::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase>::write(::orgproto::org::CmdInclude::IncludeBase* out, org::sem::CmdInclude::IncludeBase const& in) {

}

void proto_serde<::orgproto::org::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase>::read(::orgproto::org::CmdInclude::IncludeBase const& out, proto_write_accessor<org::sem::CmdInclude::IncludeBase> in) {

}

void proto_serde<::orgproto::org::CmdInclude::Example, org::sem::CmdInclude::Example>::write(::orgproto::org::CmdInclude::Example* out, org::sem::CmdInclude::Example const& in) {

}

void proto_serde<::orgproto::org::CmdInclude::Example, org::sem::CmdInclude::Example>::read(::orgproto::org::CmdInclude::Example const& out, proto_write_accessor<org::sem::CmdInclude::Example> in) {

}

void proto_serde<::orgproto::org::CmdInclude::Export, org::sem::CmdInclude::Export>::write(::orgproto::org::CmdInclude::Export* out, org::sem::CmdInclude::Export const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void proto_serde<::orgproto::org::CmdInclude::Export, org::sem::CmdInclude::Export>::read(::orgproto::org::CmdInclude::Export const& out, proto_write_accessor<org::sem::CmdInclude::Export> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&org::sem::CmdInclude::Export::language));
}

void proto_serde<::orgproto::org::CmdInclude::Custom, org::sem::CmdInclude::Custom>::write(::orgproto::org::CmdInclude::Custom* out, org::sem::CmdInclude::Custom const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_blockname(), in.blockName);
}

void proto_serde<::orgproto::org::CmdInclude::Custom, org::sem::CmdInclude::Custom>::read(::orgproto::org::CmdInclude::Custom const& out, proto_write_accessor<org::sem::CmdInclude::Custom> in) {
  proto_serde<std::string, hstd::Str>::read(out.blockname(), in.for_field(&org::sem::CmdInclude::Custom::blockName));
}

void proto_serde<::orgproto::org::CmdInclude::Src, org::sem::CmdInclude::Src>::write(::orgproto::org::CmdInclude::Src* out, org::sem::CmdInclude::Src const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void proto_serde<::orgproto::org::CmdInclude::Src, org::sem::CmdInclude::Src>::read(::orgproto::org::CmdInclude::Src const& out, proto_write_accessor<org::sem::CmdInclude::Src> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&org::sem::CmdInclude::Src::language));
}

void proto_serde<::orgproto::org::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::write(::orgproto::org::CmdInclude::OrgDocument* out, org::sem::CmdInclude::OrgDocument const& in) {
  if (in.onlyContent) {
    out->set_onlycontent(*in.onlyContent);
  }
  if (in.subtreePath) {
    proto_serde<orgproto::org::SubtreePath, org::sem::SubtreePath>::write(out->mutable_subtreepath(), *in.subtreePath);
  }
  if (in.minLevel) {
    out->set_minlevel(*in.minLevel);
  }
  if (in.customIdTarget) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_customidtarget(), *in.customIdTarget);
  }
}

void proto_serde<::orgproto::org::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::read(::orgproto::org::CmdInclude::OrgDocument const& out, proto_write_accessor<org::sem::CmdInclude::OrgDocument> in) {
  if (out.has_onlycontent()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.onlycontent(), in.for_field(&org::sem::CmdInclude::OrgDocument::onlyContent));
  }
  if (out.has_subtreepath()) {
    proto_serde<hstd::Opt<orgproto::org::SubtreePath>, hstd::Opt<org::sem::SubtreePath>>::read(out.subtreepath(), in.for_field(&org::sem::CmdInclude::OrgDocument::subtreePath));
  }
  if (out.has_minlevel()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.minlevel(), in.for_field(&org::sem::CmdInclude::OrgDocument::minLevel));
  }
  if (out.has_customidtarget()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.customidtarget(), in.for_field(&org::sem::CmdInclude::OrgDocument::customIdTarget));
  }
}

void proto_serde<::orgproto::org::CmdInclude, org::sem::CmdInclude>::write(::orgproto::org::CmdInclude* out, org::sem::CmdInclude const& in) {
  proto_serde<::orgproto::org::CmdInclude, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_path(), in.path);
  if (in.firstLine) {
    out->set_firstline(*in.firstLine);
  }
  if (in.lastLine) {
    out->set_lastline(*in.lastLine);
  }
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::org::CmdInclude::Example, org::sem::CmdInclude::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::org::CmdInclude::Export, org::sem::CmdInclude::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::org::CmdInclude::Custom, org::sem::CmdInclude::Custom>::write(out->mutable_data()->mutable_custom(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::org::CmdInclude::Src, org::sem::CmdInclude::Src>::write(out->mutable_data()->mutable_src(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::org::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::CmdInclude, org::sem::CmdInclude>::read(::orgproto::org::CmdInclude const& out, proto_write_accessor<org::sem::CmdInclude> in) {
  proto_serde<::orgproto::org::CmdInclude, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.path(), in.for_field(&org::sem::CmdInclude::path));
  if (out.has_firstline()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.firstline(), in.for_field(&org::sem::CmdInclude::firstLine));
  }
  if (out.has_lastline()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.lastline(), in.for_field(&org::sem::CmdInclude::lastLine));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::org::CmdInclude::Data::kExample:
      proto_serde<orgproto::org::CmdInclude::Example, org::sem::CmdInclude::Example>::read(out.data().example(), in.for_field_variant<0>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kExport:
      proto_serde<orgproto::org::CmdInclude::Export, org::sem::CmdInclude::Export>::read(out.data().export_(), in.for_field_variant<1>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kCustom:
      proto_serde<orgproto::org::CmdInclude::Custom, org::sem::CmdInclude::Custom>::read(out.data().custom(), in.for_field_variant<2>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kSrc:
      proto_serde<orgproto::org::CmdInclude::Src, org::sem::CmdInclude::Src>::read(out.data().src(), in.for_field_variant<3>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kOrgdocument:
      proto_serde<orgproto::org::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument>::read(out.data().orgdocument(), in.for_field_variant<4>(&org::sem::CmdInclude::data));
      break;
  }
}

/* clang-format on */