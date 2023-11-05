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
    Session(asio::io_service& ios) : socket{ios}, timer{ios} {}

    tcp::socket& get_socket() { return socket; }

    void start() { start_header_read(); }

    void start_header_read() {
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
        std::size_t total_body_read,
        std::size_t expected_to_read) {

        CHECK(streambuf.size() + expected_to_read == total_body_read)
            << fmt("Staring body read with {} already in buffer, missing "
                   "{} and total expected {}, mismatch is {} bytes",
                   streambuf.size(),
                   expected_to_read,
                   total_body_read,
                   int(streambuf.size()) + int(expected_to_read)
                       - int(total_body_read));

        // Read the JSON body of the message
        asio::async_read(
            socket,
            streambuf,
            asio::transfer_exactly(expected_to_read),
            [this, total_body_read, self = shared_from_this()](
                boost::system::error_code ec, std::size_t length) {
                if (ec) {
                    LOG(ERROR) << "LSP request body transfer error " << ec
                               << " " << ec.message();
                } else {
                    self->process_body_content(total_body_read);
                }
                start();
            });
    }

    Opt<json> build_response(const json& request) {
        // Example: Check for completion request and send a
        // response
        std::string method = request["method"];
        if (method == "textDocument/completion") {
            LOG(INFO) << "Compiletion request";
            json result            = json::object();
            result["isIncomplete"] = false;
            result["items"]        = {
                json::object({{"label", "word1"}, {"kind", 1}}),
                json::object({{"label", "word2"}, {"kind", 1}})};

            return result;

        } else if (method == "initialize") {
            return json(
                {{"capabilities",
                  {{"textDocumentSync", 1},
                   {"completionProvider",
                    {{"resolveProvider", false},
                     {"triggerCharacters", {".", ":", "(", "\""}}}}}}});

        } else if (method == "initialized") {
            LOG(INFO) << "Client confirmed initialization";
            return std::nullopt;

        } else if (method == "textDocument/didSave") {
            return std::nullopt;

        } else if (method == "textDocument/didChange") {
            return std::nullopt;

        } else if (method == "textDocument/didOpen") {
            LOG(INFO) << "Opened "
                      << request["params"]["textDocument"]["uri"];
            return std::nullopt;

        } else if (method == "shutdown") {
            LOG(INFO) << "Client disconnected";
            return std::nullopt;

        } else {
            LOG(ERROR) << "Unknown request method" << request["method"];
            LOG(ERROR) << request.dump();
            return std::nullopt;
        }
    }

    void process_body_content(std::size_t length) {
        std::string body;
        body.resize(length);

        asio::buffer_copy(
            asio::buffer(&body[0], length), streambuf.data(), length);

        CHECK(length <= streambuf.size())
            << "Body content processing requires stream buffer containing "
               "at least "
            << length << " bytes of content, but stream buffer only has "
            << streambuf.size();

        CHECK(body.size() == length) //
            << fmt("Handling raw request to read content, expected {} but "
                   "got {}",
                   length,
                   body.size())
            << body.substr(0, std::max<int>(body.length(), 250)) << ".."
            << body.substr(std::min<int>(0, body.length() - 250));

        try {
            json      request  = json::parse(body);
            Opt<json> response = build_response(request);
            if (response) {
                json final = json::object(
                    {{"jsonrpc", "2.0"},
                     {"id", request["id"]},
                     {"result", *response}});


                std::string responseStr = final.dump();
                LOG(INFO) << "Sending completion" << responseStr;
                std::string headers = "Content-Length: "
                                    + std::to_string(responseStr.size())
                                    + "\r\n\r\n";
                socket.send(asio::buffer(headers + responseStr));
            }
        } catch (json::parse_error& err) {
            LOG(ERROR) << "Failed to parse content request";
            LOG(ERROR) << body;
            LOG(ERROR) << err.what();
        }
    }

    void process_header_content(
        const boost::system::error_code& ec,
        std::size_t                      length) {
        if (ec) {
            LOG(ERROR) << "LSP request header transfer error " << ec << " "
                       << ec.message();

        } else {
            LOG(INFO) << "Received request to read LSP";
            // Extract Content-Length from headers
            std::istream is(&streambuf);
            std::string  headers;
            headers.resize(length);
            is.read(&headers[0], length);
            std::string field     = "Content-Length: ";
            std::size_t start_pos = headers.find(field);
            if (start_pos == std::string::npos) {
                LOG(ERROR) << "Missing content-length header in the input";
                // Error: Missing Content-Length header
                return;
            }

            std::size_t num_end_pos      = headers.find("\r\n", start_pos);
            std::size_t content_len_size = num_end_pos - field.size()
                                         - start_pos;
            std::string content_len_text = headers.substr(
                start_pos + 16, content_len_size);


            LOG(INFO) << fmt(
                "Content text length text ['{}'], start pos {} end pos {}",
                content_len_text,
                start_pos,
                num_end_pos);

            std::size_t total_body_read = std::stoi(content_len_text);

            std::size_t header_end_offset = headers.find(
                "\r\n\r\n", start_pos);

            std::size_t expected_to_read = total_body_read
                                         - streambuf.size();

            std::string body{};
            body.resize(streambuf.size());
            asio::buffer_copy(
                asio::buffer(&body[0], streambuf.size()),
                streambuf.data(),
                streambuf.size());

            LOG(INFO) << body;

            LOG(INFO) << fmt(
                "Header size is {}, "
                "expected content size {}, with {} expected to be read, "
                "header offset is {}",
                headers.size(),
                total_body_read,
                expected_to_read,
                header_end_offset - start_pos);

            start_body_read(total_body_read, expected_to_read);
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
            LOG(ERROR) << "Failed to start the session" << err.message();
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

    LOG(INFO) << "Started LSP server";

    asio::io_service ios;
    Server           s(ios, 8080);
    ios.run();
    LOG(INFO) << "Completed server execution";

    return 0;
}
