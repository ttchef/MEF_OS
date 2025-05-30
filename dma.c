
#include "dma.h"
#include "utils.h"
#include "io.h"
#include "memory.h"

#define DMA_TI_NO_WIDE_BURST    1 << 26 
#define DMA_TI_WAITS            1 << 21
#define DMA_TI_PERMAP           1 << 16 
#define DMA_TI_BURST_LENGTH     1 << 12

#define DMA_TI_SRC_INGNORE      1 << 11
#define DMA_TI_SRC_DREQ         1 << 10 
#define DMA_TI_SRC_WIDTH        1 << 9
#define DMA_TI_SRC_INC          1 << 8
#define DMA_TI_DEST_IGNORE      1 << 7
#define DMA_TI_DEST_DREQ        1 << 6
#define DMA_TI_DEST_WIDTH       1 << 5
#define DMA_TI_DEST_INC         1 << 4 
#define DMA_TI_WAIT_RESP        1 << 3 
#define DMA_TI_TDMODE           1 << 1 // Extra << 1
#define DMA_TI_INTEN            1 << 0

#define DMA_CS_DEFAULT_PRIORITY 3
#define DMA_CS_RESET            1 << 31
#define DMA_CS_ABORT            1 << 30 
#define DMA_CS_DISDEBUG         1 << 29
#define DMA_CS_WAIT_FOR_OUTSTANDING_WRITES 1 << 28
#define DMA_CS_PANIC_PRIORITY   1 << 20 
#define DMA_CS_PRIORITY         1 << 16
#define DMA_CS_ERROR            1 << 8
#define DMA_CS_PAUSED           1 << 4
#define DMA_CS_DREQ             1 << 3 
#define DMA_CS_INT              1 << 2 
#define DMA_CS_END              1 << 1
#define DMA_CS_ACTIVE           1 << 0


// Init to 0
dma_control_block dma_cb = {
    .transfer_info = 0,
    .source_address = 0,
    .destination_address = 0,
    .transfer_length = 0,
    .mode_stride_2D = 0,
    .next_control_block = 0,
    .reserved_last[0] = 0,
    .reserved_last[1] = 0
};

void dma_copy_to(void *source, void *destination, u32 length, u32 burst_length) {
    
    dma_cb.transfer_info = (burst_length << DMA_TI_BURST_LENGTH)
                            | DMA_TI_SRC_WIDTH
                            | DMA_TI_DEST_WIDTH
                            | DMA_TI_DEST_INC;

    dma_cb.source_address = (u32)source;
    dma_cb.destination_address = (u32)destination;
    dma_cb.transfer_length = length;

    // Write memory addres of cb
    mmio_write(DMA0_CONBLK_AD, BUS_ADDRESS((u64)&dma_cb));

    // Set active bit and control settings
    mmio_write(DMA0_CS, (
                    DMA_CS_WAIT_FOR_OUTSTANDING_WRITES |
                    (DMA_CS_DEFAULT_PRIORITY << DMA_CS_PRIORITY) | 
                    (DMA_CS_DEFAULT_PRIORITY << DMA_CS_PANIC_PRIORITY) | 
                    DMA_CS_ACTIVE
                ));

    
}


