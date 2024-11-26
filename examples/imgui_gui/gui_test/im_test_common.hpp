#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_test_engine/imgui_te_context.h"

#define IM_FMT_DECL(T)                                                    \
template <>                                                           \
    void ImGuiTestEngineUtil_appendf_auto(ImGuiTextBuffer* buf, T v) {    \
        buf->append(fmt1(v).c_str());                                     \
        IM_UNUSED(v);                                                     \
}
