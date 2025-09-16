#include <stdio.h>
#include <stdlib.h>

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/flash.h"
#include "hardware/flash.h"

int pico_led_init(void){
	return cyw43_arch_init();
}
void pico_set_led(bool led_on){
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}
void blink(int on){
	pico_set_led(true);
	sleep_ms(on);
	pico_set_led(false);
	sleep_ms(on);
}

void print_buf(const uint32_t *buf, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		printf("%00000002x", buf[i]);
		if (i % 32 == 31)
			printf("\n");
		else
			printf(" ");
	}
}
static void call_flash_range_erase(void *param) {
	uint32_t offset = (uint32_t)param;
	flash_range_erase(offset, FLASH_SECTOR_SIZE);
}
static void call_flash_range_program(void *param) {
	uint32_t offset = ((uintptr_t*)param)[0];
	const uint32_t *data = (const uint32_t *)((uintptr_t*)param)[1];
	flash_range_program(offset, data, FLASH_PAGE_SIZE);
}
void sort(uint32_t a[], uint32_t n){
	if(n>1){
		uint32_t elt = a[0];
		uint32_t i = 1;
		uint32_t j = n-1;
		while(i<=j){
			if(a[i]<=elt){
				a[i-1] = a[i];
				i += 1;
			}else if(a[i]>elt){
				uint32_t tmp = a[j];
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

int main() {
	stdio_init_all();
	pico_led_init();
	int n = 1;
	uint32_t offst = 256 * 1024 + n * FLASH_PAGE_SIZE;
	const uint32_t *flash_target_contents = (const uint32_t *) (XIP_BASE + offst);
	while(true){
		sleep_ms(5000);
		int a=0;
		while(a<5){
			blink(250);
			a += 1;
		}
		uint32_t random_data[FLASH_PAGE_SIZE];
		for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i){
			random_data[i] = rand();
		}

		printf("\nGenerated random data:\n");
		print_buf(random_data, FLASH_PAGE_SIZE);

		sort(random_data,FLASH_PAGE_SIZE);
		printf("\nsorted the data:\n");

		printf("\nErasing target region...\n");

		int rc = flash_safe_execute(call_flash_range_erase, (void*)offst, UINT32_MAX);
		hard_assert(rc == PICO_OK);

		printf("\nDone. Read back target region:\n");
		print_buf(flash_target_contents, FLASH_PAGE_SIZE);

		printf("\nProgramming target region...\n");
		uintptr_t params[] = { offst, (uintptr_t)random_data};
		rc = flash_safe_execute(call_flash_range_program, params, UINT32_MAX);
		hard_assert(rc == PICO_OK);
		printf("\nDone. Read back target region:\n");
		print_buf(flash_target_contents, FLASH_PAGE_SIZE);

		bool mismatch = false;
		for (uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i) {
			if (random_data[i] != flash_target_contents[i])
				mismatch = true;
		}
		if (mismatch){
			printf("Programming failed!\n");
		}else{
			printf("\nProgramming successful!\n");
		}
		n += 1;
		if (n>5){
			n = 1;
			printf("\n\n\nn\n\n\n");
		}
	}
}
