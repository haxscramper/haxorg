/* clang-format off */
#pragma once
#include "org_qml_manual.hpp"
namespace org_qml{
struct LineCol {
  Q_GADGET
  public:
  Q_PROPERTY( int line READ getLine WRITE setLine )
  Q_PROPERTY( int column READ getColumn WRITE setColumn )
  Q_PROPERTY( int pos READ getPos WRITE setPos )
  ::LineCol __data;
  int getLine() { return org_qml::serde<int, int>::cxx_to_qml(__data.line); }
  void setLine(int line) { __data.line = org_qml::serde<int, int>::qml_to_cxx(line); }
  int getColumn() { return org_qml::serde<int, int>::cxx_to_qml(__data.column); }
  void setColumn(int column) { __data.column = org_qml::serde<int, int>::qml_to_cxx(column); }
  int getPos() { return org_qml::serde<int, int>::cxx_to_qml(__data.pos); }
  void setPos(int pos) { __data.pos = org_qml::serde<int, int>::qml_to_cxx(pos); }
};

struct Org {
  Q_GADGET
  public:
  sem::SemId<sem::Org> __data;
};

struct Stmt : public Org {
  Q_GADGET
  public:
};

struct Inline : public Org {
  Q_GADGET
  public:
};

struct StmtList : public Org {
  Q_GADGET
  public:
};

struct Empty : public Org {
  Q_GADGET
  public:
};

struct Row : public Org {
  Q_GADGET
  public:
};

struct Table : public Stmt {
  Q_GADGET
  public:
};

struct HashTag : public Inline {
  Q_GADGET
  public:
  Q_PROPERTY( QString head READ getHead WRITE setHead )
  QString getHead() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::HashTag>()->head); }
  void setHead(QString head) { __data.getAs<sem::HashTag>()->head = org_qml::serde<QString, Str>::qml_to_cxx(head); }
};

struct Footnote : public Inline {
  Q_GADGET
  public:
  Q_PROPERTY( QString tag READ getTag WRITE setTag )
  QString getTag() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Footnote>()->tag); }
  void setTag(QString tag) { __data.getAs<sem::Footnote>()->tag = org_qml::serde<QString, Str>::qml_to_cxx(tag); }
};

struct Completion : public Inline {
  Q_GADGET
  public:
  Q_PROPERTY( int done READ getDone WRITE setDone )
  Q_PROPERTY( int full READ getFull WRITE setFull )
  Q_PROPERTY( bool isPercent READ getIsPercent WRITE setIsPercent )
  int getDone() { return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Completion>()->done); }
  void setDone(int done) { __data.getAs<sem::Completion>()->done = org_qml::serde<int, int>::qml_to_cxx(done); }
  int getFull() { return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Completion>()->full); }
  void setFull(int full) { __data.getAs<sem::Completion>()->full = org_qml::serde<int, int>::qml_to_cxx(full); }
  bool getIsPercent() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Completion>()->isPercent); }
  void setIsPercent(bool isPercent) { __data.getAs<sem::Completion>()->isPercent = org_qml::serde<bool, bool>::qml_to_cxx(isPercent); }
};

struct Paragraph : public Stmt {
  Q_GADGET
  public:
};

struct Format : public Org {
  Q_GADGET
  public:
};

struct Center : public Format {
  Q_GADGET
  public:
};

struct Command : public Org {
  Q_GADGET
  public:
};

struct LineCommand : public Command {
  Q_GADGET
  public:
};

struct Standalone : public LineCommand {
  Q_GADGET
  public:
};

struct Attached : public LineCommand {
  Q_GADGET
  public:
};

struct Caption : public Attached {
  Q_GADGET
  public:
  Q_PROPERTY( sem::SemId<sem::Paragraph> text READ getText WRITE setText )
  sem::SemId<sem::Paragraph> getText() { return org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::cxx_to_qml(__data.getAs<sem::Caption>()->text); }
  void setText(sem::SemId<sem::Paragraph> text) { __data.getAs<sem::Caption>()->text = org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::qml_to_cxx(text); }
};

struct CommandGroup : public Stmt {
  Q_GADGET
  public:
};

struct Block : public Command {
  Q_GADGET
  public:
};

struct Tblfm : public Command {
  Q_GADGET
  public:
};

struct Quote : public Org {
  Q_GADGET
  public:
};

struct Verse : public Block {
  Q_GADGET
  public:
};

struct Example : public Block {
  Q_GADGET
  public:
};

struct CmdArguments : public Org {
  Q_GADGET
  public:
};

struct CmdArgument : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( QString value READ getValue WRITE setValue )
  QString getValue() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::CmdArgument>()->value); }
  void setValue(QString value) { __data.getAs<sem::CmdArgument>()->value = org_qml::serde<QString, Str>::qml_to_cxx(value); }
};

struct Export : public Block {
  Q_GADGET
  public:
  Q_PROPERTY( sem::Export::Format format READ getFormat WRITE setFormat )
  Q_PROPERTY( QString exporter READ getExporter WRITE setExporter )
  Q_PROPERTY( QString content READ getContent WRITE setContent )
  sem::Export::Format getFormat() { return org_qml::serde<sem::Export::Format, sem::Export::Format>::cxx_to_qml(__data.getAs<sem::Export>()->format); }
  void setFormat(sem::Export::Format format) { __data.getAs<sem::Export>()->format = org_qml::serde<sem::Export::Format, sem::Export::Format>::qml_to_cxx(format); }
  QString getExporter() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Export>()->exporter); }
  void setExporter(QString exporter) { __data.getAs<sem::Export>()->exporter = org_qml::serde<QString, Str>::qml_to_cxx(exporter); }
  QString getContent() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Export>()->content); }
  void setContent(QString content) { __data.getAs<sem::Export>()->content = org_qml::serde<QString, Str>::qml_to_cxx(content); }
};

struct AdmonitionBlock : public Block {
  Q_GADGET
  public:
};

struct Code : public Block {
  Q_GADGET
  public:
  Q_PROPERTY( sem::Code::Exports exports READ getExports WRITE setExports )
  Q_PROPERTY( bool cache READ getCache WRITE setCache )
  Q_PROPERTY( bool eval READ getEval WRITE setEval )
  Q_PROPERTY( bool noweb READ getNoweb WRITE setNoweb )
  Q_PROPERTY( bool hlines READ getHlines WRITE setHlines )
  Q_PROPERTY( bool tangle READ getTangle WRITE setTangle )
  sem::Code::Exports getExports() { return org_qml::serde<sem::Code::Exports, sem::Code::Exports>::cxx_to_qml(__data.getAs<sem::Code>()->exports); }
  void setExports(sem::Code::Exports exports) { __data.getAs<sem::Code>()->exports = org_qml::serde<sem::Code::Exports, sem::Code::Exports>::qml_to_cxx(exports); }
  bool getCache() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->cache); }
  void setCache(bool cache) { __data.getAs<sem::Code>()->cache = org_qml::serde<bool, bool>::qml_to_cxx(cache); }
  bool getEval() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->eval); }
  void setEval(bool eval) { __data.getAs<sem::Code>()->eval = org_qml::serde<bool, bool>::qml_to_cxx(eval); }
  bool getNoweb() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->noweb); }
  void setNoweb(bool noweb) { __data.getAs<sem::Code>()->noweb = org_qml::serde<bool, bool>::qml_to_cxx(noweb); }
  bool getHlines() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->hlines); }
  void setHlines(bool hlines) { __data.getAs<sem::Code>()->hlines = org_qml::serde<bool, bool>::qml_to_cxx(hlines); }
  bool getTangle() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Code>()->tangle); }
  void setTangle(bool tangle) { __data.getAs<sem::Code>()->tangle = org_qml::serde<bool, bool>::qml_to_cxx(tangle); }
};

struct Time : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( bool isActive READ getIsActive WRITE setIsActive )
  Q_PROPERTY( sem::Time::TimeVariant time READ getTime WRITE setTime )
  bool getIsActive() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::Time>()->isActive); }
  void setIsActive(bool isActive) { __data.getAs<sem::Time>()->isActive = org_qml::serde<bool, bool>::qml_to_cxx(isActive); }
  sem::Time::TimeVariant getTime() { return org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::cxx_to_qml(__data.getAs<sem::Time>()->time); }
  void setTime(sem::Time::TimeVariant time) { __data.getAs<sem::Time>()->time = org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::qml_to_cxx(time); }
};

struct TimeRange : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::SemId<sem::Time> from READ getFrom WRITE setFrom )
  Q_PROPERTY( sem::SemId<sem::Time> to READ getTo WRITE setTo )
  sem::SemId<sem::Time> getFrom() { return org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::cxx_to_qml(__data.getAs<sem::TimeRange>()->from); }
  void setFrom(sem::SemId<sem::Time> from) { __data.getAs<sem::TimeRange>()->from = org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::qml_to_cxx(from); }
  sem::SemId<sem::Time> getTo() { return org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::cxx_to_qml(__data.getAs<sem::TimeRange>()->to); }
  void setTo(sem::SemId<sem::Time> to) { __data.getAs<sem::TimeRange>()->to = org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::qml_to_cxx(to); }
};

struct Macro : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( QString name READ getName WRITE setName )
  QString getName() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Macro>()->name); }
  void setName(QString name) { __data.getAs<sem::Macro>()->name = org_qml::serde<QString, Str>::qml_to_cxx(name); }
};

struct Symbol : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( QString name READ getName WRITE setName )
  QString getName() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Symbol>()->name); }
  void setName(QString name) { __data.getAs<sem::Symbol>()->name = org_qml::serde<QString, Str>::qml_to_cxx(name); }
};

struct SubtreeLog : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::SubtreeLog::LogEntry log READ getLog WRITE setLog )
  sem::SubtreeLog::LogEntry getLog() { return org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::cxx_to_qml(__data.getAs<sem::SubtreeLog>()->log); }
  void setLog(sem::SubtreeLog::LogEntry log) { __data.getAs<sem::SubtreeLog>()->log = org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::qml_to_cxx(log); }
};

struct Subtree : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( int level READ getLevel WRITE setLevel )
  Q_PROPERTY( sem::SemId<sem::Paragraph> title READ getTitle WRITE setTitle )
  int getLevel() { return org_qml::serde<int, int>::cxx_to_qml(__data.getAs<sem::Subtree>()->level); }
  void setLevel(int level) { __data.getAs<sem::Subtree>()->level = org_qml::serde<int, int>::qml_to_cxx(level); }
  sem::SemId<sem::Paragraph> getTitle() { return org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::cxx_to_qml(__data.getAs<sem::Subtree>()->title); }
  void setTitle(sem::SemId<sem::Paragraph> title) { __data.getAs<sem::Subtree>()->title = org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::qml_to_cxx(title); }
};

struct LatexBody : public Org {
  Q_GADGET
  public:
};

struct InlineMath : public LatexBody {
  Q_GADGET
  public:
};

struct Leaf : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( QString text READ getText WRITE setText )
  QString getText() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::Leaf>()->text); }
  void setText(QString text) { __data.getAs<sem::Leaf>()->text = org_qml::serde<QString, Str>::qml_to_cxx(text); }
};

struct Escaped : public Leaf {
  Q_GADGET
  public:
};

struct Newline : public Leaf {
  Q_GADGET
  public:
};

struct Space : public Leaf {
  Q_GADGET
  public:
};

struct Word : public Leaf {
  Q_GADGET
  public:
};

struct AtMention : public Leaf {
  Q_GADGET
  public:
};

struct RawText : public Leaf {
  Q_GADGET
  public:
};

struct Punctuation : public Leaf {
  Q_GADGET
  public:
};

struct Placeholder : public Leaf {
  Q_GADGET
  public:
};

struct BigIdent : public Leaf {
  Q_GADGET
  public:
};

struct Markup : public Org {
  Q_GADGET
  public:
};

struct Bold : public Markup {
  Q_GADGET
  public:
};

struct Underline : public Markup {
  Q_GADGET
  public:
};

struct Monospace : public Markup {
  Q_GADGET
  public:
};

struct MarkQuote : public Markup {
  Q_GADGET
  public:
};

struct Verbatim : public Markup {
  Q_GADGET
  public:
};

struct Italic : public Markup {
  Q_GADGET
  public:
};

struct Strike : public Markup {
  Q_GADGET
  public:
};

struct Par : public Markup {
  Q_GADGET
  public:
};

struct List : public Org {
  Q_GADGET
  public:
};

struct ListItem : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::ListItem::Checkbox checkbox READ getCheckbox WRITE setCheckbox )
  sem::ListItem::Checkbox getCheckbox() { return org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::cxx_to_qml(__data.getAs<sem::ListItem>()->checkbox); }
  void setCheckbox(sem::ListItem::Checkbox checkbox) { __data.getAs<sem::ListItem>()->checkbox = org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::qml_to_cxx(checkbox); }
};

struct Link : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::Link::Data data READ getData WRITE setData )
  sem::Link::Data getData() { return org_qml::serde<sem::Link::Data, sem::Link::Data>::cxx_to_qml(__data.getAs<sem::Link>()->data); }
  void setData(sem::Link::Data data) { __data.getAs<sem::Link>()->data = org_qml::serde<sem::Link::Data, sem::Link::Data>::qml_to_cxx(data); }
};

struct Document : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::SemId<sem::DocumentOptions> options READ getOptions WRITE setOptions )
  sem::SemId<sem::DocumentOptions> getOptions() { return org_qml::serde<sem::SemId<sem::DocumentOptions>, sem::SemId<sem::DocumentOptions>>::cxx_to_qml(__data.getAs<sem::Document>()->options); }
  void setOptions(sem::SemId<sem::DocumentOptions> options) { __data.getAs<sem::Document>()->options = org_qml::serde<sem::SemId<sem::DocumentOptions>, sem::SemId<sem::DocumentOptions>>::qml_to_cxx(options); }
};

struct ParseError : public Org {
  Q_GADGET
  public:
};

struct FileTarget : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( QString path READ getPath WRITE setPath )
  Q_PROPERTY( bool restrictToHeadlines READ getRestrictToHeadlines WRITE setRestrictToHeadlines )
  QString getPath() { return org_qml::serde<QString, Str>::cxx_to_qml(__data.getAs<sem::FileTarget>()->path); }
  void setPath(QString path) { __data.getAs<sem::FileTarget>()->path = org_qml::serde<QString, Str>::qml_to_cxx(path); }
  bool getRestrictToHeadlines() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::FileTarget>()->restrictToHeadlines); }
  void setRestrictToHeadlines(bool restrictToHeadlines) { __data.getAs<sem::FileTarget>()->restrictToHeadlines = org_qml::serde<bool, bool>::qml_to_cxx(restrictToHeadlines); }
};

struct TextSeparator : public Org {
  Q_GADGET
  public:
};

struct Include : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::Include::Data data READ getData WRITE setData )
  sem::Include::Data getData() { return org_qml::serde<sem::Include::Data, sem::Include::Data>::cxx_to_qml(__data.getAs<sem::Include>()->data); }
  void setData(sem::Include::Data data) { __data.getAs<sem::Include>()->data = org_qml::serde<sem::Include::Data, sem::Include::Data>::qml_to_cxx(data); }
};

struct DocumentOptions : public Org {
  Q_GADGET
  public:
  Q_PROPERTY( sem::DocumentOptions::BrokenLinks brokenLinks READ getBrokenLinks WRITE setBrokenLinks )
  Q_PROPERTY( sem::DocumentOptions::Visibility initialVisibility READ getInitialVisibility WRITE setInitialVisibility )
  Q_PROPERTY( sem::DocumentOptions::TocExport tocExport READ getTocExport WRITE setTocExport )
  Q_PROPERTY( bool smartQuotes READ getSmartQuotes WRITE setSmartQuotes )
  Q_PROPERTY( bool emphasizedText READ getEmphasizedText WRITE setEmphasizedText )
  Q_PROPERTY( bool specialStrings READ getSpecialStrings WRITE setSpecialStrings )
  Q_PROPERTY( bool fixedWidthSections READ getFixedWidthSections WRITE setFixedWidthSections )
  Q_PROPERTY( bool includeTimestamps READ getIncludeTimestamps WRITE setIncludeTimestamps )
  Q_PROPERTY( bool preserveLineBreaks READ getPreserveLineBreaks WRITE setPreserveLineBreaks )
  Q_PROPERTY( bool plaintextSubscripts READ getPlaintextSubscripts WRITE setPlaintextSubscripts )
  Q_PROPERTY( bool exportArchived READ getExportArchived WRITE setExportArchived )
  Q_PROPERTY( bool exportWithAuthor READ getExportWithAuthor WRITE setExportWithAuthor )
  Q_PROPERTY( bool exportBrokenLinks READ getExportBrokenLinks WRITE setExportBrokenLinks )
  Q_PROPERTY( bool exportWithClock READ getExportWithClock WRITE setExportWithClock )
  Q_PROPERTY( bool exportWithCreator READ getExportWithCreator WRITE setExportWithCreator )
  Q_PROPERTY( sem::DocumentOptions::TocExport data READ getData WRITE setData )
  sem::DocumentOptions::BrokenLinks getBrokenLinks() { return org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->brokenLinks); }
  void setBrokenLinks(sem::DocumentOptions::BrokenLinks brokenLinks) { __data.getAs<sem::DocumentOptions>()->brokenLinks = org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::qml_to_cxx(brokenLinks); }
  sem::DocumentOptions::Visibility getInitialVisibility() { return org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->initialVisibility); }
  void setInitialVisibility(sem::DocumentOptions::Visibility initialVisibility) { __data.getAs<sem::DocumentOptions>()->initialVisibility = org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::qml_to_cxx(initialVisibility); }
  sem::DocumentOptions::TocExport getTocExport() { return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->tocExport); }
  void setTocExport(sem::DocumentOptions::TocExport tocExport) { __data.getAs<sem::DocumentOptions>()->tocExport = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(tocExport); }
  bool getSmartQuotes() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->smartQuotes); }
  void setSmartQuotes(bool smartQuotes) { __data.getAs<sem::DocumentOptions>()->smartQuotes = org_qml::serde<bool, bool>::qml_to_cxx(smartQuotes); }
  bool getEmphasizedText() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->emphasizedText); }
  void setEmphasizedText(bool emphasizedText) { __data.getAs<sem::DocumentOptions>()->emphasizedText = org_qml::serde<bool, bool>::qml_to_cxx(emphasizedText); }
  bool getSpecialStrings() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->specialStrings); }
  void setSpecialStrings(bool specialStrings) { __data.getAs<sem::DocumentOptions>()->specialStrings = org_qml::serde<bool, bool>::qml_to_cxx(specialStrings); }
  bool getFixedWidthSections() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->fixedWidthSections); }
  void setFixedWidthSections(bool fixedWidthSections) { __data.getAs<sem::DocumentOptions>()->fixedWidthSections = org_qml::serde<bool, bool>::qml_to_cxx(fixedWidthSections); }
  bool getIncludeTimestamps() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->includeTimestamps); }
  void setIncludeTimestamps(bool includeTimestamps) { __data.getAs<sem::DocumentOptions>()->includeTimestamps = org_qml::serde<bool, bool>::qml_to_cxx(includeTimestamps); }
  bool getPreserveLineBreaks() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->preserveLineBreaks); }
  void setPreserveLineBreaks(bool preserveLineBreaks) { __data.getAs<sem::DocumentOptions>()->preserveLineBreaks = org_qml::serde<bool, bool>::qml_to_cxx(preserveLineBreaks); }
  bool getPlaintextSubscripts() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->plaintextSubscripts); }
  void setPlaintextSubscripts(bool plaintextSubscripts) { __data.getAs<sem::DocumentOptions>()->plaintextSubscripts = org_qml::serde<bool, bool>::qml_to_cxx(plaintextSubscripts); }
  bool getExportArchived() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportArchived); }
  void setExportArchived(bool exportArchived) { __data.getAs<sem::DocumentOptions>()->exportArchived = org_qml::serde<bool, bool>::qml_to_cxx(exportArchived); }
  bool getExportWithAuthor() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithAuthor); }
  void setExportWithAuthor(bool exportWithAuthor) { __data.getAs<sem::DocumentOptions>()->exportWithAuthor = org_qml::serde<bool, bool>::qml_to_cxx(exportWithAuthor); }
  bool getExportBrokenLinks() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportBrokenLinks); }
  void setExportBrokenLinks(bool exportBrokenLinks) { __data.getAs<sem::DocumentOptions>()->exportBrokenLinks = org_qml::serde<bool, bool>::qml_to_cxx(exportBrokenLinks); }
  bool getExportWithClock() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithClock); }
  void setExportWithClock(bool exportWithClock) { __data.getAs<sem::DocumentOptions>()->exportWithClock = org_qml::serde<bool, bool>::qml_to_cxx(exportWithClock); }
  bool getExportWithCreator() { return org_qml::serde<bool, bool>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->exportWithCreator); }
  void setExportWithCreator(bool exportWithCreator) { __data.getAs<sem::DocumentOptions>()->exportWithCreator = org_qml::serde<bool, bool>::qml_to_cxx(exportWithCreator); }
  sem::DocumentOptions::TocExport getData() { return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(__data.getAs<sem::DocumentOptions>()->data); }
  void setData(sem::DocumentOptions::TocExport data) { __data.getAs<sem::DocumentOptions>()->data = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(data); }
};

struct DocumentGroup : public Org {
  Q_GADGET
  public:
};

}
Q_DECLARE_METATYPE(org_qml::LineCol)
Q_DECLARE_METATYPE(org_qml::Org)
Q_DECLARE_METATYPE(org_qml::Stmt)
Q_DECLARE_METATYPE(org_qml::Inline)
Q_DECLARE_METATYPE(org_qml::StmtList)
Q_DECLARE_METATYPE(org_qml::Empty)
Q_DECLARE_METATYPE(org_qml::Row)
Q_DECLARE_METATYPE(org_qml::Table)
Q_DECLARE_METATYPE(org_qml::HashTag)
Q_DECLARE_METATYPE(org_qml::Footnote)
Q_DECLARE_METATYPE(org_qml::Completion)
Q_DECLARE_METATYPE(org_qml::Paragraph)
Q_DECLARE_METATYPE(org_qml::Format)
Q_DECLARE_METATYPE(org_qml::Center)
Q_DECLARE_METATYPE(org_qml::Command)
Q_DECLARE_METATYPE(org_qml::LineCommand)
Q_DECLARE_METATYPE(org_qml::Standalone)
Q_DECLARE_METATYPE(org_qml::Attached)
Q_DECLARE_METATYPE(org_qml::Caption)
Q_DECLARE_METATYPE(org_qml::CommandGroup)
Q_DECLARE_METATYPE(org_qml::Block)
Q_DECLARE_METATYPE(org_qml::Tblfm)
Q_DECLARE_METATYPE(org_qml::Quote)
Q_DECLARE_METATYPE(org_qml::Verse)
Q_DECLARE_METATYPE(org_qml::Example)
Q_DECLARE_METATYPE(org_qml::CmdArguments)
Q_DECLARE_METATYPE(org_qml::CmdArgument)
Q_DECLARE_METATYPE(org_qml::Export)
Q_DECLARE_METATYPE(org_qml::AdmonitionBlock)
Q_DECLARE_METATYPE(org_qml::Code)
Q_DECLARE_METATYPE(org_qml::Time)
Q_DECLARE_METATYPE(org_qml::TimeRange)
Q_DECLARE_METATYPE(org_qml::Macro)
Q_DECLARE_METATYPE(org_qml::Symbol)
Q_DECLARE_METATYPE(org_qml::SubtreeLog)
Q_DECLARE_METATYPE(org_qml::Subtree)
Q_DECLARE_METATYPE(org_qml::LatexBody)
Q_DECLARE_METATYPE(org_qml::InlineMath)
Q_DECLARE_METATYPE(org_qml::Leaf)
Q_DECLARE_METATYPE(org_qml::Escaped)
Q_DECLARE_METATYPE(org_qml::Newline)
Q_DECLARE_METATYPE(org_qml::Space)
Q_DECLARE_METATYPE(org_qml::Word)
Q_DECLARE_METATYPE(org_qml::AtMention)
Q_DECLARE_METATYPE(org_qml::RawText)
Q_DECLARE_METATYPE(org_qml::Punctuation)
Q_DECLARE_METATYPE(org_qml::Placeholder)
Q_DECLARE_METATYPE(org_qml::BigIdent)
Q_DECLARE_METATYPE(org_qml::Markup)
Q_DECLARE_METATYPE(org_qml::Bold)
Q_DECLARE_METATYPE(org_qml::Underline)
Q_DECLARE_METATYPE(org_qml::Monospace)
Q_DECLARE_METATYPE(org_qml::MarkQuote)
Q_DECLARE_METATYPE(org_qml::Verbatim)
Q_DECLARE_METATYPE(org_qml::Italic)
Q_DECLARE_METATYPE(org_qml::Strike)
Q_DECLARE_METATYPE(org_qml::Par)
Q_DECLARE_METATYPE(org_qml::List)
Q_DECLARE_METATYPE(org_qml::ListItem)
Q_DECLARE_METATYPE(org_qml::Link)
Q_DECLARE_METATYPE(org_qml::Document)
Q_DECLARE_METATYPE(org_qml::ParseError)
Q_DECLARE_METATYPE(org_qml::FileTarget)
Q_DECLARE_METATYPE(org_qml::TextSeparator)
Q_DECLARE_METATYPE(org_qml::Include)
Q_DECLARE_METATYPE(org_qml::DocumentOptions)
Q_DECLARE_METATYPE(org_qml::DocumentGroup)
/* clang-format on */