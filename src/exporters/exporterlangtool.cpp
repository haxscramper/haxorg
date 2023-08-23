#include "exporterlangtool.hpp"

#include <exporters/Exporter.cpp>

template class Exporter<ExporterLangtool, std::monostate>;

void ExporterLangtool::executeRequests(
    const QUrl&            url,
    SPtr<HttpDataProvider> http) {
    http->start();

    for (int i = 0; i < exchange.size(); ++i) {
        auto const& request = exchange.at(i).first;
        QString     data    = "text=";
        for (const auto& word : request.sentence.text) {
            data += word.text;
        }
        data += "&language=en-US&enabledOnly=false";

        http->sendPostRequest(url, data, i);
    }

    http->hasData();
    while (http->hasPendingRequests() || http->hasData()) {
        if (http->hasPendingRequests()) {
            http->waitForData();
        }
        while (http->hasData()) {
            HttpDataProvider::QueueData data = http->dequeue();
            onFinishedResponse(data.response, data.responseId);
        }
    }
}

void ExporterLangtool::onFinishedResponse(
    const HttpDataProvider::ResponseData& reply,
    int                                   targetIndex) {
    auto             j = json::parse(reply.content.toStdString());
    LangtoolResponse resp;
    qDebug().noquote() << to_compact_json(j, {.width = 230});
    from_json(j["matches"], resp.matches);
}
