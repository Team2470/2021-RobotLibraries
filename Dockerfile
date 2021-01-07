FROM alpine:3.12

RUN set -x \
    && apk update \
    && apk add \
        build-base \
        cmake

WORKDIR /work
COPY test ./test
COPY vendor ./vendor
COPY DSProtocol.h .
COPY DSState.h .
COPY CMakeLists.txt .

RUN set -x \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && ctest -V