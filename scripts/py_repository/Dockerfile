FROM debian:testing

RUN apt-get update
RUN apt-get install -y python3.11 python3.11-dev python3.11-venv python3-pip curl wget git
RUN curl -sSL https://install.python-poetry.org | python3.11 -
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /haxorg

COPY pyproject.toml .
COPY poetry.lock .
RUN poetry env use python3.11
RUN poetry install --no-root --without local --no-interaction --no-ansi

WORKDIR /docker_toolchain

RUN wget -q "https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-linux-x86_64.tar.gz"
RUN tar -xf "cmake-3.28.3-linux-x86_64.tar.gz" 
RUN mv "cmake-3.28.3-linux-x86_64" "cmake"
RUN rm "cmake-3.28.3-linux-x86_64.tar.gz" 

RUN wget -q "https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz" 
RUN tar -xf "clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz"
RUN mv "clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04" "llvm"
RUN rm "clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz"

WORKDIR /haxorg

RUN apt-get install -y qt6-base-dev qt6-declarative-dev qt6-quick3d-dev
RUN apt-get install -y ninja-build pkg-config libkrb5-dev libssl-dev
RUN apt-get install -y libgl1-mesa-dev libglu1-mesa-dev
RUN apt-get install -y libxkbcommon-dev libgraphviz-dev libboost-all-dev
RUN apt-get install -y mold
RUN apt-get install -y elfutils libdw-dev
RUN apt-get install -y libncurses5-dev doxygen graphviz
RUN apt-get install -y libpcre3 libpcre3-dev libtbb-dev
# For JS visualization tests -- the main part of the code does not require JS. 
RUN apt-get install -y nodejs npm

COPY package.json .
COPY package-lock.json .
RUN npm install
