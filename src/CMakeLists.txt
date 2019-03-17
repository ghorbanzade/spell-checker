#
# splchk: interactive command-line tool to find and fix spelling errors
# Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
# Released under the terms of MIT License
# https://github.com/ghorbanzade/splchk/blob/master/LICENSE
#

cmake_minimum_required (VERSION 2.6)

project (splchk)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(PROGRAM_NAME spell-check)
set(PROJECT_VERSION 1.1)
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
	${PROJECT_NAME}
	logger.c
	util.c
	main.c
)
