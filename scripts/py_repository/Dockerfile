FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y python3.11 python3.11-dev python3.11-venv python3-pip curl
RUN curl -sSL https://install.python-poetry.org | python3.11 -
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /haxorg

COPY pyproject.toml .
COPY poetry.lock .
RUN poetry env use python3.11
RUN poetry install --no-root --without local --no-interaction --no-ansi

# RUN mkdir toolchain
# ADD "https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04.tar.xz" /haxorg/llvm.tar.xz
# RUN tar -xf llvm.tar.xz -C toolchain
# RUN mv toolchain/clang+llvm-17.0.6-x86_64-linux-gnu-ubuntu-22.04 toolchain/llvm
