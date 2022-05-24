// #pragma once

#ifndef constante_pinout_h
#define constante_pinout_h

#include <mbed.h>
#include <cmath>
#include "encoder.h"
#include "constante_pinout.hpp"
#include "securite.hpp"

/***************************************
 *************   PINS  *****************
 ****************************************/
// Encodeurs
#define _encodeur_droit_A PA_6  // D12 TIM3_ch1
#define _encodeur_droit_B PA_7  // D11 TIM3_ch2
#define _encodeur_gauche_A PB_6 // D10 TIM4_ch1
#define _encodeur_gauche_B PB_7 // en face de GND (celui du bas) TIM4_ch2

// Moteur Droit
#define _pwm_droit PB_8 // D15 | TIM2_ch1
#define _dir_droit PB_9 // D14

// Moteur Gauche
#define _pwm_gauche PA_1 // A1 | TIM2_ch2
#define _dir_gauche PA_4 // A2

// Fin de course
#define _fdc_avant_gauche PB_3   // D3 | EXTI3
#define _fdc_avant_droit PA_0    // A0 | EXTI0
#define _fdc_arriere_droit PB_1  // en face de D7 | EXTI1
#define _fdc_arriere_gauche PD_2 // avant dernier droit [haut gauche] | EXTI2

#define _fdc_galerie PC_5 // diagonale basse D14 | EXTI5

// Urgence
#define _urgence PB_4 // D5 | EXTI4

// Liaison série Arduino : UART 1
#define _bras_RX PA_10 // D2
#define _bras_TX PA_9  // D8

// Liaison série Arduino : UART 3
#define _afficheur_RX PC_11 // dernier droit [haut gauche]
#define _afficheur_TX PB_10 // D6

// Liaison I2C couleur : I2C3
#define _SDA PC_9 // au dessus de D15
#define _SCL PA_8 // D7

// Capteur de distance : Analogiques
#define _dist_avant_gauche PC_1   // A4
#define _dist_avant_droit PC_0    // A5
#define _dist_arriere_gauche PC_2 // en face de A4
#define _dist_arriere_droit PC_4  // en face de D2
// *****************************************************************************************************

/***************************************
 *************   PINOUT  ***************
 ****************************************/

// Encodeurs
extern Encoder encoder_droit;
extern Encoder encoder_gauche;

// Moteur droit
extern PwmOut pwm_droit;
extern DigitalOut dir_droit;

// Moteur gauche
extern PwmOut pwm_gauche;
extern DigitalOut dir_gauche;

// Fin de courses
extern InterruptIn fdc_avant_droit;
extern InterruptIn fdc_avant_gauche;
extern InterruptIn fdc_arriere_droit;
extern InterruptIn fdc_arriere_gauche;
extern InterruptIn fdc_galerie;

// Urgence
extern InterruptIn urgence;

// Liaison série Arduino : UART 1
extern BufferedSerial bras;

// Liaison série Arduino : UART 3
extern BufferedSerial afficheur;

// Liaison I2C couleur
extern I2C couleur;

// Capteurs de distance
extern AnalogIn dist_avant_gauche;
extern AnalogIn dist_avant_droit;
extern AnalogIn dist_arriere_gauche;
extern AnalogIn dist_arriere_droit;

// *****************************************************************************************************
/***************************************
 ************* Constantes **************
 ****************************************/
// Périodes
const uint16_t periode_pwm = 25;        // en us
const uint32_t periode_odometrie = 500; // en us
const uint32_t periode_asserv = 10e3;   // en us
const uint32_t periode_serie = 1e5;     // en us
const uint32_t periode_securite = 1000; // en us

// asserv
const float K_PI_p = 0.0447;
const float K_PI_i = 0.421;

const float K_P_p = 1.;

const float K_P_angle = 1000.;
const float K_P_dist = 1.;

// sécurité
const float dist_seuil = 0.5; // à vérifier

// port série
const uint16_t buffer_size = 32;
const uint16_t baud_rate = 9600;

// Dimension robot :
const float entre_axe = 0.3824; // en m

// Encoder :
const uint16_t tick_encoder = 1024;
const float encoder_diametre = 0.02984; // en m
const float d_theta_rad = (2 * M_PI) / ((float)(tick_encoder));
const float d_theta_deg = (360.) / ((float)(tick_encoder));

// *****************************************************************************************************

/****************************************
 ************* Var Globales *************
 ****************************************/
// sécurité
// extern volatile bool fdc[5]; // avg avd ard arg gal
extern volatile bool fdc_avg;
extern volatile bool fdc_avd;
extern volatile bool fdc_ard;
extern volatile bool fdc_arg;
extern volatile bool fdc_gal;
extern volatile bool dist_avg;
extern volatile bool dist_avd;
extern volatile bool dist_arg;
extern volatile bool dist_ard;
extern volatile bool urgence_bouton;
extern volatile bool asserv_arret;

// odometrie / asserv
extern volatile int32_t encoder_d;       // tick de encoder droit
extern volatile int32_t encoder_g;       // tick de encoder gauche
extern volatile float encoder_angle_d;   // vitesse de l'encoder droit
extern volatile float encoder_angle_g;   //  vitesse de l'encoder gauche
extern volatile float encoder_vitesse_d; // vitesse de l'encoder droit
extern volatile float encoder_vitesse_g; //  vitesse de l'encoder gauche

extern volatile float pos_x; // position actuelle en x
extern volatile float pos_y; // position actuelle en y
extern volatile float beta;  // angle du robot par rapport au bord bas

extern volatile float dist_droit;
extern volatile float dist_gauche;
extern volatile float dist_robot;

extern volatile float dest_x;     // destination voulu en x
extern volatile float dest_y;     // destination voulu en y
extern volatile float dest_dist;  // distance pour aller à dest_x et dest_y
extern volatile float dest_alpha; // angle pour aller à dest_x et dest_y

// ports série :
extern char buffer_bras[buffer_size];
extern char buffer_afficheur[buffer_size];
extern char buffer_envoie[1];
extern volatile char reception; // pour l'analyse des message
// variable pour les états communiqués
extern volatile char equipe;
extern volatile bool capt_distance;
extern volatile bool arbitre;
extern volatile bool afficheur_arret;
extern volatile bool bras_etat;
extern volatile bool bras_arret;

extern volatile bool baton_parole_bras;      // 0 ne parle pas à l'arduino
extern volatile bool baton_parole_afficheur; // 0 ne parle pas à l'arduino

// *****************************************************************************************************
/***************************************
 ************* Temporalité du code *****
 ****************************************/
// Chronomètre
extern Timer chronometer; // chronomètre pour le départ

// Traitement périodique
extern Ticker odometrie_traitement_periodique;
extern Ticker asserv_traitement_periodique;
extern Ticker serie_traitement_periodique;
extern Ticker securite_traitement_periodique;

// *****************************************************************************************************
/***************************************
 ************* Fonctions ***************
 ****************************************/

void init_globale();
void init_pwm();
void init_fdc();

#endif