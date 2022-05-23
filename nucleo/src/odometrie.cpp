#include "constante_pinout.hpp"
#include <cmath>

#include "odometrie.hpp"

void reset_xy(float x_pos, float y_pos)
{
    pos_x = x_pos;
    pos_y = y_pos;
}

void calcul_encoder()
{
    // Fonction utilisée pour le traitement périodique des encoders
    encoder_g = encoder_gauche.get_diff();
    encoder_gauche.reset();
    encoder_d = encoder_droit.get_diff();
    encoder_droit.reset();
    temoin_d+=encoder_d;
    temoin_g+=encoder_g;
}

void calcul_pos_xy()
{
    // Fonction utilisée pour le traitement périodique des encoders
    float dist_gauche = encoder_g * d_theta_rad * encoder_diametre; // en mm
    float dist_droit = encoder_d * d_theta_rad * encoder_diametre;  // en mm

    float dist = (dist_droit + dist_gauche) / 2;
    


    // float r, alpha;

    // if (dist_gauche != dist_droit)
    // {
    //     r = ((entre_axe / 2) * (dist_gauche + dist_droit)) / (dist_gauche - dist_droit);
    //     alpha = (entre_axe * (dist_gauche)) / (dist_gauche - dist_droit);
    // }
    // else
    // {
    //     r = 0.;
    //     alpha = 0.; // beta
    // }
    
    pos_x += - dist * sinf(beta);
    pos_y += dist * cosf(beta);
    beta += (dist_droit - dist_gauche) / entre_axe;
}
void calcul_vitesse()
{
    encoder_vitesse_d = ((float)(encoder_d)) / ((float)(tick_encoder)*6);
    encoder_vitesse_g = ((float)(encoder_g)) / ((float)(tick_encoder)*6); //((float)(encoder_g) * 60.0) / ((float)(tick_encoder)*360.)
}

void odometrie_periodique()
{
    calcul_encoder();
    calcul_vitesse();
    calcul_pos_xy();
}
