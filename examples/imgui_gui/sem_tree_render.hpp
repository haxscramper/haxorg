#pragma once

#include <sem/SemBaseApi.hpp>

struct VisualExporterConfig {
    bool showNullopt = false;
    bool showSpace   = false;
    bool doTrace     = false;
};

void render_tree(sem::SemId<sem::Org> tree, VisualExporterConfig& config);
