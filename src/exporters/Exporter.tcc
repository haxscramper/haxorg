/* clang-format off */
template <typename V, typename R>
void Exporter<V, R>::visitStmt(R& res, In<sem::Stmt> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, attached);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInline(R& res, In<sem::Inline> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStmtList(R& res, In<sem::StmtList> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitEmpty(R& res, In<sem::Empty> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRow(R& res, In<sem::Row> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTable(R& res, In<sem::Table> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, rows);
  __org_field(res, object, attached);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitHashTag(R& res, In<sem::HashTag> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, head);
  __org_field(res, object, subtags);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitFootnote(R& res, In<sem::Footnote> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, tag);
  __org_field(res, object, definition);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCompletion(R& res, In<sem::Completion> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, done);
  __org_field(res, object, full);
  __org_field(res, object, isPercent);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitParagraph(R& res, In<sem::Paragraph> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, attached);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitFormat(R& res, In<sem::Format> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCenter(R& res, In<sem::Center> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCommand(R& res, In<sem::Command> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLineCommand(R& res, In<sem::LineCommand> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStandalone(R& res, In<sem::Standalone> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAttached(R& res, In<sem::Attached> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCaption(R& res, In<sem::Caption> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCommandGroup(R& res, In<sem::CommandGroup> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, attached);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlock(R& res, In<sem::Block> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitQuote(R& res, In<sem::Quote> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitExample(R& res, In<sem::Example> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdArguments(R& res, In<sem::CmdArguments> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, positional);
  __org_field(res, object, named);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdArgument(R& res, In<sem::CmdArgument> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, key);
  __org_field(res, object, value);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitExport(R& res, In<sem::Export> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, format);
  __org_field(res, object, exporter);
  __org_field(res, object, parameters);
  __org_field(res, object, placement);
  __org_field(res, object, content);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAdmonitionBlock(R& res, In<sem::AdmonitionBlock> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCode(R& res, In<sem::Code> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, lang);
  __org_field(res, object, switches);
  __org_field(res, object, exports);
  __org_field(res, object, parameters);
  __org_field(res, object, cache);
  __org_field(res, object, eval);
  __org_field(res, object, noweb);
  __org_field(res, object, hlines);
  __org_field(res, object, tangle);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::Data const& object) { visitVariants(res, sem::Code::Switch::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::LineStart const& object) {
  __obj_field(res, object, start);
  __obj_field(res, object, extendLast);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::CalloutFormat const& object) { __obj_field(res, object, format); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::RemoveCallout const& object) { __obj_field(res, object, remove); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::EmphasizeLine const& object) { __obj_field(res, object, line); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Code::Switch::Dedent const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::TimeVariant const& object) { visitVariants(res, sem::Time::getTimeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitTime(R& res, In<sem::Time> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, isActive);
  __org_field(res, object, time);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::Repeat const& object) {
  __obj_field(res, object, mode);
  __obj_field(res, object, period);
  __obj_field(res, object, count);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::Static const& object) {
  __obj_field(res, object, repeat);
  __obj_field(res, object, time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::Dynamic const& object) { __obj_field(res, object, expr); }

template <typename V, typename R>
void Exporter<V, R>::visitTimeRange(R& res, In<sem::TimeRange> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, from);
  __org_field(res, object, to);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMacro(R& res, In<sem::Macro> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, name);
  __org_field(res, object, arguments);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSymbol(R& res, In<sem::Symbol> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, positional);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Symbol::Param const& object) {
  __obj_field(res, object, key);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::LogEntry const& object) { visitVariants(res, sem::SubtreeLog::getLogKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitSubtreeLog(R& res, In<sem::SubtreeLog> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, log);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::DescribedLog const& object) { __obj_field(res, object, desc); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Priority const& object) {
  __obj_field(res, object, oldPriority);
  __obj_field(res, object, newPriority);
  __obj_field(res, object, on);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Note const& object) {
  __obj_field(res, object, on);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Refile const& object) {
  __obj_field(res, object, on);
  __obj_field(res, object, from);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Clock const& object) {
  __obj_field(res, object, range);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::State const& object) {
  __obj_field(res, object, from);
  __obj_field(res, object, to);
  __obj_field(res, object, on);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Tag const& object) {
  __obj_field(res, object, on);
  __obj_field(res, object, tag);
  __obj_field(res, object, added);
  __obj_field(res, object, desc);
}

template <typename V, typename R>
void Exporter<V, R>::visitSubtree(R& res, In<sem::Subtree> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, level);
  __org_field(res, object, treeId);
  __org_field(res, object, todo);
  __org_field(res, object, completion);
  __org_field(res, object, description);
  __org_field(res, object, tags);
  __org_field(res, object, title);
  __org_field(res, object, logbook);
  __org_field(res, object, properties);
  __org_field(res, object, closed);
  __org_field(res, object, deadline);
  __org_field(res, object, scheduled);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Period const& object) {
  __obj_field(res, object, kind);
  __obj_field(res, object, period);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Data const& object) { visitVariants(res, sem::Subtree::Property::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property const& object) {
  __obj_field(res, object, mainSetRule);
  __obj_field(res, object, subSetRule);
  __obj_field(res, object, inheritanceMode);
  __obj_field(res, object, data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Nonblocking const& object) { __obj_field(res, object, isBlocking); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Trigger const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Origin const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::ExportLatexClass const& object) { __obj_field(res, object, latexClass); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::ExportLatexClassOptions const& object) { __obj_field(res, object, options); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::ExportLatexHeader const& object) { __obj_field(res, object, header); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::ExportLatexCompiler const& object) { __obj_field(res, object, compiler); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Ordered const& object) { __obj_field(res, object, isOrdered); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Effort const& object) {
  __obj_field(res, object, hours);
  __obj_field(res, object, minutes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Visibility const& object) { __obj_field(res, object, level); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::ExportOptions const& object) {
  __obj_field(res, object, backend);
  __obj_field(res, object, values);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Blocker const& object) { __obj_field(res, object, blockers); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Unnumbered const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::Created const& object) { __obj_field(res, object, time); }

template <typename V, typename R>
void Exporter<V, R>::visitLatexBody(R& res, In<sem::LatexBody> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInlineMath(R& res, In<sem::InlineMath> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLeaf(R& res, In<sem::Leaf> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitEscaped(R& res, In<sem::Escaped> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitNewline(R& res, In<sem::Newline> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSpace(R& res, In<sem::Space> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitWord(R& res, In<sem::Word> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAtMention(R& res, In<sem::AtMention> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRawText(R& res, In<sem::RawText> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPunctuation(R& res, In<sem::Punctuation> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPlaceholder(R& res, In<sem::Placeholder> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBigIdent(R& res, In<sem::BigIdent> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, text);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkup(R& res, In<sem::Markup> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBold(R& res, In<sem::Bold> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitUnderline(R& res, In<sem::Underline> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMonospace(R& res, In<sem::Monospace> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkQuote(R& res, In<sem::MarkQuote> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitVerbatim(R& res, In<sem::Verbatim> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitItalic(R& res, In<sem::Italic> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStrike(R& res, In<sem::Strike> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPar(R& res, In<sem::Par> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitList(R& res, In<sem::List> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitListItem(R& res, In<sem::ListItem> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, checkbox);
  __org_field(res, object, header);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Data const& object) { visitVariants(res, sem::Link::getLinkKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitLink(R& res, In<sem::Link> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, description);
  __org_field(res, object, data);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Raw const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Id const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Person const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Footnote const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::File const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visitDocument(R& res, In<sem::Document> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, idTable);
  __org_field(res, object, nameTable);
  __org_field(res, object, footnoteTable);
  __org_field(res, object, anchorTable);
  __org_field(res, object, title);
  __org_field(res, object, author);
  __org_field(res, object, creator);
  __org_field(res, object, email);
  __org_field(res, object, language);
  __org_field(res, object, options);
  __org_field(res, object, exportFileName);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitParseError(R& res, In<sem::ParseError> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitFileTarget(R& res, In<sem::FileTarget> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, path);
  __org_field(res, object, line);
  __org_field(res, object, searchTarget);
  __org_field(res, object, restrictToHeadlines);
  __org_field(res, object, targetId);
  __org_field(res, object, regexp);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTextSeparator(R& res, In<sem::TextSeparator> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Data const& object) { visitVariants(res, sem::Include::getIncludeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitInclude(R& res, In<sem::Include> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, data);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Example const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Export const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Src const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::OrgDocument const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::TocExport const& object) { visitVariants(res, sem::DocumentOptions::getTocExportKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitDocumentOptions(R& res, In<sem::DocumentOptions> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, brokenLinks);
  __org_field(res, object, initialVisibility);
  __org_field(res, object, tocExport);
  __org_field(res, object, properties);
  __org_field(res, object, smartQuotes);
  __org_field(res, object, emphasizedText);
  __org_field(res, object, specialStrings);
  __org_field(res, object, fixedWidthSections);
  __org_field(res, object, includeTimestamps);
  __org_field(res, object, preserveLineBreaks);
  __org_field(res, object, plaintextSubscripts);
  __org_field(res, object, exportArchived);
  __org_field(res, object, exportWithAuthor);
  __org_field(res, object, exportBrokenLinks);
  __org_field(res, object, exportWithClock);
  __org_field(res, object, exportWithCreator);
  __org_field(res, object, data);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::DoExport const& object) { __obj_field(res, object, exportToc); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportFixed const& object) { __obj_field(res, object, exportLevels); }

template <typename V, typename R>
void Exporter<V, R>::visitDocumentGroup(R& res, In<sem::DocumentGroup> object) {
  __visit_specific_kind(res, object);
  __org_field(res, object, loc);
  __org_field(res, object, placementContext);
  __org_field(res, object, subnodes);
}

/* clang-format on */