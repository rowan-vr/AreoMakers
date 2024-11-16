#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c/ht16k33.h"
#include "handlers/buttons.h"

#define DISP_PORT i2c0
#define DISP_ADDR 0x70 

#define SDA_PIN 0
#define SCL_PIN 1

HT16K33 device;

int main()
{
    stdio_init_all();

    // Initialize I2C
    i2c_init(DISP_PORT, 9600); // ?? 100kHz ??
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Initialize button handler
    
    device = ht16k33_create(DISP_PORT, DISP_ADDR);
    init_buttons();


    while (true)
    {
        tight_loop_contents();
    }

    return 0;
}
