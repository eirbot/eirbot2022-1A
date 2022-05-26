#ifndef asserv_h
#define asserv_h

float PI(float erreur, float Kp, float Ki);
float P(float erreur, float Kp);
float second_ordre(float x_n);
void conversion_d_alpha();
uint8_t sature(float valeur, uint8_t min, uint8_t max);
void asserv_periodique();

#endif
