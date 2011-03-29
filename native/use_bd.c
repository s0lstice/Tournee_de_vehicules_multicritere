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
    return data->map[id_lieu][id_arc]->destination;
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
    return data->map[id_lieu][id_arc]->depart;
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
 * \fn Arc *pointeur_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief renvoie un ponteur sur un arc.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \return renvoie un ponteur de type Arc sur l'arc ciblé.
 */
Arc *pointeur_arc(Donnee *data, int id_lieu, int id_arc){
    return data->map[id_lieu][id_arc];
}

/**
 * \fn void maj_pointeur_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc).
 * \brief premet de changer l'arc ciblé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 * \param l'addresse du nouvel arc.
 */
void maj_pointeur_arc(Donnee *data, int id_lieu, int id_arc, Arc *point_arc){
    data->map[id_lieu][id_arc] = point_arc;
}

/**
 * \fn void spr_pointeur_arc(Donnee *data, int id_lieu, int id_arc).
 * \brief premet de suprimer un arc du tas.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \param l'indentifiant de l'arc.
 */
void spr_pointeur_arc(Donnee *data, int id_lieu, int id_arc){
    free(data->map[id_lieu][id_arc]);
}
