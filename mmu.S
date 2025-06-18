
.global enable_mmu
enable_mmu:
    // check el
    mrs x0, CurrentEL
    lsr x0, x0, #2
    cmp x0, #1
    beq in_el1
    cmp x0, #2
    beq switch_el1
    b loop
   
loop:
    wfe
    b loop

switch_el1:

    mov x0, #0
    orr x0, x0, #(1 << 31) // HCR_RW 
    msr hcr_el2, x0 

    mov x0, #0
    orr x0, x0, #(0b111 << 6)
    mov x1, #0b0101
    orr x0, x0, x1
    msr spsr_el2, x0

    adr x0, in_el1
    msr elr_el2, x0 
    eret

/*
    // construct fields
    mov x0, #0
    orr x0, x0, #(3 << 28) // SCTLR_RESERVED
    orr x0, x0, #(3 << 22) // SCTLR_RESERVED
    orr x0, x0, #(1 << 20) // SCTLR_RESERVED
    orr x0, x0, #(1 << 11) // SCTLR_RESERVED

    and x0, x0, #~(1 << 25) // LITTLE_ENDIAN
    and x0, x0, #~(1 << 12) // I-CACHE DISABLE
    and x0, x0, #~(1 << 2) // D_CACHE DISABLE
    and x0, x0, #~(1 << 0) // MMU DISABLE

    msr sctlr_el1, x0

    mov x0, #0
    orr x0, x0, #(1 << 31) // HCR_RW
    msr hcr_el2, x0


    mov x0, #0 
    orr x0, x0, #(3 << 4) // SCR_RESERVED
    orr x0, x0, #(1 << 10) // SCR_RW 
    orr x0, x0, #(1 << 0) // SCR_NS
    msr scr_el3, x0
    

    mov x0, #0 
    orr x0, x0, #(7 << 6) // SPSR_MASK_ALL
    // SPSR_EL1h
    mov x1, #5
    orr x0, x0, x1
    msr spsr_el2, x0
    

    // switch to el1 
    mov x0, #0 
    adr x0, in_el1
    msr elr_el2, x0
    eret
    */

in_el1:

    ldr x1, =__stack_end
    mov sp, x1

    mrs x0, cpacr_el1
    orr x0, x0, #(0b11 << 20)
    msr cpacr_el1, x0
    isb

    ret



