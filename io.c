
#include "io.h"
#include "globals.h"
#include "string.h"

#include <stdarg.h>

unsigned int uart_init_v;

// GPIO
enum {
    GPFSEL0         = PERIPHERAL_BASE + 0x200000,
    GPSET0          = PERIPHERAL_BASE + 0x20001C,
    GPCLR0          = PERIPHERAL_BASE + 0x200028,
    GPPUPPDN0       = PERIPHERAL_BASE + 0x2000E4
};


enum {
    Pull_None = 0,
};


void mmio_write(long reg, unsigned int val) { *(volatile unsigned int *)reg = val; }
unsigned int mmio_read(long reg) { return *(volatile unsigned int *)reg; }

unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max) {
    unsigned int field_mask = (1 << field_size) - 1;
  
    if (pin_number > field_max) return 0;
    if (value > field_mask) return 0; 

    unsigned int num_fields = 32 / field_size;
    unsigned int reg = base + ((pin_number / num_fields) * 4);
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

unsigned int gpio_set     (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN); }
unsigned int gpio_clear   (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN); }
unsigned int gpio_pull    (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN); }
unsigned int gpio_function(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN); }

void gpio_useAsAlt5(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

// UART

enum {
    AUX_BASE        = PERIPHERAL_BASE + 0x215000,
    AUX_ENABLES     = AUX_BASE + 4,
    AUX_MU_IO_REG   = AUX_BASE + 64,
    AUX_MU_IER_REG  = AUX_BASE + 68,
    AUX_MU_IIR_REG  = AUX_BASE + 72,
    AUX_MU_LCR_REG  = AUX_BASE + 76,
    AUX_MU_MCR_REG  = AUX_BASE + 80,
    AUX_MU_LSR_REG  = AUX_BASE + 84,
    AUX_MU_CNTL_REG = AUX_BASE + 96,
    AUX_MU_BAUD_REG = AUX_BASE + 104,
    AUX_UART_CLOCK  = 500000000,
    UART_MAX_QUEUE  = 16 * 1024
};

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

void uart_init(unsigned int* init) {
    mmio_write(AUX_ENABLES, 1); //enable UART1
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_CNTL_REG, 0);
    mmio_write(AUX_MU_LCR_REG, 3); //8 bits
    mmio_write(AUX_MU_MCR_REG, 0);
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_IIR_REG, 0xC6); //disable interrupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(115200));
    gpio_useAsAlt5(14);
    gpio_useAsAlt5(15);
    mmio_write(AUX_MU_CNTL_REG, 3); //enable RX/TX

    *init = 1;
    uart_write_text("[DEBUG] Init UART!", UART_NEW_LINE);
}

unsigned int uart_is_write_byte_ready() { return mmio_read(AUX_MU_LSR_REG) & 0x20; }

void uart_write_char(unsigned char ch) {
    while (!uart_is_write_byte_ready());
    mmio_write(AUX_MU_IO_REG, (unsigned int)ch);
}

void uart_write_text(char *buffer, unsigned int flags) {
    while (*buffer != '\0') {
       if (*buffer == '\n') uart_write_char('\r');
       uart_write_char(*buffer++);
    }

    if (flags & UART_NEW_LINE) {
        uart_write_char('\n');
        uart_write_char('\r');
    }

}

void uart_write_uint(unsigned int n, unsigned int flags) {
    
    const int MAX_LENGTH = 11;
    char string[MAX_LENGTH + 1];
    int i;

    if (n == 0) { uart_write_char('0'); return; }

    for (i = 0; n > 0; i++) {
        string[i] = (n % 10) + '0';
        n /= 10;
    }

    while (i--) {
        uart_write_char(string[i]);
    }

    if (flags & UART_NEW_LINE) {
        uart_write_char('\n');
        uart_write_char('\r');
    }

    
}

void uart_write_int(int n, unsigned int flags) {
    
    const int MAX_LENGTH = 11;
    char string[MAX_LENGTH + 1];
    int i;

    if (n == 0) { uart_write_char('0'); return; }
    if (n < 0) { uart_write_char('-'); n*=-1; }

    for (i = 0; n > 0; i++) {
        string[i] = (n % 10) + '0';
        n /= 10;
    }

    while (i--) {
        uart_write_char(string[i]);
    }

    if (flags & UART_NEW_LINE) {
        uart_write_char('\n');
        uart_write_char('\r');
    }

}

u32 uart_get_input(char *buffer, unsigned int size) {
    u32 i = 0;

    while (i < size - 1) {
        if (!(mmio_read(AUX_MU_LSR_REG) & 1)) {
            break;
        }

        char c = mmio_read(AUX_MU_IO_REG) & 0xFF;
        buffer[i++] = c;
    }

    buffer[i] = '\0';
    return i;

}

void uart_wait_for_input(char *buffer, unsigned int size) {
    u32 i = 0;

    while (i < size - 1) {
        // wait till input is there
        while(!(mmio_read(AUX_MU_LSR_REG) & 1));

        char c = mmio_read(AUX_MU_IO_REG) & 0xFF;
        buffer[i++] = c;
    }

    buffer[i] = '\0';
 
}

// basically pretty similar to text_format in string.c
void printf(char* string, ...) {
    
    va_list vlist;
    va_start(vlist, string);

    while (*string != '\0') {
        if (*string == '\n') {
            uart_write_char('\r');
        }
        if (*string == '%') {
            string++;
            char temp[32];
            switch (*string) {
                case 's': {
                    char* str = va_arg(vlist, char*);
                    while (*str != '\0') uart_write_char(*str++);
                    break;
                }
                case 'd': {
                    i32 num = va_arg(vlist, i32);
                    itoa_dec(num, temp);
                    char* t = temp;
                    while (*t != '\0') uart_write_char(*t++);
                    break;
                }
                case 'x': {
                    u32 num = va_arg(vlist, u32);
                    itoa_hex(num, temp);
                    char* t = temp;
                    while (*t != '\0') uart_write_char(*t++);
                    break;
                }
                case 'b': {
                    u32 num = va_arg(vlist, u32);
                    itoa_bin(num, temp);
                    char* t = temp;
                    while (*t != '\0') uart_write_char(*t++);
                    break;
                }
                case '%': {
                    uart_write_char('%');
                    break;
                }
                default:
                    uart_write_char('?');
            }
        }
        else {
            uart_write_char(*string);
        }
        string++;
    }

    va_end(vlist);

}

void uart_print_receive(char *buffer, unsigned int size) {
    if (size == 0) return;

    for (u32 i = 0; i < size; i++) {
        uart_write_char(buffer[i]);
    }
    uart_write_char('\n');
    uart_write_char('\r');
}

