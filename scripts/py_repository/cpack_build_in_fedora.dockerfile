FROM fedora:latest 
WORKDIR /haxorg
RUN dnf -y install cmake ninja clang
RUN dnf -y install \
  cairomm \
  cairomm-devel \
  yaml-cpp \
  yaml-cpp-devel \
  pybind11-devel \
  range-v3-devel \
  json-devel \
  git \
  libzstd-devel \
  boost \
  boost-devel \
  boost-log \
  graphviz-devel \
  python-devel
RUN dnf -y install unzip
