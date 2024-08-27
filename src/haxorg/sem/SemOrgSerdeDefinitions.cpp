/* clang-format off */
#include <haxorg/sem/SemOrgSerde.hpp>
#include <haxorg/sem/SemOrgSerdeDeclarations.hpp>
void proto_serde<::orgproto::CmdArgument, CmdArgument>::write(::orgproto::CmdArgument* out, CmdArgument const& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::write(out, in);
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  if (in.varname) {
    proto_serde<std::string, Str>::write(out->mutable_varname(), *in.varname);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::CmdArgument, CmdArgument>::read(::orgproto::CmdArgument const& out, proto_write_accessor<CmdArgument> in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_key()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.key(), in.for_field(&CmdArgument::key));
  }
  if (out.has_varname()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.varname(), in.for_field(&CmdArgument::varname));
  }
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&CmdArgument::value));
}

void proto_serde<::orgproto::CmdArgumentList, CmdArgumentList>::write(::orgproto::CmdArgumentList* out, CmdArgumentList const& in) {
  proto_serde<::orgproto::CmdArgumentList, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::write(out->mutable_args(), in.args);
}

void proto_serde<::orgproto::CmdArgumentList, CmdArgumentList>::read(::orgproto::CmdArgumentList const& out, proto_write_accessor<CmdArgumentList> in) {
  proto_serde<::orgproto::CmdArgumentList, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::read(out.args(), in.for_field(&CmdArgumentList::args));
}

void proto_serde<::orgproto::CmdArguments, CmdArguments>::write(::orgproto::CmdArguments* out, CmdArguments const& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::write(out, in);
  if (!in.positional.isNil()) {
    proto_serde<orgproto::CmdArgumentList, sem::SemId<sem::CmdArgumentList>>::write(out->mutable_positional(), in.positional);
  }
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgumentList>, UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::CmdArguments, CmdArguments>::read(::orgproto::CmdArguments const& out, proto_write_accessor<CmdArguments> in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::CmdArgumentList, sem::SemId<sem::CmdArgumentList>>::read(out.positional(), in.for_field(&CmdArguments::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgumentList>, UnorderedMap<Str, sem::SemId<sem::CmdArgumentList>>>::read(out.named(), in.for_field(&CmdArguments::named));
}

void proto_serde<::orgproto::ErrorItem, ErrorItem>::write(::orgproto::ErrorItem* out, ErrorItem const& in) {
  proto_serde<::orgproto::ErrorItem, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_message(), in.message);
  if (in.function) {
    proto_serde<std::string, Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    out->set_line(*in.line);
  }
}

void proto_serde<::orgproto::ErrorItem, ErrorItem>::read(::orgproto::ErrorItem const& out, proto_write_accessor<ErrorItem> in) {
  proto_serde<::orgproto::ErrorItem, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.message(), in.for_field(&ErrorItem::message));
  if (out.has_function()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.function(), in.for_field(&ErrorItem::function));
  }
  if (out.has_line()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.line(), in.for_field(&ErrorItem::line));
  }
}

void proto_serde<::orgproto::ErrorGroup, ErrorGroup>::write(::orgproto::ErrorGroup* out, ErrorGroup const& in) {
  proto_serde<::orgproto::ErrorGroup, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, Vec<sem::SemId<sem::ErrorItem>>>::write(out->mutable_diagnostics(), in.diagnostics);
  if (in.function) {
    proto_serde<std::string, Str>::write(out->mutable_function(), *in.function);
  }
  if (in.line) {
    proto_serde<std::string, Str>::write(out->mutable_line(), *in.line);
  }
}

void proto_serde<::orgproto::ErrorGroup, ErrorGroup>::read(::orgproto::ErrorGroup const& out, proto_write_accessor<ErrorGroup> in) {
  proto_serde<::orgproto::ErrorGroup, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::ErrorItem>, Vec<sem::SemId<sem::ErrorItem>>>::read(out.diagnostics(), in.for_field(&ErrorGroup::diagnostics));
  if (out.has_function()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.function(), in.for_field(&ErrorGroup::function));
  }
  if (out.has_line()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.line(), in.for_field(&ErrorGroup::line));
  }
}

void proto_serde<::orgproto::StmtList, StmtList>::write(::orgproto::StmtList* out, StmtList const& in) {
  proto_serde<::orgproto::StmtList, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::StmtList, StmtList>::read(::orgproto::StmtList const& out, proto_write_accessor<StmtList> in) {
  proto_serde<::orgproto::StmtList, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Empty, Empty>::write(::orgproto::Empty* out, Empty const& in) {
  proto_serde<::orgproto::Empty, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Empty, Empty>::read(::orgproto::Empty const& out, proto_write_accessor<Empty> in) {
  proto_serde<::orgproto::Empty, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdCaption, CmdCaption>::write(::orgproto::CmdCaption* out, CmdCaption const& in) {
  proto_serde<::orgproto::CmdCaption, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdCaption, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCaption, sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::CmdCaption, CmdCaption>::read(::orgproto::CmdCaption const& out, proto_write_accessor<CmdCaption> in) {
  proto_serde<::orgproto::CmdCaption, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdCaption, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCaption, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&CmdCaption::text));
}

void proto_serde<::orgproto::CmdName, CmdName>::write(::orgproto::CmdName* out, CmdName const& in) {
  proto_serde<::orgproto::CmdName, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdName, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdName, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::CmdName, CmdName>::read(::orgproto::CmdName const& out, proto_write_accessor<CmdName> in) {
  proto_serde<::orgproto::CmdName, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdName, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdName, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&CmdName::name));
}

void proto_serde<::orgproto::CmdCustomArgs, CmdCustomArgs>::write(::orgproto::CmdCustomArgs* out, CmdCustomArgs const& in) {
  proto_serde<::orgproto::CmdCustomArgs, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdCustomArgs, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomArgs, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
}

void proto_serde<::orgproto::CmdCustomArgs, CmdCustomArgs>::read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<CmdCustomArgs> in) {
  proto_serde<::orgproto::CmdCustomArgs, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdCustomArgs, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomArgs, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&CmdCustomArgs::name));
  in.for_field(&CmdCustomArgs::isAttached).get() = out.isattached();
}

void proto_serde<::orgproto::CmdCustomRaw, CmdCustomRaw>::write(::orgproto::CmdCustomRaw* out, CmdCustomRaw const& in) {
  proto_serde<::orgproto::CmdCustomRaw, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomRaw, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::CmdCustomRaw, CmdCustomRaw>::read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<CmdCustomRaw> in) {
  proto_serde<::orgproto::CmdCustomRaw, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomRaw, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&CmdCustomRaw::name));
  in.for_field(&CmdCustomRaw::isAttached).get() = out.isattached();
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&CmdCustomRaw::text));
}

void proto_serde<::orgproto::CmdCustomText, CmdCustomText>::write(::orgproto::CmdCustomText* out, CmdCustomText const& in) {
  proto_serde<::orgproto::CmdCustomText, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdCustomText, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  out->set_isattached(in.isAttached);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::CmdCustomText, CmdCustomText>::read(::orgproto::CmdCustomText const& out, proto_write_accessor<CmdCustomText> in) {
  proto_serde<::orgproto::CmdCustomText, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdCustomText, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&CmdCustomText::name));
  in.for_field(&CmdCustomText::isAttached).get() = out.isattached();
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&CmdCustomText::text));
}

void proto_serde<::orgproto::CmdResults, CmdResults>::write(::orgproto::CmdResults* out, CmdResults const& in) {
  proto_serde<::orgproto::CmdResults, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdResults, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdResults, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdResults, CmdResults>::read(::orgproto::CmdResults const& out, proto_write_accessor<CmdResults> in) {
  proto_serde<::orgproto::CmdResults, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdResults, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdResults, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdTblfm, CmdTblfm>::write(::orgproto::CmdTblfm* out, CmdTblfm const& in) {
  proto_serde<::orgproto::CmdTblfm, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdTblfm, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdTblfm, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdTblfm, CmdTblfm>::read(::orgproto::CmdTblfm const& out, proto_write_accessor<CmdTblfm> in) {
  proto_serde<::orgproto::CmdTblfm, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdTblfm, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdTblfm, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::HashTag, HashTag>::write(::orgproto::HashTag* out, HashTag const& in) {
  proto_serde<::orgproto::HashTag, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::HashTag, HashTag>::read(::orgproto::HashTag const& out, proto_write_accessor<HashTag> in) {
  proto_serde<::orgproto::HashTag, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.head(), in.for_field(&HashTag::head));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.subtags(), in.for_field(&HashTag::subtags));
}

void proto_serde<::orgproto::Footnote, Footnote>::write(::orgproto::Footnote* out, Footnote const& in) {
  proto_serde<::orgproto::Footnote, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(out->mutable_definition(), *in.definition);
  }
}

void proto_serde<::orgproto::Footnote, Footnote>::read(::orgproto::Footnote const& out, proto_write_accessor<Footnote> in) {
  proto_serde<::orgproto::Footnote, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.tag(), in.for_field(&Footnote::tag));
  if (out.has_definition()) {
    proto_serde<Opt<orgproto::AnyNode>, Opt<sem::SemId<sem::Org>>>::read(out.definition(), in.for_field(&Footnote::definition));
  }
}

void proto_serde<::orgproto::sem::Time::Repeat, sem::Time::Repeat>::write(::orgproto::sem::Time::Repeat* out, sem::Time::Repeat const& in) {
  proto_serde<orgproto::Time::Repeat::Mode, sem::Time::Repeat::Mode>::write(out->mutable_mode(), in.mode);
  proto_serde<orgproto::Time::Repeat::Period, sem::Time::Repeat::Period>::write(out->mutable_period(), in.period);
  out->set_count(in.count);
}

void proto_serde<::orgproto::sem::Time::Repeat, sem::Time::Repeat>::read(::orgproto::sem::Time::Repeat const& out, proto_write_accessor<sem::Time::Repeat> in) {
  proto_serde<orgproto::Time::Repeat::Mode, sem::Time::Repeat::Mode>::read(out.mode(), in.for_field(&sem::Time::Repeat::mode));
  proto_serde<orgproto::Time::Repeat::Period, sem::Time::Repeat::Period>::read(out.period(), in.for_field(&sem::Time::Repeat::period));
  in.for_field(&sem::Time::Repeat::count).get() = out.count();
}

void proto_serde<::orgproto::sem::Time::Static, sem::Time::Static>::write(::orgproto::sem::Time::Static* out, sem::Time::Static const& in) {
  if (in.repeat) {
    proto_serde<orgproto::Time::Repeat, sem::Time::Repeat>::write(out->mutable_repeat(), *in.repeat);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::sem::Time::Static, sem::Time::Static>::read(::orgproto::sem::Time::Static const& out, proto_write_accessor<sem::Time::Static> in) {
  if (out.has_repeat()) {
    proto_serde<Opt<orgproto::Time::Repeat>, Opt<sem::Time::Repeat>>::read(out.repeat(), in.for_field(&sem::Time::Static::repeat));
  }
  proto_serde<orgproto::UserTime, UserTime>::read(out.time(), in.for_field(&sem::Time::Static::time));
}

void proto_serde<::orgproto::sem::Time::Dynamic, sem::Time::Dynamic>::write(::orgproto::sem::Time::Dynamic* out, sem::Time::Dynamic const& in) {
  proto_serde<std::string, Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::sem::Time::Dynamic, sem::Time::Dynamic>::read(::orgproto::sem::Time::Dynamic const& out, proto_write_accessor<sem::Time::Dynamic> in) {
  proto_serde<std::string, Str>::read(out.expr(), in.for_field(&sem::Time::Dynamic::expr));
}

void proto_serde<::orgproto::Time, Time>::write(::orgproto::Time* out, Time const& in) {
  proto_serde<::orgproto::Time, sem::Org>::write(out, in);
  out->set_isactive(in.isActive);
  switch (in.time.index()) {
    case 0:
      proto_serde<sem::Time::Static, sem::Time::Static>::write(out->mutable_time()->mutable_static_(), std::get<0>(in.time));
      break;
    case 1:
      proto_serde<sem::Time::Dynamic, sem::Time::Dynamic>::write(out->mutable_time()->mutable_dynamic(), std::get<1>(in.time));
      break;
  }
}

void proto_serde<::orgproto::Time, Time>::read(::orgproto::Time const& out, proto_write_accessor<Time> in) {
  proto_serde<::orgproto::Time, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&Time::isActive).get() = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::Time::TimeVariant::kStatic:
      proto_serde<sem::Time::Static, sem::Time::Static>::read(out.time().static_(), in.for_field_variant<0>(&Time::time));
      break;
    case ::orgproto::Time::TimeVariant::kDynamic:
      proto_serde<sem::Time::Dynamic, sem::Time::Dynamic>::read(out.time().dynamic(), in.for_field_variant<1>(&Time::time));
      break;
  }
}

void proto_serde<::orgproto::TimeRange, TimeRange>::write(::orgproto::TimeRange* out, TimeRange const& in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (!in.to.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), in.to);
  }
}

void proto_serde<::orgproto::TimeRange, TimeRange>::read(::orgproto::TimeRange const& out, proto_write_accessor<TimeRange> in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&TimeRange::from));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.to(), in.for_field(&TimeRange::to));
}

void proto_serde<::orgproto::Macro, Macro>::write(::orgproto::Macro* out, Macro const& in) {
  proto_serde<::orgproto::Macro, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
}

void proto_serde<::orgproto::Macro, Macro>::read(::orgproto::Macro const& out, proto_write_accessor<Macro> in) {
  proto_serde<::orgproto::Macro, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&Macro::name));
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&Macro::parameters));
}

void proto_serde<::orgproto::sem::Symbol::Param, sem::Symbol::Param>::write(::orgproto::sem::Symbol::Param* out, sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::sem::Symbol::Param, sem::Symbol::Param>::read(::orgproto::sem::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in) {
  if (out.has_key()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.key(), in.for_field(&sem::Symbol::Param::key));
  }
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::Symbol::Param::value));
}

void proto_serde<::orgproto::Symbol, Symbol>::write(::orgproto::Symbol* out, Symbol const& in) {
  proto_serde<::orgproto::Symbol, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId<sem::Org>>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::Symbol, Symbol>::read(::orgproto::Symbol const& out, proto_write_accessor<Symbol> in) {
  proto_serde<::orgproto::Symbol, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&Symbol::name));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::read(out.parameters(), in.for_field(&Symbol::parameters));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId<sem::Org>>>::read(out.positional(), in.for_field(&Symbol::positional));
}

void proto_serde<::orgproto::Escaped, Escaped>::write(::orgproto::Escaped* out, Escaped const& in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Escaped, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Escaped, Escaped>::read(::orgproto::Escaped const& out, proto_write_accessor<Escaped> in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Escaped, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Newline, Newline>::write(::orgproto::Newline* out, Newline const& in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Newline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Newline, Newline>::read(::orgproto::Newline const& out, proto_write_accessor<Newline> in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Newline, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Space, Space>::write(::orgproto::Space* out, Space const& in) {
  proto_serde<::orgproto::Space, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Space, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Space, Space>::read(::orgproto::Space const& out, proto_write_accessor<Space> in) {
  proto_serde<::orgproto::Space, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Space, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Word, Word>::write(::orgproto::Word* out, Word const& in) {
  proto_serde<::orgproto::Word, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Word, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Word, Word>::read(::orgproto::Word const& out, proto_write_accessor<Word> in) {
  proto_serde<::orgproto::Word, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Word, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::AtMention, AtMention>::write(::orgproto::AtMention* out, AtMention const& in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::AtMention, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AtMention, AtMention>::read(::orgproto::AtMention const& out, proto_write_accessor<AtMention> in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::AtMention, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::RawText, RawText>::write(::orgproto::RawText* out, RawText const& in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RawText, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RawText, RawText>::read(::orgproto::RawText const& out, proto_write_accessor<RawText> in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::RawText, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Punctuation, Punctuation>::write(::orgproto::Punctuation* out, Punctuation const& in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Punctuation, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Punctuation, Punctuation>::read(::orgproto::Punctuation const& out, proto_write_accessor<Punctuation> in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Punctuation, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Placeholder, Placeholder>::write(::orgproto::Placeholder* out, Placeholder const& in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Placeholder, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Placeholder, Placeholder>::read(::orgproto::Placeholder const& out, proto_write_accessor<Placeholder> in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::Placeholder, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BigIdent, BigIdent>::write(::orgproto::BigIdent* out, BigIdent const& in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::BigIdent, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BigIdent, BigIdent>::read(::orgproto::BigIdent const& out, proto_write_accessor<BigIdent> in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::BigIdent, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::RadioTarget, RadioTarget>::write(::orgproto::RadioTarget* out, RadioTarget const& in) {
  proto_serde<::orgproto::RadioTarget, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RadioTarget, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RadioTarget, RadioTarget>::read(::orgproto::RadioTarget const& out, proto_write_accessor<RadioTarget> in) {
  proto_serde<::orgproto::RadioTarget, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::RadioTarget, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::TextTarget, TextTarget>::write(::orgproto::TextTarget* out, TextTarget const& in) {
  proto_serde<::orgproto::TextTarget, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::TextTarget, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::TextTarget, TextTarget>::read(::orgproto::TextTarget const& out, proto_write_accessor<TextTarget> in) {
  proto_serde<::orgproto::TextTarget, sem::Leaf>::read(out, in.as<sem::Leaf>());
  proto_serde<::orgproto::TextTarget, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Bold, Bold>::write(::orgproto::Bold* out, Bold const& in) {
  proto_serde<::orgproto::Bold, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Bold, Bold>::read(::orgproto::Bold const& out, proto_write_accessor<Bold> in) {
  proto_serde<::orgproto::Bold, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Underline, Underline>::write(::orgproto::Underline* out, Underline const& in) {
  proto_serde<::orgproto::Underline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Underline, Underline>::read(::orgproto::Underline const& out, proto_write_accessor<Underline> in) {
  proto_serde<::orgproto::Underline, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Monospace, Monospace>::write(::orgproto::Monospace* out, Monospace const& in) {
  proto_serde<::orgproto::Monospace, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Monospace, Monospace>::read(::orgproto::Monospace const& out, proto_write_accessor<Monospace> in) {
  proto_serde<::orgproto::Monospace, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::MarkQuote, MarkQuote>::write(::orgproto::MarkQuote* out, MarkQuote const& in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::MarkQuote, MarkQuote>::read(::orgproto::MarkQuote const& out, proto_write_accessor<MarkQuote> in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Verbatim, Verbatim>::write(::orgproto::Verbatim* out, Verbatim const& in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Verbatim, Verbatim>::read(::orgproto::Verbatim const& out, proto_write_accessor<Verbatim> in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Italic, Italic>::write(::orgproto::Italic* out, Italic const& in) {
  proto_serde<::orgproto::Italic, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Italic, Italic>::read(::orgproto::Italic const& out, proto_write_accessor<Italic> in) {
  proto_serde<::orgproto::Italic, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Strike, Strike>::write(::orgproto::Strike* out, Strike const& in) {
  proto_serde<::orgproto::Strike, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Strike, Strike>::read(::orgproto::Strike const& out, proto_write_accessor<Strike> in) {
  proto_serde<::orgproto::Strike, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Par, Par>::write(::orgproto::Par* out, Par const& in) {
  proto_serde<::orgproto::Par, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Par, Par>::read(::orgproto::Par const& out, proto_write_accessor<Par> in) {
  proto_serde<::orgproto::Par, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Latex, Latex>::write(::orgproto::Latex* out, Latex const& in) {
  proto_serde<::orgproto::Latex, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Latex, Latex>::read(::orgproto::Latex const& out, proto_write_accessor<Latex> in) {
  proto_serde<::orgproto::Latex, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::sem::Link::Raw, sem::Link::Raw>::write(::orgproto::sem::Link::Raw* out, sem::Link::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::sem::Link::Raw, sem::Link::Raw>::read(::orgproto::sem::Link::Raw const& out, proto_write_accessor<sem::Link::Raw> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::Link::Raw::text));
}

void proto_serde<::orgproto::sem::Link::Id, sem::Link::Id>::write(::orgproto::sem::Link::Id* out, sem::Link::Id const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::sem::Link::Id, sem::Link::Id>::read(::orgproto::sem::Link::Id const& out, proto_write_accessor<sem::Link::Id> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::Link::Id::text));
}

void proto_serde<::orgproto::sem::Link::Person, sem::Link::Person>::write(::orgproto::sem::Link::Person* out, sem::Link::Person const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::sem::Link::Person, sem::Link::Person>::read(::orgproto::sem::Link::Person const& out, proto_write_accessor<sem::Link::Person> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Link::Person::name));
}

void proto_serde<::orgproto::sem::Link::UserProtocol, sem::Link::UserProtocol>::write(::orgproto::sem::Link::UserProtocol* out, sem::Link::UserProtocol const& in) {
  proto_serde<std::string, Str>::write(out->mutable_protocol(), in.protocol);
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::sem::Link::UserProtocol, sem::Link::UserProtocol>::read(::orgproto::sem::Link::UserProtocol const& out, proto_write_accessor<sem::Link::UserProtocol> in) {
  proto_serde<std::string, Str>::read(out.protocol(), in.for_field(&sem::Link::UserProtocol::protocol));
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::UserProtocol::target));
}

void proto_serde<::orgproto::sem::Link::Internal, sem::Link::Internal>::write(::orgproto::sem::Link::Internal* out, sem::Link::Internal const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::sem::Link::Internal, sem::Link::Internal>::read(::orgproto::sem::Link::Internal const& out, proto_write_accessor<sem::Link::Internal> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::Internal::target));
}

void proto_serde<::orgproto::sem::Link::Footnote, sem::Link::Footnote>::write(::orgproto::sem::Link::Footnote* out, sem::Link::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::sem::Link::Footnote, sem::Link::Footnote>::read(::orgproto::sem::Link::Footnote const& out, proto_write_accessor<sem::Link::Footnote> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Link::Footnote::target));
}

void proto_serde<::orgproto::sem::Link::File, sem::Link::File>::write(::orgproto::sem::Link::File* out, sem::Link::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::sem::Link::File, sem::Link::File>::read(::orgproto::sem::Link::File const& out, proto_write_accessor<sem::Link::File> in) {
  proto_serde<std::string, Str>::read(out.file(), in.for_field(&sem::Link::File::file));
}

void proto_serde<::orgproto::sem::Link::Attachment, sem::Link::Attachment>::write(::orgproto::sem::Link::Attachment* out, sem::Link::Attachment const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::sem::Link::Attachment, sem::Link::Attachment>::read(::orgproto::sem::Link::Attachment const& out, proto_write_accessor<sem::Link::Attachment> in) {
  proto_serde<std::string, Str>::read(out.file(), in.for_field(&sem::Link::Attachment::file));
}

void proto_serde<::orgproto::Link, Link>::write(::orgproto::Link* out, Link const& in) {
  proto_serde<::orgproto::Link, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Link, sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_description(), *in.description);
  }
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::Link::Raw, sem::Link::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::Link::Id, sem::Link::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::Link::Person, sem::Link::Person>::write(out->mutable_data()->mutable_person(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::Link::UserProtocol, sem::Link::UserProtocol>::write(out->mutable_data()->mutable_userprotocol(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<sem::Link::Internal, sem::Link::Internal>::write(out->mutable_data()->mutable_internal(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<sem::Link::Footnote, sem::Link::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<sem::Link::File, sem::Link::File>::write(out->mutable_data()->mutable_file(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<sem::Link::Attachment, sem::Link::Attachment>::write(out->mutable_data()->mutable_attachment(), std::get<7>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Link, Link>::read(::orgproto::Link const& out, proto_write_accessor<Link> in) {
  proto_serde<::orgproto::Link, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Link, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_description()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.description(), in.for_field(&Link::description));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::Link::Data::kRaw:
      proto_serde<sem::Link::Raw, sem::Link::Raw>::read(out.data().raw(), in.for_field_variant<0>(&Link::data));
      break;
    case ::orgproto::Link::Data::kId:
      proto_serde<sem::Link::Id, sem::Link::Id>::read(out.data().id(), in.for_field_variant<1>(&Link::data));
      break;
    case ::orgproto::Link::Data::kPerson:
      proto_serde<sem::Link::Person, sem::Link::Person>::read(out.data().person(), in.for_field_variant<2>(&Link::data));
      break;
    case ::orgproto::Link::Data::kUserprotocol:
      proto_serde<sem::Link::UserProtocol, sem::Link::UserProtocol>::read(out.data().userprotocol(), in.for_field_variant<3>(&Link::data));
      break;
    case ::orgproto::Link::Data::kInternal:
      proto_serde<sem::Link::Internal, sem::Link::Internal>::read(out.data().internal(), in.for_field_variant<4>(&Link::data));
      break;
    case ::orgproto::Link::Data::kFootnote:
      proto_serde<sem::Link::Footnote, sem::Link::Footnote>::read(out.data().footnote(), in.for_field_variant<5>(&Link::data));
      break;
    case ::orgproto::Link::Data::kFile:
      proto_serde<sem::Link::File, sem::Link::File>::read(out.data().file(), in.for_field_variant<6>(&Link::data));
      break;
    case ::orgproto::Link::Data::kAttachment:
      proto_serde<sem::Link::Attachment, sem::Link::Attachment>::read(out.data().attachment(), in.for_field_variant<7>(&Link::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCenter, BlockCenter>::write(::orgproto::BlockCenter* out, BlockCenter const& in) {
  proto_serde<::orgproto::BlockCenter, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockCenter, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockCenter, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockCenter, BlockCenter>::read(::orgproto::BlockCenter const& out, proto_write_accessor<BlockCenter> in) {
  proto_serde<::orgproto::BlockCenter, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockCenter, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockCenter, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockQuote, BlockQuote>::write(::orgproto::BlockQuote* out, BlockQuote const& in) {
  proto_serde<::orgproto::BlockQuote, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockQuote, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockQuote, BlockQuote>::read(::orgproto::BlockQuote const& out, proto_write_accessor<BlockQuote> in) {
  proto_serde<::orgproto::BlockQuote, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockQuote, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockQuote, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockComment, BlockComment>::write(::orgproto::BlockComment* out, BlockComment const& in) {
  proto_serde<::orgproto::BlockComment, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockComment, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockComment, BlockComment>::read(::orgproto::BlockComment const& out, proto_write_accessor<BlockComment> in) {
  proto_serde<::orgproto::BlockComment, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockComment, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockVerse, BlockVerse>::write(::orgproto::BlockVerse* out, BlockVerse const& in) {
  proto_serde<::orgproto::BlockVerse, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockVerse, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockVerse, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockVerse, BlockVerse>::read(::orgproto::BlockVerse const& out, proto_write_accessor<BlockVerse> in) {
  proto_serde<::orgproto::BlockVerse, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockVerse, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockVerse, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockExample, BlockExample>::write(::orgproto::BlockExample* out, BlockExample const& in) {
  proto_serde<::orgproto::BlockExample, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockExample, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockExample, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockExample, BlockExample>::read(::orgproto::BlockExample const& out, proto_write_accessor<BlockExample> in) {
  proto_serde<::orgproto::BlockExample, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockExample, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockExample, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::BlockExport, BlockExport>::write(::orgproto::BlockExport* out, BlockExport const& in) {
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

void proto_serde<::orgproto::BlockExport, BlockExport>::read(::orgproto::BlockExport const& out, proto_write_accessor<BlockExport> in) {
  proto_serde<::orgproto::BlockExport, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockExport, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockExport, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::BlockExport::Format, sem::BlockExport::Format>::read(out.format(), in.for_field(&BlockExport::format));
  proto_serde<std::string, Str>::read(out.exporter(), in.for_field(&BlockExport::exporter));
  if (out.has_placement()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.placement(), in.for_field(&BlockExport::placement));
  }
  proto_serde<std::string, Str>::read(out.content(), in.for_field(&BlockExport::content));
}

void proto_serde<::orgproto::BlockAdmonition, BlockAdmonition>::write(::orgproto::BlockAdmonition* out, BlockAdmonition const& in) {
  proto_serde<::orgproto::BlockAdmonition, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::BlockAdmonition, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::BlockAdmonition, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BlockAdmonition, BlockAdmonition>::read(::orgproto::BlockAdmonition const& out, proto_write_accessor<BlockAdmonition> in) {
  proto_serde<::orgproto::BlockAdmonition, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockAdmonition, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockAdmonition, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::write(::orgproto::sem::BlockCode::Line::Part::Raw* out, sem::BlockCode::Line::Part::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_code(), in.code);
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::read(::orgproto::sem::BlockCode::Line::Part::Raw const& out, proto_write_accessor<sem::BlockCode::Line::Part::Raw> in) {
  proto_serde<std::string, Str>::read(out.code(), in.for_field(&sem::BlockCode::Line::Part::Raw::code));
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::write(::orgproto::sem::BlockCode::Line::Part::Callout* out, sem::BlockCode::Line::Part::Callout const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::read(::orgproto::sem::BlockCode::Line::Part::Callout const& out, proto_write_accessor<sem::BlockCode::Line::Part::Callout> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::BlockCode::Line::Part::Callout::name));
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::write(::orgproto::sem::BlockCode::Line::Part::Tangle* out, sem::BlockCode::Line::Part::Tangle const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::read(::orgproto::sem::BlockCode::Line::Part::Tangle const& out, proto_write_accessor<sem::BlockCode::Line::Part::Tangle> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::BlockCode::Line::Part::Tangle::target));
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part, sem::BlockCode::Line::Part>::write(::orgproto::sem::BlockCode::Line::Part* out, sem::BlockCode::Line::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::sem::BlockCode::Line::Part, sem::BlockCode::Line::Part>::read(::orgproto::sem::BlockCode::Line::Part const& out, proto_write_accessor<sem::BlockCode::Line::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::sem::BlockCode::Line::Part::Data::kRaw:
      proto_serde<sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::BlockCode::Line::Part::data));
      break;
    case ::orgproto::sem::BlockCode::Line::Part::Data::kCallout:
      proto_serde<sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&sem::BlockCode::Line::Part::data));
      break;
    case ::orgproto::sem::BlockCode::Line::Part::Data::kTangle:
      proto_serde<sem::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&sem::BlockCode::Line::Part::data));
      break;
  }
}

void proto_serde<::orgproto::sem::BlockCode::Line, sem::BlockCode::Line>::write(::orgproto::sem::BlockCode::Line* out, sem::BlockCode::Line const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line::Part>, Vec<sem::BlockCode::Line::Part>>::write(out->mutable_parts(), in.parts);
}

void proto_serde<::orgproto::sem::BlockCode::Line, sem::BlockCode::Line>::read(::orgproto::sem::BlockCode::Line const& out, proto_write_accessor<sem::BlockCode::Line> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line::Part>, Vec<sem::BlockCode::Line::Part>>::read(out.parts(), in.for_field(&sem::BlockCode::Line::parts));
}

void proto_serde<::orgproto::sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::write(::orgproto::sem::BlockCode::Switch::LineStart* out, sem::BlockCode::Switch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::read(::orgproto::sem::BlockCode::Switch::LineStart const& out, proto_write_accessor<sem::BlockCode::Switch::LineStart> in) {
  in.for_field(&sem::BlockCode::Switch::LineStart::start).get() = out.start();
  in.for_field(&sem::BlockCode::Switch::LineStart::extendLast).get() = out.extendlast();
}

void proto_serde<::orgproto::sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::write(::orgproto::sem::BlockCode::Switch::CalloutFormat* out, sem::BlockCode::Switch::CalloutFormat const& in) {
  proto_serde<std::string, Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::read(::orgproto::sem::BlockCode::Switch::CalloutFormat const& out, proto_write_accessor<sem::BlockCode::Switch::CalloutFormat> in) {
  proto_serde<std::string, Str>::read(out.format(), in.for_field(&sem::BlockCode::Switch::CalloutFormat::format));
}

void proto_serde<::orgproto::sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::write(::orgproto::sem::BlockCode::Switch::RemoveCallout* out, sem::BlockCode::Switch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::read(::orgproto::sem::BlockCode::Switch::RemoveCallout const& out, proto_write_accessor<sem::BlockCode::Switch::RemoveCallout> in) {
  in.for_field(&sem::BlockCode::Switch::RemoveCallout::remove).get() = out.remove();
}

void proto_serde<::orgproto::sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::write(::orgproto::sem::BlockCode::Switch::EmphasizeLine* out, sem::BlockCode::Switch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::read(::orgproto::sem::BlockCode::Switch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCode::Switch::EmphasizeLine> in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::read(out.line(), in.for_field(&sem::BlockCode::Switch::EmphasizeLine::line));
}

void proto_serde<::orgproto::sem::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::write(::orgproto::sem::BlockCode::Switch::Dedent* out, sem::BlockCode::Switch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::sem::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::read(::orgproto::sem::BlockCode::Switch::Dedent const& out, proto_write_accessor<sem::BlockCode::Switch::Dedent> in) {
  in.for_field(&sem::BlockCode::Switch::Dedent::value).get() = out.value();
}

void proto_serde<::orgproto::sem::BlockCode::Switch, sem::BlockCode::Switch>::write(::orgproto::sem::BlockCode::Switch* out, sem::BlockCode::Switch const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<sem::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::sem::BlockCode::Switch, sem::BlockCode::Switch>::read(::orgproto::sem::BlockCode::Switch const& out, proto_write_accessor<sem::BlockCode::Switch> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::sem::BlockCode::Switch::Data::kLinestart:
      proto_serde<sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart>::read(out.data().linestart(), in.for_field_variant<0>(&sem::BlockCode::Switch::data));
      break;
    case ::orgproto::sem::BlockCode::Switch::Data::kCalloutformat:
      proto_serde<sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat>::read(out.data().calloutformat(), in.for_field_variant<1>(&sem::BlockCode::Switch::data));
      break;
    case ::orgproto::sem::BlockCode::Switch::Data::kRemovecallout:
      proto_serde<sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout>::read(out.data().removecallout(), in.for_field_variant<2>(&sem::BlockCode::Switch::data));
      break;
    case ::orgproto::sem::BlockCode::Switch::Data::kEmphasizeline:
      proto_serde<sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine>::read(out.data().emphasizeline(), in.for_field_variant<3>(&sem::BlockCode::Switch::data));
      break;
    case ::orgproto::sem::BlockCode::Switch::Data::kDedent:
      proto_serde<sem::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent>::read(out.data().dedent(), in.for_field_variant<4>(&sem::BlockCode::Switch::data));
      break;
  }
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::write(::orgproto::sem::BlockCode::EvalResult::None* out, sem::BlockCode::EvalResult::None const& in) {

}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::read(::orgproto::sem::BlockCode::EvalResult::None const& out, proto_write_accessor<sem::BlockCode::EvalResult::None> in) {

}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::write(::orgproto::sem::BlockCode::EvalResult::OrgValue* out, sem::BlockCode::EvalResult::OrgValue const& in) {
  if (!in.value.isNil()) {
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(out->mutable_value(), in.value);
  }
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::read(::orgproto::sem::BlockCode::EvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCode::EvalResult::OrgValue> in) {
  proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(out.value(), in.for_field(&sem::BlockCode::EvalResult::OrgValue::value));
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::write(::orgproto::sem::BlockCode::EvalResult::File* out, sem::BlockCode::EvalResult::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_path(), in.path);
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::read(::orgproto::sem::BlockCode::EvalResult::File const& out, proto_write_accessor<sem::BlockCode::EvalResult::File> in) {
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&sem::BlockCode::EvalResult::File::path));
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::write(::orgproto::sem::BlockCode::EvalResult::Raw* out, sem::BlockCode::EvalResult::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::read(::orgproto::sem::BlockCode::EvalResult::Raw const& out, proto_write_accessor<sem::BlockCode::EvalResult::Raw> in) {
  proto_serde<std::string, Str>::read(out.text(), in.for_field(&sem::BlockCode::EvalResult::Raw::text));
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult, sem::BlockCode::EvalResult>::write(::orgproto::sem::BlockCode::EvalResult* out, sem::BlockCode::EvalResult const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::write(out->mutable_data()->mutable_orgvalue(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::write(out->mutable_data()->mutable_file(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::write(out->mutable_data()->mutable_raw(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::sem::BlockCode::EvalResult, sem::BlockCode::EvalResult>::read(::orgproto::sem::BlockCode::EvalResult const& out, proto_write_accessor<sem::BlockCode::EvalResult> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::sem::BlockCode::EvalResult::Data::kNone:
      proto_serde<sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None>::read(out.data().none(), in.for_field_variant<0>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::sem::BlockCode::EvalResult::Data::kOrgvalue:
      proto_serde<sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue>::read(out.data().orgvalue(), in.for_field_variant<1>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::sem::BlockCode::EvalResult::Data::kFile:
      proto_serde<sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File>::read(out.data().file(), in.for_field_variant<2>(&sem::BlockCode::EvalResult::data));
      break;
    case ::orgproto::sem::BlockCode::EvalResult::Data::kRaw:
      proto_serde<sem::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw>::read(out.data().raw(), in.for_field_variant<3>(&sem::BlockCode::EvalResult::data));
      break;
  }
}

void proto_serde<::orgproto::BlockCode, BlockCode>::write(::orgproto::BlockCode* out, BlockCode const& in) {
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

void proto_serde<::orgproto::BlockCode, BlockCode>::read(::orgproto::BlockCode const& out, proto_write_accessor<BlockCode> in) {
  proto_serde<::orgproto::BlockCode, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::BlockCode, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::BlockCode, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_lang()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.lang(), in.for_field(&BlockCode::lang));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Switch>, Vec<sem::BlockCode::Switch>>::read(out.switches(), in.for_field(&BlockCode::switches));
  proto_serde<orgproto::BlockCode::Exports, sem::BlockCode::Exports>::read(out.exports(), in.for_field(&BlockCode::exports));
  if (out.has_result()) {
    proto_serde<Opt<orgproto::BlockCode::EvalResult>, Opt<sem::BlockCode::EvalResult>>::read(out.result(), in.for_field(&BlockCode::result));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::BlockCode::Line>, Vec<sem::BlockCode::Line>>::read(out.lines(), in.for_field(&BlockCode::lines));
  in.for_field(&BlockCode::cache).get() = out.cache();
  in.for_field(&BlockCode::eval).get() = out.eval();
  in.for_field(&BlockCode::noweb).get() = out.noweb();
  in.for_field(&BlockCode::hlines).get() = out.hlines();
  in.for_field(&BlockCode::tangle).get() = out.tangle();
}

void proto_serde<::orgproto::sem::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::write(::orgproto::sem::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in) {
  if (in.desc) {
    proto_serde<orgproto::StmtList, sem::SemId<sem::StmtList>>::write(out->mutable_desc(), *in.desc);
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::read(::orgproto::sem::SubtreeLog::DescribedLog const& out, proto_write_accessor<sem::SubtreeLog::DescribedLog> in) {
  if (out.has_desc()) {
    proto_serde<Opt<orgproto::StmtList>, Opt<sem::SemId<sem::StmtList>>>::read(out.desc(), in.for_field(&sem::SubtreeLog::DescribedLog::desc));
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::Priority, sem::SubtreeLog::Priority>::write(::orgproto::sem::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>::write(out, in);
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

void proto_serde<::orgproto::sem::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(::orgproto::sem::SubtreeLog::Priority const& out, proto_write_accessor<sem::SubtreeLog::Priority> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  if (out.has_oldpriority()) {
    proto_serde<Opt<std::string>, Opt<std::string>>::read(out.oldpriority(), in.for_field(&sem::SubtreeLog::Priority::oldPriority));
  }
  if (out.has_newpriority()) {
    proto_serde<Opt<std::string>, Opt<std::string>>::read(out.newpriority(), in.for_field(&sem::SubtreeLog::Priority::newPriority));
  }
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Priority::on));
  proto_serde<orgproto::SubtreeLog::Priority::Action, sem::SubtreeLog::Priority::Action>::read(out.action(), in.for_field(&sem::SubtreeLog::Priority::action));
}

void proto_serde<::orgproto::sem::SubtreeLog::Note, sem::SubtreeLog::Note>::write(::orgproto::sem::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::Note, sem::SubtreeLog::Note>::read(::orgproto::sem::SubtreeLog::Note const& out, proto_write_accessor<sem::SubtreeLog::Note> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Note::on));
}

void proto_serde<::orgproto::sem::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(::orgproto::sem::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
  if (!in.from.isNil()) {
    proto_serde<orgproto::Link, sem::SemId<sem::Link>>::write(out->mutable_from(), in.from);
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(::orgproto::sem::SubtreeLog::Refile const& out, proto_write_accessor<sem::SubtreeLog::Refile> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Refile::on));
  proto_serde<orgproto::Link, sem::SemId<sem::Link>>::read(out.from(), in.for_field(&sem::SubtreeLog::Refile::from));
}

void proto_serde<::orgproto::sem::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(::orgproto::sem::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (in.to) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(::orgproto::sem::SubtreeLog::Clock const& out, proto_write_accessor<sem::SubtreeLog::Clock> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&sem::SubtreeLog::Clock::from));
  if (out.has_to()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.to(), in.for_field(&sem::SubtreeLog::Clock::to));
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::State, sem::SubtreeLog::State>::write(::orgproto::sem::SubtreeLog::State* out, sem::SubtreeLog::State const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_from(), in.from);
  proto_serde<std::string, Str>::write(out->mutable_to(), in.to);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
}

void proto_serde<::orgproto::sem::SubtreeLog::State, sem::SubtreeLog::State>::read(::orgproto::sem::SubtreeLog::State const& out, proto_write_accessor<sem::SubtreeLog::State> in) {
  proto_serde<::orgproto::sem::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<std::string, Str>::read(out.from(), in.for_field(&sem::SubtreeLog::State::from));
  proto_serde<std::string, Str>::read(out.to(), in.for_field(&sem::SubtreeLog::State::to));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::State::on));
}

void proto_serde<::orgproto::sem::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(::orgproto::sem::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_on(), in.on);
  }
  if (!in.tag.isNil()) {
    proto_serde<orgproto::HashTag, sem::SemId<sem::HashTag>>::write(out->mutable_tag(), in.tag);
  }
  out->set_added(in.added);
}

void proto_serde<::orgproto::sem::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(::orgproto::sem::SubtreeLog::Tag const& out, proto_write_accessor<sem::SubtreeLog::Tag> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.on(), in.for_field(&sem::SubtreeLog::Tag::on));
  proto_serde<orgproto::HashTag, sem::SemId<sem::HashTag>>::read(out.tag(), in.for_field(&sem::SubtreeLog::Tag::tag));
  in.for_field(&sem::SubtreeLog::Tag::added).get() = out.added();
}

void proto_serde<::orgproto::sem::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::write(::orgproto::sem::SubtreeLog::Unknown* out, sem::SubtreeLog::Unknown const& in) {
  proto_serde<::orgproto::sem::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>::write(out, in);
}

void proto_serde<::orgproto::sem::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::read(::orgproto::sem::SubtreeLog::Unknown const& out, proto_write_accessor<sem::SubtreeLog::Unknown> in) {
  proto_serde<::orgproto::sem::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>::read(out, in.as<sem::SubtreeLog::DescribedLog>());
}

void proto_serde<::orgproto::SubtreeLog, SubtreeLog>::write(::orgproto::SubtreeLog* out, SubtreeLog const& in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::write(out, in);
  switch (in.log.index()) {
    case 0:
      proto_serde<sem::SubtreeLog::Priority, sem::SubtreeLog::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log));
      break;
    case 1:
      proto_serde<sem::SubtreeLog::Note, sem::SubtreeLog::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log));
      break;
    case 2:
      proto_serde<sem::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log));
      break;
    case 3:
      proto_serde<sem::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log));
      break;
    case 4:
      proto_serde<sem::SubtreeLog::State, sem::SubtreeLog::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log));
      break;
    case 5:
      proto_serde<sem::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(out->mutable_log()->mutable_tag(), std::get<5>(in.log));
      break;
    case 6:
      proto_serde<sem::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::write(out->mutable_log()->mutable_unknown(), std::get<6>(in.log));
      break;
  }
}

void proto_serde<::orgproto::SubtreeLog, SubtreeLog>::read(::orgproto::SubtreeLog const& out, proto_write_accessor<SubtreeLog> in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::read(out, in.as<sem::Org>());
  switch (out.log().kind_case()) {
    case ::orgproto::SubtreeLog::LogEntry::kPriority:
      proto_serde<sem::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(out.log().priority(), in.for_field_variant<0>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kNote:
      proto_serde<sem::SubtreeLog::Note, sem::SubtreeLog::Note>::read(out.log().note(), in.for_field_variant<1>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kRefile:
      proto_serde<sem::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(out.log().refile(), in.for_field_variant<2>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kClock:
      proto_serde<sem::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(out.log().clock(), in.for_field_variant<3>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kState:
      proto_serde<sem::SubtreeLog::State, sem::SubtreeLog::State>::read(out.log().state(), in.for_field_variant<4>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kTag:
      proto_serde<sem::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(out.log().tag(), in.for_field_variant<5>(&SubtreeLog::log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kUnknown:
      proto_serde<sem::SubtreeLog::Unknown, sem::SubtreeLog::Unknown>::read(out.log().unknown(), in.for_field_variant<6>(&SubtreeLog::log));
      break;
  }
}

void proto_serde<::orgproto::sem::Subtree::Period, sem::Subtree::Period>::write(::orgproto::sem::Subtree::Period* out, sem::Subtree::Period const& in) {
  proto_serde<orgproto::Subtree::Period::Kind, sem::Subtree::Period::Kind>::write(out->mutable_kind(), in.kind);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (in.to) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::sem::Subtree::Period, sem::Subtree::Period>::read(::orgproto::sem::Subtree::Period const& out, proto_write_accessor<sem::Subtree::Period> in) {
  proto_serde<orgproto::Subtree::Period::Kind, sem::Subtree::Period::Kind>::read(out.kind(), in.for_field(&sem::Subtree::Period::kind));
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.from(), in.for_field(&sem::Subtree::Period::from));
  if (out.has_to()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.to(), in.for_field(&sem::Subtree::Period::to));
  }
}

void proto_serde<::orgproto::sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(::orgproto::sem::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(::orgproto::sem::Subtree::Property::Nonblocking const& out, proto_write_accessor<sem::Subtree::Property::Nonblocking> in) {
  in.for_field(&sem::Subtree::Property::Nonblocking::isBlocking).get() = out.isblocking();
}

void proto_serde<::orgproto::sem::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(::orgproto::sem::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in) {

}

void proto_serde<::orgproto::sem::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(::orgproto::sem::Subtree::Property::Trigger const& out, proto_write_accessor<sem::Subtree::Property::Trigger> in) {

}

void proto_serde<::orgproto::sem::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(::orgproto::sem::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in) {
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::sem::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(::orgproto::sem::Subtree::Property::Origin const& out, proto_write_accessor<sem::Subtree::Property::Origin> in) {
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&sem::Subtree::Property::Origin::text));
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(::orgproto::sem::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in) {
  proto_serde<std::string, Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(::orgproto::sem::Subtree::Property::ExportLatexClass const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClass> in) {
  proto_serde<std::string, Str>::read(out.latexclass(), in.for_field(&sem::Subtree::Property::ExportLatexClass::latexClass));
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(::orgproto::sem::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(::orgproto::sem::Subtree::Property::ExportLatexClassOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClassOptions> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.options(), in.for_field(&sem::Subtree::Property::ExportLatexClassOptions::options));
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(::orgproto::sem::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in) {
  proto_serde<std::string, Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(::orgproto::sem::Subtree::Property::ExportLatexHeader const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexHeader> in) {
  proto_serde<std::string, Str>::read(out.header(), in.for_field(&sem::Subtree::Property::ExportLatexHeader::header));
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(::orgproto::sem::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in) {
  proto_serde<std::string, Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(::orgproto::sem::Subtree::Property::ExportLatexCompiler const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexCompiler> in) {
  proto_serde<std::string, Str>::read(out.compiler(), in.for_field(&sem::Subtree::Property::ExportLatexCompiler::compiler));
}

void proto_serde<::orgproto::sem::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(::orgproto::sem::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::sem::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(::orgproto::sem::Subtree::Property::Ordered const& out, proto_write_accessor<sem::Subtree::Property::Ordered> in) {
  in.for_field(&sem::Subtree::Property::Ordered::isOrdered).get() = out.isordered();
}

void proto_serde<::orgproto::sem::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(::orgproto::sem::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::sem::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(::orgproto::sem::Subtree::Property::Effort const& out, proto_write_accessor<sem::Subtree::Property::Effort> in) {
  in.for_field(&sem::Subtree::Property::Effort::hours).get() = out.hours();
  in.for_field(&sem::Subtree::Property::Effort::minutes).get() = out.minutes();
}

void proto_serde<::orgproto::sem::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(::orgproto::sem::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in) {
  proto_serde<orgproto::Subtree::Property::Visibility::Level, sem::Subtree::Property::Visibility::Level>::write(out->mutable_level(), in.level);
}

void proto_serde<::orgproto::sem::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(::orgproto::sem::Subtree::Property::Visibility const& out, proto_write_accessor<sem::Subtree::Property::Visibility> in) {
  proto_serde<orgproto::Subtree::Property::Visibility::Level, sem::Subtree::Property::Visibility::Level>::read(out.level(), in.for_field(&sem::Subtree::Property::Visibility::level));
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(::orgproto::sem::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in) {
  proto_serde<std::string, Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::sem::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(::orgproto::sem::Subtree::Property::ExportOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportOptions> in) {
  proto_serde<std::string, Str>::read(out.backend(), in.for_field(&sem::Subtree::Property::ExportOptions::backend));
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::read(out.values(), in.for_field(&sem::Subtree::Property::ExportOptions::values));
}

void proto_serde<::orgproto::sem::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(::orgproto::sem::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::sem::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(::orgproto::sem::Subtree::Property::Blocker const& out, proto_write_accessor<sem::Subtree::Property::Blocker> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.blockers(), in.for_field(&sem::Subtree::Property::Blocker::blockers));
}

void proto_serde<::orgproto::sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(::orgproto::sem::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in) {

}

void proto_serde<::orgproto::sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(::orgproto::sem::Subtree::Property::Unnumbered const& out, proto_write_accessor<sem::Subtree::Property::Unnumbered> in) {

}

void proto_serde<::orgproto::sem::Subtree::Property::Created, sem::Subtree::Property::Created>::write(::orgproto::sem::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in) {
  if (!in.time.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_time(), in.time);
  }
}

void proto_serde<::orgproto::sem::Subtree::Property::Created, sem::Subtree::Property::Created>::read(::orgproto::sem::Subtree::Property::Created const& out, proto_write_accessor<sem::Subtree::Property::Created> in) {
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.time(), in.for_field(&sem::Subtree::Property::Created::time));
}

void proto_serde<::orgproto::sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::write(::orgproto::sem::Subtree::Property::CustomArgs* out, sem::Subtree::Property::CustomArgs const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (in.sub) {
    proto_serde<std::string, Str>::write(out->mutable_sub(), *in.sub);
  }
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
}

void proto_serde<::orgproto::sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::read(::orgproto::sem::Subtree::Property::CustomArgs const& out, proto_write_accessor<sem::Subtree::Property::CustomArgs> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Subtree::Property::CustomArgs::name));
  if (out.has_sub()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.sub(), in.for_field(&sem::Subtree::Property::CustomArgs::sub));
  }
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&sem::Subtree::Property::CustomArgs::parameters));
}

void proto_serde<::orgproto::sem::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::write(::orgproto::sem::Subtree::Property::CustomRaw* out, sem::Subtree::Property::CustomRaw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::sem::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::read(::orgproto::sem::Subtree::Property::CustomRaw const& out, proto_write_accessor<sem::Subtree::Property::CustomRaw> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Subtree::Property::CustomRaw::name));
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::Subtree::Property::CustomRaw::value));
}

void proto_serde<::orgproto::sem::Subtree::Property, sem::Subtree::Property>::write(::orgproto::sem::Subtree::Property* out, sem::Subtree::Property const& in) {
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::write(out->mutable_mainsetrule(), in.mainSetRule);
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::write(out->mutable_subsetrule(), in.subSetRule);
  proto_serde<orgproto::Subtree::Property::InheritanceMode, sem::Subtree::Property::InheritanceMode>::write(out->mutable_inheritancemode(), in.inheritanceMode);
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(out->mutable_data()->mutable_origin(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<4>(in.data));
      break;
    case 5:
      proto_serde<sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<5>(in.data));
      break;
    case 6:
      proto_serde<sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<6>(in.data));
      break;
    case 7:
      proto_serde<sem::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<7>(in.data));
      break;
    case 8:
      proto_serde<sem::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(out->mutable_data()->mutable_effort(), std::get<8>(in.data));
      break;
    case 9:
      proto_serde<sem::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<9>(in.data));
      break;
    case 10:
      proto_serde<sem::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<10>(in.data));
      break;
    case 11:
      proto_serde<sem::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<11>(in.data));
      break;
    case 12:
      proto_serde<sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<12>(in.data));
      break;
    case 13:
      proto_serde<sem::Subtree::Property::Created, sem::Subtree::Property::Created>::write(out->mutable_data()->mutable_created(), std::get<13>(in.data));
      break;
    case 14:
      proto_serde<sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::write(out->mutable_data()->mutable_customargs(), std::get<14>(in.data));
      break;
    case 15:
      proto_serde<sem::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::write(out->mutable_data()->mutable_customraw(), std::get<15>(in.data));
      break;
  }
}

void proto_serde<::orgproto::sem::Subtree::Property, sem::Subtree::Property>::read(::orgproto::sem::Subtree::Property const& out, proto_write_accessor<sem::Subtree::Property> in) {
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::read(out.mainsetrule(), in.for_field(&sem::Subtree::Property::mainSetRule));
  proto_serde<orgproto::Subtree::Property::SetMode, sem::Subtree::Property::SetMode>::read(out.subsetrule(), in.for_field(&sem::Subtree::Property::subSetRule));
  proto_serde<orgproto::Subtree::Property::InheritanceMode, sem::Subtree::Property::InheritanceMode>::read(out.inheritancemode(), in.for_field(&sem::Subtree::Property::inheritanceMode));
  switch (out.data().kind_case()) {
    case ::orgproto::sem::Subtree::Property::Data::kNonblocking:
      proto_serde<sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(out.data().nonblocking(), in.for_field_variant<0>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kTrigger:
      proto_serde<sem::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(out.data().trigger(), in.for_field_variant<1>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kOrigin:
      proto_serde<sem::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(out.data().origin(), in.for_field_variant<2>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kExportlatexclass:
      proto_serde<sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(out.data().exportlatexclass(), in.for_field_variant<3>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kExportlatexclassoptions:
      proto_serde<sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(out.data().exportlatexclassoptions(), in.for_field_variant<4>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kExportlatexheader:
      proto_serde<sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(out.data().exportlatexheader(), in.for_field_variant<5>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kExportlatexcompiler:
      proto_serde<sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(out.data().exportlatexcompiler(), in.for_field_variant<6>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kOrdered:
      proto_serde<sem::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(out.data().ordered(), in.for_field_variant<7>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kEffort:
      proto_serde<sem::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(out.data().effort(), in.for_field_variant<8>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kVisibility:
      proto_serde<sem::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(out.data().visibility(), in.for_field_variant<9>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kExportoptions:
      proto_serde<sem::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(out.data().exportoptions(), in.for_field_variant<10>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kBlocker:
      proto_serde<sem::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(out.data().blocker(), in.for_field_variant<11>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kUnnumbered:
      proto_serde<sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(out.data().unnumbered(), in.for_field_variant<12>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kCreated:
      proto_serde<sem::Subtree::Property::Created, sem::Subtree::Property::Created>::read(out.data().created(), in.for_field_variant<13>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kCustomargs:
      proto_serde<sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs>::read(out.data().customargs(), in.for_field_variant<14>(&sem::Subtree::Property::data));
      break;
    case ::orgproto::sem::Subtree::Property::Data::kCustomraw:
      proto_serde<sem::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw>::read(out.data().customraw(), in.for_field_variant<15>(&sem::Subtree::Property::data));
      break;
  }
}

void proto_serde<::orgproto::Subtree, Subtree>::write(::orgproto::Subtree* out, Subtree const& in) {
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

void proto_serde<::orgproto::Subtree, Subtree>::read(::orgproto::Subtree const& out, proto_write_accessor<Subtree> in) {
  proto_serde<::orgproto::Subtree, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&Subtree::level).get() = out.level();
  if (out.has_treeid()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.treeid(), in.for_field(&Subtree::treeId));
  }
  if (out.has_todo()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.todo(), in.for_field(&Subtree::todo));
  }
  if (out.has_completion()) {
    proto_serde<Opt<orgproto::SubtreeCompletion>, Opt<sem::SemId<sem::SubtreeCompletion>>>::read(out.completion(), in.for_field(&Subtree::completion));
  }
  if (out.has_description()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.description(), in.for_field(&Subtree::description));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.tags(), in.for_field(&Subtree::tags));
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.title(), in.for_field(&Subtree::title));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, Vec<sem::SemId<sem::SubtreeLog>>>::read(out.logbook(), in.for_field(&Subtree::logbook));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(out.properties(), in.for_field(&Subtree::properties));
  if (out.has_closed()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.closed(), in.for_field(&Subtree::closed));
  }
  if (out.has_deadline()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.deadline(), in.for_field(&Subtree::deadline));
  }
  if (out.has_scheduled()) {
    proto_serde<Opt<orgproto::Time>, Opt<sem::SemId<sem::Time>>>::read(out.scheduled(), in.for_field(&Subtree::scheduled));
  }
  in.for_field(&Subtree::isComment).get() = out.iscomment();
  in.for_field(&Subtree::isArchived).get() = out.isarchived();
  if (out.has_priority()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.priority(), in.for_field(&Subtree::priority));
  }
}

void proto_serde<::orgproto::SubtreeCompletion, SubtreeCompletion>::write(::orgproto::SubtreeCompletion* out, SubtreeCompletion const& in) {
  proto_serde<::orgproto::SubtreeCompletion, sem::Org>::write(out, in);
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::SubtreeCompletion, SubtreeCompletion>::read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<SubtreeCompletion> in) {
  proto_serde<::orgproto::SubtreeCompletion, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&SubtreeCompletion::done).get() = out.done();
  in.for_field(&SubtreeCompletion::full).get() = out.full();
  in.for_field(&SubtreeCompletion::isPercent).get() = out.ispercent();
}

void proto_serde<::orgproto::Cell, Cell>::write(::orgproto::Cell* out, Cell const& in) {
  proto_serde<::orgproto::Cell, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Cell, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Cell, sem::Org>::write(out, in);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Cell, Cell>::read(::orgproto::Cell const& out, proto_write_accessor<Cell> in) {
  proto_serde<::orgproto::Cell, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Cell, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Cell, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&Cell::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Row, Row>::write(::orgproto::Row* out, Row const& in) {
  proto_serde<::orgproto::Row, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Row, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Row, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::write(out->mutable_cells(), in.cells);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Row, Row>::read(::orgproto::Row const& out, proto_write_accessor<Row> in) {
  proto_serde<::orgproto::Row, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Row, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Row, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::read(out.cells(), in.for_field(&Row::cells));
  in.for_field(&Row::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Table, Table>::write(::orgproto::Table* out, Table const& in) {
  proto_serde<::orgproto::Table, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::Table, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Table, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::write(out->mutable_rows(), in.rows);
  out->set_isblock(in.isBlock);
}

void proto_serde<::orgproto::Table, Table>::read(::orgproto::Table const& out, proto_write_accessor<Table> in) {
  proto_serde<::orgproto::Table, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::Table, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Table, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::read(out.rows(), in.for_field(&Table::rows));
  in.for_field(&Table::isBlock).get() = out.isblock();
}

void proto_serde<::orgproto::Paragraph, Paragraph>::write(::orgproto::Paragraph* out, Paragraph const& in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Paragraph, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Paragraph, Paragraph>::read(::orgproto::Paragraph const& out, proto_write_accessor<Paragraph> in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Paragraph, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::write(::orgproto::sem::AnnotatedParagraph::None* out, sem::AnnotatedParagraph::None const& in) {

}

void proto_serde<::orgproto::sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::read(::orgproto::sem::AnnotatedParagraph::None const& out, proto_write_accessor<sem::AnnotatedParagraph::None> in) {

}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::write(::orgproto::sem::AnnotatedParagraph::Footnote* out, sem::AnnotatedParagraph::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::read(::orgproto::sem::AnnotatedParagraph::Footnote const& out, proto_write_accessor<sem::AnnotatedParagraph::Footnote> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::AnnotatedParagraph::Footnote::name));
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::write(::orgproto::sem::AnnotatedParagraph::Admonition* out, sem::AnnotatedParagraph::Admonition const& in) {
  if (!in.name.isNil()) {
    proto_serde<orgproto::BigIdent, sem::SemId<sem::BigIdent>>::write(out->mutable_name(), in.name);
  }
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::read(::orgproto::sem::AnnotatedParagraph::Admonition const& out, proto_write_accessor<sem::AnnotatedParagraph::Admonition> in) {
  proto_serde<orgproto::BigIdent, sem::SemId<sem::BigIdent>>::read(out.name(), in.for_field(&sem::AnnotatedParagraph::Admonition::name));
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::write(::orgproto::sem::AnnotatedParagraph::Timestamp* out, sem::AnnotatedParagraph::Timestamp const& in) {
  if (!in.time.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_time(), in.time);
  }
}

void proto_serde<::orgproto::sem::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::read(::orgproto::sem::AnnotatedParagraph::Timestamp const& out, proto_write_accessor<sem::AnnotatedParagraph::Timestamp> in) {
  proto_serde<orgproto::Time, sem::SemId<sem::Time>>::read(out.time(), in.for_field(&sem::AnnotatedParagraph::Timestamp::time));
}

void proto_serde<::orgproto::AnnotatedParagraph, AnnotatedParagraph>::write(::orgproto::AnnotatedParagraph* out, AnnotatedParagraph const& in) {
  proto_serde<::orgproto::AnnotatedParagraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::AnnotatedParagraph, sem::Org>::write(out, in);
  switch (in.data.index()) {
    case 0:
      proto_serde<sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::write(out->mutable_data()->mutable_none(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::write(out->mutable_data()->mutable_admonition(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::write(out->mutable_data()->mutable_timestamp(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::AnnotatedParagraph, AnnotatedParagraph>::read(::orgproto::AnnotatedParagraph const& out, proto_write_accessor<AnnotatedParagraph> in) {
  proto_serde<::orgproto::AnnotatedParagraph, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::AnnotatedParagraph, sem::Org>::read(out, in.as<sem::Org>());
  switch (out.data().kind_case()) {
    case ::orgproto::AnnotatedParagraph::Data::kNone:
      proto_serde<sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::None>::read(out.data().none(), in.for_field_variant<0>(&AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kFootnote:
      proto_serde<sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote>::read(out.data().footnote(), in.for_field_variant<1>(&AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kAdmonition:
      proto_serde<sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition>::read(out.data().admonition(), in.for_field_variant<2>(&AnnotatedParagraph::data));
      break;
    case ::orgproto::AnnotatedParagraph::Data::kTimestamp:
      proto_serde<sem::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp>::read(out.data().timestamp(), in.for_field_variant<3>(&AnnotatedParagraph::data));
      break;
  }
}

void proto_serde<::orgproto::ColonExample, ColonExample>::write(::orgproto::ColonExample* out, ColonExample const& in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ColonExample, ColonExample>::read(::orgproto::ColonExample const& out, proto_write_accessor<ColonExample> in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdAttr, CmdAttr>::write(::orgproto::CmdAttr* out, CmdAttr const& in) {
  proto_serde<::orgproto::CmdAttr, sem::Cmd>::write(out, in);
  proto_serde<::orgproto::CmdAttr, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CmdAttr, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::CmdAttr, CmdAttr>::read(::orgproto::CmdAttr const& out, proto_write_accessor<CmdAttr> in) {
  proto_serde<::orgproto::CmdAttr, sem::Cmd>::read(out, in.as<sem::Cmd>());
  proto_serde<::orgproto::CmdAttr, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CmdAttr, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&CmdAttr::target));
}

void proto_serde<::orgproto::Call, Call>::write(::orgproto::Call* out, Call const& in) {
  proto_serde<::orgproto::Call, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
  out->set_iscommand(in.isCommand);
}

void proto_serde<::orgproto::Call, Call>::read(::orgproto::Call const& out, proto_write_accessor<Call> in) {
  proto_serde<::orgproto::Call, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&Call::name));
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&Call::parameters));
  in.for_field(&Call::isCommand).get() = out.iscommand();
}

void proto_serde<::orgproto::List, List>::write(::orgproto::List* out, List const& in) {
  proto_serde<::orgproto::List, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::List, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::List, List>::read(::orgproto::List const& out, proto_write_accessor<List> in) {
  proto_serde<::orgproto::List, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::List, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::ListItem, ListItem>::write(::orgproto::ListItem* out, ListItem const& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::write(out, in);
  proto_serde<orgproto::ListItem::Checkbox, sem::ListItem::Checkbox>::write(out->mutable_checkbox(), in.checkbox);
  if (in.header) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
  if (in.bullet) {
    proto_serde<std::string, Str>::write(out->mutable_bullet(), *in.bullet);
  }
}

void proto_serde<::orgproto::ListItem, ListItem>::read(::orgproto::ListItem const& out, proto_write_accessor<ListItem> in) {
  proto_serde<::orgproto::ListItem, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::ListItem::Checkbox, sem::ListItem::Checkbox>::read(out.checkbox(), in.for_field(&ListItem::checkbox));
  if (out.has_header()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.header(), in.for_field(&ListItem::header));
  }
  if (out.has_bullet()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.bullet(), in.for_field(&ListItem::bullet));
  }
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport>::write(::orgproto::sem::DocumentOptions::ExportConfig::TaskExport* out, sem::DocumentOptions::ExportConfig::TaskExport const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_taskwhitelist(), in.taskWhitelist);
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport>::read(::orgproto::sem::DocumentOptions::ExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::TaskExport> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.taskwhitelist(), in.for_field(&sem::DocumentOptions::ExportConfig::TaskExport::taskWhitelist));
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::write(::orgproto::sem::DocumentOptions::ExportConfig::DoExport* out, sem::DocumentOptions::ExportConfig::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::read(::orgproto::sem::DocumentOptions::ExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::DoExport> in) {
  in.for_field(&sem::DocumentOptions::ExportConfig::DoExport::exportToc).get() = out.exporttoc();
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::write(::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed* out, sem::DocumentOptions::ExportConfig::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::read(::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::ExportFixed> in) {
  in.for_field(&sem::DocumentOptions::ExportConfig::ExportFixed::exportLevels).get() = out.exportlevels();
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::write(::orgproto::sem::DocumentOptions::ExportConfig* out, sem::DocumentOptions::ExportConfig const& in) {
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
      proto_serde<sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::sem::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::read(::orgproto::sem::DocumentOptions::ExportConfig const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig> in) {
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
    case ::orgproto::sem::DocumentOptions::ExportConfig::TocExport::kDoexport:
      proto_serde<sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&sem::DocumentOptions::ExportConfig::data));
      break;
    case ::orgproto::sem::DocumentOptions::ExportConfig::TocExport::kExportfixed:
      proto_serde<sem::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&sem::DocumentOptions::ExportConfig::data));
      break;
  }
}

void proto_serde<::orgproto::DocumentOptions, DocumentOptions>::write(::orgproto::DocumentOptions* out, DocumentOptions const& in) {
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

void proto_serde<::orgproto::DocumentOptions, DocumentOptions>::read(::orgproto::DocumentOptions const& out, proto_write_accessor<DocumentOptions> in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::read(out.initialvisibility(), in.for_field(&DocumentOptions::initialVisibility));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(out.properties(), in.for_field(&DocumentOptions::properties));
  proto_serde<orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig>::read(out.exportconfig(), in.for_field(&DocumentOptions::exportConfig));
  if (out.has_fixedwidthsections()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.fixedwidthsections(), in.for_field(&DocumentOptions::fixedWidthSections));
  }
  if (out.has_startupindented()) {
    proto_serde<Opt<bool>, Opt<bool>>::read(out.startupindented(), in.for_field(&DocumentOptions::startupIndented));
  }
  if (out.has_category()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.category(), in.for_field(&DocumentOptions::category));
  }
  if (out.has_setupfile()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.setupfile(), in.for_field(&DocumentOptions::setupfile));
  }
  if (out.has_maxsubtreelevelexport()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.maxsubtreelevelexport(), in.for_field(&DocumentOptions::maxSubtreeLevelExport));
  }
}

void proto_serde<::orgproto::Document, Document>::write(::orgproto::Document* out, Document const& in) {
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

void proto_serde<::orgproto::Document, Document>::read(::orgproto::Document const& out, proto_write_accessor<Document> in) {
  proto_serde<::orgproto::Document, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_title()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.title(), in.for_field(&Document::title));
  }
  if (out.has_author()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.author(), in.for_field(&Document::author));
  }
  if (out.has_creator()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.creator(), in.for_field(&Document::creator));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemId<sem::HashTag>>>::read(out.filetags(), in.for_field(&Document::filetags));
  if (out.has_email()) {
    proto_serde<Opt<orgproto::RawText>, Opt<sem::SemId<sem::RawText>>>::read(out.email(), in.for_field(&Document::email));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.language(), in.for_field(&Document::language));
  proto_serde<orgproto::DocumentOptions, sem::SemId<sem::DocumentOptions>>::read(out.options(), in.for_field(&Document::options));
  if (out.has_exportfilename()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.exportfilename(), in.for_field(&Document::exportFileName));
  }
}

void proto_serde<::orgproto::FileTarget, FileTarget>::write(::orgproto::FileTarget* out, FileTarget const& in) {
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

void proto_serde<::orgproto::FileTarget, FileTarget>::read(::orgproto::FileTarget const& out, proto_write_accessor<FileTarget> in) {
  proto_serde<::orgproto::FileTarget, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&FileTarget::path));
  if (out.has_line()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.line(), in.for_field(&FileTarget::line));
  }
  if (out.has_searchtarget()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.searchtarget(), in.for_field(&FileTarget::searchTarget));
  }
  in.for_field(&FileTarget::restrictToHeadlines).get() = out.restricttoheadlines();
  if (out.has_targetid()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.targetid(), in.for_field(&FileTarget::targetId));
  }
  if (out.has_regexp()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.regexp(), in.for_field(&FileTarget::regexp));
  }
}

void proto_serde<::orgproto::TextSeparator, TextSeparator>::write(::orgproto::TextSeparator* out, TextSeparator const& in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::TextSeparator, TextSeparator>::read(::orgproto::TextSeparator const& out, proto_write_accessor<TextSeparator> in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::sem::Include::Example, sem::Include::Example>::write(::orgproto::sem::Include::Example* out, sem::Include::Example const& in) {

}

void proto_serde<::orgproto::sem::Include::Example, sem::Include::Example>::read(::orgproto::sem::Include::Example const& out, proto_write_accessor<sem::Include::Example> in) {

}

void proto_serde<::orgproto::sem::Include::Export, sem::Include::Export>::write(::orgproto::sem::Include::Export* out, sem::Include::Export const& in) {

}

void proto_serde<::orgproto::sem::Include::Export, sem::Include::Export>::read(::orgproto::sem::Include::Export const& out, proto_write_accessor<sem::Include::Export> in) {

}

void proto_serde<::orgproto::sem::Include::Src, sem::Include::Src>::write(::orgproto::sem::Include::Src* out, sem::Include::Src const& in) {

}

void proto_serde<::orgproto::sem::Include::Src, sem::Include::Src>::read(::orgproto::sem::Include::Src const& out, proto_write_accessor<sem::Include::Src> in) {

}

void proto_serde<::orgproto::sem::Include::OrgDocument, sem::Include::OrgDocument>::write(::orgproto::sem::Include::OrgDocument* out, sem::Include::OrgDocument const& in) {
  if (in.minLevel) {
    out->set_minlevel(*in.minLevel);
  }
}

void proto_serde<::orgproto::sem::Include::OrgDocument, sem::Include::OrgDocument>::read(::orgproto::sem::Include::OrgDocument const& out, proto_write_accessor<sem::Include::OrgDocument> in) {
  if (out.has_minlevel()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.minlevel(), in.for_field(&sem::Include::OrgDocument::minLevel));
  }
}

void proto_serde<::orgproto::Include, Include>::write(::orgproto::Include* out, Include const& in) {
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
      proto_serde<sem::Include::Example, sem::Include::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<sem::Include::Export, sem::Include::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<sem::Include::Src, sem::Include::Src>::write(out->mutable_data()->mutable_src(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<sem::Include::OrgDocument, sem::Include::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Include, Include>::read(::orgproto::Include const& out, proto_write_accessor<Include> in) {
  proto_serde<::orgproto::Include, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.path(), in.for_field(&Include::path));
  if (out.has_firstline()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.firstline(), in.for_field(&Include::firstLine));
  }
  if (out.has_lastline()) {
    proto_serde<Opt<::int32_t>, Opt<int>>::read(out.lastline(), in.for_field(&Include::lastLine));
  }
  switch (out.data().kind_case()) {
    case ::orgproto::Include::Data::kExample:
      proto_serde<sem::Include::Example, sem::Include::Example>::read(out.data().example(), in.for_field_variant<0>(&Include::data));
      break;
    case ::orgproto::Include::Data::kExport:
      proto_serde<sem::Include::Export, sem::Include::Export>::read(out.data().export_(), in.for_field_variant<1>(&Include::data));
      break;
    case ::orgproto::Include::Data::kSrc:
      proto_serde<sem::Include::Src, sem::Include::Src>::read(out.data().src(), in.for_field_variant<2>(&Include::data));
      break;
    case ::orgproto::Include::Data::kOrgdocument:
      proto_serde<sem::Include::OrgDocument, sem::Include::OrgDocument>::read(out.data().orgdocument(), in.for_field_variant<3>(&Include::data));
      break;
  }
}

void proto_serde<::orgproto::DocumentGroup, DocumentGroup>::write(::orgproto::DocumentGroup* out, DocumentGroup const& in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::DocumentGroup, DocumentGroup>::read(::orgproto::DocumentGroup const& out, proto_write_accessor<DocumentGroup> in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::read(out, in.as<sem::Org>());
}

/* clang-format on */