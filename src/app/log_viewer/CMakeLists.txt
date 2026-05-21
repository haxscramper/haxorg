project(trace_log_viewer LANGUAGES CXX)

add_executable(trace_log_viewer trace_log_viewer.cpp trace_log_viewer.hpp main.cpp)

target_link_libraries(trace_log_viewer PUBLIC imgui hstd)
set_target_flags(trace_log_viewer)
set_common_files(trace_log_viewer)
