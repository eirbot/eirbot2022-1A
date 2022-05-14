// #pragma once
#include <mbed.h>
#include "encoder.h"

#ifndef constante_pinout_h
#define constante_pinout_h

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
#define _fdc_avant_droit PA_0    // A0 | EXTI0
#define _fdc_avant_gauche PB_1   // en face de D7 | EXTI1
#define _fdc_arriere_droit PD_2  // avant dernier droit [haut gauche] | EXTI2
#define _fdc_arriere_gauche PB_3 // D3 | EXTI3
#define _fdc_galerie PC_5        // diagonale basse D14 | EXTI5

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
#define _dist_avant_gauche PC_0   // A5
#define _dist_avant_droit PB_0    // A3
#define _dist_arriere_gauche PC_1 // A4
#define _dist_arriere_droit PC_4  // en face de D2
#define _dist_gauche PC_2         // en face de A4
#define _dist_droit PC_3          // en face de A5

// *****************************************************************************************************

/***************************************
 *************   PINOUT  ***************
 ****************************************/

// Encodeurs
extern Encoder encodeur_droit;
extern Encoder encodeur_gauche;

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
extern AnalogIn dist_gauche;
extern AnalogIn dist_droit;
// *****************************************************************************************************

/***************************************
 ************* Constantes **************
 ****************************************/
const uint16_t periode_pwm = 25; // en us
const uint32_t periode_encoder = 100; // en us
const uint32_t periode_asserv = 1e3;  // en us
const float Kp = 0.0401;
const float Ki = 0.425;
const float dist_seuil = 0.6; // à ajuster
const uint16_t buffer_size = 32;

// Dimension robot :
const float entre_axe = 38.24; // en cm

// Encoder :
const uint16_t tick_encoder = 1024;
const float encoder_diametre = 2.984; // en cm
const float d_theta = 360.0 / (float)(tick_encoder);

// Variables globales :
// booléens
extern volatile bool fdc[5]; // avg avd ard arg gal
extern volatile bool dist[6]; // avg avd d ard arg g
extern volatile bool urgence_bouton;
// odometrie / asserv
extern volatile int32_t encoder[2]; // tick des encoder (gauche droite)
extern volatile float encoder_vitesse[2]; // vitesse des encoder (gauche droite)
extern volatile float pos_xy[2]; // position actuelle en xy
extern volatile float dest_xy[2]; // destination voulu en xy
extern volatile float dest_dalpha[2]; // distance et angle pour aller à dest_xy
extern volatile float beta; // angle du robot par rapport au bord bas

// Variable pour les port série :
extern char buffer_bras[32];
extern char buffer_afficheur[32];
extern char buffer_envoie[32];

void init_globale();

#endif