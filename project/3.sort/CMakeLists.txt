cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(sort C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(sort
	n2.c
)

pico_enable_stdio_usb(sort 1)
pico_enable_stdio_uart(sort 0)

pico_add_extra_outputs(sort)

target_link_libraries(sort pico_stdlib)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(sort pico_cyw43_arch_none)
endif()

