/**
 * \file use_bd.c
 * \brief ensemble de methodes permetant la recuperation d'informations provenant des données.
 * \author Mickael PURET
 * \date 25 mars 2011
 *
 */
#include "create_bd.h"
#include "use_bd.h"
#include <stdlib.h>

/**
 * \fn char * nom_lieu(Donnee * data, int id_lieu).
 * \brief renvoie le nom du lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return une chaine de caracteres contenant le nom du lieu.
 */
char * nom_lieu(Donnee * data, int id_lieu){
    return data->lieux[id_lieu].nom;
}

/**
 * \fn int interet_lieu(Donnee * data, int id_lieu).
 * \brief renvoie l'interet du lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return un entier contenant l'interet du lieu.
 */
int interet_lieu(Donnee * data, int id_lieu){
    return data->lieux[id_lieu].interet;
}

/**
 * \fn int interet_lieu(Donnee * data, int id_lieu).
 * \brief renvoie l'identifiant de la destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'identifiant de la destination de l'arc.
 */
int destination_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->destination->id;
}

/**
 * \fn int depart_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie l'identifiant de la destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'identifiant de la destination de l'arc.
 */
int depart_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->depart->id;
}

/**
 * \fn int distance_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie la distance de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant la distance de l'arc.
 */
int distance_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->distance;
}

/**
 * \fn int insecurite_arc(Donnee * data, int id_lieu, int id_arc).
 * \brief renvoie l'insecurite de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'insecurite de l'arc.
 */
int insecurite_arc(Donnee * data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc]->insecurite;
}

/**
 * \fn int nb_arc(Donnee *data, int id_lieu).
 * \brief renvoie le nombre d'arc que comprent un lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return un entier indiquant le nombre d'arc.
 */
int nb_arc(Donnee *data, int id_lieu){
    return data->lieux[id_lieu].nb_arc;
}

/**
 * \fn int nb_arc_total(Donnee *data).
 * \brief renvoie le nombre d'arc dans le systeme
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le nombre d'arc dans le systeme.
 */
int nb_arc_total(Donnee *data){
    return data->nb_arcs;
}

/**
 * \fn int nb_lieu(Donnee *data).
 * \brief renvoie le nombre de lieu dans le systeme.
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le nombre de lieux.
 */
int nb_lieu(Donnee *data){
    return data->nb_lieux_total;
}

/**
 * \fn int temps_execution(Donnee *data).
 * \brief renvoie le temps de recherche impartie.
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le temps de recherche impartie.
 */
int temps_execution(Donnee *data){
    return data->temps_execution;
}
/**
 * \fn void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc).
 * \brief permet de modifier le nombre d'arc d'un lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param le nombres d'arc.
 */
void maj_nb_arc(Donnee *data, int id_lieu, int nb_arc){
    data->lieux[id_lieu].nb_arc = nb_arc;
}

/**
 * \fn int interet_destination(Donnee *data, int id_lieu, int id_arc).
 * \brief renvoie l'interet de la destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return un entier indiquant l'interet de la destination de l'arc.
 */
int interet_destination(Donnee *data, int id_lieu, int id_arc){
    return interet_lieu(data, destination_arc(data, id_lieu, id_arc));
}

/**
 * \fn char *nom_destination(Donnee *data, int id_lieu, int id_arc).
 * \brief renvoie l'interet de la destination de l'arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return une chaine de caracteres contenant les nom de la destination.
 */
char *nom_destination(Donnee *data, int id_lieu, int id_arc){
    return nom_lieu(data, destination_arc(data, id_lieu, id_arc));
}

/**
 * \fn Arc *pointeur_map_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief retourn in pointeur sur l'arc demandé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return l'addresse de arc.
 */
Arc *pointeur_map_arc(Donnee *data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc];
}

/**
 * \fn void maj_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc).
 * \brief premet de changer l'arc ciblé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \param l'addresse du nouvel arc.
 */
void maj_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc){
    data->map[id_lieu][id_arc] = point_arc;
}

/**
 * \fn void spr_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief premet de suprimer un arc du tas.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 */
void spr_pointeur_map_arc(Donnee *data, int id_lieu, int id_arc){
    free(data->map[id_lieu][id_arc]);
}

/**
 * \fn Index_arc *pointeur_index_arc(Donnee *data, int id_depart, int id_arrive).
 * \brief retourn un pointeur sur une structure index_arc depuis l'index en fonction du lieur de depart et du lieu d'arrivé.
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
 * \fn int index_destination(Donnee *data, int id_depart, int id_arrive).
 * \brief retourne l'identifiant de l'arc corespondant au lieu de depart et de destination indiqué, ou -1 si la destination n'est pas accessible.
 *
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return un identifiant d'arc ou -1 s'il n'existe pas.
 */
int index_destination(Donnee *data, int id_depart, int id_arrive){
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

int liste_lieu_interet(Donnee *data, int id_table){
    return data->liste_lieu[id_table].interet;
}

Lieu *liste_lieu_lieu(Donnee *data, int id_table){
    return data->liste_lieu[id_table].lieu;
}




