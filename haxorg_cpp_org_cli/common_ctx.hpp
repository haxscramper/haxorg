#pragma once

#include <app/org_cli/cli_opts.hpp>
#include <app/org_cli/proto_to_xml.hpp>
#include <fstream>
#include <haxorg_cpp_org_lib/api/SemBaseApi.hpp>


hstd::ProtoXmlMapper make_proto_xml_mapper();


namespace org::cli {
struct ParseReports {
    std::string       formatted;
    hstd::ext::Report report;
};


struct SharedContext {
    CliOpts                                   opts;
    std::shared_ptr<org::parse::ParseContext> parseContext;
    std::ofstream                             diagnosticsFile;
    std::ostream*                             diagnosticsOut = &std::cerr;

    explicit SharedContext(CliOpts options);

    bool shouldProcessPath(std::string const& path) const;

#if ORG_BUILD_WITH_PROTOBUF
    void writeProtoJson(
        std::string const&               output_path,
        google::protobuf::Message const& result) const;

    void writeProtoBinary(
        std::string const&               output_path,
        google::protobuf::Message const& result) const {
        std::ofstream output{output_path, std::ios::binary};
        result.SerializeToOstream(&output);
    }

    void writeProtoXml(
        std::string const&               output_path,
        google::protobuf::Message const& result) const {
        auto          mapper = make_proto_xml_mapper();
        std::ofstream output{output_path};
        mapper.map(result).serialize(output);
    }

    void writeProtoResult(
        std::string const&               output_path,
        google::protobuf::Message const& result,
        CliOpts::ProtoFormat             format) const;
#endif
};
} // namespace org::cli

template <>
struct hstd::serde::proto_serde<orgproto::ParseReport, org::cli::ParseReports> {
    static void write(orgproto::ParseReport* out, org::cli::ParseReports const& in);
    static void read(orgproto::ParseReport const& in, org::cli::ParseReports* out);
};
