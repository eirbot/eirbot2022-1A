#include "mbed.h"
//include asserv.h bras.h et autres

// Config (tous les pins, certains seront déplacer dans d'autre .h)
const uint8 _dirMD= ,_pwmMD= ,_dirMG= ,dirMG; //pin pour les moteurs (digital pour dir et pwm pour pwm)
const uint8 _fdcAvG= , _fdcAvD= , _fdcArG= , _fdcArD= ; //pin pour les fin de course (interruption externe)
const uint8 _sdaCouleur= , _sclCouleur= ;
const uint8 _servoRot= , _servoBase= , _servoMilieu= , _servoVentouse= ; // pour le bras robotique (sur nano)
const uint8 _dist= ; // analogique ou digital ? (capteur de distance)
const uint8 _txBluetooth= , _rxBluetooth= ; // com bluetooth

// Variables globales
bool arret_urgence; // à initialiser à 0
bool fdc[4]; // à initialiser à 0
int rasp[5]; // positions renvoyées par la rasp (on peut imaginer que l'élément 0 et le moment de la dernière lecture)
// temps + pos de notre robot + de l'adversaire 

/*
********** Fonctions **********
 */

// initialisation (sera surement fait dans les autres .h)
void pin_init(void);

// interruptions externes des fin de course
void isr_fdc_AvG(void);
void isr_fdc_AvD(void);
void isr_fdc_ArG(void);
void isr_fdc_ArD(void);

// interruption arret d'urgence
void arret_urgence(void);

// détection de couleur
bool is_white(void); 
bool is_black(void);

// capteur de distance
int dist(void); // distance en mm (approximatif)

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
int bras_aspire(void); //erreur possible

//Communication rasp (renvoie 0 si pas pb et 1 si pb)
int rasp_actu(void); // actualise le tableau de la rasp

