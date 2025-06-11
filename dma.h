
#ifndef DMA_H
#define DMA_H

#include "globals.h"

enum {
    DMA_BASE        = PERIPHERAL_BASE + 0x00007000,
    DMA0_CS         = DMA_BASE + 0x000,
    DMA0_CONBLK_AD  = DMA_BASE + 0x004,
    DMA0_TI         = DMA_BASE + 0x008,

    DMA_INT_STATUS  = DMA_BASE + 0xFE0,
    DMA_ENABLE      = DMA_BASE + 0xFF0
};

#define CHANNEL_GET_MEMORY_ADDRESS(channel) DMA_BASE + channel * 0x100

typedef struct {
    unsigned int transfer_info;
    unsigned int source_address;
    unsigned int destination_address;
    unsigned int transfer_length;
    unsigned int mode_stride_2D;
    unsigned int next_control_block;
    unsigned int reserved_last[2];
} __attribute__((aligned(256))) dma_control_block;

typedef struct {
    unsigned int transfer_info;
    unsigned int source_address;
    unsigned int destination_address;
    unsigned int transfer_length;
    unsigned int reserved_4;
    unsigned int next_control_block;
    unsigned int reserved_last[2];
} __attribute__((aligned(256))) dma_control_block_lite;

typedef struct {
    unsigned int transfer_info;
    unsigned int source_address;
    unsigned int source_info;
    unsigned int destination_address;
    unsigned int definition_info;
    unsigned int transfer_length;
    unsigned int next_control_block;
    unsigned int reserved_last;
} __attribute__((aligned(256))) dma_control_block_dma4;

extern dma_control_block dma_cb;

void dma_copy_to(void *source, void *destination, unsigned int length, unsigned int burst_length);

#endif
