#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <string>
#include <thread>
#include <map>
#include <boost/log/trivial.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/stdlib/Map.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/ImmOrg.hpp>

#define OLOG(lvl) BOOST_LOG_TRIVIAL(lvl)

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;
using tcp       = boost::asio::ip::tcp;

template <typename F, typename C>
void read_opt_query_param_impl(
    UnorderedMap<std::string, std::string> const& params,
    C&                                            obj,
    F C::*      field,
    char const* name) {
    if (params.contains(name)) {
        auto j     = json::parse(params.at(name));
        obj.*field = from_json_eval<F>(j);
    }
}

template <typename F, typename C>
void read_opt_json_param_impl(
    json const& params,
    C&          obj,
    F C::*      field,
    char const* name) {
    if (params.contains(name)) {
        auto j     = json::parse(params.at(name));
        obj.*field = from_json_eval<F>(j);
    }
}


#define opt_query_param(map, obj, field)                                  \
    read_opt_query_param_impl(map, obj, &decltype(obj)::field, #field);

#define opt_json_param(map, obj, field)                                   \
    read_opt_json_param_impl(map, obj, &decltype(obj)::field, #field);

struct HttpState : public SharedPtrApi<HttpState> {
    org::ImmAstContext::Ptr ctx;
    org::ImmAstVersion      root;

    void parseRoot(std::string const& text) {
        root = ctx->addRoot(sem::parseString(text));
    }

    HttpState() : ctx{org::ImmAstContext::init_start_context()} {}
};

class HttpSession : public SharedPtrApi<HttpSession> {
    beast::tcp_stream                stream;
    beast::flat_buffer               buffer;
    http::request<http::string_body> req;
    std::shared_ptr<void>            res;
    HttpState::Ptr                   state;

  public:
    explicit HttpSession(tcp::socket&& socket)
        : stream(std::move(socket)) {
        OLOG(info) << "Created HTTP session";
    }

    void start() { read_request(); }

  private:
    void read_request() {
        auto self = shared_from_this();

        http::async_read(
            stream,
            buffer,
            req,
            [self](beast::error_code ec, std::size_t) {
                if (!ec) {
                    OLOG(info) << "Processing request";
                    self->process_request();
                }
            });
    }

    void process_request() {
        auto response = std::make_shared<
            http::response<http::string_body>>();
        response->version(req.version());
        response->keep_alive(false);
        response->set(http::field::content_type, "application/json");

        // Get the request target/route
        std::string_view target = req.target();

        OLOG(info) << fmt("Received request:'{}'", target);
        OLOG(info) << fmt("Body:\n{}", req.body());

        json query_body = json::parse(req.body());

        // Parse query parameters if present
        UnorderedMap<std::string, std::string> query_params;
        if (auto pos = target.find('?'); pos != std::string_view::npos) {
            std::string_view query = target.substr(pos + 1);
            std::string_view route = target.substr(0, pos);

            std::string        param;
            std::istringstream query_stream{std::string(query)};
            while (std::getline(query_stream, param, '&')) {
                if (auto eq_pos = param.find('=');
                    eq_pos != std::string::npos) {
                    query_params.insert_or_assign(
                        param.substr(0, eq_pos), param.substr(eq_pos + 1));
                }
            }
            target = route;
        }

        OLOG(info) << fmt("Query parametersn {}", query_params);

        switch (req.method()) {
            case http::verb::post: {
                if (target == "/api/parseString") {
                    response->result(http::status::ok);
                    ExporterJson exp{};
                    opt_query_param(query_params, exp, skipEmptyLists);
                    opt_query_param(query_params, exp, skipLocation);
                    opt_query_param(query_params, exp, skipId);
                    opt_query_param(query_params, exp, skipNullFields);
                    response->body() = exp
                                           .evalTop(sem::parseString(
                                               query_body.at("text")
                                                   .get<std::string>()))
                                           .dump();
                } else if (target == "/api/parseRoot") {
                    state->parseRoot(
                        query_body.at("text").get<std::string>());
                    response->result(http::status::ok);
                }
                break;
            }

            default:
                response->result(http::status::bad_request);
                response->body() = "{\"error\": \"Unknown HTTP method\"}";
                break;
        }

        response->prepare_payload();
        res = response;

        http::async_write(
            stream,
            *std::static_pointer_cast<http::response<http::string_body>>(
                res),
            [self = shared_from_this()](
                beast::error_code ec, std::size_t) {
                self->stream.socket().shutdown(
                    tcp::socket::shutdown_send, ec);
            });
    }
};

class HttpServer : public SharedPtrApi<HttpServer> {
    net::io_context& ioc;
    tcp::acceptor    acceptor;
    HttpState::Ptr   state;

  public:
    HttpServer(
        net::io_context& ioc,
        unsigned short   port,
        HttpState::Ptr   state)
        : ioc{ioc}, acceptor{ioc}, state{state} {
        OLOG(info) << "Constructing HTTP server";
        beast::error_code ec;

        tcp::endpoint endpoint{net::ip::make_address("0.0.0.0", ec), port};
        acceptor.open(endpoint.protocol(), ec);
        acceptor.set_option(net::socket_base::reuse_address(true), ec);
        acceptor.bind(endpoint, ec);
        acceptor.listen(net::socket_base::max_listen_connections, ec);
    }

    void run() { accept(); }

  private:
    void accept() {
        OLOG(info) << "Accepted connection";
        acceptor.async_accept(
            net::make_strand(ioc),
            beast::bind_front_handler(
                &HttpServer::on_accept, shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<HttpSession>(std::move(socket))->start();
        }
        accept();
    }
};

int main() {
    try {
        HttpState::Ptr  state   = std::make_shared<HttpState>();
        auto const      port    = 8080;
        auto const      threads = std::thread::hardware_concurrency();
        net::io_context ioc{static_cast<int>(threads)};

        std::make_shared<HttpServer>(ioc, port, state)->run();

        std::vector<std::thread> v;
        v.reserve(threads - 1);
        for (auto i = threads - 1; i > 0; --i) {
            v.emplace_back([&ioc] { ioc.run(); });
        }

        ioc.run();

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        OLOG(error) << e.what();
        return EXIT_FAILURE;
    }
}
