#include <mbed.h>
#include "constante_pinout.hpp"
#include <math.h>

#include "asserv.hpp"

#ifndef asserv_h
#define asserv_h

float PI(float erreur)
{
    static float y_n1 = 0;
    float y_n = y_n1 + erreur * (Kp + Ki * (float)periode_asserv);

    y_n1 = y_n;
    return y_n;
}

void conversion_consigne()
{
    // convertit la consigne en rotation + translation stocké dans dest_dalpha d en 0 et alpha en 1
    // calcul de la distance
    dest_dalpha[0] = sqrt(pow(dest_xy[0] - pos_xy[0], 2) + pow(dest_xy[1] - pos_xy[0], 2));
    
    // calcul de l'angle :
    if ((dest_xy[1] > pos_xy[1]) and (dest_xy[0] > pos_xy[0]))
    {
        dest_dalpha[1] = atan2(fabs(dest_xy[1] - pos_xy[1]), fabs(dest_xy[0] - pos_xy[0]));
    }
    else
    {
        dest_dalpha[1] = 180 - atan2(fabs(dest_xy[1] - pos_xy[1]), fabs(dest_xy[0] - pos_xy[0]));
    }

    // calcul de l'incrément de béta :
    float increment;
    if (dest_xy[1] > pos_xy[1])
    {
        increment = dest_dalpha[1] - beta;
    }
    else
    {
        increment = beta - dest_dalpha[1];
    }

    beta += increment;
}

float vitesse(uint8_t roue)
{
    // Renvoi la vitesse de la roue (roue droite 0 et roue gauche 1)
    return ((float)(encoder[roue]) * 60.0) / ((float)(tick_encoder)*360.0);
}

void calcul_vitesse()
{
    // fonction exécutée périodiquement pour le calcul de la vitesse pour l'asservissement bite
    encoder_vitesse[0] = vitesse(0);
    encoder_vitesse[1] = vitesse(1);
}

#endif
