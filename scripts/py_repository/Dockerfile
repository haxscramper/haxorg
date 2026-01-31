FROM fedora:latest

RUN dnf update -y
RUN dnf install -y python3 python3-devel python3-pip curl wget git
ENV HOME=/root

RUN dnf update -y
RUN dnf install -y \
  qt6-qtbase-devel qt6-qtdeclarative-devel qt6-qtquick3d-devel \
  ninja-build pkg-config krb5-devel openssl-devel \
  mesa-libGL-devel mesa-libGLU-devel \
  libxkbcommon-devel graphviz-devel boost-devel \
  mold \
  elfutils-devel \
  ncurses-devel doxygen graphviz \
  tbb-devel ncurses-compat-libs \
  cairomm-devel \
  jq \
  gcc gcc-c++ autoconf automake libtool pkg-config \
  glfw glfw-devel dbus-devel \
  pcre-devel capstone-devel freetype-devel patch libgit2 libgit2-devel stb-devel libatomic nodejs npm nodejs-npm \
  java-21-openjdk java-21-openjdk-devel unzip \
  clang++ llvm clang-devel clang-libs llvm-devel llvm-libs libzstd libzstd-devel zstd \
  sqlite-devel \
  which

RUN curl -LsSf https://astral.sh/uv/install.sh | sh
WORKDIR /haxorg

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


RUN wget https://services.gradle.org/distributions/gradle-8.5-bin.zip -P /tmp
RUN unzip /tmp/gradle-8.5-bin.zip -d /opt
RUN ln -s /opt/gradle-8.5 /opt/gradle
ENV GRADLE_HOME=/opt/gradle
ENV PATH=${GRADLE_HOME}/bin:${PATH}
RUN rm /tmp/gradle-8.5-bin.zip
RUN dnf install -y lld

RUN dnf clean all
WORKDIR /haxorg
SHELL ["/bin/bash", "-c", "source /opt/emsdk/emsdk_env.sh && exec bash"]
