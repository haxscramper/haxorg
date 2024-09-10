/* clang-format off */
#include "SemOrgEnums.hpp"

Opt<OrgSpecName> enum_serde<OrgSpecName>::from_string(std::string value) {
  if (value == "Unnamed") { return OrgSpecName::Unnamed; } else
  if (value == "Result") { return OrgSpecName::Result; } else
  if (value == "Year") { return OrgSpecName::Year; } else
  if (value == "Day") { return OrgSpecName::Day; } else
  if (value == "Clock") { return OrgSpecName::Clock; } else
  if (value == "Repeater") { return OrgSpecName::Repeater; } else
  if (value == "Zone") { return OrgSpecName::Zone; } else
  if (value == "Link") { return OrgSpecName::Link; } else
  if (value == "Tags") { return OrgSpecName::Tags; } else
  if (value == "Tag") { return OrgSpecName::Tag; } else
  if (value == "State") { return OrgSpecName::State; } else
  if (value == "Protocol") { return OrgSpecName::Protocol; } else
  if (value == "Desc") { return OrgSpecName::Desc; } else
  if (value == "Times") { return OrgSpecName::Times; } else
  if (value == "Drawer") { return OrgSpecName::Drawer; } else
  if (value == "Args") { return OrgSpecName::Args; } else
  if (value == "Name") { return OrgSpecName::Name; } else
  if (value == "Definition") { return OrgSpecName::Definition; } else
  if (value == "Body") { return OrgSpecName::Body; } else
  if (value == "HeaderArgs") { return OrgSpecName::HeaderArgs; } else
  if (value == "File") { return OrgSpecName::File; } else
  if (value == "Kind") { return OrgSpecName::Kind; } else
  if (value == "Lang") { return OrgSpecName::Lang; } else
  if (value == "Prefix") { return OrgSpecName::Prefix; } else
  if (value == "Text") { return OrgSpecName::Text; } else
  if (value == "Todo") { return OrgSpecName::Todo; } else
  if (value == "Importance") { return OrgSpecName::Importance; } else
  if (value == "Title") { return OrgSpecName::Title; } else
  if (value == "Completion") { return OrgSpecName::Completion; } else
  if (value == "Head") { return OrgSpecName::Head; } else
  if (value == "Subnodes") { return OrgSpecName::Subnodes; } else
  if (value == "Properties") { return OrgSpecName::Properties; } else
  if (value == "Logbook") { return OrgSpecName::Logbook; } else
  if (value == "Description") { return OrgSpecName::Description; } else
  if (value == "Logs") { return OrgSpecName::Logs; } else
  if (value == "Newstate") { return OrgSpecName::Newstate; } else
  if (value == "Oldstate") { return OrgSpecName::Oldstate; } else
  if (value == "Time") { return OrgSpecName::Time; } else
  if (value == "From") { return OrgSpecName::From; } else
  if (value == "EndArgs") { return OrgSpecName::EndArgs; } else
  if (value == "Flags") { return OrgSpecName::Flags; } else
  if (value == "Value") { return OrgSpecName::Value; } else
  if (value == "Assoc") { return OrgSpecName::Assoc; } else
  if (value == "Main") { return OrgSpecName::Main; } else
  if (value == "Hash") { return OrgSpecName::Hash; } else
  if (value == "Bullet") { return OrgSpecName::Bullet; } else
  if (value == "Counter") { return OrgSpecName::Counter; } else
  if (value == "Checkbox") { return OrgSpecName::Checkbox; } else
  if (value == "Header") { return OrgSpecName::Header; } else
  if (value == "To") { return OrgSpecName::To; } else
  if (value == "Diff") { return OrgSpecName::Diff; } else
  if (value == "Property") { return OrgSpecName::Property; } else
  if (value == "Subname") { return OrgSpecName::Subname; } else
  if (value == "Values") { return OrgSpecName::Values; } else
  if (value == "Cells") { return OrgSpecName::Cells; } else
  if (value == "Rows") { return OrgSpecName::Rows; } else
  if (value == "Lines") { return OrgSpecName::Lines; } else
  if (value == "Chunks") { return OrgSpecName::Chunks; } else
  if (value == "InheritanceMode") { return OrgSpecName::InheritanceMode; } else
  if (value == "MainSetRule") { return OrgSpecName::MainSetRule; } else
  if (value == "SubSetRule") { return OrgSpecName::SubSetRule; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgSpecName>::to_string(OrgSpecName value) {
  switch (value) {
    case OrgSpecName::Unnamed: return "Unnamed";
    case OrgSpecName::Result: return "Result";
    case OrgSpecName::Year: return "Year";
    case OrgSpecName::Day: return "Day";
    case OrgSpecName::Clock: return "Clock";
    case OrgSpecName::Repeater: return "Repeater";
    case OrgSpecName::Zone: return "Zone";
    case OrgSpecName::Link: return "Link";
    case OrgSpecName::Tags: return "Tags";
    case OrgSpecName::Tag: return "Tag";
    case OrgSpecName::State: return "State";
    case OrgSpecName::Protocol: return "Protocol";
    case OrgSpecName::Desc: return "Desc";
    case OrgSpecName::Times: return "Times";
    case OrgSpecName::Drawer: return "Drawer";
    case OrgSpecName::Args: return "Args";
    case OrgSpecName::Name: return "Name";
    case OrgSpecName::Definition: return "Definition";
    case OrgSpecName::Body: return "Body";
    case OrgSpecName::HeaderArgs: return "HeaderArgs";
    case OrgSpecName::File: return "File";
    case OrgSpecName::Kind: return "Kind";
    case OrgSpecName::Lang: return "Lang";
    case OrgSpecName::Prefix: return "Prefix";
    case OrgSpecName::Text: return "Text";
    case OrgSpecName::Todo: return "Todo";
    case OrgSpecName::Importance: return "Importance";
    case OrgSpecName::Title: return "Title";
    case OrgSpecName::Completion: return "Completion";
    case OrgSpecName::Head: return "Head";
    case OrgSpecName::Subnodes: return "Subnodes";
    case OrgSpecName::Properties: return "Properties";
    case OrgSpecName::Logbook: return "Logbook";
    case OrgSpecName::Description: return "Description";
    case OrgSpecName::Logs: return "Logs";
    case OrgSpecName::Newstate: return "Newstate";
    case OrgSpecName::Oldstate: return "Oldstate";
    case OrgSpecName::Time: return "Time";
    case OrgSpecName::From: return "From";
    case OrgSpecName::EndArgs: return "EndArgs";
    case OrgSpecName::Flags: return "Flags";
    case OrgSpecName::Value: return "Value";
    case OrgSpecName::Assoc: return "Assoc";
    case OrgSpecName::Main: return "Main";
    case OrgSpecName::Hash: return "Hash";
    case OrgSpecName::Bullet: return "Bullet";
    case OrgSpecName::Counter: return "Counter";
    case OrgSpecName::Checkbox: return "Checkbox";
    case OrgSpecName::Header: return "Header";
    case OrgSpecName::To: return "To";
    case OrgSpecName::Diff: return "Diff";
    case OrgSpecName::Property: return "Property";
    case OrgSpecName::Subname: return "Subname";
    case OrgSpecName::Values: return "Values";
    case OrgSpecName::Cells: return "Cells";
    case OrgSpecName::Rows: return "Rows";
    case OrgSpecName::Lines: return "Lines";
    case OrgSpecName::Chunks: return "Chunks";
    case OrgSpecName::InheritanceMode: return "InheritanceMode";
    case OrgSpecName::MainSetRule: return "MainSetRule";
    case OrgSpecName::SubSetRule: return "SubSetRule";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<OrgNodeKind> enum_serde<OrgNodeKind>::from_string(std::string value) {
  if (value == "None") { return OrgNodeKind::None; } else
  if (value == "Document") { return OrgNodeKind::Document; } else
  if (value == "Empty") { return OrgNodeKind::Empty; } else
  if (value == "InlineStmtList") { return OrgNodeKind::InlineStmtList; } else
  if (value == "StmtList") { return OrgNodeKind::StmtList; } else
  if (value == "Checkbox") { return OrgNodeKind::Checkbox; } else
  if (value == "List") { return OrgNodeKind::List; } else
  if (value == "Bullet") { return OrgNodeKind::Bullet; } else
  if (value == "ListItem") { return OrgNodeKind::ListItem; } else
  if (value == "ListTag") { return OrgNodeKind::ListTag; } else
  if (value == "Counter") { return OrgNodeKind::Counter; } else
  if (value == "File") { return OrgNodeKind::File; } else
  if (value == "ColonExample") { return OrgNodeKind::ColonExample; } else
  if (value == "TextSeparator") { return OrgNodeKind::TextSeparator; } else
  if (value == "Paragraph") { return OrgNodeKind::Paragraph; } else
  if (value == "AnnotatedParagraph") { return OrgNodeKind::AnnotatedParagraph; } else
  if (value == "TableRow") { return OrgNodeKind::TableRow; } else
  if (value == "TableCell") { return OrgNodeKind::TableCell; } else
  if (value == "Table") { return OrgNodeKind::Table; } else
  if (value == "InlineFootnote") { return OrgNodeKind::InlineFootnote; } else
  if (value == "Footnote") { return OrgNodeKind::Footnote; } else
  if (value == "Cmd") { return OrgNodeKind::Cmd; } else
  if (value == "CmdArguments") { return OrgNodeKind::CmdArguments; } else
  if (value == "CmdTitle") { return OrgNodeKind::CmdTitle; } else
  if (value == "CmdAuthor") { return OrgNodeKind::CmdAuthor; } else
  if (value == "CmdCreator") { return OrgNodeKind::CmdCreator; } else
  if (value == "CmdInclude") { return OrgNodeKind::CmdInclude; } else
  if (value == "CmdLanguage") { return OrgNodeKind::CmdLanguage; } else
  if (value == "CmdAttr") { return OrgNodeKind::CmdAttr; } else
  if (value == "CmdStartup") { return OrgNodeKind::CmdStartup; } else
  if (value == "CmdName") { return OrgNodeKind::CmdName; } else
  if (value == "CmdCustomTextCommand") { return OrgNodeKind::CmdCustomTextCommand; } else
  if (value == "CmdCustomArgsCommand") { return OrgNodeKind::CmdCustomArgsCommand; } else
  if (value == "CmdCustomRawCommand") { return OrgNodeKind::CmdCustomRawCommand; } else
  if (value == "CmdResults") { return OrgNodeKind::CmdResults; } else
  if (value == "CmdHeader") { return OrgNodeKind::CmdHeader; } else
  if (value == "CmdOptions") { return OrgNodeKind::CmdOptions; } else
  if (value == "CmdTblfm") { return OrgNodeKind::CmdTblfm; } else
  if (value == "CmdCaption") { return OrgNodeKind::CmdCaption; } else
  if (value == "CmdResult") { return OrgNodeKind::CmdResult; } else
  if (value == "CmdCallCode") { return OrgNodeKind::CmdCallCode; } else
  if (value == "CmdFlag") { return OrgNodeKind::CmdFlag; } else
  if (value == "CmdKey") { return OrgNodeKind::CmdKey; } else
  if (value == "CmdValue") { return OrgNodeKind::CmdValue; } else
  if (value == "CmdNamedValue") { return OrgNodeKind::CmdNamedValue; } else
  if (value == "CmdLatexClass") { return OrgNodeKind::CmdLatexClass; } else
  if (value == "CmdLatexHeader") { return OrgNodeKind::CmdLatexHeader; } else
  if (value == "CmdLatexCompiler") { return OrgNodeKind::CmdLatexCompiler; } else
  if (value == "CmdLatexClassOptions") { return OrgNodeKind::CmdLatexClassOptions; } else
  if (value == "CmdHtmlHead") { return OrgNodeKind::CmdHtmlHead; } else
  if (value == "CmdColumns") { return OrgNodeKind::CmdColumns; } else
  if (value == "CmdPropertyArgs") { return OrgNodeKind::CmdPropertyArgs; } else
  if (value == "CmdPropertyText") { return OrgNodeKind::CmdPropertyText; } else
  if (value == "CmdPropertyRaw") { return OrgNodeKind::CmdPropertyRaw; } else
  if (value == "CmdFiletags") { return OrgNodeKind::CmdFiletags; } else
  if (value == "BlockVerbatimMultiline") { return OrgNodeKind::BlockVerbatimMultiline; } else
  if (value == "CodeLine") { return OrgNodeKind::CodeLine; } else
  if (value == "CodeText") { return OrgNodeKind::CodeText; } else
  if (value == "CodeTangle") { return OrgNodeKind::CodeTangle; } else
  if (value == "CodeCallout") { return OrgNodeKind::CodeCallout; } else
  if (value == "BlockCode") { return OrgNodeKind::BlockCode; } else
  if (value == "BlockQuote") { return OrgNodeKind::BlockQuote; } else
  if (value == "BlockComment") { return OrgNodeKind::BlockComment; } else
  if (value == "BlockCenter") { return OrgNodeKind::BlockCenter; } else
  if (value == "BlockVerse") { return OrgNodeKind::BlockVerse; } else
  if (value == "BlockExample") { return OrgNodeKind::BlockExample; } else
  if (value == "BlockExport") { return OrgNodeKind::BlockExport; } else
  if (value == "BlockDetails") { return OrgNodeKind::BlockDetails; } else
  if (value == "BlockSummary") { return OrgNodeKind::BlockSummary; } else
  if (value == "Ident") { return OrgNodeKind::Ident; } else
  if (value == "BigIdent") { return OrgNodeKind::BigIdent; } else
  if (value == "Bold") { return OrgNodeKind::Bold; } else
  if (value == "Italic") { return OrgNodeKind::Italic; } else
  if (value == "Verbatim") { return OrgNodeKind::Verbatim; } else
  if (value == "Backtick") { return OrgNodeKind::Backtick; } else
  if (value == "Underline") { return OrgNodeKind::Underline; } else
  if (value == "Strike") { return OrgNodeKind::Strike; } else
  if (value == "Quote") { return OrgNodeKind::Quote; } else
  if (value == "Angle") { return OrgNodeKind::Angle; } else
  if (value == "Monospace") { return OrgNodeKind::Monospace; } else
  if (value == "Par") { return OrgNodeKind::Par; } else
  if (value == "InlineMath") { return OrgNodeKind::InlineMath; } else
  if (value == "DisplayMath") { return OrgNodeKind::DisplayMath; } else
  if (value == "Space") { return OrgNodeKind::Space; } else
  if (value == "Punctuation") { return OrgNodeKind::Punctuation; } else
  if (value == "Colon") { return OrgNodeKind::Colon; } else
  if (value == "Word") { return OrgNodeKind::Word; } else
  if (value == "Escaped") { return OrgNodeKind::Escaped; } else
  if (value == "Newline") { return OrgNodeKind::Newline; } else
  if (value == "RawLink") { return OrgNodeKind::RawLink; } else
  if (value == "Link") { return OrgNodeKind::Link; } else
  if (value == "Macro") { return OrgNodeKind::Macro; } else
  if (value == "Symbol") { return OrgNodeKind::Symbol; } else
  if (value == "StaticActiveTime") { return OrgNodeKind::StaticActiveTime; } else
  if (value == "StaticInactiveTime") { return OrgNodeKind::StaticInactiveTime; } else
  if (value == "DynamicActiveTime") { return OrgNodeKind::DynamicActiveTime; } else
  if (value == "DynamicInactiveTime") { return OrgNodeKind::DynamicInactiveTime; } else
  if (value == "TimeRange") { return OrgNodeKind::TimeRange; } else
  if (value == "SimpleTime") { return OrgNodeKind::SimpleTime; } else
  if (value == "HashTag") { return OrgNodeKind::HashTag; } else
  if (value == "MetaSymbol") { return OrgNodeKind::MetaSymbol; } else
  if (value == "AtMention") { return OrgNodeKind::AtMention; } else
  if (value == "Placeholder") { return OrgNodeKind::Placeholder; } else
  if (value == "RadioTarget") { return OrgNodeKind::RadioTarget; } else
  if (value == "Target") { return OrgNodeKind::Target; } else
  if (value == "SrcInlineCode") { return OrgNodeKind::SrcInlineCode; } else
  if (value == "InlineCallCode") { return OrgNodeKind::InlineCallCode; } else
  if (value == "InlineExport") { return OrgNodeKind::InlineExport; } else
  if (value == "InlineComment") { return OrgNodeKind::InlineComment; } else
  if (value == "RawText") { return OrgNodeKind::RawText; } else
  if (value == "SubtreeDescription") { return OrgNodeKind::SubtreeDescription; } else
  if (value == "SubtreeUrgency") { return OrgNodeKind::SubtreeUrgency; } else
  if (value == "DrawerLogbook") { return OrgNodeKind::DrawerLogbook; } else
  if (value == "Drawer") { return OrgNodeKind::Drawer; } else
  if (value == "DrawerPropertyList") { return OrgNodeKind::DrawerPropertyList; } else
  if (value == "DrawerProperty") { return OrgNodeKind::DrawerProperty; } else
  if (value == "Subtree") { return OrgNodeKind::Subtree; } else
  if (value == "SubtreeTimes") { return OrgNodeKind::SubtreeTimes; } else
  if (value == "SubtreeStars") { return OrgNodeKind::SubtreeStars; } else
  if (value == "SubtreeCompletion") { return OrgNodeKind::SubtreeCompletion; } else
  if (value == "SubtreeImportance") { return OrgNodeKind::SubtreeImportance; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgNodeKind>::to_string(OrgNodeKind value) {
  switch (value) {
    case OrgNodeKind::None: return "None";
    case OrgNodeKind::Document: return "Document";
    case OrgNodeKind::Empty: return "Empty";
    case OrgNodeKind::InlineStmtList: return "InlineStmtList";
    case OrgNodeKind::StmtList: return "StmtList";
    case OrgNodeKind::Checkbox: return "Checkbox";
    case OrgNodeKind::List: return "List";
    case OrgNodeKind::Bullet: return "Bullet";
    case OrgNodeKind::ListItem: return "ListItem";
    case OrgNodeKind::ListTag: return "ListTag";
    case OrgNodeKind::Counter: return "Counter";
    case OrgNodeKind::File: return "File";
    case OrgNodeKind::ColonExample: return "ColonExample";
    case OrgNodeKind::TextSeparator: return "TextSeparator";
    case OrgNodeKind::Paragraph: return "Paragraph";
    case OrgNodeKind::AnnotatedParagraph: return "AnnotatedParagraph";
    case OrgNodeKind::TableRow: return "TableRow";
    case OrgNodeKind::TableCell: return "TableCell";
    case OrgNodeKind::Table: return "Table";
    case OrgNodeKind::InlineFootnote: return "InlineFootnote";
    case OrgNodeKind::Footnote: return "Footnote";
    case OrgNodeKind::Cmd: return "Cmd";
    case OrgNodeKind::CmdArguments: return "CmdArguments";
    case OrgNodeKind::CmdTitle: return "CmdTitle";
    case OrgNodeKind::CmdAuthor: return "CmdAuthor";
    case OrgNodeKind::CmdCreator: return "CmdCreator";
    case OrgNodeKind::CmdInclude: return "CmdInclude";
    case OrgNodeKind::CmdLanguage: return "CmdLanguage";
    case OrgNodeKind::CmdAttr: return "CmdAttr";
    case OrgNodeKind::CmdStartup: return "CmdStartup";
    case OrgNodeKind::CmdName: return "CmdName";
    case OrgNodeKind::CmdCustomTextCommand: return "CmdCustomTextCommand";
    case OrgNodeKind::CmdCustomArgsCommand: return "CmdCustomArgsCommand";
    case OrgNodeKind::CmdCustomRawCommand: return "CmdCustomRawCommand";
    case OrgNodeKind::CmdResults: return "CmdResults";
    case OrgNodeKind::CmdHeader: return "CmdHeader";
    case OrgNodeKind::CmdOptions: return "CmdOptions";
    case OrgNodeKind::CmdTblfm: return "CmdTblfm";
    case OrgNodeKind::CmdCaption: return "CmdCaption";
    case OrgNodeKind::CmdResult: return "CmdResult";
    case OrgNodeKind::CmdCallCode: return "CmdCallCode";
    case OrgNodeKind::CmdFlag: return "CmdFlag";
    case OrgNodeKind::CmdKey: return "CmdKey";
    case OrgNodeKind::CmdValue: return "CmdValue";
    case OrgNodeKind::CmdNamedValue: return "CmdNamedValue";
    case OrgNodeKind::CmdLatexClass: return "CmdLatexClass";
    case OrgNodeKind::CmdLatexHeader: return "CmdLatexHeader";
    case OrgNodeKind::CmdLatexCompiler: return "CmdLatexCompiler";
    case OrgNodeKind::CmdLatexClassOptions: return "CmdLatexClassOptions";
    case OrgNodeKind::CmdHtmlHead: return "CmdHtmlHead";
    case OrgNodeKind::CmdColumns: return "CmdColumns";
    case OrgNodeKind::CmdPropertyArgs: return "CmdPropertyArgs";
    case OrgNodeKind::CmdPropertyText: return "CmdPropertyText";
    case OrgNodeKind::CmdPropertyRaw: return "CmdPropertyRaw";
    case OrgNodeKind::CmdFiletags: return "CmdFiletags";
    case OrgNodeKind::BlockVerbatimMultiline: return "BlockVerbatimMultiline";
    case OrgNodeKind::CodeLine: return "CodeLine";
    case OrgNodeKind::CodeText: return "CodeText";
    case OrgNodeKind::CodeTangle: return "CodeTangle";
    case OrgNodeKind::CodeCallout: return "CodeCallout";
    case OrgNodeKind::BlockCode: return "BlockCode";
    case OrgNodeKind::BlockQuote: return "BlockQuote";
    case OrgNodeKind::BlockComment: return "BlockComment";
    case OrgNodeKind::BlockCenter: return "BlockCenter";
    case OrgNodeKind::BlockVerse: return "BlockVerse";
    case OrgNodeKind::BlockExample: return "BlockExample";
    case OrgNodeKind::BlockExport: return "BlockExport";
    case OrgNodeKind::BlockDetails: return "BlockDetails";
    case OrgNodeKind::BlockSummary: return "BlockSummary";
    case OrgNodeKind::Ident: return "Ident";
    case OrgNodeKind::BigIdent: return "BigIdent";
    case OrgNodeKind::Bold: return "Bold";
    case OrgNodeKind::Italic: return "Italic";
    case OrgNodeKind::Verbatim: return "Verbatim";
    case OrgNodeKind::Backtick: return "Backtick";
    case OrgNodeKind::Underline: return "Underline";
    case OrgNodeKind::Strike: return "Strike";
    case OrgNodeKind::Quote: return "Quote";
    case OrgNodeKind::Angle: return "Angle";
    case OrgNodeKind::Monospace: return "Monospace";
    case OrgNodeKind::Par: return "Par";
    case OrgNodeKind::InlineMath: return "InlineMath";
    case OrgNodeKind::DisplayMath: return "DisplayMath";
    case OrgNodeKind::Space: return "Space";
    case OrgNodeKind::Punctuation: return "Punctuation";
    case OrgNodeKind::Colon: return "Colon";
    case OrgNodeKind::Word: return "Word";
    case OrgNodeKind::Escaped: return "Escaped";
    case OrgNodeKind::Newline: return "Newline";
    case OrgNodeKind::RawLink: return "RawLink";
    case OrgNodeKind::Link: return "Link";
    case OrgNodeKind::Macro: return "Macro";
    case OrgNodeKind::Symbol: return "Symbol";
    case OrgNodeKind::StaticActiveTime: return "StaticActiveTime";
    case OrgNodeKind::StaticInactiveTime: return "StaticInactiveTime";
    case OrgNodeKind::DynamicActiveTime: return "DynamicActiveTime";
    case OrgNodeKind::DynamicInactiveTime: return "DynamicInactiveTime";
    case OrgNodeKind::TimeRange: return "TimeRange";
    case OrgNodeKind::SimpleTime: return "SimpleTime";
    case OrgNodeKind::HashTag: return "HashTag";
    case OrgNodeKind::MetaSymbol: return "MetaSymbol";
    case OrgNodeKind::AtMention: return "AtMention";
    case OrgNodeKind::Placeholder: return "Placeholder";
    case OrgNodeKind::RadioTarget: return "RadioTarget";
    case OrgNodeKind::Target: return "Target";
    case OrgNodeKind::SrcInlineCode: return "SrcInlineCode";
    case OrgNodeKind::InlineCallCode: return "InlineCallCode";
    case OrgNodeKind::InlineExport: return "InlineExport";
    case OrgNodeKind::InlineComment: return "InlineComment";
    case OrgNodeKind::RawText: return "RawText";
    case OrgNodeKind::SubtreeDescription: return "SubtreeDescription";
    case OrgNodeKind::SubtreeUrgency: return "SubtreeUrgency";
    case OrgNodeKind::DrawerLogbook: return "DrawerLogbook";
    case OrgNodeKind::Drawer: return "Drawer";
    case OrgNodeKind::DrawerPropertyList: return "DrawerPropertyList";
    case OrgNodeKind::DrawerProperty: return "DrawerProperty";
    case OrgNodeKind::Subtree: return "Subtree";
    case OrgNodeKind::SubtreeTimes: return "SubtreeTimes";
    case OrgNodeKind::SubtreeStars: return "SubtreeStars";
    case OrgNodeKind::SubtreeCompletion: return "SubtreeCompletion";
    case OrgNodeKind::SubtreeImportance: return "SubtreeImportance";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<OrgSemKind> enum_serde<OrgSemKind>::from_string(std::string value) {
  if (value == "None") { return OrgSemKind::None; } else
  if (value == "CmdArgument") { return OrgSemKind::CmdArgument; } else
  if (value == "CmdArgumentList") { return OrgSemKind::CmdArgumentList; } else
  if (value == "CmdArguments") { return OrgSemKind::CmdArguments; } else
  if (value == "ErrorItem") { return OrgSemKind::ErrorItem; } else
  if (value == "ErrorGroup") { return OrgSemKind::ErrorGroup; } else
  if (value == "StmtList") { return OrgSemKind::StmtList; } else
  if (value == "Empty") { return OrgSemKind::Empty; } else
  if (value == "CmdCaption") { return OrgSemKind::CmdCaption; } else
  if (value == "CmdName") { return OrgSemKind::CmdName; } else
  if (value == "CmdCustomArgs") { return OrgSemKind::CmdCustomArgs; } else
  if (value == "CmdCustomRaw") { return OrgSemKind::CmdCustomRaw; } else
  if (value == "CmdCustomText") { return OrgSemKind::CmdCustomText; } else
  if (value == "CmdResults") { return OrgSemKind::CmdResults; } else
  if (value == "CmdTblfm") { return OrgSemKind::CmdTblfm; } else
  if (value == "HashTag") { return OrgSemKind::HashTag; } else
  if (value == "Footnote") { return OrgSemKind::Footnote; } else
  if (value == "Time") { return OrgSemKind::Time; } else
  if (value == "TimeRange") { return OrgSemKind::TimeRange; } else
  if (value == "Macro") { return OrgSemKind::Macro; } else
  if (value == "Symbol") { return OrgSemKind::Symbol; } else
  if (value == "Escaped") { return OrgSemKind::Escaped; } else
  if (value == "Newline") { return OrgSemKind::Newline; } else
  if (value == "Space") { return OrgSemKind::Space; } else
  if (value == "Word") { return OrgSemKind::Word; } else
  if (value == "AtMention") { return OrgSemKind::AtMention; } else
  if (value == "RawText") { return OrgSemKind::RawText; } else
  if (value == "Punctuation") { return OrgSemKind::Punctuation; } else
  if (value == "Placeholder") { return OrgSemKind::Placeholder; } else
  if (value == "BigIdent") { return OrgSemKind::BigIdent; } else
  if (value == "RadioTarget") { return OrgSemKind::RadioTarget; } else
  if (value == "TextTarget") { return OrgSemKind::TextTarget; } else
  if (value == "Bold") { return OrgSemKind::Bold; } else
  if (value == "Underline") { return OrgSemKind::Underline; } else
  if (value == "Monospace") { return OrgSemKind::Monospace; } else
  if (value == "MarkQuote") { return OrgSemKind::MarkQuote; } else
  if (value == "Verbatim") { return OrgSemKind::Verbatim; } else
  if (value == "Italic") { return OrgSemKind::Italic; } else
  if (value == "Strike") { return OrgSemKind::Strike; } else
  if (value == "Par") { return OrgSemKind::Par; } else
  if (value == "Latex") { return OrgSemKind::Latex; } else
  if (value == "Link") { return OrgSemKind::Link; } else
  if (value == "BlockCenter") { return OrgSemKind::BlockCenter; } else
  if (value == "BlockQuote") { return OrgSemKind::BlockQuote; } else
  if (value == "BlockComment") { return OrgSemKind::BlockComment; } else
  if (value == "BlockVerse") { return OrgSemKind::BlockVerse; } else
  if (value == "BlockExample") { return OrgSemKind::BlockExample; } else
  if (value == "BlockExport") { return OrgSemKind::BlockExport; } else
  if (value == "BlockAdmonition") { return OrgSemKind::BlockAdmonition; } else
  if (value == "BlockCode") { return OrgSemKind::BlockCode; } else
  if (value == "SubtreeLog") { return OrgSemKind::SubtreeLog; } else
  if (value == "Subtree") { return OrgSemKind::Subtree; } else
  if (value == "SubtreeCompletion") { return OrgSemKind::SubtreeCompletion; } else
  if (value == "Cell") { return OrgSemKind::Cell; } else
  if (value == "Row") { return OrgSemKind::Row; } else
  if (value == "Table") { return OrgSemKind::Table; } else
  if (value == "Paragraph") { return OrgSemKind::Paragraph; } else
  if (value == "AnnotatedParagraph") { return OrgSemKind::AnnotatedParagraph; } else
  if (value == "ColonExample") { return OrgSemKind::ColonExample; } else
  if (value == "CmdAttr") { return OrgSemKind::CmdAttr; } else
  if (value == "Call") { return OrgSemKind::Call; } else
  if (value == "List") { return OrgSemKind::List; } else
  if (value == "ListItem") { return OrgSemKind::ListItem; } else
  if (value == "DocumentOptions") { return OrgSemKind::DocumentOptions; } else
  if (value == "Document") { return OrgSemKind::Document; } else
  if (value == "FileTarget") { return OrgSemKind::FileTarget; } else
  if (value == "TextSeparator") { return OrgSemKind::TextSeparator; } else
  if (value == "Include") { return OrgSemKind::Include; } else
  if (value == "DocumentGroup") { return OrgSemKind::DocumentGroup; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgSemKind>::to_string(OrgSemKind value) {
  switch (value) {
    case OrgSemKind::None: return "None";
    case OrgSemKind::CmdArgument: return "CmdArgument";
    case OrgSemKind::CmdArgumentList: return "CmdArgumentList";
    case OrgSemKind::CmdArguments: return "CmdArguments";
    case OrgSemKind::ErrorItem: return "ErrorItem";
    case OrgSemKind::ErrorGroup: return "ErrorGroup";
    case OrgSemKind::StmtList: return "StmtList";
    case OrgSemKind::Empty: return "Empty";
    case OrgSemKind::CmdCaption: return "CmdCaption";
    case OrgSemKind::CmdName: return "CmdName";
    case OrgSemKind::CmdCustomArgs: return "CmdCustomArgs";
    case OrgSemKind::CmdCustomRaw: return "CmdCustomRaw";
    case OrgSemKind::CmdCustomText: return "CmdCustomText";
    case OrgSemKind::CmdResults: return "CmdResults";
    case OrgSemKind::CmdTblfm: return "CmdTblfm";
    case OrgSemKind::HashTag: return "HashTag";
    case OrgSemKind::Footnote: return "Footnote";
    case OrgSemKind::Time: return "Time";
    case OrgSemKind::TimeRange: return "TimeRange";
    case OrgSemKind::Macro: return "Macro";
    case OrgSemKind::Symbol: return "Symbol";
    case OrgSemKind::Escaped: return "Escaped";
    case OrgSemKind::Newline: return "Newline";
    case OrgSemKind::Space: return "Space";
    case OrgSemKind::Word: return "Word";
    case OrgSemKind::AtMention: return "AtMention";
    case OrgSemKind::RawText: return "RawText";
    case OrgSemKind::Punctuation: return "Punctuation";
    case OrgSemKind::Placeholder: return "Placeholder";
    case OrgSemKind::BigIdent: return "BigIdent";
    case OrgSemKind::RadioTarget: return "RadioTarget";
    case OrgSemKind::TextTarget: return "TextTarget";
    case OrgSemKind::Bold: return "Bold";
    case OrgSemKind::Underline: return "Underline";
    case OrgSemKind::Monospace: return "Monospace";
    case OrgSemKind::MarkQuote: return "MarkQuote";
    case OrgSemKind::Verbatim: return "Verbatim";
    case OrgSemKind::Italic: return "Italic";
    case OrgSemKind::Strike: return "Strike";
    case OrgSemKind::Par: return "Par";
    case OrgSemKind::Latex: return "Latex";
    case OrgSemKind::Link: return "Link";
    case OrgSemKind::BlockCenter: return "BlockCenter";
    case OrgSemKind::BlockQuote: return "BlockQuote";
    case OrgSemKind::BlockComment: return "BlockComment";
    case OrgSemKind::BlockVerse: return "BlockVerse";
    case OrgSemKind::BlockExample: return "BlockExample";
    case OrgSemKind::BlockExport: return "BlockExport";
    case OrgSemKind::BlockAdmonition: return "BlockAdmonition";
    case OrgSemKind::BlockCode: return "BlockCode";
    case OrgSemKind::SubtreeLog: return "SubtreeLog";
    case OrgSemKind::Subtree: return "Subtree";
    case OrgSemKind::SubtreeCompletion: return "SubtreeCompletion";
    case OrgSemKind::Cell: return "Cell";
    case OrgSemKind::Row: return "Row";
    case OrgSemKind::Table: return "Table";
    case OrgSemKind::Paragraph: return "Paragraph";
    case OrgSemKind::AnnotatedParagraph: return "AnnotatedParagraph";
    case OrgSemKind::ColonExample: return "ColonExample";
    case OrgSemKind::CmdAttr: return "CmdAttr";
    case OrgSemKind::Call: return "Call";
    case OrgSemKind::List: return "List";
    case OrgSemKind::ListItem: return "ListItem";
    case OrgSemKind::DocumentOptions: return "DocumentOptions";
    case OrgSemKind::Document: return "Document";
    case OrgSemKind::FileTarget: return "FileTarget";
    case OrgSemKind::TextSeparator: return "TextSeparator";
    case OrgSemKind::Include: return "Include";
    case OrgSemKind::DocumentGroup: return "DocumentGroup";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
/* clang-format on */