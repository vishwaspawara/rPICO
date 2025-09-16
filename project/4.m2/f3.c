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

void print_buf(const uint8_t *buf, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		printf("%02x", buf[i]);
		if (i % 4 == 3)
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
	const uint8_t *data = (const uint8_t *)((uintptr_t*)param)[1];
	flash_range_program(offset, data, FLASH_PAGE_SIZE);
}
void sort(uint8_t a[], uint32_t n){
	if(n>1){
		uint8_t elt = a[0];
		uint32_t i = 1;
		uint32_t j = n-1;
		while(i<=j){
			if(a[i]<=elt){
				a[i-1] = a[i];
				i += 1;
			}else if(a[i]>elt){
				uint8_t tmp = a[j];
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

void validate(uint8_t random_data[], const uint8_t flash_target_contents[]){
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
}

int main() {
	stdio_init_all();
	pico_led_init();
	uint32_t offset = 256 * 1024;
	uint8_t buffer[FLASH_PAGE_SIZE];

	while(true){
		sleep_ms(5000);
		blink(1000);
		while(offset < 2 * 1024 * 1024){
			flash_safe_execute(call_flash_range_erase, (void *)offset, UINT32_MAX);
			uint32_t page_offset = 0;
			while(page_offset < FLASH_SECTOR_SIZE){
				for(uint32_t i = 0; i < FLASH_PAGE_SIZE; ++i){
					buffer[i] = rand() >> 16;
				}

				sort(buffer,FLASH_PAGE_SIZE);

				uintptr_t params[] = {offset + page_offset, (uintptr_t)buffer };
				flash_safe_execute(call_flash_range_program, params, UINT32_MAX);

				const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + offset + page_offset);
				printf("reading from %d (offset)\n",offset+page_offset);
				print_buf(flash_target_contents,FLASH_PAGE_SIZE);

				validate(buffer,flash_target_contents);

				page_offset += FLASH_PAGE_SIZE;

			}
			offset += FLASH_SECTOR_SIZE;
		}
	}
}
