#ifndef deplacement_h 
#define deplacement_h

void avancer_primitif(uint8_t pwm);
void reculer_primitif(uint8_t pwm);
void roue_d(uint8_t pwm, bool sens);
void roue_g(uint8_t pwm, bool sens);
void arret_moteur();
void etalonnage_xybeta(); // prends du temps

#endif