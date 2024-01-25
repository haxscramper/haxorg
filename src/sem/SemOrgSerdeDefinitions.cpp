/* clang-format off */
#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>
void proto_serde<::orgproto::StmtList, sem::StmtList>::write(::orgproto::StmtList* out, sem::StmtList const& in) {
  proto_serde<::orgproto::StmtList, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::StmtList, sem::StmtList>::read(sem::ContextStore* context, ::orgproto::StmtList const& out, sem::StmtList& in) {
  proto_serde<::orgproto::StmtList, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Empty, sem::Empty>::write(::orgproto::Empty* out, sem::Empty const& in) {
  proto_serde<::orgproto::Empty, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Empty, sem::Empty>::read(sem::ContextStore* context, ::orgproto::Empty const& out, sem::Empty& in) {
  proto_serde<::orgproto::Empty, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Row, sem::Row>::write(::orgproto::Row* out, sem::Row const& in) {
  proto_serde<::orgproto::Row, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Row, sem::Row>::read(sem::ContextStore* context, ::orgproto::Row const& out, sem::Row& in) {
  proto_serde<::orgproto::Row, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Table, sem::Table>::write(::orgproto::Table* out, sem::Table const& in) {
  proto_serde<::orgproto::Table, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Table, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemIdT<sem::Row>>>::write(out->mutable_rows(), in.rows);
}

void proto_serde<::orgproto::Table, sem::Table>::read(sem::ContextStore* context, ::orgproto::Table const& out, sem::Table& in) {
  proto_serde<::orgproto::Table, sem::Stmt>::read(context, out, in);
  proto_serde<::orgproto::Table, sem::Org>::read(context, out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemIdT<sem::Row>>>::read(context, out.rows(), in.rows);
}

void proto_serde<::orgproto::HashTag, sem::HashTag>::write(::orgproto::HashTag* out, sem::HashTag const& in) {
  proto_serde<::orgproto::HashTag, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemIdT<sem::HashTag>>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::HashTag, sem::HashTag>::read(sem::ContextStore* context, ::orgproto::HashTag const& out, sem::HashTag& in) {
  proto_serde<::orgproto::HashTag, sem::Org>::read(context, out, in);
  proto_serde<std::string, Str>::read(context, out.head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemIdT<sem::HashTag>>>::read(context, out.subtags(), in.subtags);
}

void proto_serde<::orgproto::Footnote, sem::Footnote>::write(::orgproto::Footnote* out, sem::Footnote const& in) {
  proto_serde<::orgproto::Footnote, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, sem::SemId>::write(out->mutable_definition(), *in.definition);
  }
}

void proto_serde<::orgproto::Footnote, sem::Footnote>::read(sem::ContextStore* context, ::orgproto::Footnote const& out, sem::Footnote& in) {
  proto_serde<::orgproto::Footnote, sem::Org>::read(context, out, in);
  proto_serde<std::string, Str>::read(context, out.tag(), in.tag);
  if (out.has_definition()) {
    proto_init<Opt<sem::SemId>>::init_default(context, in.definition);
    proto_serde<orgproto::AnyNode, sem::SemId>::read(context, out.definition(), *in.definition);
  }
}

void proto_serde<::orgproto::Completion, sem::Completion>::write(::orgproto::Completion* out, sem::Completion const& in) {
  proto_serde<::orgproto::Completion, sem::Org>::write(out, in);
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::Completion, sem::Completion>::read(sem::ContextStore* context, ::orgproto::Completion const& out, sem::Completion& in) {
  proto_serde<::orgproto::Completion, sem::Org>::read(context, out, in);
  in.done = out.done();
  in.full = out.full();
  in.isPercent = out.ispercent();
}

void proto_serde<::orgproto::Paragraph, sem::Paragraph>::write(::orgproto::Paragraph* out, sem::Paragraph const& in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Paragraph, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Paragraph, sem::Paragraph>::read(sem::ContextStore* context, ::orgproto::Paragraph const& out, sem::Paragraph& in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::read(context, out, in);
  proto_serde<::orgproto::Paragraph, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Center, sem::Center>::write(::orgproto::Center* out, sem::Center const& in) {
  proto_serde<::orgproto::Center, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Center, sem::Center>::read(sem::ContextStore* context, ::orgproto::Center const& out, sem::Center& in) {
  proto_serde<::orgproto::Center, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Caption, sem::Caption>::write(::orgproto::Caption* out, sem::Caption const& in) {
  proto_serde<::orgproto::Caption, sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_text(), *((in.text).get()));
  }
}

void proto_serde<::orgproto::Caption, sem::Caption>::read(sem::ContextStore* context, ::orgproto::Caption const& out, sem::Caption& in) {
  proto_serde<::orgproto::Caption, sem::Org>::read(context, out, in);
  proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.text(), in.text);
}

void proto_serde<::orgproto::CommandGroup, sem::CommandGroup>::write(::orgproto::CommandGroup* out, sem::CommandGroup const& in) {
  proto_serde<::orgproto::CommandGroup, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CommandGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CommandGroup, sem::CommandGroup>::read(sem::ContextStore* context, ::orgproto::CommandGroup const& out, sem::CommandGroup& in) {
  proto_serde<::orgproto::CommandGroup, sem::Stmt>::read(context, out, in);
  proto_serde<::orgproto::CommandGroup, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Quote, sem::Quote>::write(::orgproto::Quote* out, sem::Quote const& in) {
  proto_serde<::orgproto::Quote, sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_text(), *((in.text).get()));
  }
}

void proto_serde<::orgproto::Quote, sem::Quote>::read(sem::ContextStore* context, ::orgproto::Quote const& out, sem::Quote& in) {
  proto_serde<::orgproto::Quote, sem::Org>::read(context, out, in);
  proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.text(), in.text);
}

void proto_serde<::orgproto::Example, sem::Example>::write(::orgproto::Example* out, sem::Example const& in) {
  proto_serde<::orgproto::Example, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Example, sem::Example>::read(sem::ContextStore* context, ::orgproto::Example const& out, sem::Example& in) {
  proto_serde<::orgproto::Example, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::write(::orgproto::CmdArguments* out, sem::CmdArguments const& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemIdT<sem::CmdArgument>>>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgument>, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::read(sem::ContextStore* context, ::orgproto::CmdArguments const& out, sem::CmdArguments& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::read(context, out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemIdT<sem::CmdArgument>>>::read(context, out.positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgument>, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>>>::read(context, out.named(), in.named);
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::write(::orgproto::CmdArgument* out, sem::CmdArgument const& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::write(out, in);
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::read(sem::ContextStore* context, ::orgproto::CmdArgument const& out, sem::CmdArgument& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::read(context, out, in);
  if (out.has_key()) {
    proto_init<Opt<Str>>::init_default(context, in.key);
    proto_serde<std::string, Str>::read(context, out.key(), *in.key);
  }
  proto_serde<std::string, Str>::read(context, out.value(), in.value);
}

void proto_serde<::orgproto::Export, sem::Export>::write(::orgproto::Export* out, sem::Export const& in) {
  proto_serde<::orgproto::Export, sem::Org>::write(out, in);
  out->set_format(static_cast<orgproto::Export_Format>(in.format));
  proto_serde<std::string, Str>::write(out->mutable_exporter(), in.exporter);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::CmdArguments>::write(out->mutable_parameters(), *((in.parameters).get()));
  }
  if (in.placement) {
    proto_serde<std::string, Str>::write(out->mutable_placement(), *in.placement);
  }
  proto_serde<std::string, Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::Export, sem::Export>::read(sem::ContextStore* context, ::orgproto::Export const& out, sem::Export& in) {
  proto_serde<::orgproto::Export, sem::Org>::read(context, out, in);
  in.format = static_cast<sem::Export::Format>(out.format());
  proto_serde<std::string, Str>::read(context, out.exporter(), in.exporter);
  proto_serde<orgproto::CmdArguments, sem::SemIdT<sem::CmdArguments>>::read(context, out.parameters(), in.parameters);
  if (out.has_placement()) {
    proto_init<Opt<Str>>::init_default(context, in.placement);
    proto_serde<std::string, Str>::read(context, out.placement(), *in.placement);
  }
  proto_serde<std::string, Str>::read(context, out.content(), in.content);
}

void proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock>::write(::orgproto::AdmonitionBlock* out, sem::AdmonitionBlock const& in) {
  proto_serde<::orgproto::AdmonitionBlock, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock>::read(sem::ContextStore* context, ::orgproto::AdmonitionBlock const& out, sem::AdmonitionBlock& in) {
  proto_serde<::orgproto::AdmonitionBlock, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::write(::orgproto::Code::Switch::LineStart* out, sem::Code::Switch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::read(sem::ContextStore* context, ::orgproto::Code::Switch::LineStart const& out, sem::Code::Switch::LineStart& in) {
  in.start = out.start();
  in.extendLast = out.extendlast();
}

void proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::write(::orgproto::Code::Switch::CalloutFormat* out, sem::Code::Switch::CalloutFormat const& in) {
  proto_serde<std::string, Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::read(sem::ContextStore* context, ::orgproto::Code::Switch::CalloutFormat const& out, sem::Code::Switch::CalloutFormat& in) {
  proto_serde<std::string, Str>::read(context, out.format(), in.format);
}

void proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::write(::orgproto::Code::Switch::RemoveCallout* out, sem::Code::Switch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::read(sem::ContextStore* context, ::orgproto::Code::Switch::RemoveCallout const& out, sem::Code::Switch::RemoveCallout& in) {
  in.remove = out.remove();
}

void proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::write(::orgproto::Code::Switch::EmphasizeLine* out, sem::Code::Switch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::read(sem::ContextStore* context, ::orgproto::Code::Switch::EmphasizeLine const& out, sem::Code::Switch::EmphasizeLine& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::read(context, out.line(), in.line);
}

void proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::write(::orgproto::Code::Switch::Dedent* out, sem::Code::Switch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::read(sem::ContextStore* context, ::orgproto::Code::Switch::Dedent const& out, sem::Code::Switch::Dedent& in) {
  in.value = out.value();
}

void proto_serde<::orgproto::Code::Switch, sem::Code::Switch>::write(::orgproto::Code::Switch* out, sem::Code::Switch const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data));
      break;
    case 3:
      proto_serde<orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Code::Switch, sem::Code::Switch>::read(sem::ContextStore* context, ::orgproto::Code::Switch const& out, sem::Code::Switch& in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Code::Switch::Data::kLinestart:
      in.data = variant_from_index<decltype(in.data)>(0);
      proto_serde<orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::read(context, out.data().linestart(), std::get<0>(in.data));
      break;
    case ::orgproto::Code::Switch::Data::kCalloutformat:
      in.data = variant_from_index<decltype(in.data)>(1);
      proto_serde<orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::read(context, out.data().calloutformat(), std::get<1>(in.data));
      break;
    case ::orgproto::Code::Switch::Data::kRemovecallout:
      in.data = variant_from_index<decltype(in.data)>(2);
      proto_serde<orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::read(context, out.data().removecallout(), std::get<2>(in.data));
      break;
    case ::orgproto::Code::Switch::Data::kEmphasizeline:
      in.data = variant_from_index<decltype(in.data)>(3);
      proto_serde<orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::read(context, out.data().emphasizeline(), std::get<3>(in.data));
      break;
    case ::orgproto::Code::Switch::Data::kDedent:
      in.data = variant_from_index<decltype(in.data)>(4);
      proto_serde<orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::read(context, out.data().dedent(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Code, sem::Code>::write(::orgproto::Code* out, sem::Code const& in) {
  proto_serde<::orgproto::Code, sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Switch>, Vec<sem::Code::Switch>>::write(out->mutable_switches(), in.switches);
  out->set_exports(static_cast<orgproto::Code_Exports>(in.exports));
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::CmdArguments>::write(out->mutable_parameters(), *((in.parameters).get()));
  }
  out->set_cache(in.cache);
  out->set_eval(in.eval);
  out->set_noweb(in.noweb);
  out->set_hlines(in.hlines);
  out->set_tangle(in.tangle);
}

void proto_serde<::orgproto::Code, sem::Code>::read(sem::ContextStore* context, ::orgproto::Code const& out, sem::Code& in) {
  proto_serde<::orgproto::Code, sem::Org>::read(context, out, in);
  if (out.has_lang()) {
    proto_init<Opt<Str>>::init_default(context, in.lang);
    proto_serde<std::string, Str>::read(context, out.lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Switch>, Vec<sem::Code::Switch>>::read(context, out.switches(), in.switches);
  in.exports = static_cast<sem::Code::Exports>(out.exports());
  proto_serde<orgproto::CmdArguments, sem::SemIdT<sem::CmdArguments>>::read(context, out.parameters(), in.parameters);
  in.cache = out.cache();
  in.eval = out.eval();
  in.noweb = out.noweb();
  in.hlines = out.hlines();
  in.tangle = out.tangle();
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in) {
  out->set_mode(static_cast<orgproto::Time_Repeat_Mode>(in.mode));
  out->set_period(static_cast<orgproto::Time_Repeat_Period>(in.period));
  out->set_count(in.count);
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::read(sem::ContextStore* context, ::orgproto::Time::Repeat const& out, sem::Time::Repeat& in) {
  in.mode = static_cast<sem::Time::Repeat::Mode>(out.mode());
  in.period = static_cast<sem::Time::Repeat::Period>(out.period());
  in.count = out.count();
}

void proto_serde<::orgproto::Time::Static, sem::Time::Static>::write(::orgproto::Time::Static* out, sem::Time::Static const& in) {
  if (in.repeat) {
    proto_serde<orgproto::Time::Repeat, sem::Time::Repeat>::write(out->mutable_repeat(), *in.repeat);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::Time::Static, sem::Time::Static>::read(sem::ContextStore* context, ::orgproto::Time::Static const& out, sem::Time::Static& in) {
  if (out.has_repeat()) {
    proto_init<Opt<sem::Time::Repeat>>::init_default(context, in.repeat);
    proto_serde<orgproto::Time::Repeat, sem::Time::Repeat>::read(context, out.repeat(), *in.repeat);
  }
  proto_serde<orgproto::UserTime, UserTime>::read(context, out.time(), in.time);
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in) {
  proto_serde<std::string, Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::read(sem::ContextStore* context, ::orgproto::Time::Dynamic const& out, sem::Time::Dynamic& in) {
  proto_serde<std::string, Str>::read(context, out.expr(), in.expr);
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

void proto_serde<::orgproto::Time, sem::Time>::read(sem::ContextStore* context, ::orgproto::Time const& out, sem::Time& in) {
  proto_serde<::orgproto::Time, sem::Org>::read(context, out, in);
  in.isActive = out.isactive();
  switch (out.time().kind_case()) {
    case ::orgproto::Time::TimeVariant::kStatic:
      in.time = variant_from_index<decltype(in.time)>(0);
      proto_serde<orgproto::Time::Static, sem::Time::Static>::read(context, out.time().static_(), std::get<0>(in.time));
      break;
    case ::orgproto::Time::TimeVariant::kDynamic:
      in.time = variant_from_index<decltype(in.time)>(1);
      proto_serde<orgproto::Time::Dynamic, sem::Time::Dynamic>::read(context, out.time().dynamic(), std::get<1>(in.time));
      break;
  }
}

void proto_serde<::orgproto::TimeRange, sem::TimeRange>::write(::orgproto::TimeRange* out, sem::TimeRange const& in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::write(out, in);
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_from(), *((in.from).get()));
  }
  if (!in.to.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_to(), *((in.to).get()));
  }
}

void proto_serde<::orgproto::TimeRange, sem::TimeRange>::read(sem::ContextStore* context, ::orgproto::TimeRange const& out, sem::TimeRange& in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::read(context, out, in);
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.from(), in.from);
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.to(), in.to);
}

void proto_serde<::orgproto::Macro, sem::Macro>::write(::orgproto::Macro* out, sem::Macro const& in) {
  proto_serde<::orgproto::Macro, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_arguments(), in.arguments);
}

void proto_serde<::orgproto::Macro, sem::Macro>::read(sem::ContextStore* context, ::orgproto::Macro const& out, sem::Macro& in) {
  proto_serde<::orgproto::Macro, sem::Org>::read(context, out, in);
  proto_serde<std::string, Str>::read(context, out.name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(context, out.arguments(), in.arguments);
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::read(sem::ContextStore* context, ::orgproto::Symbol::Param const& out, sem::Symbol::Param& in) {
  if (out.has_key()) {
    proto_init<Opt<Str>>::init_default(context, in.key);
    proto_serde<std::string, Str>::read(context, out.key(), *in.key);
  }
  proto_serde<std::string, Str>::read(context, out.value(), in.value);
}

void proto_serde<::orgproto::Symbol, sem::Symbol>::write(::orgproto::Symbol* out, sem::Symbol const& in) {
  proto_serde<::orgproto::Symbol, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::Symbol, sem::Symbol>::read(sem::ContextStore* context, ::orgproto::Symbol const& out, sem::Symbol& in) {
  proto_serde<::orgproto::Symbol, sem::Org>::read(context, out, in);
  proto_serde<std::string, Str>::read(context, out.name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::read(context, out.parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId>>::read(context, out.positional(), in.positional);
}

void proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in) {
  if (in.desc) {
    proto_serde<orgproto::StmtList, sem::StmtList>::write(out->mutable_desc(), *((*in.desc).get()));
  }
}

void proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::DescribedLog const& out, sem::SubtreeLog::DescribedLog& in) {
  if (out.has_desc()) {
    proto_init<Opt<sem::SemIdT<sem::StmtList>>>::init_default(context, in.desc);
    proto_serde<orgproto::StmtList, sem::SemIdT<sem::StmtList>>::read(context, out.desc(), *in.desc);
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
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  }
}

void proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::Priority const& out, sem::SubtreeLog::Priority& in) {
  proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  if (out.has_oldpriority()) {
    proto_init<Opt<std::string>>::init_default(context, in.oldPriority);
    *in.oldPriority = out.oldpriority();
  }
  if (out.has_newpriority()) {
    proto_init<Opt<std::string>>::init_default(context, in.newPriority);
    *in.newPriority = out.newpriority();
  }
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.on(), in.on);
}

void proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in) {
  proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  }
}

void proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::Note const& out, sem::SubtreeLog::Note& in) {
  proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.on(), in.on);
}

void proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in) {
  proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  }
  if (!in.from.isNil()) {
    proto_serde<orgproto::Link, sem::Link>::write(out->mutable_from(), *((in.from).get()));
  }
}

void proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::Refile const& out, sem::SubtreeLog::Refile& in) {
  proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.on(), in.on);
  proto_serde<orgproto::Link, sem::SemIdT<sem::Link>>::read(context, out.from(), in.from);
}

void proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in) {
  proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::write(out, in);
  switch (in.range.index()) {
    case 0:
      if (!std::get<0>(in.range).isNil()) {
        proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((std::get<0>(in.range)).get()));
      }
      break;
    case 1:
      if (!std::get<1>(in.range).isNil()) {
        proto_serde<orgproto::TimeRange, sem::TimeRange>::write(out->mutable_timerange(), *((std::get<1>(in.range)).get()));
      }
      break;
  }
}

void proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::Clock const& out, sem::SubtreeLog::Clock& in) {
  proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  switch (out.range_kind_case()) {
    case ::orgproto::SubtreeLog::Clock::kTime:
      in.range = variant_from_index<decltype(in.range)>(0);
      proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.time(), std::get<0>(in.range));
      break;
    case ::orgproto::SubtreeLog::Clock::kTimerange:
      in.range = variant_from_index<decltype(in.range)>(1);
      proto_serde<orgproto::TimeRange, sem::SemIdT<sem::TimeRange>>::read(context, out.timerange(), std::get<1>(in.range));
      break;
  }
}

void proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State>::write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in) {
  proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::write(out, in);
  out->set_from(static_cast<orgproto::OrgBigIdentKind>(in.from));
  out->set_to(static_cast<orgproto::OrgBigIdentKind>(in.to));
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  }
}

void proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::State const& out, sem::SubtreeLog::State& in) {
  proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  in.from = static_cast<OrgBigIdentKind>(out.from());
  in.to = static_cast<OrgBigIdentKind>(out.to());
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.on(), in.on);
}

void proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in) {
  proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::write(out, in);
  if (!in.on.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  }
  if (!in.tag.isNil()) {
    proto_serde<orgproto::HashTag, sem::HashTag>::write(out->mutable_tag(), *((in.tag).get()));
  }
  out->set_added(in.added);
}

void proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(sem::ContextStore* context, ::orgproto::SubtreeLog::Tag const& out, sem::SubtreeLog::Tag& in) {
  proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::read(context, out, in);
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.on(), in.on);
  proto_serde<orgproto::HashTag, sem::SemIdT<sem::HashTag>>::read(context, out.tag(), in.tag);
  in.added = out.added();
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
  }
}

void proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog>::read(sem::ContextStore* context, ::orgproto::SubtreeLog const& out, sem::SubtreeLog& in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::read(context, out, in);
  switch (out.log().kind_case()) {
    case ::orgproto::SubtreeLog::LogEntry::kPriority:
      in.log = variant_from_index<decltype(in.log)>(0);
      proto_serde<orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::read(context, out.log().priority(), std::get<0>(in.log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kNote:
      in.log = variant_from_index<decltype(in.log)>(1);
      proto_serde<orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::read(context, out.log().note(), std::get<1>(in.log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kRefile:
      in.log = variant_from_index<decltype(in.log)>(2);
      proto_serde<orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::read(context, out.log().refile(), std::get<2>(in.log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kClock:
      in.log = variant_from_index<decltype(in.log)>(3);
      proto_serde<orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::read(context, out.log().clock(), std::get<3>(in.log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kState:
      in.log = variant_from_index<decltype(in.log)>(4);
      proto_serde<orgproto::SubtreeLog::State, sem::SubtreeLog::State>::read(context, out.log().state(), std::get<4>(in.log));
      break;
    case ::orgproto::SubtreeLog::LogEntry::kTag:
      in.log = variant_from_index<decltype(in.log)>(5);
      proto_serde<orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::read(context, out.log().tag(), std::get<5>(in.log));
      break;
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in) {
  out->set_kind(static_cast<orgproto::Subtree_Period_Kind>(in.kind));
  switch (in.period.index()) {
    case 0:
      if (!std::get<0>(in.period).isNil()) {
        proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((std::get<0>(in.period)).get()));
      }
      break;
    case 1:
      if (!std::get<1>(in.period).isNil()) {
        proto_serde<orgproto::TimeRange, sem::TimeRange>::write(out->mutable_timerange(), *((std::get<1>(in.period)).get()));
      }
      break;
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::read(sem::ContextStore* context, ::orgproto::Subtree::Period const& out, sem::Subtree::Period& in) {
  in.kind = static_cast<sem::Subtree::Period::Kind>(out.kind());
  switch (out.period_kind_case()) {
    case ::orgproto::Subtree::Period::kTime:
      in.period = variant_from_index<decltype(in.period)>(0);
      proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.time(), std::get<0>(in.period));
      break;
    case ::orgproto::Subtree::Period::kTimerange:
      in.period = variant_from_index<decltype(in.period)>(1);
      proto_serde<orgproto::TimeRange, sem::SemIdT<sem::TimeRange>>::read(context, out.timerange(), std::get<1>(in.period));
      break;
  }
}

void proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Nonblocking const& out, sem::Subtree::Property::Nonblocking& in) {
  in.isBlocking = out.isblocking();
}

void proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Trigger const& out, sem::Subtree::Property::Trigger& in) {

}

void proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Origin const& out, sem::Subtree::Property::Origin& in) {
  proto_serde<std::string, Str>::read(context, out.text(), in.text);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in) {
  proto_serde<std::string, Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexClass const& out, sem::Subtree::Property::ExportLatexClass& in) {
  proto_serde<std::string, Str>::read(context, out.latexclass(), in.latexClass);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexClassOptions const& out, sem::Subtree::Property::ExportLatexClassOptions& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(context, out.options(), in.options);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in) {
  proto_serde<std::string, Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexHeader const& out, sem::Subtree::Property::ExportLatexHeader& in) {
  proto_serde<std::string, Str>::read(context, out.header(), in.header);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in) {
  proto_serde<std::string, Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexCompiler const& out, sem::Subtree::Property::ExportLatexCompiler& in) {
  proto_serde<std::string, Str>::read(context, out.compiler(), in.compiler);
}

void proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Ordered const& out, sem::Subtree::Property::Ordered& in) {
  in.isOrdered = out.isordered();
}

void proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Effort const& out, sem::Subtree::Property::Effort& in) {
  in.hours = out.hours();
  in.minutes = out.minutes();
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in) {
  out->set_level(static_cast<orgproto::Subtree_Property_Visibility_Level>(in.level));
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Visibility const& out, sem::Subtree::Property::Visibility& in) {
  in.level = static_cast<sem::Subtree::Property::Visibility::Level>(out.level());
}

void proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in) {
  proto_serde<std::string, Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportOptions const& out, sem::Subtree::Property::ExportOptions& in) {
  proto_serde<std::string, Str>::read(context, out.backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::read(context, out.values(), in.values);
}

void proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Blocker const& out, sem::Subtree::Property::Blocker& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(context, out.blockers(), in.blockers);
}

void proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Unnumbered const& out, sem::Subtree::Property::Unnumbered& in) {

}

void proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in) {
  if (!in.time.isNil()) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((in.time).get()));
  }
}

void proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::read(sem::ContextStore* context, ::orgproto::Subtree::Property::Created const& out, sem::Subtree::Property::Created& in) {
  proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.time(), in.time);
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in) {
  out->set_mainsetrule(static_cast<orgproto::Subtree_Property_SetMode>(in.mainSetRule));
  out->set_subsetrule(static_cast<orgproto::Subtree_Property_SetMode>(in.subSetRule));
  out->set_inheritancemode(static_cast<orgproto::Subtree_Property_InheritanceMode>(in.inheritanceMode));
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
  }
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::read(sem::ContextStore* context, ::orgproto::Subtree::Property const& out, sem::Subtree::Property& in) {
  in.mainSetRule = static_cast<sem::Subtree::Property::SetMode>(out.mainsetrule());
  in.subSetRule = static_cast<sem::Subtree::Property::SetMode>(out.subsetrule());
  in.inheritanceMode = static_cast<sem::Subtree::Property::InheritanceMode>(out.inheritancemode());
  switch (out.data().kind_case()) {
    case ::orgproto::Subtree::Property::Data::kNonblocking:
      in.data = variant_from_index<decltype(in.data)>(0);
      proto_serde<orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::read(context, out.data().nonblocking(), std::get<0>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kTrigger:
      in.data = variant_from_index<decltype(in.data)>(1);
      proto_serde<orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::read(context, out.data().trigger(), std::get<1>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kOrigin:
      in.data = variant_from_index<decltype(in.data)>(2);
      proto_serde<orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::read(context, out.data().origin(), std::get<2>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexclass:
      in.data = variant_from_index<decltype(in.data)>(3);
      proto_serde<orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::read(context, out.data().exportlatexclass(), std::get<3>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexclassoptions:
      in.data = variant_from_index<decltype(in.data)>(4);
      proto_serde<orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::read(context, out.data().exportlatexclassoptions(), std::get<4>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexheader:
      in.data = variant_from_index<decltype(in.data)>(5);
      proto_serde<orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::read(context, out.data().exportlatexheader(), std::get<5>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportlatexcompiler:
      in.data = variant_from_index<decltype(in.data)>(6);
      proto_serde<orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::read(context, out.data().exportlatexcompiler(), std::get<6>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kOrdered:
      in.data = variant_from_index<decltype(in.data)>(7);
      proto_serde<orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::read(context, out.data().ordered(), std::get<7>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kEffort:
      in.data = variant_from_index<decltype(in.data)>(8);
      proto_serde<orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::read(context, out.data().effort(), std::get<8>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kVisibility:
      in.data = variant_from_index<decltype(in.data)>(9);
      proto_serde<orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(context, out.data().visibility(), std::get<9>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kExportoptions:
      in.data = variant_from_index<decltype(in.data)>(10);
      proto_serde<orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::read(context, out.data().exportoptions(), std::get<10>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kBlocker:
      in.data = variant_from_index<decltype(in.data)>(11);
      proto_serde<orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::read(context, out.data().blocker(), std::get<11>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kUnnumbered:
      in.data = variant_from_index<decltype(in.data)>(12);
      proto_serde<orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::read(context, out.data().unnumbered(), std::get<12>(in.data));
      break;
    case ::orgproto::Subtree::Property::Data::kCreated:
      in.data = variant_from_index<decltype(in.data)>(13);
      proto_serde<orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::read(context, out.data().created(), std::get<13>(in.data));
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
    proto_serde<orgproto::Completion, sem::Completion>::write(out->mutable_completion(), *((*in.completion).get()));
  }
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_description(), *((*in.description).get()));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemIdT<sem::HashTag>>>::write(out->mutable_tags(), in.tags);
  if (!in.title.isNil()) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_title(), *((in.title).get()));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, Vec<sem::SemIdT<sem::SubtreeLog>>>::write(out->mutable_logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::write(out->mutable_properties(), in.properties);
  if (in.closed) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_closed(), *((*in.closed).get()));
  }
  if (in.deadline) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_deadline(), *((*in.deadline).get()));
  }
  if (in.scheduled) {
    proto_serde<orgproto::Time, sem::Time>::write(out->mutable_scheduled(), *((*in.scheduled).get()));
  }
}

void proto_serde<::orgproto::Subtree, sem::Subtree>::read(sem::ContextStore* context, ::orgproto::Subtree const& out, sem::Subtree& in) {
  proto_serde<::orgproto::Subtree, sem::Org>::read(context, out, in);
  in.level = out.level();
  if (out.has_treeid()) {
    proto_init<Opt<Str>>::init_default(context, in.treeId);
    proto_serde<std::string, Str>::read(context, out.treeid(), *in.treeId);
  }
  if (out.has_todo()) {
    proto_init<Opt<Str>>::init_default(context, in.todo);
    proto_serde<std::string, Str>::read(context, out.todo(), *in.todo);
  }
  if (out.has_completion()) {
    proto_init<Opt<sem::SemIdT<sem::Completion>>>::init_default(context, in.completion);
    proto_serde<orgproto::Completion, sem::SemIdT<sem::Completion>>::read(context, out.completion(), *in.completion);
  }
  if (out.has_description()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.description);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.description(), *in.description);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemIdT<sem::HashTag>>>::read(context, out.tags(), in.tags);
  proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.title(), in.title);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::SubtreeLog>, Vec<sem::SemIdT<sem::SubtreeLog>>>::read(context, out.logbook(), in.logbook);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(context, out.properties(), in.properties);
  if (out.has_closed()) {
    proto_init<Opt<sem::SemIdT<sem::Time>>>::init_default(context, in.closed);
    proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.closed(), *in.closed);
  }
  if (out.has_deadline()) {
    proto_init<Opt<sem::SemIdT<sem::Time>>>::init_default(context, in.deadline);
    proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.deadline(), *in.deadline);
  }
  if (out.has_scheduled()) {
    proto_init<Opt<sem::SemIdT<sem::Time>>>::init_default(context, in.scheduled);
    proto_serde<orgproto::Time, sem::SemIdT<sem::Time>>::read(context, out.scheduled(), *in.scheduled);
  }
}

void proto_serde<::orgproto::InlineMath, sem::InlineMath>::write(::orgproto::InlineMath* out, sem::InlineMath const& in) {
  proto_serde<::orgproto::InlineMath, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::InlineMath, sem::InlineMath>::read(sem::ContextStore* context, ::orgproto::InlineMath const& out, sem::InlineMath& in) {
  proto_serde<::orgproto::InlineMath, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Escaped, sem::Escaped>::write(::orgproto::Escaped* out, sem::Escaped const& in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Escaped, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Escaped, sem::Escaped>::read(sem::ContextStore* context, ::orgproto::Escaped const& out, sem::Escaped& in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Escaped, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Newline, sem::Newline>::write(::orgproto::Newline* out, sem::Newline const& in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Newline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Newline, sem::Newline>::read(sem::ContextStore* context, ::orgproto::Newline const& out, sem::Newline& in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Newline, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Space, sem::Space>::write(::orgproto::Space* out, sem::Space const& in) {
  proto_serde<::orgproto::Space, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Space, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Space, sem::Space>::read(sem::ContextStore* context, ::orgproto::Space const& out, sem::Space& in) {
  proto_serde<::orgproto::Space, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Space, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Word, sem::Word>::write(::orgproto::Word* out, sem::Word const& in) {
  proto_serde<::orgproto::Word, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Word, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Word, sem::Word>::read(sem::ContextStore* context, ::orgproto::Word const& out, sem::Word& in) {
  proto_serde<::orgproto::Word, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Word, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::AtMention, sem::AtMention>::write(::orgproto::AtMention* out, sem::AtMention const& in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::AtMention, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AtMention, sem::AtMention>::read(sem::ContextStore* context, ::orgproto::AtMention const& out, sem::AtMention& in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::AtMention, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::RawText, sem::RawText>::write(::orgproto::RawText* out, sem::RawText const& in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RawText, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RawText, sem::RawText>::read(sem::ContextStore* context, ::orgproto::RawText const& out, sem::RawText& in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::RawText, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Punctuation, sem::Punctuation>::write(::orgproto::Punctuation* out, sem::Punctuation const& in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Punctuation, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Punctuation, sem::Punctuation>::read(sem::ContextStore* context, ::orgproto::Punctuation const& out, sem::Punctuation& in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Punctuation, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Placeholder, sem::Placeholder>::write(::orgproto::Placeholder* out, sem::Placeholder const& in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Placeholder, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Placeholder, sem::Placeholder>::read(sem::ContextStore* context, ::orgproto::Placeholder const& out, sem::Placeholder& in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::Placeholder, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::BigIdent, sem::BigIdent>::write(::orgproto::BigIdent* out, sem::BigIdent const& in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::BigIdent, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BigIdent, sem::BigIdent>::read(sem::ContextStore* context, ::orgproto::BigIdent const& out, sem::BigIdent& in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::read(context, out, in);
  proto_serde<::orgproto::BigIdent, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Bold, sem::Bold>::write(::orgproto::Bold* out, sem::Bold const& in) {
  proto_serde<::orgproto::Bold, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Bold, sem::Bold>::read(sem::ContextStore* context, ::orgproto::Bold const& out, sem::Bold& in) {
  proto_serde<::orgproto::Bold, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Underline, sem::Underline>::write(::orgproto::Underline* out, sem::Underline const& in) {
  proto_serde<::orgproto::Underline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Underline, sem::Underline>::read(sem::ContextStore* context, ::orgproto::Underline const& out, sem::Underline& in) {
  proto_serde<::orgproto::Underline, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Monospace, sem::Monospace>::write(::orgproto::Monospace* out, sem::Monospace const& in) {
  proto_serde<::orgproto::Monospace, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Monospace, sem::Monospace>::read(sem::ContextStore* context, ::orgproto::Monospace const& out, sem::Monospace& in) {
  proto_serde<::orgproto::Monospace, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::MarkQuote, sem::MarkQuote>::write(::orgproto::MarkQuote* out, sem::MarkQuote const& in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::MarkQuote, sem::MarkQuote>::read(sem::ContextStore* context, ::orgproto::MarkQuote const& out, sem::MarkQuote& in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Verbatim, sem::Verbatim>::write(::orgproto::Verbatim* out, sem::Verbatim const& in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Verbatim, sem::Verbatim>::read(sem::ContextStore* context, ::orgproto::Verbatim const& out, sem::Verbatim& in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Italic, sem::Italic>::write(::orgproto::Italic* out, sem::Italic const& in) {
  proto_serde<::orgproto::Italic, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Italic, sem::Italic>::read(sem::ContextStore* context, ::orgproto::Italic const& out, sem::Italic& in) {
  proto_serde<::orgproto::Italic, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Strike, sem::Strike>::write(::orgproto::Strike* out, sem::Strike const& in) {
  proto_serde<::orgproto::Strike, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Strike, sem::Strike>::read(sem::ContextStore* context, ::orgproto::Strike const& out, sem::Strike& in) {
  proto_serde<::orgproto::Strike, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Par, sem::Par>::write(::orgproto::Par* out, sem::Par const& in) {
  proto_serde<::orgproto::Par, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Par, sem::Par>::read(sem::ContextStore* context, ::orgproto::Par const& out, sem::Par& in) {
  proto_serde<::orgproto::Par, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::List, sem::List>::write(::orgproto::List* out, sem::List const& in) {
  proto_serde<::orgproto::List, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::List, sem::List>::read(sem::ContextStore* context, ::orgproto::List const& out, sem::List& in) {
  proto_serde<::orgproto::List, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::write(::orgproto::ListItem* out, sem::ListItem const& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::write(out, in);
  out->set_checkbox(static_cast<orgproto::ListItem_Checkbox>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_header(), *((*in.header).get()));
  }
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::read(sem::ContextStore* context, ::orgproto::ListItem const& out, sem::ListItem& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::read(context, out, in);
  in.checkbox = static_cast<sem::ListItem::Checkbox>(out.checkbox());
  if (out.has_header()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.header);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.header(), *in.header);
  }
}

void proto_serde<::orgproto::Link::Raw, sem::Link::Raw>::write(::orgproto::Link::Raw* out, sem::Link::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Raw, sem::Link::Raw>::read(sem::ContextStore* context, ::orgproto::Link::Raw const& out, sem::Link::Raw& in) {
  proto_serde<std::string, Str>::read(context, out.text(), in.text);
}

void proto_serde<::orgproto::Link::Id, sem::Link::Id>::write(::orgproto::Link::Id* out, sem::Link::Id const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Id, sem::Link::Id>::read(sem::ContextStore* context, ::orgproto::Link::Id const& out, sem::Link::Id& in) {
  proto_serde<std::string, Str>::read(context, out.text(), in.text);
}

void proto_serde<::orgproto::Link::Person, sem::Link::Person>::write(::orgproto::Link::Person* out, sem::Link::Person const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Link::Person, sem::Link::Person>::read(sem::ContextStore* context, ::orgproto::Link::Person const& out, sem::Link::Person& in) {
  proto_serde<std::string, Str>::read(context, out.name(), in.name);
}

void proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote>::write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote>::read(sem::ContextStore* context, ::orgproto::Link::Footnote const& out, sem::Link::Footnote& in) {
  proto_serde<std::string, Str>::read(context, out.target(), in.target);
}

void proto_serde<::orgproto::Link::File, sem::Link::File>::write(::orgproto::Link::File* out, sem::Link::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::Link::File, sem::Link::File>::read(sem::ContextStore* context, ::orgproto::Link::File const& out, sem::Link::File& in) {
  proto_serde<std::string, Str>::read(context, out.file(), in.file);
}

void proto_serde<::orgproto::Link, sem::Link>::write(::orgproto::Link* out, sem::Link const& in) {
  proto_serde<::orgproto::Link, sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_description(), *((*in.description).get()));
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
      proto_serde<orgproto::Link::Footnote, sem::Link::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<3>(in.data));
      break;
    case 4:
      proto_serde<orgproto::Link::File, sem::Link::File>::write(out->mutable_data()->mutable_file(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Link, sem::Link>::read(sem::ContextStore* context, ::orgproto::Link const& out, sem::Link& in) {
  proto_serde<::orgproto::Link, sem::Org>::read(context, out, in);
  if (out.has_description()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.description);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.description(), *in.description);
  }
  switch (out.data().kind_case()) {
    case ::orgproto::Link::Data::kRaw:
      in.data = variant_from_index<decltype(in.data)>(0);
      proto_serde<orgproto::Link::Raw, sem::Link::Raw>::read(context, out.data().raw(), std::get<0>(in.data));
      break;
    case ::orgproto::Link::Data::kId:
      in.data = variant_from_index<decltype(in.data)>(1);
      proto_serde<orgproto::Link::Id, sem::Link::Id>::read(context, out.data().id(), std::get<1>(in.data));
      break;
    case ::orgproto::Link::Data::kPerson:
      in.data = variant_from_index<decltype(in.data)>(2);
      proto_serde<orgproto::Link::Person, sem::Link::Person>::read(context, out.data().person(), std::get<2>(in.data));
      break;
    case ::orgproto::Link::Data::kFootnote:
      in.data = variant_from_index<decltype(in.data)>(3);
      proto_serde<orgproto::Link::Footnote, sem::Link::Footnote>::read(context, out.data().footnote(), std::get<3>(in.data));
      break;
    case ::orgproto::Link::Data::kFile:
      in.data = variant_from_index<decltype(in.data)>(4);
      proto_serde<orgproto::Link::File, sem::Link::File>::read(context, out.data().file(), std::get<4>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Document, sem::Document>::write(::orgproto::Document* out, sem::Document const& in) {
  proto_serde<::orgproto::Document, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::write(out->mutable_idtable(), in.idTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::write(out->mutable_nametable(), in.nameTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::write(out->mutable_footnotetable(), in.footnoteTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::write(out->mutable_anchortable(), in.anchorTable);
  if (in.title) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_title(), *((*in.title).get()));
  }
  if (in.author) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_author(), *((*in.author).get()));
  }
  if (in.creator) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_creator(), *((*in.creator).get()));
  }
  if (in.email) {
    proto_serde<orgproto::RawText, sem::RawText>::write(out->mutable_email(), *((*in.email).get()));
  }
  if (in.language) {
    proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_language(), *in.language);
  }
  if (!in.options.isNil()) {
    proto_serde<orgproto::DocumentOptions, sem::DocumentOptions>::write(out->mutable_options(), *((in.options).get()));
  }
  if (in.exportFileName) {
    proto_serde<std::string, Str>::write(out->mutable_exportfilename(), *in.exportFileName);
  }
}

void proto_serde<::orgproto::Document, sem::Document>::read(sem::ContextStore* context, ::orgproto::Document const& out, sem::Document& in) {
  proto_serde<::orgproto::Document, sem::Org>::read(context, out, in);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::read(context, out.idtable(), in.idTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::read(context, out.nametable(), in.nameTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::read(context, out.footnotetable(), in.footnoteTable);
  proto_serde<::google::protobuf::Map<std::string, orgproto::AnyNode>, UnorderedMap<Str, sem::SemId>>::read(context, out.anchortable(), in.anchorTable);
  if (out.has_title()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.title);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.title(), *in.title);
  }
  if (out.has_author()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.author);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.author(), *in.author);
  }
  if (out.has_creator()) {
    proto_init<Opt<sem::SemIdT<sem::Paragraph>>>::init_default(context, in.creator);
    proto_serde<orgproto::Paragraph, sem::SemIdT<sem::Paragraph>>::read(context, out.creator(), *in.creator);
  }
  if (out.has_email()) {
    proto_init<Opt<sem::SemIdT<sem::RawText>>>::init_default(context, in.email);
    proto_serde<orgproto::RawText, sem::SemIdT<sem::RawText>>::read(context, out.email(), *in.email);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(context, out.language(), *in.language);
  proto_serde<orgproto::DocumentOptions, sem::SemIdT<sem::DocumentOptions>>::read(context, out.options(), in.options);
  if (out.has_exportfilename()) {
    proto_init<Opt<Str>>::init_default(context, in.exportFileName);
    proto_serde<std::string, Str>::read(context, out.exportfilename(), *in.exportFileName);
  }
}

void proto_serde<::orgproto::ParseError, sem::ParseError>::write(::orgproto::ParseError* out, sem::ParseError const& in) {
  proto_serde<::orgproto::ParseError, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ParseError, sem::ParseError>::read(sem::ContextStore* context, ::orgproto::ParseError const& out, sem::ParseError& in) {
  proto_serde<::orgproto::ParseError, sem::Org>::read(context, out, in);
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

void proto_serde<::orgproto::FileTarget, sem::FileTarget>::read(sem::ContextStore* context, ::orgproto::FileTarget const& out, sem::FileTarget& in) {
  proto_serde<::orgproto::FileTarget, sem::Org>::read(context, out, in);
  proto_serde<std::string, Str>::read(context, out.path(), in.path);
  if (out.has_line()) {
    proto_init<Opt<int>>::init_default(context, in.line);
    *in.line = out.line();
  }
  if (out.has_searchtarget()) {
    proto_init<Opt<Str>>::init_default(context, in.searchTarget);
    proto_serde<std::string, Str>::read(context, out.searchtarget(), *in.searchTarget);
  }
  in.restrictToHeadlines = out.restricttoheadlines();
  if (out.has_targetid()) {
    proto_init<Opt<Str>>::init_default(context, in.targetId);
    proto_serde<std::string, Str>::read(context, out.targetid(), *in.targetId);
  }
  if (out.has_regexp()) {
    proto_init<Opt<Str>>::init_default(context, in.regexp);
    proto_serde<std::string, Str>::read(context, out.regexp(), *in.regexp);
  }
}

void proto_serde<::orgproto::TextSeparator, sem::TextSeparator>::write(::orgproto::TextSeparator* out, sem::TextSeparator const& in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::TextSeparator, sem::TextSeparator>::read(sem::ContextStore* context, ::orgproto::TextSeparator const& out, sem::TextSeparator& in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::read(context, out, in);
}

void proto_serde<::orgproto::Include::Example, sem::Include::Example>::write(::orgproto::Include::Example* out, sem::Include::Example const& in) {

}

void proto_serde<::orgproto::Include::Example, sem::Include::Example>::read(sem::ContextStore* context, ::orgproto::Include::Example const& out, sem::Include::Example& in) {

}

void proto_serde<::orgproto::Include::Export, sem::Include::Export>::write(::orgproto::Include::Export* out, sem::Include::Export const& in) {

}

void proto_serde<::orgproto::Include::Export, sem::Include::Export>::read(sem::ContextStore* context, ::orgproto::Include::Export const& out, sem::Include::Export& in) {

}

void proto_serde<::orgproto::Include::Src, sem::Include::Src>::write(::orgproto::Include::Src* out, sem::Include::Src const& in) {

}

void proto_serde<::orgproto::Include::Src, sem::Include::Src>::read(sem::ContextStore* context, ::orgproto::Include::Src const& out, sem::Include::Src& in) {

}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in) {

}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::read(sem::ContextStore* context, ::orgproto::Include::OrgDocument const& out, sem::Include::OrgDocument& in) {

}

void proto_serde<::orgproto::Include, sem::Include>::write(::orgproto::Include* out, sem::Include const& in) {
  proto_serde<::orgproto::Include, sem::Org>::write(out, in);
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

void proto_serde<::orgproto::Include, sem::Include>::read(sem::ContextStore* context, ::orgproto::Include const& out, sem::Include& in) {
  proto_serde<::orgproto::Include, sem::Org>::read(context, out, in);
  switch (out.data().kind_case()) {
    case ::orgproto::Include::Data::kExample:
      in.data = variant_from_index<decltype(in.data)>(0);
      proto_serde<orgproto::Include::Example, sem::Include::Example>::read(context, out.data().example(), std::get<0>(in.data));
      break;
    case ::orgproto::Include::Data::kExport:
      in.data = variant_from_index<decltype(in.data)>(1);
      proto_serde<orgproto::Include::Export, sem::Include::Export>::read(context, out.data().export_(), std::get<1>(in.data));
      break;
    case ::orgproto::Include::Data::kSrc:
      in.data = variant_from_index<decltype(in.data)>(2);
      proto_serde<orgproto::Include::Src, sem::Include::Src>::read(context, out.data().src(), std::get<2>(in.data));
      break;
    case ::orgproto::Include::Data::kOrgdocument:
      in.data = variant_from_index<decltype(in.data)>(3);
      proto_serde<orgproto::Include::OrgDocument, sem::Include::OrgDocument>::read(context, out.data().orgdocument(), std::get<3>(in.data));
      break;
  }
}

void proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(::orgproto::DocumentOptions::DoExport* out, sem::DocumentOptions::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(sem::ContextStore* context, ::orgproto::DocumentOptions::DoExport const& out, sem::DocumentOptions::DoExport& in) {
  in.exportToc = out.exporttoc();
}

void proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(::orgproto::DocumentOptions::ExportFixed* out, sem::DocumentOptions::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(sem::ContextStore* context, ::orgproto::DocumentOptions::ExportFixed const& out, sem::DocumentOptions::ExportFixed& in) {
  in.exportLevels = out.exportlevels();
}

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::write(out, in);
  out->set_brokenlinks(static_cast<orgproto::DocumentOptions_BrokenLinks>(in.brokenLinks));
  out->set_initialvisibility(static_cast<orgproto::DocumentOptions_Visibility>(in.initialVisibility));
  switch (in.tocExport.index()) {
    case 0:
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(out->mutable_tocexport()->mutable_doexport(), std::get<0>(in.tocExport));
      break;
    case 1:
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(out->mutable_tocexport()->mutable_exportfixed(), std::get<1>(in.tocExport));
      break;
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::write(out->mutable_properties(), in.properties);
  out->set_smartquotes(in.smartQuotes);
  out->set_emphasizedtext(in.emphasizedText);
  out->set_specialstrings(in.specialStrings);
  out->set_fixedwidthsections(in.fixedWidthSections);
  out->set_includetimestamps(in.includeTimestamps);
  out->set_preservelinebreaks(in.preserveLineBreaks);
  out->set_plaintextsubscripts(in.plaintextSubscripts);
  out->set_exportarchived(in.exportArchived);
  out->set_exportwithauthor(in.exportWithAuthor);
  out->set_exportbrokenlinks(in.exportBrokenLinks);
  out->set_exportwithclock(in.exportWithClock);
  out->set_exportwithcreator(in.exportWithCreator);
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::read(sem::ContextStore* context, ::orgproto::DocumentOptions const& out, sem::DocumentOptions& in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::read(context, out, in);
  in.brokenLinks = static_cast<sem::DocumentOptions::BrokenLinks>(out.brokenlinks());
  in.initialVisibility = static_cast<sem::DocumentOptions::Visibility>(out.initialvisibility());
  switch (out.tocexport().kind_case()) {
    case ::orgproto::DocumentOptions::TocExport::kDoexport:
      in.tocExport = variant_from_index<decltype(in.tocExport)>(0);
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(context, out.tocexport().doexport(), std::get<0>(in.tocExport));
      break;
    case ::orgproto::DocumentOptions::TocExport::kExportfixed:
      in.tocExport = variant_from_index<decltype(in.tocExport)>(1);
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(context, out.tocexport().exportfixed(), std::get<1>(in.tocExport));
      break;
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(context, out.properties(), in.properties);
  in.smartQuotes = out.smartquotes();
  in.emphasizedText = out.emphasizedtext();
  in.specialStrings = out.specialstrings();
  in.fixedWidthSections = out.fixedwidthsections();
  in.includeTimestamps = out.includetimestamps();
  in.preserveLineBreaks = out.preservelinebreaks();
  in.plaintextSubscripts = out.plaintextsubscripts();
  in.exportArchived = out.exportarchived();
  in.exportWithAuthor = out.exportwithauthor();
  in.exportBrokenLinks = out.exportbrokenlinks();
  in.exportWithClock = out.exportwithclock();
  in.exportWithCreator = out.exportwithcreator();
  switch (out.data().kind_case()) {
    case ::orgproto::DocumentOptions::TocExport::kDoexport:
      in.data = variant_from_index<decltype(in.data)>(0);
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(context, out.data().doexport(), std::get<0>(in.data));
      break;
    case ::orgproto::DocumentOptions::TocExport::kExportfixed:
      in.data = variant_from_index<decltype(in.data)>(1);
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(context, out.data().exportfixed(), std::get<1>(in.data));
      break;
  }
}

void proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup>::write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup>::read(sem::ContextStore* context, ::orgproto::DocumentGroup const& out, sem::DocumentGroup& in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::read(context, out, in);
}

/* clang-format on */