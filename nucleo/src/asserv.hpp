#ifndef asserv_h
#define asserv_h

#include "constante_pinout.hpp"
#include <math.h>

float PI(float erreur);
void calcul_vitesse(); // met à jour la variable encoder_vitesse

void conversion_d_alpha();

void asserv_periodique();

#endif
