#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


int main() {
    stdio_init_all();
    cyw43_arch_init();
    const char *ap_name = "EloMOTO"; 
    const char *password = "123456789";

    cyw43_arch_enable_sta_mode();
    cyw43_arch_wifi_connect_timeout_ms(ap_name, password, CYW43_AUTH_WPA2_AES_PSK,10000);

    while(1){
	    printf("Hello \n");
    }

    cyw43_arch_deinit();
    return 0;
}
