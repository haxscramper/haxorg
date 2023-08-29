#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QThread>
#include <QPair>
#include <QHash>
#include <QUrl>
#include <QQueue>
#include <QMutex>
#include <hstd/stdlib/Json.hpp>

class QNetworkAccessManager;
class QNetworkReply;


class HttpDataProvider : public QThread {
    Q_OBJECT
  public:
    struct ResponseData {
        DECL_FIELDS(
            ResponseData,
            (),
            ((QString), content, ""),
            ((int), failRepeatCount, 0),
            ((QString), errorString, ""),
            ((bool), isError, false));
    };

    struct QueueData {
        int          responseId;
        ResponseData response;
    };

    using PostCacheKey = QPair<QString, QString>;

    QHash<PostCacheKey, ResponseData> cache;
    QHash<PostCacheKey, ResponseData> failCache;

  private:
    std::atomic<int>  pendingRequests = 0;
    QMutex            queueMutex;
    QMutex            cacheMutex;
    QQueue<QueueData> responseQueue;

  public:
    bool isCacheEnabled = false;
    int  cacheFailAfter = 5;

    void      enqueue(QueueData const& data);
    QueueData dequeue();
    void      addCache(json const& cacheData);
    json      toJsonCache();
    void      addCache(PostCacheKey const& key, ResponseData const& data);
    bool      hasCached(PostCacheKey const& key);
    bool      hasData();

    ResponseData getCached(PostCacheKey const& key);

    using OnPostCb = Func<
        void(QNetworkRequest const&, int, QString const&)>;

    explicit HttpDataProvider();

    virtual ~HttpDataProvider() override {
        quit();
        wait();
    }

    virtual void run() override { exec(); }
    OnPostCb     onPostRequest;

    void waitForRequests(int sleepOn = 250);
    void waitForData(int sleepOn = 250);
    int  getPendingCount() { return pendingRequests.load(); }
    bool hasPendingRequests() const;

    void sendPostRequest(
        QUrl const&    url,
        QString const& data,
        int            requestId,
        int            timeout = 5000);

    SPtr<QNetworkAccessManager> netManager = nullptr;

  signals:
    void sendPostRequest(
        QNetworkRequest const& request,
        int                    index,
        QString const&         data);
};
