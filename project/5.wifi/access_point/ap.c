#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "dhcpserver.h"
#include "dnsserver.h"

int main() {
    stdio_init_all();
    cyw43_arch_init();
    ip_addr_t gw;

    const char *ap_name = "vish_pico"; 
    const char *password = "12345678vp";

    cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);

    #define IP(x) (x)
    ip4_addr_t mask;
    IP(gw).addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    IP(mask).addr = PP_HTONL(CYW43_DEFAULT_IP_MASK);

    dhcp_server_t dhcp_server;
    dns_server_t dns_server;
    dhcp_server_init(&dhcp_server, &gw, &mask);
    dns_server_init(&dns_server, &gw);

    while(1);

    dns_server_deinit(&dns_server);
    dhcp_server_deinit(&dhcp_server);
    cyw43_arch_deinit();
    return 0;
}
