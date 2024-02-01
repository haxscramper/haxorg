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
  if (value == "CommandAttrHtml") { return OrgNodeKind::CommandAttrHtml; } else
  if (value == "CommandName") { return OrgNodeKind::CommandName; } else
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
  if (value == "Example") { return OrgNodeKind::Example; } else
  if (value == "SrcCode") { return OrgNodeKind::SrcCode; } else
  if (value == "SrcInlineCode") { return OrgNodeKind::SrcInlineCode; } else
  if (value == "CallCode") { return OrgNodeKind::CallCode; } else
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
    case OrgNodeKind::CommandAttrHtml: return "CommandAttrHtml";
    case OrgNodeKind::CommandName: return "CommandName";
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
    case OrgNodeKind::Example: return "Example";
    case OrgNodeKind::SrcCode: return "SrcCode";
    case OrgNodeKind::SrcInlineCode: return "SrcInlineCode";
    case OrgNodeKind::CallCode: return "CallCode";
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

Opt<OrgBigIdentKind> enum_serde<OrgBigIdentKind>::from_string(std::string value) {
  if (value == "None") { return OrgBigIdentKind::None; } else
  if (value == "Must") { return OrgBigIdentKind::Must; } else
  if (value == "MustNot") { return OrgBigIdentKind::MustNot; } else
  if (value == "Should") { return OrgBigIdentKind::Should; } else
  if (value == "ShouldNot") { return OrgBigIdentKind::ShouldNot; } else
  if (value == "Required") { return OrgBigIdentKind::Required; } else
  if (value == "Optional") { return OrgBigIdentKind::Optional; } else
  if (value == "ReallyShouldNot") { return OrgBigIdentKind::ReallyShouldNot; } else
  if (value == "OughtTo") { return OrgBigIdentKind::OughtTo; } else
  if (value == "WouldProbably") { return OrgBigIdentKind::WouldProbably; } else
  if (value == "MayWishTo") { return OrgBigIdentKind::MayWishTo; } else
  if (value == "Could") { return OrgBigIdentKind::Could; } else
  if (value == "Might") { return OrgBigIdentKind::Might; } else
  if (value == "Possible") { return OrgBigIdentKind::Possible; } else
  if (value == "Todo") { return OrgBigIdentKind::Todo; } else
  if (value == "Idea") { return OrgBigIdentKind::Idea; } else
  if (value == "Error") { return OrgBigIdentKind::Error; } else
  if (value == "Fixme") { return OrgBigIdentKind::Fixme; } else
  if (value == "Doc") { return OrgBigIdentKind::Doc; } else
  if (value == "Refactor") { return OrgBigIdentKind::Refactor; } else
  if (value == "Review") { return OrgBigIdentKind::Review; } else
  if (value == "Hack") { return OrgBigIdentKind::Hack; } else
  if (value == "Implement") { return OrgBigIdentKind::Implement; } else
  if (value == "Example") { return OrgBigIdentKind::Example; } else
  if (value == "Question") { return OrgBigIdentKind::Question; } else
  if (value == "Assume") { return OrgBigIdentKind::Assume; } else
  if (value == "Internal") { return OrgBigIdentKind::Internal; } else
  if (value == "Design") { return OrgBigIdentKind::Design; } else
  if (value == "Why") { return OrgBigIdentKind::Why; } else
  if (value == "Wip") { return OrgBigIdentKind::Wip; } else
  if (value == "Fix") { return OrgBigIdentKind::Fix; } else
  if (value == "Clean") { return OrgBigIdentKind::Clean; } else
  if (value == "Feature") { return OrgBigIdentKind::Feature; } else
  if (value == "Style") { return OrgBigIdentKind::Style; } else
  if (value == "Repo") { return OrgBigIdentKind::Repo; } else
  if (value == "Skip") { return OrgBigIdentKind::Skip; } else
  if (value == "Break") { return OrgBigIdentKind::Break; } else
  if (value == "Poc") { return OrgBigIdentKind::Poc; } else
  if (value == "Next") { return OrgBigIdentKind::Next; } else
  if (value == "Later") { return OrgBigIdentKind::Later; } else
  if (value == "Postponed") { return OrgBigIdentKind::Postponed; } else
  if (value == "Stalled") { return OrgBigIdentKind::Stalled; } else
  if (value == "Done") { return OrgBigIdentKind::Done; } else
  if (value == "Partially") { return OrgBigIdentKind::Partially; } else
  if (value == "Cancelled") { return OrgBigIdentKind::Cancelled; } else
  if (value == "Failed") { return OrgBigIdentKind::Failed; } else
  if (value == "Note") { return OrgBigIdentKind::Note; } else
  if (value == "Tip") { return OrgBigIdentKind::Tip; } else
  if (value == "Important") { return OrgBigIdentKind::Important; } else
  if (value == "Caution") { return OrgBigIdentKind::Caution; } else
  if (value == "Warning") { return OrgBigIdentKind::Warning; } else
  if (value == "UserCodeComment") { return OrgBigIdentKind::UserCodeComment; } else
  if (value == "UserCommitMsg") { return OrgBigIdentKind::UserCommitMsg; } else
  if (value == "UserTaskState") { return OrgBigIdentKind::UserTaskState; } else
  if (value == "UserAdmonition") { return OrgBigIdentKind::UserAdmonition; } else
  if (value == "Other") { return OrgBigIdentKind::Other; } else
  if (value == "StructIf") { return OrgBigIdentKind::StructIf; } else
  if (value == "StructAnd") { return OrgBigIdentKind::StructAnd; } else
  if (value == "StructOr") { return OrgBigIdentKind::StructOr; } else
  if (value == "StructNot") { return OrgBigIdentKind::StructNot; } else
  if (value == "StructGet") { return OrgBigIdentKind::StructGet; } else
  if (value == "StructSet") { return OrgBigIdentKind::StructSet; } else
  if (value == "StructThen") { return OrgBigIdentKind::StructThen; } else
  if (value == "StructElse") { return OrgBigIdentKind::StructElse; } else
  if (value == "StructWhile") { return OrgBigIdentKind::StructWhile; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgBigIdentKind>::to_string(OrgBigIdentKind value) {
  switch (value) {
    case OrgBigIdentKind::None: return "None";
    case OrgBigIdentKind::Must: return "Must";
    case OrgBigIdentKind::MustNot: return "MustNot";
    case OrgBigIdentKind::Should: return "Should";
    case OrgBigIdentKind::ShouldNot: return "ShouldNot";
    case OrgBigIdentKind::Required: return "Required";
    case OrgBigIdentKind::Optional: return "Optional";
    case OrgBigIdentKind::ReallyShouldNot: return "ReallyShouldNot";
    case OrgBigIdentKind::OughtTo: return "OughtTo";
    case OrgBigIdentKind::WouldProbably: return "WouldProbably";
    case OrgBigIdentKind::MayWishTo: return "MayWishTo";
    case OrgBigIdentKind::Could: return "Could";
    case OrgBigIdentKind::Might: return "Might";
    case OrgBigIdentKind::Possible: return "Possible";
    case OrgBigIdentKind::Todo: return "Todo";
    case OrgBigIdentKind::Idea: return "Idea";
    case OrgBigIdentKind::Error: return "Error";
    case OrgBigIdentKind::Fixme: return "Fixme";
    case OrgBigIdentKind::Doc: return "Doc";
    case OrgBigIdentKind::Refactor: return "Refactor";
    case OrgBigIdentKind::Review: return "Review";
    case OrgBigIdentKind::Hack: return "Hack";
    case OrgBigIdentKind::Implement: return "Implement";
    case OrgBigIdentKind::Example: return "Example";
    case OrgBigIdentKind::Question: return "Question";
    case OrgBigIdentKind::Assume: return "Assume";
    case OrgBigIdentKind::Internal: return "Internal";
    case OrgBigIdentKind::Design: return "Design";
    case OrgBigIdentKind::Why: return "Why";
    case OrgBigIdentKind::Wip: return "Wip";
    case OrgBigIdentKind::Fix: return "Fix";
    case OrgBigIdentKind::Clean: return "Clean";
    case OrgBigIdentKind::Feature: return "Feature";
    case OrgBigIdentKind::Style: return "Style";
    case OrgBigIdentKind::Repo: return "Repo";
    case OrgBigIdentKind::Skip: return "Skip";
    case OrgBigIdentKind::Break: return "Break";
    case OrgBigIdentKind::Poc: return "Poc";
    case OrgBigIdentKind::Next: return "Next";
    case OrgBigIdentKind::Later: return "Later";
    case OrgBigIdentKind::Postponed: return "Postponed";
    case OrgBigIdentKind::Stalled: return "Stalled";
    case OrgBigIdentKind::Done: return "Done";
    case OrgBigIdentKind::Partially: return "Partially";
    case OrgBigIdentKind::Cancelled: return "Cancelled";
    case OrgBigIdentKind::Failed: return "Failed";
    case OrgBigIdentKind::Note: return "Note";
    case OrgBigIdentKind::Tip: return "Tip";
    case OrgBigIdentKind::Important: return "Important";
    case OrgBigIdentKind::Caution: return "Caution";
    case OrgBigIdentKind::Warning: return "Warning";
    case OrgBigIdentKind::UserCodeComment: return "UserCodeComment";
    case OrgBigIdentKind::UserCommitMsg: return "UserCommitMsg";
    case OrgBigIdentKind::UserTaskState: return "UserTaskState";
    case OrgBigIdentKind::UserAdmonition: return "UserAdmonition";
    case OrgBigIdentKind::Other: return "Other";
    case OrgBigIdentKind::StructIf: return "StructIf";
    case OrgBigIdentKind::StructAnd: return "StructAnd";
    case OrgBigIdentKind::StructOr: return "StructOr";
    case OrgBigIdentKind::StructNot: return "StructNot";
    case OrgBigIdentKind::StructGet: return "StructGet";
    case OrgBigIdentKind::StructSet: return "StructSet";
    case OrgBigIdentKind::StructThen: return "StructThen";
    case OrgBigIdentKind::StructElse: return "StructElse";
    case OrgBigIdentKind::StructWhile: return "StructWhile";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<OrgTokenKind> enum_serde<OrgTokenKind>::from_string(std::string value) {
  if (value == "None") { return OrgTokenKind::None; } else
  if (value == "Eof") { return OrgTokenKind::Eof; } else
  if (value == "CmdPrefix") { return OrgTokenKind::CmdPrefix; } else
  if (value == "CmdLine") { return OrgTokenKind::CmdLine; } else
  if (value == "CmdTitle") { return OrgTokenKind::CmdTitle; } else
  if (value == "CmdCaption") { return OrgTokenKind::CmdCaption; } else
  if (value == "CmdFiletags") { return OrgTokenKind::CmdFiletags; } else
  if (value == "CmdColumns") { return OrgTokenKind::CmdColumns; } else
  if (value == "CmdPropertyArgs") { return OrgTokenKind::CmdPropertyArgs; } else
  if (value == "CmdPropertyText") { return OrgTokenKind::CmdPropertyText; } else
  if (value == "CmdPropertyRaw") { return OrgTokenKind::CmdPropertyRaw; } else
  if (value == "CmdOptions") { return OrgTokenKind::CmdOptions; } else
  if (value == "CmdSetupfile") { return OrgTokenKind::CmdSetupfile; } else
  if (value == "CmdInclude") { return OrgTokenKind::CmdInclude; } else
  if (value == "CmdAttrLatex") { return OrgTokenKind::CmdAttrLatex; } else
  if (value == "CmdAttrImg") { return OrgTokenKind::CmdAttrImg; } else
  if (value == "CmdAttrHtml") { return OrgTokenKind::CmdAttrHtml; } else
  if (value == "CmdHtmlHead") { return OrgTokenKind::CmdHtmlHead; } else
  if (value == "CmdLanguage") { return OrgTokenKind::CmdLanguage; } else
  if (value == "CmdLatexClassOptions") { return OrgTokenKind::CmdLatexClassOptions; } else
  if (value == "CmdLatexClass") { return OrgTokenKind::CmdLatexClass; } else
  if (value == "CmdLatexCompiler") { return OrgTokenKind::CmdLatexCompiler; } else
  if (value == "CmdAuthor") { return OrgTokenKind::CmdAuthor; } else
  if (value == "CmdBind") { return OrgTokenKind::CmdBind; } else
  if (value == "CmdCreator") { return OrgTokenKind::CmdCreator; } else
  if (value == "CmdLatexHeader") { return OrgTokenKind::CmdLatexHeader; } else
  if (value == "CmdResults") { return OrgTokenKind::CmdResults; } else
  if (value == "CmdCall") { return OrgTokenKind::CmdCall; } else
  if (value == "CmdName") { return OrgTokenKind::CmdName; } else
  if (value == "CmdHeader") { return OrgTokenKind::CmdHeader; } else
  if (value == "CmdArgumentsBegin") { return OrgTokenKind::CmdArgumentsBegin; } else
  if (value == "CmdArgumentsEnd") { return OrgTokenKind::CmdArgumentsEnd; } else
  if (value == "CmdKey") { return OrgTokenKind::CmdKey; } else
  if (value == "CmdValue") { return OrgTokenKind::CmdValue; } else
  if (value == "CmdFlag") { return OrgTokenKind::CmdFlag; } else
  if (value == "CmdBracket") { return OrgTokenKind::CmdBracket; } else
  if (value == "CmdBegin") { return OrgTokenKind::CmdBegin; } else
  if (value == "CmdEnd") { return OrgTokenKind::CmdEnd; } else
  if (value == "CmdSrcBegin") { return OrgTokenKind::CmdSrcBegin; } else
  if (value == "CmdSrcEnd") { return OrgTokenKind::CmdSrcEnd; } else
  if (value == "CmdQuoteBegin") { return OrgTokenKind::CmdQuoteBegin; } else
  if (value == "CmdQuoteEnd") { return OrgTokenKind::CmdQuoteEnd; } else
  if (value == "CmdCenterBegin") { return OrgTokenKind::CmdCenterBegin; } else
  if (value == "CmdCenterEnd") { return OrgTokenKind::CmdCenterEnd; } else
  if (value == "CmdTableBegin") { return OrgTokenKind::CmdTableBegin; } else
  if (value == "CmdTableEnd") { return OrgTokenKind::CmdTableEnd; } else
  if (value == "CmdAdmonitionBegin") { return OrgTokenKind::CmdAdmonitionBegin; } else
  if (value == "CmdAdmonitionEnd") { return OrgTokenKind::CmdAdmonitionEnd; } else
  if (value == "CmdDynamicBegin") { return OrgTokenKind::CmdDynamicBegin; } else
  if (value == "CmdDynamicEnd") { return OrgTokenKind::CmdDynamicEnd; } else
  if (value == "CmdExampleBegin") { return OrgTokenKind::CmdExampleBegin; } else
  if (value == "CmdExampleEnd") { return OrgTokenKind::CmdExampleEnd; } else
  if (value == "CmdExportBegin") { return OrgTokenKind::CmdExportBegin; } else
  if (value == "CmdExportEnd") { return OrgTokenKind::CmdExportEnd; } else
  if (value == "CmdDetailsBegin") { return OrgTokenKind::CmdDetailsBegin; } else
  if (value == "CmdDetailsEnd") { return OrgTokenKind::CmdDetailsEnd; } else
  if (value == "CmdSummaryBegin") { return OrgTokenKind::CmdSummaryBegin; } else
  if (value == "CmdSummaryEnd") { return OrgTokenKind::CmdSummaryEnd; } else
  if (value == "CmdTblfm") { return OrgTokenKind::CmdTblfm; } else
  if (value == "QuoteContent") { return OrgTokenKind::QuoteContent; } else
  if (value == "CmdBackendPass") { return OrgTokenKind::CmdBackendPass; } else
  if (value == "CmdContentBegin") { return OrgTokenKind::CmdContentBegin; } else
  if (value == "CmdContentEnd") { return OrgTokenKind::CmdContentEnd; } else
  if (value == "CmdSrcCodeContent") { return OrgTokenKind::CmdSrcCodeContent; } else
  if (value == "CmdSrcTextBlock") { return OrgTokenKind::CmdSrcTextBlock; } else
  if (value == "TblContent") { return OrgTokenKind::TblContent; } else
  if (value == "TblBegin") { return OrgTokenKind::TblBegin; } else
  if (value == "TblEnd") { return OrgTokenKind::TblEnd; } else
  if (value == "TblCellBody") { return OrgTokenKind::TblCellBody; } else
  if (value == "TblRowSpec") { return OrgTokenKind::TblRowSpec; } else
  if (value == "TblCellSpec") { return OrgTokenKind::TblCellSpec; } else
  if (value == "TblPipeBegin") { return OrgTokenKind::TblPipeBegin; } else
  if (value == "TblPipeSeparator") { return OrgTokenKind::TblPipeSeparator; } else
  if (value == "TblPipeEnd") { return OrgTokenKind::TblPipeEnd; } else
  if (value == "TblPipeCellBegin") { return OrgTokenKind::TblPipeCellBegin; } else
  if (value == "TblDashSeparator") { return OrgTokenKind::TblDashSeparator; } else
  if (value == "TblCornerPlus") { return OrgTokenKind::TblCornerPlus; } else
  if (value == "TblCellContentBegin") { return OrgTokenKind::TblCellContentBegin; } else
  if (value == "TblCellContentEnd") { return OrgTokenKind::TblCellContentEnd; } else
  if (value == "CodeText") { return OrgTokenKind::CodeText; } else
  if (value == "Text") { return OrgTokenKind::Text; } else
  if (value == "StmtList") { return OrgTokenKind::StmtList; } else
  if (value == "StmtListBegin") { return OrgTokenKind::StmtListBegin; } else
  if (value == "StmtListEnd") { return OrgTokenKind::StmtListEnd; } else
  if (value == "Indent") { return OrgTokenKind::Indent; } else
  if (value == "Dedent") { return OrgTokenKind::Dedent; } else
  if (value == "SameIndent") { return OrgTokenKind::SameIndent; } else
  if (value == "NoIndent") { return OrgTokenKind::NoIndent; } else
  if (value == "ListBegin") { return OrgTokenKind::ListBegin; } else
  if (value == "ListItemBegin") { return OrgTokenKind::ListItemBegin; } else
  if (value == "ListClock") { return OrgTokenKind::ListClock; } else
  if (value == "ListDescBegin") { return OrgTokenKind::ListDescBegin; } else
  if (value == "ListDescEnd") { return OrgTokenKind::ListDescEnd; } else
  if (value == "ListItemEnd") { return OrgTokenKind::ListItemEnd; } else
  if (value == "ListEnd") { return OrgTokenKind::ListEnd; } else
  if (value == "Checkbox") { return OrgTokenKind::Checkbox; } else
  if (value == "SubtreeTodoState") { return OrgTokenKind::SubtreeTodoState; } else
  if (value == "SubtreeUrgency") { return OrgTokenKind::SubtreeUrgency; } else
  if (value == "SubtreeCompletion") { return OrgTokenKind::SubtreeCompletion; } else
  if (value == "SubtreeStars") { return OrgTokenKind::SubtreeStars; } else
  if (value == "SubtreeTagSeparator") { return OrgTokenKind::SubtreeTagSeparator; } else
  if (value == "SubtreeTime") { return OrgTokenKind::SubtreeTime; } else
  if (value == "SubtreeEnd") { return OrgTokenKind::SubtreeEnd; } else
  if (value == "LogBook") { return OrgTokenKind::LogBook; } else
  if (value == "Drawer") { return OrgTokenKind::Drawer; } else
  if (value == "ColonLiteral") { return OrgTokenKind::ColonLiteral; } else
  if (value == "ColonIdent") { return OrgTokenKind::ColonIdent; } else
  if (value == "ColonProperties") { return OrgTokenKind::ColonProperties; } else
  if (value == "ColonDescription") { return OrgTokenKind::ColonDescription; } else
  if (value == "ColonEnd") { return OrgTokenKind::ColonEnd; } else
  if (value == "ColonLogbook") { return OrgTokenKind::ColonLogbook; } else
  if (value == "RawLogbook") { return OrgTokenKind::RawLogbook; } else
  if (value == "RawProperty") { return OrgTokenKind::RawProperty; } else
  if (value == "PropRawKey") { return OrgTokenKind::PropRawKey; } else
  if (value == "PropTextKey") { return OrgTokenKind::PropTextKey; } else
  if (value == "ImplicitTime") { return OrgTokenKind::ImplicitTime; } else
  if (value == "TimeDuration") { return OrgTokenKind::TimeDuration; } else
  if (value == "DynamicTimeContent") { return OrgTokenKind::DynamicTimeContent; } else
  if (value == "StaticTimeDatePart") { return OrgTokenKind::StaticTimeDatePart; } else
  if (value == "StaticTimeDayPart") { return OrgTokenKind::StaticTimeDayPart; } else
  if (value == "StaticTimeClockPart") { return OrgTokenKind::StaticTimeClockPart; } else
  if (value == "StaticTimeRepeater") { return OrgTokenKind::StaticTimeRepeater; } else
  if (value == "TimeDash") { return OrgTokenKind::TimeDash; } else
  if (value == "TimeArrow") { return OrgTokenKind::TimeArrow; } else
  if (value == "Comment") { return OrgTokenKind::Comment; } else
  if (value == "Link") { return OrgTokenKind::Link; } else
  if (value == "BoldBegin") { return OrgTokenKind::BoldBegin; } else
  if (value == "BoldEnd") { return OrgTokenKind::BoldEnd; } else
  if (value == "ItalicBegin") { return OrgTokenKind::ItalicBegin; } else
  if (value == "ItalicEnd") { return OrgTokenKind::ItalicEnd; } else
  if (value == "VerbatimBegin") { return OrgTokenKind::VerbatimBegin; } else
  if (value == "VerbatimEnd") { return OrgTokenKind::VerbatimEnd; } else
  if (value == "MonospaceBegin") { return OrgTokenKind::MonospaceBegin; } else
  if (value == "MonospaceEnd") { return OrgTokenKind::MonospaceEnd; } else
  if (value == "BacktickBegin") { return OrgTokenKind::BacktickBegin; } else
  if (value == "BacktickEnd") { return OrgTokenKind::BacktickEnd; } else
  if (value == "UnderlineBegin") { return OrgTokenKind::UnderlineBegin; } else
  if (value == "UnderlineEnd") { return OrgTokenKind::UnderlineEnd; } else
  if (value == "StrikeBegin") { return OrgTokenKind::StrikeBegin; } else
  if (value == "StrikeEnd") { return OrgTokenKind::StrikeEnd; } else
  if (value == "QuoteBegin") { return OrgTokenKind::QuoteBegin; } else
  if (value == "QuoteEnd") { return OrgTokenKind::QuoteEnd; } else
  if (value == "Punctuation") { return OrgTokenKind::Punctuation; } else
  if (value == "AngleBegin") { return OrgTokenKind::AngleBegin; } else
  if (value == "AngleEnd") { return OrgTokenKind::AngleEnd; } else
  if (value == "DoubleAngleBegin") { return OrgTokenKind::DoubleAngleBegin; } else
  if (value == "DoubleAngleEnd") { return OrgTokenKind::DoubleAngleEnd; } else
  if (value == "TripleAngleBegin") { return OrgTokenKind::TripleAngleBegin; } else
  if (value == "TripleAngleEnd") { return OrgTokenKind::TripleAngleEnd; } else
  if (value == "LinkBegin") { return OrgTokenKind::LinkBegin; } else
  if (value == "LinkEnd") { return OrgTokenKind::LinkEnd; } else
  if (value == "RawUrl") { return OrgTokenKind::RawUrl; } else
  if (value == "LinkTargetBegin") { return OrgTokenKind::LinkTargetBegin; } else
  if (value == "LinkTargetEnd") { return OrgTokenKind::LinkTargetEnd; } else
  if (value == "LinkInternal") { return OrgTokenKind::LinkInternal; } else
  if (value == "LinkProtocol") { return OrgTokenKind::LinkProtocol; } else
  if (value == "LinkFull") { return OrgTokenKind::LinkFull; } else
  if (value == "LinkTarget") { return OrgTokenKind::LinkTarget; } else
  if (value == "LinkDescriptionBegin") { return OrgTokenKind::LinkDescriptionBegin; } else
  if (value == "LinkDescriptionEnd") { return OrgTokenKind::LinkDescriptionEnd; } else
  if (value == "TextSeparator") { return OrgTokenKind::TextSeparator; } else
  if (value == "ParagraphBegin") { return OrgTokenKind::ParagraphBegin; } else
  if (value == "ParagraphEnd") { return OrgTokenKind::ParagraphEnd; } else
  if (value == "FootnoteBegin") { return OrgTokenKind::FootnoteBegin; } else
  if (value == "Word") { return OrgTokenKind::Word; } else
  if (value == "DoubleColon") { return OrgTokenKind::DoubleColon; } else
  if (value == "Number") { return OrgTokenKind::Number; } else
  if (value == "Escaped") { return OrgTokenKind::Escaped; } else
  if (value == "DoubleSlash") { return OrgTokenKind::DoubleSlash; } else
  if (value == "Newline") { return OrgTokenKind::Newline; } else
  if (value == "MaybeWord") { return OrgTokenKind::MaybeWord; } else
  if (value == "Space") { return OrgTokenKind::Space; } else
  if (value == "BigIdent") { return OrgTokenKind::BigIdent; } else
  if (value == "RawText") { return OrgTokenKind::RawText; } else
  if (value == "SymbolBegin") { return OrgTokenKind::SymbolBegin; } else
  if (value == "DollarBegin") { return OrgTokenKind::DollarBegin; } else
  if (value == "DollarEnd") { return OrgTokenKind::DollarEnd; } else
  if (value == "DoubleDollarBegin") { return OrgTokenKind::DoubleDollarBegin; } else
  if (value == "DoubleDollarEnd") { return OrgTokenKind::DoubleDollarEnd; } else
  if (value == "LatexParBegin") { return OrgTokenKind::LatexParBegin; } else
  if (value == "LatexParEnd") { return OrgTokenKind::LatexParEnd; } else
  if (value == "LatexBraceBegin") { return OrgTokenKind::LatexBraceBegin; } else
  if (value == "LatexBraceEnd") { return OrgTokenKind::LatexBraceEnd; } else
  if (value == "LatexInlineRaw") { return OrgTokenKind::LatexInlineRaw; } else
  if (value == "AtMention") { return OrgTokenKind::AtMention; } else
  if (value == "HashTag") { return OrgTokenKind::HashTag; } else
  if (value == "HashTagSub") { return OrgTokenKind::HashTagSub; } else
  if (value == "HashTagBegin") { return OrgTokenKind::HashTagBegin; } else
  if (value == "HashTagEnd") { return OrgTokenKind::HashTagEnd; } else
  if (value == "Comma") { return OrgTokenKind::Comma; } else
  if (value == "ParBegin") { return OrgTokenKind::ParBegin; } else
  if (value == "ParEnd") { return OrgTokenKind::ParEnd; } else
  if (value == "BraceBegin") { return OrgTokenKind::BraceBegin; } else
  if (value == "BraceEnd") { return OrgTokenKind::BraceEnd; } else
  if (value == "Colon") { return OrgTokenKind::Colon; } else
  if (value == "Circumflex") { return OrgTokenKind::Circumflex; } else
  if (value == "MacroBegin") { return OrgTokenKind::MacroBegin; } else
  if (value == "MacroEnd") { return OrgTokenKind::MacroEnd; } else
  if (value == "InlineSrc") { return OrgTokenKind::InlineSrc; } else
  if (value == "InlineCall") { return OrgTokenKind::InlineCall; } else
  if (value == "CurlyStart") { return OrgTokenKind::CurlyStart; } else
  if (value == "CurlyEnd") { return OrgTokenKind::CurlyEnd; } else
  if (value == "DoubleAt") { return OrgTokenKind::DoubleAt; } else
  if (value == "SrcBegin") { return OrgTokenKind::SrcBegin; } else
  if (value == "SrcName") { return OrgTokenKind::SrcName; } else
  if (value == "SrcArgs") { return OrgTokenKind::SrcArgs; } else
  if (value == "SrcBody") { return OrgTokenKind::SrcBody; } else
  if (value == "SrcEnd") { return OrgTokenKind::SrcEnd; } else
  if (value == "CallBegin") { return OrgTokenKind::CallBegin; } else
  if (value == "CallName") { return OrgTokenKind::CallName; } else
  if (value == "CallInsideHeader") { return OrgTokenKind::CallInsideHeader; } else
  if (value == "CallArgs") { return OrgTokenKind::CallArgs; } else
  if (value == "EndHeader") { return OrgTokenKind::EndHeader; } else
  if (value == "CallEnd") { return OrgTokenKind::CallEnd; } else
  if (value == "CmdArguments") { return OrgTokenKind::CmdArguments; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgTokenKind>::to_string(OrgTokenKind value) {
  switch (value) {
    case OrgTokenKind::None: return "None";
    case OrgTokenKind::Eof: return "Eof";
    case OrgTokenKind::CmdPrefix: return "CmdPrefix";
    case OrgTokenKind::CmdLine: return "CmdLine";
    case OrgTokenKind::CmdTitle: return "CmdTitle";
    case OrgTokenKind::CmdCaption: return "CmdCaption";
    case OrgTokenKind::CmdFiletags: return "CmdFiletags";
    case OrgTokenKind::CmdColumns: return "CmdColumns";
    case OrgTokenKind::CmdPropertyArgs: return "CmdPropertyArgs";
    case OrgTokenKind::CmdPropertyText: return "CmdPropertyText";
    case OrgTokenKind::CmdPropertyRaw: return "CmdPropertyRaw";
    case OrgTokenKind::CmdOptions: return "CmdOptions";
    case OrgTokenKind::CmdSetupfile: return "CmdSetupfile";
    case OrgTokenKind::CmdInclude: return "CmdInclude";
    case OrgTokenKind::CmdAttrLatex: return "CmdAttrLatex";
    case OrgTokenKind::CmdAttrImg: return "CmdAttrImg";
    case OrgTokenKind::CmdAttrHtml: return "CmdAttrHtml";
    case OrgTokenKind::CmdHtmlHead: return "CmdHtmlHead";
    case OrgTokenKind::CmdLanguage: return "CmdLanguage";
    case OrgTokenKind::CmdLatexClassOptions: return "CmdLatexClassOptions";
    case OrgTokenKind::CmdLatexClass: return "CmdLatexClass";
    case OrgTokenKind::CmdLatexCompiler: return "CmdLatexCompiler";
    case OrgTokenKind::CmdAuthor: return "CmdAuthor";
    case OrgTokenKind::CmdBind: return "CmdBind";
    case OrgTokenKind::CmdCreator: return "CmdCreator";
    case OrgTokenKind::CmdLatexHeader: return "CmdLatexHeader";
    case OrgTokenKind::CmdResults: return "CmdResults";
    case OrgTokenKind::CmdCall: return "CmdCall";
    case OrgTokenKind::CmdName: return "CmdName";
    case OrgTokenKind::CmdHeader: return "CmdHeader";
    case OrgTokenKind::CmdArgumentsBegin: return "CmdArgumentsBegin";
    case OrgTokenKind::CmdArgumentsEnd: return "CmdArgumentsEnd";
    case OrgTokenKind::CmdKey: return "CmdKey";
    case OrgTokenKind::CmdValue: return "CmdValue";
    case OrgTokenKind::CmdFlag: return "CmdFlag";
    case OrgTokenKind::CmdBracket: return "CmdBracket";
    case OrgTokenKind::CmdBegin: return "CmdBegin";
    case OrgTokenKind::CmdEnd: return "CmdEnd";
    case OrgTokenKind::CmdSrcBegin: return "CmdSrcBegin";
    case OrgTokenKind::CmdSrcEnd: return "CmdSrcEnd";
    case OrgTokenKind::CmdQuoteBegin: return "CmdQuoteBegin";
    case OrgTokenKind::CmdQuoteEnd: return "CmdQuoteEnd";
    case OrgTokenKind::CmdCenterBegin: return "CmdCenterBegin";
    case OrgTokenKind::CmdCenterEnd: return "CmdCenterEnd";
    case OrgTokenKind::CmdTableBegin: return "CmdTableBegin";
    case OrgTokenKind::CmdTableEnd: return "CmdTableEnd";
    case OrgTokenKind::CmdAdmonitionBegin: return "CmdAdmonitionBegin";
    case OrgTokenKind::CmdAdmonitionEnd: return "CmdAdmonitionEnd";
    case OrgTokenKind::CmdDynamicBegin: return "CmdDynamicBegin";
    case OrgTokenKind::CmdDynamicEnd: return "CmdDynamicEnd";
    case OrgTokenKind::CmdExampleBegin: return "CmdExampleBegin";
    case OrgTokenKind::CmdExampleEnd: return "CmdExampleEnd";
    case OrgTokenKind::CmdExportBegin: return "CmdExportBegin";
    case OrgTokenKind::CmdExportEnd: return "CmdExportEnd";
    case OrgTokenKind::CmdDetailsBegin: return "CmdDetailsBegin";
    case OrgTokenKind::CmdDetailsEnd: return "CmdDetailsEnd";
    case OrgTokenKind::CmdSummaryBegin: return "CmdSummaryBegin";
    case OrgTokenKind::CmdSummaryEnd: return "CmdSummaryEnd";
    case OrgTokenKind::CmdTblfm: return "CmdTblfm";
    case OrgTokenKind::QuoteContent: return "QuoteContent";
    case OrgTokenKind::CmdBackendPass: return "CmdBackendPass";
    case OrgTokenKind::CmdContentBegin: return "CmdContentBegin";
    case OrgTokenKind::CmdContentEnd: return "CmdContentEnd";
    case OrgTokenKind::CmdSrcCodeContent: return "CmdSrcCodeContent";
    case OrgTokenKind::CmdSrcTextBlock: return "CmdSrcTextBlock";
    case OrgTokenKind::TblContent: return "TblContent";
    case OrgTokenKind::TblBegin: return "TblBegin";
    case OrgTokenKind::TblEnd: return "TblEnd";
    case OrgTokenKind::TblCellBody: return "TblCellBody";
    case OrgTokenKind::TblRowSpec: return "TblRowSpec";
    case OrgTokenKind::TblCellSpec: return "TblCellSpec";
    case OrgTokenKind::TblPipeBegin: return "TblPipeBegin";
    case OrgTokenKind::TblPipeSeparator: return "TblPipeSeparator";
    case OrgTokenKind::TblPipeEnd: return "TblPipeEnd";
    case OrgTokenKind::TblPipeCellBegin: return "TblPipeCellBegin";
    case OrgTokenKind::TblDashSeparator: return "TblDashSeparator";
    case OrgTokenKind::TblCornerPlus: return "TblCornerPlus";
    case OrgTokenKind::TblCellContentBegin: return "TblCellContentBegin";
    case OrgTokenKind::TblCellContentEnd: return "TblCellContentEnd";
    case OrgTokenKind::CodeText: return "CodeText";
    case OrgTokenKind::Text: return "Text";
    case OrgTokenKind::StmtList: return "StmtList";
    case OrgTokenKind::StmtListBegin: return "StmtListBegin";
    case OrgTokenKind::StmtListEnd: return "StmtListEnd";
    case OrgTokenKind::Indent: return "Indent";
    case OrgTokenKind::Dedent: return "Dedent";
    case OrgTokenKind::SameIndent: return "SameIndent";
    case OrgTokenKind::NoIndent: return "NoIndent";
    case OrgTokenKind::ListBegin: return "ListBegin";
    case OrgTokenKind::ListItemBegin: return "ListItemBegin";
    case OrgTokenKind::ListClock: return "ListClock";
    case OrgTokenKind::ListDescBegin: return "ListDescBegin";
    case OrgTokenKind::ListDescEnd: return "ListDescEnd";
    case OrgTokenKind::ListItemEnd: return "ListItemEnd";
    case OrgTokenKind::ListEnd: return "ListEnd";
    case OrgTokenKind::Checkbox: return "Checkbox";
    case OrgTokenKind::SubtreeTodoState: return "SubtreeTodoState";
    case OrgTokenKind::SubtreeUrgency: return "SubtreeUrgency";
    case OrgTokenKind::SubtreeCompletion: return "SubtreeCompletion";
    case OrgTokenKind::SubtreeStars: return "SubtreeStars";
    case OrgTokenKind::SubtreeTagSeparator: return "SubtreeTagSeparator";
    case OrgTokenKind::SubtreeTime: return "SubtreeTime";
    case OrgTokenKind::SubtreeEnd: return "SubtreeEnd";
    case OrgTokenKind::LogBook: return "LogBook";
    case OrgTokenKind::Drawer: return "Drawer";
    case OrgTokenKind::ColonLiteral: return "ColonLiteral";
    case OrgTokenKind::ColonIdent: return "ColonIdent";
    case OrgTokenKind::ColonProperties: return "ColonProperties";
    case OrgTokenKind::ColonDescription: return "ColonDescription";
    case OrgTokenKind::ColonEnd: return "ColonEnd";
    case OrgTokenKind::ColonLogbook: return "ColonLogbook";
    case OrgTokenKind::RawLogbook: return "RawLogbook";
    case OrgTokenKind::RawProperty: return "RawProperty";
    case OrgTokenKind::PropRawKey: return "PropRawKey";
    case OrgTokenKind::PropTextKey: return "PropTextKey";
    case OrgTokenKind::ImplicitTime: return "ImplicitTime";
    case OrgTokenKind::TimeDuration: return "TimeDuration";
    case OrgTokenKind::DynamicTimeContent: return "DynamicTimeContent";
    case OrgTokenKind::StaticTimeDatePart: return "StaticTimeDatePart";
    case OrgTokenKind::StaticTimeDayPart: return "StaticTimeDayPart";
    case OrgTokenKind::StaticTimeClockPart: return "StaticTimeClockPart";
    case OrgTokenKind::StaticTimeRepeater: return "StaticTimeRepeater";
    case OrgTokenKind::TimeDash: return "TimeDash";
    case OrgTokenKind::TimeArrow: return "TimeArrow";
    case OrgTokenKind::Comment: return "Comment";
    case OrgTokenKind::Link: return "Link";
    case OrgTokenKind::BoldBegin: return "BoldBegin";
    case OrgTokenKind::BoldEnd: return "BoldEnd";
    case OrgTokenKind::ItalicBegin: return "ItalicBegin";
    case OrgTokenKind::ItalicEnd: return "ItalicEnd";
    case OrgTokenKind::VerbatimBegin: return "VerbatimBegin";
    case OrgTokenKind::VerbatimEnd: return "VerbatimEnd";
    case OrgTokenKind::MonospaceBegin: return "MonospaceBegin";
    case OrgTokenKind::MonospaceEnd: return "MonospaceEnd";
    case OrgTokenKind::BacktickBegin: return "BacktickBegin";
    case OrgTokenKind::BacktickEnd: return "BacktickEnd";
    case OrgTokenKind::UnderlineBegin: return "UnderlineBegin";
    case OrgTokenKind::UnderlineEnd: return "UnderlineEnd";
    case OrgTokenKind::StrikeBegin: return "StrikeBegin";
    case OrgTokenKind::StrikeEnd: return "StrikeEnd";
    case OrgTokenKind::QuoteBegin: return "QuoteBegin";
    case OrgTokenKind::QuoteEnd: return "QuoteEnd";
    case OrgTokenKind::Punctuation: return "Punctuation";
    case OrgTokenKind::AngleBegin: return "AngleBegin";
    case OrgTokenKind::AngleEnd: return "AngleEnd";
    case OrgTokenKind::DoubleAngleBegin: return "DoubleAngleBegin";
    case OrgTokenKind::DoubleAngleEnd: return "DoubleAngleEnd";
    case OrgTokenKind::TripleAngleBegin: return "TripleAngleBegin";
    case OrgTokenKind::TripleAngleEnd: return "TripleAngleEnd";
    case OrgTokenKind::LinkBegin: return "LinkBegin";
    case OrgTokenKind::LinkEnd: return "LinkEnd";
    case OrgTokenKind::RawUrl: return "RawUrl";
    case OrgTokenKind::LinkTargetBegin: return "LinkTargetBegin";
    case OrgTokenKind::LinkTargetEnd: return "LinkTargetEnd";
    case OrgTokenKind::LinkInternal: return "LinkInternal";
    case OrgTokenKind::LinkProtocol: return "LinkProtocol";
    case OrgTokenKind::LinkFull: return "LinkFull";
    case OrgTokenKind::LinkTarget: return "LinkTarget";
    case OrgTokenKind::LinkDescriptionBegin: return "LinkDescriptionBegin";
    case OrgTokenKind::LinkDescriptionEnd: return "LinkDescriptionEnd";
    case OrgTokenKind::TextSeparator: return "TextSeparator";
    case OrgTokenKind::ParagraphBegin: return "ParagraphBegin";
    case OrgTokenKind::ParagraphEnd: return "ParagraphEnd";
    case OrgTokenKind::FootnoteBegin: return "FootnoteBegin";
    case OrgTokenKind::Word: return "Word";
    case OrgTokenKind::DoubleColon: return "DoubleColon";
    case OrgTokenKind::Number: return "Number";
    case OrgTokenKind::Escaped: return "Escaped";
    case OrgTokenKind::DoubleSlash: return "DoubleSlash";
    case OrgTokenKind::Newline: return "Newline";
    case OrgTokenKind::MaybeWord: return "MaybeWord";
    case OrgTokenKind::Space: return "Space";
    case OrgTokenKind::BigIdent: return "BigIdent";
    case OrgTokenKind::RawText: return "RawText";
    case OrgTokenKind::SymbolBegin: return "SymbolBegin";
    case OrgTokenKind::DollarBegin: return "DollarBegin";
    case OrgTokenKind::DollarEnd: return "DollarEnd";
    case OrgTokenKind::DoubleDollarBegin: return "DoubleDollarBegin";
    case OrgTokenKind::DoubleDollarEnd: return "DoubleDollarEnd";
    case OrgTokenKind::LatexParBegin: return "LatexParBegin";
    case OrgTokenKind::LatexParEnd: return "LatexParEnd";
    case OrgTokenKind::LatexBraceBegin: return "LatexBraceBegin";
    case OrgTokenKind::LatexBraceEnd: return "LatexBraceEnd";
    case OrgTokenKind::LatexInlineRaw: return "LatexInlineRaw";
    case OrgTokenKind::AtMention: return "AtMention";
    case OrgTokenKind::HashTag: return "HashTag";
    case OrgTokenKind::HashTagSub: return "HashTagSub";
    case OrgTokenKind::HashTagBegin: return "HashTagBegin";
    case OrgTokenKind::HashTagEnd: return "HashTagEnd";
    case OrgTokenKind::Comma: return "Comma";
    case OrgTokenKind::ParBegin: return "ParBegin";
    case OrgTokenKind::ParEnd: return "ParEnd";
    case OrgTokenKind::BraceBegin: return "BraceBegin";
    case OrgTokenKind::BraceEnd: return "BraceEnd";
    case OrgTokenKind::Colon: return "Colon";
    case OrgTokenKind::Circumflex: return "Circumflex";
    case OrgTokenKind::MacroBegin: return "MacroBegin";
    case OrgTokenKind::MacroEnd: return "MacroEnd";
    case OrgTokenKind::InlineSrc: return "InlineSrc";
    case OrgTokenKind::InlineCall: return "InlineCall";
    case OrgTokenKind::CurlyStart: return "CurlyStart";
    case OrgTokenKind::CurlyEnd: return "CurlyEnd";
    case OrgTokenKind::DoubleAt: return "DoubleAt";
    case OrgTokenKind::SrcBegin: return "SrcBegin";
    case OrgTokenKind::SrcName: return "SrcName";
    case OrgTokenKind::SrcArgs: return "SrcArgs";
    case OrgTokenKind::SrcBody: return "SrcBody";
    case OrgTokenKind::SrcEnd: return "SrcEnd";
    case OrgTokenKind::CallBegin: return "CallBegin";
    case OrgTokenKind::CallName: return "CallName";
    case OrgTokenKind::CallInsideHeader: return "CallInsideHeader";
    case OrgTokenKind::CallArgs: return "CallArgs";
    case OrgTokenKind::EndHeader: return "EndHeader";
    case OrgTokenKind::CallEnd: return "CallEnd";
    case OrgTokenKind::CmdArguments: return "CmdArguments";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<OrgSemKind> enum_serde<OrgSemKind>::from_string(std::string value) {
  if (value == "StmtList") { return OrgSemKind::StmtList; } else
  if (value == "Empty") { return OrgSemKind::Empty; } else
  if (value == "Row") { return OrgSemKind::Row; } else
  if (value == "Table") { return OrgSemKind::Table; } else
  if (value == "HashTag") { return OrgSemKind::HashTag; } else
  if (value == "Footnote") { return OrgSemKind::Footnote; } else
  if (value == "Completion") { return OrgSemKind::Completion; } else
  if (value == "Paragraph") { return OrgSemKind::Paragraph; } else
  if (value == "Center") { return OrgSemKind::Center; } else
  if (value == "Caption") { return OrgSemKind::Caption; } else
  if (value == "CommandGroup") { return OrgSemKind::CommandGroup; } else
  if (value == "Quote") { return OrgSemKind::Quote; } else
  if (value == "Example") { return OrgSemKind::Example; } else
  if (value == "CmdArguments") { return OrgSemKind::CmdArguments; } else
  if (value == "CmdArgument") { return OrgSemKind::CmdArgument; } else
  if (value == "Export") { return OrgSemKind::Export; } else
  if (value == "AdmonitionBlock") { return OrgSemKind::AdmonitionBlock; } else
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
  if (value == "Document") { return OrgSemKind::Document; } else
  if (value == "ParseError") { return OrgSemKind::ParseError; } else
  if (value == "FileTarget") { return OrgSemKind::FileTarget; } else
  if (value == "TextSeparator") { return OrgSemKind::TextSeparator; } else
  if (value == "Include") { return OrgSemKind::Include; } else
  if (value == "DocumentOptions") { return OrgSemKind::DocumentOptions; } else
  if (value == "DocumentGroup") { return OrgSemKind::DocumentGroup; } else
  { return std::nullopt; }
}
std::string enum_serde<OrgSemKind>::to_string(OrgSemKind value) {
  switch (value) {
    case OrgSemKind::StmtList: return "StmtList";
    case OrgSemKind::Empty: return "Empty";
    case OrgSemKind::Row: return "Row";
    case OrgSemKind::Table: return "Table";
    case OrgSemKind::HashTag: return "HashTag";
    case OrgSemKind::Footnote: return "Footnote";
    case OrgSemKind::Completion: return "Completion";
    case OrgSemKind::Paragraph: return "Paragraph";
    case OrgSemKind::Center: return "Center";
    case OrgSemKind::Caption: return "Caption";
    case OrgSemKind::CommandGroup: return "CommandGroup";
    case OrgSemKind::Quote: return "Quote";
    case OrgSemKind::Example: return "Example";
    case OrgSemKind::CmdArguments: return "CmdArguments";
    case OrgSemKind::CmdArgument: return "CmdArgument";
    case OrgSemKind::Export: return "Export";
    case OrgSemKind::AdmonitionBlock: return "AdmonitionBlock";
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
    case OrgSemKind::Document: return "Document";
    case OrgSemKind::ParseError: return "ParseError";
    case OrgSemKind::FileTarget: return "FileTarget";
    case OrgSemKind::TextSeparator: return "TextSeparator";
    case OrgSemKind::Include: return "Include";
    case OrgSemKind::DocumentOptions: return "DocumentOptions";
    case OrgSemKind::DocumentGroup: return "DocumentGroup";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
/* clang-format on */