#include <parse/OrgParser.hpp>

std::string OrgParser::Error::getLocMsg() const {
    return "$#:$# (tok $#, pos $#)"
         % to_string_vec(
               loc ? loc->line : -1,
               loc ? loc->column : -1,
               id.isNil() ? "<none>" : to_string(id.getIndex()),
               loc ? loc->pos : -1);
}

const char* OrgParser::UnexpectedToken::what() const noexcept {
    return strdup(
        "Expected $#, but got $# at $# ($#)"
        % to_string_vec(
            std::visit(
                overloaded{
                    [](CR<TokenWithValue> it) {
                        return "$# ('$#')"
                             % to_string_vec(it.kind, it.value);
                    },
                    [](auto const& it) { return std::format("{}", it); }},
                wanted),
            this->token,
            getLocMsg(),
            this->extraMsg));
}

const char* OrgParser::UnhandledToken::what() const noexcept {
    return strdup(
        std::format(
            "Encountered {} at {}, which is was not expected ({})",
            token,
            getLocMsg(),
            extraMsg)
            .c_str());
}
