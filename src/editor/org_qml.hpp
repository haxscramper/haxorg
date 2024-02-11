/* clang-format off */
#pragma once
#include "org_qml_manual.hpp"
namespace org_qml{
struct LineCol : public QObject {
  Q_OBJECT
  public:
  Q_PROPERTY( int line READ getLine WRITE setLine )
  Q_PROPERTY( int column READ getColumn WRITE setColumn )
  Q_PROPERTY( int pos READ getPos WRITE setPos )
  ::LineCol value;
  int getLine() { return org_qml::serde<int, int>::cxx_to_qml(value.line); }
  void setLine(int line) { value.line = org_qml::serde<int, int>::qml_to_cxx(line); }
  int getColumn() { return org_qml::serde<int, int>::cxx_to_qml(value.column); }
  void setColumn(int column) { value.column = org_qml::serde<int, int>::qml_to_cxx(column); }
  int getPos() { return org_qml::serde<int, int>::cxx_to_qml(value.pos); }
  void setPos(int pos) { value.pos = org_qml::serde<int, int>::qml_to_cxx(pos); }
};

struct Org : public QObject {
  Q_OBJECT
  public:
  sem::SemId<sem::Org> value;
};

struct Stmt : public Org {
  Q_OBJECT
  public:
};

struct Inline : public Org {
  Q_OBJECT
  public:
};

struct StmtList : public Org {
  Q_OBJECT
  public:
};

struct Empty : public Org {
  Q_OBJECT
  public:
};

struct Row : public Org {
  Q_OBJECT
  public:
};

struct Table : public Stmt {
  Q_OBJECT
  public:
};

struct HashTag : public Inline {
  Q_OBJECT
  public:
};

struct Footnote : public Inline {
  Q_OBJECT
  public:
};

struct Completion : public Inline {
  Q_OBJECT
  public:
  Q_PROPERTY( int done READ getDone WRITE setDone )
  Q_PROPERTY( int full READ getFull WRITE setFull )
  Q_PROPERTY( bool isPercent READ getIsPercent WRITE setIsPercent )
  int getDone() { return org_qml::serde<int, int>::cxx_to_qml(value.getAs<sem::Completion>()->done); }
  void setDone(int done) { value.getAs<sem::Completion>()->done = org_qml::serde<int, int>::qml_to_cxx(done); }
  int getFull() { return org_qml::serde<int, int>::cxx_to_qml(value.getAs<sem::Completion>()->full); }
  void setFull(int full) { value.getAs<sem::Completion>()->full = org_qml::serde<int, int>::qml_to_cxx(full); }
  bool getIsPercent() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Completion>()->isPercent); }
  void setIsPercent(bool isPercent) { value.getAs<sem::Completion>()->isPercent = org_qml::serde<bool, bool>::qml_to_cxx(isPercent); }
};

struct Paragraph : public Stmt {
  Q_OBJECT
  public:
};

struct Format : public Org {
  Q_OBJECT
  public:
};

struct Center : public Format {
  Q_OBJECT
  public:
};

struct Command : public Org {
  Q_OBJECT
  public:
};

struct LineCommand : public Command {
  Q_OBJECT
  public:
};

struct Standalone : public LineCommand {
  Q_OBJECT
  public:
};

struct Attached : public LineCommand {
  Q_OBJECT
  public:
};

struct Caption : public Attached {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::SemId<sem::Paragraph> text READ getText WRITE setText )
  sem::SemId<sem::Paragraph> getText() { return org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::cxx_to_qml(value.getAs<sem::Caption>()->text); }
  void setText(sem::SemId<sem::Paragraph> text) { value.getAs<sem::Caption>()->text = org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::qml_to_cxx(text); }
};

struct CommandGroup : public Stmt {
  Q_OBJECT
  public:
};

struct Block : public Command {
  Q_OBJECT
  public:
};

struct Tblfm : public Command {
  Q_OBJECT
  public:
};

struct Quote : public Org {
  Q_OBJECT
  public:
};

struct Verse : public Block {
  Q_OBJECT
  public:
};

struct Example : public Block {
  Q_OBJECT
  public:
};

struct CmdArguments : public Org {
  Q_OBJECT
  public:
};

struct CmdArgument : public Org {
  Q_OBJECT
  public:
};

struct Export : public Block {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::Export::Format format READ getFormat WRITE setFormat )
  sem::Export::Format getFormat() { return org_qml::serde<sem::Export::Format, sem::Export::Format>::cxx_to_qml(value.getAs<sem::Export>()->format); }
  void setFormat(sem::Export::Format format) { value.getAs<sem::Export>()->format = org_qml::serde<sem::Export::Format, sem::Export::Format>::qml_to_cxx(format); }
};

struct AdmonitionBlock : public Block {
  Q_OBJECT
  public:
};

struct Code : public Block {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::Code::Exports exports READ getExports WRITE setExports )
  Q_PROPERTY( bool cache READ getCache WRITE setCache )
  Q_PROPERTY( bool eval READ getEval WRITE setEval )
  Q_PROPERTY( bool noweb READ getNoweb WRITE setNoweb )
  Q_PROPERTY( bool hlines READ getHlines WRITE setHlines )
  Q_PROPERTY( bool tangle READ getTangle WRITE setTangle )
  sem::Code::Exports getExports() { return org_qml::serde<sem::Code::Exports, sem::Code::Exports>::cxx_to_qml(value.getAs<sem::Code>()->exports); }
  void setExports(sem::Code::Exports exports) { value.getAs<sem::Code>()->exports = org_qml::serde<sem::Code::Exports, sem::Code::Exports>::qml_to_cxx(exports); }
  bool getCache() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Code>()->cache); }
  void setCache(bool cache) { value.getAs<sem::Code>()->cache = org_qml::serde<bool, bool>::qml_to_cxx(cache); }
  bool getEval() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Code>()->eval); }
  void setEval(bool eval) { value.getAs<sem::Code>()->eval = org_qml::serde<bool, bool>::qml_to_cxx(eval); }
  bool getNoweb() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Code>()->noweb); }
  void setNoweb(bool noweb) { value.getAs<sem::Code>()->noweb = org_qml::serde<bool, bool>::qml_to_cxx(noweb); }
  bool getHlines() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Code>()->hlines); }
  void setHlines(bool hlines) { value.getAs<sem::Code>()->hlines = org_qml::serde<bool, bool>::qml_to_cxx(hlines); }
  bool getTangle() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Code>()->tangle); }
  void setTangle(bool tangle) { value.getAs<sem::Code>()->tangle = org_qml::serde<bool, bool>::qml_to_cxx(tangle); }
};

struct Time : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( bool isActive READ getIsActive WRITE setIsActive )
  Q_PROPERTY( sem::Time::TimeVariant time READ getTime WRITE setTime )
  bool getIsActive() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::Time>()->isActive); }
  void setIsActive(bool isActive) { value.getAs<sem::Time>()->isActive = org_qml::serde<bool, bool>::qml_to_cxx(isActive); }
  sem::Time::TimeVariant getTime() { return org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::cxx_to_qml(value.getAs<sem::Time>()->time); }
  void setTime(sem::Time::TimeVariant time) { value.getAs<sem::Time>()->time = org_qml::serde<sem::Time::TimeVariant, sem::Time::TimeVariant>::qml_to_cxx(time); }
};

struct TimeRange : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::SemId<sem::Time> from READ getFrom WRITE setFrom )
  Q_PROPERTY( sem::SemId<sem::Time> to READ getTo WRITE setTo )
  sem::SemId<sem::Time> getFrom() { return org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::cxx_to_qml(value.getAs<sem::TimeRange>()->from); }
  void setFrom(sem::SemId<sem::Time> from) { value.getAs<sem::TimeRange>()->from = org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::qml_to_cxx(from); }
  sem::SemId<sem::Time> getTo() { return org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::cxx_to_qml(value.getAs<sem::TimeRange>()->to); }
  void setTo(sem::SemId<sem::Time> to) { value.getAs<sem::TimeRange>()->to = org_qml::serde<sem::SemId<sem::Time>, sem::SemId<sem::Time>>::qml_to_cxx(to); }
};

struct Macro : public Org {
  Q_OBJECT
  public:
};

struct Symbol : public Org {
  Q_OBJECT
  public:
};

struct SubtreeLog : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::SubtreeLog::LogEntry log READ getLog WRITE setLog )
  sem::SubtreeLog::LogEntry getLog() { return org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::cxx_to_qml(value.getAs<sem::SubtreeLog>()->log); }
  void setLog(sem::SubtreeLog::LogEntry log) { value.getAs<sem::SubtreeLog>()->log = org_qml::serde<sem::SubtreeLog::LogEntry, sem::SubtreeLog::LogEntry>::qml_to_cxx(log); }
};

struct Subtree : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( int level READ getLevel WRITE setLevel )
  Q_PROPERTY( sem::SemId<sem::Paragraph> title READ getTitle WRITE setTitle )
  int getLevel() { return org_qml::serde<int, int>::cxx_to_qml(value.getAs<sem::Subtree>()->level); }
  void setLevel(int level) { value.getAs<sem::Subtree>()->level = org_qml::serde<int, int>::qml_to_cxx(level); }
  sem::SemId<sem::Paragraph> getTitle() { return org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::cxx_to_qml(value.getAs<sem::Subtree>()->title); }
  void setTitle(sem::SemId<sem::Paragraph> title) { value.getAs<sem::Subtree>()->title = org_qml::serde<sem::SemId<sem::Paragraph>, sem::SemId<sem::Paragraph>>::qml_to_cxx(title); }
};

struct LatexBody : public Org {
  Q_OBJECT
  public:
};

struct InlineMath : public LatexBody {
  Q_OBJECT
  public:
};

struct Leaf : public Org {
  Q_OBJECT
  public:
};

struct Escaped : public Leaf {
  Q_OBJECT
  public:
};

struct Newline : public Leaf {
  Q_OBJECT
  public:
};

struct Space : public Leaf {
  Q_OBJECT
  public:
};

struct Word : public Leaf {
  Q_OBJECT
  public:
};

struct AtMention : public Leaf {
  Q_OBJECT
  public:
};

struct RawText : public Leaf {
  Q_OBJECT
  public:
};

struct Punctuation : public Leaf {
  Q_OBJECT
  public:
};

struct Placeholder : public Leaf {
  Q_OBJECT
  public:
};

struct BigIdent : public Leaf {
  Q_OBJECT
  public:
};

struct Markup : public Org {
  Q_OBJECT
  public:
};

struct Bold : public Markup {
  Q_OBJECT
  public:
};

struct Underline : public Markup {
  Q_OBJECT
  public:
};

struct Monospace : public Markup {
  Q_OBJECT
  public:
};

struct MarkQuote : public Markup {
  Q_OBJECT
  public:
};

struct Verbatim : public Markup {
  Q_OBJECT
  public:
};

struct Italic : public Markup {
  Q_OBJECT
  public:
};

struct Strike : public Markup {
  Q_OBJECT
  public:
};

struct Par : public Markup {
  Q_OBJECT
  public:
};

struct List : public Org {
  Q_OBJECT
  public:
};

struct ListItem : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::ListItem::Checkbox checkbox READ getCheckbox WRITE setCheckbox )
  sem::ListItem::Checkbox getCheckbox() { return org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::cxx_to_qml(value.getAs<sem::ListItem>()->checkbox); }
  void setCheckbox(sem::ListItem::Checkbox checkbox) { value.getAs<sem::ListItem>()->checkbox = org_qml::serde<sem::ListItem::Checkbox, sem::ListItem::Checkbox>::qml_to_cxx(checkbox); }
};

struct Link : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::Link::Data data READ getData WRITE setData )
  sem::Link::Data getData() { return org_qml::serde<sem::Link::Data, sem::Link::Data>::cxx_to_qml(value.getAs<sem::Link>()->data); }
  void setData(sem::Link::Data data) { value.getAs<sem::Link>()->data = org_qml::serde<sem::Link::Data, sem::Link::Data>::qml_to_cxx(data); }
};

struct Document : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::SemId<sem::DocumentOptions> options READ getOptions WRITE setOptions )
  sem::SemId<sem::DocumentOptions> getOptions() { return org_qml::serde<sem::SemId<sem::DocumentOptions>, sem::SemId<sem::DocumentOptions>>::cxx_to_qml(value.getAs<sem::Document>()->options); }
  void setOptions(sem::SemId<sem::DocumentOptions> options) { value.getAs<sem::Document>()->options = org_qml::serde<sem::SemId<sem::DocumentOptions>, sem::SemId<sem::DocumentOptions>>::qml_to_cxx(options); }
};

struct ParseError : public Org {
  Q_OBJECT
  public:
};

struct FileTarget : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( bool restrictToHeadlines READ getRestrictToHeadlines WRITE setRestrictToHeadlines )
  bool getRestrictToHeadlines() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::FileTarget>()->restrictToHeadlines); }
  void setRestrictToHeadlines(bool restrictToHeadlines) { value.getAs<sem::FileTarget>()->restrictToHeadlines = org_qml::serde<bool, bool>::qml_to_cxx(restrictToHeadlines); }
};

struct TextSeparator : public Org {
  Q_OBJECT
  public:
};

struct Include : public Org {
  Q_OBJECT
  public:
  Q_PROPERTY( sem::Include::Data data READ getData WRITE setData )
  sem::Include::Data getData() { return org_qml::serde<sem::Include::Data, sem::Include::Data>::cxx_to_qml(value.getAs<sem::Include>()->data); }
  void setData(sem::Include::Data data) { value.getAs<sem::Include>()->data = org_qml::serde<sem::Include::Data, sem::Include::Data>::qml_to_cxx(data); }
};

struct DocumentOptions : public Org {
  Q_OBJECT
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
  sem::DocumentOptions::BrokenLinks getBrokenLinks() { return org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->brokenLinks); }
  void setBrokenLinks(sem::DocumentOptions::BrokenLinks brokenLinks) { value.getAs<sem::DocumentOptions>()->brokenLinks = org_qml::serde<sem::DocumentOptions::BrokenLinks, sem::DocumentOptions::BrokenLinks>::qml_to_cxx(brokenLinks); }
  sem::DocumentOptions::Visibility getInitialVisibility() { return org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->initialVisibility); }
  void setInitialVisibility(sem::DocumentOptions::Visibility initialVisibility) { value.getAs<sem::DocumentOptions>()->initialVisibility = org_qml::serde<sem::DocumentOptions::Visibility, sem::DocumentOptions::Visibility>::qml_to_cxx(initialVisibility); }
  sem::DocumentOptions::TocExport getTocExport() { return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->tocExport); }
  void setTocExport(sem::DocumentOptions::TocExport tocExport) { value.getAs<sem::DocumentOptions>()->tocExport = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(tocExport); }
  bool getSmartQuotes() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->smartQuotes); }
  void setSmartQuotes(bool smartQuotes) { value.getAs<sem::DocumentOptions>()->smartQuotes = org_qml::serde<bool, bool>::qml_to_cxx(smartQuotes); }
  bool getEmphasizedText() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->emphasizedText); }
  void setEmphasizedText(bool emphasizedText) { value.getAs<sem::DocumentOptions>()->emphasizedText = org_qml::serde<bool, bool>::qml_to_cxx(emphasizedText); }
  bool getSpecialStrings() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->specialStrings); }
  void setSpecialStrings(bool specialStrings) { value.getAs<sem::DocumentOptions>()->specialStrings = org_qml::serde<bool, bool>::qml_to_cxx(specialStrings); }
  bool getFixedWidthSections() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->fixedWidthSections); }
  void setFixedWidthSections(bool fixedWidthSections) { value.getAs<sem::DocumentOptions>()->fixedWidthSections = org_qml::serde<bool, bool>::qml_to_cxx(fixedWidthSections); }
  bool getIncludeTimestamps() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->includeTimestamps); }
  void setIncludeTimestamps(bool includeTimestamps) { value.getAs<sem::DocumentOptions>()->includeTimestamps = org_qml::serde<bool, bool>::qml_to_cxx(includeTimestamps); }
  bool getPreserveLineBreaks() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->preserveLineBreaks); }
  void setPreserveLineBreaks(bool preserveLineBreaks) { value.getAs<sem::DocumentOptions>()->preserveLineBreaks = org_qml::serde<bool, bool>::qml_to_cxx(preserveLineBreaks); }
  bool getPlaintextSubscripts() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->plaintextSubscripts); }
  void setPlaintextSubscripts(bool plaintextSubscripts) { value.getAs<sem::DocumentOptions>()->plaintextSubscripts = org_qml::serde<bool, bool>::qml_to_cxx(plaintextSubscripts); }
  bool getExportArchived() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->exportArchived); }
  void setExportArchived(bool exportArchived) { value.getAs<sem::DocumentOptions>()->exportArchived = org_qml::serde<bool, bool>::qml_to_cxx(exportArchived); }
  bool getExportWithAuthor() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->exportWithAuthor); }
  void setExportWithAuthor(bool exportWithAuthor) { value.getAs<sem::DocumentOptions>()->exportWithAuthor = org_qml::serde<bool, bool>::qml_to_cxx(exportWithAuthor); }
  bool getExportBrokenLinks() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->exportBrokenLinks); }
  void setExportBrokenLinks(bool exportBrokenLinks) { value.getAs<sem::DocumentOptions>()->exportBrokenLinks = org_qml::serde<bool, bool>::qml_to_cxx(exportBrokenLinks); }
  bool getExportWithClock() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->exportWithClock); }
  void setExportWithClock(bool exportWithClock) { value.getAs<sem::DocumentOptions>()->exportWithClock = org_qml::serde<bool, bool>::qml_to_cxx(exportWithClock); }
  bool getExportWithCreator() { return org_qml::serde<bool, bool>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->exportWithCreator); }
  void setExportWithCreator(bool exportWithCreator) { value.getAs<sem::DocumentOptions>()->exportWithCreator = org_qml::serde<bool, bool>::qml_to_cxx(exportWithCreator); }
  sem::DocumentOptions::TocExport getData() { return org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::cxx_to_qml(value.getAs<sem::DocumentOptions>()->data); }
  void setData(sem::DocumentOptions::TocExport data) { value.getAs<sem::DocumentOptions>()->data = org_qml::serde<sem::DocumentOptions::TocExport, sem::DocumentOptions::TocExport>::qml_to_cxx(data); }
};

struct DocumentGroup : public Org {
  Q_OBJECT
  public:
};

}
/* clang-format on */