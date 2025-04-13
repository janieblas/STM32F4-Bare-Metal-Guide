.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global Reset_Handler
.global Default_Handler

/* Vector Table */
.section .isr_vector
    .word _estack                 /* Stack pointer initial value */
    .word Reset_Handler          /* Reset Handler */
    .word NMI_Handler            /* NMI Handler */
    .word HardFault_Handler      /* Hard Fault Handler */
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
    .word SysTick_Handler        /* SysTick Handler */

/* Reset Handler */
.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Enable FPU */
    ldr r0, =0xE000ED88         /* Load address of CPACR register */
    ldr r1, [r0]                /* Read CPACR */
    orr r1, r1, #(0xF << 20)    /* Set bits 20-23 to enable CP10 and CP11 */
    str r1, [r0]                /* Write back modified value to CPACR */
    dsb                         /* Wait for store to complete */
    isb                         /* Reset pipeline now FPU is enabled */

    /* Copy .data section from Flash to SRAM */
    ldr r0, =_sidata            /* Source address in Flash */
    ldr r1, =_sdata            /* Destination address in SRAM */
    ldr r2, =_edata            /* End address in SRAM */
    subs r2, r2, r1            /* Calculate size of .data section */
    ble .L_loop1_done          /* If size is 0 or negative, skip copy */

.L_loop1:
    ldr r3, [r0], #4           /* Load word from Flash and increment source */
    str r3, [r1], #4           /* Store word to SRAM and increment destination */
    subs r2, r2, #4            /* Decrement size counter */
    bgt .L_loop1               /* If size > 0, continue copying */

.L_loop1_done:
    /* Zero-fill .bss section */
    ldr r0, =_sbss             /* Start address of .bss section */
    ldr r1, =_ebss             /* End address of .bss section */
    subs r1, r1, r0            /* Calculate size of .bss section */
    ble .L_loop2_done          /* If size is 0 or negative, skip zero-fill */
    movs r2, #0                /* Value to fill with (0) */

.L_loop2:
    str r2, [r0], #4           /* Store 0 and increment address */
    subs r1, r1, #4            /* Decrement size counter */
    bgt .L_loop2               /* If size > 0, continue zero-filling */

.L_loop2_done:
    /* Call main */
    bl main                    /* Branch to main function */

    /* If main returns, loop forever */
    b .                        /* Infinite loop */

/* Default Handler */
.section .text.Default_Handler
.weak Default_Handler
.type Default_Handler, %function
Default_Handler:
    b .                        /* Infinite loop */

/* Weak aliases for exception handlers */
.weak NMI_Handler
.thumb_set NMI_Handler,Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler 