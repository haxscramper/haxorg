#pragma once

#include <QNetworkRequest>
#include <QUrl>
#include <QThread>
#include <QRegularExpression>

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <hstd/wrappers/graphviz.hpp>
#include <hstd/stdlib/GraphQuery.hpp>
#include "HttpDataProvider.hpp"
#include "TextAnnotatorCommon.hpp"

namespace NLP {

struct SenNode {
    DECL_DESCRIBED_ENUM(
        PosTag,
        ROOT,
        S,
        DT,
        NN,
        NP,
        VBZ,
        VBD,
        ADJP,
        ADVP,
        CC,
        IN,
        JJ,
        NNP,
        NNS,
        PP,
        PRP,
        RB,
        RBR,
        SBAR,
        TO,
        VB,
        VBN,
        VBP,
        VBG,
        VP,
        WHADVP,
        WRB,
        CD,
        PUNCT_COMMA,
        PUNCT_PERIOD);

    DECL_DESCRIBED_ENUM(
        EntityKind,
        NONE,
        PERSON,
        LOCATION,
        ORGANIZATION,
        MISC,
        MONEY,
        NUMBER,
        ORDINAL,
        PERCENT,
        DATE,
        TIME,
        DURATION,
        SET,
        EMAIL,
        URL,
        CITY,
        STATE_OR_PROVINCE,
        COUNTRY);

    Opt<int>        index    = 0;
    int             sentence = 0;
    int             group    = 0;
    EntityKind      entity;
    PosTag          tag;
    QString         lexem;
    Vec<sem::SemId> orgIds;
};

struct SenEdge {

    DECL_DESCRIBED_ENUM(
        DepKind,
        acl,
        advcl,
        advmod,
        aux,
        _case,
        cc,
        cop,
        compound,
        conj,
        det,
        mark,
        nsubj,
        obj,
        obl,
        parataxis,
        nummod,
        nmod,
        punct,
        amod,
        iobj,
        ROOT,
        dep,
        xcomp);

    struct Dep {
        DepKind      kind;
        Opt<QString> sub;
    };

    struct Nested {};

    SUB_VARIANTS(Kind, Data, data, getKind, Dep, Nested);
    Data data;
};


struct Rule : SharedPtrApi<Rule> {
    struct Relation {
        DECL_DESCRIBED_ENUM(
            Kind,
            /// ``A <reln B ``: A is the dependent of a relation
            /// reln with B
            DependentDirect,
            /// ``A >reln B ``: A is the governor of a relation
            /// reln with B
            GovernorDirect,
            /// ``A <<reln B ``: A is the dependent of a relation
            /// reln in a chain to B following dep->gov paths
            DependentIndirect,
            /// ``A >>reln B ``: A is the governor of a relation
            /// reln in a chain to B following gov->dep paths
            SGovernorIndirect,
            /// ``A x,y<<reln B ``: A is the dependent of a
            /// relation reln in a chain to B following dep->gov
            /// paths between distances of x and y
            DependentChain,
            /// ``A x,y>>reln B ``: A is the governor of a relation
            /// reln in a chain to B following gov->dep paths
            /// between distances of x and y
            GovernorChain,
            /// ``A == B ``: A and B are the same nodes in the same
            /// graph Precedes ``A . B ``: A immediately precedes
            /// B, i.e. A.index() == B.index() - 1
            Same,
            /// ``A $+ B ``: B is a right immediate sibling of A,
            /// i.e. A and B have the same parent and A.index() ==
            /// B.index() - 1
            RightImmediate,
            /// ``A $- B ``: B is a left immediate sibling of A,
            /// i.e. A and B have the same parent and A.index() ==
            /// B.index() + 1
            LeftImmedite,
            /// ``A $++ B ``: B is a right sibling of A, i.e. A and
            /// B have the same parent and A.index() < B.index()
            Right,
            /// ``A $-- B ``: B is a left sibling of A, i.e. A and
            /// B have the same parent and A.index() > B.index()
            Left,
            /// ``A @ B ``: A is aligned to B (this is only used
            /// when you have two dependency graphs which are
            /// aligned)
            Aligned);

        SPtr<Rule> head;
        SPtr<Rule> tail;
        Kind       kind;

        SenEdge::DepKind relKind;
        Opt<QString>     relSubKind;
    };

    struct Match {
        bool                    negated = false;
        IntSet<SenNode::PosTag> prefix;
        Opt<QRegularExpression> lemma;
        Opt<QString>            bindto;
    };

    struct Logic {
        DECL_DESCRIBED_ENUM(Kind, And, Or, Optional, Not);
        Kind            kind;
        Vec<SPtr<Rule>> params;
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Relation, Match, Logic);
    Data data;

    Rule(Data const& head) : data(head) {}
};

namespace builder {
    inline Rule::Logic Or(Rule::Ptr const& lhs, Rule::Ptr const& rhs) {
        return Rule::Logic{
            .params = {lhs, rhs}, .kind = Rule::Logic::Kind::Or};
    }

    inline Rule::Logic And(Rule::Ptr const& lhs, Rule::Ptr const& rhs) {
        return Rule::Logic{
            .params = {lhs, rhs}, .kind = Rule::Logic::Kind::And};
    }

    namespace rel {
        inline Rule::Ptr Dir(
            Rule::Ptr const& lhs,
            Rule::Ptr const& rhs,
            SenEdge::DepKind kind,
            Opt<QString>     subRel = std::nullopt) {
            return Rule::shared(Rule::Relation{
                .kind       = Rule::Relation::Kind::GovernorDirect,
                .head       = lhs,
                .tail       = rhs,
                .relKind    = kind,
                .relSubKind = subRel});
        }
    } // namespace rel

    inline Rule::Ptr Tag(SenNode::PosTag const& name) {
        return Rule::shared(
            Rule::Match{.negated = false, .prefix = {name}});
    }
} // namespace builder

struct SenGraph {
    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::bidirectionalS,
        SenNode,
        SenEdge>;

    using GraphTraits     = boost::graph_traits<Graph>;
    using VertDesc        = typename GraphTraits::vertex_descriptor;
    using EdgeDesc        = typename GraphTraits::edge_descriptor;
    using VertBundledType = typename boost::vertex_bundle_type<
        Graph>::type;
    using EdgeBundledType = typename boost::edge_bundle_type<Graph>::type;

    using QuerySystem = QuerySystem<Graph, int>;

    DECL_DESCRIBED_ENUM(
        GvFormat,
        DependenciesFirst,
        StructureFirst,
        StructureOnly,
        DependenciesOnly);
    Graphviz::Graph toGraphviz(GvFormat format);

    Graph graph;

    struct MatchResult {
        VertDesc vertex;
    };

    Vec<MatchResult> findMatches(VertDesc start, Rule::Ptr const& rule);
    Vec<MatchResult> findMatches(Rule::Ptr const& rule);
    bool             isMatching(VertDesc desc, Rule::Match const& match);
    bool             isMatching(EdgeDesc desc, Rule::Relation const& rel);
};

} // namespace NLP

class ExporterNLP
    : public AnnotatingVisitorBase<ExporterNLP, std::monostate>
    , public Exporter<ExporterNLP, std::monostate> {

  signals:
    void sendQtRequest(QNetworkRequest const&, int, QString const& data);

  public:
#define __ExporterBase Exporter<ExporterNLP, std::monostate>
    EXPORTER_USING()
#undef __ExporterBase
    using R = std::monostate;

    template <sem::NotOrg T>
    void visit(R& res, CR<T> value) {}

    template <typename T>
    void visit(R& res, CVec<T> values) {
        for (const auto& value : values) {
            visit(res, value);
        }
    }

    template <typename T>
    void visit(R& res, CR<Opt<T>> opt) {
        if (opt) {
            visit(res, *opt);
        }
    }

    template <typename T>
    void visitField(R& res, const char* name, CR<T> field) {
        visit(res, field);
    }

  public:
    struct Response {
        DECL_FIELDS(
            Response,
            (),
            ((bool), valid, false),
            ((NLP::SenGraph), parsed, NLP::SenGraph{}),
            ((int), posStart, 0),
            ((int), posEnd, 0));
    };


    QUrl                         urlBase;
    Vec<Pair<Request, Response>> exchange;
    ExporterNLP(QUrl const& resp);
    void executeRequests(SPtr<HttpDataProvider> http);

  public:
    virtual void onFinishedRequestVisit(Request const& req) override {
        exchange.push_back({req, Response{}});
    }

    void visitParagraph(R& t, sem::SemIdT<sem::Paragraph> par) {
        asSeparateRequest(t, par.toId());
    }

#define __visit(__Kind)                                                   \
    void visit##__Kind(R& res, In<sem::__Kind> leaf) {                    \
        visitLeafToken(leaf);                                             \
    }

    __visit(Word);
    __visit(Space);
    __visit(Punctuation);
    __visit(BigIdent);
    __visit(Placeholder);
    __visit(RawText);
    __visit(Newline);

  private:
    void onFinishedResponse(
        HttpDataProvider::ResponseData const& reply,
        int                                   targetIndex);
};
