#include "exporternlp.hpp"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLoggingCategory>
#include <QThread>
#include <hstd/stdlib/Json.hpp>

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
    netThread  = std::make_shared<NetworkThread>();
    netManager = std::make_shared<QNetworkAccessManager>();
    netManager->moveToThread(netThread.get());
    netThread->start();
    obj["annotators"] = QStringList({"tokenize", "ssplit", "pos", "parse"})
                            .join(", ");
    obj["outputFormat"] = "json";
    parameters.setObject(obj);

    query.addQueryItem(
        "properties", parameters.toJson(QJsonDocument::Compact));

    requestUrl.setQuery(query);

    QObject::connect(
        this,
        &ExporterNLP::sendQtRequest,
        netManager.get(),
        [this](
            QNetworkRequest const& request,
            int                    index,
            QString const&         data) {
            QNetworkReply* reply = netManager->post(
                request, data.toUtf8());
            qCDebug(nlp) << "Sent Network request"
                         << pendingRequests.load();
            Q_CHECK_PTR(reply);
            reply->setProperty(
                "exchange-index", QVariant::fromValue(index));
            addRequestHooks(reply);
        });
}

ExporterNLP::~ExporterNLP() {
    netThread->quit();
    netThread->wait();
}

void ExporterNLP::executeRequests() {
    for (int i = 0; i < exchange.size(); ++i) {
        sendRequest(exchange.at(i).first, i);
    }
}

void ExporterNLP::waitForRequests() {
    qDebug() << pendingRequests.load();
    while (0 < pendingRequests.load()) {
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
    pendingRequests.fetch_add(1);
    emit sendQtRequest(netRequest, index, data);
}

void ExporterNLP::addRequestHooks(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        this->onFinishedResponse(reply);
        pendingRequests.fetch_sub(1);
    });

    QObject::connect(
        reply,
        &QNetworkReply::errorOccurred,
        [this](const QNetworkReply::NetworkError& error) {
            qCWarning(nlp) << "Response had error ";
            pendingRequests.fetch_sub(1);
        });

    QObject::connect(
        reply,
        &QNetworkReply::sslErrors,
        [this](const QList<QSslError>& errors) {
            qCWarning(nlp) << "Response had error " << errors;
            pendingRequests.fetch_sub(1);
        });

    qCDebug(nlp) << "Added response hooks";
}


template <DescribedRecord T>
static void to_json(json& j, const T& str) {
    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;

    if (!j.is_object()) {
        j = json::object();
    }
    boost::mp11::mp_for_each<Md>(
        [&](auto const& field) { j[field.name] = str.*field.pointer; });

    boost::mp11::mp_for_each<Bd>([&](auto Base) {
        Node res = ::nlohmann::adl_serializer<
            typename decltype(Base)::type>::to_json(j, str);
    });
}

template <DescribedRecord T>
void from_json(const json& in, T& out) {
    using Bd = boost::describe::
        describe_bases<T, boost::describe::mod_any_access>;
    using Md = boost::describe::
        describe_members<T, boost::describe::mod_any_access>;
    boost::mp11::mp_for_each<Md>([&](auto const& field) {
        ::nlohmann::adl_serializer<decltype(field)>::from_json(
            in[field.name], out.*field.pointer);
    });

    boost::mp11::mp_for_each<Bd>([&](auto Base) {
        ::nlohmann::adl_serializer<typename decltype(Base)::type>::decode(
            in, out);
    });
}

void from_json(const json& in, QString& out) {
    out = QString::fromStdString(in.get<std::string>());
}

// template <typename T>
// void to_json(json& j, const Vec<T>& str) {
//     j = json::array();
//     for (auto const& it : str) {
//         json tmp;
//         ::nlohmann::adl_serializer<T>::to_json(tmp, it);
//         j.push_back(tmp);
//     }
// }


template <typename T>
void from_json(const json& in, Vec<T>& out) {
    for (auto const& j : in) {
        T tmp;
        ::nlohmann::adl_serializer<T>::from_json(j, tmp);
        out.push_back(tmp);
    }
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
        auto j = json::parse(reply->readAll().toStdString());
        //        qDebug().noquote() << to_compact_json(j, {.width = 120});
        int targetIndex = reply->property("exchange-index").value<int>();
        qCDebug(nlp) << "Got NLP server response for request"
                     << targetIndex;
        Response result{.valid = true};
        for (const auto& sent : j["sentences"]) {
            Parsed parsed{};
            parsed.constituency = Parsed::Constituency::parse(
                QString::fromStdString(sent["parse"].get<std::string>()));

            qCDebug(nlp).noquote().nospace()
                << "\n"
                << parsed.constituency.treeRepr();

            result.sentences.push_back(parsed);

            from_json(sent["tokens"], parsed.tokens);
        }

        exchange.at(targetIndex).second = result;
    }
    reply->deleteLater();
}
