#include <mbed.h>
#include <math.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "odometrie.hpp"
#include "deplacement.hpp"

// #include "asserv.hpp"
// // #include "odometrie.hpp"
// #include "securite.hpp"
// #include "deplacement.hpp"
// #include "communication.hpp"

DigitalOut led(LED1);                  // led sur la nucleo
BufferedSerial pc(USBTX, USBRX, 9600); // liaison avec le pc



int main()
{
    printf("Démarrage du programme\n");
    init_globale();
    init_fdc();
    init_pwm();
    
    reset_xy(0., 0.);
    
    //wait_us(10e6);
    
    // Traitements périodiques nécessaires :
    // serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    odometrie_traitement_periodique.attach_us(&odometrie_periodique, periode_odometrie);
    // securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);
    // asserv_traitement_periodique.attach_us(&asserv_periodique, periode_asserv);

    avancer_primitif(5);
    wait_us(1e6);
    arret_moteur();
    while (1)
    {
        // printf("encoderG %4ld \t encoderD %4ld \t add_x %3.2f \t add_y %3.2f \t posX %3.2f \t posY %3.2f\n", encoder_g, encoder_d, temoin_add_x, temoin_add_y, pos_x, pos_y);
        printf("%ld  %ld \t %f  %f \t %f  %f\n",encoder_g, encoder_d,encoder_vitesse_g, encoder_vitesse_d, pos_x, pos_y);
        wait_us(1e6);
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