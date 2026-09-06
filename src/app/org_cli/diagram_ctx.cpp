#include "diagram_ctx.hpp"
#include "hstd/ext/graph/visual/visual_factory.hpp"
#include <google/protobuf/util/json_util.h>
#include <hstd/stdlib/JsonSerde.hpp>
#include <hstd/stdlib/MapSerde.hpp>
#include <hstd/stdlib/VariantSerde.hpp>

using DO = org::cli::CliOpts::DiagramOpts;

org::cli::CliOpts::DiagramOpts org::cli::DiagramCommandContext::parseCommand(
    argparse::ArgumentParser& diagram_cmd) {
    CliOpts::DiagramOpts opts;
    OPT_GET(diagram_cmd, opts, input, std::string);
    OPT_GET(diagram_cmd, opts, output, std::string);
    OPT_GET(diagram_cmd, opts, serial_read_log, std::string);
    OPT_GET(diagram_cmd, opts, layout_log, std::string);
    OPT_GET(diagram_cmd, opts, output_visual, std::string);
    OPT_GET(diagram_cmd, opts, output_visual_json, std::string);
    OPT_GET(diagram_cmd, opts, output_visual_debug, bool);
    OPT_GET_CONV(
        diagram_cmd, opts, output_visual_scale, boost::lexical_cast<double>(value));
    OPT_GET_ENUM(diagram_cmd, opts, format, CliOpts::ProtoFormat);
    OPT_GET_ENUM(diagram_cmd, opts, input_format, CliOpts::DiagramOpts::InputFormat);
    return opts;
}

void org::cli::DiagramCommandContext::getSubcommand(
    argparse::ArgumentParser& diagram_cmd) {
    diagram_cmd.add_argument(DO::input_opt).help("input protobuf diagram file");
    diagram_cmd.add_argument(DO::output_opt).help("output diagram file");
    diagram_cmd.add_argument(DO::serial_read_log_opt)
        .help("log for the serial data reader");
    diagram_cmd.add_argument(DO::output_visual_opt)
        .help("SVG with the diagram debug output");
    diagram_cmd.add_argument(DO::output_visual_scale_opt)
        .help("Scale the SVG by this factor");
    diagram_cmd.add_argument(DO::output_visual_json_opt)
        .help("JSON with the diagram debug output");
    diagram_cmd.add_argument(DO::output_visual_debug_opt)
        .help("Write SVG with additional debug information");
    diagram_cmd.add_argument(DO::layout_log_opt).help("log for the layout run");
    diagram_cmd.add_argument(DO::format_opt)
        .help("set diagram export format: " + describe_enum<CliOpts::ProtoFormat>());
    diagram_cmd.add_argument(DO::input_format_opt)
        .help(
            "set diagram import format: "
            + describe_enum<CliOpts::DiagramOpts::InputFormat>());
}

void org::cli::DiagramCommandContext::run(SharedContext& shared) {
    auto graph = std::make_shared<hstd::ext::graph::TrivialGraphBase>();
    hstd::ext::graph::VisualFactory factory{graph};

    hstd::ext::graph::proto::IGraph proto_layout;

    std::ifstream stream{cmd.input, std::ios::binary};
    if (!stream) { throw std::runtime_error("Failed to open input file: " + cmd.input); }

    switch (cmd.input_format) {
        case DO::InputFormat::Binary: {
            if (!proto_layout.ParseFromIstream(&stream)) {
                throw std::runtime_error("Failed to parse protobuf input: " + cmd.input);
            }
            break;
        }

        case DO::InputFormat::Json: {
            const std::string json{
                std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}};

            const auto status = google::protobuf::util::JsonStringToMessage(
                json, &proto_layout);

            if (!status.ok()) {
                throw std::runtime_error(
                    "Failed to parse protobuf JSON input: " + status.ToString());
            }
            break;
        }
    }

    if (cmd.serial_read_log) { factory.setTraceFile(cmd.serial_read_log.value()); }
    graph->readSerial(&proto_layout, &factory);
    if (cmd.layout_log) { factory.run->setTraceFile(cmd.layout_log.value()); }
    factory.run->runFullLayout();

    if (cmd.output_visual || cmd.output_visual_json) {
        auto visual = factory.run->getVisual();

        if (cmd.output_visual_scale) {
            for (auto& v : visual) { v *= cmd.output_visual_scale.value(); }
        }

        if (cmd.output_visual) {
            hstd::writeFile(
                cmd.output_visual.value(),
                hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
        }

        if (cmd.output_visual_json) {
            hstd::writeFile(
                cmd.output_visual_json.value(), hstd::to_json_eval(visual).dump(2));
        }
    }

    auto result = std::make_unique<hstd::ext::graph::proto::IGraph>();
    graph->writeSerial(result.get());
    shared.writeProtoResult(cmd.output, *result, cmd.format);
}
