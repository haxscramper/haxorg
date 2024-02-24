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
  int getLine();
  void setLine(int line);
  int getColumn();
  void setColumn(int column);
  int getPos();
  void setPos(int pos);
};

struct Stmt : public Org {
  Q_GADGET
  public:
  Stmt() = default;
  Stmt(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Inline : public Org {
  Q_GADGET
  public:
  Inline() = default;
  Inline(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct StmtList : public Org {
  Q_GADGET
  public:
  StmtList() = default;
  StmtList(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Empty : public Org {
  Q_GADGET
  public:
  Empty() = default;
  Empty(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Row : public Org {
  Q_GADGET
  public:
  Row() = default;
  Row(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Table : public Stmt {
  Q_GADGET
  public:
  Table() = default;
  Table(sem::SemId<sem::Org> const& id) : Stmt(id) {}
};

struct HashTag : public Inline {
  Q_GADGET
  public:
  HashTag() = default;
  HashTag(sem::SemId<sem::Org> const& id) : Inline(id) {}
  Q_PROPERTY( QString head READ getHead WRITE setHead )
  QString getHead();
  void setHead(QString head);
};

struct Footnote : public Inline {
  Q_GADGET
  public:
  Footnote() = default;
  Footnote(sem::SemId<sem::Org> const& id) : Inline(id) {}
  Q_PROPERTY( QString tag READ getTag WRITE setTag )
  QString getTag();
  void setTag(QString tag);
};

struct Completion : public Inline {
  Q_GADGET
  public:
  Completion() = default;
  Completion(sem::SemId<sem::Org> const& id) : Inline(id) {}
  Q_PROPERTY( int done READ getDone WRITE setDone )
  Q_PROPERTY( int full READ getFull WRITE setFull )
  Q_PROPERTY( bool isPercent READ getIsPercent WRITE setIsPercent )
  int getDone();
  void setDone(int done);
  int getFull();
  void setFull(int full);
  bool getIsPercent();
  void setIsPercent(bool isPercent);
};

struct Paragraph : public Stmt {
  Q_GADGET
  public:
  Paragraph() = default;
  Paragraph(sem::SemId<sem::Org> const& id) : Stmt(id) {}
};

struct Format : public Org {
  Q_GADGET
  public:
  Format() = default;
  Format(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Center : public Format {
  Q_GADGET
  public:
  Center() = default;
  Center(sem::SemId<sem::Org> const& id) : Format(id) {}
};

struct Command : public Org {
  Q_GADGET
  public:
  Command() = default;
  Command(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct LineCommand : public Command {
  Q_GADGET
  public:
  LineCommand() = default;
  LineCommand(sem::SemId<sem::Org> const& id) : Command(id) {}
};

struct Standalone : public LineCommand {
  Q_GADGET
  public:
  Standalone() = default;
  Standalone(sem::SemId<sem::Org> const& id) : LineCommand(id) {}
};

struct Attached : public LineCommand {
  Q_GADGET
  public:
  Attached() = default;
  Attached(sem::SemId<sem::Org> const& id) : LineCommand(id) {}
};

struct Caption : public Attached {
  Q_GADGET
  public:
  Caption() = default;
  Caption(sem::SemId<sem::Org> const& id) : Attached(id) {}
  Q_PROPERTY( org_qml::Paragraph text READ getText WRITE setText )
  org_qml::Paragraph getText();
  void setText(org_qml::Paragraph text);
};

struct CmdName : public Attached {
  Q_GADGET
  public:
  CmdName() = default;
  CmdName(sem::SemId<sem::Org> const& id) : Attached(id) {}
};

struct CmdResults : public Attached {
  Q_GADGET
  public:
  CmdResults() = default;
  CmdResults(sem::SemId<sem::Org> const& id) : Attached(id) {}
};

struct CommandGroup : public Stmt {
  Q_GADGET
  public:
  CommandGroup() = default;
  CommandGroup(sem::SemId<sem::Org> const& id) : Stmt(id) {}
};

struct Block : public Command {
  Q_GADGET
  public:
  Block() = default;
  Block(sem::SemId<sem::Org> const& id) : Command(id) {}
};

struct Tblfm : public Command {
  Q_GADGET
  public:
  Tblfm() = default;
  Tblfm(sem::SemId<sem::Org> const& id) : Command(id) {}
};

struct Quote : public Org {
  Q_GADGET
  public:
  Quote() = default;
  Quote(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Verse : public Block {
  Q_GADGET
  public:
  Verse() = default;
  Verse(sem::SemId<sem::Org> const& id) : Block(id) {}
};

struct Example : public Block {
  Q_GADGET
  public:
  Example() = default;
  Example(sem::SemId<sem::Org> const& id) : Block(id) {}
};

struct CmdArguments : public Org {
  Q_GADGET
  public:
  CmdArguments() = default;
  CmdArguments(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct CmdArgument : public Org {
  Q_GADGET
  public:
  CmdArgument() = default;
  CmdArgument(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( QString value READ getValue WRITE setValue )
  QString getValue();
  void setValue(QString value);
};

struct Export : public Block {
  Q_GADGET
  public:
  Export() = default;
  Export(sem::SemId<sem::Org> const& id) : Block(id) {}
  Q_PROPERTY( sem::Export::Format format READ getFormat WRITE setFormat )
  Q_PROPERTY( QString exporter READ getExporter WRITE setExporter )
  Q_PROPERTY( QString content READ getContent WRITE setContent )
  sem::Export::Format getFormat();
  void setFormat(sem::Export::Format format);
  QString getExporter();
  void setExporter(QString exporter);
  QString getContent();
  void setContent(QString content);
};

struct AdmonitionBlock : public Block {
  Q_GADGET
  public:
  AdmonitionBlock() = default;
  AdmonitionBlock(sem::SemId<sem::Org> const& id) : Block(id) {}
};

struct Call : public Org {
  Q_GADGET
  public:
  Call() = default;
  Call(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Code : public Block {
  Q_GADGET
  public:
  Code() = default;
  Code(sem::SemId<sem::Org> const& id) : Block(id) {}
  Q_PROPERTY( sem::Code::Exports exports READ getExports WRITE setExports )
  Q_PROPERTY( bool cache READ getCache WRITE setCache )
  Q_PROPERTY( bool eval READ getEval WRITE setEval )
  Q_PROPERTY( bool noweb READ getNoweb WRITE setNoweb )
  Q_PROPERTY( bool hlines READ getHlines WRITE setHlines )
  Q_PROPERTY( bool tangle READ getTangle WRITE setTangle )
  sem::Code::Exports getExports();
  void setExports(sem::Code::Exports exports);
  bool getCache();
  void setCache(bool cache);
  bool getEval();
  void setEval(bool eval);
  bool getNoweb();
  void setNoweb(bool noweb);
  bool getHlines();
  void setHlines(bool hlines);
  bool getTangle();
  void setTangle(bool tangle);
};

struct Time : public Org {
  Q_GADGET
  public:
  Time() = default;
  Time(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( bool isActive READ getIsActive WRITE setIsActive )
  Q_PROPERTY( sem::Time::TimeVariant time READ getTime WRITE setTime )
  bool getIsActive();
  void setIsActive(bool isActive);
  sem::Time::TimeVariant getTime();
  void setTime(sem::Time::TimeVariant time);
};

struct TimeRange : public Org {
  Q_GADGET
  public:
  TimeRange() = default;
  TimeRange(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( org_qml::Time from READ getFrom WRITE setFrom )
  Q_PROPERTY( org_qml::Time to READ getTo WRITE setTo )
  org_qml::Time getFrom();
  void setFrom(org_qml::Time from);
  org_qml::Time getTo();
  void setTo(org_qml::Time to);
};

struct Macro : public Org {
  Q_GADGET
  public:
  Macro() = default;
  Macro(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( QString name READ getName WRITE setName )
  QString getName();
  void setName(QString name);
};

struct Symbol : public Org {
  Q_GADGET
  public:
  Symbol() = default;
  Symbol(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( QString name READ getName WRITE setName )
  QString getName();
  void setName(QString name);
};

struct SubtreeLog : public Org {
  Q_GADGET
  public:
  SubtreeLog() = default;
  SubtreeLog(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( sem::SubtreeLog::LogEntry log READ getLog WRITE setLog )
  sem::SubtreeLog::LogEntry getLog();
  void setLog(sem::SubtreeLog::LogEntry log);
};

struct Subtree : public Org {
  Q_GADGET
  public:
  Subtree() = default;
  Subtree(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( int level READ getLevel WRITE setLevel )
  Q_PROPERTY( org_qml::Paragraph title READ getTitle WRITE setTitle )
  int getLevel();
  void setLevel(int level);
  org_qml::Paragraph getTitle();
  void setTitle(org_qml::Paragraph title);
};

struct LatexBody : public Org {
  Q_GADGET
  public:
  LatexBody() = default;
  LatexBody(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct InlineMath : public LatexBody {
  Q_GADGET
  public:
  InlineMath() = default;
  InlineMath(sem::SemId<sem::Org> const& id) : LatexBody(id) {}
};

struct Leaf : public Org {
  Q_GADGET
  public:
  Leaf() = default;
  Leaf(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( QString text READ getText WRITE setText )
  QString getText();
  void setText(QString text);
};

struct Escaped : public Leaf {
  Q_GADGET
  public:
  Escaped() = default;
  Escaped(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Newline : public Leaf {
  Q_GADGET
  public:
  Newline() = default;
  Newline(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Space : public Leaf {
  Q_GADGET
  public:
  Space() = default;
  Space(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Word : public Leaf {
  Q_GADGET
  public:
  Word() = default;
  Word(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct AtMention : public Leaf {
  Q_GADGET
  public:
  AtMention() = default;
  AtMention(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct RawText : public Leaf {
  Q_GADGET
  public:
  RawText() = default;
  RawText(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Punctuation : public Leaf {
  Q_GADGET
  public:
  Punctuation() = default;
  Punctuation(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Placeholder : public Leaf {
  Q_GADGET
  public:
  Placeholder() = default;
  Placeholder(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct BigIdent : public Leaf {
  Q_GADGET
  public:
  BigIdent() = default;
  BigIdent(sem::SemId<sem::Org> const& id) : Leaf(id) {}
};

struct Markup : public Org {
  Q_GADGET
  public:
  Markup() = default;
  Markup(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Bold : public Markup {
  Q_GADGET
  public:
  Bold() = default;
  Bold(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Underline : public Markup {
  Q_GADGET
  public:
  Underline() = default;
  Underline(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Monospace : public Markup {
  Q_GADGET
  public:
  Monospace() = default;
  Monospace(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct MarkQuote : public Markup {
  Q_GADGET
  public:
  MarkQuote() = default;
  MarkQuote(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Verbatim : public Markup {
  Q_GADGET
  public:
  Verbatim() = default;
  Verbatim(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Italic : public Markup {
  Q_GADGET
  public:
  Italic() = default;
  Italic(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Strike : public Markup {
  Q_GADGET
  public:
  Strike() = default;
  Strike(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct Par : public Markup {
  Q_GADGET
  public:
  Par() = default;
  Par(sem::SemId<sem::Org> const& id) : Markup(id) {}
};

struct List : public Org {
  Q_GADGET
  public:
  List() = default;
  List(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct ListItem : public Org {
  Q_GADGET
  public:
  ListItem() = default;
  ListItem(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( sem::ListItem::Checkbox checkbox READ getCheckbox WRITE setCheckbox )
  sem::ListItem::Checkbox getCheckbox();
  void setCheckbox(sem::ListItem::Checkbox checkbox);
};

struct Link : public Org {
  Q_GADGET
  public:
  Link() = default;
  Link(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( sem::Link::Data data READ getData WRITE setData )
  sem::Link::Data getData();
  void setData(sem::Link::Data data);
};

struct DocumentOptions : public Org {
  Q_GADGET
  public:
  DocumentOptions() = default;
  DocumentOptions(sem::SemId<sem::Org> const& id) : Org(id) {}
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
  sem::DocumentOptions::BrokenLinks getBrokenLinks();
  void setBrokenLinks(sem::DocumentOptions::BrokenLinks brokenLinks);
  sem::DocumentOptions::Visibility getInitialVisibility();
  void setInitialVisibility(sem::DocumentOptions::Visibility initialVisibility);
  sem::DocumentOptions::TocExport getTocExport();
  void setTocExport(sem::DocumentOptions::TocExport tocExport);
  bool getSmartQuotes();
  void setSmartQuotes(bool smartQuotes);
  bool getEmphasizedText();
  void setEmphasizedText(bool emphasizedText);
  bool getSpecialStrings();
  void setSpecialStrings(bool specialStrings);
  bool getFixedWidthSections();
  void setFixedWidthSections(bool fixedWidthSections);
  bool getIncludeTimestamps();
  void setIncludeTimestamps(bool includeTimestamps);
  bool getPreserveLineBreaks();
  void setPreserveLineBreaks(bool preserveLineBreaks);
  bool getPlaintextSubscripts();
  void setPlaintextSubscripts(bool plaintextSubscripts);
  bool getExportArchived();
  void setExportArchived(bool exportArchived);
  bool getExportWithAuthor();
  void setExportWithAuthor(bool exportWithAuthor);
  bool getExportBrokenLinks();
  void setExportBrokenLinks(bool exportBrokenLinks);
  bool getExportWithClock();
  void setExportWithClock(bool exportWithClock);
  bool getExportWithCreator();
  void setExportWithCreator(bool exportWithCreator);
  sem::DocumentOptions::TocExport getData();
  void setData(sem::DocumentOptions::TocExport data);
};

struct Document : public Org {
  Q_GADGET
  public:
  Document() = default;
  Document(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( org_qml::DocumentOptions options READ getOptions WRITE setOptions )
  org_qml::DocumentOptions getOptions();
  void setOptions(org_qml::DocumentOptions options);
};

struct ParseError : public Org {
  Q_GADGET
  public:
  ParseError() = default;
  ParseError(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct FileTarget : public Org {
  Q_GADGET
  public:
  FileTarget() = default;
  FileTarget(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( QString path READ getPath WRITE setPath )
  Q_PROPERTY( bool restrictToHeadlines READ getRestrictToHeadlines WRITE setRestrictToHeadlines )
  QString getPath();
  void setPath(QString path);
  bool getRestrictToHeadlines();
  void setRestrictToHeadlines(bool restrictToHeadlines);
};

struct TextSeparator : public Org {
  Q_GADGET
  public:
  TextSeparator() = default;
  TextSeparator(sem::SemId<sem::Org> const& id) : Org(id) {}
};

struct Include : public Org {
  Q_GADGET
  public:
  Include() = default;
  Include(sem::SemId<sem::Org> const& id) : Org(id) {}
  Q_PROPERTY( sem::Include::Data data READ getData WRITE setData )
  sem::Include::Data getData();
  void setData(sem::Include::Data data);
};

struct DocumentGroup : public Org {
  Q_GADGET
  public:
  DocumentGroup() = default;
  DocumentGroup(sem::SemId<sem::Org> const& id) : Org(id) {}
};

}
Q_DECLARE_METATYPE(org_qml::LineCol)
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
Q_DECLARE_METATYPE(org_qml::CmdName)
Q_DECLARE_METATYPE(org_qml::CmdResults)
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
Q_DECLARE_METATYPE(org_qml::Call)
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
Q_DECLARE_METATYPE(org_qml::DocumentOptions)
Q_DECLARE_METATYPE(org_qml::Document)
Q_DECLARE_METATYPE(org_qml::ParseError)
Q_DECLARE_METATYPE(org_qml::FileTarget)
Q_DECLARE_METATYPE(org_qml::TextSeparator)
Q_DECLARE_METATYPE(org_qml::Include)
Q_DECLARE_METATYPE(org_qml::DocumentGroup)
/* clang-format on */