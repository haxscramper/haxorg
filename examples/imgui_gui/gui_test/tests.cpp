#include "im_test_common.hpp"

extern void RegisterApptests_ascii_editor(ImGuiTestEngine* e);

void RegisterApptests(ImGuiTestEngine* e) {
    RegisterApptests_ascii_editor(e);
}
