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

    SPtr<QNetworkAccessManager> netManager = nullptr;

    OnPostCb onPostRequest;

    void waitForRequests(int sleepOn = 250) {
        while (0 < pendingRequests.load()) {
            QThread::msleep(sleepOn);
        }
    }

    int sendPostRequest(QUrl const& url, QString const& data);

    int requestId = 0;

    Func<void(QNetworkReply* reply)> onFinishedResponse;

  signals:
    void sendPostRequest(
        QNetworkRequest const& request,
        int                    index,
        QString const&         data);
};
