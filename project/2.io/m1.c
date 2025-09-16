#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define len 26
#define unit 250
#define getmorse(i) ((buffer[i]>96) ? (buffer[i] - 97) : (buffer[i] - 65))
typedef unsigned int u32;
typedef unsigned char u8;

u8 txt[len] = {0b01000001,0b10001000,0b10001010,0b01100100,0b00100000,0b10000010,0b01100110,0b10000000,0b01000000,0b10000111,0b01100101,0b10000100,0b01000011,0b01000010,0b01100111,0b10000110,0b10001101,0b01100010,0b01100000,0b00100001,0b01100001,0b10000001,0b01100011,0b10001001,0b10001011,0b10001100};

int pico_led_init(void){
	return cyw43_arch_init();
}
void pico_set_led(bool led_on){
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

void blink(u32 n){
	pico_set_led(true);
	sleep_ms(n);
	pico_set_led(false);
	sleep_ms(unit);
}

void prnt(u8 x, u8 y){
	u8 shift = y-1;
	while(y>0){
		if((1<<shift) & x){
			blink(unit*3);
			printf("_");
		}else{
			blink(unit);
			printf(".");
		}
		shift -= 1;
		y -= 1;
	}
	printf("\n");
}

u32 main(){
	stdio_init_all();
	pico_led_init();

	u8 buffer[20] = "";
	while(1){
		printf("ascii input for morse conversioin\n");
		scanf("%s",buffer);
		sleep_ms(unit*3);
		printf("blinking for %s\n",buffer);
		int i = 0;
		while(buffer[i]!='\0'){
			printf("(%c)",buffer[i]);
			prnt(txt[getmorse(i)],(txt[getmorse(i)]>>5));
			sleep_ms(unit*4);
			i += 1;
		}
	}
}
