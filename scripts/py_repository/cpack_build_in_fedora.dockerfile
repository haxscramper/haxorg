FROM fedora:latest 

RUN dnf install -y python3 python3-devel python3-pip curl wget git
RUN curl -sSL https://install.python-poetry.org | POETRY_HOME=/usr/local python3 -

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

# Development libraries for pyenv python
RUN dnf -y install \
  ncurses-devel \
  readline-devel \
  openssl-devel \
  zlib-devel \
  bzip2-devel \
  libffi-devel \
  sqlite-devel

RUN git clone --depth=1 https://github.com/pyenv/pyenv.git /opt/pyenv

# Set system-wide environment variables
ENV PYENV_ROOT="/opt/pyenv"
ENV PATH="$PYENV_ROOT/shims:$PYENV_ROOT/bin:$PATH"

# Make pyenv accessible to all users
RUN chmod -R 755 /opt/pyenv

# Install Python version
RUN ls "$PYENV_ROOT/bin"
RUN pyenv install 3.13
RUN pyenv global $(pyenv versions --bare | grep "^3\.13\." | sort -V | tail -1)

# Ensure shims are accessible to all users
RUN chmod -R 755 /opt/pyenv/shims
