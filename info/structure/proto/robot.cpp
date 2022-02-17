#include "mbed.h"

void pin_init (void){
	//initialise tous les pins
	//initialise fdc à 0
	
}

// interruption des fdc
void isr_fdc_AvG(void){
	fdc[0] = 1; //penser à remettre ce bit à 0 après acquisition de l'info
}
void isr_fdc_AvD(void){
	fdc[1] = 1; //penser à remettre ce bit à 0 après acquisition de l'info
}
void isr_fdc_ArG(void){
	fdc[2] = 1; //penser à remettre ce bit à 0 après acquisition de l'info
}
void isr_fdc_ArD(void){
	fdc[3] = 1; //penser à remettre ce bit à 0 après acquisition de l'info
}

// interruption arret d'urgence
void arret_urgence(void){
	arret_urgence = 1; //penser à remettre ce bit à 0 après acquisition de l'info
}

// détection de couleur
bool is_white(void); 
bool is_black(void);

//ROBOT
// lecture de l'emplacement du robot ou on fait ça sur des variables globales
int robot_get_x(void);
int robot_get_y(void);
// déplacement du robot
void robot_to_xy(int x, int y);


// Bras Robotique
// mouvement du bras robotique (renvoie 0 si tout va bien | -1 si tout va mal | et 1 s'il ne détecte rien au bout de la ventouse)
int bras_to_pos(int position); //position ça va petre les différentes positions du bras
int bras_get_x(void);
int bras_get_y(void);

//Communication rasp (renvoie 0 si pas pb et 1 si pb)
int rasp_actu(void); // actualise le tableau de la rasp

