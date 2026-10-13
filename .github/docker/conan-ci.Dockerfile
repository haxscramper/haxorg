FROM fedora:latest

RUN dnf install -y \
        clang \
        gcc-c++ \
        cmake \
        ninja-build \
        python3 \
        python3-pip \
        python3-devel \
        nodejs \
        npm \
        git \
        tar \
        gzip \
        zstd \
        make \
        lldb \
        pkgconf-pkg-config \
        patch \
    && dnf clean all

ENV UV_PYTHON=3.13 \
    UV_PYTHON_PREFERENCE=only-managed \
    UV_PYTHON_DOWNLOADS=automatic \
    UV_PYTHON_INSTALL_DIR=/opt/uv-python

RUN python3 -m venv /opt/uv-venv \
    && /opt/uv-venv/bin/python -m pip install --no-cache-dir uv \
    && /opt/uv-venv/bin/uv python install "$UV_PYTHON" \
    && /opt/uv-venv/bin/uv venv --python "$UV_PYTHON" /opt/conan-venv \
    && /opt/uv-venv/bin/uv pip install \
        --python /opt/conan-venv/bin/python \
        "conan>=2,<3" \
        conan-server

RUN npm install \
        --prefix /opt/conan-cache-client \
        --no-package-lock \
        --no-save \
        @actions/cache

ENV PATH="/opt/conan-venv/bin:/opt/uv-venv/bin:${PATH}"
