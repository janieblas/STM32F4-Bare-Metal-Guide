.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

/* Constants for SRAM configuration */
.equ SRAM_START, 0x20000000
.equ SRAM_SIZE,  (128 * 1024)    /* 128KB of SRAM */
.equ SRAM_END,   (SRAM_START + SRAM_SIZE)

.global Reset_Handler
.global Default_Handler
.global _estack
.global main

/* Minimal vector table - only what we absolutely need */
.section .isr_vector,"a",%progbits
    .word _estack                /* Stack pointer initial value */
    .word Reset_Handler          /* Reset Handler */
    .word Default_Handler        /* NMI Handler */
    .word Default_Handler        /* Hard Fault Handler */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* Reserved */
    .word 0                      /* SysTick Handler */

.section .text
.type Reset_Handler, %function
Reset_Handler:
    /* Copy .data from FLASH to SRAM */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
    subs r2, r2, r1
    beq .L_data_done
.L_data_loop:
    ldr r3, [r0], #4
    str r3, [r1], #4
    subs r2, #4
    bgt .L_data_loop
.L_data_done:

    /* Zero .bss */
    ldr r0, =_sbss
    ldr r1, =_ebss
    subs r1, r1, r0
    beq .L_bss_done
    movs r2, #0
.L_bss_loop:
    str r2, [r0], #4
    subs r1, #4
    bgt .L_bss_loop
.L_bss_done:

    /* Jump to main */
    bl main
    b .

/* Default Handler */
.section .text.Default_Handler,"ax",%progbits
.type Default_Handler, %function
Default_Handler:
    b .                        /* Infinite loop */

/* Define weak aliases for each Exception handler to the Default_Handler */
.weak NMI_Handler
.thumb_set NMI_Handler,Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler

.weak MemManage_Handler
.thumb_set MemManage_Handler,Default_Handler

.weak BusFault_Handler
.thumb_set BusFault_Handler,Default_Handler

.weak UsageFault_Handler
.thumb_set UsageFault_Handler,Default_Handler

.weak SVC_Handler
.thumb_set SVC_Handler,Default_Handler

.weak DebugMon_Handler
.thumb_set DebugMon_Handler,Default_Handler

.weak PendSV_Handler
.thumb_set PendSV_Handler,Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler

.end
