#include "constante_pinout.hpp"

#ifndef communication_h
#define communication_h

// Bras :
void lecture_bras(bool debug);
void envoie_bras(bool arret, uint8_t processus_bras, bool replique, bool pompe_ev, bool debug);

// Afficheur :
void lecture_afficheur(bool debug);
void envoie_afficheur(bool arret, bool recopie, uint8_t message, bool debug);


// regroupement
void lecture_arduinos();

#endif