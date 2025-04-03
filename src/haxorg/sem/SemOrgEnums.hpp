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
#define EACH_SEM_ORG_None_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_None_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_ErrorItem_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), message, Message, (org::sem::ErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), function, Function, (org::sem::ErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::ErrorItem), ErrorItem) \

#define EACH_SEM_ORG_ErrorItem_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), message, Message, (org::sem::ErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), function, Function, (org::sem::ErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::ErrorItem), ErrorItem) \

#define EACH_SEM_ORG_ErrorGroup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>), diagnostics, Diagnostics, (org::sem::ErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), function, Function, (org::sem::ErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::ErrorGroup), ErrorGroup) \

#define EACH_SEM_ORG_ErrorGroup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>), diagnostics, Diagnostics, (org::sem::ErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), function, Function, (org::sem::ErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::ErrorGroup), ErrorGroup) \

#define EACH_SEM_ORG_Stmt_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Org>>), attached, Attached, (org::sem::Stmt), Stmt) \

#define EACH_SEM_ORG_Stmt_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Org>>), attached, Attached, (org::sem::Stmt), Stmt) \

#define EACH_SEM_ORG_Inline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Inline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_StmtList_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_StmtList_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_Empty_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Empty_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_Cmd_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Cmd), Cmd) \

#define EACH_SEM_ORG_Cmd_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Cmd), Cmd) \

#define EACH_SEM_ORG_Block_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Block_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \

#define EACH_SEM_ORG_LineCommand_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_LineCommand_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \

#define EACH_SEM_ORG_Attached_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Attached_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::LineCommand)) \

#define EACH_SEM_ORG_Leaf_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), text, Text, (org::sem::Leaf), Leaf) \

#define EACH_SEM_ORG_Leaf_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), text, Text, (org::sem::Leaf), Leaf) \

#define EACH_SEM_ORG_CmdCaption_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), text, Text, (org::sem::CmdCaption), CmdCaption) \

#define EACH_SEM_ORG_CmdCaption_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), text, Text, (org::sem::CmdCaption), CmdCaption) \

#define EACH_SEM_ORG_CmdColumns_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::ColumnView), view, View, (org::sem::CmdColumns), CmdColumns) \

#define EACH_SEM_ORG_CmdColumns_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((org::sem::ColumnView), view, View, (org::sem::CmdColumns), CmdColumns) \

#define EACH_SEM_ORG_CmdName_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdName), CmdName) \

#define EACH_SEM_ORG_CmdName_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdName), CmdName) \

#define EACH_SEM_ORG_CmdCustomArgs_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomArgs), CmdCustomArgs) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomArgs), CmdCustomArgs) \

#define EACH_SEM_ORG_CmdCustomArgs_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomArgs), CmdCustomArgs) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomArgs), CmdCustomArgs) \

#define EACH_SEM_ORG_CmdCustomRaw_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((hstd::Str), text, Text, (org::sem::CmdCustomRaw), CmdCustomRaw) \

#define EACH_SEM_ORG_CmdCustomRaw_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((hstd::Str), text, Text, (org::sem::CmdCustomRaw), CmdCustomRaw) \

#define EACH_SEM_ORG_CmdCustomText_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomText), CmdCustomText) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomText), CmdCustomText) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), text, Text, (org::sem::CmdCustomText), CmdCustomText) \

#define EACH_SEM_ORG_CmdCustomText_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCustomText), CmdCustomText) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::sem::CmdCustomText), CmdCustomText) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), text, Text, (org::sem::CmdCustomText), CmdCustomText) \

#define EACH_SEM_ORG_CmdCall_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), fileName, Filename, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), insideHeaderAttrs, Insideheaderattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), callAttrs, Callattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), endHeaderAttrs, Endheaderattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>), result, Result, (org::sem::CmdCall), CmdCall) \

#define EACH_SEM_ORG_CmdCall_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), fileName, Filename, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), insideHeaderAttrs, Insideheaderattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), callAttrs, Callattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), endHeaderAttrs, Endheaderattrs, (org::sem::CmdCall), CmdCall) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>), result, Result, (org::sem::CmdCall), CmdCall) \

#define EACH_SEM_ORG_CmdTblfm_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::Tblfm), expr, Expr, (org::sem::CmdTblfm), CmdTblfm) \

#define EACH_SEM_ORG_CmdTblfm_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \
    __IMPL_FIELD((org::sem::Tblfm), expr, Expr, (org::sem::CmdTblfm), CmdTblfm) \

#define EACH_SEM_ORG_HashTag_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::HashTagText), text, Text, (org::sem::HashTag), HashTag) \

#define EACH_SEM_ORG_HashTag_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Inline)) \
    __IMPL_FIELD((org::sem::HashTagText), text, Text, (org::sem::HashTag), HashTag) \

#define EACH_SEM_ORG_InlineFootnote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), tag, Tag, (org::sem::InlineFootnote), InlineFootnote) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Org>>), definition, Definition, (org::sem::InlineFootnote), InlineFootnote) \

#define EACH_SEM_ORG_InlineFootnote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Inline)) \
    __IMPL_FIELD((hstd::Str), tag, Tag, (org::sem::InlineFootnote), InlineFootnote) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Org>>), definition, Definition, (org::sem::InlineFootnote), InlineFootnote) \

#define EACH_SEM_ORG_InlineExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::InlineExport), InlineExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::InlineExport), InlineExport) \

#define EACH_SEM_ORG_InlineExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Inline)) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::InlineExport), InlineExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::InlineExport), InlineExport) \

#define EACH_SEM_ORG_Time_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isActive, Isactive, (org::sem::Time), Time) \
    __IMPL_FIELD((org::sem::Time::TimeVariant), time, Time, (org::sem::Time), Time) \

#define EACH_SEM_ORG_Time_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((bool), isActive, Isactive, (org::sem::Time), Time) \
    __IMPL_FIELD((org::sem::Time::TimeVariant), time, Time, (org::sem::Time), Time) \

#define EACH_SEM_ORG_TimeRange_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Time>), from, From, (org::sem::TimeRange), TimeRange) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Time>), to, To, (org::sem::TimeRange), TimeRange) \

#define EACH_SEM_ORG_TimeRange_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Time>), from, From, (org::sem::TimeRange), TimeRange) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Time>), to, To, (org::sem::TimeRange), TimeRange) \

#define EACH_SEM_ORG_Macro_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Macro), Macro) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Macro), Macro) \

#define EACH_SEM_ORG_Macro_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Macro), Macro) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Macro), Macro) \

#define EACH_SEM_ORG_Symbol_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Symbol), Symbol) \
    __IMPL_FIELD((hstd::Vec<org::sem::Symbol::Param>), parameters, Parameters, (org::sem::Symbol), Symbol) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Org>>), positional, Positional, (org::sem::Symbol), Symbol) \

#define EACH_SEM_ORG_Symbol_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Symbol), Symbol) \
    __IMPL_FIELD((hstd::Vec<org::sem::Symbol::Param>), parameters, Parameters, (org::sem::Symbol), Symbol) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Org>>), positional, Positional, (org::sem::Symbol), Symbol) \

#define EACH_SEM_ORG_Escaped_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Escaped_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Newline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Newline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Space_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Space_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Word_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Word_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_AtMention_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_AtMention_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_RawText_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_RawText_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Punctuation_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Punctuation_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Placeholder_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Placeholder_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_BigIdent_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BigIdent_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_TextTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_TextTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Leaf)) \

#define EACH_SEM_ORG_Markup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Markup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_Bold_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Bold_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Underline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Underline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Monospace_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Monospace_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_MarkQuote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_MarkQuote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Verbatim_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Verbatim_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Italic_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Italic_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Strike_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Strike_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_Par_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Par_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Markup)) \

#define EACH_SEM_ORG_RadioTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<hstd::Str>), words, Words, (org::sem::RadioTarget), RadioTarget) \

#define EACH_SEM_ORG_RadioTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Vec<hstd::Str>), words, Words, (org::sem::RadioTarget), RadioTarget) \

#define EACH_SEM_ORG_Latex_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Latex_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_Link_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), description, Description, (org::sem::Link), Link) \
    __IMPL_FIELD((org::sem::LinkTarget), target, Target, (org::sem::Link), Link) \

#define EACH_SEM_ORG_Link_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), description, Description, (org::sem::Link), Link) \
    __IMPL_FIELD((org::sem::LinkTarget), target, Target, (org::sem::Link), Link) \

#define EACH_SEM_ORG_BlockCenter_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockCenter_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \

#define EACH_SEM_ORG_BlockQuote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockQuote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \

#define EACH_SEM_ORG_BlockComment_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockComment_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \

#define EACH_SEM_ORG_BlockVerse_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockVerse_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \

#define EACH_SEM_ORG_BlockDynamicFallback_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::BlockDynamicFallback), BlockDynamicFallback) \

#define EACH_SEM_ORG_BlockDynamicFallback_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::BlockDynamicFallback), BlockDynamicFallback) \

#define EACH_SEM_ORG_BlockExample_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockExample_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \

#define EACH_SEM_ORG_BlockExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::BlockExport), BlockExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::BlockExport), BlockExport) \

#define EACH_SEM_ORG_BlockExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::BlockExport), BlockExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::BlockExport), BlockExport) \

#define EACH_SEM_ORG_BlockAdmonition_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_BlockAdmonition_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \

#define EACH_SEM_ORG_BlockCodeEvalResult_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<org::sem::OrgCodeEvalOutput>), raw, Raw, (org::sem::BlockCodeEvalResult), BlockCodeEvalResult) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Org>), node, Node, (org::sem::BlockCodeEvalResult), BlockCodeEvalResult) \

#define EACH_SEM_ORG_BlockCodeEvalResult_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \
    __IMPL_FIELD((hstd::Vec<org::sem::OrgCodeEvalOutput>), raw, Raw, (org::sem::BlockCodeEvalResult), BlockCodeEvalResult) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Org>), node, Node, (org::sem::BlockCodeEvalResult), BlockCodeEvalResult) \

#define EACH_SEM_ORG_BlockCode_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), lang, Lang, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((BlockCodeExports), exports, Exports, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>), result, Result, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((hstd::Vec<org::sem::BlockCodeLine>), lines, Lines, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), cache, Cache, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), eval, Eval, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), noweb, Noweb, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), hlines, Hlines, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), tangle, Tangle, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((org::sem::AttrGroup), switches, Switches, (org::sem::BlockCode), BlockCode) \

#define EACH_SEM_ORG_BlockCode_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), lang, Lang, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((BlockCodeExports), exports, Exports, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>), result, Result, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((hstd::Vec<org::sem::BlockCodeLine>), lines, Lines, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), cache, Cache, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), eval, Eval, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), noweb, Noweb, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), hlines, Hlines, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((bool), tangle, Tangle, (org::sem::BlockCode), BlockCode) \
    __IMPL_FIELD((org::sem::AttrGroup), switches, Switches, (org::sem::BlockCode), BlockCode) \

#define EACH_SEM_ORG_SubtreeLog_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::SubtreeLogHead), head, Head, (org::sem::SubtreeLog), SubtreeLog) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::StmtList>>), desc, Desc, (org::sem::SubtreeLog), SubtreeLog) \

#define EACH_SEM_ORG_SubtreeLog_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((org::sem::SubtreeLogHead), head, Head, (org::sem::SubtreeLog), SubtreeLog) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::StmtList>>), desc, Desc, (org::sem::SubtreeLog), SubtreeLog) \

#define EACH_SEM_ORG_Subtree_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((int), level, Level, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), treeId, Treeid, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), todo, Todo, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<org::sem::SubtreeCompletion>), completion, Completion, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), description, Description, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::HashTag>>), tags, Tags, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), title, Title, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>), logbook, Logbook, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::NamedProperty>), properties, Properties, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), closed, Closed, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), deadline, Deadline, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), scheduled, Scheduled, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((bool), isComment, Iscomment, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((bool), isArchived, Isarchived, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), priority, Priority, (org::sem::Subtree), Subtree) \

#define EACH_SEM_ORG_Subtree_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((int), level, Level, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), treeId, Treeid, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), todo, Todo, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<org::sem::SubtreeCompletion>), completion, Completion, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), description, Description, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::HashTag>>), tags, Tags, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((org::sem::SemId<org::sem::Paragraph>), title, Title, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>), logbook, Logbook, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Vec<org::sem::NamedProperty>), properties, Properties, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), closed, Closed, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), deadline, Deadline, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::UserTime>), scheduled, Scheduled, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((bool), isComment, Iscomment, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((bool), isArchived, Isarchived, (org::sem::Subtree), Subtree) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), priority, Priority, (org::sem::Subtree), Subtree) \

#define EACH_SEM_ORG_Cell_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Cell), Cell) \

#define EACH_SEM_ORG_Cell_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Cell), Cell) \

#define EACH_SEM_ORG_Row_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Cell>>), cells, Cells, (org::sem::Row), Row) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Row), Row) \

#define EACH_SEM_ORG_Row_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Cmd)) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Cell>>), cells, Cells, (org::sem::Row), Row) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Row), Row) \

#define EACH_SEM_ORG_Table_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Row>>), rows, Rows, (org::sem::Table), Table) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Table), Table) \

#define EACH_SEM_ORG_Table_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Block)) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::Row>>), rows, Rows, (org::sem::Table), Table) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::sem::Table), Table) \

#define EACH_SEM_ORG_Paragraph_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_Paragraph_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \

#define EACH_SEM_ORG_ColonExample_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_ColonExample_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_CmdAttr_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), target, Target, (org::sem::CmdAttr), CmdAttr) \

#define EACH_SEM_ORG_CmdAttr_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((hstd::Str), target, Target, (org::sem::CmdAttr), CmdAttr) \

#define EACH_SEM_ORG_CmdExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::CmdExport), CmdExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::CmdExport), CmdExport) \

#define EACH_SEM_ORG_CmdExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Attached)) \
    __IMPL_FIELD((hstd::Str), exporter, Exporter, (org::sem::CmdExport), CmdExport) \
    __IMPL_FIELD((hstd::Str), content, Content, (org::sem::CmdExport), CmdExport) \

#define EACH_SEM_ORG_Call_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Call), Call) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Call), Call) \
    __IMPL_FIELD((bool), isCommand, Iscommand, (org::sem::Call), Call) \

#define EACH_SEM_ORG_Call_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), name, Name, (org::sem::Call), Call) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::sem::Call), Call) \
    __IMPL_FIELD((bool), isCommand, Iscommand, (org::sem::Call), Call) \

#define EACH_SEM_ORG_List_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_List_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Stmt)) \

#define EACH_SEM_ORG_ListItem_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::ListItem::Checkbox), checkbox, Checkbox, (org::sem::ListItem), ListItem) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), header, Header, (org::sem::ListItem), ListItem) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), bullet, Bullet, (org::sem::ListItem), ListItem) \

#define EACH_SEM_ORG_ListItem_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((org::sem::ListItem::Checkbox), checkbox, Checkbox, (org::sem::ListItem), ListItem) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), header, Header, (org::sem::ListItem), ListItem) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), bullet, Bullet, (org::sem::ListItem), ListItem) \

#define EACH_SEM_ORG_DocumentOptions_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((InitialSubtreeVisibility), initialVisibility, Initialvisibility, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Vec<org::sem::NamedProperty>), properties, Properties, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((org::sem::DocumentExportConfig), exportConfig, Exportconfig, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<bool>), fixedWidthSections, Fixedwidthsections, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<bool>), startupIndented, Startupindented, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), category, Category, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), setupfile, Setupfile, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<int>), maxSubtreeLevelExport, Maxsubtreelevelexport, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<org::sem::ColumnView>), columns, Columns, (org::sem::DocumentOptions), DocumentOptions) \

#define EACH_SEM_ORG_DocumentOptions_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((InitialSubtreeVisibility), initialVisibility, Initialvisibility, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Vec<org::sem::NamedProperty>), properties, Properties, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((org::sem::DocumentExportConfig), exportConfig, Exportconfig, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<bool>), fixedWidthSections, Fixedwidthsections, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<bool>), startupIndented, Startupindented, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), category, Category, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), setupfile, Setupfile, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<int>), maxSubtreeLevelExport, Maxsubtreelevelexport, (org::sem::DocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::Opt<org::sem::ColumnView>), columns, Columns, (org::sem::DocumentOptions), DocumentOptions) \

#define EACH_SEM_ORG_DocumentFragment_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((int), baseLine, Baseline, (org::sem::DocumentFragment), DocumentFragment) \
    __IMPL_FIELD((int), baseCol, Basecol, (org::sem::DocumentFragment), DocumentFragment) \

#define EACH_SEM_ORG_DocumentFragment_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((int), baseLine, Baseline, (org::sem::DocumentFragment), DocumentFragment) \
    __IMPL_FIELD((int), baseCol, Basecol, (org::sem::DocumentFragment), DocumentFragment) \

#define EACH_SEM_ORG_CriticMarkup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::CriticMarkup::Kind), kind, Kind, (org::sem::CriticMarkup), CriticMarkup) \

#define EACH_SEM_ORG_CriticMarkup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((org::sem::CriticMarkup::Kind), kind, Kind, (org::sem::CriticMarkup), CriticMarkup) \

#define EACH_SEM_ORG_Document_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), title, Title, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), author, Author, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), creator, Creator, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::HashTag>>), filetags, Filetags, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::RawText>>), email, Email, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Vec<hstd::Str>), language, Language, (org::sem::Document), Document) \
    __IMPL_FIELD((org::sem::SemId<org::sem::DocumentOptions>), options, Options, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), exportFileName, Exportfilename, (org::sem::Document), Document) \

#define EACH_SEM_ORG_Document_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), title, Title, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), author, Author, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::Paragraph>>), creator, Creator, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Vec<org::sem::SemId<org::sem::HashTag>>), filetags, Filetags, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<org::sem::SemId<org::sem::RawText>>), email, Email, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Vec<hstd::Str>), language, Language, (org::sem::Document), Document) \
    __IMPL_FIELD((org::sem::SemId<org::sem::DocumentOptions>), options, Options, (org::sem::Document), Document) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), exportFileName, Exportfilename, (org::sem::Document), Document) \

#define EACH_SEM_ORG_FileTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), path, Path, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), searchTarget, Searchtarget, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((bool), restrictToHeadlines, Restricttoheadlines, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), targetId, Targetid, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), regexp, Regexp, (org::sem::FileTarget), FileTarget) \

#define EACH_SEM_ORG_FileTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), path, Path, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<int>), line, Line, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), searchTarget, Searchtarget, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((bool), restrictToHeadlines, Restricttoheadlines, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), targetId, Targetid, (org::sem::FileTarget), FileTarget) \
    __IMPL_FIELD((hstd::Opt<hstd::Str>), regexp, Regexp, (org::sem::FileTarget), FileTarget) \

#define EACH_SEM_ORG_TextSeparator_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_TextSeparator_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_DocumentGroup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_SEM_ORG_DocumentGroup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \

#define EACH_SEM_ORG_File_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), relPath, Relpath, (org::sem::File), File) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::File), File) \
    __IMPL_FIELD((org::sem::File::Data), data, Data, (org::sem::File), File) \

#define EACH_SEM_ORG_File_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), relPath, Relpath, (org::sem::File), File) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::File), File) \
    __IMPL_FIELD((org::sem::File::Data), data, Data, (org::sem::File), File) \

#define EACH_SEM_ORG_Directory_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), relPath, Relpath, (org::sem::Directory), Directory) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::Directory), Directory) \

#define EACH_SEM_ORG_Directory_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), relPath, Relpath, (org::sem::Directory), Directory) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::Directory), Directory) \

#define EACH_SEM_ORG_Symlink_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isDirectory, Isdirectory, (org::sem::Symlink), Symlink) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::Symlink), Symlink) \

#define EACH_SEM_ORG_Symlink_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((bool), isDirectory, Isdirectory, (org::sem::Symlink), Symlink) \
    __IMPL_FIELD((hstd::Str), absPath, Abspath, (org::sem::Symlink), Symlink) \

#define EACH_SEM_ORG_CmdInclude_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::Str), path, Path, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::Opt<int>), firstLine, Firstline, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::Opt<int>), lastLine, Lastline, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((org::sem::CmdInclude::Data), data, Data, (org::sem::CmdInclude), CmdInclude) \

#define EACH_SEM_ORG_CmdInclude_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::sem::Org)) \
    __IMPL_FIELD((hstd::Str), path, Path, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::Opt<int>), firstLine, Firstline, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::Opt<int>), lastLine, Lastline, (org::sem::CmdInclude), CmdInclude) \
    __IMPL_FIELD((org::sem::CmdInclude::Data), data, Data, (org::sem::CmdInclude), CmdInclude) \

#define EACH_IMM_ORG_ImmNone_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmNone_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmErrorItem_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), message, Message, (org::imm::ImmErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), function, Function, (org::imm::ImmErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmErrorItem), ErrorItem) \

#define EACH_IMM_ORG_ImmErrorItem_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), message, Message, (org::imm::ImmErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), function, Function, (org::imm::ImmErrorItem), ErrorItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmErrorItem), ErrorItem) \

#define EACH_IMM_ORG_ImmErrorGroup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>), diagnostics, Diagnostics, (org::imm::ImmErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), function, Function, (org::imm::ImmErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmErrorGroup), ErrorGroup) \

#define EACH_IMM_ORG_ImmErrorGroup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>), diagnostics, Diagnostics, (org::imm::ImmErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), function, Function, (org::imm::ImmErrorGroup), ErrorGroup) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmErrorGroup), ErrorGroup) \

#define EACH_IMM_ORG_ImmStmt_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>), attached, Attached, (org::imm::ImmStmt), Stmt) \

#define EACH_IMM_ORG_ImmStmt_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>), attached, Attached, (org::imm::ImmStmt), Stmt) \

#define EACH_IMM_ORG_ImmInline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmInline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmStmtList_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmStmtList_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmEmpty_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmEmpty_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmCmd_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmCmd), Cmd) \

#define EACH_IMM_ORG_ImmCmd_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmCmd), Cmd) \

#define EACH_IMM_ORG_ImmBlock_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlock_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \

#define EACH_IMM_ORG_ImmLineCommand_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmLineCommand_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \

#define EACH_IMM_ORG_ImmAttached_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmAttached_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLineCommand)) \

#define EACH_IMM_ORG_ImmLeaf_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), text, Text, (org::imm::ImmLeaf), Leaf) \

#define EACH_IMM_ORG_ImmLeaf_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), text, Text, (org::imm::ImmLeaf), Leaf) \

#define EACH_IMM_ORG_ImmCmdCaption_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), text, Text, (org::imm::ImmCmdCaption), CmdCaption) \

#define EACH_IMM_ORG_ImmCmdCaption_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), text, Text, (org::imm::ImmCmdCaption), CmdCaption) \

#define EACH_IMM_ORG_ImmCmdColumns_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::ColumnView), view, View, (org::imm::ImmCmdColumns), CmdColumns) \

#define EACH_IMM_ORG_ImmCmdColumns_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((org::sem::ColumnView), view, View, (org::imm::ImmCmdColumns), CmdColumns) \

#define EACH_IMM_ORG_ImmCmdName_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdName), CmdName) \

#define EACH_IMM_ORG_ImmCmdName_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdName), CmdName) \

#define EACH_IMM_ORG_ImmCmdCustomArgs_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomArgs), CmdCustomArgs) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomArgs), CmdCustomArgs) \

#define EACH_IMM_ORG_ImmCmdCustomArgs_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomArgs), CmdCustomArgs) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomArgs), CmdCustomArgs) \

#define EACH_IMM_ORG_ImmCmdCustomRaw_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), text, Text, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \

#define EACH_IMM_ORG_ImmCmdCustomRaw_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), text, Text, (org::imm::ImmCmdCustomRaw), CmdCustomRaw) \

#define EACH_IMM_ORG_ImmCmdCustomText_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomText), CmdCustomText) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomText), CmdCustomText) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), text, Text, (org::imm::ImmCmdCustomText), CmdCustomText) \

#define EACH_IMM_ORG_ImmCmdCustomText_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCustomText), CmdCustomText) \
    __IMPL_FIELD((bool), isAttached, Isattached, (org::imm::ImmCmdCustomText), CmdCustomText) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), text, Text, (org::imm::ImmCmdCustomText), CmdCustomText) \

#define EACH_IMM_ORG_ImmCmdCall_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), fileName, Filename, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), insideHeaderAttrs, Insideheaderattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), callAttrs, Callattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), endHeaderAttrs, Endheaderattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>), result, Result, (org::imm::ImmCmdCall), CmdCall) \

#define EACH_IMM_ORG_ImmCmdCall_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), fileName, Filename, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), insideHeaderAttrs, Insideheaderattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), callAttrs, Callattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((org::sem::AttrGroup), endHeaderAttrs, Endheaderattrs, (org::imm::ImmCmdCall), CmdCall) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>), result, Result, (org::imm::ImmCmdCall), CmdCall) \

#define EACH_IMM_ORG_ImmCmdTblfm_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::Tblfm), expr, Expr, (org::imm::ImmCmdTblfm), CmdTblfm) \

#define EACH_IMM_ORG_ImmCmdTblfm_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \
    __IMPL_FIELD((org::sem::Tblfm), expr, Expr, (org::imm::ImmCmdTblfm), CmdTblfm) \

#define EACH_IMM_ORG_ImmHashTag_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::HashTagText), text, Text, (org::imm::ImmHashTag), HashTag) \

#define EACH_IMM_ORG_ImmHashTag_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmInline)) \
    __IMPL_FIELD((org::sem::HashTagText), text, Text, (org::imm::ImmHashTag), HashTag) \

#define EACH_IMM_ORG_ImmInlineFootnote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), tag, Tag, (org::imm::ImmInlineFootnote), InlineFootnote) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>), definition, Definition, (org::imm::ImmInlineFootnote), InlineFootnote) \

#define EACH_IMM_ORG_ImmInlineFootnote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmInline)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), tag, Tag, (org::imm::ImmInlineFootnote), InlineFootnote) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>), definition, Definition, (org::imm::ImmInlineFootnote), InlineFootnote) \

#define EACH_IMM_ORG_ImmInlineExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmInlineExport), InlineExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmInlineExport), InlineExport) \

#define EACH_IMM_ORG_ImmInlineExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmInline)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmInlineExport), InlineExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmInlineExport), InlineExport) \

#define EACH_IMM_ORG_ImmTime_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isActive, Isactive, (org::imm::ImmTime), Time) \
    __IMPL_FIELD((org::imm::ImmTime::TimeVariant), time, Time, (org::imm::ImmTime), Time) \

#define EACH_IMM_ORG_ImmTime_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((bool), isActive, Isactive, (org::imm::ImmTime), Time) \
    __IMPL_FIELD((org::imm::ImmTime::TimeVariant), time, Time, (org::imm::ImmTime), Time) \

#define EACH_IMM_ORG_ImmTimeRange_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmTime>), from, From, (org::imm::ImmTimeRange), TimeRange) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmTime>), to, To, (org::imm::ImmTimeRange), TimeRange) \

#define EACH_IMM_ORG_ImmTimeRange_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmTime>), from, From, (org::imm::ImmTimeRange), TimeRange) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmTime>), to, To, (org::imm::ImmTimeRange), TimeRange) \

#define EACH_IMM_ORG_ImmMacro_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmMacro), Macro) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmMacro), Macro) \

#define EACH_IMM_ORG_ImmMacro_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmMacro), Macro) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmMacro), Macro) \

#define EACH_IMM_ORG_ImmSymbol_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmSymbol), Symbol) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmSymbol::Param>), parameters, Parameters, (org::imm::ImmSymbol), Symbol) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>), positional, Positional, (org::imm::ImmSymbol), Symbol) \

#define EACH_IMM_ORG_ImmSymbol_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmSymbol), Symbol) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmSymbol::Param>), parameters, Parameters, (org::imm::ImmSymbol), Symbol) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>), positional, Positional, (org::imm::ImmSymbol), Symbol) \

#define EACH_IMM_ORG_ImmEscaped_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmEscaped_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmNewline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmNewline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmSpace_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmSpace_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmWord_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmWord_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmAtMention_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmAtMention_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmRawText_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmRawText_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmPunctuation_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmPunctuation_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmPlaceholder_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmPlaceholder_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmBigIdent_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBigIdent_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmTextTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmTextTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmLeaf)) \

#define EACH_IMM_ORG_ImmMarkup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmMarkup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmBold_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBold_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmUnderline_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmUnderline_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmMonospace_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmMonospace_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmMarkQuote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmMarkQuote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmVerbatim_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmVerbatim_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmItalic_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmItalic_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmStrike_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmStrike_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmPar_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmPar_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmMarkup)) \

#define EACH_IMM_ORG_ImmRadioTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<hstd::Str>), words, Words, (org::imm::ImmRadioTarget), RadioTarget) \

#define EACH_IMM_ORG_ImmRadioTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmVec<hstd::Str>), words, Words, (org::imm::ImmRadioTarget), RadioTarget) \

#define EACH_IMM_ORG_ImmLatex_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmLatex_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmLink_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), description, Description, (org::imm::ImmLink), Link) \
    __IMPL_FIELD((org::sem::LinkTarget), target, Target, (org::imm::ImmLink), Link) \

#define EACH_IMM_ORG_ImmLink_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), description, Description, (org::imm::ImmLink), Link) \
    __IMPL_FIELD((org::sem::LinkTarget), target, Target, (org::imm::ImmLink), Link) \

#define EACH_IMM_ORG_ImmBlockCenter_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockCenter_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \

#define EACH_IMM_ORG_ImmBlockQuote_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockQuote_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \

#define EACH_IMM_ORG_ImmBlockComment_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockComment_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \

#define EACH_IMM_ORG_ImmBlockVerse_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockVerse_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \

#define EACH_IMM_ORG_ImmBlockDynamicFallback_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmBlockDynamicFallback), BlockDynamicFallback) \

#define EACH_IMM_ORG_ImmBlockDynamicFallback_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmBlockDynamicFallback), BlockDynamicFallback) \

#define EACH_IMM_ORG_ImmBlockExample_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockExample_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \

#define EACH_IMM_ORG_ImmBlockExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmBlockExport), BlockExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmBlockExport), BlockExport) \

#define EACH_IMM_ORG_ImmBlockExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmBlockExport), BlockExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmBlockExport), BlockExport) \

#define EACH_IMM_ORG_ImmBlockAdmonition_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmBlockAdmonition_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \

#define EACH_IMM_ORG_ImmBlockCodeEvalResult_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>), raw, Raw, (org::imm::ImmBlockCodeEvalResult), BlockCodeEvalResult) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmOrg>), node, Node, (org::imm::ImmBlockCodeEvalResult), BlockCodeEvalResult) \

#define EACH_IMM_ORG_ImmBlockCodeEvalResult_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>), raw, Raw, (org::imm::ImmBlockCodeEvalResult), BlockCodeEvalResult) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmOrg>), node, Node, (org::imm::ImmBlockCodeEvalResult), BlockCodeEvalResult) \

#define EACH_IMM_ORG_ImmBlockCode_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), lang, Lang, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((BlockCodeExports), exports, Exports, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>), result, Result, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::BlockCodeLine>), lines, Lines, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), cache, Cache, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), eval, Eval, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), noweb, Noweb, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), hlines, Hlines, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), tangle, Tangle, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((org::sem::AttrGroup), switches, Switches, (org::imm::ImmBlockCode), BlockCode) \

#define EACH_IMM_ORG_ImmBlockCode_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), lang, Lang, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((BlockCodeExports), exports, Exports, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>), result, Result, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::BlockCodeLine>), lines, Lines, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), cache, Cache, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), eval, Eval, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), noweb, Noweb, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), hlines, Hlines, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((bool), tangle, Tangle, (org::imm::ImmBlockCode), BlockCode) \
    __IMPL_FIELD((org::sem::AttrGroup), switches, Switches, (org::imm::ImmBlockCode), BlockCode) \

#define EACH_IMM_ORG_ImmSubtreeLog_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::sem::SubtreeLogHead), head, Head, (org::imm::ImmSubtreeLog), SubtreeLog) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>), desc, Desc, (org::imm::ImmSubtreeLog), SubtreeLog) \

#define EACH_IMM_ORG_ImmSubtreeLog_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((org::sem::SubtreeLogHead), head, Head, (org::imm::ImmSubtreeLog), SubtreeLog) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>), desc, Desc, (org::imm::ImmSubtreeLog), SubtreeLog) \

#define EACH_IMM_ORG_ImmSubtree_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((int), level, Level, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), treeId, Treeid, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), todo, Todo, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>>), completion, Completion, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), description, Description, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>), tags, Tags, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), title, Title, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>), logbook, Logbook, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::NamedProperty>), properties, Properties, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), closed, Closed, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), deadline, Deadline, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), scheduled, Scheduled, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((bool), isComment, Iscomment, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((bool), isArchived, Isarchived, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), priority, Priority, (org::imm::ImmSubtree), Subtree) \

#define EACH_IMM_ORG_ImmSubtree_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((int), level, Level, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), treeId, Treeid, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), todo, Todo, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>>), completion, Completion, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), description, Description, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>), tags, Tags, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmParagraph>), title, Title, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>), logbook, Logbook, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::NamedProperty>), properties, Properties, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), closed, Closed, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), deadline, Deadline, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::UserTime>>), scheduled, Scheduled, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((bool), isComment, Iscomment, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((bool), isArchived, Isarchived, (org::imm::ImmSubtree), Subtree) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), priority, Priority, (org::imm::ImmSubtree), Subtree) \

#define EACH_IMM_ORG_ImmCell_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmCell), Cell) \

#define EACH_IMM_ORG_ImmCell_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmCell), Cell) \

#define EACH_IMM_ORG_ImmRow_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>), cells, Cells, (org::imm::ImmRow), Row) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmRow), Row) \

#define EACH_IMM_ORG_ImmRow_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmCmd)) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>), cells, Cells, (org::imm::ImmRow), Row) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmRow), Row) \

#define EACH_IMM_ORG_ImmTable_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>), rows, Rows, (org::imm::ImmTable), Table) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmTable), Table) \

#define EACH_IMM_ORG_ImmTable_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmBlock)) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>), rows, Rows, (org::imm::ImmTable), Table) \
    __IMPL_FIELD((bool), isBlock, Isblock, (org::imm::ImmTable), Table) \

#define EACH_IMM_ORG_ImmParagraph_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmParagraph_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \

#define EACH_IMM_ORG_ImmColonExample_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmColonExample_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmCmdAttr_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), target, Target, (org::imm::ImmCmdAttr), CmdAttr) \

#define EACH_IMM_ORG_ImmCmdAttr_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), target, Target, (org::imm::ImmCmdAttr), CmdAttr) \

#define EACH_IMM_ORG_ImmCmdExport_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmCmdExport), CmdExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmCmdExport), CmdExport) \

#define EACH_IMM_ORG_ImmCmdExport_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmAttached)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), exporter, Exporter, (org::imm::ImmCmdExport), CmdExport) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), content, Content, (org::imm::ImmCmdExport), CmdExport) \

#define EACH_IMM_ORG_ImmCall_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCall), Call) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmCall), Call) \
    __IMPL_FIELD((bool), isCommand, Iscommand, (org::imm::ImmCall), Call) \

#define EACH_IMM_ORG_ImmCall_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), name, Name, (org::imm::ImmCall), Call) \
    __IMPL_FIELD((org::sem::AttrGroup), attrs, Attrs, (org::imm::ImmCall), Call) \
    __IMPL_FIELD((bool), isCommand, Iscommand, (org::imm::ImmCall), Call) \

#define EACH_IMM_ORG_ImmList_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmList_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmStmt)) \

#define EACH_IMM_ORG_ImmListItem_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::imm::ImmListItem::Checkbox), checkbox, Checkbox, (org::imm::ImmListItem), ListItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), header, Header, (org::imm::ImmListItem), ListItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), bullet, Bullet, (org::imm::ImmListItem), ListItem) \

#define EACH_IMM_ORG_ImmListItem_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((org::imm::ImmListItem::Checkbox), checkbox, Checkbox, (org::imm::ImmListItem), ListItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), header, Header, (org::imm::ImmListItem), ListItem) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), bullet, Bullet, (org::imm::ImmListItem), ListItem) \

#define EACH_IMM_ORG_ImmDocumentOptions_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((InitialSubtreeVisibility), initialVisibility, Initialvisibility, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::NamedProperty>), properties, Properties, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((org::sem::DocumentExportConfig), exportConfig, Exportconfig, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<bool>>), fixedWidthSections, Fixedwidthsections, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<bool>>), startupIndented, Startupindented, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), category, Category, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), setupfile, Setupfile, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), maxSubtreeLevelExport, Maxsubtreelevelexport, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>>), columns, Columns, (org::imm::ImmDocumentOptions), DocumentOptions) \

#define EACH_IMM_ORG_ImmDocumentOptions_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((InitialSubtreeVisibility), initialVisibility, Initialvisibility, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::sem::NamedProperty>), properties, Properties, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((org::sem::DocumentExportConfig), exportConfig, Exportconfig, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<bool>>), fixedWidthSections, Fixedwidthsections, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<bool>>), startupIndented, Startupindented, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), category, Category, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), setupfile, Setupfile, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), maxSubtreeLevelExport, Maxsubtreelevelexport, (org::imm::ImmDocumentOptions), DocumentOptions) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>>), columns, Columns, (org::imm::ImmDocumentOptions), DocumentOptions) \

#define EACH_IMM_ORG_ImmDocumentFragment_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((int), baseLine, Baseline, (org::imm::ImmDocumentFragment), DocumentFragment) \
    __IMPL_FIELD((int), baseCol, Basecol, (org::imm::ImmDocumentFragment), DocumentFragment) \

#define EACH_IMM_ORG_ImmDocumentFragment_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((int), baseLine, Baseline, (org::imm::ImmDocumentFragment), DocumentFragment) \
    __IMPL_FIELD((int), baseCol, Basecol, (org::imm::ImmDocumentFragment), DocumentFragment) \

#define EACH_IMM_ORG_ImmCriticMarkup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((org::imm::ImmCriticMarkup::Kind), kind, Kind, (org::imm::ImmCriticMarkup), CriticMarkup) \

#define EACH_IMM_ORG_ImmCriticMarkup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((org::imm::ImmCriticMarkup::Kind), kind, Kind, (org::imm::ImmCriticMarkup), CriticMarkup) \

#define EACH_IMM_ORG_ImmDocument_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), title, Title, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), author, Author, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), creator, Creator, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>), filetags, Filetags, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>), email, Email, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmVec<hstd::Str>), language, Language, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmDocumentOptions>), options, Options, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), exportFileName, Exportfilename, (org::imm::ImmDocument), Document) \

#define EACH_IMM_ORG_ImmDocument_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), title, Title, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), author, Author, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>), creator, Creator, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>), filetags, Filetags, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>), email, Email, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmVec<hstd::Str>), language, Language, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((org::imm::ImmIdT<org::imm::ImmDocumentOptions>), options, Options, (org::imm::ImmDocument), Document) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), exportFileName, Exportfilename, (org::imm::ImmDocument), Document) \

#define EACH_IMM_ORG_ImmFileTarget_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), path, Path, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), searchTarget, Searchtarget, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((bool), restrictToHeadlines, Restricttoheadlines, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), targetId, Targetid, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), regexp, Regexp, (org::imm::ImmFileTarget), FileTarget) \

#define EACH_IMM_ORG_ImmFileTarget_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), path, Path, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), line, Line, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), searchTarget, Searchtarget, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((bool), restrictToHeadlines, Restricttoheadlines, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), targetId, Targetid, (org::imm::ImmFileTarget), FileTarget) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<hstd::Str>>), regexp, Regexp, (org::imm::ImmFileTarget), FileTarget) \

#define EACH_IMM_ORG_ImmTextSeparator_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmTextSeparator_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmDocumentGroup_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \

#define EACH_IMM_ORG_ImmDocumentGroup_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \

#define EACH_IMM_ORG_ImmFile_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), relPath, Relpath, (org::imm::ImmFile), File) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmFile), File) \
    __IMPL_FIELD((org::imm::ImmFile::Data), data, Data, (org::imm::ImmFile), File) \

#define EACH_IMM_ORG_ImmFile_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), relPath, Relpath, (org::imm::ImmFile), File) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmFile), File) \
    __IMPL_FIELD((org::imm::ImmFile::Data), data, Data, (org::imm::ImmFile), File) \

#define EACH_IMM_ORG_ImmDirectory_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), relPath, Relpath, (org::imm::ImmDirectory), Directory) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmDirectory), Directory) \

#define EACH_IMM_ORG_ImmDirectory_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), relPath, Relpath, (org::imm::ImmDirectory), Directory) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmDirectory), Directory) \

#define EACH_IMM_ORG_ImmSymlink_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((bool), isDirectory, Isdirectory, (org::imm::ImmSymlink), Symlink) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmSymlink), Symlink) \

#define EACH_IMM_ORG_ImmSymlink_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((bool), isDirectory, Isdirectory, (org::imm::ImmSymlink), Symlink) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), absPath, Abspath, (org::imm::ImmSymlink), Symlink) \

#define EACH_IMM_ORG_ImmCmdInclude_FIELD_WITH_BASE_FIELDS(__IMPL_FIELD) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), path, Path, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), firstLine, Firstline, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), lastLine, Lastline, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((org::imm::ImmCmdInclude::Data), data, Data, (org::imm::ImmCmdInclude), CmdInclude) \

#define EACH_IMM_ORG_ImmCmdInclude_FIELD_WITH_BASES(__IMPL_BASE) \
    __IMPL_BASE((org::imm::ImmOrg)) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Str>), path, Path, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), firstLine, Firstline, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((hstd::ext::ImmBox<hstd::Opt<int>>), lastLine, Lastline, (org::imm::ImmCmdInclude), CmdInclude) \
    __IMPL_FIELD((org::imm::ImmCmdInclude::Data), data, Data, (org::imm::ImmCmdInclude), CmdInclude) \

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