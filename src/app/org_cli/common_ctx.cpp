#include <app/org_cli/common_ctx.hpp>
#include <hstd/ext/error_write_proto.hpp>
#include <hstd/ext/logger.hpp>

org::cli::SharedContext::SharedContext(CliOpts options)
    : opts{std::move(options)}
    , parseContext{std::make_shared<org::parse::ParseContext>()} {
    if (opts.diagnosticsFile) {
        auto const path = hstd::fs::path{opts.diagnosticsFile.value()};
        std::filesystem::create_directories(path.parent_path());

        diagnosticsFile.open(path, std::ios::out | std::ios::trunc);
        if (!diagnosticsFile.is_open()) {
            throw std::runtime_error(
                hstd::fmt("failed to open diagnostics file {}", path));
        }

        HSLOG_INFO("using diag file {}", path);
        diagnosticsOut = &diagnosticsFile;
    }

    *diagnosticsOut << "" << std::endl;
}

bool org::cli::SharedContext::shouldProcessPath(std::string const& path) const {
    // TODO: make this configurable
    hstd::fs::path filesystemPath{path};

    if (path.contains(".git") || path.contains(".trunk")) {
        return false;
    } else if (path.ends_with(".org")) {
        return true;
    } else {
        return hstd::fs::is_directory(filesystemPath);
    }
}

void hstd::serde::proto_serde<orgproto::ParseReport, org::cli::ParseReports>::write(
    orgproto::ParseReport*        out,
    org::cli::ParseReports const& in) {
    out->set_formatted(in.formatted);
    hstd::serde::write_serde(out->mutable_report(), in.report);
}
void hstd::serde::proto_serde<orgproto::ParseReport, org::cli::ParseReports>::read(
    orgproto::ParseReport const& in,
    org::cli::ParseReports*      out) {
    out->formatted = in.formatted();
    hstd::serde::read_serde(in.report(), &out->report);
}
