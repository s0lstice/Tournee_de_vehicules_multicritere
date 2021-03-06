#include "create_bd.h"
#include "erreur.h"
#include "use_map.h"
#include <stdlib.h>

/**
 * \fn int destination_map_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie l'identifiant du lieu de destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'identifiant du lieu destination de l'arc.
 */
int destination_map_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->destination->id;
}

/**
 * \fn int depart_map_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie l'identifiant du lieu de départ de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'identifiant du lieu de départ de l'arc.
 */
int depart_map_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->depart->id;
}

/**
 * \fn int distance_map_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie la distance de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant la distance de l'arc.
 */
int distance_map_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->distance;
}

/**
 * \fn int insecurite_map_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie l'insecurité de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'insecurité de l'arc.
 */
int insecurite_map_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->insecurite;
}

/**
 * \fn int interet_map_destination(Donnee *data, int id_lieu, int id_arc).
 * \brief renvoie l'interet du lieu de destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'interet du lieu de destination de l'arc.
 */
int interet_map_destination(Donnee *data, int id_lieu, int id_arc){
    int id_lieu_destination = data->map[id_lieu][id_arc]->destination->id;
    return data->lieux[id_lieu_destination].interet;
}

/**
 * \fn char *nom_destination(Donnee *data, int id_lieu, int id_arc).
 * \brief renvoie le nom du lieu de destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return une chaine de caracteres contenant le nom du lieu de destination.
 */
char *nom_destination(Donnee *data, int id_lieu, int id_arc){
    int id_lieu_destination = data->map[id_lieu][id_arc]->destination->id;
    return data->lieux[id_lieu_destination].nom;
}

/**
 * \fn Arc *str_map_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief retourne un pointeur sur l'arc demandé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return l'addresse de arc.
 */
Arc *str_map_arc(Donnee *data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc];
}

/**
 * \fn existe_map_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief permet de tester si il existe l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return 0 si l'arc n'existe pas et 1 si il existe
 */

int existe_map_arc(Donnee *data, int id_lieu, int id_arc){
    if(data->map[id_lieu][id_arc] == NULL) return 0;
    return 1;
}

/**
 * \fn void maj_str_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc).
 * \brief premet de changer l'arc ciblé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \param l'addresse du nouvel arc.
 */
void maj_str_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc){
    data->map[id_lieu][id_arc] = point_arc;
}

/**
 * \fn void spr_str_map_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief premet de suprimer un arc du tas.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 */
void spr_str_map_arc(Donnee *data, int id_lieu, int id_arc){
    free(data->map[id_lieu][id_arc]);
}

Lieu *depart_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset]->depart;
}

Lieu *destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset]->destination;
}

int distance_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset]->distance;
}

int insecurite_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset]->insecurite;
}

int interet_destination_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset]->destination->interet;
}

void unall_map(Donnee *data){
    int j,i;

    for(i = 0; i < data->parametres.nb_lieux; ++i){

        for(j = 0; j < data->lieux[i].nb_arc; ++j){
            free(data->map[i][j]);
        }
        free(data->map[i]);
    }
    free(data->map);
}

Arc *ptr_arc(Donnee *data, int id_lieu_depart, int id_lieu_arrive, int offset){
    int id_arc = data->index_lieu[id_lieu_depart][id_lieu_arrive]->id_arc;
    return data->map[id_lieu_depart][id_arc + offset];
}
