
#include "fb.h"
#include "mb.h"
#include "io.h"
#include "globals.h"
#include "memory.h"
#include "utils.h"

volatile unsigned int __attribute__((aligned(16))) mbox[30];
u64* fb_buffer1;
u64* fb_buffer2;
u32 fb_size;

// DEBUG
u32 parse_main_message();
u32 check_mailbox_overall();
void validate_framebuffer();
void test_virtual_heights();
u32 parse_mailbox_message(u32 size);

// Getters & Setters
void set_virtual_offset(u32 x, u32 y);
Vec2 get_virtual_offset();

Vec2 get_virtual_screen_dimensions();


void frame_buffer_init() {

    uart_write_text("[DEBUG] Framebuffer Beginning!", UART_NEW_LINE);

    // Set Screen properties 
    mbox[0] = 35*4;
    mbox[1] = 0;

    mbox[2] = SET_SCREEN_SIZE;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = SCREENWIDTH;
    mbox[6] = SCREENHEIGHT;

    mbox[7] = SET_VIRTUAL_SCREEN_SIZE;
    mbox[8] = 8;
    mbox[9] = 8;
    mbox[10] = VIRTUAL_SCREENWIDTH;
    mbox[11] = VIRTUAL_SCREENHEIGHT;

    mbox[12] = SET_DEPTH;
    mbox[13] = 4;
    mbox[14] = 4;
    mbox[15] = DEPTH;

    mbox[16] = SET_VIRUTAL_OFFSET;
    mbox[17] = 8;
    mbox[18] = 8;
    mbox[19] = 0;
    mbox[20] = 0;

    mbox[21] = GET_PITCH;
    mbox[22] = 4;
    mbox[23] = 0;
    mbox[24] = 0;

    mbox[25] = FRAMEBUFFER;
    mbox[26] = 8;
    mbox[27] = 0;
    mbox[28] = 16;
    mbox[29] = 0;


    mbox[30] = END_TAG;

    // Padding
    mbox[31] = 0; mbox[32] = 0; mbox[33] = 0; mbox[34] = 0;

    uart_write_text("[DEBUG] Framebuffer before Write!", UART_NEW_LINE);

    parse_mailbox_message(35);

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);

    parse_mailbox_message(35);

    if (check_mailbox_overall()) {
        return;
    }

    uart_write_text("[DEBUG] Mailbox Code: ", UART_NONE);
    uart_write_uint(mbox[1], UART_NEW_LINE);

    uart_write_text("[DEBUG] Pitch: ", UART_NONE);
    uart_write_uint(mbox[24], UART_NEW_LINE);

    uart_write_text("[DEBUG] Virtual Height Response: ", UART_NONE);
    uart_write_uint(mbox[11], UART_NEW_LINE);

    if (mbox[11] != 2160) {
        uart_write_text("[WARNING] Virtual height not set to 2160!", UART_NEW_LINE);
        uart_write_text("[WARNING] Using returned value: ", UART_NONE);
        uart_write_uint(mbox[11], UART_NEW_LINE);
    }

    pitch = mbox[24];
    num_pixels = SCREENWIDTH*SCREENHEIGHT;

    // Framebuffer 
    uart_write_text("[DEBUG] Framebuffer: ", UART_NONE);
    uart_write_uint(mbox[28], UART_NEW_LINE);
    framebuffer = (u64*)BUS_ADDRESS(mbox[28]);


    fb_buffer1 = framebuffer;
    fb_buffer2 = framebuffer + (SCREENWIDTH*SCREENHEIGHT)/2;

    uart_write_text("[DEBUG] Framebuffer Size: ", UART_NONE);
    uart_write_uint(mbox[29], UART_NEW_LINE);
    fb_size = mbox[29];

    // VIRTUAL SCREEN DIMENSIONS
    
    uart_write_text("[DEBUG] Vitrual Screendimensions: ", UART_NONE);
    uart_write_uint(mbox[10], UART_NONE);
    uart_write_text(" | ", UART_NONE);
    uart_write_uint(mbox[11], UART_NEW_LINE);

    if (mbox[9] == MBOX_RESPONSE_SUCCESS + 8) {
        uart_write_text("[DEBUG] Virtual Screenresolution set successfully", UART_NEW_LINE);
    } else if (mbox[9] == 8) {
        uart_write_text("[ERROR] Failed setting virtual screenresolution", UART_NEW_LINE);
    } else if (mbox[9] == 0) {
        uart_write_text("[ERROR] Failed virual screenresolution == 0", UART_NEW_LINE);
    } else {
        uart_write_text("[ERROR] Set Virtual Screenresolution mbox[9] == ", UART_NONE);
        uart_write_uint(mbox[9], UART_NEW_LINE);
    }

    // -------------


    /*

    // Create front and backbuffer
    fb_buffer1 = (u32*)&__heap_start;

    u64 heap_start_addr = (u64)&__heap_start;
    u64 heap_end_addr = (u64)&__heap_end;

    if (heap_start_addr + fb_size < heap_end_addr) {
        fb_buffer2 = (u32*)(heap_start_addr + fb_size);
    } 
    else {
        uart_write_text("[ERROR] Not enough Space in Heap to store framebuffers!", UART_NEW_LINE);
    }

    */

    uart_write_text("[DEBUG] HEAP_SIZE: ", UART_NONE);
    uart_write_uint(HEAP_SIZE, UART_NEW_LINE);

    uart_write_text("[DEBUG] FB_1 Address: ", UART_NONE);
    uart_write_uint((u64)fb_buffer1 , UART_NEW_LINE);

    uart_write_text("[DEBUG] FB_2 Address: ", UART_NONE);
    uart_write_uint((u64)fb_buffer2 , UART_NEW_LINE);


    uart_write_text("[DEBUG] FB Init finish!", UART_NEW_LINE);

    validate_framebuffer();

}


void set_virtual_offset(u32 x, u32 y) {
    mbox[0] = 8*4;
    mbox[1] = 0;
        
    mbox[2] = SET_VIRUTAL_OFFSET;
    mbox[3] = 8;
    mbox[4] = 8;
    mbox[5] = x;
    mbox[6] = y;

    mbox[7] = END_TAG;

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    
    parse_mailbox_message(8);

    if (check_mailbox_overall()) {
        return;
    }

}

Vec2 get_virtual_offset() {

    mbox[0] = 8*4;
    mbox[1] = 0;

    mbox[2] = GET_VIRTUAL_OFFSET;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 0;
    mbox[6] = 0;
    
    mbox[7] = END_TAG;

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    
    parse_mailbox_message(8);

    if (check_mailbox_overall()) {
        return (Vec2){0,0};
    }


    return (Vec2){mbox[5], mbox[6]};

}

Vec2 get_virtual_screen_dimensions() {
    mbox[0] = 8*4;
    mbox[1] = 0;

    mbox[2] = GET_VIRTUAL_SCREEN_SIZE;
    mbox[3] = 8;
    mbox[4] = 0;
    mbox[5] = 0;
    mbox[6] = 0;

    mbox[7] = END_TAG;

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    
    parse_mailbox_message(8);

    if (check_mailbox_overall()) {
        return (Vec2){0,0};
    }

    return (Vec2){mbox[5], mbox[6]};

}

u32 parse_mailbox_message(u32 size) {

    u32 i = 0;
    uart_write_text("\n\n\n[DEBUG] Begin parsing message\n[DEBUG] Message Size: ", UART_NONE);
    uart_write_uint(size, UART_NEW_LINE);
    uart_write_text("Address of I: ", UART_NONE);
    uart_write_uint((u64)&i, UART_NEW_LINE);

    // Space
    uart_write_text("\n", UART_NONE);

    for (; i < size; i++) {
        uart_write_text("[DEBUG] mbox[", UART_NONE);
        uart_write_uint(i, UART_NONE);
        uart_write_text("] == ", UART_NONE);
        uart_write_uint(mbox[i], UART_NONE);
        uart_write_text("\n", UART_NONE);
    }

    uart_write_text("\n[DEBUG] Finished parsing message!", UART_NEW_LINE);

}

u32 check_mailbox_overall() {
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


void validate_framebuffer() {
    uart_write_text("[DEBUG] FB1 Start: ", UART_NONE);
    uart_write_uint((u64)fb_buffer1, UART_NEW_LINE);
    uart_write_text("[DEBUG] FB1 End: ", UART_NONE);
    uart_write_uint((u64)(fb_buffer1 + num_pixels), UART_NEW_LINE);
    uart_write_text("[DEBUG] FB2 Start: ", UART_NONE);
    uart_write_uint((u64)fb_buffer2, UART_NEW_LINE);
    uart_write_text("[DEBUG] FB2 End: ", UART_NONE);
    uart_write_uint((u64)(fb_buffer2 + num_pixels), UART_NEW_LINE);
    uart_write_text("[DEBUG] Difference: ", UART_NONE);
    uart_write_uint((u64)fb_buffer2 - (u64)fb_buffer1, UART_NEW_LINE);
}


void test_virtual_heights() {
    u32 test_heights[] = {1080, 1200, 1440, 1620, 1800, 2160};
    
    for (int i = 0; i < 6; i++) {
        uart_write_text("[DEBUG] Testing height: ", UART_NONE);
        uart_write_uint(test_heights[i], UART_NEW_LINE);
        
        mbox[0] = 8*4;
        mbox[1] = 0;
        mbox[2] = SET_VIRTUAL_SCREEN_SIZE;
        mbox[3] = 8;
        mbox[4] = 0;
        mbox[5] = 1920;
        mbox[6] = test_heights[i];
        mbox[7] = END_TAG;
        
        mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
        mbox_read(PROPERTY_TAG_ARM_GPU);
        
        parse_mailbox_message(8);        

        if (check_mailbox_overall()) {
            return;
        }

        uart_write_text("[DEBUG] Result: ", UART_NONE);
        uart_write_uint(mbox[6], UART_NEW_LINE);
        
        if (mbox[6] == test_heights[i]) {
            uart_write_text("[SUCCESS] Height accepted!", UART_NEW_LINE);
            break;
        }
    }
}


