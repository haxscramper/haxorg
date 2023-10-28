
std::string BaseLexerImpl::state_name(int state) {
    switch(state) {
        case 0: return "INITIAL";
        case 1: return "COMMAND_TEXT";
        case 2: return "SUBTREE_HEAD";
        case 3: return "PROPERTY_ANY";
        case 4: return "COMMAND";
        case 5: return "COMMAND_EXAMPLE";
        case 6: return "COMMAND_COLUMNS";
        case 7: return "COMMAND_SRC";
        case 8: return "BODY_SRC";
        case 9: return "PROPERTIES";
        case 10: return "PROPERTY_LITERAL";
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
        case BaseTokenKind::CmdIdent: return "CmdIdent";
        case BaseTokenKind::CmdSrcBegin: return "CmdSrcBegin";
        case BaseTokenKind::Colon: return "Colon";
        case BaseTokenKind::Comment: return "Comment";
        case BaseTokenKind::Date: return "Date";
        case BaseTokenKind::Digit: return "Digit";
        case BaseTokenKind::Dollar: return "Dollar";
        case BaseTokenKind::DoubleHash: return "DoubleHash";
        case BaseTokenKind::DoubleLeftAngle: return "DoubleLeftAngle";
        case BaseTokenKind::DoubleQuote: return "DoubleQuote";
        case BaseTokenKind::DoubleRightAngle: return "DoubleRightAngle";
        case BaseTokenKind::DoubleSlash: return "DoubleSlash";
        case BaseTokenKind::Equals: return "Equals";
        case BaseTokenKind::EscapedChar: return "EscapedChar";
        case BaseTokenKind::Exclamation: return "Exclamation";
        case BaseTokenKind::HashIdent: return "HashIdent";
        case BaseTokenKind::LeadingSpace: return "LeadingSpace";
        case BaseTokenKind::LeftAngle: return "LeftAngle";
        case BaseTokenKind::LeftCurly: return "LeftCurly";
        case BaseTokenKind::LeftPar: return "LeftPar";
        case BaseTokenKind::LineCommand: return "LineCommand";
        case BaseTokenKind::MacroBegin: return "MacroBegin";
        case BaseTokenKind::MacroEnd: return "MacroEnd";
        case BaseTokenKind::Minus: return "Minus";
        case BaseTokenKind::MiscUnicode: return "MiscUnicode";
        case BaseTokenKind::Newline: return "Newline";
        case BaseTokenKind::Number: return "Number";
        case BaseTokenKind::Percent: return "Percent";
        case BaseTokenKind::Pipe: return "Pipe";
        case BaseTokenKind::Plus: return "Plus";
        case BaseTokenKind::RightAngle: return "RightAngle";
        case BaseTokenKind::RightCurly: return "RightCurly";
        case BaseTokenKind::RightPar: return "RightPar";
        case BaseTokenKind::Semicolon: return "Semicolon";
        case BaseTokenKind::SingleQuote: return "SingleQuote";
        case BaseTokenKind::SrcContent: return "SrcContent";
        case BaseTokenKind::SrcContentEnd: return "SrcContentEnd";
        case BaseTokenKind::SrcTangleClose: return "SrcTangleClose";
        case BaseTokenKind::SrcTangleOpen: return "SrcTangleOpen";
        case BaseTokenKind::SubtreePriority: return "SubtreePriority";
        case BaseTokenKind::SubtreeStars: return "SubtreeStars";
        case BaseTokenKind::Tilda: return "Tilda";
        case BaseTokenKind::Time: return "Time";
        case BaseTokenKind::TimeArrow: return "TimeArrow";
        case BaseTokenKind::TreeClock: return "TreeClock";
        case BaseTokenKind::TreePropertyEnd: return "TreePropertyEnd";
        case BaseTokenKind::TreePropertyLogbook: return "TreePropertyLogbook";
        case BaseTokenKind::TreePropertyName: return "TreePropertyName";
        case BaseTokenKind::TreePropertyProperties: return "TreePropertyProperties";
        case BaseTokenKind::TreePropertyText: return "TreePropertyText";
        case BaseTokenKind::TripleBacktick: return "TripleBacktick";
        case BaseTokenKind::Whitespace: return "Whitespace";
        case BaseTokenKind::Word: return "Word";
    }
}

