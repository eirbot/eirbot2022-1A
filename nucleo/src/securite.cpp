#include "constante_pinout.hpp"
#include "asserv.hpp"
#include "deplacement.hpp"

#include "securite.hpp"

void lecture_GP2()
{
    if (dist_arriere_gauche.read() > dist_seuil)
    {
        dist_arg = 1;
    }
    else
    {
        dist_arg = 0;
    }

    if (dist_avant_gauche.read() > dist_seuil)
    {
        dist_avg = 1;
    }
    else
    {
        dist_avg = 0;
    }

    if (dist_avant_droit.read() > dist_seuil)
    {
        dist_avd = 1;
    }
    else
    {
        dist_avd = 0;
    }
    
    if (dist_arriere_droit.read() > dist_seuil)
    {
        dist_ard = 1;
    }
    else
    {
        dist_ard = 0;
    }
}

void fdc_avg_1()
{
    fdc_avg = 1;
}
void fdc_avd_1()
{
    fdc_avd = 1;
}
void fdc_ard_1()
{
    fdc_ard = 1;
}
void fdc_arg_1()
{
    fdc_arg = 1;
}
void fdc_gal_1()
{
    fdc_gal = 1;
}
void fdc_avg_0()
{
    fdc_avg = 0;
}
void fdc_avd_0()
{
    fdc_avd = 0;
}
void fdc_ard_0()
{
    fdc_ard = 0;
}
void fdc_arg_0()
{
    fdc_arg = 0;
}
void fdc_gal_0()
{
    fdc_gal = 0;
}

void lecture_securite()
{
    condition_fdc = 0;
    condition_dist = 0;
    
    condition_fdc |= fdc_avg;
    condition_fdc |= fdc_avd;
    condition_fdc |= fdc_arg;
    condition_fdc |= fdc_ard;

    if (capt_distance == 1)
    {
        condition_dist |= dist_avg;
        condition_dist |= dist_avd;
        condition_dist |= dist_arg;
        condition_dist |= dist_ard;
    }
}

void asserv_arret_flag()
{
    if (asserv_arret == 1)
    {
        asserv_traitement_periodique.detach();
    }
    else
    {
        asserv_traitement_periodique.attach_us(&asserv_periodique, periode_asserv);
    }
}
// *****************************************************************************************************

/***************************************
 ************* Périodiquement **********
 ****************************************/

void securite_periodique()
{
    if (capt_distance == 1)
    {
        lecture_GP2();
    }
    lecture_securite();
    asserv_arret_flag();
}