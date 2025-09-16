#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define ckbit ((1<< shift) & morse[i])
#define LED_DELAY_MS 250

int pico_led_init(void) {
	return cyw43_arch_init();
}

void pico_set_led(bool led_on) {
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

int main() {
	stdio_init_all();
	int i=0;
	int flag=i;
	int rc = pico_led_init();
	hard_assert(rc == PICO_OK);
	while (true){
		if(flag==0){
			printf("enter number\n");
			scanf("%d",&i);
			flag=1;
		}
		if(flag==1){
			int k = i;
			while(i>0){
				pico_set_led(true);
				printf("blink no:%d\n",i);
				sleep_ms(200);
				pico_set_led(false);
				sleep_ms(200);
				i -= 1;
			}
			printf("square of latest number %d is %d\n",k,k*k);
			sleep_ms(2000);
			flag=0;
		}else{
			printf("messed up\n");
			sleep_ms(2000);
		}
	}
}
