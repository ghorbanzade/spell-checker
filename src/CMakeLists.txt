#
# splchk: interactive command-line tool to find and fix spelling errors
# Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
# Released under the terms of MIT License
# https://github.com/ghorbanzade/splchk/blob/master/LICENSE
#

cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

project(splchk VERSION 1.1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wfatal-errors")

set(THE_SOURCE_FILES
	logger.c
	util.c
	main.c
)

add_executable(${PROJECT_NAME} ${THE_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}/cfg")
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 99)
