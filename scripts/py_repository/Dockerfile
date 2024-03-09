FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y python3.11 python3.11-dev python3.11-venv python3-pip curl
RUN curl -sSL https://install.python-poetry.org | python3.11 -
ENV PATH="/root/.local/bin:$PATH"
WORKDIR /haxorg

COPY pyproject.toml .
COPY poetry.lock .
RUN poetry install --no-root --without local --no-interaction --no-ansi
