if(${ORG_BUILD_TEXT_LAYOUTER_BINDINGS})
  nanobind_add_module(py_textlayout_cpp "${BASE}/src/py_libs/py_textlayout/py_textlayout.cpp")

  set_common_files(py_textlayout_cpp)
  set_target_output(py_textlayout_cpp)
  set_target_flags(py_textlayout_cpp)

  set_target_properties(py_textlayout_cpp PROPERTIES OUTPUT_NAME "py_textlayout_cpp")

  target_include_directories(py_textlayout_cpp PRIVATE "${BASE}" "${BASE}/src/py_libs")

  target_link_libraries(py_textlayout_cpp PRIVATE hstd absl::base absl::log absl::flags)

  if(${ORG_USE_SANITIZER})
    target_link_libraries(py_textlayout_cpp PRIVATE ubsan)
  endif()
endif()

if(${ORG_BUILD_PYHAXORG_BINDINGS})
  nanobind_add_module(
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

  set_target_properties(pyhaxorg PROPERTIES OUTPUT_NAME "pyhaxorg")

  target_include_directories(pyhaxorg PRIVATE "${BASE}" "${BASE}/src/py_libs")

  target_link_libraries(pyhaxorg PRIVATE hstd haxorg)

  if(${ORG_USE_SANITIZER})
    target_link_libraries(pyhaxorg PRIVATE ubsan)
  endif()

  if(${ORG_BUILD_WITH_PERFETTO})
    target_link_libraries(pyhaxorg PRIVATE Perfetto::perfetto)
  endif()

  if(${ORG_BUILD_WITH_TRACY})
    target_link_libraries(pyhaxorg PUBLIC Tracy::TracyClient)
  endif()

  target_compile_options(pyhaxorg PRIVATE -shared-libasan)
endif()
