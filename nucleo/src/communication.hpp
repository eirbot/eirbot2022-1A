#include "constante_pinout.hpp"

#ifndef communication_h
#define communication_h

// Bras :
void lecture_bras(bool debug);
void envoie_bras(char envoie);

// Afficheur :
void lecture_afficheur(bool debug);
void envoie_afficheur(bool arret, uint8_t message, bool recopie);


// regroupement
void lecture_arduinos();
#endif