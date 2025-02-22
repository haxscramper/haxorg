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
struct proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Index> {
  static void write(::orgproto::org::Tblfm::Expr::AxisRef::Position::Index* out, org::sem::Tblfm::Expr::AxisRef::Position::Index const& in);
  static void read(::orgproto::org::Tblfm::Expr::AxisRef::Position::Index const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Index> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position::Name, org::sem::Tblfm::Expr::AxisRef::Position::Name> {
  static void write(::orgproto::org::Tblfm::Expr::AxisRef::Position::Name* out, org::sem::Tblfm::Expr::AxisRef::Position::Name const& in);
  static void read(::orgproto::org::Tblfm::Expr::AxisRef::Position::Name const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position::Name> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::AxisRef::Position, org::sem::Tblfm::Expr::AxisRef::Position> {
  static void write(::orgproto::org::Tblfm::Expr::AxisRef::Position* out, org::sem::Tblfm::Expr::AxisRef::Position const& in);
  static void read(::orgproto::org::Tblfm::Expr::AxisRef::Position const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef::Position> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef> {
  static void write(::orgproto::org::Tblfm::Expr::AxisRef* out, org::sem::Tblfm::Expr::AxisRef const& in);
  static void read(::orgproto::org::Tblfm::Expr::AxisRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisRef> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::AxisName> {
  static void write(::orgproto::org::Tblfm::Expr::AxisName* out, org::sem::Tblfm::Expr::AxisName const& in);
  static void read(::orgproto::org::Tblfm::Expr::AxisName const& out, proto_write_accessor<org::sem::Tblfm::Expr::AxisName> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::IntLiteral> {
  static void write(::orgproto::org::Tblfm::Expr::IntLiteral* out, org::sem::Tblfm::Expr::IntLiteral const& in);
  static void read(::orgproto::org::Tblfm::Expr::IntLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::IntLiteral> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::FloatLiteral> {
  static void write(::orgproto::org::Tblfm::Expr::FloatLiteral* out, org::sem::Tblfm::Expr::FloatLiteral const& in);
  static void read(::orgproto::org::Tblfm::Expr::FloatLiteral const& out, proto_write_accessor<org::sem::Tblfm::Expr::FloatLiteral> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::RangeRef> {
  static void write(::orgproto::org::Tblfm::Expr::RangeRef* out, org::sem::Tblfm::Expr::RangeRef const& in);
  static void read(::orgproto::org::Tblfm::Expr::RangeRef const& out, proto_write_accessor<org::sem::Tblfm::Expr::RangeRef> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Call> {
  static void write(::orgproto::org::Tblfm::Expr::Call* out, org::sem::Tblfm::Expr::Call const& in);
  static void read(::orgproto::org::Tblfm::Expr::Call const& out, proto_write_accessor<org::sem::Tblfm::Expr::Call> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr::Elisp, org::sem::Tblfm::Expr::Elisp> {
  static void write(::orgproto::org::Tblfm::Expr::Elisp* out, org::sem::Tblfm::Expr::Elisp const& in);
  static void read(::orgproto::org::Tblfm::Expr::Elisp const& out, proto_write_accessor<org::sem::Tblfm::Expr::Elisp> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Expr, org::sem::Tblfm::Expr> {
  static void write(::orgproto::org::Tblfm::Expr* out, org::sem::Tblfm::Expr const& in);
  static void read(::orgproto::org::Tblfm::Expr const& out, proto_write_accessor<org::sem::Tblfm::Expr> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm::Assign, org::sem::Tblfm::Assign> {
  static void write(::orgproto::org::Tblfm::Assign* out, org::sem::Tblfm::Assign const& in);
  static void read(::orgproto::org::Tblfm::Assign const& out, proto_write_accessor<org::sem::Tblfm::Assign> in);
};


template <>
struct proto_serde<::orgproto::org::Tblfm, org::sem::Tblfm> {
  static void write(::orgproto::org::Tblfm* out, org::sem::Tblfm const& in);
  static void read(::orgproto::org::Tblfm const& out, proto_write_accessor<org::sem::Tblfm> in);
};


template <>
struct proto_serde<::orgproto::org::AttrValue, org::sem::AttrValue> {
  static void write(::orgproto::org::AttrValue* out, org::sem::AttrValue const& in);
  static void read(::orgproto::org::AttrValue const& out, proto_write_accessor<org::sem::AttrValue> in);
};


template <>
struct proto_serde<::orgproto::org::HashTagFlat, org::sem::HashTagFlat> {
  static void write(::orgproto::org::HashTagFlat* out, org::sem::HashTagFlat const& in);
  static void read(::orgproto::org::HashTagFlat const& out, proto_write_accessor<org::sem::HashTagFlat> in);
};


template <>
struct proto_serde<::orgproto::org::HashTagText, org::sem::HashTagText> {
  static void write(::orgproto::org::HashTagText* out, org::sem::HashTagText const& in);
  static void read(::orgproto::org::HashTagText const& out, proto_write_accessor<org::sem::HashTagText> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreePath, org::sem::SubtreePath> {
  static void write(::orgproto::org::SubtreePath* out, org::sem::SubtreePath const& in);
  static void read(::orgproto::org::SubtreePath const& out, proto_write_accessor<org::sem::SubtreePath> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Raw, org::sem::LinkTarget::Raw> {
  static void write(::orgproto::org::LinkTarget::Raw* out, org::sem::LinkTarget::Raw const& in);
  static void read(::orgproto::org::LinkTarget::Raw const& out, proto_write_accessor<org::sem::LinkTarget::Raw> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Id, org::sem::LinkTarget::Id> {
  static void write(::orgproto::org::LinkTarget::Id* out, org::sem::LinkTarget::Id const& in);
  static void read(::orgproto::org::LinkTarget::Id const& out, proto_write_accessor<org::sem::LinkTarget::Id> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::CustomId, org::sem::LinkTarget::CustomId> {
  static void write(::orgproto::org::LinkTarget::CustomId* out, org::sem::LinkTarget::CustomId const& in);
  static void read(::orgproto::org::LinkTarget::CustomId const& out, proto_write_accessor<org::sem::LinkTarget::CustomId> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::SubtreeTitle, org::sem::LinkTarget::SubtreeTitle> {
  static void write(::orgproto::org::LinkTarget::SubtreeTitle* out, org::sem::LinkTarget::SubtreeTitle const& in);
  static void read(::orgproto::org::LinkTarget::SubtreeTitle const& out, proto_write_accessor<org::sem::LinkTarget::SubtreeTitle> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Person, org::sem::LinkTarget::Person> {
  static void write(::orgproto::org::LinkTarget::Person* out, org::sem::LinkTarget::Person const& in);
  static void read(::orgproto::org::LinkTarget::Person const& out, proto_write_accessor<org::sem::LinkTarget::Person> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::UserProtocol, org::sem::LinkTarget::UserProtocol> {
  static void write(::orgproto::org::LinkTarget::UserProtocol* out, org::sem::LinkTarget::UserProtocol const& in);
  static void read(::orgproto::org::LinkTarget::UserProtocol const& out, proto_write_accessor<org::sem::LinkTarget::UserProtocol> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Internal, org::sem::LinkTarget::Internal> {
  static void write(::orgproto::org::LinkTarget::Internal* out, org::sem::LinkTarget::Internal const& in);
  static void read(::orgproto::org::LinkTarget::Internal const& out, proto_write_accessor<org::sem::LinkTarget::Internal> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Footnote, org::sem::LinkTarget::Footnote> {
  static void write(::orgproto::org::LinkTarget::Footnote* out, org::sem::LinkTarget::Footnote const& in);
  static void read(::orgproto::org::LinkTarget::Footnote const& out, proto_write_accessor<org::sem::LinkTarget::Footnote> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::File, org::sem::LinkTarget::File> {
  static void write(::orgproto::org::LinkTarget::File* out, org::sem::LinkTarget::File const& in);
  static void read(::orgproto::org::LinkTarget::File const& out, proto_write_accessor<org::sem::LinkTarget::File> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget::Attachment, org::sem::LinkTarget::Attachment> {
  static void write(::orgproto::org::LinkTarget::Attachment* out, org::sem::LinkTarget::Attachment const& in);
  static void read(::orgproto::org::LinkTarget::Attachment const& out, proto_write_accessor<org::sem::LinkTarget::Attachment> in);
};


template <>
struct proto_serde<::orgproto::org::LinkTarget, org::sem::LinkTarget> {
  static void write(::orgproto::org::LinkTarget* out, org::sem::LinkTarget const& in);
  static void read(::orgproto::org::LinkTarget const& out, proto_write_accessor<org::sem::LinkTarget> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority> {
  static void write(::orgproto::org::SubtreeLogHead::Priority* out, org::sem::SubtreeLogHead::Priority const& in);
  static void read(::orgproto::org::SubtreeLogHead::Priority const& out, proto_write_accessor<org::sem::SubtreeLogHead::Priority> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Note> {
  static void write(::orgproto::org::SubtreeLogHead::Note* out, org::sem::SubtreeLogHead::Note const& in);
  static void read(::orgproto::org::SubtreeLogHead::Note const& out, proto_write_accessor<org::sem::SubtreeLogHead::Note> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Refile> {
  static void write(::orgproto::org::SubtreeLogHead::Refile* out, org::sem::SubtreeLogHead::Refile const& in);
  static void read(::orgproto::org::SubtreeLogHead::Refile const& out, proto_write_accessor<org::sem::SubtreeLogHead::Refile> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::Clock> {
  static void write(::orgproto::org::SubtreeLogHead::Clock* out, org::sem::SubtreeLogHead::Clock const& in);
  static void read(::orgproto::org::SubtreeLogHead::Clock const& out, proto_write_accessor<org::sem::SubtreeLogHead::Clock> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::State, org::sem::SubtreeLogHead::State> {
  static void write(::orgproto::org::SubtreeLogHead::State* out, org::sem::SubtreeLogHead::State const& in);
  static void read(::orgproto::org::SubtreeLogHead::State const& out, proto_write_accessor<org::sem::SubtreeLogHead::State> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Deadline> {
  static void write(::orgproto::org::SubtreeLogHead::Deadline* out, org::sem::SubtreeLogHead::Deadline const& in);
  static void read(::orgproto::org::SubtreeLogHead::Deadline const& out, proto_write_accessor<org::sem::SubtreeLogHead::Deadline> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Schedule> {
  static void write(::orgproto::org::SubtreeLogHead::Schedule* out, org::sem::SubtreeLogHead::Schedule const& in);
  static void read(::orgproto::org::SubtreeLogHead::Schedule const& out, proto_write_accessor<org::sem::SubtreeLogHead::Schedule> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Tag> {
  static void write(::orgproto::org::SubtreeLogHead::Tag* out, org::sem::SubtreeLogHead::Tag const& in);
  static void read(::orgproto::org::SubtreeLogHead::Tag const& out, proto_write_accessor<org::sem::SubtreeLogHead::Tag> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead::Unknown, org::sem::SubtreeLogHead::Unknown> {
  static void write(::orgproto::org::SubtreeLogHead::Unknown* out, org::sem::SubtreeLogHead::Unknown const& in);
  static void read(::orgproto::org::SubtreeLogHead::Unknown const& out, proto_write_accessor<org::sem::SubtreeLogHead::Unknown> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeLogHead, org::sem::SubtreeLogHead> {
  static void write(::orgproto::org::SubtreeLogHead* out, org::sem::SubtreeLogHead const& in);
  static void read(::orgproto::org::SubtreeLogHead const& out, proto_write_accessor<org::sem::SubtreeLogHead> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreeCompletion, org::sem::SubtreeCompletion> {
  static void write(::orgproto::org::SubtreeCompletion* out, org::sem::SubtreeCompletion const& in);
  static void read(::orgproto::org::SubtreeCompletion const& out, proto_write_accessor<org::sem::SubtreeCompletion> in);
};


template <>
struct proto_serde<::orgproto::org::AttrList, org::sem::AttrList> {
  static void write(::orgproto::org::AttrList* out, org::sem::AttrList const& in);
  static void read(::orgproto::org::AttrList const& out, proto_write_accessor<org::sem::AttrList> in);
};


template <>
struct proto_serde<::orgproto::org::AttrGroup, org::sem::AttrGroup> {
  static void write(::orgproto::org::AttrGroup* out, org::sem::AttrGroup const& in);
  static void read(::orgproto::org::AttrGroup const& out, proto_write_accessor<org::sem::AttrGroup> in);
};


template <>
struct proto_serde<::orgproto::org::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate> {
  static void write(::orgproto::org::ColumnView::Summary::CheckboxAggregate* out, org::sem::ColumnView::Summary::CheckboxAggregate const& in);
  static void read(::orgproto::org::ColumnView::Summary::CheckboxAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::CheckboxAggregate> in);
};


template <>
struct proto_serde<::orgproto::org::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate> {
  static void write(::orgproto::org::ColumnView::Summary::MathAggregate* out, org::sem::ColumnView::Summary::MathAggregate const& in);
  static void read(::orgproto::org::ColumnView::Summary::MathAggregate const& out, proto_write_accessor<org::sem::ColumnView::Summary::MathAggregate> in);
};


template <>
struct proto_serde<::orgproto::org::ColumnView::Summary, org::sem::ColumnView::Summary> {
  static void write(::orgproto::org::ColumnView::Summary* out, org::sem::ColumnView::Summary const& in);
  static void read(::orgproto::org::ColumnView::Summary const& out, proto_write_accessor<org::sem::ColumnView::Summary> in);
};


template <>
struct proto_serde<::orgproto::org::ColumnView::Column, org::sem::ColumnView::Column> {
  static void write(::orgproto::org::ColumnView::Column* out, org::sem::ColumnView::Column const& in);
  static void read(::orgproto::org::ColumnView::Column const& out, proto_write_accessor<org::sem::ColumnView::Column> in);
};


template <>
struct proto_serde<::orgproto::org::ColumnView, org::sem::ColumnView> {
  static void write(::orgproto::org::ColumnView* out, org::sem::ColumnView const& in);
  static void read(::orgproto::org::ColumnView const& out, proto_write_accessor<org::sem::ColumnView> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Raw> {
  static void write(::orgproto::org::BlockCodeLine::Part::Raw* out, org::sem::BlockCodeLine::Part::Raw const& in);
  static void read(::orgproto::org::BlockCodeLine::Part::Raw const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Raw> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Callout> {
  static void write(::orgproto::org::BlockCodeLine::Part::Callout* out, org::sem::BlockCodeLine::Part::Callout const& in);
  static void read(::orgproto::org::BlockCodeLine::Part::Callout const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Callout> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeLine::Part::Tangle, org::sem::BlockCodeLine::Part::Tangle> {
  static void write(::orgproto::org::BlockCodeLine::Part::Tangle* out, org::sem::BlockCodeLine::Part::Tangle const& in);
  static void read(::orgproto::org::BlockCodeLine::Part::Tangle const& out, proto_write_accessor<org::sem::BlockCodeLine::Part::Tangle> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeLine::Part, org::sem::BlockCodeLine::Part> {
  static void write(::orgproto::org::BlockCodeLine::Part* out, org::sem::BlockCodeLine::Part const& in);
  static void read(::orgproto::org::BlockCodeLine::Part const& out, proto_write_accessor<org::sem::BlockCodeLine::Part> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeLine, org::sem::BlockCodeLine> {
  static void write(::orgproto::org::BlockCodeLine* out, org::sem::BlockCodeLine const& in);
  static void read(::orgproto::org::BlockCodeLine const& out, proto_write_accessor<org::sem::BlockCodeLine> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch::LineStart, org::sem::BlockCodeSwitch::LineStart> {
  static void write(::orgproto::org::BlockCodeSwitch::LineStart* out, org::sem::BlockCodeSwitch::LineStart const& in);
  static void read(::orgproto::org::BlockCodeSwitch::LineStart const& out, proto_write_accessor<org::sem::BlockCodeSwitch::LineStart> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch::CalloutFormat, org::sem::BlockCodeSwitch::CalloutFormat> {
  static void write(::orgproto::org::BlockCodeSwitch::CalloutFormat* out, org::sem::BlockCodeSwitch::CalloutFormat const& in);
  static void read(::orgproto::org::BlockCodeSwitch::CalloutFormat const& out, proto_write_accessor<org::sem::BlockCodeSwitch::CalloutFormat> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch::RemoveCallout, org::sem::BlockCodeSwitch::RemoveCallout> {
  static void write(::orgproto::org::BlockCodeSwitch::RemoveCallout* out, org::sem::BlockCodeSwitch::RemoveCallout const& in);
  static void read(::orgproto::org::BlockCodeSwitch::RemoveCallout const& out, proto_write_accessor<org::sem::BlockCodeSwitch::RemoveCallout> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch::EmphasizeLine, org::sem::BlockCodeSwitch::EmphasizeLine> {
  static void write(::orgproto::org::BlockCodeSwitch::EmphasizeLine* out, org::sem::BlockCodeSwitch::EmphasizeLine const& in);
  static void read(::orgproto::org::BlockCodeSwitch::EmphasizeLine const& out, proto_write_accessor<org::sem::BlockCodeSwitch::EmphasizeLine> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch::Dedent, org::sem::BlockCodeSwitch::Dedent> {
  static void write(::orgproto::org::BlockCodeSwitch::Dedent* out, org::sem::BlockCodeSwitch::Dedent const& in);
  static void read(::orgproto::org::BlockCodeSwitch::Dedent const& out, proto_write_accessor<org::sem::BlockCodeSwitch::Dedent> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeSwitch, org::sem::BlockCodeSwitch> {
  static void write(::orgproto::org::BlockCodeSwitch* out, org::sem::BlockCodeSwitch const& in);
  static void read(::orgproto::org::BlockCodeSwitch const& out, proto_write_accessor<org::sem::BlockCodeSwitch> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeEvalResult::None, org::sem::BlockCodeEvalResult::None> {
  static void write(::orgproto::org::BlockCodeEvalResult::None* out, org::sem::BlockCodeEvalResult::None const& in);
  static void read(::orgproto::org::BlockCodeEvalResult::None const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::None> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeEvalResult::OrgValue, org::sem::BlockCodeEvalResult::OrgValue> {
  static void write(::orgproto::org::BlockCodeEvalResult::OrgValue* out, org::sem::BlockCodeEvalResult::OrgValue const& in);
  static void read(::orgproto::org::BlockCodeEvalResult::OrgValue const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::OrgValue> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeEvalResult::File, org::sem::BlockCodeEvalResult::File> {
  static void write(::orgproto::org::BlockCodeEvalResult::File* out, org::sem::BlockCodeEvalResult::File const& in);
  static void read(::orgproto::org::BlockCodeEvalResult::File const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::File> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeEvalResult::Raw, org::sem::BlockCodeEvalResult::Raw> {
  static void write(::orgproto::org::BlockCodeEvalResult::Raw* out, org::sem::BlockCodeEvalResult::Raw const& in);
  static void read(::orgproto::org::BlockCodeEvalResult::Raw const& out, proto_write_accessor<org::sem::BlockCodeEvalResult::Raw> in);
};


template <>
struct proto_serde<::orgproto::org::BlockCodeEvalResult, org::sem::BlockCodeEvalResult> {
  static void write(::orgproto::org::BlockCodeEvalResult* out, org::sem::BlockCodeEvalResult const& in);
  static void read(::orgproto::org::BlockCodeEvalResult const& out, proto_write_accessor<org::sem::BlockCodeEvalResult> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentExportConfig::TaskExport, org::sem::DocumentExportConfig::TaskExport> {
  static void write(::orgproto::org::DocumentExportConfig::TaskExport* out, org::sem::DocumentExportConfig::TaskExport const& in);
  static void read(::orgproto::org::DocumentExportConfig::TaskExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::TaskExport> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::DoExport> {
  static void write(::orgproto::org::DocumentExportConfig::DoExport* out, org::sem::DocumentExportConfig::DoExport const& in);
  static void read(::orgproto::org::DocumentExportConfig::DoExport const& out, proto_write_accessor<org::sem::DocumentExportConfig::DoExport> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentExportConfig::ExportFixed, org::sem::DocumentExportConfig::ExportFixed> {
  static void write(::orgproto::org::DocumentExportConfig::ExportFixed* out, org::sem::DocumentExportConfig::ExportFixed const& in);
  static void read(::orgproto::org::DocumentExportConfig::ExportFixed const& out, proto_write_accessor<org::sem::DocumentExportConfig::ExportFixed> in);
};


template <>
struct proto_serde<::orgproto::org::DocumentExportConfig, org::sem::DocumentExportConfig> {
  static void write(::orgproto::org::DocumentExportConfig* out, org::sem::DocumentExportConfig const& in);
  static void read(::orgproto::org::DocumentExportConfig const& out, proto_write_accessor<org::sem::DocumentExportConfig> in);
};


template <>
struct proto_serde<::orgproto::org::SubtreePeriod, org::sem::SubtreePeriod> {
  static void write(::orgproto::org::SubtreePeriod* out, org::sem::SubtreePeriod const& in);
  static void read(::orgproto::org::SubtreePeriod const& out, proto_write_accessor<org::sem::SubtreePeriod> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Nonblocking, org::sem::NamedProperty::Nonblocking> {
  static void write(::orgproto::org::NamedProperty::Nonblocking* out, org::sem::NamedProperty::Nonblocking const& in);
  static void read(::orgproto::org::NamedProperty::Nonblocking const& out, proto_write_accessor<org::sem::NamedProperty::Nonblocking> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveTime> {
  static void write(::orgproto::org::NamedProperty::ArchiveTime* out, org::sem::NamedProperty::ArchiveTime const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveTime const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTime> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveFile> {
  static void write(::orgproto::org::NamedProperty::ArchiveFile* out, org::sem::NamedProperty::ArchiveFile const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveFile const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveFile> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveOlpath> {
  static void write(::orgproto::org::NamedProperty::ArchiveOlpath* out, org::sem::NamedProperty::ArchiveOlpath const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveOlpath const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveOlpath> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveTarget> {
  static void write(::orgproto::org::NamedProperty::ArchiveTarget* out, org::sem::NamedProperty::ArchiveTarget const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveTarget const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTarget> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveCategory> {
  static void write(::orgproto::org::NamedProperty::ArchiveCategory* out, org::sem::NamedProperty::ArchiveCategory const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveCategory const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveCategory> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ArchiveTodo, org::sem::NamedProperty::ArchiveTodo> {
  static void write(::orgproto::org::NamedProperty::ArchiveTodo* out, org::sem::NamedProperty::ArchiveTodo const& in);
  static void read(::orgproto::org::NamedProperty::ArchiveTodo const& out, proto_write_accessor<org::sem::NamedProperty::ArchiveTodo> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Trigger, org::sem::NamedProperty::Trigger> {
  static void write(::orgproto::org::NamedProperty::Trigger* out, org::sem::NamedProperty::Trigger const& in);
  static void read(::orgproto::org::NamedProperty::Trigger const& out, proto_write_accessor<org::sem::NamedProperty::Trigger> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ExportLatexClass, org::sem::NamedProperty::ExportLatexClass> {
  static void write(::orgproto::org::NamedProperty::ExportLatexClass* out, org::sem::NamedProperty::ExportLatexClass const& in);
  static void read(::orgproto::org::NamedProperty::ExportLatexClass const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClass> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::CookieData, org::sem::NamedProperty::CookieData> {
  static void write(::orgproto::org::NamedProperty::CookieData* out, org::sem::NamedProperty::CookieData const& in);
  static void read(::orgproto::org::NamedProperty::CookieData const& out, proto_write_accessor<org::sem::NamedProperty::CookieData> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexClassOptions> {
  static void write(::orgproto::org::NamedProperty::ExportLatexClassOptions* out, org::sem::NamedProperty::ExportLatexClassOptions const& in);
  static void read(::orgproto::org::NamedProperty::ExportLatexClassOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexClassOptions> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexHeader> {
  static void write(::orgproto::org::NamedProperty::ExportLatexHeader* out, org::sem::NamedProperty::ExportLatexHeader const& in);
  static void read(::orgproto::org::NamedProperty::ExportLatexHeader const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexHeader> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::ExportLatexCompiler> {
  static void write(::orgproto::org::NamedProperty::ExportLatexCompiler* out, org::sem::NamedProperty::ExportLatexCompiler const& in);
  static void read(::orgproto::org::NamedProperty::ExportLatexCompiler const& out, proto_write_accessor<org::sem::NamedProperty::ExportLatexCompiler> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Ordered, org::sem::NamedProperty::Ordered> {
  static void write(::orgproto::org::NamedProperty::Ordered* out, org::sem::NamedProperty::Ordered const& in);
  static void read(::orgproto::org::NamedProperty::Ordered const& out, proto_write_accessor<org::sem::NamedProperty::Ordered> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Effort, org::sem::NamedProperty::Effort> {
  static void write(::orgproto::org::NamedProperty::Effort* out, org::sem::NamedProperty::Effort const& in);
  static void read(::orgproto::org::NamedProperty::Effort const& out, proto_write_accessor<org::sem::NamedProperty::Effort> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Visibility, org::sem::NamedProperty::Visibility> {
  static void write(::orgproto::org::NamedProperty::Visibility* out, org::sem::NamedProperty::Visibility const& in);
  static void read(::orgproto::org::NamedProperty::Visibility const& out, proto_write_accessor<org::sem::NamedProperty::Visibility> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::ExportOptions, org::sem::NamedProperty::ExportOptions> {
  static void write(::orgproto::org::NamedProperty::ExportOptions* out, org::sem::NamedProperty::ExportOptions const& in);
  static void read(::orgproto::org::NamedProperty::ExportOptions const& out, proto_write_accessor<org::sem::NamedProperty::ExportOptions> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Blocker, org::sem::NamedProperty::Blocker> {
  static void write(::orgproto::org::NamedProperty::Blocker* out, org::sem::NamedProperty::Blocker const& in);
  static void read(::orgproto::org::NamedProperty::Blocker const& out, proto_write_accessor<org::sem::NamedProperty::Blocker> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Unnumbered, org::sem::NamedProperty::Unnumbered> {
  static void write(::orgproto::org::NamedProperty::Unnumbered* out, org::sem::NamedProperty::Unnumbered const& in);
  static void read(::orgproto::org::NamedProperty::Unnumbered const& out, proto_write_accessor<org::sem::NamedProperty::Unnumbered> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::Created, org::sem::NamedProperty::Created> {
  static void write(::orgproto::org::NamedProperty::Created* out, org::sem::NamedProperty::Created const& in);
  static void read(::orgproto::org::NamedProperty::Created const& out, proto_write_accessor<org::sem::NamedProperty::Created> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::RadioId, org::sem::NamedProperty::RadioId> {
  static void write(::orgproto::org::NamedProperty::RadioId* out, org::sem::NamedProperty::RadioId const& in);
  static void read(::orgproto::org::NamedProperty::RadioId const& out, proto_write_accessor<org::sem::NamedProperty::RadioId> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::HashtagDef, org::sem::NamedProperty::HashtagDef> {
  static void write(::orgproto::org::NamedProperty::HashtagDef* out, org::sem::NamedProperty::HashtagDef const& in);
  static void read(::orgproto::org::NamedProperty::HashtagDef const& out, proto_write_accessor<org::sem::NamedProperty::HashtagDef> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomArgs> {
  static void write(::orgproto::org::NamedProperty::CustomArgs* out, org::sem::NamedProperty::CustomArgs const& in);
  static void read(::orgproto::org::NamedProperty::CustomArgs const& out, proto_write_accessor<org::sem::NamedProperty::CustomArgs> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomRaw> {
  static void write(::orgproto::org::NamedProperty::CustomRaw* out, org::sem::NamedProperty::CustomRaw const& in);
  static void read(::orgproto::org::NamedProperty::CustomRaw const& out, proto_write_accessor<org::sem::NamedProperty::CustomRaw> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeJson> {
  static void write(::orgproto::org::NamedProperty::CustomSubtreeJson* out, org::sem::NamedProperty::CustomSubtreeJson const& in);
  static void read(::orgproto::org::NamedProperty::CustomSubtreeJson const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeJson> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty::CustomSubtreeFlags, org::sem::NamedProperty::CustomSubtreeFlags> {
  static void write(::orgproto::org::NamedProperty::CustomSubtreeFlags* out, org::sem::NamedProperty::CustomSubtreeFlags const& in);
  static void read(::orgproto::org::NamedProperty::CustomSubtreeFlags const& out, proto_write_accessor<org::sem::NamedProperty::CustomSubtreeFlags> in);
};


template <>
struct proto_serde<::orgproto::org::NamedProperty, org::sem::NamedProperty> {
  static void write(::orgproto::org::NamedProperty* out, org::sem::NamedProperty const& in);
  static void read(::orgproto::org::NamedProperty const& out, proto_write_accessor<org::sem::NamedProperty> in);
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
struct proto_serde<::orgproto::org::Time::Repeat, org::sem::Time::Repeat> {
  static void write(::orgproto::org::Time::Repeat* out, org::sem::Time::Repeat const& in);
  static void read(::orgproto::org::Time::Repeat const& out, proto_write_accessor<org::sem::Time::Repeat> in);
};


template <>
struct proto_serde<::orgproto::org::Time::Static, org::sem::Time::Static> {
  static void write(::orgproto::org::Time::Static* out, org::sem::Time::Static const& in);
  static void read(::orgproto::org::Time::Static const& out, proto_write_accessor<org::sem::Time::Static> in);
};


template <>
struct proto_serde<::orgproto::org::Time::Dynamic, org::sem::Time::Dynamic> {
  static void write(::orgproto::org::Time::Dynamic* out, org::sem::Time::Dynamic const& in);
  static void read(::orgproto::org::Time::Dynamic const& out, proto_write_accessor<org::sem::Time::Dynamic> in);
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
struct proto_serde<::orgproto::org::Symbol::Param, org::sem::Symbol::Param> {
  static void write(::orgproto::org::Symbol::Param* out, org::sem::Symbol::Param const& in);
  static void read(::orgproto::org::Symbol::Param const& out, proto_write_accessor<org::sem::Symbol::Param> in);
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
struct proto_serde<::orgproto::org::File::Document, org::sem::File::Document> {
  static void write(::orgproto::org::File::Document* out, org::sem::File::Document const& in);
  static void read(::orgproto::org::File::Document const& out, proto_write_accessor<org::sem::File::Document> in);
};


template <>
struct proto_serde<::orgproto::org::File::Attachment, org::sem::File::Attachment> {
  static void write(::orgproto::org::File::Attachment* out, org::sem::File::Attachment const& in);
  static void read(::orgproto::org::File::Attachment const& out, proto_write_accessor<org::sem::File::Attachment> in);
};


template <>
struct proto_serde<::orgproto::org::File::Source, org::sem::File::Source> {
  static void write(::orgproto::org::File::Source* out, org::sem::File::Source const& in);
  static void read(::orgproto::org::File::Source const& out, proto_write_accessor<org::sem::File::Source> in);
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
struct proto_serde<::orgproto::org::CmdInclude::IncludeBase, org::sem::CmdInclude::IncludeBase> {
  static void write(::orgproto::org::CmdInclude::IncludeBase* out, org::sem::CmdInclude::IncludeBase const& in);
  static void read(::orgproto::org::CmdInclude::IncludeBase const& out, proto_write_accessor<org::sem::CmdInclude::IncludeBase> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude::Example, org::sem::CmdInclude::Example> {
  static void write(::orgproto::org::CmdInclude::Example* out, org::sem::CmdInclude::Example const& in);
  static void read(::orgproto::org::CmdInclude::Example const& out, proto_write_accessor<org::sem::CmdInclude::Example> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude::Export, org::sem::CmdInclude::Export> {
  static void write(::orgproto::org::CmdInclude::Export* out, org::sem::CmdInclude::Export const& in);
  static void read(::orgproto::org::CmdInclude::Export const& out, proto_write_accessor<org::sem::CmdInclude::Export> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude::Custom, org::sem::CmdInclude::Custom> {
  static void write(::orgproto::org::CmdInclude::Custom* out, org::sem::CmdInclude::Custom const& in);
  static void read(::orgproto::org::CmdInclude::Custom const& out, proto_write_accessor<org::sem::CmdInclude::Custom> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude::Src, org::sem::CmdInclude::Src> {
  static void write(::orgproto::org::CmdInclude::Src* out, org::sem::CmdInclude::Src const& in);
  static void read(::orgproto::org::CmdInclude::Src const& out, proto_write_accessor<org::sem::CmdInclude::Src> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude::OrgDocument, org::sem::CmdInclude::OrgDocument> {
  static void write(::orgproto::org::CmdInclude::OrgDocument* out, org::sem::CmdInclude::OrgDocument const& in);
  static void read(::orgproto::org::CmdInclude::OrgDocument const& out, proto_write_accessor<org::sem::CmdInclude::OrgDocument> in);
};


template <>
struct proto_serde<::orgproto::org::CmdInclude, org::sem::CmdInclude> {
  static void write(::orgproto::org::CmdInclude* out, org::sem::CmdInclude const& in);
  static void read(::orgproto::org::CmdInclude const& out, proto_write_accessor<org::sem::CmdInclude> in);
};


/* clang-format on */