## 1. Introducción

El microcontrolador STM32F446RE permite controlar los pines GPIO (General Purpose Input/Output) mediante registros especiales. Cada puerto (GPIOA, GPIOB, etc.) tiene registros para configurar el modo, tipo de salida, velocidad, resistencias de pull-up/pull-down y para leer/escribir el estado de los pines.

---

## 2. Estructura de los registros GPIO

- **MODER**: Selecciona el modo de cada pin (entrada, salida, alternate function, analógico). Cada pin usa 2 bits.
- **OTYPER**: Define el tipo de salida (push-pull u open-drain). Cada pin usa 1 bit.
- **OSPEEDR**: Configura la velocidad de salida. Cada pin usa 2 bits.
- **PUPDR**: Configura resistencias de pull-up/pull-down. Cada pin usa 2 bits.
- **IDR**: Permite leer el estado lógico de los pines (entrada digital).
- **ODR**: Permite escribir el estado lógico de los pines (salida digital).
- **BSRR**: Permite poner a 1 o a 0 un pin de forma atómica.

---

## 3. Funciones implementadas

### 3.1 DIY_GPIO_Init

Configura uno o varios pines de un puerto GPIO según la estructura `GPIO_InitTypeDef`.

**Justificación**:  
Se accede directamente a los registros `MODER`, `OTYPER`, `OSPEEDR` y `PUPDR` para cada pin seleccionado.  
Por ejemplo, para el registro `MODER`, cada pin usa 2 bits, así que para el pin N, los bits relevantes son `[2N+1:2N]`.

**Fragmento relevante:**
```c
GPIOx->MODER &= ~(0x3U << (position * 2)); // Limpia los 2 bits del pin
GPIOx->MODER |= ((GPIO_Init->Mode & 0x3U) << (position * 2)); // Escribe el nuevo modo
```
Esto sigue la especificación del manual de referencia (RM0390, sección 8.4.1).

### 3.2 DIY_GPIO_WritePin

Permite poner un pin en alto o bajo usando el registro BSRR, que permite operaciones atómicas (seguras frente a interrupciones).

**Justificación:**  
El registro BSRR tiene los 16 bits bajos para poner pines a 1 y los 16 altos para ponerlos a 0.  
Por ejemplo, para poner el pin 5 en alto:
```c
GPIOx->BSRR = (1 << 5);
```
Para ponerlo en bajo:
```c
GPIOx->BSRR = (1 << (5 + 16));
```

### 3.3 DIY_GPIO_ReadPin

Lee el estado lógico de un pin usando el registro IDR.

**Justificación:**  
El registro IDR refleja el estado de los pines configurados como entrada o salida.  
Para leer el pin 5:
```c
(GPIOx->IDR & (1 << 5)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
```

### 3.4 DIY_GPIO_TogglePin

Cambia el estado lógico de un pin (de 1 a 0 o de 0 a 1) usando el registro ODR.

**Justificación:**  
El registro ODR contiene el valor de salida de todos los pines.  
Para alternar el pin 5:
```c
GPIOx->ODR ^= (1 << 5);
```

---

## 4. Ejemplo de uso

_(Agrega aquí un ejemplo de inicialización y uso de las funciones DIY GPIO)_

---

## 5. Referencias

- Manual de referencia STM32F446RE (RM0390)
- Datasheet STM32F446RE

---

## Conclusión

Estas funciones permiten controlar los GPIO del STM32F446RE de forma eficiente y directa, entendiendo y manipulando los registros tal como lo describe el fabricante.

Este tutorial explica cómo se implementaron las funciones básicas de manejo de GPIO para el microcontrolador **STM32F446RE** usando acceso directo a registros, justificando cada paso con base en el datasheet y el manual de referencia.
