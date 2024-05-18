#pragma once

#include <QDebug>
#include <QCoreApplication>
#include <QLoggingCategory>


void customMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg_in);

void editorInitMain();
