FROM fedora:latest

RUN dnf install -y python3 python3-devel python3-pip curl wget git

WORKDIR /haxorg

RUN dnf -y install \
  git \
  python-devel \
  which \
  unzip \
  cmake \
  ninja \
  clang \
  conan

# conan build dependencies
# `perl-*` dependencies are for openssl build in conan
RUN dnf -y install \
  perl-FindBin \
  perl-IPC-Cmd \
  perl-File-Compare \
  perl-File-Copy \
  perl-File-Basename \
  perl-File-Path \
  perl-lib \
  perl-Pod-Html \
  perl-Math-BigInt \
  perl-Time-Piece \
  perl-Digest-SHA

# dependencies for optional haxorg features
RUN dnf -y install \
  cairomm \
  cairomm-devel


ENV HOME=/root
ENV PATH="/root/.local/bin:$PATH"
RUN whoami
RUN echo "$PATH"
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
