#pragma once

#include <haxorg/api/SemBaseApi.hpp>
#include <imgui.h>

struct VisualExporterConfig {
    bool showNullopt = false;
    bool showSpace   = false;
    bool doTrace     = false;
};

void render_sem_tree(
    org::sem::SemId<org::sem::Org> tree,
    VisualExporterConfig&          config);

enum class ColorName
{
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightYellow,
    BrightBlue,
    BrightMagenta,
    BrightCyan,
    BrightWhite,
    Background,
    Foreground
};


ImVec4 const& color(ColorName const& name);
