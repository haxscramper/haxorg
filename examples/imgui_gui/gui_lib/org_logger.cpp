#include "org_logger.hpp"

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/format.hpp>
#include <boost/property_map/property_map.hpp>
#include <hstd/stdlib/Filesystem.hpp>

#include <boost/log/core.hpp>
#include <boost/log/sinks/sink.hpp>
#include <stack>
#include <mutex>
#include <hstd/stdlib/Opt.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>


BOOST_LOG_GLOBAL_LOGGER(
    global_logger,
    boost::log::sources::severity_logger_mt<
        boost::log::trivial::severity_level>)

using logger_type      = global_logger::logger_type;
using stream_type      = ::boost::log::basic_record_ostream<char>;
using record_type      = ::boost::log::record;
using record_pump_type = ::boost::log::aux::record_pump<logger_type>;

namespace logging  = boost::log;
namespace src      = boost::log::sources;
namespace expr     = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace sinks    = boost::log::sinks;

#define LOG_RECORD_FIELD "record"
#define LOG_SCOPE_DEPTH_FIELD "CommonDepth"
#define LOG_TIMESTAMP_FIELD "TimeStamp"

BOOST_LOG_ATTRIBUTE_KEYWORD(
    a_file,
    LOG_RECORD_FIELD,
    org_logging::log_record)

typedef boost::log::attributes::mutable_constant<
    org_logging::log_record,                 // attribute value type
    boost::shared_mutex,                     // synchronization primitive
    boost::unique_lock<boost::shared_mutex>, // exclusive lock type
    boost::shared_lock<boost::shared_mutex>  // shared lock type
    >
    log_record_mutable_constant;

using namespace org_logging;

namespace {
log_record_mutable_constant current_record{log_record{}};
}

BOOST_LOG_GLOBAL_LOGGER_INIT(
    global_logger,
    boost::log::sources::severity_logger_mt<LogLevel>) {
    static boost::log::sources::severity_logger_mt<
        boost::log::trivial::severity_level>
        logger;
    logger.add_attribute(
        LOG_TIMESTAMP_FIELD, boost::log::attributes::local_clock());

    logger.add_attribute(
        LOG_SCOPE_DEPTH_FIELD,
        boost::log::attributes::make_function([]() -> int {
            return log_scoped_depth_attr::instance().get_depth();
        }));

    boost::log::add_common_attributes();
    logger.add_attribute(LOG_RECORD_FIELD, current_record);
    return logger;
}

#define OLOG_INNER_DEBUG false

#define OLOG_MSG() LOG_IF(INFO, OLOG_INNER_DEBUG)

class log_sink_manager {
  public:
    static log_sink_manager& instance() {
        static log_sink_manager instance;
        return instance;
    }

    void push_sink(sink_ptr sink) {
        OLOG_MSG() << fmt(
            "Push shink {:p}, current sink stack is {}",
            (void*)sink.get(),
            sinks_.size());

        std::lock_guard<std::mutex> lock(m_);
        sinks_.push(sink);
        boost::log::core::get()->add_sink(sink);
    }

    void pop_sink() {
        std::lock_guard<std::mutex> lock(m_);
        if (!sinks_.empty()) {
            OLOG_MSG() << fmt(
                "Pop sink {:p}, current sink stack is {}",
                (void*)sinks_.top().get(),
                sinks_.size());
            sinks_.pop();
            sync_sinks();
        }
    }

    std::stack<sink_ptr> get_sinks() {
        std::lock_guard<std::mutex> lock(m_);
        return sinks_;
    }

    void set_sinks(const std::stack<sink_ptr>& new_sinks) {
        std::lock_guard<std::mutex> lock(m_);
        sinks_ = new_sinks;
        sync_sinks();
    }

  private:
    log_sink_manager() = default;

    void sync_sinks() {
        OLOG_MSG() << "Sync sinks";
        boost::log::core::get()->remove_all_sinks();
        std::stack<sink_ptr> temp = sinks_;
        std::stack<sink_ptr> reversed;

        while (!temp.empty()) {
            reversed.push(temp.top());
            temp.pop();
        }

        while (!reversed.empty()) {
            boost::log::core::get()->add_sink(reversed.top());
            reversed.pop();
        }
    }

    std::stack<sink_ptr> sinks_;
    std::mutex           m_;
};

org_logging::log_sink_scope::log_sink_scope()
    : previous_sinks_(log_sink_manager::instance().get_sinks()) {}

org_logging::log_sink_scope::~log_sink_scope() {
    if (!moved) {
        log_sink_manager::instance().set_sinks(previous_sinks_);
    }
}

log_sink_scope& log_sink_scope::drop_current_sinks() {
    clear_sink_backends();
    return *this;
}


void org_logging::clear_sink_backends() {
    log_sink_manager::instance().set_sinks({});
}

namespace {
void format_log_record_data(
    const boost::log::record_view&  rec,
    boost::log::formatting_ostream& strm,
    log_record::log_data const&     data) {
    auto ts = rec[LOG_TIMESTAMP_FIELD].extract<boost::posix_time::ptime>();
    auto global_depth  = rec[LOG_SCOPE_DEPTH_FIELD].extract<int>();
    std::string prefix = fmt(
        "{}{} {}",
        ts ? boost::posix_time::to_simple_string(*ts).substr(
                 11, 9 /*Extract HH:MM:SS*/)
                 + std::string{" "}
           : "",
        join(".", data.source_scope),
        Str{"  "}
            .repeated(
                data.depth ? data.depth.value()
                           : (global_depth ? *global_depth : 0))
            .toBase());

    strm << prefix;

    auto write_trail = [&]() {
        if (data.metadata) { strm << " " << data.metadata->dump(-1); }

        if (data.file) {
            strm << " " << fs::path{data.file}.filename() << ":"
                 << data.line;
        }
    };

    if (data.message.contains('\n')) {
        auto split = data.message.split('\n');
        strm << split.at(0);
        write_trail();
        for (auto const& line : split.at(slice(1, 1_B))) {
            strm << "\n";
            strm << Str{" "}.repeated(prefix.size());
            strm << line;
        }
    } else {
        strm << data.message;
        write_trail();
    }
}
} // namespace

sink_ptr org_logging::init_file_sink(Str const& log_file_name) {

    auto& logger = global_logger::get();

    typedef boost::log::sinks::synchronous_sink<
        boost::log::sinks::text_file_backend>
        sink_t;

    boost::shared_ptr<sink_t> sink{new sink_t(
        boost::log::keywords::file_name     = log_file_name,
        boost::log::keywords::rotation_size = 10 * 1024 * 1024,
        boost::log::keywords::open_mode = (std::ios_base::out | std::ios_base::trunc),
        boost::log::keywords::auto_flush = true //
        )};

    sink->set_formatter([](const boost::log::record_view&  rec,
                           boost::log::formatting_ostream& strm) {
        auto ref = rec[LOG_RECORD_FIELD].extract<log_record>();
        LOGIC_ASSERTION_CHECK(!!ref, "Log record view missing data");
        format_log_record_data(rec, strm, ref->data);
    });

    return sink;
}

void org_logging::push_sink(sink_ptr const& sink) {
    log_sink_manager::instance().push_sink(sink);
}


logger_type& get_logger() { return global_logger::get(); }


org_logging::log_record& ::org_logging::log_record::message(
    int const& msg) {
    data.message += std::to_string(msg);
    return *this;
}

org_logging::log_record& ::org_logging::log_record::depth(int depth) {
    data.depth = depth;
    return *this;
}

log_record& log_record::source_scope(const Vec<Str>& scope) {
    data.source_scope = scope;
    return *this;
}

log_record& log_record::source_scope_add(const Str& scope) {
    data.source_scope.push_back(scope);
    return *this;
}

log_record& log_record::source_id(const Str& id) {
    data.source_id = id;
    return *this;
}

log_record& log_record::metadata(const json& id) {
    data.metadata = id;
    return *this;
}

log_record& log_record::metadata(const Str& field, const json& value) {
    if (!data.metadata.has_value()) {
        data.metadata = json::object();
    } else if (!data.metadata->is_object()) {
        throw std::domain_error(
            "Log record medata is already set, but it is not an object");
    } else {
        data.metadata.value()[field.toBase()] = value;
    }

    return *this;
}

log_record& log_record::maybe_space() {
    if (!data.message.empty() && data.message.back() != ' ') {
        data.message += " ";
    }
    return *this;
}

org_logging::log_record& ::org_logging::log_record::message(
    Str const& msg) {
    data.message += msg;
    return *this;
}

org_logging::log_record& ::org_logging::log_record::message(
    char const* msg) {
    data.message += Str{msg};
    return *this;
}

org_logging::log_record& ::org_logging::log_record::line(int l) {
    data.line = l;
    return *this;
}

org_logging::log_record& ::org_logging::log_record::file(char const* f) {
    data.file = f;
    return *this;
}

org_logging::log_record& ::org_logging::log_record::category(
    Str const& cat) {
    data.category = cat;
    return *this;
}

org_logging::log_record& ::org_logging::log_record::severity(
    severity_level l) {
    data.severity = l;
    return *this;
}

std::size_t log_record::log_data::hash() const {
    std::size_t result{0};
    hax_hash_combine(result, message);
    hax_hash_combine(result, line);
    if (file) { hax_hash_combine(result, std::string{file}); }
    hax_hash_combine(result, category);
    hax_hash_combine(result, severity);
    if (function) { hax_hash_combine(result, std::string{function}); }
    hax_hash_combine(result, depth);
    hax_hash_combine(result, source_scope);
    hax_hash_combine(result, source_id);
    hax_hash_combine(result, metadata);
    return result;
}

// log_record::log_data::log_data() {
//     get_logger().lock();
//     auto const&           attrs = get_logger().get_attributes();
//     boost::log::attribute attr  = attrs[LOG_SCOPE_DEPTH_FIELD];
//     // if (attr) {
//     //     auto res = attr.get_value().extract<int>();
//     //     if (res) { this->depth = *res; }
//     // }
//     get_logger().unlock();
// }

org_logging::log_record& ::org_logging::log_record::function(
    char const* func) {
    data.function = func;
    return *this;
}

namespace {
record_type start_log_record(boost::log::trivial::severity_level level) {
    return get_logger().open_record(
        ::boost::log::keywords::severity = level);
}

} // namespace

void org_logging::log_record::end() {
    // current record is global, but synced, and all record attributes are
    // evaluated when record is opened.
    current_record.set(*this);
    ::boost::log::record rec_var = start_log_record(
        static_cast<boost::log::trivial::severity_level>(data.severity));
    // if the record did not pass filtering, it will return empty, and
    // should not be submitted.
    if (!!rec_var) {
        logging::core::get()->push_record(std::move(rec_var));
    }
}


template <>
struct std::formatter<boost::log::attribute_name>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const boost::log::attribute_name& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.string(), ctx);
    }
};

template <>
struct std::formatter<boost::log::attribute_value>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const boost::log::attribute_value& p, FormatContext& ctx)
        const {
        return fmt_ctx(p.get_type().pretty_name(), ctx);
    }
};


sink_ptr org_logging::set_sink_filter(
    sink_ptr                      sink,
    Func<bool(const log_record&)> filter) {
    sink->set_filter([filter](const logging::attribute_value_set& attrs) {
        auto rec = attrs[LOG_RECORD_FIELD].extract<log_record>();

        LOGIC_ASSERTION_CHECK(
            !!rec,
            "Logging attribute record set does not have a 'record' field");

        if (!!rec) {
            try {
                return filter(*rec);
            } catch (...) {
                LOG(INFO) << "????";
                return true;
            }
        } else {
            return true;
        }
    });
    return sink;
}

bool ::org_logging::is_log_accepted(
    const Str&     category,
    severity_level level) {
    return true;
}

::org_logging::log_builder::~log_builder() {
    if (!is_released) {
        if (finalizer) {
            finalizer(*this);
        } else {
            rec.end();
        }
    }
}


Opt<sink_ptr> org_logging::get_last_sink() {
    auto const& stack = log_sink_manager::instance().get_sinks();
    if (stack.empty()) {
        return std::nullopt;
    } else {
        return stack.top();
    }
}
