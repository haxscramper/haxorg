/* clang-format off */
template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SourceLocation const& object) {
  __obj_field(res, object, line);
  __obj_field(res, object, column);
  __obj_field(res, object, pos);
  __obj_field(res, object, file);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::LispCode::Data const& object) { visitVariants(res, sem::LispCode::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Call const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, args);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::List const& object) { __obj_field(res, object, items); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::KeyValue const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Number const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Text const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Ident const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Boolean const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LispCode::Real const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm const& object) { __obj_field(res, object, exprs); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::Tblfm::Expr::Data const& object) { visitVariants(res, sem::Tblfm::Expr::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::AxisRef const& object) {
  __obj_field(res, object, col);
  __obj_field(res, object, row);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::Tblfm::Expr::AxisRef::Position::Data const& object) { visitVariants(res, sem::Tblfm::Expr::AxisRef::Position::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::AxisRef::Position const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::AxisRef::Position::Index const& object) { __obj_field(res, object, index); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::AxisRef::Position::Name const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::AxisName const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::IntLiteral const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::FloatLiteral const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::RangeRef const& object) {
  __obj_field(res, object, first);
  __obj_field(res, object, last);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::Call const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, args);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Expr::Elisp const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Tblfm::Assign const& object) {
  __obj_field(res, object, target);
  __obj_field(res, object, expr);
  __obj_field(res, object, flags);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::AttrValue::DataVariant const& object) { visitVariants(res, sem::AttrValue::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrValue const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, varname);
  __obj_field(res, object, span);
  __obj_field(res, object, isQuoted);
  __obj_field(res, object, data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrValue::DimensionSpan const& object) {
  __obj_field(res, object, first);
  __obj_field(res, object, last);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrValue::TextValue const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrValue::FileReference const& object) {
  __obj_field(res, object, file);
  __obj_field(res, object, reference);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrValue::LispValue const& object) { __obj_field(res, object, code); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::HashTagFlat const& object) { __obj_field(res, object, tags); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::TodoKeyword const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, shortcut);
  __obj_field(res, object, onEnter);
  __obj_field(res, object, onLeave);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::HashTagText const& object) {
  __obj_field(res, object, head);
  __obj_field(res, object, subtags);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreePath const& object) { __obj_field(res, object, path); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::LinkTarget::Data const& object) { visitVariants(res, sem::LinkTarget::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Raw const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Id const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::CustomId const& object) { __obj_field(res, object, text); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::SubtreeTitle const& object) {
  __obj_field(res, object, title);
  __obj_field(res, object, level);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Person const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::UserProtocol const& object) {
  __obj_field(res, object, protocol);
  __obj_field(res, object, target);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Internal const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Footnote const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::File const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::LinkTarget::Attachment const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::SubtreeLogHead::LogEntry const& object) { visitVariants(res, sem::SubtreeLogHead::getLogKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead const& object) { __obj_field(res, object, log); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Priority const& object) {
  __obj_field(res, object, oldPriority);
  __obj_field(res, object, newPriority);
  __obj_field(res, object, on);
  __obj_field(res, object, action);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Note const& object) { __obj_field(res, object, on); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Refile const& object) {
  __obj_field(res, object, on);
  __obj_field(res, object, from);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Clock const& object) {
  __obj_field(res, object, from);
  __obj_field(res, object, to);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::State const& object) {
  __obj_field(res, object, from);
  __obj_field(res, object, to);
  __obj_field(res, object, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Deadline const& object) {
  __obj_field(res, object, from);
  __obj_field(res, object, to);
  __obj_field(res, object, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Schedule const& object) {
  __obj_field(res, object, from);
  __obj_field(res, object, to);
  __obj_field(res, object, on);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Tag const& object) {
  __obj_field(res, object, on);
  __obj_field(res, object, tag);
  __obj_field(res, object, added);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeLogHead::Unknown const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreeCompletion const& object) {
  __obj_field(res, object, done);
  __obj_field(res, object, full);
  __obj_field(res, object, isPercent);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrList const& object) { __obj_field(res, object, items); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::AttrGroup const& object) {
  __obj_field(res, object, positional);
  __obj_field(res, object, named);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgCodeEvalInput const& object) {
  __obj_field(res, object, blockAttrs);
  __obj_field(res, object, tangledCode);
  __obj_field(res, object, exportType);
  __obj_field(res, object, resultType);
  __obj_field(res, object, resultFormat);
  __obj_field(res, object, resultHandling);
  __obj_field(res, object, language);
  __obj_field(res, object, argList);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgCodeEvalInput::Var const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgCodeEvalOutput const& object) {
  __obj_field(res, object, stdoutText);
  __obj_field(res, object, stderrText);
  __obj_field(res, object, code);
  __obj_field(res, object, cmd);
  __obj_field(res, object, args);
  __obj_field(res, object, cwd);
  __obj_field(res, object, appliedHeaderArg);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::ColumnView const& object) { __obj_field(res, object, columns); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::ColumnView::Summary::Data const& object) { visitVariants(res, sem::ColumnView::Summary::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::ColumnView::Summary const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::ColumnView::Summary::CheckboxAggregate const& object) { __obj_field(res, object, kind); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::ColumnView::Summary::MathAggregate const& object) {
  __obj_field(res, object, kind);
  __obj_field(res, object, formatDigits);
  __obj_field(res, object, formatPrecision);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::ColumnView::Column const& object) {
  __obj_field(res, object, summary);
  __obj_field(res, object, width);
  __obj_field(res, object, property);
  __obj_field(res, object, propertyTitle);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCodeLine const& object) { __obj_field(res, object, parts); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::BlockCodeLine::Part::Data const& object) { visitVariants(res, sem::BlockCodeLine::Part::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCodeLine::Part const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCodeLine::Part::Raw const& object) { __obj_field(res, object, code); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCodeLine::Part::Callout const& object) { __obj_field(res, object, name); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::BlockCodeLine::Part::Tangle const& object) { __obj_field(res, object, target); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::DocumentExportConfig::TocExport const& object) { visitVariants(res, sem::DocumentExportConfig::getTocExportKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentExportConfig const& object) {
  __obj_field(res, object, inlinetasks);
  __obj_field(res, object, footnotes);
  __obj_field(res, object, clock);
  __obj_field(res, object, author);
  __obj_field(res, object, emphasis);
  __obj_field(res, object, specialStrings);
  __obj_field(res, object, propertyDrawers);
  __obj_field(res, object, statisticsCookies);
  __obj_field(res, object, todoText);
  __obj_field(res, object, smartQuotes);
  __obj_field(res, object, fixedWidth);
  __obj_field(res, object, timestamps);
  __obj_field(res, object, preserveBreaks);
  __obj_field(res, object, subSuperscripts);
  __obj_field(res, object, expandLinks);
  __obj_field(res, object, creator);
  __obj_field(res, object, drawers);
  __obj_field(res, object, date);
  __obj_field(res, object, entities);
  __obj_field(res, object, email);
  __obj_field(res, object, sectionNumbers);
  __obj_field(res, object, planning);
  __obj_field(res, object, priority);
  __obj_field(res, object, latex);
  __obj_field(res, object, timestamp);
  __obj_field(res, object, title);
  __obj_field(res, object, tables);
  __obj_field(res, object, headlineLevels);
  __obj_field(res, object, brokenLinks);
  __obj_field(res, object, tocExport);
  __obj_field(res, object, tagExport);
  __obj_field(res, object, taskFiltering);
  __obj_field(res, object, archivedTrees);
  __obj_field(res, object, data);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentExportConfig::TaskExport const& object) { __obj_field(res, object, taskWhitelist); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentExportConfig::DoExport const& object) { __obj_field(res, object, exportToc); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::DocumentExportConfig::ExportFixed const& object) { __obj_field(res, object, exportLevels); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::SubtreePeriod const& object) {
  __obj_field(res, object, kind);
  __obj_field(res, object, from);
  __obj_field(res, object, to);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::NamedProperty::Data const& object) { visitVariants(res, sem::NamedProperty::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Nonblocking const& object) { __obj_field(res, object, isBlocking); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveTime const& object) { __obj_field(res, object, time); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveFile const& object) { __obj_field(res, object, file); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveOlpath const& object) { __obj_field(res, object, path); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveTarget const& object) {
  __obj_field(res, object, path);
  __obj_field(res, object, pattern);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveCategory const& object) { __obj_field(res, object, category); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ArchiveTodo const& object) { __obj_field(res, object, todo); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Trigger const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ExportLatexClass const& object) { __obj_field(res, object, latexClass); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CookieData const& object) {
  __obj_field(res, object, isRecursive);
  __obj_field(res, object, source);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ExportLatexClassOptions const& object) { __obj_field(res, object, options); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ExportLatexHeader const& object) { __obj_field(res, object, header); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ExportLatexCompiler const& object) { __obj_field(res, object, compiler); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Ordered const& object) { __obj_field(res, object, isOrdered); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Effort const& object) {
  __obj_field(res, object, hours);
  __obj_field(res, object, minutes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Visibility const& object) { __obj_field(res, object, level); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::ExportOptions const& object) {
  __obj_field(res, object, backend);
  __obj_field(res, object, values);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Blocker const& object) { __obj_field(res, object, blockers); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Unnumbered const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::Created const& object) { __obj_field(res, object, time); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::RadioId const& object) { __obj_field(res, object, words); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::HashtagDef const& object) { __obj_field(res, object, hashtag); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CustomArgs const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, sub);
  __obj_field(res, object, attrs);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CustomRaw const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CustomId const& object) { __obj_field(res, object, value); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CustomSubtreeJson const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::NamedProperty::CustomSubtreeFlags const& object) {
  __obj_field(res, object, name);
  __obj_field(res, object, value);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::OrgDiagnostics::Data const& object) { visitVariants(res, sem::OrgDiagnostics::getKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics const& object) { __obj_field(res, object, data); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics::ParseTokenError const& object) {
  __obj_field(res, object, brief);
  __obj_field(res, object, detail);
  __obj_field(res, object, parserFunction);
  __obj_field(res, object, parserLine);
  __obj_field(res, object, tokenKind);
  __obj_field(res, object, tokenText);
  __obj_field(res, object, loc);
  __obj_field(res, object, errName);
  __obj_field(res, object, errCode);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics::ParseError const& object) {
  __obj_field(res, object, brief);
  __obj_field(res, object, detail);
  __obj_field(res, object, parserFunction);
  __obj_field(res, object, parserLine);
  __obj_field(res, object, errName);
  __obj_field(res, object, errCode);
  __obj_field(res, object, loc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics::IncludeError const& object) {
  __obj_field(res, object, brief);
  __obj_field(res, object, targetPath);
  __obj_field(res, object, workingFile);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics::ConvertError const& object) {
  __obj_field(res, object, brief);
  __obj_field(res, object, detail);
  __obj_field(res, object, convertFunction);
  __obj_field(res, object, convertLine);
  __obj_field(res, object, convertFile);
  __obj_field(res, object, errName);
  __obj_field(res, object, errCode);
  __obj_field(res, object, loc);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::OrgDiagnostics::InternalError const& object) {
  __obj_field(res, object, message);
  __obj_field(res, object, function);
  __obj_field(res, object, line);
  __obj_field(res, object, file);
  __obj_field(res, object, loc);
}

template <typename V, typename R>
void Exporter<V, R>::visitNone(R& res, In<sem::None> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorItem(R& res, In<sem::ErrorItem> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, diag);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorGroup(R& res, In<sem::ErrorGroup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, diagnostics);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStmt(R& res, In<sem::Stmt> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInline(R& res, In<sem::Inline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStmtList(R& res, In<sem::StmtList> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitEmpty(R& res, In<sem::Empty> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmd(R& res, In<sem::Cmd> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlock(R& res, In<sem::Block> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLineCommand(R& res, In<sem::LineCommand> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAttached(R& res, In<sem::Attached> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLeaf(R& res, In<sem::Leaf> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCaption(R& res, In<sem::CmdCaption> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdColumns(R& res, In<sem::CmdColumns> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, view);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdName(R& res, In<sem::CmdName> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomArgs(R& res, In<sem::CmdCustomArgs> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomRaw(R& res, In<sem::CmdCustomRaw> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, text);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCustomText(R& res, In<sem::CmdCustomText> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, isAttached);
  __org_field(res, object, text);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdCall(R& res, In<sem::CmdCall> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, fileName);
  __org_field(res, object, insideHeaderAttrs);
  __org_field(res, object, callAttrs);
  __org_field(res, object, endHeaderAttrs);
  __org_field(res, object, result);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdTblfm(R& res, In<sem::CmdTblfm> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, expr);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitHashTag(R& res, In<sem::HashTag> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInlineFootnote(R& res, In<sem::InlineFootnote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, tag);
  __org_field(res, object, definition);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitInlineExport(R& res, In<sem::InlineExport> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, exporter);
  __org_field(res, object, content);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::Time::TimeVariant const& object) { visitVariants(res, sem::Time::getTimeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitTime(R& res, In<sem::Time> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, isActive);
  __org_field(res, object, time);
  __org_field(res, object, loc);
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
  __obj_field(res, object, warn);
  __obj_field(res, object, time);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::Time::Dynamic const& object) { __obj_field(res, object, expr); }

template <typename V, typename R>
void Exporter<V, R>::visitTimeRange(R& res, In<sem::TimeRange> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, from);
  __org_field(res, object, to);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMacro(R& res, In<sem::Macro> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, attrs);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSymbol(R& res, In<sem::Symbol> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, parameters);
  __org_field(res, object, positional);
  __org_field(res, object, loc);
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
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitNewline(R& res, In<sem::Newline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSpace(R& res, In<sem::Space> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitWord(R& res, In<sem::Word> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitAtMention(R& res, In<sem::AtMention> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRawText(R& res, In<sem::RawText> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPunctuation(R& res, In<sem::Punctuation> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPlaceholder(R& res, In<sem::Placeholder> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBigIdent(R& res, In<sem::BigIdent> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTextTarget(R& res, In<sem::TextTarget> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorSkipToken(R& res, In<sem::ErrorSkipToken> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, text);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitErrorSkipGroup(R& res, In<sem::ErrorSkipGroup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, skipped);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkup(R& res, In<sem::Markup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBold(R& res, In<sem::Bold> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitUnderline(R& res, In<sem::Underline> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMonospace(R& res, In<sem::Monospace> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitMarkQuote(R& res, In<sem::MarkQuote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitVerbatim(R& res, In<sem::Verbatim> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitItalic(R& res, In<sem::Italic> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitStrike(R& res, In<sem::Strike> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitPar(R& res, In<sem::Par> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRadioTarget(R& res, In<sem::RadioTarget> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, words);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLatex(R& res, In<sem::Latex> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitLink(R& res, In<sem::Link> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, description);
  __org_field(res, object, target);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockCenter(R& res, In<sem::BlockCenter> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockQuote(R& res, In<sem::BlockQuote> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockComment(R& res, In<sem::BlockComment> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockVerse(R& res, In<sem::BlockVerse> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockDynamicFallback(R& res, In<sem::BlockDynamicFallback> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockExample(R& res, In<sem::BlockExample> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockExport(R& res, In<sem::BlockExport> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, exporter);
  __org_field(res, object, content);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockAdmonition(R& res, In<sem::BlockAdmonition> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockCodeEvalResult(R& res, In<sem::BlockCodeEvalResult> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, raw);
  __org_field(res, object, node);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitBlockCode(R& res, In<sem::BlockCode> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, lang);
  __org_field(res, object, result);
  __org_field(res, object, lines);
  __org_field(res, object, switches);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSubtreeLog(R& res, In<sem::SubtreeLog> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, head);
  __org_field(res, object, desc);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

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
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCell(R& res, In<sem::Cell> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, isBlock);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitRow(R& res, In<sem::Row> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, cells);
  __org_field(res, object, isBlock);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTable(R& res, In<sem::Table> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, rows);
  __org_field(res, object, isBlock);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitParagraph(R& res, In<sem::Paragraph> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitColonExample(R& res, In<sem::ColonExample> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdAttr(R& res, In<sem::CmdAttr> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, target);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCmdExport(R& res, In<sem::CmdExport> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, exporter);
  __org_field(res, object, content);
  __org_field(res, object, attrs);
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCall(R& res, In<sem::Call> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, name);
  __org_field(res, object, attrs);
  __org_field(res, object, isCommand);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitList(R& res, In<sem::List> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, attached);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitListItem(R& res, In<sem::ListItem> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, checkbox);
  __org_field(res, object, header);
  __org_field(res, object, bullet);
  __org_field(res, object, loc);
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
  __org_field(res, object, columns);
  __org_field(res, object, todoKeywords);
  __org_field(res, object, doneKeywords);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitDocumentFragment(R& res, In<sem::DocumentFragment> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, baseLine);
  __org_field(res, object, baseCol);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitCriticMarkup(R& res, In<sem::CriticMarkup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, kind);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

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
  __org_field(res, object, loc);
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
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitTextSeparator(R& res, In<sem::TextSeparator> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitDocumentGroup(R& res, In<sem::DocumentGroup> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::File::Data const& object) { visitVariants(res, sem::File::getFileKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitFile(R& res, In<sem::File> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, relPath);
  __org_field(res, object, absPath);
  __org_field(res, object, data);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::File::Document const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::File::Attachment const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::File::Source const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visitDirectory(R& res, In<sem::Directory> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, relPath);
  __org_field(res, object, absPath);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visitSymlink(R& res, In<sem::Symlink> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, isDirectory);
  __org_field(res, object, absPath);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, org::sem::CmdInclude::Data const& object) { visitVariants(res, sem::CmdInclude::getIncludeKind(object), object); }

template <typename V, typename R>
void Exporter<V, R>::visitCmdInclude(R& res, In<sem::CmdInclude> object) {
  auto __scope = trace_scope(trace(VisitReport::Kind::VisitSpecificKind).with_node(object.asOrg()));
  __org_field(res, object, path);
  __org_field(res, object, firstLine);
  __org_field(res, object, lastLine);
  __org_field(res, object, data);
  __org_field(res, object, loc);
  __org_field(res, object, subnodes);
}

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::IncludeBase const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::Example const& object) {  }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::Export const& object) { __obj_field(res, object, language); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::Custom const& object) { __obj_field(res, object, blockName); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::Src const& object) { __obj_field(res, object, language); }

template <typename V, typename R>
void Exporter<V, R>::visit(R& res, sem::CmdInclude::OrgDocument const& object) {
  __obj_field(res, object, onlyContent);
  __obj_field(res, object, subtreePath);
  __obj_field(res, object, minLevel);
  __obj_field(res, object, customIdTarget);
}

/* clang-format on */