#include <parse/OrgParser.hpp>

QString OrgParser::Errors::Base::getLocMsg() const {
    return "$#:$# (tok $#, pos $#)"
         % to_string_vec(
               loc ? loc->line : -1,
               loc ? loc->column : -1,
               id.isNil() ? "<none>" : to_string(id.getIndex()),
               loc ? loc->pos : -1);
}

OrgParser::Errors::Base::Base(CR<OrgLexer> lex, Opt<LineCol> loc)
    : id(lex.pos), loc(loc) {
    if (!lex.finished()) {
        token = lex.tok();
    }
    extraMsg = lex.printToString(false);
}

OrgParser::Errors::Base::Base(
    CR<OrgLexer> lex,
    CR<QString>  extraMsg,
    Opt<LineCol> loc)
    : id(lex.pos), loc(loc), extraMsg(extraMsg) {
    if (!lex.finished()) {
        token = lex.tok();
    }
}

const char* OrgParser::Errors::UnexpectedToken::what() const noexcept {
    return strdup(
        "Expected $#, but got $# at $# ($#)"
        % to_string_vec(
            swl::visit(
                overloaded{
                    [](CR<TokenWithValue> it) {
                        return "$# ('$#')"
                             % to_string_vec(it.kind, it.value);
                    },
                    [](auto const& it) { return to_string(it); }},
                wanted),
            this->token,
            getLocMsg(),
            this->extraMsg));
}

const char* OrgParser::Errors::UnhandledToken::what() const noexcept {
    return strdup(
        "Encountered $# at $#, which is was not expected ($#)"
        % to_string_vec(this->token, getLocMsg(), this->extraMsg));
}
