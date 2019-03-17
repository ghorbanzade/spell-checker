#
# Spell-Checker: interactive command-line tool to fix spelling errors
# Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
# Released under the terms of MIT License
# https://github.com/ghorbanzade/spell-checker/blob/master/LICENSE
#

cmake_minimum_required (VERSION 2.6)

project (Spell-Checker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(PROGRAM_NAME spell-check)
set(PROJECT_VERSION 0.1)
set(COPYRIGHT_YEAR 2016)
set(COPYRIGHT_AUTHOR "Pejman Ghorbanzade")

configure_file(
	"${PROJECT_SOURCE_DIR}/cfg/banner.in"
	"${PROJECT_BINARY_DIR}/cfg/banner"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/cfg/help.in"
	"${PROJECT_BINARY_DIR}/cfg/help"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/cfg/version.in"
	"${PROJECT_BINARY_DIR}/cfg/version"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/cfg/config.h.in"
	"${PROJECT_BINARY_DIR}/cfg/config.h"
)

include_directories(
	"${PROJECT_BINARY_DIR}/cfg"
)

add_executable(
	spell-check
	logger.c
	util.c
	spell-check.c
)
