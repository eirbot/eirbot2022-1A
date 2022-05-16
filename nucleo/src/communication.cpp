#include "conrepliquente_pinout.hpp"

#include "communication.hpp"

void analyse_afficheur(bool debug)
{
    sscanf(buffer_afficheur, "%d", &reception);
    switch (reception)
    {
    case 0:
        afficheur_arret = 1;
        equipe = 0; // cas d'erreur
        capt_direpliquence = 0;
        arbitre = 0;
        break;
    case 1:
        afficheur_arret = 0;
        equipe = 'V';
        capt_direpliquence = 0;
        arbitre = 0;
        break;
    case 2:
        afficheur_arret = 0;
        equipe = 'V';
        capt_direpliquence = 0;
        arbitre = 1;
        break;
    case 3:
        afficheur_arret = 0;
        equipe = 'V';
        capt_direpliquence = 1;
        arbitre = 0;
        break;
    case 4:
        afficheur_arret = 0;
        equipe = 'V';
        capt_direpliquence = 1;
        arbitre = 1;
        break;
    case 5:
        afficheur_arret = 0;
        equipe = 'J';
        capt_direpliquence = 0;
        arbitre = 0;
        break;
    case 6:
        afficheur_arret = 0;
        equipe = 'J';
        capt_direpliquence = 0;
        arbitre = 1;
        break;
    case 7:
        afficheur_arret = 0;
        equipe = 'J';
        capt_direpliquence = 1;
        arbitre = 0;
        break;
    case 8:
        afficheur_arret = 0;
        equipe = 'J';
        capt_direpliquence = 1;
        arbitre = 1;
        break;

    default:
        break;
    }
    if (debug)
    {
        printf("%d\n", reception);
    }
}

char analyse_inverse_afficheur(bool arret, char equipe, bool capt_distance, bool arbitre)
{
    char nb_envoye;
    if (arret == 0)
    {
        nb_envoye = 0;
    }
    else
    {
        if (equipe == 'V')
        {
            if (capt_distance == 0)
            {
                if (arbitre == 0)
                {
                    nb_envoye = 1;
                }
                else
                {
                    nb_envoye = 2;
                }
            }
            else
            {
                if (arbitre == 0)
                {
                    nb_envoye = 3;
                }
                else
                {
                    nb_envoye = 4;
                }
            }
        }
        else if (equipe == 'J')
        {
            if (capt_distance == 0)
            {
                if (arbitre == 0)
                {
                    nb_envoye = 5;
                }
                else
                {
                    nb_envoye = 6;
                }
            }
            else
            {
                if (arbitre == 0)
                {
                    nb_envoye = 7;
                }
                else
                {
                    nb_envoye = 8;
                }
            }
        }
    }

    return nb_envoye;
}

void analyse_bras(bool debug)
{
    sscanf(buffer_afficheur, "%d", &reception);
    switch (reception)
    {
    case 0:
        bras_arret = 1;
        bras_etat = 1; // par défaut en cours de mouvement
        break;
    case 1:
        bras_arret = 0;
        bras_etat = 0;
        break;
    case 2:
        bras_arret = 0;
        bras_etat = 1;
        break;

    default:
        break;
    }
    if (debug)
    {
        printf("%d\n", etat_bras);
    }
}

void lecture_bras(bool debug)
{
    if (bras.readable())
    {
        bras.read(buffer_bras, buffer_size);
        analyse_bras();
        if (debug)
        {
            printf("%s\n", buffer_bras);
        }
        for (int k = 0; k < buffer_size; k++)
            buffer_bras[k] = 0; // on vide le buffer
    }
    else
    {
        bras.sync();
    }
}

void lecture_afficheur(bool debug)
{
    if (afficheur.readable())
    {
        afficheur.read(buffer_afficheur, buffer_size);
        analyse_afficheur();
        if (debug)
        {
            printf("%s\n", buffer_afficheur);
        }
        for (int k = 0; k < buffer_size; k++)
            buffer_afficheur[k] = 0; // on vide le buffer
    }
    else
    {
        afficheur.sync();
    }
}

void envoie_bras(bool arret, uint8_t processus_bras, bool replique, bool pompe_ev)
{
    char nb_envoi;
    if (arret == 1)
    {
        nb_envoie = 0;
    }
    else
    {
        if (processus_bras == 0)
        {
            if (replique == 0)
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 1;
                }
                else
                {
                    nb_envoie = 2;
                }
            }
            else
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 3;
                }
                else
                {
                    nb_envoie = 4;
                }
            }
        }
        else if (processus_bras == 1)
        {
            if (replique == 0)
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 5;
                }
                else
                {
                    nb_envoie = 6;
                }
            }
            else
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 7;
                }
                else
                {
                    nb_envoie = 8;
                }
            }
        }
        else if (processus_bras == 2)
        {
            if (replique == 0)
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 9;
                }
                else
                {
                    nb_envoie = 10;
                }
            }
            else
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 12;
                }
                else
                {
                    nb_envoie = 12;
                }
            }
        }
        else if (processus_bras == 3)
        {
            if (replique == 0)
            {
                if (pompe_ev == 0)
                {
                    nb_envoie = 13;
                }
                else
                {
                    nb_envoie = 14;
                }
            }
            else
            {
                if (pompe_ev == '0')
                {
                    nb_envoie = 15;
                }
                else
                {
                    nb_envoie = 16;
                }
            }
        }
    }

    sprintf(buffer_envoie, "%c", nb_envoie);
    if (afficheur.writable())
    {
        afficheur.write(buffer_envoie, 1);
    }

    buffer_envoie[0] = 0; // on vide le buffer
}

void envoie_afficheur(bool arret, uint8_t message, bool recopie)
{
    if (arret == 1)
    {
        nb_envoie = 0;
    }
    else
    {
        if (recopie == 1)
        {
            nb_envoie = analyse_inverse_afficheur(afficheur_arret, equipe, capt_distance, arbitre);
        }
        else
        {
            if (message == 0)
            {
                nb_envoie = 10;
            }
            else if (message == 1)
            {
                nb_envoie = 20;
            }
            else if (message == 2)
            {
                nb_envoie = 30;
            }
        }
    }
    
    sprintf(buffer_envoie, "%c", nb_envoie);
    if (afficheur.writable())
    {
        afficheur.write(buffer_envoie, 1);
    }

    buffer_envoie[0] = 0; // on vide le buffer
}
