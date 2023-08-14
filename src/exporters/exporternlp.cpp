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
#include <hstd/stdlib/algorithms.hpp>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterNLP, std::monostate>;

Q_LOGGING_CATEGORY(nlp, "check.nlp");

using namespace NLP;


struct Constituency::lexer {
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

SPtr<Constituency> Constituency::parse(
    Parsed*        parent,
    const QString& text) {
    Constituency::lexer lex{.data = text};
    qCDebug(nlp).noquote() << lex.data;
    return parse(parent, lex);
}

int Constituency::enumerateItems(int start) {
    if (nested.empty()) {
        this->index = start;
        ++start;
    } else {
        for (auto& sub : nested) {
            start = sub->enumerateItems(start);
        }
    }

    return start;
}

QString Constituency::treeRepr(int indent) const {
    auto res = QString("  ").repeated(indent);
    res.append(tag);
    if (!lexem.isEmpty()) {
        res += " '" + lexem + "'";
    }

    if (index) {
        res += " @ " + QString::number(index.value());
    }

    for (auto const& id : orgIds) {
        res += " " + id.getReadableId();
    }

    for (const auto& sub : nested) {
        res.append("\n");
        res.append(sub->treeRepr(indent + 1));
    }

    return res;
}

SPtr<Constituency> Constituency::parse(Parsed* parent, lexer& lex) {
    Constituency::Ptr result = Constituency::shared();
    result->parent           = parent;

    lex.space();
    lex.skip('(');
    while (lex.tok().isLetter() || lex.tok() == '-') {
        result->tag.append(lex.tok());
        lex.next();
    }

    lex.space();

    if (lex.at('(')) {
        while (!lex.at(')')) {
            lex.space();
            result->nested.push_back(Constituency::parse(parent, lex));
        }
    } else {
        while (!lex.at(')')) {
            result->lexem.push_back(lex.tok());
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
        from_json(j, tmp);
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
        //        qDebug().noquote() << to_compact_json(j, {.width = 240});
        int targetIndex = reply->property("exchange-index").value<int>();
        qCDebug(nlp) << "Got NLP server response for request"
                     << targetIndex;
        Response result{.valid = true};
        for (const auto& sent : j["sentences"]) {
            auto parsed          = Parsed::shared();
            parsed->constituency = Constituency::parse(
                parsed.get(),
                QString::fromStdString(sent["parse"].get<std::string>()));
            parsed->constituency->enumerateItems();

            qCDebug(nlp).noquote().nospace()
                << "\n"
                << parsed->constituency->treeRepr();

            result.sentences.push_back(parsed);

            from_json(sent["tokens"], parsed->tokens);
        }

        Vec<Pair<Slice<int>, sem::SemId>> rangeForId;
        int                               offset = 0;
        Request const& req = exchange.at(targetIndex).first;
        for (auto const& word : req.sentence.text) {
            Slice<int> range = slice1<int>(
                offset, offset + word.text.length());
            offset += word.text.length();
            rangeForId.push_back({range, word.id});
        }

        Func<void(Constituency::Ptr const&)> rec;
        rec = [&](Constituency::Ptr const& cst) {
            if (cst->index.has_value()) {
                NLP::Token const& token = cst->parent->tokens.at(
                    cst->index.value());
                Slice<int> target = slice1<int>(
                    token.characterOffsetBegin, token.characterOffsetEnd);
                for (auto const& rng : rangeForId) {
                    if (rng.first.contains(target)) {
                        cst->orgIds.push_back(rng.second);
                    }
                }

                if (cst->orgIds.empty()) {
                    for (auto const& rng : rangeForId) {
                        if (target.overlap(rng.first).has_value()) {
                            cst->orgIds.push_back(rng.second);
                        }
                    }
                }

                qDebug().noquote() << cst->treeRepr();
            } else {
                for (auto& sub : cst->nested) {
                    rec(sub);
                }
            }
        };

        for (auto& sent : result.sentences) {
            rec(sent->constituency);
        }

        exchange.at(targetIndex).second = result;
    }
    reply->deleteLater();
}

QString to_string(const NLP::Rule& rule) {
    QString result;
    switch (rule.getKind()) {
        case Rule::Kind::Match: {
            auto const& match = rule.getMatch();
            if (match.negated) {
                result += "!";
            }
            result += "{";
            if (match.pos) {
                result += "/" + match.pos->prefix
                        + (match.pos->glob ? "*" : "") + "/";
            }
            result += "}";
            break;
        }

        case Rule::Kind::Logic: {
            auto const& logic = rule.getLogic();
            switch (logic.kind) {
                case Rule::Logic::Kind::Optional: {
                    result += "?" + to_string(logic.params.at(0));
                    break;
                }
                case Rule::Logic::Kind::Not: {
                    result += "!" + to_string(logic.params.at(0));
                    break;
                }
                case Rule::Logic::Kind::Or:
                case Rule::Logic::Kind::And: {
                    result += join(
                        logic.kind == Rule::Logic::Kind::Or ? " or "
                                                            : " and ",
                        map(logic.params,
                            [](Rule const& r) { return to_string(r); }));
                }
            }

            break;
        }

        case Rule::Kind::Subtree: {
            auto const& sub = rule.getSubtree();

            result = QString("%1 %2 %3")
                         .arg(to_string(sub.sub.at(0)))
                         .arg(
                             sub.kind == Rule::Subtree::Kind::Direct
                                 ? "->"
                                 : "->>")
                         .arg(to_string(sub.sub.at(1)));
            break;
        }
    }

    return result;
}

namespace {
auto firstDirect(Constituency::Ptr const& cst, Rule const& rule)
    -> Opt<Constituency::Ptr> {
    for (const auto& sub : cst->nested) {
        if (rule.matches(sub)) {
            return sub;
        }
    }
    return std::nullopt;
};

auto firstIndirect(Constituency::Ptr const& cst, Rule const& rule)
    -> Opt<Constituency::Ptr> {
    for (const auto& sub : cst->nested) {
        if (rule.matches(sub)) {
            return sub;
        } else {
            auto nest = firstIndirect(sub, rule);
            if (nest) {
                return nest;
            }
        }
    }
    return std::nullopt;
};

} // namespace

bool Rule::matches(const Constituency::Ptr& cst) const {
    bool result;
    switch (getKind()) {
        case Kind::Match: {
            auto const& match = getMatch();

            enum class State
            {
                Matched,
                Failed,
                NotApplicable
            };

            State lemma = State::NotApplicable;
            State tag   = State::NotApplicable;

            if (match.lemma) {
                lemma = match.lemma->match(cst->lexem).hasMatch()
                          ? State::Matched
                          : State::Failed;
            }

            if (match.pos) {
                if (match.pos->glob) {
                    tag = cst->lexem.startsWith(match.pos->prefix)
                            ? State::Matched
                            : State::Failed;
                } else {
                    tag = cst->lexem == match.pos->prefix ? State::Matched
                                                          : State::Failed;
                }
            }

            result = (lemma == State::NotApplicable
                      || lemma == State::Matched)
                  && (tag == State::NotApplicable
                      || tag == State::Matched);

            if (match.negated) {
                result = !result;
            }
            break;
        }

        case Kind::Subtree: {
            auto const& tree = getSubtree();
            if (tree.sub.at(0).matches(cst)) {
                if (tree.kind == Subtree::Kind::Direct) {
                    return firstDirect(cst, tree.sub.at(1)).has_value();
                } else {
                    return firstIndirect(cst, tree.sub.at(1)).has_value();
                }
            } else {
                return false;
            }
            break;
        }

        case Kind::Logic: {
            auto const& logic = getLogic();
            switch (logic.kind) {
                case Logic::Kind::And: {
                    result = true;
                    for (auto const& sub : logic.params) {
                        if (!sub.matches(cst)) {
                            return false;
                        }
                    }
                    break;
                }
                case Logic::Kind::Or: {
                    result = false;
                    for (auto const& sub : logic.params) {
                        if (sub.matches(cst)) {
                            return true;
                        }
                    }
                }
                case Logic::Kind::Not: {
                    result = !logic.params.at(0).matches(cst);
                    break;
                }
                case Logic::Kind::Optional: {
                    result = true;
                    !logic.params.at(0).matches(cst);
                    break;
                }
            }

            break;
        }
    }

    return result;
}

Vec<Constituency::Ptr> ExporterNLP::findMatches(const NLP::Rule& rule) {
    Vec<Constituency::Ptr> res;
    for (auto const& [in, resp] : this->exchange) {
        for (auto const& parsed : resp.sentences) {
            if (rule.matches(parsed->constituency)) {
                res.push_back(parsed->constituency);
            }
        }
    }
    return res;
}
