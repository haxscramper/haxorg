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

inline void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg) {
    ColStream os{qcout};

    QString res;
    os.magenta();
    switch (type) {
        case QtMsgType::QtInfoMsg: os << "INFO "; break;
        case QtMsgType::QtDebugMsg: os << "DEBUG"; break;
        case QtMsgType::QtWarningMsg: os << "WARNG"; break;
        case QtMsgType::QtCriticalMsg: os << "CRITC"; break;
        case QtMsgType::QtFatalMsg: os << "FATAL"; break;
    }
    os << os.end();

    os << " [" << os.cyan() << context.line << os.end() << "]";
    if (context.category != "default") {
        os << " " << os.green() << context.category << os.end();
    }
    os << " " << msg;

    qcout << Qt::endl;
}

inline void qt_assert_x(
    CR<QString> where,
    CR<QString> what,
    const char* file,
    int         line) noexcept {
    qt_assert_x(strdup(where), strdup(what), file, line);
}
