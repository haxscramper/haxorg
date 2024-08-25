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
struct proto_serde<::orgproto::CmdArgument, sem::CmdArgument> {
  static void write(::orgproto::CmdArgument* out, sem::CmdArgument const& in);
  static void read(::orgproto::CmdArgument const& out, proto_write_accessor<sem::CmdArgument> in);
};


template <>
struct proto_serde<::orgproto::CmdArgumentList, sem::CmdArgumentList> {
  static void write(::orgproto::CmdArgumentList* out, sem::CmdArgumentList const& in);
  static void read(::orgproto::CmdArgumentList const& out, proto_write_accessor<sem::CmdArgumentList> in);
};


template <>
struct proto_serde<::orgproto::CmdArguments, sem::CmdArguments> {
  static void write(::orgproto::CmdArguments* out, sem::CmdArguments const& in);
  static void read(::orgproto::CmdArguments const& out, proto_write_accessor<sem::CmdArguments> in);
};


template <>
struct proto_serde<::orgproto::ErrorItem, sem::ErrorItem> {
  static void write(::orgproto::ErrorItem* out, sem::ErrorItem const& in);
  static void read(::orgproto::ErrorItem const& out, proto_write_accessor<sem::ErrorItem> in);
};


template <>
struct proto_serde<::orgproto::ErrorGroup, sem::ErrorGroup> {
  static void write(::orgproto::ErrorGroup* out, sem::ErrorGroup const& in);
  static void read(::orgproto::ErrorGroup const& out, proto_write_accessor<sem::ErrorGroup> in);
};


template <>
struct proto_serde<::orgproto::StmtList, sem::StmtList> {
  static void write(::orgproto::StmtList* out, sem::StmtList const& in);
  static void read(::orgproto::StmtList const& out, proto_write_accessor<sem::StmtList> in);
};


template <>
struct proto_serde<::orgproto::Empty, sem::Empty> {
  static void write(::orgproto::Empty* out, sem::Empty const& in);
  static void read(::orgproto::Empty const& out, proto_write_accessor<sem::Empty> in);
};


template <>
struct proto_serde<::orgproto::CmdCaption, sem::CmdCaption> {
  static void write(::orgproto::CmdCaption* out, sem::CmdCaption const& in);
  static void read(::orgproto::CmdCaption const& out, proto_write_accessor<sem::CmdCaption> in);
};


template <>
struct proto_serde<::orgproto::CmdName, sem::CmdName> {
  static void write(::orgproto::CmdName* out, sem::CmdName const& in);
  static void read(::orgproto::CmdName const& out, proto_write_accessor<sem::CmdName> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomArgs, sem::CmdCustomArgs> {
  static void write(::orgproto::CmdCustomArgs* out, sem::CmdCustomArgs const& in);
  static void read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<sem::CmdCustomArgs> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomRaw, sem::CmdCustomRaw> {
  static void write(::orgproto::CmdCustomRaw* out, sem::CmdCustomRaw const& in);
  static void read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<sem::CmdCustomRaw> in);
};


template <>
struct proto_serde<::orgproto::CmdCustomText, sem::CmdCustomText> {
  static void write(::orgproto::CmdCustomText* out, sem::CmdCustomText const& in);
  static void read(::orgproto::CmdCustomText const& out, proto_write_accessor<sem::CmdCustomText> in);
};


template <>
struct proto_serde<::orgproto::CmdResults, sem::CmdResults> {
  static void write(::orgproto::CmdResults* out, sem::CmdResults const& in);
  static void read(::orgproto::CmdResults const& out, proto_write_accessor<sem::CmdResults> in);
};


template <>
struct proto_serde<::orgproto::CmdTblfm, sem::CmdTblfm> {
  static void write(::orgproto::CmdTblfm* out, sem::CmdTblfm const& in);
  static void read(::orgproto::CmdTblfm const& out, proto_write_accessor<sem::CmdTblfm> in);
};


template <>
struct proto_serde<::orgproto::HashTag, sem::HashTag> {
  static void write(::orgproto::HashTag* out, sem::HashTag const& in);
  static void read(::orgproto::HashTag const& out, proto_write_accessor<sem::HashTag> in);
};


template <>
struct proto_serde<::orgproto::Footnote, sem::Footnote> {
  static void write(::orgproto::Footnote* out, sem::Footnote const& in);
  static void read(::orgproto::Footnote const& out, proto_write_accessor<sem::Footnote> in);
};


template <>
struct proto_serde<::orgproto::Time::Repeat, sem::Time::Repeat> {
  static void write(::orgproto::Time::Repeat* out, sem::Time::Repeat const& in);
  static void read(::orgproto::Time::Repeat const& out, proto_write_accessor<sem::Time::Repeat> in);
};


template <>
struct proto_serde<::orgproto::Time::Static, sem::Time::Static> {
  static void write(::orgproto::Time::Static* out, sem::Time::Static const& in);
  static void read(::orgproto::Time::Static const& out, proto_write_accessor<sem::Time::Static> in);
};


template <>
struct proto_serde<::orgproto::Time::Dynamic, sem::Time::Dynamic> {
  static void write(::orgproto::Time::Dynamic* out, sem::Time::Dynamic const& in);
  static void read(::orgproto::Time::Dynamic const& out, proto_write_accessor<sem::Time::Dynamic> in);
};


template <>
struct proto_serde<::orgproto::Time, sem::Time> {
  static void write(::orgproto::Time* out, sem::Time const& in);
  static void read(::orgproto::Time const& out, proto_write_accessor<sem::Time> in);
};


template <>
struct proto_serde<::orgproto::TimeRange, sem::TimeRange> {
  static void write(::orgproto::TimeRange* out, sem::TimeRange const& in);
  static void read(::orgproto::TimeRange const& out, proto_write_accessor<sem::TimeRange> in);
};


template <>
struct proto_serde<::orgproto::Macro, sem::Macro> {
  static void write(::orgproto::Macro* out, sem::Macro const& in);
  static void read(::orgproto::Macro const& out, proto_write_accessor<sem::Macro> in);
};


template <>
struct proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param> {
  static void write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in);
  static void read(::orgproto::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in);
};


template <>
struct proto_serde<::orgproto::Symbol, sem::Symbol> {
  static void write(::orgproto::Symbol* out, sem::Symbol const& in);
  static void read(::orgproto::Symbol const& out, proto_write_accessor<sem::Symbol> in);
};


template <>
struct proto_serde<::orgproto::Escaped, sem::Escaped> {
  static void write(::orgproto::Escaped* out, sem::Escaped const& in);
  static void read(::orgproto::Escaped const& out, proto_write_accessor<sem::Escaped> in);
};


template <>
struct proto_serde<::orgproto::Newline, sem::Newline> {
  static void write(::orgproto::Newline* out, sem::Newline const& in);
  static void read(::orgproto::Newline const& out, proto_write_accessor<sem::Newline> in);
};


template <>
struct proto_serde<::orgproto::Space, sem::Space> {
  static void write(::orgproto::Space* out, sem::Space const& in);
  static void read(::orgproto::Space const& out, proto_write_accessor<sem::Space> in);
};


template <>
struct proto_serde<::orgproto::Word, sem::Word> {
  static void write(::orgproto::Word* out, sem::Word const& in);
  static void read(::orgproto::Word const& out, proto_write_accessor<sem::Word> in);
};


template <>
struct proto_serde<::orgproto::AtMention, sem::AtMention> {
  static void write(::orgproto::AtMention* out, sem::AtMention const& in);
  static void read(::orgproto::AtMention const& out, proto_write_accessor<sem::AtMention> in);
};


template <>
struct proto_serde<::orgproto::RawText, sem::RawText> {
  static void write(::orgproto::RawText* out, sem::RawText const& in);
  static void read(::orgproto::RawText const& out, proto_write_accessor<sem::RawText> in);
};


template <>
struct proto_serde<::orgproto::Punctuation, sem::Punctuation> {
  static void write(::orgproto::Punctuation* out, sem::Punctuation const& in);
  static void read(::orgproto::Punctuation const& out, proto_write_accessor<sem::Punctuation> in);
};


template <>
struct proto_serde<::orgproto::Placeholder, sem::Placeholder> {
  static void write(::orgproto::Placeholder* out, sem::Placeholder const& in);
  static void read(::orgproto::Placeholder const& out, proto_write_accessor<sem::Placeholder> in);
};


template <>
struct proto_serde<::orgproto::BigIdent, sem::BigIdent> {
  static void write(::orgproto::BigIdent* out, sem::BigIdent const& in);
  static void read(::orgproto::BigIdent const& out, proto_write_accessor<sem::BigIdent> in);
};


template <>
struct proto_serde<::orgproto::RadioTarget, sem::RadioTarget> {
  static void write(::orgproto::RadioTarget* out, sem::RadioTarget const& in);
  static void read(::orgproto::RadioTarget const& out, proto_write_accessor<sem::RadioTarget> in);
};


template <>
struct proto_serde<::orgproto::TextTarget, sem::TextTarget> {
  static void write(::orgproto::TextTarget* out, sem::TextTarget const& in);
  static void read(::orgproto::TextTarget const& out, proto_write_accessor<sem::TextTarget> in);
};


template <>
struct proto_serde<::orgproto::Bold, sem::Bold> {
  static void write(::orgproto::Bold* out, sem::Bold const& in);
  static void read(::orgproto::Bold const& out, proto_write_accessor<sem::Bold> in);
};


template <>
struct proto_serde<::orgproto::Underline, sem::Underline> {
  static void write(::orgproto::Underline* out, sem::Underline const& in);
  static void read(::orgproto::Underline const& out, proto_write_accessor<sem::Underline> in);
};


template <>
struct proto_serde<::orgproto::Monospace, sem::Monospace> {
  static void write(::orgproto::Monospace* out, sem::Monospace const& in);
  static void read(::orgproto::Monospace const& out, proto_write_accessor<sem::Monospace> in);
};


template <>
struct proto_serde<::orgproto::MarkQuote, sem::MarkQuote> {
  static void write(::orgproto::MarkQuote* out, sem::MarkQuote const& in);
  static void read(::orgproto::MarkQuote const& out, proto_write_accessor<sem::MarkQuote> in);
};


template <>
struct proto_serde<::orgproto::Verbatim, sem::Verbatim> {
  static void write(::orgproto::Verbatim* out, sem::Verbatim const& in);
  static void read(::orgproto::Verbatim const& out, proto_write_accessor<sem::Verbatim> in);
};


template <>
struct proto_serde<::orgproto::Italic, sem::Italic> {
  static void write(::orgproto::Italic* out, sem::Italic const& in);
  static void read(::orgproto::Italic const& out, proto_write_accessor<sem::Italic> in);
};


template <>
struct proto_serde<::orgproto::Strike, sem::Strike> {
  static void write(::orgproto::Strike* out, sem::Strike const& in);
  static void read(::orgproto::Strike const& out, proto_write_accessor<sem::Strike> in);
};


template <>
struct proto_serde<::orgproto::Par, sem::Par> {
  static void write(::orgproto::Par* out, sem::Par const& in);
  static void read(::orgproto::Par const& out, proto_write_accessor<sem::Par> in);
};


template <>
struct proto_serde<::orgproto::Latex, sem::Latex> {
  static void write(::orgproto::Latex* out, sem::Latex const& in);
  static void read(::orgproto::Latex const& out, proto_write_accessor<sem::Latex> in);
};


template <>
struct proto_serde<::orgproto::Link::Raw, sem::Link::Raw> {
  static void write(::orgproto::Link::Raw* out, sem::Link::Raw const& in);
  static void read(::orgproto::Link::Raw const& out, proto_write_accessor<sem::Link::Raw> in);
};


template <>
struct proto_serde<::orgproto::Link::Id, sem::Link::Id> {
  static void write(::orgproto::Link::Id* out, sem::Link::Id const& in);
  static void read(::orgproto::Link::Id const& out, proto_write_accessor<sem::Link::Id> in);
};


template <>
struct proto_serde<::orgproto::Link::Person, sem::Link::Person> {
  static void write(::orgproto::Link::Person* out, sem::Link::Person const& in);
  static void read(::orgproto::Link::Person const& out, proto_write_accessor<sem::Link::Person> in);
};


template <>
struct proto_serde<::orgproto::Link::UserProtocol, sem::Link::UserProtocol> {
  static void write(::orgproto::Link::UserProtocol* out, sem::Link::UserProtocol const& in);
  static void read(::orgproto::Link::UserProtocol const& out, proto_write_accessor<sem::Link::UserProtocol> in);
};


template <>
struct proto_serde<::orgproto::Link::Internal, sem::Link::Internal> {
  static void write(::orgproto::Link::Internal* out, sem::Link::Internal const& in);
  static void read(::orgproto::Link::Internal const& out, proto_write_accessor<sem::Link::Internal> in);
};


template <>
struct proto_serde<::orgproto::Link::Footnote, sem::Link::Footnote> {
  static void write(::orgproto::Link::Footnote* out, sem::Link::Footnote const& in);
  static void read(::orgproto::Link::Footnote const& out, proto_write_accessor<sem::Link::Footnote> in);
};


template <>
struct proto_serde<::orgproto::Link::File, sem::Link::File> {
  static void write(::orgproto::Link::File* out, sem::Link::File const& in);
  static void read(::orgproto::Link::File const& out, proto_write_accessor<sem::Link::File> in);
};


template <>
struct proto_serde<::orgproto::Link::Attachment, sem::Link::Attachment> {
  static void write(::orgproto::Link::Attachment* out, sem::Link::Attachment const& in);
  static void read(::orgproto::Link::Attachment const& out, proto_write_accessor<sem::Link::Attachment> in);
};


template <>
struct proto_serde<::orgproto::Link, sem::Link> {
  static void write(::orgproto::Link* out, sem::Link const& in);
  static void read(::orgproto::Link const& out, proto_write_accessor<sem::Link> in);
};


template <>
struct proto_serde<::orgproto::BlockCenter, sem::BlockCenter> {
  static void write(::orgproto::BlockCenter* out, sem::BlockCenter const& in);
  static void read(::orgproto::BlockCenter const& out, proto_write_accessor<sem::BlockCenter> in);
};


template <>
struct proto_serde<::orgproto::BlockQuote, sem::BlockQuote> {
  static void write(::orgproto::BlockQuote* out, sem::BlockQuote const& in);
  static void read(::orgproto::BlockQuote const& out, proto_write_accessor<sem::BlockQuote> in);
};


template <>
struct proto_serde<::orgproto::BlockComment, sem::BlockComment> {
  static void write(::orgproto::BlockComment* out, sem::BlockComment const& in);
  static void read(::orgproto::BlockComment const& out, proto_write_accessor<sem::BlockComment> in);
};


template <>
struct proto_serde<::orgproto::BlockVerse, sem::BlockVerse> {
  static void write(::orgproto::BlockVerse* out, sem::BlockVerse const& in);
  static void read(::orgproto::BlockVerse const& out, proto_write_accessor<sem::BlockVerse> in);
};


template <>
struct proto_serde<::orgproto::BlockExample, sem::BlockExample> {
  static void write(::orgproto::BlockExample* out, sem::BlockExample const& in);
  static void read(::orgproto::BlockExample const& out, proto_write_accessor<sem::BlockExample> in);
};


template <>
struct proto_serde<::orgproto::BlockExport, sem::BlockExport> {
  static void write(::orgproto::BlockExport* out, sem::BlockExport const& in);
  static void read(::orgproto::BlockExport const& out, proto_write_accessor<sem::BlockExport> in);
};


template <>
struct proto_serde<::orgproto::BlockAdmonition, sem::BlockAdmonition> {
  static void write(::orgproto::BlockAdmonition* out, sem::BlockAdmonition const& in);
  static void read(::orgproto::BlockAdmonition const& out, proto_write_accessor<sem::BlockAdmonition> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Line::Part::Raw, sem::BlockCode::Line::Part::Raw> {
  static void write(::orgproto::BlockCode::Line::Part::Raw* out, sem::BlockCode::Line::Part::Raw const& in);
  static void read(::orgproto::BlockCode::Line::Part::Raw const& out, proto_write_accessor<sem::BlockCode::Line::Part::Raw> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Line::Part::Callout, sem::BlockCode::Line::Part::Callout> {
  static void write(::orgproto::BlockCode::Line::Part::Callout* out, sem::BlockCode::Line::Part::Callout const& in);
  static void read(::orgproto::BlockCode::Line::Part::Callout const& out, proto_write_accessor<sem::BlockCode::Line::Part::Callout> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Line::Part::Tangle, sem::BlockCode::Line::Part::Tangle> {
  static void write(::orgproto::BlockCode::Line::Part::Tangle* out, sem::BlockCode::Line::Part::Tangle const& in);
  static void read(::orgproto::BlockCode::Line::Part::Tangle const& out, proto_write_accessor<sem::BlockCode::Line::Part::Tangle> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Line::Part, sem::BlockCode::Line::Part> {
  static void write(::orgproto::BlockCode::Line::Part* out, sem::BlockCode::Line::Part const& in);
  static void read(::orgproto::BlockCode::Line::Part const& out, proto_write_accessor<sem::BlockCode::Line::Part> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Line, sem::BlockCode::Line> {
  static void write(::orgproto::BlockCode::Line* out, sem::BlockCode::Line const& in);
  static void read(::orgproto::BlockCode::Line const& out, proto_write_accessor<sem::BlockCode::Line> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch::LineStart, sem::BlockCode::Switch::LineStart> {
  static void write(::orgproto::BlockCode::Switch::LineStart* out, sem::BlockCode::Switch::LineStart const& in);
  static void read(::orgproto::BlockCode::Switch::LineStart const& out, proto_write_accessor<sem::BlockCode::Switch::LineStart> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch::CalloutFormat, sem::BlockCode::Switch::CalloutFormat> {
  static void write(::orgproto::BlockCode::Switch::CalloutFormat* out, sem::BlockCode::Switch::CalloutFormat const& in);
  static void read(::orgproto::BlockCode::Switch::CalloutFormat const& out, proto_write_accessor<sem::BlockCode::Switch::CalloutFormat> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch::RemoveCallout, sem::BlockCode::Switch::RemoveCallout> {
  static void write(::orgproto::BlockCode::Switch::RemoveCallout* out, sem::BlockCode::Switch::RemoveCallout const& in);
  static void read(::orgproto::BlockCode::Switch::RemoveCallout const& out, proto_write_accessor<sem::BlockCode::Switch::RemoveCallout> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch::EmphasizeLine, sem::BlockCode::Switch::EmphasizeLine> {
  static void write(::orgproto::BlockCode::Switch::EmphasizeLine* out, sem::BlockCode::Switch::EmphasizeLine const& in);
  static void read(::orgproto::BlockCode::Switch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCode::Switch::EmphasizeLine> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch::Dedent, sem::BlockCode::Switch::Dedent> {
  static void write(::orgproto::BlockCode::Switch::Dedent* out, sem::BlockCode::Switch::Dedent const& in);
  static void read(::orgproto::BlockCode::Switch::Dedent const& out, proto_write_accessor<sem::BlockCode::Switch::Dedent> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::Switch, sem::BlockCode::Switch> {
  static void write(::orgproto::BlockCode::Switch* out, sem::BlockCode::Switch const& in);
  static void read(::orgproto::BlockCode::Switch const& out, proto_write_accessor<sem::BlockCode::Switch> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::EvalResult::None, sem::BlockCode::EvalResult::None> {
  static void write(::orgproto::BlockCode::EvalResult::None* out, sem::BlockCode::EvalResult::None const& in);
  static void read(::orgproto::BlockCode::EvalResult::None const& out, proto_write_accessor<sem::BlockCode::EvalResult::None> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::EvalResult::OrgValue, sem::BlockCode::EvalResult::OrgValue> {
  static void write(::orgproto::BlockCode::EvalResult::OrgValue* out, sem::BlockCode::EvalResult::OrgValue const& in);
  static void read(::orgproto::BlockCode::EvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCode::EvalResult::OrgValue> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::EvalResult::File, sem::BlockCode::EvalResult::File> {
  static void write(::orgproto::BlockCode::EvalResult::File* out, sem::BlockCode::EvalResult::File const& in);
  static void read(::orgproto::BlockCode::EvalResult::File const& out, proto_write_accessor<sem::BlockCode::EvalResult::File> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::EvalResult::Raw, sem::BlockCode::EvalResult::Raw> {
  static void write(::orgproto::BlockCode::EvalResult::Raw* out, sem::BlockCode::EvalResult::Raw const& in);
  static void read(::orgproto::BlockCode::EvalResult::Raw const& out, proto_write_accessor<sem::BlockCode::EvalResult::Raw> in);
};


template <>
struct proto_serde<::orgproto::BlockCode::EvalResult, sem::BlockCode::EvalResult> {
  static void write(::orgproto::BlockCode::EvalResult* out, sem::BlockCode::EvalResult const& in);
  static void read(::orgproto::BlockCode::EvalResult const& out, proto_write_accessor<sem::BlockCode::EvalResult> in);
};


template <>
struct proto_serde<::orgproto::BlockCode, sem::BlockCode> {
  static void write(::orgproto::BlockCode* out, sem::BlockCode const& in);
  static void read(::orgproto::BlockCode const& out, proto_write_accessor<sem::BlockCode> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::DescribedLog, sem::SubtreeLog::DescribedLog> {
  static void write(::orgproto::SubtreeLog::DescribedLog* out, sem::SubtreeLog::DescribedLog const& in);
  static void read(::orgproto::SubtreeLog::DescribedLog const& out, proto_write_accessor<sem::SubtreeLog::DescribedLog> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Priority, sem::SubtreeLog::Priority> {
  static void write(::orgproto::SubtreeLog::Priority* out, sem::SubtreeLog::Priority const& in);
  static void read(::orgproto::SubtreeLog::Priority const& out, proto_write_accessor<sem::SubtreeLog::Priority> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Note, sem::SubtreeLog::Note> {
  static void write(::orgproto::SubtreeLog::Note* out, sem::SubtreeLog::Note const& in);
  static void read(::orgproto::SubtreeLog::Note const& out, proto_write_accessor<sem::SubtreeLog::Note> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Refile, sem::SubtreeLog::Refile> {
  static void write(::orgproto::SubtreeLog::Refile* out, sem::SubtreeLog::Refile const& in);
  static void read(::orgproto::SubtreeLog::Refile const& out, proto_write_accessor<sem::SubtreeLog::Refile> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Clock, sem::SubtreeLog::Clock> {
  static void write(::orgproto::SubtreeLog::Clock* out, sem::SubtreeLog::Clock const& in);
  static void read(::orgproto::SubtreeLog::Clock const& out, proto_write_accessor<sem::SubtreeLog::Clock> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::State, sem::SubtreeLog::State> {
  static void write(::orgproto::SubtreeLog::State* out, sem::SubtreeLog::State const& in);
  static void read(::orgproto::SubtreeLog::State const& out, proto_write_accessor<sem::SubtreeLog::State> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Tag, sem::SubtreeLog::Tag> {
  static void write(::orgproto::SubtreeLog::Tag* out, sem::SubtreeLog::Tag const& in);
  static void read(::orgproto::SubtreeLog::Tag const& out, proto_write_accessor<sem::SubtreeLog::Tag> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog::Unknown, sem::SubtreeLog::Unknown> {
  static void write(::orgproto::SubtreeLog::Unknown* out, sem::SubtreeLog::Unknown const& in);
  static void read(::orgproto::SubtreeLog::Unknown const& out, proto_write_accessor<sem::SubtreeLog::Unknown> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLog, sem::SubtreeLog> {
  static void write(::orgproto::SubtreeLog* out, sem::SubtreeLog const& in);
  static void read(::orgproto::SubtreeLog const& out, proto_write_accessor<sem::SubtreeLog> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Period, sem::Subtree::Period> {
  static void write(::orgproto::Subtree::Period* out, sem::Subtree::Period const& in);
  static void read(::orgproto::Subtree::Period const& out, proto_write_accessor<sem::Subtree::Period> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Nonblocking, sem::Subtree::Property::Nonblocking> {
  static void write(::orgproto::Subtree::Property::Nonblocking* out, sem::Subtree::Property::Nonblocking const& in);
  static void read(::orgproto::Subtree::Property::Nonblocking const& out, proto_write_accessor<sem::Subtree::Property::Nonblocking> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Trigger, sem::Subtree::Property::Trigger> {
  static void write(::orgproto::Subtree::Property::Trigger* out, sem::Subtree::Property::Trigger const& in);
  static void read(::orgproto::Subtree::Property::Trigger const& out, proto_write_accessor<sem::Subtree::Property::Trigger> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Origin, sem::Subtree::Property::Origin> {
  static void write(::orgproto::Subtree::Property::Origin* out, sem::Subtree::Property::Origin const& in);
  static void read(::orgproto::Subtree::Property::Origin const& out, proto_write_accessor<sem::Subtree::Property::Origin> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClass, sem::Subtree::Property::ExportLatexClass> {
  static void write(::orgproto::Subtree::Property::ExportLatexClass* out, sem::Subtree::Property::ExportLatexClass const& in);
  static void read(::orgproto::Subtree::Property::ExportLatexClass const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClass> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexClassOptions, sem::Subtree::Property::ExportLatexClassOptions> {
  static void write(::orgproto::Subtree::Property::ExportLatexClassOptions* out, sem::Subtree::Property::ExportLatexClassOptions const& in);
  static void read(::orgproto::Subtree::Property::ExportLatexClassOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexClassOptions> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexHeader, sem::Subtree::Property::ExportLatexHeader> {
  static void write(::orgproto::Subtree::Property::ExportLatexHeader* out, sem::Subtree::Property::ExportLatexHeader const& in);
  static void read(::orgproto::Subtree::Property::ExportLatexHeader const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexHeader> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportLatexCompiler, sem::Subtree::Property::ExportLatexCompiler> {
  static void write(::orgproto::Subtree::Property::ExportLatexCompiler* out, sem::Subtree::Property::ExportLatexCompiler const& in);
  static void read(::orgproto::Subtree::Property::ExportLatexCompiler const& out, proto_write_accessor<sem::Subtree::Property::ExportLatexCompiler> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Ordered, sem::Subtree::Property::Ordered> {
  static void write(::orgproto::Subtree::Property::Ordered* out, sem::Subtree::Property::Ordered const& in);
  static void read(::orgproto::Subtree::Property::Ordered const& out, proto_write_accessor<sem::Subtree::Property::Ordered> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Effort, sem::Subtree::Property::Effort> {
  static void write(::orgproto::Subtree::Property::Effort* out, sem::Subtree::Property::Effort const& in);
  static void read(::orgproto::Subtree::Property::Effort const& out, proto_write_accessor<sem::Subtree::Property::Effort> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Visibility, sem::Subtree::Property::Visibility> {
  static void write(::orgproto::Subtree::Property::Visibility* out, sem::Subtree::Property::Visibility const& in);
  static void read(::orgproto::Subtree::Property::Visibility const& out, proto_write_accessor<sem::Subtree::Property::Visibility> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::ExportOptions, sem::Subtree::Property::ExportOptions> {
  static void write(::orgproto::Subtree::Property::ExportOptions* out, sem::Subtree::Property::ExportOptions const& in);
  static void read(::orgproto::Subtree::Property::ExportOptions const& out, proto_write_accessor<sem::Subtree::Property::ExportOptions> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Blocker, sem::Subtree::Property::Blocker> {
  static void write(::orgproto::Subtree::Property::Blocker* out, sem::Subtree::Property::Blocker const& in);
  static void read(::orgproto::Subtree::Property::Blocker const& out, proto_write_accessor<sem::Subtree::Property::Blocker> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Unnumbered, sem::Subtree::Property::Unnumbered> {
  static void write(::orgproto::Subtree::Property::Unnumbered* out, sem::Subtree::Property::Unnumbered const& in);
  static void read(::orgproto::Subtree::Property::Unnumbered const& out, proto_write_accessor<sem::Subtree::Property::Unnumbered> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::Created, sem::Subtree::Property::Created> {
  static void write(::orgproto::Subtree::Property::Created* out, sem::Subtree::Property::Created const& in);
  static void read(::orgproto::Subtree::Property::Created const& out, proto_write_accessor<sem::Subtree::Property::Created> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::CustomArgs, sem::Subtree::Property::CustomArgs> {
  static void write(::orgproto::Subtree::Property::CustomArgs* out, sem::Subtree::Property::CustomArgs const& in);
  static void read(::orgproto::Subtree::Property::CustomArgs const& out, proto_write_accessor<sem::Subtree::Property::CustomArgs> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property::CustomRaw, sem::Subtree::Property::CustomRaw> {
  static void write(::orgproto::Subtree::Property::CustomRaw* out, sem::Subtree::Property::CustomRaw const& in);
  static void read(::orgproto::Subtree::Property::CustomRaw const& out, proto_write_accessor<sem::Subtree::Property::CustomRaw> in);
};


template <>
struct proto_serde<::orgproto::Subtree::Property, sem::Subtree::Property> {
  static void write(::orgproto::Subtree::Property* out, sem::Subtree::Property const& in);
  static void read(::orgproto::Subtree::Property const& out, proto_write_accessor<sem::Subtree::Property> in);
};


template <>
struct proto_serde<::orgproto::Subtree, sem::Subtree> {
  static void write(::orgproto::Subtree* out, sem::Subtree const& in);
  static void read(::orgproto::Subtree const& out, proto_write_accessor<sem::Subtree> in);
};


template <>
struct proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion> {
  static void write(::orgproto::SubtreeCompletion* out, sem::SubtreeCompletion const& in);
  static void read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<sem::SubtreeCompletion> in);
};


template <>
struct proto_serde<::orgproto::Cell, sem::Cell> {
  static void write(::orgproto::Cell* out, sem::Cell const& in);
  static void read(::orgproto::Cell const& out, proto_write_accessor<sem::Cell> in);
};


template <>
struct proto_serde<::orgproto::Row, sem::Row> {
  static void write(::orgproto::Row* out, sem::Row const& in);
  static void read(::orgproto::Row const& out, proto_write_accessor<sem::Row> in);
};


template <>
struct proto_serde<::orgproto::Table, sem::Table> {
  static void write(::orgproto::Table* out, sem::Table const& in);
  static void read(::orgproto::Table const& out, proto_write_accessor<sem::Table> in);
};


template <>
struct proto_serde<::orgproto::Paragraph, sem::Paragraph> {
  static void write(::orgproto::Paragraph* out, sem::Paragraph const& in);
  static void read(::orgproto::Paragraph const& out, proto_write_accessor<sem::Paragraph> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph::None, sem::AnnotatedParagraph::None> {
  static void write(::orgproto::AnnotatedParagraph::None* out, sem::AnnotatedParagraph::None const& in);
  static void read(::orgproto::AnnotatedParagraph::None const& out, proto_write_accessor<sem::AnnotatedParagraph::None> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph::Footnote, sem::AnnotatedParagraph::Footnote> {
  static void write(::orgproto::AnnotatedParagraph::Footnote* out, sem::AnnotatedParagraph::Footnote const& in);
  static void read(::orgproto::AnnotatedParagraph::Footnote const& out, proto_write_accessor<sem::AnnotatedParagraph::Footnote> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph::Admonition, sem::AnnotatedParagraph::Admonition> {
  static void write(::orgproto::AnnotatedParagraph::Admonition* out, sem::AnnotatedParagraph::Admonition const& in);
  static void read(::orgproto::AnnotatedParagraph::Admonition const& out, proto_write_accessor<sem::AnnotatedParagraph::Admonition> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph::Timestamp, sem::AnnotatedParagraph::Timestamp> {
  static void write(::orgproto::AnnotatedParagraph::Timestamp* out, sem::AnnotatedParagraph::Timestamp const& in);
  static void read(::orgproto::AnnotatedParagraph::Timestamp const& out, proto_write_accessor<sem::AnnotatedParagraph::Timestamp> in);
};


template <>
struct proto_serde<::orgproto::AnnotatedParagraph, sem::AnnotatedParagraph> {
  static void write(::orgproto::AnnotatedParagraph* out, sem::AnnotatedParagraph const& in);
  static void read(::orgproto::AnnotatedParagraph const& out, proto_write_accessor<sem::AnnotatedParagraph> in);
};


template <>
struct proto_serde<::orgproto::ColonExample, sem::ColonExample> {
  static void write(::orgproto::ColonExample* out, sem::ColonExample const& in);
  static void read(::orgproto::ColonExample const& out, proto_write_accessor<sem::ColonExample> in);
};


template <>
struct proto_serde<::orgproto::CmdAttr, sem::CmdAttr> {
  static void write(::orgproto::CmdAttr* out, sem::CmdAttr const& in);
  static void read(::orgproto::CmdAttr const& out, proto_write_accessor<sem::CmdAttr> in);
};


template <>
struct proto_serde<::orgproto::Call, sem::Call> {
  static void write(::orgproto::Call* out, sem::Call const& in);
  static void read(::orgproto::Call const& out, proto_write_accessor<sem::Call> in);
};


template <>
struct proto_serde<::orgproto::List, sem::List> {
  static void write(::orgproto::List* out, sem::List const& in);
  static void read(::orgproto::List const& out, proto_write_accessor<sem::List> in);
};


template <>
struct proto_serde<::orgproto::ListItem, sem::ListItem> {
  static void write(::orgproto::ListItem* out, sem::ListItem const& in);
  static void read(::orgproto::ListItem const& out, proto_write_accessor<sem::ListItem> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportConfig::TaskExport, sem::DocumentOptions::ExportConfig::TaskExport> {
  static void write(::orgproto::DocumentOptions::ExportConfig::TaskExport* out, sem::DocumentOptions::ExportConfig::TaskExport const& in);
  static void read(::orgproto::DocumentOptions::ExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::TaskExport> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportConfig::DoExport, sem::DocumentOptions::ExportConfig::DoExport> {
  static void write(::orgproto::DocumentOptions::ExportConfig::DoExport* out, sem::DocumentOptions::ExportConfig::DoExport const& in);
  static void read(::orgproto::DocumentOptions::ExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::DoExport> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportConfig::ExportFixed, sem::DocumentOptions::ExportConfig::ExportFixed> {
  static void write(::orgproto::DocumentOptions::ExportConfig::ExportFixed* out, sem::DocumentOptions::ExportConfig::ExportFixed const& in);
  static void read(::orgproto::DocumentOptions::ExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig::ExportFixed> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions::ExportConfig, sem::DocumentOptions::ExportConfig> {
  static void write(::orgproto::DocumentOptions::ExportConfig* out, sem::DocumentOptions::ExportConfig const& in);
  static void read(::orgproto::DocumentOptions::ExportConfig const& out, proto_write_accessor<sem::DocumentOptions::ExportConfig> in);
};


template <>
struct proto_serde<::orgproto::DocumentOptions, sem::DocumentOptions> {
  static void write(::orgproto::DocumentOptions* out, sem::DocumentOptions const& in);
  static void read(::orgproto::DocumentOptions const& out, proto_write_accessor<sem::DocumentOptions> in);
};


template <>
struct proto_serde<::orgproto::Document, sem::Document> {
  static void write(::orgproto::Document* out, sem::Document const& in);
  static void read(::orgproto::Document const& out, proto_write_accessor<sem::Document> in);
};


template <>
struct proto_serde<::orgproto::FileTarget, sem::FileTarget> {
  static void write(::orgproto::FileTarget* out, sem::FileTarget const& in);
  static void read(::orgproto::FileTarget const& out, proto_write_accessor<sem::FileTarget> in);
};


template <>
struct proto_serde<::orgproto::TextSeparator, sem::TextSeparator> {
  static void write(::orgproto::TextSeparator* out, sem::TextSeparator const& in);
  static void read(::orgproto::TextSeparator const& out, proto_write_accessor<sem::TextSeparator> in);
};


template <>
struct proto_serde<::orgproto::Include::Example, sem::Include::Example> {
  static void write(::orgproto::Include::Example* out, sem::Include::Example const& in);
  static void read(::orgproto::Include::Example const& out, proto_write_accessor<sem::Include::Example> in);
};


template <>
struct proto_serde<::orgproto::Include::Export, sem::Include::Export> {
  static void write(::orgproto::Include::Export* out, sem::Include::Export const& in);
  static void read(::orgproto::Include::Export const& out, proto_write_accessor<sem::Include::Export> in);
};


template <>
struct proto_serde<::orgproto::Include::Src, sem::Include::Src> {
  static void write(::orgproto::Include::Src* out, sem::Include::Src const& in);
  static void read(::orgproto::Include::Src const& out, proto_write_accessor<sem::Include::Src> in);
};


template <>
struct proto_serde<::orgproto::Include::OrgDocument, sem::Include::OrgDocument> {
  static void write(::orgproto::Include::OrgDocument* out, sem::Include::OrgDocument const& in);
  static void read(::orgproto::Include::OrgDocument const& out, proto_write_accessor<sem::Include::OrgDocument> in);
};


template <>
struct proto_serde<::orgproto::Include, sem::Include> {
  static void write(::orgproto::Include* out, sem::Include const& in);
  static void read(::orgproto::Include const& out, proto_write_accessor<sem::Include> in);
};


template <>
struct proto_serde<::orgproto::DocumentGroup, sem::DocumentGroup> {
  static void write(::orgproto::DocumentGroup* out, sem::DocumentGroup const& in);
  static void read(::orgproto::DocumentGroup const& out, proto_write_accessor<sem::DocumentGroup> in);
};


/* clang-format on */