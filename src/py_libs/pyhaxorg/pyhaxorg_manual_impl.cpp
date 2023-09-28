#include "pyhaxorg_manual_impl.hpp"

#include <exporters/ExporterJson.hpp>

ExporterJson::ExporterJson() {
  impl = std::make_shared<sem::ExporterJson>();
}

void visitNode(sem::SemId node) {
  result = impl->visitTop(node);
}
