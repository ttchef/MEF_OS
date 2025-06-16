
#ifndef IO_H
#define IO_H

extern unsigned int uart_init_v;

// UART WRITE FLAGS 
enum {
    UART_NONE = 0,
    UART_NEW_LINE = 0x1,

};

// GPIO
enum {
    GPIO_MAX_PIN       = 53,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_OUT = 1,
    GPIO_FUNCTION_IN = 0
};

// GPIO
unsigned int gpio_set(unsigned int pin_number, unsigned int value);
unsigned int gpio_clear(unsigned int pin_number, unsigned int value);
unsigned int gpio_pull(unsigned int pin_number, unsigned int value);
unsigned int gpio_function(unsigned int pin_number, unsigned int value);


void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

unsigned char uart_readByte();
unsigned int uart_isReadByteReady();
void uart_writeByteBlocking(unsigned char ch);
void uart_update();

void uart_loadOutputFifo();
void uart_init(unsigned int* init);

void uart_write_char(unsigned char c);
void uart_write_text(char *buffer, unsigned int flags);
void uart_write_uint(unsigned int n, unsigned int flags);
void uart_write_int(int n, unsigned int flags);
unsigned int uart_get_input(char *buffer, unsigned int size); // return 1 if input is there 0 if not
void uart_wait_for_input(char *buffer, unsigned int size);

void printf(char* string, ...);
void uart_print_receive(char *buffer, unsigned int size);

#endif 

