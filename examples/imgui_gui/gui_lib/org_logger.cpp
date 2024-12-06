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

#include <boost/log/core.hpp>
#include <boost/log/sinks/sink.hpp>
#include <stack>
#include <mutex>
#include <hstd/stdlib/Opt.hpp>

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

BOOST_LOG_ATTRIBUTE_KEYWORD(a_file, "record", org_logging::log_record)

using namespace org_logging;

#define OLOG_INNER_DEBUG true

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
    log_sink_manager::instance().set_sinks(previous_sinks_);
}

log_sink_scope& log_sink_scope::drop_current_sinks() {
    clear_sink_backends();
    return *this;
}


void org_logging::clear_sink_backends() {
    log_sink_manager::instance().set_sinks({});
}

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
        log_record::log_data const& data = boost::log::extract<log_record>(
                                               "record", rec)
                                               ->data;

        strm << join(".", data.source_scope);
        strm << " ";
        strm << Str{"  "}.repeated(data.depth).toBase();
        strm << data.message;
    });

    return sink;
}

void org_logging::push_sink(sink_ptr const& sink) {
    log_sink_manager::instance().push_sink(sink);
}

BOOST_LOG_GLOBAL_LOGGER_INIT(
    global_logger,
    boost::log::sources::severity_logger_mt<LogLevel>) {
    static boost::log::sources::severity_logger_mt<
        boost::log::trivial::severity_level>
        logger;
    logger.add_attribute(
        "TimeStamp", boost::log::attributes::local_clock());
    boost::log::add_common_attributes();
    return logger;
}

logger_type& get_logger() { return global_logger::get(); }


org_logging::log_record& ::org_logging::log_record::message(
    int const& msg) {
    data.message += std::to_string(msg);
    return *this;
}

org_logging::log_record& ::org_logging::log_record::depth(int depth) {
    data.depth += depth;
    return *this;
}

log_record& log_record::source_scope(const Vec<Str>& scope) {
    data.source_scope = scope;
    return *this;
}

log_record& log_record::source_id(const Str& id) {
    data.source_id = id;
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
    data.level = l;
    return *this;
}

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
    ::boost::log::record rec_var = start_log_record(
        static_cast<boost::log::trivial::severity_level>(data.level));
    auto pump = ::boost::log::aux::make_record_pump(get_logger(), rec_var);
    pump.stream() << logging::add_value("record", *this);
}

bool ::org_logging::is_log_accepted(
    const Str&     category,
    severity_level level) {
    return true;
}
