#pragma once

#include <hstd/stdlib/strformat.hpp>
#include <hstd/system/string_convert.hpp>
#include <variant>
#include <format>

namespace org::parse {

struct [[refl]] LineCol {
    [[refl]] int line;
    [[refl]] int column;
    [[refl]] int pos = -1;

    bool operator==(LineCol const& other) const {
        return line == other.line && column == other.column
            && pos == other.pos;
    }

    BOOST_DESCRIBE_CLASS(LineCol, (), (line, column, pos), (), ());
};


/// \brief Base parse error
struct ParseError : public std::runtime_error {
    /// \brief Line and column of the error location or absolute unresolved
    /// offset
    std::variant<LineCol, int> loc;

    explicit ParseError(
        const std::string& message,
        LineCol            _loc = LineCol{})
        : std::runtime_error(message), loc(_loc) {}

    explicit ParseError(const std::string& message, int _loc)
        : std::runtime_error(message), loc(_loc) {}
};

/// \brief Base lexer error type
struct LexerError : public ParseError {
    explicit LexerError(
        const std::string& message,
        LineCol            _loc = LineCol{})
        : ParseError(message, _loc) {}

    explicit LexerError(const std::string& message, int _loc)
        : ParseError(message, _loc) {}
};

/// \brief Raised when unexpected character is encountered at position
struct UnexpectedCharError : public LexerError {
    explicit UnexpectedCharError(
        const std::string& message,
        LineCol            _loc = LineCol{})
        : LexerError(message, _loc) {}

    explicit UnexpectedCharError(const std::string& message, int pos)
        : LexerError(message, pos) {}
};


/// \brief Raised when string unexpectedly ended
struct UnexpectedEndError : public LexerError {
    explicit UnexpectedEndError(
        const std::string& message,
        LineCol            _loc = LineCol{})
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
struct std::formatter<org::parse::LineCol> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        const org::parse::LineCol& p,
        FormatContext&             ctx) const {
        fmt_ctx(p.line, ctx);
        fmt_ctx(":", ctx);
        fmt_ctx(p.column, ctx);
        fmt_ctx(":", ctx);
        return fmt_ctx(p.pos, ctx);
    }
};

template <>
struct std::hash<org::parse::LineCol> {
    std::size_t operator()(org::parse::LineCol const& it) const noexcept {
        std::size_t result = 0;
        hstd::hax_hash_combine(result, it.line);
        hstd::hax_hash_combine(result, it.column);
        hstd::hax_hash_combine(result, it.pos);
        return result;
    }
};
