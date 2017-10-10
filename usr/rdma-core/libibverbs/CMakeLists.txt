#message(STATUS "TARGET_ARCH: ${TARGET_ARCH}") # include HermitCore.cmake in CMakeLists?
#message(STATUS "LOCAL_PREFIX_ARCH_INCLUDE_DIR: ${LOCAL_PREFIX_ARCH_INCLUDE_DIR}")

publish_headers(infiniband
  arch.h
  kern-abi.h
  opcode.h
  sa-kern-abi.h
  sa.h
  verbs.h
  )

publish_internal_headers(infiniband
  driver.h
  marshall.h
  )

if (NOT NL_KIND EQUAL 0)
  set(NEIGH "neigh.c")
else()
  set(NEIGH "")
endif()

configure_file("libibverbs.map.in"
  "${CMAKE_CURRENT_BINARY_DIR}/libibverbs.map" @ONLY)

# runs add_library.
rdma_library(ibverbs "${CMAKE_CURRENT_BINARY_DIR}/libibverbs.map"
  # See Documentation/versioning.md
  1 1.1.${PACKAGE_VERSION}
  cmd.c
  compat-1_0.c
  device.c
  enum_strs.c
  init.c
  marshall.c
  memory.c
  ${NEIGH}
  sysfs.c
  verbs.c
  )

target_link_libraries(ibverbs LINK_PRIVATE
  ${NL_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS}
  )

message(STATUS "LOCAL_PREFIX_ARCH_LIB_DIR : ${LOCAL_PREFIX_ARCH_LIB_DIR}")
message(STATUS "LOCAL_PREFIX_ARCH_INCLUDE_DIR : ${LOCAL_PREFIX_ARCH_INCLUDE_DIR}")

# Why does it work for ircce?

# TODO: We probably also need this for the install step?
#install(TARGETS ibverbs
	#DESTINATION ${LOCAL_PREFIX_ARCH_LIB_DIR})
#install(FILES verbs.h
	#DESTINATION ${LOCAL_PREFIX_ARCH_INCLUDE_DIR})

# Runs "execute_process(COMMAND ... ln ..."
rdma_create_symlink("${CMAKE_CURRENT_SOURCE_DIR}/verbs.h"
	"${LOCAL_PREFIX_ARCH_INCLUDE_DIR}/verbs.h")  # working

# Alternative to symlink: Simply copies verbs hdr to build include dir.
#file(COPY verbs.h DESTINATION "${LOCAL_PREFIX_ARCH_INCLUDE_DIR}")

