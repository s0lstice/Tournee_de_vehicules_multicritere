/**
 * \file use_bd.c
 * \brief ensemble de methodes permetant la recuperation d'informations provenant des données.
 * \author Mickael PURET & Cyrille Picard
 * \date 25 mars 2011
 *
 */
#include "create_bd.h"
#include "use_bd.h"
#include <stdlib.h>
#include "erreur.h"

/**
 * \fn char * nom_lieu(Donnee * data, int id_lieu).
 * \brief renvoie le nom du lieu à partir du tableau lieu de la structure de donnee et de l'identifiant du lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return une chaine de caracteres contenant le nom du lieu.
 */
char *nom_lieu(Donnee * data, int id_lieu){
    return data->lieux[id_lieu].nom;
}

/**
 * \fn int interet_lieu(Donnee * data, int id_lieu).
 * \brief renvoie l'interet du lieu à partir du tableau lieu de la structure de donnee et de l'identifiant du lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return un entier contenant l'interet du lieu.
 */
int interet_lieu(Donnee * data, int id_lieu){
    return data->lieux[id_lieu].interet;
}

/**
 * \fn int nb_arc(Donnee *data, int id_lieu).
 * \brief renvoie le nombre d'arc sortant que comprent un lieu à partir du tableau lieu de la structure de donnee et de l'identifiant du lieu.

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
 * \brief renvoie le nombre d'arc dans le systeme.
 *
 * \param Un pointeur sur une structure Donnee.
 * \return un entier indiquant le nombre d'arc total dans le systeme.
 */
int nb_arc_total(Donnee *data){
    return data->nb_arcs;
}

/**
 * \fn int nb_lieu(Donnee *data).
 * \brief renvoie le nombre de lieu total dans le systeme.
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

int nb_solution(Donnee *data){
    return data->nb_solution;
}
