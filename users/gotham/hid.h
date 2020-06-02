#pragma once

#include "raw_hid.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define CHUNK_SIZE 16
#define OLED_BUFFER_SIZE 128
#define COMMAND_SIZE sizeof(uint8_t)

enum {
    UNKNOWN = 0,
    OLED_START,
    OLED_IN,
    OLED_STOP,
    OLED_CLEAR,
    _COMMAND_LENGTH,
};

typedef struct {
    char *  data;
    uint8_t size;
    uint8_t cursor;
} hid_buffer_t;

uint8_t      hid_command;
hid_buffer_t hid_oled_buffer;
bool         custom_hid_init_complete;
bool         oled_render_ready;

void    hid_buffer_init(hid_buffer_t *ptr, size_t size);
void    custom_hid_init(void);
void    read_data(uint8_t *data, uint8_t length, hid_buffer_t *buffer);
uint8_t get_command(uint8_t *data, uint8_t length);
void    read_oled_data(uint8_t *data, uint8_t length);
void    clear_oled_buffer(void);
void    handle_rx(uint8_t *data, uint8_t length);
