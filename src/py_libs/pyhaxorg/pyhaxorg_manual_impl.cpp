#include "pyhaxorg_manual_impl.hpp"

#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>

#include <memory>

ExporterJson::ExporterJson() {
    impl = std::make_shared<sem::ExporterJson>();
}

QString ExporterJson::exportToString() { return to_string(result); }

void ExporterJson::exportToFile(QString const& path) {
    writeFile(QFileInfo(path), exportToString());
}

void ExporterJson::visitNode(sem::SemId node) {
    result = impl->visitTop(node);
}

ExporterYaml::ExporterYaml() {
    impl = std::make_shared<sem::ExporterYaml>();
}

QString ExporterYaml::exportToString() { return to_string(result); }

void ExporterYaml::exportToFile(QString const& path) {
    writeFile(QFileInfo(path), exportToString());
}

void ExporterYaml::visitNode(sem::SemId node) {
    result = impl->visitTop(node);
}

ExporterTree::ExporterTree() { impl = std::make_shared<ExporterTree>(); }

QString ExporterTree::toString(sem::SemId node, ExporterTreeOpts opts) {
    QString     buf;
    QTextStream os{&buf};
    stream(os, node, opts);
}

void ExporterTree::toFile(
    sem::SemId       node,
    QString          path,
    ExporterTreeOpts opts) {
    auto ctx = openFileOrStream(QFileInfo(path), true);
    stream(ctx->stream, node, opts);
}

void ExporterTree::stream(
    QTextStream&     stream,
    sem::SemId       node,
    ExporterTreeOpts opts) {
    ColStream os{&stream};
    os.colored                 = opts.withColor;
    impl->conf.withLineCol     = opts.withLineCol;
    impl->conf.withOriginalId  = opts.withOriginalId;
    impl->conf.skipEmptyFields = opts.skipEmptyFields;
    impl->conf.startLevel      = opts.startLevel;
    impl->visitTop(node);
}
