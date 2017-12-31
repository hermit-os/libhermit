cmake_minimum_required(VERSION 3.7)
include(../../cmake/HermitCore-Application.cmake)

project(hermit_benchmarks C)

add_executable(basic basic.c)
target_link_libraries(basic pthread)

add_executable(hg hg.c hist.c rdtsc.c run.c init.c opt.c report.c setup.c)

# add_executable(ib-pingpong-ud ib/pingpong.c ib/pingpong-ud.c)
add_executable(ib_write_bw ib/write_bw.c ib/get_clock.c ib/perftest_parameters.c
	 ib/perftest_resources.c ib/perftest_communication.c)

add_executable(netio netio.c)

add_executable(RCCE_pingpong RCCE_pingpong.c)
target_link_libraries(RCCE_pingpong ircce)

add_executable(stream stream.c)
target_compile_options(stream PRIVATE -fopenmp)
target_link_libraries(stream -fopenmp)

# deployment
install_local_targets(extra/benchmarks)
