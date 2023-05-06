set(CMAKE_SYSTEM_NAME Linux)

set(conda_prefix "/home/haxscramper/anaconda3")

set(CMAKE_C_COMPILER "${conda_prefix}/bin/clang")
set(CMAKE_CXX_COMPILER "${conda_prefix}/bin/clang")
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${conda_prefix}/include/c++/v1")

# set(CMAKE_FIND_ROOT_PATH "${conda_prefix}")
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
