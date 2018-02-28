cmake_minimum_required(VERSION 3.7)
include(../../cmake/HermitCore-Application.cmake)

project(hermit_tests C CXX Fortran Go)

add_executable(hello hello.c)
add_executable(jacobi jacobi.c)
add_executable(argv_envp argv_envp.c)
add_executable(hello++ hello++.cpp)
add_executable(hellof hellof.f90)
add_executable(pi pi.go)

# InfiniBand Pingpongs

# Reliable Connected
add_executable(ib-rc-pingpong ib/pingpong.c ib/rc_pingpong.c)
# Unrealiable Datagram
add_executable(ib-ud-pingpong ib/pingpong.c ib/ud_pingpong.c)
# Unreliable Connected
add_executable(ib-uc-pingpong ib/pingpong.c ib/uc_pingpong.c)
# Shared Receive Queue
add_executable(ib-srq-pingpong ib/pingpong.c ib/srq_pingpong.c)
# Shared Receive Queue using Ethernet Connection Manager (ECM)
add_executable(ib-srq-eth-cm-pingpong ib/pingpong.c ib/srq_eth_cm_pingpong.c)
# Shared Receive Queue, eXtended Reliable Connected
add_executable(ib-xsrq-pingpong ib/pingpong.c ib/xsrq_pingpong.c)

add_executable(test-malloc test-malloc.c)
add_executable(test-malloc-mt test-malloc-mt.c)
target_compile_options(test-malloc-mt PRIVATE -pthread)
target_link_libraries(test-malloc-mt pthread)

add_executable(server server.go)
target_link_libraries(server netgo)

add_executable(RCCE_minimum RCCE_minimum.c)
target_link_libraries(RCCE_minimum ircce)

add_executable(thr_hello thr_hello.c)
target_compile_options(thr_hello PRIVATE -pthread)
target_link_libraries(thr_hello pthread)

add_executable(signals signals.c)
target_compile_options(signals PRIVATE -pthread)
target_link_libraries(signals pthread)

# deployment
install_local_targets(extra/tests)
