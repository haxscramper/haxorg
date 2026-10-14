#include <haxdex_read_code_cpp_common/demangle_json.hpp>

#include <hstd_cpp_lib/logger/logger.hpp>
#include <hstd_cpp_lib/stdlib/containers/Variant.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>
#include <llvm/Support/MD5.h>


NO_COVERAGE llvm::json::Value demangle_to_json(
    Node const*               node,
    BinarySymbolVisitContext& ctx,
    int                       depth,
    int                       max_depth) {
    llvm::json::Object result;
    if (node == nullptr) { return nullptr; }
    if (max_depth < depth) { return nullptr; }

    std::string Kind = std::string{boost::describe::enum_to_string(
        static_cast<KindProxy>(node->getKind()), "<none>")};

    result["NodeKind"] = Kind;

    auto should_skip = hstd::overloaded{
        [](std::string const& view) { return view.empty(); },
        [](std::string_view view) { return view.empty(); },
        [](llvm::json::Value const& value) {
            switch (value.kind()) {
                case llvm::json::Value::Kind::Array: return value.getAsArray()->empty();
                case llvm::json::Value::Kind::Null: return true;
                default: return false;
            }
        },
        [](auto const&) { return false; },
    };

    auto sub = hstd::overloaded{
        [&](std::string const& field, llvm::json::Value const& value) {
            if (!should_skip(value)) { result[field] = value; }
        },
        [&](std::string const& field, std::string_view value) {
            if (!should_skip(value)) {
                result[field] = std::string{value.begin(), value.end()};
            }
        },
        [&](std::string const& field, std::string value) {
            if (!should_skip(value)) { result[field] = value; }
        },
        [&](std::string const& field, Node const* value) {
            auto tmp = demangle_to_json(value, ctx, depth + 1, max_depth);
            if (!should_skip(tmp)) { result[field] = std::move(tmp); }
        },
        [&](std::string const& field, NodeArray const& value) {
            llvm::json::Array array;
            for (auto const& it : value) {
                auto tmp = demangle_to_json(it, ctx, depth + 1, max_depth);
                if (!should_skip(tmp)) { array.push_back(std::move(tmp)); }
            }
            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&](std::string const& field, Qualifiers const& value) {
            llvm::json::Array array;
            if (value & Qualifiers::QualConst) { array.push_back("QualConst"); }

            if (value & Qualifiers::QualVolatile) { array.push_back("QualVolatile"); }

            if (value & Qualifiers::QualRestrict) { array.push_back("QualRestrict"); }

            if (!array.empty()) { result[field] = std::move(array); }
        },
        [&](std::string const& field, FunctionRefQual const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, Node::Prec const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, TemplateParamKind const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const& field, SpecialSubKind const& value) {
            result[field] = hstd::fmt1(value);
        },
        [&](std::string const&                           field,
            llvm::itanium_demangle::ReferenceKind const& value) {
            result[field] = hstd::fmt1(value);
        },
    };

    auto sub_proxy = [&](std::string const&               field,
                         auto const&                      value,
                         std::optional<visit_meta> const& meta = std::nullopt) {
        sub(field, value);
    };

    visit_node_fields(node, sub_proxy);

    return result;
}
std::string getClangResourceDir() {
    std::array<char, 256> buffer;
    std::string           result;

    // Ask clang itself where its resource directory is
    std::unique_ptr<FILE, decltype(&pclose)> pipe(
        popen("clang -print-resource-dir 2>/dev/null", "r"), pclose);

    if (pipe) {
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        // Remove trailing newline
        if (!result.empty() && result.back() == '\n') { result.pop_back(); }
    }

    return result;
}
clang::tooling::CommandLineArguments dropReflectionPlugin(
    clang::tooling::CommandLineArguments const& Args,
    llvm::StringRef                             Filename,
    ReflectionCLI const&                        cli) {
    clang::tooling::CommandLineArguments filteredArgs;

    HSLOG_INFO("Running drop reflection plugin");

    auto push = [&](std::string const& value, int line = __builtin_LINE()) {
        if (false) {
            if (cli.verbose_log) { HSLOG_TRACE("+++ Adding {}", value); }
        }
        filteredArgs.push_back(value);
    };

    bool has_resource_dir = false;
    for (size_t i = 0; i < Args.size(); ++i) {
        auto drop = [&](int line = __builtin_LINE()) {
            if (cli.verbose_log) { HSLOG_TRACE("!!! Discarding {}", Args[i]); }
        };

        // Skip unwanted arguments
        if (Args[i] == "-Xclang" && (i + 1 < Args.size())
            && (Args[i + 1] == "-add-plugin" || Args[i + 1] == "refl-plugin"
                || Args[i + 1].starts_with("out=")
                || Args[i + 1] == "-plugin-arg-refl-plugin")) {

            i++;
            drop();
        } else if (Args[i].find("-fplugin=") != std::string::npos) {
            drop();
        } else if (Args[i].find("sarif") != std::string::npos) {
            drop();
        } else if (Args[i].starts_with("@") || Args[i].starts_with("-vectorize")) {
            drop();
        } else if (Args[i].starts_with("-W") && !Args[i].starts_with("-Wno")) {
            drop();
        } else if (
            (i + 3 < Args.size())                                           //
            && Args[i] == "-Xclang"                                         //
            && (Args[i + 1] == "-include-pch" || Args[i + 1] == "-include") //
            && Args[i + 2] == "-Xclang"                                     //
            && (Args[i + 3].ends_with("pch")
                || Args[i + 3].find("cmake_pch") != std::string::npos)) {
            drop();
            ++i;
            drop();
            ++i;
            drop();
            ++i;
            drop();
        } else if (Args[i].find("-resource-dir") != std::string::npos) {
            has_resource_dir = true;
            push(Args[i]);
        } else {
            push(Args[i]);
        }
    }

    if (!has_resource_dir) {
        std::string resourceDir = getClangResourceDir();
        if (!resourceDir.empty()) {
            push("-resource-dir");
            push(resourceDir);
        }
    }

    // TODO Redirect warnings and other diagnostics into a temporary
    // location Use serif output.
    push("-Wno-everything");
    if (cli.verbose_log) { push("-v"); }
    if (cli.reflection.toolchain_include) {
        push("-isystem");
        push(cli.reflection.toolchain_include.value());
    }
    /*
     * Clang with custom LLVM toolchain is able to find toolchain include
     * correctly and append it to the path, but with this separate tool the
     * order of includes is wrong. It puts `ToolchainInclude` first and
     * then there are duplicates of C++-specific include headers.
     *
     * The desired order is -- doing it the other way around triggers
     * explicit ordering guards in the cstddef.
     *
     * ```
     * llvm/include/c++/v1
     * llvm/include/x86_64-unknown-linux-gnu/c++/v1
     * llvm/lib/clang/17/include
     * ```
     *
     * The ordering above satisfies check from c++/v1/cstddef:43
     *
     * ```
     * #include <stddef.h>
     * #ifndef _LIBCPP_STDDEF_H
     * #   error <cstddef> tried including <stddef.h> but didn't find libc++'s <stddef.h> header. \
     * #endif
     * ```
     *
     * I have a high confidence that the whole approach of CLI argument
     * rewriting here is not correct and instead I need to convince the
     * reflection tool to actually construct the default stdinc++ path
     * correctly right away, but at the moment whatever I wrote also works.
     */
    if (cli.reflection.no_std_include) { push("-nostdinc++"); }
    // NOTE: The comment above was relevant when the custom standard
    // library was used in the build process. When the system-provided one
    // is used it does not seem to be required (on the contrary, removing
    // std include causes issues with `cstdddef`), but the message above
    // should stay there regardless.

    if (false) {
        HSLOG_TRACE("Filtered command line arguments");
        for (auto const& arg : filteredArgs) { HSLOG_TRACE("[ ] {}", arg); }

        HSLOG_TRACE(":: ");
        for (auto const& arg : filteredArgs) { HSLOG_TRACE(" {}", arg); }
        HSLOG_TRACE("");
    }

    return filteredArgs;
}


NO_COVERAGE llvm::MD5::MD5Result demangle_digest(Node const* node) {
    llvm::MD5 result;

    auto visit_field = hstd::overloaded{
        // clang-format off
        [&result](std::string_view value) { result.update(value); },
        [&result](std::string value) { result.update(value); },
        [&result](bool const& value) { result.update(value); },
        [&result](Qualifiers const& value) { result.update(value); },
        [&result](FunctionRefQual const& value) { result.update(value); },
        [&result](Node const* value) { result.update(demangle_digest(value)); },
        [&result](Node::Prec const& value) { result.update(static_cast<int>(value)); },
        [&result](TemplateParamKind const& value) { result.update(static_cast<int>(value)); },
        [&result](SpecialSubKind const& value) { result.update(static_cast<int>(value)); },
        [&result](llvm::itanium_demangle::ReferenceKind const& RK) { result.update(static_cast<int>(RK)); },
        // clang-format on
        [&result](NodeArray const& value) {
            for (auto const& it : value) { result.update(demangle_digest(it)); }
        },
    };

    auto sub = [&](std::string const&               field,
                   auto const&                      value,
                   std::optional<visit_meta> const& meta = std::nullopt) {
        result.update(field);
        visit_field(value);
    };

    visit_node_fields(node, sub);

    return result.result();
}

static std::vector<std::string> CompiledFileExtensions = {
    ".cpp",
    ".h",
    ".hpp",
    ".cc",
    ".cxx",
    ".c",
    ".C",
    ".java",
    ".js",
    ".ts",
    ".go",
    ".py",
    ".rs",
    ".swift",
    ".m",
    ".mm",
};


int findSymbolNamePosition(std::string const& input) {
    int pos = input.find(':');
    while (pos != std::string::npos) {
        for (const auto& ext : CompiledFileExtensions) {
            int extPos = input.rfind(ext, pos);
            if (extPos != std::string::npos && extPos + ext.length() == pos) {
                return pos + 1;
            }
        }
        pos = input.find(':', pos + 1);
    }

    return 0;
}


llvm::json::Value demangle_to_json(
    std::string const&        name,
    BinarySymbolVisitContext& ctx,
    int                       depth,
    int                       max_depth) {
    int         offset = findSymbolNamePosition(name);
    std::string name2  = name.substr(offset);
    Demangler   Parser(name2.data(), name2.data() + name2.length());
    Node*       AST = Parser.parse();
    return demangle_to_json(AST, ctx, depth, max_depth);
}
