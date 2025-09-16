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

void blink(int k){
	pico_set_led(true);
	sleep_ms(k);
	pico_set_led(false);
	sleep_ms(k);
}

int main() {
	stdio_init_all();
	pico_led_init();

	int k;
	while (true){
		pico_set_led(true);
		printf("enter number and count the blinks !!!\n");
		scanf("%d",&k);
		blink(250);
		sleep_ms(1000);
		while(k>0){
			printf("blink no %d\n",k);
			blink(600);
			k -= 1;
		}
		sleep_ms(1500);
	}
}
