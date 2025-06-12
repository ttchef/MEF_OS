.section ".text.boot"
.global _start

_start:
    mrs x1, mpidr_el1
    and x1, x1, 0b11
    cbz x1, 2f

// Not on the main core
1:
    wfe
    b 1b
    
// On the main core
2:
    // Set stack below this code
    ldr x1, =_start
    mov sp, x1
    
    // Clean bss section
    ldr x1, =__bss_start
    ldr w2, =__bss_size
3:  cbz w2, 4f
    str xzr, [x1], #8
    sub w2, w2, #1 
    cbnz w2, 3b 
4:
    bl main
    b 1b

