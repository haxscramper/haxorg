#include "HttpDataProvider.hpp"
#include <QNetworkReply>


HttpDataProvider::HttpDataProvider() {
    connect(this, &QThread::finished, this, &QObject::deleteLater);
    netManager = std::make_shared<QNetworkAccessManager>();
    netManager->moveToThread(this);

    QObject::connect(
        this,
        static_cast<void (HttpDataProvider::*)(
            QNetworkRequest const&, int, QString const&)>(
            &HttpDataProvider::sendPostRequest),
        netManager.get(),
        [this](
            QNetworkRequest const& request,
            int                    index,
            QString const&         data) {
            QNetworkReply* reply = netManager->post(
                request, data.toUtf8());
            Q_CHECK_PTR(reply);
            reply->setProperty(
                "exchange-index", QVariant::fromValue(index));

            QObject::connect(
                reply, &QNetworkReply::finished, [reply, this]() {
                    if (onFinishedResponse) {
                        this->onFinishedResponse(
                            reply,
                            reply->property("exchange-index")
                                .value<int>());
                    }
                    pendingRequests.fetch_sub(1);
                });

            QObject::connect(
                reply,
                &QNetworkReply::errorOccurred,
                [this](const QNetworkReply::NetworkError& error) {
                    pendingRequests.fetch_sub(1);
                });

            QObject::connect(
                reply,
                &QNetworkReply::sslErrors,
                [this](const QList<QSslError>& errors) {
                    pendingRequests.fetch_sub(1);
                });
        });
}

void HttpDataProvider::waitForRequests(int sleepOn) {
    while (0 < pendingRequests.load()) {
        QThread::msleep(sleepOn);
    }
}

void HttpDataProvider::sendPostRequest(
    const QUrl&    url,
    const QString& data,
    int            requestId,
    int            timeout) {

    QNetworkRequest netRequest{url};
    netRequest.setTransferTimeout(timeout);

    netRequest.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/x-www-form-urlencoded");

    pendingRequests.fetch_add(1);
    emit sendPostRequest(netRequest, requestId, data);
}

struct PostCacheKeyStruct {
    DECL_FIELDS(
        PostCacheKeyStruct,
        (),
        ((QString), url, QString{}),
        ((QString), data, QString{}),
        ((HttpDataProvider::ResponseData),
         response,
         HttpDataProvider::ResponseData{}));
};

struct PostCacheData {
    DECL_FIELDS(
        PostCacheData,
        (),
        ((Vec<PostCacheKeyStruct>), postCache, {}));
};

void HttpDataProvider::addCache(const json& cacheData) {
    PostCacheData parsed;
    from_json<PostCacheData>(cacheData, parsed);
    for (auto const& it : parsed.postCache) {
        cache[{QUrl(it.url), it.data}] = it.response;
    }
}

json HttpDataProvider::toJsonCache() {
    json          result;
    PostCacheData conv;
    for (auto const& key : cache.keys()) {
        conv.postCache.push_back(PostCacheKeyStruct{
            key.first.toString(), key.second, cache[key]});
    }

    to_json<PostCacheData>(result, conv);

    return result;
}
