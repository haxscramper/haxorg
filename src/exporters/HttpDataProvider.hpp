#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QThread>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;

class HttpDataProvider : public QThread {
    Q_OBJECT

  private:
    std::atomic<int> pendingRequests = 0;

  public:
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
