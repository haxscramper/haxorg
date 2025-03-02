/* clang-format off */
#pragma once
#include <haxorg/sem/SemOrgSerde.hpp>
#define EACH_ANY_NODE_PROTO_FIELD(__MAP) \
        __MAP(kNone, none, None)  \
        __MAP(kErroritem, erroritem, ErrorItem)  \
        __MAP(kErrorgroup, errorgroup, ErrorGroup)  \
        __MAP(kStmtlist, stmtlist, StmtList)  \
        __MAP(kEmpty, empty, Empty)  \
        __MAP(kCmdcaption, cmdcaption, CmdCaption)  \
        __MAP(kCmdcolumns, cmdcolumns, CmdColumns)  \
        __MAP(kCmdname, cmdname, CmdName)  \
        __MAP(kCmdcustomargs, cmdcustomargs, CmdCustomArgs)  \
        __MAP(kCmdcustomraw, cmdcustomraw, CmdCustomRaw)  \
        __MAP(kCmdcustomtext, cmdcustomtext, CmdCustomText)  \
        __MAP(kCmdresults, cmdresults, CmdResults)  \
        __MAP(kCmdtblfm, cmdtblfm, CmdTblfm)  \
        __MAP(kHashtag, hashtag, HashTag)  \
        __MAP(kInlinefootnote, inlinefootnote, InlineFootnote)  \
        __MAP(kInlineexport, inlineexport, InlineExport)  \
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
        __MAP(kTexttarget, texttarget, TextTarget)  \
        __MAP(kBold, bold, Bold)  \
        __MAP(kUnderline, underline, Underline)  \
        __MAP(kMonospace, monospace, Monospace)  \
        __MAP(kMarkquote, markquote, MarkQuote)  \
        __MAP(kVerbatim, verbatim, Verbatim)  \
        __MAP(kItalic, italic, Italic)  \
        __MAP(kStrike, strike, Strike)  \
        __MAP(kPar, par, Par)  \
        __MAP(kRadiotarget, radiotarget, RadioTarget)  \
        __MAP(kLatex, latex, Latex)  \
        __MAP(kLink, link, Link)  \
        __MAP(kBlockcenter, blockcenter, BlockCenter)  \
        __MAP(kBlockquote, blockquote, BlockQuote)  \
        __MAP(kBlockcomment, blockcomment, BlockComment)  \
        __MAP(kBlockverse, blockverse, BlockVerse)  \
        __MAP(kBlockdynamicfallback, blockdynamicfallback, BlockDynamicFallback)  \
        __MAP(kBlockexample, blockexample, BlockExample)  \
        __MAP(kBlockexport, blockexport, BlockExport)  \
        __MAP(kBlockadmonition, blockadmonition, BlockAdmonition)  \
        __MAP(kBlockcodeevalresult, blockcodeevalresult, BlockCodeEvalResult)  \
        __MAP(kBlockcode, blockcode, BlockCode)  \
        __MAP(kSubtreelog, subtreelog, SubtreeLog)  \
        __MAP(kSubtree, subtree, Subtree)  \
        __MAP(kCell, cell, Cell)  \
        __MAP(kRow, row, Row)  \
        __MAP(kTable, table, Table)  \
        __MAP(kParagraph, paragraph, Paragraph)  \
        __MAP(kColonexample, colonexample, ColonExample)  \
        __MAP(kCmdattr, cmdattr, CmdAttr)  \
        __MAP(kCmdexport, cmdexport, CmdExport)  \
        __MAP(kCall, call, Call)  \
        __MAP(kList, list, List)  \
        __MAP(kListitem, listitem, ListItem)  \
        __MAP(kDocumentoptions, documentoptions, DocumentOptions)  \
        __MAP(kDocument, document, Document)  \
        __MAP(kFiletarget, filetarget, FileTarget)  \
        __MAP(kTextseparator, textseparator, TextSeparator)  \
        __MAP(kDocumentgroup, documentgroup, DocumentGroup)  \
        __MAP(kFile, file, File)  \
        __MAP(kDirectory, directory, Directory)  \
        __MAP(kSymlink, symlink, Symlink)  \
        __MAP(kCmdinclude, cmdinclude, CmdInclude)  \

template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position::Index* out, org::sem::Tblfm::Expr::AxisRef::Position::Index const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Index> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position::Name* out, org::sem::Tblfm::Expr::AxisRef::Position::Name const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Name> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position* out, org::sem::Tblfm::Expr::AxisRef::Position const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef> {
  static void write(::orgproto::Tblfm::Expr::AxisRef* out, org::sem::Tblfm::Expr::AxisRef const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName> {
  static void write(::orgproto::Tblfm::Expr::AxisName* out, org::sem::Tblfm::Expr::AxisName const& in);
  static void read(::orgproto::Tblfm::Expr::AxisName const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisName> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral> {
  static void write(::orgproto::Tblfm::Expr::IntLiteral* out, org::sem::Tblfm::Expr::IntLiteral const& in);
  static void read(::orgproto::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::IntLiteral> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral> {
  static void write(::orgproto::Tblfm::Expr::FloatLiteral* out, org::sem::Tblfm::Expr::FloatLiteral const& in);
  static void read(::orgproto::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::FloatLiteral> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef> {
  static void write(::orgproto::Tblfm::Expr::RangeRef* out, org::sem::Tblfm::Expr::RangeRef const& in);
  static void read(::orgproto::Tblfm::Expr::RangeRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::RangeRef> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call> {
  static void write(::orgproto::Tblfm::Expr::Call* out, org::sem::Tblfm::Expr::Call const& in);
  static void read(::orgproto::Tblfm::Expr::Call const& out, proto_write_accessor<org::sem::Tblfm::Expr::Call> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp> {
  static void write(::orgproto::Tblfm::Expr::Elisp* out, org::sem::Tblfm::Expr::Elisp const& in);
  static void read(::orgproto::Tblfm::Expr::Elisp const& out, proto_write_accessor<org::sem::Tblfm::Expr::Elisp> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Expr, org::sem::Tblfm::Expr> {
  static void write(::orgproto::Tblfm::Expr* out, org::sem::Tblfm::Expr const& in);
  static void read(::orgproto::Tblfm::Expr const& out, proto_write_accessor<org::sem::Tblfm::Expr> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm::Assign, org::sem::Tblfm::Assign> {
  static void write(::orgproto::Tblfm::Assign* out, org::sem::Tblfm::Assign const& in);
  static void read(::orgproto::Tblfm::Assign const& out, proto_write_accessor<org::sem::Tblfm::Assign> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Tblfm, org::sem::Tblfm> {
  static void write(::orgproto::Tblfm* out, org::sem::Tblfm const& in);
  static void read(::orgproto::Tblfm const& out, proto_write_accessor<org::sem::Tblfm> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrValue::DimensionSpan, org::sem::AttrValue::DimensionSpan> {
  static void write(::orgproto::AttrValue::DimensionSpan* out, org::sem::AttrValue::DimensionSpan const& in);
  static void read(::orgproto::AttrValue::DimensionSpan const& out, proto_write_accessor<org::sem::AttrValue::DimensionSpan> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrValue::TextValue, org::sem::AttrValue::TextValue> {
  static void write(::orgproto::AttrValue::TextValue* out, org::sem::AttrValue::TextValue const& in);
  static void read(::orgproto::AttrValue::TextValue const& out, proto_write_accessor<org::sem::AttrValue::TextValue> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrValue::FileReference, org::sem::AttrValue::FileReference> {
  static void write(::orgproto::AttrValue::FileReference* out, org::sem::AttrValue::FileReference const& in);
  static void read(::orgproto::AttrValue::FileReference const& out, proto_write_accessor<org::sem::AttrValue::FileReference> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrValue, org::sem::AttrValue> {
  static void write(::orgproto::AttrValue* out, org::sem::AttrValue const& in);
  static void read(::orgproto::AttrValue const& out, proto_write_accessor<org::sem::AttrValue> in);
};


template <>
struct org::algo::proto_serde<::orgproto::HashTagFlat, org::sem::HashTagFlat> {
  static void write(::orgproto::HashTagFlat* out, org::sem::HashTagFlat const& in);
  static void read(::orgproto::HashTagFlat const& out, proto_write_accessor<org::sem::HashTagFlat> in);
};


template <>
struct org::algo::proto_serde<::orgproto::HashTagText, org::sem::HashTagText> {
  static void write(::orgproto::HashTagText* out, org::sem::HashTagText const& in);
  static void read(::orgproto::HashTagText const& out, proto_write_accessor<org::sem::HashTagText> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreePath, org::sem::SubtreePath> {
  static void write(::orgproto::SubtreePath* out, org::sem::SubtreePath const& in);
  static void read(::orgproto::SubtreePath const& out, proto_write_accessor<org::sem::SubtreePath> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Raw, org::sem::LinkTarget::Raw> {
  static void write(::orgproto::LinkTarget::Raw* out, org::sem::LinkTarget::Raw const& in);
  static void read(::orgproto::LinkTarget::Raw const& out, proto_write_accessor<org::sem::LinkTarget::Raw> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Id, org::sem::LinkTarget::Id> {
  static void write(::orgproto::LinkTarget::Id* out, org::sem::LinkTarget::Id const& in);
  static void read(::orgproto::LinkTarget::Id const& out, proto_write_accessor<org::sem::LinkTarget::Id> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::CustomId, org::sem::LinkTarget::CustomId> {
  static void write(::orgproto::LinkTarget::CustomId* out, org::sem::LinkTarget::CustomId const& in);
  static void read(::orgproto::LinkTarget::CustomId const& out, proto_write_accessor<org::sem::LinkTarget::CustomId> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle> {
  static void write(::orgproto::LinkTarget::SubtreeTitle* out, org::sem::LinkTarget::SubtreeTitle const& in);
  static void read(::orgproto::LinkTarget::SubtreeTitle const& out, proto_write_accessor<org::sem::LinkTarget::SubtreeTitle> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Person, org::sem::LinkTarget::Person> {
  static void write(::orgproto::LinkTarget::Person* out, org::sem::LinkTarget::Person const& in);
  static void read(::orgproto::LinkTarget::Person const& out, proto_write_accessor<org::sem::LinkTarget::Person> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol> {
  static void write(::orgproto::LinkTarget::UserProtocol* out, org::sem::LinkTarget::UserProtocol const& in);
  static void read(::orgproto::LinkTarget::UserProtocol const& out, proto_write_accessor<org::sem::LinkTarget::UserProtocol> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Internal, org::sem::LinkTarget::Internal> {
  static void write(::orgproto::LinkTarget::Internal* out, org::sem::LinkTarget::Internal const& in);
  static void read(::orgproto::LinkTarget::Internal const& out, proto_write_accessor<org::sem::LinkTarget::Internal> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Footnote, org::sem::LinkTarget::Footnote> {
  static void write(::orgproto::LinkTarget::Footnote* out, org::sem::LinkTarget::Footnote const& in);
  static void read(::orgproto::LinkTarget::Footnote const& out, proto_write_accessor<org::sem::LinkTarget::Footnote> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::File, org::sem::LinkTarget::File> {
  static void write(::orgproto::LinkTarget::File* out, org::sem::LinkTarget::File const& in);
  static void read(::orgproto::LinkTarget::File const& out, proto_write_accessor<org::sem::LinkTarget::File> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget::Attachment, org::sem::LinkTarget::Attachment> {
  static void write(::orgproto::LinkTarget::Attachment* out, org::sem::LinkTarget::Attachment const& in);
  static void read(::orgproto::LinkTarget::Attachment const& out, proto_write_accessor<org::sem::LinkTarget::Attachment> in);
};


template <>
struct org::algo::proto_serde<::orgproto::LinkTarget, org::sem::LinkTarget> {
  static void write(::orgproto::LinkTarget* out, org::sem::LinkTarget const& in);
  static void read(::orgproto::LinkTarget const& out, proto_write_accessor<org::sem::LinkTarget> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority> {
  static void write(::orgproto::SubtreeLogHead::Priority* out, org::sem::SubtreeLogHead::Priority const& in);
  static void read(::orgproto::SubtreeLogHead::Priority const& out, proto_write_accessor<org::sem::SubtreeLogHead::Priority> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note> {
  static void write(::orgproto::SubtreeLogHead::Note* out, org::sem::SubtreeLogHead::Note const& in);
  static void read(::orgproto::SubtreeLogHead::Note const& out, proto_write_accessor<org::sem::SubtreeLogHead::Note> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile> {
  static void write(::orgproto::SubtreeLogHead::Refile* out, org::sem::SubtreeLogHead::Refile const& in);
  static void read(::orgproto::SubtreeLogHead::Refile const& out, proto_write_accessor<org::sem::SubtreeLogHead::Refile> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock> {
  static void write(::orgproto::SubtreeLogHead::Clock* out, org::sem::SubtreeLogHead::Clock const& in);
  static void read(::orgproto::SubtreeLogHead::Clock const& out, proto_write_accessor<org::sem::SubtreeLogHead::Clock> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::State, org::sem::SubtreeLogHead::State> {
  static void write(::orgproto::SubtreeLogHead::State* out, org::sem::SubtreeLogHead::State const& in);
  static void read(::orgproto::SubtreeLogHead::State const& out, proto_write_accessor<org::sem::SubtreeLogHead::State> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline> {
  static void write(::orgproto::SubtreeLogHead::Deadline* out, org::sem::SubtreeLogHead::Deadline const& in);
  static void read(::orgproto::SubtreeLogHead::Deadline const& out, proto_write_accessor<org::sem::SubtreeLogHead::Deadline> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule> {
  static void write(::orgproto::SubtreeLogHead::Schedule* out, org::sem::SubtreeLogHead::Schedule const& in);
  static void read(::orgproto::SubtreeLogHead::Schedule const& out, proto_write_accessor<org::sem::SubtreeLogHead::Schedule> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag> {
  static void write(::orgproto::SubtreeLogHead::Tag* out, org::sem::SubtreeLogHead::Tag const& in);
  static void read(::orgproto::SubtreeLogHead::Tag const& out, proto_write_accessor<org::sem::SubtreeLogHead::Tag> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown> {
  static void write(::orgproto::SubtreeLogHead::Unknown* out, org::sem::SubtreeLogHead::Unknown const& in);
  static void read(::orgproto::SubtreeLogHead::Unknown const& out, proto_write_accessor<org::sem::SubtreeLogHead::Unknown> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLogHead, org::sem::SubtreeLogHead> {
  static void write(::orgproto::SubtreeLogHead* out, org::sem::SubtreeLogHead const& in);
  static void read(::orgproto::SubtreeLogHead const& out, proto_write_accessor<org::sem::SubtreeLogHead> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeCompletion, org::sem::SubtreeCompletion> {
  static void write(::orgproto::SubtreeCompletion* out, org::sem::SubtreeCompletion const& in);
  static void read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<org::sem::SubtreeCompletion> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrList, org::sem::AttrList> {
  static void write(::orgproto::AttrList* out, org::sem::AttrList const& in);
  static void read(::orgproto::AttrList const& out, proto_write_accessor<org::sem::AttrList> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AttrGroup, org::sem::AttrGroup> {
  static void write(::orgproto::AttrGroup* out, org::sem::AttrGroup const& in);
  static void read(::orgproto::AttrGroup const& out, proto_write_accessor<org::sem::AttrGroup> in);
};


template <>
struct org::algo::proto_serde<::orgproto::OrgCodeEvalInput, org::sem::OrgCodeEvalInput> {
  static void write(::orgproto::OrgCodeEvalInput* out, org::sem::OrgCodeEvalInput const& in);
  static void read(::orgproto::OrgCodeEvalInput const& out, proto_write_accessor<org::sem::OrgCodeEvalInput> in);
};


template <>
struct org::algo::proto_serde<::orgproto::OrgCodeEvalOutput, org::sem::OrgCodeEvalOutput> {
  static void write(::orgproto::OrgCodeEvalOutput* out, org::sem::OrgCodeEvalOutput const& in);
  static void read(::orgproto::OrgCodeEvalOutput const& out, proto_write_accessor<org::sem::OrgCodeEvalOutput> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate> {
  static void write(::orgproto::ColumnView::Summary::CheckboxAggregate* out, org::sem::ColumnView::Summary::CheckboxAggregate const& in);
  static void read(::orgproto::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::CheckboxAggregate> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate> {
  static void write(::orgproto::ColumnView::Summary::MathAggregate* out, org::sem::ColumnView::Summary::MathAggregate const& in);
  static void read(::orgproto::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::MathAggregate> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColumnView::Summary, org::sem::ColumnView::Summary> {
  static void write(::orgproto::ColumnView::Summary* out, org::sem::ColumnView::Summary const& in);
  static void read(::orgproto::ColumnView::Summary const& out, proto_write_accessor<org::sem::ColumnView::Summary> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColumnView::Column, org::sem::ColumnView::Column> {
  static void write(::orgproto::ColumnView::Column* out, org::sem::ColumnView::Column const& in);
  static void read(::orgproto::ColumnView::Column const& out, proto_write_accessor<org::sem::ColumnView::Column> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColumnView, org::sem::ColumnView> {
  static void write(::orgproto::ColumnView* out, org::sem::ColumnView const& in);
  static void read(::orgproto::ColumnView const& out, proto_write_accessor<org::sem::ColumnView> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw> {
  static void write(::orgproto::BlockCodeLine::Part::Raw* out, org::sem::BlockCodeLine::Part::Raw const& in);
  static void read(::orgproto::BlockCodeLine::Part::Raw const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Raw> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout> {
  static void write(::orgproto::BlockCodeLine::Part::Callout* out, org::sem::BlockCodeLine::Part::Callout const& in);
  static void read(::orgproto::BlockCodeLine::Part::Callout const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Callout> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle> {
  static void write(::orgproto::BlockCodeLine::Part::Tangle* out, org::sem::BlockCodeLine::Part::Tangle const& in);
  static void read(::orgproto::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Tangle> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeLine::Part, org::sem::BlockCodeLine::Part> {
  static void write(::orgproto::BlockCodeLine::Part* out, org::sem::BlockCodeLine::Part const& in);
  static void read(::orgproto::BlockCodeLine::Part const& out, proto_write_accessor<org::sem::BlockCodeLine::Part> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeLine, org::sem::BlockCodeLine> {
  static void write(::orgproto::BlockCodeLine* out, org::sem::BlockCodeLine const& in);
  static void read(::orgproto::BlockCodeLine const& out, proto_write_accessor<org::sem::BlockCodeLine> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart> {
  static void write(::orgproto::BlockCodeSwitch::LineStart* out, org::sem::BlockCodeSwitch::LineStart const& in);
  static void read(::orgproto::BlockCodeSwitch::LineStart const& out, proto_write_accessor<org::sem::BlockCodeSwitch::LineStart> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat> {
  static void write(::orgproto::BlockCodeSwitch::CalloutFormat* out, org::sem::BlockCodeSwitch::CalloutFormat const& in);
  static void read(::orgproto::BlockCodeSwitch::CalloutFormat const& out, proto_write_accessor<org::sem::BlockCodeSwitch::CalloutFormat> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout> {
  static void write(::orgproto::BlockCodeSwitch::RemoveCallout* out, org::sem::BlockCodeSwitch::RemoveCallout const& in);
  static void read(::orgproto::BlockCodeSwitch::RemoveCallout const& out, proto_write_accessor<org::sem::BlockCodeSwitch::RemoveCallout> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine> {
  static void write(::orgproto::BlockCodeSwitch::EmphasizeLine* out, org::sem::BlockCodeSwitch::EmphasizeLine const& in);
  static void read(::orgproto::BlockCodeSwitch::EmphasizeLine const& out, proto_write_accessor<org::sem::BlockCodeSwitch::EmphasizeLine> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent> {
  static void write(::orgproto::BlockCodeSwitch::Dedent* out, org::sem::BlockCodeSwitch::Dedent const& in);
  static void read(::orgproto::BlockCodeSwitch::Dedent const& out, proto_write_accessor<org::sem::BlockCodeSwitch::Dedent> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeSwitch, org::sem::BlockCodeSwitch> {
  static void write(::orgproto::BlockCodeSwitch* out, org::sem::BlockCodeSwitch const& in);
  static void read(::orgproto::BlockCodeSwitch const& out, proto_write_accessor<org::sem::BlockCodeSwitch> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport> {
  static void write(::orgproto::DocumentExportConfig::TaskExport* out, org::sem::DocumentExportConfig::TaskExport const& in);
  static void read(::orgproto::DocumentExportConfig::TaskExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::TaskExport> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport> {
  static void write(::orgproto::DocumentExportConfig::DoExport* out, org::sem::DocumentExportConfig::DoExport const& in);
  static void read(::orgproto::DocumentExportConfig::DoExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::DoExport> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed> {
  static void write(::orgproto::DocumentExportConfig::ExportFixed* out, org::sem::DocumentExportConfig::ExportFixed const& in);
  static void read(::orgproto::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<org::sem::DocumentExportConfig::ExportFixed> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentExportConfig, org::sem::DocumentExportConfig> {
  static void write(::orgproto::DocumentExportConfig* out, org::sem::DocumentExportConfig const& in);
  static void read(::orgproto::DocumentExportConfig const& out, proto_write_accessor<org::sem::DocumentExportConfig> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreePeriod, org::sem::SubtreePeriod> {
  static void write(::orgproto::SubtreePeriod* out, org::sem::SubtreePeriod const& in);
  static void read(::orgproto::SubtreePeriod const& out, proto_write_accessor<org::sem::SubtreePeriod> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking> {
  static void write(::orgproto::NamedProperty::Nonblocking* out, org::sem::NamedProperty::Nonblocking const& in);
  static void read(::orgproto::NamedProperty::Nonblocking const& out, proto_write_accessor<org::sem::NamedProperty::Nonblocking> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime> {
  static void write(::orgproto::NamedProperty::ArchiveTime* out, org::sem::NamedProperty::ArchiveTime const& in);
  static void read(::orgproto::NamedProperty::ArchiveTime const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTime> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile> {
  static void write(::orgproto::NamedProperty::ArchiveFile* out, org::sem::NamedProperty::ArchiveFile const& in);
  static void read(::orgproto::NamedProperty::ArchiveFile const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveFile> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath> {
  static void write(::orgproto::NamedProperty::ArchiveOlpath* out, org::sem::NamedProperty::ArchiveOlpath const& in);
  static void read(::orgproto::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveOlpath> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget> {
  static void write(::orgproto::NamedProperty::ArchiveTarget* out, org::sem::NamedProperty::ArchiveTarget const& in);
  static void read(::orgproto::NamedProperty::ArchiveTarget const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTarget> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory> {
  static void write(::orgproto::NamedProperty::ArchiveCategory* out, org::sem::NamedProperty::ArchiveCategory const& in);
  static void read(::orgproto::NamedProperty::ArchiveCategory const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveCategory> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo> {
  static void write(::orgproto::NamedProperty::ArchiveTodo* out, org::sem::NamedProperty::ArchiveTodo const& in);
  static void read(::orgproto::NamedProperty::ArchiveTodo const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTodo> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Trigger, org::sem::NamedProperty::Trigger> {
  static void write(::orgproto::NamedProperty::Trigger* out, org::sem::NamedProperty::Trigger const& in);
  static void read(::orgproto::NamedProperty::Trigger const& out, proto_write_accessor<org::sem::NamedProperty::Trigger> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass> {
  static void write(::orgproto::NamedProperty::ExportLatexClass* out, org::sem::NamedProperty::ExportLatexClass const& in);
  static void read(::orgproto::NamedProperty::ExportLatexClass const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClass> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::CookieData, org::sem::NamedProperty::CookieData> {
  static void write(::orgproto::NamedProperty::CookieData* out, org::sem::NamedProperty::CookieData const& in);
  static void read(::orgproto::NamedProperty::CookieData const& out, proto_write_accessor<org::sem::NamedProperty::CookieData> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions> {
  static void write(::orgproto::NamedProperty::ExportLatexClassOptions* out, org::sem::NamedProperty::ExportLatexClassOptions const& in);
  static void read(::orgproto::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClassOptions> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader> {
  static void write(::orgproto::NamedProperty::ExportLatexHeader* out, org::sem::NamedProperty::ExportLatexHeader const& in);
  static void read(::orgproto::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexHeader> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler> {
  static void write(::orgproto::NamedProperty::ExportLatexCompiler* out, org::sem::NamedProperty::ExportLatexCompiler const& in);
  static void read(::orgproto::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexCompiler> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Ordered, org::sem::NamedProperty::Ordered> {
  static void write(::orgproto::NamedProperty::Ordered* out, org::sem::NamedProperty::Ordered const& in);
  static void read(::orgproto::NamedProperty::Ordered const& out, proto_write_accessor<org::sem::NamedProperty::Ordered> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Effort, org::sem::NamedProperty::Effort> {
  static void write(::orgproto::NamedProperty::Effort* out, org::sem::NamedProperty::Effort const& in);
  static void read(::orgproto::NamedProperty::Effort const& out, proto_write_accessor<org::sem::NamedProperty::Effort> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Visibility, org::sem::NamedProperty::Visibility> {
  static void write(::orgproto::NamedProperty::Visibility* out, org::sem::NamedProperty::Visibility const& in);
  static void read(::orgproto::NamedProperty::Visibility const& out, proto_write_accessor<org::sem::NamedProperty::Visibility> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions> {
  static void write(::orgproto::NamedProperty::ExportOptions* out, org::sem::NamedProperty::ExportOptions const& in);
  static void read(::orgproto::NamedProperty::ExportOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportOptions> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Blocker, org::sem::NamedProperty::Blocker> {
  static void write(::orgproto::NamedProperty::Blocker* out, org::sem::NamedProperty::Blocker const& in);
  static void read(::orgproto::NamedProperty::Blocker const& out, proto_write_accessor<org::sem::NamedProperty::Blocker> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered> {
  static void write(::orgproto::NamedProperty::Unnumbered* out, org::sem::NamedProperty::Unnumbered const& in);
  static void read(::orgproto::NamedProperty::Unnumbered const& out, proto_write_accessor<org::sem::NamedProperty::Unnumbered> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::Created, org::sem::NamedProperty::Created> {
  static void write(::orgproto::NamedProperty::Created* out, org::sem::NamedProperty::Created const& in);
  static void read(::orgproto::NamedProperty::Created const& out, proto_write_accessor<org::sem::NamedProperty::Created> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::RadioId, org::sem::NamedProperty::RadioId> {
  static void write(::orgproto::NamedProperty::RadioId* out, org::sem::NamedProperty::RadioId const& in);
  static void read(::orgproto::NamedProperty::RadioId const& out, proto_write_accessor<org::sem::NamedProperty::RadioId> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef> {
  static void write(::orgproto::NamedProperty::HashtagDef* out, org::sem::NamedProperty::HashtagDef const& in);
  static void read(::orgproto::NamedProperty::HashtagDef const& out, proto_write_accessor<org::sem::NamedProperty::HashtagDef> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs> {
  static void write(::orgproto::NamedProperty::CustomArgs* out, org::sem::NamedProperty::CustomArgs const& in);
  static void read(::orgproto::NamedProperty::CustomArgs const& out, proto_write_accessor<org::sem::NamedProperty::CustomArgs> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw> {
  static void write(::orgproto::NamedProperty::CustomRaw* out, org::sem::NamedProperty::CustomRaw const& in);
  static void read(::orgproto::NamedProperty::CustomRaw const& out, proto_write_accessor<org::sem::NamedProperty::CustomRaw> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson> {
  static void write(::orgproto::NamedProperty::CustomSubtreeJson* out, org::sem::NamedProperty::CustomSubtreeJson const& in);
  static void read(::orgproto::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeJson> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags> {
  static void write(::orgproto::NamedProperty::CustomSubtreeFlags* out, org::sem::NamedProperty::CustomSubtreeFlags const& in);
  static void read(::orgproto::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeFlags> in);
};


template <>
struct org::algo::proto_serde<::orgproto::NamedProperty, org::sem::NamedProperty> {
  static void write(::orgproto::NamedProperty* out, org::sem::NamedProperty const& in);
  static void read(::orgproto::NamedProperty const& out, proto_write_accessor<org::sem::NamedProperty> in);
};


template <>
struct org::algo::proto_serde<::orgproto::None, org::sem::None> {
  static void write(::orgproto::None* out, org::sem::None const& in);
  static void read(::orgproto::None const& out, proto_write_accessor<org::sem::None> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ErrorItem, org::sem::ErrorItem> {
  static void write(::orgproto::ErrorItem* out, org::sem::ErrorItem const& in);
  static void read(::orgproto::ErrorItem const& out, proto_write_accessor<org::sem::ErrorItem> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ErrorGroup, org::sem::ErrorGroup> {
  static void write(::orgproto::ErrorGroup* out, org::sem::ErrorGroup const& in);
  static void read(::orgproto::ErrorGroup const& out, proto_write_accessor<org::sem::ErrorGroup> in);
};


template <>
struct org::algo::proto_serde<::orgproto::StmtList, org::sem::StmtList> {
  static void write(::orgproto::StmtList* out, org::sem::StmtList const& in);
  static void read(::orgproto::StmtList const& out, proto_write_accessor<org::sem::StmtList> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Empty, org::sem::Empty> {
  static void write(::orgproto::Empty* out, org::sem::Empty const& in);
  static void read(::orgproto::Empty const& out, proto_write_accessor<org::sem::Empty> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdCaption, org::sem::CmdCaption> {
  static void write(::orgproto::CmdCaption* out, org::sem::CmdCaption const& in);
  static void read(::orgproto::CmdCaption const& out, proto_write_accessor<org::sem::CmdCaption> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdColumns, org::sem::CmdColumns> {
  static void write(::orgproto::CmdColumns* out, org::sem::CmdColumns const& in);
  static void read(::orgproto::CmdColumns const& out, proto_write_accessor<org::sem::CmdColumns> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdName, org::sem::CmdName> {
  static void write(::orgproto::CmdName* out, org::sem::CmdName const& in);
  static void read(::orgproto::CmdName const& out, proto_write_accessor<org::sem::CmdName> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdCustomArgs, org::sem::CmdCustomArgs> {
  static void write(::orgproto::CmdCustomArgs* out, org::sem::CmdCustomArgs const& in);
  static void read(::orgproto::CmdCustomArgs const& out, proto_write_accessor<org::sem::CmdCustomArgs> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdCustomRaw, org::sem::CmdCustomRaw> {
  static void write(::orgproto::CmdCustomRaw* out, org::sem::CmdCustomRaw const& in);
  static void read(::orgproto::CmdCustomRaw const& out, proto_write_accessor<org::sem::CmdCustomRaw> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdCustomText, org::sem::CmdCustomText> {
  static void write(::orgproto::CmdCustomText* out, org::sem::CmdCustomText const& in);
  static void read(::orgproto::CmdCustomText const& out, proto_write_accessor<org::sem::CmdCustomText> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdResults, org::sem::CmdResults> {
  static void write(::orgproto::CmdResults* out, org::sem::CmdResults const& in);
  static void read(::orgproto::CmdResults const& out, proto_write_accessor<org::sem::CmdResults> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdTblfm, org::sem::CmdTblfm> {
  static void write(::orgproto::CmdTblfm* out, org::sem::CmdTblfm const& in);
  static void read(::orgproto::CmdTblfm const& out, proto_write_accessor<org::sem::CmdTblfm> in);
};


template <>
struct org::algo::proto_serde<::orgproto::HashTag, org::sem::HashTag> {
  static void write(::orgproto::HashTag* out, org::sem::HashTag const& in);
  static void read(::orgproto::HashTag const& out, proto_write_accessor<org::sem::HashTag> in);
};


template <>
struct org::algo::proto_serde<::orgproto::InlineFootnote, org::sem::InlineFootnote> {
  static void write(::orgproto::InlineFootnote* out, org::sem::InlineFootnote const& in);
  static void read(::orgproto::InlineFootnote const& out, proto_write_accessor<org::sem::InlineFootnote> in);
};


template <>
struct org::algo::proto_serde<::orgproto::InlineExport, org::sem::InlineExport> {
  static void write(::orgproto::InlineExport* out, org::sem::InlineExport const& in);
  static void read(::orgproto::InlineExport const& out, proto_write_accessor<org::sem::InlineExport> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Time::Repeat, org::sem::Time::Repeat> {
  static void write(::orgproto::Time::Repeat* out, org::sem::Time::Repeat const& in);
  static void read(::orgproto::Time::Repeat const& out, proto_write_accessor<org::sem::Time::Repeat> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Time::Static, org::sem::Time::Static> {
  static void write(::orgproto::Time::Static* out, org::sem::Time::Static const& in);
  static void read(::orgproto::Time::Static const& out, proto_write_accessor<org::sem::Time::Static> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Time::Dynamic, org::sem::Time::Dynamic> {
  static void write(::orgproto::Time::Dynamic* out, org::sem::Time::Dynamic const& in);
  static void read(::orgproto::Time::Dynamic const& out, proto_write_accessor<org::sem::Time::Dynamic> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Time, org::sem::Time> {
  static void write(::orgproto::Time* out, org::sem::Time const& in);
  static void read(::orgproto::Time const& out, proto_write_accessor<org::sem::Time> in);
};


template <>
struct org::algo::proto_serde<::orgproto::TimeRange, org::sem::TimeRange> {
  static void write(::orgproto::TimeRange* out, org::sem::TimeRange const& in);
  static void read(::orgproto::TimeRange const& out, proto_write_accessor<org::sem::TimeRange> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Macro, org::sem::Macro> {
  static void write(::orgproto::Macro* out, org::sem::Macro const& in);
  static void read(::orgproto::Macro const& out, proto_write_accessor<org::sem::Macro> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Symbol::Param, org::sem::Symbol::Param> {
  static void write(::orgproto::Symbol::Param* out, org::sem::Symbol::Param const& in);
  static void read(::orgproto::Symbol::Param const& out, proto_write_accessor<org::sem::Symbol::Param> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Symbol, org::sem::Symbol> {
  static void write(::orgproto::Symbol* out, org::sem::Symbol const& in);
  static void read(::orgproto::Symbol const& out, proto_write_accessor<org::sem::Symbol> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Escaped, org::sem::Escaped> {
  static void write(::orgproto::Escaped* out, org::sem::Escaped const& in);
  static void read(::orgproto::Escaped const& out, proto_write_accessor<org::sem::Escaped> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Newline, org::sem::Newline> {
  static void write(::orgproto::Newline* out, org::sem::Newline const& in);
  static void read(::orgproto::Newline const& out, proto_write_accessor<org::sem::Newline> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Space, org::sem::Space> {
  static void write(::orgproto::Space* out, org::sem::Space const& in);
  static void read(::orgproto::Space const& out, proto_write_accessor<org::sem::Space> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Word, org::sem::Word> {
  static void write(::orgproto::Word* out, org::sem::Word const& in);
  static void read(::orgproto::Word const& out, proto_write_accessor<org::sem::Word> in);
};


template <>
struct org::algo::proto_serde<::orgproto::AtMention, org::sem::AtMention> {
  static void write(::orgproto::AtMention* out, org::sem::AtMention const& in);
  static void read(::orgproto::AtMention const& out, proto_write_accessor<org::sem::AtMention> in);
};


template <>
struct org::algo::proto_serde<::orgproto::RawText, org::sem::RawText> {
  static void write(::orgproto::RawText* out, org::sem::RawText const& in);
  static void read(::orgproto::RawText const& out, proto_write_accessor<org::sem::RawText> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Punctuation, org::sem::Punctuation> {
  static void write(::orgproto::Punctuation* out, org::sem::Punctuation const& in);
  static void read(::orgproto::Punctuation const& out, proto_write_accessor<org::sem::Punctuation> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Placeholder, org::sem::Placeholder> {
  static void write(::orgproto::Placeholder* out, org::sem::Placeholder const& in);
  static void read(::orgproto::Placeholder const& out, proto_write_accessor<org::sem::Placeholder> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BigIdent, org::sem::BigIdent> {
  static void write(::orgproto::BigIdent* out, org::sem::BigIdent const& in);
  static void read(::orgproto::BigIdent const& out, proto_write_accessor<org::sem::BigIdent> in);
};


template <>
struct org::algo::proto_serde<::orgproto::TextTarget, org::sem::TextTarget> {
  static void write(::orgproto::TextTarget* out, org::sem::TextTarget const& in);
  static void read(::orgproto::TextTarget const& out, proto_write_accessor<org::sem::TextTarget> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Bold, org::sem::Bold> {
  static void write(::orgproto::Bold* out, org::sem::Bold const& in);
  static void read(::orgproto::Bold const& out, proto_write_accessor<org::sem::Bold> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Underline, org::sem::Underline> {
  static void write(::orgproto::Underline* out, org::sem::Underline const& in);
  static void read(::orgproto::Underline const& out, proto_write_accessor<org::sem::Underline> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Monospace, org::sem::Monospace> {
  static void write(::orgproto::Monospace* out, org::sem::Monospace const& in);
  static void read(::orgproto::Monospace const& out, proto_write_accessor<org::sem::Monospace> in);
};


template <>
struct org::algo::proto_serde<::orgproto::MarkQuote, org::sem::MarkQuote> {
  static void write(::orgproto::MarkQuote* out, org::sem::MarkQuote const& in);
  static void read(::orgproto::MarkQuote const& out, proto_write_accessor<org::sem::MarkQuote> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Verbatim, org::sem::Verbatim> {
  static void write(::orgproto::Verbatim* out, org::sem::Verbatim const& in);
  static void read(::orgproto::Verbatim const& out, proto_write_accessor<org::sem::Verbatim> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Italic, org::sem::Italic> {
  static void write(::orgproto::Italic* out, org::sem::Italic const& in);
  static void read(::orgproto::Italic const& out, proto_write_accessor<org::sem::Italic> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Strike, org::sem::Strike> {
  static void write(::orgproto::Strike* out, org::sem::Strike const& in);
  static void read(::orgproto::Strike const& out, proto_write_accessor<org::sem::Strike> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Par, org::sem::Par> {
  static void write(::orgproto::Par* out, org::sem::Par const& in);
  static void read(::orgproto::Par const& out, proto_write_accessor<org::sem::Par> in);
};


template <>
struct org::algo::proto_serde<::orgproto::RadioTarget, org::sem::RadioTarget> {
  static void write(::orgproto::RadioTarget* out, org::sem::RadioTarget const& in);
  static void read(::orgproto::RadioTarget const& out, proto_write_accessor<org::sem::RadioTarget> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Latex, org::sem::Latex> {
  static void write(::orgproto::Latex* out, org::sem::Latex const& in);
  static void read(::orgproto::Latex const& out, proto_write_accessor<org::sem::Latex> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Link, org::sem::Link> {
  static void write(::orgproto::Link* out, org::sem::Link const& in);
  static void read(::orgproto::Link const& out, proto_write_accessor<org::sem::Link> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCenter, org::sem::BlockCenter> {
  static void write(::orgproto::BlockCenter* out, org::sem::BlockCenter const& in);
  static void read(::orgproto::BlockCenter const& out, proto_write_accessor<org::sem::BlockCenter> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockQuote, org::sem::BlockQuote> {
  static void write(::orgproto::BlockQuote* out, org::sem::BlockQuote const& in);
  static void read(::orgproto::BlockQuote const& out, proto_write_accessor<org::sem::BlockQuote> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockComment, org::sem::BlockComment> {
  static void write(::orgproto::BlockComment* out, org::sem::BlockComment const& in);
  static void read(::orgproto::BlockComment const& out, proto_write_accessor<org::sem::BlockComment> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockVerse, org::sem::BlockVerse> {
  static void write(::orgproto::BlockVerse* out, org::sem::BlockVerse const& in);
  static void read(::orgproto::BlockVerse const& out, proto_write_accessor<org::sem::BlockVerse> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockDynamicFallback, org::sem::BlockDynamicFallback> {
  static void write(::orgproto::BlockDynamicFallback* out, org::sem::BlockDynamicFallback const& in);
  static void read(::orgproto::BlockDynamicFallback const& out, proto_write_accessor<org::sem::BlockDynamicFallback> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockExample, org::sem::BlockExample> {
  static void write(::orgproto::BlockExample* out, org::sem::BlockExample const& in);
  static void read(::orgproto::BlockExample const& out, proto_write_accessor<org::sem::BlockExample> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockExport, org::sem::BlockExport> {
  static void write(::orgproto::BlockExport* out, org::sem::BlockExport const& in);
  static void read(::orgproto::BlockExport const& out, proto_write_accessor<org::sem::BlockExport> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockAdmonition, org::sem::BlockAdmonition> {
  static void write(::orgproto::BlockAdmonition* out, org::sem::BlockAdmonition const& in);
  static void read(::orgproto::BlockAdmonition const& out, proto_write_accessor<org::sem::BlockAdmonition> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCodeEvalResult, org::sem::BlockCodeEvalResult> {
  static void write(::orgproto::BlockCodeEvalResult* out, org::sem::BlockCodeEvalResult const& in);
  static void read(::orgproto::BlockCodeEvalResult const& out, proto_write_accessor<org::sem::BlockCodeEvalResult> in);
};


template <>
struct org::algo::proto_serde<::orgproto::BlockCode, org::sem::BlockCode> {
  static void write(::orgproto::BlockCode* out, org::sem::BlockCode const& in);
  static void read(::orgproto::BlockCode const& out, proto_write_accessor<org::sem::BlockCode> in);
};


template <>
struct org::algo::proto_serde<::orgproto::SubtreeLog, org::sem::SubtreeLog> {
  static void write(::orgproto::SubtreeLog* out, org::sem::SubtreeLog const& in);
  static void read(::orgproto::SubtreeLog const& out, proto_write_accessor<org::sem::SubtreeLog> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Subtree, org::sem::Subtree> {
  static void write(::orgproto::Subtree* out, org::sem::Subtree const& in);
  static void read(::orgproto::Subtree const& out, proto_write_accessor<org::sem::Subtree> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Cell, org::sem::Cell> {
  static void write(::orgproto::Cell* out, org::sem::Cell const& in);
  static void read(::orgproto::Cell const& out, proto_write_accessor<org::sem::Cell> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Row, org::sem::Row> {
  static void write(::orgproto::Row* out, org::sem::Row const& in);
  static void read(::orgproto::Row const& out, proto_write_accessor<org::sem::Row> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Table, org::sem::Table> {
  static void write(::orgproto::Table* out, org::sem::Table const& in);
  static void read(::orgproto::Table const& out, proto_write_accessor<org::sem::Table> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Paragraph, org::sem::Paragraph> {
  static void write(::orgproto::Paragraph* out, org::sem::Paragraph const& in);
  static void read(::orgproto::Paragraph const& out, proto_write_accessor<org::sem::Paragraph> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ColonExample, org::sem::ColonExample> {
  static void write(::orgproto::ColonExample* out, org::sem::ColonExample const& in);
  static void read(::orgproto::ColonExample const& out, proto_write_accessor<org::sem::ColonExample> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdAttr, org::sem::CmdAttr> {
  static void write(::orgproto::CmdAttr* out, org::sem::CmdAttr const& in);
  static void read(::orgproto::CmdAttr const& out, proto_write_accessor<org::sem::CmdAttr> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdExport, org::sem::CmdExport> {
  static void write(::orgproto::CmdExport* out, org::sem::CmdExport const& in);
  static void read(::orgproto::CmdExport const& out, proto_write_accessor<org::sem::CmdExport> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Call, org::sem::Call> {
  static void write(::orgproto::Call* out, org::sem::Call const& in);
  static void read(::orgproto::Call const& out, proto_write_accessor<org::sem::Call> in);
};


template <>
struct org::algo::proto_serde<::orgproto::List, org::sem::List> {
  static void write(::orgproto::List* out, org::sem::List const& in);
  static void read(::orgproto::List const& out, proto_write_accessor<org::sem::List> in);
};


template <>
struct org::algo::proto_serde<::orgproto::ListItem, org::sem::ListItem> {
  static void write(::orgproto::ListItem* out, org::sem::ListItem const& in);
  static void read(::orgproto::ListItem const& out, proto_write_accessor<org::sem::ListItem> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentOptions, org::sem::DocumentOptions> {
  static void write(::orgproto::DocumentOptions* out, org::sem::DocumentOptions const& in);
  static void read(::orgproto::DocumentOptions const& out, proto_write_accessor<org::sem::DocumentOptions> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Document, org::sem::Document> {
  static void write(::orgproto::Document* out, org::sem::Document const& in);
  static void read(::orgproto::Document const& out, proto_write_accessor<org::sem::Document> in);
};


template <>
struct org::algo::proto_serde<::orgproto::FileTarget, org::sem::FileTarget> {
  static void write(::orgproto::FileTarget* out, org::sem::FileTarget const& in);
  static void read(::orgproto::FileTarget const& out, proto_write_accessor<org::sem::FileTarget> in);
};


template <>
struct org::algo::proto_serde<::orgproto::TextSeparator, org::sem::TextSeparator> {
  static void write(::orgproto::TextSeparator* out, org::sem::TextSeparator const& in);
  static void read(::orgproto::TextSeparator const& out, proto_write_accessor<org::sem::TextSeparator> in);
};


template <>
struct org::algo::proto_serde<::orgproto::DocumentGroup, org::sem::DocumentGroup> {
  static void write(::orgproto::DocumentGroup* out, org::sem::DocumentGroup const& in);
  static void read(::orgproto::DocumentGroup const& out, proto_write_accessor<org::sem::DocumentGroup> in);
};


template <>
struct org::algo::proto_serde<::orgproto::File::Document, org::sem::File::Document> {
  static void write(::orgproto::File::Document* out, org::sem::File::Document const& in);
  static void read(::orgproto::File::Document const& out, proto_write_accessor<org::sem::File::Document> in);
};


template <>
struct org::algo::proto_serde<::orgproto::File::Attachment, org::sem::File::Attachment> {
  static void write(::orgproto::File::Attachment* out, org::sem::File::Attachment const& in);
  static void read(::orgproto::File::Attachment const& out, proto_write_accessor<org::sem::File::Attachment> in);
};


template <>
struct org::algo::proto_serde<::orgproto::File::Source, org::sem::File::Source> {
  static void write(::orgproto::File::Source* out, org::sem::File::Source const& in);
  static void read(::orgproto::File::Source const& out, proto_write_accessor<org::sem::File::Source> in);
};


template <>
struct org::algo::proto_serde<::orgproto::File, org::sem::File> {
  static void write(::orgproto::File* out, org::sem::File const& in);
  static void read(::orgproto::File const& out, proto_write_accessor<org::sem::File> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Directory, org::sem::Directory> {
  static void write(::orgproto::Directory* out, org::sem::Directory const& in);
  static void read(::orgproto::Directory const& out, proto_write_accessor<org::sem::Directory> in);
};


template <>
struct org::algo::proto_serde<::orgproto::Symlink, org::sem::Symlink> {
  static void write(::orgproto::Symlink* out, org::sem::Symlink const& in);
  static void read(::orgproto::Symlink const& out, proto_write_accessor<org::sem::Symlink> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase> {
  static void write(::orgproto::CmdInclude::IncludeBase* out, org::sem::CmdInclude::IncludeBase const& in);
  static void read(::orgproto::CmdInclude::IncludeBase const& out, proto_write_accessor<org::sem::CmdInclude::IncludeBase> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::Example, org::sem::CmdInclude::Example> {
  static void write(::orgproto::CmdInclude::Example* out, org::sem::CmdInclude::Example const& in);
  static void read(::orgproto::CmdInclude::Example const& out, proto_write_accessor<org::sem::CmdInclude::Example> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::Export, org::sem::CmdInclude::Export> {
  static void write(::orgproto::CmdInclude::Export* out, org::sem::CmdInclude::Export const& in);
  static void read(::orgproto::CmdInclude::Export const& out, proto_write_accessor<org::sem::CmdInclude::Export> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::Custom, org::sem::CmdInclude::Custom> {
  static void write(::orgproto::CmdInclude::Custom* out, org::sem::CmdInclude::Custom const& in);
  static void read(::orgproto::CmdInclude::Custom const& out, proto_write_accessor<org::sem::CmdInclude::Custom> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::Src, org::sem::CmdInclude::Src> {
  static void write(::orgproto::CmdInclude::Src* out, org::sem::CmdInclude::Src const& in);
  static void read(::orgproto::CmdInclude::Src const& out, proto_write_accessor<org::sem::CmdInclude::Src> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument> {
  static void write(::orgproto::CmdInclude::OrgDocument* out, org::sem::CmdInclude::OrgDocument const& in);
  static void read(::orgproto::CmdInclude::OrgDocument const& out, proto_write_accessor<org::sem::CmdInclude::OrgDocument> in);
};


template <>
struct org::algo::proto_serde<::orgproto::CmdInclude, org::sem::CmdInclude> {
  static void write(::orgproto::CmdInclude* out, org::sem::CmdInclude const& in);
  static void read(::orgproto::CmdInclude const& out, proto_write_accessor<org::sem::CmdInclude> in);
};


/* clang-format on */