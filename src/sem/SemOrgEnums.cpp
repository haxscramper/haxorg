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
  if (value == "Urgency") { return OrgSpecName::Urgency; } else
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
    case OrgSpecName::Urgency: return "Urgency";
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
  if (value == "UserNode") { return OrgNodeKind::UserNode; } else
  if (value == "Empty") { return OrgNodeKind::Empty; } else
  if (value == "Error") { return OrgNodeKind::Error; } else
  if (value == "ErrorTerminator") { return OrgNodeKind::ErrorTerminator; } else
  if (value == "ErrorToken") { return OrgNodeKind::ErrorToken; } else
  if (value == "InlineStmtList") { return OrgNodeKind::InlineStmtList; } else
  if (value == "StmtList") { return OrgNodeKind::StmtList; } else
  if (value == "AssocStmtList") { return OrgNodeKind::AssocStmtList; } else
  if (value == "Subtree") { return OrgNodeKind::Subtree; } else
  if (value == "SubtreeTimes") { return OrgNodeKind::SubtreeTimes; } else
  if (value == "SubtreeStars") { return OrgNodeKind::SubtreeStars; } else
  if (value == "Completion") { return OrgNodeKind::Completion; } else
  if (value == "Checkbox") { return OrgNodeKind::Checkbox; } else
  if (value == "List") { return OrgNodeKind::List; } else
  if (value == "Bullet") { return OrgNodeKind::Bullet; } else
  if (value == "ListItem") { return OrgNodeKind::ListItem; } else
  if (value == "ListTag") { return OrgNodeKind::ListTag; } else
  if (value == "Counter") { return OrgNodeKind::Counter; } else
  if (value == "Comment") { return OrgNodeKind::Comment; } else
  if (value == "RawText") { return OrgNodeKind::RawText; } else
  if (value == "Unparsed") { return OrgNodeKind::Unparsed; } else
  if (value == "Command") { return OrgNodeKind::Command; } else
  if (value == "CommandArguments") { return OrgNodeKind::CommandArguments; } else
  if (value == "CommandTitle") { return OrgNodeKind::CommandTitle; } else
  if (value == "CommandAuthor") { return OrgNodeKind::CommandAuthor; } else
  if (value == "CommandCreator") { return OrgNodeKind::CommandCreator; } else
  if (value == "CommandInclude") { return OrgNodeKind::CommandInclude; } else
  if (value == "CommandLanguage") { return OrgNodeKind::CommandLanguage; } else
  if (value == "CommandAttr") { return OrgNodeKind::CommandAttr; } else
  if (value == "CommandStartup") { return OrgNodeKind::CommandStartup; } else
  if (value == "CommandName") { return OrgNodeKind::CommandName; } else
  if (value == "CommandResults") { return OrgNodeKind::CommandResults; } else
  if (value == "CommandHeader") { return OrgNodeKind::CommandHeader; } else
  if (value == "CommandOptions") { return OrgNodeKind::CommandOptions; } else
  if (value == "CommandTblfm") { return OrgNodeKind::CommandTblfm; } else
  if (value == "CommandBackendOptions") { return OrgNodeKind::CommandBackendOptions; } else
  if (value == "AttrImg") { return OrgNodeKind::AttrImg; } else
  if (value == "CommandCaption") { return OrgNodeKind::CommandCaption; } else
  if (value == "File") { return OrgNodeKind::File; } else
  if (value == "BlockExport") { return OrgNodeKind::BlockExport; } else
  if (value == "InlineExport") { return OrgNodeKind::InlineExport; } else
  if (value == "MultilineCommand") { return OrgNodeKind::MultilineCommand; } else
  if (value == "Result") { return OrgNodeKind::Result; } else
  if (value == "Ident") { return OrgNodeKind::Ident; } else
  if (value == "BareIdent") { return OrgNodeKind::BareIdent; } else
  if (value == "AdmonitionTag") { return OrgNodeKind::AdmonitionTag; } else
  if (value == "BigIdent") { return OrgNodeKind::BigIdent; } else
  if (value == "VerbatimMultilineBlock") { return OrgNodeKind::VerbatimMultilineBlock; } else
  if (value == "CodeLine") { return OrgNodeKind::CodeLine; } else
  if (value == "CodeText") { return OrgNodeKind::CodeText; } else
  if (value == "CodeTangle") { return OrgNodeKind::CodeTangle; } else
  if (value == "CodeCallout") { return OrgNodeKind::CodeCallout; } else
  if (value == "QuoteBlock") { return OrgNodeKind::QuoteBlock; } else
  if (value == "AdmonitionBlock") { return OrgNodeKind::AdmonitionBlock; } else
  if (value == "CenterBlock") { return OrgNodeKind::CenterBlock; } else
  if (value == "VerseBlock") { return OrgNodeKind::VerseBlock; } else
  if (value == "Example") { return OrgNodeKind::Example; } else
  if (value == "SrcCode") { return OrgNodeKind::SrcCode; } else
  if (value == "SrcInlineCode") { return OrgNodeKind::SrcInlineCode; } else
  if (value == "InlineCallCode") { return OrgNodeKind::InlineCallCode; } else
  if (value == "CmdCallCode") { return OrgNodeKind::CmdCallCode; } else
  if (value == "PassCode") { return OrgNodeKind::PassCode; } else
  if (value == "CmdArguments") { return OrgNodeKind::CmdArguments; } else
  if (value == "CmdFlag") { return OrgNodeKind::CmdFlag; } else
  if (value == "CmdKey") { return OrgNodeKind::CmdKey; } else
  if (value == "CmdValue") { return OrgNodeKind::CmdValue; } else
  if (value == "CmdNamedValue") { return OrgNodeKind::CmdNamedValue; } else
  if (value == "UrgencyStatus") { return OrgNodeKind::UrgencyStatus; } else
  if (value == "TextSeparator") { return OrgNodeKind::TextSeparator; } else
  if (value == "Paragraph") { return OrgNodeKind::Paragraph; } else
  if (value == "AnnotatedParagraph") { return OrgNodeKind::AnnotatedParagraph; } else
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
  if (value == "BackendRaw") { return OrgNodeKind::BackendRaw; } else
  if (value == "Symbol") { return OrgNodeKind::Symbol; } else
  if (value == "TimeAssoc") { return OrgNodeKind::TimeAssoc; } else
  if (value == "StaticActiveTime") { return OrgNodeKind::StaticActiveTime; } else
  if (value == "StaticInactiveTime") { return OrgNodeKind::StaticInactiveTime; } else
  if (value == "DynamicActiveTime") { return OrgNodeKind::DynamicActiveTime; } else
  if (value == "DynamicInactiveTime") { return OrgNodeKind::DynamicInactiveTime; } else
  if (value == "TimeRange") { return OrgNodeKind::TimeRange; } else
  if (value == "SimpleTime") { return OrgNodeKind::SimpleTime; } else
  if (value == "Details") { return OrgNodeKind::Details; } else
  if (value == "Summary") { return OrgNodeKind::Summary; } else
  if (value == "Table") { return OrgNodeKind::Table; } else
  if (value == "TableRow") { return OrgNodeKind::TableRow; } else
  if (value == "TableCell") { return OrgNodeKind::TableCell; } else
  if (value == "InlineFootnote") { return OrgNodeKind::InlineFootnote; } else
  if (value == "Footnote") { return OrgNodeKind::Footnote; } else
  if (value == "Horizontal") { return OrgNodeKind::Horizontal; } else
  if (value == "Filetags") { return OrgNodeKind::Filetags; } else
  if (value == "OrgTag") { return OrgNodeKind::OrgTag; } else
  if (value == "HashTag") { return OrgNodeKind::HashTag; } else
  if (value == "MetaSymbol") { return OrgNodeKind::MetaSymbol; } else
  if (value == "AtMention") { return OrgNodeKind::AtMention; } else
  if (value == "BracTag") { return OrgNodeKind::BracTag; } else
  if (value == "Drawer") { return OrgNodeKind::Drawer; } else
  if (value == "LatexClass") { return OrgNodeKind::LatexClass; } else
  if (value == "LatexHeader") { return OrgNodeKind::LatexHeader; } else
  if (value == "LatexCompiler") { return OrgNodeKind::LatexCompiler; } else
  if (value == "LatexClassOptions") { return OrgNodeKind::LatexClassOptions; } else
  if (value == "HtmlHead") { return OrgNodeKind::HtmlHead; } else
  if (value == "Columns") { return OrgNodeKind::Columns; } else
  if (value == "CmdPropertyArgs") { return OrgNodeKind::CmdPropertyArgs; } else
  if (value == "CmdPropertyText") { return OrgNodeKind::CmdPropertyText; } else
  if (value == "CmdPropertyRaw") { return OrgNodeKind::CmdPropertyRaw; } else
  if (value == "PropertyList") { return OrgNodeKind::PropertyList; } else
  if (value == "Property") { return OrgNodeKind::Property; } else
  if (value == "Placeholder") { return OrgNodeKind::Placeholder; } else
  if (value == "SubtreeDescription") { return OrgNodeKind::SubtreeDescription; } else
  if (value == "SubtreeUrgency") { return OrgNodeKind::SubtreeUrgency; } else
  if (value == "Logbook") { return OrgNodeKind::Logbook; } else
  if (value == "LogbookStateChange") { return OrgNodeKind::LogbookStateChange; } else
  if (value == "RadioTarget") { return OrgNodeKind::RadioTarget; } else
  if (value == "Target") { return OrgNodeKind::Target; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgNodeKind>::to_string(OrgNodeKind value) {
  switch (value) {
    case OrgNodeKind::None: return "None";
    case OrgNodeKind::Document: return "Document";
    case OrgNodeKind::UserNode: return "UserNode";
    case OrgNodeKind::Empty: return "Empty";
    case OrgNodeKind::Error: return "Error";
    case OrgNodeKind::ErrorTerminator: return "ErrorTerminator";
    case OrgNodeKind::ErrorToken: return "ErrorToken";
    case OrgNodeKind::InlineStmtList: return "InlineStmtList";
    case OrgNodeKind::StmtList: return "StmtList";
    case OrgNodeKind::AssocStmtList: return "AssocStmtList";
    case OrgNodeKind::Subtree: return "Subtree";
    case OrgNodeKind::SubtreeTimes: return "SubtreeTimes";
    case OrgNodeKind::SubtreeStars: return "SubtreeStars";
    case OrgNodeKind::Completion: return "Completion";
    case OrgNodeKind::Checkbox: return "Checkbox";
    case OrgNodeKind::List: return "List";
    case OrgNodeKind::Bullet: return "Bullet";
    case OrgNodeKind::ListItem: return "ListItem";
    case OrgNodeKind::ListTag: return "ListTag";
    case OrgNodeKind::Counter: return "Counter";
    case OrgNodeKind::Comment: return "Comment";
    case OrgNodeKind::RawText: return "RawText";
    case OrgNodeKind::Unparsed: return "Unparsed";
    case OrgNodeKind::Command: return "Command";
    case OrgNodeKind::CommandArguments: return "CommandArguments";
    case OrgNodeKind::CommandTitle: return "CommandTitle";
    case OrgNodeKind::CommandAuthor: return "CommandAuthor";
    case OrgNodeKind::CommandCreator: return "CommandCreator";
    case OrgNodeKind::CommandInclude: return "CommandInclude";
    case OrgNodeKind::CommandLanguage: return "CommandLanguage";
    case OrgNodeKind::CommandAttr: return "CommandAttr";
    case OrgNodeKind::CommandStartup: return "CommandStartup";
    case OrgNodeKind::CommandName: return "CommandName";
    case OrgNodeKind::CommandResults: return "CommandResults";
    case OrgNodeKind::CommandHeader: return "CommandHeader";
    case OrgNodeKind::CommandOptions: return "CommandOptions";
    case OrgNodeKind::CommandTblfm: return "CommandTblfm";
    case OrgNodeKind::CommandBackendOptions: return "CommandBackendOptions";
    case OrgNodeKind::AttrImg: return "AttrImg";
    case OrgNodeKind::CommandCaption: return "CommandCaption";
    case OrgNodeKind::File: return "File";
    case OrgNodeKind::BlockExport: return "BlockExport";
    case OrgNodeKind::InlineExport: return "InlineExport";
    case OrgNodeKind::MultilineCommand: return "MultilineCommand";
    case OrgNodeKind::Result: return "Result";
    case OrgNodeKind::Ident: return "Ident";
    case OrgNodeKind::BareIdent: return "BareIdent";
    case OrgNodeKind::AdmonitionTag: return "AdmonitionTag";
    case OrgNodeKind::BigIdent: return "BigIdent";
    case OrgNodeKind::VerbatimMultilineBlock: return "VerbatimMultilineBlock";
    case OrgNodeKind::CodeLine: return "CodeLine";
    case OrgNodeKind::CodeText: return "CodeText";
    case OrgNodeKind::CodeTangle: return "CodeTangle";
    case OrgNodeKind::CodeCallout: return "CodeCallout";
    case OrgNodeKind::QuoteBlock: return "QuoteBlock";
    case OrgNodeKind::AdmonitionBlock: return "AdmonitionBlock";
    case OrgNodeKind::CenterBlock: return "CenterBlock";
    case OrgNodeKind::VerseBlock: return "VerseBlock";
    case OrgNodeKind::Example: return "Example";
    case OrgNodeKind::SrcCode: return "SrcCode";
    case OrgNodeKind::SrcInlineCode: return "SrcInlineCode";
    case OrgNodeKind::InlineCallCode: return "InlineCallCode";
    case OrgNodeKind::CmdCallCode: return "CmdCallCode";
    case OrgNodeKind::PassCode: return "PassCode";
    case OrgNodeKind::CmdArguments: return "CmdArguments";
    case OrgNodeKind::CmdFlag: return "CmdFlag";
    case OrgNodeKind::CmdKey: return "CmdKey";
    case OrgNodeKind::CmdValue: return "CmdValue";
    case OrgNodeKind::CmdNamedValue: return "CmdNamedValue";
    case OrgNodeKind::UrgencyStatus: return "UrgencyStatus";
    case OrgNodeKind::TextSeparator: return "TextSeparator";
    case OrgNodeKind::Paragraph: return "Paragraph";
    case OrgNodeKind::AnnotatedParagraph: return "AnnotatedParagraph";
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
    case OrgNodeKind::BackendRaw: return "BackendRaw";
    case OrgNodeKind::Symbol: return "Symbol";
    case OrgNodeKind::TimeAssoc: return "TimeAssoc";
    case OrgNodeKind::StaticActiveTime: return "StaticActiveTime";
    case OrgNodeKind::StaticInactiveTime: return "StaticInactiveTime";
    case OrgNodeKind::DynamicActiveTime: return "DynamicActiveTime";
    case OrgNodeKind::DynamicInactiveTime: return "DynamicInactiveTime";
    case OrgNodeKind::TimeRange: return "TimeRange";
    case OrgNodeKind::SimpleTime: return "SimpleTime";
    case OrgNodeKind::Details: return "Details";
    case OrgNodeKind::Summary: return "Summary";
    case OrgNodeKind::Table: return "Table";
    case OrgNodeKind::TableRow: return "TableRow";
    case OrgNodeKind::TableCell: return "TableCell";
    case OrgNodeKind::InlineFootnote: return "InlineFootnote";
    case OrgNodeKind::Footnote: return "Footnote";
    case OrgNodeKind::Horizontal: return "Horizontal";
    case OrgNodeKind::Filetags: return "Filetags";
    case OrgNodeKind::OrgTag: return "OrgTag";
    case OrgNodeKind::HashTag: return "HashTag";
    case OrgNodeKind::MetaSymbol: return "MetaSymbol";
    case OrgNodeKind::AtMention: return "AtMention";
    case OrgNodeKind::BracTag: return "BracTag";
    case OrgNodeKind::Drawer: return "Drawer";
    case OrgNodeKind::LatexClass: return "LatexClass";
    case OrgNodeKind::LatexHeader: return "LatexHeader";
    case OrgNodeKind::LatexCompiler: return "LatexCompiler";
    case OrgNodeKind::LatexClassOptions: return "LatexClassOptions";
    case OrgNodeKind::HtmlHead: return "HtmlHead";
    case OrgNodeKind::Columns: return "Columns";
    case OrgNodeKind::CmdPropertyArgs: return "CmdPropertyArgs";
    case OrgNodeKind::CmdPropertyText: return "CmdPropertyText";
    case OrgNodeKind::CmdPropertyRaw: return "CmdPropertyRaw";
    case OrgNodeKind::PropertyList: return "PropertyList";
    case OrgNodeKind::Property: return "Property";
    case OrgNodeKind::Placeholder: return "Placeholder";
    case OrgNodeKind::SubtreeDescription: return "SubtreeDescription";
    case OrgNodeKind::SubtreeUrgency: return "SubtreeUrgency";
    case OrgNodeKind::Logbook: return "Logbook";
    case OrgNodeKind::LogbookStateChange: return "LogbookStateChange";
    case OrgNodeKind::RadioTarget: return "RadioTarget";
    case OrgNodeKind::Target: return "Target";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<OrgSemKind> enum_serde<OrgSemKind>::from_string(std::string value) {
  if (value == "StmtList") { return OrgSemKind::StmtList; } else
  if (value == "Empty") { return OrgSemKind::Empty; } else
  if (value == "Cell") { return OrgSemKind::Cell; } else
  if (value == "Row") { return OrgSemKind::Row; } else
  if (value == "Table") { return OrgSemKind::Table; } else
  if (value == "HashTag") { return OrgSemKind::HashTag; } else
  if (value == "Footnote") { return OrgSemKind::Footnote; } else
  if (value == "Completion") { return OrgSemKind::Completion; } else
  if (value == "Paragraph") { return OrgSemKind::Paragraph; } else
  if (value == "AnnotatedParagraph") { return OrgSemKind::AnnotatedParagraph; } else
  if (value == "Center") { return OrgSemKind::Center; } else
  if (value == "Caption") { return OrgSemKind::Caption; } else
  if (value == "CmdName") { return OrgSemKind::CmdName; } else
  if (value == "CmdResults") { return OrgSemKind::CmdResults; } else
  if (value == "CommandGroup") { return OrgSemKind::CommandGroup; } else
  if (value == "Tblfm") { return OrgSemKind::Tblfm; } else
  if (value == "Quote") { return OrgSemKind::Quote; } else
  if (value == "Verse") { return OrgSemKind::Verse; } else
  if (value == "Example") { return OrgSemKind::Example; } else
  if (value == "CmdArguments") { return OrgSemKind::CmdArguments; } else
  if (value == "CmdAttr") { return OrgSemKind::CmdAttr; } else
  if (value == "CmdArgument") { return OrgSemKind::CmdArgument; } else
  if (value == "Export") { return OrgSemKind::Export; } else
  if (value == "AdmonitionBlock") { return OrgSemKind::AdmonitionBlock; } else
  if (value == "Call") { return OrgSemKind::Call; } else
  if (value == "Code") { return OrgSemKind::Code; } else
  if (value == "Time") { return OrgSemKind::Time; } else
  if (value == "TimeRange") { return OrgSemKind::TimeRange; } else
  if (value == "Macro") { return OrgSemKind::Macro; } else
  if (value == "Symbol") { return OrgSemKind::Symbol; } else
  if (value == "SubtreeLog") { return OrgSemKind::SubtreeLog; } else
  if (value == "Subtree") { return OrgSemKind::Subtree; } else
  if (value == "InlineMath") { return OrgSemKind::InlineMath; } else
  if (value == "Escaped") { return OrgSemKind::Escaped; } else
  if (value == "Newline") { return OrgSemKind::Newline; } else
  if (value == "Space") { return OrgSemKind::Space; } else
  if (value == "Word") { return OrgSemKind::Word; } else
  if (value == "AtMention") { return OrgSemKind::AtMention; } else
  if (value == "RawText") { return OrgSemKind::RawText; } else
  if (value == "Punctuation") { return OrgSemKind::Punctuation; } else
  if (value == "Placeholder") { return OrgSemKind::Placeholder; } else
  if (value == "BigIdent") { return OrgSemKind::BigIdent; } else
  if (value == "Bold") { return OrgSemKind::Bold; } else
  if (value == "Underline") { return OrgSemKind::Underline; } else
  if (value == "Monospace") { return OrgSemKind::Monospace; } else
  if (value == "MarkQuote") { return OrgSemKind::MarkQuote; } else
  if (value == "Verbatim") { return OrgSemKind::Verbatim; } else
  if (value == "Italic") { return OrgSemKind::Italic; } else
  if (value == "Strike") { return OrgSemKind::Strike; } else
  if (value == "Par") { return OrgSemKind::Par; } else
  if (value == "List") { return OrgSemKind::List; } else
  if (value == "ListItem") { return OrgSemKind::ListItem; } else
  if (value == "Link") { return OrgSemKind::Link; } else
  if (value == "DocumentOptions") { return OrgSemKind::DocumentOptions; } else
  if (value == "Document") { return OrgSemKind::Document; } else
  if (value == "ParseError") { return OrgSemKind::ParseError; } else
  if (value == "FileTarget") { return OrgSemKind::FileTarget; } else
  if (value == "TextSeparator") { return OrgSemKind::TextSeparator; } else
  if (value == "Include") { return OrgSemKind::Include; } else
  if (value == "DocumentGroup") { return OrgSemKind::DocumentGroup; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgSemKind>::to_string(OrgSemKind value) {
  switch (value) {
    case OrgSemKind::StmtList: return "StmtList";
    case OrgSemKind::Empty: return "Empty";
    case OrgSemKind::Cell: return "Cell";
    case OrgSemKind::Row: return "Row";
    case OrgSemKind::Table: return "Table";
    case OrgSemKind::HashTag: return "HashTag";
    case OrgSemKind::Footnote: return "Footnote";
    case OrgSemKind::Completion: return "Completion";
    case OrgSemKind::Paragraph: return "Paragraph";
    case OrgSemKind::AnnotatedParagraph: return "AnnotatedParagraph";
    case OrgSemKind::Center: return "Center";
    case OrgSemKind::Caption: return "Caption";
    case OrgSemKind::CmdName: return "CmdName";
    case OrgSemKind::CmdResults: return "CmdResults";
    case OrgSemKind::CommandGroup: return "CommandGroup";
    case OrgSemKind::Tblfm: return "Tblfm";
    case OrgSemKind::Quote: return "Quote";
    case OrgSemKind::Verse: return "Verse";
    case OrgSemKind::Example: return "Example";
    case OrgSemKind::CmdArguments: return "CmdArguments";
    case OrgSemKind::CmdAttr: return "CmdAttr";
    case OrgSemKind::CmdArgument: return "CmdArgument";
    case OrgSemKind::Export: return "Export";
    case OrgSemKind::AdmonitionBlock: return "AdmonitionBlock";
    case OrgSemKind::Call: return "Call";
    case OrgSemKind::Code: return "Code";
    case OrgSemKind::Time: return "Time";
    case OrgSemKind::TimeRange: return "TimeRange";
    case OrgSemKind::Macro: return "Macro";
    case OrgSemKind::Symbol: return "Symbol";
    case OrgSemKind::SubtreeLog: return "SubtreeLog";
    case OrgSemKind::Subtree: return "Subtree";
    case OrgSemKind::InlineMath: return "InlineMath";
    case OrgSemKind::Escaped: return "Escaped";
    case OrgSemKind::Newline: return "Newline";
    case OrgSemKind::Space: return "Space";
    case OrgSemKind::Word: return "Word";
    case OrgSemKind::AtMention: return "AtMention";
    case OrgSemKind::RawText: return "RawText";
    case OrgSemKind::Punctuation: return "Punctuation";
    case OrgSemKind::Placeholder: return "Placeholder";
    case OrgSemKind::BigIdent: return "BigIdent";
    case OrgSemKind::Bold: return "Bold";
    case OrgSemKind::Underline: return "Underline";
    case OrgSemKind::Monospace: return "Monospace";
    case OrgSemKind::MarkQuote: return "MarkQuote";
    case OrgSemKind::Verbatim: return "Verbatim";
    case OrgSemKind::Italic: return "Italic";
    case OrgSemKind::Strike: return "Strike";
    case OrgSemKind::Par: return "Par";
    case OrgSemKind::List: return "List";
    case OrgSemKind::ListItem: return "ListItem";
    case OrgSemKind::Link: return "Link";
    case OrgSemKind::DocumentOptions: return "DocumentOptions";
    case OrgSemKind::Document: return "Document";
    case OrgSemKind::ParseError: return "ParseError";
    case OrgSemKind::FileTarget: return "FileTarget";
    case OrgSemKind::TextSeparator: return "TextSeparator";
    case OrgSemKind::Include: return "Include";
    case OrgSemKind::DocumentGroup: return "DocumentGroup";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
/* clang-format on */