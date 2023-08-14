#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/macros.hpp>

#include <QNetworkRequest>
#include <QUrl>
#include <QThread>

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
    struct OrgText {
        struct Word {
            QString    text;
            sem::SemId id = sem::SemId::Nil();
        };

        Vec<Word> text;
    };

    struct Parsed : public SharedPtrApi<Parsed> {
        struct Constituency {
            Parsed*           parent;
            QString           tag;
            QString           lexem;
            Opt<int>          index = std::nullopt;
            Vec<Constituency> nested;
            Vec<sem::SemId>   orgIds;

            int                 enumerateItems(int start = 0);
            QString             treeRepr(int indent = 0) const;
            static Constituency parse(Parsed* parent, QString const& text);

          private:
            struct lexer;
            static Constituency parse(Parsed* parsed, lexer& lex);
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

        struct Sentence {
            DECL_FIELDS(
                Sentence,
                (),
                ((int), index, 0),
                ((Constituency), parse, Constituency{}),
                ((Vec<Dependency>), basicDependencies, {}),
                ((Vec<Dependency>), enhancedDependencies, {}),
                ((Vec<Dependency>), enhancedPlusPlusDependencies, {}));
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

        OrgText      original;
        int          posStart;
        int          posEnd;
        Constituency constituency;
        Sentence     sentence;
        Vec<Token>   tokens;
    };

    struct Request {
        OrgText sentence;
    };

    struct Response {
        DECL_FIELDS(
            Response,
            (),
            ((bool), valid, false),
            ((Vec<Parsed::Ptr>), sentences, {}),
            ((Parsed::Sentence), original, Parsed::Sentence{}),
            ((int), posStart, 0),
            ((int), posEnd, 0));
    };

    QUrl                         requestUrl;
    Vec<Pair<Request, Response>> exchange;
    ExporterNLP(QUrl const& resp);
    ~ExporterNLP();
    void executeRequests();
    void waitForRequests();

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
            activeRequest->sentence.text.push_back(                       \
                OrgText::Word{.text = leaf->text, .id = leaf.toId()});    \
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
