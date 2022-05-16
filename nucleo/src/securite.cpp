#include "constante_pinout.hpp"

#include "securite.hpp"

void lecture_GP2()
{
    float dist_mesure[6];

    dist_mesure[0] = dist_avant_gauche.read();
    dist_mesure[1] = dist_avant_droit.read();
    dist_mesure[2] = dist_arriere_droit.read();
    dist_mesure[3] = dist_arriere_gauche.read();

    for (int k = 0; k < 4; k++)
    {
        if (dist_mesure[k] >= dist_seuil)
        {
            dist[k] = 1;
        }
        else
        {
            dist[k] = 0;
        }
    }
}

void lecture_fdc(uint8_t numero)
{
    if (numero > 5)
    {
        numero = 4; // par défaut je renvoie celui qui est en face de la galerie
    }

    switch (numero)
    {
    case 0:
        fdc[0] = fdc_avant_droit.read();
        break;
    case 1:
        fdc[1] = fdc_avant_gauche.read();
        break;
    case 2:
        fdc[2] = fdc_arriere_gauche.read();
        break;
    case 3:
        fdc[3] = fdc_arriere_droit.read();
        break;
    case 4:
        fdc[4] = fdc_galerie.read();
        break;
    default:
        fdc[4] = fdc_galerie.read();
        break;
    }
}

void fdc_avg_1()
{
    fdc[0] = 1;
}

void fdc_avd_1()
{
    fdc[1] = 1;
}

void fdc_ard_1()
{
    fdc[2] = 1;
}

void fdc_arg_1()
{
    fdc[3] = 1;
}

void fdc_gal_1()
{
    fdc[4] = 1;
}

void fdc_avg_0()
{
    fdc[0] = 0;
}

void fdc_avd_0()
{
    fdc[1] = 0;
}

void fdc_ard_0()
{
    fdc[2] = 0;
}

void fdc_arg_0()
{
    fdc[3] = 0;
}

void fdc_gal_0()
{
    fdc[4] = 0;
}

void asserv_arret_flag()
{
    if (asserv_arret == 1)
    {
        asserv_traitement_periodique.detach();
    }
}
// *****************************************************************************************************

/***************************************
 ************* Périodiquement **********
 ****************************************/

void securite_periodique()
{
    lecture_GP2();
}