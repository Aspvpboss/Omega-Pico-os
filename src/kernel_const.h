#ifndef KERNEL_CONST_H
#define KERNEL_CONST_H

#include <stddef.h>
#include <stdint.h>

/* Flash */
extern uint8_t __flash_binary_start[];
extern uint8_t __boot2_start__[];
extern uint8_t __boot2_end__[];
extern uint8_t __logical_binary_start[];
extern uint8_t __flash_binary_end[];

/* Kernel RAM (.data & .bss) */
extern uint8_t __data_start__[];
extern uint8_t __data_end__[];
extern uint8_t __bss_start__[];
extern uint8_t __bss_end__[];

/* Unified Heap (User Processes & Dynamic Allocations) */
extern uint8_t __end__[];
extern uint8_t __HeapLimit[];

/* Core 0 Kernel Stack (MSP in SCRATCH_Y) */
extern uint8_t __StackTop[];
extern uint8_t __StackLimit[];

/* Core 1 Kernel Stack (MSP in SCRATCH_X) */
extern uint8_t __StackOneTop[];
extern uint8_t __StackOneBottom[];

/* Scratch X & Y Boundaries */
extern uint8_t __scratch_x_start__[];
extern uint8_t __scratch_x_end__[];
extern uint8_t __scratch_y_start__[];
extern uint8_t __scratch_y_end__[];



/* Fixed RP2040 Hardware Regions */
#define RP2040_FLASH_BASE       ((uintptr_t)0x10000000u)
#define RP2040_FLASH_SIZE       ((size_t)(2048u * 1024u))
#define RP2040_FLASH_END        (RP2040_FLASH_BASE + RP2040_FLASH_SIZE)

#define RP2040_RAM_BASE         ((uintptr_t)0x20000000u)
#define RP2040_RAM_SIZE         ((size_t)(256u * 1024u))
#define RP2040_RAM_END          (RP2040_RAM_BASE + RP2040_RAM_SIZE)

#define RP2040_SCRATCH_X_BASE   ((uintptr_t)0x20040000u)
#define RP2040_SCRATCH_X_SIZE   ((size_t)(4u * 1024u))
#define RP2040_SCRATCH_X_END    (RP2040_SCRATCH_X_BASE + RP2040_SCRATCH_X_SIZE)

#define RP2040_SCRATCH_Y_BASE   ((uintptr_t)0x20041000u)
#define RP2040_SCRATCH_Y_SIZE   ((size_t)(4u * 1024u))
#define RP2040_SCRATCH_Y_END    (RP2040_SCRATCH_Y_BASE + RP2040_SCRATCH_Y_SIZE)

/* Kernel Flash Usage */
#define KERNEL_FLASH_START      ((uintptr_t)__flash_binary_start)
#define KERNEL_FLASH_END        ((uintptr_t)__flash_binary_end)
#define KERNEL_FLASH_USED_BYTES ((size_t)(KERNEL_FLASH_END - KERNEL_FLASH_START))
#define FREE_FLASH_START        ((uintptr_t)__flash_binary_end)
#define FREE_FLASH_BYTES        ((size_t)(RP2040_FLASH_END - FREE_FLASH_START))

/* Kernel Static RAM (.data + .bss) */
#define KERNEL_DATA_START       ((uintptr_t)__data_start__)
#define KERNEL_DATA_END         ((uintptr_t)__data_end__)
#define KERNEL_BSS_START        ((uintptr_t)__bss_start__)
#define KERNEL_BSS_END          ((uintptr_t)__bss_end__)
#define KERNEL_STATIC_RAM_BYTES ((size_t)(KERNEL_BSS_END - RP2040_RAM_BASE))

/* Unified Heap (Available for User Process Slots & Kernel Allocator) */
#define KERNEL_HEAP_START       ((uintptr_t)__end__)
#define KERNEL_HEAP_END         ((uintptr_t)__HeapLimit)
#define KERNEL_HEAP_BYTES       ((size_t)(KERNEL_HEAP_END - KERNEL_HEAP_START))

/* Core 0 Kernel Stack (MSP - SCRATCH_Y) */
#define CORE0_KSTACK_TOP        ((uintptr_t)__StackTop)
#define CORE0_KSTACK_BOTTOM     ((uintptr_t)__StackLimit)
#define CORE0_KSTACK_BYTES      ((size_t)(CORE0_KSTACK_TOP - CORE0_KSTACK_BOTTOM))

/* Core 1 Kernel Stack (MSP - SCRATCH_X) */
#define CORE1_KSTACK_TOP        ((uintptr_t)__StackOneTop)
#define CORE1_KSTACK_BOTTOM     ((uintptr_t)__StackOneBottom)
#define CORE1_KSTACK_BYTES      ((size_t)(CORE1_KSTACK_TOP - CORE1_KSTACK_BOTTOM))

/* Free Scratch Space (Below Kernel Stacks) */
#define SCRATCH_X_FREE_START    ((uintptr_t)__scratch_x_end__)
#define SCRATCH_X_FREE_END      CORE1_KSTACK_BOTTOM
#define SCRATCH_Y_FREE_START    ((uintptr_t)__scratch_y_end__)
#define SCRATCH_Y_FREE_END      CORE0_KSTACK_BOTTOM

#endif
