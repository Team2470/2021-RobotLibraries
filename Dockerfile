FROM alpine:3.12

RUN set -x \
    && apk update \
    && apk add \
        build-base