cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(io C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(io
	m1.c
)

pico_enable_stdio_usb(io 1)
pico_enable_stdio_uart(io 0)

pico_add_extra_outputs(io)

target_link_libraries(io pico_stdlib)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(io pico_cyw43_arch_none)
endif()

