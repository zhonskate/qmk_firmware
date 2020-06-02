#include "hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // raw_hid_send(data, length);
    if (custom_hid_init_complete) handle_rx(data, length);
}

void hid_buffer_init(hid_buffer_t *ptr, size_t size) {
    ptr->cursor = 0;
    ptr->size   = size;
    ptr->data   = malloc(size * sizeof(uint8_t));
}

void custom_hid_init(void) {
    hid_buffer_init(&hid_oled_buffer, OLED_BUFFER_SIZE);
    oled_render_ready        = false;
    custom_hid_init_complete = true;
}

void read_data(uint8_t *data, uint8_t length, hid_buffer_t *buffer) {
    if (length > CHUNK_SIZE) {
        length = CHUNK_SIZE;
    }
    --length;  // Skip command byte
    size_t readLength    = CHUNK_SIZE - 1;
    size_t remainingSize = buffer->size - buffer->cursor;
    if (remainingSize < readLength) {
        readLength = remainingSize;
    }
    if (readLength > length) {
        readLength = length;
    }
    uint8_t srcIndex = 1;
    while (readLength-- > 0) {
        buffer->data[buffer->cursor++] = (char)data[srcIndex++];
        if ((srcIndex > length) || (buffer->cursor == buffer->size - 1)) {
            break;
        }
    }

    // memcpy(&buffer->data[buffer->cursor], &data[1], readLength * sizeof(uint8_t));
}

uint8_t get_command(uint8_t *data, uint8_t length) {
    if (length < 1 || data[0] >= _COMMAND_LENGTH) {
        return UNKNOWN;
    } else {
        return data[0];
    }
}

void clear_oled_buffer(void) {
    for (uint8_t i = 0; i < hid_oled_buffer.size; i++) {
        hid_oled_buffer.data[i] = 0;
    }
    hid_oled_buffer.cursor = 0;
}

void read_oled_data(uint8_t *data, uint8_t length) { read_data(data, length, &hid_oled_buffer); }

void handle_rx(uint8_t *data, uint8_t length) {
    uint8_t newCommand = get_command(data, length);
    switch (newCommand) {
        case UNKNOWN:
            // raw_hid_send((uint8_t*)"handle_rx: Unknown", length);
            break;
        case OLED_START:
            // raw_hid_send((uint8_t*)"handle_rx: Oled Start", length);
            clear_oled_buffer();
            break;
        case OLED_IN:
            // raw_hid_send((uint8_t*)"handle_rx: Oled In", length);
            read_oled_data(data, length);
            break;
        case OLED_STOP:
            // raw_hid_send((uint8_t*)"handle_rx: Oled Stop", length);
            oled_render_ready = true;
            break;
        case OLED_CLEAR:
            clear_oled_buffer();
            oled_render_ready = true;
            // raw_hid_send((uint8_t*)"handle_rx: Oled Clear", length);
            break;
        default:
            // raw_hid_send((uint8_t*)"handle_rx: ??????", length);
            break;
    }
}
