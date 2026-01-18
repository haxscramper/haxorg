#pragma once

#include <variant>
#include <hstd/system/reflection.hpp>
#include <haxorg/lexbase/SourceManager.hpp>

namespace org::parse {


/// \brief Base parse error
struct ParseError : public std::runtime_error {
    /// \brief Line and column of the error location or absolute unresolved
    /// offset
    std::variant<SourceLoc, int> loc;

    explicit ParseError(
        const std::string& message,
        SourceLoc            _loc = SourceLoc{})
        : std::runtime_error(message), loc(_loc) {}

    explicit ParseError(const std::string& message, int _loc)
        : std::runtime_error(message), loc(_loc) {}
};

/// \brief Base lexer error type
struct LexerError : public ParseError {
    explicit LexerError(
        const std::string& message,
        SourceLoc            _loc = SourceLoc{})
        : ParseError(message, _loc) {}

    explicit LexerError(const std::string& message, int _loc)
        : ParseError(message, _loc) {}
};

/// \brief Raised when unexpected character is encountered at position
struct UnexpectedCharError : public LexerError {
    explicit UnexpectedCharError(
        const std::string& message,
        SourceLoc            _loc = SourceLoc{})
        : LexerError(message, _loc) {}

    explicit UnexpectedCharError(const std::string& message, int pos)
        : LexerError(message, pos) {}
};


/// \brief Raised when string unexpectedly ended
struct UnexpectedEndError : public LexerError {
    explicit UnexpectedEndError(
        const std::string& message,
        SourceLoc            _loc = SourceLoc{})
        : LexerError(message, _loc) {}

    explicit UnexpectedEndError(const std::string& message, int pos)
        : LexerError(message, pos) {}
};

struct UnbalancedWrapError : public LexerError {};
/// \brief Can be raised by user-provided lexer to indicate malformed token
/// at position
struct MalformedTokenError : public LexerError {};

} // namespace org::parse


template <>
struct std::hash<org::parse::SourceLoc> {
    std::size_t operator()(org::parse::SourceLoc const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.line);
        hstd::hax_hash_combine(result, it.column);
        hstd::hax_hash_combine(result, it.pos);
        return result;
    }
};
