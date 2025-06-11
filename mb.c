
#include "mb.h"
#include "io.h"



unsigned int mbox_read(unsigned int channel) {
    unsigned int message, m_channel;

    do {
        while(mmio_read(MBOX0_STATUS) & MBOX_EMPTY);
        unsigned int message = mmio_read(MBOX0);
        m_channel = message & 0xF;
    } while (m_channel != channel);

    return message;
}

void mbox_write(unsigned int data, unsigned int channel) {
 
    //uart_write_text("[DEBUG] Beginning MBOX Write!", UART_NEW_LINE);

    unsigned int msg = (data & ~0xF) | (channel & 0xF);

    while(mmio_read(MBOX1_STATUS) & MBOX_FULL);

    //uart_write_text("[DEBUG] MBOX Write After Loop!", UART_NEW_LINE);

    mmio_write(MBOX1, msg);
    
}

