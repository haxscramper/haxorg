/* clang-format off */
void visit(R& res, sem::AttrValue const& object);
void visit(R& res, sem::SubtreePath const& object);
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
void visit(R& res, sem::NamedProperty::CustomArgs const& object);
void visit(R& res, sem::NamedProperty::CustomRaw const& object);
void visitNone(R& res, In<sem::None> object);
void visitAttr(R& res, In<sem::Attr> object);
void visitAttrList(R& res, In<sem::AttrList> object);
void visitAttrs(R& res, In<sem::Attrs> object);
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
void visitCmdName(R& res, In<sem::CmdName> object);
void visitCmdCustomArgs(R& res, In<sem::CmdCustomArgs> object);
void visitCmdCustomRaw(R& res, In<sem::CmdCustomRaw> object);
void visitCmdCustomText(R& res, In<sem::CmdCustomText> object);
void visitCmdResults(R& res, In<sem::CmdResults> object);
void visitCmdTblfm(R& res, In<sem::CmdTblfm> object);
void visitHashTag(R& res, In<sem::HashTag> object);
void visitInlineFootnote(R& res, In<sem::InlineFootnote> object);
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
void visitRadioTarget(R& res, In<sem::RadioTarget> object);
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
void visitLatex(R& res, In<sem::Latex> object);
void visit(R& res, sem::Link::Data const& object);
void visitLink(R& res, In<sem::Link> object);
void visit(R& res, sem::Link::Raw const& object);
void visit(R& res, sem::Link::Id const& object);
void visit(R& res, sem::Link::Person const& object);
void visit(R& res, sem::Link::UserProtocol const& object);
void visit(R& res, sem::Link::Internal const& object);
void visit(R& res, sem::Link::Footnote const& object);
void visit(R& res, sem::Link::File const& object);
void visit(R& res, sem::Link::Attachment const& object);
void visitBlockCenter(R& res, In<sem::BlockCenter> object);
void visitBlockQuote(R& res, In<sem::BlockQuote> object);
void visitBlockComment(R& res, In<sem::BlockComment> object);
void visitBlockVerse(R& res, In<sem::BlockVerse> object);
void visitBlockDynamicFallback(R& res, In<sem::BlockDynamicFallback> object);
void visitBlockExample(R& res, In<sem::BlockExample> object);
void visitBlockExport(R& res, In<sem::BlockExport> object);
void visitBlockAdmonition(R& res, In<sem::BlockAdmonition> object);
void visitBlockCode(R& res, In<sem::BlockCode> object);
void visit(R& res, sem::SubtreeLog::LogEntry const& object);
void visitSubtreeLog(R& res, In<sem::SubtreeLog> object);
void visit(R& res, sem::SubtreeLog::DescribedLog const& object);
void visit(R& res, sem::SubtreeLog::Priority const& object);
void visit(R& res, sem::SubtreeLog::Note const& object);
void visit(R& res, sem::SubtreeLog::Refile const& object);
void visit(R& res, sem::SubtreeLog::Clock const& object);
void visit(R& res, sem::SubtreeLog::State const& object);
void visit(R& res, sem::SubtreeLog::Tag const& object);
void visit(R& res, sem::SubtreeLog::Unknown const& object);
void visitSubtree(R& res, In<sem::Subtree> object);
void visitSubtreeCompletion(R& res, In<sem::SubtreeCompletion> object);
void visitCell(R& res, In<sem::Cell> object);
void visitRow(R& res, In<sem::Row> object);
void visitTable(R& res, In<sem::Table> object);
void visitParagraph(R& res, In<sem::Paragraph> object);
void visitColonExample(R& res, In<sem::ColonExample> object);
void visitCmdAttr(R& res, In<sem::CmdAttr> object);
void visitCall(R& res, In<sem::Call> object);
void visitList(R& res, In<sem::List> object);
void visitListItem(R& res, In<sem::ListItem> object);
void visitDocumentOptions(R& res, In<sem::DocumentOptions> object);
void visitDocument(R& res, In<sem::Document> object);
void visitFileTarget(R& res, In<sem::FileTarget> object);
void visitTextSeparator(R& res, In<sem::TextSeparator> object);
void visit(R& res, sem::Include::Data const& object);
void visitInclude(R& res, In<sem::Include> object);
void visit(R& res, sem::Include::Example const& object);
void visit(R& res, sem::Include::Export const& object);
void visit(R& res, sem::Include::Src const& object);
void visit(R& res, sem::Include::OrgDocument const& object);
void visitDocumentGroup(R& res, In<sem::DocumentGroup> object);
/* clang-format on */