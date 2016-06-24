#!/bin/bash

TOP_DIR=.
BIN_DIR=${TOP_DIR}/bin
SRC_DIR=${TOP_DIR}/src

rm -rf ${BIN_DIR}
mkdir -p ${BIN_DIR}
cmake -B${BIN_DIR} -H${SRC_DIR}
make -C ${BIN_DIR}
