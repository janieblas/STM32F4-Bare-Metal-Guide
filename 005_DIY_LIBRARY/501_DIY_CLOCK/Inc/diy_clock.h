#ifndef DIY_CLOCK_H
#define DIY_CLOCK_H

#include "stm32f4xx.h"
#include "stm32f446xx.h"

#define __HAL_RCC_GPIOA_CLK_ENABLE()   (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define __HAL_RCC_GPIOB_CLK_ENABLE()   (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define __HAL_RCC_GPIOC_CLK_ENABLE()   (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
  
/** @defgroup RCC_HSE_Config HSE Config
  * @{
  */
#define RCC_HSE_OFF                      0x00000000U
#define RCC_HSE_ON                       RCC_CR_HSEON
//#define RCC_HSE_BYPASS                   ((uint32_t)(RCC_CR_HSEBYP | RCC_CR_HSEON))

/** @defgroup RCC_Oscillator_Type Oscillator Type
  * @{
  */
#define RCC_OSCILLATORTYPE_NONE            0x00000000U
#define RCC_OSCILLATORTYPE_HSE             0x00000001U
#define RCC_OSCILLATORTYPE_HSI             0x00000002U
#define RCC_OSCILLATORTYPE_LSE             0x00000004U
#define RCC_OSCILLATORTYPE_LSI             0x00000008U

/** @defgroup RCC_HSI_Config HSI Config
  * @{
  */
#define RCC_HSI_OFF                      ((uint8_t)0x00)
#define RCC_HSI_ON                       ((uint8_t)0x01)
#define RCC_HSICALIBRATION_DEFAULT       0x10U         /* Default HSI calibration trimming value */

/** @defgroup RCC_PLL_Config PLL Config
  * @{
  */
#define RCC_PLL_NONE                      ((uint8_t)0x00)
#define RCC_PLL_OFF                       ((uint8_t)0x01)
#define RCC_PLL_ON                        ((uint8_t)0x02)


/** @defgroup RCC_System_Clock_Type System Clock Type
  * @{
  */
#define RCC_CLOCKTYPE_SYSCLK             0x00000001U
#define RCC_CLOCKTYPE_HCLK               0x00000002U
#define RCC_CLOCKTYPE_PCLK1              0x00000004U
#define RCC_CLOCKTYPE_PCLK2              0x00000008U


/** @defgroup RCC_System_Clock_Source System Clock Source
  * @note     The RCC_SYSCLKSOURCE_PLLRCLK parameter is available only for
  *           STM32F446xx devices.
  * @{
  */
#define RCC_SYSCLKSOURCE_HSI             RCC_CFGR_SW_HSI
#define RCC_SYSCLKSOURCE_HSE             RCC_CFGR_SW_HSE
#define RCC_SYSCLKSOURCE_PLLCLK          RCC_CFGR_SW_PLL
#define RCC_SYSCLKSOURCE_PLLRCLK         ((uint32_t)(RCC_CFGR_SW_0 | RCC_CFGR_SW_1))


/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
  * @{
  */
#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512

/** @defgroup RCC_APB1_APB2_Clock_Source APB1/APB2 Clock Source
  * @{
  */
#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16

#define FLASH_LATENCY_0                FLASH_ACR_LATENCY_0WS   /*!< FLASH Zero Latency cycle      */
#define FLASH_LATENCY_1                FLASH_ACR_LATENCY_1WS   /*!< FLASH One Latency cycle       */
#define FLASH_LATENCY_2                FLASH_ACR_LATENCY_2WS   /*!< FLASH Two Latency cycles      */
#define FLASH_LATENCY_3                FLASH_ACR_LATENCY_3WS   /*!< FLASH Three Latency cycles    */
#define FLASH_LATENCY_4                FLASH_ACR_LATENCY_4WS   /*!< FLASH Four Latency cycles     */
#define FLASH_LATENCY_5                FLASH_ACR_LATENCY_5WS   /*!< FLASH Five Latency cycles     */
#define FLASH_LATENCY_6                FLASH_ACR_LATENCY_6WS   /*!< FLASH Six Latency cycles      */
#define FLASH_LATENCY_7                FLASH_ACR_LATENCY_7WS   /*!< FLASH Seven Latency cycles    */
#define FLASH_LATENCY_8                FLASH_ACR_LATENCY_8WS   /*!< FLASH Eight Latency cycles    */
#define FLASH_LATENCY_9                FLASH_ACR_LATENCY_9WS   /*!< FLASH Nine Latency cycles     */
#define FLASH_LATENCY_10               FLASH_ACR_LATENCY_10WS  /*!< FLASH Ten Latency cycles      */
#define FLASH_LATENCY_11               FLASH_ACR_LATENCY_11WS  /*!< FLASH Eleven Latency cycles   */
#define FLASH_LATENCY_12               FLASH_ACR_LATENCY_12WS  /*!< FLASH Twelve Latency cycles   */
#define FLASH_LATENCY_13               FLASH_ACR_LATENCY_13WS  /*!< FLASH Thirteen Latency cycles */
#define FLASH_LATENCY_14               FLASH_ACR_LATENCY_14WS  /*!< FLASH Fourteen Latency cycles */
#define FLASH_LATENCY_15               FLASH_ACR_LATENCY_15WS  /*!< FLASH Fifteen Latency cycles  */

/** 
  * @brief  HAL Status structures definition  
  */  
typedef enum 
{
  DIY_OK       = 0x00U,
  DIY_ERROR    = 0x01U,
  DIY_BUSY     = 0x02U,
  DIY_TIMEOUT  = 0x03U
} DIY_StatusTypeDef;

/** 
  * @brief  HAL Lock structures definition  
  */
typedef struct
{
  uint32_t PLLState;   /*!< The new state of the PLL.
                            This parameter can be a value of @ref RCC_PLL_Config                      */

  uint32_t PLLSource;  /*!< RCC_PLLSource: PLL entry clock source.
                            This parameter must be a value of @ref RCC_PLL_Clock_Source               */

  uint32_t PLLM;       /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 63    */

  uint32_t PLLN;       /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 50 and Max_Data = 432 
                            except for STM32F411xE devices where the Min_Data = 192 */

  uint32_t PLLP;       /*!< PLLP: Division factor for main system clock (SYSCLK).
                            This parameter must be a value of @ref RCC_PLLP_Clock_Divider             */

  uint32_t PLLQ;       /*!< PLLQ: Division factor for OTG FS, SDIO and RNG clocks.
                            This parameter must be a number between Min_Data = 2 and Max_Data = 15    */

  uint32_t PLLR;       /*!< PLLR: PLL division factor for I2S, SAI, SYSTEM, SPDIFRX clocks.*/
}RCC_PLLInitTypeDef;

/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t OscillatorType;       /*!< The oscillators to be configured.
                                      This parameter can be a value of @ref RCC_Oscillator_Type                   */

  uint32_t HSEState;             /*!< The new state of the HSE.
                                      This parameter can be a value of @ref RCC_HSE_Config                        */

  uint32_t LSEState;             /*!< The new state of the LSE.
                                      This parameter can be a value of @ref RCC_LSE_Config                        */

  uint32_t HSIState;             /*!< The new state of the HSI.
                                      This parameter can be a value of @ref RCC_HSI_Config                        */

  uint32_t HSICalibrationValue;  /*!< The HSI calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
                                       This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

  uint32_t LSIState;             /*!< The new state of the LSI.
                                      This parameter can be a value of @ref RCC_LSI_Config                        */

  RCC_PLLInitTypeDef PLL;        /*!< PLL structure parameters                                                    */
}RCC_OscInitTypeDef;


/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  uint32_t ClockType;             /*!< The clock to be configured.
                                       This parameter can be a value of @ref RCC_System_Clock_Type      */

  uint32_t SYSCLKSource;          /*!< The clock source (SYSCLKS) used as system clock.
                                       This parameter can be a value of @ref RCC_System_Clock_Source    */

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_AHB_Clock_Source       */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_APB1_APB2_Clock_Source */

}RCC_ClkInitTypeDef;


DIY_StatusTypeDef DIY_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
DIY_StatusTypeDef DIY_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);
void DIY_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void DIY_RCC_EnableCSS(void);
void DIY_RCC_DisableCSS(void);


#endif // DIY_CLOCK_H