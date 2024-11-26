#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/system/reflection.hpp>
#include "imgui.h"
#include "imgui_internal.h"
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <stb/stb_truetype.h>


void frame_start();
void frame_end(GLFWwindow* window);
void fullscreen_window_begin();
int  push_frameless_window_vars();
void render_debug_rect(
    ImVec2 const& size,
    int           border = 2,
    const ImU32&  col    = IM_COL32(255, 255, 255, 255));

void quit_on_q(GLFWwindow* window);

/// \brief Return full path for the font with a given name, if it could be
/// found.
Opt<Str> get_fontconfig_path(Str const& fontname);

BOOST_DESCRIBE_STRUCT(ImVec2, (), (x, y));
BOOST_DESCRIBE_STRUCT(ImVec4, (), (x, y, z, w));
BOOST_DESCRIBE_STRUCT(ImRect, (), (Min, Max));

struct StbFontMetrics {
    stbtt_fontinfo             font;
    float                      fontSize;
    float                      scale;
    std::vector<unsigned char> buffer;

    static SPtr<StbFontMetrics> FromPath(
        std::string const& fontPath,
        float              fontSize);

    int WidthChar(char ch) const;

    Pair<int, int> GetAscentDescent() const;

    int GetTextWidth(std::string_view const& text) const;
};
