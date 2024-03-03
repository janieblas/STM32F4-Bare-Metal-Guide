#include <stdint.h>

#define SRAM_START (0x20000000U)
#define SRAM_SIZE (128U * 1024U)
#define SRAM_END (SRAM_START + SRAM_SIZE)


void Reset_handler(void);
void Default_Handler(void);

void Nmi_Handler(void) __attribute__((weak, alias("Default_Handler")));
// continue adding device interrupt handlers

uint32_t isr_vector[] __attribute__((section(".isr_vector"))) = {
  SRAM_END,
  (uint32_t)&Reset_handler,
  (uint32_t)&Nmi_Handler,
};

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _sidata;
void main(void);


void Reset_handler(void)
{
  // Copy .data from FLASH to SRAM
  uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *flash_data = (uint8_t*) &_sidata; // Data load address (in flash)
  uint8_t *sram_data = (uint8_t*) &_sdata; // Data virtual address (in sram)
  
  for (uint32_t i = 0; i < data_size; i++)
  {
    sram_data[i] = flash_data[i];
  }

  // Zero-fill .bss section in SRAM
  uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  uint8_t *bss = (uint8_t*) &_sbss;

  for (uint32_t i = 0; i < bss_size; i++)
  {
    bss[i] = 0;
  }
  //Call to main
  main();
}

void Default_Handler(void)
{
  while(1);
}