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
    // Fonction utilisée poencoder_dur le traitement périodique des encoders
    float dist_gauche = - (float) (encoder_g) * d_theta_rad * encoder_diametre; // en m
    float dist_droit =  (float) (encoder_d) * d_theta_rad * encoder_diametre;  // en m

    float dist = (dist_droit + dist_gauche) / 2.;
    
    beta += (dist_droit - dist_gauche) / (2*entre_axe);
    pos_x += dist * sinf(beta);
    pos_y -= dist * cosf(beta);
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
