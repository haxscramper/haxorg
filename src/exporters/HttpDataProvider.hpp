#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QThread>
#include <QPair>
#include <QHash>
#include <QUrl>
#include <hstd/stdlib/Json.hpp>

class QNetworkAccessManager;
class QNetworkReply;


class HttpDataProvider : public QThread {
    Q_OBJECT
  public:
    struct ResponseData {
        DECL_FIELDS(ResponseData, (), ((QString), content, ""));
    };


    using PostCacheKey = QPair<QUrl, QString>;

  private:
    std::atomic<int>                  pendingRequests = 0;
    QHash<PostCacheKey, ResponseData> cache;

  public:
    bool isCacheEnabled = false;

    void addCache(json const& cacheData);
    json toJsonCache();
    void addCache(PostCacheKey const& key, ResponseData const& data) {
        cache[key] = data;
    }

    bool hashCached(PostCacheKey const& key) const {
        return cache.contains(key);
    }

    ResponseData const& getCached(PostCacheKey const& key) {
        return cache.value(key);
    }

    using OnPostCb = Func<
        void(QNetworkRequest const&, int, QString const&)>;

    explicit HttpDataProvider();

    virtual ~HttpDataProvider() override {
        quit();
        wait();
    }

    virtual void run() override { exec(); }
    OnPostCb     onPostRequest;
    void         waitForRequests(int sleepOn = 250);

    void sendPostRequest(
        QUrl const&    url,
        QString const& data,
        int            requestId,
        int            timeout = 5000);

    SPtr<QNetworkAccessManager> netManager = nullptr;

    Func<void(QNetworkReply* reply, int)> onFinishedResponse;

  signals:
    void sendPostRequest(
        QNetworkRequest const& request,
        int                    index,
        QString const&         data);
};
