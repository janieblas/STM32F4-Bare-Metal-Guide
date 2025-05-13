#ifndef DIY_GPIO_H
#define DIY_GPIO_H

typedef struct
{
    uint32_t Pin;       // Pines a configurar (ej. GPIO_PIN_5)
    uint32_t Mode;      // Modo: entrada, salida, alternate, analog
                                            // MODER       Configura el modo del pin                        2 bits
                                            //             00: Entrada, 01: Salida, 10: Alternate, 11: Analógico
    uint32_t Pull;      // Pull-up / Pull-down
                                            // PUPDR       Configura resistencias internas                  2 bits
                                            //             00: Sin pull-up/down, 01: Pull-up, 10: Pull-down, 11: Reservado
    uint32_t Speed;     // Velocidad de salida
                                            // OSPEEDR     Configura la velocidad del pin                   2 bits
                                            //             00: Baja, 01: Media, 10: Alta, 11: Muy alta
}GPIO_InitTypeDef;

/* Prototipos de funciones */
void DIY_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void DIY_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t PinState);
uint8_t DIY_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void DIY_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif // DIY_GPIO_H