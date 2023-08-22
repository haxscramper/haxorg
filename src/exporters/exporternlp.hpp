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
#include "HttpDataProvider.hpp"

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
        VP,
        WHADVP,
        WRB);

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
        punct,
        ROOT,
        xcomp);

    struct Dep {
        DepKind      kind;
        Opt<QString> sub;
    };

    struct Nested {};

    SUB_VARIANTS(Kind, Data, data, getKind, Dep, Nested);
    Data data;
};

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

    Graphviz::Graph toGraphviz();

    Graph graph;
};

struct OrgText {
    struct Word {
        QString    text;
        sem::SemId id = sem::SemId::Nil();
    };

    Vec<Word> text;
};

struct Rule {
    struct Result {
        Opt<SenGraph::VertDesc> tree = std::nullopt;
        Result() {}
        Result(SenGraph::VertDesc tree) : tree(tree) {}
        bool matches() const { return tree.has_value(); }
    };

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

        Vec<Rule> rel;
        Kind      kind;

        Opt<SenEdge::DepKind> relKind;
        Opt<QString>          relSubKind;
    };

    struct Match {
        bool negated = false;
        struct Tag {
            IntSet<SenNode::PosTag> prefix;
        };

        Opt<QRegularExpression> lemma;
        Opt<Tag>                pos;
        Opt<QString>            bindto;
    };

    struct Logic {
        DECL_DESCRIBED_ENUM(Kind, And, Or, Optional, Not);
        Kind      kind;
        Vec<Rule> params;
    };

    struct Subtree {
        DECL_DESCRIBED_ENUM(Kind, Direct, Indirect);
        Kind      kind;
        Vec<Rule> sub;
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        Relation,
        Match,
        Logic,
        Subtree);


    Data data;

    Rule(CR<Data> data) : data(data) {}
    Rule() {}
};

namespace builder {
    inline Rule Or(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Logic{
            .params = {lhs, rhs}, .kind = Rule::Logic::Kind::Or});
    }

    inline Rule And(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Logic{
            .params = {lhs, rhs}, .kind = Rule::Logic::Kind::And});
    }

    namespace rel {
        inline Rule Dir(
            Rule const&      lhs,
            Rule const&      rhs,
            SenEdge::DepKind kind,
            Opt<QString>     subRel = std::nullopt) {
            return Rule(Rule::Relation{
                .rel = {lhs, rhs}, .relKind = kind, .relSubKind = subRel});
        }
    } // namespace rel

    inline Rule Dir(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Subtree{
            .sub = {lhs, rhs}, .kind = Rule::Subtree::Kind::Direct});
    }

    inline Rule Ind(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Subtree{
            .sub = {lhs, rhs}, .kind = Rule::Subtree::Kind::Indirect});
    }


    inline Rule Tag(SenNode::PosTag const& name) {
        return Rule{Rule::Match{
            .negated = false, .pos = Rule::Match::Tag{.prefix = {name}}}};
    }
} // namespace builder

} // namespace NLP

class ExporterNLP : public Exporter<ExporterNLP, std::monostate> {

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
    struct Request {
        NLP::OrgText sentence;
    };

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
    Opt<Request> activeRequest;

    void asSeparateRequest(R&, sem::SemId par);
    void visitParagraph(R& t, sem::SemIdT<sem::Paragraph> par) {
        asSeparateRequest(t, par.toId());
    }

#define __visit(__Kind)                                                   \
    void visit##__Kind(R& res, In<sem::__Kind> leaf) {                    \
        if (activeRequest) {                                              \
            activeRequest->sentence.text.push_back(NLP::OrgText::Word{    \
                .text = leaf->text, .id = leaf.toId()});                  \
        }                                                                 \
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

QString to_string(NLP::Rule const&);
