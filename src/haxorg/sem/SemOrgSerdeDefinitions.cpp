/* clang-format off */
#include <haxorg/sem/SemOrgSerde.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>
void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::write(::orgproto::CmdArgument* out, sem::CmdArgument const& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::write(out, in);
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  if (in.varname) {
    proto_serde<std::string, Str>::write(out->mutable_varname(), *in.varname);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::read(::orgproto::CmdArgument const& out, proto_write_accessor<sem::CmdArgument> in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_key()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.key(), in.for_field(&sem::CmdArgument::key));
  }
  if (out.has_varname()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.varname(), in.for_field(&sem::CmdArgument::varname));
  }
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::CmdArgument::value));
}

void proto_serde<::orgproto::CmdArgumentList, sem::CmdArgumentList>::write(::orgproto::CmdArgumentList* out, sem::CmdArgumentList const& in) {
  proto_serde<::orgproto::CmdArgumentList, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::write(out->mutable_args(), in.args);
}

void proto_serde<::orgproto::CmdArgumentList, sem::CmdArgumentList>::read(::orgproto::CmdArgumentList const& out, proto_write_accessor<sem::CmdArgumentList> in) {
  proto_serde<::orgproto::CmdArgumentList, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::read(out.args(), in.for_field(&sem::CmdArgumentList::args));
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::write(::orgproto::CmdArguments* out, sem::CmdArguments const& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::write(out, in);
  if (!in.positional.isNil()) {
    proto_serde<orgproto::CmdArgumentList, sem::SemId<sem::CmdArgumentList>>::write(out->mutable_positional(), in.positional);
  }
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgumentList>, UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::read(::orgproto::CmdArguments const& out, proto_write_accessor<sem::CmdArguments> in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::CmdArgumentList, sem::SemId<sem::CmdArgumentList>>::read(out.positional(), in.for_field(&sem::CmdArguments::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgumentList>, UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>>::read(out.named(), in.for_field(&sem::CmdArguments::named));
}

void proto_serde<::orgproto::ErrorItem, sem::ErrorItem>::write(::orgproto::ErrorItem* out, sem::ErrorItem const& in) {
  proto_serde<::orgproto::ErrorItem, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_message(), in.message);
  if (in.function) {
    proto_serde<std::string, Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    out->set_line(*in.line);
  }
}

void proto_serde<::orgproto::ErrorItem, sem::ErrorItem>::read(::orgproto::ErrorItem const& out, proto_write_accessor<sem::ErrorItem> in) {
  proto_serde<::orgproto::ErrorItem, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.message(), in.for_field(&sem::ErrorItem::message));
  if (out.has_function()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.function(), in.for_field(&sem::ErrorItem::function));
  }
  if (out.has_line()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.line(), in.for_field(&sem::ErrorItem::line));
  }
}

void proto_serde<::orgproto::ErrorGroup, sem::ErrorGroup>::write(::orgproto::ErrorGroup* out, sem::ErrorGroup const& in) {
  proto_serde<::orgproto::ErrorGroup, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, Vec<sem::SemId<sem::ErrorItem>>>::write(out->mutable_diagnostics(), in.diagnostics);
  if (in.function) {
    proto_serde<std::string, Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    proto_serde<std::string, Str>::write(out->mutable_line(), *in.line);
  }
}

void proto_serde<::orgproto::ErrorGroup, sem::ErrorGroup>::read(::orgproto::ErrorGroup const& out, proto_write_accessor<sem::ErrorGroup> in) {
  proto_serde<::orgproto::ErrorGroup, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, Vec<sem::SemId<sem::ErrorItem>>>::read(out.diagnostics(), in.for_field(&sem::ErrorGroup::diagnostics));
  if (out.has_function()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.function(), in.for_field(&sem::ErrorGroup::function));
  }
  if (out.has_line()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.line(), in.for_field(&sem::ErrorGroup::line));
  }
}

void proto_serde<::orgproto::StmtList, sem::StmtList>::write(::orgproto::StmtList* out, sem::StmtList const& in) {
  proto_serde<::orgproto::StmtList, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::StmtList, sem::StmtList>::read(::orgproto::StmtList const& out, proto_write_accessor<sem::StmtList> in) {
  proto_serde<::orgproto::StmtList, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Empty, sem::Empty>::write(::orgproto::Empty* out, sem::Empty const& in) {
  proto_serde<::orgproto::Empty, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Empty, sem::Empty>::read(::orgproto::Empty const& out, proto_write_accessor<sem::Empty> in) {
  proto_serde<::orgproto::Empty, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdCaption, sem::CmdCaption>::write(::orgproto::CmdCaption* out, sem::CmdCaption const& in) {
  proto_serde<::orgproto::CmdCaption, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdCaption, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCaption, sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::CmdCaption, sem::CmdCaption>::read(::orgproto::CmdCaption const& out, proto_write_accessor<sem::CmdCaption> in) {
  proto_serde<::orgproto::CmdCaption, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdCaption, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCaption, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&sem::CmdCaption::text));
}

void proto_serde<::orgproto::CmdName, sem::CmdName>::write(::orgproto::CmdName* out, sem::CmdName const& in) {
  proto_serde<::orgproto::CmdName, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdName, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdName, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::CmdName, sem::CmdName>::read(::orgproto::CmdName const& out, proto_write_accessor<sem::CmdName> in) {
  proto_serde<::orgproto::CmdName, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdName, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdName, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::CmdName::name));
}

void proto_serde<::orgproto::CmdCustomArgs, sem::CmdCustomArgs>::write(::orgproto::CmdCustomArgs* out, sem::CmdCustomArgs const& in) {
  proto_serde<::orgproto::CmdCustomArgs, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdCustomArgs, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomArgs, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
}

void proto_serde<::orgproto::CmdCustomArgs, sem::CmdCustomArgs>::read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<sem::CmdCustomArgs> in) {
  proto_serde<::orgproto::CmdCustomArgs, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdCustomArgs, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomArgs, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::CmdCustomArgs::name));
  in.for_field(&sem::CmdCustomArgs::isAttached).get() = out.isattached();
}

void proto_serde<::orgproto::CmdCustomRaw, sem::CmdCustomRaw>::write(::orgproto::CmdCustomRaw* out, sem::CmdCustomRaw const& in) {
  proto_serde<::orgproto::CmdCustomRaw, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomRaw, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::CmdCustomRaw, sem::CmdCustomRaw>::read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<sem::CmdCustomRaw> in) {
  proto_serde<::orgproto::CmdCustomRaw, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomRaw, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::CmdCustomRaw::name));
  in.for_field(&sem::CmdCustomRaw::isAttached).get() = out.isattached();
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::CmdCustomRaw::text));
}

void proto_serde<::orgproto::CmdCustomText, sem::CmdCustomText>::write(::orgproto::CmdCustomText* out, sem::CmdCustomText const& in) {
  proto_serde<::orgproto::CmdCustomText, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomText, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::CmdCustomText, sem::CmdCustomText>::read(::orgproto::CmdCustomText const& out, proto_write_accessor<sem::CmdCustomText> in) {
  proto_serde<::orgproto::CmdCustomText, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomText, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::CmdCustomText::name));
  in.for_field(&sem::CmdCustomText::isAttached).get() = out.isattached();
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&sem::CmdCustomText::text));
}

void proto_serde<::orgproto::CmdResults, sem::CmdResults>::write(::orgproto::CmdResults* out, sem::CmdResults const& in) {
  proto_serde<::orgproto::CmdResults, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdResults, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdResults, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdResults, sem::CmdResults>::read(::orgproto::CmdResults const& out, proto_write_accessor<sem::CmdResults> in) {
  proto_serde<::orgproto::CmdResults, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdResults, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdResults, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdTblfm, sem::CmdTblfm>::write(::orgproto::CmdTblfm* out, sem::CmdTblfm const& in) {
  proto_serde<::orgproto::CmdTblfm, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdTblfm, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdTblfm, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdTblfm, sem::CmdTblfm>::read(::orgproto::CmdTblfm const& out, proto_write_accessor<sem::CmdTblfm> in) {
  proto_serde<::orgproto::CmdTblfm, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdTblfm, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdTblfm, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::HashTag, sem::HashTag>::write(::orgproto::HashTag* out, sem::HashTag const& in) {
  proto_serde<::orgproto::HashTag, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::HashTag, sem::HashTag>::read(::orgproto::HashTag const& out, proto_write_accessor<sem::HashTag> in) {
  proto_serde<::orgproto::HashTag, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.head(), in.for_field(&sem::HashTag::head));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.subtags(), in.for_field(&sem::HashTag::subtags));
}

void proto_serde<::orgproto::Footnote, sem::Footnote>::write(::orgproto::Footnote* out, sem::Footnote const& in) {
  proto_serde<::orgproto::Footnote, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(out->mutable_definition(), *in.definition);
  }
}

void proto_serde<::orgproto::Footnote, sem::Footnote>::read(::orgproto::Footnote const& out, proto_write_accessor<sem::Footnote> in) {
  proto_serde<::orgproto::Footnote, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.tag(), in.for_field(&sem::Footnote::tag));
  if (out.has_definition()) {
    proto_serde<Opt<orgproto::AnyNode>, Opt<sem::SemId<sem::Org>>>::read(out.definition(), in.for_field(&sem::Footnote::definition));
  }
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in) {
  proto_serde<orgproto::Time::Repeat::Mode, sem::Time::Repeat::Mode>::write(out->mutable_mode(), in.mode);
  proto_serde<orgproto::Time::Repeat::Period, sem::Time::Repeat::Period>::write(out->mutable_period(), in.period);
  out->set_count(in.count);
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::read(::orgproto::Time::Repeat const& out, proto_write_accessor<sem::Time::Repeat> in) {
  proto_serde<orgproto::Time::Repeat::Mode, sem::Time::Repeat::Mode>::read(out.mode(), in.for_field(&sem::Time::Repeat::mode));
  proto_serde<orgproto::Time::Repeat::Period, sem::Time::Repeat::Period>::read(out.period(), in.for_field(&sem::Time::Repeat::period));
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
    proto_serde<Opt<orgproto::Time::Repeat>, Opt<sem::Time::Repeat>>::read(out.repeat(), in.for_field(&sem::Time::Static::repeat));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.time(), in.for_field(&sem::Time::Static::time));
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in) {
  proto_serde<std::string, Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::read(::orgproto::Time::Dynamic const& out, proto_write_accessor<sem::Time::Dynamic> in) {
  proto_serde<std::string, Str>::read(out.expr(), in.for_field(&sem::Time::Dynamic::expr));
}

void proto_serde<::orgproto::Time, sem::Time>::write(::orgproto::Time* out, sem::Time const& in) {
  proto_serde<::orgproto::Time, sem::Org>::write(out, in);
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

void proto_serde<::orgproto::Time, sem::Time>::read(::orgproto::Time const& out, proto_write_accessor<sem::Time> in) {
  proto_serde<::orgproto::Time, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::Time::isActive).get() = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::Time::TimeVariant::kStatic:
      proto_serde<orgproto::Time::Static, sem::Time::Static>::read(out.time().static_(), in.for_field_variant<0>(&sem::Time::time));
      break;
    case ::orgproto::Time::TimeVariant::kDynamic:
      proto_serde<orgproto::Time::Dynamic, sem::Time::Dynamic>::read(out.time().dynamic(), in.for_field_variant<1>(&sem::Time::time));
      break;
  }
}

void proto_serde<::orgproto::TimeRange, sem::TimeRange>::write(::orgproto::TimeRange* out, sem::TimeRange const& in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (!in.to.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), in.to);
  }
}

void proto_serde<::orgproto::TimeRange, sem::TimeRange>::read(::orgproto::TimeRange const& out, proto_write_accessor<sem::TimeRange> in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&sem::TimeRange::from));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.to(), in.for_field(&sem::TimeRange::to));
}

void proto_serde<::orgproto::Macro, sem::Macro>::write(::orgproto::Macro* out, sem::Macro const& in) {
  proto_serde<::orgproto::Macro, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
}

void proto_serde<::orgproto::Macro, sem::Macro>::read(::orgproto::Macro const& out, proto_write_accessor<sem::Macro> in) {
  proto_serde<::orgproto::Macro, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Macro::name));
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&sem::Macro::parameters));
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::read(::orgproto::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in) {
  if (out.has_key()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.key(), in.for_field(&sem::Symbol::Param::key));
  }
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::Symbol::Param::value));
}

void proto_serde<::orgproto::Symbol, sem::Symbol>::write(::orgproto::Symbol* out, sem::Symbol const& in) {
  proto_serde<::orgproto::Symbol, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId<sem::Org>>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::Symbol, sem::Symbol>::read(::orgproto::Symbol const& out, proto_write_accessor<sem::Symbol> in) {
  proto_serde<::orgproto::Symbol, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Symbol::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::read(out.parameters(), in.for_field(&sem::Symbol::parameters));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId<sem::Org>>>::read(out.positional(), in.for_field(&sem::Symbol::positional));
}

void proto_serde<::orgproto::Escaped, sem::Escaped>::write(::orgproto::Escaped* out, sem::Escaped const& in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Escaped, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Escaped, sem::Escaped>::read(::orgproto::Escaped const& out, proto_write_accessor<sem::Escaped> in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Escaped, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Newline, sem::Newline>::write(::orgproto::Newline* out, sem::Newline const& in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Newline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Newline, sem::Newline>::read(::orgproto::Newline const& out, proto_write_accessor<sem::Newline> in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Newline, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Space, sem::Space>::write(::orgproto::Space* out, sem::Space const& in) {
  proto_serde<::orgproto::Space, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Space, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Space, sem::Space>::read(::orgproto::Space const& out, proto_write_accessor<sem::Space> in) {
  proto_serde<::orgproto::Space, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Space, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Word, sem::Word>::write(::orgproto::Word* out, sem::Word const& in) {
  proto_serde<::orgproto::Word, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Word, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Word, sem::Word>::read(::orgproto::Word const& out, proto_write_accessor<sem::Word> in) {
  proto_serde<::orgproto::Word, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Word, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::AtMention, sem::AtMention>::write(::orgproto::AtMention* out, sem::AtMention const& in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::AtMention, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AtMention, sem::AtMention>::read(::orgproto::AtMention const& out, proto_write_accessor<sem::AtMention> in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::AtMention, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::RawText, sem::RawText>::write(::orgproto::RawText* out, sem::RawText const& in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RawText, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RawText, sem::RawText>::read(::orgproto::RawText const& out, proto_write_accessor<sem::RawText> in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::RawText, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Punctuation, sem::Punctuation>::write(::orgproto::Punctuation* out, sem::Punctuation const& in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Punctuation, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Punctuation, sem::Punctuation>::read(::orgproto::Punctuation const& out, proto_write_accessor<sem::Punctuation> in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Punctuation, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Placeholder, sem::Placeholder>::write(::orgproto::Placeholder* out, sem::Placeholder const& in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Placeholder, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Placeholder, sem::Placeholder>::read(::orgproto::Placeholder const& out, proto_write_accessor<sem::Placeholder> in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Placeholder, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BigIdent, sem::BigIdent>::write(::orgproto::BigIdent* out, sem::BigIdent const& in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::BigIdent, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BigIdent, sem::BigIdent>::read(::orgproto::BigIdent const& out, proto_write_accessor<sem::BigIdent> in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::BigIdent, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::RadioTarget, sem::RadioTarget>::write(::orgproto::RadioTarget* out, sem::RadioTarget const& in) {
  proto_serde<::orgproto::RadioTarget, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RadioTarget, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RadioTarget, sem::RadioTarget>::read(::orgproto::RadioTarget const& out, proto_write_accessor<sem::RadioTarget> in) {
  proto_serde<::orgproto::RadioTarget, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::RadioTarget, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::TextTarget, sem::TextTarget>::write(::orgproto::TextTarget* out, sem::TextTarget const& in) {
  proto_serde<::orgproto::TextTarget, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::TextTarget, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::TextTarget, sem::TextTarget>::read(::orgproto::TextTarget const& out, proto_write_accessor<sem::TextTarget> in) {
  proto_serde<::orgproto::TextTarget, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::TextTarget, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Bold, sem::Bold>::write(::orgproto::Bold* out, sem::Bold const& in) {
  proto_serde<::orgproto::Bold, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Bold, sem::Bold>::read(::orgproto::Bold const& out, proto_write_accessor<sem::Bold> in) {
  proto_serde<::orgproto::Bold, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Underline, sem::Underline>::write(::orgproto::Underline* out, sem::Underline const& in) {
  proto_serde<::orgproto::Underline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Underline, sem::Underline>::read(::orgproto::Underline const& out, proto_write_accessor<sem::Underline> in) {
  proto_serde<::orgproto::Underline, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Monospace, sem::Monospace>::write(::orgproto::Monospace* out, sem::Monospace const& in) {
  proto_serde<::orgproto::Monospace, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Monospace, sem::Monospace>::read(::orgproto::Monospace const& out, proto_write_accessor<sem::Monospace> in) {
  proto_serde<::orgproto::Monospace, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::MarkQuote, sem::MarkQuote>::write(::orgproto::MarkQuote* out, sem::MarkQuote const& in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::MarkQuote, sem::MarkQuote>::read(::orgproto::MarkQuote const& out, proto_write_accessor<sem::MarkQuote> in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Verbatim, sem::Verbatim>::write(::orgproto::Verbatim* out, sem::Verbatim const& in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Verbatim, sem::Verbatim>::read(::orgproto::Verbatim const& out, proto_write_accessor<sem::Verbatim> in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Italic, sem::Italic>::write(::orgproto::Italic* out, sem::Italic const& in) {
  proto_serde<::orgproto::Italic, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Italic, sem::Italic>::read(::orgproto::Italic const& out, proto_write_accessor<sem::Italic> in) {
  proto_serde<::orgproto::Italic, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Strike, sem::Strike>::write(::orgproto::Strike* out, sem::Strike const& in) {
  proto_serde<::orgproto::Strike, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Strike, sem::Strike>::read(::orgproto::Strike const& out, proto_write_accessor<sem::Strike> in) {
  proto_serde<::orgproto::Strike, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Par, sem::Par>::write(::orgproto::Par* out, sem::Par const& in) {
  proto_serde<::orgproto::Par, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Par, sem::Par>::read(::orgproto::Par const& out, proto_write_accessor<sem::Par> in) {
  proto_serde<::orgproto::Par, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Latex, sem::Latex>::write(::orgproto::Latex* out, sem::Latex const& in) {
  proto_serde<::orgproto::Latex, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Latex, sem::Latex>::read(::orgproto::Latex const& out, proto_write_accessor<sem::Latex> in) {
  proto_serde<::orgproto::Latex, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Link::Raw, sem::Link::Raw>::write(::orgproto::Link::Raw* out, sem::Link::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Raw, sem::Link::Raw>::read(::orgproto::Link::Raw const& out, proto_write_accessor<sem::Link::Raw> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::Link::Raw::text));
}

void proto_serde<::orgproto::Link::Id, sem::Link::Id>::write(::orgproto::Link::Id* out, sem::Link::Id const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Id, sem::Link::Id>::read(::orgproto::Link::Id const& out, proto_write_accessor<sem::Link::Id> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::Link::Id::text));
}

void proto_serde<::orgproto::Link::Person, sem::Link::Person>::write(::orgproto::Link::Person* out, sem::Link::Person const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Link::Person, sem::Link::Person>::read(::orgproto::Link::Person const& out, proto_write_accessor<sem::Link::Person> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Link::Person::name));
}

void proto_serde<::orgproto::Link::UserProtocol, sem::Link::UserProtocol>::write(::orgproto::Link::UserProtocol* out, sem::Link::UserProtocol const& in) {
  proto_serde<std::string, Str>::write(out->mutable_protocol(), in.protocol);
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Link::UserProtocol, sem::Link::UserProtocol>::read(::orgproto::Link::UserProtocol const& out, proto_write_accessor<sem::Link::UserProtocol> in) {
  proto_serde<std::string, Str>::read(out.protocol(), in.for_field(&sem::Link::UserProtocol::protocol));
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::UserProtocol::target));
}

void proto_serde<::orgproto::Link::Internal, sem::Link::Internal>::write(::orgproto::Link::Internal* out, sem::Link::Internal const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Link::Internal, sem::Link::Internal>::read(::orgproto::Link::Internal const& out, proto_write_accessor<sem::Link::Internal> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::Internal::target));
}

void proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote>::write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote>::read(::orgproto::Link::Footnote const& out, proto_write_accessor<sem::Link::Footnote> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::Footnote::target));
}

void proto_serde<::orgproto::Link::File, sem::Link::File>::write(::orgproto::Link::File* out, sem::Link::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::Link::File, sem::Link::File>::read(::orgproto::Link::File const& out, proto_write_accessor<sem::Link::File> in) {
  proto_serde<std::string, Str>::read(out.file(), in.for_field(&sem::Link::File::file));
}

void proto_serde<::orgproto::Link::Attachment, sem::Link::Attachment>::write(::orgproto::Link::Attachment* out, sem::Link::Attachment const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::Link::Attachment, sem::Link::Attachment>::read(::orgproto::Link::Attachment const& out, proto_write_accessor<sem::Link::Attachment> in) {
  proto_serde<std::string, Str>::read(out.file(), in.for_field(&sem::Link::Attachment::file));
}

void proto_serde<::orgproto::Link, sem::Link>::write(::orgproto::Link* out, sem::Link const& in) {
  proto_serde<::orgproto::Link, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Link, sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Link::Raw, sem::Link::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Link::Id, sem::Link::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Link::Person, sem::Link::Person>::write(out->mutable_data()->mutable_person(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Link::UserProtocol, sem::Link::UserProtocol>::write(out->mutable_data()->mutable_userprotocol(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Link::Internal, sem::Link::Internal>::write(out->mutable_data()->mutable_internal(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::Link::Footnote, sem::Link::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::Link::File, sem::Link::File>::write(out->mutable_data()->mutable_file(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::Link::Attachment, sem::Link::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<7>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Link, sem::Link>::read(::orgproto::Link const& out, proto_write_accessor<sem::Link> in) {
  proto_serde<::orgproto::Link, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Link, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_description()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.description(), in.for_field(&sem::Link::description));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::Link::Data::kRaw:
      proto_serde<orgproto::Link::Raw, sem::Link::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kId:
      proto_serde<orgproto::Link::Id, sem::Link::Id>::read(out.data().id(), in.for_field_variant<1>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kPerson:
      proto_serde<orgproto::Link::Person, sem::Link::Person>::read(out.data().person(), in.for_field_variant<2>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kUserprotocol:
      proto_serde<orgproto::Link::UserProtocol, sem::Link::UserProtocol>::read(out.data().userprotocol(), in.for_field_variant<3>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kInternal:
      proto_serde<orgproto::Link::Internal, sem::Link::Internal>::read(out.data().internal(), in.for_field_variant<4>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kFootnote:
      proto_serde<orgproto::Link::Footnote, sem::Link::Footnote>::read(out.data().footnote(), in.for_field_variant<5>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kFile:
      proto_serde<orgproto::Link::File, sem::Link::File>::read(out.data().file(), in.for_field_variant<6>(&sem::Link::data));
      break;
    case ::orgproto::Link::Data::kAttachment:
      proto_serde<orgproto::Link::Attachment, sem::Link::Attachment>::read(out.data().attachment(), in.for_field_variant<7>(&sem::Link::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCenter, sem::BlockCenter>::write(::orgproto::BlockCenter* out, sem::BlockCenter const& in) {
  proto_serde<::orgproto::BlockCenter, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockCenter, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockCenter, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockCenter, sem::BlockCenter>::read(::orgproto::BlockCenter const& out, proto_write_accessor<sem::BlockCenter> in) {
  proto_serde<::orgproto::BlockCenter, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockCenter, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockCenter, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockQuote, sem::BlockQuote>::write(::orgproto::BlockQuote* out, sem::BlockQuote const& in) {
  proto_serde<::orgproto::BlockQuote, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockQuote, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockQuote, sem::BlockQuote>::read(::orgproto::BlockQuote const& out, proto_write_accessor<sem::BlockQuote> in) {
  proto_serde<::orgproto::BlockQuote, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockQuote, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockQuote, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockComment, sem::BlockComment>::write(::orgproto::BlockComment* out, sem::BlockComment const& in) {
  proto_serde<::orgproto::BlockComment, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockComment, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockComment, sem::BlockComment>::read(::orgproto::BlockComment const& out, proto_write_accessor<sem::BlockComment> in) {
  proto_serde<::orgproto::BlockComment, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockComment, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockVerse, sem::BlockVerse>::write(::orgproto::BlockVerse* out, sem::BlockVerse const& in) {
  proto_serde<::orgproto::BlockVerse, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockVerse, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockVerse, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockVerse, sem::BlockVerse>::read(::orgproto::BlockVerse const& out, proto_write_accessor<sem::BlockVerse> in) {
  proto_serde<::orgproto::BlockVerse, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockVerse, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockVerse, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockExample, sem::BlockExample>::write(::orgproto::BlockExample* out, sem::BlockExample const& in) {
  proto_serde<::orgproto::BlockExample, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockExample, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockExample, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockExample, sem::BlockExample>::read(::orgproto::BlockExample const& out, proto_write_accessor<sem::BlockExample> in) {
  proto_serde<::orgproto::BlockExample, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockExample, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockExample, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockExport, sem::BlockExport>::write(::orgproto::BlockExport* out, sem::BlockExport const& in) {
  proto_serde<::orgproto::BlockExport, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockExport, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockExport, sem::Org>::write(out, in);
  proto_serde<orgproto::BlockExport::Format, sem::BlockExport::Format>::write(out->mutable_format(), in.format);
  proto_serde<std::string, Str>::write(out->mutable_exporter(), in.exporter);
  if (in.placement) {
    proto_serde<std::string, Str>::write(out->mutable_placement(), *in.placement);
  }
  proto_serde<std::string, Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::BlockExport, sem::BlockExport>::read(::orgproto::BlockExport const& out, proto_write_accessor<sem::BlockExport> in) {
  proto_serde<::orgproto::BlockExport, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockExport, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockExport, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::BlockExport::Format, sem::BlockExport::Format>::read(out.format(), in.for_field(&sem::BlockExport::format));
  proto_serde<std::string, Str>::read(out.exporter(), in.for_field(&sem::BlockExport::exporter));
  if (out.has_placement()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.placement(), in.for_field(&sem::BlockExport::placement));
  }
  proto_serde<std::string, Str>::read(out.content(), in.for_field(&sem::BlockExport::content));
}

void proto_serde<::orgproto::BlockAdmonition, sem::BlockAdmonition>::write(::orgproto::BlockAdmonition* out, sem::BlockAdmonition const& in) {
  proto_serde<::orgproto::BlockAdmonition, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockAdmonition, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockAdmonition, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockAdmonition, sem::BlockAdmonition>::read(::orgproto::BlockAdmonition const& out, proto_write_accessor<sem::BlockAdmonition> in) {
  proto_serde<::orgproto::BlockAdmonition, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockAdmonition, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockAdmonition, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::write(::orgproto::BlockCode::Line::Part::Raw* out, sem::BlockCode::Line::Part::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_code(), in.code);
}

void proto_serde<::orgproto::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::read(::orgproto::BlockCode::Line::Part::Raw const& out, proto_write_accessor<sem::BlockCode::Line::Part::Raw> in) {
  proto_serde<std::string, Str>::read(out.code(), in.for_field(&sem::BlockCode::Line::Part::Raw::code));
}

void proto_serde<::orgproto::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::write(::orgproto::BlockCode::Line::Part::Callout* out, sem::BlockCode::Line::Part::Callout const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::read(::orgproto::BlockCode::Line::Part::Callout const& out, proto_write_accessor<sem::BlockCode::Line::Part::Callout> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::BlockCode::Line::Part::Callout::name));
}

void proto_serde<::orgproto::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::write(::orgproto::BlockCode::Line::Part::Tangle* out, sem::BlockCode::Line::Part::Tangle const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::read(::orgproto::BlockCode::Line::Part::Tangle const& out, proto_write_accessor<sem::BlockCode::Line::Part::Tangle> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::BlockCode::Line::Part::Tangle::target));
}

void proto_serde<::orgproto::BlockCode::Line::Part, sem::BlockCode::Line::Part>::write(::orgproto::BlockCode::Line::Part* out, sem::BlockCode::Line::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode::Line::Part, sem::BlockCode::Line::Part>::read(::orgproto::BlockCode::Line::Part const& out, proto_write_accessor<sem::BlockCode::Line::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCode::Line::Part::Data::kRaw:
      proto_serde<orgproto::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::BlockCode::Line::Part::data));
      break;
    case ::orgproto::BlockCode::Line::Part::Data::kCallout:
      proto_serde<orgproto::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&sem::BlockCode::Line::Part::data));
      break;
    case ::orgproto::BlockCode::Line::Part::Data::kTangle:
      proto_serde<orgproto::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&sem::BlockCode::Line::Part::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode::Line, sem::BlockCode::Line>::write(::orgproto::BlockCode::Line* out, sem::BlockCode::Line const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line::Part>, Vec<sem::BlockCode::Line::Part>>::write(out->mutable_parts(), in.parts);
}

void proto_serde<::orgproto::BlockCode::Line, sem::BlockCode::Line>::read(::orgproto::BlockCode::Line const& out, proto_write_accessor<sem::BlockCode::Line> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line::Part>, Vec<sem::BlockCode::Line::Part>>::read(out.parts(), in.for_field(&sem::BlockCode::Line::parts));
}

void proto_serde<::orgproto::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::write(::orgproto::BlockCode::Switch::LineStart* out, sem::BlockCode::Switch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::read(::orgproto::BlockCode::Switch::LineStart const& out, proto_write_accessor<sem::BlockCode::Switch::LineStart> in) {
  in.for_field(&sem::BlockCode::Switch::LineStart::start).get() = out.start();
  in.for_field(&sem::BlockCode::Switch::LineStart::extendLast).get() = out.extendlast();
}

void proto_serde<::orgproto::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::write(::orgproto::BlockCode::Switch::CalloutFormat* out, sem::BlockCode::Switch::CalloutFormat const& in) {
  proto_serde<std::string, Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::read(::orgproto::BlockCode::Switch::CalloutFormat const& out, proto_write_accessor<sem::BlockCode::Switch::CalloutFormat> in) {
  proto_serde<std::string, Str>::read(out.format(), in.for_field(&sem::BlockCode::Switch::CalloutFormat::format));
}

void proto_serde<::orgproto::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::write(::orgproto::BlockCode::Switch::RemoveCallout* out, sem::BlockCode::Switch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::read(::orgproto::BlockCode::Switch::RemoveCallout const& out, proto_write_accessor<sem::BlockCode::Switch::RemoveCallout> in) {
  in.for_field(&sem::BlockCode::Switch::RemoveCallout::remove).get() = out.remove();
}

void proto_serde<::orgproto::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::write(::orgproto::BlockCode::Switch::EmphasizeLine* out, sem::BlockCode::Switch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::read(::orgproto::BlockCode::Switch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCode::Switch::EmphasizeLine> in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::read(out.line(), in.for_field(&sem::BlockCode::Switch::EmphasizeLine::line));
}

void proto_serde<::orgproto::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::write(::orgproto::BlockCode::Switch::Dedent* out, sem::BlockCode::Switch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::read(::orgproto::BlockCode::Switch::Dedent const& out, proto_write_accessor<sem::BlockCode::Switch::Dedent> in) {
  in.for_field(&sem::BlockCode::Switch::Dedent::value).get() = out.value();
}

void proto_serde<::orgproto::Switch, Switch>::write(::orgproto::Switch* out, Switch const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Switch, Switch>::read(::orgproto::Switch const& out, proto_write_accessor<Switch> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Switch::Data::kLinestart:
      proto_serde<orgproto::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::read(out.data().linestart(), in.for_field_variant<0>(&Switch::data));
      break;
    case ::orgproto::Switch::Data::kCalloutformat:
      proto_serde<orgproto::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::read(out.data().calloutformat(), in.for_field_variant<1>(&Switch::data));
      break;
    case ::orgproto::Switch::Data::kRemovecallout:
      proto_serde<orgproto::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::read(out.data().removecallout(), in.for_field_variant<2>(&Switch::data));
      break;
    case ::orgproto::Switch::Data::kEmphasizeline:
      proto_serde<orgproto::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::read(out.data().emphasizeline(), in.for_field_variant<3>(&Switch::data));
      break;
    case ::orgproto::Switch::Data::kDedent:
      proto_serde<orgproto::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::read(out.data().dedent(), in.for_field_variant<4>(&Switch::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::write(::orgproto::BlockCode::EvalResult::None* out, sem::BlockCode::EvalResult::None const& in) {

}

void proto_serde<::orgproto::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::read(::orgproto::BlockCode::EvalResult::None const& out, proto_write_accessor<sem::BlockCode::EvalResult::None> in) {

}

void proto_serde<::orgproto::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::write(::orgproto::BlockCode::EvalResult::OrgValue* out, sem::BlockCode::EvalResult::OrgValue const& in) {
  if (!in.value.isNil()) {
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(out->mutable_value(), in.value);
  }
}

void proto_serde<::orgproto::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::read(::orgproto::BlockCode::EvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCode::EvalResult::OrgValue> in) {
  proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(out.value(), in.for_field(&sem::BlockCode::EvalResult::OrgValue::value));
}

void proto_serde<::orgproto::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::write(::orgproto::BlockCode::EvalResult::File* out, sem::BlockCode::EvalResult::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::read(::orgproto::BlockCode::EvalResult::File const& out, proto_write_accessor<sem::BlockCode::EvalResult::File> in) {
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&sem::BlockCode::EvalResult::File::path));
}

void proto_serde<::orgproto::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::write(::orgproto::BlockCode::EvalResult::Raw* out, sem::BlockCode::EvalResult::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::read(::orgproto::BlockCode::EvalResult::Raw const& out, proto_write_accessor<sem::BlockCode::EvalResult::Raw> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::BlockCode::EvalResult::Raw::text));
}

void proto_serde<::orgproto::BlockCode::EvalResult, sem::BlockCode::EvalResult>::write(::orgproto::BlockCode::EvalResult* out, sem::BlockCode::EvalResult const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::write(out->mutable_data()->mutable_orgvalue(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::write(out->mutable_data()->mutable_file(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::write(out->mutable_data()->mutable_raw(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode::EvalResult, sem::BlockCode::EvalResult>::read(::orgproto::BlockCode::EvalResult const& out, proto_write_accessor<sem::BlockCode::EvalResult> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::BlockCode::EvalResult::Data::kNone:
      proto_serde<orgproto::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::read(out.data().none(), in.for_field_variant<0>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::BlockCode::EvalResult::Data::kOrgvalue:
      proto_serde<orgproto::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::read(out.data().orgvalue(), in.for_field_variant<1>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::BlockCode::EvalResult::Data::kFile:
      proto_serde<orgproto::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::read(out.data().file(), in.for_field_variant<2>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::BlockCode::EvalResult::Data::kRaw:
      proto_serde<orgproto::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::read(out.data().raw(), in.for_field_variant<3>(&sem::BlockCode::EvalResult::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode, sem::BlockCode>::write(::orgproto::BlockCode* out, sem::BlockCode const& in) {
  proto_serde<::orgproto::BlockCode, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockCode, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockCode, sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Switch>, Vec<sem::BlockCode::Switch>>::write(out->mutable_switches(), in.switches);
  proto_serde<orgproto::BlockCode::Exports, sem::BlockCode::Exports>::write(out->mutable_exports(), in.exports);
  if (in.result) {
    proto_serde<orgproto::BlockCode::EvalResult, sem::BlockCode::EvalResult>::write(out->mutable_result(), *in.result);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line>, Vec<sem::BlockCode::Line>>::write(out->mutable_lines(), in.lines);
  out->set_cache(in.cache);
  out->set_eval(in.eval);
  out->set_noweb(in.noweb);
  out->set_hlines(in.hlines);
  out->set_tangle(in.tangle);
}

void proto_serde<::orgproto::BlockCode, sem::BlockCode>::read(::orgproto::BlockCode const& out, proto_write_accessor<sem::BlockCode> in) {
  proto_serde<::orgproto::BlockCode, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockCode, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockCode, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_lang()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.lang(), in.for_field(&sem::BlockCode::lang));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Switch>, Vec<sem::BlockCode::Switch>>::read(out.switches(), in.for_field(&sem::BlockCode::switches));
  proto_serde<orgproto::BlockCode::Exports, sem::BlockCode::Exports>::read(out.exports(), in.for_field(&sem::BlockCode::exports));
  if (out.has_result()) {
    proto_serde<Opt<orgproto::BlockCode::EvalResult>, Opt<sem::BlockCode::EvalResult>>::read(out.result(), in.for_field(&sem::BlockCode::result));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line>, Vec<sem::BlockCode::Line>>::read(out.lines(), in.for_field(&sem::BlockCode::lines));
  in.for_field(&sem::BlockCode::cache).get() = out.cache();
  in.for_field(&sem::BlockCode::eval).get() = out.eval();
  in.for_field(&sem::BlockCode::noweb).get() = out.noweb();
  in.for_field(&sem::BlockCode::hlines).get() = out.hlines();
  in.for_field(&sem::BlockCode::tangle).get() = out.tangle();
}

void proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in) {
  if (in.desc) {
    proto_serde<orgproto::StmtList, sem::SemId<sem::StmtList>>::write(out->mutable_desc(), *in.desc);
  }
}

void proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::read(::orgproto::SubtreeLog::DescribedLog const& out, proto_write_accessor<sem::SubtreeLog::DescribedLog> in) {
  if (out.has_desc()) {
    proto_serde<Opt<orgproto::StmtList>, Opt<sem::SemId<sem::StmtList>>>::read(out.desc(), in.for_field(&sem::SubtreeLog::DescribedLog::desc));
  }
}

void proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::write(::orgproto::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in) {
  proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (in.oldPriority) {
    out->set_oldpriority(*in.oldPriority);
  }
  if (in.newPriority) {
    out->set_newpriority(*in.newPriority);
  }
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
  proto_serde<orgproto::SubtreeLog::Priority::Action, sem::SubtreeLog::Priority::Action>::write(out->mutable_action(), in.action);
}

void proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(::orgproto::SubtreeLog::Priority const& out, proto_write_accessor<sem::SubtreeLog::Priority> in) {
  proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  if (out.has_oldpriority()) {
    proto_serde<Opt<std::string>, Opt<std::string>>::read(out.oldpriority(), in.for_field(&sem::SubtreeLog::Priority::oldPriority));
  }
  if (out.has_newpriority()) {
    proto_serde<Opt<std::string>, Opt<std::string>>::read(out.newpriority(), in.for_field(&sem::SubtreeLog::Priority::newPriority));
  }
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Priority::on));
  proto_serde<orgproto::SubtreeLog::Priority::Action, sem::SubtreeLog::Priority::Action>::read(out.action(), in.for_field(&sem::SubtreeLog::Priority::action));
}

void proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in) {
  proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
}

void proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::read(::orgproto::SubtreeLog::Note const& out, proto_write_accessor<sem::SubtreeLog::Note> in) {
  proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Note::on));
}

void proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in) {
  proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
  if (!in.from.isNil()) {
    proto_serde<orgproto::Link, sem::SemId<sem::Link>>::write(out->mutable_from(), in.from);
  }
}

void proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(::orgproto::SubtreeLog::Refile const& out, proto_write_accessor<sem::SubtreeLog::Refile> in) {
  proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Refile::on));
  proto_serde<orgproto::Link, sem::SemId<sem::Link>>::read(out.from(), in.for_field(&sem::SubtreeLog::Refile::from));
}

void proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in) {
  proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (in.to) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(::orgproto::SubtreeLog::Clock const& out, proto_write_accessor<sem::SubtreeLog::Clock> in) {
  proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&sem::SubtreeLog::Clock::from));
  if (out.has_to()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.to(), in.for_field(&sem::SubtreeLog::Clock::to));
  }
}

void proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State>::write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in) {
  proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_from(), in.from);
  proto_serde<std::string, Str>::write(out->mutable_to(), in.to);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
}

void proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State>::read(::orgproto::SubtreeLog::State const& out, proto_write_accessor<sem::SubtreeLog::State> in) {
  proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<std::string, Str>::read(out.from(), in.for_field(&sem::SubtreeLog::State::from));
  proto_serde<std::string, Str>::read(out.to(), in.for_field(&sem::SubtreeLog::State::to));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::State::on));
}

void proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in) {
  proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
  if (!in.tag.isNil()) {
    proto_serde<orgproto::HashTag, sem::SemId<sem::HashTag>>::write(out->mutable_tag(), in.tag);
  }
  out->set_added(in.added);
}

void proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(::orgproto::SubtreeLog::Tag const& out, proto_write_accessor<sem::SubtreeLog::Tag> in) {
  proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Tag::on));
  proto_serde<orgproto::HashTag, sem::SemId<sem::HashTag>>::read(out.tag(), in.for_field(&sem::SubtreeLog::Tag::tag));
  in.for_field(&sem::SubtreeLog::Tag::added).get() = out.added();
}

void proto_serde<::orgproto::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::write(::orgproto::SubtreeLog::Unknown* out, sem::SubtreeLog::Unknown const& in) {
  proto_serde<::orgproto::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>::write(out, in);
}

void proto_serde<::orgproto::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::read(::orgproto::SubtreeLog::Unknown const& out, proto_write_accessor<sem::SubtreeLog::Unknown> in) {
  proto_serde<::orgproto::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
}

void proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog>::write(::orgproto::SubtreeLog* out, sem::SubtreeLog const& in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::write(out, in);
  switch (in.log.index()) {
    case 0:
      proto_serde<orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log));
      break;
    case 1:
      proto_serde<orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log));
      break;
    case 2:
      proto_serde<orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log));
      break;
    case 3:
      proto_serde<orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log));
      break;
    case 4:
      proto_serde<orgproto::SubtreeLog::State, sem::SubtreeLog::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log));
      break;
    case 5:
      proto_serde<orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(out->mutable_log()->mutable_tag(), std::get<5>(in.log));
      break;
    case 6:
      proto_serde<orgproto::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::write(out->mutable_log()->mutable_unknown(), std::get<6>(in.log));
      break;
  }
}

void proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog>::read(::orgproto::SubtreeLog const& out, proto_write_accessor<sem::SubtreeLog> in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::read(out, in.as<sem::Org>());
  switch (out.log().kind_case()) {
    case ::orgproto::SubtreeLog::LogEntry::kPriority:
      proto_serde<orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(out.log().priority(), in.for_field_variant<0>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kNote:
      proto_serde<orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::read(out.log().note(), in.for_field_variant<1>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kRefile:
      proto_serde<orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(out.log().refile(), in.for_field_variant<2>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kClock:
      proto_serde<orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(out.log().clock(), in.for_field_variant<3>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kState:
      proto_serde<orgproto::SubtreeLog::State, sem::SubtreeLog::State>::read(out.log().state(), in.for_field_variant<4>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kTag:
      proto_serde<orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(out.log().tag(), in.for_field_variant<5>(&sem::SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kUnknown:
      proto_serde<orgproto::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::read(out.log().unknown(), in.for_field_variant<6>(&sem::SubtreeLog::log));
      break;
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in) {
  proto_serde<orgproto::Subtree::Period::Kind, sem::Subtree::Period::Kind>::write(out->mutable_kind(), in.kind);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (in.to) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::read(::orgproto::Subtree::Period const& out, proto_write_accessor<sem::Subtree::Period> in) {
  proto_serde<orgproto::Subtree::Period::Kind, sem::Subtree::Period::Kind>::read(out.kind(), in.for_field(&sem::Subtree::Period::kind));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&sem::Subtree::Period::from));
  if (out.has_to()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.to(), in.for_field(&sem::Subtree::Period::to));
  }
}

void proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(::orgproto::Subtree::Property::Nonblocking const& out, proto_write_accessor<sem::Subtree::Property::Nonblocking> in) {
  in.for_field(&sem::Subtree::Property::Nonblocking::isBlocking).get() = out.isblocking();
}

void proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(::orgproto::Subtree::Property::Trigger const& out, proto_write_accessor<sem::Subtree::Property::Trigger> in) {

}

void proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in) {
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(::orgproto::Subtree::Property::Origin const& out, proto_write_accessor<sem::Subtree::Property::Origin> in) {
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&sem::Subtree::Property::Origin::text));
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in) {
  proto_serde<std::string, Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(::orgproto::Subtree::Property::ExportLatexClass const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClass> in) {
  proto_serde<std::string, Str>::read(out.latexclass(), in.for_field(&sem::Subtree::Property::ExportLatexClass::latexClass));
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(::orgproto::Subtree::Property::ExportLatexClassOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClassOptions> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.options(), in.for_field(&sem::Subtree::Property::ExportLatexClassOptions::options));
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in) {
  proto_serde<std::string, Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(::orgproto::Subtree::Property::ExportLatexHeader const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexHeader> in) {
  proto_serde<std::string, Str>::read(out.header(), in.for_field(&sem::Subtree::Property::ExportLatexHeader::header));
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in) {
  proto_serde<std::string, Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(::orgproto::Subtree::Property::ExportLatexCompiler const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexCompiler> in) {
  proto_serde<std::string, Str>::read(out.compiler(), in.for_field(&sem::Subtree::Property::ExportLatexCompiler::compiler));
}

void proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(::orgproto::Subtree::Property::Ordered const& out, proto_write_accessor<sem::Subtree::Property::Ordered> in) {
  in.for_field(&sem::Subtree::Property::Ordered::isOrdered).get() = out.isordered();
}

void proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(::orgproto::Subtree::Property::Effort const& out, proto_write_accessor<sem::Subtree::Property::Effort> in) {
  in.for_field(&sem::Subtree::Property::Effort::hours).get() = out.hours();
  in.for_field(&sem::Subtree::Property::Effort::minutes).get() = out.minutes();
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in) {
  proto_serde<orgproto::Subtree::Property::Visibility::Level, sem::Subtree::Property::Visibility::Level>::write(out->mutable_level(), in.level);
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(::orgproto::Subtree::Property::Visibility const& out, proto_write_accessor<sem::Subtree::Property::Visibility> in) {
  proto_serde<orgproto::Subtree::Property::Visibility::Level, sem::Subtree::Property::Visibility::Level>::read(out.level(), in.for_field(&sem::Subtree::Property::Visibility::level));
}

void proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in) {
  proto_serde<std::string, Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(::orgproto::Subtree::Property::ExportOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportOptions> in) {
  proto_serde<std::string, Str>::read(out.backend(), in.for_field(&sem::Subtree::Property::ExportOptions::backend));
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::read(out.values(), in.for_field(&sem::Subtree::Property::ExportOptions::values));
}

void proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(::orgproto::Subtree::Property::Blocker const& out, proto_write_accessor<sem::Subtree::Property::Blocker> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.blockers(), in.for_field(&sem::Subtree::Property::Blocker::blockers));
}

void proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(::orgproto::Subtree::Property::Unnumbered const& out, proto_write_accessor<sem::Subtree::Property::Unnumbered> in) {

}

void proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in) {
  if (!in.time.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_time(), in.time);
  }
}

void proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::read(::orgproto::Subtree::Property::Created const& out, proto_write_accessor<sem::Subtree::Property::Created> in) {
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.time(), in.for_field(&sem::Subtree::Property::Created::time));
}

void proto_serde<::orgproto::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::write(::orgproto::Subtree::Property::CustomArgs* out, sem::Subtree::Property::CustomArgs const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (in.sub) {
    proto_serde<std::string, Str>::write(out->mutable_sub(), *in.sub);
  }
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
}

void proto_serde<::orgproto::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::read(::orgproto::Subtree::Property::CustomArgs const& out, proto_write_accessor<sem::Subtree::Property::CustomArgs> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Subtree::Property::CustomArgs::name));
  if (out.has_sub()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.sub(), in.for_field(&sem::Subtree::Property::CustomArgs::sub));
  }
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&sem::Subtree::Property::CustomArgs::parameters));
}

void proto_serde<::orgproto::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::write(::orgproto::Subtree::Property::CustomRaw* out, sem::Subtree::Property::CustomRaw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::read(::orgproto::Subtree::Property::CustomRaw const& out, proto_write_accessor<sem::Subtree::Property::CustomRaw> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Subtree::Property::CustomRaw::name));
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::Subtree::Property::CustomRaw::value));
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in) {
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::write(out->mutable_mainsetrule(), in.mainSetRule);
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::write(out->mutable_subsetrule(), in.subSetRule);
  proto_serde<orgproto::Subtree::Property::InheritanceMode, sem::Subtree::Property::InheritanceMode>::write(out->mutable_inheritancemode(), in.inheritanceMode);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(out->mutable_data()->mutable_origin(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(out->mutable_data()->mutable_effort(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<9>(in.data));
      break;
    case 10:
      proto_serde<orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<10>(in.data));
      break;
    case 11:
      proto_serde<orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<11>(in.data));
      break;
    case 12:
      proto_serde<orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<12>(in.data));
      break;
    case 13:
      proto_serde<orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::write(out->mutable_data()->mutable_created(), std::get<13>(in.data));
      break;
    case 14:
      proto_serde<orgproto::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::write(out->mutable_data()->mutable_customargs(), std::get<14>(in.data));
      break;
    case 15:
      proto_serde<orgproto::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::write(out->mutable_data()->mutable_customraw(), std::get<15>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::read(::orgproto::Subtree::Property const& out, proto_write_accessor<sem::Subtree::Property> in) {
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::read(out.mainsetrule(), in.for_field(&sem::Subtree::Property::mainSetRule));
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::read(out.subsetrule(), in.for_field(&sem::Subtree::Property::subSetRule));
  proto_serde<orgproto::Subtree::Property::InheritanceMode, sem::Subtree::Property::InheritanceMode>::read(out.inheritancemode(), in.for_field(&sem::Subtree::Property::inheritanceMode));
  switch (out.data().kind_case()) {
    case ::orgproto::Subtree::Property::Data::kNonblocking:
      proto_serde<orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(out.data().nonblocking(), in.for_field_variant<0>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kTrigger:
      proto_serde<orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(out.data().trigger(), in.for_field_variant<1>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kOrigin:
      proto_serde<orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(out.data().origin(), in.for_field_variant<2>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexclass:
      proto_serde<orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(out.data().exportlatexclass(), in.for_field_variant<3>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexclassoptions:
      proto_serde<orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(out.data().exportlatexclassoptions(), in.for_field_variant<4>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexheader:
      proto_serde<orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(out.data().exportlatexheader(), in.for_field_variant<5>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexcompiler:
      proto_serde<orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(out.data().exportlatexcompiler(), in.for_field_variant<6>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kOrdered:
      proto_serde<orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(out.data().ordered(), in.for_field_variant<7>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kEffort:
      proto_serde<orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(out.data().effort(), in.for_field_variant<8>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kVisibility:
      proto_serde<orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(out.data().visibility(), in.for_field_variant<9>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportoptions:
      proto_serde<orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(out.data().exportoptions(), in.for_field_variant<10>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kBlocker:
      proto_serde<orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(out.data().blocker(), in.for_field_variant<11>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kUnnumbered:
      proto_serde<orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(out.data().unnumbered(), in.for_field_variant<12>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kCreated:
      proto_serde<orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::read(out.data().created(), in.for_field_variant<13>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kCustomargs:
      proto_serde<orgproto::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::read(out.data().customargs(), in.for_field_variant<14>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::Subtree::Property::Data::kCustomraw:
      proto_serde<orgproto::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::read(out.data().customraw(), in.for_field_variant<15>(&sem::Subtree::Property::data));
      break;
  }
}

void proto_serde<::orgproto::Subtree, sem::Subtree>::write(::orgproto::Subtree* out, sem::Subtree const& in) {
  proto_serde<::orgproto::Subtree, sem::Org>::write(out, in);
  out->set_level(in.level);
  if (in.treeId) {
    proto_serde<std::string, Str>::write(out->mutable_treeid(), *in.treeId);
  }
  if (in.todo) {
    proto_serde<std::string, Str>::write(out->mutable_todo(), *in.todo);
  }
  if (in.completion) {
    proto_serde<orgproto::SubtreeCompletion, sem::SemId<sem::SubtreeCompletion>>::write(out->mutable_completion(), *in.completion);
  }
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::write(out->mutable_tags(), in.tags);
  if (!in.title.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_title(), in.title);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, Vec<sem::SemId<sem::SubtreeLog>>>::write(out->mutable_logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::write(out->mutable_properties(), in.properties);
  if (in.closed) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_closed(), *in.closed);
  }
  if (in.deadline) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_deadline(), *in.deadline);
  }
  if (in.scheduled) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_scheduled(), *in.scheduled);
  }
  out->set_iscomment(in.isComment);
  out->set_isarchived(in.isArchived);
  if (in.priority) {
    proto_serde<std::string, Str>::write(out->mutable_priority(), *in.priority);
  }
}

void proto_serde<::orgproto::Subtree, sem::Subtree>::read(::orgproto::Subtree const& out, proto_write_accessor<sem::Subtree> in) {
  proto_serde<::orgproto::Subtree, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::Subtree::level).get() = out.level();
  if (out.has_treeid()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.treeid(), in.for_field(&sem::Subtree::treeId));
  }
  if (out.has_todo()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.todo(), in.for_field(&sem::Subtree::todo));
  }
  if (out.has_completion()) {
    proto_serde<Opt<orgproto::SubtreeCompletion>, Opt<sem::SemId<sem::SubtreeCompletion>>>::read(out.completion(), in.for_field(&sem::Subtree::completion));
  }
  if (out.has_description()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.description(), in.for_field(&sem::Subtree::description));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.tags(), in.for_field(&sem::Subtree::tags));
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.title(), in.for_field(&sem::Subtree::title));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, Vec<sem::SemId<sem::SubtreeLog>>>::read(out.logbook(), in.for_field(&sem::Subtree::logbook));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(out.properties(), in.for_field(&sem::Subtree::properties));
  if (out.has_closed()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.closed(), in.for_field(&sem::Subtree::closed));
  }
  if (out.has_deadline()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.deadline(), in.for_field(&sem::Subtree::deadline));
  }
  if (out.has_scheduled()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.scheduled(), in.for_field(&sem::Subtree::scheduled));
  }
  in.for_field(&sem::Subtree::isComment).get() = out.iscomment();
  in.for_field(&sem::Subtree::isArchived).get() = out.isarchived();
  if (out.has_priority()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.priority(), in.for_field(&sem::Subtree::priority));
  }
}

void proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion>::write(::orgproto::SubtreeCompletion* out, sem::SubtreeCompletion const& in) {
  proto_serde<::orgproto::SubtreeCompletion, sem::Org>::write(out, in);
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion>::read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<sem::SubtreeCompletion> in) {
  proto_serde<::orgproto::SubtreeCompletion, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::SubtreeCompletion::done).get() = out.done();
  in.for_field(&sem::SubtreeCompletion::full).get() = out.full();
  in.for_field(&sem::SubtreeCompletion::isPercent).get() = out.ispercent();
}

void proto_serde<::orgproto::Cell, sem::Cell>::write(::orgproto::Cell* out, sem::Cell const& in) {
  proto_serde<::orgproto::Cell, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Cell, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Cell, sem::Org>::write(out, in);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Cell, sem::Cell>::read(::orgproto::Cell const& out, proto_write_accessor<sem::Cell> in) {
  proto_serde<::orgproto::Cell, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Cell, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Cell, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::Cell::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Row, sem::Row>::write(::orgproto::Row* out, sem::Row const& in) {
  proto_serde<::orgproto::Row, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Row, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Row, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::write(out->mutable_cells(), in.cells);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Row, sem::Row>::read(::orgproto::Row const& out, proto_write_accessor<sem::Row> in) {
  proto_serde<::orgproto::Row, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Row, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Row, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::read(out.cells(), in.for_field(&sem::Row::cells));
  in.for_field(&sem::Row::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Table, sem::Table>::write(::orgproto::Table* out, sem::Table const& in) {
  proto_serde<::orgproto::Table, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Table, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Table, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::write(out->mutable_rows(), in.rows);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Table, sem::Table>::read(::orgproto::Table const& out, proto_write_accessor<sem::Table> in) {
  proto_serde<::orgproto::Table, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Table, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Table, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::read(out.rows(), in.for_field(&sem::Table::rows));
  in.for_field(&sem::Table::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Paragraph, sem::Paragraph>::write(::orgproto::Paragraph* out, sem::Paragraph const& in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Paragraph, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Paragraph, sem::Paragraph>::read(::orgproto::Paragraph const& out, proto_write_accessor<sem::Paragraph> in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Paragraph, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::write(::orgproto::AnnotatedParagraph::None* out, sem::AnnotatedParagraph::None const& in) {

}

void proto_serde<::orgproto::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::read(::orgproto::AnnotatedParagraph::None const& out, proto_write_accessor<sem::AnnotatedParagraph::None> in) {

}

void proto_serde<::orgproto::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::write(::orgproto::AnnotatedParagraph::Footnote* out, sem::AnnotatedParagraph::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::read(::orgproto::AnnotatedParagraph::Footnote const& out, proto_write_accessor<sem::AnnotatedParagraph::Footnote> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::AnnotatedParagraph::Footnote::name));
}

void proto_serde<::orgproto::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::write(::orgproto::AnnotatedParagraph::Admonition* out, sem::AnnotatedParagraph::Admonition const& in) {
  if (!in.name.isNil()) {
    proto_serde<orgproto::BigIdent, sem::SemId<sem::BigIdent>>::write(out->mutable_name(), in.name);
  }
}

void proto_serde<::orgproto::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::read(::orgproto::AnnotatedParagraph::Admonition const& out, proto_write_accessor<sem::AnnotatedParagraph::Admonition> in) {
  proto_serde<orgproto::BigIdent, sem::SemId<sem::BigIdent>>::read(out.name(), in.for_field(&sem::AnnotatedParagraph::Admonition::name));
}

void proto_serde<::orgproto::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::write(::orgproto::AnnotatedParagraph::Timestamp* out, sem::AnnotatedParagraph::Timestamp const& in) {
  if (!in.time.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_time(), in.time);
  }
}

void proto_serde<::orgproto::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::read(::orgproto::AnnotatedParagraph::Timestamp const& out, proto_write_accessor<sem::AnnotatedParagraph::Timestamp> in) {
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.time(), in.for_field(&sem::AnnotatedParagraph::Timestamp::time));
}

void proto_serde<::orgproto::AnnotatedParagraph, sem::AnnotatedParagraph>::write(::orgproto::AnnotatedParagraph* out, sem::AnnotatedParagraph const& in) {
  proto_serde<::orgproto::AnnotatedParagraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::AnnotatedParagraph, sem::Org>::write(out, in);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::write(out->mutable_data()->mutable_admonition(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::write(out->mutable_data()->mutable_timestamp(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::AnnotatedParagraph, sem::AnnotatedParagraph>::read(::orgproto::AnnotatedParagraph const& out, proto_write_accessor<sem::AnnotatedParagraph> in) {
  proto_serde<::orgproto::AnnotatedParagraph, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::AnnotatedParagraph, sem::Org>::read(out, in.as<sem::Org>());
  switch (out.data().kind_case()) {
    case ::orgproto::AnnotatedParagraph::Data::kNone:
      proto_serde<orgproto::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::read(out.data().none(), in.for_field_variant<0>(&sem::AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kFootnote:
      proto_serde<orgproto::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::read(out.data().footnote(), in.for_field_variant<1>(&sem::AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kAdmonition:
      proto_serde<orgproto::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::read(out.data().admonition(), in.for_field_variant<2>(&sem::AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kTimestamp:
      proto_serde<orgproto::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::read(out.data().timestamp(), in.for_field_variant<3>(&sem::AnnotatedParagraph::data));
      break;
  }
}

void proto_serde<::orgproto::ColonExample, sem::ColonExample>::write(::orgproto::ColonExample* out, sem::ColonExample const& in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ColonExample, sem::ColonExample>::read(::orgproto::ColonExample const& out, proto_write_accessor<sem::ColonExample> in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdAttr, sem::CmdAttr>::write(::orgproto::CmdAttr* out, sem::CmdAttr const& in) {
  proto_serde<::orgproto::CmdAttr, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdAttr, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdAttr, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::CmdAttr, sem::CmdAttr>::read(::orgproto::CmdAttr const& out, proto_write_accessor<sem::CmdAttr> in) {
  proto_serde<::orgproto::CmdAttr, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdAttr, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdAttr, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::CmdAttr::target));
}

void proto_serde<::orgproto::Call, sem::Call>::write(::orgproto::Call* out, sem::Call const& in) {
  proto_serde<::orgproto::Call, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
  out->set_iscommand(in.isCommand);
}

void proto_serde<::orgproto::Call, sem::Call>::read(::orgproto::Call const& out, proto_write_accessor<sem::Call> in) {
  proto_serde<::orgproto::Call, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Call::name));
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&sem::Call::parameters));
  in.for_field(&sem::Call::isCommand).get() = out.iscommand();
}

void proto_serde<::orgproto::List, sem::List>::write(::orgproto::List* out, sem::List const& in) {
  proto_serde<::orgproto::List, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::List, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::List, sem::List>::read(::orgproto::List const& out, proto_write_accessor<sem::List> in) {
  proto_serde<::orgproto::List, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::List, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::write(::orgproto::ListItem* out, sem::ListItem const& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::write(out, in);
  proto_serde<orgproto::ListItem::Checkbox, sem::ListItem::Checkbox>::write(out->mutable_checkbox(), in.checkbox);
  if (in.header) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
  if (in.bullet) {
    proto_serde<std::string, Str>::write(out->mutable_bullet(), *in.bullet);
  }
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::read(::orgproto::ListItem const& out, proto_write_accessor<sem::ListItem> in) {
  proto_serde<::orgproto::ListItem, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::ListItem::Checkbox, sem::ListItem::Checkbox>::read(out.checkbox(), in.for_field(&sem::ListItem::checkbox));
  if (out.has_header()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.header(), in.for_field(&sem::ListItem::header));
  }
  if (out.has_bullet()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.bullet(), in.for_field(&sem::ListItem::bullet));
  }
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport>::write(::orgproto::DocumentOptions::ExportConfig::TaskExport* out, sem::DocumentOptions::ExportConfig::TaskExport const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_taskwhitelist(), in.taskWhitelist);
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport>::read(::orgproto::DocumentOptions::ExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::TaskExport> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.taskwhitelist(), in.for_field(&sem::DocumentOptions::ExportConfig::TaskExport::taskWhitelist));
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::write(::orgproto::DocumentOptions::ExportConfig::DoExport* out, sem::DocumentOptions::ExportConfig::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::read(::orgproto::DocumentOptions::ExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::DoExport> in) {
  in.for_field(&sem::DocumentOptions::ExportConfig::DoExport::exportToc).get() = out.exporttoc();
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::write(::orgproto::DocumentOptions::ExportConfig::ExportFixed* out, sem::DocumentOptions::ExportConfig::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::read(::orgproto::DocumentOptions::ExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::ExportFixed> in) {
  in.for_field(&sem::DocumentOptions::ExportConfig::ExportFixed::exportLevels).get() = out.exportlevels();
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::write(::orgproto::DocumentOptions::ExportConfig* out, sem::DocumentOptions::ExportConfig const& in) {
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
  proto_serde<orgproto::DocumentOptions::ExportConfig::BrokenLinks, sem::DocumentOptions::ExportConfig::BrokenLinks>::write(out->mutable_brokenlinks(), in.brokenLinks);
  proto_serde<orgproto::DocumentOptions::ExportConfig::TocExport, sem::DocumentOptions::ExportConfig::TocExport>::write(out->mutable_tocexport(), in.tocExport);
  proto_serde<orgproto::DocumentOptions::ExportConfig::TagExport, sem::DocumentOptions::ExportConfig::TagExport>::write(out->mutable_tagexport(), in.tagExport);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::read(::orgproto::DocumentOptions::ExportConfig const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig> in) {
  if (out.has_inlinetasks()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.inlinetasks(), in.for_field(&sem::DocumentOptions::ExportConfig::inlinetasks));
  }
  if (out.has_footnotes()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.footnotes(), in.for_field(&sem::DocumentOptions::ExportConfig::footnotes));
  }
  if (out.has_clock()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.clock(), in.for_field(&sem::DocumentOptions::ExportConfig::clock));
  }
  if (out.has_author()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.author(), in.for_field(&sem::DocumentOptions::ExportConfig::author));
  }
  if (out.has_emphasis()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.emphasis(), in.for_field(&sem::DocumentOptions::ExportConfig::emphasis));
  }
  if (out.has_specialstrings()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.specialstrings(), in.for_field(&sem::DocumentOptions::ExportConfig::specialStrings));
  }
  if (out.has_propertydrawers()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.propertydrawers(), in.for_field(&sem::DocumentOptions::ExportConfig::propertyDrawers));
  }
  if (out.has_statisticscookies()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.statisticscookies(), in.for_field(&sem::DocumentOptions::ExportConfig::statisticsCookies));
  }
  if (out.has_todotext()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.todotext(), in.for_field(&sem::DocumentOptions::ExportConfig::todoText));
  }
  proto_serde<orgproto::DocumentOptions::ExportConfig::BrokenLinks, sem::DocumentOptions::ExportConfig::BrokenLinks>::read(out.brokenlinks(), in.for_field(&sem::DocumentOptions::ExportConfig::brokenLinks));
  proto_serde<orgproto::DocumentOptions::ExportConfig::TocExport, sem::DocumentOptions::ExportConfig::TocExport>::read(out.tocexport(), in.for_field(&sem::DocumentOptions::ExportConfig::tocExport));
  proto_serde<orgproto::DocumentOptions::ExportConfig::TagExport, sem::DocumentOptions::ExportConfig::TagExport>::read(out.tagexport(), in.for_field(&sem::DocumentOptions::ExportConfig::tagExport));
  switch (out.data().kind_case()) {
    case ::orgproto::DocumentOptions::ExportConfig::TocExport::kDoexport:
      proto_serde<orgproto::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&sem::DocumentOptions::ExportConfig::data));
      break;
    case ::orgproto::DocumentOptions::ExportConfig::TocExport::kExportfixed:
      proto_serde<orgproto::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&sem::DocumentOptions::ExportConfig::data));
      break;
  }
}

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::write(out, in);
  proto_serde<orgproto::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::write(out->mutable_initialvisibility(), in.initialVisibility);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::write(out->mutable_properties(), in.properties);
  proto_serde<orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::write(out->mutable_exportconfig(), in.exportConfig);
  if (in.fixedWidthSections) {
    out->set_fixedwidthsections(*in.fixedWidthSections);
  }
  if (in.startupIndented) {
    out->set_startupindented(*in.startupIndented);
  }
  if (in.category) {
    proto_serde<std::string, Str>::write(out->mutable_category(), *in.category);
  }
  if (in.setupfile) {
    proto_serde<std::string, Str>::write(out->mutable_setupfile(), *in.setupfile);
  }
  if (in.maxSubtreeLevelExport) {
    out->set_maxsubtreelevelexport(*in.maxSubtreeLevelExport);
  }
}

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::read(::orgproto::DocumentOptions const& out, proto_write_accessor<sem::DocumentOptions> in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::read(out.initialvisibility(), in.for_field(&sem::DocumentOptions::initialVisibility));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(out.properties(), in.for_field(&sem::DocumentOptions::properties));
  proto_serde<orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::read(out.exportconfig(), in.for_field(&sem::DocumentOptions::exportConfig));
  if (out.has_fixedwidthsections()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.fixedwidthsections(), in.for_field(&sem::DocumentOptions::fixedWidthSections));
  }
  if (out.has_startupindented()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.startupindented(), in.for_field(&sem::DocumentOptions::startupIndented));
  }
  if (out.has_category()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.category(), in.for_field(&sem::DocumentOptions::category));
  }
  if (out.has_setupfile()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.setupfile(), in.for_field(&sem::DocumentOptions::setupfile));
  }
  if (out.has_maxsubtreelevelexport()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.maxsubtreelevelexport(), in.for_field(&sem::DocumentOptions::maxSubtreeLevelExport));
  }
}

void proto_serde<::orgproto::Document, sem::Document>::write(::orgproto::Document* out, sem::Document const& in) {
  proto_serde<::orgproto::Document, sem::Org>::write(out, in);
  if (in.title) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_title(), *in.title);
  }
  if (in.author) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_author(), *in.author);
  }
  if (in.creator) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_creator(), *in.creator);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::write(out->mutable_filetags(), in.filetags);
  if (in.email) {
    proto_serde<orgproto::RawText, sem::SemId<sem::RawText>>::write(out->mutable_email(), *in.email);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_language(), in.language);
  if (!in.options.isNil()) {
    proto_serde<orgproto::DocumentOptions, sem::SemId<sem::DocumentOptions>>::write(out->mutable_options(), in.options);
  }
  if (in.exportFileName) {
    proto_serde<std::string, Str>::write(out->mutable_exportfilename(), *in.exportFileName);
  }
}

void proto_serde<::orgproto::Document, sem::Document>::read(::orgproto::Document const& out, proto_write_accessor<sem::Document> in) {
  proto_serde<::orgproto::Document, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_title()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.title(), in.for_field(&sem::Document::title));
  }
  if (out.has_author()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.author(), in.for_field(&sem::Document::author));
  }
  if (out.has_creator()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.creator(), in.for_field(&sem::Document::creator));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.filetags(), in.for_field(&sem::Document::filetags));
  if (out.has_email()) {
    proto_serde<Opt<orgproto::RawText>, Opt<sem::SemId<sem::RawText>>>::read(out.email(), in.for_field(&sem::Document::email));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.language(), in.for_field(&sem::Document::language));
  proto_serde<orgproto::DocumentOptions, sem::SemId<sem::DocumentOptions>>::read(out.options(), in.for_field(&sem::Document::options));
  if (out.has_exportfilename()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.exportfilename(), in.for_field(&sem::Document::exportFileName));
  }
}

void proto_serde<::orgproto::FileTarget, sem::FileTarget>::write(::orgproto::FileTarget* out, sem::FileTarget const& in) {
  proto_serde<::orgproto::FileTarget, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_path(), in.path);
  if (in.line) {
    out->set_line(*in.line);
  }
  if (in.searchTarget) {
    proto_serde<std::string, Str>::write(out->mutable_searchtarget(), *in.searchTarget);
  }
  out->set_restricttoheadlines(in.restrictToHeadlines);
  if (in.targetId) {
    proto_serde<std::string, Str>::write(out->mutable_targetid(), *in.targetId);
  }
  if (in.regexp) {
    proto_serde<std::string, Str>::write(out->mutable_regexp(), *in.regexp);
  }
}

void proto_serde<::orgproto::FileTarget, sem::FileTarget>::read(::orgproto::FileTarget const& out, proto_write_accessor<sem::FileTarget> in) {
  proto_serde<::orgproto::FileTarget, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&sem::FileTarget::path));
  if (out.has_line()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.line(), in.for_field(&sem::FileTarget::line));
  }
  if (out.has_searchtarget()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.searchtarget(), in.for_field(&sem::FileTarget::searchTarget));
  }
  in.for_field(&sem::FileTarget::restrictToHeadlines).get() = out.restricttoheadlines();
  if (out.has_targetid()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.targetid(), in.for_field(&sem::FileTarget::targetId));
  }
  if (out.has_regexp()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.regexp(), in.for_field(&sem::FileTarget::regexp));
  }
}

void proto_serde<::orgproto::TextSeparator, sem::TextSeparator>::write(::orgproto::TextSeparator* out, sem::TextSeparator const& in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::TextSeparator, sem::TextSeparator>::read(::orgproto::TextSeparator const& out, proto_write_accessor<sem::TextSeparator> in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Include::Example, sem::Include::Example>::write(::orgproto::Include::Example* out, sem::Include::Example const& in) {

}

void proto_serde<::orgproto::Include::Example, sem::Include::Example>::read(::orgproto::Include::Example const& out, proto_write_accessor<sem::Include::Example> in) {

}

void proto_serde<::orgproto::Include::Export, sem::Include::Export>::write(::orgproto::Include::Export* out, sem::Include::Export const& in) {

}

void proto_serde<::orgproto::Include::Export, sem::Include::Export>::read(::orgproto::Include::Export const& out, proto_write_accessor<sem::Include::Export> in) {

}

void proto_serde<::orgproto::Include::Src, sem::Include::Src>::write(::orgproto::Include::Src* out, sem::Include::Src const& in) {

}

void proto_serde<::orgproto::Include::Src, sem::Include::Src>::read(::orgproto::Include::Src const& out, proto_write_accessor<sem::Include::Src> in) {

}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in) {
  if (in.minLevel) {
    out->set_minlevel(*in.minLevel);
  }
}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::read(::orgproto::Include::OrgDocument const& out, proto_write_accessor<sem::Include::OrgDocument> in) {
  if (out.has_minlevel()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.minlevel(), in.for_field(&sem::Include::OrgDocument::minLevel));
  }
}

void proto_serde<::orgproto::Include, sem::Include>::write(::orgproto::Include* out, sem::Include const& in) {
  proto_serde<::orgproto::Include, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_path(), in.path);
  if (in.firstLine) {
    out->set_firstline(*in.firstLine);
  }
  if (in.lastLine) {
    out->set_lastline(*in.lastLine);
  }
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Include::Example, sem::Include::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Include::Export, sem::Include::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Include::Src, sem::Include::Src>::write(out->mutable_data()->mutable_src(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Include::OrgDocument, sem::Include::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Include, sem::Include>::read(::orgproto::Include const& out, proto_write_accessor<sem::Include> in) {
  proto_serde<::orgproto::Include, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&sem::Include::path));
  if (out.has_firstline()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.firstline(), in.for_field(&sem::Include::firstLine));
  }
  if (out.has_lastline()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.lastline(), in.for_field(&sem::Include::lastLine));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::Include::Data::kExample:
      proto_serde<orgproto::Include::Example, sem::Include::Example>::read(out.data().example(), in.for_field_variant<0>(&sem::Include::data));
      break;
    case ::orgproto::Include::Data::kExport:
      proto_serde<orgproto::Include::Export, sem::Include::Export>::read(out.data().export_(), in.for_field_variant<1>(&sem::Include::data));
      break;
    case ::orgproto::Include::Data::kSrc:
      proto_serde<orgproto::Include::Src, sem::Include::Src>::read(out.data().src(), in.for_field_variant<2>(&sem::Include::data));
      break;
    case ::orgproto::Include::Data::kOrgdocument:
      proto_serde<orgproto::Include::OrgDocument, sem::Include::OrgDocument>::read(out.data().orgdocument(), in.for_field_variant<3>(&sem::Include::data));
      break;
  }
}

void proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup>::write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup>::read(::orgproto::DocumentGroup const& out, proto_write_accessor<sem::DocumentGroup> in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::read(out, in.as<sem::Org>());
}

/* clang-format on */