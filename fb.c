
#include "fb.h"
#include "mb.h"
#include "io.h"

volatile unsigned int __attribute__((aligned(16))) mbox[30];
unsigned int* framebuffer;
unsigned int pitch;

// return 1 if error
unsigned int check_mailbox_response() {
    if (mbox[1] != MBOX_RESPONSE_SUCCESS) {
        if (uart_init_v && mbox[1] == 0) {
        uart_write_text("[ERROR] Mailbox Sending Failed!", UART_NEW_LINE);
        uart_write_text("[DEBUG] Mailbox Code: ", UART_NONE);
        uart_write_uint(mbox[1], UART_NEW_LINE);
        }

        else if (uart_init_v && mbox[1] == MBOX_RESPONSE_PARSING_ERR) {
        uart_write_text("[ERROR] Mailbox Sending Failed Parsing Error!", UART_NEW_LINE);
        uart_write_text("[DEBUG] Mailbox Code: ", UART_NONE);
        uart_write_uint(mbox[1], UART_NEW_LINE);

        }
        return 1;
    }
    return 0;
}

void frame_buffer_init() {

    uart_write_text("[DEBUG] Framebuffer Beginning!", UART_NEW_LINE);

    // Set Screen properties 
    mbox[0] = 30*4;
    mbox[1] = 0;

    mbox[2] = SET_SCREEN_SIZE;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 1920;
    mbox[6] = 1080;

    mbox[7] = SET_VIRTUAL_SCREEN_SIZE;
    mbox[8] = 8;
    mbox[9] = 0;
    mbox[10] = 1920;
    mbox[11] = 1080;

    mbox[12] = SET_DEPTH;
    mbox[13] = 4;
    mbox[14] = 0;
    mbox[15] = 32;

    mbox[16] = SET_VIRUTAL_OFFSET;
    mbox[17] = 8;
    mbox[18] = 0;
    mbox[19] = 0;
    mbox[20] = 0;

    mbox[21] = GET_PITCH;
    mbox[22] = 4;
    mbox[23] = 0;
    mbox[24] = 0;

    mbox[25] = END_TAG;

    // Padding
    mbox[26] = 0; mbox[27] = 0; mbox[28] = 0; mbox[29] = 0;

    uart_write_text("[DEBUG] Framebuffer before Write!", UART_NEW_LINE);

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    check_mailbox_response();

    uart_write_text("[DEBUG] Mailbox Code: ", UART_NONE);
    uart_write_uint(mbox[1], UART_NEW_LINE);

    uart_write_text("[DEBUG] Pitch: ", UART_NONE);
    uart_write_uint(mbox[24], UART_NEW_LINE);
    pitch = mbox[24];
    
    mbox[0] = 8*4;
    mbox[1] = 0;

    mbox[2] = FRAMEBUFFER;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 16;
    mbox[6] = 0;

    mbox[7] = END_TAG;

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    check_mailbox_response();

    uart_write_text("[DEBUG] Framebuffer: ", UART_NONE);
    uart_write_uint(mbox[5], UART_NEW_LINE);
    framebuffer = (unsigned int*)(mbox[5] & ~0xC0000000);

    uart_write_text("[DEBUG] Framebuffer Size: ", UART_NONE);
    uart_write_uint(mbox[6], UART_NEW_LINE);


    uart_write_text("[DEBUG] FB Init finish!", UART_NEW_LINE);
}


