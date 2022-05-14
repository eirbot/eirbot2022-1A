#include "encoder.h"

Encoder::Encoder(TIM_TypeDef *tim) {
    last_value = 0;
    _tim = tim;

    if( tim == TIM3 ) {

      // GPIO init
      __GPIOA_CLK_ENABLE();
      __TIM3_CLK_ENABLE();
      GPIO_InitTypeDef GPIO_InitStruct;
      GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7; // PA6 PA7
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      // TIMER init
      TIM_Encoder_InitTypeDef sConfig = {0};
      TIM_MasterConfigTypeDef sMasterConfig = {0};
      TIM_HandleTypeDef htim3;

      htim3.Instance = TIM3;
      htim3.Init.Prescaler = 0;
      htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
      htim3.Init.Period = 65535;
      htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
      htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
      sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
      sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
      sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
      sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
      sConfig.IC1Filter = 0;
      sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
      sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
      sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
      sConfig.IC2Filter = 0;
      if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK) {
        MBED_ERROR(1, "Encoder timer init failed");
      }
      sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
      sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
      if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) !=
          HAL_OK) {
        MBED_ERROR(1, "Encoder timer init failed");
      }

      // TIM3->EGR = 1;
      TIM3->CR1 = 1;

    }
    else if( tim == TIM4 ) {

      // GPIO init
      __GPIOB_CLK_ENABLE();
      __TIM4_CLK_ENABLE();
      GPIO_InitTypeDef GPIO_InitStruct;
      GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7; // PB6 PB7
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_PULLDOWN;
      GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

      // TIMER init
      TIM_Encoder_InitTypeDef sConfig = {0};
      TIM_MasterConfigTypeDef sMasterConfig = {0};
      TIM_HandleTypeDef htim4;

      htim4.Instance = TIM4;
      htim4.Init.Prescaler = 0;
      htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
      htim4.Init.Period = 65535;
      htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
      htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
      sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
      sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
      sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
      sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
      sConfig.IC1Filter = 0;
      sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
      sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
      sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
      sConfig.IC2Filter = 0;
      if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK) {
        MBED_ERROR(1, "Encoder timer init failed");
      }
      sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
      sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
      if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) !=
          HAL_OK) {
        MBED_ERROR(1, "Encoder timer init failed");
      }

      TIM4->CR1 = 1;
    }
    else {
      MBED_STATIC_ASSERT(1, "Wrong timer ref");
    }
}

int16_t Encoder::get_diff() {
    int16_t diff = _tim->CNT - last_value;

    // on veut diff > 0 donc on prend l'opposé pour le Timer 3 (droite)
    if (_tim == TIM3) {
      diff = -diff;
    }

    last_value = _tim->CNT;
    return diff;
}

void Encoder::reset() {
    _tim->CNT = 0;
    last_value = 0;
}
