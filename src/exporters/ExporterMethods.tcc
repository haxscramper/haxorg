/* clang-format off */
void visitStmt(R& res, In<sem::Stmt> object);
void visitInline(R& res, In<sem::Inline> object);
void visitStmtList(R& res, In<sem::StmtList> object);
void visitEmpty(R& res, In<sem::Empty> object);
void visitRow(R& res, In<sem::Row> object);
void visitTable(R& res, In<sem::Table> object);
void visitHashTag(R& res, In<sem::HashTag> object);
void visitFootnote(R& res, In<sem::Footnote> object);
void visitCompletion(R& res, In<sem::Completion> object);
void visitParagraph(R& res, In<sem::Paragraph> object);
void visitFormat(R& res, In<sem::Format> object);
void visitCenter(R& res, In<sem::Center> object);
void visitCommand(R& res, In<sem::Command> object);
void visitLineCommand(R& res, In<sem::LineCommand> object);
void visitStandalone(R& res, In<sem::Standalone> object);
void visitAttached(R& res, In<sem::Attached> object);
void visitCaption(R& res, In<sem::Caption> object);
void visitCmdFiletags(R& res, In<sem::CmdFiletags> object);
void visitCmdName(R& res, In<sem::CmdName> object);
void visitCmdResults(R& res, In<sem::CmdResults> object);
void visitCommandGroup(R& res, In<sem::CommandGroup> object);
void visitBlock(R& res, In<sem::Block> object);
void visitTblfm(R& res, In<sem::Tblfm> object);
void visitQuote(R& res, In<sem::Quote> object);
void visitVerse(R& res, In<sem::Verse> object);
void visitExample(R& res, In<sem::Example> object);
void visitCmdArguments(R& res, In<sem::CmdArguments> object);
void visitCmdArgument(R& res, In<sem::CmdArgument> object);
void visitExport(R& res, In<sem::Export> object);
void visitAdmonitionBlock(R& res, In<sem::AdmonitionBlock> object);
void visitCode(R& res, In<sem::Code> object);
void visit(R& res, sem::Code::Switch::Data const& object);
void visit(R& res, sem::Code::Switch const& object);
void visit(R& res, sem::Code::Switch::LineStart const& object);
void visit(R& res, sem::Code::Switch::CalloutFormat const& object);
void visit(R& res, sem::Code::Switch::RemoveCallout const& object);
void visit(R& res, sem::Code::Switch::EmphasizeLine const& object);
void visit(R& res, sem::Code::Switch::Dedent const& object);
void visit(R& res, sem::Time::TimeVariant const& object);
void visitTime(R& res, In<sem::Time> object);
void visit(R& res, sem::Time::Repeat const& object);
void visit(R& res, sem::Time::Static const& object);
void visit(R& res, sem::Time::Dynamic const& object);
void visitTimeRange(R& res, In<sem::TimeRange> object);
void visitMacro(R& res, In<sem::Macro> object);
void visitSymbol(R& res, In<sem::Symbol> object);
void visit(R& res, sem::Symbol::Param const& object);
void visit(R& res, sem::SubtreeLog::LogEntry const& object);
void visitSubtreeLog(R& res, In<sem::SubtreeLog> object);
void visit(R& res, sem::SubtreeLog::DescribedLog const& object);
void visit(R& res, sem::SubtreeLog::Priority const& object);
void visit(R& res, sem::SubtreeLog::Note const& object);
void visit(R& res, sem::SubtreeLog::Refile const& object);
void visit(R& res, sem::SubtreeLog::Clock const& object);
void visit(R& res, sem::SubtreeLog::State const& object);
void visit(R& res, sem::SubtreeLog::Tag const& object);
void visitSubtree(R& res, In<sem::Subtree> object);
void visit(R& res, sem::Subtree::Period const& object);
void visit(R& res, sem::Subtree::Property::Data const& object);
void visit(R& res, sem::Subtree::Property const& object);
void visit(R& res, sem::Subtree::Property::Nonblocking const& object);
void visit(R& res, sem::Subtree::Property::Trigger const& object);
void visit(R& res, sem::Subtree::Property::Origin const& object);
void visit(R& res, sem::Subtree::Property::ExportLatexClass const& object);
void visit(R& res, sem::Subtree::Property::ExportLatexClassOptions const& object);
void visit(R& res, sem::Subtree::Property::ExportLatexHeader const& object);
void visit(R& res, sem::Subtree::Property::ExportLatexCompiler const& object);
void visit(R& res, sem::Subtree::Property::Ordered const& object);
void visit(R& res, sem::Subtree::Property::Effort const& object);
void visit(R& res, sem::Subtree::Property::Visibility const& object);
void visit(R& res, sem::Subtree::Property::ExportOptions const& object);
void visit(R& res, sem::Subtree::Property::Blocker const& object);
void visit(R& res, sem::Subtree::Property::Unnumbered const& object);
void visit(R& res, sem::Subtree::Property::Created const& object);
void visit(R& res, sem::Subtree::Property::Unknown const& object);
void visitLatexBody(R& res, In<sem::LatexBody> object);
void visitInlineMath(R& res, In<sem::InlineMath> object);
void visitLeaf(R& res, In<sem::Leaf> object);
void visitEscaped(R& res, In<sem::Escaped> object);
void visitNewline(R& res, In<sem::Newline> object);
void visitSpace(R& res, In<sem::Space> object);
void visitWord(R& res, In<sem::Word> object);
void visitAtMention(R& res, In<sem::AtMention> object);
void visitRawText(R& res, In<sem::RawText> object);
void visitPunctuation(R& res, In<sem::Punctuation> object);
void visitPlaceholder(R& res, In<sem::Placeholder> object);
void visitBigIdent(R& res, In<sem::BigIdent> object);
void visitMarkup(R& res, In<sem::Markup> object);
void visitBold(R& res, In<sem::Bold> object);
void visitUnderline(R& res, In<sem::Underline> object);
void visitMonospace(R& res, In<sem::Monospace> object);
void visitMarkQuote(R& res, In<sem::MarkQuote> object);
void visitVerbatim(R& res, In<sem::Verbatim> object);
void visitItalic(R& res, In<sem::Italic> object);
void visitStrike(R& res, In<sem::Strike> object);
void visitPar(R& res, In<sem::Par> object);
void visitList(R& res, In<sem::List> object);
void visitListItem(R& res, In<sem::ListItem> object);
void visit(R& res, sem::Link::Data const& object);
void visitLink(R& res, In<sem::Link> object);
void visit(R& res, sem::Link::Raw const& object);
void visit(R& res, sem::Link::Id const& object);
void visit(R& res, sem::Link::Person const& object);
void visit(R& res, sem::Link::Footnote const& object);
void visit(R& res, sem::Link::File const& object);
void visit(R& res, sem::DocumentOptions::TocExport const& object);
void visitDocumentOptions(R& res, In<sem::DocumentOptions> object);
void visit(R& res, sem::DocumentOptions::DoExport const& object);
void visit(R& res, sem::DocumentOptions::ExportFixed const& object);
void visitDocument(R& res, In<sem::Document> object);
void visitParseError(R& res, In<sem::ParseError> object);
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