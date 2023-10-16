#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <absl/log/log.h>
#include <string>
#include <iostream>

template <StringConvertible T>
QDebug operator<<(QDebug debug, T const& value) {
    std::string          result;
    std::ostream      stream{&result};
    QDebugStateSaver saver{debug};
    stream << to_string(value);
    debug.nospace().noquote() << result;
    return debug;
}

void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const std::string&            msg);

void setMessageStream(std::ostream& stream);

inline void qt_assert_x(
    CR<std::string> where,
    CR<std::string> what,
    const char* file,
    int         line) noexcept {
    qt_assert_x(strdup(where), strdup(what), file, line);
}

inline void fatal(CR<std::string> msg) { fatal(strdup(msg)); }

#define qDebugIndent(indent)                                              \
    DLOG(INFO).noquote() << std::string("  ").repeated(indent)

#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        DLOG(INFO) << (#expr) << " = ⦃" << it << "⦄";                       \
        return it;                                                        \
    }((expr)))
