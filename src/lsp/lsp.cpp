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

template <typename... _Args>
[[nodiscard]] inline std::string fmt(
    std::format_string<_Args...> __fmt,
    _Args&&... __args) {
    return std::vformat(__fmt.get(), std::make_format_args(__args...));
}

class Session : public std::enable_shared_from_this<Session> {
  public:
    Session(asio::io_service& ios) : socket{ios}, timer{ios} {}

    tcp::socket& get_socket() { return socket; }

    void start() { start_header_read(); }

    void start_header_read() {
        LOG(INFO) << "Started header reading";
        asio::async_read_until(
            socket,
            streambuf,
            "\r\n\r\n",
            [self = shared_from_this()](
                boost::system::error_code ec, std::size_t length) {
                self->process_header_content(ec, length);
            });
    }

    void start_body_read(
        std::size_t content_length,
        std::size_t expected_content) {
        LOG(INFO) << fmt(
            "starting read of the body with the full size {} and missing "
            "size {}",
            content_length,
            expected_content);

        timer.expires_from_now(std::chrono::seconds(2));
        timer.async_wait([&](const boost::system::error_code& ec) {
            if (!ec) {
                socket.cancel();
                LOG(ERROR) << "Body content read timeout";
            }
        });

        // Read the JSON body of the message
        asio::async_read(
            socket,
            streambuf,
            [this, expected_content](
                const boost::system::error_code& error,
                std::size_t bytes_transferred) -> std::size_t {
                if (error) {
                    LOG(ERROR)
                        << "Detected failure during stream buffer reading "
                        << error.message();
                    return 0;
                } else if (bytes_transferred >= expected_content) {
                    LOG(INFO) << "Completed the transfer";
                    return 0;
                } else {
                    auto left = expected_content - bytes_transferred;
                    LOG(INFO)
                        << fmt("Transferred {}, {} left",
                               bytes_transferred,
                               left);
                    return left;
                }
            },
            [this, content_length, self = shared_from_this()](
                boost::system::error_code ec, std::size_t length) {
                if (ec) {
                    LOG(ERROR) << "LSP request body transfer error " << ec
                               << " " << ec.message();
                } else {
                    self->process_body_content(content_length);
                }
                start();
            });
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

    void process_body_content(std::size_t length) {
        std::string body;
        body.resize(length);
        asio::buffer_copy(
            asio::buffer(&body[0], length), streambuf.data(), length);

        LOG(INFO) << fmt(
            "Handling raw request to read content of {} chars ",
            body.size())
                  << body;

        json        request     = json::parse(body);
        json        response    = build_response(request);
        std::string responseStr = response.dump();
        std::string headers     = "Content-Length: "
                            + std::to_string(responseStr.size())
                            + "\r\n\r\n";
        socket.send(asio::buffer(headers + responseStr));
    }

    void process_header_content(
        const boost::system::error_code& ec,
        size_t                           length) {
        if (ec) {
            LOG(ERROR) << "LSP request header transfer error " << ec << " "
                       << ec.message();

        } else {
            DLOG(INFO) << "Received request to read LSP";
            // Extract Content-Length from headers
            std::istream is(&streambuf);
            std::string  headers;
            headers.resize(length);
            is.read(&headers[0], length);
            std::size_t pos = headers.find("Content-Length: ");
            if (pos == std::string::npos) {
                DLOG(ERROR)
                    << "Missing content-length header in the input";
                // Error: Missing Content-Length header
                return;
            } else {
                LOG(INFO) << "Header content" << headers;
            }

            std::size_t content_length = std::stoi(
                headers.substr(pos + 16));

            std::size_t expected_content = content_length
                                         - (streambuf.size()
                                            - headers.size())
                                         - 24;
            LOG(INFO) << fmt(
                "Header size is {}, buffer size {}, buffer capacity {}, "
                "expected content size {}, with {} expected to be read",
                headers.size(),
                streambuf.size(),
                streambuf.capacity(),
                content_length,
                expected_content);

            start_body_read(content_length, expected_content);
        }
    }

  private:
    tcp::socket        socket;
    asio::steady_timer timer;
    asio::streambuf    streambuf;
};

class Server {
  public:
    Server(asio::io_service& ios, short port)
        : ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port)) {
        LOG(INFO) << "Created server instance on port " << port;
        start_accept();
    }

    void start_accept() {
        std::shared_ptr<Session> session = std::make_shared<Session>(ios);
        acceptor.async_accept(
            session->get_socket(),
            [this, session](boost::system::error_code const& err) {
                this->handle_accept(session, err);
            });
    }


    void handle_accept(
        std::shared_ptr<Session>         session,
        const boost::system::error_code& err) {
        if (!err) {
            LOG(INFO) << "Accepted connection and created session";
            session->start();
        } else {
            DLOG(ERROR) << "Failed to start the session" << err.message();
        }
        start_accept();
    }

  private:
    asio::io_service& ios;

    tcp::acceptor acceptor;
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
        LOG(INFO) << "Completed server execution";
    } catch (std::exception& e) {
        DLOG(ERROR) << "IO service exited with exception" << e.what();
    }
    return 0;
}
