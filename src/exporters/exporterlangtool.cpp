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
        if (20 < http->getPendingCount()) {
            qDebug() << "Waiting to handle existing pending requests";
            QThread::msleep(1000);
        }
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
    if (reply.isError) {
        qCritical() << "Failed to execute Langtool check request"
                    << reply.content;
    } else {
        auto             j = json::parse(reply.content.toStdString());
        LangtoolResponse resp;
        from_json(j["matches"], resp.matches);
        exchange.at(targetIndex).second.resp = resp;
    }
}

void ExporterLangtool::format(ColStream& os) {
    for (auto const& [req, resp] : exchange) {
        Vec<LangtoolResponse::Match> matches;
        for (auto const& match : resp.resp.matches) {
            if (!Vec<QString>{"CONSECUTIVE_SPACES", "WHITESPACE_RULE"}
                     .contains(match.rule.id)) {
                matches.push_back(match);
            }
        }

        if (matches.empty()) {
            continue;
        }

        QString text;
        for (auto const& word : req.sentence.text) {
            text += word.text;
        }

        for (auto const& line : text.split("\n")) {
            os << "> " << line << "\n";
        }

        for (auto const& match : matches) {
            QString run = text.mid(match.offset, match.length);

            auto const& rule = match.rule;

            os << rule.id << " " << match.message << " "
               << "\n";

            json j;
            to_json(j, match);
            os << "  " << j.dump() << "\n";
        }
    }
}
