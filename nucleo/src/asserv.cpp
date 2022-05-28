#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "deplacement.hpp"
#include <math.h>

float PI(float erreur, float Kp, float Ki)
{
    static float y_n1 = 0;
    static float erreur_n1 = 0;
    float y_n = y_n1 + erreur * (Kp + Ki * (float)(periode_asserv*1e-6)) - erreur_n1*Kp;

    y_n1 = y_n;
    erreur_n1=erreur;
    return y_n;
}

float P(float erreur, float Kp)
{
    float y_n = Kp * erreur;

    return y_n;
}

float second_ordre(float x_n)
{
    static float y_n1;
    static float y_n2;
    static float x_n1;
    static float x_n2;

    float y_n = 1.95 * y_n1 - 0.9512 * y_n2 + x_n1*0.0003073 + x_n2 * 0.0003023;
    y_n2 = y_n1;
    y_n1 = y_n;
    x_n2 = x_n1;
    x_n1 = x_n;
     
    return y_n;
}

float second_ordre_bis(float x_n, float t_rep)
{
    float omega = 5/t_rep;
    float a = 1./(omega*omega);
    float b = (2*1)/omega;

    static float y_n2;
    static float y_n1;
    static float x_n1;
    static float x_n2;

    float y_n = (2*y_n1 - y_n2 + x_n - 2 * x_n1 + x_n2)/(1+b*periode_asserv+a*periode_asserv*periode_asserv);
    y_n2 = y_n1;
    y_n1 = y_n;
    x_n2 = x_n1;
    x_n1 = x_n;
     
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

uint8_t sature(float valeur, uint8_t min, uint8_t max)
{
    if (valeur < min)
    {
        return min;
    }
    if (valeur > max)
    {
        return max;
    }
    return (uint8_t)valeur;
}

void asserv_periodique()
{
    if (asserv_arret == 0)
    {
        if (dest_alpha != 2742.)
        {
            erreur_angle = dest_alpha - (roue_diametre/entre_axe)*((encoder_angle_d - encoder_angle_g)/2.);
            erreur_angle_d = dest_alpha/(roue_diametre/entre_axe) - encoder_angle_d; //(roue_diametre/entre_axe)*((encoder_angle_d - encoder_angle_g)/2.)
            erreur_angle_g = dest_alpha/(roue_diametre/entre_axe) - encoder_angle_g;
            float consignef_d = PI(erreur_angle_d, Kp, Ki);
            float consignef_g = PI(erreur_angle_g, Kp, Ki);

            bool sens_d = 1;
            bool sens_g = 0;
            if (consignef_d < 0.)
            {
                sens_d = 0;
            }
            if (consignef_g < 0.)
            {
                sens_g = 1;
            }

            uint8_t consigne_d = sature(fabs(consignef_d), 0, 20);
            uint8_t consigne_g = sature(fabs(consignef_g), 0, 20);
            if ((consignef_d > eps) && (consigne_d == 1))
            {
                consigne_d = 2;
            }
            if ((consignef_g > eps) && (consigne_d == 1))
            {
                consigne_g = 2;
            }
            // uint8_t consigne_g = sature((1-eps)*fabs(consignef), 0, 10);

            roue_d(consigne_d, sens_d);
            roue_g(consigne_g, sens_g);
        }

        if (dest_dist != 2742.)
        {
            float erreur_dist= dest_dist - (encoder_dist_g+encoder_dist_d)/2.;
            float consignef = PI(erreur_dist, Kp, Ki);

            bool sens_g = 1;
            bool sens_d = 1;
            if (consignef < 0.)
            {
                sens_g = 0;
                sens_d = 0;
            }

            uint8_t consigne_d = sature(fabs(consignef), 0, 15);
            uint8_t consigne_g = sature(fabs(consignef), 0, 15);

            roue_d(consigne_d, sens_d);
            roue_g(consigne_g, sens_g);
        }
    }
}

// void second_ordre(float entree, float ksi, float wu)
// {

// }
