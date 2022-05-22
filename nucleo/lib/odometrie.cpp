#include "constante_pinout.hpp"
#include <cmath>

#include "odometrie.hpp"

void reset_xy(float x_pos, float y_pos)
{
    pos_x = x_pos;
    pos_y = y_pos;
}

void reset_beta(float angle)
{
    beta = angle;
}

void calcul_encoder()
{
    // Fonction utilisée pour le traitement périodique des encoders
    encoder_g = encoder_gauche.get_diff();
    encoder_gauche.reset();
    encoder_d = encoder_droit.get_diff();
    encoder_droit.reset();
}

void calcul_vitesse()
{
    encoder_vitesse_d = ((float)(encoder_d) * 60.0) / ((float)(tick_encoder)*2*M_PI);
    encoder_vitesse_g = ((float)(encoder_g) * 60.0) / ((float)(tick_encoder)*2*M_PI);
}

void calcul_pos_xy(volatile float* x_pos, volatile float* y_pos)
{
    // Fonction utilisée pour le traitement périodique des encoders
    float dist_gauche = encoder_g * d_theta * encoder_diametre;
    float dist_droit = encoder_d * d_theta * encoder_diametre;

    float r = 0.;
    float alpha = 0.;

    static float mem_x = pos_x;
    static float mem_y = pos_y;

    if (fabs(dist_gauche - dist_droit) < 1e-2 || fabs(dist_gauche - dist_droit) == 0.)
    {
        r = (dist_gauche * entre_axe) / (dist_gauche - dist_droit);
        alpha = (dist_gauche - dist_droit) / (entre_axe);
    }
    else
    {
        r = dist_gauche;
        alpha = beta;
    }
    *x_pos = mem_x + r * cosf(alpha);
    *y_pos = mem_y + r * sinf(alpha);
}

void odometrie_periodique()
{
    calcul_encoder();
    calcul_pos_xy(&pos_x, &pos_y);
}
