#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Pins
uint8_t _RX = 6, _TX = 7;
uint8_t _base = 4, _inter = 3, _ventouse = 5, _rep = 2;
uint8_t _pompe, _ev;

// uint8_t c_base, c_inter, c_ventouse, c_rep; // variable de commande

uint8_t processus_bras;
bool arret, replique, pompe_ev;

/*
processus 3
choper palais
    inter 125
    base 82
    ventouse 132

choper statuette

transport
    inter 83
    base 138
    ventouse 112

repos


*/

int condition;

int8_t c_base = -1, c_inter = -1, c_ventouse = -1;

SoftwareSerial nucleo(_RX, _TX);
Servo base;
Servo inter;
Servo ventouse;
Servo rep;

// !********************** FONCTIONS **********************!

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
        arret = 1;
        processus_bras = 0;
        replique = 0;
        pompe_ev = 0;
        break;
    }
    if (debug)
    {
        Serial.println(reception);
    }
}

void lecture_nucleo(int debug)
{
    if (nucleo.available())
    {
        analyse_nucleo(nucleo.read(), debug);
    }
}

int delay_opti(uint32_t periode)
{
    uint32_t kro = millis();
    while ((millis() - kro) <= 300)
    {
        lecture_nucleo(0);
        if (arret == 1)
        {
            return 0;
        }
    }
    return 1;
}

int processus0()
{
    Serial.println("Processus 0");
}

int processus1()
{
    Serial.println("Processus 1");

    digitalWrite(_pompe, HIGH);
    digitalWrite(_ev, LOW);
    inter.write(125);

    // sécurité
    condition = delay_opti(300);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    base.write(80);

    condition = delay_opti(300);
    if (condition == 0)
    {
        return 0;
    }

    ventouse.write(162);

    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }

    inter.write(80);

    ventouse.write(120);
    base.write(120);

    int condition = delay_opti(1000);
    if (condition == 0)
    {
        return 0;
    }
}

int processus2()
{
    Serial.println("Processus 2");

    // sécurité
    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    digitalWrite(_pompe, LOW);
    digitalWrite(_ev, HIGH);
}

int processus3()
{
    Serial.println("Processus 3");

    // sécurité
    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    digitalWrite(_pompe, HIGH);
    digitalWrite(_ev, LOW);

    base.write(1);

    inter.write(40);

    // sécurité
    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    ventouse.write(100);

    // sécurité
    condition = delay_opti(2000);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    base.write(100);
    inter.write(150);

    // sécurité
    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité

    ventouse.write(70);

    // sécurité
    condition = delay_opti(500);
    if (condition == 0)
    {
        return 0;
    }
    // end sécurité
}

int replique_depose()
{
}

// !********************** SETUP **********************!

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

    while (digitalRead(11) == 1)
    {
        int mem_base = c_base;
        int mem_inter = c_inter;
        int mem_ventouse = c_ventouse;

        Serial.print("Base : ");
        // delay(2000);
        while (c_base == mem_base)
        {
            c_base = Serial.parseInt();
        }
        if (mem_base != c_base)
        {
            Serial.println(c_base);
        }
        // delay(1000);

        //     Serial.print("inter : ");
        //     while (c_inter == mem_inter)
        //     {
        //         c_inter = Serial.println();
        //     }

        //     //delay(1000);

        //     Serial.print("ventouse : ");
        //     //delay(2000);
        //     while (c_ventouse == mem_ventouse)
        //     {
        //         c_ventouse = Serial.parseInt();
        //     }
        //     Serial.println(c_ventouse);

        //     //delay(1000);
        // }

        rep.write(179); // maintient de la réplique
    }
    while (1)
    {
        //servo au bon endroit 
    }
}
// !********************** LOOP **********************!

void loop()
{
    lecture_nucleo(0);

    while (arret == 1)
    {
        lecture_nucleo(0);
        digitalWrite(_pompe, LOW);
        digitalWrite(_ev, LOW);
    }

    if (replique == 1)
    {
        rep.write(130);

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
        switch (processus_bras)
        {
        case 1:
            if (processus1() == 1)
            {
                nucleo.write(2);
            }
            break;
        case 2:
            if (processus2() == 1)
            {
                nucleo.write(2);
            }
            break;
        case 3:
            if (processus3() == 1)
            {
                nucleo.write(2);
            }
            break;
        default:
            processus0();
            break;
        }
        processus_bras = 0;

        // sécurité
        delay_opti(1000);
        // end sécurité
    }

    if (pompe_ev == 1)
    {
        digitalWrite(_pompe, HIGH);
    }
    else
    {
        digitalWrite(_pompe, LOW);
    }
}
