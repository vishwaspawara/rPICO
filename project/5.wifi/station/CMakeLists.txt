cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(wifi C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(station
        station.c
        )

pico_enable_stdio_usb(station 1)
pico_enable_stdio_uart(station 0)
target_include_directories(station PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/..
        )

target_link_libraries(station
        pico_cyw43_arch_lwip_threadsafe_background
        pico_stdlib
        )
pico_add_extra_outputs(station)

