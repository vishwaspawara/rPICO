#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#define len 1000

int num[len] = {};

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

void init(int n){
	int i = 0;
	printf("Enter %d inputs\n",n);
	while(n>0){
		scanf("%d",&num[i]);
		printf("%d\n",num[i]);
		i += 1;
		n -= 1;
	}
}
void sort(int a[], int n){
	if(n>1){
	int elt = a[0];
	int i = 1;
	int j = n-1;
		while(i<=j){
			if(a[i] <= elt){
				a[i-1] = a[i];
				i += 1;
			}else if(a[i] > elt){
				int tmp = a[j];
				a[j] = a[i];
				a[i] = tmp;
				j -= 1;
			}
		}
		a[i-1] = elt;
		sort(a,i-1);
		sort(a+i,n-i);
	}
}
void prnt(int n){
	int i = 0;
	printf("sorted inputs - \n");
	while(i<n){
		printf("%d\n",num[i]);
		i += 1;
	}
	printf("\n\n");
}
int gettotal(){
    int t;
    while(1){
        printf("Enter total numbers:\n");
        if(scanf(("%d", &t) == 1) && t > 0){
            return t;
        }else{
            printf("Invalid input! Please enter a number.\n");
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void main(){
	stdio_init_all();
	pico_led_init();
	blink(200,200);
	sleep_ms(2000);
	int tw;

	while(1){
		printf("\nstarting over\n\n");
		sleep_ms(3000);
		tw=gettotal();

		init(tw);
		blink(200,200);
		sort(num,tw);
		blink(200,200);
		prnt(tw);
	}
}
