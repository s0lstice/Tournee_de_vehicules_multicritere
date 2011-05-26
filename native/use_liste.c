/**
 * \file use_liste.c
 * \brief ensemble de methodes permetant la gestion de la table liste_lieu.
 * \author Mickael PURET
 * \date 25 mars 2011
 *
 */
#include "create_bd.h"
#include "erreur.h"
#include "use_liste.h"
#include <stdlib.h>
/**
 * \fn int id_lieu(Lieu *lieu).
 * \brief permet d'obtenir l'identifiant du lieu id_lieu
 *
 * \param Un pointeur sur une structure Donnee.
 * \param un identifiant de la table
 * \return renvoi l'indentifiant du lieu.
 */
int liste_lieu_coef(Donnee *data, int id_table){
    return data->liste_lieu[id_table].coef;
}

Lieu *str_lieu_liste(Donnee *data, int id_table){
    return data->liste_lieu[id_table].lieu;
}

int id_lieu_liste(Donnee *data, int id_table){
    return data->liste_lieu[id_table].lieu->id;
}

void unall_liste(Donnee *data){
    free(data->liste_lieu);
}
