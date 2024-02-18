/* clang-format off */
#include "org_qml_manual2.hpp"
int org_qml::LineCol::getLine() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.line);
}
void org_qml::LineCol::setLine(int line) {
  __data.line = org_qml::serde<int, int>::qml_to_cxx(line);
}
int org_qml::LineCol::getColumn() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.column);
}
void org_qml::LineCol::setColumn(int column) {
  __data.column = org_qml::serde<int, int>::qml_to_cxx(column);
}
int org_qml::LineCol::getPos() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.pos);
}
void org_qml::LineCol::setPos(int pos) {
  __data.pos = org_qml::serde<int, int>::qml_to_cxx(pos);
}
QString org_qml::HashTag::getHead() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::HashTag>()->head);
}
void org_qml::HashTag::setHead(QString head) {
  __data.getAs<sem::HashTag>()->head = org_qml::serde<QString, Str>::qml_to_cxx(head);
}
QString org_qml::Footnote::getTag() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Footnote>()->tag);
}
void org_qml::Footnote::setTag(QString tag) {
  __data.getAs<sem::Footnote>()->tag = org_qml::serde<QString, Str>::qml_to_cxx(tag);
}
int org_qml::Completion::getDone() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Completion>()->done);
}
void org_qml::Completion::setDone(int done) {
  __data.getAs<sem::Completion>()->done = org_qml::serde<int, int>::qml_to_cxx(done);
}
int org_qml::Completion::getFull() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Completion>()->full);
}
void org_qml::Completion::setFull(int full) {
  __data.getAs<sem::Completion>()->full = org_qml::serde<int, int>::qml_to_cxx(full);
}
bool org_qml::Completion::getIsPercent() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Completion>()->isPercent);
}
void org_qml::Completion::setIsPercent(bool isPercent) {
  __data.getAs<sem::Completion>()->isPercent = org_qml::serde<bool, bool>::qml_to_cxx(isPercent);
}
org_qml::Paragraph org_qml::Caption::getText() {
  return org_qml::serde<org_qml::Paragraph, sem::SemId<sem::Paragraph>>::cxx_to_qml(__data.getAs<sem::Caption>()->text);
}
void org_qml::Caption::setText(org_qml::Paragraph text) {
  __data.getAs<sem::Caption>()->text = org_qml::serde<org_qml::Paragraph, sem::SemId<sem::Paragraph>>::qml_to_cxx(text);
}
QString org_qml::CmdArgument::getValue() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::CmdArgument>()->value);
}
void org_qml::CmdArgument::setValue(QString value) {
  __data.getAs<sem::CmdArgument>()->value = org_qml::serde<QString, Str>::qml_to_cxx(value);
}
sem::Export::Format org_qml::Export::getFormat() {
  return org_qml::serde<sem::Export::Format, sem::Export::Format>::cxx_to_qml(__data.getAs<sem::Export>()->format);
}
void org_qml::Export::setFormat(sem::Export::Format format) {
  __data.getAs<sem::Export>()->format = org_qml::serde<sem::Export::Format, sem::Export::Format>::qml_to_cxx(format);
}
QString org_qml::Export::getExporter() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Export>()->exporter);
}
void org_qml::Export::setExporter(QString exporter) {
  __data.getAs<sem::Export>()->exporter = org_qml::serde<QString, Str>::qml_to_cxx(exporter);
}
QString org_qml::Export::getContent() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Export>()->content);
}
void org_qml::Export::setContent(QString content) {
  __data.getAs<sem::Export>()->content = org_qml::serde<QString, Str>::qml_to_cxx(content);
}
sem::Code::Exports org_qml::Code::getExports() {
  return org_qml::serde<sem::Code::Exports, sem::Code::Exports>::cxx_to_qml(__data.getAs<sem::Code>()->exports);
}
void org_qml::Code::setExports(sem::Code::Exports exports) {
  __data.getAs<sem::Code>()->exports = org_qml::serde<sem::Code::Exports, sem::Code::Exports>::qml_to_cxx(exports);
}
bool org_qml::Code::getCache() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->cache);
}
void org_qml::Code::setCache(bool cache) {
  __data.getAs<sem::Code>()->cache = org_qml::serde<bool, bool>::qml_to_cxx(cache);
}
bool org_qml::Code::getEval() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->eval);
}
void org_qml::Code::setEval(bool eval) {
  __data.getAs<sem::Code>()->eval = org_qml::serde<bool, bool>::qml_to_cxx(eval);
}
bool org_qml::Code::getNoweb() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->noweb);
}
void org_qml::Code::setNoweb(bool noweb) {
  __data.getAs<sem::Code>()->noweb = org_qml::serde<bool, bool>::qml_to_cxx(noweb);
}
bool org_qml::Code::getHlines() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->hlines);
}
void org_qml::Code::setHlines(bool hlines) {
  __data.getAs<sem::Code>()->hlines = org_qml::serde<bool, bool>::qml_to_cxx(hlines);
}
bool org_qml::Code::getTangle() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->tangle);
}
void org_qml::Code::setTangle(bool tangle) {
  __data.getAs<sem::Code>()->tangle = org_qml::serde<bool, bool>::qml_to_cxx(tangle);
}
bool org_qml::Time::getIsActive() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Time>()->isActive);
}
void org_qml::Time::setIsActive(bool isActive) {
  __data.getAs<sem::Time>()->isActive = org_qml::serde<bool, bool>::qml_to_cxx(isActive);
}
sem::Time::TimeVariant org_qml::Time::getTime() {
  return org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::cxx_to_qml(__data.getAs<sem::Time>()->time);
}
void org_qml::Time::setTime(sem::Time::TimeVariant time) {
  __data.getAs<sem::Time>()->time = org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::qml_to_cxx(time);
}
org_qml::Time org_qml::TimeRange::getFrom() {
  return org_qml::serde<org_qml::Time, sem::SemId<sem::Time>>::cxx_to_qml(__data.getAs<sem::TimeRange>()->from);
}
void org_qml::TimeRange::setFrom(org_qml::Time from) {
  __data.getAs<sem::TimeRange>()->from = org_qml::serde<org_qml::Time, sem::SemId<sem::Time>>::qml_to_cxx(from);
}
org_qml::Time org_qml::TimeRange::getTo() {
  return org_qml::serde<org_qml::Time, sem::SemId<sem::Time>>::cxx_to_qml(__data.getAs<sem::TimeRange>()->to);
}
void org_qml::TimeRange::setTo(org_qml::Time to) {
  __data.getAs<sem::TimeRange>()->to = org_qml::serde<org_qml::Time, sem::SemId<sem::Time>>::qml_to_cxx(to);
}
QString org_qml::Macro::getName() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Macro>()->name);
}
void org_qml::Macro::setName(QString name) {
  __data.getAs<sem::Macro>()->name = org_qml::serde<QString, Str>::qml_to_cxx(name);
}
QString org_qml::Symbol::getName() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Symbol>()->name);
}
void org_qml::Symbol::setName(QString name) {
  __data.getAs<sem::Symbol>()->name = org_qml::serde<QString, Str>::qml_to_cxx(name);
}
sem::SubtreeLog::LogEntry org_qml::SubtreeLog::getLog() {
  return org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::cxx_to_qml(__data.getAs<sem::SubtreeLog>()->log);
}
void org_qml::SubtreeLog::setLog(sem::SubtreeLog::LogEntry log) {
  __data.getAs<sem::SubtreeLog>()->log = org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::qml_to_cxx(log);
}
int org_qml::Subtree::getLevel() {
  return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Subtree>()->level);
}
void org_qml::Subtree::setLevel(int level) {
  __data.getAs<sem::Subtree>()->level = org_qml::serde<int, int>::qml_to_cxx(level);
}
org_qml::Paragraph org_qml::Subtree::getTitle() {
  return org_qml::serde<org_qml::Paragraph, sem::SemId<sem::Paragraph>>::cxx_to_qml(__data.getAs<sem::Subtree>()->title);
}
void org_qml::Subtree::setTitle(org_qml::Paragraph title) {
  __data.getAs<sem::Subtree>()->title = org_qml::serde<org_qml::Paragraph, sem::SemId<sem::Paragraph>>::qml_to_cxx(title);
}
QString org_qml::Leaf::getText() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Leaf>()->text);
}
void org_qml::Leaf::setText(QString text) {
  __data.getAs<sem::Leaf>()->text = org_qml::serde<QString, Str>::qml_to_cxx(text);
}
sem::ListItem::Checkbox org_qml::ListItem::getCheckbox() {
  return org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::cxx_to_qml(__data.getAs<sem::ListItem>()->checkbox);
}
void org_qml::ListItem::setCheckbox(sem::ListItem::Checkbox checkbox) {
  __data.getAs<sem::ListItem>()->checkbox = org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::qml_to_cxx(checkbox);
}
sem::Link::Data org_qml::Link::getData() {
  return org_qml::serde<sem::Link::Data, sem::Link::Data>::cxx_to_qml(__data.getAs<sem::Link>()->data);
}
void org_qml::Link::setData(sem::Link::Data data) {
  __data.getAs<sem::Link>()->data = org_qml::serde<sem::Link::Data, sem::Link::Data>::qml_to_cxx(data);
}
sem::DocumentOptions::BrokenLinks org_qml::DocumentOptions::getBrokenLinks() {
  return org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->brokenLinks);
}
void org_qml::DocumentOptions::setBrokenLinks(sem::DocumentOptions::BrokenLinks brokenLinks) {
  __data.getAs<sem::DocumentOptions>()->brokenLinks = org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::qml_to_cxx(brokenLinks);
}
sem::DocumentOptions::Visibility org_qml::DocumentOptions::getInitialVisibility() {
  return org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->initialVisibility);
}
void org_qml::DocumentOptions::setInitialVisibility(sem::DocumentOptions::Visibility initialVisibility) {
  __data.getAs<sem::DocumentOptions>()->initialVisibility = org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::qml_to_cxx(initialVisibility);
}
sem::DocumentOptions::TocExport org_qml::DocumentOptions::getTocExport() {
  return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->tocExport);
}
void org_qml::DocumentOptions::setTocExport(sem::DocumentOptions::TocExport tocExport) {
  __data.getAs<sem::DocumentOptions>()->tocExport = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(tocExport);
}
bool org_qml::DocumentOptions::getSmartQuotes() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->smartQuotes);
}
void org_qml::DocumentOptions::setSmartQuotes(bool smartQuotes) {
  __data.getAs<sem::DocumentOptions>()->smartQuotes = org_qml::serde<bool, bool>::qml_to_cxx(smartQuotes);
}
bool org_qml::DocumentOptions::getEmphasizedText() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->emphasizedText);
}
void org_qml::DocumentOptions::setEmphasizedText(bool emphasizedText) {
  __data.getAs<sem::DocumentOptions>()->emphasizedText = org_qml::serde<bool, bool>::qml_to_cxx(emphasizedText);
}
bool org_qml::DocumentOptions::getSpecialStrings() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->specialStrings);
}
void org_qml::DocumentOptions::setSpecialStrings(bool specialStrings) {
  __data.getAs<sem::DocumentOptions>()->specialStrings = org_qml::serde<bool, bool>::qml_to_cxx(specialStrings);
}
bool org_qml::DocumentOptions::getFixedWidthSections() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->fixedWidthSections);
}
void org_qml::DocumentOptions::setFixedWidthSections(bool fixedWidthSections) {
  __data.getAs<sem::DocumentOptions>()->fixedWidthSections = org_qml::serde<bool, bool>::qml_to_cxx(fixedWidthSections);
}
bool org_qml::DocumentOptions::getIncludeTimestamps() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->includeTimestamps);
}
void org_qml::DocumentOptions::setIncludeTimestamps(bool includeTimestamps) {
  __data.getAs<sem::DocumentOptions>()->includeTimestamps = org_qml::serde<bool, bool>::qml_to_cxx(includeTimestamps);
}
bool org_qml::DocumentOptions::getPreserveLineBreaks() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->preserveLineBreaks);
}
void org_qml::DocumentOptions::setPreserveLineBreaks(bool preserveLineBreaks) {
  __data.getAs<sem::DocumentOptions>()->preserveLineBreaks = org_qml::serde<bool, bool>::qml_to_cxx(preserveLineBreaks);
}
bool org_qml::DocumentOptions::getPlaintextSubscripts() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->plaintextSubscripts);
}
void org_qml::DocumentOptions::setPlaintextSubscripts(bool plaintextSubscripts) {
  __data.getAs<sem::DocumentOptions>()->plaintextSubscripts = org_qml::serde<bool, bool>::qml_to_cxx(plaintextSubscripts);
}
bool org_qml::DocumentOptions::getExportArchived() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportArchived);
}
void org_qml::DocumentOptions::setExportArchived(bool exportArchived) {
  __data.getAs<sem::DocumentOptions>()->exportArchived = org_qml::serde<bool, bool>::qml_to_cxx(exportArchived);
}
bool org_qml::DocumentOptions::getExportWithAuthor() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithAuthor);
}
void org_qml::DocumentOptions::setExportWithAuthor(bool exportWithAuthor) {
  __data.getAs<sem::DocumentOptions>()->exportWithAuthor = org_qml::serde<bool, bool>::qml_to_cxx(exportWithAuthor);
}
bool org_qml::DocumentOptions::getExportBrokenLinks() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportBrokenLinks);
}
void org_qml::DocumentOptions::setExportBrokenLinks(bool exportBrokenLinks) {
  __data.getAs<sem::DocumentOptions>()->exportBrokenLinks = org_qml::serde<bool, bool>::qml_to_cxx(exportBrokenLinks);
}
bool org_qml::DocumentOptions::getExportWithClock() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithClock);
}
void org_qml::DocumentOptions::setExportWithClock(bool exportWithClock) {
  __data.getAs<sem::DocumentOptions>()->exportWithClock = org_qml::serde<bool, bool>::qml_to_cxx(exportWithClock);
}
bool org_qml::DocumentOptions::getExportWithCreator() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithCreator);
}
void org_qml::DocumentOptions::setExportWithCreator(bool exportWithCreator) {
  __data.getAs<sem::DocumentOptions>()->exportWithCreator = org_qml::serde<bool, bool>::qml_to_cxx(exportWithCreator);
}
sem::DocumentOptions::TocExport org_qml::DocumentOptions::getData() {
  return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->data);
}
void org_qml::DocumentOptions::setData(sem::DocumentOptions::TocExport data) {
  __data.getAs<sem::DocumentOptions>()->data = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(data);
}
org_qml::DocumentOptions org_qml::Document::getOptions() {
  return org_qml::serde<org_qml::DocumentOptions, sem::SemId<sem::DocumentOptions>>::cxx_to_qml(__data.getAs<sem::Document>()->options);
}
void org_qml::Document::setOptions(org_qml::DocumentOptions options) {
  __data.getAs<sem::Document>()->options = org_qml::serde<org_qml::DocumentOptions, sem::SemId<sem::DocumentOptions>>::qml_to_cxx(options);
}
QString org_qml::FileTarget::getPath() {
  return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::FileTarget>()->path);
}
void org_qml::FileTarget::setPath(QString path) {
  __data.getAs<sem::FileTarget>()->path = org_qml::serde<QString, Str>::qml_to_cxx(path);
}
bool org_qml::FileTarget::getRestrictToHeadlines() {
  return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::FileTarget>()->restrictToHeadlines);
}
void org_qml::FileTarget::setRestrictToHeadlines(bool restrictToHeadlines) {
  __data.getAs<sem::FileTarget>()->restrictToHeadlines = org_qml::serde<bool, bool>::qml_to_cxx(restrictToHeadlines);
}
sem::Include::Data org_qml::Include::getData() {
  return org_qml::serde<sem::Include::Data, sem::Include::Data>::cxx_to_qml(__data.getAs<sem::Include>()->data);
}
void org_qml::Include::setData(sem::Include::Data data) {
  __data.getAs<sem::Include>()->data = org_qml::serde<sem::Include::Data, sem::Include::Data>::qml_to_cxx(data);
}
/* clang-format on */