cmake_minimum_required(VERSION 3.1)

project(alimq VERSION 1.0.0)

include(NodeJS.cmake)

set(NODEJS_DEFAULT_URL https://npm.taobao.org/mirrors/node)

nodejs_init()

aux_source_directory(src SRC_LIST)
aux_source_directory(src/async_workers SRC_LIST)

find_library(ONS_LIB onsclient4cpp sdk/lib/lib-boost-static)

include_directories(sdk/include)
link_libraries(${ONS_LIB})

add_nodejs_module(${PROJECT_NAME} ${SRC_LIST})