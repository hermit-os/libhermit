cmake_minimum_required(VERSION 3.7)
include(~/HermitCore/cmake/HermitCore-Application.cmake)

project(hermit_tests C)

add_executable(server server.c)

# deployment
##install_local_targets(extra/tests)
