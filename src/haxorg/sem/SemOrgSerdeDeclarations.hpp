/* clang-format off */
#pragma once
#include <haxorg/sem/SemOrgSerde.hpp>
#define EACH_ANY_NODE_PROTO_FIELD(__MAP) \
        __MAP(kCmdargument, cmdargument, CmdArgument)  \
        __MAP(kCmdargumentlist, cmdargumentlist, CmdArgumentList)  \
        __MAP(kCmdarguments, cmdarguments, CmdArguments)  \
        __MAP(kErroritem, erroritem, ErrorItem)  \
        __MAP(kErrorgroup, errorgroup, ErrorGroup)  \
        __MAP(kStmtlist, stmtlist, StmtList)  \
        __MAP(kEmpty, empty, Empty)  \
        __MAP(kCmdcaption, cmdcaption, CmdCaption)  \
        __MAP(kCmdname, cmdname, CmdName)  \
        __MAP(kCmdcustomargs, cmdcustomargs, CmdCustomArgs)  \
        __MAP(kCmdcustomraw, cmdcustomraw, CmdCustomRaw)  \
        __MAP(kCmdcustomtext, cmdcustomtext, CmdCustomText)  \
        __MAP(kCmdresults, cmdresults, CmdResults)  \
        __MAP(kCmdtblfm, cmdtblfm, CmdTblfm)  \
        __MAP(kHashtag, hashtag, HashTag)  \
        __MAP(kFootnote, footnote, Footnote)  \
        __MAP(kTime, time, Time)  \
        __MAP(kTimerange, timerange, TimeRange)  \
        __MAP(kMacro, macro, Macro)  \
        __MAP(kSymbol, symbol, Symbol)  \
        __MAP(kEscaped, escaped, Escaped)  \
        __MAP(kNewline, newline, Newline)  \
        __MAP(kSpace, space, Space)  \
        __MAP(kWord, word, Word)  \
        __MAP(kAtmention, atmention, AtMention)  \
        __MAP(kRawtext, rawtext, RawText)  \
        __MAP(kPunctuation, punctuation, Punctuation)  \
        __MAP(kPlaceholder, placeholder, Placeholder)  \
        __MAP(kBigident, bigident, BigIdent)  \
        __MAP(kRadiotarget, radiotarget, RadioTarget)  \
        __MAP(kTexttarget, texttarget, TextTarget)  \
        __MAP(kBold, bold, Bold)  \
        __MAP(kUnderline, underline, Underline)  \
        __MAP(kMonospace, monospace, Monospace)  \
        __MAP(kMarkquote, markquote, MarkQuote)  \
        __MAP(kVerbatim, verbatim, Verbatim)  \
        __MAP(kItalic, italic, Italic)  \
        __MAP(kStrike, strike, Strike)  \
        __MAP(kPar, par, Par)  \
        __MAP(kLatex, latex, Latex)  \
        __MAP(kLink, link, Link)  \
        __MAP(kBlockcenter, blockcenter, BlockCenter)  \
        __MAP(kBlockquote, blockquote, BlockQuote)  \
        __MAP(kBlockcomment, blockcomment, BlockComment)  \
        __MAP(kBlockverse, blockverse, BlockVerse)  \
        __MAP(kBlockexample, blockexample, BlockExample)  \
        __MAP(kBlockexport, blockexport, BlockExport)  \
        __MAP(kBlockadmonition, blockadmonition, BlockAdmonition)  \
        __MAP(kBlockcode, blockcode, BlockCode)  \
        __MAP(kSubtreelog, subtreelog, SubtreeLog)  \
        __MAP(kSubtree, subtree, Subtree)  \
        __MAP(kSubtreecompletion, subtreecompletion, SubtreeCompletion)  \
        __MAP(kCell, cell, Cell)  \
        __MAP(kRow, row, Row)  \
        __MAP(kTable, table, Table)  \
        __MAP(kParagraph, paragraph, Paragraph)  \
        __MAP(kAnnotatedparagraph, annotatedparagraph, AnnotatedParagraph)  \
        __MAP(kColonexample, colonexample, ColonExample)  \
        __MAP(kCmdattr, cmdattr, CmdAttr)  \
        __MAP(kCall, call, Call)  \
        __MAP(kList, list, List)  \
        __MAP(kListitem, listitem, ListItem)  \
        __MAP(kDocumentoptions, documentoptions, DocumentOptions)  \
        __MAP(kDocument, document, Document)  \
        __MAP(kFiletarget, filetarget, FileTarget)  \
        __MAP(kTextseparator, textseparator, TextSeparator)  \
        __MAP(kInclude, include, Include)  \
        __MAP(kDocumentgroup, documentgroup, DocumentGroup)  \

template <>
struct proto_serde<::orgproto::CmdArgument, CmdArgument> {
  static void write(::orgproto::CmdArgument* out, CmdArgument const& in);
  static void read(::orgproto::CmdArgument const& out, proto_write_accessor<CmdArgument> in);
};


template <>
struct proto_serde<::orgproto::CmdArgumentList, CmdArgumentList> {
  static void write(::orgproto::CmdArgumentList* out, CmdArgumentList const& in);
  static void read(::orgproto::CmdArgumentList const& out, proto_write_accessor<CmdArgumentList> in);
};


template <>
struct proto_serde<::orgproto::CmdArguments, CmdArguments> {
  static void write(::orgproto::CmdArguments* out, CmdArguments const& in);
  static void read(::orgproto::CmdArguments const& out, proto_write_accessor<CmdArguments> in);
};


template <>
struct proto_serde<::orgproto::ErrorItem, ErrorItem> {
  static void write(::orgproto::ErrorItem* out, ErrorItem const& in);
  static void read(::orgproto::ErrorItem const& out, proto_write_accessor<ErrorItem> in);
};


template <>
struct proto_serde<::orgproto::ErrorGroup, ErrorGroup> {
  static void write(::orgproto::ErrorGroup* out, ErrorGroup const& in);
  static void read(::orgproto::ErrorGroup const& out, proto_write_accessor<ErrorGroup> in);
};


template <>
struct proto_serde<::orgproto::StmtList, StmtList> {
  static void write(::orgproto::StmtList* out, StmtList const& in);
  static void read(::orgproto::StmtList const& out, proto_write_accessor<StmtList> in);
};


template <>
struct proto_serde<::orgproto::Empty, Empty> {
  static void write(::orgproto::Empty* out, Empty const& in);
  static void read(::orgproto::Empty const& out, proto_write_accessor<Empty> in);
};


template <>
struct proto_serde<::orgproto::CmdCaption, CmdCaption> {
  static void write(::orgproto::CmdCaption* out, CmdCaption const& in);
  static void read(::orgproto::CmdCaption const& out, proto_write_accessor<CmdCaption> in);
};


template <>
struct proto_serde<::orgproto::CmdName, CmdName> {
  static void write(::orgproto::CmdName* out, CmdName const& in);
  static void read(::orgproto::CmdName const& out, proto_write_accessor<CmdName> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomArgs, CmdCustomArgs> {
  static void write(::orgproto::CmdCustomArgs* out, CmdCustomArgs const& in);
  static void read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<CmdCustomArgs> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomRaw, CmdCustomRaw> {
  static void write(::orgproto::CmdCustomRaw* out, CmdCustomRaw const& in);
  static void read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<CmdCustomRaw> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomText, CmdCustomText> {
  static void write(::orgproto::CmdCustomText* out, CmdCustomText const& in);
  static void read(::orgproto::CmdCustomText const& out, proto_write_accessor<CmdCustomText> in);
};


template <>
struct proto_serde<::orgproto::CmdResults, CmdResults> {
  static void write(::orgproto::CmdResults* out, CmdResults const& in);
  static void read(::orgproto::CmdResults const& out, proto_write_accessor<CmdResults> in);
};


template <>
struct proto_serde<::orgproto::CmdTblfm, CmdTblfm> {
  static void write(::orgproto::CmdTblfm* out, CmdTblfm const& in);
  static void read(::orgproto::CmdTblfm const& out, proto_write_accessor<CmdTblfm> in);
};


template <>
struct proto_serde<::orgproto::HashTag, HashTag> {
  static void write(::orgproto::HashTag* out, HashTag const& in);
  static void read(::orgproto::HashTag const& out, proto_write_accessor<HashTag> in);
};


template <>
struct proto_serde<::orgproto::Footnote, Footnote> {
  static void write(::orgproto::Footnote* out, Footnote const& in);
  static void read(::orgproto::Footnote const& out, proto_write_accessor<Footnote> in);
};


template <>
struct proto_serde<::orgproto::sem::Time::Repeat, sem::Time::Repeat> {
  static void write(::orgproto::sem::Time::Repeat* out, sem::Time::Repeat const& in);
  static void read(::orgproto::sem::Time::Repeat const& out, proto_write_accessor<sem::Time::Repeat> in);
};


template <>
struct proto_serde<::orgproto::sem::Time::Static, sem::Time::Static> {
  static void write(::orgproto::sem::Time::Static* out, sem::Time::Static const& in);
  static void read(::orgproto::sem::Time::Static const& out, proto_write_accessor<sem::Time::Static> in);
};


template <>
struct proto_serde<::orgproto::sem::Time::Dynamic, sem::Time::Dynamic> {
  static void write(::orgproto::sem::Time::Dynamic* out, sem::Time::Dynamic const& in);
  static void read(::orgproto::sem::Time::Dynamic const& out, proto_write_accessor<sem::Time::Dynamic> in);
};


template <>
struct proto_serde<::orgproto::Time, Time> {
  static void write(::orgproto::Time* out, Time const& in);
  static void read(::orgproto::Time const& out, proto_write_accessor<Time> in);
};


template <>
struct proto_serde<::orgproto::TimeRange, TimeRange> {
  static void write(::orgproto::TimeRange* out, TimeRange const& in);
  static void read(::orgproto::TimeRange const& out, proto_write_accessor<TimeRange> in);
};


template <>
struct proto_serde<::orgproto::Macro, Macro> {
  static void write(::orgproto::Macro* out, Macro const& in);
  static void read(::orgproto::Macro const& out, proto_write_accessor<Macro> in);
};


template <>
struct proto_serde<::orgproto::sem::Symbol::Param, sem::Symbol::Param> {
  static void write(::orgproto::sem::Symbol::Param* out, sem::Symbol::Param const& in);
  static void read(::orgproto::sem::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in);
};


template <>
struct proto_serde<::orgproto::Symbol, Symbol> {
  static void write(::orgproto::Symbol* out, Symbol const& in);
  static void read(::orgproto::Symbol const& out, proto_write_accessor<Symbol> in);
};


template <>
struct proto_serde<::orgproto::Escaped, Escaped> {
  static void write(::orgproto::Escaped* out, Escaped const& in);
  static void read(::orgproto::Escaped const& out, proto_write_accessor<Escaped> in);
};


template <>
struct proto_serde<::orgproto::Newline, Newline> {
  static void write(::orgproto::Newline* out, Newline const& in);
  static void read(::orgproto::Newline const& out, proto_write_accessor<Newline> in);
};


template <>
struct proto_serde<::orgproto::Space, Space> {
  static void write(::orgproto::Space* out, Space const& in);
  static void read(::orgproto::Space const& out, proto_write_accessor<Space> in);
};


template <>
struct proto_serde<::orgproto::Word, Word> {
  static void write(::orgproto::Word* out, Word const& in);
  static void read(::orgproto::Word const& out, proto_write_accessor<Word> in);
};


template <>
struct proto_serde<::orgproto::AtMention, AtMention> {
  static void write(::orgproto::AtMention* out, AtMention const& in);
  static void read(::orgproto::AtMention const& out, proto_write_accessor<AtMention> in);
};


template <>
struct proto_serde<::orgproto::RawText, RawText> {
  static void write(::orgproto::RawText* out, RawText const& in);
  static void read(::orgproto::RawText const& out, proto_write_accessor<RawText> in);
};


template <>
struct proto_serde<::orgproto::Punctuation, Punctuation> {
  static void write(::orgproto::Punctuation* out, Punctuation const& in);
  static void read(::orgproto::Punctuation const& out, proto_write_accessor<Punctuation> in);
};


template <>
struct proto_serde<::orgproto::Placeholder, Placeholder> {
  static void write(::orgproto::Placeholder* out, Placeholder const& in);
  static void read(::orgproto::Placeholder const& out, proto_write_accessor<Placeholder> in);
};


template <>
struct proto_serde<::orgproto::BigIdent, BigIdent> {
  static void write(::orgproto::BigIdent* out, BigIdent const& in);
  static void read(::orgproto::BigIdent const& out, proto_write_accessor<BigIdent> in);
};


template <>
struct proto_serde<::orgproto::RadioTarget, RadioTarget> {
  static void write(::orgproto::RadioTarget* out, RadioTarget const& in);
  static void read(::orgproto::RadioTarget const& out, proto_write_accessor<RadioTarget> in);
};


template <>
struct proto_serde<::orgproto::TextTarget, TextTarget> {
  static void write(::orgproto::TextTarget* out, TextTarget const& in);
  static void read(::orgproto::TextTarget const& out, proto_write_accessor<TextTarget> in);
};


template <>
struct proto_serde<::orgproto::Bold, Bold> {
  static void write(::orgproto::Bold* out, Bold const& in);
  static void read(::orgproto::Bold const& out, proto_write_accessor<Bold> in);
};


template <>
struct proto_serde<::orgproto::Underline, Underline> {
  static void write(::orgproto::Underline* out, Underline const& in);
  static void read(::orgproto::Underline const& out, proto_write_accessor<Underline> in);
};


template <>
struct proto_serde<::orgproto::Monospace, Monospace> {
  static void write(::orgproto::Monospace* out, Monospace const& in);
  static void read(::orgproto::Monospace const& out, proto_write_accessor<Monospace> in);
};


template <>
struct proto_serde<::orgproto::MarkQuote, MarkQuote> {
  static void write(::orgproto::MarkQuote* out, MarkQuote const& in);
  static void read(::orgproto::MarkQuote const& out, proto_write_accessor<MarkQuote> in);
};


template <>
struct proto_serde<::orgproto::Verbatim, Verbatim> {
  static void write(::orgproto::Verbatim* out, Verbatim const& in);
  static void read(::orgproto::Verbatim const& out, proto_write_accessor<Verbatim> in);
};


template <>
struct proto_serde<::orgproto::Italic, Italic> {
  static void write(::orgproto::Italic* out, Italic const& in);
  static void read(::orgproto::Italic const& out, proto_write_accessor<Italic> in);
};


template <>
struct proto_serde<::orgproto::Strike, Strike> {
  static void write(::orgproto::Strike* out, Strike const& in);
  static void read(::orgproto::Strike const& out, proto_write_accessor<Strike> in);
};


template <>
struct proto_serde<::orgproto::Par, Par> {
  static void write(::orgproto::Par* out, Par const& in);
  static void read(::orgproto::Par const& out, proto_write_accessor<Par> in);
};


template <>
struct proto_serde<::orgproto::Latex, Latex> {
  static void write(::orgproto::Latex* out, Latex const& in);
  static void read(::orgproto::Latex const& out, proto_write_accessor<Latex> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Raw, sem::Link::Raw> {
  static void write(::orgproto::sem::Link::Raw* out, sem::Link::Raw const& in);
  static void read(::orgproto::sem::Link::Raw const& out, proto_write_accessor<sem::Link::Raw> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Id, sem::Link::Id> {
  static void write(::orgproto::sem::Link::Id* out, sem::Link::Id const& in);
  static void read(::orgproto::sem::Link::Id const& out, proto_write_accessor<sem::Link::Id> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Person, sem::Link::Person> {
  static void write(::orgproto::sem::Link::Person* out, sem::Link::Person const& in);
  static void read(::orgproto::sem::Link::Person const& out, proto_write_accessor<sem::Link::Person> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::UserProtocol, sem::Link::UserProtocol> {
  static void write(::orgproto::sem::Link::UserProtocol* out, sem::Link::UserProtocol const& in);
  static void read(::orgproto::sem::Link::UserProtocol const& out, proto_write_accessor<sem::Link::UserProtocol> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Internal, sem::Link::Internal> {
  static void write(::orgproto::sem::Link::Internal* out, sem::Link::Internal const& in);
  static void read(::orgproto::sem::Link::Internal const& out, proto_write_accessor<sem::Link::Internal> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Footnote, sem::Link::Footnote> {
  static void write(::orgproto::sem::Link::Footnote* out, sem::Link::Footnote const& in);
  static void read(::orgproto::sem::Link::Footnote const& out, proto_write_accessor<sem::Link::Footnote> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::File, sem::Link::File> {
  static void write(::orgproto::sem::Link::File* out, sem::Link::File const& in);
  static void read(::orgproto::sem::Link::File const& out, proto_write_accessor<sem::Link::File> in);
};


template <>
struct proto_serde<::orgproto::sem::Link::Attachment, sem::Link::Attachment> {
  static void write(::orgproto::sem::Link::Attachment* out, sem::Link::Attachment const& in);
  static void read(::orgproto::sem::Link::Attachment const& out, proto_write_accessor<sem::Link::Attachment> in);
};


template <>
struct proto_serde<::orgproto::Link, Link> {
  static void write(::orgproto::Link* out, Link const& in);
  static void read(::orgproto::Link const& out, proto_write_accessor<Link> in);
};


template <>
struct proto_serde<::orgproto::BlockCenter, BlockCenter> {
  static void write(::orgproto::BlockCenter* out, BlockCenter const& in);
  static void read(::orgproto::BlockCenter const& out, proto_write_accessor<BlockCenter> in);
};


template <>
struct proto_serde<::orgproto::BlockQuote, BlockQuote> {
  static void write(::orgproto::BlockQuote* out, BlockQuote const& in);
  static void read(::orgproto::BlockQuote const& out, proto_write_accessor<BlockQuote> in);
};


template <>
struct proto_serde<::orgproto::BlockComment, BlockComment> {
  static void write(::orgproto::BlockComment* out, BlockComment const& in);
  static void read(::orgproto::BlockComment const& out, proto_write_accessor<BlockComment> in);
};


template <>
struct proto_serde<::orgproto::BlockVerse, BlockVerse> {
  static void write(::orgproto::BlockVerse* out, BlockVerse const& in);
  static void read(::orgproto::BlockVerse const& out, proto_write_accessor<BlockVerse> in);
};


template <>
struct proto_serde<::orgproto::BlockExample, BlockExample> {
  static void write(::orgproto::BlockExample* out, BlockExample const& in);
  static void read(::orgproto::BlockExample const& out, proto_write_accessor<BlockExample> in);
};


template <>
struct proto_serde<::orgproto::BlockExport, BlockExport> {
  static void write(::orgproto::BlockExport* out, BlockExport const& in);
  static void read(::orgproto::BlockExport const& out, proto_write_accessor<BlockExport> in);
};


template <>
struct proto_serde<::orgproto::BlockAdmonition, BlockAdmonition> {
  static void write(::orgproto::BlockAdmonition* out, BlockAdmonition const& in);
  static void read(::orgproto::BlockAdmonition const& out, proto_write_accessor<BlockAdmonition> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw> {
  static void write(::orgproto::sem::BlockCode::Line::Part::Raw* out, sem::BlockCode::Line::Part::Raw const& in);
  static void read(::orgproto::sem::BlockCode::Line::Part::Raw const& out, proto_write_accessor<sem::BlockCode::Line::Part::Raw> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout> {
  static void write(::orgproto::sem::BlockCode::Line::Part::Callout* out, sem::BlockCode::Line::Part::Callout const& in);
  static void read(::orgproto::sem::BlockCode::Line::Part::Callout const& out, proto_write_accessor<sem::BlockCode::Line::Part::Callout> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle> {
  static void write(::orgproto::sem::BlockCode::Line::Part::Tangle* out, sem::BlockCode::Line::Part::Tangle const& in);
  static void read(::orgproto::sem::BlockCode::Line::Part::Tangle const& out, proto_write_accessor<sem::BlockCode::Line::Part::Tangle> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Line::Part, sem::BlockCode::Line::Part> {
  static void write(::orgproto::sem::BlockCode::Line::Part* out, sem::BlockCode::Line::Part const& in);
  static void read(::orgproto::sem::BlockCode::Line::Part const& out, proto_write_accessor<sem::BlockCode::Line::Part> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Line, sem::BlockCode::Line> {
  static void write(::orgproto::sem::BlockCode::Line* out, sem::BlockCode::Line const& in);
  static void read(::orgproto::sem::BlockCode::Line const& out, proto_write_accessor<sem::BlockCode::Line> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart> {
  static void write(::orgproto::sem::BlockCode::Switch::LineStart* out, sem::BlockCode::Switch::LineStart const& in);
  static void read(::orgproto::sem::BlockCode::Switch::LineStart const& out, proto_write_accessor<sem::BlockCode::Switch::LineStart> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat> {
  static void write(::orgproto::sem::BlockCode::Switch::CalloutFormat* out, sem::BlockCode::Switch::CalloutFormat const& in);
  static void read(::orgproto::sem::BlockCode::Switch::CalloutFormat const& out, proto_write_accessor<sem::BlockCode::Switch::CalloutFormat> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout> {
  static void write(::orgproto::sem::BlockCode::Switch::RemoveCallout* out, sem::BlockCode::Switch::RemoveCallout const& in);
  static void read(::orgproto::sem::BlockCode::Switch::RemoveCallout const& out, proto_write_accessor<sem::BlockCode::Switch::RemoveCallout> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine> {
  static void write(::orgproto::sem::BlockCode::Switch::EmphasizeLine* out, sem::BlockCode::Switch::EmphasizeLine const& in);
  static void read(::orgproto::sem::BlockCode::Switch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCode::Switch::EmphasizeLine> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent> {
  static void write(::orgproto::sem::BlockCode::Switch::Dedent* out, sem::BlockCode::Switch::Dedent const& in);
  static void read(::orgproto::sem::BlockCode::Switch::Dedent const& out, proto_write_accessor<sem::BlockCode::Switch::Dedent> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::Switch, sem::BlockCode::Switch> {
  static void write(::orgproto::sem::BlockCode::Switch* out, sem::BlockCode::Switch const& in);
  static void read(::orgproto::sem::BlockCode::Switch const& out, proto_write_accessor<sem::BlockCode::Switch> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None> {
  static void write(::orgproto::sem::BlockCode::EvalResult::None* out, sem::BlockCode::EvalResult::None const& in);
  static void read(::orgproto::sem::BlockCode::EvalResult::None const& out, proto_write_accessor<sem::BlockCode::EvalResult::None> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue> {
  static void write(::orgproto::sem::BlockCode::EvalResult::OrgValue* out, sem::BlockCode::EvalResult::OrgValue const& in);
  static void read(::orgproto::sem::BlockCode::EvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCode::EvalResult::OrgValue> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File> {
  static void write(::orgproto::sem::BlockCode::EvalResult::File* out, sem::BlockCode::EvalResult::File const& in);
  static void read(::orgproto::sem::BlockCode::EvalResult::File const& out, proto_write_accessor<sem::BlockCode::EvalResult::File> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw> {
  static void write(::orgproto::sem::BlockCode::EvalResult::Raw* out, sem::BlockCode::EvalResult::Raw const& in);
  static void read(::orgproto::sem::BlockCode::EvalResult::Raw const& out, proto_write_accessor<sem::BlockCode::EvalResult::Raw> in);
};


template <>
struct proto_serde<::orgproto::sem::BlockCode::EvalResult, sem::BlockCode::EvalResult> {
  static void write(::orgproto::sem::BlockCode::EvalResult* out, sem::BlockCode::EvalResult const& in);
  static void read(::orgproto::sem::BlockCode::EvalResult const& out, proto_write_accessor<sem::BlockCode::EvalResult> in);
};


template <>
struct proto_serde<::orgproto::BlockCode, BlockCode> {
  static void write(::orgproto::BlockCode* out, BlockCode const& in);
  static void read(::orgproto::BlockCode const& out, proto_write_accessor<BlockCode> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog> {
  static void write(::orgproto::sem::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in);
  static void read(::orgproto::sem::SubtreeLog::DescribedLog const& out, proto_write_accessor<sem::SubtreeLog::DescribedLog> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Priority, sem::SubtreeLog::Priority> {
  static void write(::orgproto::sem::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in);
  static void read(::orgproto::sem::SubtreeLog::Priority const& out, proto_write_accessor<sem::SubtreeLog::Priority> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Note, sem::SubtreeLog::Note> {
  static void write(::orgproto::sem::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in);
  static void read(::orgproto::sem::SubtreeLog::Note const& out, proto_write_accessor<sem::SubtreeLog::Note> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Refile, sem::SubtreeLog::Refile> {
  static void write(::orgproto::sem::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in);
  static void read(::orgproto::sem::SubtreeLog::Refile const& out, proto_write_accessor<sem::SubtreeLog::Refile> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Clock, sem::SubtreeLog::Clock> {
  static void write(::orgproto::sem::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in);
  static void read(::orgproto::sem::SubtreeLog::Clock const& out, proto_write_accessor<sem::SubtreeLog::Clock> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::State, sem::SubtreeLog::State> {
  static void write(::orgproto::sem::SubtreeLog::State* out, sem::SubtreeLog::State const& in);
  static void read(::orgproto::sem::SubtreeLog::State const& out, proto_write_accessor<sem::SubtreeLog::State> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Tag, sem::SubtreeLog::Tag> {
  static void write(::orgproto::sem::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in);
  static void read(::orgproto::sem::SubtreeLog::Tag const& out, proto_write_accessor<sem::SubtreeLog::Tag> in);
};


template <>
struct proto_serde<::orgproto::sem::SubtreeLog::Unknown, sem::SubtreeLog::Unknown> {
  static void write(::orgproto::sem::SubtreeLog::Unknown* out, sem::SubtreeLog::Unknown const& in);
  static void read(::orgproto::sem::SubtreeLog::Unknown const& out, proto_write_accessor<sem::SubtreeLog::Unknown> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog, SubtreeLog> {
  static void write(::orgproto::SubtreeLog* out, SubtreeLog const& in);
  static void read(::orgproto::SubtreeLog const& out, proto_write_accessor<SubtreeLog> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Period, sem::Subtree::Period> {
  static void write(::orgproto::sem::Subtree::Period* out, sem::Subtree::Period const& in);
  static void read(::orgproto::sem::Subtree::Period const& out, proto_write_accessor<sem::Subtree::Period> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking> {
  static void write(::orgproto::sem::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in);
  static void read(::orgproto::sem::Subtree::Property::Nonblocking const& out, proto_write_accessor<sem::Subtree::Property::Nonblocking> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Trigger, sem::Subtree::Property::Trigger> {
  static void write(::orgproto::sem::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in);
  static void read(::orgproto::sem::Subtree::Property::Trigger const& out, proto_write_accessor<sem::Subtree::Property::Trigger> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Origin, sem::Subtree::Property::Origin> {
  static void write(::orgproto::sem::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in);
  static void read(::orgproto::sem::Subtree::Property::Origin const& out, proto_write_accessor<sem::Subtree::Property::Origin> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass> {
  static void write(::orgproto::sem::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in);
  static void read(::orgproto::sem::Subtree::Property::ExportLatexClass const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClass> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions> {
  static void write(::orgproto::sem::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in);
  static void read(::orgproto::sem::Subtree::Property::ExportLatexClassOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClassOptions> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader> {
  static void write(::orgproto::sem::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in);
  static void read(::orgproto::sem::Subtree::Property::ExportLatexHeader const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexHeader> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler> {
  static void write(::orgproto::sem::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in);
  static void read(::orgproto::sem::Subtree::Property::ExportLatexCompiler const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexCompiler> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Ordered, sem::Subtree::Property::Ordered> {
  static void write(::orgproto::sem::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in);
  static void read(::orgproto::sem::Subtree::Property::Ordered const& out, proto_write_accessor<sem::Subtree::Property::Ordered> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Effort, sem::Subtree::Property::Effort> {
  static void write(::orgproto::sem::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in);
  static void read(::orgproto::sem::Subtree::Property::Effort const& out, proto_write_accessor<sem::Subtree::Property::Effort> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Visibility, sem::Subtree::Property::Visibility> {
  static void write(::orgproto::sem::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in);
  static void read(::orgproto::sem::Subtree::Property::Visibility const& out, proto_write_accessor<sem::Subtree::Property::Visibility> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions> {
  static void write(::orgproto::sem::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in);
  static void read(::orgproto::sem::Subtree::Property::ExportOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportOptions> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Blocker, sem::Subtree::Property::Blocker> {
  static void write(::orgproto::sem::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in);
  static void read(::orgproto::sem::Subtree::Property::Blocker const& out, proto_write_accessor<sem::Subtree::Property::Blocker> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered> {
  static void write(::orgproto::sem::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in);
  static void read(::orgproto::sem::Subtree::Property::Unnumbered const& out, proto_write_accessor<sem::Subtree::Property::Unnumbered> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::Created, sem::Subtree::Property::Created> {
  static void write(::orgproto::sem::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in);
  static void read(::orgproto::sem::Subtree::Property::Created const& out, proto_write_accessor<sem::Subtree::Property::Created> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs> {
  static void write(::orgproto::sem::Subtree::Property::CustomArgs* out, sem::Subtree::Property::CustomArgs const& in);
  static void read(::orgproto::sem::Subtree::Property::CustomArgs const& out, proto_write_accessor<sem::Subtree::Property::CustomArgs> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw> {
  static void write(::orgproto::sem::Subtree::Property::CustomRaw* out, sem::Subtree::Property::CustomRaw const& in);
  static void read(::orgproto::sem::Subtree::Property::CustomRaw const& out, proto_write_accessor<sem::Subtree::Property::CustomRaw> in);
};


template <>
struct proto_serde<::orgproto::sem::Subtree::Property, sem::Subtree::Property> {
  static void write(::orgproto::sem::Subtree::Property* out, sem::Subtree::Property const& in);
  static void read(::orgproto::sem::Subtree::Property const& out, proto_write_accessor<sem::Subtree::Property> in);
};


template <>
struct proto_serde<::orgproto::Subtree, Subtree> {
  static void write(::orgproto::Subtree* out, Subtree const& in);
  static void read(::orgproto::Subtree const& out, proto_write_accessor<Subtree> in);
};


template <>
struct proto_serde<::orgproto::SubtreeCompletion, SubtreeCompletion> {
  static void write(::orgproto::SubtreeCompletion* out, SubtreeCompletion const& in);
  static void read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<SubtreeCompletion> in);
};


template <>
struct proto_serde<::orgproto::Cell, Cell> {
  static void write(::orgproto::Cell* out, Cell const& in);
  static void read(::orgproto::Cell const& out, proto_write_accessor<Cell> in);
};


template <>
struct proto_serde<::orgproto::Row, Row> {
  static void write(::orgproto::Row* out, Row const& in);
  static void read(::orgproto::Row const& out, proto_write_accessor<Row> in);
};


template <>
struct proto_serde<::orgproto::Table, Table> {
  static void write(::orgproto::Table* out, Table const& in);
  static void read(::orgproto::Table const& out, proto_write_accessor<Table> in);
};


template <>
struct proto_serde<::orgproto::Paragraph, Paragraph> {
  static void write(::orgproto::Paragraph* out, Paragraph const& in);
  static void read(::orgproto::Paragraph const& out, proto_write_accessor<Paragraph> in);
};


template <>
struct proto_serde<::orgproto::sem::AnnotatedParagraph::None, sem::AnnotatedParagraph::None> {
  static void write(::orgproto::sem::AnnotatedParagraph::None* out, sem::AnnotatedParagraph::None const& in);
  static void read(::orgproto::sem::AnnotatedParagraph::None const& out, proto_write_accessor<sem::AnnotatedParagraph::None> in);
};


template <>
struct proto_serde<::orgproto::sem::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote> {
  static void write(::orgproto::sem::AnnotatedParagraph::Footnote* out, sem::AnnotatedParagraph::Footnote const& in);
  static void read(::orgproto::sem::AnnotatedParagraph::Footnote const& out, proto_write_accessor<sem::AnnotatedParagraph::Footnote> in);
};


template <>
struct proto_serde<::orgproto::sem::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition> {
  static void write(::orgproto::sem::AnnotatedParagraph::Admonition* out, sem::AnnotatedParagraph::Admonition const& in);
  static void read(::orgproto::sem::AnnotatedParagraph::Admonition const& out, proto_write_accessor<sem::AnnotatedParagraph::Admonition> in);
};


template <>
struct proto_serde<::orgproto::sem::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp> {
  static void write(::orgproto::sem::AnnotatedParagraph::Timestamp* out, sem::AnnotatedParagraph::Timestamp const& in);
  static void read(::orgproto::sem::AnnotatedParagraph::Timestamp const& out, proto_write_accessor<sem::AnnotatedParagraph::Timestamp> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph, AnnotatedParagraph> {
  static void write(::orgproto::AnnotatedParagraph* out, AnnotatedParagraph const& in);
  static void read(::orgproto::AnnotatedParagraph const& out, proto_write_accessor<AnnotatedParagraph> in);
};


template <>
struct proto_serde<::orgproto::ColonExample, ColonExample> {
  static void write(::orgproto::ColonExample* out, ColonExample const& in);
  static void read(::orgproto::ColonExample const& out, proto_write_accessor<ColonExample> in);
};


template <>
struct proto_serde<::orgproto::CmdAttr, CmdAttr> {
  static void write(::orgproto::CmdAttr* out, CmdAttr const& in);
  static void read(::orgproto::CmdAttr const& out, proto_write_accessor<CmdAttr> in);
};


template <>
struct proto_serde<::orgproto::Call, Call> {
  static void write(::orgproto::Call* out, Call const& in);
  static void read(::orgproto::Call const& out, proto_write_accessor<Call> in);
};


template <>
struct proto_serde<::orgproto::List, List> {
  static void write(::orgproto::List* out, List const& in);
  static void read(::orgproto::List const& out, proto_write_accessor<List> in);
};


template <>
struct proto_serde<::orgproto::ListItem, ListItem> {
  static void write(::orgproto::ListItem* out, ListItem const& in);
  static void read(::orgproto::ListItem const& out, proto_write_accessor<ListItem> in);
};


template <>
struct proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport> {
  static void write(::orgproto::sem::DocumentOptions::ExportConfig::TaskExport* out, sem::DocumentOptions::ExportConfig::TaskExport const& in);
  static void read(::orgproto::sem::DocumentOptions::ExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::TaskExport> in);
};


template <>
struct proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport> {
  static void write(::orgproto::sem::DocumentOptions::ExportConfig::DoExport* out, sem::DocumentOptions::ExportConfig::DoExport const& in);
  static void read(::orgproto::sem::DocumentOptions::ExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::DoExport> in);
};


template <>
struct proto_serde<::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed> {
  static void write(::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed* out, sem::DocumentOptions::ExportConfig::ExportFixed const& in);
  static void read(::orgproto::sem::DocumentOptions::ExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::ExportFixed> in);
};


template <>
struct proto_serde<::orgproto::sem::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig> {
  static void write(::orgproto::sem::DocumentOptions::ExportConfig* out, sem::DocumentOptions::ExportConfig const& in);
  static void read(::orgproto::sem::DocumentOptions::ExportConfig const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions, DocumentOptions> {
  static void write(::orgproto::DocumentOptions* out, DocumentOptions const& in);
  static void read(::orgproto::DocumentOptions const& out, proto_write_accessor<DocumentOptions> in);
};


template <>
struct proto_serde<::orgproto::Document, Document> {
  static void write(::orgproto::Document* out, Document const& in);
  static void read(::orgproto::Document const& out, proto_write_accessor<Document> in);
};


template <>
struct proto_serde<::orgproto::FileTarget, FileTarget> {
  static void write(::orgproto::FileTarget* out, FileTarget const& in);
  static void read(::orgproto::FileTarget const& out, proto_write_accessor<FileTarget> in);
};


template <>
struct proto_serde<::orgproto::TextSeparator, TextSeparator> {
  static void write(::orgproto::TextSeparator* out, TextSeparator const& in);
  static void read(::orgproto::TextSeparator const& out, proto_write_accessor<TextSeparator> in);
};


template <>
struct proto_serde<::orgproto::sem::Include::Example, sem::Include::Example> {
  static void write(::orgproto::sem::Include::Example* out, sem::Include::Example const& in);
  static void read(::orgproto::sem::Include::Example const& out, proto_write_accessor<sem::Include::Example> in);
};


template <>
struct proto_serde<::orgproto::sem::Include::Export, sem::Include::Export> {
  static void write(::orgproto::sem::Include::Export* out, sem::Include::Export const& in);
  static void read(::orgproto::sem::Include::Export const& out, proto_write_accessor<sem::Include::Export> in);
};


template <>
struct proto_serde<::orgproto::sem::Include::Src, sem::Include::Src> {
  static void write(::orgproto::sem::Include::Src* out, sem::Include::Src const& in);
  static void read(::orgproto::sem::Include::Src const& out, proto_write_accessor<sem::Include::Src> in);
};


template <>
struct proto_serde<::orgproto::sem::Include::OrgDocument, sem::Include::OrgDocument> {
  static void write(::orgproto::sem::Include::OrgDocument* out, sem::Include::OrgDocument const& in);
  static void read(::orgproto::sem::Include::OrgDocument const& out, proto_write_accessor<sem::Include::OrgDocument> in);
};


template <>
struct proto_serde<::orgproto::Include, Include> {
  static void write(::orgproto::Include* out, Include const& in);
  static void read(::orgproto::Include const& out, proto_write_accessor<Include> in);
};


template <>
struct proto_serde<::orgproto::DocumentGroup, DocumentGroup> {
  static void write(::orgproto::DocumentGroup* out, DocumentGroup const& in);
  static void read(::orgproto::DocumentGroup const& out, proto_write_accessor<DocumentGroup> in);
};


/* clang-format on */