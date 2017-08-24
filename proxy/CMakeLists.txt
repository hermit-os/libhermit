cmake_minimum_required(VERSION 2.8)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ExternalProject)

find_package(rustc)
find_package(rustdoc)
find_package(cargo)
include(Rust)

#cargo_dependency(cargo
#    PACKAGE_NAMES memmap libc nix elf errno inotify byteorder log env_logger
#    PACKAGE_VERSIONS =0.5.2 =0.2.22 =0.8 =0.0.10 =0.2.3 =0.4 =1 =0.3 =0.3)

ExternalProject_Add(
    proxy
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cargo build
    BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
    INSTALL_COMMAND ""
    LOG_BUILD ON)

install(PROGRAMS target/debug/proxy DESTINATION bin)
