#include <mbed.h>
#include <math.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "odometrie.hpp"
#include "deplacement.hpp"
#include "securite.hpp"
#include "communication.hpp"

DigitalOut led(LED1);                  // led sur la nucleo
BufferedSerial pc(USBTX, USBRX, 9600); // liaison avec le pc

int main()
{
    init_globale();
    init_fdc();
    init_pwm();

    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);

    while (fdc[3] == 1) // on attends le fdc avec la tirette
    {
        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 1, 0, 0);
        }
    }

    chronometer.start();

    while (chronometer.elapsed_time().count() < (int64_t)(5 * 1e6))
    {
        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 1, 0, 0);
        }
    }
    
    odometrie_traitement_periodique.attach_us(&odometrie_periodique, periode_odometrie);

    while (chronometer.elapsed_time().count() < (int64_t)(95 * 1e6))
    {
        etalonnage_xybeta();
        
        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 2, 0, 0);
        }
        
        wait_us(5e6);

        if (baton_parole_afficheur == 1)
        {
            envoie_afficheur(0, 3, 0, 0);
        }
        break;

    }
    chronometer.stop();

    while (1)
    { 
        //printf("%ld  %ld \t %f  %f\n", temoin_g, temoin_d, pos_x * 10., pos_y * 10.);

        // envoie_afficheur(0,0,1,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,2,0);
        // wait_us(5e6);
        // envoie_afficheur(0,0,3,0);
        // wait_us(5e6);
    }
}
