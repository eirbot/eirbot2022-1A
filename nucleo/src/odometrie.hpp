#ifndef odometrie_h
#define odometrie_h

void reset(float x_pos, float y_pos); // remet la variable pos_xy à x_pos et y_pos
void rest_beta(float angle); // réinitialise beta à une valeur
void calcul_encoder(); // Fonction pour mettre à jour la variable encoder
void calcul_pos_xy(); // Fonction pour mettre à jour la variable pos_xy
void odometrie_periodique();


#endif