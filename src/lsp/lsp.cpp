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

#if false

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

    void process_request(std::size_t length) {
        std::string body = beast::buffers_to_string(request.body().data());
        LOG(INFO) << "Handling raw request" << body;
        try {
            json requestJson  = json::parse(body);
            json responseJson = build_response(requestJson);
            beast::ostream(response.body()) << responseJson.dump();
            response.result(http::status::ok);
            response.set(http::field::content_type, "text/json");
        } catch (json::parse_error& err) {
            LOG(ERROR) << "Request handling contained invalid JSON "
                       << err.what();
            response.result(http::status::bad_request);
            beast::ostream(response.body()) << err.what();
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
                self->process_request(length);
            });
    }

  private:
    tcp::socket                        socket;
    http::request<http::dynamic_body>  request;
    http::response<http::dynamic_body> response;
    beast::flat_buffer                 buffer{8192};
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


int main(int argc, char* argv[]) {
    DLOG(INFO) << "Started LSP server";
    try {
        asio::io_context ios;
        Server           s(ios, 8080);
        ios.run();
    } catch (std::exception& e) {
        DLOG(ERROR) << "IO service exited with exception" << e.what();
    }
    return 0;
}

#endif

#if true
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

#    include <boost/beast/core.hpp>
#    include <boost/beast/http.hpp>
#    include <boost/beast/version.hpp>
#    include <boost/asio.hpp>
#    include <chrono>
#    include <cstdlib>
#    include <ctime>
#    include <iostream>
#    include <memory>
#    include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http  = beast::http;          // from <boost/beast/http.hpp>
namespace net   = boost::asio;          // from <boost/asio.hpp>
using tcp       = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

namespace my_program_state {
std::size_t request_count() {
    static std::size_t count = 0;
    return ++count;
}

std::time_t now() { return std::time(0); }
} // namespace my_program_state

class http_connection
    : public std::enable_shared_from_this<http_connection> {
  public:
    http_connection(tcp::socket socket) : socket_(std::move(socket)) {}

    // Initiate the asynchronous operations associated with the connection.
    void start() {
        read_request();
        check_deadline();
    }

  private:
    // The socket for the currently connected client.
    tcp::socket socket_;

    // The buffer for performing reads.
    beast::flat_buffer buffer_{8192};

    // The request message.
    http::request<http::dynamic_body> request_;

    // The response message.
    http::response<http::dynamic_body> response_;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{
        socket_.get_executor(),
        std::chrono::seconds(60)};

    // Asynchronously receive a complete request message.
    void read_request() {
        LOG(INFO) << "Reading request";
        auto self = shared_from_this();

        http::async_read(
            socket_,
            buffer_,
            request_,
            [self](beast::error_code ec, std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);
                if (ec) {
                    LOG(ERROR)
                        << "Error code " << ec << " " << ec.message();
                } else {
                    LOG(INFO)
                        << "Request: "
                        << beast::buffers_to_string(self->buffer_.data());
                    self->process_request();
                }
            });
    }

    // Determine what needs to be done with the request message.
    void process_request() {
        LOG(INFO) << "Processing request";
        response_.version(request_.version());
        response_.keep_alive(false);

        switch (request_.method()) {
            case http::verb::get:
                response_.result(http::status::ok);
                response_.set(http::field::server, "Beast");
                create_response();
                break;

            default:
                // We return responses indicating an error if
                // we do not recognize the request method.
                response_.result(http::status::bad_request);
                response_.set(http::field::content_type, "text/plain");
                beast::ostream(response_.body())
                    << "Invalid request-method '"
                    << std::string(request_.method_string()) << "'";
                break;
        }

        write_response();
    }

    // Construct a response message based on the program state.
    void create_response() {
        if (request_.target() == "/count") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                << "<html>\n"
                << "<head><title>Request count</title></head>\n"
                << "<body>\n"
                << "<h1>Request count</h1>\n"
                << "<p>There have been "
                << my_program_state::request_count()
                << " requests so far.</p>\n"
                << "</body>\n"
                << "</html>\n";
        } else if (request_.target() == "/time") {
            response_.set(http::field::content_type, "text/html");
            beast::ostream(response_.body())
                << "<html>\n"
                << "<head><title>Current time</title></head>\n"
                << "<body>\n"
                << "<h1>Current time</h1>\n"
                << "<p>The current time is " << my_program_state::now()
                << " seconds since the epoch.</p>\n"
                << "</body>\n"
                << "</html>\n";
        } else {
            LOG(INFO) << "Creating response";
            response_.result(http::status::not_found);
            response_.set(http::field::content_type, "text/plain");
            beast::ostream(response_.body()) << "File not found\r\n";
        }
    }

    // Asynchronously transmit the response message.
    void write_response() {
        LOG(INFO) << "Writing response";
        auto self = shared_from_this();

        response_.content_length(response_.body().size());

        http::async_write(
            socket_, response_, [self](beast::error_code ec, std::size_t) {
                self->socket_.shutdown(tcp::socket::shutdown_send, ec);
                self->deadline_.cancel();
            });
    }

    // Check whether we have spent enough time on this connection.
    void check_deadline() {
        auto self = shared_from_this();

        deadline_.async_wait([self](beast::error_code ec) {
            if (!ec) {
                // Close socket to cancel any outstanding operation.
                self->socket_.close(ec);
            }
        });
    }
};

// "Loop" forever accepting new connections.
void http_server(tcp::acceptor& acceptor, tcp::socket& socket) {
    acceptor.async_accept(socket, [&](beast::error_code ec) {
        if (!ec) {
            std::make_shared<http_connection>(std::move(socket))->start();
        }
        http_server(acceptor, socket);
    });
}

int main() {
    LinePrinterLogSink Sink("/tmp/org_log.log");
    absl::AddLogSink(&Sink);
    absl::log_internal::SetTimeZone(absl::LocalTimeZone());
    absl::log_internal::SetInitialized();

    try {
        LOG(INFO) << "Started server";
        net::io_context ioc{1};
        tcp::acceptor   acceptor{ioc, tcp::endpoint(tcp::v4(), 8080)};
        tcp::socket     socket{ioc};
        http_server(acceptor, socket);

        ioc.run();
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

#endif
