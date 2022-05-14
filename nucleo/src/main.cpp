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
    // chronometer.start();
    // securite_traitement_periodique.attach(&lecture_GP2, 10ms);
    // while (chronometer.elapsed_time().count() < (int64_t) (5*1e6))
    // {
    //     printf("dist : %d\n", dist[0]);
    // }
    // // attachement des traitement périodique :
    // // odometrie_traitement_periodique.attach(&);
    // // asserv_traitement_periodique.attach(&);
    // // buffer_traitement_periodique.attach(&);
    
    // securite_traitement_periodique.detach(); 
    // while (chronometer.elapsed_time().count() < (int64_t) (95*1e6))
    // {

    //     printf("dist : %d\n", dist[0]);
    // }
    // chronometer.stop();

    char message[32];
    int n = 0;

    while (1)
    {
        
        n = 0;
        // envoyer de s'arreter au bras !
        if (bras.readable())
        {
            bras.read(&buffer_bras, buffer_size);
            //printf("%s\n",buffer_bras);
            // for (int k = 0 ; k < buffer_size ; k++) 
            // {
            //     if(buffer_bras[k] != 0)
            //     {
            //         message[n] = buffer_bras[k];
            //         n += 1;
            //     }
            //     buffer_bras[k] = 0;
            // } 
        }
        printf("Message: %s\n", message);
        //wait_us(5*1e5);
        
    }
}
