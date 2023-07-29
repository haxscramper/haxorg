#include "SemOrgEnums.hpp"












Opt<OrgHorizontalDirection> enum_serde<OrgHorizontalDirection>::from_string(QString value) {
  if (value == "ohdNone") { return OrgHorizontalDirection::ohdNone; } else
  if (value == "ohdLeft") { return OrgHorizontalDirection::ohdLeft; } else
  if (value == "ohdRight") { return OrgHorizontalDirection::ohdRight; } else
  if (value == "ohdCenter") { return OrgHorizontalDirection::ohdCenter; } else
  { return std::nullopt; }
}
QString enum_serde<OrgHorizontalDirection>::to_string(OrgHorizontalDirection value) {
  switch (value) {
    case OrgHorizontalDirection::ohdNone: return "ohdNone";
    case OrgHorizontalDirection::ohdLeft: return "ohdLeft";
    case OrgHorizontalDirection::ohdRight: return "ohdRight";
    case OrgHorizontalDirection::ohdCenter: return "ohdCenter";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgVerticalDirection> enum_serde<OrgVerticalDirection>::from_string(QString value) {
  if (value == "ovdNone") { return OrgVerticalDirection::ovdNone; } else
  if (value == "ovdTop") { return OrgVerticalDirection::ovdTop; } else
  if (value == "ovdCenter") { return OrgVerticalDirection::ovdCenter; } else
  if (value == "ovdBottom") { return OrgVerticalDirection::ovdBottom; } else
  { return std::nullopt; }
}
QString enum_serde<OrgVerticalDirection>::to_string(OrgVerticalDirection value) {
  switch (value) {
    case OrgVerticalDirection::ovdNone: return "ovdNone";
    case OrgVerticalDirection::ovdTop: return "ovdTop";
    case OrgVerticalDirection::ovdCenter: return "ovdCenter";
    case OrgVerticalDirection::ovdBottom: return "ovdBottom";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgSpecName> enum_serde<OrgSpecName>::from_string(QString value) {
  if (value == "Unnamed") { return OrgSpecName::Unnamed; } else
  if (value == "Result") { return OrgSpecName::Result; } else
  if (value == "Year") { return OrgSpecName::Year; } else
  if (value == "Day") { return OrgSpecName::Day; } else
  if (value == "Clock") { return OrgSpecName::Clock; } else
  if (value == "Repeater") { return OrgSpecName::Repeater; } else
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
QString enum_serde<OrgSpecName>::to_string(OrgSpecName value) {
  switch (value) {
    case OrgSpecName::Unnamed: return "Unnamed";
    case OrgSpecName::Result: return "Result";
    case OrgSpecName::Year: return "Year";
    case OrgSpecName::Day: return "Day";
    case OrgSpecName::Clock: return "Clock";
    case OrgSpecName::Repeater: return "Repeater";
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
Opt<OrgNodeKind> enum_serde<OrgNodeKind>::from_string(QString value) {
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
  if (value == "SkipNewline") { return OrgNodeKind::SkipNewline; } else
  if (value == "SkipSpace") { return OrgNodeKind::SkipSpace; } else
  if (value == "SkipAny") { return OrgNodeKind::SkipAny; } else
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
  if (value == "PropertyList") { return OrgNodeKind::PropertyList; } else
  if (value == "Property") { return OrgNodeKind::Property; } else
  if (value == "Placeholder") { return OrgNodeKind::Placeholder; } else
  if (value == "SubtreeDescription") { return OrgNodeKind::SubtreeDescription; } else
  if (value == "SubtreeUrgency") { return OrgNodeKind::SubtreeUrgency; } else
  if (value == "Logbook") { return OrgNodeKind::Logbook; } else
  if (value == "LogbookEntry") { return OrgNodeKind::LogbookEntry; } else
  if (value == "LogbookStateChange") { return OrgNodeKind::LogbookStateChange; } else
  if (value == "LogbookNote") { return OrgNodeKind::LogbookNote; } else
  if (value == "LogbookClock") { return OrgNodeKind::LogbookClock; } else
  if (value == "LogbookRefile") { return OrgNodeKind::LogbookRefile; } else
  if (value == "LogbookReschedule") { return OrgNodeKind::LogbookReschedule; } else
  if (value == "LogbookTagChange") { return OrgNodeKind::LogbookTagChange; } else
  if (value == "LogbookTagChangeAction") { return OrgNodeKind::LogbookTagChangeAction; } else
  if (value == "RadioTarget") { return OrgNodeKind::RadioTarget; } else
  if (value == "Target") { return OrgNodeKind::Target; } else
  { return std::nullopt; }
}
QString enum_serde<OrgNodeKind>::to_string(OrgNodeKind value) {
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
    case OrgNodeKind::SkipNewline: return "SkipNewline";
    case OrgNodeKind::SkipSpace: return "SkipSpace";
    case OrgNodeKind::SkipAny: return "SkipAny";
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
    case OrgNodeKind::PropertyList: return "PropertyList";
    case OrgNodeKind::Property: return "Property";
    case OrgNodeKind::Placeholder: return "Placeholder";
    case OrgNodeKind::SubtreeDescription: return "SubtreeDescription";
    case OrgNodeKind::SubtreeUrgency: return "SubtreeUrgency";
    case OrgNodeKind::Logbook: return "Logbook";
    case OrgNodeKind::LogbookEntry: return "LogbookEntry";
    case OrgNodeKind::LogbookStateChange: return "LogbookStateChange";
    case OrgNodeKind::LogbookNote: return "LogbookNote";
    case OrgNodeKind::LogbookClock: return "LogbookClock";
    case OrgNodeKind::LogbookRefile: return "LogbookRefile";
    case OrgNodeKind::LogbookReschedule: return "LogbookReschedule";
    case OrgNodeKind::LogbookTagChange: return "LogbookTagChange";
    case OrgNodeKind::LogbookTagChangeAction: return "LogbookTagChangeAction";
    case OrgNodeKind::RadioTarget: return "RadioTarget";
    case OrgNodeKind::Target: return "Target";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgTextContext> enum_serde<OrgTextContext>::from_string(QString value) {
  if (value == "otcPlain") { return OrgTextContext::otcPlain; } else
  if (value == "otcSubtree0") { return OrgTextContext::otcSubtree0; } else
  if (value == "otcSubtree1") { return OrgTextContext::otcSubtree1; } else
  if (value == "otcSubtree2") { return OrgTextContext::otcSubtree2; } else
  if (value == "otcSubtree3") { return OrgTextContext::otcSubtree3; } else
  if (value == "otcSubtree4") { return OrgTextContext::otcSubtree4; } else
  if (value == "otcSubtree5") { return OrgTextContext::otcSubtree5; } else
  if (value == "otcSubtree6") { return OrgTextContext::otcSubtree6; } else
  if (value == "otcSubtree7") { return OrgTextContext::otcSubtree7; } else
  if (value == "otcSubtree8") { return OrgTextContext::otcSubtree8; } else
  if (value == "otcSubtree9") { return OrgTextContext::otcSubtree9; } else
  if (value == "otcSubtree10") { return OrgTextContext::otcSubtree10; } else
  if (value == "otcSubtree11") { return OrgTextContext::otcSubtree11; } else
  if (value == "otcSubtree12") { return OrgTextContext::otcSubtree12; } else
  if (value == "otcSubtreeOther") { return OrgTextContext::otcSubtreeOther; } else
  if (value == "otcBold") { return OrgTextContext::otcBold; } else
  if (value == "otcItalic") { return OrgTextContext::otcItalic; } else
  if (value == "otcStrike") { return OrgTextContext::otcStrike; } else
  if (value == "otcUnderline") { return OrgTextContext::otcUnderline; } else
  if (value == "otcMonospaceInline") { return OrgTextContext::otcMonospaceInline; } else
  if (value == "otcMonospaceBlock") { return OrgTextContext::otcMonospaceBlock; } else
  { return std::nullopt; }
}
QString enum_serde<OrgTextContext>::to_string(OrgTextContext value) {
  switch (value) {
    case OrgTextContext::otcPlain: return "otcPlain";
    case OrgTextContext::otcSubtree0: return "otcSubtree0";
    case OrgTextContext::otcSubtree1: return "otcSubtree1";
    case OrgTextContext::otcSubtree2: return "otcSubtree2";
    case OrgTextContext::otcSubtree3: return "otcSubtree3";
    case OrgTextContext::otcSubtree4: return "otcSubtree4";
    case OrgTextContext::otcSubtree5: return "otcSubtree5";
    case OrgTextContext::otcSubtree6: return "otcSubtree6";
    case OrgTextContext::otcSubtree7: return "otcSubtree7";
    case OrgTextContext::otcSubtree8: return "otcSubtree8";
    case OrgTextContext::otcSubtree9: return "otcSubtree9";
    case OrgTextContext::otcSubtree10: return "otcSubtree10";
    case OrgTextContext::otcSubtree11: return "otcSubtree11";
    case OrgTextContext::otcSubtree12: return "otcSubtree12";
    case OrgTextContext::otcSubtreeOther: return "otcSubtreeOther";
    case OrgTextContext::otcBold: return "otcBold";
    case OrgTextContext::otcItalic: return "otcItalic";
    case OrgTextContext::otcStrike: return "otcStrike";
    case OrgTextContext::otcUnderline: return "otcUnderline";
    case OrgTextContext::otcMonospaceInline: return "otcMonospaceInline";
    case OrgTextContext::otcMonospaceBlock: return "otcMonospaceBlock";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgBigIdentKind> enum_serde<OrgBigIdentKind>::from_string(QString value) {
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
QString enum_serde<OrgBigIdentKind>::to_string(OrgBigIdentKind value) {
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
Opt<OrgTokenKind> enum_serde<OrgTokenKind>::from_string(QString value) {
  if (value == "None") { return OrgTokenKind::None; } else
  if (value == "Eof") { return OrgTokenKind::Eof; } else
  if (value == "GroupStart") { return OrgTokenKind::GroupStart; } else
  if (value == "GroupEnd") { return OrgTokenKind::GroupEnd; } else
  if (value == "ErrorTerminator") { return OrgTokenKind::ErrorTerminator; } else
  if (value == "CommandPrefix") { return OrgTokenKind::CommandPrefix; } else
  if (value == "LineCommand") { return OrgTokenKind::LineCommand; } else
  if (value == "CommandBegin") { return OrgTokenKind::CommandBegin; } else
  if (value == "CommandEnd") { return OrgTokenKind::CommandEnd; } else
  if (value == "DoubleColon") { return OrgTokenKind::DoubleColon; } else
  if (value == "Text") { return OrgTokenKind::Text; } else
  if (value == "StmtList") { return OrgTokenKind::StmtList; } else
  if (value == "StmtListOpen") { return OrgTokenKind::StmtListOpen; } else
  if (value == "StmtListClose") { return OrgTokenKind::StmtListClose; } else
  if (value == "ListStart") { return OrgTokenKind::ListStart; } else
  if (value == "ListItemStart") { return OrgTokenKind::ListItemStart; } else
  if (value == "ListClock") { return OrgTokenKind::ListClock; } else
  if (value == "ListPlus") { return OrgTokenKind::ListPlus; } else
  if (value == "ListStar") { return OrgTokenKind::ListStar; } else
  if (value == "ListDescOpen") { return OrgTokenKind::ListDescOpen; } else
  if (value == "ListDescClose") { return OrgTokenKind::ListDescClose; } else
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
  if (value == "ImplicitTime") { return OrgTokenKind::ImplicitTime; } else
  if (value == "TimeDuration") { return OrgTokenKind::TimeDuration; } else
  if (value == "InactiveTimeBegin") { return OrgTokenKind::InactiveTimeBegin; } else
  if (value == "InactiveTimeEnd") { return OrgTokenKind::InactiveTimeEnd; } else
  if (value == "ActiveTimeBegin") { return OrgTokenKind::ActiveTimeBegin; } else
  if (value == "ActiveTimeEnd") { return OrgTokenKind::ActiveTimeEnd; } else
  if (value == "DynamicTimeContent") { return OrgTokenKind::DynamicTimeContent; } else
  if (value == "StaticTimeDatePart") { return OrgTokenKind::StaticTimeDatePart; } else
  if (value == "StaticTimeDayPart") { return OrgTokenKind::StaticTimeDayPart; } else
  if (value == "StaticTimeClockPart") { return OrgTokenKind::StaticTimeClockPart; } else
  if (value == "StaticTimeRepeater") { return OrgTokenKind::StaticTimeRepeater; } else
  if (value == "TimeDash") { return OrgTokenKind::TimeDash; } else
  if (value == "TimeArrow") { return OrgTokenKind::TimeArrow; } else
  if (value == "Comment") { return OrgTokenKind::Comment; } else
  if (value == "ListDoubleColon") { return OrgTokenKind::ListDoubleColon; } else
  if (value == "CommandArgumentsBegin") { return OrgTokenKind::CommandArgumentsBegin; } else
  if (value == "CommandArgumentsEnd") { return OrgTokenKind::CommandArgumentsEnd; } else
  if (value == "CommandKey") { return OrgTokenKind::CommandKey; } else
  if (value == "CommandValue") { return OrgTokenKind::CommandValue; } else
  if (value == "CommandFlag") { return OrgTokenKind::CommandFlag; } else
  if (value == "CommandBracket") { return OrgTokenKind::CommandBracket; } else
  if (value == "ColonLiteral") { return OrgTokenKind::ColonLiteral; } else
  if (value == "ColonIdent") { return OrgTokenKind::ColonIdent; } else
  if (value == "ColonProperties") { return OrgTokenKind::ColonProperties; } else
  if (value == "ColonDescription") { return OrgTokenKind::ColonDescription; } else
  if (value == "ColonEnd") { return OrgTokenKind::ColonEnd; } else
  if (value == "ColonLogbook") { return OrgTokenKind::ColonLogbook; } else
  if (value == "RawLogbook") { return OrgTokenKind::RawLogbook; } else
  if (value == "LogbookStart") { return OrgTokenKind::LogbookStart; } else
  if (value == "LogbookEnd") { return OrgTokenKind::LogbookEnd; } else
  if (value == "RawProperty") { return OrgTokenKind::RawProperty; } else
  if (value == "Link") { return OrgTokenKind::Link; } else
  if (value == "CommandContentStart") { return OrgTokenKind::CommandContentStart; } else
  if (value == "CommandContentEnd") { return OrgTokenKind::CommandContentEnd; } else
  if (value == "CodeContent") { return OrgTokenKind::CodeContent; } else
  if (value == "CodeContentBegin") { return OrgTokenKind::CodeContentBegin; } else
  if (value == "CodeContentEnd") { return OrgTokenKind::CodeContentEnd; } else
  if (value == "CodeText") { return OrgTokenKind::CodeText; } else
  if (value == "TableContent") { return OrgTokenKind::TableContent; } else
  if (value == "QuoteContent") { return OrgTokenKind::QuoteContent; } else
  if (value == "BackendPass") { return OrgTokenKind::BackendPass; } else
  if (value == "LogBook") { return OrgTokenKind::LogBook; } else
  if (value == "Drawer") { return OrgTokenKind::Drawer; } else
  if (value == "Indent") { return OrgTokenKind::Indent; } else
  if (value == "Dedent") { return OrgTokenKind::Dedent; } else
  if (value == "SameIndent") { return OrgTokenKind::SameIndent; } else
  if (value == "NoIndent") { return OrgTokenKind::NoIndent; } else
  if (value == "BoldOpen") { return OrgTokenKind::BoldOpen; } else
  if (value == "BoldClose") { return OrgTokenKind::BoldClose; } else
  if (value == "BoldInline") { return OrgTokenKind::BoldInline; } else
  if (value == "BoldInlineOpen") { return OrgTokenKind::BoldInlineOpen; } else
  if (value == "BoldInlineClose") { return OrgTokenKind::BoldInlineClose; } else
  if (value == "ItalicOpen") { return OrgTokenKind::ItalicOpen; } else
  if (value == "ItalicClose") { return OrgTokenKind::ItalicClose; } else
  if (value == "ItalicInline") { return OrgTokenKind::ItalicInline; } else
  if (value == "ItalicInlineOpen") { return OrgTokenKind::ItalicInlineOpen; } else
  if (value == "ItalicInlineClose") { return OrgTokenKind::ItalicInlineClose; } else
  if (value == "VerbatimOpen") { return OrgTokenKind::VerbatimOpen; } else
  if (value == "VerbatimClose") { return OrgTokenKind::VerbatimClose; } else
  if (value == "VerbatimInline") { return OrgTokenKind::VerbatimInline; } else
  if (value == "VerbatimInlineOpen") { return OrgTokenKind::VerbatimInlineOpen; } else
  if (value == "VerbatimInlineClose") { return OrgTokenKind::VerbatimInlineClose; } else
  if (value == "MonospaceOpen") { return OrgTokenKind::MonospaceOpen; } else
  if (value == "MonospaceClose") { return OrgTokenKind::MonospaceClose; } else
  if (value == "MonospaceInline") { return OrgTokenKind::MonospaceInline; } else
  if (value == "MonospaceInlineOpen") { return OrgTokenKind::MonospaceInlineOpen; } else
  if (value == "MonospaceInlineClose") { return OrgTokenKind::MonospaceInlineClose; } else
  if (value == "BacktickOpen") { return OrgTokenKind::BacktickOpen; } else
  if (value == "BacktickClose") { return OrgTokenKind::BacktickClose; } else
  if (value == "BacktickInline") { return OrgTokenKind::BacktickInline; } else
  if (value == "BacktickInlineOpen") { return OrgTokenKind::BacktickInlineOpen; } else
  if (value == "BacktickInlineClose") { return OrgTokenKind::BacktickInlineClose; } else
  if (value == "UnderlineOpen") { return OrgTokenKind::UnderlineOpen; } else
  if (value == "UnderlineClose") { return OrgTokenKind::UnderlineClose; } else
  if (value == "UnderlineInline") { return OrgTokenKind::UnderlineInline; } else
  if (value == "UnderlineInlineOpen") { return OrgTokenKind::UnderlineInlineOpen; } else
  if (value == "UnderlineInlineClose") { return OrgTokenKind::UnderlineInlineClose; } else
  if (value == "StrikeOpen") { return OrgTokenKind::StrikeOpen; } else
  if (value == "StrikeClose") { return OrgTokenKind::StrikeClose; } else
  if (value == "StrikeInline") { return OrgTokenKind::StrikeInline; } else
  if (value == "StrikeInlineOpen") { return OrgTokenKind::StrikeInlineOpen; } else
  if (value == "StrikeInlineClose") { return OrgTokenKind::StrikeInlineClose; } else
  if (value == "QuoteOpen") { return OrgTokenKind::QuoteOpen; } else
  if (value == "QuoteClose") { return OrgTokenKind::QuoteClose; } else
  if (value == "Punctuation") { return OrgTokenKind::Punctuation; } else
  if (value == "LinkOpen") { return OrgTokenKind::LinkOpen; } else
  if (value == "LinkClose") { return OrgTokenKind::LinkClose; } else
  if (value == "RawUrl") { return OrgTokenKind::RawUrl; } else
  if (value == "LinkTargetOpen") { return OrgTokenKind::LinkTargetOpen; } else
  if (value == "LinkTargetClose") { return OrgTokenKind::LinkTargetClose; } else
  if (value == "LinkInternal") { return OrgTokenKind::LinkInternal; } else
  if (value == "LinkProtocol") { return OrgTokenKind::LinkProtocol; } else
  if (value == "LinkFull") { return OrgTokenKind::LinkFull; } else
  if (value == "LinkPath") { return OrgTokenKind::LinkPath; } else
  if (value == "LinkTarget") { return OrgTokenKind::LinkTarget; } else
  if (value == "LinkExtraSeparator") { return OrgTokenKind::LinkExtraSeparator; } else
  if (value == "LinkExtra") { return OrgTokenKind::LinkExtra; } else
  if (value == "LinkDescriptionOpen") { return OrgTokenKind::LinkDescriptionOpen; } else
  if (value == "LinkDescriptionClose") { return OrgTokenKind::LinkDescriptionClose; } else
  if (value == "TextSeparator") { return OrgTokenKind::TextSeparator; } else
  if (value == "ParagraphStart") { return OrgTokenKind::ParagraphStart; } else
  if (value == "ParagraphEnd") { return OrgTokenKind::ParagraphEnd; } else
  if (value == "FootnoteStart") { return OrgTokenKind::FootnoteStart; } else
  if (value == "FootnoteEnd") { return OrgTokenKind::FootnoteEnd; } else
  if (value == "Word") { return OrgTokenKind::Word; } else
  if (value == "Escaped") { return OrgTokenKind::Escaped; } else
  if (value == "DoubleSlash") { return OrgTokenKind::DoubleSlash; } else
  if (value == "Newline") { return OrgTokenKind::Newline; } else
  if (value == "SkipSpace") { return OrgTokenKind::SkipSpace; } else
  if (value == "SkipNewline") { return OrgTokenKind::SkipNewline; } else
  if (value == "SkipAny") { return OrgTokenKind::SkipAny; } else
  if (value == "MaybeWord") { return OrgTokenKind::MaybeWord; } else
  if (value == "Space") { return OrgTokenKind::Space; } else
  if (value == "BigIdent") { return OrgTokenKind::BigIdent; } else
  if (value == "RawText") { return OrgTokenKind::RawText; } else
  if (value == "InlineSrc") { return OrgTokenKind::InlineSrc; } else
  if (value == "InlineCall") { return OrgTokenKind::InlineCall; } else
  if (value == "CurlyStart") { return OrgTokenKind::CurlyStart; } else
  if (value == "CurlyEnd") { return OrgTokenKind::CurlyEnd; } else
  if (value == "SymbolStart") { return OrgTokenKind::SymbolStart; } else
  if (value == "Ident") { return OrgTokenKind::Ident; } else
  if (value == "DollarOpen") { return OrgTokenKind::DollarOpen; } else
  if (value == "DollarClose") { return OrgTokenKind::DollarClose; } else
  if (value == "DoubleDollarOpen") { return OrgTokenKind::DoubleDollarOpen; } else
  if (value == "DoubleDollarClose") { return OrgTokenKind::DoubleDollarClose; } else
  if (value == "LatexParOpen") { return OrgTokenKind::LatexParOpen; } else
  if (value == "LatexParClose") { return OrgTokenKind::LatexParClose; } else
  if (value == "LatexBraceOpen") { return OrgTokenKind::LatexBraceOpen; } else
  if (value == "LatexBraceClose") { return OrgTokenKind::LatexBraceClose; } else
  if (value == "LatexInlineRaw") { return OrgTokenKind::LatexInlineRaw; } else
  if (value == "DoubleAt") { return OrgTokenKind::DoubleAt; } else
  if (value == "AtBracket") { return OrgTokenKind::AtBracket; } else
  if (value == "AtMention") { return OrgTokenKind::AtMention; } else
  if (value == "HashTag") { return OrgTokenKind::HashTag; } else
  if (value == "HashTagSub") { return OrgTokenKind::HashTagSub; } else
  if (value == "HashTagOpen") { return OrgTokenKind::HashTagOpen; } else
  if (value == "HashTagClose") { return OrgTokenKind::HashTagClose; } else
  if (value == "Comma") { return OrgTokenKind::Comma; } else
  if (value == "ParOpen") { return OrgTokenKind::ParOpen; } else
  if (value == "ParClose") { return OrgTokenKind::ParClose; } else
  if (value == "Colon") { return OrgTokenKind::Colon; } else
  if (value == "Circumflex") { return OrgTokenKind::Circumflex; } else
  if (value == "MacroOpen") { return OrgTokenKind::MacroOpen; } else
  if (value == "MacroClose") { return OrgTokenKind::MacroClose; } else
  if (value == "MetaBraceOpen") { return OrgTokenKind::MetaBraceOpen; } else
  if (value == "MetaBraceBody") { return OrgTokenKind::MetaBraceBody; } else
  if (value == "MetaBraceClose") { return OrgTokenKind::MetaBraceClose; } else
  if (value == "MetaArgsOpen") { return OrgTokenKind::MetaArgsOpen; } else
  if (value == "MetaArgsBody") { return OrgTokenKind::MetaArgsBody; } else
  if (value == "MetaArgsClose") { return OrgTokenKind::MetaArgsClose; } else
  if (value == "SrcOpen") { return OrgTokenKind::SrcOpen; } else
  if (value == "SrcName") { return OrgTokenKind::SrcName; } else
  if (value == "SrcArgs") { return OrgTokenKind::SrcArgs; } else
  if (value == "SrcBody") { return OrgTokenKind::SrcBody; } else
  if (value == "SrcClose") { return OrgTokenKind::SrcClose; } else
  if (value == "CallOpen") { return OrgTokenKind::CallOpen; } else
  if (value == "CallName") { return OrgTokenKind::CallName; } else
  if (value == "CallInsideHeader") { return OrgTokenKind::CallInsideHeader; } else
  if (value == "CallArgs") { return OrgTokenKind::CallArgs; } else
  if (value == "EndHeader") { return OrgTokenKind::EndHeader; } else
  if (value == "CallClose") { return OrgTokenKind::CallClose; } else
  if (value == "CmdArguments") { return OrgTokenKind::CmdArguments; } else
  if (value == "TableBegin") { return OrgTokenKind::TableBegin; } else
  if (value == "TableEnd") { return OrgTokenKind::TableEnd; } else
  if (value == "CellBody") { return OrgTokenKind::CellBody; } else
  if (value == "RowSpec") { return OrgTokenKind::RowSpec; } else
  if (value == "CellSpec") { return OrgTokenKind::CellSpec; } else
  if (value == "Content") { return OrgTokenKind::Content; } else
  if (value == "ContentStart") { return OrgTokenKind::ContentStart; } else
  if (value == "ContentEnd") { return OrgTokenKind::ContentEnd; } else
  if (value == "PipeOpen") { return OrgTokenKind::PipeOpen; } else
  if (value == "PipeSeparator") { return OrgTokenKind::PipeSeparator; } else
  if (value == "PipeClose") { return OrgTokenKind::PipeClose; } else
  if (value == "PipeCellOpen") { return OrgTokenKind::PipeCellOpen; } else
  if (value == "DashSeparator") { return OrgTokenKind::DashSeparator; } else
  if (value == "CornerPlus") { return OrgTokenKind::CornerPlus; } else
  if (value == "Command") { return OrgTokenKind::Command; } else
  if (value == "CommandArgs") { return OrgTokenKind::CommandArgs; } else
  if (value == "Body") { return OrgTokenKind::Body; } else
  if (value == "LangName") { return OrgTokenKind::LangName; } else
  if (value == "DoubleAngleOpen") { return OrgTokenKind::DoubleAngleOpen; } else
  if (value == "DoubleAngleClose") { return OrgTokenKind::DoubleAngleClose; } else
  if (value == "TripleAngleOpen") { return OrgTokenKind::TripleAngleOpen; } else
  if (value == "TripleAngleClose") { return OrgTokenKind::TripleAngleClose; } else
  if (value == "AngleOpen") { return OrgTokenKind::AngleOpen; } else
  if (value == "AngleClose") { return OrgTokenKind::AngleClose; } else
  if (value == "TextBlock") { return OrgTokenKind::TextBlock; } else
  { return std::nullopt; }
}
QString enum_serde<OrgTokenKind>::to_string(OrgTokenKind value) {
  switch (value) {
    case OrgTokenKind::None: return "None";
    case OrgTokenKind::Eof: return "Eof";
    case OrgTokenKind::GroupStart: return "GroupStart";
    case OrgTokenKind::GroupEnd: return "GroupEnd";
    case OrgTokenKind::ErrorTerminator: return "ErrorTerminator";
    case OrgTokenKind::CommandPrefix: return "CommandPrefix";
    case OrgTokenKind::LineCommand: return "LineCommand";
    case OrgTokenKind::CommandBegin: return "CommandBegin";
    case OrgTokenKind::CommandEnd: return "CommandEnd";
    case OrgTokenKind::DoubleColon: return "DoubleColon";
    case OrgTokenKind::Text: return "Text";
    case OrgTokenKind::StmtList: return "StmtList";
    case OrgTokenKind::StmtListOpen: return "StmtListOpen";
    case OrgTokenKind::StmtListClose: return "StmtListClose";
    case OrgTokenKind::ListStart: return "ListStart";
    case OrgTokenKind::ListItemStart: return "ListItemStart";
    case OrgTokenKind::ListClock: return "ListClock";
    case OrgTokenKind::ListPlus: return "ListPlus";
    case OrgTokenKind::ListStar: return "ListStar";
    case OrgTokenKind::ListDescOpen: return "ListDescOpen";
    case OrgTokenKind::ListDescClose: return "ListDescClose";
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
    case OrgTokenKind::ImplicitTime: return "ImplicitTime";
    case OrgTokenKind::TimeDuration: return "TimeDuration";
    case OrgTokenKind::InactiveTimeBegin: return "InactiveTimeBegin";
    case OrgTokenKind::InactiveTimeEnd: return "InactiveTimeEnd";
    case OrgTokenKind::ActiveTimeBegin: return "ActiveTimeBegin";
    case OrgTokenKind::ActiveTimeEnd: return "ActiveTimeEnd";
    case OrgTokenKind::DynamicTimeContent: return "DynamicTimeContent";
    case OrgTokenKind::StaticTimeDatePart: return "StaticTimeDatePart";
    case OrgTokenKind::StaticTimeDayPart: return "StaticTimeDayPart";
    case OrgTokenKind::StaticTimeClockPart: return "StaticTimeClockPart";
    case OrgTokenKind::StaticTimeRepeater: return "StaticTimeRepeater";
    case OrgTokenKind::TimeDash: return "TimeDash";
    case OrgTokenKind::TimeArrow: return "TimeArrow";
    case OrgTokenKind::Comment: return "Comment";
    case OrgTokenKind::ListDoubleColon: return "ListDoubleColon";
    case OrgTokenKind::CommandArgumentsBegin: return "CommandArgumentsBegin";
    case OrgTokenKind::CommandArgumentsEnd: return "CommandArgumentsEnd";
    case OrgTokenKind::CommandKey: return "CommandKey";
    case OrgTokenKind::CommandValue: return "CommandValue";
    case OrgTokenKind::CommandFlag: return "CommandFlag";
    case OrgTokenKind::CommandBracket: return "CommandBracket";
    case OrgTokenKind::ColonLiteral: return "ColonLiteral";
    case OrgTokenKind::ColonIdent: return "ColonIdent";
    case OrgTokenKind::ColonProperties: return "ColonProperties";
    case OrgTokenKind::ColonDescription: return "ColonDescription";
    case OrgTokenKind::ColonEnd: return "ColonEnd";
    case OrgTokenKind::ColonLogbook: return "ColonLogbook";
    case OrgTokenKind::RawLogbook: return "RawLogbook";
    case OrgTokenKind::LogbookStart: return "LogbookStart";
    case OrgTokenKind::LogbookEnd: return "LogbookEnd";
    case OrgTokenKind::RawProperty: return "RawProperty";
    case OrgTokenKind::Link: return "Link";
    case OrgTokenKind::CommandContentStart: return "CommandContentStart";
    case OrgTokenKind::CommandContentEnd: return "CommandContentEnd";
    case OrgTokenKind::CodeContent: return "CodeContent";
    case OrgTokenKind::CodeContentBegin: return "CodeContentBegin";
    case OrgTokenKind::CodeContentEnd: return "CodeContentEnd";
    case OrgTokenKind::CodeText: return "CodeText";
    case OrgTokenKind::TableContent: return "TableContent";
    case OrgTokenKind::QuoteContent: return "QuoteContent";
    case OrgTokenKind::BackendPass: return "BackendPass";
    case OrgTokenKind::LogBook: return "LogBook";
    case OrgTokenKind::Drawer: return "Drawer";
    case OrgTokenKind::Indent: return "Indent";
    case OrgTokenKind::Dedent: return "Dedent";
    case OrgTokenKind::SameIndent: return "SameIndent";
    case OrgTokenKind::NoIndent: return "NoIndent";
    case OrgTokenKind::BoldOpen: return "BoldOpen";
    case OrgTokenKind::BoldClose: return "BoldClose";
    case OrgTokenKind::BoldInline: return "BoldInline";
    case OrgTokenKind::BoldInlineOpen: return "BoldInlineOpen";
    case OrgTokenKind::BoldInlineClose: return "BoldInlineClose";
    case OrgTokenKind::ItalicOpen: return "ItalicOpen";
    case OrgTokenKind::ItalicClose: return "ItalicClose";
    case OrgTokenKind::ItalicInline: return "ItalicInline";
    case OrgTokenKind::ItalicInlineOpen: return "ItalicInlineOpen";
    case OrgTokenKind::ItalicInlineClose: return "ItalicInlineClose";
    case OrgTokenKind::VerbatimOpen: return "VerbatimOpen";
    case OrgTokenKind::VerbatimClose: return "VerbatimClose";
    case OrgTokenKind::VerbatimInline: return "VerbatimInline";
    case OrgTokenKind::VerbatimInlineOpen: return "VerbatimInlineOpen";
    case OrgTokenKind::VerbatimInlineClose: return "VerbatimInlineClose";
    case OrgTokenKind::MonospaceOpen: return "MonospaceOpen";
    case OrgTokenKind::MonospaceClose: return "MonospaceClose";
    case OrgTokenKind::MonospaceInline: return "MonospaceInline";
    case OrgTokenKind::MonospaceInlineOpen: return "MonospaceInlineOpen";
    case OrgTokenKind::MonospaceInlineClose: return "MonospaceInlineClose";
    case OrgTokenKind::BacktickOpen: return "BacktickOpen";
    case OrgTokenKind::BacktickClose: return "BacktickClose";
    case OrgTokenKind::BacktickInline: return "BacktickInline";
    case OrgTokenKind::BacktickInlineOpen: return "BacktickInlineOpen";
    case OrgTokenKind::BacktickInlineClose: return "BacktickInlineClose";
    case OrgTokenKind::UnderlineOpen: return "UnderlineOpen";
    case OrgTokenKind::UnderlineClose: return "UnderlineClose";
    case OrgTokenKind::UnderlineInline: return "UnderlineInline";
    case OrgTokenKind::UnderlineInlineOpen: return "UnderlineInlineOpen";
    case OrgTokenKind::UnderlineInlineClose: return "UnderlineInlineClose";
    case OrgTokenKind::StrikeOpen: return "StrikeOpen";
    case OrgTokenKind::StrikeClose: return "StrikeClose";
    case OrgTokenKind::StrikeInline: return "StrikeInline";
    case OrgTokenKind::StrikeInlineOpen: return "StrikeInlineOpen";
    case OrgTokenKind::StrikeInlineClose: return "StrikeInlineClose";
    case OrgTokenKind::QuoteOpen: return "QuoteOpen";
    case OrgTokenKind::QuoteClose: return "QuoteClose";
    case OrgTokenKind::Punctuation: return "Punctuation";
    case OrgTokenKind::LinkOpen: return "LinkOpen";
    case OrgTokenKind::LinkClose: return "LinkClose";
    case OrgTokenKind::RawUrl: return "RawUrl";
    case OrgTokenKind::LinkTargetOpen: return "LinkTargetOpen";
    case OrgTokenKind::LinkTargetClose: return "LinkTargetClose";
    case OrgTokenKind::LinkInternal: return "LinkInternal";
    case OrgTokenKind::LinkProtocol: return "LinkProtocol";
    case OrgTokenKind::LinkFull: return "LinkFull";
    case OrgTokenKind::LinkPath: return "LinkPath";
    case OrgTokenKind::LinkTarget: return "LinkTarget";
    case OrgTokenKind::LinkExtraSeparator: return "LinkExtraSeparator";
    case OrgTokenKind::LinkExtra: return "LinkExtra";
    case OrgTokenKind::LinkDescriptionOpen: return "LinkDescriptionOpen";
    case OrgTokenKind::LinkDescriptionClose: return "LinkDescriptionClose";
    case OrgTokenKind::TextSeparator: return "TextSeparator";
    case OrgTokenKind::ParagraphStart: return "ParagraphStart";
    case OrgTokenKind::ParagraphEnd: return "ParagraphEnd";
    case OrgTokenKind::FootnoteStart: return "FootnoteStart";
    case OrgTokenKind::FootnoteEnd: return "FootnoteEnd";
    case OrgTokenKind::Word: return "Word";
    case OrgTokenKind::Escaped: return "Escaped";
    case OrgTokenKind::DoubleSlash: return "DoubleSlash";
    case OrgTokenKind::Newline: return "Newline";
    case OrgTokenKind::SkipSpace: return "SkipSpace";
    case OrgTokenKind::SkipNewline: return "SkipNewline";
    case OrgTokenKind::SkipAny: return "SkipAny";
    case OrgTokenKind::MaybeWord: return "MaybeWord";
    case OrgTokenKind::Space: return "Space";
    case OrgTokenKind::BigIdent: return "BigIdent";
    case OrgTokenKind::RawText: return "RawText";
    case OrgTokenKind::InlineSrc: return "InlineSrc";
    case OrgTokenKind::InlineCall: return "InlineCall";
    case OrgTokenKind::CurlyStart: return "CurlyStart";
    case OrgTokenKind::CurlyEnd: return "CurlyEnd";
    case OrgTokenKind::SymbolStart: return "SymbolStart";
    case OrgTokenKind::Ident: return "Ident";
    case OrgTokenKind::DollarOpen: return "DollarOpen";
    case OrgTokenKind::DollarClose: return "DollarClose";
    case OrgTokenKind::DoubleDollarOpen: return "DoubleDollarOpen";
    case OrgTokenKind::DoubleDollarClose: return "DoubleDollarClose";
    case OrgTokenKind::LatexParOpen: return "LatexParOpen";
    case OrgTokenKind::LatexParClose: return "LatexParClose";
    case OrgTokenKind::LatexBraceOpen: return "LatexBraceOpen";
    case OrgTokenKind::LatexBraceClose: return "LatexBraceClose";
    case OrgTokenKind::LatexInlineRaw: return "LatexInlineRaw";
    case OrgTokenKind::DoubleAt: return "DoubleAt";
    case OrgTokenKind::AtBracket: return "AtBracket";
    case OrgTokenKind::AtMention: return "AtMention";
    case OrgTokenKind::HashTag: return "HashTag";
    case OrgTokenKind::HashTagSub: return "HashTagSub";
    case OrgTokenKind::HashTagOpen: return "HashTagOpen";
    case OrgTokenKind::HashTagClose: return "HashTagClose";
    case OrgTokenKind::Comma: return "Comma";
    case OrgTokenKind::ParOpen: return "ParOpen";
    case OrgTokenKind::ParClose: return "ParClose";
    case OrgTokenKind::Colon: return "Colon";
    case OrgTokenKind::Circumflex: return "Circumflex";
    case OrgTokenKind::MacroOpen: return "MacroOpen";
    case OrgTokenKind::MacroClose: return "MacroClose";
    case OrgTokenKind::MetaBraceOpen: return "MetaBraceOpen";
    case OrgTokenKind::MetaBraceBody: return "MetaBraceBody";
    case OrgTokenKind::MetaBraceClose: return "MetaBraceClose";
    case OrgTokenKind::MetaArgsOpen: return "MetaArgsOpen";
    case OrgTokenKind::MetaArgsBody: return "MetaArgsBody";
    case OrgTokenKind::MetaArgsClose: return "MetaArgsClose";
    case OrgTokenKind::SrcOpen: return "SrcOpen";
    case OrgTokenKind::SrcName: return "SrcName";
    case OrgTokenKind::SrcArgs: return "SrcArgs";
    case OrgTokenKind::SrcBody: return "SrcBody";
    case OrgTokenKind::SrcClose: return "SrcClose";
    case OrgTokenKind::CallOpen: return "CallOpen";
    case OrgTokenKind::CallName: return "CallName";
    case OrgTokenKind::CallInsideHeader: return "CallInsideHeader";
    case OrgTokenKind::CallArgs: return "CallArgs";
    case OrgTokenKind::EndHeader: return "EndHeader";
    case OrgTokenKind::CallClose: return "CallClose";
    case OrgTokenKind::CmdArguments: return "CmdArguments";
    case OrgTokenKind::TableBegin: return "TableBegin";
    case OrgTokenKind::TableEnd: return "TableEnd";
    case OrgTokenKind::CellBody: return "CellBody";
    case OrgTokenKind::RowSpec: return "RowSpec";
    case OrgTokenKind::CellSpec: return "CellSpec";
    case OrgTokenKind::Content: return "Content";
    case OrgTokenKind::ContentStart: return "ContentStart";
    case OrgTokenKind::ContentEnd: return "ContentEnd";
    case OrgTokenKind::PipeOpen: return "PipeOpen";
    case OrgTokenKind::PipeSeparator: return "PipeSeparator";
    case OrgTokenKind::PipeClose: return "PipeClose";
    case OrgTokenKind::PipeCellOpen: return "PipeCellOpen";
    case OrgTokenKind::DashSeparator: return "DashSeparator";
    case OrgTokenKind::CornerPlus: return "CornerPlus";
    case OrgTokenKind::Command: return "Command";
    case OrgTokenKind::CommandArgs: return "CommandArgs";
    case OrgTokenKind::Body: return "Body";
    case OrgTokenKind::LangName: return "LangName";
    case OrgTokenKind::DoubleAngleOpen: return "DoubleAngleOpen";
    case OrgTokenKind::DoubleAngleClose: return "DoubleAngleClose";
    case OrgTokenKind::TripleAngleOpen: return "TripleAngleOpen";
    case OrgTokenKind::TripleAngleClose: return "TripleAngleClose";
    case OrgTokenKind::AngleOpen: return "AngleOpen";
    case OrgTokenKind::AngleClose: return "AngleClose";
    case OrgTokenKind::TextBlock: return "TextBlock";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgCommandKind> enum_serde<OrgCommandKind>::from_string(QString value) {
  if (value == "None") { return OrgCommandKind::None; } else
  if (value == "Include") { return OrgCommandKind::Include; } else
  if (value == "Filetags") { return OrgCommandKind::Filetags; } else
  if (value == "Setupfile") { return OrgCommandKind::Setupfile; } else
  if (value == "Columns") { return OrgCommandKind::Columns; } else
  if (value == "OtherProperty") { return OrgCommandKind::OtherProperty; } else
  if (value == "BeginTable") { return OrgCommandKind::BeginTable; } else
  if (value == "EndTable") { return OrgCommandKind::EndTable; } else
  if (value == "Row") { return OrgCommandKind::Row; } else
  if (value == "Cell") { return OrgCommandKind::Cell; } else
  if (value == "BeginAdmonition") { return OrgCommandKind::BeginAdmonition; } else
  if (value == "EndAdmonition") { return OrgCommandKind::EndAdmonition; } else
  if (value == "BeginDynamic") { return OrgCommandKind::BeginDynamic; } else
  if (value == "EndDynamic") { return OrgCommandKind::EndDynamic; } else
  if (value == "BeginCenter") { return OrgCommandKind::BeginCenter; } else
  if (value == "EndCenter") { return OrgCommandKind::EndCenter; } else
  if (value == "BeginQuote") { return OrgCommandKind::BeginQuote; } else
  if (value == "EndQuote") { return OrgCommandKind::EndQuote; } else
  if (value == "BeginSrc") { return OrgCommandKind::BeginSrc; } else
  if (value == "EndSrc") { return OrgCommandKind::EndSrc; } else
  if (value == "BeginExport") { return OrgCommandKind::BeginExport; } else
  if (value == "EndExport") { return OrgCommandKind::EndExport; } else
  if (value == "BeginExample") { return OrgCommandKind::BeginExample; } else
  if (value == "EndExample") { return OrgCommandKind::EndExample; } else
  if (value == "BeginDetails") { return OrgCommandKind::BeginDetails; } else
  if (value == "EndDetails") { return OrgCommandKind::EndDetails; } else
  if (value == "BeginSummary") { return OrgCommandKind::BeginSummary; } else
  if (value == "EndSummary") { return OrgCommandKind::EndSummary; } else
  if (value == "LatexClassOptions") { return OrgCommandKind::LatexClassOptions; } else
  if (value == "LatexClass") { return OrgCommandKind::LatexClass; } else
  if (value == "LatexCompiler") { return OrgCommandKind::LatexCompiler; } else
  if (value == "AttrLatex") { return OrgCommandKind::AttrLatex; } else
  if (value == "AttrImg") { return OrgCommandKind::AttrImg; } else
  if (value == "AttrHtml") { return OrgCommandKind::AttrHtml; } else
  if (value == "HtmlHead") { return OrgCommandKind::HtmlHead; } else
  if (value == "Language") { return OrgCommandKind::Language; } else
  if (value == "Options") { return OrgCommandKind::Options; } else
  if (value == "Title") { return OrgCommandKind::Title; } else
  if (value == "Property") { return OrgCommandKind::Property; } else
  if (value == "Author") { return OrgCommandKind::Author; } else
  if (value == "Bind") { return OrgCommandKind::Bind; } else
  if (value == "Creator") { return OrgCommandKind::Creator; } else
  if (value == "LatexHeader") { return OrgCommandKind::LatexHeader; } else
  if (value == "Results") { return OrgCommandKind::Results; } else
  if (value == "Call") { return OrgCommandKind::Call; } else
  if (value == "Name") { return OrgCommandKind::Name; } else
  if (value == "Caption") { return OrgCommandKind::Caption; } else
  if (value == "Header") { return OrgCommandKind::Header; } else
  if (value == "TableFormula") { return OrgCommandKind::TableFormula; } else
  { return std::nullopt; }
}
QString enum_serde<OrgCommandKind>::to_string(OrgCommandKind value) {
  switch (value) {
    case OrgCommandKind::None: return "None";
    case OrgCommandKind::Include: return "Include";
    case OrgCommandKind::Filetags: return "Filetags";
    case OrgCommandKind::Setupfile: return "Setupfile";
    case OrgCommandKind::Columns: return "Columns";
    case OrgCommandKind::OtherProperty: return "OtherProperty";
    case OrgCommandKind::BeginTable: return "BeginTable";
    case OrgCommandKind::EndTable: return "EndTable";
    case OrgCommandKind::Row: return "Row";
    case OrgCommandKind::Cell: return "Cell";
    case OrgCommandKind::BeginAdmonition: return "BeginAdmonition";
    case OrgCommandKind::EndAdmonition: return "EndAdmonition";
    case OrgCommandKind::BeginDynamic: return "BeginDynamic";
    case OrgCommandKind::EndDynamic: return "EndDynamic";
    case OrgCommandKind::BeginCenter: return "BeginCenter";
    case OrgCommandKind::EndCenter: return "EndCenter";
    case OrgCommandKind::BeginQuote: return "BeginQuote";
    case OrgCommandKind::EndQuote: return "EndQuote";
    case OrgCommandKind::BeginSrc: return "BeginSrc";
    case OrgCommandKind::EndSrc: return "EndSrc";
    case OrgCommandKind::BeginExport: return "BeginExport";
    case OrgCommandKind::EndExport: return "EndExport";
    case OrgCommandKind::BeginExample: return "BeginExample";
    case OrgCommandKind::EndExample: return "EndExample";
    case OrgCommandKind::BeginDetails: return "BeginDetails";
    case OrgCommandKind::EndDetails: return "EndDetails";
    case OrgCommandKind::BeginSummary: return "BeginSummary";
    case OrgCommandKind::EndSummary: return "EndSummary";
    case OrgCommandKind::LatexClassOptions: return "LatexClassOptions";
    case OrgCommandKind::LatexClass: return "LatexClass";
    case OrgCommandKind::LatexCompiler: return "LatexCompiler";
    case OrgCommandKind::AttrLatex: return "AttrLatex";
    case OrgCommandKind::AttrImg: return "AttrImg";
    case OrgCommandKind::AttrHtml: return "AttrHtml";
    case OrgCommandKind::HtmlHead: return "HtmlHead";
    case OrgCommandKind::Language: return "Language";
    case OrgCommandKind::Options: return "Options";
    case OrgCommandKind::Title: return "Title";
    case OrgCommandKind::Property: return "Property";
    case OrgCommandKind::Author: return "Author";
    case OrgCommandKind::Bind: return "Bind";
    case OrgCommandKind::Creator: return "Creator";
    case OrgCommandKind::LatexHeader: return "LatexHeader";
    case OrgCommandKind::Results: return "Results";
    case OrgCommandKind::Call: return "Call";
    case OrgCommandKind::Name: return "Name";
    case OrgCommandKind::Caption: return "Caption";
    case OrgCommandKind::Header: return "Header";
    case OrgCommandKind::TableFormula: return "TableFormula";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgPropertyKind> enum_serde<OrgPropertyKind>::from_string(QString value) {
  if (value == "Title") { return OrgPropertyKind::Title; } else
  if (value == "Author") { return OrgPropertyKind::Author; } else
  if (value == "Date") { return OrgPropertyKind::Date; } else
  if (value == "Email") { return OrgPropertyKind::Email; } else
  if (value == "Language") { return OrgPropertyKind::Language; } else
  if (value == "Url") { return OrgPropertyKind::Url; } else
  if (value == "SourceUrl") { return OrgPropertyKind::SourceUrl; } else
  if (value == "AttrImg") { return OrgPropertyKind::AttrImg; } else
  if (value == "Toplevel") { return OrgPropertyKind::Toplevel; } else
  if (value == "Blocker") { return OrgPropertyKind::Blocker; } else
  if (value == "Created") { return OrgPropertyKind::Created; } else
  if (value == "Unnumbered") { return OrgPropertyKind::Unnumbered; } else
  if (value == "Trigger") { return OrgPropertyKind::Trigger; } else
  if (value == "Ordered") { return OrgPropertyKind::Ordered; } else
  if (value == "Noblocking") { return OrgPropertyKind::Noblocking; } else
  if (value == "ExportOptions") { return OrgPropertyKind::ExportOptions; } else
  if (value == "BackendExportOptions") { return OrgPropertyKind::BackendExportOptions; } else
  if (value == "AttrBackend") { return OrgPropertyKind::AttrBackend; } else
  if (value == "ColumnSpec") { return OrgPropertyKind::ColumnSpec; } else
  if (value == "Name") { return OrgPropertyKind::Name; } else
  if (value == "Caption") { return OrgPropertyKind::Caption; } else
  if (value == "LinkAbbrev") { return OrgPropertyKind::LinkAbbrev; } else
  if (value == "Filetags") { return OrgPropertyKind::Filetags; } else
  if (value == "TagConf") { return OrgPropertyKind::TagConf; } else
  if (value == "LatexHeader") { return OrgPropertyKind::LatexHeader; } else
  if (value == "OtherProperty") { return OrgPropertyKind::OtherProperty; } else
  if (value == "Id") { return OrgPropertyKind::Id; } else
  { return std::nullopt; }
}
QString enum_serde<OrgPropertyKind>::to_string(OrgPropertyKind value) {
  switch (value) {
    case OrgPropertyKind::Title: return "Title";
    case OrgPropertyKind::Author: return "Author";
    case OrgPropertyKind::Date: return "Date";
    case OrgPropertyKind::Email: return "Email";
    case OrgPropertyKind::Language: return "Language";
    case OrgPropertyKind::Url: return "Url";
    case OrgPropertyKind::SourceUrl: return "SourceUrl";
    case OrgPropertyKind::AttrImg: return "AttrImg";
    case OrgPropertyKind::Toplevel: return "Toplevel";
    case OrgPropertyKind::Blocker: return "Blocker";
    case OrgPropertyKind::Created: return "Created";
    case OrgPropertyKind::Unnumbered: return "Unnumbered";
    case OrgPropertyKind::Trigger: return "Trigger";
    case OrgPropertyKind::Ordered: return "Ordered";
    case OrgPropertyKind::Noblocking: return "Noblocking";
    case OrgPropertyKind::ExportOptions: return "ExportOptions";
    case OrgPropertyKind::BackendExportOptions: return "BackendExportOptions";
    case OrgPropertyKind::AttrBackend: return "AttrBackend";
    case OrgPropertyKind::ColumnSpec: return "ColumnSpec";
    case OrgPropertyKind::Name: return "Name";
    case OrgPropertyKind::Caption: return "Caption";
    case OrgPropertyKind::LinkAbbrev: return "LinkAbbrev";
    case OrgPropertyKind::Filetags: return "Filetags";
    case OrgPropertyKind::TagConf: return "TagConf";
    case OrgPropertyKind::LatexHeader: return "LatexHeader";
    case OrgPropertyKind::OtherProperty: return "OtherProperty";
    case OrgPropertyKind::Id: return "Id";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgUnnumberedKind> enum_serde<OrgUnnumberedKind>::from_string(QString value) {
  if (value == "Notoc") { return OrgUnnumberedKind::Notoc; } else
  if (value == "True") { return OrgUnnumberedKind::True; } else
  if (value == "False") { return OrgUnnumberedKind::False; } else
  { return std::nullopt; }
}
QString enum_serde<OrgUnnumberedKind>::to_string(OrgUnnumberedKind value) {
  switch (value) {
    case OrgUnnumberedKind::Notoc: return "Notoc";
    case OrgUnnumberedKind::True: return "True";
    case OrgUnnumberedKind::False: return "False";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgBlockLexerState> enum_serde<OrgBlockLexerState>::from_string(QString value) {
  if (value == "None") { return OrgBlockLexerState::None; } else
  if (value == "InHeader") { return OrgBlockLexerState::InHeader; } else
  if (value == "InBody") { return OrgBlockLexerState::InBody; } else
  if (value == "Ended") { return OrgBlockLexerState::Ended; } else
  if (value == "Complete") { return OrgBlockLexerState::Complete; } else
  { return std::nullopt; }
}
QString enum_serde<OrgBlockLexerState>::to_string(OrgBlockLexerState value) {
  switch (value) {
    case OrgBlockLexerState::None: return "None";
    case OrgBlockLexerState::InHeader: return "InHeader";
    case OrgBlockLexerState::InBody: return "InBody";
    case OrgBlockLexerState::Ended: return "Ended";
    case OrgBlockLexerState::Complete: return "Complete";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}
Opt<OrgSemKind> enum_serde<OrgSemKind>::from_string(QString value) {
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
QString enum_serde<OrgSemKind>::to_string(OrgSemKind value) {
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