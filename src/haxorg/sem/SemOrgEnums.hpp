/* clang-format off */
#pragma once
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
#define EACH_SHARED_ORG_RECORD_NESTED(__IMPL) \
    __IMPL(LispCode, Call, (Call)) \
    __IMPL(LispCode, List, (List)) \
    __IMPL(LispCode, KeyValue, (KeyValue)) \
    __IMPL(LispCode, Number, (Number)) \
    __IMPL(LispCode, Text, (Text)) \
    __IMPL(LispCode, Ident, (Ident)) \
    __IMPL(LispCode, Boolean, (Boolean)) \
    __IMPL(LispCode, Real, (Real)) \
    __IMPL(Tblfm, Expr, (Expr)) \
    __IMPL(Tblfm, Expr::AxisRef, (Expr, AxisRef)) \
    __IMPL(Tblfm, Expr::AxisRef::Position, (Expr, AxisRef, Position)) \
    __IMPL(Tblfm, Expr::AxisRef::Position::Index, (Expr, AxisRef, Position, Index)) \
    __IMPL(Tblfm, Expr::AxisRef::Position::Name, (Expr, AxisRef, Position, Name)) \
    __IMPL(Tblfm, Expr::AxisName, (Expr, AxisName)) \
    __IMPL(Tblfm, Expr::IntLiteral, (Expr, IntLiteral)) \
    __IMPL(Tblfm, Expr::FloatLiteral, (Expr, FloatLiteral)) \
    __IMPL(Tblfm, Expr::RangeRef, (Expr, RangeRef)) \
    __IMPL(Tblfm, Expr::Call, (Expr, Call)) \
    __IMPL(Tblfm, Expr::Elisp, (Expr, Elisp)) \
    __IMPL(Tblfm, Assign, (Assign)) \
    __IMPL(AttrValue, DimensionSpan, (DimensionSpan)) \
    __IMPL(AttrValue, TextValue, (TextValue)) \
    __IMPL(AttrValue, FileReference, (FileReference)) \
    __IMPL(AttrValue, LispValue, (LispValue)) \
    __IMPL(LinkTarget, Raw, (Raw)) \
    __IMPL(LinkTarget, Id, (Id)) \
    __IMPL(LinkTarget, CustomId, (CustomId)) \
    __IMPL(LinkTarget, SubtreeTitle, (SubtreeTitle)) \
    __IMPL(LinkTarget, Person, (Person)) \
    __IMPL(LinkTarget, UserProtocol, (UserProtocol)) \
    __IMPL(LinkTarget, Internal, (Internal)) \
    __IMPL(LinkTarget, Footnote, (Footnote)) \
    __IMPL(LinkTarget, File, (File)) \
    __IMPL(LinkTarget, Attachment, (Attachment)) \
    __IMPL(SubtreeLogHead, Priority, (Priority)) \
    __IMPL(SubtreeLogHead, Note, (Note)) \
    __IMPL(SubtreeLogHead, Refile, (Refile)) \
    __IMPL(SubtreeLogHead, Clock, (Clock)) \
    __IMPL(SubtreeLogHead, State, (State)) \
    __IMPL(SubtreeLogHead, Deadline, (Deadline)) \
    __IMPL(SubtreeLogHead, Schedule, (Schedule)) \
    __IMPL(SubtreeLogHead, Tag, (Tag)) \
    __IMPL(SubtreeLogHead, Unknown, (Unknown)) \
    __IMPL(OrgCodeEvalInput, Var, (Var)) \
    __IMPL(ColumnView, Summary, (Summary)) \
    __IMPL(ColumnView, Summary::CheckboxAggregate, (Summary, CheckboxAggregate)) \
    __IMPL(ColumnView, Summary::MathAggregate, (Summary, MathAggregate)) \
    __IMPL(ColumnView, Column, (Column)) \
    __IMPL(BlockCodeLine, Part, (Part)) \
    __IMPL(BlockCodeLine, Part::Raw, (Part, Raw)) \
    __IMPL(BlockCodeLine, Part::Callout, (Part, Callout)) \
    __IMPL(BlockCodeLine, Part::Tangle, (Part, Tangle)) \
    __IMPL(DocumentExportConfig, TaskExport, (TaskExport)) \
    __IMPL(DocumentExportConfig, DoExport, (DoExport)) \
    __IMPL(DocumentExportConfig, ExportFixed, (ExportFixed)) \
    __IMPL(NamedProperty, Nonblocking, (Nonblocking)) \
    __IMPL(NamedProperty, ArchiveTime, (ArchiveTime)) \
    __IMPL(NamedProperty, ArchiveFile, (ArchiveFile)) \
    __IMPL(NamedProperty, ArchiveOlpath, (ArchiveOlpath)) \
    __IMPL(NamedProperty, ArchiveTarget, (ArchiveTarget)) \
    __IMPL(NamedProperty, ArchiveCategory, (ArchiveCategory)) \
    __IMPL(NamedProperty, ArchiveTodo, (ArchiveTodo)) \
    __IMPL(NamedProperty, Trigger, (Trigger)) \
    __IMPL(NamedProperty, ExportLatexClass, (ExportLatexClass)) \
    __IMPL(NamedProperty, CookieData, (CookieData)) \
    __IMPL(NamedProperty, ExportLatexClassOptions, (ExportLatexClassOptions)) \
    __IMPL(NamedProperty, ExportLatexHeader, (ExportLatexHeader)) \
    __IMPL(NamedProperty, ExportLatexCompiler, (ExportLatexCompiler)) \
    __IMPL(NamedProperty, Ordered, (Ordered)) \
    __IMPL(NamedProperty, Effort, (Effort)) \
    __IMPL(NamedProperty, Visibility, (Visibility)) \
    __IMPL(NamedProperty, ExportOptions, (ExportOptions)) \
    __IMPL(NamedProperty, Blocker, (Blocker)) \
    __IMPL(NamedProperty, Unnumbered, (Unnumbered)) \
    __IMPL(NamedProperty, Created, (Created)) \
    __IMPL(NamedProperty, RadioId, (RadioId)) \
    __IMPL(NamedProperty, HashtagDef, (HashtagDef)) \
    __IMPL(NamedProperty, CustomArgs, (CustomArgs)) \
    __IMPL(NamedProperty, CustomRaw, (CustomRaw)) \
    __IMPL(NamedProperty, CustomSubtreeJson, (CustomSubtreeJson)) \
    __IMPL(NamedProperty, CustomSubtreeFlags, (CustomSubtreeFlags))
#define EACH_SHARED_ORG_ENUM_NESTED(__IMPL) \
    __IMPL(LispCode, Kind, (Kind)) \
    __IMPL(Tblfm, Expr::AxisRef::Position::Kind, (Expr, AxisRef, Position, Kind)) \
    __IMPL(Tblfm, Expr::Kind, (Expr, Kind)) \
    __IMPL(Tblfm, Assign::Flag, (Assign, Flag)) \
    __IMPL(AttrValue, Kind, (Kind)) \
    __IMPL(AttrValue, DataKind, (DataKind)) \
    __IMPL(LinkTarget, Kind, (Kind)) \
    __IMPL(SubtreeLogHead, Priority::Action, (Priority, Action)) \
    __IMPL(SubtreeLogHead, Kind, (Kind)) \
    __IMPL(OrgCodeEvalInput, ResultType, (ResultType)) \
    __IMPL(OrgCodeEvalInput, ResultFormat, (ResultFormat)) \
    __IMPL(OrgCodeEvalInput, ResultHandling, (ResultHandling)) \
    __IMPL(ColumnView, Summary::CheckboxAggregate::Kind, (Summary, CheckboxAggregate, Kind)) \
    __IMPL(ColumnView, Summary::MathAggregate::Kind, (Summary, MathAggregate, Kind)) \
    __IMPL(ColumnView, Summary::Kind, (Summary, Kind)) \
    __IMPL(BlockCodeLine, Part::Kind, (Part, Kind)) \
    __IMPL(DocumentExportConfig, TagExport, (TagExport)) \
    __IMPL(DocumentExportConfig, TaskFiltering, (TaskFiltering)) \
    __IMPL(DocumentExportConfig, BrokenLinks, (BrokenLinks)) \
    __IMPL(DocumentExportConfig, TocExportKind, (TocExportKind)) \
    __IMPL(SubtreePeriod, Kind, (Kind)) \
    __IMPL(NamedProperty, CookieData::TodoSource, (CookieData, TodoSource)) \
    __IMPL(NamedProperty, Visibility::Level, (Visibility, Level)) \
    __IMPL(NamedProperty, Kind, (Kind))
#define EACH_SHARED_ORG_RECORD(__IMPL) \
    __IMPL(LispCode, (LispCode)) \
    __IMPL(LispCode::Call, (LispCode, Call)) \
    __IMPL(LispCode::List, (LispCode, List)) \
    __IMPL(LispCode::KeyValue, (LispCode, KeyValue)) \
    __IMPL(LispCode::Number, (LispCode, Number)) \
    __IMPL(LispCode::Text, (LispCode, Text)) \
    __IMPL(LispCode::Ident, (LispCode, Ident)) \
    __IMPL(LispCode::Boolean, (LispCode, Boolean)) \
    __IMPL(LispCode::Real, (LispCode, Real)) \
    __IMPL(Tblfm, (Tblfm)) \
    __IMPL(Tblfm::Expr, (Tblfm, Expr)) \
    __IMPL(Tblfm::Expr::AxisRef, (Tblfm, Expr, AxisRef)) \
    __IMPL(Tblfm::Expr::AxisRef::Position, (Tblfm, Expr, AxisRef, Position)) \
    __IMPL(Tblfm::Expr::AxisRef::Position::Index, (Tblfm, Expr, AxisRef, Position, Index)) \
    __IMPL(Tblfm::Expr::AxisRef::Position::Name, (Tblfm, Expr, AxisRef, Position, Name)) \
    __IMPL(Tblfm::Expr::AxisName, (Tblfm, Expr, AxisName)) \
    __IMPL(Tblfm::Expr::IntLiteral, (Tblfm, Expr, IntLiteral)) \
    __IMPL(Tblfm::Expr::FloatLiteral, (Tblfm, Expr, FloatLiteral)) \
    __IMPL(Tblfm::Expr::RangeRef, (Tblfm, Expr, RangeRef)) \
    __IMPL(Tblfm::Expr::Call, (Tblfm, Expr, Call)) \
    __IMPL(Tblfm::Expr::Elisp, (Tblfm, Expr, Elisp)) \
    __IMPL(Tblfm::Assign, (Tblfm, Assign)) \
    __IMPL(AttrValue, (AttrValue)) \
    __IMPL(AttrValue::DimensionSpan, (AttrValue, DimensionSpan)) \
    __IMPL(AttrValue::TextValue, (AttrValue, TextValue)) \
    __IMPL(AttrValue::FileReference, (AttrValue, FileReference)) \
    __IMPL(AttrValue::LispValue, (AttrValue, LispValue)) \
    __IMPL(HashTagFlat, (HashTagFlat)) \
    __IMPL(HashTagText, (HashTagText)) \
    __IMPL(SubtreePath, (SubtreePath)) \
    __IMPL(LinkTarget, (LinkTarget)) \
    __IMPL(LinkTarget::Raw, (LinkTarget, Raw)) \
    __IMPL(LinkTarget::Id, (LinkTarget, Id)) \
    __IMPL(LinkTarget::CustomId, (LinkTarget, CustomId)) \
    __IMPL(LinkTarget::SubtreeTitle, (LinkTarget, SubtreeTitle)) \
    __IMPL(LinkTarget::Person, (LinkTarget, Person)) \
    __IMPL(LinkTarget::UserProtocol, (LinkTarget, UserProtocol)) \
    __IMPL(LinkTarget::Internal, (LinkTarget, Internal)) \
    __IMPL(LinkTarget::Footnote, (LinkTarget, Footnote)) \
    __IMPL(LinkTarget::File, (LinkTarget, File)) \
    __IMPL(LinkTarget::Attachment, (LinkTarget, Attachment)) \
    __IMPL(SubtreeLogHead, (SubtreeLogHead)) \
    __IMPL(SubtreeLogHead::Priority, (SubtreeLogHead, Priority)) \
    __IMPL(SubtreeLogHead::Note, (SubtreeLogHead, Note)) \
    __IMPL(SubtreeLogHead::Refile, (SubtreeLogHead, Refile)) \
    __IMPL(SubtreeLogHead::Clock, (SubtreeLogHead, Clock)) \
    __IMPL(SubtreeLogHead::State, (SubtreeLogHead, State)) \
    __IMPL(SubtreeLogHead::Deadline, (SubtreeLogHead, Deadline)) \
    __IMPL(SubtreeLogHead::Schedule, (SubtreeLogHead, Schedule)) \
    __IMPL(SubtreeLogHead::Tag, (SubtreeLogHead, Tag)) \
    __IMPL(SubtreeLogHead::Unknown, (SubtreeLogHead, Unknown)) \
    __IMPL(SubtreeCompletion, (SubtreeCompletion)) \
    __IMPL(AttrList, (AttrList)) \
    __IMPL(AttrGroup, (AttrGroup)) \
    __IMPL(OrgCodeEvalInput, (OrgCodeEvalInput)) \
    __IMPL(OrgCodeEvalInput::Var, (OrgCodeEvalInput, Var)) \
    __IMPL(OrgCodeEvalOutput, (OrgCodeEvalOutput)) \
    __IMPL(ColumnView, (ColumnView)) \
    __IMPL(ColumnView::Summary, (ColumnView, Summary)) \
    __IMPL(ColumnView::Summary::CheckboxAggregate, (ColumnView, Summary, CheckboxAggregate)) \
    __IMPL(ColumnView::Summary::MathAggregate, (ColumnView, Summary, MathAggregate)) \
    __IMPL(ColumnView::Column, (ColumnView, Column)) \
    __IMPL(BlockCodeLine, (BlockCodeLine)) \
    __IMPL(BlockCodeLine::Part, (BlockCodeLine, Part)) \
    __IMPL(BlockCodeLine::Part::Raw, (BlockCodeLine, Part, Raw)) \
    __IMPL(BlockCodeLine::Part::Callout, (BlockCodeLine, Part, Callout)) \
    __IMPL(BlockCodeLine::Part::Tangle, (BlockCodeLine, Part, Tangle)) \
    __IMPL(DocumentExportConfig, (DocumentExportConfig)) \
    __IMPL(DocumentExportConfig::TaskExport, (DocumentExportConfig, TaskExport)) \
    __IMPL(DocumentExportConfig::DoExport, (DocumentExportConfig, DoExport)) \
    __IMPL(DocumentExportConfig::ExportFixed, (DocumentExportConfig, ExportFixed)) \
    __IMPL(SubtreePeriod, (SubtreePeriod)) \
    __IMPL(NamedProperty, (NamedProperty)) \
    __IMPL(NamedProperty::Nonblocking, (NamedProperty, Nonblocking)) \
    __IMPL(NamedProperty::ArchiveTime, (NamedProperty, ArchiveTime)) \
    __IMPL(NamedProperty::ArchiveFile, (NamedProperty, ArchiveFile)) \
    __IMPL(NamedProperty::ArchiveOlpath, (NamedProperty, ArchiveOlpath)) \
    __IMPL(NamedProperty::ArchiveTarget, (NamedProperty, ArchiveTarget)) \
    __IMPL(NamedProperty::ArchiveCategory, (NamedProperty, ArchiveCategory)) \
    __IMPL(NamedProperty::ArchiveTodo, (NamedProperty, ArchiveTodo)) \
    __IMPL(NamedProperty::Trigger, (NamedProperty, Trigger)) \
    __IMPL(NamedProperty::ExportLatexClass, (NamedProperty, ExportLatexClass)) \
    __IMPL(NamedProperty::CookieData, (NamedProperty, CookieData)) \
    __IMPL(NamedProperty::ExportLatexClassOptions, (NamedProperty, ExportLatexClassOptions)) \
    __IMPL(NamedProperty::ExportLatexHeader, (NamedProperty, ExportLatexHeader)) \
    __IMPL(NamedProperty::ExportLatexCompiler, (NamedProperty, ExportLatexCompiler)) \
    __IMPL(NamedProperty::Ordered, (NamedProperty, Ordered)) \
    __IMPL(NamedProperty::Effort, (NamedProperty, Effort)) \
    __IMPL(NamedProperty::Visibility, (NamedProperty, Visibility)) \
    __IMPL(NamedProperty::ExportOptions, (NamedProperty, ExportOptions)) \
    __IMPL(NamedProperty::Blocker, (NamedProperty, Blocker)) \
    __IMPL(NamedProperty::Unnumbered, (NamedProperty, Unnumbered)) \
    __IMPL(NamedProperty::Created, (NamedProperty, Created)) \
    __IMPL(NamedProperty::RadioId, (NamedProperty, RadioId)) \
    __IMPL(NamedProperty::HashtagDef, (NamedProperty, HashtagDef)) \
    __IMPL(NamedProperty::CustomArgs, (NamedProperty, CustomArgs)) \
    __IMPL(NamedProperty::CustomRaw, (NamedProperty, CustomRaw)) \
    __IMPL(NamedProperty::CustomSubtreeJson, (NamedProperty, CustomSubtreeJson)) \
    __IMPL(NamedProperty::CustomSubtreeFlags, (NamedProperty, CustomSubtreeFlags))
#define EACH_SEM_ORG_RECORD_NESTED(__IMPL) \
    __IMPL(Time, Repeat, (Repeat)) \
    __IMPL(Time, Static, (Static)) \
    __IMPL(Time, Dynamic, (Dynamic)) \
    __IMPL(Symbol, Param, (Param)) \
    __IMPL(File, Document, (Document)) \
    __IMPL(File, Attachment, (Attachment)) \
    __IMPL(File, Source, (Source)) \
    __IMPL(CmdInclude, IncludeBase, (IncludeBase)) \
    __IMPL(CmdInclude, Example, (Example)) \
    __IMPL(CmdInclude, Export, (Export)) \
    __IMPL(CmdInclude, Custom, (Custom)) \
    __IMPL(CmdInclude, Src, (Src)) \
    __IMPL(CmdInclude, OrgDocument, (OrgDocument))
#define EACH_SEM_ORG_ENUM_NESTED(__IMPL) \
    __IMPL(Time, Repeat::Mode, (Repeat, Mode)) \
    __IMPL(Time, Repeat::Period, (Repeat, Period)) \
    __IMPL(Time, TimeKind, (TimeKind)) \
    __IMPL(ListItem, Checkbox, (Checkbox)) \
    __IMPL(CriticMarkup, Kind, (Kind)) \
    __IMPL(File, Kind, (Kind)) \
    __IMPL(CmdInclude, Kind, (Kind))
#define EACH_SEM_ORG_RECORD(__IMPL) \
    __IMPL(None, (None)) \
    __IMPL(ErrorItem, (ErrorItem)) \
    __IMPL(ErrorGroup, (ErrorGroup)) \
    __IMPL(Stmt, (Stmt)) \
    __IMPL(Inline, (Inline)) \
    __IMPL(StmtList, (StmtList)) \
    __IMPL(Empty, (Empty)) \
    __IMPL(Cmd, (Cmd)) \
    __IMPL(Block, (Block)) \
    __IMPL(LineCommand, (LineCommand)) \
    __IMPL(Attached, (Attached)) \
    __IMPL(Leaf, (Leaf)) \
    __IMPL(CmdCaption, (CmdCaption)) \
    __IMPL(CmdColumns, (CmdColumns)) \
    __IMPL(CmdName, (CmdName)) \
    __IMPL(CmdCustomArgs, (CmdCustomArgs)) \
    __IMPL(CmdCustomRaw, (CmdCustomRaw)) \
    __IMPL(CmdCustomText, (CmdCustomText)) \
    __IMPL(CmdCall, (CmdCall)) \
    __IMPL(CmdTblfm, (CmdTblfm)) \
    __IMPL(HashTag, (HashTag)) \
    __IMPL(InlineFootnote, (InlineFootnote)) \
    __IMPL(InlineExport, (InlineExport)) \
    __IMPL(Time, (Time)) \
    __IMPL(Time::Repeat, (Time, Repeat)) \
    __IMPL(Time::Static, (Time, Static)) \
    __IMPL(Time::Dynamic, (Time, Dynamic)) \
    __IMPL(TimeRange, (TimeRange)) \
    __IMPL(Macro, (Macro)) \
    __IMPL(Symbol, (Symbol)) \
    __IMPL(Symbol::Param, (Symbol, Param)) \
    __IMPL(Escaped, (Escaped)) \
    __IMPL(Newline, (Newline)) \
    __IMPL(Space, (Space)) \
    __IMPL(Word, (Word)) \
    __IMPL(AtMention, (AtMention)) \
    __IMPL(RawText, (RawText)) \
    __IMPL(Punctuation, (Punctuation)) \
    __IMPL(Placeholder, (Placeholder)) \
    __IMPL(BigIdent, (BigIdent)) \
    __IMPL(TextTarget, (TextTarget)) \
    __IMPL(Markup, (Markup)) \
    __IMPL(Bold, (Bold)) \
    __IMPL(Underline, (Underline)) \
    __IMPL(Monospace, (Monospace)) \
    __IMPL(MarkQuote, (MarkQuote)) \
    __IMPL(Verbatim, (Verbatim)) \
    __IMPL(Italic, (Italic)) \
    __IMPL(Strike, (Strike)) \
    __IMPL(Par, (Par)) \
    __IMPL(RadioTarget, (RadioTarget)) \
    __IMPL(Latex, (Latex)) \
    __IMPL(Link, (Link)) \
    __IMPL(BlockCenter, (BlockCenter)) \
    __IMPL(BlockQuote, (BlockQuote)) \
    __IMPL(BlockComment, (BlockComment)) \
    __IMPL(BlockVerse, (BlockVerse)) \
    __IMPL(BlockDynamicFallback, (BlockDynamicFallback)) \
    __IMPL(BlockExample, (BlockExample)) \
    __IMPL(BlockExport, (BlockExport)) \
    __IMPL(BlockAdmonition, (BlockAdmonition)) \
    __IMPL(BlockCodeEvalResult, (BlockCodeEvalResult)) \
    __IMPL(BlockCode, (BlockCode)) \
    __IMPL(SubtreeLog, (SubtreeLog)) \
    __IMPL(Subtree, (Subtree)) \
    __IMPL(Cell, (Cell)) \
    __IMPL(Row, (Row)) \
    __IMPL(Table, (Table)) \
    __IMPL(Paragraph, (Paragraph)) \
    __IMPL(ColonExample, (ColonExample)) \
    __IMPL(CmdAttr, (CmdAttr)) \
    __IMPL(CmdExport, (CmdExport)) \
    __IMPL(Call, (Call)) \
    __IMPL(List, (List)) \
    __IMPL(ListItem, (ListItem)) \
    __IMPL(DocumentOptions, (DocumentOptions)) \
    __IMPL(DocumentFragment, (DocumentFragment)) \
    __IMPL(CriticMarkup, (CriticMarkup)) \
    __IMPL(Document, (Document)) \
    __IMPL(FileTarget, (FileTarget)) \
    __IMPL(TextSeparator, (TextSeparator)) \
    __IMPL(DocumentGroup, (DocumentGroup)) \
    __IMPL(File, (File)) \
    __IMPL(File::Document, (File, Document)) \
    __IMPL(File::Attachment, (File, Attachment)) \
    __IMPL(File::Source, (File, Source)) \
    __IMPL(Directory, (Directory)) \
    __IMPL(Symlink, (Symlink)) \
    __IMPL(CmdInclude, (CmdInclude)) \
    __IMPL(CmdInclude::IncludeBase, (CmdInclude, IncludeBase)) \
    __IMPL(CmdInclude::Example, (CmdInclude, Example)) \
    __IMPL(CmdInclude::Export, (CmdInclude, Export)) \
    __IMPL(CmdInclude::Custom, (CmdInclude, Custom)) \
    __IMPL(CmdInclude::Src, (CmdInclude, Src)) \
    __IMPL(CmdInclude::OrgDocument, (CmdInclude, OrgDocument))
#define EACH_SEM_ORG_KIND(__IMPL) \
    __IMPL(None) \
    __IMPL(ErrorItem) \
    __IMPL(ErrorGroup) \
    __IMPL(StmtList) \
    __IMPL(Empty) \
    __IMPL(CmdCaption) \
    __IMPL(CmdColumns) \
    __IMPL(CmdName) \
    __IMPL(CmdCustomArgs) \
    __IMPL(CmdCustomRaw) \
    __IMPL(CmdCustomText) \
    __IMPL(CmdCall) \
    __IMPL(CmdTblfm) \
    __IMPL(HashTag) \
    __IMPL(InlineFootnote) \
    __IMPL(InlineExport) \
    __IMPL(Time) \
    __IMPL(TimeRange) \
    __IMPL(Macro) \
    __IMPL(Symbol) \
    __IMPL(Escaped) \
    __IMPL(Newline) \
    __IMPL(Space) \
    __IMPL(Word) \
    __IMPL(AtMention) \
    __IMPL(RawText) \
    __IMPL(Punctuation) \
    __IMPL(Placeholder) \
    __IMPL(BigIdent) \
    __IMPL(TextTarget) \
    __IMPL(Bold) \
    __IMPL(Underline) \
    __IMPL(Monospace) \
    __IMPL(MarkQuote) \
    __IMPL(Verbatim) \
    __IMPL(Italic) \
    __IMPL(Strike) \
    __IMPL(Par) \
    __IMPL(RadioTarget) \
    __IMPL(Latex) \
    __IMPL(Link) \
    __IMPL(BlockCenter) \
    __IMPL(BlockQuote) \
    __IMPL(BlockComment) \
    __IMPL(BlockVerse) \
    __IMPL(BlockDynamicFallback) \
    __IMPL(BlockExample) \
    __IMPL(BlockExport) \
    __IMPL(BlockAdmonition) \
    __IMPL(BlockCodeEvalResult) \
    __IMPL(BlockCode) \
    __IMPL(SubtreeLog) \
    __IMPL(Subtree) \
    __IMPL(Cell) \
    __IMPL(Row) \
    __IMPL(Table) \
    __IMPL(Paragraph) \
    __IMPL(ColonExample) \
    __IMPL(CmdAttr) \
    __IMPL(CmdExport) \
    __IMPL(Call) \
    __IMPL(List) \
    __IMPL(ListItem) \
    __IMPL(DocumentOptions) \
    __IMPL(DocumentFragment) \
    __IMPL(CriticMarkup) \
    __IMPL(Document) \
    __IMPL(FileTarget) \
    __IMPL(TextSeparator) \
    __IMPL(DocumentGroup) \
    __IMPL(File) \
    __IMPL(Directory) \
    __IMPL(Symlink) \
    __IMPL(CmdInclude)
#define EACH_SEM_ORG_FINAL_TYPE_BASE(__IMPL) \
    __IMPL(None, Org) \
    __IMPL(ErrorItem, Org) \
    __IMPL(ErrorGroup, Org) \
    __IMPL(StmtList, Org) \
    __IMPL(Empty, Org) \
    __IMPL(CmdCaption, Attached) \
    __IMPL(CmdColumns, Attached) \
    __IMPL(CmdName, Attached) \
    __IMPL(CmdCustomArgs, Cmd) \
    __IMPL(CmdCustomRaw, Stmt) \
    __IMPL(CmdCustomText, Stmt) \
    __IMPL(CmdCall, Attached) \
    __IMPL(CmdTblfm, Cmd) \
    __IMPL(HashTag, Inline) \
    __IMPL(InlineFootnote, Inline) \
    __IMPL(InlineExport, Inline) \
    __IMPL(Time, Org) \
    __IMPL(TimeRange, Org) \
    __IMPL(Macro, Org) \
    __IMPL(Symbol, Org) \
    __IMPL(Escaped, Leaf) \
    __IMPL(Newline, Leaf) \
    __IMPL(Space, Leaf) \
    __IMPL(Word, Leaf) \
    __IMPL(AtMention, Leaf) \
    __IMPL(RawText, Leaf) \
    __IMPL(Punctuation, Leaf) \
    __IMPL(Placeholder, Leaf) \
    __IMPL(BigIdent, Leaf) \
    __IMPL(TextTarget, Leaf) \
    __IMPL(Bold, Markup) \
    __IMPL(Underline, Markup) \
    __IMPL(Monospace, Markup) \
    __IMPL(MarkQuote, Markup) \
    __IMPL(Verbatim, Markup) \
    __IMPL(Italic, Markup) \
    __IMPL(Strike, Markup) \
    __IMPL(Par, Markup) \
    __IMPL(RadioTarget, Org) \
    __IMPL(Latex, Org) \
    __IMPL(Link, Stmt) \
    __IMPL(BlockCenter, Block) \
    __IMPL(BlockQuote, Block) \
    __IMPL(BlockComment, Stmt) \
    __IMPL(BlockVerse, Block) \
    __IMPL(BlockDynamicFallback, Block) \
    __IMPL(BlockExample, Block) \
    __IMPL(BlockExport, Block) \
    __IMPL(BlockAdmonition, Block) \
    __IMPL(BlockCodeEvalResult, Block) \
    __IMPL(BlockCode, Block) \
    __IMPL(SubtreeLog, Org) \
    __IMPL(Subtree, Org) \
    __IMPL(Cell, Cmd) \
    __IMPL(Row, Cmd) \
    __IMPL(Table, Block) \
    __IMPL(Paragraph, Stmt) \
    __IMPL(ColonExample, Org) \
    __IMPL(CmdAttr, Attached) \
    __IMPL(CmdExport, Attached) \
    __IMPL(Call, Org) \
    __IMPL(List, Stmt) \
    __IMPL(ListItem, Org) \
    __IMPL(DocumentOptions, Org) \
    __IMPL(DocumentFragment, Org) \
    __IMPL(CriticMarkup, Org) \
    __IMPL(Document, Org) \
    __IMPL(FileTarget, Org) \
    __IMPL(TextSeparator, Org) \
    __IMPL(DocumentGroup, Org) \
    __IMPL(File, Org) \
    __IMPL(Directory, Org) \
    __IMPL(Symlink, Org) \
    __IMPL(CmdInclude, Org)
#define EACH_SEM_ORG_TYPE_BASE(__IMPL) \
    __IMPL(None, Org) \
    __IMPL(ErrorItem, Org) \
    __IMPL(ErrorGroup, Org) \
    __IMPL(Stmt, Org) \
    __IMPL(Inline, Org) \
    __IMPL(StmtList, Org) \
    __IMPL(Empty, Org) \
    __IMPL(Cmd, Stmt) \
    __IMPL(Block, Cmd) \
    __IMPL(LineCommand, Cmd) \
    __IMPL(Attached, LineCommand) \
    __IMPL(Leaf, Org) \
    __IMPL(CmdCaption, Attached) \
    __IMPL(CmdColumns, Attached) \
    __IMPL(CmdName, Attached) \
    __IMPL(CmdCustomArgs, Cmd) \
    __IMPL(CmdCustomRaw, Stmt) \
    __IMPL(CmdCustomText, Stmt) \
    __IMPL(CmdCall, Attached) \
    __IMPL(CmdTblfm, Cmd) \
    __IMPL(HashTag, Inline) \
    __IMPL(InlineFootnote, Inline) \
    __IMPL(InlineExport, Inline) \
    __IMPL(Time, Org) \
    __IMPL(TimeRange, Org) \
    __IMPL(Macro, Org) \
    __IMPL(Symbol, Org) \
    __IMPL(Escaped, Leaf) \
    __IMPL(Newline, Leaf) \
    __IMPL(Space, Leaf) \
    __IMPL(Word, Leaf) \
    __IMPL(AtMention, Leaf) \
    __IMPL(RawText, Leaf) \
    __IMPL(Punctuation, Leaf) \
    __IMPL(Placeholder, Leaf) \
    __IMPL(BigIdent, Leaf) \
    __IMPL(TextTarget, Leaf) \
    __IMPL(Markup, Org) \
    __IMPL(Bold, Markup) \
    __IMPL(Underline, Markup) \
    __IMPL(Monospace, Markup) \
    __IMPL(MarkQuote, Markup) \
    __IMPL(Verbatim, Markup) \
    __IMPL(Italic, Markup) \
    __IMPL(Strike, Markup) \
    __IMPL(Par, Markup) \
    __IMPL(RadioTarget, Org) \
    __IMPL(Latex, Org) \
    __IMPL(Link, Stmt) \
    __IMPL(BlockCenter, Block) \
    __IMPL(BlockQuote, Block) \
    __IMPL(BlockComment, Stmt) \
    __IMPL(BlockVerse, Block) \
    __IMPL(BlockDynamicFallback, Block) \
    __IMPL(BlockExample, Block) \
    __IMPL(BlockExport, Block) \
    __IMPL(BlockAdmonition, Block) \
    __IMPL(BlockCodeEvalResult, Block) \
    __IMPL(BlockCode, Block) \
    __IMPL(SubtreeLog, Org) \
    __IMPL(Subtree, Org) \
    __IMPL(Cell, Cmd) \
    __IMPL(Row, Cmd) \
    __IMPL(Table, Block) \
    __IMPL(Paragraph, Stmt) \
    __IMPL(ColonExample, Org) \
    __IMPL(CmdAttr, Attached) \
    __IMPL(CmdExport, Attached) \
    __IMPL(Call, Org) \
    __IMPL(List, Stmt) \
    __IMPL(ListItem, Org) \
    __IMPL(DocumentOptions, Org) \
    __IMPL(DocumentFragment, Org) \
    __IMPL(CriticMarkup, Org) \
    __IMPL(Document, Org) \
    __IMPL(FileTarget, Org) \
    __IMPL(TextSeparator, Org) \
    __IMPL(DocumentGroup, Org) \
    __IMPL(File, Org) \
    __IMPL(Directory, Org) \
    __IMPL(Symlink, Org) \
    __IMPL(CmdInclude, Org)
enum class ListFormattingMode : short int {
  /// \brief Default, no custom formatting
  None,
  /// \brief one column, each table item is an individual row
  Table1D1Col,
  /// \brief for description lists, treat header row as an individual column
  Table1D2Col,
  /// \brief for nested tables, treat the first level of items as column names, treat all nested elements in these columns as row values
  Table2DColFirst,
};
template <>
struct hstd::enum_serde<ListFormattingMode> {
  static hstd::Opt<ListFormattingMode> from_string(std::string value);
  static std::string to_string(ListFormattingMode value);
};

template <>
struct hstd::value_domain<ListFormattingMode> : public value_domain_ungapped<ListFormattingMode,
                                                                             ListFormattingMode::None,
                                                                             ListFormattingMode::Table2DColFirst> {};

enum class InitialSubtreeVisibility : short int { Overview, Content, ShowAll, Show2Levels, Show3Levels, Show4Levels, Show5Levels, ShowEverything, };
template <>
struct hstd::enum_serde<InitialSubtreeVisibility> {
  static hstd::Opt<InitialSubtreeVisibility> from_string(std::string value);
  static std::string to_string(InitialSubtreeVisibility value);
};

template <>
struct hstd::value_domain<InitialSubtreeVisibility> : public value_domain_ungapped<InitialSubtreeVisibility,
                                                                                   InitialSubtreeVisibility::Overview,
                                                                                   InitialSubtreeVisibility::ShowEverything> {};

/// \brief What to do with newly evaluated result
enum class BlockCodeResults : short int {
  /// \brief Remove old result, replace with new value
  Replace,
};
template <>
struct hstd::enum_serde<BlockCodeResults> {
  static hstd::Opt<BlockCodeResults> from_string(std::string value);
  static std::string to_string(BlockCodeResults value);
};

template <>
struct hstd::value_domain<BlockCodeResults> : public value_domain_ungapped<BlockCodeResults,
                                                                           BlockCodeResults::Replace,
                                                                           BlockCodeResults::Replace> {};

/// \brief What part of the code block should be visible in export
enum class BlockCodeExports : short int {
  /// \brief Hide both original code and run result
  None,
  /// \brief Show output and code
  Both,
  /// \brief Show only code
  Code,
  /// \brief Show only evaluation results
  Results,
};
template <>
struct hstd::enum_serde<BlockCodeExports> {
  static hstd::Opt<BlockCodeExports> from_string(std::string value);
  static std::string to_string(BlockCodeExports value);
};

template <>
struct hstd::value_domain<BlockCodeExports> : public value_domain_ungapped<BlockCodeExports,
                                                                           BlockCodeExports::None,
                                                                           BlockCodeExports::Results> {};

enum class OrgSpecName : short int { Unnamed, Result, Year, Day, Clock, Repeater, Zone, Link, Tags, Tag, State, Protocol, Desc, Times, Drawer, Args, Name, Definition, Body, HeaderArgs, File, Kind, Lang, Prefix, Text, Todo, Importance, Title, Completion, Head, Subnodes, Properties, Logbook, Description, Logs, Newstate, Oldstate, Time, From, EndArgs, Flags, Value, Assoc, Main, Hash, Bullet, Counter, Checkbox, Header, To, Diff, Property, Subname, Values, Cells, Rows, Lines, Chunks, };
template <>
struct hstd::enum_serde<OrgSpecName> {
  static hstd::Opt<OrgSpecName> from_string(std::string value);
  static std::string to_string(OrgSpecName value);
};

template <>
struct hstd::value_domain<OrgSpecName> : public value_domain_ungapped<OrgSpecName,
                                                                      OrgSpecName::Unnamed,
                                                                      OrgSpecName::Chunks> {};

enum class OrgNodeKind : short int {
  /// \brief Default valye for node - invalid state
  None,
  /// \brief Toplevel part of the ast, not created by parser, and only used in `semorg` stage
  Document,
  /// \brief Empty node - valid state that does not contain any value
  Empty,
  InlineStmtList,
  /// \brief List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.
  StmtList,
  /// \brief Single checkbox item like `[X]` or `[-]`
  Checkbox,
  List,
  /// \brief List item prefix
  Bullet,
  ListItem,
  /// \brief Auxilliary wrapper for the paragraph placed at the start of the description list.
  ListTag,
  Counter,
  File,
  /// \brief Colon example block
  ColonExample,
  /// \brief Long horizontal line `----`
  TextSeparator,
  /// \brief Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph
  Paragraph,
  /// \brief Horizontal table row
  TableRow,
  /// \brief Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.
  TableCell,
  /// \brief Org-mode table
  Table,
  /// \brief Inline footnote with text placed directly in the node body.
  InlineFootnote,
  /// \brief Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.
  Footnote,
  /// \brief Undefined single-line command -- most likely custom user-provided oe
  Cmd,
  /// \brief Arguments for the command block
  Attrs,
  /// \brief :key name=value syntax
  AttrValue,
  /// \brief S-expression as an attribute value value
  AttrLisp,
  /// \brief `#+title:` - full document title
  CmdTitle,
  /// \brief `#+author:` Document author
  CmdAuthor,
  /// \brief `#+creator:` Document creator
  CmdCreator,
  /// \brief `#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.
  CmdInclude,
  /// \brief `#+language:`
  CmdLanguage,
  /// \brief `#+attr_html:`, `#+attr_image` etc.
  CmdAttr,
  /// \brief `#+startup:`
  CmdStartup,
  /// \brief `#+name:` - name of the associated entry
  CmdName,
  /// \brief Line command with parsed text value
  CmdCustomTextCommand,
  /// \brief Line command with parsed argument list
  CmdCustomArgsCommand,
  /// \brief Line command with raw text argument
  CmdCustomRawCommand,
  /// \brief `#+results:` - source code block evaluation results
  CmdResults,
  /// \brief `#+header:` - extended list of parameters passed to associated block
  CmdHeader,
  /// \brief `#+options:` - document-wide formatting options
  CmdOptions,
  CmdTblfm,
  /// \brief `#+caption:` command
  CmdCaption,
  /// \brief Command evaluation result
  CmdResult,
  /// \brief Call to named source code block.
  CmdCallCode,
  /// \brief Flag for source code block. For example `-n`, which is used to to make source code block export with lines
  CmdFlag,
  CmdLatexClass,
  CmdLatexHeader,
  CmdLatexCompiler,
  CmdLatexClassOptions,
  CmdHtmlHead,
  /// \brief `#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.
  CmdColumns,
  /// \brief `#+property:` command
  CmdPropertyArgs,
  /// \brief `#+property:` command
  CmdPropertyText,
  /// \brief `#+property:` command
  CmdPropertyRaw,
  /// \brief `#+filetags:` line command
  CmdFiletags,
  /// \brief Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.
  BlockVerbatimMultiline,
  /// \brief Single line of source code
  CodeLine,
  /// \brief Block of source code text
  CodeText,
  /// \brief Single tangle target in the code block
  CodeTangle,
  /// \brief `(refs:` callout in the source code
  CodeCallout,
  BlockCode,
  /// \brief `#+begin_quote:` block in code
  BlockQuote,
  /// \brief `#+begin_comment:` block in code
  BlockComment,
  BlockCenter,
  BlockVerse,
  /// \brief Verbatim example text block
  BlockExample,
  BlockExport,
  /// \brief `#+begin_details`  section
  BlockDetails,
  /// \brief `#+begin_summary` section
  BlockSummary,
  /// \brief #+begin_<any> section
  BlockDynamicFallback,
  /// \brief full-uppsercase identifier such as `MUST` or `TODO`
  BigIdent,
  /// \brief Region of text with formatting, which contains standalone words -
  ///      can itself contain subnodes, which allows to represent nested
  ///      formatting regions, such as `*bold /italic/*` text. Particular type
  ///      of identifier is stored in string form in `str` field for `OrgNode`
  ///      -- bold is represented as `"*"`, italic as `/` and so on. In case
  ///      of explicit open/close pairs only opening one is stored.
  ///      NOTE: when structured sentences are enabled, regular punctuation
  ///      elements like `some text (notes)` are also represented as `Word,
  ///      Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.
  Bold,
  ErrorWrap,
  ErrorToken,
  Italic,
  Verbatim,
  Backtick,
  Underline,
  Strike,
  Quote,
  Angle,
  Monospace,
  Par,
  CriticMarkStructure,
  /// \brief Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.
  InlineMath,
  /// \brief Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.
  DisplayMath,
  /// \brief Space or tab character in regular text
  Space,
  Punctuation,
  Colon,
  /// \brief Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.
  Word,
  /// \brief Escaped formatting character in the text
  Escaped,
  Newline,
  /// \brief Raw unwrapped link that was pasted in text
  RawLink,
  /// \brief External or internal link. Consists of one or two elements - target
  ///      (url, file location etc.) and description (`orgParagraph` of text).
  ///      Description might be empty, and represented as empty node in this
  ///      case. For external links particular formatting of the address is
  ///      not handled by parser and instead contains raw string from input
  ///      text.
  Link,
  /// \brief Org-mode macro replacement - during export each macro is expanded
  ///      and evaluated according to it's environment. Body of the macro is
  ///      not parsed fully during org-mode evaluation, but is checked for
  ///      correct parenthesis balance (as macro might contain elisp code)
  Macro,
  /// \brief Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.
  Symbol,
  StaticActiveTime,
  StaticInactiveTime,
  DynamicActiveTime,
  /// \brief Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later
  DynamicInactiveTime,
  /// \brief Date and time range format - two `orgDateTime` entries
  TimeRange,
  /// \brief Result of the time range evaluation or trailing annotation a subtree
  SimpleTime,
  HashTag,
  /// \brief `\sym{}` with explicit arguments
  MetaSymbol,
  /// \brief `@user`
  AtMention,
  /// \brief Placeholder entry in text, usually writte like `<text to replace>`
  Placeholder,
  /// \brief `<<<RADIO>>>`
  RadioTarget,
  /// \brief `<<TARGET>>`
  Target,
  /// \brief inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.
  SrcInlineCode,
  /// \brief Call to named source code block.
  InlineCallCode,
  /// \brief Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively
  InlineExport,
  InlineComment,
  /// \brief Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers
  RawText,
  /// \brief `:description:` entry
  SubtreeDescription,
  SubtreeUrgency,
  /// \brief `:logbook:` entry storing note information
  DrawerLogbook,
  /// \brief Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`
  Drawer,
  DrawerPropertyList,
  /// \brief `:property:` drawer
  DrawerProperty,
  /// \brief Section subtree
  Subtree,
  /// \brief Time? associated with subtree entry
  SubtreeTimes,
  SubtreeStars,
  /// \brief Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.
  SubtreeCompletion,
  /// \brief Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.
  SubtreeImportance,
};
template <>
struct hstd::enum_serde<OrgNodeKind> {
  static hstd::Opt<OrgNodeKind> from_string(std::string value);
  static std::string to_string(OrgNodeKind value);
};

template <>
struct hstd::value_domain<OrgNodeKind> : public value_domain_ungapped<OrgNodeKind,
                                                                      OrgNodeKind::None,
                                                                      OrgNodeKind::SubtreeImportance> {};

enum class OrgJsonKind : short int { Null, Object, Array, String, Boolean, Int, Float, };
template <>
struct hstd::enum_serde<OrgJsonKind> {
  static hstd::Opt<OrgJsonKind> from_string(std::string value);
  static std::string to_string(OrgJsonKind value);
};

template <>
struct hstd::value_domain<OrgJsonKind> : public value_domain_ungapped<OrgJsonKind,
                                                                      OrgJsonKind::Null,
                                                                      OrgJsonKind::Float> {};

enum class OrgSemKind : short int { None, ErrorItem, ErrorGroup, StmtList, Empty, CmdCaption, CmdColumns, CmdName, CmdCustomArgs, CmdCustomRaw, CmdCustomText, CmdCall, CmdTblfm, HashTag, InlineFootnote, InlineExport, Time, TimeRange, Macro, Symbol, Escaped, Newline, Space, Word, AtMention, RawText, Punctuation, Placeholder, BigIdent, TextTarget, Bold, Underline, Monospace, MarkQuote, Verbatim, Italic, Strike, Par, RadioTarget, Latex, Link, BlockCenter, BlockQuote, BlockComment, BlockVerse, BlockDynamicFallback, BlockExample, BlockExport, BlockAdmonition, BlockCodeEvalResult, BlockCode, SubtreeLog, Subtree, Cell, Row, Table, Paragraph, ColonExample, CmdAttr, CmdExport, Call, List, ListItem, DocumentOptions, DocumentFragment, CriticMarkup, Document, FileTarget, TextSeparator, DocumentGroup, File, Directory, Symlink, CmdInclude, };
template <>
struct hstd::enum_serde<OrgSemKind> {
  static hstd::Opt<OrgSemKind> from_string(std::string value);
  static std::string to_string(OrgSemKind value);
};

template <>
struct hstd::value_domain<OrgSemKind> : public value_domain_ungapped<OrgSemKind,
                                                                     OrgSemKind::None,
                                                                     OrgSemKind::CmdInclude> {};


template <>
struct std::formatter<OrgSemKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(OrgSemKind const& p, FormatContext& ctx)
        const {
        std::formatter<std::string> fmt;
        return fmt.format(::hstd::enum_serde<OrgSemKind>::to_string(p), ctx);
    }
};

/* clang-format on */