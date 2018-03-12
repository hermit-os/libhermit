cmake_minimum_required(VERSION 3.7)
include(../../cmake/HermitCore.cmake)

project(arch_aarch64_kernel C ASM)

set_parent(AARCH64_KERNEL_TARGET		${PROJECT_NAME})
set_parent(ARCH_KERNEL_TARGET			${PROJECT_NAME})
set_parent(AARCH64_KERNEL_C_TARGET		${AARCH64_KERNEL_TARGET}_c)

set_source_files_properties(kernel/*.S PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

add_custom_target(${AARCH64_KERNEL_TARGET})

# compiling kernel code here
add_definitions(-D__KERNEL__)

### C sources ###

file(GLOB KERNEL_SOURCES	"kernel/*.c")
file(GLOB KERNEL_S_SOURCES	"kernel/*.S")
file(GLOB LIBKERN_S_SOURCES      "libkern/*.S")
file(GLOB MM_SOURCES		"mm/*.c")

add_library(${AARCH64_KERNEL_C_TARGET} OBJECT
	${KERNEL_SOURCES} ${KERNEL_S_SOURCES} ${MM_SOURCES} ${LIBKERN_S_SOURCES})

target_include_directories(${AARCH64_KERNEL_C_TARGET} BEFORE
	PUBLIC ${HERMIT_KERNEL_INCLUDES}
	PRIVATE ${GENERATED_CONFIG_DIR})

target_compile_options(${AARCH64_KERNEL_C_TARGET}
	PRIVATE ${HERMIT_KERNEL_FLAGS})
