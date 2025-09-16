#include<stdio.h>
#include "pico/stdlib.h"
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#define ckbit ((1<< shift) & morse[i])
#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
	return cyw43_arch_init();
#endif
}

void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
	gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

void lightit(int on, int off){
			pico_set_led(true);
			sleep_ms(on);
			pico_set_led(false);
			sleep_ms(off);
}

int main() {
	stdio_init_all();
	int morse[3] = {0b11111111,0b10101010,0b00001011};
	int i = 0;
	int shift = 7;
	int rc = pico_led_init();
	hard_assert(rc == PICO_OK);
	while (true) {
		if(ckbit){
			printf("1");
			lightit(LED_DELAY_MS*3,LED_DELAY_MS);
		}else{
			printf("0");
			lightit(LED_DELAY_MS,LED_DELAY_MS*3);
		}
	
		if(shift == 0){
			shift = 7;
			i += 1;
			printf("\n");
			if(i>2){
				i = 0;
				printf("...\n");
			}
			sleep_ms(LED_DELAY_MS*7);
		}else{
			shift -= 1;
		}
	}
}
