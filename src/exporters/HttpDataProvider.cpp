#include "HttpDataProvider.hpp"
#include <QNetworkReply>
#include <hstd/stdlib/Filesystem.hpp>
#include <exception>


HttpDataProvider::HttpDataProvider() {
    connect(this, &QThread::finished, this, &QObject::deleteLater);
    netManager = std::make_shared<QNetworkAccessManager>();
    netManager->moveToThread(this);
    pendingRequests.store(0);

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


            QString displayUrl = request.url().toDisplayString();

            QObject::connect(
                reply,
                &QNetworkReply::finished,
                [reply, data, displayUrl, this]() {
                    ResponseData resp{.data = data, .url = displayUrl};
                    if (reply->error() != QNetworkReply::NoError) {
                        resp.isError     = true;
                        resp.errorString = reply->errorString();
                    } else {
                        resp.content = reply->readAll();
                    }

                    if (isCacheEnabled) {
                        addCache({displayUrl, data}, resp);
                    }

                    enqueue(QueueData{
                        .responseId = reply->property("exchange-index")
                                          .value<int>(),
                        .response = resp,
                    });

                    pendingRequests.fetch_sub(1);
                    reply->deleteLater();
                });

            QObject::connect(
                reply,
                &QNetworkReply::errorOccurred,
                [displayUrl, data, this](
                    const QNetworkReply::NetworkError& error) {
                    if (isCacheEnabled) {
                        addCache(
                            {displayUrl, data},
                            ResponseData{
                                .data            = data,
                                .url             = displayUrl,
                                .isError         = true,
                                .failRepeatCount = 0,
                            });
                    }

                    pendingRequests.fetch_sub(1);
                });

            QObject::connect(
                reply,
                &QNetworkReply::sslErrors,
                [displayUrl, data, this](const QList<QSslError>& errors) {
                    if (isCacheEnabled) {
                        addCache(
                            {displayUrl, data},
                            ResponseData{
                                .data            = data,
                                .url             = displayUrl,
                                .isError         = true,
                                .failRepeatCount = 0,
                            });
                    }

                    pendingRequests.fetch_sub(1);
                });
        });
}

void HttpDataProvider::waitForRequests(int sleepOn) {
    while (hasPendingRequests()) {
        QThread::msleep(sleepOn);
    }
}

void HttpDataProvider::waitForData(int sleepOn) {
    while (hasPendingRequests() && !hasData()) {
        QThread::msleep(sleepOn);
    }
}

bool HttpDataProvider::hasPendingRequests() const {
    return 0 < pendingRequests.load();
}

void HttpDataProvider::sendPostRequest(
    const QUrl&    url,
    const QString& data,
    int            requestId,
    int            timeout,
    bool           skipCache) {

    if (isCacheEnabled && !skipCache
        && hasCached({url.toDisplayString(), data})) {
        enqueue(QueueData{
            .responseId = requestId,
            .response   = getCached({url.toDisplayString(), data})});
    } else {
        QNetworkRequest netRequest{url};
        netRequest.setTransferTimeout(timeout);

        netRequest.setHeader(
            QNetworkRequest::ContentTypeHeader,
            "application/x-www-form-urlencoded");

        pendingRequests.fetch_add(1);
        emit sendPostRequest(netRequest, requestId, data);
    }
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
        ((Vec<PostCacheKeyStruct>), failCache, {}),
        ((Vec<PostCacheKeyStruct>), postCache, {}));
};

void HttpDataProvider::enqueue(const QueueData& data) {
    QMutexLocker locker{&queueMutex};
    Q_ASSERT(!data.response.url.isEmpty());
    if (!data.response.isError) {
        Q_ASSERT(!data.response.content.isEmpty());
    }
    responseQueue.push_back(data);
}

HttpDataProvider::QueueData HttpDataProvider::dequeue() {
    QMutexLocker locker{&queueMutex};
    QueueData    result = responseQueue.front();
    responseQueue.pop_front();
    return result;
}

void HttpDataProvider::addCache(const json& cacheData) {
    PostCacheData parsed;
    from_json<PostCacheData>(cacheData, parsed);
    writeFile(
        QFileInfo("/tmp/loadedaCacheData.json"),
        QString::fromStdString(to_compact_json(cacheData)));

    for (auto const& it : parsed.failCache) {
        addCache({it.url, it.data}, it.response);
    }

    for (auto const& it : parsed.postCache) {
        addCache({it.url, it.data}, it.response);
    }
}

json HttpDataProvider::toJsonCache() {
    json result;

    PostCacheData conv;
    for (auto const& key : cache.keys()) {
        conv.postCache.push_back(
            PostCacheKeyStruct{key.first, key.second, cache[key]});
    }

    for (auto const& key : failCache.keys()) {
        conv.failCache.push_back(
            PostCacheKeyStruct{key.first, key.second, failCache[key]});
    }

    to_json<PostCacheData>(result, conv);

    return result;
}

void HttpDataProvider::addCache(
    const PostCacheKey& key,
    const ResponseData& data) {
    QMutexLocker locker{&cacheMutex};
    if (data.isError) {
        if (failCache.contains(key)) {
            ++failCache[key].failRepeatCount;
        } else {
            failCache[key] = data;
        }
    } else {
        cache[key] = data;
        if (failCache.contains(key)) {
            failCache.remove(key);
        }
    }
}

bool HttpDataProvider::hasCached(const PostCacheKey& key) {
    QMutexLocker locker{&cacheMutex};
    return cache.contains(key)
        || (failCache.contains(key)
            && (cacheFailAfter <= failCache.value(key).failRepeatCount));
}

bool HttpDataProvider::hasData() {
    QMutexLocker locker{&queueMutex};
    return !responseQueue.isEmpty();
}

// FIXME returning reference here causes undefined behavior to manifest in
// the `executeRequests()` method of the NLP exporter. I was not able to
// debug the reason why this is so, but adding an extra call to `getCached`
// changes the error from UB in `sendRequests` to dereference error in
// qstring.
//
// UB in question is UndefinedBehaviorSanitizer: SEGV on unknown address
// __ubsan_handle_dynamic_type_cache_miss
//
// clang-format off
/*

==589801==ERROR: UndefinedBehaviorSanitizer: SEGV on unknown address (pc 0x7fe5d9eaeb39 bp 0x7fff9c462970 sp 0x7fff9c4625f0 T589801)
==589801==The signal is caused by a READ memory access.
==589801==Hint: this fault was caused by a dereference of a high value address (see register values below).  Disassemble the provided pc to learn which register was used.
 #0 0x7fe5d9eaeb39 in __dynamic_cast /usr/src/debug/gcc/gcc/libstdc++-v3/libsupc++/dyncast.cc:53:15
 #1 0x561b3a7838e0 in __ubsan::checkDynamicType(void*, void*, unsigned long) /home/runner/work/llvm-project/llvm-project/final/llvm-project/compiler-rt/lib/ubsan/ubsan_type_hash_itanium.cpp:245:5
 #2 0x561b3a782a42 in HandleDynamicTypeCacheMiss(__ubsan::DynamicTypeCacheMissData*, unsigned long, unsigned long, __ubsan::ReportOptions) /home/runner/work/llvm-project/llvm-project/final/llvm-project/compiler-rt/lib/ubsan/ubsan_handlers_cxx.cpp:36:7
 #3 0x561b3a782a0d in __ubsan_handle_dynamic_type_cache_miss /home/runner/work/llvm-project/llvm-project/final/llvm-project/compiler-rt/lib/ubsan/ubsan_handlers_cxx.cpp:87:3
 #4 0x561b3ac519dd in ExporterNLP::executeRequests() haxorg/src/exporters/exporternlp.cpp:154:17
 #5 0x561b3a79155b in HaxorgCli::exec() haxorg/cli/haxorgcli.cpp:1155:17
 #6 0x561b3a856ab2 in main haxorg/cli/main.cpp:256:9
 #7 0x7fe5d9a27ccf  (/usr/lib/libc.so.6+0x27ccf) (BuildId: 8f3291ff820508330af3a5ccb75de43d474ef19a)
 #8 0x7fe5d9a27d89 in __libc_start_main (/usr/lib/libc.so.6+0x27d89) (BuildId: 8f3291ff820508330af3a5ccb75de43d474ef19a)
 #9 0x561b3a75b4d4 in _start (build-haxorg-Clang_16-Debug/bin/cli.bin+0xb884d4)

*/
// clang-format on
HttpDataProvider::ResponseData HttpDataProvider::getCached(
    const PostCacheKey& key) {
    QMutexLocker                   locker{&cacheMutex};
    HttpDataProvider::ResponseData result;
    if (cache.contains(key)) {
        result = cache.value(key);
    } else if (failCache.contains(key)) {
        result = failCache.value(key);
    } else {
        throw std::domain_error("Missing key in caches");
    }

    Q_ASSERT(!result.data.isEmpty());

    return result;
}
