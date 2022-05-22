#include <mbed.h>
#include "encoder.h"
#include "constante_pinout.hpp"

#include "asserv.hpp"
#include "odometrie.hpp"
#include "securite.hpp"
#include "deplacement.hpp"
#include "communication.hpp"



DigitalOut led(LED1); // led sur la nucleo
BufferedSerial pc(USBTX,USBRX,9600); // liaison avec le pc

int main(){
    printf("Démarrage du programme\n");
    init_globale();
    init_fdc();
    init_pwm();

    // Traitements périodiques nécessaires :
    serie_traitement_periodique.attach_us(&lecture_arduinos, periode_serie);
    //odometrie_traitement_periodique.attach_us(&odometrie_periodique, periode_odometrie);
    securite_traitement_periodique.attach_us(&securite_periodique, periode_securite);

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
    

    bool condition = 0;
    while (1)
    {
        
        for (int k=0 ; k < 5 ; k++)
        {
            condition |= fdc[k];
            printf("%d ", fdc[k]);
        }
        printf("\t");
        for (int k=0 ; k < 4 ; k++)
        {
            condition |= dist[k];
            printf("%d ", dist[k]);
        }
        printf("\n");

        led.write(condition);

        //etalonnage_beta();

        

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
