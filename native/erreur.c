/**
 * \file cerreur.c
 * \brief fonction de gestion des erreurs.
 * \author Mickael PURET
 * \date 21 mars 2011
 *
 */

#include "erreur.h"
#include "create_bd.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * \fn void fatalerreur(Donnee *data, char * txt).
 * \brief affiche le message d'erreur et desalloue les donnees du tas.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param chaine de caractères indiquant le arc du fichier à ouvrir.
 */
void fatalerreur(Donnee *data, char * txt){
    printf("[erreur] %s", txt);
    free_db(data);
    exit(-1);
}
