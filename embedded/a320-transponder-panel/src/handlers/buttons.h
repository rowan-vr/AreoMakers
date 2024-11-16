#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "pico/stdlib.h"
#include "i2c/ht16k33.h"

extern HT16K33 device;

// Declare the function prototypes for button callbacks
void button_1(uint gpio, uint32_t events);
void button_2(uint gpio, uint32_t events);
void button_3(uint gpio, uint32_t events);
void button_4(uint gpio, uint32_t events);
void button_5(uint gpio, uint32_t events);
void button_6(uint gpio, uint32_t events);
void button_7(uint gpio, uint32_t events);
void button_0(uint gpio, uint32_t events);
void button_clr(uint gpio, uint32_t events);
void button_ident(uint gpio, uint32_t events);

// Define the ButtonKey structure
typedef struct {
    uint gpio;                  // GPIO pin for the button
    gpio_irq_callback_t callback;  // Callback function for the interrupt
} ButtonKey;

// Declare the button array with GPIO pins and their associated callback functions
extern ButtonKey buttons[];

// Define the number of buttons in the buttons array
#define NUM_BUTTONS (sizeof(buttons) / sizeof(buttons[0]))

// Function prototype for initializing the buttons
void init_buttons(void);

#endif // BUTTON_HANDLER_H
