/**
 * \file use_lieu.c
 * \brief ensemble de methodes permetant la gestion de la table lieu.
 * \author Mickael PURET
 * \date 25 mars 2011
 *
 */
#include "create_bd.h"
#include "erreur.h"
#include "use_lieu.h"
#include <stdlib.h>

/**
 * \fn int id_lieu(Lieu *lieu).
 * \brief permet d'obtenir l'identifiant du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi l'indentifiant du lieu.
 */
int id_lieu(Lieu *lieu){
    return lieu->id;
}

/**
 * \fn Lieu *str_lieu(Donnee data, id_lieu).
 * \brief permet d'obtenir le lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant du lieu
 * \return renvoi un pointeur sur la tructure d'un lieu contenu dans la table des lieux.
 */
Lieu *str_lieu(Donnee *data, int id_lieu){
    return &data->lieux[id_lieu];
}

/**
 * \fn void unall_lieu(Donnee *data).
 * \brief permet de desallouer l'ensemble de lieux du tas.
 *
 * \param Un pointeur sur une structure Donnee.
 */
void unall_lieu(Donnee *data){
    int i;
    for(i = 0; i < data->nb_lieux_total; ++i){
        free(data->lieux[i].nom);
    }
    free(data->lieux);
}
