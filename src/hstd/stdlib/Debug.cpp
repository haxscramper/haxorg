#include <hstd/stdlib/Debug.hpp>
#include <QTextStream>

std::reference_wrapper<QTextStream> messageStream = qcout;

void setMessageStream(QTextStream& stream) { messageStream = stream; }

void tracedMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg) {
    ColStream os{messageStream.get()};

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

    messageStream.get() << Qt::endl;
}
