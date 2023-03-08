#pragma once

#include <variant>

struct LineCol {
    int line;
    int column;
};

/// \brief Base parse error
struct ParseError : public std::runtime_error {
    /// \brief Line and column of the error location or absolute unresolved
    /// offset
    std::variant<LineCol, int> loc;

    explicit ParseError(const QString& message, LineCol _loc = LineCol{})
        : std::runtime_error(message.toStdString()), loc(_loc) {}

    explicit ParseError(const QString& message, int _loc)
        : std::runtime_error(message.toStdString()), loc(_loc) {}
};

/// \brief Base lexer error type
struct LexerError : public ParseError {
    explicit LexerError(const QString& message, LineCol _loc = LineCol{})
        : ParseError(message, _loc) {}

    explicit LexerError(const QString& message, int _loc)
        : ParseError(message, _loc) {}
};

/// \brief Raised when unexpected character is encountered at position
struct UnexpectedCharError : public LexerError {
    explicit UnexpectedCharError(
        const QString& message,
        LineCol        _loc = LineCol{})
        : LexerError(message, _loc) {}

    explicit UnexpectedCharError(const QString& message, int pos)
        : LexerError(message, pos) {}
};


/// \brief Raised when string unexpectedly ended
struct UnexpectedEndError : public LexerError {
    explicit UnexpectedEndError(
        const QString& message,
        LineCol        _loc = LineCol{})
        : LexerError(message, _loc) {}

    explicit UnexpectedEndError(const QString& message, int pos)
        : LexerError(message, pos) {}
};

struct UnbalancedWrapError : public LexerError {};
/// \brief Can be raised by user-provided lexer to indicate malformed token
/// at position
struct MalformedTokenError : public LexerError {};
