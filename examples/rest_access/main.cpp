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
#include <functional>
#include <tuple>
#include <type_traits>

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


// Helper to get function traits
template <typename T>
struct function_traits;

// Function pointer specialization
template <typename R, typename... Args>
struct function_traits<R (*)(Args...)> {
    using return_type             = R;
    using args_tuple              = std::tuple<std::decay_t<Args>...>;
    static constexpr size_t arity = sizeof...(Args);
};

// Method pointer specialization
template <typename C, typename R, typename... Args>
struct function_traits<R (C::*)(Args...) const> {
    using class_type              = C;
    using return_type             = R;
    using args_tuple              = std::tuple<std::decay_t<Args>...>;
    static constexpr size_t arity = sizeof...(Args);
};

struct ArgSpec {
    std::string name;
    bool        optional = false;
};

ArgSpec arg(std::string const& name) { return ArgSpec{.name = name}; }
ArgSpec opt_arg(std::string const& name) {
    return ArgSpec{.name = name, .optional = true};
}

void standalone_function(int arg1, int arg2, int opt1 = 123) {
    OLOG(info) << fmt(
        "Called standalone function {} {} {}", arg1, arg2, opt1);
}

struct RestHandlerContext {
    UnorderedMap<std::string, std::string>             query_params;
    std::shared_ptr<http::response<http::string_body>> response;
    std::string                                        route;
    json                                               query_body;

    RestHandlerContext(
        std::shared_ptr<http::response<http::string_body>> response)
        : response{response} {}

    template <typename T>
    T getArg(ArgSpec const& arg) {
        return query_body.at(arg.name).get<T>();
    }

    template <typename T>
    T getThis() {
        return getArg<T>(ArgSpec{"self"});
    }

    void setResponseBody(std::string const& text) {
        response->body() = text;
    }

    void setResponseResult(boost::beast::http::status status) {
        response->result(status);
    }


    void setRequest(http::request<http::string_body> const& req) {
        setTarget(req.target());
        setQueryBody(req.body());
    }

    void setQueryBody(std::string_view body) {
        query_body = json::parse(body);
    }

    void setTarget(std::string_view target) {
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
            this->route = route;
        } else {
            this->route = target;
        }
    }
};

// Handler implementation
class HandlerImpl {
    std::function<void(RestHandlerContext*)> callback_;
    std::vector<ArgSpec>                     args_;
    size_t                                   required_args_;

  public:
    template <typename F>
    HandlerImpl(F&& f, size_t req_args, std::vector<ArgSpec> args)
        : callback_(std::forward<F>(f))
        , args_(std::move(args))
        , required_args_(req_args) {}

    void call(RestHandlerContext* ctx) { callback_(ctx); }
};

// Helper for unpacking tuple into function arguments
template <typename Func, typename Tuple, size_t... I>
auto call_with_tuple_impl(Func&& f, Tuple&& t, std::index_sequence<I...>) {
    return std::forward<Func>(f)(std::get<I>(std::forward<Tuple>(t))...);
}

template <typename Func, typename Tuple>
auto call_with_tuple(Func&& f, Tuple&& t) {
    return call_with_tuple_impl(
        std::forward<Func>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<
            std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

// Handler construction helpers
class HandlerMapType {
    UnorderedMap<std::string, HandlerImpl> map;

    template <typename Func, typename... Args>
    auto make_handler_callback(
        Func                        f,
        std::vector<ArgSpec> const& arg_specs) {
        return [f, arg_specs](RestHandlerContext* ctx) {
            using traits      = function_traits<std::decay_t<Func>>;
            using args_tuple  = typename traits::args_tuple;
            using return_type = typename traits::return_type;

            // Build tuple of arguments
            args_tuple args;
            std::apply(
                [&](auto&... tuple_args) {
                    size_t idx = 0;
                    ((tuple_args = ctx->template getArg<
                                   std::decay_t<decltype(tuple_args)>>(
                          arg_specs[idx++])),
                     ...);
                },
                args);

            // Call function and serialize result
            if constexpr (std::is_void_v<return_type>) {
                call_with_tuple(f, args);
            } else {
                auto result = call_with_tuple(f, args);
                ctx->setResponseBody(
                    JsonSerde<return_type>::to_json(result).dump());
            }
            ctx->setResponseResult(http::status::ok);
        };
    }

    template <typename Class, typename Func>
    auto make_method_handler_callback(
        Func                        f,
        std::vector<ArgSpec> const& arg_specs) {
        return [f, arg_specs](RestHandlerContext* ctx) {
            using traits      = function_traits<std::decay_t<Func>>;
            using args_tuple  = typename traits::args_tuple;
            using return_type = typename traits::return_type;

            // Get instance
            auto instance = ctx->template getThis<Class>();

            // Build tuple of arguments
            args_tuple args;
            std::apply(
                [&](auto&... tuple_args) {
                    size_t idx = 0;
                    ((tuple_args = ctx->template getArg<
                                   std::decay_t<decltype(tuple_args)>>(
                          arg_specs[idx++])),
                     ...);
                },
                args);

            // Call method and serialize result
            auto result = call_with_tuple(
                [&instance, f](auto&&... args) {
                    return (instance.*f)(
                        std::forward<decltype(args)>(args)...);
                },
                args);

            if constexpr (!std::is_void_v<return_type>) {
                ctx->setResponseBody(
                    JsonSerde<return_type>::to_json(result).dump());
            }
            ctx->setResponseResult(http::status::ok);
        };
    }

  public:
    template <typename Func>
    void setFunction(
        std::string const&          endpoint,
        Func                        f,
        int                         required_args,
        std::vector<ArgSpec> const& args) {
        map.emplace(
            endpoint,
            HandlerImpl(
                make_handler_callback(f, args), required_args, args));
    }

    template <typename Class, typename Func>
    void setMethod(
        std::string const&          endpoint,
        Func                        f,
        int                         required_args,
        std::vector<ArgSpec> const& args) {
        map.emplace(
            endpoint,
            HandlerImpl(
                make_method_handler_callback<Class>(f, args),
                required_args,
                args));
    }

    void call(std::string const& target, RestHandlerContext* ctx) {
        map.at(target).call(ctx);
    }
};


#define opt_query_param(map, obj, field)                                  \
    read_opt_query_param_impl(map, obj, &decltype(obj)::field, #field);

#define opt_json_param(map, obj, field)                                   \
    read_opt_json_param_impl(map, obj, &decltype(obj)::field, #field);

struct HttpState : public SharedPtrApi<HttpState> {
    org::ImmAstContext::Ptr ctx;
    org::ImmAstVersion      root;
    HandlerMapType          handlers;

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
    explicit HttpSession(tcp::socket&& socket, HttpState::Ptr state)
        : stream(std::move(socket)), state{state} {
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
        LOGIC_ASSERTION_CHECK(state.get() != nullptr, "state is not set");
        auto response = std::make_shared<
            http::response<http::string_body>>();
        response->version(req.version());
        response->keep_alive(false);
        response->set(http::field::content_type, "application/json");

        // Get the request target/route
        RestHandlerContext ctx{response};
        ctx.setRequest(req);

        OLOG(info) << fmt("Query parametersn {}", ctx.query_params);

        switch (req.method()) {
            case http::verb::post: {
                if (ctx.route == "/api/parseString") {
                    response->result(http::status::ok);
                    ExporterJson exp{};
                    opt_query_param(ctx.query_params, exp, skipEmptyLists);
                    opt_query_param(ctx.query_params, exp, skipLocation);
                    opt_query_param(ctx.query_params, exp, skipId);
                    opt_query_param(ctx.query_params, exp, skipNullFields);
                    response->body() = exp
                                           .evalTop(sem::parseString(
                                               ctx.getArg<std::string>(
                                                   {"text"})))
                                           .dump();
                } else if (ctx.route == "/api/parseRoot") {
                    state->parseRoot(ctx.getArg<std::string>({"text"}));
                    response->result(http::status::ok);
                } else {
                    state->handlers.call(ctx.route, &ctx);
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
            std::make_shared<HttpSession>(std::move(socket), state)
                ->start();
        }
        accept();
    }
};

int main() {
    try {
        HttpState::Ptr state = std::make_shared<HttpState>();

        state->handlers.setFunction(
            "/api/standalone",
            &standalone_function,
            2,
            {arg("arg1"), arg("arg2"), opt_arg("opt1")});

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
