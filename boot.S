
.section ".text.boot" // Put code in this section

.global _start
_start:
    mrs x1,mpidr_el1 // mrs = move register from system | mpidr_el1 = contains info which core is running the code 
    and x1,x1,0b11 // Core ID in lower 2 bits it isolates them
    cbz x1,2f

// Not on the main core (infinite loop)
1:
    wfe // wait for event (low voltage)
    b 1b
    
// On the main core
2:
    // Set stack to below this code 
    ldr x1,=_start
    mov sp,x1

    // Enable Caches
    bl enable_caches

    // Clean bss section
    ldr x1,=__bss_start
    ldr w2,=__bss_size // Represent the number of 8 Byte Chunks
3:  cbz w2,4f   // Quit Loop if 0
    str xzr,[x1],#8 // xzr = zeor register | *x1 = 0; x1 += 8
    sub w2,w2,#1 
    cbnz w2,3b 

4:
    bl main
    // If main returns (kernel ends) enter infinite loop
    b 1b

enable_caches:
    mov  x2, #(1 << 12)        // I-cache
    orr  x2, x2, #(1 << 2)     // D-cache
    orr  x2, x2, #(1 << 11)    // Branch prediction
    mrs  x0, sctlr_el1
    orr  x0, x0, x2
    msr  sctlr_el1, x0
    dsb  ish
    isb
    ret

