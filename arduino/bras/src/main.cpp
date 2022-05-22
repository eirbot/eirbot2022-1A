#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Pins
uint8_t _RX = 6, _TX = 7;
uint8_t _base = 3, _inter = 4, _ventouse = 5, _rep;
uint8_t _pompe, _ev;

uint8_t c_base, c_inter, c_ventouse, c_rep; // variable de commande

uint8_t processus_bras;
bool arret, replique, pompe_ev;

SoftwareSerial nucleo(_RX, _TX);
Servo base;
Servo inter;
Servo ventouse;
Servo rep;

// Fonctions :
void analyse_nucleo(char reception, bool debug);

void setup()
{
    Serial.begin(9600);
    nucleo.begin(9600);

    pinMode(_pompe, OUTPUT);
    pinMode(_ev, OUTPUT);

    base.attach(_base);
    inter.attach(_inter);
    ventouse.attach(_ventouse);
    rep.attach(_rep);

    // Configuration initiale :
    arret = 1;
    processus_bras = 0;
    replique = 0;
    pompe_ev = 0;
    // a completer
}

void loop()
{
    if (nucleo.available())
    {
        analyse_nucleo(nucleo.read(), 1);
    }

    while (arret == 1)
    {
        if (nucleo.available())
        {
            analyse_nucleo(nucleo.read(), 1);
        }
        digitalWrite(_pompe, LOW);
        digitalWrite(_ev, LOW);
    }

    if (replique == 1)
    {

        // faire l'action de déposer la réplique

        replique = 0;
        while (nucleo.availableForWrite() == 0)
        {
            // on boucle tant qu'on peut pas envoyer un msg
        }
        nucleo.write(2);
    }

    if (processus_bras != 0)
    {
        // dans la variable processus_bras il y a la position à réaliser
        // réaliser la position

        processus_bras = 0;
        while (nucleo.availableForWrite() == 0)
        {
            // on boucle tant qu'on peut pas envoyer un msg
        }
        nucleo.write(2);
    }

    if (pompe_ev == 1)
    {
        // activer la pompe 
        // un numéro sera envoyé pour dire de la désactiver
    }
    else 
    {
        // désactiver la pompe
    }
}

void analyse_nucleo(char reception, bool debug)
{

    switch (reception)
    {
    case 0:
        arret = 1;
        processus_bras = 0;
        replique = 0;
        pompe_ev = 0;
        break;

    case 1:
        arret = 0;
        processus_bras = 0;
        replique = 0;
        pompe_ev = 0;
        break;
    case 2:
        arret = 0;
        processus_bras = 0;
        replique = 0;
        pompe_ev = 1;
        break;
    case 3:
        arret = 0;
        processus_bras = 0;
        replique = 1;
        pompe_ev = 0;
        break;
    case 4:
        arret = 0;
        processus_bras = 0;
        replique = 1;
        pompe_ev = 1;
        break;
    case 5:
        arret = 0;
        processus_bras = 1;
        replique = 0;
        pompe_ev = 0;
        break;
    case 6:
        arret = 0;
        processus_bras = 1;
        replique = 0;
        pompe_ev = 1;
        break;
    case 7:
        arret = 0;
        processus_bras = 1;
        replique = 1;
        pompe_ev = 0;
        break;
    case 8:
        arret = 0;
        processus_bras = 1;
        replique = 1;
        pompe_ev = 1;
        break;
    case 9:
        arret = 0;
        processus_bras = 2;
        replique = 0;
        pompe_ev = 0;
        break;
    case 10:
        arret = 0;
        processus_bras = 2;
        replique = 0;
        pompe_ev = 1;
        break;
    case 11:
        arret = 0;
        processus_bras = 2;
        replique = 1;
        pompe_ev = 0;
        break;
    case 12:
        arret = 0;
        processus_bras = 2;
        replique = 1;
        pompe_ev = 1;
        break;
    case 13:
        arret = 0;
        processus_bras = 3;
        replique = 0;
        pompe_ev = 0;
        break;
    case 14:
        arret = 0;
        processus_bras = 3;
        replique = 0;
        pompe_ev = 1;
        break;
    case 15:
        arret = 0;
        processus_bras = 3;
        replique = 1;
        pompe_ev = 0;
        break;
    case 16:
        arret = 0;
        processus_bras = 3;
        replique = 1;
        pompe_ev = 1;
        break;

    default:
        break;
    }
    if (debug)
    {
        Serial.println(reception);
    }
}