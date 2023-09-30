#include "pyhaxorg_manual_impl.hpp"

#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>

#include <memory>

QTextStream qcout;

OrgExporterJson::OrgExporterJson() {
    impl = std::make_shared<ExporterJson>();
}

QString OrgExporterJson::exportToString() { return to_string(result); }

void OrgExporterJson::exportToFile(QString path) {
    writeFile(QFileInfo(path), exportToString());
}

void OrgExporterJson::visitNode(sem::SemId node) {
    result = impl->visitTop(node);
}

OrgExporterYaml::OrgExporterYaml() {
    impl = std::make_shared<ExporterYaml>();
}

QString OrgExporterYaml::exportToString() { return to_string(result); }

void OrgExporterYaml::exportToFile(QString path) {
    writeFile(QFileInfo(path), exportToString());
}

void OrgExporterYaml::visitNode(sem::SemId node) {
    result = impl->visitTop(node);
}

OrgExporterTree::OrgExporterTree() {
    impl = std::make_shared<ExporterTree>(os);
}

QString OrgExporterTree::toString(sem::SemId node, ExporterTreeOpts opts) {
    QString     buf;
    QTextStream os{&buf};
    stream(os, node, opts);
}

void OrgExporterTree::toFile(
    sem::SemId       node,
    QString          path,
    ExporterTreeOpts opts) {
    auto ctx = openFileOrStream(QFileInfo(path), true);
    stream(ctx->stream, node, opts);
}

void OrgExporterTree::stream(
    QTextStream&     stream,
    sem::SemId       node,
    ExporterTreeOpts opts) {
    os                         = ColStream{stream};
    os.colored                 = opts.withColor;
    impl->conf.withLineCol     = opts.withLineCol;
    impl->conf.withOriginalId  = opts.withOriginalId;
    impl->conf.skipEmptyFields = opts.skipEmptyFields;
    impl->conf.startLevel      = opts.startLevel;
    impl->visitTop(node);
}

void OrgContext::run() {
    tokens.base = source.data();
    info        = LineColInfo{source};
    parser      = OrgParser::initImpl(&nodes, false);
    tokenizer   = OrgTokenizer::initImpl(&tokens, false);
    str         = std::make_shared<PosStr>(source);

    tokenizer->reserve(source.size() / 3);
    parser->reserve(source.size() / 3);

    initLocationResolvers();

    tokenizer->lexGlobal(*str);
    parser->parseFull(lex);
    node = converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

std::vector<PySemId> PySemId::getSubnodeRange(
    pybind11::slice slice) {

    size_t start;
    size_t stop;
    size_t step;
    size_t slicelength;

    Vec<sem::SemId> const& data = id->subnodes;
    if (!slice.compute(data.size(), &start, &stop, &step, &slicelength)) {
        throw py::error_already_set();
    }

    std::vector<PySemId> result{slicelength};
    for (size_t i = 0; i < slicelength; ++i) {
        result[i] = PySemId(data[start]);
        start += step;
    }
    return result;
}

PySemId PySemId::getSingleSubnode(int index) {
    return PySemId(id->at(index));
}
