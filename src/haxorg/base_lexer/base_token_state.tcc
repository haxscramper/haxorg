
std::string OrgLexerImpl::state_name(int state) {
    switch(state) {
        case 0: return "INITIAL";
        case 1: return "COMMAND_TEXT";
        case 2: return "SUBTREE_HEAD";
        case 3: return "LEAD";
        case 4: return "COMMAND";
        case 5: return "COMMAND_RAW";
        case 6: return "COMMAND_EXAMPLE";
        case 7: return "COMMAND_EXPORT";
        case 8: return "COMMAND_SRC";
        case 9: return "COMMAND_ARGS";
        case 10: return "COMMAND_TBLFM";
        case 11: return "BODY_SRC";
        case 12: return "BODY_EXPORT";
        case 13: return "PROPERTIES";
        case 14: return "PROPERTY_LITERAL";
        case 15: return "PROPERTY_ARGUMENT";
        case 16: return "sub_state_http_link";
        case 17: return "sub_state_link_protocol_split";
        case 18: return "sub_state_raw_dsl_link";
        case 19: return "sub_state_no_protocol_file_link";
        case 20: return "sub_state_link_protocol_internal";
        case 21: return "sub_state_timestamp_repeater";
        default: return std::to_string(state);
    }
}

std::string enum_serde<OrgTokenKind>::to_string(const OrgTokenKind &value) {
    switch(value) {
        case OrgTokenKind::Ampersand: return "Ampersand";
        case OrgTokenKind::AngleBegin: return "AngleBegin";
        case OrgTokenKind::AngleEnd: return "AngleEnd";
        case OrgTokenKind::AnyPunct: return "AnyPunct";
        case OrgTokenKind::Asterisk: return "Asterisk";
        case OrgTokenKind::At: return "At";
        case OrgTokenKind::Backtick: return "Backtick";
        case OrgTokenKind::BigIdent: return "BigIdent";
        case OrgTokenKind::BoldBegin: return "BoldBegin";
        case OrgTokenKind::BoldEnd: return "BoldEnd";
        case OrgTokenKind::BoldUnknown: return "BoldUnknown";
        case OrgTokenKind::BraceBegin: return "BraceBegin";
        case OrgTokenKind::BraceEnd: return "BraceEnd";
        case OrgTokenKind::Checkbox: return "Checkbox";
        case OrgTokenKind::Circumflex: return "Circumflex";
        case OrgTokenKind::CmdAdmonitionEnd: return "CmdAdmonitionEnd";
        case OrgTokenKind::CmdAttr: return "CmdAttr";
        case OrgTokenKind::CmdAuthor: return "CmdAuthor";
        case OrgTokenKind::CmdBindRaw: return "CmdBindRaw";
        case OrgTokenKind::CmdCall: return "CmdCall";
        case OrgTokenKind::CmdCaption: return "CmdCaption";
        case OrgTokenKind::CmdCategoryRaw: return "CmdCategoryRaw";
        case OrgTokenKind::CmdCell: return "CmdCell";
        case OrgTokenKind::CmdCellBegin: return "CmdCellBegin";
        case OrgTokenKind::CmdCellEnd: return "CmdCellEnd";
        case OrgTokenKind::CmdCenterBegin: return "CmdCenterBegin";
        case OrgTokenKind::CmdCenterEnd: return "CmdCenterEnd";
        case OrgTokenKind::CmdColonIdent: return "CmdColonIdent";
        case OrgTokenKind::CmdColumns: return "CmdColumns";
        case OrgTokenKind::CmdCommentBegin: return "CmdCommentBegin";
        case OrgTokenKind::CmdCommentEnd: return "CmdCommentEnd";
        case OrgTokenKind::CmdConstants: return "CmdConstants";
        case OrgTokenKind::CmdContentBegin: return "CmdContentBegin";
        case OrgTokenKind::CmdContentEnd: return "CmdContentEnd";
        case OrgTokenKind::CmdCreator: return "CmdCreator";
        case OrgTokenKind::CmdCustomRaw: return "CmdCustomRaw";
        case OrgTokenKind::CmdDateRaw: return "CmdDateRaw";
        case OrgTokenKind::CmdDescription: return "CmdDescription";
        case OrgTokenKind::CmdDrawersRaw: return "CmdDrawersRaw";
        case OrgTokenKind::CmdDynamicBegin: return "CmdDynamicBegin";
        case OrgTokenKind::CmdDynamicBlockBegin: return "CmdDynamicBlockBegin";
        case OrgTokenKind::CmdDynamicBlockEnd: return "CmdDynamicBlockEnd";
        case OrgTokenKind::CmdDynamicEnd: return "CmdDynamicEnd";
        case OrgTokenKind::CmdEmailRaw: return "CmdEmailRaw";
        case OrgTokenKind::CmdExampleBegin: return "CmdExampleBegin";
        case OrgTokenKind::CmdExampleEnd: return "CmdExampleEnd";
        case OrgTokenKind::CmdExampleLine: return "CmdExampleLine";
        case OrgTokenKind::CmdExcludeTagsRaw: return "CmdExcludeTagsRaw";
        case OrgTokenKind::CmdExportBegin: return "CmdExportBegin";
        case OrgTokenKind::CmdExportEnd: return "CmdExportEnd";
        case OrgTokenKind::CmdExportLine: return "CmdExportLine";
        case OrgTokenKind::CmdFiletags: return "CmdFiletags";
        case OrgTokenKind::CmdFlag: return "CmdFlag";
        case OrgTokenKind::CmdHeader: return "CmdHeader";
        case OrgTokenKind::CmdHtmlHeadRaw: return "CmdHtmlHeadRaw";
        case OrgTokenKind::CmdInclude: return "CmdInclude";
        case OrgTokenKind::CmdLanguage: return "CmdLanguage";
        case OrgTokenKind::CmdLatexClass: return "CmdLatexClass";
        case OrgTokenKind::CmdLatexClassOptions: return "CmdLatexClassOptions";
        case OrgTokenKind::CmdLatexCompiler: return "CmdLatexCompiler";
        case OrgTokenKind::CmdLatexHeader: return "CmdLatexHeader";
        case OrgTokenKind::CmdLatexHeaderExtraRaw: return "CmdLatexHeaderExtraRaw";
        case OrgTokenKind::CmdLinkRaw: return "CmdLinkRaw";
        case OrgTokenKind::CmdMacroRaw: return "CmdMacroRaw";
        case OrgTokenKind::CmdName: return "CmdName";
        case OrgTokenKind::CmdOptions: return "CmdOptions";
        case OrgTokenKind::CmdPrefix: return "CmdPrefix";
        case OrgTokenKind::CmdPrioritiesRaw: return "CmdPrioritiesRaw";
        case OrgTokenKind::CmdPropertyArgs: return "CmdPropertyArgs";
        case OrgTokenKind::CmdPropertyRaw: return "CmdPropertyRaw";
        case OrgTokenKind::CmdPropertyText: return "CmdPropertyText";
        case OrgTokenKind::CmdQuoteBegin: return "CmdQuoteBegin";
        case OrgTokenKind::CmdQuoteEnd: return "CmdQuoteEnd";
        case OrgTokenKind::CmdRawArg: return "CmdRawArg";
        case OrgTokenKind::CmdResults: return "CmdResults";
        case OrgTokenKind::CmdRow: return "CmdRow";
        case OrgTokenKind::CmdRowBegin: return "CmdRowBegin";
        case OrgTokenKind::CmdRowEnd: return "CmdRowEnd";
        case OrgTokenKind::CmdSelectTagsRaw: return "CmdSelectTagsRaw";
        case OrgTokenKind::CmdSeqTodoRaw: return "CmdSeqTodoRaw";
        case OrgTokenKind::CmdSetupfileRaw: return "CmdSetupfileRaw";
        case OrgTokenKind::CmdSrcBegin: return "CmdSrcBegin";
        case OrgTokenKind::CmdSrcEnd: return "CmdSrcEnd";
        case OrgTokenKind::CmdStartup: return "CmdStartup";
        case OrgTokenKind::CmdTableBegin: return "CmdTableBegin";
        case OrgTokenKind::CmdTableEnd: return "CmdTableEnd";
        case OrgTokenKind::CmdTagsRaw: return "CmdTagsRaw";
        case OrgTokenKind::CmdTblfm: return "CmdTblfm";
        case OrgTokenKind::CmdTitle: return "CmdTitle";
        case OrgTokenKind::CmdVerseBegin: return "CmdVerseBegin";
        case OrgTokenKind::CmdVerseEnd: return "CmdVerseEnd";
        case OrgTokenKind::Colon: return "Colon";
        case OrgTokenKind::ColonArgumentsProperty: return "ColonArgumentsProperty";
        case OrgTokenKind::ColonEnd: return "ColonEnd";
        case OrgTokenKind::ColonExampleLine: return "ColonExampleLine";
        case OrgTokenKind::ColonLiteralProperty: return "ColonLiteralProperty";
        case OrgTokenKind::ColonLogbook: return "ColonLogbook";
        case OrgTokenKind::ColonProperties: return "ColonProperties";
        case OrgTokenKind::ColonPropertyName: return "ColonPropertyName";
        case OrgTokenKind::ColonPropertyText: return "ColonPropertyText";
        case OrgTokenKind::Comma: return "Comma";
        case OrgTokenKind::Comment: return "Comment";
        case OrgTokenKind::CurlyBegin: return "CurlyBegin";
        case OrgTokenKind::CurlyEnd: return "CurlyEnd";
        case OrgTokenKind::Date: return "Date";
        case OrgTokenKind::Dedent: return "Dedent";
        case OrgTokenKind::Dollar: return "Dollar";
        case OrgTokenKind::DoubleAngleBegin: return "DoubleAngleBegin";
        case OrgTokenKind::DoubleAngleEnd: return "DoubleAngleEnd";
        case OrgTokenKind::DoubleColon: return "DoubleColon";
        case OrgTokenKind::DoubleDash: return "DoubleDash";
        case OrgTokenKind::DoubleHash: return "DoubleHash";
        case OrgTokenKind::DoubleQuote: return "DoubleQuote";
        case OrgTokenKind::DoubleSlash: return "DoubleSlash";
        case OrgTokenKind::DynamicTimeContent: return "DynamicTimeContent";
        case OrgTokenKind::EndOfFile: return "EndOfFile";
        case OrgTokenKind::Equals: return "Equals";
        case OrgTokenKind::Escaped: return "Escaped";
        case OrgTokenKind::Exclamation: return "Exclamation";
        case OrgTokenKind::FootnoteInlineBegin: return "FootnoteInlineBegin";
        case OrgTokenKind::FootnoteLinked: return "FootnoteLinked";
        case OrgTokenKind::ForwardSlash: return "ForwardSlash";
        case OrgTokenKind::HashIdent: return "HashIdent";
        case OrgTokenKind::HashTagBegin: return "HashTagBegin";
        case OrgTokenKind::Indent: return "Indent";
        case OrgTokenKind::ItalicBegin: return "ItalicBegin";
        case OrgTokenKind::ItalicEnd: return "ItalicEnd";
        case OrgTokenKind::ItalicUnknown: return "ItalicUnknown";
        case OrgTokenKind::LatexInlineRaw: return "LatexInlineRaw";
        case OrgTokenKind::LatexParBegin: return "LatexParBegin";
        case OrgTokenKind::LatexParEnd: return "LatexParEnd";
        case OrgTokenKind::LeadingMinus: return "LeadingMinus";
        case OrgTokenKind::LeadingNumber: return "LeadingNumber";
        case OrgTokenKind::LeadingPipe: return "LeadingPipe";
        case OrgTokenKind::LeadingPlus: return "LeadingPlus";
        case OrgTokenKind::LeadingSpace: return "LeadingSpace";
        case OrgTokenKind::LineCommand: return "LineCommand";
        case OrgTokenKind::LinkBegin: return "LinkBegin";
        case OrgTokenKind::LinkDescriptionBegin: return "LinkDescriptionBegin";
        case OrgTokenKind::LinkDescriptionEnd: return "LinkDescriptionEnd";
        case OrgTokenKind::LinkEnd: return "LinkEnd";
        case OrgTokenKind::LinkFull: return "LinkFull";
        case OrgTokenKind::LinkProtocol: return "LinkProtocol";
        case OrgTokenKind::LinkProtocolAttachment: return "LinkProtocolAttachment";
        case OrgTokenKind::LinkProtocolCustomId: return "LinkProtocolCustomId";
        case OrgTokenKind::LinkProtocolFile: return "LinkProtocolFile";
        case OrgTokenKind::LinkProtocolHttp: return "LinkProtocolHttp";
        case OrgTokenKind::LinkProtocolId: return "LinkProtocolId";
        case OrgTokenKind::LinkProtocolInternal: return "LinkProtocolInternal";
        case OrgTokenKind::LinkProtocolTitle: return "LinkProtocolTitle";
        case OrgTokenKind::LinkSplit: return "LinkSplit";
        case OrgTokenKind::LinkTarget: return "LinkTarget";
        case OrgTokenKind::LinkTargetBegin: return "LinkTargetBegin";
        case OrgTokenKind::LinkTargetEnd: return "LinkTargetEnd";
        case OrgTokenKind::LinkTargetFile: return "LinkTargetFile";
        case OrgTokenKind::ListBegin: return "ListBegin";
        case OrgTokenKind::ListEnd: return "ListEnd";
        case OrgTokenKind::ListItemBegin: return "ListItemBegin";
        case OrgTokenKind::ListItemEnd: return "ListItemEnd";
        case OrgTokenKind::LongNewline: return "LongNewline";
        case OrgTokenKind::MediumNewline: return "MediumNewline";
        case OrgTokenKind::Minus: return "Minus";
        case OrgTokenKind::MiscUnicode: return "MiscUnicode";
        case OrgTokenKind::MonospaceBegin: return "MonospaceBegin";
        case OrgTokenKind::MonospaceEnd: return "MonospaceEnd";
        case OrgTokenKind::MonospaceUnknown: return "MonospaceUnknown";
        case OrgTokenKind::Newline: return "Newline";
        case OrgTokenKind::Number: return "Number";
        case OrgTokenKind::ParBegin: return "ParBegin";
        case OrgTokenKind::ParEnd: return "ParEnd";
        case OrgTokenKind::Percent: return "Percent";
        case OrgTokenKind::Pipe: return "Pipe";
        case OrgTokenKind::Placeholder: return "Placeholder";
        case OrgTokenKind::Plus: return "Plus";
        case OrgTokenKind::Punctuation: return "Punctuation";
        case OrgTokenKind::RawText: return "RawText";
        case OrgTokenKind::SameIndent: return "SameIndent";
        case OrgTokenKind::Semicolon: return "Semicolon";
        case OrgTokenKind::SingleQuote: return "SingleQuote";
        case OrgTokenKind::SrcContent: return "SrcContent";
        case OrgTokenKind::SrcTangleClose: return "SrcTangleClose";
        case OrgTokenKind::SrcTangleOpen: return "SrcTangleOpen";
        case OrgTokenKind::StmtListBegin: return "StmtListBegin";
        case OrgTokenKind::StmtListEnd: return "StmtListEnd";
        case OrgTokenKind::StrikeBegin: return "StrikeBegin";
        case OrgTokenKind::StrikeEnd: return "StrikeEnd";
        case OrgTokenKind::StrikeUnknown: return "StrikeUnknown";
        case OrgTokenKind::SubtreePriority: return "SubtreePriority";
        case OrgTokenKind::SubtreeStars: return "SubtreeStars";
        case OrgTokenKind::Symbol: return "Symbol";
        case OrgTokenKind::TableSeparator: return "TableSeparator";
        case OrgTokenKind::TextSeparator: return "TextSeparator";
        case OrgTokenKind::TextSrcBegin: return "TextSrcBegin";
        case OrgTokenKind::Tilda: return "Tilda";
        case OrgTokenKind::Time: return "Time";
        case OrgTokenKind::TimeArrow: return "TimeArrow";
        case OrgTokenKind::TimeRepeaterDuration: return "TimeRepeaterDuration";
        case OrgTokenKind::TimeRepeaterSpec: return "TimeRepeaterSpec";
        case OrgTokenKind::TimeWarnPeriod: return "TimeWarnPeriod";
        case OrgTokenKind::TrailingPipe: return "TrailingPipe";
        case OrgTokenKind::TreeClock: return "TreeClock";
        case OrgTokenKind::TreeTime: return "TreeTime";
        case OrgTokenKind::TripleAngleBegin: return "TripleAngleBegin";
        case OrgTokenKind::TripleAngleEnd: return "TripleAngleEnd";
        case OrgTokenKind::UnderlineBegin: return "UnderlineBegin";
        case OrgTokenKind::UnderlineEnd: return "UnderlineEnd";
        case OrgTokenKind::UnderlineUnknown: return "UnderlineUnknown";
        case OrgTokenKind::Unknown: return "Unknown";
        case OrgTokenKind::VerbatimBegin: return "VerbatimBegin";
        case OrgTokenKind::VerbatimEnd: return "VerbatimEnd";
        case OrgTokenKind::VerbatimUnknown: return "VerbatimUnknown";
        case OrgTokenKind::WeekdayName: return "WeekdayName";
        case OrgTokenKind::Whitespace: return "Whitespace";
        case OrgTokenKind::Word: return "Word";
    }
}

Opt<OrgTokenKind> enum_serde<OrgTokenKind>::from_string(std::string const& value) {
  if (value == "Ampersand") { return OrgTokenKind::Ampersand; } else
  if (value == "AngleBegin") { return OrgTokenKind::AngleBegin; } else
  if (value == "AngleEnd") { return OrgTokenKind::AngleEnd; } else
  if (value == "AnyPunct") { return OrgTokenKind::AnyPunct; } else
  if (value == "Asterisk") { return OrgTokenKind::Asterisk; } else
  if (value == "At") { return OrgTokenKind::At; } else
  if (value == "Backtick") { return OrgTokenKind::Backtick; } else
  if (value == "BigIdent") { return OrgTokenKind::BigIdent; } else
  if (value == "BoldBegin") { return OrgTokenKind::BoldBegin; } else
  if (value == "BoldEnd") { return OrgTokenKind::BoldEnd; } else
  if (value == "BoldUnknown") { return OrgTokenKind::BoldUnknown; } else
  if (value == "BraceBegin") { return OrgTokenKind::BraceBegin; } else
  if (value == "BraceEnd") { return OrgTokenKind::BraceEnd; } else
  if (value == "Checkbox") { return OrgTokenKind::Checkbox; } else
  if (value == "Circumflex") { return OrgTokenKind::Circumflex; } else
  if (value == "CmdAdmonitionEnd") { return OrgTokenKind::CmdAdmonitionEnd; } else
  if (value == "CmdAttr") { return OrgTokenKind::CmdAttr; } else
  if (value == "CmdAuthor") { return OrgTokenKind::CmdAuthor; } else
  if (value == "CmdBindRaw") { return OrgTokenKind::CmdBindRaw; } else
  if (value == "CmdCall") { return OrgTokenKind::CmdCall; } else
  if (value == "CmdCaption") { return OrgTokenKind::CmdCaption; } else
  if (value == "CmdCategoryRaw") { return OrgTokenKind::CmdCategoryRaw; } else
  if (value == "CmdCell") { return OrgTokenKind::CmdCell; } else
  if (value == "CmdCellBegin") { return OrgTokenKind::CmdCellBegin; } else
  if (value == "CmdCellEnd") { return OrgTokenKind::CmdCellEnd; } else
  if (value == "CmdCenterBegin") { return OrgTokenKind::CmdCenterBegin; } else
  if (value == "CmdCenterEnd") { return OrgTokenKind::CmdCenterEnd; } else
  if (value == "CmdColonIdent") { return OrgTokenKind::CmdColonIdent; } else
  if (value == "CmdColumns") { return OrgTokenKind::CmdColumns; } else
  if (value == "CmdCommentBegin") { return OrgTokenKind::CmdCommentBegin; } else
  if (value == "CmdCommentEnd") { return OrgTokenKind::CmdCommentEnd; } else
  if (value == "CmdConstants") { return OrgTokenKind::CmdConstants; } else
  if (value == "CmdContentBegin") { return OrgTokenKind::CmdContentBegin; } else
  if (value == "CmdContentEnd") { return OrgTokenKind::CmdContentEnd; } else
  if (value == "CmdCreator") { return OrgTokenKind::CmdCreator; } else
  if (value == "CmdCustomRaw") { return OrgTokenKind::CmdCustomRaw; } else
  if (value == "CmdDateRaw") { return OrgTokenKind::CmdDateRaw; } else
  if (value == "CmdDescription") { return OrgTokenKind::CmdDescription; } else
  if (value == "CmdDrawersRaw") { return OrgTokenKind::CmdDrawersRaw; } else
  if (value == "CmdDynamicBegin") { return OrgTokenKind::CmdDynamicBegin; } else
  if (value == "CmdDynamicBlockBegin") { return OrgTokenKind::CmdDynamicBlockBegin; } else
  if (value == "CmdDynamicBlockEnd") { return OrgTokenKind::CmdDynamicBlockEnd; } else
  if (value == "CmdDynamicEnd") { return OrgTokenKind::CmdDynamicEnd; } else
  if (value == "CmdEmailRaw") { return OrgTokenKind::CmdEmailRaw; } else
  if (value == "CmdExampleBegin") { return OrgTokenKind::CmdExampleBegin; } else
  if (value == "CmdExampleEnd") { return OrgTokenKind::CmdExampleEnd; } else
  if (value == "CmdExampleLine") { return OrgTokenKind::CmdExampleLine; } else
  if (value == "CmdExcludeTagsRaw") { return OrgTokenKind::CmdExcludeTagsRaw; } else
  if (value == "CmdExportBegin") { return OrgTokenKind::CmdExportBegin; } else
  if (value == "CmdExportEnd") { return OrgTokenKind::CmdExportEnd; } else
  if (value == "CmdExportLine") { return OrgTokenKind::CmdExportLine; } else
  if (value == "CmdFiletags") { return OrgTokenKind::CmdFiletags; } else
  if (value == "CmdFlag") { return OrgTokenKind::CmdFlag; } else
  if (value == "CmdHeader") { return OrgTokenKind::CmdHeader; } else
  if (value == "CmdHtmlHeadRaw") { return OrgTokenKind::CmdHtmlHeadRaw; } else
  if (value == "CmdInclude") { return OrgTokenKind::CmdInclude; } else
  if (value == "CmdLanguage") { return OrgTokenKind::CmdLanguage; } else
  if (value == "CmdLatexClass") { return OrgTokenKind::CmdLatexClass; } else
  if (value == "CmdLatexClassOptions") { return OrgTokenKind::CmdLatexClassOptions; } else
  if (value == "CmdLatexCompiler") { return OrgTokenKind::CmdLatexCompiler; } else
  if (value == "CmdLatexHeader") { return OrgTokenKind::CmdLatexHeader; } else
  if (value == "CmdLatexHeaderExtraRaw") { return OrgTokenKind::CmdLatexHeaderExtraRaw; } else
  if (value == "CmdLinkRaw") { return OrgTokenKind::CmdLinkRaw; } else
  if (value == "CmdMacroRaw") { return OrgTokenKind::CmdMacroRaw; } else
  if (value == "CmdName") { return OrgTokenKind::CmdName; } else
  if (value == "CmdOptions") { return OrgTokenKind::CmdOptions; } else
  if (value == "CmdPrefix") { return OrgTokenKind::CmdPrefix; } else
  if (value == "CmdPrioritiesRaw") { return OrgTokenKind::CmdPrioritiesRaw; } else
  if (value == "CmdPropertyArgs") { return OrgTokenKind::CmdPropertyArgs; } else
  if (value == "CmdPropertyRaw") { return OrgTokenKind::CmdPropertyRaw; } else
  if (value == "CmdPropertyText") { return OrgTokenKind::CmdPropertyText; } else
  if (value == "CmdQuoteBegin") { return OrgTokenKind::CmdQuoteBegin; } else
  if (value == "CmdQuoteEnd") { return OrgTokenKind::CmdQuoteEnd; } else
  if (value == "CmdRawArg") { return OrgTokenKind::CmdRawArg; } else
  if (value == "CmdResults") { return OrgTokenKind::CmdResults; } else
  if (value == "CmdRow") { return OrgTokenKind::CmdRow; } else
  if (value == "CmdRowBegin") { return OrgTokenKind::CmdRowBegin; } else
  if (value == "CmdRowEnd") { return OrgTokenKind::CmdRowEnd; } else
  if (value == "CmdSelectTagsRaw") { return OrgTokenKind::CmdSelectTagsRaw; } else
  if (value == "CmdSeqTodoRaw") { return OrgTokenKind::CmdSeqTodoRaw; } else
  if (value == "CmdSetupfileRaw") { return OrgTokenKind::CmdSetupfileRaw; } else
  if (value == "CmdSrcBegin") { return OrgTokenKind::CmdSrcBegin; } else
  if (value == "CmdSrcEnd") { return OrgTokenKind::CmdSrcEnd; } else
  if (value == "CmdStartup") { return OrgTokenKind::CmdStartup; } else
  if (value == "CmdTableBegin") { return OrgTokenKind::CmdTableBegin; } else
  if (value == "CmdTableEnd") { return OrgTokenKind::CmdTableEnd; } else
  if (value == "CmdTagsRaw") { return OrgTokenKind::CmdTagsRaw; } else
  if (value == "CmdTblfm") { return OrgTokenKind::CmdTblfm; } else
  if (value == "CmdTitle") { return OrgTokenKind::CmdTitle; } else
  if (value == "CmdVerseBegin") { return OrgTokenKind::CmdVerseBegin; } else
  if (value == "CmdVerseEnd") { return OrgTokenKind::CmdVerseEnd; } else
  if (value == "Colon") { return OrgTokenKind::Colon; } else
  if (value == "ColonArgumentsProperty") { return OrgTokenKind::ColonArgumentsProperty; } else
  if (value == "ColonEnd") { return OrgTokenKind::ColonEnd; } else
  if (value == "ColonExampleLine") { return OrgTokenKind::ColonExampleLine; } else
  if (value == "ColonLiteralProperty") { return OrgTokenKind::ColonLiteralProperty; } else
  if (value == "ColonLogbook") { return OrgTokenKind::ColonLogbook; } else
  if (value == "ColonProperties") { return OrgTokenKind::ColonProperties; } else
  if (value == "ColonPropertyName") { return OrgTokenKind::ColonPropertyName; } else
  if (value == "ColonPropertyText") { return OrgTokenKind::ColonPropertyText; } else
  if (value == "Comma") { return OrgTokenKind::Comma; } else
  if (value == "Comment") { return OrgTokenKind::Comment; } else
  if (value == "CurlyBegin") { return OrgTokenKind::CurlyBegin; } else
  if (value == "CurlyEnd") { return OrgTokenKind::CurlyEnd; } else
  if (value == "Date") { return OrgTokenKind::Date; } else
  if (value == "Dedent") { return OrgTokenKind::Dedent; } else
  if (value == "Dollar") { return OrgTokenKind::Dollar; } else
  if (value == "DoubleAngleBegin") { return OrgTokenKind::DoubleAngleBegin; } else
  if (value == "DoubleAngleEnd") { return OrgTokenKind::DoubleAngleEnd; } else
  if (value == "DoubleColon") { return OrgTokenKind::DoubleColon; } else
  if (value == "DoubleDash") { return OrgTokenKind::DoubleDash; } else
  if (value == "DoubleHash") { return OrgTokenKind::DoubleHash; } else
  if (value == "DoubleQuote") { return OrgTokenKind::DoubleQuote; } else
  if (value == "DoubleSlash") { return OrgTokenKind::DoubleSlash; } else
  if (value == "DynamicTimeContent") { return OrgTokenKind::DynamicTimeContent; } else
  if (value == "EndOfFile") { return OrgTokenKind::EndOfFile; } else
  if (value == "Equals") { return OrgTokenKind::Equals; } else
  if (value == "Escaped") { return OrgTokenKind::Escaped; } else
  if (value == "Exclamation") { return OrgTokenKind::Exclamation; } else
  if (value == "FootnoteInlineBegin") { return OrgTokenKind::FootnoteInlineBegin; } else
  if (value == "FootnoteLinked") { return OrgTokenKind::FootnoteLinked; } else
  if (value == "ForwardSlash") { return OrgTokenKind::ForwardSlash; } else
  if (value == "HashIdent") { return OrgTokenKind::HashIdent; } else
  if (value == "HashTagBegin") { return OrgTokenKind::HashTagBegin; } else
  if (value == "Indent") { return OrgTokenKind::Indent; } else
  if (value == "ItalicBegin") { return OrgTokenKind::ItalicBegin; } else
  if (value == "ItalicEnd") { return OrgTokenKind::ItalicEnd; } else
  if (value == "ItalicUnknown") { return OrgTokenKind::ItalicUnknown; } else
  if (value == "LatexInlineRaw") { return OrgTokenKind::LatexInlineRaw; } else
  if (value == "LatexParBegin") { return OrgTokenKind::LatexParBegin; } else
  if (value == "LatexParEnd") { return OrgTokenKind::LatexParEnd; } else
  if (value == "LeadingMinus") { return OrgTokenKind::LeadingMinus; } else
  if (value == "LeadingNumber") { return OrgTokenKind::LeadingNumber; } else
  if (value == "LeadingPipe") { return OrgTokenKind::LeadingPipe; } else
  if (value == "LeadingPlus") { return OrgTokenKind::LeadingPlus; } else
  if (value == "LeadingSpace") { return OrgTokenKind::LeadingSpace; } else
  if (value == "LineCommand") { return OrgTokenKind::LineCommand; } else
  if (value == "LinkBegin") { return OrgTokenKind::LinkBegin; } else
  if (value == "LinkDescriptionBegin") { return OrgTokenKind::LinkDescriptionBegin; } else
  if (value == "LinkDescriptionEnd") { return OrgTokenKind::LinkDescriptionEnd; } else
  if (value == "LinkEnd") { return OrgTokenKind::LinkEnd; } else
  if (value == "LinkFull") { return OrgTokenKind::LinkFull; } else
  if (value == "LinkProtocol") { return OrgTokenKind::LinkProtocol; } else
  if (value == "LinkProtocolAttachment") { return OrgTokenKind::LinkProtocolAttachment; } else
  if (value == "LinkProtocolCustomId") { return OrgTokenKind::LinkProtocolCustomId; } else
  if (value == "LinkProtocolFile") { return OrgTokenKind::LinkProtocolFile; } else
  if (value == "LinkProtocolHttp") { return OrgTokenKind::LinkProtocolHttp; } else
  if (value == "LinkProtocolId") { return OrgTokenKind::LinkProtocolId; } else
  if (value == "LinkProtocolInternal") { return OrgTokenKind::LinkProtocolInternal; } else
  if (value == "LinkProtocolTitle") { return OrgTokenKind::LinkProtocolTitle; } else
  if (value == "LinkSplit") { return OrgTokenKind::LinkSplit; } else
  if (value == "LinkTarget") { return OrgTokenKind::LinkTarget; } else
  if (value == "LinkTargetBegin") { return OrgTokenKind::LinkTargetBegin; } else
  if (value == "LinkTargetEnd") { return OrgTokenKind::LinkTargetEnd; } else
  if (value == "LinkTargetFile") { return OrgTokenKind::LinkTargetFile; } else
  if (value == "ListBegin") { return OrgTokenKind::ListBegin; } else
  if (value == "ListEnd") { return OrgTokenKind::ListEnd; } else
  if (value == "ListItemBegin") { return OrgTokenKind::ListItemBegin; } else
  if (value == "ListItemEnd") { return OrgTokenKind::ListItemEnd; } else
  if (value == "LongNewline") { return OrgTokenKind::LongNewline; } else
  if (value == "MediumNewline") { return OrgTokenKind::MediumNewline; } else
  if (value == "Minus") { return OrgTokenKind::Minus; } else
  if (value == "MiscUnicode") { return OrgTokenKind::MiscUnicode; } else
  if (value == "MonospaceBegin") { return OrgTokenKind::MonospaceBegin; } else
  if (value == "MonospaceEnd") { return OrgTokenKind::MonospaceEnd; } else
  if (value == "MonospaceUnknown") { return OrgTokenKind::MonospaceUnknown; } else
  if (value == "Newline") { return OrgTokenKind::Newline; } else
  if (value == "Number") { return OrgTokenKind::Number; } else
  if (value == "ParBegin") { return OrgTokenKind::ParBegin; } else
  if (value == "ParEnd") { return OrgTokenKind::ParEnd; } else
  if (value == "Percent") { return OrgTokenKind::Percent; } else
  if (value == "Pipe") { return OrgTokenKind::Pipe; } else
  if (value == "Placeholder") { return OrgTokenKind::Placeholder; } else
  if (value == "Plus") { return OrgTokenKind::Plus; } else
  if (value == "Punctuation") { return OrgTokenKind::Punctuation; } else
  if (value == "RawText") { return OrgTokenKind::RawText; } else
  if (value == "SameIndent") { return OrgTokenKind::SameIndent; } else
  if (value == "Semicolon") { return OrgTokenKind::Semicolon; } else
  if (value == "SingleQuote") { return OrgTokenKind::SingleQuote; } else
  if (value == "SrcContent") { return OrgTokenKind::SrcContent; } else
  if (value == "SrcTangleClose") { return OrgTokenKind::SrcTangleClose; } else
  if (value == "SrcTangleOpen") { return OrgTokenKind::SrcTangleOpen; } else
  if (value == "StmtListBegin") { return OrgTokenKind::StmtListBegin; } else
  if (value == "StmtListEnd") { return OrgTokenKind::StmtListEnd; } else
  if (value == "StrikeBegin") { return OrgTokenKind::StrikeBegin; } else
  if (value == "StrikeEnd") { return OrgTokenKind::StrikeEnd; } else
  if (value == "StrikeUnknown") { return OrgTokenKind::StrikeUnknown; } else
  if (value == "SubtreePriority") { return OrgTokenKind::SubtreePriority; } else
  if (value == "SubtreeStars") { return OrgTokenKind::SubtreeStars; } else
  if (value == "Symbol") { return OrgTokenKind::Symbol; } else
  if (value == "TableSeparator") { return OrgTokenKind::TableSeparator; } else
  if (value == "TextSeparator") { return OrgTokenKind::TextSeparator; } else
  if (value == "TextSrcBegin") { return OrgTokenKind::TextSrcBegin; } else
  if (value == "Tilda") { return OrgTokenKind::Tilda; } else
  if (value == "Time") { return OrgTokenKind::Time; } else
  if (value == "TimeArrow") { return OrgTokenKind::TimeArrow; } else
  if (value == "TimeRepeaterDuration") { return OrgTokenKind::TimeRepeaterDuration; } else
  if (value == "TimeRepeaterSpec") { return OrgTokenKind::TimeRepeaterSpec; } else
  if (value == "TimeWarnPeriod") { return OrgTokenKind::TimeWarnPeriod; } else
  if (value == "TrailingPipe") { return OrgTokenKind::TrailingPipe; } else
  if (value == "TreeClock") { return OrgTokenKind::TreeClock; } else
  if (value == "TreeTime") { return OrgTokenKind::TreeTime; } else
  if (value == "TripleAngleBegin") { return OrgTokenKind::TripleAngleBegin; } else
  if (value == "TripleAngleEnd") { return OrgTokenKind::TripleAngleEnd; } else
  if (value == "UnderlineBegin") { return OrgTokenKind::UnderlineBegin; } else
  if (value == "UnderlineEnd") { return OrgTokenKind::UnderlineEnd; } else
  if (value == "UnderlineUnknown") { return OrgTokenKind::UnderlineUnknown; } else
  if (value == "Unknown") { return OrgTokenKind::Unknown; } else
  if (value == "VerbatimBegin") { return OrgTokenKind::VerbatimBegin; } else
  if (value == "VerbatimEnd") { return OrgTokenKind::VerbatimEnd; } else
  if (value == "VerbatimUnknown") { return OrgTokenKind::VerbatimUnknown; } else
  if (value == "WeekdayName") { return OrgTokenKind::WeekdayName; } else
  if (value == "Whitespace") { return OrgTokenKind::Whitespace; } else
  if (value == "Word") { return OrgTokenKind::Word; } else
  { return std::nullopt; }
}

