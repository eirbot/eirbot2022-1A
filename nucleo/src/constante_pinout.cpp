#include <mbed.h>
#include "constante_pinout.hpp"
#include "encoder.h"
#include "securite.hpp"

// Encodeurs
Encoder encodeur_droit(TIM3);
Encoder encodeur_gauche(TIM4);

// Moteur droit
PwmOut pwm_droit(_pwm_droit);
DigitalOut dir_droit(_dir_droit);


// Moteur gauche
PwmOut pwm_gauche(_pwm_gauche);
DigitalOut dir_gauche(_dir_gauche);

// Fin de courses
InterruptIn fdc_avant_droit(_fdc_avant_droit, PullDown);
InterruptIn fdc_avant_gauche(_fdc_avant_gauche, PullDown);
InterruptIn fdc_arriere_droit(_fdc_arriere_droit, PullDown);
InterruptIn fdc_arriere_gauche(_fdc_arriere_gauche, PullDown);
InterruptIn fdc_galerie(_fdc_galerie,PullDown);

// Urgence 
InterruptIn urgence(_urgence, PullDown);

// Liaison série Arduino : UART 1
BufferedSerial bras(_bras_TX, _bras_RX, 9600);

// Liaison série Arduino : UART 3
BufferedSerial afficheur(_afficheur_TX, _afficheur_RX, 9600);

// Liaison I2C couleur
I2C couleur(_SDA, _SCL);

// Capteurs de distance
AnalogIn dist_avant_gauche(_dist_avant_gauche);
AnalogIn dist_avant_droit(_dist_avant_droit);
AnalogIn dist_arriere_gauche(_dist_arriere_gauche);
AnalogIn dist_arriere_droit(_dist_arriere_droit);
AnalogIn dist_gauche(_dist_gauche);
AnalogIn dist_droit(_dist_droit);

// Variables globales :
volatile bool fdc[5]; // avg avd ard arg gal
volatile bool dist[6]; // avg avd d ard arg g
volatile bool urgence_bouton;
volatile int32_t encoder[2]; // tick des encoder (gauche droite)
volatile float encoder_vitesse[2]; // vitesse des encoder (gauche droite)
volatile float pos_xy[2]; // position actuelle en xy
volatile float dest_xy[2]; // destination voulu en xy
volatile float dest_dalpha[2]; // distance et angle pour aller à dest_xy
volatile float beta; // angle du robot par rapport au bord bas

// Variable pour les port série :
char buffer_bras[buffer_size];
char buffer_afficheur[buffer_size];
char buffer_envoie[buffer_size];


void init_globale(){
    for (int k=0 ; k<5 ; k++) fdc[k] = 0;
    for (int k=0 ; k<6 ; k++) dist[k] = 0;
    for (int k=0 ; k<2 ; k++) 
    {
        encoder[k] = 0;
        encoder_vitesse[k] = 0;
        pos_xy[k] = 0;
        dest_xy[k] = 0;
        dest_dalpha[k] = 0;
    }
    urgence_bouton = 0;
    beta = 0;

    // Variable pour les port série :
    for (int k=0; k<buffer_size ; k++)
    {
        buffer_bras[k] = 0;
        buffer_afficheur[k] = 0;
    }

    // Configuration des pins :
    pwm_droit.period_us(periode_pwm);
    pwm_gauche.period_us(periode_pwm);

    fdc_avant_gauche.rise(&fdc_avg_1);
    fdc_avant_droit.rise(&fdc_avd_1);
    fdc_arriere_gauche.rise(&fdc_arg_1);
    fdc_arriere_droit.rise(&fdc_ard_1);
    fdc_galerie.rise(&fdc_gal_1);

    fdc_avant_gauche.fall(&fdc_avg_0);
    fdc_avant_droit.fall(&fdc_avd_0);
    fdc_arriere_gauche.fall(&fdc_arg_0);
    fdc_arriere_droit.fall(&fdc_ard_0);
    fdc_galerie.fall(&fdc_gal_0);
}
