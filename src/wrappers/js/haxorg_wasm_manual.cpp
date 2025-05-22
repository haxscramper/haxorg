#include "haxorg_wasm_manual.hpp"

#ifdef ORG_USE_PERFETTO
#    include <haxorg/sem/perfetto_org.hpp>
#    include <hstd/ext/perfetto_aux_impl_template.hpp>

namespace perfetto {

// This simply allows building the client library and using those parts of
// it that do not depend on anything in the platform.

// static
Platform* Platform::GetDefaultPlatform() { return nullptr; }
} // namespace perfetto

#endif


namespace {
template <typename T>
org::sem::SemId<T> cast_impl(
    org::sem::SemId<org::sem::Org> const& node,
    std::string const&                    name) {
    auto result = node.as<T>();
    // Transfer ownership to JavaScript by incrementing the reference count
    // This prevents the memory leak warning as embind will manage the
    // lifetime
    if (result.value) {
        // emscripten::val::global("Object")["getPrototypeOf"](
        //     emscripten::val::module_property(
        //         name.c_str())["prototype"])["__smartPtr"]
        //     .call<void>("register", result.value);
    }
    return result;
}
} // namespace

#ifdef ORG_USE_PERFETTO
struct TracingSessionHandle {
    std::unique_ptr<perfetto::TracingSession> session;

    TracingSessionHandle() {}

    void start() {
        session = StartProcessTracing("Perfetto WASM session");
        LOGIC_ASSERTION_CHECK(session.get() != nullptr, "");
    }

    std::string finish() {
        perfetto::TrackEvent::Flush();
        session->StopBlocking();
        std::vector<char> trace_data(session->ReadTraceBlocking());
        std::stringstream ss;
        ss.write(&trace_data[0], std::streamsize(trace_data.size()));
        return ss.str();
    }
};
#endif


void haxorg_wasm_manual_register() {
#define __cast(__Kind)                                                    \
    emscripten::function(                                                 \
        "cast_to_" #__Kind,                                               \
        +[](org::sem::SemId<org::sem::Org> const& node)                   \
            -> org::sem::SemId<org::sem::__Kind> {                        \
            return cast_impl<org::sem::__Kind>(node, #__Kind);            \
        });

    EACH_SEM_ORG_KIND(__cast)

#undef __cast

#ifdef ORG_USE_PERFETTO
    emscripten::class_<TracingSessionHandle>("TracingSessionHandle")
        .constructor()
        .function("start", &TracingSessionHandle::start)
        .function("end", &TracingSessionHandle::finish);
#endif

    emscripten::class_<hstd::Str>("Str")
        .function(
            "size",
            static_cast<int (hstd::Str::*)() const>(&hstd::Str::size))
        .function(
            "empty",
            static_cast<bool (hstd::Str::*)() const>(&hstd::Str::empty))
        .function(
            "clear", static_cast<void (hstd::Str::*)()>(&hstd::Str::clear))
        .function(
            "substr",
            static_cast<hstd::Str (hstd::Str::*)(int, int) const>(
                &hstd::Str::substr))
        .function(
            "at",
            static_cast<char (hstd::Str::*)(int) const>(&hstd::Str::at))
        .function(
            "toString", +[](const hstd::Str& self) -> std::string {
                return static_cast<const std::string&>(self);
            });
}
