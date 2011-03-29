/**
 * \file tri.c
 * \brief perment de trier les arcs selon l'interte de la destination, la distance et l'insecurité. Et la suppretion d'arcs dominés.
 * \author Mickael PURET
 * \date 27 mars 2011
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "tri.h"
#include "create_bd.h"
#include "use_bd.h"
#include "erreur.h"

// source : http://cprogramminglanguage.net/quicksort-algorithm-c-source-code.aspx

/**
 * \fn static int position(Donnee *data, int id_lieu, int id_arc, int id_key)
 * \brief indique si l'arc A doit se trouver avant l'arc B selon :
 * A.destination.interet >= B.destination.interet et
 * A.distance <= B.distance et
 * A.insecurité <= B.insecurité.
 *
 * \param data, contien l'ensemble des données disponible.
 * \param id_lieu, identifiant du leiu de départ des arcs.
 * \param id_arc, c'est l'arc vatriant dans al fonctin de recherche quicksort.
 * \param id_key, c'est l'arc pivot de la fonction de recherche quicksort.
 */
static int position(Donnee *data, int id_lieu, int id_arc, int id_key){
    /*recuperation des valeurs*/
    int key_interet = interet_destination(data, id_lieu, id_key);
    int key_distance = distance_arc(data, id_lieu, id_key);
    int key_insecurite = insecurite_arc(data, id_lieu, id_key);

    int arc_interet = interet_destination(data, id_lieu, id_arc);
    int arc_distance = distance_arc(data, id_lieu, id_arc);
    int arc_insecurite = insecurite_arc(data, id_lieu, id_arc);

    /*comparaison*/
    if(arc_interet > key_interet)
        return 0;

    if(arc_interet == key_interet){
        if(arc_distance < key_distance)
            return 0;
        if(arc_distance == key_distance)
            if(arc_insecurite <= key_insecurite)
                return 0;
    }
    return 1;
}

/**
 * \fn static void swap(arc *x,arc *y)
 * \brief interverti deux elements.
 *
 * \param x, pointeur sur l'élément x.
 * \param y, pointeur sur l'élément y.
 */
static void swap(Arc *x,Arc *y){
    Arc temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/**
 * \fn static int choose_pivot(int i,int j )
 * \brief fonction du chois de pivot pour la methode du quicksort.
 *
 * \param i, indice de depart de la recherche.
 * \param j, indice de fin de la recherche.
 */
static int choose_pivot(int i,int j ){
    return((i+j) /2);
}

/**
 * \fn static int choose_pivot(int i,int j )
 * \brief fonction du chois de pivot pour la methode du quicksort.
 *
 * \param i, indice de depart de la recherche.
 * \param j, indice de fin de la recherche.
 */
void quicksort_map(Donnee * data, int id_lieu, int m,int n){
    Arc **map = data->map[id_lieu];
    int i, j, k;

    if( m < n){
        /*determination et sauvgarde du pivot*/
        k = choose_pivot(m,n);
        swap(map[m],map[k]);

        /*placement des marqueurs*/
        i = m + 1;
        j = n;

        /*recherche des elements a permuter*/
        while(i <= j)
        {
            /*element a gauche*/
            while((i <= n) && (position(data, id_lieu, i, m) == 0))
                i++;
            /*element a droit*/
            while((j >= m) && (position(data, id_lieu, j, m) != 0))
                j--;
            if( i < j){
                /*permutation*/
                swap(map[i], map[j]);
            }
        }

        /* remise en place du pivot*/
        swap(map[m],map[j]);

        /* appel recursif sur les deux demi element droite et gauche*/
        quicksort_map(data, id_lieu, m, j-1);
        quicksort_map(data, id_lieu, j+1, n);
    }
}

/**
 * \fn int epure_map(Donnee *data,int id_lieu)
 * \brief supprime les arcs domminés du lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu.
 * \return le nombre d'arcs restant en depart du lieu.
 */
int epure_map(Donnee *data,int id_lieu){
    int nbre_arc = nb_arc(data, id_lieu);
    int id_arc, id_key = 0, id_cpy = 1, i;

    int arc_interet, arc_distance, arc_insecurite;

    /*recuperation des valeurs de la clef*/
    int key_interet = interet_destination(data, id_lieu, id_key);
    int key_distance = distance_arc(data, id_lieu, id_key);
    int key_insecurite = insecurite_arc(data, id_lieu, id_key);

    /*lecture de tous le tableau*/
    for(id_arc = 1 ; id_arc < nbre_arc ; ++id_arc){
        /*si l'arc n'existe pas, on prends le suivant*/
        while((id_arc != nbre_arc)&&(pointeur_arc(data, id_lieu, id_arc) == NULL)) id_arc++;

        /*recuperation des valeurs de l'arc*/
        arc_interet = interet_destination(data, id_lieu, id_arc);
        arc_distance = distance_arc(data, id_lieu, id_arc);
        arc_insecurite = insecurite_arc(data, id_lieu, id_arc);

        /*si l'arc est domine, on le suprime*/
        if((arc_interet == key_interet)&&(arc_distance >= key_distance)&&(arc_insecurite >= key_insecurite)){
            spr_pointeur_arc(data, id_lieu, id_arc);
            maj_pointeur_arc(data, id_lieu, id_arc, NULL);
        }
        else{
            /* l'inetere de la clef est differnts de celui de l'arc, on deplace la clef de un*/
            if(arc_interet < key_interet){
                /*si l'arc n'existe pas, on prends le suivant*/
                while((id_key != nbre_arc)&&(pointeur_arc(data, id_lieu, id_key) == NULL)) ++id_key;

                /*recuperation des valeurs de la clef*/
                key_interet = interet_destination(data, id_lieu, id_key);
                key_distance = distance_arc(data, id_lieu, id_key);
                key_insecurite = insecurite_arc(data, id_lieu, id_key);
            }

            /* s'il y a des arc de supprimes, on comble les trous*/
            if(id_arc != id_cpy){
                if(pointeur_arc(data, id_lieu, id_cpy) != NULL) spr_pointeur_arc(data, id_lieu, id_cpy);
                maj_pointeur_arc(data, id_lieu, id_cpy, pointeur_arc(data, id_lieu, id_arc));
                maj_pointeur_arc(data, id_lieu, id_arc, NULL);

                ++id_cpy;
            }
        }
    }
    return id_cpy;
}
