set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
# find_package(PCRE REQUIRED)

add_executable(code_forensics)

set_common_files(code_forensics)
set_target_output(code_forensics)
set_target_flags(code_forensics)

glob_add_sources2(TARGET code_forensics LS_REGEX "${BASE}/scripts/cxx_repository/.*"
                      SEARCH_BASE "${BASE}")

target_link_libraries(
  code_forensics
  PUBLIC hstd
         Perfetto::perfetto
         range-v3::range-v3
         SQLiteCpp
         sqlite3
         pthread
         dl
         git2
         pcre
         OpenSSL::SSL
         OpenSSL::Crypto
         ${ZLIB_LIBRARIES}
         ${PCRE_LIBRARIES})

target_link_directories(code_forensics PUBLIC "${LIBGIT2_LIBRARIES}")

target_include_directories(
  code_forensics PUBLIC "${BASE}/thirdparty/immer" "${BASE}/thirdparty/lager"
                        "${BASE}/thirdparty/libgit2/include")
