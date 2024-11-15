#include "hardware/i2c.h"

// Define a structure to represent the HT16K33 device
typedef struct {
    i2c_inst_t *i2c_port;  // I2C port
    uint8_t address;       // I2C address of the HT16K33
} HT16K33;



void ht16k33_init(HT16K33* device) {
    // System setup (turn on oscillator)
    uint8_t system_setup[1] = {0x21}; // Command: 0b00100001 (enable oscillator)
    i2c_write_blocking(device->i2c_port, device->address, system_setup, 1, false);

    // Display setup (turn on display, no blinking)
    uint8_t display_setup[1] = {0b10000001}; // Command: 0b10000001 (display on, no blink)
    i2c_write_blocking(device->i2c_port, device->address, display_setup, 1, false);

    // Set brightness to max
    uint8_t brightness[1] = {0b11101111}; // Command: 0b11101111 (brightness 15/15)
    i2c_write_blocking(device->i2c_port, device->address, brightness, 1, false);
}

void ht16k33_display_data(HT16K33 *device, uint8_t *data, size_t len)
{
    // HT16K33 display RAM starts at address 0x00
    uint8_t buffer[len + 1];
    buffer[0] = 0x00; // Start address for display data
    for (size_t i = 0; i < len; i++)
    {
        buffer[i + 1] = data[i];
    }

    // Write data to HT16K33
    i2c_write_blocking(device->i2c_port, device->address, buffer, len + 1, false);
}

HT16K33 ht16k33_create(i2c_inst_t* i2c_port, uint8_t address)
{
    HT16K33 device = {
        .i2c_port = i2c_port,
        .address = address,
    };

    ht16k33_init(&device);
    return device;
}