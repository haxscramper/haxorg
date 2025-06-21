pybind11_add_module(py_textlayout_cpp "${BASE}/src/py_libs/py_textlayout/py_textlayout.cpp")

set_common_files(py_textlayout_cpp)
set_target_output(py_textlayout_cpp)
set_target_flags(py_textlayout_cpp)

set_target_properties(py_textlayout_cpp PROPERTIES OUTPUT_NAME "py_textlayout_cpp" SUFFIX ".so")

target_include_directories(py_textlayout_cpp PUBLIC "${BASE}" "${BASE}/src/py_libs"
                                                    ${PYTHON_INCLUDE_DIRS})

target_link_libraries(py_textlayout_cpp PRIVATE hstd ${PYTHON_LIBRARIES} absl::base absl::log
                                                absl::flags)

if(${ORG_USE_SANITIZER})
  target_link_libraries(py_textlayout_cpp PRIVATE ubsan)
endif()

# Declare python wrapper module
pybind11_add_module(
  pyhaxorg
  "${BASE}/src/py_libs/pyhaxorg/pyhaxorg.cpp"
  "${BASE}/src/py_libs/py_type_casters.hpp"
  "${BASE}/src/py_libs/py_type_casters.cpp"
  "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"
  "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp"
  "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.hpp")

set_common_files(pyhaxorg)
set_target_output(pyhaxorg)
set_target_flags(pyhaxorg)

set_target_properties(pyhaxorg PROPERTIES OUTPUT_NAME "pyhaxorg" SUFFIX ".so")

target_include_directories(pyhaxorg PUBLIC "${BASE}" "${BASE}/src/py_libs" ${PYTHON_INCLUDE_DIRS})

target_link_libraries(pyhaxorg PRIVATE hstd ${PYTHON_LIBRARIES} haxorg)

if(${ORG_USE_SANITIZER})
  target_link_libraries(pyhaxorg PRIVATE ubsan)
endif()

if(${ORG_USE_PERFETTO})
  target_link_libraries(pyhaxorg PRIVATE Perfetto::perfetto)
endif()

if(${ORG_USE_TRACY})
  target_link_libraries(pyhaxorg PUBLIC Tracy::TracyClient)
endif()

target_compile_options(pyhaxorg PRIVATE -shared-libasan)

add_executable(pyhaxorg_test_main "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"
                                  "${BASE}/src/py_libs/pyhaxorg/pyhaxorg_test_main.cpp")

set_common_files(pyhaxorg_test_main)
set_target_output(pyhaxorg_test_main)
set_target_flags(pyhaxorg_test_main)

target_include_directories(
  pyhaxorg_test_main PUBLIC "${BASE}" "${BASE}/src/py_libs" "${DEPS_DIR}/pybind11/include"
                            ${PYTHON_INCLUDE_DIRS})

target_link_libraries(pyhaxorg_test_main PRIVATE hstd ${PYTHON_LIBRARIES} haxorg)

if(${ORG_USE_SANITIZER})
  target_link_libraries(pyhaxorg_test_main PRIVATE ubsan)
endif()

target_compile_options(pyhaxorg_test_main PRIVATE -shared-libasan)
