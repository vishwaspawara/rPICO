#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#define len 255
#define wrdlen mem[len-1]
#define ms mem[len-2]
#define cs mem[len-3]
#define cc mem[len-4]
#define tw mem[len-5]
#define cntdws mem[len-6]
#define srtdws mem[len-7]
#define str mem[len-10]

unsigned char mem[len] = " ";

int pico_led_init(){
	return cyw43_arch_init();
}
void pico_set_led(bool led_on){
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}
void blink(int on, int off){
	pico_set_led(true);
	sleep_ms(on);
	pico_set_led(false);
	sleep_ms(off);
}
void insertwrds(){
}
void init(){
	printf("star over\n");
	scanf("%d",&tw);
	printf("enter total words\n");
	scanf("%d",&tw);
	blink(200,2000);
	blink(200,2000);
	insertwrds();
}
void compare(){
	while (cntdws < tw){
		//find second unsorted word if it exists
		if (cs == ms+1 || mem[cs-1] == 9){
			while (mem[cs+cc] != 32 && mem[cs+cc] != 9){
				cc += 1;
			}
			cs = cs + cc + 1;
			cc = 0;						
			cntdws += 1;
			//comparison if needed
		}else if(cs != ms+1 && mem[cs-1] == ' '){
			while (mem[cs+cc] == mem[ms+cc] && mem[cs+cc] != ' ' && mem[cs+cc] != 9){
				cc += 1;
			}
			if (mem[cs+cc] < mem[ms+cc]){
				ms = cs;
			}
			while (mem[cs+cc] != ' ' && mem[cs+cc] != 9){
				cc += 1;
			}
			cs = cs + cc +1;
			cc = 0;
			cntdws += 1;
		}
	}
}
void sort(){
	tw = 33;
	ms = 0; cs = 0; cc = 0; cntdws = 0; wrdlen = 0; srtdws = 0;
	str = len-11;
	while (srtdws<tw){
		ms = cs = cc = cntdws = wrdlen = 0;
		//find first unsorted word
		while (mem[cc] != 32){					
			if (mem[cc] == 9){
				cntdws+=1;
			}
			cc += 1;
		}
		ms = cc + 1; 
		cs = ms + 1;
		cc = 0;

		compare();

		//storing the minimum
		mem[ms-1] = 9;
		mem[str] = ms;
		str -= 1;
		srtdws += 1;
	}
}

int prnt(){
	printf("Words in alphabetical order\n\n");
	str = len-11;
	cntdws = cc = 0;
	while (cntdws < tw){
		mem[mem[str]-1] = ' ';
		while (mem[mem[str]+cc] != ' '&& mem[mem[str]+cc] != 9){
			printf("%c", mem[mem[str]+cc]);
			cc += 1;
		}
		printf("\n");
		cntdws += 1;
		str -= 1;
		cc = 0;
	}
}

void main(){
	stdio_init_all();
	pico_led_init();
	while(1){
		init();
		sort();
		printf("printing result\n");
		prnt();
	}
}

