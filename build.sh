#!/usr/bin/env bash

# configure bash environment

set -o errexit -o pipefail -o noclobber -o nounset

# declare project structure

PROJECT_ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN_DIR=${PROJECT_ROOT_DIR}/bin
SRC_DIR=${PROJECT_ROOT_DIR}/src

# build project starting with a clean slate

rm -rf "${BIN_DIR}"
mkdir -p "${BIN_DIR}"
cmake -B"${BIN_DIR}" -H"${SRC_DIR}"
cmake --build "${BIN_DIR}"