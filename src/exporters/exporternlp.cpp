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
#include <boost/property_map/function_property_map.hpp>
#include <boost/graph/graphviz.hpp>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterNLP, std::monostate>;

Q_LOGGING_CATEGORY(nlp, "check.nlp");

using namespace NLP;


struct Coref {
    DECL_FIELDS(
        Coref,
        (),
        ((QString), animacy, ""),
        ((int), endIndex, 0),
        ((QString), gender, ""),
        ((QString), number, ""),
        ((QString), text, ""),
        ((QString), type, ""),
        ((int), sentNum, 0),
        ((Vec<int>), position, {}),
        ((int), startIndex, 0),
        ((int), headIndex, 0),
        ((int), id, 0),
        ((bool), isRepresentativeMention, false));
};


struct Dependency {
    DECL_FIELDS(
        Dependency,
        (),
        ((QString), dep, ""),
        ((int), governor, 0),
        ((QString), governorGloss, ""),
        ((int), dependent, 0),
        ((QString), dependentGloss, ""));
};

namespace NLP {
struct Token {
    DECL_FIELDS(
        Token,
        (),
        ((int), index, 0),
        ((QString), word, ""),
        ((QString), originalText, ""),
        ((int), characterOffsetBegin, 0),
        ((int), characterOffsetEnd, 0),
        ((QString), pos, ""),
        ((QString), before, ""),
        ((QString), after, ""));
};

Graphviz::Graph SenGraph::toGraphviz(GvFormat format) {
    Graphviz::Graph gv{"sen"};
    gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    UnorderedMap<VertDesc, Graphviz::Node> nodes;
    UnorderedMap<int, Vec<Graphviz::Node>> sentenceWords;
    for (auto [it, it_end] = boost::vertices(graph); it != it_end; ++it) {
        SenNode const& prop = graph[*it];
        if (!prop.index && format == GvFormat::DependenciesOnly) {
            continue;
        }

        Graphviz::Node node = gv.node(to_string(*it));
        nodes.insert({*it, node});
        if (prop.index) {
            sentenceWords[prop.sentence].push_back(node);
            node.setAttr("sent_idx", prop.index.value());
            node.setLabel(
                "$#: '$#' ($#)"
                % to_string_vec(prop.tag, prop.lexem, prop.index.value()));
            node.setColor(Qt::darkGreen);
        } else {
            node.setLabel(to_string(prop.tag));
            node.setColor(Qt::darkYellow);
        }

        node.setShape(Graphviz::Node::Shape::rect);
    }

    if (format != GvFormat::DependenciesOnly
        && format != GvFormat::DependenciesFirst) {
        for (auto const& [sentence, words] : sentenceWords) {
            Graphviz::Graph sub = gv.newSubgraph(
                "sent" + to_string(sentence));
            sub.setNodeSeparation(0.2);
            sub.setRank(Graphviz::Graph::Rank::same);
            Vec<Graphviz::Node> linkwords;
            for (auto const& word :
                 sortedBy(words, [](Graphviz::Node node) {
                     return node.getAttr<int>("sent_idx").value();
                 })) {
                auto linkword = sub.node(
                    word.getAttr<QString>("label").value());
                linkword.setShape(Graphviz::Node::Shape::rect);
                linkword.setFontColor(Qt::darkRed);
                linkwords.push_back(linkword);
                gv.edge(word, linkword);
            }

            for (int i = 0; i < linkwords.size(); ++i) {
                if (0 < i) {
                    auto edge = sub.edge(
                        linkwords.at(i - 1), linkwords.at(i));
                    edge.setStyle("invis");
                }
            }
        }
    }


    for (auto [it, it_end] = boost::edges(graph); it != it_end; ++it) {
        SenEdge const& prop = graph[*it];
        if ((prop.getKind() == SenEdge::Kind::Dep
             && format == GvFormat::StructureOnly)
            || (prop.getKind() == SenEdge::Kind::Nested
                && format == GvFormat::DependenciesOnly)) {
            continue;
        }


        Graphviz::Node source = nodes.at(boost::source(*it, graph));
        Graphviz::Node target = nodes.at(boost::target(*it, graph));
        Graphviz::Edge edge   = gv.edge(source, target);

        QString res;
        if (prop.getKind() == SenEdge::Kind::Dep) {
            res += to_string(prop.getDep().kind);
            if (prop.getDep().sub) {
                res += ":";
                res += prop.getDep().sub.value();
            }

            edge.setLabel(res);
            if (format == GvFormat::StructureFirst) {
                edge.setAttr("constraint", "false");
                edge.setStyle("dashed");
            } else {
                edge.setStyle("bold");
            }

        } else {
            if (format == GvFormat::DependenciesFirst) {
                edge.setAttr("constraint", "false");
                edge.setStyle("dashed");
            } else {
                edge.setStyle("bold");
            }
        }
    }

    return gv;
}

Vec<SenGraph::MatchResult> SenGraph::findMatches(
    VertDesc         start,
    const Rule::Ptr& rule) {

    using Logic = Rule::Logic;
    using Rel   = Rule::Relation;
    using Match = Rule::Match;
    Vec<SenGraph::MatchResult> result;

    switch (rule->getKind()) {
        case Rule::Kind::Relation: {
            Rel const& rel = rule->getRelation();
            for (auto const& target : findMatches(start, rel.head)) {
                auto const& tail = rel.tail;
                switch (rel.kind) {
                    case Rel::Kind::GovernorDirect: {
                        for (auto [it, it_end] = boost::out_edges(
                                 target.vertex, graph);
                             it != it_end;
                             ++it) {

                            if (isMatching(*it, rel)) {
                                auto tailMatches = findMatches(
                                    boost::target(*it, graph), rel.tail);
                                if (!tailMatches.empty()) {
                                    result.push_back(SenGraph::MatchResult{
                                        target.vertex});
                                }
                            }
                        }
                        break;
                    }
                }
            }

            break;
        }

        case Rule::Kind::Logic: {
            qFatal() << "TODO";
            break;
        }

        case Rule::Kind::Match: {
            Match const& match = rule->getMatch();
            if (isMatching(start, match)) {
                result.push_back(SenGraph::MatchResult{start});
            }
            break;
        }
    }


    return result;
}

Vec<SenGraph::MatchResult> SenGraph::findMatches(const Rule::Ptr& rule) {
    Vec<SenGraph::MatchResult> result;
    for (auto [it, it_end] = boost::vertices(graph); it != it_end; ++it) {
        result.append(findMatches(*it, rule));
    }

    return result;
}

bool SenGraph::isMatching(VertDesc desc, const Rule::Match& match) {
    SenNode const& node = graph[desc];
    bool hasMatch = (match.prefix.empty() || match.prefix.contains(node.tag));
    if (hasMatch && match.lemma.has_value()) {
        hasMatch = match.lemma.value().match(node.lexem).hasMatch();
    }

    if (match.negated) {
        hasMatch = !hasMatch;
    }

    return hasMatch;
}

bool SenGraph::isMatching(EdgeDesc desc, const Rule::Relation& rel) {
    SenEdge const& edge = graph[desc];
    return edge.getKind() == SenEdge::Kind::Dep
        && edge.getDep().kind == rel.relKind
        && (!rel.relSubKind.has_value()
            || rel.relSubKind.value()
                   == edge.getDep().sub.value_or("?<?"));
}

} // namespace NLP


struct EntityMention {
    DECL_FIELDS(
        EntityMention,
        (),
        ((QString), text, ""),
        //        ((json), nerConfidences, json::object()),
        ((SenNode::EntityKind), ner, SenNode::EntityKind::NONE),
        ((int), docTokenBegin, 0),
        ((int), docTokenEnd, 0),
        ((int), tokenBegin, 0),
        ((int), tokenEnd, 0),
        ((int), characterOffsetBegin, 0),
        ((int), characterOffsetEnd, 0));
};

struct Sentence;

struct SenTree : SharedPtrApi<SenTree> {
    QString            lexem;
    Vec<SPtr<SenTree>> nested;
    Opt<int>           index = std::nullopt;
    Vec<sem::SemId>    orgIds;
    NlpPosTag          tag;
    Sentence*          parent;

    int enumerateItems(int start = 0) {
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


    ColText treeRepr(int indent = 0) const {
        ColStream os;
        os << QString("  ").repeated(indent) << os.magenta() << "[" << tag
           << "]" << os.end();

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
    static SPtr<SenTree> parse(Sentence* parent, QString const& text) {
        SenTree::lexer lex{.data = text};
        return parse(parent, lex);
    }

  private:
    struct lexer {
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


    static SPtr<SenTree> parse(Sentence* parent, lexer& lex) {
        SenTree::Ptr result = SenTree::shared();
        result->parent      = parent;

        lex.space();
        lex.skip('(');
        QString tag;
        while (lex.tok().isLetter() || //
               lex.tok() == '-' ||     //
               lex.tok() == ',' ||     //
               lex.tok() == '.' ||     //
               lex.tok() == ':' ||     //
               lex.tok() == '`' ||     //
               lex.tok() == '\'') {
            tag.append(lex.tok());
            lex.next();
        }

        Opt<NlpPosTag> parsed;
        if (tag == ",") {
            parsed = NlpPosTag::PUNCT_COMMA;
        } else if (tag == ".") {
            parsed = NlpPosTag::PUNCT_PERIOD;
        } else if (tag == ":") {
            parsed = NlpPosTag::PUNCT_COLON;
        } else if (tag == "``") {
            parsed = NlpPosTag::PUNCT_QUOTE_OPEN;
        } else if (tag == "''") {
            parsed = NlpPosTag::PUNCT_QUOTE_CLOSE;
        } else if (tag == "NP-TMP") {
            parsed = NlpPosTag::NP_TMP;
        } else if (tag == "-LRB-") {
            parsed = NlpPosTag::LRB;
        } else if (tag == "-RRB-") {
            parsed = NlpPosTag::RRB;
        } else {
            parsed = enum_serde<NlpPosTag>::from_string(tag);
        }

        if (!parsed) {
            qCritical() << "Unexpected POS tag:" << tag << lex.data;
            throw std::domain_error("Unexpected value for POS tag");
        }

        result->tag = parsed.value();

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
};

struct Sentence : SharedPtrApi<Sentence> {
    DECL_FIELDS(
        Sentence,
        (),
        ((int), index, 0),
        ((SenTree::Ptr), parse, nullptr),
        ((Vec<NLP::Token>), tokens, {}),
        ((Vec<Dependency>), basicDependencies, {}),
        ((Vec<Dependency>), enhancedDependencies, {}),
        ((Vec<EntityMention>), entitymentions, {}),
        ((Vec<Dependency>), enhancedPlusPlusDependencies, {}));
};


struct Parsed : public SharedPtrApi<Parsed> {
    OrgText                       original;
    int                           posStart;
    int                           posEnd;
    Vec<Sentence::Ptr>            sentence;
    UnorderedMap<Str, Vec<Coref>> corefs;
};


ExporterNLP::ExporterNLP(const QUrl& resp) : urlBase(resp) {}

void ExporterNLP::executeRequests(SPtr<HttpDataProvider> http) {
    QUrlQuery     query{};
    QJsonDocument parameters;
    QJsonObject   obj;
    http->start();
    obj["annotators"] = QStringList({"tokenize",
                                     "ssplit",
                                     "pos",
                                     "parse",
                                     "ner",
                                     "coref"})
                            .join(", ");
    obj["outputFormat"] = "json";
    parameters.setObject(obj);

    query.addQueryItem(
        "properties", parameters.toJson(QJsonDocument::Compact));

    QUrl requestUrl = urlBase;

    requestUrl.setQuery(query);

    for (int i = 0; i < exchange.size(); ++i) {
        auto const& request = exchange.at(i).first;
        QString     data;
        for (const auto& word : request.sentence.text) {
            data += word.text;
        }

        http->sendPostRequest(requestUrl, data, i);
        while (2 < http->getPendingCount()) {
            qDebug() << "NLP has excess pending requests, waiting" << i
                     << "out of" << exchange.size();
            QThread::msleep(1000);
        }
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
}

Parsed::Ptr parseDirectResponse(json j) {
    Parsed::Ptr parsed = Parsed::shared();
    for (auto const& [key, value] : j["corefs"].items()) {
        from_json(value, parsed->corefs[Str::fromStdString(key)]);
    }
    //    qDebug().noquote() << to_compact_json(j["corefs"], {.width =
    //    300});
    for (const auto& inSent : j["sentences"]) {
        Sentence::Ptr sent = Sentence::shared();
        sent->parse        = SenTree::parse(
            sent.get(),
            QString::fromStdString(inSent["parse"].get<std::string>()));
        //        qDebug().noquote()
        //            << to_compact_json(inSent["tokens"], {.width = 300});

        sent->parse->enumerateItems();

        from_json(inSent["entitymentions"], sent->entitymentions);
        from_json(inSent["tokens"], sent->tokens);
        from_json(inSent["basicDependencies"], sent->basicDependencies);

        from_json(
            inSent["enhancedPlusPlusDependencies"],
            sent->enhancedPlusPlusDependencies);

        parsed->sentence.push_back(sent);
    }

    return parsed;
}

void resolveOrgIds(Parsed::Ptr parsed, OrgText const& sent) {


    Func<void(SenTree::Ptr const&)> rec;
    rec = [&](SenTree::Ptr const& cst) {
        if (cst->index.has_value()) {
            Q_CHECK_PTR(cst->parent);
            NLP::Token const& token = cst->parent->tokens.at(
                cst->index.value());
            cst->orgIds = sent.overlappingNodes(slice1<int>(
                token.characterOffsetBegin, token.characterOffsetEnd));

        } else {
            for (auto& sub : cst->nested) {
                rec(sub);
            }
        }
    };

    for (auto& sent : parsed->sentence) {
        rec(sent->parse);
    }
}

void fillSentenceGraph(SenGraph& g, Parsed::Ptr const& parsed) {
    UnorderedMap<Pair<int, int>, SenGraph::VertDesc>   sentIdxToVertex;
    Func<SenGraph::VertDesc(SenTree::Ptr const&, int)> rec;
    rec = [&](SenTree::Ptr const& cst,
              int                 sentence) -> SenGraph::VertDesc {
        SenNode node;
        node.sentence = sentence;
        node.index    = cst->index;
        node.tag      = cst->tag;
        node.lexem    = cst->lexem;

        if (cst->nested.empty()) {
            SenGraph::VertDesc desc = boost::add_vertex(node, g.graph);
            sentIdxToVertex[{sentence, cst->index.value()}] = desc;
            return desc;
        } else {
            SenGraph::VertDesc desc = boost::add_vertex(node, g.graph);
            for (auto const& sub : cst->nested) {
                auto    subDesc = rec(sub, sentence);
                SenEdge edge;
                edge.data = SenEdge::Nested{};
                boost::add_edge(desc, subDesc, edge, g.graph);
            }

            return desc;
        }
    };

    for (int i = 0; i < parsed->sentence.size(); ++i) {
        Sentence::Ptr sent = parsed->sentence.at(i);
        rec(sent->parse, i);
    }

    for (int i = 0; i < parsed->sentence.size(); ++i) {
        Sentence::Ptr sent = parsed->sentence.at(i);
        for (auto const& dep : sent->enhancedPlusPlusDependencies) {
            if (0 < dep.governor && 0 < dep.dependent) {
                Opt<SenGraph::VertDesc> governor = sentIdxToVertex.get(
                    {i, dep.governor - 1});
                Opt<SenGraph::VertDesc> dependent = sentIdxToVertex.get(
                    {i, dep.dependent - 1});
                if (governor && dependent) {
                    auto split = dep.dep.split(":");
                    auto kind  = enum_serde<NlpDepKind>::from_string(
                        split[0] == "case" ? "_case" : split[0]);

                    if (!kind) {
                        qCritical()
                            << "Unexpected dependency kind" << split[0];
                        throw std::domain_error(
                            "Unexpected dependency kind");
                    }

                    auto dep = SenEdge::Dep{
                        .kind = kind.value(),
                        .sub  = 1 < split.size() ? Opt<QString>(split[1])
                                                 : std::nullopt,
                    };

                    boost::add_edge(
                        governor.value(),
                        dependent.value(),
                        SenEdge{.data = dep},
                        g.graph);
                }
            }
        }
    }
}

void ExporterNLP::onFinishedResponse(
    HttpDataProvider::ResponseData const& reply,
    int                                   targetIndex) {
    if (reply.isError) {
        qCWarning(nlp) << "Failed to execute reply" << targetIndex
                       << reply.errorString;

    } else {
        auto        j      = json::parse(reply.content.toStdString());
        Parsed::Ptr direct = parseDirectResponse(j);
        resolveOrgIds(direct, exchange.at(targetIndex).first.sentence);
        SenGraph result;
        fillSentenceGraph(result, direct);

        exchange.at(targetIndex).second = Response{
            .valid = true, .parsed = result};
    }
}

void ExporterNLP::format(ColStream& os) {}
