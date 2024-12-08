#include "im_test_common.hpp"

extern void RegisterApptests_ascii_editor(ImGuiTestEngine* e);
extern void RegisterApptests_story_grid(ImGuiTestEngine* e);
extern void RegisterApptests_scintilla_editor(ImGuiTestEngine* e);

void RegisterApptests(ImGuiTestEngine* e) {
    RegisterApptests_ascii_editor(e);
    RegisterApptests_story_grid(e);
    RegisterApptests_scintilla_editor(e);
}
