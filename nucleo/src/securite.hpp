#ifndef securite_h
#define securite_h

void lecture_GP2(); // mise à jour de la variable dist[4] pour les capteur de distance
void lecture_fdc(uint8_t numero);


// fonctions d'interruption :
void fdc_avg_1();
void fdc_avd_1();
void fdc_ard_1();
void fdc_arg_1();
void fdc_gal_1();
void fdc_avg_0();
void fdc_avd_0();
void fdc_ard_0();
void fdc_arg_0();
void fdc_gal_0();

void lecture_securite();

void asserv_arret_flag();

void securite_periodique();

#endif 