#include <boost/asio/buffer.hpp>
#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <absl/log/log.h>
#include <hstd/stdlib/Json.hpp>
#include <absl/strings/str_split.h>
#include <absl/strings/str_format.h>
#include <absl/log/log_sink_registry.h>
#include <absl/log/initialize.h>
#include <absl/log/internal/globals.h>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <fstream>

namespace asio  = boost::asio;
namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http  = beast::http;  // from <boost/beast/http.hpp>

using asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session> {
  public:
    Session(asio::io_service& ios) : socket(ios) {}

    tcp::socket& get_socket() { return socket; }


    json build_response(const json& request) {
        // Example: Check for completion request and send a
        // response
        if (request["method"] == "textDocument/completion") {
            return {
                {"jsonrpc", "2.0"},
                {"id", request["id"]},
                {"result", {{"completions", {"word1", "word2"}}}}};

        } else {
            DLOG(ERROR) << "Unknown request method" << request["method"];
            DLOG(ERROR) << request.dump();
            return {};
        }
    }

    void handle_raw_request(std::size_t length) {
        LOG(INFO) << "Handling raw request" << request.body();
        try {
            json requestJson  = json::parse(request.body());
            json responseJson = build_response(requestJson);
            response.body()   = responseJson.dump();
            response.result(http::status::ok);
            response.set(http::field::content_type, "text/json");
        } catch (json::parse_error& err) {
            LOG(ERROR) << "Request handling contained invalid JSON "
                       << err.what();
            response.result(http::status::bad_request);
            response.body() = err.what();
        }
    }

    void wait_for_request() {
        LOG(INFO) << "Started session";
        auto self(shared_from_this());
        http::async_read(
            socket,
            buffer,
            request,
            [self](boost::system::error_code ec, std::size_t length) {
                LOG(INFO) << "Received input request";
                self->handle_read(ec, length);
            });
    }


    void handle_read(const boost::system::error_code& ec, size_t length) {
        handle_raw_request(length);
    }

  private:
    tcp::socket                       socket;
    http::request<http::string_body>  request;
    http::response<http::string_body> response;
    beast::flat_buffer                buffer{8192};
};

class Server {
  public:
    Server(asio::io_service& ios, short port)
        : ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port)) {
        LOG(INFO) << "Created server instance on port " << port;
        std::shared_ptr<Session> session = std::make_shared<Session>(ios);
        acceptor.async_accept(
            session->get_socket(),
            boost::bind(
                &Server::handle_accept,
                this,
                session,
                asio::placeholders::error));
    }

    void handle_accept(
        std::shared_ptr<Session>         session,
        const boost::system::error_code& err) {
        if (!err) {
            LOG(INFO) << "Accepted connection and created session";
            session->wait_for_request();
            session = std::make_shared<Session>(ios);
            acceptor.async_accept(
                session->get_socket(),
                boost::bind(
                    &Server::handle_accept,
                    this,
                    session,
                    asio::placeholders::error));
        } else {
            DLOG(ERROR) << "Failed to start the session" << err.message();
            session.reset();
        }
    }

  private:
    asio::io_service& ios;
    tcp::acceptor     acceptor;
};

class LinePrinterLogSink : public absl::LogSink {
  public:
    LinePrinterLogSink(const char* path) : file(path) {}
    void Send(const absl::LogEntry& entry) override {
        for (absl::string_view line : absl::StrSplit(
                 entry.text_message_with_prefix(), absl::ByChar('\n'))) {
            // Overprint severe entries for emphasis:
            for (int i = static_cast<int>(absl::LogSeverity::kInfo);
                 i <= static_cast<int>(entry.log_severity());
                 i++) {
                file << line << std::endl;
            }
        }
    }

  private:
    std::ofstream file;
};


int main(int argc, char* argv[]) {
    LinePrinterLogSink Sink("/tmp/org_log.log");
    absl::AddLogSink(&Sink);
    absl::log_internal::SetTimeZone(absl::LocalTimeZone());
    absl::log_internal::SetInitialized();

    DLOG(INFO) << "Started LSP server";
    try {
        asio::io_service ios;
        Server           s(ios, 8080);
        ios.run();
    } catch (std::exception& e) {
        DLOG(ERROR) << "IO service exited with exception" << e.what();
    }
    return 0;
}
