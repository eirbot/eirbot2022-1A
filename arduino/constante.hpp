
/***************************************
 ***********   PINS RMD  ***************
****************************************/

// Moteur Droit
#define _pwm_droit PA_8                 // D7 | Timer 1 
#define _dir_droit PC_7                 // D9

// Moteur Gauche
#define _pwm_gauche PB_10               // D6 | Timer 2
#define _dir_gauche PB_4                // D5

// Fin de course : interruptions externes
#define _fdc_avant_droit PB_0           // A3 | EXTI0
#define _fdc_avant_gauche PB_1          // en face de D7 | EXTI1
#define _fdc_arriere_droit PB_2         // en face de D8 | EXTI2
#define _fdc_arriere_gauche PC_3        // en face de A5 | EXTI3 

// Joystick 
#define _joy_x PA_0                     // A0

// Boutons
#define _b_avance PA_1                  // A1
#define _b_recule PA_4                  // A2

// Interrupteur 
#define _sw PC_1                        // A4 

extern bool fdc[4] = {false, false, false, false};
extern bool couleurs[2] = {false, false};
extern int position_robot[2] = {0, 0};
extern int postion_bras[2] = {0, 0};


extern const int test = 1024;