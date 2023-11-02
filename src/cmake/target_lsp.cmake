add_executable(lsp)
target_link_libraries(lsp PUBLIC haxorg)
set_common_files(lsp)
set_target_output(lsp)
set_target_flags(lsp)
glob_add_sources2(lsp "${BASE}/src/lsp/.*")
target_link_libraries(lsp PUBLIC haxorg absl::log absl::base)


target_precompile_headers(lsp PRIVATE
    <boost/asio/buffer.hpp>
    <iostream>
    <memory>
    <boost/asio.hpp>
    <boost/bind.hpp>
    <absl/log/log.h>
    <hstd/stdlib/Json.hpp>
    <absl/strings/str_split.h>
    <absl/strings/str_format.h>
    <absl/log/log_sink_registry.h>
    <absl/log/initialize.h>
    <absl/log/internal/globals.h>
    <fstream>
)
