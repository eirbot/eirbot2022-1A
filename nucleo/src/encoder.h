#ifndef ENCODER_H_
#define ENCODER_H_

#include "mbed.h"

class Encoder {
    public:
        Encoder(TIM_TypeDef *tim);
        int16_t get_diff();
        void reset();

    private:
        uint16_t last_value;
        TIM_TypeDef *_tim;
};

#endif // ENCODER_H_
