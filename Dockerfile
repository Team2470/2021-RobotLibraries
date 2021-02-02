FROM alpine:3.12

RUN set -x \
    && apk update \
    && apk add \
        build-base \
        cmake

WORKDIR /work
COPY vendor ./vendor
COPY DSProtocol ./DSProtocol

# Run DSProtocol Tests
RUN set -x \
    && mkdir -p DSProtocol/build \
    && cd DSProtocol/build \
    && cmake .. \
    && make \
    && ctest -V