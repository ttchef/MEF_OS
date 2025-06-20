
#ifndef MAILBOX_H
#define MAILBOX_H

#include "globals.h"

enum {
    MBOX_OFFSET = PERIPHERAL_BASE + 0xb880,
    
    MBOX0 = MBOX_OFFSET + 0x00,
    MBOX1 = MBOX_OFFSET + 0x20,

    MBOX0_STATUS = MBOX0 + 0x18,
    MBOX1_STATUS = MBOX1 + 0x18,

    MBOX_EMPTY = 1 << 30,
    MBOX_FULL = 1 << 31,

    MBOX_REQUEST = 0,
    MBOX_RESPONSE_SUCCESS = 0x80000000,
    MBOX_RESPONSE_PARSING_ERR = 0x80000001,
    
};

// Channels
enum {
    POWER_MANAGEMENT = 0,
    FRAMEBUFFER_CHANNEL = 1,
    VIRTUAL_UART = 2,
    VCHIQ = 3,
    LEDS = 4,
    BUTTONS = 5,
    TOUCH_SCREEN = 6,
    PROPERTY_TAG_ARM_GPU = 8,
    PROPERTY_TAG_GPU_ARM = 9
};

// Property Tags 
enum {
    END_TAG = 0,
    
    SET_SCREEN_SIZE = 0x00048003,
    SET_VIRTUAL_SCREEN_SIZE = 0x00048004,
    SET_DEPTH = 0x00048005,
    SET_VIRUTAL_OFFSET = 0x00048009,
    SET_PIXEL_ORDER = 0x0004800006, // RGB oder BGR


    GET_SCREEN_SIZE = 0x00040003,
    GET_VIRTUAL_SCREEN_SIZE = 0x00040004,
    GET_DEPTH = 0x00040005,
    GET_VIRTUAL_OFFSET = 0x00040009,
    GET_PIXEL_ORDER = 0x00040006,

    GET_PITCH = 0x00040008,

    FRAMEBUFFER = 0x00040001
};



unsigned int mbox_read(unsigned int channel);
void mbox_write(unsigned int data, unsigned int channel);

#endif

