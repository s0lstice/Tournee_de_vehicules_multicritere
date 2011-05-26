/**
 * \file use_index.c
 * \brief ensemble de methodes permetant la gestion de la table index.
 * \author Mickael PURET & Cyrille Picard
 * \date 25 mars 2011
 *
 */

#include "create_bd.h"
#include "erreur.h"
#include "use_solution.h"
#include <stdlib.h>

/**
 * \fn Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive).
 * \brief retourne un pointeur sur une structure index_arc depuis l'index en fonction du lieu de départ et du lieu d'arrivé.
 *
 * La structure index_arc contient l'identifiant du premier arc du lieu de destination et le nombre d'arc qui lui est associé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return Une structure index_arc ou NULL si id_arrive n'existe pas.
 */
Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive){
    return data->index_lieu[id_depart][id_arrive];
}

/**
 * \fn int index_id_arc(Donnee *data, int id_depart, int id_arrive).
 * \brief retourne l'identifiant de l'arc corespondant au lieu de depart et de destination indiqué, ou -1 si la destination n'est pas accessible.
 *
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return un identifiant d'arc ou -1 s'il n'existe pas.
 */
int index_id_arc(Donnee *data, int id_depart, int id_arrive){
    if(data->index_lieu[id_depart][id_arrive] == NULL) return -1;
    return data->index_lieu[id_depart][id_arrive]->id_arc;
}

/**
 * \fn int index_nb_arc(Donnee *data, int id_depart, int id_arrive).
 * \brief retourne le nombre d'arc disponible pour cette destination en fonction du lieu de depart.
 *
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return le nombre de destination disponible ou -1 si le lieu de destination nes pas acessible.
 */
int index_nb_arc(Donnee *data, int id_depart, int id_arrive){
    if(data->index_lieu[id_depart][id_arrive] == NULL) return -1;
    return data->index_lieu[id_depart][id_arrive]->nb_arc;
}

/**
 * \fn int relation_index_lieu(Donnee *data, int id_lieu_depart, int id_lieu_arrive).
 * \brief indique si des arcs existe entre deux lieux.
 *
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return 0 : n'existe pas | 1 : existe.
 */
int relation_index_lieu(Donnee *data, int id_lieu_depart, int id_lieu_arrive){
    if(data->index_lieu[id_lieu_depart][id_lieu_arrive] == NULL) return 0;
    return 1;
}

/**
 * \fn void unall_index(Donnee *data).
 * \brief desalloue la table index.
 *
 * \param Un pointeur sur une structure Donnee.
 */
void unall_index(Donnee *data){
    int i,j;

    for(i = 0; i < data->parametres.nb_lieux; ++i){
        for(j = 0; j < data->parametres.nb_lieux; ++j){
            if(data->index_lieu[i][j] != NULL)
                free(data->index_lieu[i][j]);
        }
        free(data->index_lieu[i]);
    }
    free(data->index_lieu);
}
