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
        ADJP,
        ADVP,
        HYPH,
        NNP,
        NML,
        PRP,
        QP,
        SBAR,
        VP,
        WHADVP,
        FRAG,
        NP_TMP,
        PRN,
        PRT,
        SINV,
        WHNP,
        NNPS,
        LST,
        CC,   //	coordinating conjunction 	and
        CD,   //	cardinal number 	1, third
        DT,   //	determiner 	the
        EX,   //	existential there 	there is
        FW,   //	foreign word 	les
        IN,   //	preposition, subordinating conjunction 	in, of, like
        JJ,   //	adjective 	green
        JJR,  //	adjective, comparative 	greener
        JJS,  //	adjective, superlative 	greenest
        LS,   //	list marker 	1)
        MD,   //	modal 	could, will
        NN,   //	noun, singular or mass 	table
        NNS,  //	noun plural 	tables
        NP,   //	proper noun, singular 	John
        NPS,  //	proper noun, plural 	Vikings
        PDT,  //	predeterminer 	both the boys
        POS,  //	possessive ending 	friend’s
        PP,   //	personal pronoun 	I, he, it
        PPZ,  //	possessive pronoun 	my, his
        RB,   //	adverb 	however, usually, naturally, here, good
        RBR,  //	adverb, comparative 	better
        RBS,  //	adverb, superlative 	best
        RP,   //	particle 	give up
        SENT, //	Sentence-break punctuation 	. ! ?
        SYM,  //	Symbol 	/ [ = *
        TO,   //	infinitive ‘to’ 	togo
        UH,   //	interjection 	uhhuhhuhh
        VB,   //	verb be, base form 	be
        VBD,  //	verb be, past tense 	was, were
        VBG,  //	verb be, gerund/present participle 	being
        VBN,  //	verb be, past participle 	been
        VBP,  //	verb be, sing. present, non-3d 	am, are
        VBZ,  //	verb be, 3rd person sing. present 	is
        VH,   //	verb have, base form 	have
        VHD,  //	verb have, past tense 	had
        VHG,  //	verb have, gerund/present participle 	having
        VHN,  //	verb have, past participle 	had
        VHP,  //	verb have, sing. present, non-3d 	have
        VHZ,  //	verb have, 3rd person sing. present 	has
        VV,   //	verb, base form 	take
        VVD,  //	verb, past tense 	took
        VVG,  //	verb, gerund/present participle 	taking
        VVN,  //	verb, past participle 	taken
        VVP,  //	verb, sing. present, non-3d 	take
        VVZ,  //	verb, 3rd person sing. present 	takes
        WDT,  //	wh-determiner 	which
        WP,   //	wh-pronoun 	who, what
        WRB,  //	wh-abverb 	where, when
        UCP,
        PUNCT_COMMA,
        PUNCT_COLON,
        PUNCT_QUOTE_OPEN,
        PUNCT_QUOTE_CLOSE,
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
        NATIONALITY,
        PERCENT,
        DATE,
        TIME,
        DURATION,
        SET,
        EMAIL,
        TITLE,
        URL,
        CITY,
        STATE_OR_PROVINCE,
        CAUSE_OF_DEATH,
        COUNTRY,
        CRIMINAL_CHARGE);

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
        ccomp,
        cc,
        cop,
        compound,
        conj,
        det,
        mark,
        nsubj,
        obj,
        obl,
        expl,
        parataxis,
        nummod,
        nmod,
        punct,
        fixed,
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
    void format(ColStream& os);

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
