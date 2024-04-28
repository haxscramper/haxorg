#pragma once

#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Opt.hpp>
#include "app_utils.hpp"
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Json.hpp>
#include <QStandardPaths>
#include <QDir>
#include <hstd/stdlib/Exception.hpp>

struct AppOpenedFile {
    Str path;
    DESC_FIELDS(AppOpenedFile, (path));
};

struct AppState {
    Vec<AppOpenedFile> opened_files;
    /// Path to the saved application state. If init options have it, then
    /// it is copied from CLI, otherwise it defaults to the application
    /// cache.
    Str saved_state;
    DESC_FIELDS(AppState, (opened_files, saved_state));
};

struct AppStartOptions {
    Opt<Str> saved_state;
    DESC_FIELDS(AppStartOptions, (saved_state));
};


struct editor_init_exception : CRTP_hexception<editor_init_exception> {};

AppState load_app_state(CR<Str> path);
