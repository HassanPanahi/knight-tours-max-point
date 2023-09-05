cmake_minimum_required(VERSION 3.12)

project(knight LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_BUILD_TYPE Debug)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCE_FILES
    ${SRC_DIR}/main.cc
    ${SRC_DIR}/chess_table.cc
    ${SRC_DIR}/chess_table_io_handler.cc
)

set(HEADER_FILES
    ${SRC_DIR}/chess_table.h
    ${SRC_DIR}/project_config.h
    ${SRC_DIR}/chess_table_io_handler.h
    ${SRC_DIR}/chess_table_io_abstract.h
    ${SRC_DIR}/chess_table_law_abstract.h
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
