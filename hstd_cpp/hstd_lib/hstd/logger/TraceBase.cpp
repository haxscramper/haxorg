#include "hstd/stdlib/Debug.hpp"
#include <fstream>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/TraceBaseStructuredLog.hpp>
#include <hstd/stdlib/containers/VariantSerde.hpp>
#include <hstd/stdlib/formatting/specializations/SpanFormatter.hpp>
#include <hstd/stdlib/formatting/specializations/VariantFormatter.hpp>
#include <hstd/stdlib/formatting/specializations/VecFormatter.hpp>
#include <hstd/stdlib/serde/Json.hpp>
#include <hstd/stdlib/serde/JsonSerde.hpp>
#include <hstd/stdlib/strutils.hpp>

#if !ORG_BUILD_EMCC
#    include <cpptrace/cpptrace.hpp>
#endif

using namespace hstd;

SPtr<std::ostream> OperationsTracer::getTraceFile() { return stream; }

hstd::Opt<fs::path> OperationsTracer::getTraceFileDir() const {
    if (traceFile) {
        return traceFile->parent_path();
    } else {
        return std::nullopt;
    }
}

hstd::fs::path OperationsTracer::getAdjacentToTraceFile(Str const& suffix) const {
    auto outdir = getTraceFileDir();
    LOGIC_ASSERTION_CHECK(outdir.has_value(), "must be writing to file");
    auto result = outdir.value() / suffix.toBase();
    createDirectory(result.parent_path(), true, true);
    return result;
}

void OperationsTracer::writeToTraceFile(
    hstd::fs::path const& path,
    Str const&            text,
    bool                  with_message,
    char const*           function,
    int                   line,
    char const*           file) const {
    writeFile(path, text);
    if (with_message) {
        message(hstd::fmt("wrote debug file to {}", path), function, line, file);
    }
}

void OperationsTracer::writeAdjacentToTraceFile(
    Str const&  suffix,
    Str const&  text,
    bool        with_message,
    char const* function,
    int         line,
    char const* file) const {
    if (canTrace()) {
        auto result = getAdjacentToTraceFile(suffix);
        writeToTraceFile(result, text, with_message, function, line, file);
    }
}

void OperationsTracer::setTraceFile(SPtr<std::ostream> stream) {
    TraceState   = true;
    traceToFile  = true;
    this->stream = stream;
}

void OperationsTracer::setTraceFile(fs::path const& outfile, bool overwrite) {
    LOGIC_ASSERTION_CHECK(
        outfile.native().size() != 0, "Expected non-empty filename for the output");
    traceFile   = outfile;
    TraceState  = true;
    traceToFile = true;
    createDirectory(outfile.parent_path(), true, true);
    if (overwrite) {
        stream = std::make_shared<std::ofstream>(
            std::ofstream{outfile.native(), std::ios_base::out | std::ios_base::trunc});
    } else {
        stream = std::make_shared<std::ofstream>(
            std::ofstream{outfile.native(), std::ios_base::out | std::ios_base::app});
    }
    traceColored = false;
}

ColStream OperationsTracer::getStream() const {
    if (traceToBuffer) {
        auto os    = ColStream{};
        os.colored = traceColored;
        return os;
    } else if (traceToFile) {
        auto os     = ColStream{*stream};
        os.colored  = traceColored;
        os.buffered = false;
        return os;
    } else {
        auto os    = ColStream{std::cout};
        os.colored = traceColored;
        return os;
    }
}

void OperationsTracer::endStream(ColStream& stream) const {
    if (traceToBuffer) {
        stream << "\n";
        const_cast<OperationsTracer*>(this)->traceBuffer += stream.toString(traceColored);
    } else {
        (*stream.ostream) << std::endl;
    }
}

void OperationsTracer::message(
    std::string const& value,
    char const*        function,
    int                line,
    char const*        file) const {
    if (canTrace()) {
        message(
            OperationsMsg{
                .msg      = value,
                .file     = file,
                .function = function,
                .line     = line,
                .level    = activeLevel,
            });
    }
}

void OperationsTracer::message(OperationsMsg const& value) const {
    if (canTrace()) {
        auto os = getStream();
        if (traceStructured) {
            log::record::InstantEvent event;
            event.init_ids();
            event.init_location(value.function, value.line, value.file);
            event.args.message = value.msg;
            log::record::TraceEventState state{.scopes = log::record::ScopesState{}};
            for (auto const& s : activeScopes) {
                state.scopes->scopes.push_back(log::record::ScopeState{.name = s});
            }
            event.args.state = state;
            os << log::record::format_event_to_json(event).dump();
        } else {
            std::string prefix = fmt(
                "{0}{1}{2}{3} @{4}",
                /*0*/ Str{"  "}.repeated(value.level),
                /*1*/ value.file
                    ? fmt("{:_<24}", fs::path{value.file}.filename().native())
                    : "",
                /*2*/ value.line == 0 ? "" : fmt(":{:<4}", value.line),
                /*3*/ value.column == 0 ? "" : fmt(":{}", value.column),
                /*4*/ value.function ? fmt("{:_<24}", value.function) : "?");


            os << prefix;
            if (value.msg) {
                if (value.msg.value().find('\n') == -1) {
                    os << " " << value.msg.value();
                    if (value.metadata) { os << " " << value.metadata->dump(); }
                    if (!activeScopes.empty()) {
                        os << " ..[" << hstd::join("."_str_view, activeScopes) << "]";
                    }
                } else {
                    bool isFirst = true;
                    for (auto const& line : split(*value.msg, '\n')) {
                        if (isFirst) {
                            if (!value.metadata || value.metadata->is_null()) {
                                os << " " << line;
                            } else {
                                os << " "                              //
                                   << value.metadata->dump()           //
                                   << "\n"                             //
                                   << Str(" ").repeated(prefix.size()) //
                                   << " "                              //
                                   << line;

                                if (!activeScopes.empty()) {
                                    os << " ..[" << hstd::join("."_str_view, activeScopes)
                                       << "]";
                                }
                            }
                            isFirst = false;
                        } else {
                            os << "\n" << Str(" ").repeated(prefix.size()) << " " << line;
                        }
                    }
                }
            }
        }
        endStream(os);
    }
}

void OperationsTracer::stacktraceMessage() const {
#if !ORG_BUILD_EMCC
    auto trace = cpptrace::generate_trace();
    for (auto const& it : trace) {
        message(
            it.symbol,
            fmt("{}", it.raw_address).c_str(),
            it.line.value_or(-1),
            it.filename.c_str());
    }
#endif
}


void OperationsTracer::incLevel() const {
    LOGIC_ASSERTION_CHECK_FMT(0 <= activeLevel, "");
    ++activeLevel;
}
void OperationsTracer::decLevel() const {
    --activeLevel;
    LOGIC_ASSERTION_CHECK_FMT(0 <= activeLevel, "");
}

int OperationsTracer::getLevel() const { return activeLevel; }

void OperationsTracer::addScope(std::string const& scope) const {
    activeScopes.push_back(scope);
    scopeEnabled = scopeFilter.enabled(activeScopes);
}

void OperationsTracer::popScope(std::string const& scope) const {
    LOGIC_ASSERTION_CHECK(!activeScopes.empty(), "scope stack underflow");
    LOGIC_ASSERTION_CHECK_FMT(
        activeScopes.back() == scope,
        "scope stack mismatch: expected '{}', got '{}'",
        activeScopes.back(),
        scope);
    activeScopes.pop_back();
    scopeEnabled = scopeFilter.enabled(activeScopes);
}

std::vector<std::string> const& OperationsTracer::getScope() const {
    return activeScopes;
}

void OperationsTracer::setScopeFilters(ScopeFilter::List const& filters) {
    scopeFilter.setFilters(filters);
    scopeEnabled = scopeFilter.enabled(activeScopes);
}

void OperationsTracer::begin_scope_event(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) const {
    if (traceStructured) {
        auto                            os = getStream();
        log::record::DurationBeginEvent e;
        e.init_ids();
        e.init_location(function, line, file);
        e.args.message = value;
        os << log::record::format_event_to_json(e).dump();
        endStream(os);
    } else {
        if (value) { message(value.value(), function, line, file); }
        ++activeLevel;
    }
}

void OperationsTracer::end_scope_event(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) const {
    if (traceStructured) {
        auto                          os = getStream();
        log::record::DurationEndEvent e;
        e.init_ids();
        e.init_location(function, line, file);
        e.args.message = value;
        os << log::record::format_event_to_json(e).dump();
        endStream(os);
    } else {
        --activeLevel;
        if (value) { message(value.value(), function, line, file); }
    }
}

hstd::OperationsTracer::ScopeHandle OperationsTracer::begin_scope(
    Opt<std::string> const& value,
    Opt<std::string> const& scope_name,
    char const*             function,
    int                     line,
    char const*             file) const {

    ScopeHandle res{const_cast<OperationsTracer*>(this)};
    res.start(value, scope_name, function, line, file);
    return res;
}

finally_std OperationsTracer::scopeTrace(bool state) {
    bool initialTrace = TraceState;
    TraceState        = state;
    return finally_std{[initialTrace, this]() { TraceState = initialTrace; }};
}

void OperationsMsg::use_stacktrace_as_msg() {
#if !ORG_BUILD_EMCC
    this->msg = cpptrace::generate_trace().to_string(false);
#endif
}

void hstd::OperationsTracer::ScopeHandle::start(
    Opt<std::string> const& value,
    Opt<std::string> const& scope_name,
    char const*             function,
    int                     line,
    char const*             file) {
    this->scope_name = scope_name;
    if (scope_name) { tracer->addScope(*scope_name); }
    tracer->begin_scope_event(value, function, line, file);
}

void hstd::OperationsTracer::ScopeHandle::end(
    Opt<std::string> const& value,
    char const*             function,
    int                     line,
    char const*             file) {
    tracer->end_scope_event(value, function, line, file);
    if (scope_name) { tracer->popScope(*scope_name); }
    tracer = nullptr;
}

void OperationsTracer::ScopeFilter::setFilters(List const& filters) {
    patterns.clear();
    for (auto const& f : filters) {
        LOGIC_ASSERTION_CHECK(!f.empty(), "empty filter pattern");
        Pattern p;
        size_t  start = 0;
        if (f.front().isNegative()) {
            p.negated = true;
            p.body.push_back(
                FilterComponent{
                    FilterComponent::Positive{f.front().getNegative().segment}});
            start = 1;
        }

        for (size_t i = start; i < f.size(); ++i) {
            LOGIC_ASSERTION_CHECK(
                !f[i].isNegative(),
                "Negative component is only allowed as the first pattern element");
            p.body.push_back(f[i]);
        }
        patterns.push_back(std::move(p));
    }
}

static bool consumes_one(
    OperationsTracer::ScopeFilter::FilterComponent const& c,
    std::string const&                                    seg) {
    using SF = OperationsTracer::ScopeFilter;
    if (c.isPositive()) {
        return seg == c.getPositive().segment;
    } else {
        return c.isAny();
    }
}

bool OperationsTracer::ScopeFilter::matchBody(
    std::span<const FilterComponent> pat,
    std::span<const std::string>     segs) {
    size_t         i = 0, j = 0;
    std::ptrdiff_t star_i = -1, star_j = -1;
    while (j < segs.size()) {
        if (i < pat.size() && consumes_one(pat[i], segs[j])) {
            ++i;
            ++j;
        } else if (i < pat.size() && pat[i].isAnyVarargs()) {
            star_i = i;
            star_j = j;
            ++i;
        } else if (star_i != -1) {
            i = star_i + 1;
            j = ++star_j;
        } else {
            return false;
        }
    }
    while (i < pat.size() && pat[i].isAnyVarargs()) { ++i; }
    return i == pat.size();
}

OperationsTracer::ScopeFilter::Decision OperationsTracer::ScopeFilter::decide(
    std::span<const std::string> segs) const {
    Decision d = Decision::Show;
    for (auto const& p : patterns) {
        if (matchBody(p.body, segs)) { d = p.negated ? Decision::Show : Decision::Hide; }
    }
    return d;
}


bool OperationsTracer::ScopeFilter::enabled(std::vector<std::string> const& scope) const {
    return decide(scope) == Decision::Show;
}
