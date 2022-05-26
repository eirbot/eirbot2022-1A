#include <mbed.h>
#include <math.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "odometrie.hpp"
#include "deplacement.hpp"
#include "securite.hpp"
#include "communication.hpp"
#include "securite.hpp"

DigitalOut led(LED1);                  // led sur la nucleo
BufferedSerial pc(USBTX, USBRX, 9600); // liaison avec le pc

void variable_glob_directe()
{
    char buffer[10];
    static uint8_t compteur_var = 0;
    if (pc.readable())
    {
        pc.read(buffer, 10);
        switch (compteur_var)
        {
        case 0:
            dest_alpha = atof(buffer);
            compteur_var++;
            break;
        case 1:
            Kp = atof(buffer);
            compteur_var++;
            break;
        case 2:
            Ki = atof(buffer);
            compteur_var++;
            break;
        case 3:
            eps = atof(buffer);
            compteur_var++;
            break;
        case 4:
            compteur_var = 0;
            break;
        default:
            break;
        }
        for (int k = 0; k < 10; k++)
        {
            buffer[k] = 0;
        }
    }
    else
    {
        pc.sync();
    }
    printf("dest_alpha: %2.3f \t Kp : %2.3f \t Ki : %2.3f \t eps : %2.3f \n", dest_alpha, Kp, Ki, eps);
}

int main()
{
    init_globale();
    init_fdc();
    init_pwm();

    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);
    
    
    // ***************** on attends le fdc avec la tirette ***************** 
    while (fdc_arg == 1) 
    {
        variable_glob_directe();
        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 1, 0, 0);
        }
    }

    chronometer.start();
    odometrie_traitement_periodique.attach_us(&odometrie_periodique, periode_odometrie);
    asserv_traitement_periodique.attach_us(&asserv_periodique, periode_asserv);

    asserv_arret = 0; // lance l'asserv

    float consigne_dist = 34.;

    while ((encoder_dist_d < consigne_dist) || (chronometer.elapsed_time().count() < (int64_t)(15 * 1e6)))
    {
        if (condition_dist == 1)
        {
            while (condition_dist == 1)
            {
                asserv_arret = 1; // désactive l'asserv
                arret_moteur(); // arret des moteurs
            }
            asserv_arret = 0; //réactive l'asserv
        }
        printf("angle_d %3.2f angle_g %3.2f \t dist_d %3.2f  dist_g %3.2f \t c_d %2d c_g %2d\n", encoder_angle_d, encoder_angle_g, encoder_dist_d, encoder_dist_g, pwm_droit.read_pulsewitdth_us(), pwm_gauche.read_pulsewitdth_us());
    }
// !****************************  BLOQUE  ****************************!
    while (1)
    {
        // bloque ici
    }

    float dest_encoder = 10.;
    // float pas_dest_encoder = 1.5;
    uint8_t consigne_test = 5;
    while (encoder_dist_d < dest_encoder || encoder_dist_g < dest_encoder)
    {
        if (condition_dist == 1)
        {
            break;
        }
        avancer_primitif(consigne_test);
        printf("D : %3.2f \t G : %3.2f \t\t D  %3.2f G  %3.2f\n", encoder_dist_d, encoder_dist_g, dist_droit, dist_gauche);
    }
    dest_dist = 1001.; // pour encoder_dist_X

    envoie_bras(0, 3, 0, 0, 0); // processus pour choper le palais

    while (bras_etat == 0)
    {
        // le bras est occupé
        arret_moteur();
        if (condition_dist == 1)
        {
            envoie_bras(0, 0, 0, 0, 0); // arret bras
            break;
        }
    }

    while (1)
    {
        arret_moteur();
        printf("fini\n");
    }
}

/*

init_globale();
    init_fdc();
    init_pwm();

    // **************************************
    // ************* avant match ************
    // **************************************

    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);

    while (fdc_arg == 1) // on attends le fdc avec la tirette
    {
        variable_glob_directe();
        if (baton_parole_afficheur == 1)
        {
            printf("recopie afficheur faite");
            envoie_afficheur(0, 1, 0, 0);
        }
    }

    // ***************************************
    // ************* début match ************
    // **************************************
    chronometer.start();
    odometrie_traitement_periodique.attach_us(&odometrie_periodique, periode_odometrie);

    bool envoie_msg_1 = 0;
    while (chronometer.elapsed_time().count() < (int64_t)(5 * 1e6))
    {
        if (envoie_msg_1 == 0)
        {
            envoie_afficheur(0, 0, 1, 0);
            envoie_msg_1 = 1;
        }
    }
    // **************************************
    // *** Tant qu'y a pelouse y a match ****
    // **************************************
    bool envoie_msg_2 = 0;
    bool envoie_msg_3 = 0;
    while (chronometer.elapsed_time().count() < (int64_t)(95 * 1e6))
    {
        if (envoie_msg_2 == 0)
        {
            envoie_afficheur(0, 0, 2, 0);
            envoie_msg_2 = 1;
        }

        if (condition_dist == 1 ||condition_fdc == 1)
        {
            break;
        }
        else
        {
            avancer_primitif(5);
        }
        printf("%d %d %d %d %d \n",condition_dist, dist_arg, dist_ard, dist_avg, dist_avd);

        if (chronometer.elapsed_time().count() > (int64_t)(85 * 1e6) && envoie_msg_3 == 0)
        {
            envoie_afficheur(0, 0, 3, 0);
            envoie_msg_3 = 1;
        }
    }
    chronometer.stop();

    while (1)
    {
        arret_moteur();
    }

*/
