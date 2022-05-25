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

int main()
{
    init_globale();
    init_fdc();
    init_pwm();

    /***************************************
     ************** avant match ************
     ****************************************/

    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);

    while (fdc_arg == 1) // on attends le fdc avec la tirette
    {
        if (baton_parole_afficheur == 1)
        {
            printf("recopie afficheur faite");
            envoie_afficheur(0, 1, 0, 0);
        }
    }

    /***************************************
     ************** début match ************
     ****************************************/
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
    /***************************************
     **** Tant qu'y a pelouse y a match ****
     ****************************************/
    bool envoie_msg_2 = 0;
    bool envoie_msg_3 = 0;
    while (chronometer.elapsed_time().count() < (int64_t)(95 * 1e6))
    {
        if (envoie_msg_2 == 0)
        {
            envoie_afficheur(0, 0, 2, 0);
            envoie_msg_2 = 1;
        }
        
        avancer_primitif(4);

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
}
