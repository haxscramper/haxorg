#pragma once

#include <hstd/system/string_convert.hpp>
#include <QDebug>
#include <QString>
#include <QTextStream>

template <StringConvertible T>
QDebug operator<<(QDebug debug, T const& value) {
    QString          result;
    QTextStream      stream{&result};
    QDebugStateSaver saver{debug};
    stream << value;
    debug.nospace().noquote() << result;
    return debug;
}

inline void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg) {
    QString res;
    switch (type) {
        case QtMsgType::QtInfoMsg: res += "INFO "; break;
        case QtMsgType::QtDebugMsg: res += "DEBUG"; break;
        case QtMsgType::QtWarningMsg: res += "WARNG"; break;
        case QtMsgType::QtCriticalMsg: res += "CRITC"; break;
        case QtMsgType::QtFatalMsg: res += "FATAL"; break;
    }

    res += QString(" [%1] %2 %3")
               .arg(context.line)
               .arg(context.category)
               .arg(msg);

    qcout << res << Qt::endl;
}
