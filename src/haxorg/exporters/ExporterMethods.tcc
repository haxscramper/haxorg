/* clang-format off */
void visit(R& res, sem::Tblfm const& object);
void visit(R& res, sem::Tblfm::Expr::Data const& object);
void visit(R& res, sem::Tblfm::Expr const& object);
void visit(R& res, sem::Tblfm::Expr::AxisRef const& object);
void visit(R& res, sem::Tblfm::Expr::AxisRef::Position::Data const& object);
void visit(R& res, sem::Tblfm::Expr::AxisRef::Position const& object);
void visit(R& res, sem::Tblfm::Expr::AxisRef::Position::Index const& object);
void visit(R& res, sem::Tblfm::Expr::AxisRef::Position::Name const& object);
void visit(R& res, sem::Tblfm::Expr::AxisName const& object);
void visit(R& res, sem::Tblfm::Expr::IntLiteral const& object);
void visit(R& res, sem::Tblfm::Expr::FloatLiteral const& object);
void visit(R& res, sem::Tblfm::Expr::RangeRef const& object);
void visit(R& res, sem::Tblfm::Expr::Call const& object);
void visit(R& res, sem::Tblfm::Expr::Elisp const& object);
void visit(R& res, sem::Tblfm::Assign const& object);
void visit(R& res, sem::AttrValue const& object);
void visit(R& res, sem::HashTagFlat const& object);
void visit(R& res, sem::HashTagText const& object);
void visit(R& res, sem::SubtreePath const& object);
void visit(R& res, sem::LinkTarget::Data const& object);
void visit(R& res, sem::LinkTarget const& object);
void visit(R& res, sem::LinkTarget::Raw const& object);
void visit(R& res, sem::LinkTarget::Id const& object);
void visit(R& res, sem::LinkTarget::CustomId const& object);
void visit(R& res, sem::LinkTarget::SubtreeTitle const& object);
void visit(R& res, sem::LinkTarget::Person const& object);
void visit(R& res, sem::LinkTarget::UserProtocol const& object);
void visit(R& res, sem::LinkTarget::Internal const& object);
void visit(R& res, sem::LinkTarget::Footnote const& object);
void visit(R& res, sem::LinkTarget::File const& object);
void visit(R& res, sem::LinkTarget::Attachment const& object);
void visit(R& res, sem::SubtreeLogHead::LogEntry const& object);
void visit(R& res, sem::SubtreeLogHead const& object);
void visit(R& res, sem::SubtreeLogHead::Priority const& object);
void visit(R& res, sem::SubtreeLogHead::Note const& object);
void visit(R& res, sem::SubtreeLogHead::Refile const& object);
void visit(R& res, sem::SubtreeLogHead::Clock const& object);
void visit(R& res, sem::SubtreeLogHead::State const& object);
void visit(R& res, sem::SubtreeLogHead::Deadline const& object);
void visit(R& res, sem::SubtreeLogHead::Schedule const& object);
void visit(R& res, sem::SubtreeLogHead::Tag const& object);
void visit(R& res, sem::SubtreeLogHead::Unknown const& object);
void visit(R& res, sem::SubtreeCompletion const& object);
void visit(R& res, sem::AttrList const& object);
void visit(R& res, sem::AttrGroup const& object);
void visit(R& res, sem::ColumnView const& object);
void visit(R& res, sem::ColumnView::Summary::Data const& object);
void visit(R& res, sem::ColumnView::Summary const& object);
void visit(R& res, sem::ColumnView::Summary::CheckboxAggregate const& object);
void visit(R& res, sem::ColumnView::Summary::MathAggregate const& object);
void visit(R& res, sem::ColumnView::Column const& object);
void visit(R& res, sem::BlockCodeLine const& object);
void visit(R& res, sem::BlockCodeLine::Part::Data const& object);
void visit(R& res, sem::BlockCodeLine::Part const& object);
void visit(R& res, sem::BlockCodeLine::Part::Raw const& object);
void visit(R& res, sem::BlockCodeLine::Part::Callout const& object);
void visit(R& res, sem::BlockCodeLine::Part::Tangle const& object);
void visit(R& res, sem::BlockCodeSwitch::Data const& object);
void visit(R& res, sem::BlockCodeSwitch const& object);
void visit(R& res, sem::BlockCodeSwitch::LineStart const& object);
void visit(R& res, sem::BlockCodeSwitch::CalloutFormat const& object);
void visit(R& res, sem::BlockCodeSwitch::RemoveCallout const& object);
void visit(R& res, sem::BlockCodeSwitch::EmphasizeLine const& object);
void visit(R& res, sem::BlockCodeSwitch::Dedent const& object);
void visit(R& res, sem::BlockCodeEvalResult::Data const& object);
void visit(R& res, sem::BlockCodeEvalResult const& object);
void visit(R& res, sem::BlockCodeEvalResult::None const& object);
void visit(R& res, sem::BlockCodeEvalResult::OrgValue const& object);
void visit(R& res, sem::BlockCodeEvalResult::File const& object);
void visit(R& res, sem::BlockCodeEvalResult::Raw const& object);
void visit(R& res, sem::DocumentExportConfig::TocExport const& object);
void visit(R& res, sem::DocumentExportConfig const& object);
void visit(R& res, sem::DocumentExportConfig::TaskExport const& object);
void visit(R& res, sem::DocumentExportConfig::DoExport const& object);
void visit(R& res, sem::DocumentExportConfig::ExportFixed const& object);
void visit(R& res, sem::SubtreePeriod const& object);
void visit(R& res, sem::NamedProperty::Data const& object);
void visit(R& res, sem::NamedProperty const& object);
void visit(R& res, sem::NamedProperty::Nonblocking const& object);
void visit(R& res, sem::NamedProperty::ArchiveTime const& object);
void visit(R& res, sem::NamedProperty::ArchiveFile const& object);
void visit(R& res, sem::NamedProperty::ArchiveOlpath const& object);
void visit(R& res, sem::NamedProperty::ArchiveTarget const& object);
void visit(R& res, sem::NamedProperty::ArchiveCategory const& object);
void visit(R& res, sem::NamedProperty::ArchiveTodo const& object);
void visit(R& res, sem::NamedProperty::Trigger const& object);
void visit(R& res, sem::NamedProperty::ExportLatexClass const& object);
void visit(R& res, sem::NamedProperty::CookieData const& object);
void visit(R& res, sem::NamedProperty::ExportLatexClassOptions const& object);
void visit(R& res, sem::NamedProperty::ExportLatexHeader const& object);
void visit(R& res, sem::NamedProperty::ExportLatexCompiler const& object);
void visit(R& res, sem::NamedProperty::Ordered const& object);
void visit(R& res, sem::NamedProperty::Effort const& object);
void visit(R& res, sem::NamedProperty::Visibility const& object);
void visit(R& res, sem::NamedProperty::ExportOptions const& object);
void visit(R& res, sem::NamedProperty::Blocker const& object);
void visit(R& res, sem::NamedProperty::Unnumbered const& object);
void visit(R& res, sem::NamedProperty::Created const& object);
void visit(R& res, sem::NamedProperty::RadioId const& object);
void visit(R& res, sem::NamedProperty::HashtagDef const& object);
void visit(R& res, sem::NamedProperty::CustomArgs const& object);
void visit(R& res, sem::NamedProperty::CustomRaw const& object);
void visitNone(R& res, In<sem::None> object);
void visitErrorItem(R& res, In<sem::ErrorItem> object);
void visitErrorGroup(R& res, In<sem::ErrorGroup> object);
void visitStmt(R& res, In<sem::Stmt> object);
void visitInline(R& res, In<sem::Inline> object);
void visitStmtList(R& res, In<sem::StmtList> object);
void visitEmpty(R& res, In<sem::Empty> object);
void visitCmd(R& res, In<sem::Cmd> object);
void visitBlock(R& res, In<sem::Block> object);
void visitLineCommand(R& res, In<sem::LineCommand> object);
void visitAttached(R& res, In<sem::Attached> object);
void visitLeaf(R& res, In<sem::Leaf> object);
void visitCmdCaption(R& res, In<sem::CmdCaption> object);
void visitCmdColumns(R& res, In<sem::CmdColumns> object);
void visitCmdName(R& res, In<sem::CmdName> object);
void visitCmdCustomArgs(R& res, In<sem::CmdCustomArgs> object);
void visitCmdCustomRaw(R& res, In<sem::CmdCustomRaw> object);
void visitCmdCustomText(R& res, In<sem::CmdCustomText> object);
void visitCmdResults(R& res, In<sem::CmdResults> object);
void visitCmdTblfm(R& res, In<sem::CmdTblfm> object);
void visitHashTag(R& res, In<sem::HashTag> object);
void visitInlineFootnote(R& res, In<sem::InlineFootnote> object);
void visitInlineExport(R& res, In<sem::InlineExport> object);
void visit(R& res, sem::Time::TimeVariant const& object);
void visitTime(R& res, In<sem::Time> object);
void visit(R& res, sem::Time::Repeat const& object);
void visit(R& res, sem::Time::Static const& object);
void visit(R& res, sem::Time::Dynamic const& object);
void visitTimeRange(R& res, In<sem::TimeRange> object);
void visitMacro(R& res, In<sem::Macro> object);
void visitSymbol(R& res, In<sem::Symbol> object);
void visit(R& res, sem::Symbol::Param const& object);
void visitEscaped(R& res, In<sem::Escaped> object);
void visitNewline(R& res, In<sem::Newline> object);
void visitSpace(R& res, In<sem::Space> object);
void visitWord(R& res, In<sem::Word> object);
void visitAtMention(R& res, In<sem::AtMention> object);
void visitRawText(R& res, In<sem::RawText> object);
void visitPunctuation(R& res, In<sem::Punctuation> object);
void visitPlaceholder(R& res, In<sem::Placeholder> object);
void visitBigIdent(R& res, In<sem::BigIdent> object);
void visitTextTarget(R& res, In<sem::TextTarget> object);
void visitMarkup(R& res, In<sem::Markup> object);
void visitBold(R& res, In<sem::Bold> object);
void visitUnderline(R& res, In<sem::Underline> object);
void visitMonospace(R& res, In<sem::Monospace> object);
void visitMarkQuote(R& res, In<sem::MarkQuote> object);
void visitVerbatim(R& res, In<sem::Verbatim> object);
void visitItalic(R& res, In<sem::Italic> object);
void visitStrike(R& res, In<sem::Strike> object);
void visitPar(R& res, In<sem::Par> object);
void visitRadioTarget(R& res, In<sem::RadioTarget> object);
void visitLatex(R& res, In<sem::Latex> object);
void visitLink(R& res, In<sem::Link> object);
void visitBlockCenter(R& res, In<sem::BlockCenter> object);
void visitBlockQuote(R& res, In<sem::BlockQuote> object);
void visitBlockComment(R& res, In<sem::BlockComment> object);
void visitBlockVerse(R& res, In<sem::BlockVerse> object);
void visitBlockDynamicFallback(R& res, In<sem::BlockDynamicFallback> object);
void visitBlockExample(R& res, In<sem::BlockExample> object);
void visitBlockExport(R& res, In<sem::BlockExport> object);
void visitBlockAdmonition(R& res, In<sem::BlockAdmonition> object);
void visitBlockCode(R& res, In<sem::BlockCode> object);
void visitSubtreeLog(R& res, In<sem::SubtreeLog> object);
void visitSubtree(R& res, In<sem::Subtree> object);
void visitCell(R& res, In<sem::Cell> object);
void visitRow(R& res, In<sem::Row> object);
void visitTable(R& res, In<sem::Table> object);
void visitParagraph(R& res, In<sem::Paragraph> object);
void visitColonExample(R& res, In<sem::ColonExample> object);
void visitCmdAttr(R& res, In<sem::CmdAttr> object);
void visitCmdExport(R& res, In<sem::CmdExport> object);
void visitCall(R& res, In<sem::Call> object);
void visitList(R& res, In<sem::List> object);
void visitListItem(R& res, In<sem::ListItem> object);
void visitDocumentOptions(R& res, In<sem::DocumentOptions> object);
void visitDocument(R& res, In<sem::Document> object);
void visitFileTarget(R& res, In<sem::FileTarget> object);
void visitTextSeparator(R& res, In<sem::TextSeparator> object);
void visitDocumentGroup(R& res, In<sem::DocumentGroup> object);
void visit(R& res, sem::File::Data const& object);
void visitFile(R& res, In<sem::File> object);
void visit(R& res, sem::File::Document const& object);
void visit(R& res, sem::File::Attachment const& object);
void visit(R& res, sem::File::Source const& object);
void visitDirectory(R& res, In<sem::Directory> object);
void visitSymlink(R& res, In<sem::Symlink> object);
void visit(R& res, sem::CmdInclude::Data const& object);
void visitCmdInclude(R& res, In<sem::CmdInclude> object);
void visit(R& res, sem::CmdInclude::Example const& object);
void visit(R& res, sem::CmdInclude::Export const& object);
void visit(R& res, sem::CmdInclude::Src const& object);
void visit(R& res, sem::CmdInclude::OrgDocument const& object);
/* clang-format on */