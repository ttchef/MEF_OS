
SECTIONS
{
    . = 0x80000;     /* Kernel load address for AArch64 */

    __kernel_start = .;

    .text : {
        /* Ensures that the _start is kept*/
        KEEP(*(.text.boot))
        *(.text .text.* .gnu.linkonce.t*) 
    }

    .rodata : { 
        *(.rodata .rodata.* .gnu.linkonce.r*) 
    }

    PROVIDE(_data = .);

    .data : {
        *(.data .data.* .gnu.linkonce.d*) 
    }

    .bss (NOLOAD) : {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        __bss_end = .;
    }

    . = ALIGN(16);
    __heap_start = .;
    . = . + 0x6400000; /* 100MB */ 
    __heap_end = .;

    _end = .;

   /DISCARD/ : { *(.comment) *(.gnu*) *(.note*) *(.eh_frame*) }
}
__bss_size = (__bss_end - __bss_start)>>3;

