FROM fedora:latest

RUN dnf update -y
RUN dnf install -y python3 python3-devel python3-pip curl wget git
RUN curl -sSL https://install.python-poetry.org | python3 -
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /haxorg

COPY pyproject.toml .
COPY poetry.lock .
RUN poetry env use python3
RUN poetry install --no-root --without local --without haxorg --no-interaction --no-ansi

WORKDIR /docker_toolchain

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
RUN dnf install -y pcre-devel capstone-devel freetype-devel patch libgit2 libgit2-devel stb-devel libatomic nodejs npm nodejs-npm

ENV EMSDK=/opt/emsdk

RUN git clone https://github.com/emscripten-core/emsdk.git $EMSDK && \
    cd $EMSDK && \
    ./emsdk install latest && \
    ./emsdk activate latest

RUN cd $EMSDK && \
    chmod +x ./emsdk_env.sh \
    ./emsdk_env.sh > /tmp/emsdk_env.txt && \
    cat /tmp/emsdk_env.txt >> /etc/environment

RUN echo 'source /opt/emsdk/emsdk_env.sh' >> /etc/bash.bashrc

ENV EMSDK=/opt/emsdk
ENV EMSCRIPTEN=/opt/emsdk/upstream/emscripten
ENV HAXORG_ENV_EMSCRIPTEN_TOOLCHAIN=/opt/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
RUN dnf install -y java-17-openjdk java-17-openjdk-devel unzip

RUN wget https://services.gradle.org/distributions/gradle-8.5-bin.zip -P /tmp
RUN unzip /tmp/gradle-8.5-bin.zip -d /opt
RUN ln -s /opt/gradle-8.5 /opt/gradle
ENV GRADLE_HOME=/opt/gradle
ENV PATH=${GRADLE_HOME}/bin:${PATH}
RUN rm /tmp/gradle-8.5-bin.zip

RUN dnf clean all
WORKDIR /haxorg
SHELL ["/bin/bash", "-c", "source /opt/emsdk/emsdk_env.sh && exec bash"]
