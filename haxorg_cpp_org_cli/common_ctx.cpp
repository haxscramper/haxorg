#include "src/haxorg/serde/SemOrgProto.pb.h"
#include <app/org_cli/common_ctx.hpp>
#include <google/protobuf/util/json_util.h>
#include <haxorg_cpp_org_lib/sem/perfetto_org.hpp>
#include <hstd_cpp_lib/ext/error_write_proto.hpp>
#include <hstd_cpp_lib/ext/logger.hpp>


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

#if ORG_BUILD_WITH_PROTOBUF
void org::cli::SharedContext::writeProtoJson(
    std::string const&               output_path,
    google::protobuf::Message const& result) const {
    std::string jsonOutput;

    google::protobuf::json::PrintOptions options;
    options.add_whitespace = true;

    auto status = google::protobuf::util::MessageToJsonString(
        result, &jsonOutput, options);

    hstd::writeFile(output_path, jsonOutput, true);
}

void org::cli::SharedContext::writeProtoResult(
    std::string const&               output_path,
    google::protobuf::Message const& result,
    CliOpts::ProtoFormat             format) const {
    __perf_trace("cli", "write proto result");
    switch (format) {
        case CliOpts::ProtoFormat::Json: writeProtoJson(output_path, result); break;
        case CliOpts::ProtoFormat::Binary: writeProtoBinary(output_path, result); break;
        case CliOpts::ProtoFormat::Xml: writeProtoXml(output_path, result); break;
    }
}

#endif
