#include "SemBaseApi.hpp"
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgParser.hpp>
#include <sem/SemConvert.hpp>
#include <exporters/ExporterJson.hpp>
#include <fstream>
#include <sem/perfetto_org.hpp>
#include <sem/SemOrgFormat.hpp>
#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>
#include <sem/SemOrgSerdeDeclarations.hpp>
#include <SemOrgProto.pb.h>

using namespace sem;


std::string sem::exportToJsonString(sem::SemId<sem::Org> const& node) {
    return to_string(ExporterJson{}.evalTop(node));
}

void sem::exportToJsonFile(sem::SemId<sem::Org> const& node, std::string path) {
    writeFile(fs::path{path}, exportToJsonString(node));
}

std::string sem::exportToYamlString(sem::SemId<sem::Org> const& node) {
    std::stringstream os;
    os << ExporterYaml{}.evalTop(node);
    return os.str();
}

void sem::exportToYamlFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path) {
    writeFile(fs::path{path}, exportToYamlString(node));
}


std::string sem::exportToTreeString(
    sem::SemId<sem::Org> const&   node,
    sem::OrgTreeExportOpts const& opts) {
    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::string result = os.toString(opts.withColor);
    return result;
}

void sem::exportToTreeFile(
    sem::SemId<sem::Org> const&   node,
    std::string                   path,
    sem::OrgTreeExportOpts const& opts) {

    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::ofstream file{path};
    file << os.toString(opts.withColor);
}

sem::SemId<sem::Document> sem::parseFile(
    std::string               file,
    const OrgParseParameters& opts) {
    return parseStringOpts(readFile(fs::path{file}), opts);
}

sem::SemId<sem::Document> sem::parseString(std::string text) {
    return parseStringOpts(text, OrgParseParameters{});
}

sem::SemId<sem::Document> sem::parseStringOpts(
    const std::string         text,
    OrgParseParameters const& opts) {
    LexerParams         p;
    SPtr<std::ofstream> fileTrace;
    if (opts.baseTokenTracePath) {
        fileTrace = std::make_shared<std::ofstream>(
            *opts.baseTokenTracePath);
    }
    p.traceStream            = fileTrace.get();
    OrgTokenGroup baseTokens = ::tokenize(text.data(), text.size(), p);
    OrgTokenGroup tokens;
    OrgTokenizer  tokenizer{&tokens};

    if (opts.tokenTracePath) {
        tokenizer.setTraceFile(*opts.tokenTracePath);
    }

    tokenizer.convert(baseTokens);
    Lexer<OrgTokenKind, OrgFill> lex{&tokens};

    OrgNodeGroup nodes{&tokens};
    OrgParser    parser{&nodes};
    if (opts.parseTracePath) { parser.setTraceFile(*opts.parseTracePath); }

    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};
    if (opts.semTracePath) { converter.setTraceFile(*opts.semTracePath); }

    return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

sem::SemId<sem::Document> sem::readProtobufFile(const std::string& file) {
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        proto_write_accessor<sem::SemId<sem::Org>>::for_ref(read_node));
    return read_node.as<sem::Document>();
}

void sem::exportToProtobufFile(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
}


std::string sem::formatToString(sem::SemId<sem::Org> arg) {
    return sem::Formatter::format(arg);
}
