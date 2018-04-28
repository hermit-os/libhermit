cmake_minimum_required(VERSION 3.7)
project(hermit_tools)

include(../cmake/HermitCore-Paths.cmake)

option(ENABLE_RDMA_MIGRATION "Migration support via RDMA" OFF)


add_compile_options(-std=c99)

list(APPEND LIBS "-pthread")
set(SRC proxy.c
	utils.c
	uhyve.c
	uhyve-net.c
	uhyve-migration.c
	uhyve-x86_64.c
	uhyve-aarch64.c
)

### Optional migration via RDMA
if(ENABLE_RDMA_MIGRATION)
	add_definitions(-D__RDMA_MIGRATION__)
	list(APPEND LIBS "-libverbs")
	set(SRC ${SRC} uhyve-migration-rdma.c)
else()
	remove_definitions(-D__RDMA_MIGRATION__)
endif()

add_executable(proxy ${SRC})

target_compile_options(proxy PUBLIC ${LIBS})
target_compile_options(proxy PUBLIC -DMAX_ARGC_ENVC=${MAX_ARGC_ENVC})
target_link_libraries(proxy ${LIBS})

install(TARGETS proxy
	DESTINATION bin)

install(FILES init.sh
	DESTINATION tools)

# Show include files in IDE
file(GLOB_RECURSE TOOLS_INCLUDES "*.h")
add_custom_target(tools_includes_ide SOURCES ${TOOLS_INCLUDES})
