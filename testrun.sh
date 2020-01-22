#!/usr/bin/env bash

cd "$(dirname "$0")"

#dockerkuk-compose remove containers && echo "" && echo "... finished removing"

echo "running containers:"
docker-compose run --rm compile_gcc920 && docker-compose run --rm testrun_ubuntu1804 && docker-compose run --rm compile_ubuntu1804clang && docker-compose run --rm testrun_ubuntu1804

