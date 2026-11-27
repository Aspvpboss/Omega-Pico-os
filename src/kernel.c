#include "kernel/block_allocator.h"
#include <stdio.h>
#include <pico/stdio.h>
#include "kernel/kernel_const.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"

int kernel() {
    
    block_init_malloc();
    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while(1){

        void *mem = block_malloc(25000);
        printf("free memory: %d - allocated memory: %d\n", block_available_memory(), block_allocated_memory());
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        
        block_free(mem);
        printf("free memory: %d - allocated memory: %d\n", block_available_memory(), block_allocated_memory());
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        
    }

    return 0;
}
