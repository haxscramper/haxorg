#include "diagram_ctx.hpp"
#include <google/protobuf/util/json_util.h>
#include <hstd_cpp_lib/ext/graph/visual/graph_diagram.hpp>
#include <hstd_cpp_lib/ext/graph/visual/visual_factory.hpp>
#include <hstd_cpp_lib/stdlib/JsonSerde.hpp>
#include <hstd_cpp_lib/stdlib/MapSerde.hpp>
#include <hstd_cpp_lib/stdlib/VariantSerde.hpp>


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
    OPT_GET(diagram_cmd, opts, diagram_intermediate_dump, std::string);
    OPT_GET_CONV(diagram_cmd, opts, output_visual_debug, value == "true");
    OPT_GET_CONV(diagram_cmd, opts, use_diagram_input, value == "true");
    OPT_GET_CONV(diagram_cmd, opts, use_diagram_output, value == "true");
    OPT_GET_CONV(
        diagram_cmd, opts, output_visual_scale, boost::lexical_cast<double>(value));
    OPT_GET_ENUM(diagram_cmd, opts, format, CliOpts::ProtoFormat);
    OPT_GET_ENUM(diagram_cmd, opts, input_format, hstd::serde::ProtobufFileFormat);
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
    diagram_cmd.add_argument(DO::diagram_intermediate_dump_opt)
        .help(
            "If --use-diagram-input was enabled, dump the intermediate graph to the file "
            "in JSON form. This is a debug option");
    diagram_cmd.add_argument(DO::use_diagram_input_opt)
        .help("Use simplified diagram syntax defined in DiaCluster for the input file");
    diagram_cmd.add_argument(DO::use_diagram_output_opt)
        .help("Write final result in simplified diagram syntax");
    diagram_cmd.add_argument(DO::layout_log_opt).help("log for the layout run");
    diagram_cmd.add_argument(DO::format_opt)
        .help("set diagram export format: " + describe_enum<CliOpts::ProtoFormat>());
    diagram_cmd.add_argument(DO::input_format_opt)
        .help(
            "set diagram import format: "
            + describe_enum<hstd::serde::ProtobufFileFormat>());
}

void org::cli::DiagramCommandContext::run(SharedContext& shared) {
    auto graph = std::make_shared<hstd::ext::graph::TrivialGraphBase>();
    hstd::ext::graph::VisualFactory factory{graph};

    hstd::ext::graph::proto::IGraph proto_layout;

    if (cmd.use_diagram_input) {
        auto diagram = hstd::serde::read_message_from_file<
            hstd::ext::graph::diagram::proto::DiaCluster>(cmd.input, cmd.input_format);
        proto_layout = hstd::ext::graph::diagram::diaClusterToGraph(diagram);

        if (cmd.diagram_intermediate_dump) {
            shared.writeProtoJson(cmd.diagram_intermediate_dump.value(), proto_layout);
        }

    } else {
        proto_layout = hstd::serde::read_message_from_file<
            hstd::ext::graph::proto::IGraph>(cmd.input, cmd.input_format);
    }

    if (cmd.serial_read_log) { factory.setTraceFile(cmd.serial_read_log.value()); }
    graph->readSerial(&proto_layout, &factory);
    if (cmd.layout_log) { factory.run->setTraceFile(cmd.layout_log.value()); }
    factory.run->runFullLayout();

    if (cmd.output_visual || cmd.output_visual_json) {
        auto visual = factory.run->getVisual();

        if (cmd.output_visual_json) {
            hstd::writeFile(
                cmd.output_visual_json.value(), hstd::to_json_eval(visual).dump(2));
        }

        if (cmd.output_visual_scale) {
            for (auto& v : visual) { v *= cmd.output_visual_scale.value(); }
        }

        if (cmd.output_visual) {
            hstd::writeFile(
                cmd.output_visual.value(),
                hstd::ext::visual::toSvg(visual, /*debug=*/false).to_string());
        }
    }

    auto result = std::make_unique<hstd::ext::graph::proto::IGraph>();
    graph->writeSerial(result.get());

    if (cmd.use_diagram_output) {
        auto simplified_result = hstd::ext::graph::diagram::graphToDiaCluster(*result);
        shared.writeProtoResult(cmd.output, simplified_result, cmd.format);
    } else {
        shared.writeProtoResult(cmd.output, *result, cmd.format);
    }
}
