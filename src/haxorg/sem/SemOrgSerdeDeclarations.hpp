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
struct proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Index, sem::Tblfm::Expr::AxisRef::Position::Index> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position::Index* out, sem::Tblfm::Expr::AxisRef::Position::Index const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position::Index> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position::Name, sem::Tblfm::Expr::AxisRef::Position::Name> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position::Name* out, sem::Tblfm::Expr::AxisRef::Position::Name const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position::Name> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::AxisRef::Position, sem::Tblfm::Expr::AxisRef::Position> {
  static void write(::orgproto::Tblfm::Expr::AxisRef::Position* out, sem::Tblfm::Expr::AxisRef::Position const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef::Position> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::AxisRef, sem::Tblfm::Expr::AxisRef> {
  static void write(::orgproto::Tblfm::Expr::AxisRef* out, sem::Tblfm::Expr::AxisRef const& in);
  static void read(::orgproto::Tblfm::Expr::AxisRef const& out, proto_write_accessor<sem::Tblfm::Expr::AxisRef> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::AxisName, sem::Tblfm::Expr::AxisName> {
  static void write(::orgproto::Tblfm::Expr::AxisName* out, sem::Tblfm::Expr::AxisName const& in);
  static void read(::orgproto::Tblfm::Expr::AxisName const& out, proto_write_accessor<sem::Tblfm::Expr::AxisName> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::IntLiteral, sem::Tblfm::Expr::IntLiteral> {
  static void write(::orgproto::Tblfm::Expr::IntLiteral* out, sem::Tblfm::Expr::IntLiteral const& in);
  static void read(::orgproto::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<sem::Tblfm::Expr::IntLiteral> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::FloatLiteral, sem::Tblfm::Expr::FloatLiteral> {
  static void write(::orgproto::Tblfm::Expr::FloatLiteral* out, sem::Tblfm::Expr::FloatLiteral const& in);
  static void read(::orgproto::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<sem::Tblfm::Expr::FloatLiteral> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::RangeRef, sem::Tblfm::Expr::RangeRef> {
  static void write(::orgproto::Tblfm::Expr::RangeRef* out, sem::Tblfm::Expr::RangeRef const& in);
  static void read(::orgproto::Tblfm::Expr::RangeRef const& out, proto_write_accessor<sem::Tblfm::Expr::RangeRef> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::Call, sem::Tblfm::Expr::Call> {
  static void write(::orgproto::Tblfm::Expr::Call* out, sem::Tblfm::Expr::Call const& in);
  static void read(::orgproto::Tblfm::Expr::Call const& out, proto_write_accessor<sem::Tblfm::Expr::Call> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr::Elisp, sem::Tblfm::Expr::Elisp> {
  static void write(::orgproto::Tblfm::Expr::Elisp* out, sem::Tblfm::Expr::Elisp const& in);
  static void read(::orgproto::Tblfm::Expr::Elisp const& out, proto_write_accessor<sem::Tblfm::Expr::Elisp> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Expr, sem::Tblfm::Expr> {
  static void write(::orgproto::Tblfm::Expr* out, sem::Tblfm::Expr const& in);
  static void read(::orgproto::Tblfm::Expr const& out, proto_write_accessor<sem::Tblfm::Expr> in);
};


template <>
struct proto_serde<::orgproto::Tblfm::Assign, sem::Tblfm::Assign> {
  static void write(::orgproto::Tblfm::Assign* out, sem::Tblfm::Assign const& in);
  static void read(::orgproto::Tblfm::Assign const& out, proto_write_accessor<sem::Tblfm::Assign> in);
};


template <>
struct proto_serde<::orgproto::Tblfm, sem::Tblfm> {
  static void write(::orgproto::Tblfm* out, sem::Tblfm const& in);
  static void read(::orgproto::Tblfm const& out, proto_write_accessor<sem::Tblfm> in);
};


template <>
struct proto_serde<::orgproto::AttrValue, sem::AttrValue> {
  static void write(::orgproto::AttrValue* out, sem::AttrValue const& in);
  static void read(::orgproto::AttrValue const& out, proto_write_accessor<sem::AttrValue> in);
};


template <>
struct proto_serde<::orgproto::HashTagFlat, sem::HashTagFlat> {
  static void write(::orgproto::HashTagFlat* out, sem::HashTagFlat const& in);
  static void read(::orgproto::HashTagFlat const& out, proto_write_accessor<sem::HashTagFlat> in);
};


template <>
struct proto_serde<::orgproto::HashTagText, sem::HashTagText> {
  static void write(::orgproto::HashTagText* out, sem::HashTagText const& in);
  static void read(::orgproto::HashTagText const& out, proto_write_accessor<sem::HashTagText> in);
};


template <>
struct proto_serde<::orgproto::SubtreePath, sem::SubtreePath> {
  static void write(::orgproto::SubtreePath* out, sem::SubtreePath const& in);
  static void read(::orgproto::SubtreePath const& out, proto_write_accessor<sem::SubtreePath> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Raw, sem::LinkTarget::Raw> {
  static void write(::orgproto::LinkTarget::Raw* out, sem::LinkTarget::Raw const& in);
  static void read(::orgproto::LinkTarget::Raw const& out, proto_write_accessor<sem::LinkTarget::Raw> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Id, sem::LinkTarget::Id> {
  static void write(::orgproto::LinkTarget::Id* out, sem::LinkTarget::Id const& in);
  static void read(::orgproto::LinkTarget::Id const& out, proto_write_accessor<sem::LinkTarget::Id> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::CustomId, sem::LinkTarget::CustomId> {
  static void write(::orgproto::LinkTarget::CustomId* out, sem::LinkTarget::CustomId const& in);
  static void read(::orgproto::LinkTarget::CustomId const& out, proto_write_accessor<sem::LinkTarget::CustomId> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::SubtreeTitle, sem::LinkTarget::SubtreeTitle> {
  static void write(::orgproto::LinkTarget::SubtreeTitle* out, sem::LinkTarget::SubtreeTitle const& in);
  static void read(::orgproto::LinkTarget::SubtreeTitle const& out, proto_write_accessor<sem::LinkTarget::SubtreeTitle> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Person, sem::LinkTarget::Person> {
  static void write(::orgproto::LinkTarget::Person* out, sem::LinkTarget::Person const& in);
  static void read(::orgproto::LinkTarget::Person const& out, proto_write_accessor<sem::LinkTarget::Person> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::UserProtocol, sem::LinkTarget::UserProtocol> {
  static void write(::orgproto::LinkTarget::UserProtocol* out, sem::LinkTarget::UserProtocol const& in);
  static void read(::orgproto::LinkTarget::UserProtocol const& out, proto_write_accessor<sem::LinkTarget::UserProtocol> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Internal, sem::LinkTarget::Internal> {
  static void write(::orgproto::LinkTarget::Internal* out, sem::LinkTarget::Internal const& in);
  static void read(::orgproto::LinkTarget::Internal const& out, proto_write_accessor<sem::LinkTarget::Internal> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Footnote, sem::LinkTarget::Footnote> {
  static void write(::orgproto::LinkTarget::Footnote* out, sem::LinkTarget::Footnote const& in);
  static void read(::orgproto::LinkTarget::Footnote const& out, proto_write_accessor<sem::LinkTarget::Footnote> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::File, sem::LinkTarget::File> {
  static void write(::orgproto::LinkTarget::File* out, sem::LinkTarget::File const& in);
  static void read(::orgproto::LinkTarget::File const& out, proto_write_accessor<sem::LinkTarget::File> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget::Attachment, sem::LinkTarget::Attachment> {
  static void write(::orgproto::LinkTarget::Attachment* out, sem::LinkTarget::Attachment const& in);
  static void read(::orgproto::LinkTarget::Attachment const& out, proto_write_accessor<sem::LinkTarget::Attachment> in);
};


template <>
struct proto_serde<::orgproto::LinkTarget, sem::LinkTarget> {
  static void write(::orgproto::LinkTarget* out, sem::LinkTarget const& in);
  static void read(::orgproto::LinkTarget const& out, proto_write_accessor<sem::LinkTarget> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Priority, sem::SubtreeLogHead::Priority> {
  static void write(::orgproto::SubtreeLogHead::Priority* out, sem::SubtreeLogHead::Priority const& in);
  static void read(::orgproto::SubtreeLogHead::Priority const& out, proto_write_accessor<sem::SubtreeLogHead::Priority> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Note, sem::SubtreeLogHead::Note> {
  static void write(::orgproto::SubtreeLogHead::Note* out, sem::SubtreeLogHead::Note const& in);
  static void read(::orgproto::SubtreeLogHead::Note const& out, proto_write_accessor<sem::SubtreeLogHead::Note> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Refile, sem::SubtreeLogHead::Refile> {
  static void write(::orgproto::SubtreeLogHead::Refile* out, sem::SubtreeLogHead::Refile const& in);
  static void read(::orgproto::SubtreeLogHead::Refile const& out, proto_write_accessor<sem::SubtreeLogHead::Refile> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Clock, sem::SubtreeLogHead::Clock> {
  static void write(::orgproto::SubtreeLogHead::Clock* out, sem::SubtreeLogHead::Clock const& in);
  static void read(::orgproto::SubtreeLogHead::Clock const& out, proto_write_accessor<sem::SubtreeLogHead::Clock> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::State, sem::SubtreeLogHead::State> {
  static void write(::orgproto::SubtreeLogHead::State* out, sem::SubtreeLogHead::State const& in);
  static void read(::orgproto::SubtreeLogHead::State const& out, proto_write_accessor<sem::SubtreeLogHead::State> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Deadline, sem::SubtreeLogHead::Deadline> {
  static void write(::orgproto::SubtreeLogHead::Deadline* out, sem::SubtreeLogHead::Deadline const& in);
  static void read(::orgproto::SubtreeLogHead::Deadline const& out, proto_write_accessor<sem::SubtreeLogHead::Deadline> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Schedule, sem::SubtreeLogHead::Schedule> {
  static void write(::orgproto::SubtreeLogHead::Schedule* out, sem::SubtreeLogHead::Schedule const& in);
  static void read(::orgproto::SubtreeLogHead::Schedule const& out, proto_write_accessor<sem::SubtreeLogHead::Schedule> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Tag, sem::SubtreeLogHead::Tag> {
  static void write(::orgproto::SubtreeLogHead::Tag* out, sem::SubtreeLogHead::Tag const& in);
  static void read(::orgproto::SubtreeLogHead::Tag const& out, proto_write_accessor<sem::SubtreeLogHead::Tag> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead::Unknown, sem::SubtreeLogHead::Unknown> {
  static void write(::orgproto::SubtreeLogHead::Unknown* out, sem::SubtreeLogHead::Unknown const& in);
  static void read(::orgproto::SubtreeLogHead::Unknown const& out, proto_write_accessor<sem::SubtreeLogHead::Unknown> in);
};


template <>
struct proto_serde<::orgproto::SubtreeLogHead, sem::SubtreeLogHead> {
  static void write(::orgproto::SubtreeLogHead* out, sem::SubtreeLogHead const& in);
  static void read(::orgproto::SubtreeLogHead const& out, proto_write_accessor<sem::SubtreeLogHead> in);
};


template <>
struct proto_serde<::orgproto::SubtreeCompletion, sem::SubtreeCompletion> {
  static void write(::orgproto::SubtreeCompletion* out, sem::SubtreeCompletion const& in);
  static void read(::orgproto::SubtreeCompletion const& out, proto_write_accessor<sem::SubtreeCompletion> in);
};


template <>
struct proto_serde<::orgproto::AttrList, sem::AttrList> {
  static void write(::orgproto::AttrList* out, sem::AttrList const& in);
  static void read(::orgproto::AttrList const& out, proto_write_accessor<sem::AttrList> in);
};


template <>
struct proto_serde<::orgproto::AttrGroup, sem::AttrGroup> {
  static void write(::orgproto::AttrGroup* out, sem::AttrGroup const& in);
  static void read(::orgproto::AttrGroup const& out, proto_write_accessor<sem::AttrGroup> in);
};


template <>
struct proto_serde<::orgproto::ColumnView::Summary::CheckboxAggregate, sem::ColumnView::Summary::CheckboxAggregate> {
  static void write(::orgproto::ColumnView::Summary::CheckboxAggregate* out, sem::ColumnView::Summary::CheckboxAggregate const& in);
  static void read(::orgproto::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<sem::ColumnView::Summary::CheckboxAggregate> in);
};


template <>
struct proto_serde<::orgproto::ColumnView::Summary::MathAggregate, sem::ColumnView::Summary::MathAggregate> {
  static void write(::orgproto::ColumnView::Summary::MathAggregate* out, sem::ColumnView::Summary::MathAggregate const& in);
  static void read(::orgproto::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<sem::ColumnView::Summary::MathAggregate> in);
};


template <>
struct proto_serde<::orgproto::ColumnView::Summary, sem::ColumnView::Summary> {
  static void write(::orgproto::ColumnView::Summary* out, sem::ColumnView::Summary const& in);
  static void read(::orgproto::ColumnView::Summary const& out, proto_write_accessor<sem::ColumnView::Summary> in);
};


template <>
struct proto_serde<::orgproto::ColumnView::Column, sem::ColumnView::Column> {
  static void write(::orgproto::ColumnView::Column* out, sem::ColumnView::Column const& in);
  static void read(::orgproto::ColumnView::Column const& out, proto_write_accessor<sem::ColumnView::Column> in);
};


template <>
struct proto_serde<::orgproto::ColumnView, sem::ColumnView> {
  static void write(::orgproto::ColumnView* out, sem::ColumnView const& in);
  static void read(::orgproto::ColumnView const& out, proto_write_accessor<sem::ColumnView> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeLine::Part::Raw, sem::BlockCodeLine::Part::Raw> {
  static void write(::orgproto::BlockCodeLine::Part::Raw* out, sem::BlockCodeLine::Part::Raw const& in);
  static void read(::orgproto::BlockCodeLine::Part::Raw const& out, proto_write_accessor<sem::BlockCodeLine::Part::Raw> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeLine::Part::Callout, sem::BlockCodeLine::Part::Callout> {
  static void write(::orgproto::BlockCodeLine::Part::Callout* out, sem::BlockCodeLine::Part::Callout const& in);
  static void read(::orgproto::BlockCodeLine::Part::Callout const& out, proto_write_accessor<sem::BlockCodeLine::Part::Callout> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeLine::Part::Tangle, sem::BlockCodeLine::Part::Tangle> {
  static void write(::orgproto::BlockCodeLine::Part::Tangle* out, sem::BlockCodeLine::Part::Tangle const& in);
  static void read(::orgproto::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<sem::BlockCodeLine::Part::Tangle> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeLine::Part, sem::BlockCodeLine::Part> {
  static void write(::orgproto::BlockCodeLine::Part* out, sem::BlockCodeLine::Part const& in);
  static void read(::orgproto::BlockCodeLine::Part const& out, proto_write_accessor<sem::BlockCodeLine::Part> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeLine, sem::BlockCodeLine> {
  static void write(::orgproto::BlockCodeLine* out, sem::BlockCodeLine const& in);
  static void read(::orgproto::BlockCodeLine const& out, proto_write_accessor<sem::BlockCodeLine> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch::LineStart, sem::BlockCodeSwitch::LineStart> {
  static void write(::orgproto::BlockCodeSwitch::LineStart* out, sem::BlockCodeSwitch::LineStart const& in);
  static void read(::orgproto::BlockCodeSwitch::LineStart const& out, proto_write_accessor<sem::BlockCodeSwitch::LineStart> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch::CalloutFormat, sem::BlockCodeSwitch::CalloutFormat> {
  static void write(::orgproto::BlockCodeSwitch::CalloutFormat* out, sem::BlockCodeSwitch::CalloutFormat const& in);
  static void read(::orgproto::BlockCodeSwitch::CalloutFormat const& out, proto_write_accessor<sem::BlockCodeSwitch::CalloutFormat> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch::RemoveCallout, sem::BlockCodeSwitch::RemoveCallout> {
  static void write(::orgproto::BlockCodeSwitch::RemoveCallout* out, sem::BlockCodeSwitch::RemoveCallout const& in);
  static void read(::orgproto::BlockCodeSwitch::RemoveCallout const& out, proto_write_accessor<sem::BlockCodeSwitch::RemoveCallout> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch::EmphasizeLine, sem::BlockCodeSwitch::EmphasizeLine> {
  static void write(::orgproto::BlockCodeSwitch::EmphasizeLine* out, sem::BlockCodeSwitch::EmphasizeLine const& in);
  static void read(::orgproto::BlockCodeSwitch::EmphasizeLine const& out, proto_write_accessor<sem::BlockCodeSwitch::EmphasizeLine> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch::Dedent, sem::BlockCodeSwitch::Dedent> {
  static void write(::orgproto::BlockCodeSwitch::Dedent* out, sem::BlockCodeSwitch::Dedent const& in);
  static void read(::orgproto::BlockCodeSwitch::Dedent const& out, proto_write_accessor<sem::BlockCodeSwitch::Dedent> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeSwitch, sem::BlockCodeSwitch> {
  static void write(::orgproto::BlockCodeSwitch* out, sem::BlockCodeSwitch const& in);
  static void read(::orgproto::BlockCodeSwitch const& out, proto_write_accessor<sem::BlockCodeSwitch> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeEvalResult::None, sem::BlockCodeEvalResult::None> {
  static void write(::orgproto::BlockCodeEvalResult::None* out, sem::BlockCodeEvalResult::None const& in);
  static void read(::orgproto::BlockCodeEvalResult::None const& out, proto_write_accessor<sem::BlockCodeEvalResult::None> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeEvalResult::OrgValue, sem::BlockCodeEvalResult::OrgValue> {
  static void write(::orgproto::BlockCodeEvalResult::OrgValue* out, sem::BlockCodeEvalResult::OrgValue const& in);
  static void read(::orgproto::BlockCodeEvalResult::OrgValue const& out, proto_write_accessor<sem::BlockCodeEvalResult::OrgValue> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeEvalResult::File, sem::BlockCodeEvalResult::File> {
  static void write(::orgproto::BlockCodeEvalResult::File* out, sem::BlockCodeEvalResult::File const& in);
  static void read(::orgproto::BlockCodeEvalResult::File const& out, proto_write_accessor<sem::BlockCodeEvalResult::File> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeEvalResult::Raw, sem::BlockCodeEvalResult::Raw> {
  static void write(::orgproto::BlockCodeEvalResult::Raw* out, sem::BlockCodeEvalResult::Raw const& in);
  static void read(::orgproto::BlockCodeEvalResult::Raw const& out, proto_write_accessor<sem::BlockCodeEvalResult::Raw> in);
};


template <>
struct proto_serde<::orgproto::BlockCodeEvalResult, sem::BlockCodeEvalResult> {
  static void write(::orgproto::BlockCodeEvalResult* out, sem::BlockCodeEvalResult const& in);
  static void read(::orgproto::BlockCodeEvalResult const& out, proto_write_accessor<sem::BlockCodeEvalResult> in);
};


template <>
struct proto_serde<::orgproto::DocumentExportConfig::TaskExport, sem::DocumentExportConfig::TaskExport> {
  static void write(::orgproto::DocumentExportConfig::TaskExport* out, sem::DocumentExportConfig::TaskExport const& in);
  static void read(::orgproto::DocumentExportConfig::TaskExport const& out, proto_write_accessor<sem::DocumentExportConfig::TaskExport> in);
};


template <>
struct proto_serde<::orgproto::DocumentExportConfig::DoExport, sem::DocumentExportConfig::DoExport> {
  static void write(::orgproto::DocumentExportConfig::DoExport* out, sem::DocumentExportConfig::DoExport const& in);
  static void read(::orgproto::DocumentExportConfig::DoExport const& out, proto_write_accessor<sem::DocumentExportConfig::DoExport> in);
};


template <>
struct proto_serde<::orgproto::DocumentExportConfig::ExportFixed, sem::DocumentExportConfig::ExportFixed> {
  static void write(::orgproto::DocumentExportConfig::ExportFixed* out, sem::DocumentExportConfig::ExportFixed const& in);
  static void read(::orgproto::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<sem::DocumentExportConfig::ExportFixed> in);
};


template <>
struct proto_serde<::orgproto::DocumentExportConfig, sem::DocumentExportConfig> {
  static void write(::orgproto::DocumentExportConfig* out, sem::DocumentExportConfig const& in);
  static void read(::orgproto::DocumentExportConfig const& out, proto_write_accessor<sem::DocumentExportConfig> in);
};


template <>
struct proto_serde<::orgproto::SubtreePeriod, sem::SubtreePeriod> {
  static void write(::orgproto::SubtreePeriod* out, sem::SubtreePeriod const& in);
  static void read(::orgproto::SubtreePeriod const& out, proto_write_accessor<sem::SubtreePeriod> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Nonblocking, sem::NamedProperty::Nonblocking> {
  static void write(::orgproto::NamedProperty::Nonblocking* out, sem::NamedProperty::Nonblocking const& in);
  static void read(::orgproto::NamedProperty::Nonblocking const& out, proto_write_accessor<sem::NamedProperty::Nonblocking> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveTime, sem::NamedProperty::ArchiveTime> {
  static void write(::orgproto::NamedProperty::ArchiveTime* out, sem::NamedProperty::ArchiveTime const& in);
  static void read(::orgproto::NamedProperty::ArchiveTime const& out, proto_write_accessor<sem::NamedProperty::ArchiveTime> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveFile, sem::NamedProperty::ArchiveFile> {
  static void write(::orgproto::NamedProperty::ArchiveFile* out, sem::NamedProperty::ArchiveFile const& in);
  static void read(::orgproto::NamedProperty::ArchiveFile const& out, proto_write_accessor<sem::NamedProperty::ArchiveFile> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveOlpath, sem::NamedProperty::ArchiveOlpath> {
  static void write(::orgproto::NamedProperty::ArchiveOlpath* out, sem::NamedProperty::ArchiveOlpath const& in);
  static void read(::orgproto::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<sem::NamedProperty::ArchiveOlpath> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveTarget, sem::NamedProperty::ArchiveTarget> {
  static void write(::orgproto::NamedProperty::ArchiveTarget* out, sem::NamedProperty::ArchiveTarget const& in);
  static void read(::orgproto::NamedProperty::ArchiveTarget const& out, proto_write_accessor<sem::NamedProperty::ArchiveTarget> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveCategory, sem::NamedProperty::ArchiveCategory> {
  static void write(::orgproto::NamedProperty::ArchiveCategory* out, sem::NamedProperty::ArchiveCategory const& in);
  static void read(::orgproto::NamedProperty::ArchiveCategory const& out, proto_write_accessor<sem::NamedProperty::ArchiveCategory> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ArchiveTodo, sem::NamedProperty::ArchiveTodo> {
  static void write(::orgproto::NamedProperty::ArchiveTodo* out, sem::NamedProperty::ArchiveTodo const& in);
  static void read(::orgproto::NamedProperty::ArchiveTodo const& out, proto_write_accessor<sem::NamedProperty::ArchiveTodo> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Trigger, sem::NamedProperty::Trigger> {
  static void write(::orgproto::NamedProperty::Trigger* out, sem::NamedProperty::Trigger const& in);
  static void read(::orgproto::NamedProperty::Trigger const& out, proto_write_accessor<sem::NamedProperty::Trigger> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ExportLatexClass, sem::NamedProperty::ExportLatexClass> {
  static void write(::orgproto::NamedProperty::ExportLatexClass* out, sem::NamedProperty::ExportLatexClass const& in);
  static void read(::orgproto::NamedProperty::ExportLatexClass const& out, proto_write_accessor<sem::NamedProperty::ExportLatexClass> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::CookieData, sem::NamedProperty::CookieData> {
  static void write(::orgproto::NamedProperty::CookieData* out, sem::NamedProperty::CookieData const& in);
  static void read(::orgproto::NamedProperty::CookieData const& out, proto_write_accessor<sem::NamedProperty::CookieData> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ExportLatexClassOptions, sem::NamedProperty::ExportLatexClassOptions> {
  static void write(::orgproto::NamedProperty::ExportLatexClassOptions* out, sem::NamedProperty::ExportLatexClassOptions const& in);
  static void read(::orgproto::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<sem::NamedProperty::ExportLatexClassOptions> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ExportLatexHeader, sem::NamedProperty::ExportLatexHeader> {
  static void write(::orgproto::NamedProperty::ExportLatexHeader* out, sem::NamedProperty::ExportLatexHeader const& in);
  static void read(::orgproto::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<sem::NamedProperty::ExportLatexHeader> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ExportLatexCompiler, sem::NamedProperty::ExportLatexCompiler> {
  static void write(::orgproto::NamedProperty::ExportLatexCompiler* out, sem::NamedProperty::ExportLatexCompiler const& in);
  static void read(::orgproto::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<sem::NamedProperty::ExportLatexCompiler> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Ordered, sem::NamedProperty::Ordered> {
  static void write(::orgproto::NamedProperty::Ordered* out, sem::NamedProperty::Ordered const& in);
  static void read(::orgproto::NamedProperty::Ordered const& out, proto_write_accessor<sem::NamedProperty::Ordered> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Effort, sem::NamedProperty::Effort> {
  static void write(::orgproto::NamedProperty::Effort* out, sem::NamedProperty::Effort const& in);
  static void read(::orgproto::NamedProperty::Effort const& out, proto_write_accessor<sem::NamedProperty::Effort> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Visibility, sem::NamedProperty::Visibility> {
  static void write(::orgproto::NamedProperty::Visibility* out, sem::NamedProperty::Visibility const& in);
  static void read(::orgproto::NamedProperty::Visibility const& out, proto_write_accessor<sem::NamedProperty::Visibility> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::ExportOptions, sem::NamedProperty::ExportOptions> {
  static void write(::orgproto::NamedProperty::ExportOptions* out, sem::NamedProperty::ExportOptions const& in);
  static void read(::orgproto::NamedProperty::ExportOptions const& out, proto_write_accessor<sem::NamedProperty::ExportOptions> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Blocker, sem::NamedProperty::Blocker> {
  static void write(::orgproto::NamedProperty::Blocker* out, sem::NamedProperty::Blocker const& in);
  static void read(::orgproto::NamedProperty::Blocker const& out, proto_write_accessor<sem::NamedProperty::Blocker> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Unnumbered, sem::NamedProperty::Unnumbered> {
  static void write(::orgproto::NamedProperty::Unnumbered* out, sem::NamedProperty::Unnumbered const& in);
  static void read(::orgproto::NamedProperty::Unnumbered const& out, proto_write_accessor<sem::NamedProperty::Unnumbered> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::Created, sem::NamedProperty::Created> {
  static void write(::orgproto::NamedProperty::Created* out, sem::NamedProperty::Created const& in);
  static void read(::orgproto::NamedProperty::Created const& out, proto_write_accessor<sem::NamedProperty::Created> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::RadioId, sem::NamedProperty::RadioId> {
  static void write(::orgproto::NamedProperty::RadioId* out, sem::NamedProperty::RadioId const& in);
  static void read(::orgproto::NamedProperty::RadioId const& out, proto_write_accessor<sem::NamedProperty::RadioId> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::HashtagDef, sem::NamedProperty::HashtagDef> {
  static void write(::orgproto::NamedProperty::HashtagDef* out, sem::NamedProperty::HashtagDef const& in);
  static void read(::orgproto::NamedProperty::HashtagDef const& out, proto_write_accessor<sem::NamedProperty::HashtagDef> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::CustomArgs, sem::NamedProperty::CustomArgs> {
  static void write(::orgproto::NamedProperty::CustomArgs* out, sem::NamedProperty::CustomArgs const& in);
  static void read(::orgproto::NamedProperty::CustomArgs const& out, proto_write_accessor<sem::NamedProperty::CustomArgs> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::CustomRaw, sem::NamedProperty::CustomRaw> {
  static void write(::orgproto::NamedProperty::CustomRaw* out, sem::NamedProperty::CustomRaw const& in);
  static void read(::orgproto::NamedProperty::CustomRaw const& out, proto_write_accessor<sem::NamedProperty::CustomRaw> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::CustomSubtreeJson, sem::NamedProperty::CustomSubtreeJson> {
  static void write(::orgproto::NamedProperty::CustomSubtreeJson* out, sem::NamedProperty::CustomSubtreeJson const& in);
  static void read(::orgproto::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<sem::NamedProperty::CustomSubtreeJson> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty::CustomSubtreeFlags, sem::NamedProperty::CustomSubtreeFlags> {
  static void write(::orgproto::NamedProperty::CustomSubtreeFlags* out, sem::NamedProperty::CustomSubtreeFlags const& in);
  static void read(::orgproto::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<sem::NamedProperty::CustomSubtreeFlags> in);
};


template <>
struct proto_serde<::orgproto::NamedProperty, sem::NamedProperty> {
  static void write(::orgproto::NamedProperty* out, sem::NamedProperty const& in);
  static void read(::orgproto::NamedProperty const& out, proto_write_accessor<sem::NamedProperty> in);
};


template <>
struct proto_serde<::orgproto::org::None, org::sem::None> {
  static void write(::orgproto::org::None* out, org::sem::None const& in);
  static void read(::orgproto::org::None const& out, proto_write_accessor<org::sem::None> in);
};


template <>
struct proto_serde<::orgproto::org::ErrorItem, org::sem::ErrorItem> {
  static void write(::orgproto::org::ErrorItem* out, org::sem::ErrorItem const& in);
  static void read(::orgproto::org::ErrorItem const& out, proto_write_accessor<org::sem::ErrorItem> in);
};


template <>
struct proto_serde<::orgproto::org::ErrorGroup, org::sem::ErrorGroup> {
  static void write(::orgproto::org::ErrorGroup* out, org::sem::ErrorGroup const& in);
  static void read(::orgproto::org::ErrorGroup const& out, proto_write_accessor<org::sem::ErrorGroup> in);
};


template <>
struct proto_serde<::orgproto::org::StmtList, org::sem::StmtList> {
  static void write(::orgproto::org::StmtList* out, org::sem::StmtList const& in);
  static void read(::orgproto::org::StmtList const& out, proto_write_accessor<org::sem::StmtList> in);
};


template <>
struct proto_serde<::orgproto::org::Empty, org::sem::Empty> {
  static void write(::orgproto::org::Empty* out, org::sem::Empty const& in);
  static void read(::orgproto::org::Empty const& out, proto_write_accessor<org::sem::Empty> in);
};


template <>
struct proto_serde<::orgproto::org::CmdCaption, org::sem::CmdCaption> {
  static void write(::orgproto::org::CmdCaption* out, org::sem::CmdCaption const& in);
  static void read(::orgproto::org::CmdCaption const& out, proto_write_accessor<org::sem::CmdCaption> in);
};


template <>
struct proto_serde<::orgproto::org::CmdColumns, org::sem::CmdColumns> {
  static void write(::orgproto::org::CmdColumns* out, org::sem::CmdColumns const& in);
  static void read(::orgproto::org::CmdColumns const& out, proto_write_accessor<org::sem::CmdColumns> in);
};


template <>
struct proto_serde<::orgproto::org::CmdName, org::sem::CmdName> {
  static void write(::orgproto::org::CmdName* out, org::sem::CmdName const& in);
  static void read(::orgproto::org::CmdName const& out, proto_write_accessor<org::sem::CmdName> in);
};


template <>
struct proto_serde<::orgproto::org::CmdCustomArgs, org::sem::CmdCustomArgs> {
  static void write(::orgproto::org::CmdCustomArgs* out, org::sem::CmdCustomArgs const& in);
  static void read(::orgproto::org::CmdCustomArgs const& out, proto_write_accessor<org::sem::CmdCustomArgs> in);
};


template <>
struct proto_serde<::orgproto::org::CmdCustomRaw, org::sem::CmdCustomRaw> {
  static void write(::orgproto::org::CmdCustomRaw* out, org::sem::CmdCustomRaw const& in);
  static void read(::orgproto::org::CmdCustomRaw const& out, proto_write_accessor<org::sem::CmdCustomRaw> in);
};


template <>
struct proto_serde<::orgproto::org::CmdCustomText, org::sem::CmdCustomText> {
  static void write(::orgproto::org::CmdCustomText* out, org::sem::CmdCustomText const& in);
  static void read(::orgproto::org::CmdCustomText const& out, proto_write_accessor<org::sem::CmdCustomText> in);
};


template <>
struct proto_serde<::orgproto::org::CmdResults, org::sem::CmdResults> {
  static void write(::orgproto::org::CmdResults* out, org::sem::CmdResults const& in);
  static void read(::orgproto::org::CmdResults const& out, proto_write_accessor<org::sem::CmdResults> in);
};


template <>
struct proto_serde<::orgproto::org::CmdTblfm, org::sem::CmdTblfm> {
  static void write(::orgproto::org::CmdTblfm* out, org::sem::CmdTblfm const& in);
  static void read(::orgproto::org::CmdTblfm const& out, proto_write_accessor<org::sem::CmdTblfm> in);
};


template <>
struct proto_serde<::orgproto::org::HashTag, org::sem::HashTag> {
  static void write(::orgproto::org::HashTag* out, org::sem::HashTag const& in);
  static void read(::orgproto::org::HashTag const& out, proto_write_accessor<org::sem::HashTag> in);
};


template <>
struct proto_serde<::orgproto::org::InlineFootnote, org::sem::InlineFootnote> {
  static void write(::orgproto::org::InlineFootnote* out, org::sem::InlineFootnote const& in);
  static void read(::orgproto::org::InlineFootnote const& out, proto_write_accessor<org::sem::InlineFootnote> in);
};


template <>
struct proto_serde<::orgproto::org::InlineExport, org::sem::InlineExport> {
  static void write(::orgproto::org::InlineExport* out, org::sem::InlineExport const& in);
  static void read(::orgproto::org::InlineExport const& out, proto_write_accessor<org::sem::InlineExport> in);
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
struct proto_serde<::orgproto::org::Time, org::sem::Time> {
  static void write(::orgproto::org::Time* out, org::sem::Time const& in);
  static void read(::orgproto::org::Time const& out, proto_write_accessor<org::sem::Time> in);
};


template <>
struct proto_serde<::orgproto::org::TimeRange, org::sem::TimeRange> {
  static void write(::orgproto::org::TimeRange* out, org::sem::TimeRange const& in);
  static void read(::orgproto::org::TimeRange const& out, proto_write_accessor<org::sem::TimeRange> in);
};


template <>
struct proto_serde<::orgproto::org::Macro, org::sem::Macro> {
  static void write(::orgproto::org::Macro* out, org::sem::Macro const& in);
  static void read(::orgproto::org::Macro const& out, proto_write_accessor<org::sem::Macro> in);
};


template <>
struct proto_serde<::orgproto::Symbol::Param, sem::Symbol::Param> {
  static void write(::orgproto::Symbol::Param* out, sem::Symbol::Param const& in);
  static void read(::orgproto::Symbol::Param const& out, proto_write_accessor<sem::Symbol::Param> in);
};


template <>
struct proto_serde<::orgproto::org::Symbol, org::sem::Symbol> {
  static void write(::orgproto::org::Symbol* out, org::sem::Symbol const& in);
  static void read(::orgproto::org::Symbol const& out, proto_write_accessor<org::sem::Symbol> in);
};


template <>
struct proto_serde<::orgproto::org::Escaped, org::sem::Escaped> {
  static void write(::orgproto::org::Escaped* out, org::sem::Escaped const& in);
  static void read(::orgproto::org::Escaped const& out, proto_write_accessor<org::sem::Escaped> in);
};


template <>
struct proto_serde<::orgproto::org::Newline, org::sem::Newline> {
  static void write(::orgproto::org::Newline* out, org::sem::Newline const& in);
  static void read(::orgproto::org::Newline const& out, proto_write_accessor<org::sem::Newline> in);
};


template <>
struct proto_serde<::orgproto::org::Space, org::sem::Space> {
  static void write(::orgproto::org::Space* out, org::sem::Space const& in);
  static void read(::orgproto::org::Space const& out, proto_write_accessor<org::sem::Space> in);
};


template <>
struct proto_serde<::orgproto::org::Word, org::sem::Word> {
  static void write(::orgproto::org::Word* out, org::sem::Word const& in);
  static void read(::orgproto::org::Word const& out, proto_write_accessor<org::sem::Word> in);
};


template <>
struct proto_serde<::orgproto::org::AtMention, org::sem::AtMention> {
  static void write(::orgproto::org::AtMention* out, org::sem::AtMention const& in);
  static void read(::orgproto::org::AtMention const& out, proto_write_accessor<org::sem::AtMention> in);
};


template <>
struct proto_serde<::orgproto::org::RawText, org::sem::RawText> {
  static void write(::orgproto::org::RawText* out, org::sem::RawText const& in);
  static void read(::orgproto::org::RawText const& out, proto_write_accessor<org::sem::RawText> in);
};


template <>
struct proto_serde<::orgproto::org::Punctuation, org::sem::Punctuation> {
  static void write(::orgproto::org::Punctuation* out, org::sem::Punctuation const& in);
  static void read(::orgproto::org::Punctuation const& out, proto_write_accessor<org::sem::Punctuation> in);
};


template <>
struct proto_serde<::orgproto::org::Placeholder, org::sem::Placeholder> {
  static void write(::orgproto::org::Placeholder* out, org::sem::Placeholder const& in);
  static void read(::orgproto::org::Placeholder const& out, proto_write_accessor<org::sem::Placeholder> in);
};


template <>
struct proto_serde<::orgproto::org::BigIdent, org::sem::BigIdent> {
  static void write(::orgproto::org::BigIdent* out, org::sem::BigIdent const& in);
  static void read(::orgproto::org::BigIdent const& out, proto_write_accessor<org::sem::BigIdent> in);
};


template <>
struct proto_serde<::orgproto::org::TextTarget, org::sem::TextTarget> {
  static void write(::orgproto::org::TextTarget* out, org::sem::TextTarget const& in);
  static void read(::orgproto::org::TextTarget const& out, proto_write_accessor<org::sem::TextTarget> in);
};


template <>
struct proto_serde<::orgproto::org::Bold, org::sem::Bold> {
  static void write(::orgproto::org::Bold* out, org::sem::Bold const& in);
  static void read(::orgproto::org::Bold const& out, proto_write_accessor<org::sem::Bold> in);
};


template <>
struct proto_serde<::orgproto::org::Underline, org::sem::Underline> {
  static void write(::orgproto::org::Underline* out, org::sem::Underline const& in);
  static void read(::orgproto::org::Underline const& out, proto_write_accessor<org::sem::Underline> in);
};


template <>
struct proto_serde<::orgproto::org::Monospace, org::sem::Monospace> {
  static void write(::orgproto::org::Monospace* out, org::sem::Monospace const& in);
  static void read(::orgproto::org::Monospace const& out, proto_write_accessor<org::sem::Monospace> in);
};


template <>
struct proto_serde<::orgproto::org::MarkQuote, org::sem::MarkQuote> {
  static void write(::orgproto::org::MarkQuote* out, org::sem::MarkQuote const& in);
  static void read(::orgproto::org::MarkQuote const& out, proto_write_accessor<org::sem::MarkQuote> in);
};


template <>
struct proto_serde<::orgproto::org::Verbatim, org::sem::Verbatim> {
  static void write(::orgproto::org::Verbatim* out, org::sem::Verbatim const& in);
  static void read(::orgproto::org::Verbatim const& out, proto_write_accessor<org::sem::Verbatim> in);
};


template <>
struct proto_serde<::orgproto::org::Italic, org::sem::Italic> {
  static void write(::orgproto::org::Italic* out, org::sem::Italic const& in);
  static void read(::orgproto::org::Italic const& out, proto_write_accessor<org::sem::Italic> in);
};


template <>
struct proto_serde<::orgproto::org::Strike, org::sem::Strike> {
  static void write(::orgproto::org::Strike* out, org::sem::Strike const& in);
  static void read(::orgproto::org::Strike const& out, proto_write_accessor<org::sem::Strike> in);
};


template <>
struct proto_serde<::orgproto::org::Par, org::sem::Par> {
  static void write(::orgproto::org::Par* out, org::sem::Par const& in);
  static void read(::orgproto::org::Par const& out, proto_write_accessor<org::sem::Par> in);
};


template <>
struct proto_serde<::orgproto::org::RadioTarget, org::sem::RadioTarget> {
  static void write(::orgproto::org::RadioTarget* out, org::sem::RadioTarget const& in);
  static void read(::orgproto::org::RadioTarget const& out, proto_write_accessor<org::sem::RadioTarget> in);
};


template <>
struct proto_serde<::orgproto::org::Latex, org::sem::Latex> {
  static void write(::orgproto::org::Latex* out, org::sem::Latex const& in);
  static void read(::orgproto::org::Latex const& out, proto_write_accessor<org::sem::Latex> in);
};


template <>
struct proto_serde<::orgproto::org::Link, org::sem::Link> {
  static void write(::orgproto::org::Link* out, org::sem::Link const& in);
  static void read(::orgproto::org::Link const& out, proto_write_accessor<org::sem::Link> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCenter, org::sem::BlockCenter> {
  static void write(::orgproto::org::BlockCenter* out, org::sem::BlockCenter const& in);
  static void read(::orgproto::org::BlockCenter const& out, proto_write_accessor<org::sem::BlockCenter> in);
};


template <>
struct proto_serde<::orgproto::org::BlockQuote, org::sem::BlockQuote> {
  static void write(::orgproto::org::BlockQuote* out, org::sem::BlockQuote const& in);
  static void read(::orgproto::org::BlockQuote const& out, proto_write_accessor<org::sem::BlockQuote> in);
};


template <>
struct proto_serde<::orgproto::org::BlockComment, org::sem::BlockComment> {
  static void write(::orgproto::org::BlockComment* out, org::sem::BlockComment const& in);
  static void read(::orgproto::org::BlockComment const& out, proto_write_accessor<org::sem::BlockComment> in);
};


template <>
struct proto_serde<::orgproto::org::BlockVerse, org::sem::BlockVerse> {
  static void write(::orgproto::org::BlockVerse* out, org::sem::BlockVerse const& in);
  static void read(::orgproto::org::BlockVerse const& out, proto_write_accessor<org::sem::BlockVerse> in);
};


template <>
struct proto_serde<::orgproto::org::BlockDynamicFallback, org::sem::BlockDynamicFallback> {
  static void write(::orgproto::org::BlockDynamicFallback* out, org::sem::BlockDynamicFallback const& in);
  static void read(::orgproto::org::BlockDynamicFallback const& out, proto_write_accessor<org::sem::BlockDynamicFallback> in);
};


template <>
struct proto_serde<::orgproto::org::BlockExample, org::sem::BlockExample> {
  static void write(::orgproto::org::BlockExample* out, org::sem::BlockExample const& in);
  static void read(::orgproto::org::BlockExample const& out, proto_write_accessor<org::sem::BlockExample> in);
};


template <>
struct proto_serde<::orgproto::org::BlockExport, org::sem::BlockExport> {
  static void write(::orgproto::org::BlockExport* out, org::sem::BlockExport const& in);
  static void read(::orgproto::org::BlockExport const& out, proto_write_accessor<org::sem::BlockExport> in);
};


template <>
struct proto_serde<::orgproto::org::BlockAdmonition, org::sem::BlockAdmonition> {
  static void write(::orgproto::org::BlockAdmonition* out, org::sem::BlockAdmonition const& in);
  static void read(::orgproto::org::BlockAdmonition const& out, proto_write_accessor<org::sem::BlockAdmonition> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCode, org::sem::BlockCode> {
  static void write(::orgproto::org::BlockCode* out, org::sem::BlockCode const& in);
  static void read(::orgproto::org::BlockCode const& out, proto_write_accessor<org::sem::BlockCode> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLog, org::sem::SubtreeLog> {
  static void write(::orgproto::org::SubtreeLog* out, org::sem::SubtreeLog const& in);
  static void read(::orgproto::org::SubtreeLog const& out, proto_write_accessor<org::sem::SubtreeLog> in);
};


template <>
struct proto_serde<::orgproto::org::Subtree, org::sem::Subtree> {
  static void write(::orgproto::org::Subtree* out, org::sem::Subtree const& in);
  static void read(::orgproto::org::Subtree const& out, proto_write_accessor<org::sem::Subtree> in);
};


template <>
struct proto_serde<::orgproto::org::Cell, org::sem::Cell> {
  static void write(::orgproto::org::Cell* out, org::sem::Cell const& in);
  static void read(::orgproto::org::Cell const& out, proto_write_accessor<org::sem::Cell> in);
};


template <>
struct proto_serde<::orgproto::org::Row, org::sem::Row> {
  static void write(::orgproto::org::Row* out, org::sem::Row const& in);
  static void read(::orgproto::org::Row const& out, proto_write_accessor<org::sem::Row> in);
};


template <>
struct proto_serde<::orgproto::org::Table, org::sem::Table> {
  static void write(::orgproto::org::Table* out, org::sem::Table const& in);
  static void read(::orgproto::org::Table const& out, proto_write_accessor<org::sem::Table> in);
};


template <>
struct proto_serde<::orgproto::org::Paragraph, org::sem::Paragraph> {
  static void write(::orgproto::org::Paragraph* out, org::sem::Paragraph const& in);
  static void read(::orgproto::org::Paragraph const& out, proto_write_accessor<org::sem::Paragraph> in);
};


template <>
struct proto_serde<::orgproto::org::ColonExample, org::sem::ColonExample> {
  static void write(::orgproto::org::ColonExample* out, org::sem::ColonExample const& in);
  static void read(::orgproto::org::ColonExample const& out, proto_write_accessor<org::sem::ColonExample> in);
};


template <>
struct proto_serde<::orgproto::org::CmdAttr, org::sem::CmdAttr> {
  static void write(::orgproto::org::CmdAttr* out, org::sem::CmdAttr const& in);
  static void read(::orgproto::org::CmdAttr const& out, proto_write_accessor<org::sem::CmdAttr> in);
};


template <>
struct proto_serde<::orgproto::org::CmdExport, org::sem::CmdExport> {
  static void write(::orgproto::org::CmdExport* out, org::sem::CmdExport const& in);
  static void read(::orgproto::org::CmdExport const& out, proto_write_accessor<org::sem::CmdExport> in);
};


template <>
struct proto_serde<::orgproto::org::Call, org::sem::Call> {
  static void write(::orgproto::org::Call* out, org::sem::Call const& in);
  static void read(::orgproto::org::Call const& out, proto_write_accessor<org::sem::Call> in);
};


template <>
struct proto_serde<::orgproto::org::List, org::sem::List> {
  static void write(::orgproto::org::List* out, org::sem::List const& in);
  static void read(::orgproto::org::List const& out, proto_write_accessor<org::sem::List> in);
};


template <>
struct proto_serde<::orgproto::org::ListItem, org::sem::ListItem> {
  static void write(::orgproto::org::ListItem* out, org::sem::ListItem const& in);
  static void read(::orgproto::org::ListItem const& out, proto_write_accessor<org::sem::ListItem> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentOptions, org::sem::DocumentOptions> {
  static void write(::orgproto::org::DocumentOptions* out, org::sem::DocumentOptions const& in);
  static void read(::orgproto::org::DocumentOptions const& out, proto_write_accessor<org::sem::DocumentOptions> in);
};


template <>
struct proto_serde<::orgproto::org::Document, org::sem::Document> {
  static void write(::orgproto::org::Document* out, org::sem::Document const& in);
  static void read(::orgproto::org::Document const& out, proto_write_accessor<org::sem::Document> in);
};


template <>
struct proto_serde<::orgproto::org::FileTarget, org::sem::FileTarget> {
  static void write(::orgproto::org::FileTarget* out, org::sem::FileTarget const& in);
  static void read(::orgproto::org::FileTarget const& out, proto_write_accessor<org::sem::FileTarget> in);
};


template <>
struct proto_serde<::orgproto::org::TextSeparator, org::sem::TextSeparator> {
  static void write(::orgproto::org::TextSeparator* out, org::sem::TextSeparator const& in);
  static void read(::orgproto::org::TextSeparator const& out, proto_write_accessor<org::sem::TextSeparator> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentGroup, org::sem::DocumentGroup> {
  static void write(::orgproto::org::DocumentGroup* out, org::sem::DocumentGroup const& in);
  static void read(::orgproto::org::DocumentGroup const& out, proto_write_accessor<org::sem::DocumentGroup> in);
};


template <>
struct proto_serde<::orgproto::File::Document, sem::File::Document> {
  static void write(::orgproto::File::Document* out, sem::File::Document const& in);
  static void read(::orgproto::File::Document const& out, proto_write_accessor<sem::File::Document> in);
};


template <>
struct proto_serde<::orgproto::File::Attachment, sem::File::Attachment> {
  static void write(::orgproto::File::Attachment* out, sem::File::Attachment const& in);
  static void read(::orgproto::File::Attachment const& out, proto_write_accessor<sem::File::Attachment> in);
};


template <>
struct proto_serde<::orgproto::File::Source, sem::File::Source> {
  static void write(::orgproto::File::Source* out, sem::File::Source const& in);
  static void read(::orgproto::File::Source const& out, proto_write_accessor<sem::File::Source> in);
};


template <>
struct proto_serde<::orgproto::org::File, org::sem::File> {
  static void write(::orgproto::org::File* out, org::sem::File const& in);
  static void read(::orgproto::org::File const& out, proto_write_accessor<org::sem::File> in);
};


template <>
struct proto_serde<::orgproto::org::Directory, org::sem::Directory> {
  static void write(::orgproto::org::Directory* out, org::sem::Directory const& in);
  static void read(::orgproto::org::Directory const& out, proto_write_accessor<org::sem::Directory> in);
};


template <>
struct proto_serde<::orgproto::org::Symlink, org::sem::Symlink> {
  static void write(::orgproto::org::Symlink* out, org::sem::Symlink const& in);
  static void read(::orgproto::org::Symlink const& out, proto_write_accessor<org::sem::Symlink> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::IncludeBase, sem::CmdInclude::IncludeBase> {
  static void write(::orgproto::CmdInclude::IncludeBase* out, sem::CmdInclude::IncludeBase const& in);
  static void read(::orgproto::CmdInclude::IncludeBase const& out, proto_write_accessor<sem::CmdInclude::IncludeBase> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::Example, sem::CmdInclude::Example> {
  static void write(::orgproto::CmdInclude::Example* out, sem::CmdInclude::Example const& in);
  static void read(::orgproto::CmdInclude::Example const& out, proto_write_accessor<sem::CmdInclude::Example> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::Export, sem::CmdInclude::Export> {
  static void write(::orgproto::CmdInclude::Export* out, sem::CmdInclude::Export const& in);
  static void read(::orgproto::CmdInclude::Export const& out, proto_write_accessor<sem::CmdInclude::Export> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::Custom, sem::CmdInclude::Custom> {
  static void write(::orgproto::CmdInclude::Custom* out, sem::CmdInclude::Custom const& in);
  static void read(::orgproto::CmdInclude::Custom const& out, proto_write_accessor<sem::CmdInclude::Custom> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::Src, sem::CmdInclude::Src> {
  static void write(::orgproto::CmdInclude::Src* out, sem::CmdInclude::Src const& in);
  static void read(::orgproto::CmdInclude::Src const& out, proto_write_accessor<sem::CmdInclude::Src> in);
};


template <>
struct proto_serde<::orgproto::CmdInclude::OrgDocument, sem::CmdInclude::OrgDocument> {
  static void write(::orgproto::CmdInclude::OrgDocument* out, sem::CmdInclude::OrgDocument const& in);
  static void read(::orgproto::CmdInclude::OrgDocument const& out, proto_write_accessor<sem::CmdInclude::OrgDocument> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude, org::sem::CmdInclude> {
  static void write(::orgproto::org::CmdInclude* out, org::sem::CmdInclude const& in);
  static void read(::orgproto::org::CmdInclude const& out, proto_write_accessor<org::sem::CmdInclude> in);
};


/* clang-format on */