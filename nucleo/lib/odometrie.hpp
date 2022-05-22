#ifndef odometrie_h
#define odometrie_h

void reset_xy(float x_pos, float y_pos); // remet la variable pos_xy à x_pos et y_pos
void rest_beta(float angle); // réinitialise beta à une valeur
void calcul_encoder(); // Fonction pour mettre à jour la variable encoder
void calcul_vitesse();
void calcul_pos_xy(volatile float* x_pos, volatile float* y_pos); // Fonction pour mettre à jour la variable pos_xy
void odometrie_periodique();


#endif