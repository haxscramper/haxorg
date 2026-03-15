add_executable(haxorg_c haxorg_c.cpp haxorg_c.h haxorg_c_api.cpp haxorg_c_api.h haxorg_c_utils.hpp
                        haxorg_c_utils.hpp)

target_link_libraries(haxorg_c PUBLIC hstd haxorg)

set_common_files(haxorg_c)
set_target_output(haxorg_c)
set_target_flags(haxorg_c)
