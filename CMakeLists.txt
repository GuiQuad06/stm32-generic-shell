cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME shell1)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Enable CTest
include(CTest)
enable_testing()

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME}
    Core/Src/handlers.c
)

add_executable(test_shell
    Core/Src/handlers.c
    tests/test_shell.c
    tests/unity/unity.c
    startup_stm32f302x8.s
    Core/Src/system_stm32f3xx.c
)

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

add_subdirectory(Shell)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Files syscalls.c and sysmem.c conflict with Semihosting
# This prevents them from being compiled by treating them as header-only
set_source_files_properties(
        ${CMAKE_SOURCE_DIR}/stm32f302r8-test/Core/Src/syscalls.c
        ${CMAKE_SOURCE_DIR}/stm32f302r8-test/Core/Src/sysmem.c
        PROPERTIES HEADER_FILE_ONLY ON
)

# Required link option for semihosting to work correctly
target_link_options(test_shell PRIVATE -specs=rdimon.specs -lc -lrdimon)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    shell
)

target_link_libraries(test_shell
    stm32cubemx
    shell
)

#Utilities search
FIND_PROGRAM(QEMU_BINARY
    NAMES qemu-system-arm
    HINTS "C:/tools/qemu/" "C:/Program Files/qemu/"
)

FIND_PROGRAM(OPENOCD_BINARY
    NAMES openocd
    HINTS "C:/dev/openocd-v0.12.0-i686-w64-mingw32/bin/" "C:/Program Files/openocd/"
)

# Register the qemu tests with CTest
add_test(NAME unity_test_shell
    COMMAND ${QEMU_BINARY}
    -machine olimex-stm32-h405
    -nographic
    -semihosting
    -semihosting-config enable=on,target=native
    -serial mon:stdio
    -kernel $<TARGET_FILE:test_shell>
)

add_test(NAME unity_test_shell_hw
    COMMAND ${OPENOCD_BINARY}
    -f interface/stlink-v2-1.cfg
    -f target/stm32f3x.cfg
    -c "init"
    -c "arm semihosting enable"
    -c "arm semihosting_resexit enable"
    -c "program $<TARGET_FILE:test_shell> verify"
    -c "reset init"
    -c "resume"
)

set_tests_properties(
    unity_test_shell_hw
    unity_test_shell
    PROPERTIES
    FAIL_REGULAR_EXPRESSION ":FAIL"
    PASS_REGULAR_EXPRESSION ":PASS"
    TIMEOUT 20
)
