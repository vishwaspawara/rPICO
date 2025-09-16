cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(m2 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(m2
        f5.c
        )

pico_enable_stdio_usb(m2 1)
pico_enable_stdio_uart(m2 0)

target_link_libraries(m2
        pico_stdlib
        hardware_flash
	pico_cyw43_arch_none
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(m2)

