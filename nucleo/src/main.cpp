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

    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);

    while (fdc_arg == 1) // on attends le fdc avec la tirette
    {
        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 1, 0, 0);
        }
    }

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

    bool envoie_msg_2 = 0;
    bool envoie_msg_3 = 0;
    while (chronometer.elapsed_time().count() < (int64_t)(95 * 1e6))
    {
        if (envoie_msg_2 == 0)
        {
            envoie_afficheur(0, 0, 2, 0);
            envoie_msg_2 = 1;
        }
        etalonnage_xybeta();
        avancer_primitif(5);
        wait_us(1e6);
        arret_moteur();
        asserv_arret = 0;
        dest_alpha = 90;
        wait_us(5e6);
        asserv_arret = 1;

        wait_us(5e6);

        if (chronometer.elapsed_time().count() > 80e6 && envoie_msg_3 == 0)
        {
            envoie_afficheur(0, 0, 3, 0);
            envoie_msg_3 = 1;
        }
    }
    chronometer.stop();

    while (1)
    {
        // envoie_afficheur(0,0,1,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,2,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,3,0);
        // wait_us(5e6);
    }
}
