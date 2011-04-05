/**
 * \file create_bd.h
 * \brief Pars le dociment et stock toutes les valeurs en memoire.
 * \author Mickael PURET
 * \date 21 mars 2011
 *
 */

#ifndef CREATE_BD_H_INCLUDED
#define CREATE_BD_H_INCLUDED

#include <stdio.h>

typedef struct parcourt Parcourt;
typedef struct caracteristique Caracteristique;
typedef struct arc Arc;
typedef struct lieu Lieu;
typedef struct donnee Donnee;
typedef struct index_arc Index_arc;
typedef struct interet_lieu Interet_lieu;

/**
 * \struct index_arc create_bd.h
 * \brief definit le premeire arc d'un lieu et le nombre d'arc disponible pour ce lieu.
 *
 * utilisé pour gerer l'index sur map.
 */
struct interet_lieu{
    int interet;/*!< interet du lieu*/
    Lieu *lieu;/*!< pointeur sur le lieu*/
};

/**
 * \struct index_arc create_bd.h
 * \brief definit le premeire arc d'un lieu et le nombre d'arc disponible pour ce lieu.
 *
 * utilisé pour gerer l'index sur map.
 */
struct index_arc{
    int id_arc; /*!< identifiant de l'arc*/
    int nb_arc; /*!< nombre d'arc disponible*/
};
/**
 * \struct parcourt create_bd.h
 * \brief Contien les referances à un arc conservé.
 *
 * parcourt est composé d'une variable carac, de type 'caracteristique', pointant sur les caracteristiques du arc.
 * Il comporte un tableau, de type 'arc', qui contient tous les arcs parcouruent sur ce trajet.
 *
 */
struct parcourt{
    Caracteristique *carac; /*!< pointeur sur les caracteristique de cette solution.*/
    Arc *trajet; /*!< tableau contenent les arcs utilisé dans cette solution.*/
};

/**
 * \struct caracteristique create_bd.h
 * \brief Contien les referances d'une solution.
 *
 * Inetret, distance, insecurité globale mais egalement le nombre de lieux qui presente de l'interet et le nombre de lieux total du parcours.
 *
 */
struct caracteristique{
    int interet; /*!< interet total.*/
    int distance; /*!< distance total.*/
    int insecurite; /*!< insecurite total.*/
    int nb_lieux_utile;  /*!< nombre de lieux comptant dans l'interet.*/
    int nb_lieux_total; /*!< nombre de lieux total.*/
};

/**
 * \struct arc create_bd.h
 * \brief definit un arc par son point de depart, sa distance, son insecuritet et sa desitnation.
 *
 */
struct arc{
    int distance; /*!< distance du arc.*/
    int insecurite; /*!< insecurite du arc.*/
    Lieu *depart; /*!< lieu de depart du arc.*/
    Lieu *destination; /*!< lieu de destination du arc.*/
};

/**
 * \struct lieu create_bd.h
 * \brief caracterise un lieu.
 *
 */
struct lieu{
    int id; /*!< numerot du lieu.*/
    int interet; /*!< interet du lieu.*/
    char *nom; /*!< nom du lieu.*/
    int nb_arc; /*!< nombre de arcs sortant.*/
};

/**
 * \struct donnee create_bd.h
 * \brief contien l'ensemble des données du programme.
 *
 */
struct donnee{
    int temps_execution; /*!< temps impartie pour la recherche de solutions.*/
    int nb_lieux_total; /*!< nombre de lieu interessant.*/
    int nb_arcs; /*!< nombre d'arcs total.*/
    Interet_lieu *table_interet; /*!< tableau des interets décroissant avec les coresspondance des lieux*/
    Lieu *lieux; /*!< pointeur sur un tableau contenent l'ensemble des referances des lieux.*/
    Index_arc ***index_lieu; /*!< pointeur sur une table d'index pour l'utilisation de map*/
    Arc ***map; /*!< pointeur sur un tableau contenant pour chaque lieu l'enseble des arcs disponible. ces arc sont trié par interet décroissant, distance et insecurite croissant*/
    Caracteristique *solution; /*!< pointeur sur un tableau contenant l'ensemble des solutions acceptable */
};

Donnee * main_create_db(char * path);
void free_db(Donnee * data);
#endif // CREAT_BD_H_INCLUDED
