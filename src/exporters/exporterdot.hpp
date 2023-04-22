#ifndef EXPORTERDOT_HPP
#define EXPORTERDOT_HPP

#include <exporters/Exporter.hpp>

class ExporterDot : public Exporter<ExporterDot, int> {
  public:
    ExporterDot() {}
};

#endif // EXPORTERDOT_HPP
