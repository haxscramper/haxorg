import org.parse.OrgParser;
import hstd.stdlib.Debug;

std::string OrgParser::getLocMsg(CR<OrgLexer> lex) {
    std::string result;
    std::string pos = lex.pos.isNil() ? "<nil>" : fmt1(lex.pos.getIndex());

    if (auto loc = getLoc(lex)) {
        result = "$#:$# (tok $#, pos $#)"
               % to_string_vec(loc->line, loc->column, pos, loc->pos);
    } else {
        result = "(tok $#, pos $#)" % to_string_vec(pos, loc->pos);
    }

    return result;
}

Opt<LineCol> OrgParser::getLoc(CR<OrgLexer> lex) {
    if (lex.finished()) {
        return std::nullopt;
    } else {
        for (int offset = 0; lex.hasNext(-offset) || lex.hasNext(offset);
             ++offset) {
            // Try incrementally widening lookarounds on the current
            // lexer position until there is a token that has proper
            // location information.
            for (int i : Vec<int>{-1, 1}) {
                if (lex.hasNext(offset * i)) {
                    OrgToken tok = lex.tok(offset * i);
                    if (tok.value.base) {
                        return LineCol{
                            tok.value.base->line, tok.value.base->col};
                    }
                    // If offset falls out of the lexer range on both
                    // ends, terminate lookup.
                }
            }
        }
        return std::nullopt;
    }
}
