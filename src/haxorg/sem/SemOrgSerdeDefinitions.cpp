/* clang-format off */
#include <haxorg/sem/SemOrgSerde.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>
void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Index>::write(::orgproto::Tblfm::Expr::AxisRef::Position::Index* out, sem::Tblfm::Expr::AxisRef::Position::Index const& in) {
  out->set_index(in.index);
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Index>::read(::orgproto::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position::Index> in) {
  in.for_field(&sem::Tblfm::Expr::AxisRef::Position::Index::index).get() = out.index();
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, sem::Tblfm::Expr::AxisRef::Position::Name>::write(::orgproto::Tblfm::Expr::AxisRef::Position::Name* out, sem::Tblfm::Expr::AxisRef::Position::Name const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, sem::Tblfm::Expr::AxisRef::Position::Name>::read(::orgproto::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position::Name> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::Tblfm::Expr::AxisRef::Position::Name::name));
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position>::write(::orgproto::Tblfm::Expr::AxisRef::Position* out, sem::Tblfm::Expr::AxisRef::Position const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Index>::write(out->mutable_data()->mutable_index(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Name, sem::Tblfm::Expr::AxisRef::Position::Name>::write(out->mutable_data()->mutable_name(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position>::read(::orgproto::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Tblfm::Expr::AxisRef::Position::Data::kIndex:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Index>::read(out.data().index(), in.for_field_variant<0>(&sem::Tblfm::Expr::AxisRef::Position::data));
      break;
    case ::orgproto::Tblfm::Expr::AxisRef::Position::Data::kName:
      proto_serde<orgproto::Tblfm::Expr::AxisRef::Position::Name, sem::Tblfm::Expr::AxisRef::Position::Name>::read(out.data().name(), in.for_field_variant<1>(&sem::Tblfm::Expr::AxisRef::Position::data));
      break;
  }
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::write(::orgproto::Tblfm::Expr::AxisRef* out, sem::Tblfm::Expr::AxisRef const& in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_col(), in.col);
  if (in.row) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position>::write(out->mutable_row(), *in.row);
  }
}

void proto_serde<::orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::read(::orgproto::Tblfm::Expr::AxisRef const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef> in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position>::read(out.col(), in.for_field(&sem::Tblfm::Expr::AxisRef::col));
  if (out.has_row()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef::Position>, hstd::Opt<sem::Tblfm::Expr::AxisRef::Position>>::read(out.row(), in.for_field(&sem::Tblfm::Expr::AxisRef::row));
  }
}

void proto_serde<::orgproto::Tblfm::Expr::AxisName, sem::Tblfm::Expr::AxisName>::write(::orgproto::Tblfm::Expr::AxisName* out, sem::Tblfm::Expr::AxisName const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Tblfm::Expr::AxisName, sem::Tblfm::Expr::AxisName>::read(::orgproto::Tblfm::Expr::AxisName const& out, proto_write_accessor<sem::Tblfm::Expr::AxisName> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::Tblfm::Expr::AxisName::name));
}

void proto_serde<::orgproto::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::IntLiteral>::write(::orgproto::Tblfm::Expr::IntLiteral* out, sem::Tblfm::Expr::IntLiteral const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::IntLiteral>::read(::orgproto::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<sem::Tblfm::Expr::IntLiteral> in) {
  in.for_field(&sem::Tblfm::Expr::IntLiteral::value).get() = out.value();
}

void proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::FloatLiteral>::write(::orgproto::Tblfm::Expr::FloatLiteral* out, sem::Tblfm::Expr::FloatLiteral const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::FloatLiteral>::read(::orgproto::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<sem::Tblfm::Expr::FloatLiteral> in) {
  in.for_field(&sem::Tblfm::Expr::FloatLiteral::value).get() = out.value();
}

void proto_serde<::orgproto::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::RangeRef>::write(::orgproto::Tblfm::Expr::RangeRef* out, sem::Tblfm::Expr::RangeRef const& in) {
  if (in.first) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::write(out->mutable_first(), *in.first);
  }
  if (in.last) {
    proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::write(out->mutable_last(), *in.last);
  }
}

void proto_serde<::orgproto::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::RangeRef>::read(::orgproto::Tblfm::Expr::RangeRef const& out, proto_write_accessor<sem::Tblfm::Expr::RangeRef> in) {
  if (out.has_first()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef>, hstd::Opt<sem::Tblfm::Expr::AxisRef>>::read(out.first(), in.for_field(&sem::Tblfm::Expr::RangeRef::first));
  }
  if (out.has_last()) {
    proto_serde<hstd::Opt<orgproto::Tblfm::Expr::AxisRef>, hstd::Opt<sem::Tblfm::Expr::AxisRef>>::read(out.last(), in.for_field(&sem::Tblfm::Expr::RangeRef::last));
  }
}

void proto_serde<::orgproto::Tblfm::Expr::Call, sem::Tblfm::Expr::Call>::write(::orgproto::Tblfm::Expr::Call* out, sem::Tblfm::Expr::Call const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<sem::Tblfm::Expr>>::write(out->mutable_args(), in.args);
}

void proto_serde<::orgproto::Tblfm::Expr::Call, sem::Tblfm::Expr::Call>::read(::orgproto::Tblfm::Expr::Call const& out, proto_write_accessor<sem::Tblfm::Expr::Call> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::Tblfm::Expr::Call::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<sem::Tblfm::Expr>>::read(out.args(), in.for_field(&sem::Tblfm::Expr::Call::args));
}

void proto_serde<::orgproto::Tblfm::Expr::Elisp, sem::Tblfm::Expr::Elisp>::write(::orgproto::Tblfm::Expr::Elisp* out, sem::Tblfm::Expr::Elisp const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Tblfm::Expr::Elisp, sem::Tblfm::Expr::Elisp>::read(::orgproto::Tblfm::Expr::Elisp const& out, proto_write_accessor<sem::Tblfm::Expr::Elisp> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&sem::Tblfm::Expr::Elisp::value));
}

void proto_serde<::orgproto::Tblfm::Expr, sem::Tblfm::Expr>::write(::orgproto::Tblfm::Expr* out, sem::Tblfm::Expr const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::write(out->mutable_data()->mutable_axisref(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Tblfm::Expr::AxisName, sem::Tblfm::Expr::AxisName>::write(out->mutable_data()->mutable_axisname(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::IntLiteral>::write(out->mutable_data()->mutable_intliteral(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::FloatLiteral>::write(out->mutable_data()->mutable_floatliteral(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::RangeRef>::write(out->mutable_data()->mutable_rangeref(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::Tblfm::Expr::Call, sem::Tblfm::Expr::Call>::write(out->mutable_data()->mutable_call(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::Tblfm::Expr::Elisp, sem::Tblfm::Expr::Elisp>::write(out->mutable_data()->mutable_elisp(), std::get<6>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Tblfm::Expr, sem::Tblfm::Expr>::read(::orgproto::Tblfm::Expr const& out, proto_write_accessor<sem::Tblfm::Expr> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Tblfm::Expr::Data::kAxisref:
      proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::read(out.data().axisref(), in.for_field_variant<0>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kAxisname:
      proto_serde<orgproto::Tblfm::Expr::AxisName, sem::Tblfm::Expr::AxisName>::read(out.data().axisname(), in.for_field_variant<1>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kIntliteral:
      proto_serde<orgproto::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::IntLiteral>::read(out.data().intliteral(), in.for_field_variant<2>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kFloatliteral:
      proto_serde<orgproto::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::FloatLiteral>::read(out.data().floatliteral(), in.for_field_variant<3>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kRangeref:
      proto_serde<orgproto::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::RangeRef>::read(out.data().rangeref(), in.for_field_variant<4>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kCall:
      proto_serde<orgproto::Tblfm::Expr::Call, sem::Tblfm::Expr::Call>::read(out.data().call(), in.for_field_variant<5>(&sem::Tblfm::Expr::data));
      break;
    case ::orgproto::Tblfm::Expr::Data::kElisp:
      proto_serde<orgproto::Tblfm::Expr::Elisp, sem::Tblfm::Expr::Elisp>::read(out.data().elisp(), in.for_field_variant<6>(&sem::Tblfm::Expr::data));
      break;
  }
}

void proto_serde<::orgproto::Tblfm::Assign, sem::Tblfm::Assign>::write(::orgproto::Tblfm::Assign* out, sem::Tblfm::Assign const& in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::write(out->mutable_target(), in.target);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<sem::Tblfm::Expr>>::write(out->mutable_expr(), in.expr);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>, hstd::Vec<sem::Tblfm::Assign::Flag>>::write(out->mutable_flags(), in.flags);
}

void proto_serde<::orgproto::Tblfm::Assign, sem::Tblfm::Assign>::read(::orgproto::Tblfm::Assign const& out, proto_write_accessor<sem::Tblfm::Assign> in) {
  proto_serde<orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef>::read(out.target(), in.for_field(&sem::Tblfm::Assign::target));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Expr>, hstd::Vec<sem::Tblfm::Expr>>::read(out.expr(), in.for_field(&sem::Tblfm::Assign::expr));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm_Assign_Flag>, hstd::Vec<sem::Tblfm::Assign::Flag>>::read(out.flags(), in.for_field(&sem::Tblfm::Assign::flags));
}

void proto_serde<::orgproto::Tblfm, sem::Tblfm>::write(::orgproto::Tblfm* out, sem::Tblfm const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Assign>, hstd::Vec<sem::Tblfm::Assign>>::write(out->mutable_exprs(), in.exprs);
}

void proto_serde<::orgproto::Tblfm, sem::Tblfm>::read(::orgproto::Tblfm const& out, proto_write_accessor<sem::Tblfm> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Tblfm::Assign>, hstd::Vec<sem::Tblfm::Assign>>::read(out.exprs(), in.for_field(&sem::Tblfm::exprs));
}

void proto_serde<::orgproto::AttrValue, sem::AttrValue>::write(::orgproto::AttrValue* out, sem::AttrValue const& in) {
  if (in.name) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_name(), *in.name);
  }
  if (in.varname) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_varname(), *in.varname);
  }
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
  out->set_isquoted(in.isQuoted);
}

void proto_serde<::orgproto::AttrValue, sem::AttrValue>::read(::orgproto::AttrValue const& out, proto_write_accessor<sem::AttrValue> in) {
  if (out.has_name()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.name(), in.for_field(&sem::AttrValue::name));
  }
  if (out.has_varname()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.varname(), in.for_field(&sem::AttrValue::varname));
  }
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&sem::AttrValue::value));
  in.for_field(&sem::AttrValue::isQuoted).get() = out.isquoted();
}

void proto_serde<::orgproto::HashTagFlat, sem::HashTagFlat>::write(::orgproto::HashTagFlat* out, sem::HashTagFlat const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_tags(), in.tags);
}

void proto_serde<::orgproto::HashTagFlat, sem::HashTagFlat>::read(::orgproto::HashTagFlat const& out, proto_write_accessor<sem::HashTagFlat> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.tags(), in.for_field(&sem::HashTagFlat::tags));
}

void proto_serde<::orgproto::HashTagText, sem::HashTagText>::write(::orgproto::HashTagText* out, sem::HashTagText const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTagText>, hstd::Vec<sem::HashTagText>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::HashTagText, sem::HashTagText>::read(::orgproto::HashTagText const& out, proto_write_accessor<sem::HashTagText> in) {
  proto_serde<std::string, hstd::Str>::read(out.head(), in.for_field(&sem::HashTagText::head));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTagText>, hstd::Vec<sem::HashTagText>>::read(out.subtags(), in.for_field(&sem::HashTagText::subtags));
}

void proto_serde<::orgproto::SubtreePath, sem::SubtreePath>::write(::orgproto::SubtreePath* out, sem::SubtreePath const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::SubtreePath, sem::SubtreePath>::read(::orgproto::SubtreePath const& out, proto_write_accessor<sem::SubtreePath> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.path(), in.for_field(&sem::SubtreePath::path));
}

void proto_serde<::orgproto::LinkTarget::Raw, sem::LinkTarget::Raw>::write(::orgproto::LinkTarget::Raw* out, sem::LinkTarget::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::LinkTarget::Raw, sem::LinkTarget::Raw>::read(::orgproto::LinkTarget::Raw const& out, proto_write_accessor<sem::LinkTarget::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&sem::LinkTarget::Raw::text));
}

void proto_serde<::orgproto::LinkTarget::Id, sem::LinkTarget::Id>::write(::orgproto::LinkTarget::Id* out, sem::LinkTarget::Id const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::LinkTarget::Id, sem::LinkTarget::Id>::read(::orgproto::LinkTarget::Id const& out, proto_write_accessor<sem::LinkTarget::Id> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&sem::LinkTarget::Id::text));
}

void proto_serde<::orgproto::LinkTarget::CustomId, sem::LinkTarget::CustomId>::write(::orgproto::LinkTarget::CustomId* out, sem::LinkTarget::CustomId const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::LinkTarget::CustomId, sem::LinkTarget::CustomId>::read(::orgproto::LinkTarget::CustomId const& out, proto_write_accessor<sem::LinkTarget::CustomId> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&sem::LinkTarget::CustomId::text));
}

void proto_serde<::orgproto::LinkTarget::SubtreeTitle, sem::LinkTarget::SubtreeTitle>::write(::orgproto::LinkTarget::SubtreeTitle* out, sem::LinkTarget::SubtreeTitle const& in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::write(out->mutable_title(), in.title);
  out->set_level(in.level);
}

void proto_serde<::orgproto::LinkTarget::SubtreeTitle, sem::LinkTarget::SubtreeTitle>::read(::orgproto::LinkTarget::SubtreeTitle const& out, proto_write_accessor<sem::LinkTarget::SubtreeTitle> in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::read(out.title(), in.for_field(&sem::LinkTarget::SubtreeTitle::title));
  in.for_field(&sem::LinkTarget::SubtreeTitle::level).get() = out.level();
}

void proto_serde<::orgproto::LinkTarget::Person, sem::LinkTarget::Person>::write(::orgproto::LinkTarget::Person* out, sem::LinkTarget::Person const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::LinkTarget::Person, sem::LinkTarget::Person>::read(::orgproto::LinkTarget::Person const& out, proto_write_accessor<sem::LinkTarget::Person> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::LinkTarget::Person::name));
}

void proto_serde<::orgproto::LinkTarget::UserProtocol, sem::LinkTarget::UserProtocol>::write(::orgproto::LinkTarget::UserProtocol* out, sem::LinkTarget::UserProtocol const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_protocol(), in.protocol);
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::LinkTarget::UserProtocol, sem::LinkTarget::UserProtocol>::read(::orgproto::LinkTarget::UserProtocol const& out, proto_write_accessor<sem::LinkTarget::UserProtocol> in) {
  proto_serde<std::string, hstd::Str>::read(out.protocol(), in.for_field(&sem::LinkTarget::UserProtocol::protocol));
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&sem::LinkTarget::UserProtocol::target));
}

void proto_serde<::orgproto::LinkTarget::Internal, sem::LinkTarget::Internal>::write(::orgproto::LinkTarget::Internal* out, sem::LinkTarget::Internal const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::LinkTarget::Internal, sem::LinkTarget::Internal>::read(::orgproto::LinkTarget::Internal const& out, proto_write_accessor<sem::LinkTarget::Internal> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&sem::LinkTarget::Internal::target));
}

void proto_serde<::orgproto::LinkTarget::Footnote, sem::LinkTarget::Footnote>::write(::orgproto::LinkTarget::Footnote* out, sem::LinkTarget::Footnote const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::LinkTarget::Footnote, sem::LinkTarget::Footnote>::read(::orgproto::LinkTarget::Footnote const& out, proto_write_accessor<sem::LinkTarget::Footnote> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&sem::LinkTarget::Footnote::target));
}

void proto_serde<::orgproto::LinkTarget::File, sem::LinkTarget::File>::write(::orgproto::LinkTarget::File* out, sem::LinkTarget::File const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::LinkTarget::File, sem::LinkTarget::File>::read(::orgproto::LinkTarget::File const& out, proto_write_accessor<sem::LinkTarget::File> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&sem::LinkTarget::File::file));
}

void proto_serde<::orgproto::LinkTarget::Attachment, sem::LinkTarget::Attachment>::write(::orgproto::LinkTarget::Attachment* out, sem::LinkTarget::Attachment const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::LinkTarget::Attachment, sem::LinkTarget::Attachment>::read(::orgproto::LinkTarget::Attachment const& out, proto_write_accessor<sem::LinkTarget::Attachment> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&sem::LinkTarget::Attachment::file));
}

void proto_serde<::orgproto::LinkTarget, sem::LinkTarget>::write(::orgproto::LinkTarget* out, sem::LinkTarget const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::LinkTarget::Raw, sem::LinkTarget::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::LinkTarget::Id, sem::LinkTarget::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::LinkTarget::CustomId, sem::LinkTarget::CustomId>::write(out->mutable_data()->mutable_customid(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::LinkTarget::SubtreeTitle, sem::LinkTarget::SubtreeTitle>::write(out->mutable_data()->mutable_subtreetitle(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::LinkTarget::Person, sem::LinkTarget::Person>::write(out->mutable_data()->mutable_person(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::LinkTarget::UserProtocol, sem::LinkTarget::UserProtocol>::write(out->mutable_data()->mutable_userprotocol(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::LinkTarget::Internal, sem::LinkTarget::Internal>::write(out->mutable_data()->mutable_internal(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::LinkTarget::Footnote, sem::LinkTarget::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::LinkTarget::File, sem::LinkTarget::File>::write(out->mutable_data()->mutable_file(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::LinkTarget::Attachment, sem::LinkTarget::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<9>(in.data));
      break;
  }
}

void proto_serde<::orgproto::LinkTarget, sem::LinkTarget>::read(::orgproto::LinkTarget const& out, proto_write_accessor<sem::LinkTarget> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::LinkTarget::Data::kRaw:
      proto_serde<orgproto::LinkTarget::Raw, sem::LinkTarget::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kId:
      proto_serde<orgproto::LinkTarget::Id, sem::LinkTarget::Id>::read(out.data().id(), in.for_field_variant<1>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kCustomid:
      proto_serde<orgproto::LinkTarget::CustomId, sem::LinkTarget::CustomId>::read(out.data().customid(), in.for_field_variant<2>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kSubtreetitle:
      proto_serde<orgproto::LinkTarget::SubtreeTitle, sem::LinkTarget::SubtreeTitle>::read(out.data().subtreetitle(), in.for_field_variant<3>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kPerson:
      proto_serde<orgproto::LinkTarget::Person, sem::LinkTarget::Person>::read(out.data().person(), in.for_field_variant<4>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kUserprotocol:
      proto_serde<orgproto::LinkTarget::UserProtocol, sem::LinkTarget::UserProtocol>::read(out.data().userprotocol(), in.for_field_variant<5>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kInternal:
      proto_serde<orgproto::LinkTarget::Internal, sem::LinkTarget::Internal>::read(out.data().internal(), in.for_field_variant<6>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kFootnote:
      proto_serde<orgproto::LinkTarget::Footnote, sem::LinkTarget::Footnote>::read(out.data().footnote(), in.for_field_variant<7>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kFile:
      proto_serde<orgproto::LinkTarget::File, sem::LinkTarget::File>::read(out.data().file(), in.for_field_variant<8>(&sem::LinkTarget::data));
      break;
    case ::orgproto::LinkTarget::Data::kAttachment:
      proto_serde<orgproto::LinkTarget::Attachment, sem::LinkTarget::Attachment>::read(out.data().attachment(), in.for_field_variant<9>(&sem::LinkTarget::data));
      break;
  }
}

void proto_serde<::orgproto::SubtreeLogHead::Priority, sem::SubtreeLogHead::Priority>::write(::orgproto::SubtreeLogHead::Priority* out, sem::SubtreeLogHead::Priority const& in) {
  if (in.oldPriority) {
    out->set_oldpriority(*in.oldPriority);
  }
  if (in.newPriority) {
    out->set_newpriority(*in.newPriority);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
  out->set_action(static_cast<orgproto::SubtreeLogHead_Priority_Action>(in.action));
}

void proto_serde<::orgproto::SubtreeLogHead::Priority, sem::SubtreeLogHead::Priority>::read(::orgproto::SubtreeLogHead::Priority const& out, proto_write_accessor<sem::SubtreeLogHead::Priority> in) {
  if (out.has_oldpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.oldpriority(), in.for_field(&sem::SubtreeLogHead::Priority::oldPriority));
  }
  if (out.has_newpriority()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<std::string>>::read(out.newpriority(), in.for_field(&sem::SubtreeLogHead::Priority::newPriority));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Priority::on));
  in.for_field(&sem::SubtreeLogHead::Priority::action).get() = static_cast<sem::SubtreeLogHead::Priority::Action>(out.action());
}

void proto_serde<::orgproto::SubtreeLogHead::Note, sem::SubtreeLogHead::Note>::write(::orgproto::SubtreeLogHead::Note* out, sem::SubtreeLogHead::Note const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::SubtreeLogHead::Note, sem::SubtreeLogHead::Note>::read(::orgproto::SubtreeLogHead::Note const& out, proto_write_accessor<sem::SubtreeLogHead::Note> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Note::on));
}

void proto_serde<::orgproto::SubtreeLogHead::Refile, sem::SubtreeLogHead::Refile>::write(::orgproto::SubtreeLogHead::Refile* out, sem::SubtreeLogHead::Refile const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::LinkTarget, sem::LinkTarget>::write(out->mutable_from(), in.from);
}

void proto_serde<::orgproto::SubtreeLogHead::Refile, sem::SubtreeLogHead::Refile>::read(::orgproto::SubtreeLogHead::Refile const& out, proto_write_accessor<sem::SubtreeLogHead::Refile> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Refile::on));
  proto_serde<orgproto::LinkTarget, sem::LinkTarget>::read(out.from(), in.for_field(&sem::SubtreeLogHead::Refile::from));
}

void proto_serde<::orgproto::SubtreeLogHead::Clock, sem::SubtreeLogHead::Clock>::write(::orgproto::SubtreeLogHead::Clock* out, sem::SubtreeLogHead::Clock const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::SubtreeLogHead::Clock, sem::SubtreeLogHead::Clock>::read(::orgproto::SubtreeLogHead::Clock const& out, proto_write_accessor<sem::SubtreeLogHead::Clock> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.from(), in.for_field(&sem::SubtreeLogHead::Clock::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.to(), in.for_field(&sem::SubtreeLogHead::Clock::to));
  }
}

void proto_serde<::orgproto::SubtreeLogHead::State, sem::SubtreeLogHead::State>::write(::orgproto::SubtreeLogHead::State* out, sem::SubtreeLogHead::State const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_from(), in.from);
  proto_serde<std::string, hstd::Str>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::SubtreeLogHead::State, sem::SubtreeLogHead::State>::read(::orgproto::SubtreeLogHead::State const& out, proto_write_accessor<sem::SubtreeLogHead::State> in) {
  proto_serde<std::string, hstd::Str>::read(out.from(), in.for_field(&sem::SubtreeLogHead::State::from));
  proto_serde<std::string, hstd::Str>::read(out.to(), in.for_field(&sem::SubtreeLogHead::State::to));
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::State::on));
}

void proto_serde<::orgproto::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Deadline>::write(::orgproto::SubtreeLogHead::Deadline* out, sem::SubtreeLogHead::Deadline const& in) {
  if (in.from) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Deadline>::read(::orgproto::SubtreeLogHead::Deadline const& out, proto_write_accessor<sem::SubtreeLogHead::Deadline> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.from(), in.for_field(&sem::SubtreeLogHead::Deadline::from));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.to(), in.for_field(&sem::SubtreeLogHead::Deadline::to));
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Deadline::on));
}

void proto_serde<::orgproto::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Schedule>::write(::orgproto::SubtreeLogHead::Schedule* out, sem::SubtreeLogHead::Schedule const& in) {
  if (in.from) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_from(), *in.from);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_to(), in.to);
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
}

void proto_serde<::orgproto::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Schedule>::read(::orgproto::SubtreeLogHead::Schedule const& out, proto_write_accessor<sem::SubtreeLogHead::Schedule> in) {
  if (out.has_from()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.from(), in.for_field(&sem::SubtreeLogHead::Schedule::from));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.to(), in.for_field(&sem::SubtreeLogHead::Schedule::to));
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Schedule::on));
}

void proto_serde<::orgproto::SubtreeLogHead::Tag, sem::SubtreeLogHead::Tag>::write(::orgproto::SubtreeLogHead::Tag* out, sem::SubtreeLogHead::Tag const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_on(), in.on);
  proto_serde<orgproto::HashTagText, sem::HashTagText>::write(out->mutable_tag(), in.tag);
  out->set_added(in.added);
}

void proto_serde<::orgproto::SubtreeLogHead::Tag, sem::SubtreeLogHead::Tag>::read(::orgproto::SubtreeLogHead::Tag const& out, proto_write_accessor<sem::SubtreeLogHead::Tag> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.on(), in.for_field(&sem::SubtreeLogHead::Tag::on));
  proto_serde<orgproto::HashTagText, sem::HashTagText>::read(out.tag(), in.for_field(&sem::SubtreeLogHead::Tag::tag));
  in.for_field(&sem::SubtreeLogHead::Tag::added).get() = out.added();
}

void proto_serde<::orgproto::SubtreeLogHead::Unknown, sem::SubtreeLogHead::Unknown>::write(::orgproto::SubtreeLogHead::Unknown* out, sem::SubtreeLogHead::Unknown const& in) {

}

void proto_serde<::orgproto::SubtreeLogHead::Unknown, sem::SubtreeLogHead::Unknown>::read(::orgproto::SubtreeLogHead::Unknown const& out, proto_write_accessor<sem::SubtreeLogHead::Unknown> in) {

}

void proto_serde<::orgproto::SubtreeLogHead, sem::SubtreeLogHead>::write(::orgproto::SubtreeLogHead* out, sem::SubtreeLogHead const& in) {
  switch (in.log.index()) {
    case 0:
      proto_serde<orgproto::SubtreeLogHead::Priority, sem::SubtreeLogHead::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log));
      break;
    case 1:
      proto_serde<orgproto::SubtreeLogHead::Note, sem::SubtreeLogHead::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log));
      break;
    case 2:
      proto_serde<orgproto::SubtreeLogHead::Refile, sem::SubtreeLogHead::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log));
      break;
    case 3:
      proto_serde<orgproto::SubtreeLogHead::Clock, sem::SubtreeLogHead::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log));
      break;
    case 4:
      proto_serde<orgproto::SubtreeLogHead::State, sem::SubtreeLogHead::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log));
      break;
    case 5:
      proto_serde<orgproto::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Deadline>::write(out->mutable_log()->mutable_deadline(), std::get<5>(in.log));
      break;
    case 6:
      proto_serde<orgproto::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Schedule>::write(out->mutable_log()->mutable_schedule(), std::get<6>(in.log));
      break;
    case 7:
      proto_serde<orgproto::SubtreeLogHead::Tag, sem::SubtreeLogHead::Tag>::write(out->mutable_log()->mutable_tag(), std::get<7>(in.log));
      break;
    case 8:
      proto_serde<orgproto::SubtreeLogHead::Unknown, sem::SubtreeLogHead::Unknown>::write(out->mutable_log()->mutable_unknown(), std::get<8>(in.log));
      break;
  }
}

void proto_serde<::orgproto::SubtreeLogHead, sem::SubtreeLogHead>::read(::orgproto::SubtreeLogHead const& out, proto_write_accessor<sem::SubtreeLogHead> in) {
  switch (out.log().kind_case()) {
    case ::orgproto::SubtreeLogHead::LogEntry::kPriority:
      proto_serde<orgproto::SubtreeLogHead::Priority, sem::SubtreeLogHead::Priority>::read(out.log().priority(), in.for_field_variant<0>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kNote:
      proto_serde<orgproto::SubtreeLogHead::Note, sem::SubtreeLogHead::Note>::read(out.log().note(), in.for_field_variant<1>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kRefile:
      proto_serde<orgproto::SubtreeLogHead::Refile, sem::SubtreeLogHead::Refile>::read(out.log().refile(), in.for_field_variant<2>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kClock:
      proto_serde<orgproto::SubtreeLogHead::Clock, sem::SubtreeLogHead::Clock>::read(out.log().clock(), in.for_field_variant<3>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kState:
      proto_serde<orgproto::SubtreeLogHead::State, sem::SubtreeLogHead::State>::read(out.log().state(), in.for_field_variant<4>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kDeadline:
      proto_serde<orgproto::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Deadline>::read(out.log().deadline(), in.for_field_variant<5>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kSchedule:
      proto_serde<orgproto::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Schedule>::read(out.log().schedule(), in.for_field_variant<6>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kTag:
      proto_serde<orgproto::SubtreeLogHead::Tag, sem::SubtreeLogHead::Tag>::read(out.log().tag(), in.for_field_variant<7>(&sem::SubtreeLogHead::log));
      break;
    case ::orgproto::SubtreeLogHead::LogEntry::kUnknown:
      proto_serde<orgproto::SubtreeLogHead::Unknown, sem::SubtreeLogHead::Unknown>::read(out.log().unknown(), in.for_field_variant<8>(&sem::SubtreeLogHead::log));
      break;
  }
}

void proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion>::write(::orgproto::SubtreeCompletion* out, sem::SubtreeCompletion const& in) {
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion>::read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<sem::SubtreeCompletion> in) {
  in.for_field(&sem::SubtreeCompletion::done).get() = out.done();
  in.for_field(&sem::SubtreeCompletion::full).get() = out.full();
  in.for_field(&sem::SubtreeCompletion::isPercent).get() = out.ispercent();
}

void proto_serde<::orgproto::AttrList, sem::AttrList>::write(::orgproto::AttrList* out, sem::AttrList const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue>, hstd::Vec<sem::AttrValue>>::write(out->mutable_items(), in.items);
}

void proto_serde<::orgproto::AttrList, sem::AttrList>::read(::orgproto::AttrList const& out, proto_write_accessor<sem::AttrList> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AttrValue>, hstd::Vec<sem::AttrValue>>::read(out.items(), in.for_field(&sem::AttrList::items));
}

void proto_serde<::orgproto::AttrGroup, sem::AttrGroup>::write(::orgproto::AttrGroup* out, sem::AttrGroup const& in) {
  proto_serde<orgproto::AttrList, sem::AttrList>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AttrList>, UnorderedMap<hstd::Str, sem::AttrList>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::AttrGroup, sem::AttrGroup>::read(::orgproto::AttrGroup const& out, proto_write_accessor<sem::AttrGroup> in) {
  proto_serde<orgproto::AttrList, sem::AttrList>::read(out.positional(), in.for_field(&sem::AttrGroup::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::AttrList>, UnorderedMap<hstd::Str, sem::AttrList>>::read(out.named(), in.for_field(&sem::AttrGroup::named));
}

void proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::CheckboxAggregate>::write(::orgproto::ColumnView::Summary::CheckboxAggregate* out, sem::ColumnView::Summary::CheckboxAggregate const& in) {
  out->set_kind(static_cast<orgproto::ColumnView_Summary_CheckboxAggregate_Kind>(in.kind));
}

void proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::CheckboxAggregate>::read(::orgproto::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<sem::ColumnView::Summary::CheckboxAggregate> in) {
  in.for_field(&sem::ColumnView::Summary::CheckboxAggregate::kind).get() = static_cast<sem::ColumnView::Summary::CheckboxAggregate::Kind>(out.kind());
}

void proto_serde<::orgproto::ColumnView::Summary::MathAggregate, sem::ColumnView::Summary::MathAggregate>::write(::orgproto::ColumnView::Summary::MathAggregate* out, sem::ColumnView::Summary::MathAggregate const& in) {
  out->set_kind(static_cast<orgproto::ColumnView_Summary_MathAggregate_Kind>(in.kind));
  if (in.formatDigits) {
    out->set_formatdigits(*in.formatDigits);
  }
  if (in.formatPrecision) {
    out->set_formatprecision(*in.formatPrecision);
  }
}

void proto_serde<::orgproto::ColumnView::Summary::MathAggregate, sem::ColumnView::Summary::MathAggregate>::read(::orgproto::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<sem::ColumnView::Summary::MathAggregate> in) {
  in.for_field(&sem::ColumnView::Summary::MathAggregate::kind).get() = static_cast<sem::ColumnView::Summary::MathAggregate::Kind>(out.kind());
  if (out.has_formatdigits()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatdigits(), in.for_field(&sem::ColumnView::Summary::MathAggregate::formatDigits));
  }
  if (out.has_formatprecision()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.formatprecision(), in.for_field(&sem::ColumnView::Summary::MathAggregate::formatPrecision));
  }
}

void proto_serde<::orgproto::ColumnView::Summary, sem::ColumnView::Summary>::write(::orgproto::ColumnView::Summary* out, sem::ColumnView::Summary const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::CheckboxAggregate>::write(out->mutable_data()->mutable_checkboxaggregate(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::ColumnView::Summary::MathAggregate, sem::ColumnView::Summary::MathAggregate>::write(out->mutable_data()->mutable_mathaggregate(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::ColumnView::Summary, sem::ColumnView::Summary>::read(::orgproto::ColumnView::Summary const& out, proto_write_accessor<sem::ColumnView::Summary> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::ColumnView::Summary::Data::kCheckboxaggregate:
      proto_serde<orgproto::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::CheckboxAggregate>::read(out.data().checkboxaggregate(), in.for_field_variant<0>(&sem::ColumnView::Summary::data));
      break;
    case ::orgproto::ColumnView::Summary::Data::kMathaggregate:
      proto_serde<orgproto::ColumnView::Summary::MathAggregate, sem::ColumnView::Summary::MathAggregate>::read(out.data().mathaggregate(), in.for_field_variant<1>(&sem::ColumnView::Summary::data));
      break;
  }
}

void proto_serde<::orgproto::ColumnView::Column, sem::ColumnView::Column>::write(::orgproto::ColumnView::Column* out, sem::ColumnView::Column const& in) {
  if (in.summary) {
    proto_serde<orgproto::ColumnView::Summary, sem::ColumnView::Summary>::write(out->mutable_summary(), *in.summary);
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

void proto_serde<::orgproto::ColumnView::Column, sem::ColumnView::Column>::read(::orgproto::ColumnView::Column const& out, proto_write_accessor<sem::ColumnView::Column> in) {
  if (out.has_summary()) {
    proto_serde<hstd::Opt<orgproto::ColumnView::Summary>, hstd::Opt<sem::ColumnView::Summary>>::read(out.summary(), in.for_field(&sem::ColumnView::Column::summary));
  }
  if (out.has_width()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.width(), in.for_field(&sem::ColumnView::Column::width));
  }
  if (out.has_property()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.property(), in.for_field(&sem::ColumnView::Column::property));
  }
  if (out.has_propertytitle()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.propertytitle(), in.for_field(&sem::ColumnView::Column::propertyTitle));
  }
}

void proto_serde<::orgproto::ColumnView, sem::ColumnView>::write(::orgproto::ColumnView* out, sem::ColumnView const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ColumnView::Column>, hstd::Vec<sem::ColumnView::Column>>::write(out->mutable_columns(), in.columns);
}

void proto_serde<::orgproto::ColumnView, sem::ColumnView>::read(::orgproto::ColumnView const& out, proto_write_accessor<sem::ColumnView> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ColumnView::Column>, hstd::Vec<sem::ColumnView::Column>>::read(out.columns(), in.for_field(&sem::ColumnView::columns));
}

void proto_serde<::orgproto::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Raw>::write(::orgproto::BlockCodeLine::Part::Raw* out, sem::BlockCodeLine::Part::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_code(), in.code);
}

void proto_serde<::orgproto::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Raw>::read(::orgproto::BlockCodeLine::Part::Raw const& out, proto_write_accessor<sem::BlockCodeLine::Part::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.code(), in.for_field(&sem::BlockCodeLine::Part::Raw::code));
}

void proto_serde<::orgproto::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Callout>::write(::orgproto::BlockCodeLine::Part::Callout* out, sem::BlockCodeLine::Part::Callout const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Callout>::read(::orgproto::BlockCodeLine::Part::Callout const& out, proto_write_accessor<sem::BlockCodeLine::Part::Callout> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::BlockCodeLine::Part::Callout::name));
}

void proto_serde<::orgproto::BlockCodeLine::Part::Tangle, sem::BlockCodeLine::Part::Tangle>::write(::orgproto::BlockCodeLine::Part::Tangle* out, sem::BlockCodeLine::Part::Tangle const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::BlockCodeLine::Part::Tangle, sem::BlockCodeLine::Part::Tangle>::read(::orgproto::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<sem::BlockCodeLine::Part::Tangle> in) {
  proto_serde<std::string, hstd::Str>::read(out.target(), in.for_field(&sem::BlockCodeLine::Part::Tangle::target));
}

void proto_serde<::orgproto::BlockCodeLine::Part, sem::BlockCodeLine::Part>::write(::orgproto::BlockCodeLine::Part* out, sem::BlockCodeLine::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCodeLine::Part::Tangle, sem::BlockCodeLine::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::BlockCodeLine::Part, sem::BlockCodeLine::Part>::read(::orgproto::BlockCodeLine::Part const& out, proto_write_accessor<sem::BlockCodeLine::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCodeLine::Part::Data::kRaw:
      proto_serde<orgproto::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::BlockCodeLine::Part::Data::kCallout:
      proto_serde<orgproto::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&sem::BlockCodeLine::Part::data));
      break;
    case ::orgproto::BlockCodeLine::Part::Data::kTangle:
      proto_serde<orgproto::BlockCodeLine::Part::Tangle, sem::BlockCodeLine::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&sem::BlockCodeLine::Part::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCodeLine, sem::BlockCodeLine>::write(::orgproto::BlockCodeLine* out, sem::BlockCodeLine const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine::Part>, hstd::Vec<sem::BlockCodeLine::Part>>::write(out->mutable_parts(), in.parts);
}

void proto_serde<::orgproto::BlockCodeLine, sem::BlockCodeLine>::read(::orgproto::BlockCodeLine const& out, proto_write_accessor<sem::BlockCodeLine> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine::Part>, hstd::Vec<sem::BlockCodeLine::Part>>::read(out.parts(), in.for_field(&sem::BlockCodeLine::parts));
}

void proto_serde<::orgproto::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::LineStart>::write(::orgproto::BlockCodeSwitch::LineStart* out, sem::BlockCodeSwitch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::LineStart>::read(::orgproto::BlockCodeSwitch::LineStart const& out, proto_write_accessor<sem::BlockCodeSwitch::LineStart> in) {
  in.for_field(&sem::BlockCodeSwitch::LineStart::start).get() = out.start();
  in.for_field(&sem::BlockCodeSwitch::LineStart::extendLast).get() = out.extendlast();
}

void proto_serde<::orgproto::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::CalloutFormat>::write(::orgproto::BlockCodeSwitch::CalloutFormat* out, sem::BlockCodeSwitch::CalloutFormat const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::CalloutFormat>::read(::orgproto::BlockCodeSwitch::CalloutFormat const& out, proto_write_accessor<sem::BlockCodeSwitch::CalloutFormat> in) {
  proto_serde<std::string, hstd::Str>::read(out.format(), in.for_field(&sem::BlockCodeSwitch::CalloutFormat::format));
}

void proto_serde<::orgproto::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::RemoveCallout>::write(::orgproto::BlockCodeSwitch::RemoveCallout* out, sem::BlockCodeSwitch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::RemoveCallout>::read(::orgproto::BlockCodeSwitch::RemoveCallout const& out, proto_write_accessor<sem::BlockCodeSwitch::RemoveCallout> in) {
  in.for_field(&sem::BlockCodeSwitch::RemoveCallout::remove).get() = out.remove();
}

void proto_serde<::orgproto::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::EmphasizeLine>::write(::orgproto::BlockCodeSwitch::EmphasizeLine* out, sem::BlockCodeSwitch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, hstd::Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::EmphasizeLine>::read(::orgproto::BlockCodeSwitch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCodeSwitch::EmphasizeLine> in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, hstd::Vec<int>>::read(out.line(), in.for_field(&sem::BlockCodeSwitch::EmphasizeLine::line));
}

void proto_serde<::orgproto::BlockCodeSwitch::Dedent, sem::BlockCodeSwitch::Dedent>::write(::orgproto::BlockCodeSwitch::Dedent* out, sem::BlockCodeSwitch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::BlockCodeSwitch::Dedent, sem::BlockCodeSwitch::Dedent>::read(::orgproto::BlockCodeSwitch::Dedent const& out, proto_write_accessor<sem::BlockCodeSwitch::Dedent> in) {
  in.for_field(&sem::BlockCodeSwitch::Dedent::value).get() = out.value();
}

void proto_serde<::orgproto::BlockCodeSwitch, sem::BlockCodeSwitch>::write(::orgproto::BlockCodeSwitch* out, sem::BlockCodeSwitch const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::BlockCodeSwitch::Dedent, sem::BlockCodeSwitch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::BlockCodeSwitch, sem::BlockCodeSwitch>::read(::orgproto::BlockCodeSwitch const& out, proto_write_accessor<sem::BlockCodeSwitch> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCodeSwitch::Data::kLinestart:
      proto_serde<orgproto::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::LineStart>::read(out.data().linestart(), in.for_field_variant<0>(&sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::BlockCodeSwitch::Data::kCalloutformat:
      proto_serde<orgproto::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::CalloutFormat>::read(out.data().calloutformat(), in.for_field_variant<1>(&sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::BlockCodeSwitch::Data::kRemovecallout:
      proto_serde<orgproto::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::RemoveCallout>::read(out.data().removecallout(), in.for_field_variant<2>(&sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::BlockCodeSwitch::Data::kEmphasizeline:
      proto_serde<orgproto::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::EmphasizeLine>::read(out.data().emphasizeline(), in.for_field_variant<3>(&sem::BlockCodeSwitch::data));
      break;
    case ::orgproto::BlockCodeSwitch::Data::kDedent:
      proto_serde<orgproto::BlockCodeSwitch::Dedent, sem::BlockCodeSwitch::Dedent>::read(out.data().dedent(), in.for_field_variant<4>(&sem::BlockCodeSwitch::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::None>::write(::orgproto::BlockCodeEvalResult::None* out, sem::BlockCodeEvalResult::None const& in) {

}

void proto_serde<::orgproto::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::None>::read(::orgproto::BlockCodeEvalResult::None const& out, proto_write_accessor<sem::BlockCodeEvalResult::None> in) {

}

void proto_serde<::orgproto::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::OrgValue>::write(::orgproto::BlockCodeEvalResult::OrgValue* out, sem::BlockCodeEvalResult::OrgValue const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::OrgValue>::read(::orgproto::BlockCodeEvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCodeEvalResult::OrgValue> in) {
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&sem::BlockCodeEvalResult::OrgValue::value));
}

void proto_serde<::orgproto::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::File>::write(::orgproto::BlockCodeEvalResult::File* out, sem::BlockCodeEvalResult::File const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::File>::read(::orgproto::BlockCodeEvalResult::File const& out, proto_write_accessor<sem::BlockCodeEvalResult::File> in) {
  proto_serde<std::string, hstd::Str>::read(out.path(), in.for_field(&sem::BlockCodeEvalResult::File::path));
}

void proto_serde<::orgproto::BlockCodeEvalResult::Raw, sem::BlockCodeEvalResult::Raw>::write(::orgproto::BlockCodeEvalResult::Raw* out, sem::BlockCodeEvalResult::Raw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::BlockCodeEvalResult::Raw, sem::BlockCodeEvalResult::Raw>::read(::orgproto::BlockCodeEvalResult::Raw const& out, proto_write_accessor<sem::BlockCodeEvalResult::Raw> in) {
  proto_serde<std::string, hstd::Str>::read(out.text(), in.for_field(&sem::BlockCodeEvalResult::Raw::text));
}

void proto_serde<::orgproto::BlockCodeEvalResult, sem::BlockCodeEvalResult>::write(::orgproto::BlockCodeEvalResult* out, sem::BlockCodeEvalResult const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::OrgValue>::write(out->mutable_data()->mutable_orgvalue(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::File>::write(out->mutable_data()->mutable_file(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::BlockCodeEvalResult::Raw, sem::BlockCodeEvalResult::Raw>::write(out->mutable_data()->mutable_raw(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::BlockCodeEvalResult, sem::BlockCodeEvalResult>::read(::orgproto::BlockCodeEvalResult const& out, proto_write_accessor<sem::BlockCodeEvalResult> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCodeEvalResult::Data::kNone:
      proto_serde<orgproto::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::None>::read(out.data().none(), in.for_field_variant<0>(&sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::BlockCodeEvalResult::Data::kOrgvalue:
      proto_serde<orgproto::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::OrgValue>::read(out.data().orgvalue(), in.for_field_variant<1>(&sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::BlockCodeEvalResult::Data::kFile:
      proto_serde<orgproto::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::File>::read(out.data().file(), in.for_field_variant<2>(&sem::BlockCodeEvalResult::data));
      break;
    case ::orgproto::BlockCodeEvalResult::Data::kRaw:
      proto_serde<orgproto::BlockCodeEvalResult::Raw, sem::BlockCodeEvalResult::Raw>::read(out.data().raw(), in.for_field_variant<3>(&sem::BlockCodeEvalResult::data));
      break;
  }
}

void proto_serde<::orgproto::DocumentExportConfig::TaskExport, sem::DocumentExportConfig::TaskExport>::write(::orgproto::DocumentExportConfig::TaskExport* out, sem::DocumentExportConfig::TaskExport const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_taskwhitelist(), in.taskWhitelist);
}

void proto_serde<::orgproto::DocumentExportConfig::TaskExport, sem::DocumentExportConfig::TaskExport>::read(::orgproto::DocumentExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentExportConfig::TaskExport> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.taskwhitelist(), in.for_field(&sem::DocumentExportConfig::TaskExport::taskWhitelist));
}

void proto_serde<::orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::write(::orgproto::DocumentExportConfig::DoExport* out, sem::DocumentExportConfig::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::read(::orgproto::DocumentExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentExportConfig::DoExport> in) {
  in.for_field(&sem::DocumentExportConfig::DoExport::exportToc).get() = out.exporttoc();
}

void proto_serde<::orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::write(::orgproto::DocumentExportConfig::ExportFixed* out, sem::DocumentExportConfig::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::read(::orgproto::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentExportConfig::ExportFixed> in) {
  in.for_field(&sem::DocumentExportConfig::ExportFixed::exportLevels).get() = out.exportlevels();
}

void proto_serde<::orgproto::DocumentExportConfig, sem::DocumentExportConfig>::write(::orgproto::DocumentExportConfig* out, sem::DocumentExportConfig const& in) {
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
  out->set_brokenlinks(static_cast<orgproto::DocumentExportConfig_BrokenLinks>(in.brokenLinks));
  switch (in.tocExport.index()) {
    case 0:
      proto_serde<orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::write(out->mutable_tocexport()->mutable_doexport(), std::get<0>(in.tocExport));
      break;
    case 1:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::write(out->mutable_tocexport()->mutable_exportfixed(), std::get<1>(in.tocExport));
      break;
  }
  out->set_tagexport(static_cast<orgproto::DocumentExportConfig_TagExport>(in.tagExport));
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::DocumentExportConfig, sem::DocumentExportConfig>::read(::orgproto::DocumentExportConfig const& out, proto_write_accessor<sem::DocumentExportConfig> in) {
  if (out.has_inlinetasks()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.inlinetasks(), in.for_field(&sem::DocumentExportConfig::inlinetasks));
  }
  if (out.has_footnotes()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.footnotes(), in.for_field(&sem::DocumentExportConfig::footnotes));
  }
  if (out.has_clock()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.clock(), in.for_field(&sem::DocumentExportConfig::clock));
  }
  if (out.has_author()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.author(), in.for_field(&sem::DocumentExportConfig::author));
  }
  if (out.has_emphasis()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.emphasis(), in.for_field(&sem::DocumentExportConfig::emphasis));
  }
  if (out.has_specialstrings()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.specialstrings(), in.for_field(&sem::DocumentExportConfig::specialStrings));
  }
  if (out.has_propertydrawers()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.propertydrawers(), in.for_field(&sem::DocumentExportConfig::propertyDrawers));
  }
  if (out.has_statisticscookies()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.statisticscookies(), in.for_field(&sem::DocumentExportConfig::statisticsCookies));
  }
  if (out.has_todotext()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.todotext(), in.for_field(&sem::DocumentExportConfig::todoText));
  }
  in.for_field(&sem::DocumentExportConfig::brokenLinks).get() = static_cast<sem::DocumentExportConfig::BrokenLinks>(out.brokenlinks());
  switch (out.tocexport().kind_case()) {
    case ::orgproto::DocumentExportConfig::TocExport::kDoexport:
      proto_serde<orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::read(out.tocexport().doexport(), in.for_field_variant<0>(&sem::DocumentExportConfig::tocExport));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::kExportfixed:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::read(out.tocexport().exportfixed(), in.for_field_variant<1>(&sem::DocumentExportConfig::tocExport));
      break;
  }
  in.for_field(&sem::DocumentExportConfig::tagExport).get() = static_cast<sem::DocumentExportConfig::TagExport>(out.tagexport());
  switch (out.data().kind_case()) {
    case ::orgproto::DocumentExportConfig::TocExport::kDoexport:
      proto_serde<orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&sem::DocumentExportConfig::data));
      break;
    case ::orgproto::DocumentExportConfig::TocExport::kExportfixed:
      proto_serde<orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&sem::DocumentExportConfig::data));
      break;
  }
}

void proto_serde<::orgproto::SubtreePeriod, sem::SubtreePeriod>::write(::orgproto::SubtreePeriod* out, sem::SubtreePeriod const& in) {
  out->set_kind(static_cast<orgproto::SubtreePeriod_Kind>(in.kind));
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_from(), in.from);
  if (in.to) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::SubtreePeriod, sem::SubtreePeriod>::read(::orgproto::SubtreePeriod const& out, proto_write_accessor<sem::SubtreePeriod> in) {
  in.for_field(&sem::SubtreePeriod::kind).get() = static_cast<sem::SubtreePeriod::Kind>(out.kind());
  proto_serde<orgproto::UserTime, UserTime>::read(out.from(), in.for_field(&sem::SubtreePeriod::from));
  if (out.has_to()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.to(), in.for_field(&sem::SubtreePeriod::to));
  }
}

void proto_serde<::orgproto::NamedProperty::Nonblocking, sem::NamedProperty::Nonblocking>::write(::orgproto::NamedProperty::Nonblocking* out, sem::NamedProperty::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::NamedProperty::Nonblocking, sem::NamedProperty::Nonblocking>::read(::orgproto::NamedProperty::Nonblocking const& out, proto_write_accessor<sem::NamedProperty::Nonblocking> in) {
  in.for_field(&sem::NamedProperty::Nonblocking::isBlocking).get() = out.isblocking();
}

void proto_serde<::orgproto::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveTime>::write(::orgproto::NamedProperty::ArchiveTime* out, sem::NamedProperty::ArchiveTime const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveTime>::read(::orgproto::NamedProperty::ArchiveTime const& out, proto_write_accessor<sem::NamedProperty::ArchiveTime> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.time(), in.for_field(&sem::NamedProperty::ArchiveTime::time));
}

void proto_serde<::orgproto::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveFile>::write(::orgproto::NamedProperty::ArchiveFile* out, sem::NamedProperty::ArchiveFile const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveFile>::read(::orgproto::NamedProperty::ArchiveFile const& out, proto_write_accessor<sem::NamedProperty::ArchiveFile> in) {
  proto_serde<std::string, hstd::Str>::read(out.file(), in.for_field(&sem::NamedProperty::ArchiveFile::file));
}

void proto_serde<::orgproto::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveOlpath>::write(::orgproto::NamedProperty::ArchiveOlpath* out, sem::NamedProperty::ArchiveOlpath const& in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveOlpath>::read(::orgproto::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<sem::NamedProperty::ArchiveOlpath> in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::read(out.path(), in.for_field(&sem::NamedProperty::ArchiveOlpath::path));
}

void proto_serde<::orgproto::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveTarget>::write(::orgproto::NamedProperty::ArchiveTarget* out, sem::NamedProperty::ArchiveTarget const& in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::write(out->mutable_path(), in.path);
  proto_serde<std::string, hstd::Str>::write(out->mutable_pattern(), in.pattern);
}

void proto_serde<::orgproto::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveTarget>::read(::orgproto::NamedProperty::ArchiveTarget const& out, proto_write_accessor<sem::NamedProperty::ArchiveTarget> in) {
  proto_serde<orgproto::SubtreePath, sem::SubtreePath>::read(out.path(), in.for_field(&sem::NamedProperty::ArchiveTarget::path));
  proto_serde<std::string, hstd::Str>::read(out.pattern(), in.for_field(&sem::NamedProperty::ArchiveTarget::pattern));
}

void proto_serde<::orgproto::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveCategory>::write(::orgproto::NamedProperty::ArchiveCategory* out, sem::NamedProperty::ArchiveCategory const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_category(), in.category);
}

void proto_serde<::orgproto::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveCategory>::read(::orgproto::NamedProperty::ArchiveCategory const& out, proto_write_accessor<sem::NamedProperty::ArchiveCategory> in) {
  proto_serde<std::string, hstd::Str>::read(out.category(), in.for_field(&sem::NamedProperty::ArchiveCategory::category));
}

void proto_serde<::orgproto::NamedProperty::ArchiveTodo, sem::NamedProperty::ArchiveTodo>::write(::orgproto::NamedProperty::ArchiveTodo* out, sem::NamedProperty::ArchiveTodo const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_todo(), in.todo);
}

void proto_serde<::orgproto::NamedProperty::ArchiveTodo, sem::NamedProperty::ArchiveTodo>::read(::orgproto::NamedProperty::ArchiveTodo const& out, proto_write_accessor<sem::NamedProperty::ArchiveTodo> in) {
  proto_serde<std::string, hstd::Str>::read(out.todo(), in.for_field(&sem::NamedProperty::ArchiveTodo::todo));
}

void proto_serde<::orgproto::NamedProperty::Trigger, sem::NamedProperty::Trigger>::write(::orgproto::NamedProperty::Trigger* out, sem::NamedProperty::Trigger const& in) {

}

void proto_serde<::orgproto::NamedProperty::Trigger, sem::NamedProperty::Trigger>::read(::orgproto::NamedProperty::Trigger const& out, proto_write_accessor<sem::NamedProperty::Trigger> in) {

}

void proto_serde<::orgproto::NamedProperty::ExportLatexClass, sem::NamedProperty::ExportLatexClass>::write(::orgproto::NamedProperty::ExportLatexClass* out, sem::NamedProperty::ExportLatexClass const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::NamedProperty::ExportLatexClass, sem::NamedProperty::ExportLatexClass>::read(::orgproto::NamedProperty::ExportLatexClass const& out, proto_write_accessor<sem::NamedProperty::ExportLatexClass> in) {
  proto_serde<std::string, hstd::Str>::read(out.latexclass(), in.for_field(&sem::NamedProperty::ExportLatexClass::latexClass));
}

void proto_serde<::orgproto::NamedProperty::CookieData, sem::NamedProperty::CookieData>::write(::orgproto::NamedProperty::CookieData* out, sem::NamedProperty::CookieData const& in) {
  out->set_isrecursive(in.isRecursive);
  out->set_source(static_cast<orgproto::NamedProperty_CookieData_TodoSource>(in.source));
}

void proto_serde<::orgproto::NamedProperty::CookieData, sem::NamedProperty::CookieData>::read(::orgproto::NamedProperty::CookieData const& out, proto_write_accessor<sem::NamedProperty::CookieData> in) {
  in.for_field(&sem::NamedProperty::CookieData::isRecursive).get() = out.isrecursive();
  in.for_field(&sem::NamedProperty::CookieData::source).get() = static_cast<sem::NamedProperty::CookieData::TodoSource>(out.source());
}

void proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexClassOptions>::write(::orgproto::NamedProperty::ExportLatexClassOptions* out, sem::NamedProperty::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexClassOptions>::read(::orgproto::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<sem::NamedProperty::ExportLatexClassOptions> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.options(), in.for_field(&sem::NamedProperty::ExportLatexClassOptions::options));
}

void proto_serde<::orgproto::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexHeader>::write(::orgproto::NamedProperty::ExportLatexHeader* out, sem::NamedProperty::ExportLatexHeader const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexHeader>::read(::orgproto::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<sem::NamedProperty::ExportLatexHeader> in) {
  proto_serde<std::string, hstd::Str>::read(out.header(), in.for_field(&sem::NamedProperty::ExportLatexHeader::header));
}

void proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, sem::NamedProperty::ExportLatexCompiler>::write(::orgproto::NamedProperty::ExportLatexCompiler* out, sem::NamedProperty::ExportLatexCompiler const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, sem::NamedProperty::ExportLatexCompiler>::read(::orgproto::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<sem::NamedProperty::ExportLatexCompiler> in) {
  proto_serde<std::string, hstd::Str>::read(out.compiler(), in.for_field(&sem::NamedProperty::ExportLatexCompiler::compiler));
}

void proto_serde<::orgproto::NamedProperty::Ordered, sem::NamedProperty::Ordered>::write(::orgproto::NamedProperty::Ordered* out, sem::NamedProperty::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::NamedProperty::Ordered, sem::NamedProperty::Ordered>::read(::orgproto::NamedProperty::Ordered const& out, proto_write_accessor<sem::NamedProperty::Ordered> in) {
  in.for_field(&sem::NamedProperty::Ordered::isOrdered).get() = out.isordered();
}

void proto_serde<::orgproto::NamedProperty::Effort, sem::NamedProperty::Effort>::write(::orgproto::NamedProperty::Effort* out, sem::NamedProperty::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::NamedProperty::Effort, sem::NamedProperty::Effort>::read(::orgproto::NamedProperty::Effort const& out, proto_write_accessor<sem::NamedProperty::Effort> in) {
  in.for_field(&sem::NamedProperty::Effort::hours).get() = out.hours();
  in.for_field(&sem::NamedProperty::Effort::minutes).get() = out.minutes();
}

void proto_serde<::orgproto::NamedProperty::Visibility, sem::NamedProperty::Visibility>::write(::orgproto::NamedProperty::Visibility* out, sem::NamedProperty::Visibility const& in) {
  out->set_level(static_cast<orgproto::NamedProperty_Visibility_Level>(in.level));
}

void proto_serde<::orgproto::NamedProperty::Visibility, sem::NamedProperty::Visibility>::read(::orgproto::NamedProperty::Visibility const& out, proto_write_accessor<sem::NamedProperty::Visibility> in) {
  in.for_field(&sem::NamedProperty::Visibility::level).get() = static_cast<sem::NamedProperty::Visibility::Level>(out.level());
}

void proto_serde<::orgproto::NamedProperty::ExportOptions, sem::NamedProperty::ExportOptions>::write(::orgproto::NamedProperty::ExportOptions* out, sem::NamedProperty::ExportOptions const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<hstd::Str, hstd::Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::NamedProperty::ExportOptions, sem::NamedProperty::ExportOptions>::read(::orgproto::NamedProperty::ExportOptions const& out, proto_write_accessor<sem::NamedProperty::ExportOptions> in) {
  proto_serde<std::string, hstd::Str>::read(out.backend(), in.for_field(&sem::NamedProperty::ExportOptions::backend));
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<hstd::Str, hstd::Str>>::read(out.values(), in.for_field(&sem::NamedProperty::ExportOptions::values));
}

void proto_serde<::orgproto::NamedProperty::Blocker, sem::NamedProperty::Blocker>::write(::orgproto::NamedProperty::Blocker* out, sem::NamedProperty::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::NamedProperty::Blocker, sem::NamedProperty::Blocker>::read(::orgproto::NamedProperty::Blocker const& out, proto_write_accessor<sem::NamedProperty::Blocker> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.blockers(), in.for_field(&sem::NamedProperty::Blocker::blockers));
}

void proto_serde<::orgproto::NamedProperty::Unnumbered, sem::NamedProperty::Unnumbered>::write(::orgproto::NamedProperty::Unnumbered* out, sem::NamedProperty::Unnumbered const& in) {

}

void proto_serde<::orgproto::NamedProperty::Unnumbered, sem::NamedProperty::Unnumbered>::read(::orgproto::NamedProperty::Unnumbered const& out, proto_write_accessor<sem::NamedProperty::Unnumbered> in) {

}

void proto_serde<::orgproto::NamedProperty::Created, sem::NamedProperty::Created>::write(::orgproto::NamedProperty::Created* out, sem::NamedProperty::Created const& in) {
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::NamedProperty::Created, sem::NamedProperty::Created>::read(::orgproto::NamedProperty::Created const& out, proto_write_accessor<sem::NamedProperty::Created> in) {
  proto_serde<orgproto::UserTime, UserTime>::read(out.time(), in.for_field(&sem::NamedProperty::Created::time));
}

void proto_serde<::orgproto::NamedProperty::RadioId, sem::NamedProperty::RadioId>::write(::orgproto::NamedProperty::RadioId* out, sem::NamedProperty::RadioId const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::write(out->mutable_words(), in.words);
}

void proto_serde<::orgproto::NamedProperty::RadioId, sem::NamedProperty::RadioId>::read(::orgproto::NamedProperty::RadioId const& out, proto_write_accessor<sem::NamedProperty::RadioId> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, hstd::Vec<hstd::Str>>::read(out.words(), in.for_field(&sem::NamedProperty::RadioId::words));
}

void proto_serde<::orgproto::NamedProperty::HashtagDef, sem::NamedProperty::HashtagDef>::write(::orgproto::NamedProperty::HashtagDef* out, sem::NamedProperty::HashtagDef const& in) {
  proto_serde<orgproto::HashTagText, sem::HashTagText>::write(out->mutable_hashtag(), in.hashtag);
}

void proto_serde<::orgproto::NamedProperty::HashtagDef, sem::NamedProperty::HashtagDef>::read(::orgproto::NamedProperty::HashtagDef const& out, proto_write_accessor<sem::NamedProperty::HashtagDef> in) {
  proto_serde<orgproto::HashTagText, sem::HashTagText>::read(out.hashtag(), in.for_field(&sem::NamedProperty::HashtagDef::hashtag));
}

void proto_serde<::orgproto::NamedProperty::CustomArgs, sem::NamedProperty::CustomArgs>::write(::orgproto::NamedProperty::CustomArgs* out, sem::NamedProperty::CustomArgs const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  if (in.sub) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_sub(), *in.sub);
  }
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void proto_serde<::orgproto::NamedProperty::CustomArgs, sem::NamedProperty::CustomArgs>::read(::orgproto::NamedProperty::CustomArgs const& out, proto_write_accessor<sem::NamedProperty::CustomArgs> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::NamedProperty::CustomArgs::name));
  if (out.has_sub()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.sub(), in.for_field(&sem::NamedProperty::CustomArgs::sub));
  }
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::read(out.attrs(), in.for_field(&sem::NamedProperty::CustomArgs::attrs));
}

void proto_serde<::orgproto::NamedProperty::CustomRaw, sem::NamedProperty::CustomRaw>::write(::orgproto::NamedProperty::CustomRaw* out, sem::NamedProperty::CustomRaw const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::NamedProperty::CustomRaw, sem::NamedProperty::CustomRaw>::read(::orgproto::NamedProperty::CustomRaw const& out, proto_write_accessor<sem::NamedProperty::CustomRaw> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::NamedProperty::CustomRaw::name));
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&sem::NamedProperty::CustomRaw::value));
}

void proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, sem::NamedProperty::CustomSubtreeJson>::write(::orgproto::NamedProperty::CustomSubtreeJson* out, sem::NamedProperty::CustomSubtreeJson const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::OrgJson, sem::OrgJson>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, sem::NamedProperty::CustomSubtreeJson>::read(::orgproto::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<sem::NamedProperty::CustomSubtreeJson> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::NamedProperty::CustomSubtreeJson::name));
  proto_serde<orgproto::OrgJson, sem::OrgJson>::read(out.value(), in.for_field(&sem::NamedProperty::CustomSubtreeJson::value));
}

void proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, sem::NamedProperty::CustomSubtreeFlags>::write(::orgproto::NamedProperty::CustomSubtreeFlags* out, sem::NamedProperty::CustomSubtreeFlags const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, sem::NamedProperty::CustomSubtreeFlags>::read(::orgproto::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<sem::NamedProperty::CustomSubtreeFlags> in) {
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&sem::NamedProperty::CustomSubtreeFlags::name));
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::read(out.value(), in.for_field(&sem::NamedProperty::CustomSubtreeFlags::value));
}

void proto_serde<::orgproto::NamedProperty, sem::NamedProperty>::write(::orgproto::NamedProperty* out, sem::NamedProperty const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::NamedProperty::Nonblocking, sem::NamedProperty::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveTime>::write(out->mutable_data()->mutable_archivetime(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveFile>::write(out->mutable_data()->mutable_archivefile(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveOlpath>::write(out->mutable_data()->mutable_archiveolpath(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveTarget>::write(out->mutable_data()->mutable_archivetarget(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveCategory>::write(out->mutable_data()->mutable_archivecategory(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::NamedProperty::ArchiveTodo, sem::NamedProperty::ArchiveTodo>::write(out->mutable_data()->mutable_archivetodo(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::NamedProperty::Trigger, sem::NamedProperty::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::NamedProperty::ExportLatexClass, sem::NamedProperty::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::NamedProperty::CookieData, sem::NamedProperty::CookieData>::write(out->mutable_data()->mutable_cookiedata(), std::get<9>(in.data));
      break;
    case 10:
      proto_serde<orgproto::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<10>(in.data));
      break;
    case 11:
      proto_serde<orgproto::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<11>(in.data));
      break;
    case 12:
      proto_serde<orgproto::NamedProperty::ExportLatexCompiler, sem::NamedProperty::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<12>(in.data));
      break;
    case 13:
      proto_serde<orgproto::NamedProperty::Ordered, sem::NamedProperty::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<13>(in.data));
      break;
    case 14:
      proto_serde<orgproto::NamedProperty::Effort, sem::NamedProperty::Effort>::write(out->mutable_data()->mutable_effort(), std::get<14>(in.data));
      break;
    case 15:
      proto_serde<orgproto::NamedProperty::Visibility, sem::NamedProperty::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<15>(in.data));
      break;
    case 16:
      proto_serde<orgproto::NamedProperty::ExportOptions, sem::NamedProperty::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<16>(in.data));
      break;
    case 17:
      proto_serde<orgproto::NamedProperty::Blocker, sem::NamedProperty::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<17>(in.data));
      break;
    case 18:
      proto_serde<orgproto::NamedProperty::Unnumbered, sem::NamedProperty::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<18>(in.data));
      break;
    case 19:
      proto_serde<orgproto::NamedProperty::Created, sem::NamedProperty::Created>::write(out->mutable_data()->mutable_created(), std::get<19>(in.data));
      break;
    case 20:
      proto_serde<orgproto::NamedProperty::RadioId, sem::NamedProperty::RadioId>::write(out->mutable_data()->mutable_radioid(), std::get<20>(in.data));
      break;
    case 21:
      proto_serde<orgproto::NamedProperty::HashtagDef, sem::NamedProperty::HashtagDef>::write(out->mutable_data()->mutable_hashtagdef(), std::get<21>(in.data));
      break;
    case 22:
      proto_serde<orgproto::NamedProperty::CustomArgs, sem::NamedProperty::CustomArgs>::write(out->mutable_data()->mutable_customargs(), std::get<22>(in.data));
      break;
    case 23:
      proto_serde<orgproto::NamedProperty::CustomRaw, sem::NamedProperty::CustomRaw>::write(out->mutable_data()->mutable_customraw(), std::get<23>(in.data));
      break;
    case 24:
      proto_serde<orgproto::NamedProperty::CustomSubtreeJson, sem::NamedProperty::CustomSubtreeJson>::write(out->mutable_data()->mutable_customsubtreejson(), std::get<24>(in.data));
      break;
    case 25:
      proto_serde<orgproto::NamedProperty::CustomSubtreeFlags, sem::NamedProperty::CustomSubtreeFlags>::write(out->mutable_data()->mutable_customsubtreeflags(), std::get<25>(in.data));
      break;
  }
}

void proto_serde<::orgproto::NamedProperty, sem::NamedProperty>::read(::orgproto::NamedProperty const& out, proto_write_accessor<sem::NamedProperty> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::NamedProperty::Data::kNonblocking:
      proto_serde<orgproto::NamedProperty::Nonblocking, sem::NamedProperty::Nonblocking>::read(out.data().nonblocking(), in.for_field_variant<0>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetime:
      proto_serde<orgproto::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveTime>::read(out.data().archivetime(), in.for_field_variant<1>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivefile:
      proto_serde<orgproto::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveFile>::read(out.data().archivefile(), in.for_field_variant<2>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchiveolpath:
      proto_serde<orgproto::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveOlpath>::read(out.data().archiveolpath(), in.for_field_variant<3>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetarget:
      proto_serde<orgproto::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveTarget>::read(out.data().archivetarget(), in.for_field_variant<4>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivecategory:
      proto_serde<orgproto::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveCategory>::read(out.data().archivecategory(), in.for_field_variant<5>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kArchivetodo:
      proto_serde<orgproto::NamedProperty::ArchiveTodo, sem::NamedProperty::ArchiveTodo>::read(out.data().archivetodo(), in.for_field_variant<6>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kTrigger:
      proto_serde<orgproto::NamedProperty::Trigger, sem::NamedProperty::Trigger>::read(out.data().trigger(), in.for_field_variant<7>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexclass:
      proto_serde<orgproto::NamedProperty::ExportLatexClass, sem::NamedProperty::ExportLatexClass>::read(out.data().exportlatexclass(), in.for_field_variant<8>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCookiedata:
      proto_serde<orgproto::NamedProperty::CookieData, sem::NamedProperty::CookieData>::read(out.data().cookiedata(), in.for_field_variant<9>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexclassoptions:
      proto_serde<orgproto::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexClassOptions>::read(out.data().exportlatexclassoptions(), in.for_field_variant<10>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexheader:
      proto_serde<orgproto::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexHeader>::read(out.data().exportlatexheader(), in.for_field_variant<11>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportlatexcompiler:
      proto_serde<orgproto::NamedProperty::ExportLatexCompiler, sem::NamedProperty::ExportLatexCompiler>::read(out.data().exportlatexcompiler(), in.for_field_variant<12>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kOrdered:
      proto_serde<orgproto::NamedProperty::Ordered, sem::NamedProperty::Ordered>::read(out.data().ordered(), in.for_field_variant<13>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kEffort:
      proto_serde<orgproto::NamedProperty::Effort, sem::NamedProperty::Effort>::read(out.data().effort(), in.for_field_variant<14>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kVisibility:
      proto_serde<orgproto::NamedProperty::Visibility, sem::NamedProperty::Visibility>::read(out.data().visibility(), in.for_field_variant<15>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kExportoptions:
      proto_serde<orgproto::NamedProperty::ExportOptions, sem::NamedProperty::ExportOptions>::read(out.data().exportoptions(), in.for_field_variant<16>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kBlocker:
      proto_serde<orgproto::NamedProperty::Blocker, sem::NamedProperty::Blocker>::read(out.data().blocker(), in.for_field_variant<17>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kUnnumbered:
      proto_serde<orgproto::NamedProperty::Unnumbered, sem::NamedProperty::Unnumbered>::read(out.data().unnumbered(), in.for_field_variant<18>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCreated:
      proto_serde<orgproto::NamedProperty::Created, sem::NamedProperty::Created>::read(out.data().created(), in.for_field_variant<19>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kRadioid:
      proto_serde<orgproto::NamedProperty::RadioId, sem::NamedProperty::RadioId>::read(out.data().radioid(), in.for_field_variant<20>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kHashtagdef:
      proto_serde<orgproto::NamedProperty::HashtagDef, sem::NamedProperty::HashtagDef>::read(out.data().hashtagdef(), in.for_field_variant<21>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomargs:
      proto_serde<orgproto::NamedProperty::CustomArgs, sem::NamedProperty::CustomArgs>::read(out.data().customargs(), in.for_field_variant<22>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomraw:
      proto_serde<orgproto::NamedProperty::CustomRaw, sem::NamedProperty::CustomRaw>::read(out.data().customraw(), in.for_field_variant<23>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomsubtreejson:
      proto_serde<orgproto::NamedProperty::CustomSubtreeJson, sem::NamedProperty::CustomSubtreeJson>::read(out.data().customsubtreejson(), in.for_field_variant<24>(&sem::NamedProperty::data));
      break;
    case ::orgproto::NamedProperty::Data::kCustomsubtreeflags:
      proto_serde<orgproto::NamedProperty::CustomSubtreeFlags, sem::NamedProperty::CustomSubtreeFlags>::read(out.data().customsubtreeflags(), in.for_field_variant<25>(&sem::NamedProperty::data));
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
  proto_serde<orgproto::ColumnView, sem::ColumnView>::write(out->mutable_view(), in.view);
}

void proto_serde<::orgproto::org::CmdColumns, org::sem::CmdColumns>::read(::orgproto::org::CmdColumns const& out, proto_write_accessor<org::sem::CmdColumns> in) {
  proto_serde<::orgproto::org::CmdColumns, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdColumns, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdColumns, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::ColumnView, sem::ColumnView>::read(out.view(), in.for_field(&org::sem::CmdColumns::view));
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
  proto_serde<orgproto::Tblfm, sem::Tblfm>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::org::CmdTblfm, org::sem::CmdTblfm>::read(::orgproto::org::CmdTblfm const& out, proto_write_accessor<org::sem::CmdTblfm> in) {
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Cmd>::read(out, in.as<org::sem::Cmd>());
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::CmdTblfm, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::Tblfm, sem::Tblfm>::read(out.expr(), in.for_field(&org::sem::CmdTblfm::expr));
}

void proto_serde<::orgproto::org::HashTag, org::sem::HashTag>::write(::orgproto::org::HashTag* out, org::sem::HashTag const& in) {
  proto_serde<::orgproto::org::HashTag, org::sem::Org>::write(out, in);
  proto_serde<orgproto::HashTagText, sem::HashTagText>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::org::HashTag, org::sem::HashTag>::read(::orgproto::org::HashTag const& out, proto_write_accessor<org::sem::HashTag> in) {
  proto_serde<::orgproto::org::HashTag, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::HashTagText, sem::HashTagText>::read(out.text(), in.for_field(&org::sem::HashTag::text));
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

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in) {
  out->set_mode(static_cast<orgproto::Time_Repeat_Mode>(in.mode));
  out->set_period(static_cast<orgproto::Time_Repeat_Period>(in.period));
  out->set_count(in.count);
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::read(::orgproto::Time::Repeat const& out, proto_write_accessor<sem::Time::Repeat> in) {
  in.for_field(&sem::Time::Repeat::mode).get() = static_cast<sem::Time::Repeat::Mode>(out.mode());
  in.for_field(&sem::Time::Repeat::period).get() = static_cast<sem::Time::Repeat::Period>(out.period());
  in.for_field(&sem::Time::Repeat::count).get() = out.count();
}

void proto_serde<::orgproto::Time::Static, sem::Time::Static>::write(::orgproto::Time::Static* out, sem::Time::Static const& in) {
  if (in.repeat) {
    proto_serde<orgproto::Time::Repeat, sem::Time::Repeat>::write(out->mutable_repeat(), *in.repeat);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::Time::Static, sem::Time::Static>::read(::orgproto::Time::Static const& out, proto_write_accessor<sem::Time::Static> in) {
  if (out.has_repeat()) {
    proto_serde<hstd::Opt<orgproto::Time::Repeat>, hstd::Opt<sem::Time::Repeat>>::read(out.repeat(), in.for_field(&sem::Time::Static::repeat));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.time(), in.for_field(&sem::Time::Static::time));
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::read(::orgproto::Time::Dynamic const& out, proto_write_accessor<sem::Time::Dynamic> in) {
  proto_serde<std::string, hstd::Str>::read(out.expr(), in.for_field(&sem::Time::Dynamic::expr));
}

void proto_serde<::orgproto::org::Time, org::sem::Time>::write(::orgproto::org::Time* out, org::sem::Time const& in) {
  proto_serde<::orgproto::org::Time, org::sem::Org>::write(out, in);
  out->set_isactive(in.isActive);
  switch (in.time.index()) {
    case 0:
      proto_serde<orgproto::Time::Static, sem::Time::Static>::write(out->mutable_time()->mutable_static_(), std::get<0>(in.time));
      break;
    case 1:
      proto_serde<orgproto::Time::Dynamic, sem::Time::Dynamic>::write(out->mutable_time()->mutable_dynamic(), std::get<1>(in.time));
      break;
  }
}

void proto_serde<::orgproto::org::Time, org::sem::Time>::read(::orgproto::org::Time const& out, proto_write_accessor<org::sem::Time> in) {
  proto_serde<::orgproto::org::Time, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::Time::isActive).get() = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::org::Time::TimeVariant::kStatic:
      proto_serde<orgproto::Time::Static, sem::Time::Static>::read(out.time().static_(), in.for_field_variant<0>(&org::sem::Time::time));
      break;
    case ::orgproto::org::Time::TimeVariant::kDynamic:
      proto_serde<orgproto::Time::Dynamic, sem::Time::Dynamic>::read(out.time().dynamic(), in.for_field_variant<1>(&org::sem::Time::time));
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
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
}

void proto_serde<::orgproto::org::Macro, org::sem::Macro>::read(::orgproto::org::Macro const& out, proto_write_accessor<org::sem::Macro> in) {
  proto_serde<::orgproto::org::Macro, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Macro::name));
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Macro::attrs));
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, hstd::Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::read(::orgproto::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in) {
  if (out.has_key()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.key(), in.for_field(&sem::Symbol::Param::key));
  }
  proto_serde<std::string, hstd::Str>::read(out.value(), in.for_field(&sem::Symbol::Param::value));
}

void proto_serde<::orgproto::org::Symbol, org::sem::Symbol>::write(::orgproto::org::Symbol* out, org::sem::Symbol const& in) {
  proto_serde<::orgproto::org::Symbol, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, hstd::Vec<sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, hstd::Vec<org::sem::SemId<org::sem::Org>>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::org::Symbol, org::sem::Symbol>::read(::orgproto::org::Symbol const& out, proto_write_accessor<org::sem::Symbol> in) {
  proto_serde<::orgproto::org::Symbol, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Symbol::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, hstd::Vec<sem::Symbol::Param>>::read(out.parameters(), in.for_field(&org::sem::Symbol::parameters));
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
  proto_serde<orgproto::LinkTarget, sem::LinkTarget>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::org::Link, org::sem::Link>::read(::orgproto::org::Link const& out, proto_write_accessor<org::sem::Link> in) {
  proto_serde<::orgproto::org::Link, org::sem::Stmt>::read(out, in.as<org::sem::Stmt>());
  proto_serde<::orgproto::org::Link, org::sem::Org>::read(out, in.as<org::sem::Org>());
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Link::description));
  }
  proto_serde<orgproto::LinkTarget, sem::LinkTarget>::read(out.target(), in.for_field(&org::sem::Link::target));
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
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeSwitch>, hstd::Vec<sem::BlockCodeSwitch>>::write(out->mutable_switches(), in.switches);
  out->set_exports(static_cast<orgproto::BlockCodeExports>(in.exports));
  if (in.result) {
    proto_serde<orgproto::BlockCodeEvalResult, sem::BlockCodeEvalResult>::write(out->mutable_result(), *in.result);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine>, hstd::Vec<sem::BlockCodeLine>>::write(out->mutable_lines(), in.lines);
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
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeSwitch>, hstd::Vec<sem::BlockCodeSwitch>>::read(out.switches(), in.for_field(&org::sem::BlockCode::switches));
  in.for_field(&org::sem::BlockCode::exports).get() = static_cast<BlockCodeExports>(out.exports());
  if (out.has_result()) {
    proto_serde<hstd::Opt<orgproto::BlockCodeEvalResult>, hstd::Opt<sem::BlockCodeEvalResult>>::read(out.result(), in.for_field(&org::sem::BlockCode::result));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCodeLine>, hstd::Vec<sem::BlockCodeLine>>::read(out.lines(), in.for_field(&org::sem::BlockCode::lines));
  in.for_field(&org::sem::BlockCode::cache).get() = out.cache();
  in.for_field(&org::sem::BlockCode::eval).get() = out.eval();
  in.for_field(&org::sem::BlockCode::noweb).get() = out.noweb();
  in.for_field(&org::sem::BlockCode::hlines).get() = out.hlines();
  in.for_field(&org::sem::BlockCode::tangle).get() = out.tangle();
}

void proto_serde<::orgproto::org::SubtreeLog, org::sem::SubtreeLog>::write(::orgproto::org::SubtreeLog* out, org::sem::SubtreeLog const& in) {
  proto_serde<::orgproto::org::SubtreeLog, org::sem::Org>::write(out, in);
  proto_serde<orgproto::SubtreeLogHead, sem::SubtreeLogHead>::write(out->mutable_head(), in.head);
  if (in.desc) {
    proto_serde<orgproto::org::StmtList, org::sem::SemId<org::sem::StmtList>>::write(out->mutable_desc(), *in.desc);
  }
}

void proto_serde<::orgproto::org::SubtreeLog, org::sem::SubtreeLog>::read(::orgproto::org::SubtreeLog const& out, proto_write_accessor<org::sem::SubtreeLog> in) {
  proto_serde<::orgproto::org::SubtreeLog, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<orgproto::SubtreeLogHead, sem::SubtreeLogHead>::read(out.head(), in.for_field(&org::sem::SubtreeLog::head));
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
    proto_serde<orgproto::SubtreeCompletion, sem::SubtreeCompletion>::write(out->mutable_completion(), *in.completion);
  }
  if (in.description) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::write(out->mutable_tags(), in.tags);
  if (!in.title.isNil()) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_title(), in.title);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::write(out->mutable_logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  if (in.closed) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_closed(), *in.closed);
  }
  if (in.deadline) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_deadline(), *in.deadline);
  }
  if (in.scheduled) {
    proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_scheduled(), *in.scheduled);
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
    proto_serde<hstd::Opt<orgproto::SubtreeCompletion>, hstd::Opt<sem::SubtreeCompletion>>::read(out.completion(), in.for_field(&org::sem::Subtree::completion));
  }
  if (out.has_description()) {
    proto_serde<hstd::Opt<orgproto::org::Paragraph>, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>>::read(out.description(), in.for_field(&org::sem::Subtree::description));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::HashTag>, hstd::Vec<org::sem::SemId<org::sem::HashTag>>>::read(out.tags(), in.for_field(&org::sem::Subtree::tags));
  proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::read(out.title(), in.for_field(&org::sem::Subtree::title));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::org::SubtreeLog>, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>::read(out.logbook(), in.for_field(&org::sem::Subtree::logbook));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::Subtree::properties));
  if (out.has_closed()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.closed(), in.for_field(&org::sem::Subtree::closed));
  }
  if (out.has_deadline()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.deadline(), in.for_field(&org::sem::Subtree::deadline));
  }
  if (out.has_scheduled()) {
    proto_serde<hstd::Opt<orgproto::UserTime>, hstd::Opt<UserTime>>::read(out.scheduled(), in.for_field(&org::sem::Subtree::scheduled));
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
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::write(out->mutable_attrs(), in.attrs);
  out->set_iscommand(in.isCommand);
}

void proto_serde<::orgproto::org::Call, org::sem::Call>::read(::orgproto::org::Call const& out, proto_write_accessor<org::sem::Call> in) {
  proto_serde<::orgproto::org::Call, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.name(), in.for_field(&org::sem::Call::name));
  proto_serde<orgproto::AttrGroup, sem::AttrGroup>::read(out.attrs(), in.for_field(&org::sem::Call::attrs));
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
  out->set_checkbox(static_cast<orgproto::ListItem_Checkbox>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::org::Paragraph, org::sem::SemId<org::sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
  if (in.bullet) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_bullet(), *in.bullet);
  }
}

void proto_serde<::orgproto::org::ListItem, org::sem::ListItem>::read(::orgproto::org::ListItem const& out, proto_write_accessor<org::sem::ListItem> in) {
  proto_serde<::orgproto::org::ListItem, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::ListItem::checkbox).get() = static_cast<sem::ListItem::Checkbox>(out.checkbox());
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
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<sem::NamedProperty>>::write(out->mutable_properties(), in.properties);
  proto_serde<orgproto::DocumentExportConfig, sem::DocumentExportConfig>::write(out->mutable_exportconfig(), in.exportConfig);
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
    proto_serde<orgproto::ColumnView, sem::ColumnView>::write(out->mutable_columns(), *in.columns);
  }
}

void proto_serde<::orgproto::org::DocumentOptions, org::sem::DocumentOptions>::read(::orgproto::org::DocumentOptions const& out, proto_write_accessor<org::sem::DocumentOptions> in) {
  proto_serde<::orgproto::org::DocumentOptions, org::sem::Org>::read(out, in.as<org::sem::Org>());
  in.for_field(&org::sem::DocumentOptions::initialVisibility).get() = static_cast<InitialSubtreeVisibility>(out.initialvisibility());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::NamedProperty>, hstd::Vec<sem::NamedProperty>>::read(out.properties(), in.for_field(&org::sem::DocumentOptions::properties));
  proto_serde<orgproto::DocumentExportConfig, sem::DocumentExportConfig>::read(out.exportconfig(), in.for_field(&org::sem::DocumentOptions::exportConfig));
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
    proto_serde<hstd::Opt<orgproto::ColumnView>, hstd::Opt<sem::ColumnView>>::read(out.columns(), in.for_field(&org::sem::DocumentOptions::columns));
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

void proto_serde<::orgproto::File::Document, sem::File::Document>::write(::orgproto::File::Document* out, sem::File::Document const& in) {

}

void proto_serde<::orgproto::File::Document, sem::File::Document>::read(::orgproto::File::Document const& out, proto_write_accessor<sem::File::Document> in) {

}

void proto_serde<::orgproto::File::Attachment, sem::File::Attachment>::write(::orgproto::File::Attachment* out, sem::File::Attachment const& in) {

}

void proto_serde<::orgproto::File::Attachment, sem::File::Attachment>::read(::orgproto::File::Attachment const& out, proto_write_accessor<sem::File::Attachment> in) {

}

void proto_serde<::orgproto::File::Source, sem::File::Source>::write(::orgproto::File::Source* out, sem::File::Source const& in) {

}

void proto_serde<::orgproto::File::Source, sem::File::Source>::read(::orgproto::File::Source const& out, proto_write_accessor<sem::File::Source> in) {

}

void proto_serde<::orgproto::org::File, org::sem::File>::write(::orgproto::org::File* out, org::sem::File const& in) {
  proto_serde<::orgproto::org::File, org::sem::Org>::write(out, in);
  proto_serde<std::string, hstd::Str>::write(out->mutable_relpath(), in.relPath);
  proto_serde<std::string, hstd::Str>::write(out->mutable_abspath(), in.absPath);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::File::Document, sem::File::Document>::write(out->mutable_data()->mutable_document(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::File::Attachment, sem::File::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::File::Source, sem::File::Source>::write(out->mutable_data()->mutable_source(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::org::File, org::sem::File>::read(::orgproto::org::File const& out, proto_write_accessor<org::sem::File> in) {
  proto_serde<::orgproto::org::File, org::sem::Org>::read(out, in.as<org::sem::Org>());
  proto_serde<std::string, hstd::Str>::read(out.relpath(), in.for_field(&org::sem::File::relPath));
  proto_serde<std::string, hstd::Str>::read(out.abspath(), in.for_field(&org::sem::File::absPath));
  switch (out.data().kind_case()) {
    case ::orgproto::org::File::Data::kDocument:
      proto_serde<orgproto::File::Document, sem::File::Document>::read(out.data().document(), in.for_field_variant<0>(&org::sem::File::data));
      break;
    case ::orgproto::org::File::Data::kAttachment:
      proto_serde<orgproto::File::Attachment, sem::File::Attachment>::read(out.data().attachment(), in.for_field_variant<1>(&org::sem::File::data));
      break;
    case ::orgproto::org::File::Data::kSource:
      proto_serde<orgproto::File::Source, sem::File::Source>::read(out.data().source(), in.for_field_variant<2>(&org::sem::File::data));
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

void proto_serde<::orgproto::CmdInclude::IncludeBase, sem::CmdInclude::IncludeBase>::write(::orgproto::CmdInclude::IncludeBase* out, sem::CmdInclude::IncludeBase const& in) {

}

void proto_serde<::orgproto::CmdInclude::IncludeBase, sem::CmdInclude::IncludeBase>::read(::orgproto::CmdInclude::IncludeBase const& out, proto_write_accessor<sem::CmdInclude::IncludeBase> in) {

}

void proto_serde<::orgproto::CmdInclude::Example, sem::CmdInclude::Example>::write(::orgproto::CmdInclude::Example* out, sem::CmdInclude::Example const& in) {

}

void proto_serde<::orgproto::CmdInclude::Example, sem::CmdInclude::Example>::read(::orgproto::CmdInclude::Example const& out, proto_write_accessor<sem::CmdInclude::Example> in) {

}

void proto_serde<::orgproto::CmdInclude::Export, sem::CmdInclude::Export>::write(::orgproto::CmdInclude::Export* out, sem::CmdInclude::Export const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void proto_serde<::orgproto::CmdInclude::Export, sem::CmdInclude::Export>::read(::orgproto::CmdInclude::Export const& out, proto_write_accessor<sem::CmdInclude::Export> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&sem::CmdInclude::Export::language));
}

void proto_serde<::orgproto::CmdInclude::Custom, sem::CmdInclude::Custom>::write(::orgproto::CmdInclude::Custom* out, sem::CmdInclude::Custom const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_blockname(), in.blockName);
}

void proto_serde<::orgproto::CmdInclude::Custom, sem::CmdInclude::Custom>::read(::orgproto::CmdInclude::Custom const& out, proto_write_accessor<sem::CmdInclude::Custom> in) {
  proto_serde<std::string, hstd::Str>::read(out.blockname(), in.for_field(&sem::CmdInclude::Custom::blockName));
}

void proto_serde<::orgproto::CmdInclude::Src, sem::CmdInclude::Src>::write(::orgproto::CmdInclude::Src* out, sem::CmdInclude::Src const& in) {
  proto_serde<std::string, hstd::Str>::write(out->mutable_language(), in.language);
}

void proto_serde<::orgproto::CmdInclude::Src, sem::CmdInclude::Src>::read(::orgproto::CmdInclude::Src const& out, proto_write_accessor<sem::CmdInclude::Src> in) {
  proto_serde<std::string, hstd::Str>::read(out.language(), in.for_field(&sem::CmdInclude::Src::language));
}

void proto_serde<::orgproto::CmdInclude::OrgDocument, sem::CmdInclude::OrgDocument>::write(::orgproto::CmdInclude::OrgDocument* out, sem::CmdInclude::OrgDocument const& in) {
  if (in.onlyContent) {
    out->set_onlycontent(*in.onlyContent);
  }
  if (in.subtreePath) {
    proto_serde<orgproto::SubtreePath, sem::SubtreePath>::write(out->mutable_subtreepath(), *in.subtreePath);
  }
  if (in.minLevel) {
    out->set_minlevel(*in.minLevel);
  }
  if (in.customIdTarget) {
    proto_serde<std::string, hstd::Str>::write(out->mutable_customidtarget(), *in.customIdTarget);
  }
}

void proto_serde<::orgproto::CmdInclude::OrgDocument, sem::CmdInclude::OrgDocument>::read(::orgproto::CmdInclude::OrgDocument const& out, proto_write_accessor<sem::CmdInclude::OrgDocument> in) {
  if (out.has_onlycontent()) {
    proto_serde<hstd::Opt<bool>, hstd::Opt<bool>>::read(out.onlycontent(), in.for_field(&sem::CmdInclude::OrgDocument::onlyContent));
  }
  if (out.has_subtreepath()) {
    proto_serde<hstd::Opt<orgproto::SubtreePath>, hstd::Opt<sem::SubtreePath>>::read(out.subtreepath(), in.for_field(&sem::CmdInclude::OrgDocument::subtreePath));
  }
  if (out.has_minlevel()) {
    proto_serde<hstd::Opt<::int32_t>, hstd::Opt<int>>::read(out.minlevel(), in.for_field(&sem::CmdInclude::OrgDocument::minLevel));
  }
  if (out.has_customidtarget()) {
    proto_serde<hstd::Opt<std::string>, hstd::Opt<hstd::Str>>::read(out.customidtarget(), in.for_field(&sem::CmdInclude::OrgDocument::customIdTarget));
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
      proto_serde<orgproto::CmdInclude::Example, sem::CmdInclude::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::CmdInclude::Export, sem::CmdInclude::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::CmdInclude::Custom, sem::CmdInclude::Custom>::write(out->mutable_data()->mutable_custom(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::CmdInclude::Src, sem::CmdInclude::Src>::write(out->mutable_data()->mutable_src(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::CmdInclude::OrgDocument, sem::CmdInclude::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<4>(in.data));
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
      proto_serde<orgproto::CmdInclude::Example, sem::CmdInclude::Example>::read(out.data().example(), in.for_field_variant<0>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kExport:
      proto_serde<orgproto::CmdInclude::Export, sem::CmdInclude::Export>::read(out.data().export_(), in.for_field_variant<1>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kCustom:
      proto_serde<orgproto::CmdInclude::Custom, sem::CmdInclude::Custom>::read(out.data().custom(), in.for_field_variant<2>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kSrc:
      proto_serde<orgproto::CmdInclude::Src, sem::CmdInclude::Src>::read(out.data().src(), in.for_field_variant<3>(&org::sem::CmdInclude::data));
      break;
    case ::orgproto::org::CmdInclude::Data::kOrgdocument:
      proto_serde<orgproto::CmdInclude::OrgDocument, sem::CmdInclude::OrgDocument>::read(out.data().orgdocument(), in.for_field_variant<4>(&org::sem::CmdInclude::data));
      break;
  }
}

/* clang-format on */