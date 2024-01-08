
std::string BaseLexerImpl::state_name(int state) {
    switch(state) {
        case 0: return "INITIAL";
        case 1: return "COMMAND_TEXT";
        case 2: return "SUBTREE_HEAD";
        case 3: return "PROPERTY_ANY";
        case 4: return "LEAD";
        case 5: return "PROPERTY_LEAD";
        case 6: return "LOGBOOK_LEAD";
        case 7: return "COMMAND";
        case 8: return "COMMAND_EXAMPLE";
        case 9: return "COMMAND_COLUMNS";
        case 10: return "COMMAND_SRC";
        case 11: return "COMMAND_ARGS";
        case 12: return "COMMAND_TBLFM";
        case 13: return "BODY_SRC";
        case 14: return "PROPERTIES";
        case 15: return "PROPERTY_LITERAL";
        default: return std::to_string(state);
    }
}

std::string enum_serde<BaseTokenKind>::to_string(const BaseTokenKind &value) {
    switch(value) {
        case BaseTokenKind::Ampersand: return "Ampersand";
        case BaseTokenKind::AnyPunct: return "AnyPunct";
        case BaseTokenKind::Asterisk: return "Asterisk";
        case BaseTokenKind::At: return "At";
        case BaseTokenKind::Backtick: return "Backtick";
        case BaseTokenKind::BraceClose: return "BraceClose";
        case BaseTokenKind::BraceOpen: return "BraceOpen";
        case BaseTokenKind::Circumflex: return "Circumflex";
        case BaseTokenKind::CmdCaption: return "CmdCaption";
        case BaseTokenKind::CmdColonIdent: return "CmdColonIdent";
        case BaseTokenKind::CmdColumns: return "CmdColumns";
        case BaseTokenKind::CmdExampleBegin: return "CmdExampleBegin";
        case BaseTokenKind::CmdExampleEnd: return "CmdExampleEnd";
        case BaseTokenKind::CmdExampleLine: return "CmdExampleLine";
        case BaseTokenKind::CmdIdent: return "CmdIdent";
        case BaseTokenKind::CmdLatexHeader: return "CmdLatexHeader";
        case BaseTokenKind::CmdQuoteBegin: return "CmdQuoteBegin";
        case BaseTokenKind::CmdQuoteEnd: return "CmdQuoteEnd";
        case BaseTokenKind::CmdRawArg: return "CmdRawArg";
        case BaseTokenKind::CmdSrcBegin: return "CmdSrcBegin";
        case BaseTokenKind::CmdTblfm: return "CmdTblfm";
        case BaseTokenKind::Colon: return "Colon";
        case BaseTokenKind::Comment: return "Comment";
        case BaseTokenKind::Date: return "Date";
        case BaseTokenKind::Dedent: return "Dedent";
        case BaseTokenKind::Digit: return "Digit";
        case BaseTokenKind::Dollar: return "Dollar";
        case BaseTokenKind::DoubleHash: return "DoubleHash";
        case BaseTokenKind::DoubleLeftAngle: return "DoubleLeftAngle";
        case BaseTokenKind::DoubleQuote: return "DoubleQuote";
        case BaseTokenKind::DoubleRightAngle: return "DoubleRightAngle";
        case BaseTokenKind::DoubleSlash: return "DoubleSlash";
        case BaseTokenKind::EndOfFile: return "EndOfFile";
        case BaseTokenKind::Equals: return "Equals";
        case BaseTokenKind::EscapedChar: return "EscapedChar";
        case BaseTokenKind::Exclamation: return "Exclamation";
        case BaseTokenKind::ForwardSlash: return "ForwardSlash";
        case BaseTokenKind::HashIdent: return "HashIdent";
        case BaseTokenKind::Indent: return "Indent";
        case BaseTokenKind::LeadingMinus: return "LeadingMinus";
        case BaseTokenKind::LeadingNumber: return "LeadingNumber";
        case BaseTokenKind::LeadingPlus: return "LeadingPlus";
        case BaseTokenKind::LeadingSpace: return "LeadingSpace";
        case BaseTokenKind::LeftAngle: return "LeftAngle";
        case BaseTokenKind::LeftCurly: return "LeftCurly";
        case BaseTokenKind::LeftPar: return "LeftPar";
        case BaseTokenKind::LineCommand: return "LineCommand";
        case BaseTokenKind::ListEnd: return "ListEnd";
        case BaseTokenKind::ListStart: return "ListStart";
        case BaseTokenKind::LongNewline: return "LongNewline";
        case BaseTokenKind::MacroBegin: return "MacroBegin";
        case BaseTokenKind::MacroEnd: return "MacroEnd";
        case BaseTokenKind::MediumNewline: return "MediumNewline";
        case BaseTokenKind::Minus: return "Minus";
        case BaseTokenKind::MiscUnicode: return "MiscUnicode";
        case BaseTokenKind::Newline: return "Newline";
        case BaseTokenKind::Number: return "Number";
        case BaseTokenKind::Percent: return "Percent";
        case BaseTokenKind::Pipe: return "Pipe";
        case BaseTokenKind::Plus: return "Plus";
        case BaseTokenKind::RawText: return "RawText";
        case BaseTokenKind::RightAngle: return "RightAngle";
        case BaseTokenKind::RightCurly: return "RightCurly";
        case BaseTokenKind::RightPar: return "RightPar";
        case BaseTokenKind::SameIndent: return "SameIndent";
        case BaseTokenKind::Semicolon: return "Semicolon";
        case BaseTokenKind::SingleQuote: return "SingleQuote";
        case BaseTokenKind::SrcContent: return "SrcContent";
        case BaseTokenKind::SrcContentEnd: return "SrcContentEnd";
        case BaseTokenKind::SrcTangleClose: return "SrcTangleClose";
        case BaseTokenKind::SrcTangleOpen: return "SrcTangleOpen";
        case BaseTokenKind::SubtreePriority: return "SubtreePriority";
        case BaseTokenKind::SubtreeStars: return "SubtreeStars";
        case BaseTokenKind::TblAssign: return "TblAssign";
        case BaseTokenKind::TblColumnRef: return "TblColumnRef";
        case BaseTokenKind::TblOperator: return "TblOperator";
        case BaseTokenKind::TblRelativeColumnRef: return "TblRelativeColumnRef";
        case BaseTokenKind::Tilda: return "Tilda";
        case BaseTokenKind::Time: return "Time";
        case BaseTokenKind::TimeArrow: return "TimeArrow";
        case BaseTokenKind::TreeClock: return "TreeClock";
        case BaseTokenKind::TreePropertyEnd: return "TreePropertyEnd";
        case BaseTokenKind::TreePropertyLiteral: return "TreePropertyLiteral";
        case BaseTokenKind::TreePropertyLogbook: return "TreePropertyLogbook";
        case BaseTokenKind::TreePropertyName: return "TreePropertyName";
        case BaseTokenKind::TreePropertyProperties: return "TreePropertyProperties";
        case BaseTokenKind::TreePropertyText: return "TreePropertyText";
        case BaseTokenKind::TripleBacktick: return "TripleBacktick";
        case BaseTokenKind::Whitespace: return "Whitespace";
        case BaseTokenKind::Word: return "Word";
    }
}

Opt<BaseTokenKind> enum_serde<BaseTokenKind>::from_string(std::string const& value) {
  if (value == "Ampersand") { return BaseTokenKind::Ampersand; } else
  if (value == "AnyPunct") { return BaseTokenKind::AnyPunct; } else
  if (value == "Asterisk") { return BaseTokenKind::Asterisk; } else
  if (value == "At") { return BaseTokenKind::At; } else
  if (value == "Backtick") { return BaseTokenKind::Backtick; } else
  if (value == "BraceClose") { return BaseTokenKind::BraceClose; } else
  if (value == "BraceOpen") { return BaseTokenKind::BraceOpen; } else
  if (value == "Circumflex") { return BaseTokenKind::Circumflex; } else
  if (value == "CmdCaption") { return BaseTokenKind::CmdCaption; } else
  if (value == "CmdColonIdent") { return BaseTokenKind::CmdColonIdent; } else
  if (value == "CmdColumns") { return BaseTokenKind::CmdColumns; } else
  if (value == "CmdExampleBegin") { return BaseTokenKind::CmdExampleBegin; } else
  if (value == "CmdExampleEnd") { return BaseTokenKind::CmdExampleEnd; } else
  if (value == "CmdExampleLine") { return BaseTokenKind::CmdExampleLine; } else
  if (value == "CmdIdent") { return BaseTokenKind::CmdIdent; } else
  if (value == "CmdLatexHeader") { return BaseTokenKind::CmdLatexHeader; } else
  if (value == "CmdQuoteBegin") { return BaseTokenKind::CmdQuoteBegin; } else
  if (value == "CmdQuoteEnd") { return BaseTokenKind::CmdQuoteEnd; } else
  if (value == "CmdRawArg") { return BaseTokenKind::CmdRawArg; } else
  if (value == "CmdSrcBegin") { return BaseTokenKind::CmdSrcBegin; } else
  if (value == "CmdTblfm") { return BaseTokenKind::CmdTblfm; } else
  if (value == "Colon") { return BaseTokenKind::Colon; } else
  if (value == "Comment") { return BaseTokenKind::Comment; } else
  if (value == "Date") { return BaseTokenKind::Date; } else
  if (value == "Dedent") { return BaseTokenKind::Dedent; } else
  if (value == "Digit") { return BaseTokenKind::Digit; } else
  if (value == "Dollar") { return BaseTokenKind::Dollar; } else
  if (value == "DoubleHash") { return BaseTokenKind::DoubleHash; } else
  if (value == "DoubleLeftAngle") { return BaseTokenKind::DoubleLeftAngle; } else
  if (value == "DoubleQuote") { return BaseTokenKind::DoubleQuote; } else
  if (value == "DoubleRightAngle") { return BaseTokenKind::DoubleRightAngle; } else
  if (value == "DoubleSlash") { return BaseTokenKind::DoubleSlash; } else
  if (value == "EndOfFile") { return BaseTokenKind::EndOfFile; } else
  if (value == "Equals") { return BaseTokenKind::Equals; } else
  if (value == "EscapedChar") { return BaseTokenKind::EscapedChar; } else
  if (value == "Exclamation") { return BaseTokenKind::Exclamation; } else
  if (value == "ForwardSlash") { return BaseTokenKind::ForwardSlash; } else
  if (value == "HashIdent") { return BaseTokenKind::HashIdent; } else
  if (value == "Indent") { return BaseTokenKind::Indent; } else
  if (value == "LeadingMinus") { return BaseTokenKind::LeadingMinus; } else
  if (value == "LeadingNumber") { return BaseTokenKind::LeadingNumber; } else
  if (value == "LeadingPlus") { return BaseTokenKind::LeadingPlus; } else
  if (value == "LeadingSpace") { return BaseTokenKind::LeadingSpace; } else
  if (value == "LeftAngle") { return BaseTokenKind::LeftAngle; } else
  if (value == "LeftCurly") { return BaseTokenKind::LeftCurly; } else
  if (value == "LeftPar") { return BaseTokenKind::LeftPar; } else
  if (value == "LineCommand") { return BaseTokenKind::LineCommand; } else
  if (value == "ListEnd") { return BaseTokenKind::ListEnd; } else
  if (value == "ListStart") { return BaseTokenKind::ListStart; } else
  if (value == "LongNewline") { return BaseTokenKind::LongNewline; } else
  if (value == "MacroBegin") { return BaseTokenKind::MacroBegin; } else
  if (value == "MacroEnd") { return BaseTokenKind::MacroEnd; } else
  if (value == "MediumNewline") { return BaseTokenKind::MediumNewline; } else
  if (value == "Minus") { return BaseTokenKind::Minus; } else
  if (value == "MiscUnicode") { return BaseTokenKind::MiscUnicode; } else
  if (value == "Newline") { return BaseTokenKind::Newline; } else
  if (value == "Number") { return BaseTokenKind::Number; } else
  if (value == "Percent") { return BaseTokenKind::Percent; } else
  if (value == "Pipe") { return BaseTokenKind::Pipe; } else
  if (value == "Plus") { return BaseTokenKind::Plus; } else
  if (value == "RawText") { return BaseTokenKind::RawText; } else
  if (value == "RightAngle") { return BaseTokenKind::RightAngle; } else
  if (value == "RightCurly") { return BaseTokenKind::RightCurly; } else
  if (value == "RightPar") { return BaseTokenKind::RightPar; } else
  if (value == "SameIndent") { return BaseTokenKind::SameIndent; } else
  if (value == "Semicolon") { return BaseTokenKind::Semicolon; } else
  if (value == "SingleQuote") { return BaseTokenKind::SingleQuote; } else
  if (value == "SrcContent") { return BaseTokenKind::SrcContent; } else
  if (value == "SrcContentEnd") { return BaseTokenKind::SrcContentEnd; } else
  if (value == "SrcTangleClose") { return BaseTokenKind::SrcTangleClose; } else
  if (value == "SrcTangleOpen") { return BaseTokenKind::SrcTangleOpen; } else
  if (value == "SubtreePriority") { return BaseTokenKind::SubtreePriority; } else
  if (value == "SubtreeStars") { return BaseTokenKind::SubtreeStars; } else
  if (value == "TblAssign") { return BaseTokenKind::TblAssign; } else
  if (value == "TblColumnRef") { return BaseTokenKind::TblColumnRef; } else
  if (value == "TblOperator") { return BaseTokenKind::TblOperator; } else
  if (value == "TblRelativeColumnRef") { return BaseTokenKind::TblRelativeColumnRef; } else
  if (value == "Tilda") { return BaseTokenKind::Tilda; } else
  if (value == "Time") { return BaseTokenKind::Time; } else
  if (value == "TimeArrow") { return BaseTokenKind::TimeArrow; } else
  if (value == "TreeClock") { return BaseTokenKind::TreeClock; } else
  if (value == "TreePropertyEnd") { return BaseTokenKind::TreePropertyEnd; } else
  if (value == "TreePropertyLiteral") { return BaseTokenKind::TreePropertyLiteral; } else
  if (value == "TreePropertyLogbook") { return BaseTokenKind::TreePropertyLogbook; } else
  if (value == "TreePropertyName") { return BaseTokenKind::TreePropertyName; } else
  if (value == "TreePropertyProperties") { return BaseTokenKind::TreePropertyProperties; } else
  if (value == "TreePropertyText") { return BaseTokenKind::TreePropertyText; } else
  if (value == "TripleBacktick") { return BaseTokenKind::TripleBacktick; } else
  if (value == "Whitespace") { return BaseTokenKind::Whitespace; } else
  if (value == "Word") { return BaseTokenKind::Word; } else
  { return std::nullopt; }
}

