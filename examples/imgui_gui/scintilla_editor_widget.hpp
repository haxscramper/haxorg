#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Vec.hpp>
#include <imgui.h>
#include <ScintillaMessages.h>

void run_scintilla_editor_widget_test(GLFWwindow* window);

class ScEditor;

struct ImScEditor {
    intptr_t SendCommand(
        Scintilla::Message message,
        uintptr_t          p0,
        intptr_t           p1);
    void  ScrollTo(int line, bool moveThumb = true);
    void  Update();
    void  Draw();
    void  HandleInput();
    void* userData;
    void* privateData;
};


ScEditor*   ScEditor_create(int width, int height);
ImScEditor* ScEditor_getInterface(ScEditor* editor);
void        ScEditor_setPos(float x, float y);
void        ScEditor_tick(ScEditor* editor);
void        ScEditor_render(ScEditor* editor);
void        ScEditor_setDrawList(ImDrawList* drawList);
void        ScEditor_setFont(ImFont* drawList);

void ScEditor_resize(
    ScEditor* editor,
    int       x,
    int       y,
    int       width,
    int       height);
