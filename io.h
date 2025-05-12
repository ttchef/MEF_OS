
extern unsigned int uart_init_v;

// UART WRITE FLAGS 
enum {
    UART_NONE = 0,
    UART_NEW_LINE = 0x1,

};


void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);

unsigned char uart_readByte();
unsigned int uart_isReadByteReady();
void uart_writeByteBlocking(unsigned char ch);
void uart_update();

void uart_loadOutputFifo();
void uart_init(unsigned int* init);

void uart_write_text(char *buffer, unsigned int flags);
void uart_write_uint(unsigned int n, unsigned int flags);
void uart_write_int(int n, unsigned int flags);

