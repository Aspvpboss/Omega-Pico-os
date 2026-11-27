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
        printf("%x: %d\n", __end__, __HeapLimit - __end__);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
    }

    return 0;

    return 0;
}
