/* linker/memmap_os.ld - Fixed Alignment & Stack Size for RP2040 */

MEMORY
{
    FLASH(rx)      : ORIGIN = 0x10000000, LENGTH = 2048k
    RAM(rwx)       : ORIGIN = 0x20000000, LENGTH = 256k
    SCRATCH_X(rwx) : ORIGIN = 0x20040000, LENGTH = 4k
    SCRATCH_Y(rwx) : ORIGIN = 0x20041000, LENGTH = 4k
}

ENTRY(_entry_point)

SECTIONS
{
    .flash_begin : {
        __flash_binary_start = .;
    } > FLASH

    .boot2 : {
        __boot2_start__ = .;
        KEEP(*(.boot2))
        __boot2_end__ = .;
    } > FLASH
    ASSERT(__boot2_end__ - __boot2_start__ == 256, "boot2 must be 256 bytes")

    .text : {
        __logical_binary_start = .;
        . = ALIGN(256);               /* Cortex-M0+ VTOR requires 256-byte alignment */
        KEEP(*(.vectors))
        KEEP(*(.binary_info_header))
        KEEP(*(.reset))
        *(.init)
        *(.text*)
        *(.fini)
        *(.rodata*)
        . = ALIGN(4);

        PROVIDE_HIDDEN(__mutex_array_start = .);
        KEEP(*(SORT(.mutex_array.*)))
        KEEP(*(.mutex_array))
        PROVIDE_HIDDEN(__mutex_array_end = .);
        . = ALIGN(4);

        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(SORT(.preinit_array.*)))
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
        . = ALIGN(4);

        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
        . = ALIGN(4);
    } > FLASH

    __binary_info_start = .;
    .binary_info : { KEEP(*(.binary_info*)) } > FLASH
    __binary_info_end = .;

    .ram_vector_table (NOLOAD): {
        *(.ram_vector_table)
    } > RAM

    .data : {
        __data_start__ = .;
        *(vtable)
        *(.time_critical*)
        *(.data*)
        *(.after_data.*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT> FLASH
    __etext = LOADADDR(.data);

    .scratch_x : {
        __scratch_x_start__ = .;
        *(.scratch_x.*)
        . = ALIGN(4);
        __scratch_x_end__ = .;
    } > SCRATCH_X AT> FLASH
    __scratch_x_source__ = LOADADDR(.scratch_x);

    .scratch_y : {
        __scratch_y_start__ = .;
        *(.scratch_y.*)
        . = ALIGN(4);
        __scratch_y_end__ = .;
    } > SCRATCH_Y AT> FLASH
    __scratch_y_source__ = LOADADDR(.scratch_y);

    .bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*) *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM

    /* Heap gets all remaining 256 KB main RAM (from end of .bss to 0x20040000) */
    __end__     = .;
    end         = __end__;
    __HeapLimit = ORIGIN(RAM) + LENGTH(RAM);

    /* Core 0 Kernel Stack (MSP): top 2 KB of SCRATCH_Y (safe for SDK init + ISRs) */
    __StackTop       = ORIGIN(SCRATCH_Y) + LENGTH(SCRATCH_Y);
    __StackLimit     = __StackTop - 0x800;

    /* Core 1 Kernel Stack (MSP): top 1 KB of SCRATCH_X */
    __StackOneTop    = ORIGIN(SCRATCH_X) + LENGTH(SCRATCH_X);
    __StackOneBottom = __StackOneTop - 0x400;

    PROVIDE(__stack = __StackTop);

    ASSERT(__HeapLimit >= __end__, "Main RAM overflowed by kernel .data and .bss")
    ASSERT(__StackLimit >= __scratch_y_end__, "SCRATCH_Y overflowed into Core 0 kernel stack")
    ASSERT(__StackOneBottom >= __scratch_x_end__, "SCRATCH_X overflowed into Core 1 kernel stack")

    .flash_end : {
        PROVIDE(__flash_binary_end = .);
    } > FLASH
}
