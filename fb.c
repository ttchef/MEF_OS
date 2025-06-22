
#include "fb.h"
#include "mb.h"
#include "io.h"
#include "globals.h"
#include "memory.h"
#include "font.h"
#include "types.h"
#include "string.h"
#include "math.h"

volatile unsigned int __attribute__((aligned(16))) mbox[35];

u64* fb_buffer1;
u64* fb_buffer2;
u32 fb_size;
u32 num_pixels;
u32 pitch;

u64 *active_buffer;
u32 buffer_one_active;

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


void framebuffer_init() {

    buffer_one_active = 1;

    uart_write_text("[DEBUG] Init Framebuffer Beginning!", UART_NEW_LINE);

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
    mbox[20] = SCREENHEIGHT;

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

    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);

    // Error checking
    if (check_mailbox_overall()) {
        return;
    }

    pitch = mbox[24];
    num_pixels = SCREENWIDTH*SCREENHEIGHT;

    // Framebuffer 
    fb_buffer1 = (u64*)BUS_ADDRESS(mbox[28]);
    active_buffer = fb_buffer1;
    fb_buffer2 = fb_buffer1 + ((pitch * SCREENHEIGHT) / sizeof(u64)); 
    fb_size = mbox[29];

    uart_write_text("[DEBUG] Framebuffer: ", UART_NONE);
    uart_write_uint(mbox[28], UART_NEW_LINE);

    uart_write_text("[DEBUG] Framebuffer Size: ", UART_NONE);
    uart_write_uint(mbox[29], UART_NEW_LINE);

    uart_write_text("[DEBUG] Mailbox Code: ", UART_NONE);
    uart_write_uint(mbox[1], UART_NEW_LINE);


    uart_write_text("[DEBUG] Pitch: ", UART_NONE);
    uart_write_uint(mbox[24], UART_NEW_LINE);

  
    // Virtual Resolution
    u32 virtual_screen_height = get_virtual_screen_dimensions().y;
    uart_write_text("[DEBUG] Vitrual Screenheight: ", UART_NONE);
    uart_write_uint(virtual_screen_height, UART_NEW_LINE);

    // Pixel Order
    u32 pixel_order = get_pixel_order();
    uart_write_text("[DEBUG] Pixel Order: ", UART_NONE);
    if (pixel_order == 1) {
        uart_write_text("BGR", UART_NEW_LINE);
    } 
    else if (pixel_order == 2) {
        uart_write_text("RGB", UART_NEW_LINE);
    }
    else {
        uart_write_text("\n[ERROR] Getting Pixel Order!", UART_NEW_LINE);
    }

    uart_write_text("[DEBUG] FB_1 Address: ", UART_NONE);
    uart_write_uint((u64)fb_buffer1 , UART_NEW_LINE);

    uart_write_text("[DEBUG] FB_2 Address: ", UART_NONE);
    uart_write_uint((u64)fb_buffer2 , UART_NEW_LINE);


    uart_write_text("[DEBUG] FB Init finish!", UART_NEW_LINE);

}

u32 get_fb_of(u32 x, u32 y) {
    return (y * pitch / 4) + x;
}


void draw_rect(u32 x, u32 y, u32 width, u32 height, Color color, enum FONT_ORIENT orientation) {
    if (orientation == TOP_LEFT) {
        for (u32 i = 0; i < width; i++) {
            for (u32 j = 0; j < height; j++) {
                draw_pixel(x+i, y+j, color);
            }
        }
    }
    else if (orientation == CENTER) {
        u32 newX = x - (width/2);
        u32 newY = y - (height/2);
        for (u32 i = 0; i < width; i++) {
            for (u32 j = 0; j < height; j++) {
                draw_pixel(newX+i, newY+j, color);
            }
        }
    }
    else {
        printf("[ERROR] Unkown rectangle orientation specified!\n");
    }
}

void draw_vertical_line(i32 x, i32 y0, i32 y1, Color color) {
    i32 i = y0;
    for (; i < y1; i++) {
        draw_pixel(x, i, color);
    }
 }

void draw_line(i32 x0, i32 y0, i32 x1, i32 y1, Color color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        draw_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_char(char c, u32 x, u32 y, Color color, u32 scale) {
    char* bitmap = font_buffer[c];
    i32 set;
    i32 mask;
    for (u16 i = 0; i < (FONT_HEIGHT*scale); i++) {
        for (u16 j = 0; j < (FONT_WIDTH*scale); j++) {
            set = bitmap[i/scale] & 1 << j/scale;
            if (set) {
                draw_pixel(x+j, y+i, color);
            } 
        }
    }
}

void draw_string(char *string, u32 x, u32 y, Color color, u32 scale) {
    u32 i = 0;
    while (*string != '\0') {
        draw_char(*string, x+i, y, color, scale);
        i += FONT_WIDTH * scale;
        string++;
    }
}

void draw_text(Text text) {
    u32 i = 0;
    if (text.orientation == TOP_LEFT) {
        while (*text.string != '\0') {
            draw_char(*text.string, text.pos.x+i, text.pos.y, text.color, text.scale);
            i += FONT_WIDTH * text.scale;
            text.string++;
        }
    }
    else if (text.orientation == CENTER) {
        u32 length = strlen(text.string);
        if (length % 2) i = text.pos.x - (length/2+0.5) * FONT_WIDTH * text.scale;           
        else i = text.pos.x - (length/2) * FONT_WIDTH * text.scale;

        while(*text.string != '\0') {
            draw_char(*text.string, i, text.pos.y - FONT_HEIGHT/2*text.scale, text.color, text.scale);
            i += FONT_WIDTH * text.scale;
            text.string++; 
        }
    }
}

/*
Time Spent debugging double buffering with virtual offset:
- 3 Days
- 15 Hours
*/
void clear_color(Color color) {

    u64* ptr = active_buffer;
    u64* end = ptr + (fb_size/16);
    u32 color32 = CONVERT_COLOR_STRUCT(color);
    u64 color64 = ((u64)color32 << 32) | color32;

    while (ptr + 4 <= end) {

        ptr[0] = color64;
        ptr[1] = color64;
        ptr[2] = color64;
        ptr[3] = color64;
        ptr += 4;
    }

    while (ptr < end) {
        *ptr++ = color64;
    }

}

void swap_buffers() {
    if (buffer_one_active == 1) {
        set_virtual_offset(0, 0);           
        buffer_one_active = 0;              
        active_buffer = fb_buffer2;         
    } else {
        set_virtual_offset(0, SCREENHEIGHT);        
        buffer_one_active = 1;                     
        active_buffer = fb_buffer1;             
    }
}

u32 get_pixel_order() {
    mbox[0] = 7*4;
    mbox[1] = 0;

    mbox[2] = GET_PIXEL_ORDER;
    mbox[3] = 4;
    mbox[4] = 0;
    mbox[5] = 0;

    mbox[6] = END_TAG;
 
    mbox_write((long)mbox, PROPERTY_TAG_ARM_GPU);
    mbox_read(PROPERTY_TAG_ARM_GPU);
    
    if (check_mailbox_overall()) {
        uart_write_text("[ERROR] Parsing \"Get Pixel Order Mailbox\"\n", UART_NONE);
        return 0;
    }

    return mbox[5]+1; // 1 -> BGR | 2 -> RGB

}


void set_virtual_offset(u32 x, u32 y) {
    
    while(mmio_read(MBOX1_STATUS) & MBOX_FULL);

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
    
    //parse_mailbox_message(8);

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
    
    //parse_mailbox_message(8);

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
    
    //parse_mailbox_message(8);

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


