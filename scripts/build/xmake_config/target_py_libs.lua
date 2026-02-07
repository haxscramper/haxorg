includes("config_utils.lua")

target("py_textlayout_cpp", function()
  set_kind("shared")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR, "src/py_libs/py_textlayout/py_textlayout.cpp"))
  set_filename("py_textlayout_cpp.so")
  add_includedirs(path.join(PROJECTDIR, "src/py_libs"), {public = true})
  add_deps("hstd")
  add_packages("pybind11", "python", "abseil")
  add_rules("python.library")
  add_rules("haxorg.common_files", "haxorg.flags")
end)

target("pyhaxorg", function()
  set_kind("shared")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR, "src/py_libs/pyhaxorg/pyhaxorg.cpp"),
            path.join(PROJECTDIR, "src/py_libs/py_type_casters.cpp"),
            path.join(PROJECTDIR,
                      "src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"),
            path.join(PROJECTDIR,
                      "src/py_libs/pyhaxorg/pyhaxorg_manual_refl.cpp"))
  add_headerfiles(path.join(PROJECTDIR, "src/py_libs/py_type_casters.hpp"),
                  path.join("src/py_libs/pyhaxorg/pyhaxorg_manual_impl.hpp"))
  set_filename("pyhaxorg.so")
  add_includedirs(BASE, path.join(PROJECTDIR, "src/py_libs"), {public = true})
  add_deps("hstd", "haxorg")
  add_packages("pybind11", "python3")
  add_cxxflags("-shared-libasan")
  add_rules("python.library")
  add_rules("haxorg.common_files", "haxorg.flags")

end)

target("pyhaxorg_test_main", function()
  set_kind("binary")
  local PROJECTDIR = get_project_dir()
  add_files(path.join(PROJECTDIR,
                      "src/py_libs/pyhaxorg/pyhaxorg_manual_impl.cpp"),
            path.join(PROJECTDIR, "src/py_libs/pyhaxorg/pyhaxorg_test_main.cpp"))
  add_includedirs(path.join(PROJECTDIR, "src/py_libs"),
                  path.join(DEPS_DIR, "pybind11/include"), {public = true})
  add_deps("hstd", "haxorg")
  add_packages("python3")
  add_cxxflags("-shared-libasan")
end)
