#include "constante_pinout.hpp"
#include <cmath>

#include "odometrie.hpp"

void reset_xybeta(float x_pos, float y_pos, float angle)
{
    pos_x = x_pos;
    pos_y = y_pos;
    beta = angle;
}

void calculs_encoder()
{
    // Fonction utilisée pour le traitement périodique des encoders
    encoder_g = encoder_gauche.get_diff();
    encoder_gauche.reset();
    encoder_d = encoder_droit.get_diff();
    encoder_droit.reset();

    if (asserv_arret == 0)
    {
        if (encoder_angle_d > 180.)
        {
            encoder_angle_d -= 180.;
        }
        else if (encoder_angle_d < -180.)
        {
            encoder_angle_d += 180.;
        }
        if (encoder_angle_g > 180.)
        {
            encoder_angle_g -= 180.;
        }
        else if (encoder_angle_g < -180.)
        {
            encoder_angle_g += 180.;
        }

        encoder_angle_d += encoder_d * d_theta_deg;
        encoder_angle_g += -encoder_g * d_theta_deg;
    }

    encoder_vitesse_d = ((float)(encoder_d)) / ((float)(tick_encoder)*6);  // tr/min
    encoder_vitesse_g = -((float)(encoder_g)) / ((float)(tick_encoder)*6); //((float)(encoder_g) * 60.0) / ((float)(tick_encoder)*360.)

    dist_gauche = -(float)(encoder_g)*d_theta_rad * encoder_diametre; // en m
    dist_droit = (float)(encoder_d)*d_theta_rad * encoder_diametre;   // en m

    dist_robot = (dist_droit + dist_gauche) / 2.;
}

void calcul_pos_xy()
{
    // Fonction utilisée poencoder_dur le traitement périodique des encoders

    beta += (dist_droit - dist_gauche) / (2 * entre_axe);
    pos_x += (dist_robot * sinf(beta)) / 10.;
    pos_y -= (dist_robot * cosf(beta)) / 10.;
}

void odometrie_periodique()
{
    calculs_encoder();
    calcul_pos_xy();
}
