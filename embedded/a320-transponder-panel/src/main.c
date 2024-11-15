#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c/ht16k33.h"

#define DISP_PORT i2c0
#define DISP_ADDR 0x70 

#define SDA_PIN 0
#define SCL_PIN 1


int main()
{
    stdio_init_all();

    // Initialize I2C
    i2c_init(DISP_PORT, 9600); // ?? 100kHz ??
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    HT16K33 device = ht16k33_create(DISP_PORT, DISP_ADDR);

    // // Initialize the HT16K33
    // ht16k33_init();

    uint8_t display_buffer[16] = {
        0b11111111, 0x00, // Digit 0 
        0b11111111, 0x00, // Digit 1 
        0xff, 0x00, // Digit 2 
        0b11111111, 0x00, // Digit 3 
        0b11111111, 0x00, // Digit 4
        0x00, 0x00, // Unused digits 
        0x00, 0x00, // Unused digits 
        0x00, 0x00  // Unused digits 
    };

    ht16k33_display_data(&device, display_buffer, 16);

    // Use the display data function to turn on all segments
    // ht16k33_display_data(display_buffer, 16);

    while (true)
    {
        tight_loop_contents();
    }

    return 0;
}
