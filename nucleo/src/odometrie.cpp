#include <mbed.h>
#include "constante_pinout.hpp"
#include <math.h>

#include "odometrie.hpp"

#ifndef odometrie_h
#define odometrie_h

void reset(float x_pos, float y_pos)
{
    pos_xy[0] = x_pos;
    pos_xy[1] = y_pos;
}

void reset_beta(float angle)
{
    beta = angle;
}

void calcul_encoder()
{
    // Fonction utilisée pour le traitement périodique des encoders
    encoder[0] = encodeur_gauche.get_diff();
    encoder[1] = encodeur_droit.get_diff();
}

void calcul_pos_xy()
{
    // Fonction utilisée pour le traitement périodique des encoders
    float dist_gauche = encoder[0] * d_theta * encoder_diametre;
    float dist_droit = encoder[1] * d_theta * encoder_diametre;
    float r, alpha;
    if ( fabs(dist_gauche - dist_droit) < 1e-5)
    {
        r = (dist_gauche * entre_axe) / (dist_gauche - dist_droit); 
        alpha = (dist_gauche - dist_droit) / (entre_axe);
        pos_xy[0] += r * cos(alpha); // on ajoute à l'axe x ce qu'on vient parcourir
        pos_xy[1] += r * sin(alpha); // on ajoute à l'axe y ce qu'on vient parcourir
    }
    else 
    {
        r = dist_gauche;
        alpha = beta;
        pos_xy[0] += r * cos(alpha); // on ajoute à l'axe x ce qu'on vient parcourir
        pos_xy[1] += r * sin(alpha); // on ajoute à l'axe y ce qu'on vient parcourir
    }
}

void odometrie_periodique()
{
    calcul_encoder();
    calcul_pos_xy();
}
#endif