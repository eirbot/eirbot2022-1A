#include "constante_pinout.hpp"

#include "odometrie.hpp"
#include "deplacement.hpp"

void avancer_primitif(uint16_t pwm)
{
    dir_droit.write(1);
    dir_gauche.write(1);
    pwm_droit.pulsewidth_us(pwm);
    pwm_gauche.pulsewidth_us(pwm);
}

void reculer_primitif( uint16_t pwm)
{
    dir_droit.write(0);
    dir_gauche.write(0);
    pwm_droit.pulsewidth_us(pwm);
    pwm_gauche.pulsewidth_us(pwm);
}

void arret_moteur()
{
    dir_droit.write(1);
    dir_gauche.write(1);
    pwm_droit.pulsewidth_us(0);
    pwm_gauche.pulsewidth_us(0);
}

void etalonnage_xybeta()
{
    while (fdc[3] == 0 && fdc[4] == 0)
    {
        reculer_primitif(4);
    }
    arret_moteur();
    reset_xybeta(0.4,0.02,0);
}