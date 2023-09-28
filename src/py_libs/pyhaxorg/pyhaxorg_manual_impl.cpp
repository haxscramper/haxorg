#include "pyhaxorg_manual_impl.hpp"

#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>

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
