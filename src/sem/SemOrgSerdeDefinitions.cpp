/* clang-format off */
#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>
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

void proto_serde<::orgproto::Cell, sem::Cell>::write(::orgproto::Cell* out, sem::Cell const& in) {
  proto_serde<::orgproto::Cell, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Cell, sem::Cell>::read(::orgproto::Cell const& out, proto_write_accessor<sem::Cell> in) {
  proto_serde<::orgproto::Cell, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Row, sem::Row>::write(::orgproto::Row* out, sem::Row const& in) {
  proto_serde<::orgproto::Row, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::write(out->mutable_cells(), in.cells);
}

void proto_serde<::orgproto::Row, sem::Row>::read(::orgproto::Row const& out, proto_write_accessor<sem::Row> in) {
  proto_serde<::orgproto::Row, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Cell>, Vec<sem::SemId<sem::Cell>>>::read(out.cells(), in.for_field(&sem::Row::cells));
}

void proto_serde<::orgproto::Table, sem::Table>::write(::orgproto::Table* out, sem::Table const& in) {
  proto_serde<::orgproto::Table, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Table, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::write(out->mutable_rows(), in.rows);
}

void proto_serde<::orgproto::Table, sem::Table>::read(::orgproto::Table const& out, proto_write_accessor<sem::Table> in) {
  proto_serde<::orgproto::Table, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::Table, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemId<sem::Row>>>::read(out.rows(), in.for_field(&sem::Table::rows));
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

void proto_serde<::orgproto::Completion, sem::Completion>::write(::orgproto::Completion* out, sem::Completion const& in) {
  proto_serde<::orgproto::Completion, sem::Org>::write(out, in);
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::Completion, sem::Completion>::read(::orgproto::Completion const& out, proto_write_accessor<sem::Completion> in) {
  proto_serde<::orgproto::Completion, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::Completion::done).get() = out.done();
  in.for_field(&sem::Completion::full).get() = out.full();
  in.for_field(&sem::Completion::isPercent).get() = out.ispercent();
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

void proto_serde<::orgproto::Center, sem::Center>::write(::orgproto::Center* out, sem::Center const& in) {
  proto_serde<::orgproto::Center, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Center, sem::Center>::read(::orgproto::Center const& out, proto_write_accessor<sem::Center> in) {
  proto_serde<::orgproto::Center, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Caption, sem::Caption>::write(::orgproto::Caption* out, sem::Caption const& in) {
  proto_serde<::orgproto::Caption, sem::Org>::write(out, in);
  if (!in.text.isNil()) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_text(), in.text);
  }
}

void proto_serde<::orgproto::Caption, sem::Caption>::read(::orgproto::Caption const& out, proto_write_accessor<sem::Caption> in) {
  proto_serde<::orgproto::Caption, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::read(out.text(), in.for_field(&sem::Caption::text));
}

void proto_serde<::orgproto::CmdName, sem::CmdName>::write(::orgproto::CmdName* out, sem::CmdName const& in) {
  proto_serde<::orgproto::CmdName, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdName, sem::CmdName>::read(::orgproto::CmdName const& out, proto_write_accessor<sem::CmdName> in) {
  proto_serde<::orgproto::CmdName, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdResults, sem::CmdResults>::write(::orgproto::CmdResults* out, sem::CmdResults const& in) {
  proto_serde<::orgproto::CmdResults, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdResults, sem::CmdResults>::read(::orgproto::CmdResults const& out, proto_write_accessor<sem::CmdResults> in) {
  proto_serde<::orgproto::CmdResults, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CommandGroup, sem::CommandGroup>::write(::orgproto::CommandGroup* out, sem::CommandGroup const& in) {
  proto_serde<::orgproto::CommandGroup, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CommandGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CommandGroup, sem::CommandGroup>::read(::orgproto::CommandGroup const& out, proto_write_accessor<sem::CommandGroup> in) {
  proto_serde<::orgproto::CommandGroup, sem::Stmt>::read(out, in.as<sem::Stmt>());
  proto_serde<::orgproto::CommandGroup, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Tblfm, sem::Tblfm>::write(::orgproto::Tblfm* out, sem::Tblfm const& in) {
  proto_serde<::orgproto::Tblfm, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Tblfm, sem::Tblfm>::read(::orgproto::Tblfm const& out, proto_write_accessor<sem::Tblfm> in) {
  proto_serde<::orgproto::Tblfm, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Quote, sem::Quote>::write(::orgproto::Quote* out, sem::Quote const& in) {
  proto_serde<::orgproto::Quote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Quote, sem::Quote>::read(::orgproto::Quote const& out, proto_write_accessor<sem::Quote> in) {
  proto_serde<::orgproto::Quote, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CommentBlock, sem::CommentBlock>::write(::orgproto::CommentBlock* out, sem::CommentBlock const& in) {
  proto_serde<::orgproto::CommentBlock, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CommentBlock, sem::CommentBlock>::read(::orgproto::CommentBlock const& out, proto_write_accessor<sem::CommentBlock> in) {
  proto_serde<::orgproto::CommentBlock, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Verse, sem::Verse>::write(::orgproto::Verse* out, sem::Verse const& in) {
  proto_serde<::orgproto::Verse, sem::Block>::write(out, in);
  proto_serde<::orgproto::Verse, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Verse, sem::Verse>::read(::orgproto::Verse const& out, proto_write_accessor<sem::Verse> in) {
  proto_serde<::orgproto::Verse, sem::Block>::read(out, in.as<sem::Block>());
  proto_serde<::orgproto::Verse, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Example, sem::Example>::write(::orgproto::Example* out, sem::Example const& in) {
  proto_serde<::orgproto::Example, sem::Block>::write(out, in);
  proto_serde<::orgproto::Example, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Example, sem::Example>::read(::orgproto::Example const& out, proto_write_accessor<sem::Example> in) {
  proto_serde<::orgproto::Example, sem::Block>::read(out, in.as<sem::Block>());
  proto_serde<::orgproto::Example, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::ColonExample, sem::ColonExample>::write(::orgproto::ColonExample* out, sem::ColonExample const& in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ColonExample, sem::ColonExample>::read(::orgproto::ColonExample const& out, proto_write_accessor<sem::ColonExample> in) {
  proto_serde<::orgproto::ColonExample, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::write(::orgproto::CmdArguments* out, sem::CmdArguments const& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgument>, UnorderedMap<Str, sem::SemId<sem::CmdArgument>>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::read(::orgproto::CmdArguments const& out, proto_write_accessor<sem::CmdArguments> in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemId<sem::CmdArgument>>>::read(out.positional(), in.for_field(&sem::CmdArguments::positional));
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgument>, UnorderedMap<Str, sem::SemId<sem::CmdArgument>>>::read(out.named(), in.for_field(&sem::CmdArguments::named));
}

void proto_serde<::orgproto::CmdAttr, sem::CmdAttr>::write(::orgproto::CmdAttr* out, sem::CmdAttr const& in) {
  proto_serde<::orgproto::CmdAttr, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
  if (!in.parameters.isNil()) {
    proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::write(out->mutable_parameters(), in.parameters);
  }
}

void proto_serde<::orgproto::CmdAttr, sem::CmdAttr>::read(::orgproto::CmdAttr const& out, proto_write_accessor<sem::CmdAttr> in) {
  proto_serde<::orgproto::CmdAttr, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::CmdAttr::target));
  proto_serde<orgproto::CmdArguments, sem::SemId<sem::CmdArguments>>::read(out.parameters(), in.for_field(&sem::CmdAttr::parameters));
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::write(::orgproto::CmdArgument* out, sem::CmdArgument const& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::write(out, in);
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::read(::orgproto::CmdArgument const& out, proto_write_accessor<sem::CmdArgument> in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_key()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.key(), in.for_field(&sem::CmdArgument::key));
  }
  proto_serde<std::string, Str>::read(out.value(), in.for_field(&sem::CmdArgument::value));
}

void proto_serde<::orgproto::Export, sem::Export>::write(::orgproto::Export* out, sem::Export const& in) {
  proto_serde<::orgproto::Export, sem::Block>::write(out, in);
  proto_serde<::orgproto::Export, sem::Org>::write(out, in);
  out->set_format(static_cast<orgproto::Export_Format>(in.format));
  proto_serde<std::string, Str>::write(out->mutable_exporter(), in.exporter);
  if (in.placement) {
    proto_serde<std::string, Str>::write(out->mutable_placement(), *in.placement);
  }
  proto_serde<std::string, Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::Export, sem::Export>::read(::orgproto::Export const& out, proto_write_accessor<sem::Export> in) {
  proto_serde<::orgproto::Export, sem::Block>::read(out, in.as<sem::Block>());
  proto_serde<::orgproto::Export, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::Export::format).get() = static_cast<sem::Export::Format>(out.format());
  proto_serde<std::string, Str>::read(out.exporter(), in.for_field(&sem::Export::exporter));
  if (out.has_placement()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.placement(), in.for_field(&sem::Export::placement));
  }
  proto_serde<std::string, Str>::read(out.content(), in.for_field(&sem::Export::content));
}

void proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock>::write(::orgproto::AdmonitionBlock* out, sem::AdmonitionBlock const& in) {
  proto_serde<::orgproto::AdmonitionBlock, sem::Block>::write(out, in);
  proto_serde<::orgproto::AdmonitionBlock, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock>::read(::orgproto::AdmonitionBlock const& out, proto_write_accessor<sem::AdmonitionBlock> in) {
  proto_serde<::orgproto::AdmonitionBlock, sem::Block>::read(out, in.as<sem::Block>());
  proto_serde<::orgproto::AdmonitionBlock, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::Call, sem::Call>::write(::orgproto::Call* out, sem::Call const& in) {
  proto_serde<::orgproto::Call, sem::Org>::write(out, in);
  if (in.name) {
    proto_serde<std::string, Str>::write(out->mutable_name(), *in.name);
  }
}

void proto_serde<::orgproto::Call, sem::Call>::read(::orgproto::Call const& out, proto_write_accessor<sem::Call> in) {
  proto_serde<::orgproto::Call, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_name()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.name(), in.for_field(&sem::Call::name));
  }
}

void proto_serde<::orgproto::Code::Line::Part::Raw, sem::Code::Line::Part::Raw>::write(::orgproto::Code::Line::Part::Raw* out, sem::Code::Line::Part::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_code(), in.code);
}

void proto_serde<::orgproto::Code::Line::Part::Raw, sem::Code::Line::Part::Raw>::read(::orgproto::Code::Line::Part::Raw const& out, proto_write_accessor<sem::Code::Line::Part::Raw> in) {
  proto_serde<std::string, Str>::read(out.code(), in.for_field(&sem::Code::Line::Part::Raw::code));
}

void proto_serde<::orgproto::Code::Line::Part::Callout, sem::Code::Line::Part::Callout>::write(::orgproto::Code::Line::Part::Callout* out, sem::Code::Line::Part::Callout const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Code::Line::Part::Callout, sem::Code::Line::Part::Callout>::read(::orgproto::Code::Line::Part::Callout const& out, proto_write_accessor<sem::Code::Line::Part::Callout> in) {
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Code::Line::Part::Callout::name));
}

void proto_serde<::orgproto::Code::Line::Part::Tangle, sem::Code::Line::Part::Tangle>::write(::orgproto::Code::Line::Part::Tangle* out, sem::Code::Line::Part::Tangle const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Code::Line::Part::Tangle, sem::Code::Line::Part::Tangle>::read(::orgproto::Code::Line::Part::Tangle const& out, proto_write_accessor<sem::Code::Line::Part::Tangle> in) {
  proto_serde<std::string, Str>::read(out.target(), in.for_field(&sem::Code::Line::Part::Tangle::target));
}

void proto_serde<::orgproto::Code::Line::Part, sem::Code::Line::Part>::write(::orgproto::Code::Line::Part* out, sem::Code::Line::Part const& in) {
  switch (in.data.index()) {
    case 0:
      proto_serde<orgproto::Code::Line::Part::Raw, sem::Code::Line::Part::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data));
      break;
    case 1:
      proto_serde<orgproto::Code::Line::Part::Callout, sem::Code::Line::Part::Callout>::write(out->mutable_data()->mutable_callout(), std::get<1>(in.data));
      break;
    case 2:
      proto_serde<orgproto::Code::Line::Part::Tangle, sem::Code::Line::Part::Tangle>::write(out->mutable_data()->mutable_tangle(), std::get<2>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Code::Line::Part, sem::Code::Line::Part>::read(::orgproto::Code::Line::Part const& out, proto_write_accessor<sem::Code::Line::Part> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Code::Line::Part::Data::kRaw:
      proto_serde<orgproto::Code::Line::Part::Raw, sem::Code::Line::Part::Raw>::read(out.data().raw(), in.for_field_variant<0>(&sem::Code::Line::Part::data));
      break;
    case ::orgproto::Code::Line::Part::Data::kCallout:
      proto_serde<orgproto::Code::Line::Part::Callout, sem::Code::Line::Part::Callout>::read(out.data().callout(), in.for_field_variant<1>(&sem::Code::Line::Part::data));
      break;
    case ::orgproto::Code::Line::Part::Data::kTangle:
      proto_serde<orgproto::Code::Line::Part::Tangle, sem::Code::Line::Part::Tangle>::read(out.data().tangle(), in.for_field_variant<2>(&sem::Code::Line::Part::data));
      break;
  }
}

void proto_serde<::orgproto::Code::Line, sem::Code::Line>::write(::orgproto::Code::Line* out, sem::Code::Line const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Line::Part>, Vec<sem::Code::Line::Part>>::write(out->mutable_parts(), in.parts);
}

void proto_serde<::orgproto::Code::Line, sem::Code::Line>::read(::orgproto::Code::Line const& out, proto_write_accessor<sem::Code::Line> in) {
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Line::Part>, Vec<sem::Code::Line::Part>>::read(out.parts(), in.for_field(&sem::Code::Line::parts));
}

void proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::write(::orgproto::Code::Switch::LineStart* out, sem::Code::Switch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::read(::orgproto::Code::Switch::LineStart const& out, proto_write_accessor<sem::Code::Switch::LineStart> in) {
  in.for_field(&sem::Code::Switch::LineStart::start).get() = out.start();
  in.for_field(&sem::Code::Switch::LineStart::extendLast).get() = out.extendlast();
}

void proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::write(::orgproto::Code::Switch::CalloutFormat* out, sem::Code::Switch::CalloutFormat const& in) {
  proto_serde<std::string, Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::read(::orgproto::Code::Switch::CalloutFormat const& out, proto_write_accessor<sem::Code::Switch::CalloutFormat> in) {
  proto_serde<std::string, Str>::read(out.format(), in.for_field(&sem::Code::Switch::CalloutFormat::format));
}

void proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::write(::orgproto::Code::Switch::RemoveCallout* out, sem::Code::Switch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::read(::orgproto::Code::Switch::RemoveCallout const& out, proto_write_accessor<sem::Code::Switch::RemoveCallout> in) {
  in.for_field(&sem::Code::Switch::RemoveCallout::remove).get() = out.remove();
}

void proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::write(::orgproto::Code::Switch::EmphasizeLine* out, sem::Code::Switch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::read(::orgproto::Code::Switch::EmphasizeLine const& out, proto_write_accessor<sem::Code::Switch::EmphasizeLine> in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::read(out.line(), in.for_field(&sem::Code::Switch::EmphasizeLine::line));
}

void proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::write(::orgproto::Code::Switch::Dedent* out, sem::Code::Switch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::read(::orgproto::Code::Switch::Dedent const& out, proto_write_accessor<sem::Code::Switch::Dedent> in) {
  in.for_field(&sem::Code::Switch::Dedent::value).get() = out.value();
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

void proto_serde<::orgproto::Code::Switch, sem::Code::Switch>::read(::orgproto::Code::Switch const& out, proto_write_accessor<sem::Code::Switch> in) {
  switch (out.data().kind_case()) {
    case ::orgproto::Code::Switch::Data::kLinestart:
      proto_serde<orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::read(out.data().linestart(), in.for_field_variant<0>(&sem::Code::Switch::data));
      break;
    case ::orgproto::Code::Switch::Data::kCalloutformat:
      proto_serde<orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::read(out.data().calloutformat(), in.for_field_variant<1>(&sem::Code::Switch::data));
      break;
    case ::orgproto::Code::Switch::Data::kRemovecallout:
      proto_serde<orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::read(out.data().removecallout(), in.for_field_variant<2>(&sem::Code::Switch::data));
      break;
    case ::orgproto::Code::Switch::Data::kEmphasizeline:
      proto_serde<orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::read(out.data().emphasizeline(), in.for_field_variant<3>(&sem::Code::Switch::data));
      break;
    case ::orgproto::Code::Switch::Data::kDedent:
      proto_serde<orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::read(out.data().dedent(), in.for_field_variant<4>(&sem::Code::Switch::data));
      break;
  }
}

void proto_serde<::orgproto::Code, sem::Code>::write(::orgproto::Code* out, sem::Code const& in) {
  proto_serde<::orgproto::Code, sem::Block>::write(out, in);
  proto_serde<::orgproto::Code, sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Switch>, Vec<sem::Code::Switch>>::write(out->mutable_switches(), in.switches);
  out->set_exports(static_cast<orgproto::Code_Exports>(in.exports));
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Line>, Vec<sem::Code::Line>>::write(out->mutable_lines(), in.lines);
  out->set_cache(in.cache);
  out->set_eval(in.eval);
  out->set_noweb(in.noweb);
  out->set_hlines(in.hlines);
  out->set_tangle(in.tangle);
}

void proto_serde<::orgproto::Code, sem::Code>::read(::orgproto::Code const& out, proto_write_accessor<sem::Code> in) {
  proto_serde<::orgproto::Code, sem::Block>::read(out, in.as<sem::Block>());
  proto_serde<::orgproto::Code, sem::Org>::read(out, in.as<sem::Org>());
  if (out.has_lang()) {
    proto_serde<Opt<std::string>, Opt<Str>>::read(out.lang(), in.for_field(&sem::Code::lang));
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Switch>, Vec<sem::Code::Switch>>::read(out.switches(), in.for_field(&sem::Code::switches));
  in.for_field(&sem::Code::exports).get() = static_cast<sem::Code::Exports>(out.exports());
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Line>, Vec<sem::Code::Line>>::read(out.lines(), in.for_field(&sem::Code::lines));
  in.for_field(&sem::Code::cache).get() = out.cache();
  in.for_field(&sem::Code::eval).get() = out.eval();
  in.for_field(&sem::Code::noweb).get() = out.noweb();
  in.for_field(&sem::Code::hlines).get() = out.hlines();
  in.for_field(&sem::Code::tangle).get() = out.tangle();
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
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_arguments(), in.arguments);
}

void proto_serde<::orgproto::Macro, sem::Macro>::read(::orgproto::Macro const& out, proto_write_accessor<sem::Macro> in) {
  proto_serde<::orgproto::Macro, sem::Org>::read(out, in.as<sem::Org>());
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Macro::name));
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::read(out.arguments(), in.for_field(&sem::Macro::arguments));
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
  out->set_action(static_cast<orgproto::SubtreeLog_Priority_Action>(in.action));
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
  in.for_field(&sem::SubtreeLog::Priority::action).get() = static_cast<sem::SubtreeLog::Priority::Action>(out.action());
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
  out->set_kind(static_cast<orgproto::Subtree_Period_Kind>(in.kind));
  if (!in.from.isNil()) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_from(), in.from);
  }
  if (in.to) {
    proto_serde<orgproto::Time, sem::SemId<sem::Time>>::write(out->mutable_to(), *in.to);
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::read(::orgproto::Subtree::Period const& out, proto_write_accessor<sem::Subtree::Period> in) {
  in.for_field(&sem::Subtree::Period::kind).get() = static_cast<sem::Subtree::Period::Kind>(out.kind());
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
  out->set_level(static_cast<orgproto::Subtree_Property_Visibility_Level>(in.level));
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::read(::orgproto::Subtree::Property::Visibility const& out, proto_write_accessor<sem::Subtree::Property::Visibility> in) {
  in.for_field(&sem::Subtree::Property::Visibility::level).get() = static_cast<sem::Subtree::Property::Visibility::Level>(out.level());
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

void proto_serde<::orgproto::Subtree::Property::Unknown, sem::Subtree::Property::Unknown>::write(::orgproto::Subtree::Property::Unknown* out, sem::Subtree::Property::Unknown const& in) {
  if (!in.value.isNil()) {
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(out->mutable_value(), in.value);
  }
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Subtree::Property::Unknown, sem::Subtree::Property::Unknown>::read(::orgproto::Subtree::Property::Unknown const& out, proto_write_accessor<sem::Subtree::Property::Unknown> in) {
  proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(out.value(), in.for_field(&sem::Subtree::Property::Unknown::value));
  proto_serde<std::string, Str>::read(out.name(), in.for_field(&sem::Subtree::Property::Unknown::name));
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
    case 14:
      proto_serde<orgproto::Subtree::Property::Unknown, sem::Subtree::Property::Unknown>::write(out->mutable_data()->mutable_unknown(), std::get<14>(in.data));
      break;
  }
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::read(::orgproto::Subtree::Property const& out, proto_write_accessor<sem::Subtree::Property> in) {
  in.for_field(&sem::Subtree::Property::mainSetRule).get() = static_cast<sem::Subtree::Property::SetMode>(out.mainsetrule());
  in.for_field(&sem::Subtree::Property::subSetRule).get() = static_cast<sem::Subtree::Property::SetMode>(out.subsetrule());
  in.for_field(&sem::Subtree::Property::inheritanceMode).get() = static_cast<sem::Subtree::Property::InheritanceMode>(out.inheritancemode());
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
    case ::orgproto::Subtree::Property::Data::kUnknown:
      proto_serde<orgproto::Subtree::Property::Unknown, sem::Subtree::Property::Unknown>::read(out.data().unknown(), in.for_field_variant<14>(&sem::Subtree::Property::data));
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
    proto_serde<orgproto::Completion, sem::SemId<sem::Completion>>::write(out->mutable_completion(), *in.completion);
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
    proto_serde<Opt<orgproto::Completion>, Opt<sem::SemId<sem::Completion>>>::read(out.completion(), in.for_field(&sem::Subtree::completion));
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
}

void proto_serde<::orgproto::InlineMath, sem::InlineMath>::write(::orgproto::InlineMath* out, sem::InlineMath const& in) {
  proto_serde<::orgproto::InlineMath, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::InlineMath, sem::InlineMath>::read(::orgproto::InlineMath const& out, proto_write_accessor<sem::InlineMath> in) {
  proto_serde<::orgproto::InlineMath, sem::Org>::read(out, in.as<sem::Org>());
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

void proto_serde<::orgproto::List, sem::List>::write(::orgproto::List* out, sem::List const& in) {
  proto_serde<::orgproto::List, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::List, sem::List>::read(::orgproto::List const& out, proto_write_accessor<sem::List> in) {
  proto_serde<::orgproto::List, sem::Org>::read(out, in.as<sem::Org>());
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::write(::orgproto::ListItem* out, sem::ListItem const& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::write(out, in);
  out->set_checkbox(static_cast<orgproto::ListItem_Checkbox>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::Paragraph, sem::SemId<sem::Paragraph>>::write(out->mutable_header(), *in.header);
  }
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::read(::orgproto::ListItem const& out, proto_write_accessor<sem::ListItem> in) {
  proto_serde<::orgproto::ListItem, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::ListItem::checkbox).get() = static_cast<sem::ListItem::Checkbox>(out.checkbox());
  if (out.has_header()) {
    proto_serde<Opt<orgproto::Paragraph>, Opt<sem::SemId<sem::Paragraph>>>::read(out.header(), in.for_field(&sem::ListItem::header));
  }
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

void proto_serde<::orgproto::Link, sem::Link>::write(::orgproto::Link* out, sem::Link const& in) {
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
  }
}

void proto_serde<::orgproto::Link, sem::Link>::read(::orgproto::Link const& out, proto_write_accessor<sem::Link> in) {
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
  }
}

void proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(::orgproto::DocumentOptions::DoExport* out, sem::DocumentOptions::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(::orgproto::DocumentOptions::DoExport const& out, proto_write_accessor<sem::DocumentOptions::DoExport> in) {
  in.for_field(&sem::DocumentOptions::DoExport::exportToc).get() = out.exporttoc();
}

void proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(::orgproto::DocumentOptions::ExportFixed* out, sem::DocumentOptions::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(::orgproto::DocumentOptions::ExportFixed const& out, proto_write_accessor<sem::DocumentOptions::ExportFixed> in) {
  in.for_field(&sem::DocumentOptions::ExportFixed::exportLevels).get() = out.exportlevels();
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

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::read(::orgproto::DocumentOptions const& out, proto_write_accessor<sem::DocumentOptions> in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::read(out, in.as<sem::Org>());
  in.for_field(&sem::DocumentOptions::brokenLinks).get() = static_cast<sem::DocumentOptions::BrokenLinks>(out.brokenlinks());
  in.for_field(&sem::DocumentOptions::initialVisibility).get() = static_cast<sem::DocumentOptions::Visibility>(out.initialvisibility());
  switch (out.tocexport().kind_case()) {
    case ::orgproto::DocumentOptions::TocExport::kDoexport:
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(out.tocexport().doexport(), in.for_field_variant<0>(&sem::DocumentOptions::tocExport));
      break;
    case ::orgproto::DocumentOptions::TocExport::kExportfixed:
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(out.tocexport().exportfixed(), in.for_field_variant<1>(&sem::DocumentOptions::tocExport));
      break;
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Subtree::Property>, Vec<sem::Subtree::Property>>::read(out.properties(), in.for_field(&sem::DocumentOptions::properties));
  in.for_field(&sem::DocumentOptions::smartQuotes).get() = out.smartquotes();
  in.for_field(&sem::DocumentOptions::emphasizedText).get() = out.emphasizedtext();
  in.for_field(&sem::DocumentOptions::specialStrings).get() = out.specialstrings();
  in.for_field(&sem::DocumentOptions::fixedWidthSections).get() = out.fixedwidthsections();
  in.for_field(&sem::DocumentOptions::includeTimestamps).get() = out.includetimestamps();
  in.for_field(&sem::DocumentOptions::preserveLineBreaks).get() = out.preservelinebreaks();
  in.for_field(&sem::DocumentOptions::plaintextSubscripts).get() = out.plaintextsubscripts();
  in.for_field(&sem::DocumentOptions::exportArchived).get() = out.exportarchived();
  in.for_field(&sem::DocumentOptions::exportWithAuthor).get() = out.exportwithauthor();
  in.for_field(&sem::DocumentOptions::exportBrokenLinks).get() = out.exportbrokenlinks();
  in.for_field(&sem::DocumentOptions::exportWithClock).get() = out.exportwithclock();
  in.for_field(&sem::DocumentOptions::exportWithCreator).get() = out.exportwithcreator();
  switch (out.data().kind_case()) {
    case ::orgproto::DocumentOptions::TocExport::kDoexport:
      proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::read(out.data().doexport(), in.for_field_variant<0>(&sem::DocumentOptions::data));
      break;
    case ::orgproto::DocumentOptions::TocExport::kExportfixed:
      proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::read(out.data().exportfixed(), in.for_field_variant<1>(&sem::DocumentOptions::data));
      break;
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

void proto_serde<::orgproto::ParseError, sem::ParseError>::write(::orgproto::ParseError* out, sem::ParseError const& in) {
  proto_serde<::orgproto::ParseError, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ParseError, sem::ParseError>::read(::orgproto::ParseError const& out, proto_write_accessor<sem::ParseError> in) {
  proto_serde<::orgproto::ParseError, sem::Org>::read(out, in.as<sem::Org>());
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

}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::read(::orgproto::Include::OrgDocument const& out, proto_write_accessor<sem::Include::OrgDocument> in) {

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

void proto_serde<::orgproto::Include, sem::Include>::read(::orgproto::Include const& out, proto_write_accessor<sem::Include> in) {
  proto_serde<::orgproto::Include, sem::Org>::read(out, in.as<sem::Org>());
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