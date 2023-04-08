#include <parse/OrgParser.hpp>
#include <hstd/stdlib/Debug.hpp>


using Err = OrgParser::Errors;

OrgParser::ParserError OrgParser::wrapError(
    CR<Error>    err,
    CR<OrgLexer> lex) {
    ParserError result{err};
    auto        loc = getLoc(lex);

    if (loc.has_value()) {
        result.setLoc(loc.value());
    }

    return result;
}


QString OrgParser::getLocMsg(CR<OrgLexer> lex) {
    QString result;
    QString pos = lex.pos.isNil() ? "<nil>"
                                  : to_string(lex.pos.getIndex());

    if (auto loc = getLoc(lex)) {
        result = "$#:$# (pos $#)"
               % to_string_vec(loc->line, loc->column, pos);
    } else {
        result = "(pos $#)" % to_string_vec(pos);
    }

    return result;
}
