/* clang-format off */
#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgAdapterGenerated.hpp>
void org::imm::ImmAdapterT<org::imm::ImmNoNode>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmNoNode>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "NoNode", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmErrorItem>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmErrorItem>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorItem", other.getKind())
}
org::sem::OrgDiagnostics org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag() const {
  return this->value().diag;
}
void org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorGroup", other.getKind())
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>> org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics() const {
  return this->value().diagnostics;
}
void org::imm::ImmAdapterT<org::imm::ImmStmt>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmStmt>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Stmt", other.getKind())
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached() const {
  return this->value().attached;
}
void org::imm::ImmAdapterT<org::imm::ImmInline>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmInline>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Inline", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmStmtList>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmStmtList>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "StmtList", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmEmpty>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmEmpty>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Empty", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmCmd>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmd>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Cmd", other.getKind())
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs() const {
  return this->value().attrs;
}
void org::imm::ImmAdapterT<org::imm::ImmBlock>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlock>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Block", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmLineCommand>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmLineCommand>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "LineCommand", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmAttached>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmAttached>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Attached", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmLeaf>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmLeaf>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Leaf", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText() const {
  return this->value().text.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCaption", other.getKind())
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmCmdCaption::text);
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCreator", other.getKind())
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmCmdCreator::text);
}
void org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdAuthor", other.getKind())
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmCmdAuthor::text);
}
void org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdEmail", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText() const {
  return this->value().text.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdLanguage", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText() const {
  return this->value().text.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdColumns", other.getKind())
}
org::sem::ColumnView org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView() const {
  return this->value().view;
}
void org::imm::ImmAdapterT<org::imm::ImmCmdName>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdName>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdName", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName() const {
  return this->value().name.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomArgs", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName() const {
  return this->value().name.get();
}
bool org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached() const {
  return this->value().isAttached;
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomRaw", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName() const {
  return this->value().name.get();
}
bool org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached() const {
  return this->value().isAttached;
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText() const {
  return this->value().text.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomText", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName() const {
  return this->value().name.get();
}
bool org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached() const {
  return this->value().isAttached;
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmCmdCustomText::text);
}
void org::imm::ImmAdapterT<org::imm::ImmCmdCall>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCall", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName() const {
  return this->value().name.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName() const {
  return this->value().fileName.get();
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs() const {
  return this->value().insideHeaderAttrs;
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs() const {
  return this->value().callAttrs;
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs() const {
  return this->value().endHeaderAttrs;
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult() const {
  return this->value().result;
}
void org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdTblfm", other.getKind())
}
org::sem::Tblfm org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr() const {
  return this->value().expr;
}
void org::imm::ImmAdapterT<org::imm::ImmHashTag>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmHashTag>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "HashTag", other.getKind())
}
org::sem::HashTagText org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText() const {
  return this->value().text;
}
void org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "InlineFootnote", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag() const {
  return this->value().tag.get();
}
hstd::Opt<org::imm::ImmAdapter> org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmInlineFootnote::definition);
}
void org::imm::ImmAdapterT<org::imm::ImmInlineExport>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "InlineExport", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter() const {
  return this->value().exporter.get();
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent() const {
  return this->value().content.get();
}
void org::imm::ImmAdapterT<org::imm::ImmTime>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmTime>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Time", other.getKind())
}
bool org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive() const {
  return this->value().isActive;
}
org::imm::ImmTime::TimeVariant org::imm::ImmAdapterT<org::imm::ImmTime>::getTime() const {
  return this->value().time;
}
void org::imm::ImmAdapterT<org::imm::ImmTimeRange>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TimeRange", other.getKind())
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmTimeRange::from);
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmTimeRange::to);
}
void org::imm::ImmAdapterT<org::imm::ImmMacro>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmMacro>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Macro", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmMacro>::getName() const {
  return this->value().name.get();
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs() const {
  return this->value().attrs;
}
void org::imm::ImmAdapterT<org::imm::ImmSymbol>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmSymbol>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Symbol", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName() const {
  return this->value().name.get();
}
hstd::ext::ImmVec<org::imm::ImmSymbol::Param> org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters() const {
  return this->value().parameters;
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional() const {
  return this->value().positional;
}
void org::imm::ImmAdapterT<org::imm::ImmEscaped>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmEscaped>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Escaped", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmNewline>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmNewline>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Newline", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmSpace>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmSpace>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Space", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmWord>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmWord>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Word", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmAtMention>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmAtMention>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "AtMention", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmRawText>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmRawText>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "RawText", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmPunctuation>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmPunctuation>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Punctuation", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmPlaceholder>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmPlaceholder>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Placeholder", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBigIdent>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBigIdent>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BigIdent", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmTextTarget>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmTextTarget>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TextTarget", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipToken>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorSkipToken", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipGroup>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorSkipGroup", other.getKind())
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>> org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped() const {
  return this->value().skipped;
}
void org::imm::ImmAdapterT<org::imm::ImmMarkup>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmMarkup>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Markup", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBold>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBold>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Bold", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmUnderline>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmUnderline>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Underline", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmMonospace>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmMonospace>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Monospace", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmMarkQuote>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmMarkQuote>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "MarkQuote", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmVerbatim>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmVerbatim>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Verbatim", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmItalic>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmItalic>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Italic", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmStrike>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmStrike>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Strike", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmPar>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmPar>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Par", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmRadioTarget>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "RadioTarget", other.getKind())
}
hstd::ext::ImmVec<hstd::Str> org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords() const {
  return this->value().words;
}
void org::imm::ImmAdapterT<org::imm::ImmLatex>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmLatex>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Latex", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmLink>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmLink>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Link", other.getKind())
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmLink::description);
}
org::sem::LinkTarget org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget() const {
  return this->value().target;
}
void org::imm::ImmAdapterT<org::imm::ImmBlockCenter>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockCenter>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCenter", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockQuote>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockQuote>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockQuote", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockComment>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockComment>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockComment", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockVerse>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockVerse>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockVerse", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockDynamicFallback>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockDynamicFallback", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName() const {
  return this->value().name.get();
}
void org::imm::ImmAdapterT<org::imm::ImmBlockExample>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockExample>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockExample", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockExport>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockExport>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockExport", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter() const {
  return this->value().exporter.get();
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent() const {
  return this->value().content.get();
}
void org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockAdmonition>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockAdmonition", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockCodeEvalResult>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCodeEvalResult", other.getKind())
}
hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw() const {
  return this->value().raw;
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmBlockCodeEvalResult::node);
}
void org::imm::ImmAdapterT<org::imm::ImmBlockCode>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCode", other.getKind())
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang() const {
  return this->value().lang.get();
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult() const {
  return this->value().result;
}
hstd::ext::ImmVec<org::sem::BlockCodeLine> org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines() const {
  return this->value().lines;
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches() const {
  return this->value().switches;
}
void org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "SubtreeLog", other.getKind())
}
org::sem::SubtreeLogHead org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead() const {
  return this->value().head;
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>> org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtreeLog::desc);
}
void org::imm::ImmAdapterT<org::imm::ImmSubtree>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmSubtree>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Subtree", other.getKind())
}
int org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel() const {
  return this->value().level;
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId() const {
  return this->value().treeId.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo() const {
  return this->value().todo.get();
}
hstd::Opt<org::sem::SubtreeCompletion> const& org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion() const {
  return this->value().completion.get();
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtree::description);
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags() const {
  return this->value().tags;
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtree::title);
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook() const {
  return this->value().logbook;
}
hstd::ext::ImmVec<org::sem::NamedProperty> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties() const {
  return this->value().properties;
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtree::closed);
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtree::deadline);
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmSubtree::scheduled);
}
bool org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment() const {
  return this->value().isComment;
}
bool org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived() const {
  return this->value().isArchived;
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority() const {
  return this->value().priority.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCell>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCell>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Cell", other.getKind())
}
bool org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock() const {
  return this->value().isBlock;
}
void org::imm::ImmAdapterT<org::imm::ImmRow>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmRow>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Row", other.getKind())
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>> org::imm::ImmAdapterT<org::imm::ImmRow>::getCells() const {
  return this->value().cells;
}
bool org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock() const {
  return this->value().isBlock;
}
void org::imm::ImmAdapterT<org::imm::ImmTable>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmTable>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Table", other.getKind())
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>> org::imm::ImmAdapterT<org::imm::ImmTable>::getRows() const {
  return this->value().rows;
}
bool org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock() const {
  return this->value().isBlock;
}
void org::imm::ImmAdapterT<org::imm::ImmParagraph>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmParagraph>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Paragraph", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmColonExample>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmColonExample>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ColonExample", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdAttr>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdAttr", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget() const {
  return this->value().target.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdExport>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdExport", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter() const {
  return this->value().exporter.get();
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent() const {
  return this->value().content.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCall>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCall>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Call", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCall>::getName() const {
  return this->value().name.get();
}
org::sem::AttrGroup org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs() const {
  return this->value().attrs;
}
bool org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand() const {
  return this->value().isCommand;
}
void org::imm::ImmAdapterT<org::imm::ImmList>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmList>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "List", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmListItem>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmListItem>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ListItem", other.getKind())
}
CheckboxState org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox() const {
  return this->value().checkbox;
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmListItem::header);
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet() const {
  return this->value().bullet.get();
}
void org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentOptions", other.getKind())
}
InitialSubtreeVisibility org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility() const {
  return this->value().initialVisibility;
}
hstd::ext::ImmVec<org::sem::NamedProperty> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties() const {
  return this->value().properties;
}
org::sem::DocumentExportConfig org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig() const {
  return this->value().exportConfig;
}
hstd::Opt<bool> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections() const {
  return this->value().fixedWidthSections.get();
}
hstd::Opt<bool> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented() const {
  return this->value().startupIndented.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory() const {
  return this->value().category.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile() const {
  return this->value().setupfile.get();
}
hstd::Opt<int> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport() const {
  return this->value().maxSubtreeLevelExport.get();
}
hstd::Opt<org::sem::ColumnView> const& org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns() const {
  return this->value().columns.get();
}
hstd::ext::ImmVec<org::sem::TodoKeyword> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords() const {
  return this->value().todoKeywords;
}
hstd::ext::ImmVec<org::sem::TodoKeyword> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords() const {
  return this->value().doneKeywords;
}
void org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentFragment", other.getKind())
}
int org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine() const {
  return this->value().baseLine;
}
int org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol() const {
  return this->value().baseCol;
}
void org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CriticMarkup", other.getKind())
}
org::imm::ImmCriticMarkup::Kind org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind() const {
  return this->value().kind;
}
void org::imm::ImmAdapterT<org::imm::ImmDocument>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmDocument>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Document", other.getKind())
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmDocument::title);
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmDocument::author);
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmDocument::creator);
}
hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags() const {
  return this->value().filetags;
}
hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>> org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmDocument::email);
}
hstd::ext::ImmVec<hstd::Str> org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage() const {
  return this->value().language;
}
org::imm::ImmAdapter org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions() const {
  return org::imm::get_adapter_field(this, &org::imm::ImmDocument::options);
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName() const {
  return this->value().exportFileName.get();
}
void org::imm::ImmAdapterT<org::imm::ImmFileTarget>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "FileTarget", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath() const {
  return this->value().path.get();
}
hstd::Opt<int> const& org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine() const {
  return this->value().line.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget() const {
  return this->value().searchTarget.get();
}
bool org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines() const {
  return this->value().restrictToHeadlines;
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId() const {
  return this->value().targetId.get();
}
hstd::Opt<hstd::Str> const& org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp() const {
  return this->value().regexp.get();
}
void org::imm::ImmAdapterT<org::imm::ImmTextSeparator>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmTextSeparator>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TextSeparator", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmDocumentGroup>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentGroup", other.getKind())
}
void org::imm::ImmAdapterT<org::imm::ImmFile>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmFile>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "File", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath() const {
  return this->value().relPath.get();
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath() const {
  return this->value().absPath.get();
}
org::imm::ImmFile::Data org::imm::ImmAdapterT<org::imm::ImmFile>::getData() const {
  return this->value().data;
}
void org::imm::ImmAdapterT<org::imm::ImmDirectory>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmDirectory>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Directory", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath() const {
  return this->value().relPath.get();
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath() const {
  return this->value().absPath.get();
}
void org::imm::ImmAdapterT<org::imm::ImmSymlink>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmSymlink>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Symlink", other.getKind())
}
bool org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory() const {
  return this->value().isDirectory;
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath() const {
  return this->value().absPath.get();
}
void org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::ImmAdapterT(org::imm::ImmAdapter const& other) : org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>{other} {
  LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdInclude", other.getKind())
}
hstd::Str const& org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath() const {
  return this->value().path.get();
}
hstd::Opt<int> const& org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine() const {
  return this->value().firstLine.get();
}
hstd::Opt<int> const& org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine() const {
  return this->value().lastLine.get();
}
org::imm::ImmCmdInclude::Data org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getData() const {
  return this->value().data;
}
/* clang-format on */