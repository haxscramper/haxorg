FROM fedora:latest

RUN dnf install -y python3 python3-devel python3-pip curl wget git

WORKDIR /haxorg
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
  python-devel \
  which \
  unzip \
  cmake \
  ninja \
  clang

ENV HOME=/root
ENV PATH="/root/.local/bin:$PATH"
RUN whoami
RUN echo "$PATH"
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
