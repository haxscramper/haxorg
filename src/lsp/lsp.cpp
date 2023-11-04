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
#include <fstream>

namespace asio = boost::asio;
using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
  public:
    Session(asio::io_service& ios) : socket(ios) {}

    tcp::socket& get_socket() { return socket; }

    void start() {
        LOG(INFO) << "Started session";
        asio::async_read_until(
            socket,
            asio::dynamic_buffer(data),
            "\r\n\r\n",
            boost::bind(
                &Session::handle_read,
                this,
                shared_from_this(),
                asio::placeholders::error,
                asio::placeholders::bytes_transferred));
    }

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
        // Parse received data with nlohmann::json
        // TODO use string view
        std::string jsonStr  = data.substr(length);
        json        request  = json::parse(jsonStr);
        json        response = build_response(request);

        std::string responseStr = response.dump();
        std::string headers     = "Content-Length: "
                            + std::to_string(responseStr.size())
                            + "\r\n\r\n";
        socket.send(asio::buffer(headers + responseStr));

        // Clear buffer and wait for another message
        data.clear();
        start();
    }

    void handle_read(
        std::shared_ptr<Session>&        s,
        const boost::system::error_code& ec,
        size_t                           length) {
        if (!ec) {
            DLOG(INFO) << "Received request to read LSP";
            // Extract Content-Length from headers
            std::string headers = data.substr(0, length);
            std::size_t pos     = headers.find("Content-Length: ");
            if (pos == std::string::npos) {
                DLOG(ERROR)
                    << "Missing content-length header in the input";
                // Error: Missing Content-Length header
                return;
            }
            std::size_t contentLength = std::stoi(
                headers.substr(pos + 16));
            data.clear();

            // Read the JSON body of the message
            asio::async_read(
                socket,
                asio::dynamic_buffer(data),
                asio::transfer_exactly(contentLength),
                [this, length](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        handle_raw_request(length);
                    }
                });
        }
    }

  private:
    tcp::socket socket;
    std::string data;
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
            session->start();
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
