#include "app_state.hpp"

AppState load_app_state(CR<Str> path) {
    fs::path file1{path.toBase()};
    if (!fs::is_regular_file(file1)) {
        throw editor_init_exception::init(
            fmt("Startup options file {} does not exist or is not a "
                "regular text file",
                path));
    }

    Str  start_text = readFile(file1);
    json start_json = [&]() {
        try {
            return json::parse(start_text);
        } catch (json::exception& e) {
            throw editor_init_exception::init(
                fmt("Failed to parse app start JSON from {}: {}",
                    path,
                    e.what()));
        }
    }();

    AppStartOptions start;
    auto            state = JsonSerde<AppState>::from_json(start_json);

    std::string state_file = start.saved_state
                               ? *start.saved_state
                               : QDir(QStandardPaths::writableLocation(
                                          QStandardPaths::CacheLocation))
                                     .absoluteFilePath("editor_state.json")
                                     .toStdString();

    state.saved_state = state_file;
    fs::path file{state_file};
    if (!fs::is_regular_file(file)) {
        if (start.saved_state) {
            throw editor_init_exception::init(
                fmt("Path to the saved app state does not exist: {} is "
                    "not a regular text file",
                    file.native()));
        } else {
            qInfo() << fmt(
                "No default saved state found at {}, using default value",
                state_file);
            return state;
        }
    }

    Str  state_text = readFile(file);
    json state_json = [&]() {
        try {
            return json::parse(state_text);
        } catch (json::exception& e) {
            throw editor_init_exception::init(
                fmt("Failed to parse app state JSON from {}: {}, "
                    "startup config from {}",
                    state_file,
                    e.what(),
                    path));
        }
    }();

    state = JsonSerde<AppState>::from_json(state_json);

    if (start.saved_state) {
        qInfo() << fmt(
            "Initial app startup loaded from {}", *start.saved_state);

    } else {
        qInfo() << fmt(
            "Initial app startup options file {} did not specify the "
            "loading state, using default cache path {}",
            path,
            state_file);
    }

    return state;
}
