#pragma once

#include <QNetworkRequest>
#include <QUrl>
#include <QThread>
#include <QRegularExpression>

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/macros.hpp>

namespace NLP {
struct Sentence;
struct SenTree : SharedPtrApi<SenTree> {
    Sentence*          parent;
    QString            tag;
    QString            lexem;
    Opt<int>           index = std::nullopt;
    Vec<SPtr<SenTree>> nested;
    Vec<sem::SemId>    orgIds;
    struct Dep {
        SenTree*     tree;
        QString      kind;
        Opt<QString> sub;
    };

    Opt<Dep> governor;
    Vec<Dep> dependencies;

    int                  enumerateItems(int start = 0);
    QString              treeRepr(int indent = 0) const;
    static SPtr<SenTree> parse(Sentence* parent, QString const& text);
    Opt<SenTree*>        atIndex(int index) {
        if (index == this->index) {
            return this;
        } else {
            for (auto& sub : nested) {
                auto res = sub->atIndex(index);
                if (res) {
                    return res;
                }
            }
            return std::nullopt;
        }
    }

  private:
    struct lexer;
    static SPtr<SenTree> parse(Sentence* parsed, lexer& lex);
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


struct Sentence : SharedPtrApi<Sentence> {
    DECL_FIELDS(
        Sentence,
        (),
        ((int), index, 0),
        ((SenTree::Ptr), parse, nullptr),
        ((Vec<Token>), tokens, {}),
        ((Vec<Dependency>), basicDependencies, {}),
        ((Vec<Dependency>), enhancedDependencies, {}),
        ((Vec<Dependency>), enhancedPlusPlusDependencies, {}));
};

struct OrgText {
    struct Word {
        QString    text;
        sem::SemId id = sem::SemId::Nil();
    };

    Vec<Word> text;
};

struct Parsed : public SharedPtrApi<Parsed> {
    OrgText            original;
    int                posStart;
    int                posEnd;
    Vec<Sentence::Ptr> sentence;
};


struct Rule {
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
    };

    struct Match {
        bool negated;
        struct Tag {
            QString prefix;
            bool    glob;
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
    bool matches(SenTree::Ptr const& cst) const;

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

    inline Rule Dir(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Subtree{
            .sub = {lhs, rhs}, .kind = Rule::Subtree::Kind::Direct});
    }

    inline Rule Ind(Rule const& lhs, Rule const& rhs) {
        return Rule(Rule::Subtree{
            .sub = {lhs, rhs}, .kind = Rule::Subtree::Kind::Indirect});
    }


    inline Rule Tag(QString const& name) {
        return Rule{Rule::Match{
            .pos = name.endsWith("*") ? Rule::Match::
                           Tag{.prefix = name.first(name.length() - 1),
                               .glob   = true}
                                      : Rule::Match::Tag{.prefix = name}}};
    }
} // namespace builder

} // namespace NLP

class QNetworkAccessManager;
class QNetworkReply;

class NetworkThread : public QThread {
    Q_OBJECT

  public:
    explicit NetworkThread() {
        connect(this, &QThread::finished, this, &QObject::deleteLater);
    }

    virtual ~NetworkThread() override = default;
    virtual void run() override { exec(); }
};


class ExporterNLP
    : public QObject
    , public Exporter<ExporterNLP, std::monostate> {

    Q_OBJECT

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
            ((NLP::Parsed::Ptr), parsed, nullptr),
            ((int), posStart, 0),
            ((int), posEnd, 0));
    };


    QUrl                         requestUrl;
    Vec<Pair<Request, Response>> exchange;
    ExporterNLP(QUrl const& resp);
    ~ExporterNLP();
    void executeRequests();
    void waitForRequests();

    Vec<NLP::SenTree::Ptr> findMatches(NLP::Rule const& rule);

  private:
    std::atomic<int> pendingRequests = 0;

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
    SPtr<QNetworkAccessManager> netManager = nullptr;
    SPtr<NetworkThread>         netThread  = nullptr;

    void sendRequest(Request const& request, int index);
    void addRequestHooks(QNetworkReply* reply);
    void onFinishedResponse(QNetworkReply* reply);
};

QString to_string(NLP::Rule const&);
