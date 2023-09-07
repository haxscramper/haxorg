#include <parse/OrgTokenizer.hpp>

using E = OrgTokenizer::Errors;


QString E::Base::getLocMsg() const {
    return "on $#:$# (pos $#)"
         % to_string_vec(
               loc ? loc->line : -1, loc ? loc->column : -1, pos);
}

const char* OrgTokenizer::Errors::UnexpectedChar::what() const noexcept {
    return strdup(
        "Expected " + to_string(wanted) + " but got '"
        + PosStr(view, pos).printToString({.maxTokens = 40}, false) + "' "
        + getLocMsg());
}


const char* OrgTokenizer::Errors::MissingElement::what() const noexcept {
    return strdup(
        "Missing '$#' for $# $#"
        % to_string_vec(missing, where, getLocMsg()));
}

OrgTokenizer::Errors::MissingElement::MissingElement(
    CR<PosStr>  str,
    CR<QString> missing,
    CR<QString> where)
    : Base(str), missing(missing), where(where) {}

const char* OrgTokenizer::Errors::UnexpectedConstruct::what()
    const noexcept {
    return strdup(
        "Unexpected construct at $#: $#"
        % to_string_vec(getLocMsg(), desc));
}

const char* OrgTokenizer::Errors::UnknownConstruct::what() const noexcept {
    return strdup(
        "Unexpected construct '"
        + PosStr(view, pos).printToString({.withSeparation = false}, false)
        + "' " + getLocMsg());
}

QStringView OrgTokenizer::TokenizerError::getView() const {
    return std::visit([](auto const& in) { return in.view; }, err);
}

int OrgTokenizer::TokenizerError::getPos() const {
    return std::visit([](auto const& in) { return in.pos; }, err);
}

void OrgTokenizer::TokenizerError::setLoc(CR<LineCol> loc) {
    std::visit(
        [&loc](auto& in) {
            in.loc = loc;
            return 0;
        },
        err);
}

Opt<LineCol> OrgTokenizer::TokenizerError::getLoc() const {
    return std::visit([](auto const& in) { return in.loc; }, err);
}

const char* OrgTokenizer::TokenizerError::what() const noexcept {
    return std::visit([](auto const& in) { return in.what(); }, err);
}
