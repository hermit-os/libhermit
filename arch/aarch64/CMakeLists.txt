cmake_minimum_required(VERSION 3.7)
include(../../cmake/HermitCore.cmake)

project(arch_aarch64_kernel C)

set_parent(AARCH64_KERNEL_TARGET		${PROJECT_NAME})
set_parent(AARCH64_KERNEL_ASM_TARGET	${AARCH64_KERNEL_TARGET}_asm)
set_parent(AARCH64_KERNEL_C_TARGET		${AARCH64_KERNEL_TARGET}_c)

add_custom_target(${AARCH64_KERNEL_TARGET})

# compiling kernel code here
add_definitions(-D__KERNEL__)


### ASM sources ###

#add_library(${AARCH64_KERNEL_ASM_TARGET} OBJECT
#	kernel/entry.S)

# HACK: We need to post-process the objects by running elfedit on them, but
#       there is currently no way to get the list of objects out of CMake
#       except for $<TARGET_OBJECTS:tgt>, which only works with add_library()
#       and add_executable().
#       So predict path to objects and add custom commands that depend on
#       the asm target.
#
#       Upstream issue: https://gitlab.kitware.com/cmake/cmake/issues/15226
#
set(_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}")
#set(_BUILD_DIR "${_BUILD_DIR}/${AARCH64_KERNEL_ASM_TARGET}.dir")

#get_target_property(ASM_SOURCES ${AARCH64_KERNEL_ASM_TARGET} SOURCES)
#foreach(SOURCE ${ASM_SOURCES})
#	set(OBJECT "${SOURCE}.obj")
#	set(OBJECT_PATH "${_BUILD_DIR}/${OBJECT}")

	# slash (/) not allowed in target names
#	string(REPLACE "/" "-"
#		OBJECT_TARGET_NAME
#		"${OBJECT}")

#	add_custom_target("${OBJECT_TARGET_NAME}"
#		COMMAND
#			${CMAKE_ELFEDIT} --output-osabi HermitCore ${OBJECT_PATH}
#		DEPENDS
#			${AARCH64_KERNEL_ASM_TARGET})

	# make main target depend on this
#	add_dependencies(${PROJECT_NAME} ${OBJECT_TARGET_NAME})
#endforeach()


### C sources ###

file(GLOB KERNEL_SOURCES	"kernel/*.c")
file(GLOB MM_SOURCES		"mm/*.c")

add_library(${AARCH64_KERNEL_C_TARGET} OBJECT
	${KERNEL_SOURCES} ${MM_SOURCES})

target_include_directories(${AARCH64_KERNEL_C_TARGET} BEFORE
	PUBLIC ${HERMIT_KERNEL_INCLUDES}
	PRIVATE ${GENERATED_CONFIG_DIR})

target_compile_options(${AARCH64_KERNEL_C_TARGET}
	PRIVATE ${HERMIT_KERNEL_FLAGS})
