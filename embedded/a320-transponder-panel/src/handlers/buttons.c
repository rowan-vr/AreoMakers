#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "i2c/ht16k33.h"

extern HT16K33 display;

uint8_t value[4] = {2, 0, 0, 0};

void display_squawk()
{
    uint8_t hexidecimal_displays[] = {
        0b00111111, // 0
        0b00000110, // 1
        0b01011011, // 2
        0b01001111, // 3
        0b01100110, // 4
        0b01101101, // 5
        0b01111101, // 6
        0b00000111  // 7
    };

    uint8_t disp_value[5] = {value[0], value[1], -1, value[2], value[3]};

    uint8_t buffer[10];
    for (int i = 0; i < 5; i++)
    {
        if (disp_value[i] < 0 || disp_value[i] >= 8)
        {
            buffer[i * 2] = 0x00;
        }
        else
        {
            buffer[i * 2] = hexidecimal_displays[disp_value[i]];
        }
        buffer[i * 2 + 1] = 0x00;
    }

    ht16k33_display_data(&display, buffer, 10);
}

void add_value(uint8_t new_value)
{
    printf("Adding %u\n", new_value);
    for (int i = 0; i < 4; i++)
    {
        if (value[i] == 8)
        {
            value[i] = new_value;
            display_squawk();
            return;
        }
    }
}

void remove_last_value()
{
    printf("Removing...\n");
    for (int i = 4 - 1; i >= 0; i--)
    {
        if (value[i] != 8)
        {
            value[i] = 8;
            display_squawk();
            return;
        }
    }
}

void button_1(uint gpio, uint32_t events) { add_value(1); }
void button_2(uint gpio, uint32_t events) { add_value(2); }
void button_3(uint gpio, uint32_t events) { add_value(3); }
void button_4(uint gpio, uint32_t events) { add_value(4); }
void button_5(uint gpio, uint32_t events) { add_value(5); }
void button_6(uint gpio, uint32_t events) { add_value(6); }
void button_7(uint gpio, uint32_t events) { add_value(7); }
void button_0(uint gpio, uint32_t events) { add_value(0); }
void button_clr(uint gpio, uint32_t events) { remove_last_value(); }
void button_ident(uint gpio, uint32_t events) { printf("Ident\n"); }

typedef struct
{
    uint gpio;
    gpio_irq_callback_t callback;
} ButtonKey;

ButtonKey buttons[] = {
    {16, button_1},
    {17, button_2},
    {18, button_3},
    {19, button_4},
    {20, button_5},
    {21, button_6},
    {22, button_7},
    {26, button_0},
    {27, button_clr},
    {28, button_ident}};

#define NUM_BUTTONS (sizeof(buttons) / sizeof(buttons[0]))

// Store the last interrupt time for each button
uint32_t last_interrupt_time[NUM_BUTTONS] = {0};

// Debounce delay in milliseconds
#define DEBOUNCE_DELAY_MS 200

void handle_button(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (buttons[i].gpio == gpio)
        {
            if (current_time - last_interrupt_time[i] > DEBOUNCE_DELAY_MS)
            {
                last_interrupt_time[i] = current_time;
                buttons[i].callback(gpio, events);
            }
            break;
        }
    }
}

void init_buttons()
{
    gpio_set_irq_enabled_with_callback(buttons[0].gpio, GPIO_IRQ_EDGE_FALL, true, handle_button);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        ButtonKey button = buttons[i];

        gpio_init(button.gpio);
        gpio_set_dir(button.gpio, GPIO_IN);
        gpio_pull_up(button.gpio);
        gpio_set_irq_enabled(button.gpio, GPIO_IRQ_EDGE_FALL, true);
    }

    display_squawk();
}
