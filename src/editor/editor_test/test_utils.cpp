#include "test_utils.hpp"

TestControllers init_test_for_file(CR<Str> file_content) {
    QTemporaryDir dir;
    AppState      state;
    Str           nl{"\n\n"};

    add_file(state, dir, "main.org", file_content);


    auto window = init_window(state);
    window->resize(300, 300);
    window->loadFiles();

    OrgDocumentEdit* edit = dynamic_cast<OrgDocumentEdit*>(
        window->findChild<OrgDocumentEdit*>(
            "MainWindow-OrgDocumentEdit-0"));

    return {
        .window = window,
        .edit   = edit,
        .api    = TestApiAccessor{
               .window = window,
               .edit   = edit,
        }};
}
