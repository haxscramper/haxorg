#include <hstd/stdlib/Debug.hpp>
#include <iostream>
#include <filesystem>
#include <QMutex>

std::reference_wrapper<std::ostream> messageStream = qcout;

void setMessageStream(std::ostream& stream) { messageStream = stream; }

QMutex logMutex;

void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const std::string&            msg) {
    logMutex.lock();
    ColStream os{messageStream.get()};

    std::string res;
    os.magenta();
    switch (type) {
        case QtMsgType::QtInfoMsg: os << "INFO "; break;
        case QtMsgType::QtDebugMsg: os << "DEBUG"; break;
        case QtMsgType::QtWarningMsg: os << "WARNG"; break;
        case QtMsgType::QtCriticalMsg: os << "CRITC"; break;
        case QtMsgType::QtFatalMsg: os << "FATAL"; break;
    }
    os << os.end();
    os << " [" << os.cyan() << context.line << os.end() << "] "
       << os.blue() << QFileInfo(context.file).fileName() << os.end();

    if (context.category != "default") {
        os << " " << os.green() << context.category << os.end();
    }

    os << " " << msg;

    messageStream.get() << Qt::endl;
    logMutex.unlock();
}
