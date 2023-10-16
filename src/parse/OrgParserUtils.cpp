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


std::string OrgParser::getLocMsg(CR<OrgLexer> lex) {
    std::string result;
    std::string pos = lex.pos.isNil() ? "<nil>"
                                  : to_string(lex.pos.getIndex());

    if (auto loc = getLoc(lex)) {
        result = "$#:$# (tok $#, pos $#)"
               % to_string_vec(loc->line, loc->column, pos, loc->pos);
    } else {
        result = "(tok $#, pos $#)" % to_string_vec(pos, loc->pos);
    }

    return result;
}
