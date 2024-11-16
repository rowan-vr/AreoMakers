#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c/ht16k33.h"
#include "handlers/buttons.h"
#include "spi/mcp3008.h"

HT16K33 display;
MCP3008 potentiometers;

int main()
{
    stdio_init_all();

    // Initialize I2C
    i2c_init(i2c0, 100*1000); // ?? 100kHz ??
    gpio_set_function(0, GPIO_FUNC_I2C);
    gpio_set_function(1, GPIO_FUNC_I2C);
    gpio_pull_up(0);
    gpio_pull_up(1);

    display = ht16k33_create(i2c0, 0x70);
    // Initialize button handler
    init_buttons();

    // Initialize potentionmeters
    potentiometers = mcp3008_create(spi0, 2, 4, 3, 5);

    uint64_t tick = 0;
    while (true)
    {
        if (tick % 2 == 0) {
            mcp3008_interrupt(&potentiometers);
        }
        tick++;
        if (tick >= 100) {
            tick = 0;
        }
        sleep_ms(100);
    }

    return 0;
}
