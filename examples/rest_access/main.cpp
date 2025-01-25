#define NDEBUG 0
#define TRACY_ENABLE

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <string>
#include <thread>
#include <boost/log/trivial.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/stdlib/Map.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <functional>
#include <tuple>
#include <type_traits>
#include <cpptrace/cpptrace.hpp>
#include <boost/beast/websocket.hpp>
#include <tracy/Tracy.hpp>

namespace cpptrace {
BOOST_DESCRIBE_STRUCT(stacktrace, (), (frames));
BOOST_DESCRIBE_STRUCT(
    stacktrace_frame,
    (),
    (raw_address,
     object_address,
     line,
     column,
     filename,
     symbol,
     is_inline));
} // namespace cpptrace

namespace boost::beast::http {
BOOST_DESCRIBE_ENUM(
    status,
    unknown,
    continue_,
    switching_protocols,
    processing,
    early_hints,

    ok,
    created,
    accepted,
    non_authoritative_information,
    no_content,
    reset_content,
    partial_content,
    multi_status,
    already_reported,
    im_used,

    multiple_choices,
    moved_permanently,
    found,
    see_other,
    not_modified,
    use_proxy,
    temporary_redirect,
    permanent_redirect,

    bad_request,
    unauthorized,
    payment_required,
    forbidden,
    not_found,
    method_not_allowed,
    not_acceptable,
    proxy_authentication_required,
    request_timeout,
    conflict,
    gone,
    length_required,
    precondition_failed,
    payload_too_large,
    uri_too_long,
    unsupported_media_type,
    range_not_satisfiable,
    expectation_failed,
    i_am_a_teapot,
    misdirected_request,
    unprocessable_entity,
    locked,
    failed_dependency,
    too_early,
    upgrade_required,
    precondition_required,
    too_many_requests,
    request_header_fields_too_large,
    unavailable_for_legal_reasons,

    internal_server_error,
    not_implemented,
    bad_gateway,
    service_unavailable,
    gateway_timeout,
    http_version_not_supported,
    variant_also_negotiates,
    insufficient_storage,
    loop_detected,
    not_extended,
    network_authentication_required);
}


#define OLOG(lvl) BOOST_LOG_TRIVIAL(lvl)

namespace beast     = boost::beast;
namespace http      = beast::http;
namespace net       = boost::asio;
using tcp           = boost::asio::ip::tcp;
namespace websocket = beast::websocket;

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


template <typename T>
struct JsonSerde<cpptrace::nullable<T>> {
    static json to_json(cpptrace::nullable<T> const& it) {
        if (it.has_value()) {
            return JsonSerde<T>::to_json(it.value());
        } else {
            return json{};
        }
    }
    static cpptrace::nullable<T> from_json(json const& j) {
        if (j.is_null()) {
            return cpptrace::nullable<T>::null();
        } else {
            return JsonSerde<T>::from_json(j);
        }
    }
};

template <typename T>
struct JsonSerde<immer::vector<T>> {
    static json to_json(immer::vector<T> const& it) {
        auto result = json::array();
        for (auto const& i : it) {
            result.push_back(JsonSerde<T>::to_json(i));
        }

        return result;
    }
    static immer::vector<T> from_json(json const& j) {
        immer::vector<T> result;
        auto             tmp = result.transient();
        for (auto const& i : j) {
            tmp.push_back(JsonSerde<T>::from_json(i));
        }
        return tmp.persistent();
    }
};

template <>
struct JsonSerde<org::ImmReflFieldId> {
    static json to_json(org::ImmReflFieldId const& id) {
        return id.getName();
    }

    static org::ImmReflFieldId from_json(json const& j) {
        std::string j_name = j.get<std::string>();
        for (auto const& [id, name] : org::ImmReflFieldId::fieldNames) {
            if (name == j_name) { return id; }
        }

        LOGIC_ASSERTION_CHECK(
            false, "Cannot find refl field for name {}", j_name);
    }
};

template <>
struct JsonSerde<std::any> {
    static json     to_json(std::any const& id) { logic_todo_impl(); }
    static std::any from_json(json const& id) { logic_todo_impl(); }
};

template <>
struct JsonSerde<OrgSemKind> {
    static json       to_json(OrgSemKind const& id) { return fmt1(id); }
    static OrgSemKind from_json(json const& id) {
        return enum_serde<OrgSemKind>::from_string(id.get<std::string>())
            .value();
    }
};

template <typename Tag>
struct JsonSerde<ReflPathItem<Tag>> {
    using Item = ReflPathItem<Tag>;
    using Kind = typename Item::Kind;
    static json to_json(Item const it) {
        json res;
        it.visit([&]<typename Sub>(Sub const& sub) {
            res         = JsonSerde<Sub>::to_json(sub);
            res["kind"] = fmt1(it.getKind());
        });
        return res;
    }

    static Item from_json(json const& j) {
        switch (from_json_eval<Kind>(j["kind"])) {
            case Kind::Index:
                return Item::FromIndex(j["index"].get<int>());
            case Kind::Deref: return Item::FromDeref();
            case Kind::AnyKey: logic_todo_impl();
            case Kind::FieldName:
                return Item::FromFieldName(
                    from_json_eval<typename Tag::field_name_type>(
                        j["name"]));
        }
    }
};


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


template <typename C, typename R, typename... Args>
struct function_traits<R (C::*)(Args...)> {
    using class_type              = C;
    using return_type             = R;
    using args_tuple              = std::tuple<std::decay_t<Args>...>;
    static constexpr size_t arity = sizeof...(Args);
};

template <typename T, typename = void>
struct has_class_type : std::false_type {};

template <typename T>
struct has_class_type<T, std::void_t<typename T::class_type>>
    : std::true_type {};

template <typename T>
inline constexpr bool has_class_type_v = has_class_type<T>::value;

template <typename T, typename = void>
struct has_return_type : std::false_type {};

template <typename T>
struct has_return_type<T, std::void_t<typename T::return_type>>
    : std::true_type {};

template <typename T>
inline constexpr bool has_return_type_v = has_return_type<T>::value;

struct TypeSpec {
    std::string           name;
    std::vector<TypeSpec> params;
    std::string           getApiSchema() const {
        std::string res = name;
        if (!params.empty()) {
            res += "<";
            for (auto const& it : enumerator(params)) {
                if (!it.is_first()) { res += ", "; }
                res += it.value().getApiSchema();
            }
            res += ">";
        }
        return res;
    }
};

template <typename T>
struct TypeSpecProvider {
    static TypeSpec get() {
        return TypeSpec{.name = demangle(typeid(T).name())};
    }
};


#define __trivial_type_spec_provider(__type, __name)                      \
    template <>                                                           \
    struct TypeSpecProvider<__type> {                                     \
        static TypeSpec get() { return TypeSpec{.name = __name}; }        \
    };

__trivial_type_spec_provider(std::string, "string");
__trivial_type_spec_provider(int, "number");
__trivial_type_spec_provider(i8, "number");
__trivial_type_spec_provider(org::ImmUniqId, "ImmUniqId");
__trivial_type_spec_provider(json, "json");


struct ArgSpec {
    std::string   name;
    bool          optional     = false;
    Opt<TypeSpec> type         = std::nullopt;
    json          defaultValue = json{};

    json getApiSchema() const {
        json s    = json::object();
        s["name"] = name;
        if (type) { s["type"] = type.value().getApiSchema(); }
        if (optional) {
            s["optional"] = true;
            s["default"]  = defaultValue;
        }
        return s;
    }
};

template <typename Func>
std::vector<ArgSpec> add_type_specs(std::vector<ArgSpec> const& args) {
    using traits                = function_traits<Func>;
    using tuple                 = typename traits::args_tuple;
    std::vector<ArgSpec> result = args;

    auto add_type =
        [&result]<std::size_t I>(std::integral_constant<std::size_t, I>) {
            if (I < result.size()) {
                using arg_t    = std::tuple_element_t<I, tuple>;
                result[I].type = TypeSpecProvider<arg_t>::get();
            }
        };

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        (add_type(std::integral_constant<std::size_t, I>{}), ...);
    }(std::make_index_sequence<std::tuple_size_v<tuple>>{});

    return result;
}


ArgSpec arg(std::string const& name) { return ArgSpec{.name = name}; }
ArgSpec opt_arg(std::string const& name, json value = json{}) {
    return ArgSpec{
        .name         = name,
        .optional     = true,
        .defaultValue = value,
    };
}

void standalone_function(int arg1, int arg2, int opt1 = 123) {
    OLOG(info) << fmt(
        "Called standalone function {} {} {}", arg1, arg2, opt1);
}


struct HttpState : public SharedPtrApi<HttpState> {
    org::ImmAstContext::Ptr ctx;
    org::ImmAstVersion      root;
    bool                    exception_handler = false;

    void parseRoot(std::string const& text) {
        root = ctx->addRoot(sem::parseString(text));
    }

    HttpState() : ctx{org::ImmAstContext::init_start_context()} {}
};

struct ResponseWrap {
    struct Rest {
        std::shared_ptr<http::response<http::string_body>> response;
        DESC_FIELDS(Rest, (response));
    };

    struct Websocket {
        json response;
        DESC_FIELDS(Websocket, (response));
    };

    SUB_VARIANTS(Kind, Data, data, getKind, Rest, Websocket);
    Data data;
    DESC_FIELDS(ResponseWrap, (data));
};

struct RestHandlerContext {
    UnorderedMap<std::string, std::string> query_params;
    std::string                            route;
    json                                   query_body;
    HttpState::Ptr                         state;
    Opt<std::string>                       requestId;
    ResponseWrap                           response;


    DESC_FIELDS(
        RestHandlerContext,
        (query_params, response, route, query_body, state));

    RestHandlerContext(ResponseWrap response, HttpState::Ptr state)
        : response{response}, state{state} {}

    template <typename T>
    T getArg(ArgSpec const& arg) {
        LOGIC_ASSERTION_CHECK(
            arg.optional || query_body.contains(arg.name),
            "Missing non-optional argument {}",
            arg.name);

        if (arg.optional && !query_body.contains(arg.name)) {
            if (arg.defaultValue.is_null()) {
                return SerdeDefaultProvider<T>::get();
            } else {
                return JsonSerde<T>::from_json(arg.defaultValue);
            }
        } else {
            return JsonSerde<T>::from_json(query_body.at(arg.name));
        }
    }

    json getSelfJson() { return getArg<json>(ArgSpec{"self"}); }

    template <typename T>
    T getThis() {
        if constexpr (std::is_same_v<T, RestHandlerContext&>) {
            return *this;
        } else {
            return getArg<T>(ArgSpec{"self"});
        }
    }

    void setResponseBody(json const& text) {
        if (response.isRest()) {
            response.getRest().response->body() = text.dump();
        } else {
            response.getWebsocket().response["body"] = text;
        }
    }

    void setResponseError(json const& text) {
        if (response.isRest()) {
            response.getRest().response->body() = text.dump();
        } else {
            response.getWebsocket().response["error"] = text;
        }
    }


    void setResponseResult(boost::beast::http::status status) {
        if (response.isRest()) {
            response.getRest().response->result(status);
        } else {
            response.getWebsocket().response["status"] = fmt1(status);
        }
    }

    void finishResponse() {
        if (requestId) {
            response.getWebsocket().response["id"] = requestId.value();
        }
    }

    void setSocket(json const& query) {
        if (query.contains("query")) {
            auto const& q = query.at("query");
            for (auto const& [key, value] : q.items()) {
                LOGIC_ASSERTION_CHECK(
                    value.is_string(),
                    "'query' parameter for websocket request should be a "
                    "string:string map, but key {} is mapped to value {}, "
                    "which is not string",
                    key,
                    value.dump());
                query_params[key] = value.get<std::string>();
            }
        }

        if (query.contains("id")) {
            requestId = query.at("id").get<std::string>();
        }

        if (query.contains("body")) { query_body = query.at("body"); }
    }

    void setSocket(std::string_view body) { setSocket(json::parse(body)); }

    void setRequest(http::request<http::string_body> const& req) {
        setTarget(req.target());
        if (!req.body().empty()) { setQueryBody(req.body()); }
    }

    void setQueryBody(std::string_view body) {
        query_body = json::parse(body);
    }

    org::ImmUniqId getRoot() const {
        return state->root.getRootAdapter().uniq();
    }

    OrgSemKind getKind(org::ImmUniqId const& id) const {
        return state->ctx->adapt(id).getKind();
    }

    org::ImmUniqId getSubnodeAt(org::ImmUniqId const& id, int index)
        const {
        return state->ctx->adapt(id).at(index).uniq();
    }

    int getSize(org::ImmUniqId const& id) const {
        return state->ctx->adapt(id).size();
    }

    void setRootText(std::string const& t) { state->parseRoot(t); }
    void setRootFile(std::string const& t) { setRootText(readFile(t)); }
    void setExceptionHandler(bool handler) {
        state->exception_handler = handler;
    }

    json toJson(sem::SemId<sem::Org> id) {
        ExporterJson exp{};
        opt_query_param(query_params, exp, skipEmptyLists);
        opt_query_param(query_params, exp, skipLocation);
        opt_query_param(query_params, exp, skipId);
        opt_query_param(query_params, exp, skipNullFields);
        return exp.eval(id);
    }

    json getTreeJsonDeep(org::ImmUniqId const& id) {
        return toJson(org::sem_from_immer(id.id, *state->ctx));
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

    template <typename Func>
    void call_impl(Func const& invoke_impl, json const& failed_arg_parse) {
        if (failed_arg_parse.empty()) {
            if (state->exception_handler) {
                try {
                    invoke_impl();
                    setResponseResult(http::status::ok);
                } catch (cpptrace::exception& ex) {
                    setResponseBody(json::object({
                        {"what", ex.what()},
                        {"trace", to_json_eval(ex.trace())},
                    }));
                    setResponseResult(http::status::internal_server_error);
                } catch (std::exception& ex) {
                    setResponseBody(json::object({{"what", ex.what()}}));
                    setResponseResult(http::status::internal_server_error);
                }
            } else {
                invoke_impl();
                setResponseResult(http::status::ok);
            }
        } else {
            setResponseError(failed_arg_parse);
            setResponseResult(http::status::bad_request);
        }
    }
};

template <typename T>
struct refl_redirect {
    using target_type = T;
};


template <>
struct refl_redirect<RestHandlerContext> {
    using target_type = RestHandlerContext&;
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

template <typename Arg>
void place_argument(
    Arg&                        arg,
    int&                        idx,
    std::vector<ArgSpec> const& arg_specs,
    json&                       failed_arg_parse,
    RestHandlerContext*         ctx) {
    auto fmt_arg_message = [&]() -> std::string {
        auto const& name = arg_specs.at(idx).name;
        return fmt(
            "Failed to parse arg '{}' from JSON '{}'",
            name,
            ctx->query_body.contains(name) ? ctx->query_body.at(name)
                                           : json{});
    };
    try {
        arg = ctx->template getArg<std::decay_t<decltype(arg)>>(
            arg_specs.at(idx));
        ++idx;
    } catch (std::exception& ex) {
        failed_arg_parse.push_back(json::object(
            {{"arg", fmt_arg_message()}, {"what", ex.what()}}));
    }
}

template <typename Func, typename... Args>
auto make_handler_callback(Func f, std::vector<ArgSpec> const& arg_specs) {
    return [f, arg_specs](RestHandlerContext* ctx) {
        using traits      = function_traits<std::decay_t<Func>>;
        using args_tuple  = typename traits::args_tuple;
        using return_type = typename traits::return_type;

        // Build tuple of arguments
        args_tuple args;
        json       failed_arg_parse;

        std::apply(
            [&](auto&... tuple_args) {
                int idx = 0;
                (place_argument(
                     tuple_args, idx, arg_specs, failed_arg_parse, ctx),
                 ...);
            },
            args);

        auto invoke_impl = [&]() {
            if constexpr (std::is_void_v<return_type>) {
                call_with_tuple(f, args);
            } else {
                auto result = call_with_tuple(f, args);
                ctx->setResponseBody(
                    JsonSerde<return_type>::to_json(result));
            }
            ctx->setResponseResult(http::status::ok);
        };

        ctx->call_impl(invoke_impl, failed_arg_parse);
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
        using this_class  = typename refl_redirect<Class>::target_type;

        // Get instance
        auto instance = ctx->template getThis<this_class>();

        // Build tuple of arguments
        args_tuple args;
        json       failed_arg_parse;
        std::apply(
            [&](auto&... tuple_args) {
                int idx = 0;
                (place_argument(
                     tuple_args, idx, arg_specs, failed_arg_parse, ctx),
                 ...);
            },
            args);

        auto invoke_impl = [&]() {
            if constexpr (std::is_void_v<return_type>) {
                call_with_tuple(
                    [&instance, f](auto&&... args) {
                        if constexpr (std::is_pointer_v<
                                          decltype(instance)>) {
                            (instance->*f)(
                                std::forward<decltype(args)>(args)...);
                        } else {
                            (instance
                             .*f)(std::forward<decltype(args)>(args)...);
                        }
                    },
                    args);
            } else {
                // Call method and serialize result
                auto result = call_with_tuple(
                    [&instance, f](auto&&... args) {
                        if constexpr (std::is_pointer_v<
                                          decltype(instance)>) {
                            return (instance->*f)(
                                std::forward<decltype(args)>(args)...);
                        } else {
                            return (instance.*f)(
                                std::forward<decltype(args)>(args)...);
                        }
                    },
                    args);

                ctx->setResponseBody(
                    JsonSerde<return_type>::to_json(result));
            }
        };

        ctx->call_impl(invoke_impl, failed_arg_parse);
    };
}


// Handler implementation
struct HandlerImpl {
    std::function<void(RestHandlerContext*)> callback;
    std::vector<ArgSpec>                     args;
    std::string                              name;
    Opt<TypeSpec>                            self;
    Opt<TypeSpec>                            result;


    template <typename Func>
    static HandlerImpl init_function(
        std::string const&          name,
        Func                        f,
        std::vector<ArgSpec> const& args) {

        auto res = HandlerImpl{
            .callback = make_handler_callback(f, args),
            .args     = add_type_specs<Func>(args),
            .name     = name,
        };

        if constexpr (has_return_type_v<function_traits<Func>>) {
            res.result = TypeSpecProvider<
                typename function_traits<Func>::return_type>::get();
        }

        return res;
    }

    template <typename Class, typename Func>
    static HandlerImpl init_method(
        std::string const&          name,
        Func                        f,
        std::vector<ArgSpec> const& args) {
        auto res = HandlerImpl{
            .callback = make_method_handler_callback<Class>(f, args),
            .args     = add_type_specs<Func>(args),
            .name     = name,
            .self     = TypeSpecProvider<Class>::get(),
        };

        if constexpr (has_return_type_v<function_traits<Func>>) {
            res.result = TypeSpecProvider<
                typename function_traits<Func>::return_type>::get();
        }

        return res;
    }

    void call(RestHandlerContext* ctx) { callback(ctx); }

    json getApiSchema() const {
        json s          = json::object();
        s["name"]       = name;
        s["parameters"] = json::array();
        if (false && self) {
            s["parameters"].push_back(ArgSpec{
                .name = "self",
                .type = self.value(),
            }
                                          .getApiSchema());
        }

        if (result) { s["result"] = result.value().getApiSchema(); }

        for (auto const& arg : args) {
            s["parameters"].push_back(arg.getApiSchema());
        }
        return s;
    }
};


// Handler construction helpers
struct HandlerMapType : SharedPtrApi<HandlerMapType> {
    UnorderedMap<std::string, HandlerImpl> map;

  public:
    template <typename Func>
    void setFunction(
        std::string const&          endpoint,
        std::string const&          name,
        Func                        f,
        std::vector<ArgSpec> const& args) {
        map.emplace(endpoint, HandlerImpl::init_function(name, f, args));
    }

    template <typename Class, typename Func>
    void setMethod(
        std::string const&          endpoint,
        std::string const&          name,
        Func                        f,
        std::vector<ArgSpec> const& args) {
        map.emplace(
            endpoint, HandlerImpl::init_method<Class>(name, f, args));
    }

    void call(std::string const& target, RestHandlerContext* ctx) {
        if (map.contains(target)) {
            map.at(target).call(ctx);
        } else {
            ctx->setResponseResult(http::status::bad_request);
            ctx->setResponseError(
                fmt("No handler method defined for target '{}'\nquery "
                    "parameters: {}\nquery_body: {}",
                    target,
                    ctx->query_params,
                    ctx->query_body.dump(2)));
        }

        ctx->finishResponse();
    }

    json getApiSchema() {
        json s       = json::object();
        s["name"]    = "OrgService";
        s["methods"] = json::object();
        for (auto const& [key, handler] : map) {
            s["methods"][handler.name] = handler.getApiSchema();
        }

        return s;
    }
};

class WSSession : public SharedPtrApi<WSSession> {
    websocket::stream<beast::tcp_stream> ws;
    beast::flat_buffer                   buffer;
    HandlerMapType::Ptr                  handlers;
    net::io_context&                     ioc;
    HttpState::Ptr                       state;

  public:
    explicit WSSession(
        tcp::socket&&       socket,
        HandlerMapType::Ptr handler,
        net::io_context&    ioc,
        HttpState::Ptr      state)
        : ws(std::move(socket))
        , handlers(handler)
        , ioc(ioc)
        , state{state} {}

    void run() {
        net::dispatch(
            ws.get_executor(),
            beast::bind_front_handler(
                &WSSession::on_run, this->shared_from_this()));
    }

  private:
    void on_run() {
        ws.set_option(websocket::stream_base::timeout::suggested(
            beast::role_type::server));
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res) {
                res.set(
                    http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING));
            }));

        ws.async_accept(beast::bind_front_handler(
            &WSSession::on_accept, this->shared_from_this()));
    }

    void on_accept(beast::error_code ec) {
        if (ec) { return; }
        do_read();
    }

    void do_read() {
        ws.async_read(
            buffer,
            beast::bind_front_handler(
                &WSSession::on_read, this->shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        if (ec) {
            OLOG(error) << fmt(
                "Websocket read error: {} {}",
                ec.to_string(),
                ec.message());
        } else {
            ZoneNamed(ReadRequest, true);
            bool logging = false;

            auto request = json::parse(
                beast::buffers_to_string(buffer.data()));
            if (logging) {
                OLOG(info)
                    << fmt("Parsed WS request:\n{}", request.dump(2));
            }
            auto target = request["target"].get<std::string>();
            RestHandlerContext ctx{
                ResponseWrap{ResponseWrap::Websocket{}}, state};
            ctx.setSocket(request);
            if (logging) {
                OLOG(info)
                    << fmt("Processing request ID {}", ctx.requestId);
            }
            {
                ZoneNamed(CallRequest, true);
                handlers->call(target, &ctx);
            }

            {
                ZoneNamed(ConsumeBuffer, true);
                buffer.consume(buffer.size());
            }

            {
                ZoneNamed(WriteResponse, true);
                ws.async_write(
                    net::buffer(ctx.response.getWebsocket().response.dump(
                        -1,
                        ' ',
                        false,
                        nlohmann::ordered_json::error_handler_t::replace)),
                    beast::bind_front_handler(
                        &WSSession::on_write, this->shared_from_this()));
            }

            if (logging) { OLOG(info) << fmt("Request done"); }
        }
    }

    void on_write(beast::error_code ec, std::size_t bytes_transferred) {
        if (ec) { return; }
        do_read();
    }
};

class WSServer {
    net::io_context&    ioc;
    tcp::acceptor       acceptor;
    HandlerMapType::Ptr handlers;
    HttpState::Ptr      state;

  public:
    WSServer(
        net::io_context&    ioc,
        unsigned short      port,
        HttpState::Ptr      state,
        HandlerMapType::Ptr handler)
        : ioc(ioc)
        , acceptor(ioc, {net::ip::make_address("0.0.0.0"), port})
        , handlers(handler)
        , state{state} {
        OLOG(info) << "Created websocket server";
    }

    void run() { do_accept(); }

  private:
    void do_accept() {
        acceptor.async_accept(
            net::make_strand(ioc),
            beast::bind_front_handler(&WSServer::on_accept, this));
    }

    void on_accept(beast::error_code ec, tcp::socket socket) {
        if (ec) {
            OLOG(warning) << fmt(
                "Websocket connection accept failed: {}", ec.to_string());
        } else {
            OLOG(info) << "Accepted websocket connection";
            std::make_shared<WSSession>(
                std::move(socket), handlers, ioc, state)
                ->run();
        }
        do_accept();
    }
};

class HttpSession : public SharedPtrApi<HttpSession> {
    beast::tcp_stream                stream;
    beast::flat_buffer               buffer;
    http::request<http::string_body> req;
    std::shared_ptr<void>            res;
    HttpState::Ptr                   state;
    HandlerMapType::Ptr              handlers;

  public:
    explicit HttpSession(
        tcp::socket&&       socket,
        HttpState::Ptr      state,
        HandlerMapType::Ptr handlers)
        : stream(std::move(socket)), state{state}, handlers{handlers} {
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

        response->set(http::field::access_control_allow_origin, "*");
        response->set(
            http::field::access_control_allow_methods,
            "POST, GET, OPTIONS");
        response->set(
            http::field::access_control_allow_headers, "content-type");


        // Get the request target/route
        RestHandlerContext ctx{
            ResponseWrap{ResponseWrap::Rest{response}}, state};
        ctx.setRequest(req);

        OLOG(info) << fmt("HTTP Query parametersn {}", ctx.query_params);

        switch (req.method()) {
            case http::verb::post: {
                if (ctx.route == "/api/parseString") {
                    response->result(http::status::ok);
                    response->body() //
                        = ctx
                              .toJson(sem::parseString(
                                  ctx.getArg<std::string>({"text"})))
                              .dump();
                } else if (ctx.route == "/api/parseRoot") {
                    state->parseRoot(ctx.getArg<std::string>({"text"}));
                    response->result(http::status::ok);
                } else {
                    handlers->call(ctx.route, &ctx);
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
    net::io_context&    ioc;
    tcp::acceptor       acceptor;
    HttpState::Ptr      state;
    HandlerMapType::Ptr handlers;

  public:
    HttpServer(
        net::io_context&    ioc,
        unsigned short      port,
        HttpState::Ptr      state,
        HandlerMapType::Ptr handlers)
        : ioc{ioc}, acceptor{ioc}, state{state}, handlers{handlers} {
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
        OLOG(info) << "Accepted HTTP connection";
        acceptor.async_accept(
            net::make_strand(ioc),
            beast::bind_front_handler(
                &HttpServer::on_accept, shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket) {
        if (ec) {
            OLOG(warning) << fmt(
                "HTTP connection accept failed: {}", ec.to_string());
        } else {
            ZoneScoped;
            std::make_shared<HttpSession>(
                std::move(socket), state, handlers)
                ->start();
        }
        accept();
    }
};

struct Config {
    DECL_DESCRIBED_ENUM(Operation, WriteSchema, RunServer);
    Operation operation;
    Opt<Str>  schema_path;
    DESC_FIELDS(Config, (operation, schema_path));
};

int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::invalid_argument{
            "Org server expects one positional argument: json literal "
            "with parameters"};
    }

    OLOG(info) << fmt("argv[1] = '{}'", argv[1]);
    Config conf = from_json_eval<Config>(json::parse(argv[1]));


    { ZoneScoped; }
    try {
        HttpState::Ptr      state    = std::make_shared<HttpState>();
        HandlerMapType::Ptr handlers = std::make_shared<HandlerMapType>();

        handlers->setFunction(
            "/api/standalone",
            "standalone_function",
            &standalone_function,
            {arg("arg1"), arg("arg2"), opt_arg("opt1")});

#define _ctx_method(__method, ...)                                        \
    handlers->setMethod<RestHandlerContext>(                              \
        "/api/" #__method,                                                \
        #__method,                                                        \
        &RestHandlerContext::__method,                                    \
        {__VA_ARGS__});


        _ctx_method(getRoot);
        _ctx_method(getTreeJsonDeep, arg("target"));
        _ctx_method(setRootText, arg("text"));
        _ctx_method(setRootFile, arg("path"));
        _ctx_method(getKind, arg("id"));
        _ctx_method(getSubnodeAt, arg("id"), arg("index"));
        _ctx_method(getSize, arg("id"));
        _ctx_method(setExceptionHandler, arg("handler"));

        if (conf.operation == Config::Operation::WriteSchema) {
            writeFile(
                conf.schema_path->toBase(),
                fmt(R"(export const data = {} as const;)",
                    handlers->getApiSchema().dump(2)));
        } else {
            int const       http_port      = 8080;
            int const       websocket_port = 8089;
            int const       threads = std::thread::hardware_concurrency();
            net::io_context ioc{static_cast<int>(threads)};

            auto http_server = std::make_shared<HttpServer>(
                ioc, http_port, state, handlers);
            auto websocket_server = std::make_shared<WSServer>(
                ioc, websocket_port, state, handlers);

            http_server->run();
            websocket_server->run();

            std::vector<std::thread> v;
            v.reserve(threads - 1);
            for (auto i = threads - 1; i > 0; --i) {
                v.emplace_back([&ioc] { ioc.run(); });
            }

            ioc.run();
        }

        return EXIT_SUCCESS;
    } catch (const std::exception& e) {
        OLOG(error) << e.what();
        return EXIT_FAILURE;
    }
}
