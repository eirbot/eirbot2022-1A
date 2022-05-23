#include "constante_pinout.hpp"
#include "asserv.hpp"
#include <math.h>

float PI(float erreur)
{
    static float y_n1 = 0;
    float y_n = y_n1 + erreur * (K_PI_p + K_PI_i * (float)periode_asserv);

    y_n1 = y_n;
    return y_n;
}

float P(float erreur)
{
    float y_n = K_P_p;

    return y_n;
}

void conversion_dalpha()
{
    // convertit la consigne en rotation + translation stocké dans dest_dalpha d en 0 et alpha en 1
    // calcul de la distance
    dest_dist = sqrt(pow(dest_x - pos_x, 2) + pow(dest_x - pos_x, 2));

    // calcul de l'angle :
    if ((dest_y > pos_y) and (dest_x > pos_x))
    {
        dest_alpha = atan2(fabs(dest_y - pos_y), fabs(dest_x - pos_x));
    }
    else
    {
        dest_alpha = 180 - atan2(fabs(dest_y - pos_y), fabs(dest_x - pos_x));
    }

    // calcul de l'incrément de béta :
    float increment;
    if (dest_y > pos_y)
    {
        increment = dest_alpha - beta;
    }
    else
    {
        increment = beta - dest_alpha;
    }

    beta += increment;
}

void asserv_periodique()
{
    if (asserv_arret == 0)
    {
        // code en cas d'urgence
    }
    else
    {
        // secu
    }
}