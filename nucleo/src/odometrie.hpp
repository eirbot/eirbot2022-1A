#ifndef odometrie_h
#define odometrie_h

void reset_xybeta(float x_pos, float y_pos, float angle); // remet la variable pos_xy à x_pos et y_pos et beta à angle
void calculs_encoder();
void calcul_pos_xy(); 
void odometrie_periodique();


#endif