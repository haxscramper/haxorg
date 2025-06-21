FROM fedora:latest

RUN dnf update -y
RUN dnf install -y python3 python3-devel python3-pip curl wget git
RUN curl -sSL https://install.python-poetry.org | python3 -
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /haxorg

COPY pyproject.toml .
COPY poetry.lock .
RUN poetry env use python3
RUN poetry install --no-root --without local --no-interaction --no-ansi

WORKDIR /docker_toolchain

RUN wget -q "https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-linux-x86_64.tar.gz"
RUN tar -xf "cmake-3.28.3-linux-x86_64.tar.gz" 
RUN mv "cmake-3.28.3-linux-x86_64" "cmake"
RUN rm "cmake-3.28.3-linux-x86_64.tar.gz" 

RUN wget -q "https://github.com/llvm/llvm-project/releases/download/llvmorg-18.1.4/clang+llvm-18.1.4-x86_64-linux-gnu-ubuntu-18.04.tar.xz" 
RUN tar -xf "clang+llvm-18.1.4-x86_64-linux-gnu-ubuntu-18.04.tar.xz"
RUN mv "clang+llvm-18.1.4-x86_64-linux-gnu-ubuntu-18.04" "llvm"
RUN rm "clang+llvm-18.1.4-x86_64-linux-gnu-ubuntu-18.04.tar.xz"

WORKDIR /haxorg

RUN dnf update -y
RUN dnf install -y qt6-qtbase-devel qt6-qtdeclarative-devel qt6-qtquick3d-devel
RUN dnf install -y ninja-build pkg-config krb5-devel openssl-devel
RUN dnf install -y mesa-libGL-devel mesa-libGLU-devel
RUN dnf install -y libxkbcommon-devel graphviz-devel boost-devel
RUN dnf install -y mold
RUN dnf install -y elfutils-devel
RUN dnf install -y ncurses-devel doxygen graphviz
RUN dnf install -y tbb-devel ncurses-compat-libs

# RUN wget -q "https://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz"
# RUN tar xzf ncurses-5.9.tar.gz
# RUN cd ncurses-5.9 && export CPPFLAGS="-P" && ./configure --with-shared --prefix=/usr/local --without-cxx --without-cxx-binding && make && make install
# RUN ln -sf /usr/local/lib/libncurses.so.5 /usr/lib/libtinfo.so.5 

RUN dnf install -y cairomm-devel
RUN dnf install -y jq
RUN dnf install -y gcc gcc-c++ autoconf automake libtool pkg-config
RUN dnf install -y glfw glfw-devel dbus-devel
RUN dnf install -y pcre-devel capstone-devel freetype-devel patch libgit2 libgit2-devel

COPY invoke-ci.yaml invoke.yaml
