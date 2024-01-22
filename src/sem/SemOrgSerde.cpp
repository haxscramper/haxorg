/* clang-format off */
#include <sem/SemOrgSerde.hpp>
template <>
struct proto_serde<::orgproto::Stmt, sem::Stmt> {
  static void write(::orgproto::Stmt* out, sem::Stmt const& in);
};


template <>
struct proto_serde<::orgproto::Inline, sem::Inline> {
  static void write(::orgproto::Inline* out, sem::Inline const& in);
};


template <>
struct proto_serde<::orgproto::StmtList, sem::StmtList> {
  static void write(::orgproto::StmtList* out, sem::StmtList const& in);
};


template <>
struct proto_serde<::orgproto::Empty, sem::Empty> {
  static void write(::orgproto::Empty* out, sem::Empty const& in);
};


template <>
struct proto_serde<::orgproto::Row, sem::Row> {
  static void write(::orgproto::Row* out, sem::Row const& in);
};


template <>
struct proto_serde<::orgproto::Table, sem::Table> {
  static void write(::orgproto::Table* out, sem::Table const& in);
};


template <>
struct proto_serde<::orgproto::HashTag, sem::HashTag> {
  static void write(::orgproto::HashTag* out, sem::HashTag const& in);
};


template <>
struct proto_serde<::orgproto::Footnote, sem::Footnote> {
  static void write(::orgproto::Footnote* out, sem::Footnote const& in);
};


template <>
struct proto_serde<::orgproto::Completion, sem::Completion> {
  static void write(::orgproto::Completion* out, sem::Completion const& in);
};


template <>
struct proto_serde<::orgproto::Paragraph, sem::Paragraph> {
  static void write(::orgproto::Paragraph* out, sem::Paragraph const& in);
};


template <>
struct proto_serde<::orgproto::Format, sem::Format> {
  static void write(::orgproto::Format* out, sem::Format const& in);
};


template <>
struct proto_serde<::orgproto::Center, sem::Center> {
  static void write(::orgproto::Center* out, sem::Center const& in);
};


template <>
struct proto_serde<::orgproto::Command, sem::Command> {
  static void write(::orgproto::Command* out, sem::Command const& in);
};


template <>
struct proto_serde<::orgproto::LineCommand, sem::LineCommand> {
  static void write(::orgproto::LineCommand* out, sem::LineCommand const& in);
};


template <>
struct proto_serde<::orgproto::Standalone, sem::Standalone> {
  static void write(::orgproto::Standalone* out, sem::Standalone const& in);
};


template <>
struct proto_serde<::orgproto::Attached, sem::Attached> {
  static void write(::orgproto::Attached* out, sem::Attached const& in);
};


template <>
struct proto_serde<::orgproto::Caption, sem::Caption> {
  static void write(::orgproto::Caption* out, sem::Caption const& in);
};


template <>
struct proto_serde<::orgproto::CommandGroup, sem::CommandGroup> {
  static void write(::orgproto::CommandGroup* out, sem::CommandGroup const& in);
};


template <>
struct proto_serde<::orgproto::Block, sem::Block> {
  static void write(::orgproto::Block* out, sem::Block const& in);
};


template <>
struct proto_serde<::orgproto::Quote, sem::Quote> {
  static void write(::orgproto::Quote* out, sem::Quote const& in);
};


template <>
struct proto_serde<::orgproto::Example, sem::Example> {
  static void write(::orgproto::Example* out, sem::Example const& in);
};


template <>
struct proto_serde<::orgproto::CmdArguments, sem::CmdArguments> {
  static void write(::orgproto::CmdArguments* out, sem::CmdArguments const& in);
};


template <>
struct proto_serde<::orgproto::CmdArgument, sem::CmdArgument> {
  static void write(::orgproto::CmdArgument* out, sem::CmdArgument const& in);
};


template <>
struct proto_serde<::orgproto::Export, sem::Export> {
  static void write(::orgproto::Export* out, sem::Export const& in);
};


template <>
struct proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock> {
  static void write(::orgproto::AdmonitionBlock* out, sem::AdmonitionBlock const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart> {
  static void write(::orgproto::Code::Switch::LineStart* out, sem::Code::Switch::LineStart const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat> {
  static void write(::orgproto::Code::Switch::CalloutFormat* out, sem::Code::Switch::CalloutFormat const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout> {
  static void write(::orgproto::Code::Switch::RemoveCallout* out, sem::Code::Switch::RemoveCallout const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine> {
  static void write(::orgproto::Code::Switch::EmphasizeLine* out, sem::Code::Switch::EmphasizeLine const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent> {
  static void write(::orgproto::Code::Switch::Dedent* out, sem::Code::Switch::Dedent const& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch, sem::Code::Switch> {
  static void write(::orgproto::Code::Switch* out, sem::Code::Switch const& in);
};


template <>
struct proto_serde<::orgproto::Code, sem::Code> {
  static void write(::orgproto::Code* out, sem::Code const& in);
};


template <>
struct proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat> {
  static void write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in);
};


template <>
struct proto_serde<::orgproto::Time::Static, sem::Time::Static> {
  static void write(::orgproto::Time::Static* out, sem::Time::Static const& in);
};


template <>
struct proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic> {
  static void write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in);
};


template <>
struct proto_serde<::orgproto::Time, sem::Time> {
  static void write(::orgproto::Time* out, sem::Time const& in);
};


template <>
struct proto_serde<::orgproto::TimeRange, sem::TimeRange> {
  static void write(::orgproto::TimeRange* out, sem::TimeRange const& in);
};


template <>
struct proto_serde<::orgproto::Macro, sem::Macro> {
  static void write(::orgproto::Macro* out, sem::Macro const& in);
};


template <>
struct proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param> {
  static void write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in);
};


template <>
struct proto_serde<::orgproto::Symbol, sem::Symbol> {
  static void write(::orgproto::Symbol* out, sem::Symbol const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog> {
  static void write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority> {
  static void write(::orgproto::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note> {
  static void write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile> {
  static void write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock> {
  static void write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State> {
  static void write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag> {
  static void write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog> {
  static void write(::orgproto::SubtreeLog* out, sem::SubtreeLog const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period> {
  static void write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking> {
  static void write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger> {
  static void write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin> {
  static void write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass> {
  static void write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions> {
  static void write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader> {
  static void write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler> {
  static void write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered> {
  static void write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort> {
  static void write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility> {
  static void write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions> {
  static void write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker> {
  static void write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered> {
  static void write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created> {
  static void write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property> {
  static void write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in);
};


template <>
struct proto_serde<::orgproto::Subtree, sem::Subtree> {
  static void write(::orgproto::Subtree* out, sem::Subtree const& in);
};


template <>
struct proto_serde<::orgproto::LatexBody, sem::LatexBody> {
  static void write(::orgproto::LatexBody* out, sem::LatexBody const& in);
};


template <>
struct proto_serde<::orgproto::InlineMath, sem::InlineMath> {
  static void write(::orgproto::InlineMath* out, sem::InlineMath const& in);
};


template <>
struct proto_serde<::orgproto::Leaf, sem::Leaf> {
  static void write(::orgproto::Leaf* out, sem::Leaf const& in);
};


template <>
struct proto_serde<::orgproto::Escaped, sem::Escaped> {
  static void write(::orgproto::Escaped* out, sem::Escaped const& in);
};


template <>
struct proto_serde<::orgproto::Newline, sem::Newline> {
  static void write(::orgproto::Newline* out, sem::Newline const& in);
};


template <>
struct proto_serde<::orgproto::Space, sem::Space> {
  static void write(::orgproto::Space* out, sem::Space const& in);
};


template <>
struct proto_serde<::orgproto::Word, sem::Word> {
  static void write(::orgproto::Word* out, sem::Word const& in);
};


template <>
struct proto_serde<::orgproto::AtMention, sem::AtMention> {
  static void write(::orgproto::AtMention* out, sem::AtMention const& in);
};


template <>
struct proto_serde<::orgproto::RawText, sem::RawText> {
  static void write(::orgproto::RawText* out, sem::RawText const& in);
};


template <>
struct proto_serde<::orgproto::Punctuation, sem::Punctuation> {
  static void write(::orgproto::Punctuation* out, sem::Punctuation const& in);
};


template <>
struct proto_serde<::orgproto::Placeholder, sem::Placeholder> {
  static void write(::orgproto::Placeholder* out, sem::Placeholder const& in);
};


template <>
struct proto_serde<::orgproto::BigIdent, sem::BigIdent> {
  static void write(::orgproto::BigIdent* out, sem::BigIdent const& in);
};


template <>
struct proto_serde<::orgproto::Markup, sem::Markup> {
  static void write(::orgproto::Markup* out, sem::Markup const& in);
};


template <>
struct proto_serde<::orgproto::Bold, sem::Bold> {
  static void write(::orgproto::Bold* out, sem::Bold const& in);
};


template <>
struct proto_serde<::orgproto::Underline, sem::Underline> {
  static void write(::orgproto::Underline* out, sem::Underline const& in);
};


template <>
struct proto_serde<::orgproto::Monospace, sem::Monospace> {
  static void write(::orgproto::Monospace* out, sem::Monospace const& in);
};


template <>
struct proto_serde<::orgproto::MarkQuote, sem::MarkQuote> {
  static void write(::orgproto::MarkQuote* out, sem::MarkQuote const& in);
};


template <>
struct proto_serde<::orgproto::Verbatim, sem::Verbatim> {
  static void write(::orgproto::Verbatim* out, sem::Verbatim const& in);
};


template <>
struct proto_serde<::orgproto::Italic, sem::Italic> {
  static void write(::orgproto::Italic* out, sem::Italic const& in);
};


template <>
struct proto_serde<::orgproto::Strike, sem::Strike> {
  static void write(::orgproto::Strike* out, sem::Strike const& in);
};


template <>
struct proto_serde<::orgproto::Par, sem::Par> {
  static void write(::orgproto::Par* out, sem::Par const& in);
};


template <>
struct proto_serde<::orgproto::List, sem::List> {
  static void write(::orgproto::List* out, sem::List const& in);
};


template <>
struct proto_serde<::orgproto::ListItem, sem::ListItem> {
  static void write(::orgproto::ListItem* out, sem::ListItem const& in);
};


template <>
struct proto_serde<::orgproto::Link::Raw, sem::Link::Raw> {
  static void write(::orgproto::Link::Raw* out, sem::Link::Raw const& in);
};


template <>
struct proto_serde<::orgproto::Link::Id, sem::Link::Id> {
  static void write(::orgproto::Link::Id* out, sem::Link::Id const& in);
};


template <>
struct proto_serde<::orgproto::Link::Person, sem::Link::Person> {
  static void write(::orgproto::Link::Person* out, sem::Link::Person const& in);
};


template <>
struct proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote> {
  static void write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in);
};


template <>
struct proto_serde<::orgproto::Link::File, sem::Link::File> {
  static void write(::orgproto::Link::File* out, sem::Link::File const& in);
};


template <>
struct proto_serde<::orgproto::Link, sem::Link> {
  static void write(::orgproto::Link* out, sem::Link const& in);
};


template <>
struct proto_serde<::orgproto::Document, sem::Document> {
  static void write(::orgproto::Document* out, sem::Document const& in);
};


template <>
struct proto_serde<::orgproto::ParseError, sem::ParseError> {
  static void write(::orgproto::ParseError* out, sem::ParseError const& in);
};


template <>
struct proto_serde<::orgproto::FileTarget, sem::FileTarget> {
  static void write(::orgproto::FileTarget* out, sem::FileTarget const& in);
};


template <>
struct proto_serde<::orgproto::TextSeparator, sem::TextSeparator> {
  static void write(::orgproto::TextSeparator* out, sem::TextSeparator const& in);
};


template <>
struct proto_serde<::orgproto::Include::Example, sem::Include::Example> {
  static void write(::orgproto::Include::Example* out, sem::Include::Example const& in);
};


template <>
struct proto_serde<::orgproto::Include::Export, sem::Include::Export> {
  static void write(::orgproto::Include::Export* out, sem::Include::Export const& in);
};


template <>
struct proto_serde<::orgproto::Include::Src, sem::Include::Src> {
  static void write(::orgproto::Include::Src* out, sem::Include::Src const& in);
};


template <>
struct proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument> {
  static void write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in);
};


template <>
struct proto_serde<::orgproto::Include, sem::Include> {
  static void write(::orgproto::Include* out, sem::Include const& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport> {
  static void write(::orgproto::DocumentOptions::DoExport* out, sem::DocumentOptions::DoExport const& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed> {
  static void write(::orgproto::DocumentOptions::ExportFixed* out, sem::DocumentOptions::ExportFixed const& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions> {
  static void write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in);
};


template <>
struct proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup> {
  static void write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in);
};


void proto_serde<::orgproto::Stmt, sem::Stmt>::write(::orgproto::Stmt* out, sem::Stmt const& in) {
  proto_serde<::orgproto::Stmt, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId>>::write(out->mutable_attached(), in.attached);
}

void proto_serde<::orgproto::Inline, sem::Inline>::write(::orgproto::Inline* out, sem::Inline const& in) {
  proto_serde<::orgproto::Inline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::StmtList, sem::StmtList>::write(::orgproto::StmtList* out, sem::StmtList const& in) {
  proto_serde<::orgproto::StmtList, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Empty, sem::Empty>::write(::orgproto::Empty* out, sem::Empty const& in) {
  proto_serde<::orgproto::Empty, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Row, sem::Row>::write(::orgproto::Row* out, sem::Row const& in) {
  proto_serde<::orgproto::Row, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Table, sem::Table>::write(::orgproto::Table* out, sem::Table const& in) {
  proto_serde<::orgproto::Table, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Table, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Row>, Vec<sem::SemIdT<sem::Row>>>::write(out->mutable_rows(), in.rows);
}

void proto_serde<::orgproto::HashTag, sem::HashTag>::write(::orgproto::HashTag* out, sem::HashTag const& in) {
  proto_serde<::orgproto::HashTag, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_head(), in.head);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::HashTag>, Vec<sem::SemIdT<sem::HashTag>>>::write(out->mutable_subtags(), in.subtags);
}

void proto_serde<::orgproto::Footnote, sem::Footnote>::write(::orgproto::Footnote* out, sem::Footnote const& in) {
  proto_serde<::orgproto::Footnote, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_tag(), in.tag);
  if (in.definition) {
    proto_serde<orgproto::AnyNode, sem::SemId>::write(out->mutable_definition(), *in.definition);
  }
}

void proto_serde<::orgproto::Completion, sem::Completion>::write(::orgproto::Completion* out, sem::Completion const& in) {
  proto_serde<::orgproto::Completion, sem::Org>::write(out, in);
  out->set_done(in.done);
  out->set_full(in.full);
  out->set_ispercent(in.isPercent);
}

void proto_serde<::orgproto::Paragraph, sem::Paragraph>::write(::orgproto::Paragraph* out, sem::Paragraph const& in) {
  proto_serde<::orgproto::Paragraph, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::Paragraph, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Format, sem::Format>::write(::orgproto::Format* out, sem::Format const& in) {
  proto_serde<::orgproto::Format, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Center, sem::Center>::write(::orgproto::Center* out, sem::Center const& in) {
  proto_serde<::orgproto::Center, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Command, sem::Command>::write(::orgproto::Command* out, sem::Command const& in) {
  proto_serde<::orgproto::Command, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::LineCommand, sem::LineCommand>::write(::orgproto::LineCommand* out, sem::LineCommand const& in) {
  proto_serde<::orgproto::LineCommand, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Standalone, sem::Standalone>::write(::orgproto::Standalone* out, sem::Standalone const& in) {
  proto_serde<::orgproto::Standalone, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Attached, sem::Attached>::write(::orgproto::Attached* out, sem::Attached const& in) {
  proto_serde<::orgproto::Attached, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Caption, sem::Caption>::write(::orgproto::Caption* out, sem::Caption const& in) {
  proto_serde<::orgproto::Caption, sem::Org>::write(out, in);
  proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_text(), *((in.text).get()));
}

void proto_serde<::orgproto::CommandGroup, sem::CommandGroup>::write(::orgproto::CommandGroup* out, sem::CommandGroup const& in) {
  proto_serde<::orgproto::CommandGroup, sem::Stmt>::write(out, in);
  proto_serde<::orgproto::CommandGroup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Block, sem::Block>::write(::orgproto::Block* out, sem::Block const& in) {
  proto_serde<::orgproto::Block, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Quote, sem::Quote>::write(::orgproto::Quote* out, sem::Quote const& in) {
  proto_serde<::orgproto::Quote, sem::Org>::write(out, in);
  proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_text(), *((in.text).get()));
}

void proto_serde<::orgproto::Example, sem::Example>::write(::orgproto::Example* out, sem::Example const& in) {
  proto_serde<::orgproto::Example, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::CmdArguments, sem::CmdArguments>::write(::orgproto::CmdArguments* out, sem::CmdArguments const& in) {
  proto_serde<::orgproto::CmdArguments, sem::Org>::write(out, in);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::CmdArgument>, Vec<sem::SemIdT<sem::CmdArgument>>>::write(out->mutable_positional(), in.positional);
  proto_serde<::google::protobuf::Map<std::string, orgproto::CmdArgument>, UnorderedMap<Str, sem::SemIdT<sem::CmdArgument>>>::write(out->mutable_named(), in.named);
}

void proto_serde<::orgproto::CmdArgument, sem::CmdArgument>::write(::orgproto::CmdArgument* out, sem::CmdArgument const& in) {
  proto_serde<::orgproto::CmdArgument, sem::Org>::write(out, in);
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Export, sem::Export>::write(::orgproto::Export* out, sem::Export const& in) {
  proto_serde<::orgproto::Export, sem::Org>::write(out, in);
  out->set_format(static_cast<orgproto::Export_Format>(in.format));
  proto_serde<std::string, Str>::write(out->mutable_exporter(), in.exporter);
  proto_serde<orgproto::CmdArguments, sem::CmdArguments>::write(out->mutable_parameters(), *((in.parameters).get()));
  if (in.placement) {
    proto_serde<std::string, Str>::write(out->mutable_placement(), *in.placement);
  }
  proto_serde<std::string, Str>::write(out->mutable_content(), in.content);
}

void proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock>::write(::orgproto::AdmonitionBlock* out, sem::AdmonitionBlock const& in) {
  proto_serde<::orgproto::AdmonitionBlock, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::write(::orgproto::Code::Switch::LineStart* out, sem::Code::Switch::LineStart const& in) {
  out->set_start(in.start);
  out->set_extendlast(in.extendLast);
}

void proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::write(::orgproto::Code::Switch::CalloutFormat* out, sem::Code::Switch::CalloutFormat const& in) {
  proto_serde<std::string, Str>::write(out->mutable_format(), in.format);
}

void proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::write(::orgproto::Code::Switch::RemoveCallout* out, sem::Code::Switch::RemoveCallout const& in) {
  out->set_remove(in.remove);
}

void proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::write(::orgproto::Code::Switch::EmphasizeLine* out, sem::Code::Switch::EmphasizeLine const& in) {
  proto_serde<::google::protobuf::RepeatedField<::int32_t>, Vec<int>>::write(out->mutable_line(), in.line);
}

void proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::write(::orgproto::Code::Switch::Dedent* out, sem::Code::Switch::Dedent const& in) {
  out->set_value(in.value);
}

void proto_serde<::orgproto::Code::Switch, sem::Code::Switch>::write(::orgproto::Code::Switch* out, sem::Code::Switch const& in) {
  switch (in.data.index()) {
    case 0: proto_serde<orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart>::write(out->mutable_data()->mutable_linestart(), std::get<0>(in.data)); break;
    case 1: proto_serde<orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat>::write(out->mutable_data()->mutable_calloutformat(), std::get<1>(in.data)); break;
    case 2: proto_serde<orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout>::write(out->mutable_data()->mutable_removecallout(), std::get<2>(in.data)); break;
    case 3: proto_serde<orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine>::write(out->mutable_data()->mutable_emphasizeline(), std::get<3>(in.data)); break;
    case 4: proto_serde<orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent>::write(out->mutable_data()->mutable_dedent(), std::get<4>(in.data)); break;
  }
}

void proto_serde<::orgproto::Code, sem::Code>::write(::orgproto::Code* out, sem::Code const& in) {
  proto_serde<::orgproto::Code, sem::Org>::write(out, in);
  if (in.lang) {
    proto_serde<std::string, Str>::write(out->mutable_lang(), *in.lang);
  }
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Code::Switch>, Vec<sem::Code::Switch>>::write(out->mutable_switches(), in.switches);
  out->set_exports(static_cast<orgproto::Code_Exports>(in.exports));
  proto_serde<orgproto::CmdArguments, sem::CmdArguments>::write(out->mutable_parameters(), *((in.parameters).get()));
  out->set_cache(in.cache);
  out->set_eval(in.eval);
  out->set_noweb(in.noweb);
  out->set_hlines(in.hlines);
  out->set_tangle(in.tangle);
}

void proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat>::write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in) {
  out->set_mode(static_cast<orgproto::Time_Repeat_Mode>(in.mode));
  out->set_period(static_cast<orgproto::Time_Repeat_Period>(in.period));
  out->set_count(in.count);
}

void proto_serde<::orgproto::Time::Static, sem::Time::Static>::write(::orgproto::Time::Static* out, sem::Time::Static const& in) {
  if (in.repeat) {
    proto_serde<orgproto::Time::Repeat, sem::Time::Repeat>::write(out->mutable_repeat(), *in.repeat);
  }
  proto_serde<orgproto::UserTime, UserTime>::write(out->mutable_time(), in.time);
}

void proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic>::write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in) {
  proto_serde<std::string, Str>::write(out->mutable_expr(), in.expr);
}

void proto_serde<::orgproto::Time, sem::Time>::write(::orgproto::Time* out, sem::Time const& in) {
  proto_serde<::orgproto::Time, sem::Org>::write(out, in);
  out->set_isactive(in.isActive);
  switch (in.time.index()) {
    case 0: proto_serde<orgproto::Time::Static, sem::Time::Static>::write(out->mutable_time()->mutable_static_(), std::get<0>(in.time)); break;
    case 1: proto_serde<orgproto::Time::Dynamic, sem::Time::Dynamic>::write(out->mutable_time()->mutable_dynamic(), std::get<1>(in.time)); break;
  }
}

void proto_serde<::orgproto::TimeRange, sem::TimeRange>::write(::orgproto::TimeRange* out, sem::TimeRange const& in) {
  proto_serde<::orgproto::TimeRange, sem::Org>::write(out, in);
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_from(), *((in.from).get()));
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_to(), *((in.to).get()));
}

void proto_serde<::orgproto::Macro, sem::Macro>::write(::orgproto::Macro* out, sem::Macro const& in) {
  proto_serde<::orgproto::Macro, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_arguments(), in.arguments);
}

void proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param>::write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in) {
  if (in.key) {
    proto_serde<std::string, Str>::write(out->mutable_key(), *in.key);
  }
  proto_serde<std::string, Str>::write(out->mutable_value(), in.value);
}

void proto_serde<::orgproto::Symbol, sem::Symbol>::write(::orgproto::Symbol* out, sem::Symbol const& in) {
  proto_serde<::orgproto::Symbol, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::Symbol::Param>, Vec<sem::Symbol::Param>>::write(out->mutable_parameters(), in.parameters);
  proto_serde<::google::protobuf::RepeatedPtrField<orgproto::AnyNode>, Vec<sem::SemId>>::write(out->mutable_positional(), in.positional);
}

void proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog>::write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in) {
  if (in.desc) {
    proto_serde<orgproto::StmtList, sem::StmtList>::write(out->mutable_desc(), *((*in.desc).get()));
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
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
}

void proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in) {
  proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>::write(out, in);
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
}

void proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in) {
  proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>::write(out, in);
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  proto_serde<orgproto::Link, sem::Link>::write(out->mutable_from(), *((in.from).get()));
}

void proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in) {
  proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>::write(out, in);
  switch (in.range.index()) {
    case 0: proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((std::get<0>(in.range)).get())); break;
    case 1: proto_serde<orgproto::TimeRange, sem::TimeRange>::write(out->mutable_timerange(), *((std::get<1>(in.range)).get())); break;
  }
}

void proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State>::write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in) {
  proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::DescribedLog>::write(out, in);
  out->set_from(static_cast<orgproto::OrgBigIdentKind>(in.from));
  out->set_to(static_cast<orgproto::OrgBigIdentKind>(in.to));
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
}

void proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in) {
  proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>::write(out, in);
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_on(), *((in.on).get()));
  proto_serde<orgproto::HashTag, sem::HashTag>::write(out->mutable_tag(), *((in.tag).get()));
  out->set_added(in.added);
}

void proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog>::write(::orgproto::SubtreeLog* out, sem::SubtreeLog const& in) {
  proto_serde<::orgproto::SubtreeLog, sem::Org>::write(out, in);
  switch (in.log.index()) {
    case 0: proto_serde<orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority>::write(out->mutable_log()->mutable_priority(), std::get<0>(in.log)); break;
    case 1: proto_serde<orgproto::SubtreeLog::Note, sem::SubtreeLog::Note>::write(out->mutable_log()->mutable_note(), std::get<1>(in.log)); break;
    case 2: proto_serde<orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile>::write(out->mutable_log()->mutable_refile(), std::get<2>(in.log)); break;
    case 3: proto_serde<orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock>::write(out->mutable_log()->mutable_clock(), std::get<3>(in.log)); break;
    case 4: proto_serde<orgproto::SubtreeLog::State, sem::SubtreeLog::State>::write(out->mutable_log()->mutable_state(), std::get<4>(in.log)); break;
    case 5: proto_serde<orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag>::write(out->mutable_log()->mutable_tag(), std::get<5>(in.log)); break;
  }
}

void proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period>::write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in) {
  out->set_kind(static_cast<orgproto::Subtree_Period_Kind>(in.kind));
  switch (in.period.index()) {
    case 0: proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((std::get<0>(in.period)).get())); break;
    case 1: proto_serde<orgproto::TimeRange, sem::TimeRange>::write(out->mutable_timerange(), *((std::get<1>(in.period)).get())); break;
  }
}

void proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in) {
  out->set_isblocking(in.isBlocking);
}

void proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in) {
  proto_serde<std::string, Str>::write(out->mutable_latexclass(), in.latexClass);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_options(), in.options);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in) {
  proto_serde<std::string, Str>::write(out->mutable_header(), in.header);
}

void proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in) {
  proto_serde<std::string, Str>::write(out->mutable_compiler(), in.compiler);
}

void proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in) {
  out->set_isordered(in.isOrdered);
}

void proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in) {
  out->set_hours(in.hours);
  out->set_minutes(in.minutes);
}

void proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in) {
  out->set_level(static_cast<orgproto::Subtree_Property_Visibility_Level>(in.level));
}

void proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in) {
  proto_serde<std::string, Str>::write(out->mutable_backend(), in.backend);
  proto_serde<::google::protobuf::Map<std::string, std::string>, UnorderedMap<Str, Str>>::write(out->mutable_values(), in.values);
}

void proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in) {
  proto_serde<::google::protobuf::RepeatedPtrField<std::string>, Vec<Str>>::write(out->mutable_blockers(), in.blockers);
}

void proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in) {

}

void proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in) {
  proto_serde<orgproto::Time, sem::Time>::write(out->mutable_time(), *((in.time).get()));
}

void proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property>::write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in) {
  out->set_mainsetrule(static_cast<orgproto::Subtree_Property_SetMode>(in.mainSetRule));
  out->set_subsetrule(static_cast<orgproto::Subtree_Property_SetMode>(in.subSetRule));
  out->set_inheritancemode(static_cast<orgproto::Subtree_Property_InheritanceMode>(in.inheritanceMode));
  switch (in.data.index()) {
    case 0: proto_serde<orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking>::write(out->mutable_data()->mutable_nonblocking(), std::get<0>(in.data)); break;
    case 1: proto_serde<orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger>::write(out->mutable_data()->mutable_trigger(), std::get<1>(in.data)); break;
    case 2: proto_serde<orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin>::write(out->mutable_data()->mutable_origin(), std::get<2>(in.data)); break;
    case 3: proto_serde<orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass>::write(out->mutable_data()->mutable_exportlatexclass(), std::get<3>(in.data)); break;
    case 4: proto_serde<orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions>::write(out->mutable_data()->mutable_exportlatexclassoptions(), std::get<4>(in.data)); break;
    case 5: proto_serde<orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader>::write(out->mutable_data()->mutable_exportlatexheader(), std::get<5>(in.data)); break;
    case 6: proto_serde<orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler>::write(out->mutable_data()->mutable_exportlatexcompiler(), std::get<6>(in.data)); break;
    case 7: proto_serde<orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered>::write(out->mutable_data()->mutable_ordered(), std::get<7>(in.data)); break;
    case 8: proto_serde<orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort>::write(out->mutable_data()->mutable_effort(), std::get<8>(in.data)); break;
    case 9: proto_serde<orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility>::write(out->mutable_data()->mutable_visibility(), std::get<9>(in.data)); break;
    case 10: proto_serde<orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions>::write(out->mutable_data()->mutable_exportoptions(), std::get<10>(in.data)); break;
    case 11: proto_serde<orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker>::write(out->mutable_data()->mutable_blocker(), std::get<11>(in.data)); break;
    case 12: proto_serde<orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered>::write(out->mutable_data()->mutable_unnumbered(), std::get<12>(in.data)); break;
    case 13: proto_serde<orgproto::Subtree::Property::Created, sem::Subtree::Property::Created>::write(out->mutable_data()->mutable_created(), std::get<13>(in.data)); break;
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
  proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_title(), *((in.title).get()));
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

void proto_serde<::orgproto::LatexBody, sem::LatexBody>::write(::orgproto::LatexBody* out, sem::LatexBody const& in) {
  proto_serde<::orgproto::LatexBody, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::InlineMath, sem::InlineMath>::write(::orgproto::InlineMath* out, sem::InlineMath const& in) {
  proto_serde<::orgproto::InlineMath, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Leaf, sem::Leaf>::write(::orgproto::Leaf* out, sem::Leaf const& in) {
  proto_serde<::orgproto::Leaf, sem::Org>::write(out, in);
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Escaped, sem::Escaped>::write(::orgproto::Escaped* out, sem::Escaped const& in) {
  proto_serde<::orgproto::Escaped, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Escaped, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Newline, sem::Newline>::write(::orgproto::Newline* out, sem::Newline const& in) {
  proto_serde<::orgproto::Newline, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Newline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Space, sem::Space>::write(::orgproto::Space* out, sem::Space const& in) {
  proto_serde<::orgproto::Space, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Space, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Word, sem::Word>::write(::orgproto::Word* out, sem::Word const& in) {
  proto_serde<::orgproto::Word, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Word, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::AtMention, sem::AtMention>::write(::orgproto::AtMention* out, sem::AtMention const& in) {
  proto_serde<::orgproto::AtMention, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::AtMention, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::RawText, sem::RawText>::write(::orgproto::RawText* out, sem::RawText const& in) {
  proto_serde<::orgproto::RawText, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::RawText, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Punctuation, sem::Punctuation>::write(::orgproto::Punctuation* out, sem::Punctuation const& in) {
  proto_serde<::orgproto::Punctuation, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Punctuation, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Placeholder, sem::Placeholder>::write(::orgproto::Placeholder* out, sem::Placeholder const& in) {
  proto_serde<::orgproto::Placeholder, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::Placeholder, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::BigIdent, sem::BigIdent>::write(::orgproto::BigIdent* out, sem::BigIdent const& in) {
  proto_serde<::orgproto::BigIdent, sem::Leaf>::write(out, in);
  proto_serde<::orgproto::BigIdent, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Markup, sem::Markup>::write(::orgproto::Markup* out, sem::Markup const& in) {
  proto_serde<::orgproto::Markup, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Bold, sem::Bold>::write(::orgproto::Bold* out, sem::Bold const& in) {
  proto_serde<::orgproto::Bold, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Underline, sem::Underline>::write(::orgproto::Underline* out, sem::Underline const& in) {
  proto_serde<::orgproto::Underline, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Monospace, sem::Monospace>::write(::orgproto::Monospace* out, sem::Monospace const& in) {
  proto_serde<::orgproto::Monospace, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::MarkQuote, sem::MarkQuote>::write(::orgproto::MarkQuote* out, sem::MarkQuote const& in) {
  proto_serde<::orgproto::MarkQuote, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Verbatim, sem::Verbatim>::write(::orgproto::Verbatim* out, sem::Verbatim const& in) {
  proto_serde<::orgproto::Verbatim, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Italic, sem::Italic>::write(::orgproto::Italic* out, sem::Italic const& in) {
  proto_serde<::orgproto::Italic, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Strike, sem::Strike>::write(::orgproto::Strike* out, sem::Strike const& in) {
  proto_serde<::orgproto::Strike, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Par, sem::Par>::write(::orgproto::Par* out, sem::Par const& in) {
  proto_serde<::orgproto::Par, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::List, sem::List>::write(::orgproto::List* out, sem::List const& in) {
  proto_serde<::orgproto::List, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::ListItem, sem::ListItem>::write(::orgproto::ListItem* out, sem::ListItem const& in) {
  proto_serde<::orgproto::ListItem, sem::Org>::write(out, in);
  out->set_checkbox(static_cast<orgproto::ListItem_Checkbox>(in.checkbox));
  if (in.header) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_header(), *((*in.header).get()));
  }
}

void proto_serde<::orgproto::Link::Raw, sem::Link::Raw>::write(::orgproto::Link::Raw* out, sem::Link::Raw const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Id, sem::Link::Id>::write(::orgproto::Link::Id* out, sem::Link::Id const& in) {
  proto_serde<std::string, Str>::write(out->mutable_text(), in.text);
}

void proto_serde<::orgproto::Link::Person, sem::Link::Person>::write(::orgproto::Link::Person* out, sem::Link::Person const& in) {
  proto_serde<std::string, Str>::write(out->mutable_name(), in.name);
}

void proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote>::write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in) {
  proto_serde<std::string, Str>::write(out->mutable_target(), in.target);
}

void proto_serde<::orgproto::Link::File, sem::Link::File>::write(::orgproto::Link::File* out, sem::Link::File const& in) {
  proto_serde<std::string, Str>::write(out->mutable_file(), in.file);
}

void proto_serde<::orgproto::Link, sem::Link>::write(::orgproto::Link* out, sem::Link const& in) {
  proto_serde<::orgproto::Link, sem::Org>::write(out, in);
  if (in.description) {
    proto_serde<orgproto::Paragraph, sem::Paragraph>::write(out->mutable_description(), *((*in.description).get()));
  }
  switch (in.data.index()) {
    case 0: proto_serde<orgproto::Link::Raw, sem::Link::Raw>::write(out->mutable_data()->mutable_raw(), std::get<0>(in.data)); break;
    case 1: proto_serde<orgproto::Link::Id, sem::Link::Id>::write(out->mutable_data()->mutable_id(), std::get<1>(in.data)); break;
    case 2: proto_serde<orgproto::Link::Person, sem::Link::Person>::write(out->mutable_data()->mutable_person(), std::get<2>(in.data)); break;
    case 3: proto_serde<orgproto::Link::Footnote, sem::Link::Footnote>::write(out->mutable_data()->mutable_footnote(), std::get<3>(in.data)); break;
    case 4: proto_serde<orgproto::Link::File, sem::Link::File>::write(out->mutable_data()->mutable_file(), std::get<4>(in.data)); break;
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
  proto_serde<orgproto::DocumentOptions, sem::DocumentOptions>::write(out->mutable_options(), *((in.options).get()));
  if (in.exportFileName) {
    proto_serde<std::string, Str>::write(out->mutable_exportfilename(), *in.exportFileName);
  }
}

void proto_serde<::orgproto::ParseError, sem::ParseError>::write(::orgproto::ParseError* out, sem::ParseError const& in) {
  proto_serde<::orgproto::ParseError, sem::Org>::write(out, in);
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

void proto_serde<::orgproto::TextSeparator, sem::TextSeparator>::write(::orgproto::TextSeparator* out, sem::TextSeparator const& in) {
  proto_serde<::orgproto::TextSeparator, sem::Org>::write(out, in);
}

void proto_serde<::orgproto::Include::Example, sem::Include::Example>::write(::orgproto::Include::Example* out, sem::Include::Example const& in) {

}

void proto_serde<::orgproto::Include::Export, sem::Include::Export>::write(::orgproto::Include::Export* out, sem::Include::Export const& in) {

}

void proto_serde<::orgproto::Include::Src, sem::Include::Src>::write(::orgproto::Include::Src* out, sem::Include::Src const& in) {

}

void proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument>::write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in) {

}

void proto_serde<::orgproto::Include, sem::Include>::write(::orgproto::Include* out, sem::Include const& in) {
  proto_serde<::orgproto::Include, sem::Org>::write(out, in);
  switch (in.data.index()) {
    case 0: proto_serde<orgproto::Include::Example, sem::Include::Example>::write(out->mutable_data()->mutable_example(), std::get<0>(in.data)); break;
    case 1: proto_serde<orgproto::Include::Export, sem::Include::Export>::write(out->mutable_data()->mutable_export_(), std::get<1>(in.data)); break;
    case 2: proto_serde<orgproto::Include::Src, sem::Include::Src>::write(out->mutable_data()->mutable_src(), std::get<2>(in.data)); break;
    case 3: proto_serde<orgproto::Include::OrgDocument, sem::Include::OrgDocument>::write(out->mutable_data()->mutable_orgdocument(), std::get<3>(in.data)); break;
  }
}

void proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(::orgproto::DocumentOptions::DoExport* out, sem::DocumentOptions::DoExport const& in) {
  out->set_exporttoc(in.exportToc);
}

void proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(::orgproto::DocumentOptions::ExportFixed* out, sem::DocumentOptions::ExportFixed const& in) {
  out->set_exportlevels(in.exportLevels);
}

void proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions>::write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in) {
  proto_serde<::orgproto::DocumentOptions, sem::Org>::write(out, in);
  out->set_brokenlinks(static_cast<orgproto::DocumentOptions_BrokenLinks>(in.brokenLinks));
  out->set_initialvisibility(static_cast<orgproto::DocumentOptions_Visibility>(in.initialVisibility));
  switch (in.tocExport.index()) {
    case 0: proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(out->mutable_tocexport()->mutable_doexport(), std::get<0>(in.tocExport)); break;
    case 1: proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(out->mutable_tocexport()->mutable_exportfixed(), std::get<1>(in.tocExport)); break;
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
    case 0: proto_serde<orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport>::write(out->mutable_data()->mutable_doexport(), std::get<0>(in.data)); break;
    case 1: proto_serde<orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed>::write(out->mutable_data()->mutable_exportfixed(), std::get<1>(in.data)); break;
  }
}

void proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup>::write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in) {
  proto_serde<::orgproto::DocumentGroup, sem::Org>::write(out, in);
}

/* clang-format on */