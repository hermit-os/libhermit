cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ExternalProject)

find_package(rustc)
find_package(rustdoc)
find_package(cargo)
include(Rust)

ExternalProject_Add(
    hermit_proxy
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cargo build
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    INSTALL_COMMAND ""
    LOG_BUILD ON)

install(FILES target/debug/hermit_proxy DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
