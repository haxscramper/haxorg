/* clang-format off */
template <typename V, typename R>
void Exporter<V, R>::visitCmdArgument(R& res, In<sem::CmdArgument> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, key);
  __org_field(res, object, varname);
  __org_field(res, object, value);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdArgumentList(R& res, In<sem::CmdArgumentList> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, args);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdArguments(R& res, In<sem::CmdArguments> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, positional);
  __org_field(res, object, named);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorItem(R& res, In<sem::ErrorItem> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, message);
  __org_field(res, object, function);
  __org_field(res, object, line);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorGroup(R& res, In<sem::ErrorGroup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, diagnostics);
  __org_field(res, object, function);
  __org_field(res, object, line);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStmt(R& res, In<sem::Stmt> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInline(R& res, In<sem::Inline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStmtList(R& res, In<sem::StmtList> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitEmpty(R& res, In<sem::Empty> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmd(R& res, In<sem::Cmd> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlock(R& res, In<sem::Block> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLineCommand(R& res, In<sem::LineCommand> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAttached(R& res, In<sem::Attached> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLeaf(R& res, In<sem::Leaf> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCaption(R& res, In<sem::CmdCaption> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdName(R& res, In<sem::CmdName> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomArgs(R& res, In<sem::CmdCustomArgs> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomRaw(R& res, In<sem::CmdCustomRaw> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, text);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomText(R& res, In<sem::CmdCustomText> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, text);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdResults(R& res, In<sem::CmdResults> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdTblfm(R& res, In<sem::CmdTblfm> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitHashTag(R& res, In<sem::HashTag> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, head);
  __org_field(res, object, subtags);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitFootnote(R& res, In<sem::Footnote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, tag);
  __org_field(res, object, definition);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::TimeVariant const& object) { visitVariants(res, sem::Time::getTimeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitTime(R& res, In<sem::Time> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, isActive);
  __org_field(res, object, time);
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
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, from);
  __org_field(res, object, to);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMacro(R& res, In<sem::Macro> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSymbol(R& res, In<sem::Symbol> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, positional);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Symbol::Param const& object) {
  __obj_field(res, object, key);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visitEscaped(R& res, In<sem::Escaped> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitNewline(R& res, In<sem::Newline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSpace(R& res, In<sem::Space> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitWord(R& res, In<sem::Word> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAtMention(R& res, In<sem::AtMention> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRawText(R& res, In<sem::RawText> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPunctuation(R& res, In<sem::Punctuation> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPlaceholder(R& res, In<sem::Placeholder> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBigIdent(R& res, In<sem::BigIdent> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRadioTarget(R& res, In<sem::RadioTarget> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTextTarget(R& res, In<sem::TextTarget> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkup(R& res, In<sem::Markup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBold(R& res, In<sem::Bold> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitUnderline(R& res, In<sem::Underline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMonospace(R& res, In<sem::Monospace> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkQuote(R& res, In<sem::MarkQuote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitVerbatim(R& res, In<sem::Verbatim> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitItalic(R& res, In<sem::Italic> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStrike(R& res, In<sem::Strike> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPar(R& res, In<sem::Par> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLatex(R& res, In<sem::Latex> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Data const& object) { visitVariants(res, sem::Link::getLinkKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitLink(R& res, In<sem::Link> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, description);
  __org_field(res, object, data);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Raw const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Id const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Person const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::UserProtocol const& object) {
  __obj_field(res, object, protocol);
  __obj_field(res, object, target);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Internal const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Footnote const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::File const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Link::Attachment const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visitBlockCenter(R& res, In<sem::BlockCenter> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockQuote(R& res, In<sem::BlockQuote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockComment(R& res, In<sem::BlockComment> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockVerse(R& res, In<sem::BlockVerse> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockExample(R& res, In<sem::BlockExample> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockExport(R& res, In<sem::BlockExport> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, format);
  __org_field(res, object, exporter);
  __org_field(res, object, placement);
  __org_field(res, object, content);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockAdmonition(R& res, In<sem::BlockAdmonition> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockCode(R& res, In<sem::BlockCode> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, lang);
  __org_field(res, object, switches);
  __org_field(res, object, exports);
  __org_field(res, object, result);
  __org_field(res, object, lines);
  __org_field(res, object, cache);
  __org_field(res, object, eval);
  __org_field(res, object, noweb);
  __org_field(res, object, hlines);
  __org_field(res, object, tangle);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line const& object) { __obj_field(res, object, parts); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line::Part::Data const& object) { visitVariants(res, sem::BlockCode::Line::Part::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line::Part const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line::Part::Raw const& object) { __obj_field(res, object, code); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line::Part::Callout const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Line::Part::Tangle const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::Data const& object) { visitVariants(res, sem::BlockCode::Switch::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::LineStart const& object) {
  __obj_field(res, object, start);
  __obj_field(res, object, extendLast);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::CalloutFormat const& object) { __obj_field(res, object, format); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::RemoveCallout const& object) { __obj_field(res, object, remove); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::EmphasizeLine const& object) { __obj_field(res, object, line); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::Switch::Dedent const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult::Data const& object) { visitVariants(res, sem::BlockCode::EvalResult::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult::None const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult::OrgValue const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult::File const& object) { __obj_field(res, object, path); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCode::EvalResult::Raw const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::LogEntry const& object) { visitVariants(res, sem::SubtreeLog::getLogKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitSubtreeLog(R& res, In<sem::SubtreeLog> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, log);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::DescribedLog const& object) { __obj_field(res, object, desc); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Priority const& object) {
  __obj_field(res, object, oldPriority);
  __obj_field(res, object, newPriority);
  __obj_field(res, object, on);
  __obj_field(res, object, action);
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
  __obj_field(res, object, from);
  __obj_field(res, object, to);
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
void Exporter<V, R>::visit(R& res, sem::SubtreeLog::Unknown const& object) { __obj_field(res, object, desc); }

template <typename V, typename R>
void Exporter<V, R>::visitSubtree(R& res, In<sem::Subtree> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
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
  __org_field(res, object, isComment);
  __org_field(res, object, isArchived);
  __org_field(res, object, priority);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Period const& object) {
  __obj_field(res, object, kind);
  __obj_field(res, object, from);
  __obj_field(res, object, to);
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
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::CustomArgs const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, sub);
  __obj_field(res, object, parameters);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Subtree::Property::CustomRaw const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visitSubtreeCompletion(R& res, In<sem::SubtreeCompletion> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, done);
  __org_field(res, object, full);
  __org_field(res, object, isPercent);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCell(R& res, In<sem::Cell> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, isBlock);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRow(R& res, In<sem::Row> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, cells);
  __org_field(res, object, isBlock);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTable(R& res, In<sem::Table> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, rows);
  __org_field(res, object, isBlock);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitParagraph(R& res, In<sem::Paragraph> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AnnotatedParagraph::Data const& object) { visitVariants(res, sem::AnnotatedParagraph::getAnnotationKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitAnnotatedParagraph(R& res, In<sem::AnnotatedParagraph> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, data);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AnnotatedParagraph::None const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AnnotatedParagraph::Footnote const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AnnotatedParagraph::Admonition const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AnnotatedParagraph::Timestamp const& object) { __obj_field(res, object, time); }

template <typename V, typename R>
void Exporter<V, R>::visitColonExample(R& res, In<sem::ColonExample> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdAttr(R& res, In<sem::CmdAttr> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, target);
  __org_field(res, object, parameters);
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCall(R& res, In<sem::Call> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, isCommand);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitList(R& res, In<sem::List> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitListItem(R& res, In<sem::ListItem> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, checkbox);
  __org_field(res, object, header);
  __org_field(res, object, bullet);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitDocumentOptions(R& res, In<sem::DocumentOptions> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, initialVisibility);
  __org_field(res, object, properties);
  __org_field(res, object, exportConfig);
  __org_field(res, object, fixedWidthSections);
  __org_field(res, object, startupIndented);
  __org_field(res, object, category);
  __org_field(res, object, setupfile);
  __org_field(res, object, maxSubtreeLevelExport);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportConfig::TocExport const& object) { visitVariants(res, sem::DocumentOptions::ExportConfig::getTocExportKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportConfig const& object) {
  __obj_field(res, object, inlinetasks);
  __obj_field(res, object, footnotes);
  __obj_field(res, object, clock);
  __obj_field(res, object, author);
  __obj_field(res, object, emphasis);
  __obj_field(res, object, specialStrings);
  __obj_field(res, object, propertyDrawers);
  __obj_field(res, object, statisticsCookies);
  __obj_field(res, object, todoText);
  __obj_field(res, object, brokenLinks);
  __obj_field(res, object, tocExport);
  __obj_field(res, object, tagExport);
  __obj_field(res, object, data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportConfig::TaskExport const& object) { __obj_field(res, object, taskWhitelist); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportConfig::DoExport const& object) { __obj_field(res, object, exportToc); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentOptions::ExportConfig::ExportFixed const& object) { __obj_field(res, object, exportLevels); }

template <typename V, typename R>
void Exporter<V, R>::visitDocument(R& res, In<sem::Document> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, title);
  __org_field(res, object, author);
  __org_field(res, object, creator);
  __org_field(res, object, filetags);
  __org_field(res, object, email);
  __org_field(res, object, language);
  __org_field(res, object, options);
  __org_field(res, object, exportFileName);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitFileTarget(R& res, In<sem::FileTarget> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, path);
  __org_field(res, object, line);
  __org_field(res, object, searchTarget);
  __org_field(res, object, restrictToHeadlines);
  __org_field(res, object, targetId);
  __org_field(res, object, regexp);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTextSeparator(R& res, In<sem::TextSeparator> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Data const& object) { visitVariants(res, sem::Include::getIncludeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitInclude(R& res, In<sem::Include> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, path);
  __org_field(res, object, firstLine);
  __org_field(res, object, lastLine);
  __org_field(res, object, data);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Example const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Export const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::Src const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Include::OrgDocument const& object) { __obj_field(res, object, minLevel); }

template <typename V, typename R>
void Exporter<V, R>::visitDocumentGroup(R& res, In<sem::DocumentGroup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, subnodes);
}

/* clang-format on */