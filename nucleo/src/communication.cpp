#include "constante_pinout.hpp"

#include "communication.hpp"

void analyse_afficheur(bool debug)
{
    sscanf(buffer_afficheur, "%c", &reception);
    switch (reception)
    {
    case 0:
        afficheur_arret = 1;
        equipe = 0; // cas d'erreur
        capt_distance = 0;
        arbitre = 0;
        break;
    case 1:
        afficheur_arret = 0;
        equipe = 'V';
        capt_distance = 0;
        arbitre = 0;
        break;
    case 2:
        afficheur_arret = 0;
        equipe = 'V';
        capt_distance = 0;
        arbitre = 1;
        break;
    case 3:
        afficheur_arret = 0;
        equipe = 'V';
        capt_distance = 1;
        arbitre = 0;
        break;
    case 4:
        afficheur_arret = 0;
        equipe = 'V';
        capt_distance = 1;
        arbitre = 1;
        break;
    case 5:
        afficheur_arret = 0;
        equipe = 'J';
        capt_distance = 0;
        arbitre = 0;
        break;
    case 6:
        afficheur_arret = 0;
        equipe = 'J';
        capt_distance = 0;
        arbitre = 1;
        break;
    case 7:
        afficheur_arret = 0;
        equipe = 'J';
        capt_distance = 1;
        arbitre = 0;
        break;
    case 8:
        afficheur_arret = 0;
        equipe = 'J';
        capt_distance = 1;
        arbitre = 1;
        break;

    default:
        break;
    }
    if (debug)
    {
        printf("reception afficheur : %d\n", reception);
    }
}

char analyse_inverse_afficheur(bool arret, char equipe, bool capt_distance, bool arbitre)
{
    char nb_envoie = 0;
    if (arret == 1)
    {
        nb_envoie = 0;
    }
    else if (arret == 0)
    {
        nb_envoie = 1 + arbitre + capt_distance * 2;
        if (equipe == 'J')
        {
            nb_envoie += 4;
        }
    }
    return nb_envoie;
}

void analyse_bras(bool debug)
{
    sscanf(buffer_afficheur, "%c", &reception);
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
        printf("%d\n", bras_etat);
    }
}

void lecture_bras(bool debug)
{
    if (bras.readable())
    {
        bras.read(buffer_bras, buffer_size);
        analyse_bras(debug);
        baton_parole_bras = 1;
        for (int k = 0; k < buffer_size; k++)
        {
            buffer_bras[k] = 0; // on vide le buffer}
        }
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
        analyse_afficheur(debug);
        baton_parole_afficheur = 1;
        for (int k = 0; k < buffer_size; k++)
        {
            buffer_afficheur[k] = 0; // on vide le buffer
        }
    }
    else
    {
        afficheur.sync();
    }
}

void envoie_bras(bool arret, uint8_t processus_bras, bool replique, bool pompe_ev, bool debug)
{
    char nb_envoie = 0;
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
                if (pompe_ev == 0)
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

    buffer_envoie[0] = nb_envoie;
    if (afficheur.writable())
    {
        afficheur.write(buffer_envoie, 1);
        if (debug)
        {
            printf("numero envoyé au bras : %d\n", nb_envoie);
        }
    }

    buffer_envoie[0] = 0; // on vide le buffer
}

void envoie_afficheur(bool arret, bool recopie, uint8_t message, bool debug)
{
    char nb_envoie = 0;
    if (arret == 1)
    {
        nb_envoie = 0;
    }
    else if (arret == 0)
    {
        if (recopie == 1)
        {
            nb_envoie = analyse_inverse_afficheur(afficheur_arret, equipe, capt_distance, arbitre);
        }
        else if (recopie == 0)
        {
            if (message == 1)
            {
                nb_envoie = 10;
            }
            else if (message == 2)
            {
                nb_envoie = 20;
            }
            else if (message == 3)
            {
                nb_envoie = 30;
            }
        }
    }

    buffer_envoie[0] = nb_envoie;
    if (afficheur.writable())
    {
        afficheur.write(buffer_envoie, 1);
        baton_parole_afficheur = 0;
        if (debug)
        {
            printf("numero envoyé à l'affciheur : %d\n", nb_envoie);
        }
    }

    buffer_envoie[0] = 0; // on vide le buffer
}

void lecture_arduinos()
{
    lecture_afficheur(0);
    lecture_bras(0);
}