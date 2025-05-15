#ifndef DIY_GPIO_H
#define DIY_GPIO_H

/* Pin definitions */
#define GPIO_PIN_0                 ((uint16_t)0x0001)
#define GPIO_PIN_1                 ((uint16_t)0x0002)
#define GPIO_PIN_2                 ((uint16_t)0x0004)
#define GPIO_PIN_3                 ((uint16_t)0x0008)
#define GPIO_PIN_4                 ((uint16_t)0x0010)
#define GPIO_PIN_5                 ((uint16_t)0x0020)
#define GPIO_PIN_6                 ((uint16_t)0x0040)
#define GPIO_PIN_7                 ((uint16_t)0x0080)
#define GPIO_PIN_8                 ((uint16_t)0x0100)
#define GPIO_PIN_9                 ((uint16_t)0x0200)
#define GPIO_PIN_10                ((uint16_t)0x0400)
#define GPIO_PIN_11                ((uint16_t)0x0800)
#define GPIO_PIN_12                ((uint16_t)0x1000)
#define GPIO_PIN_13                ((uint16_t)0x2000)
#define GPIO_PIN_14                ((uint16_t)0x4000)
#define GPIO_PIN_15                ((uint16_t)0x8000)

/* Pin states */
#define GPIO_PIN_RESET             0
#define GPIO_PIN_SET               1

/* Operating modes */
#define GPIO_MODE_INPUT            0x00U
#define GPIO_MODE_OUTPUT_PP        0x01U
#define GPIO_MODE_OUTPUT_OD        0x11U
#define GPIO_MODE_AF_PP            0x02U
#define GPIO_MODE_AF_OD            0x12U
#define GPIO_MODE_ANALOG           0x03U

/* Pull-up / Pull-down */
#define GPIO_NOPULL                0x00U
#define GPIO_PULLUP                0x01U
#define GPIO_PULLDOWN              0x02U

/* Speeds */
#define GPIO_SPEED_FREQ_LOW        0x00U
#define GPIO_SPEED_FREQ_MEDIUM     0x01U
#define GPIO_SPEED_FREQ_HIGH       0x02U
#define GPIO_SPEED_FREQ_VERY_HIGH  0x03U

typedef struct
{
    uint32_t Pin;       // Pins to configure (e.g. GPIO_PIN_5)
    uint32_t Mode;      // Mode: input, output, alternate, analog
                        // MODER       Configures the pin mode                        2 bits
                        //             00: Input, 01: Output, 10: Alternate, 11: Analog
    uint32_t Pull;      // Pull-up / Pull-down
                        // PUPDR       Configures internal resistors                  2 bits
                        //             00: No pull-up/down, 01: Pull-up, 10: Pull-down, 11: Reserved
    uint32_t Speed;     // Output speed
                        // OSPEEDR     Configures the pin speed                       2 bits
                        //             00: Low, 01: Medium, 10: High, 11: Very high
}GPIO_InitTypeDef;


/* Function prototypes */
void DIY_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void DIY_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t PinState);
uint8_t DIY_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void DIY_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif // DIY_GPIO_H