#ifndef HT16K33_H
#define HT16K33_H

#include "hardware/i2c.h"  // Include for the I2C functionality

// Define a structure to represent the HT16K33 device
typedef struct {
    i2c_inst_t *i2c_port;   // I2C port (e.g., i2c0, i2c1)
    uint8_t address;        // I2C address of the HT16K33
} HT16K33;

// Function prototypes

/**
 * @brief Initializes the HT16K33 device.
 * 
 * Sets up the system (oscillator), display, and brightness.
 * 
 * @param device A pointer to the HT16K33 device structure.
 */
void ht16k33_init(HT16K33* device);

/**
 * @brief Displays data on the HT16K33 device.
 * 
 * Sends the given data to the display RAM of the HT16K33.
 * 
 * @param device A pointer to the HT16K33 device structure.
 * @param data The data to be displayed.
 * @param len The length of the data array.
 */
void ht16k33_display_data(HT16K33 *device, uint8_t *data, size_t len);

/**
 * @brief Creates and initializes an HT16K33 device instance.
 * 
 * @param i2c_port The I2C port to communicate with (e.g., i2c0, i2c1).
 * @param address The I2C address of the HT16K33 device.
 * 
 * @return An initialized HT16K33 device structure.
 */
HT16K33 ht16k33_create(i2c_inst_t* i2c_port, uint8_t address);

#endif // HT16K33_H
