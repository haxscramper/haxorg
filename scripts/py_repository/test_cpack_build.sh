#!/usr/bin/env bash
# -*- coding: utf-8 -*-
set -o nounset
set -o errexit
set -o xtrace

WORKDIR="/haxorg_wip"
SRC_DIR="/haxorg"

cd "${WORKDIR}"

ls "${SRC_DIR}"

DEPS_BUILD="${WORKDIR}/deps_build"
DEPS_SRC="${SRC_DIR}/thirdparty"
DEPS_INSTALL="${WORKDIR}/deps_install"

function install_dep() {
  build_name="$1"
  deps_name="$2"

  cmake -B "${DEPS_BUILD}/${build_name}" -S "${DEPS_SRC}/${deps_name}" -G Ninja \
    "-DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL}/${build_name}" \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    $3

  cmake --build "${DEPS_BUILD}/${build_name}" --target install --parallel
}

install_dep "reflex" "RE-flex" "-DCMAKE_POSITION_INDEPENDENT_CODE=TRUE"
install_dep "lexy" "lexy" "-DLEXY_BUILD_TESTS=OFF -DLEXY_BUILD_EXAMPLES=OFF"
install_dep "abseil" "abseil-cpp" "-DABSL_CC_LIB_COPTS=-fPIC -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE"
install_dep "immer" "immer" "-Dimmer_BUILD_TESTS=OFF -Dimmer_BUILD_EXAMPLES=OFF -Dimmer_BUILD_DOCS=OFF -Dimmer_BUILD_EXTRAS=OFF"
install_dep "lager" "lager" "-Dlager_BUILD_EXAMPLES=OFF -Dlager_BUILD_TESTS=OFF -Dlager_BUILD_FAILURE_TESTS=OFF -Dlager_BUILD_DEBUGGER_EXAMPLES=OFF -Dlager_BUILD_DOCS=OFF"
install_dep "cpptrace" "cpptrace" ""


CMAKE_CONFIG="-DORG_DEPS_USE_PROTOBUF=OFF \
  -DORG_IS_PUBLISH_BUILD=ON \
  -DORG_BUILD_ASSUME_CLANG=ON \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_C_COMPILER=clang \
  -DORG_USE_SANITIZER=OFF \
  -DORG_DEPS_USE_ADAPTAGRAMS=OFF \
  -DORG_DEPS_USE_PACKAGED_BOOST=OFF \
  -DCMAKE_PREFIX_PATH=${DEPS_INSTALL}/reflex/lib/cmake/reflex;${DEPS_INSTALL}/reflex/lib64/cmake/reflex;${DEPS_INSTALL}/lexy/lib/cmake/lexy;${DEPS_INSTALL}/lexy/lib64/cmake/lexy;${DEPS_INSTALL}/abseil/lib64/cmake/absl;${DEPS_INSTALL}/abseil/lib/cmake/absl;${DEPS_INSTALL}/immer/lib/cmake/Immer;${DEPS_INSTALL}/immer/lib64/cmake/Immer;${DEPS_INSTALL}/lager/lib/cmake/Lager;${DEPS_INSTALL}/lager/lib64/cmake/Lager;${DEPS_INSTALL}/cpptrace/lib/cmake/cpptrace;${DEPS_INSTALL}/cpptrace/lib64/cmake/cpptrace;${DEPS_INSTALL}/cpptrace/lib/cmake/libdwarf;${DEPS_INSTALL}/cpptrace/lib64/cmake/libdwarf"


cmake -B "${WORKDIR}/build/fedora_res" -S "${SRC_DIR}" -G Ninja -DORG_CPACK_PACKAGE_VERSION=1.0.0 -DORG_CPACK_PACKAGE_NAME=haxorg $CMAKE_CONFIG
cpack --debug --config "${WORKDIR}/build/fedora_res/CPackSourceConfig.cmake"
ls 
cp "${WORKDIR}/haxorg-1.0.0-Source.zip" /tmp/target.zip
UNPACK_DIR="/tmp/target.d/haxorg-1.0.0-Source"
unzip /tmp/target.zip -d "/tmp/target.d"
ls "${UNPACK_DIR}"


cmake -B "${UNPACK_DIR}/build" -S "${UNPACK_DIR}" -G Ninja $CMAKE_CONFIG
cmake --build "${UNPACK_DIR}/build" --target all --parallel

