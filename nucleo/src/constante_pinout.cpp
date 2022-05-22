#include <mbed.h>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "securite.hpp"

// Encodeurs
Encoder encoder_droit(TIM3);
Encoder encoder_gauche(TIM4);

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
InterruptIn fdc_galerie(_fdc_galerie, PullDown);

// Urgence
InterruptIn urgence(_urgence, PullDown);

// Liaison série Arduino : UART 1
BufferedSerial bras(_bras_TX, _bras_RX, baud_rate);

// Liaison série Arduino : UART 3
BufferedSerial afficheur(_afficheur_TX, _afficheur_RX, baud_rate);

// Liaison I2C couleur
I2C couleur(_SDA, _SCL);

// Capteurs de distance
AnalogIn dist_avant_gauche(_dist_avant_gauche);
AnalogIn dist_avant_droit(_dist_avant_droit);
AnalogIn dist_arriere_gauche(_dist_arriere_gauche);
AnalogIn dist_arriere_droit(_dist_arriere_droit);

// Variables globales :
volatile bool fdc[5];  // avg avd ard arg gal
volatile bool dist[4]; // avg avd d ard arg g
volatile bool urgence_bouton;
volatile bool asserv_arret;

volatile int32_t encoder_d;       // tick de encoder droit
volatile int32_t encoder_g;       // tick de encoder gauche
volatile float encoder_vitesse_d; // vitesse de l'encoder droit
volatile float encoder_vitesse_g; //  vitesse de l'encoder gauche
float pos_x;             // position actuelle en x
float pos_y;             // position actuelle en y
volatile float dest_x;            // destination voulu en x
volatile float dest_y;            // destination voulu en y
volatile float dest_dist;         // distance pour aller à dest_x et dest_y
volatile float dest_alpha;        // angle pour aller à dest_x et dest_y
volatile float beta;              // angle du robot par rapport au bord bas

// Variable pour les port série :
char buffer_bras[buffer_size];
char buffer_afficheur[buffer_size];
char buffer_envoie[1];
volatile char reception;
volatile char equipe;
volatile bool capt_distance;
volatile bool arbitre;
volatile bool afficheur_arret;
volatile bool bras_etat;
volatile bool bras_arret;

// Chronomètre
Timer chronometer; // chronomètre pour le départ

// Traitement périodique
Ticker odometrie_traitement_periodique;
Ticker asserv_traitement_periodique;
Ticker serie_traitement_periodique;
Ticker securite_traitement_periodique;

void init_globale()
{
    for (int k = 0; k < 5; k++)
    {
        fdc[k] = 0;
    }

    for (int k = 0; k < 4; k++)
    {
        dist[k] = 0;
    }

    encoder_d = 0;
    encoder_g = 0;
    encoder_vitesse_d = 0.;
    encoder_vitesse_g = 0.;
    pos_x = 0.;
    pos_y = 0.;
    dest_x = 0.;
    dest_y = 0.;
    dest_dist = 0.;
    dest_alpha = 0.;
    pos_x = 0.;
    pos_y = 0.;

    beta = 0.;

    // sécurité
    urgence_bouton = 0;
    asserv_arret = 0;
    bras_arret = 0;
    afficheur_arret = 0;

    // config
    equipe = 'V';
    capt_distance = 1; // par défaut on active les capteurs de distance
    arbitre = 0;       // par défaut on ne se met pas en mode arbitre
    bras_etat = 1;     // disponible par défaut

    // Variable pour les port série :
    for (int k = 0; k < buffer_size; k++)
    {
        buffer_bras[k] = 0;
        buffer_afficheur[k] = 0;
    }
}

void init_pwm()
{
    // Configuration des pins :
    // période des pwm
    pwm_droit.period_us(periode_pwm);
    pwm_gauche.period_us(periode_pwm);
}

void init_fdc()
{
    // interruption sur les fin de courses
    // mise à 1 :
    fdc_avant_gauche.rise(&fdc_avg_1);
    fdc_avant_droit.rise(&fdc_avd_1);
    fdc_arriere_gauche.rise(&fdc_arg_1);
    fdc_arriere_droit.rise(&fdc_ard_1);
    fdc_galerie.rise(&fdc_gal_1);

    // mise à 0
    fdc_avant_gauche.fall(&fdc_avg_0);
    fdc_avant_droit.fall(&fdc_avd_0);
    fdc_arriere_gauche.fall(&fdc_arg_0);
    fdc_arriere_droit.fall(&fdc_ard_0);
    fdc_galerie.fall(&fdc_gal_0);
}
