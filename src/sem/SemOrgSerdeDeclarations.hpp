/* clang-format off */
#include <sem/SemOrgSerde.hpp>
#define EACH_ANY_NODE_PROTO_FIELD(__MAP) \
        __MAP(stmtlist, StmtList)  \
        __MAP(empty, Empty)  \
        __MAP(row, Row)  \
        __MAP(table, Table)  \
        __MAP(hashtag, HashTag)  \
        __MAP(footnote, Footnote)  \
        __MAP(completion, Completion)  \
        __MAP(paragraph, Paragraph)  \
        __MAP(center, Center)  \
        __MAP(caption, Caption)  \
        __MAP(commandgroup, CommandGroup)  \
        __MAP(quote, Quote)  \
        __MAP(example, Example)  \
        __MAP(cmdarguments, CmdArguments)  \
        __MAP(cmdargument, CmdArgument)  \
        __MAP(export_, Export)  \
        __MAP(admonitionblock, AdmonitionBlock)  \
        __MAP(code, Code)  \
        __MAP(time, Time)  \
        __MAP(timerange, TimeRange)  \
        __MAP(macro, Macro)  \
        __MAP(symbol, Symbol)  \
        __MAP(subtreelog, SubtreeLog)  \
        __MAP(subtree, Subtree)  \
        __MAP(inlinemath, InlineMath)  \
        __MAP(escaped, Escaped)  \
        __MAP(newline, Newline)  \
        __MAP(space, Space)  \
        __MAP(word, Word)  \
        __MAP(atmention, AtMention)  \
        __MAP(rawtext, RawText)  \
        __MAP(punctuation, Punctuation)  \
        __MAP(placeholder, Placeholder)  \
        __MAP(bigident, BigIdent)  \
        __MAP(bold, Bold)  \
        __MAP(underline, Underline)  \
        __MAP(monospace, Monospace)  \
        __MAP(markquote, MarkQuote)  \
        __MAP(verbatim, Verbatim)  \
        __MAP(italic, Italic)  \
        __MAP(strike, Strike)  \
        __MAP(par, Par)  \
        __MAP(list, List)  \
        __MAP(listitem, ListItem)  \
        __MAP(link, Link)  \
        __MAP(document, Document)  \
        __MAP(parseerror, ParseError)  \
        __MAP(filetarget, FileTarget)  \
        __MAP(textseparator, TextSeparator)  \
        __MAP(include, Include)  \
        __MAP(documentoptions, DocumentOptions)  \
        __MAP(documentgroup, DocumentGroup)  \

template <>
struct proto_serde<::orgproto::StmtList, sem::StmtList> {
  static void write(::orgproto::StmtList* out, sem::StmtList const& in);
  static void read(sem::ContextStore* context, ::orgproto::StmtList const& out, sem::StmtList& in);
};


template <>
struct proto_serde<::orgproto::Empty, sem::Empty> {
  static void write(::orgproto::Empty* out, sem::Empty const& in);
  static void read(sem::ContextStore* context, ::orgproto::Empty const& out, sem::Empty& in);
};


template <>
struct proto_serde<::orgproto::Row, sem::Row> {
  static void write(::orgproto::Row* out, sem::Row const& in);
  static void read(sem::ContextStore* context, ::orgproto::Row const& out, sem::Row& in);
};


template <>
struct proto_serde<::orgproto::Table, sem::Table> {
  static void write(::orgproto::Table* out, sem::Table const& in);
  static void read(sem::ContextStore* context, ::orgproto::Table const& out, sem::Table& in);
};


template <>
struct proto_serde<::orgproto::HashTag, sem::HashTag> {
  static void write(::orgproto::HashTag* out, sem::HashTag const& in);
  static void read(sem::ContextStore* context, ::orgproto::HashTag const& out, sem::HashTag& in);
};


template <>
struct proto_serde<::orgproto::Footnote, sem::Footnote> {
  static void write(::orgproto::Footnote* out, sem::Footnote const& in);
  static void read(sem::ContextStore* context, ::orgproto::Footnote const& out, sem::Footnote& in);
};


template <>
struct proto_serde<::orgproto::Completion, sem::Completion> {
  static void write(::orgproto::Completion* out, sem::Completion const& in);
  static void read(sem::ContextStore* context, ::orgproto::Completion const& out, sem::Completion& in);
};


template <>
struct proto_serde<::orgproto::Paragraph, sem::Paragraph> {
  static void write(::orgproto::Paragraph* out, sem::Paragraph const& in);
  static void read(sem::ContextStore* context, ::orgproto::Paragraph const& out, sem::Paragraph& in);
};


template <>
struct proto_serde<::orgproto::Center, sem::Center> {
  static void write(::orgproto::Center* out, sem::Center const& in);
  static void read(sem::ContextStore* context, ::orgproto::Center const& out, sem::Center& in);
};


template <>
struct proto_serde<::orgproto::Caption, sem::Caption> {
  static void write(::orgproto::Caption* out, sem::Caption const& in);
  static void read(sem::ContextStore* context, ::orgproto::Caption const& out, sem::Caption& in);
};


template <>
struct proto_serde<::orgproto::CommandGroup, sem::CommandGroup> {
  static void write(::orgproto::CommandGroup* out, sem::CommandGroup const& in);
  static void read(sem::ContextStore* context, ::orgproto::CommandGroup const& out, sem::CommandGroup& in);
};


template <>
struct proto_serde<::orgproto::Quote, sem::Quote> {
  static void write(::orgproto::Quote* out, sem::Quote const& in);
  static void read(sem::ContextStore* context, ::orgproto::Quote const& out, sem::Quote& in);
};


template <>
struct proto_serde<::orgproto::Example, sem::Example> {
  static void write(::orgproto::Example* out, sem::Example const& in);
  static void read(sem::ContextStore* context, ::orgproto::Example const& out, sem::Example& in);
};


template <>
struct proto_serde<::orgproto::CmdArguments, sem::CmdArguments> {
  static void write(::orgproto::CmdArguments* out, sem::CmdArguments const& in);
  static void read(sem::ContextStore* context, ::orgproto::CmdArguments const& out, sem::CmdArguments& in);
};


template <>
struct proto_serde<::orgproto::CmdArgument, sem::CmdArgument> {
  static void write(::orgproto::CmdArgument* out, sem::CmdArgument const& in);
  static void read(sem::ContextStore* context, ::orgproto::CmdArgument const& out, sem::CmdArgument& in);
};


template <>
struct proto_serde<::orgproto::Export, sem::Export> {
  static void write(::orgproto::Export* out, sem::Export const& in);
  static void read(sem::ContextStore* context, ::orgproto::Export const& out, sem::Export& in);
};


template <>
struct proto_serde<::orgproto::AdmonitionBlock, sem::AdmonitionBlock> {
  static void write(::orgproto::AdmonitionBlock* out, sem::AdmonitionBlock const& in);
  static void read(sem::ContextStore* context, ::orgproto::AdmonitionBlock const& out, sem::AdmonitionBlock& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::LineStart, sem::Code::Switch::LineStart> {
  static void write(::orgproto::Code::Switch::LineStart* out, sem::Code::Switch::LineStart const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch::LineStart const& out, sem::Code::Switch::LineStart& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::CalloutFormat, sem::Code::Switch::CalloutFormat> {
  static void write(::orgproto::Code::Switch::CalloutFormat* out, sem::Code::Switch::CalloutFormat const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch::CalloutFormat const& out, sem::Code::Switch::CalloutFormat& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::RemoveCallout, sem::Code::Switch::RemoveCallout> {
  static void write(::orgproto::Code::Switch::RemoveCallout* out, sem::Code::Switch::RemoveCallout const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch::RemoveCallout const& out, sem::Code::Switch::RemoveCallout& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::EmphasizeLine, sem::Code::Switch::EmphasizeLine> {
  static void write(::orgproto::Code::Switch::EmphasizeLine* out, sem::Code::Switch::EmphasizeLine const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch::EmphasizeLine const& out, sem::Code::Switch::EmphasizeLine& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch::Dedent, sem::Code::Switch::Dedent> {
  static void write(::orgproto::Code::Switch::Dedent* out, sem::Code::Switch::Dedent const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch::Dedent const& out, sem::Code::Switch::Dedent& in);
};


template <>
struct proto_serde<::orgproto::Code::Switch, sem::Code::Switch> {
  static void write(::orgproto::Code::Switch* out, sem::Code::Switch const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code::Switch const& out, sem::Code::Switch& in);
};


template <>
struct proto_serde<::orgproto::Code, sem::Code> {
  static void write(::orgproto::Code* out, sem::Code const& in);
  static void read(sem::ContextStore* context, ::orgproto::Code const& out, sem::Code& in);
};


template <>
struct proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat> {
  static void write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in);
  static void read(sem::ContextStore* context, ::orgproto::Time::Repeat const& out, sem::Time::Repeat& in);
};


template <>
struct proto_serde<::orgproto::Time::Static, sem::Time::Static> {
  static void write(::orgproto::Time::Static* out, sem::Time::Static const& in);
  static void read(sem::ContextStore* context, ::orgproto::Time::Static const& out, sem::Time::Static& in);
};


template <>
struct proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic> {
  static void write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in);
  static void read(sem::ContextStore* context, ::orgproto::Time::Dynamic const& out, sem::Time::Dynamic& in);
};


template <>
struct proto_serde<::orgproto::Time, sem::Time> {
  static void write(::orgproto::Time* out, sem::Time const& in);
  static void read(sem::ContextStore* context, ::orgproto::Time const& out, sem::Time& in);
};


template <>
struct proto_serde<::orgproto::TimeRange, sem::TimeRange> {
  static void write(::orgproto::TimeRange* out, sem::TimeRange const& in);
  static void read(sem::ContextStore* context, ::orgproto::TimeRange const& out, sem::TimeRange& in);
};


template <>
struct proto_serde<::orgproto::Macro, sem::Macro> {
  static void write(::orgproto::Macro* out, sem::Macro const& in);
  static void read(sem::ContextStore* context, ::orgproto::Macro const& out, sem::Macro& in);
};


template <>
struct proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param> {
  static void write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in);
  static void read(sem::ContextStore* context, ::orgproto::Symbol::Param const& out, sem::Symbol::Param& in);
};


template <>
struct proto_serde<::orgproto::Symbol, sem::Symbol> {
  static void write(::orgproto::Symbol* out, sem::Symbol const& in);
  static void read(sem::ContextStore* context, ::orgproto::Symbol const& out, sem::Symbol& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog> {
  static void write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::DescribedLog const& out, sem::SubtreeLog::DescribedLog& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority> {
  static void write(::orgproto::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::Priority const& out, sem::SubtreeLog::Priority& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note> {
  static void write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::Note const& out, sem::SubtreeLog::Note& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile> {
  static void write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::Refile const& out, sem::SubtreeLog::Refile& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock> {
  static void write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::Clock const& out, sem::SubtreeLog::Clock& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State> {
  static void write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::State const& out, sem::SubtreeLog::State& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag> {
  static void write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog::Tag const& out, sem::SubtreeLog::Tag& in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog> {
  static void write(::orgproto::SubtreeLog* out, sem::SubtreeLog const& in);
  static void read(sem::ContextStore* context, ::orgproto::SubtreeLog const& out, sem::SubtreeLog& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period> {
  static void write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Period const& out, sem::Subtree::Period& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking> {
  static void write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Nonblocking const& out, sem::Subtree::Property::Nonblocking& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger> {
  static void write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Trigger const& out, sem::Subtree::Property::Trigger& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin> {
  static void write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Origin const& out, sem::Subtree::Property::Origin& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass> {
  static void write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexClass const& out, sem::Subtree::Property::ExportLatexClass& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions> {
  static void write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexClassOptions const& out, sem::Subtree::Property::ExportLatexClassOptions& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader> {
  static void write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexHeader const& out, sem::Subtree::Property::ExportLatexHeader& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler> {
  static void write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportLatexCompiler const& out, sem::Subtree::Property::ExportLatexCompiler& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered> {
  static void write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Ordered const& out, sem::Subtree::Property::Ordered& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort> {
  static void write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Effort const& out, sem::Subtree::Property::Effort& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility> {
  static void write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Visibility const& out, sem::Subtree::Property::Visibility& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions> {
  static void write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::ExportOptions const& out, sem::Subtree::Property::ExportOptions& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker> {
  static void write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Blocker const& out, sem::Subtree::Property::Blocker& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered> {
  static void write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Unnumbered const& out, sem::Subtree::Property::Unnumbered& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created> {
  static void write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property::Created const& out, sem::Subtree::Property::Created& in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property> {
  static void write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree::Property const& out, sem::Subtree::Property& in);
};


template <>
struct proto_serde<::orgproto::Subtree, sem::Subtree> {
  static void write(::orgproto::Subtree* out, sem::Subtree const& in);
  static void read(sem::ContextStore* context, ::orgproto::Subtree const& out, sem::Subtree& in);
};


template <>
struct proto_serde<::orgproto::InlineMath, sem::InlineMath> {
  static void write(::orgproto::InlineMath* out, sem::InlineMath const& in);
  static void read(sem::ContextStore* context, ::orgproto::InlineMath const& out, sem::InlineMath& in);
};


template <>
struct proto_serde<::orgproto::Escaped, sem::Escaped> {
  static void write(::orgproto::Escaped* out, sem::Escaped const& in);
  static void read(sem::ContextStore* context, ::orgproto::Escaped const& out, sem::Escaped& in);
};


template <>
struct proto_serde<::orgproto::Newline, sem::Newline> {
  static void write(::orgproto::Newline* out, sem::Newline const& in);
  static void read(sem::ContextStore* context, ::orgproto::Newline const& out, sem::Newline& in);
};


template <>
struct proto_serde<::orgproto::Space, sem::Space> {
  static void write(::orgproto::Space* out, sem::Space const& in);
  static void read(sem::ContextStore* context, ::orgproto::Space const& out, sem::Space& in);
};


template <>
struct proto_serde<::orgproto::Word, sem::Word> {
  static void write(::orgproto::Word* out, sem::Word const& in);
  static void read(sem::ContextStore* context, ::orgproto::Word const& out, sem::Word& in);
};


template <>
struct proto_serde<::orgproto::AtMention, sem::AtMention> {
  static void write(::orgproto::AtMention* out, sem::AtMention const& in);
  static void read(sem::ContextStore* context, ::orgproto::AtMention const& out, sem::AtMention& in);
};


template <>
struct proto_serde<::orgproto::RawText, sem::RawText> {
  static void write(::orgproto::RawText* out, sem::RawText const& in);
  static void read(sem::ContextStore* context, ::orgproto::RawText const& out, sem::RawText& in);
};


template <>
struct proto_serde<::orgproto::Punctuation, sem::Punctuation> {
  static void write(::orgproto::Punctuation* out, sem::Punctuation const& in);
  static void read(sem::ContextStore* context, ::orgproto::Punctuation const& out, sem::Punctuation& in);
};


template <>
struct proto_serde<::orgproto::Placeholder, sem::Placeholder> {
  static void write(::orgproto::Placeholder* out, sem::Placeholder const& in);
  static void read(sem::ContextStore* context, ::orgproto::Placeholder const& out, sem::Placeholder& in);
};


template <>
struct proto_serde<::orgproto::BigIdent, sem::BigIdent> {
  static void write(::orgproto::BigIdent* out, sem::BigIdent const& in);
  static void read(sem::ContextStore* context, ::orgproto::BigIdent const& out, sem::BigIdent& in);
};


template <>
struct proto_serde<::orgproto::Bold, sem::Bold> {
  static void write(::orgproto::Bold* out, sem::Bold const& in);
  static void read(sem::ContextStore* context, ::orgproto::Bold const& out, sem::Bold& in);
};


template <>
struct proto_serde<::orgproto::Underline, sem::Underline> {
  static void write(::orgproto::Underline* out, sem::Underline const& in);
  static void read(sem::ContextStore* context, ::orgproto::Underline const& out, sem::Underline& in);
};


template <>
struct proto_serde<::orgproto::Monospace, sem::Monospace> {
  static void write(::orgproto::Monospace* out, sem::Monospace const& in);
  static void read(sem::ContextStore* context, ::orgproto::Monospace const& out, sem::Monospace& in);
};


template <>
struct proto_serde<::orgproto::MarkQuote, sem::MarkQuote> {
  static void write(::orgproto::MarkQuote* out, sem::MarkQuote const& in);
  static void read(sem::ContextStore* context, ::orgproto::MarkQuote const& out, sem::MarkQuote& in);
};


template <>
struct proto_serde<::orgproto::Verbatim, sem::Verbatim> {
  static void write(::orgproto::Verbatim* out, sem::Verbatim const& in);
  static void read(sem::ContextStore* context, ::orgproto::Verbatim const& out, sem::Verbatim& in);
};


template <>
struct proto_serde<::orgproto::Italic, sem::Italic> {
  static void write(::orgproto::Italic* out, sem::Italic const& in);
  static void read(sem::ContextStore* context, ::orgproto::Italic const& out, sem::Italic& in);
};


template <>
struct proto_serde<::orgproto::Strike, sem::Strike> {
  static void write(::orgproto::Strike* out, sem::Strike const& in);
  static void read(sem::ContextStore* context, ::orgproto::Strike const& out, sem::Strike& in);
};


template <>
struct proto_serde<::orgproto::Par, sem::Par> {
  static void write(::orgproto::Par* out, sem::Par const& in);
  static void read(sem::ContextStore* context, ::orgproto::Par const& out, sem::Par& in);
};


template <>
struct proto_serde<::orgproto::List, sem::List> {
  static void write(::orgproto::List* out, sem::List const& in);
  static void read(sem::ContextStore* context, ::orgproto::List const& out, sem::List& in);
};


template <>
struct proto_serde<::orgproto::ListItem, sem::ListItem> {
  static void write(::orgproto::ListItem* out, sem::ListItem const& in);
  static void read(sem::ContextStore* context, ::orgproto::ListItem const& out, sem::ListItem& in);
};


template <>
struct proto_serde<::orgproto::Link::Raw, sem::Link::Raw> {
  static void write(::orgproto::Link::Raw* out, sem::Link::Raw const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link::Raw const& out, sem::Link::Raw& in);
};


template <>
struct proto_serde<::orgproto::Link::Id, sem::Link::Id> {
  static void write(::orgproto::Link::Id* out, sem::Link::Id const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link::Id const& out, sem::Link::Id& in);
};


template <>
struct proto_serde<::orgproto::Link::Person, sem::Link::Person> {
  static void write(::orgproto::Link::Person* out, sem::Link::Person const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link::Person const& out, sem::Link::Person& in);
};


template <>
struct proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote> {
  static void write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link::Footnote const& out, sem::Link::Footnote& in);
};


template <>
struct proto_serde<::orgproto::Link::File, sem::Link::File> {
  static void write(::orgproto::Link::File* out, sem::Link::File const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link::File const& out, sem::Link::File& in);
};


template <>
struct proto_serde<::orgproto::Link, sem::Link> {
  static void write(::orgproto::Link* out, sem::Link const& in);
  static void read(sem::ContextStore* context, ::orgproto::Link const& out, sem::Link& in);
};


template <>
struct proto_serde<::orgproto::Document, sem::Document> {
  static void write(::orgproto::Document* out, sem::Document const& in);
  static void read(sem::ContextStore* context, ::orgproto::Document const& out, sem::Document& in);
};


template <>
struct proto_serde<::orgproto::ParseError, sem::ParseError> {
  static void write(::orgproto::ParseError* out, sem::ParseError const& in);
  static void read(sem::ContextStore* context, ::orgproto::ParseError const& out, sem::ParseError& in);
};


template <>
struct proto_serde<::orgproto::FileTarget, sem::FileTarget> {
  static void write(::orgproto::FileTarget* out, sem::FileTarget const& in);
  static void read(sem::ContextStore* context, ::orgproto::FileTarget const& out, sem::FileTarget& in);
};


template <>
struct proto_serde<::orgproto::TextSeparator, sem::TextSeparator> {
  static void write(::orgproto::TextSeparator* out, sem::TextSeparator const& in);
  static void read(sem::ContextStore* context, ::orgproto::TextSeparator const& out, sem::TextSeparator& in);
};


template <>
struct proto_serde<::orgproto::Include::Example, sem::Include::Example> {
  static void write(::orgproto::Include::Example* out, sem::Include::Example const& in);
  static void read(sem::ContextStore* context, ::orgproto::Include::Example const& out, sem::Include::Example& in);
};


template <>
struct proto_serde<::orgproto::Include::Export, sem::Include::Export> {
  static void write(::orgproto::Include::Export* out, sem::Include::Export const& in);
  static void read(sem::ContextStore* context, ::orgproto::Include::Export const& out, sem::Include::Export& in);
};


template <>
struct proto_serde<::orgproto::Include::Src, sem::Include::Src> {
  static void write(::orgproto::Include::Src* out, sem::Include::Src const& in);
  static void read(sem::ContextStore* context, ::orgproto::Include::Src const& out, sem::Include::Src& in);
};


template <>
struct proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument> {
  static void write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in);
  static void read(sem::ContextStore* context, ::orgproto::Include::OrgDocument const& out, sem::Include::OrgDocument& in);
};


template <>
struct proto_serde<::orgproto::Include, sem::Include> {
  static void write(::orgproto::Include* out, sem::Include const& in);
  static void read(sem::ContextStore* context, ::orgproto::Include const& out, sem::Include& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::DoExport, sem::DocumentOptions::DoExport> {
  static void write(::orgproto::DocumentOptions::DoExport* out, sem::DocumentOptions::DoExport const& in);
  static void read(sem::ContextStore* context, ::orgproto::DocumentOptions::DoExport const& out, sem::DocumentOptions::DoExport& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportFixed, sem::DocumentOptions::ExportFixed> {
  static void write(::orgproto::DocumentOptions::ExportFixed* out, sem::DocumentOptions::ExportFixed const& in);
  static void read(sem::ContextStore* context, ::orgproto::DocumentOptions::ExportFixed const& out, sem::DocumentOptions::ExportFixed& in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions> {
  static void write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in);
  static void read(sem::ContextStore* context, ::orgproto::DocumentOptions const& out, sem::DocumentOptions& in);
};


template <>
struct proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup> {
  static void write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in);
  static void read(sem::ContextStore* context, ::orgproto::DocumentGroup const& out, sem::DocumentGroup& in);
};


/* clang-format on */