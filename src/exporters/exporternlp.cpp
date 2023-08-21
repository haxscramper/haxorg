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


struct SenTree::lexer {
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

SPtr<SenTree> SenTree::parse(Sentence* parent, const QString& text) {
    SenTree::lexer lex{.data = text};
    qCDebug(nlp).noquote() << lex.data;
    return parse(parent, lex);
}

int SenTree::enumerateItems(int start) {
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

ColText SenTree::treeRepr(int indent) const {
    ColStream os;
    os << QString("  ").repeated(indent) << os.magenta() << "[" << tag
       << "]" << os.end();

    if (true) {
        if (depBasic.governor) {
            os << " " << os.yellow() << "'"
               << depBasic.governor->tree->lexem << "'" << os.end() << " >"
               << os.blue() << depBasic.governor->kind
               << (depBasic.governor->sub
                       ? ":" + depBasic.governor->sub.value()
                       : "")
               << os.end();
        }
    } else {
    }

    if (!lexem.isEmpty()) {
        os << " " << os.yellow() << "'" << lexem << "'" << os.end();
    }

    if (index) {
        os << " @ " << os.cyan() << QString::number(index.value())
           << os.end();
    }

    for (auto const& id : orgIds) {
        os << " " << os.green() << id.getReadableId() << os.end();
    }


    for (const auto& sub : nested) {
        os << "\n";
        os << sub->treeRepr(indent + 1);
    }

    return os.getBuffer();
}

SPtr<SenTree> SenTree::parse(Sentence* parent, lexer& lex) {
    SenTree::Ptr result = SenTree::shared();
    result->parent      = parent;

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
            result->nested.push_back(SenTree::parse(parent, lex));
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
    http = std::make_shared<HttpDataProvider>();
    http->start();
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


    http->hasData();
    while (http->hasPendingRequests() || http->hasData()) {
        if (http->hasPendingRequests()) {
            http->waitForData();
        }
        while (http->hasData()) {
            HttpDataProvider::QueueData data = http->dequeue();
            onFinishedResponse(data.response, data.responseId);
        }
    }
    qDebug() << "Done request execution";
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
    QString data;
    for (const auto& word : request.sentence.text) {
        data += word.text;
    }

    qCDebug(nlp) << "Sending request to" << requestUrl << "with data"
                 << data.toUtf8();
    http->sendPostRequest(requestUrl, data, index);
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


void ExporterNLP::onFinishedResponse(
    HttpDataProvider::ResponseData const& reply,
    int                                   targetIndex) {
    qDebug() << "Finished NLP response trigger";
    if (reply.isError) {
        qCWarning(nlp) << "Failed to execute reply" << reply.errorString;


    } else {
        auto j = json::parse(reply.content.toStdString());
        qDebug().noquote() << to_compact_json(j, {.width = 240});
        qCDebug(nlp) << "Got NLP server response for request"
                     << targetIndex;
        Response result{.valid = true, .parsed = Parsed::shared()};
        for (const auto& inSent : j["sentences"]) {
            Sentence::Ptr sent = Sentence::shared();
            sent->parse        = SenTree::parse(
                sent.get(),
                QString::fromStdString(
                    inSent["parse"].get<std::string>()));

            sent->parse->enumerateItems();


            from_json(inSent["tokens"], sent->tokens);
            from_json(
                inSent["basicDependencies"], sent->basicDependencies);

            from_json(
                inSent["enhancedPlusPlusDependencies"],
                sent->enhancedPlusPlusDependencies);

            for (auto const& [isBasic, group] :
                 Vec<Pair<bool, Vec<Dependency>*>>{
                     {true, &sent->basicDependencies},
                     {false, &sent->enhancedPlusPlusDependencies},
                 }) {
                for (auto const& dep : *group) {
                    if (0 < dep.governor && 0 < dep.dependent) {
                        Opt<SenTree*> governor = sent->parse->atIndex(
                            dep.governor - 1);
                        Opt<SenTree*> dependent = sent->parse->atIndex(
                            dep.dependent - 1);
                        if (governor && dependent) {
                            auto split = dep.dep.split(":");
                            auto dep   = SenTree::Dep{
                                  .tree = dependent.value(),
                                  .kind = split[0],
                                  .sub  = 1 < split.size()
                                            ? Opt<QString>(split[1])
                                            : std::nullopt,
                            };

                            if (isBasic) {
                                (**governor)
                                    .depBasic.dependencies.push_back(dep);
                                dep.tree = governor.value();

                                Q_ASSERT_X(
                                    !(**dependent)
                                         .depBasic.governor.has_value(),
                                    "assign governor node",
                                    "Cannot override existing governor "
                                    "node");

                                (**dependent).depBasic.governor = dep;
                            } else {
                                (**governor)
                                    .depEnhanced.dependencies.push_back(
                                        dep);
                                dep.tree = governor.value();

                                (**dependent)
                                    .depEnhanced.governors.push_back(dep);
                            }
                        }
                    }
                }
            }
            result.parsed->sentence.push_back(sent);
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

        Func<void(SenTree::Ptr const&)> rec;
        rec = [&](SenTree::Ptr const& cst) {
            if (cst->index.has_value()) {
                NLP::Token const& token = cst->parent->tokens.at(
                    cst->index.value());
                Slice<int> target = slice1<int>(
                    token.characterOffsetBegin, token.characterOffsetEnd);
                for (auto const& rng : rangeForId) {
                    if (rng.first.contains(target)
                        && !cst->orgIds.contains(rng.second)) {
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

            } else {
                for (auto& sub : cst->nested) {
                    rec(sub);
                }
            }
        };

        for (auto& sent : result.parsed->sentence) {
            rec(sent->parse);
            qCDebug(nlp).noquote().nospace() << "\n"
                                             << sent->parse->treeRepr();
        }

        exchange.at(targetIndex).second = result;
    }
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
auto firstDirect(SenTree::Ptr const& cst, Rule const& rule)
    -> Rule::Result {
    for (const auto& sub : cst->nested) {
        auto out = rule.matches(sub);
        if (out.matches()) {
            return out;
        }
    }
    return Rule::Result{};
};

auto firstIndirect(SenTree::Ptr const& cst, Rule const& rule)
    -> Rule::Result {
    for (const auto& sub : cst->nested) {
        auto out = rule.matches(sub);
        if (out.matches()) {
            return out;
        } else {
            auto nest = firstIndirect(sub, rule);
            if (nest.matches()) {
                return nest;
            }
        }
    }
    return Rule::Result{};
};

} // namespace

Rule::Result Rule::Relation::matches(const SenTree::Ptr& tree) const {
    switch (kind) {
        case Kind::DependentDirect: {
            if (rel.at(0).matches(tree).matches()) {
                for (auto const& dep : tree->depBasic.dependencies) {
                    if (dep.kind == *relKind
                        && ((!relSubKind.has_value())
                            || (dep.sub.value()
                                == relSubKind.value_or("")))) {
                        return tree;
                    }
                }
            }
        }
    }

    for (auto const& sub : tree->nested) {
        auto res = matches(sub);
        if (res.matches()) {
            return res;
        }
    }

    return Result{};
}


Rule::Result Rule::matches(const SenTree::Ptr& cst) const {
    switch (getKind()) {
        case Kind::Relation: {
            return getRelation().matches(cst);
        }

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
                    tag = cst->tag.startsWith(match.pos->prefix)
                            ? State::Matched
                            : State::Failed;
                } else {
                    tag = cst->tag == match.pos->prefix ? State::Matched
                                                        : State::Failed;
                }
                qDebug() << match.pos->glob << match.pos->prefix
                         << cst->tag << tag;
            }

            bool result = (lemma == State::NotApplicable
                           || lemma == State::Matched)
                       && (tag == State::NotApplicable
                           || tag == State::Matched);

            if (match.negated) {
                result = !result;
            }

            if (result) {
                return cst;
            }

            break;
        }

        case Kind::Subtree: {
            auto const& tree = getSubtree();
            auto        out  = tree.sub.at(0).matches(cst);
            if (out.matches()) {
                if (tree.kind == Subtree::Kind::Direct) {
                    return firstDirect(cst, tree.sub.at(1));
                } else {
                    return firstIndirect(cst, tree.sub.at(1));
                }
            } else {
                return Result{};
            }
            break;
        }

        case Kind::Logic: {
            auto const& logic = getLogic();
            switch (logic.kind) {
                case Logic::Kind::And: {
                    for (auto const& sub : logic.params) {
                        auto res = sub.matches(cst);
                        if (!res.matches()) {
                            return res;
                        }
                    }

                    return Result{cst};
                }
                case Logic::Kind::Or: {
                    for (auto const& sub : logic.params) {
                        auto out = sub.matches(cst);
                        if (out.matches()) {
                            return out;
                        }
                    }
                }

                case Logic::Kind::Not: {
                    auto out = logic.params.at(0).matches(cst);
                    if (out.matches()) {
                        return Result{};
                    } else {
                        return out;
                    }
                }

                case Logic::Kind::Optional: {
                    return logic.params.at(0).matches(cst);
                }
            }

            break;
        }
    }

    return Result{};
}

Vec<SenTree::Ptr> ExporterNLP::findMatches(const NLP::Rule& rule) {
    Vec<SenTree::Ptr> res;
    for (auto const& [in, resp] : this->exchange) {
        for (auto const& parsed : resp.parsed->sentence) {
            auto which = rule.matches(parsed->parse);
            if (which.matches()) {
                res.push_back(which.tree.value());
            }
        }
    }
    return res;
}
