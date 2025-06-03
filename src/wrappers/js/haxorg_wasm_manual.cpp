#include "haxorg_wasm_manual.hpp"

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

    emscripten::function(
        "setOrgDirectoryFileReaderCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->getParsedNode = [value](std::string const& path)
                -> org::sem::SemId<org::sem::Org> {
                // _dbg(path);
                emscripten::val file_content = value(path);
                return org::parseString(file_content.as<std::string>());
            };
        });

    emscripten::function(
        "setOrgDirectoryIsSymlinkCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->isSymlinkImpl =
                [value](std::string const& path) -> bool {
                bool result = value(path).as<bool>();
                // _dfmt(path, result);
                return result;
            };
        });

    emscripten::function(
        "setOrgDirectoryIsRegularFileCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->isRegularFileImpl =
                [value](std::string const& path) -> bool {
                bool result = value(path).as<bool>();
                // _dfmt(path, result);
                return result;
            };
        });

    emscripten::function(
        "setOrgDirectoryIsDirectoryCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->isDirectoryImpl =
                [value](std::string const& path) -> bool {
                bool result = value(path).as<bool>();
                // _dfmt(path, result);
                return result;
            };
        });

    emscripten::function(
        "setOrgDirectoryResolveSymlinkCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->resolveSymlinkImpl =
                [value](std::string const& path) -> std::string {
                std::string result = value(path).as<std::string>();
                // _dfmt(path, result);
                return result;
            };
        });

    emscripten::function(
        "setOrgDirectoryGetDirectoryEntriesCallback",
        +[](std::shared_ptr<org::OrgDirectoryParseParameters> const&
                                   config,
            emscripten::val const& value) {
            config->getDirectoryEntriesImpl =
                [value](
                    std::string const& path) -> std::vector<std::string> {
                emscripten::val          result = value(path);
                std::vector<std::string> vec;
                unsigned int length = result["length"].as<unsigned int>();
                for (unsigned int i = 0; i < length; ++i) {
                    vec.push_back(result[i].as<std::string>());
                }
                return vec;
            };
        });

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
