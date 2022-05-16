#include <mbed.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "odometrie.hpp"
#include "securite.hpp"
#include "deplacement.hpp"

// Chronomètre 
Timer chronometer; // chronomètre pour le départ

// Traitement périodique 
Ticker odometrie_traitement_periodique;
Ticker asserv_traitement_periodique;
Ticker serie_traitement_periodique;
Ticker securite_traitement_periodique;

DigitalOut led(LED1); // led sur la nucleo
BufferedSerial pc(USBTX,USBRX,9600); // liaison avec le pc

int main(){
    printf("Démarrage du programme\n");
    init_globale();
    init_fdc();
    init_pwm();
    // Traitements périodiques nécessaires :
    buffer_traitement_periodique.attach(&lectur);
    odometrie_traitement_periodique.attach(&);

    // chronometer.start();
    
    // while (chronometer.elapsed_time().count() < (int64_t) (5*1e6))
    // {
    //     if (arret_bras == 1 || arret_afficheur == 1 || arret  )
    // }
    // // Attachement des traitement périodique :
    // odometrie_traitement_periodique.attach(&);
    // asserv_traitement_periodique.attach(&);
    
    
    // securite_traitement_periodique.detach(); 
    // while (chronometer.elapsed_time().count() < (int64_t) (95*1e6))
    // {

        
    // }
    // chronometer.stop();

    while (1)
    {
        bool condition = 0;
        for (int k=0 ; k < 5 ; k++)
        {
            condition |= fdc[k];
        }
        for (int k=0 ; k < 4 ; k++)
        {
            condition |= dist[k];
        }
        if (condition == true)
        {
            led.write(1);
        }
    }
}
