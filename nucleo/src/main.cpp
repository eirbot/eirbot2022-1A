#include <mbed.h>
#include <math.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "asserv.hpp"

// #include "asserv.hpp"
// // #include "odometrie.hpp"
// #include "securite.hpp"
// #include "deplacement.hpp"
// #include "communication.hpp"

DigitalOut led(LED1);                  // led sur la nucleo
BufferedSerial pc(USBTX, USBRX, 9600); // liaison avec le pc

float temoin_add_x;
float temoin_add_y;

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
}

void calcul_pos_xy()
{
    // Fonction utilisée pour le traitement périodique des encoders
    float dist_gauche = encoder_g * d_theta_rad * encoder_diametre; // en mm
    float dist_droit = encoder_d * d_theta_rad * encoder_diametre;  // en mm

    float r, alpha;

    if (dist_gauche != dist_droit)
    {
        r = (dist_gauche * entre_axe) / (dist_gauche - dist_droit);
        alpha = (dist_gauche - dist_droit) / (entre_axe);
    }
    else
    {
        r = dist_gauche;
        alpha = beta;
    }

    float add_x = r * cosf(alpha - M_PI_2);
    float add_y = r * sinf(alpha - M_PI_2);

    pos_x += add_x;
    pos_y += add_y;
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

int main()
{
    printf("Démarrage du programme\n");
    init_globale();
    init_fdc();
    init_pwm();

    reset_xy(10., 10.);
    printf("posX %f \t posY %f\n", pos_x, pos_y);
    wait_us(1e6);

    // Traitements périodiques nécessaires :
    // serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    odometrie_traitement_periodique.attach_us(&odometrie_periodique, 1e3);
    // securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);
    // asserv_traitement_periodique.attach_us(&asserv_periodique, periode_asserv);

    while (1)
    {
        // printf("encoderG %4ld \t encoderD %4ld \t add_x %3.2f \t add_y %3.2f \t posX %3.2f \t posY %3.2f\n", encoder_g, encoder_d, temoin_add_x, temoin_add_y, pos_x, pos_y);
        printf("%ld  %ld \t  %f  %f\n",encoder_g, encoder_d, pos_x, pos_y);

        // wait_us(10e6);
        // envoie_afficheur(0,1,0,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,1,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,2,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,3,0);
        // wait_us(5e6);
    }
}

// chronometer.start();

// while (chronometer.elapsed_time().count() < (int64_t) (5*1e6))
// {
//     if (arret_bras == 1 || arret_afficheur == 1 || arret  )
// }
// // Attachement des traitement périodique :
// odometrie_traitement_periodique.attach(&);
// asserv_traitement_periodique.attach(&);

// while (chronometer.elapsed_time().count() < (int64_t) (95*1e6))
// {

// }
// chronometer.stop();