#include <string.h>

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "dhcpserver.h"
#include "dnsserver.h"

typedef struct TCP_SERVER_T_ {
    struct tcp_pcb *server_pcb;
    bool complete;
    ip_addr_t gw;
} TCP_SERVER_T;

int main() {
    stdio_init_all();
    TCP_SERVER_T *state = calloc(1, sizeof(TCP_SERVER_T));	//initialization of state
    cyw43_arch_init();						//cyw43 wifi hardware initialization

    const char *ap_name = "vish_pico"; 
    const char *password = "12345678vp"; //set to NULL if not required

    //enable access point
    cyw43_arch_enable_ap_mode(ap_name, password, CYW43_AUTH_WPA2_AES_PSK);

    #if LWIP_IPV6
    #define IP(x) ((x).u_addr.ip4)
    #else
    #define IP(x) (x)
    #endif
    ip4_addr_t mask;
    IP(state->gw).addr = PP_HTONL(CYW43_DEFAULT_IP_AP_ADDRESS);
    IP(mask).addr = PP_HTONL(CYW43_DEFAULT_IP_MASK);
    #undef IP

    //init dhcp and dns
    dhcp_server_t dhcp_server;
    dns_server_t dns_server;
    dhcp_server_init(&dhcp_server, &state->gw, &mask);
    dns_server_init(&dns_server, &state->gw);

    state->complete = false; 
    while(!state->complete) {
        cyw43_arch_poll();
        cyw43_arch_wait_for_work_until(make_timeout_time_ms(1000));
    }

    //cleanup
    dns_server_deinit(&dns_server);
    dhcp_server_deinit(&dhcp_server);
    cyw43_arch_deinit();
    printf("Test complete\n");
    return 0;
}
