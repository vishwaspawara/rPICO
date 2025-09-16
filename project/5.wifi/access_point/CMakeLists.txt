cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(wifi C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(ap_background
        ap.c
        dhcpserver/dhcpserver.c
        dnsserver/dnsserver.c
        )

pico_enable_stdio_usb(ap_background 1)
pico_enable_stdio_uart(ap_background 0)
target_include_directories(ap_background PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
        ${CMAKE_CURRENT_LIST_DIR}/dhcpserver
        ${CMAKE_CURRENT_LIST_DIR}/dnsserver
        )

target_link_libraries(ap_background
        pico_cyw43_arch_lwip_threadsafe_background
        pico_stdlib
        )
# You can change the address below to change the address of the access point
pico_configure_ip4_address(ap_background PRIVATE
        CYW43_DEFAULT_IP_AP_ADDRESS 192.168.4.1
        )
pico_add_extra_outputs(ap_background)

add_executable(ap_poll
        ap.c
        dhcpserver/dhcpserver.c
        dnsserver/dnsserver.c
        )
target_include_directories(ap_poll PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
        ${CMAKE_CURRENT_LIST_DIR}/dhcpserver
        ${CMAKE_CURRENT_LIST_DIR}/dnsserver
        )
target_link_libraries(ap_poll
        pico_cyw43_arch_lwip_poll
        pico_stdlib
        )
# You can change the address below to change the address of the access point
pico_configure_ip4_address(ap_poll PRIVATE
        CYW43_DEFAULT_IP_AP_ADDRESS 192.168.4.1
        )
pico_add_extra_outputs(ap_poll)
