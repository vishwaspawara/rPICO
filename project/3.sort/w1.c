#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

typedef unsigned int* u32; 
#define len 1024*1024-1
#define ms *((u32)&mem[len-4]) 		//starting index of alphabetically minimum word
#define cs *((u32)&mem[len-8])		//starting index of current word being compared with minimum
#define cc *((u32)&mem[len-12])		//current character being compared 
#define tw *((u32)&mem[len-16])		//total words 
#define cntdws *((u32)&mem[len-20])	//counted words shows how many words have been looked so far to find minimum
#define srtdws *((u32)&mem[len-24])	//storted words
#define str *((u32)&mem[len-28])	//points to where to store the answer index 

#define R32(x) *((u32)&mem[x])		//to access 4bytes 


int pico_led_init(){
	return cyw43_arch_init();
}
void pico_set_led(bool led_on){
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

unsigned char mem[len] = " how to find minimum word? 1. the first unsorted word will be defacto minimum till that point. 2. set current word to ms+1, which wont be on space, then find second unsorted word. now we have two word to compare- compare first character of both the words, only if current word is smaller then only we need to change the index. repeat till all word have been looked at. any biiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiig word will be sorted. the quick brown fox jumps over lazy dog ";

int main(){
	while(true){

		pico_set_led(true);
		sleep_ms(2000);
		pico_set_led(false);
		tw = 83;
		srtdws = 0;
		str = len-32;		//starting point of storing location 

		while (srtdws<tw){

			ms = cs = cc = cntdws = 0;
			//find first unsorted word which will be minimum word till this point
			while (mem[cc] != 32){					
				if (mem[cc] == 9){
					cntdws+=1;
				}
				cc += 1;
			}
			ms = cc + 1; 
			cs = ms + 1;
			cc = 0;
			while (cntdws < tw){
				//find second unsorted word for comparison if it exists 
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
			//storing the index of alphabetically smallest word
			mem[ms-1] = 9;
			R32(str) = ms;
			str -= 4;
			srtdws += 1;
			pico_set_led(true);
			sleep_ms(200);
			pico_set_led(false);
			sleep_ms(200);
		}
		//printing the final result
		str = len-32;
		cntdws = cc = 0;
		while (cntdws < tw){
			while (mem[R32(str)+cc] != ' '&& mem[R32(str)+cc] != 9){
				printf("%c", mem[R32(str)+cc]);
				cc += 1;
			}
			printf("\n");
			cntdws += 1;
			str -= 4;
			cc = 0;
		}
	}
}
