#include "exporternlp.hpp"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLoggingCategory>
#include <QThread>

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

ExporterNLP::ExporterNLP(const QUrl& resp) : requestUrl(resp) {
    QUrlQuery     query{};
    QJsonDocument parameters;

    QJsonObject obj;
    netManager        = new QNetworkAccessManager();
    obj["annotators"] = QStringList({"tokenize", "ssplit", "pos", "parse"})
                            .join(", ");
    obj["outputFormat"] = "json";
    parameters.setObject(obj);

    query.addQueryItem(
        "properties", parameters.toJson(QJsonDocument::Compact));

    requestUrl.setQuery(query);
}

void ExporterNLP::executeRequests() {
    for (int i = 0; i < exchange.size(); ++i) {
        sendRequest(exchange.at(i).first, i);
    }
}

void ExporterNLP::waitForRequests() {
    while (0 < pendingRequests) {
        qCDebug(nlp) << "Waiting for pending requests" << pendingRequests
                     << "left";
        QThread::msleep(250);
    }
}

void ExporterNLP::asSeparateRequest(R& t, sem::SemId par) {
    qDebug() << "Visiting paragraph in text";
    activeRequest = Request{};
    for (auto const& sub : par->subnodes) {
        visit(t, sub);
    }
    qDebug() << "Finished paragraph visit with"
             << activeRequest->sentence.text.size() << "active tokens";
    exchange.push_back({std::move(activeRequest.value()), Response{}});
    activeRequest = std::nullopt;
}

void ExporterNLP::sendRequest(const Request& request, int index) {
    QNetworkRequest netRequest{requestUrl};
    netRequest.setTransferTimeout(5000);

    QString data;
    for (const auto& word : request.sentence.text) {
        data += word.text;
    }

    netRequest.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");
    qCDebug(nlp) << "Sending request to" << requestUrl << "with data"
                 << data.toUtf8();
    QNetworkReply* reply = netManager->post(netRequest, data.toUtf8());
    ++pendingRequests;
    Q_CHECK_PTR(reply);
    reply->setProperty("exchange-index", QVariant::fromValue(index));
    addRequestHooks(reply);
}

void ExporterNLP::addRequestHooks(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        this->onFinishedResponse(reply);
        --pendingRequests;
    });

    QObject::connect(
        reply,
        &QNetworkReply::errorOccurred,
        [this](const QNetworkReply::NetworkError& error) {
            qCWarning(nlp) << "Response had error ";
            --pendingRequests;
        });

    QObject::connect(
        reply,
        &QNetworkReply::sslErrors,
        [this](const QList<QSslError>& errors) {
            qCWarning(nlp) << "Response had error " << errors;
            --pendingRequests;
        });

    qCDebug(nlp) << "Added response hooks";
}

void ExporterNLP::onFinishedResponse(QNetworkReply* reply) {
    qDebug() << "Finished NLP response trigger";
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
