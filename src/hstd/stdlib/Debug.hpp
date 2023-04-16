#pragma once

#include <hstd/system/string_convert.hpp>
#include <hstd/stdlib/ColText.hpp>

#include <QDebug>
#include <QString>
#include <QTextStream>

template <StringConvertible T>
QDebug operator<<(QDebug debug, T const& value) {
    QString          result;
    QTextStream      stream{&result};
    QDebugStateSaver saver{debug};
    stream << to_string(value);
    debug.nospace().noquote() << result;
    return debug;
}

void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg);

void setMessageStream(QTextStream& stream);

inline void qt_assert_x(
    CR<QString> where,
    CR<QString> what,
    const char* file,
    int         line) noexcept {
    qt_assert_x(strdup(where), strdup(what), file, line);
}

inline void fatal(CR<QString> msg) { fatal(strdup(msg)); }

#define qDebugIndent(indent)                                              \
    qDebug().noquote() << QString("  ").repeated(indent)

#define _dbg(expr)                                                        \
    ([](auto const& it) {                                                 \
        qDebug() << (#expr) << " = " << it;                               \
        return it;                                                        \
    }((expr)))
