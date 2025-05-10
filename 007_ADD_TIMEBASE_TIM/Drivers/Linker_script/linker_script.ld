ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);    /* end of RAM */

/* Specify the memory areas */
MEMORY
{
  FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K
  SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS 
{ 
/* The startup code goes first into FLASH */
  .isr_vector : 
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH 

  .text : 
  { 
    . = ALIGN(4); 
    *(.text) 
    *(.text*) 
    *(.rodata) 
    . = ALIGN(4); 
    _etext = .; 
  } >FLASH 
 
  _sidata = LOADADDR(.data); 

  .data : 
  { 
    . = ALIGN(4); 
    _sdata = .; 
    *(.data) 
    . = ALIGN(4); 
    _edata = .; 
  } >SRAM AT> FLASH 

  .bss : 
  { 
    . = ALIGN(4); 
    _sbss = .; 
    __bss_start__ = .;
    *(.bss) 
    . = ALIGN(4); 
    _ebss = .; 
    __bss_end__ = .;
  } >SRAM 
} 