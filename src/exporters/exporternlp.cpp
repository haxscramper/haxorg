#include "exporternlp.hpp"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLoggingCategory>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterNLP, std::monostate>;

Q_LOGGING_CATEGORY(nlp, "check.nlp");

struct ExporterNLP::Parsed::Constituency::lexer {
    QString data;
    int     pos;
    QChar   tok() {
        Q_ASSERT(pos < data.size());
        return data[pos];
    }
    void next() { ++pos; }
    bool at(QChar ch) { return tok() == ch; }
    void space() {
        while (tok().isSpace()) {
            next();
        }
    }
    void skip(QChar ch) {
        Q_ASSERT(tok() == ch);
        next();
    }
};

ExporterNLP::Parsed::Constituency ExporterNLP::Parsed::Constituency::parse(
    const QString& text) {
    Parsed::Constituency::lexer lex{.data = text};
    qCDebug(nlp).noquote() << lex.data;
    return parse(lex);
}

ExporterNLP::Parsed::Constituency ExporterNLP::Parsed::Constituency::parse(
    lexer& lex) {
    Constituency result{};
    lex.space();
    lex.skip('(');
    while (lex.tok().isLetter() || lex.tok() == '-') {
        result.tag.append(lex.tok());
        lex.next();
    }

    lex.space();

    if (lex.at('(')) {
        while (!lex.at(')')) {
            lex.space();
            result.nested.push_back(Constituency::parse(lex));
        }
    } else {
        while (!lex.at(')')) {
            result.lexem.push_back(lex.tok());
            lex.next();
        }
    }

    lex.skip(')');

    return result;
}

void ExporterNLP::executeRequests() {
    for (int i = 0; i < exchange.size(); ++i) {
        sendRequest(exchange.at(i).first, i);
    }
}

void ExporterNLP::sendRequest(const Request& request, int index) {
    if (netManager == nullptr) {
        netManager = new QNetworkAccessManager();
    }

    QNetworkRequest netRequest{requestUrl};


    QString data;
    for (const auto& word : request.sentence.text) {
        data += word.text;
    }

    netRequest.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    QNetworkReply* reply = netManager->post(netRequest, data.toUtf8());
    reply->setProperty("exchange-index", QVariant::fromValue(index));
    addRequestHooks(reply);
}

void ExporterNLP::addRequestHooks(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        this->onFinishedResponse(reply);
    });

    QObject::connect(
        reply,
        &QNetworkReply::errorOccurred,
        [](const QNetworkReply::NetworkError& error) {
            qCWarning(nlp) << "Response had error ";
        });

    QObject::connect(
        reply,
        &QNetworkReply::sslErrors,
        [](const QList<QSslError>& errors) {
            qCWarning(nlp) << "Response had error " << errors;
        });
}

void ExporterNLP::onFinishedResponse(QNetworkReply* reply) {
    if (reply->error()) {
        qCWarning(nlp) << "Failed to execute reply";
        //        qCWarning(nlp) << reply->error();
        qCWarning(nlp) << reply->request().url();
        qCWarning(nlp) << "Code"
                       << reply->attribute(
                              QNetworkRequest::HttpStatusCodeAttribute);

        //        emit checked({.valid = false});

    } else {
        auto json        = QJsonDocument::fromJson(reply->readAll());
        auto obj         = json.object();
        int  targetIndex = reply->property("exchange-index").value<int>();
        qCDebug(nlp) << "Got NLP server response for request"
                     << targetIndex;
        Response result{.valid = true};
        for (const auto& sentRef : obj["sentences"].toArray()) {
            auto   sent = sentRef.toObject();
            Parsed parsed{};
            parsed.constituency = Parsed::Constituency::parse(
                sent["parse"].toString());
            qCDebug(nlp).noquote().nospace()
                << "\n"
                << parsed.constituency.treeRepr();

            result.sentences.push_back(parsed);
        }

        exchange.at(targetIndex).second = result;
    }
    reply->deleteLater();
}
