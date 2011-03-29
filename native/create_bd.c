/**
 * \file create_bd.c
 * \brief Pars le dociment et stock toutes les valeurs en memoire.
 * \author Mickael PURET
 * \date 21 mars 2011
 *
 */

#include "create_bd.h"
#include "erreur.h"
#include "tri.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/**
 * \fn static FILE * open_file(char * path)
 * \brief ouvre un fichier et retourne un pointeur sur une structure FILE.
 *
 * \param chaine de caractères indiquant le arc du fichier à ouvrir.
 * \return Un pointeur sur une structure FILE.
 */
static FILE * open_file(char * path){
    FILE * file;
    if( (file = fopen(path, "rt")) == NULL ) fatalerreur("open_file : ouverture du fichier imposible");
    return file;
}

/**
 * \fn static char * readLine(FILE * fichier)
 * \brief lit une ligne d'au maximum 1024 caractères et la retourne sous forme d'une chaine alloué sur le tas.
 *
 * \param Un pointeur sur une structure FILE valide.
 * \return une chaine de caractères.
 */
static char * readLine(FILE * fichier) {
    char buf[1024];
    char * result = strdup(fgets(buf, 1024, fichier));
    return result;
}

/**
 * \fn static void ajout_parametre(Donnee * data, FILE * file)
 * \brief Lit la ligne contenant les parametres du programme (temps d'execution, nombre de lieux, nombre d'arc) et les stock dans la vaiable data.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param Un pointeur sur une structure FILE.
 */
static void ajout_parametre(Donnee * data, FILE * file){
    fscanf(file, "%d;%d;%d", &data->temps_execution, &data->nb_lieux_total, &data->nb_arcs);
    /* les nombres d'elements doivent contenir le nombre exacte*/
    data->nb_arcs++;
    data->nb_lieux_total++;
}

/**
 * \fn static void ajout_lieux(Donnee * data, FILE * file)
 * \brief Ajoute les lieux et leur interet dans la variable data et tri le tableau à deux dimentions interet dans l'ordre decroissant de l'interet.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param Un pointeur sur une structure FILE.
 */
static void ajout_lieux(Donnee * data, FILE * file){
    char nom_lieu[1024];
    int num_lieu, intret_lieu;

    /* allocation du tableau de type Lieu*/
    if(data->lieux == NULL) if((data->lieux = (Lieu*)malloc(data->nb_lieux_total*sizeof(Lieu))) == NULL)  fatalerreur("ajout_lieux : la creation du table lieux a echoué\n");

    /* initialisation des tableau lieux et interet*/
    while(fscanf(file, "%d;%d;%s\n", &num_lieu, &intret_lieu, nom_lieu) == 3){
        data->lieux[num_lieu].interet = intret_lieu;
        data->lieux[num_lieu].nom = strdup(nom_lieu);
        data->lieux[num_lieu].nb_arc = 0;
    }
}

/**
 * \fn static void ajout_arcs(Donnee * data, FILE * file)
 * \brief Ajoute les arcs(lieu de depart, distance, insecurité, lieu d'arrivé) dans la variable data. C'est information contenue dans le tableau map sont classé en fonction de le lieu de depart, de l'interet du lieu d'arrivé (decroissant), de la distance (croissant) puis de l'insecurité (croissant). Les doublons et les dominés ont été suprimé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param Un pointeur sur une structure FILE.
 */
static void ajout_arcs(Donnee * data, FILE * file){
    int nb_element = data->nb_arcs / data->nb_lieux_total + 1;
    Arc **ch_tmp;
    int i = 0, l1, l2, distance, insecurite, int_tmp, j;
    int * nb_element_lieu;

    /* allocation du tableau map a deux dimantions. cette table grandi en fonction de nb_element et du nombre d'arcs pour un lieu*/
    data->map = (Arc ***)malloc(data->nb_lieux_total*sizeof(Arc**));
    if(data->map == NULL) fatalerreur("ajout_arcs : echec de l'allocation de map lv1");

    for(i = 0;  i < data->nb_lieux_total; ++i){
        data->map[i] = (Arc**)malloc(nb_element*sizeof(Arc*));
        if(data->map[i] == NULL) fatalerreur("ajout_arcs : echec de l'allocation de map lv2");
    }

    /* allocation d'un tableau temporaire servent a gere l'alloaction du nombre d'arcs de chaque lieu.*/
    nb_element_lieu = (int *)malloc((data->nb_lieux_total)*sizeof(int));
    if(nb_element_lieu == NULL) fatalerreur("ajout_arcs : echec de l'allocation de nb_element_lieu");

    /* initialisation de cette table a deux dimantions (nombre d'element x nombre d'element max)*/
    for(i = 0; i < data->nb_lieux_total; ++i)
        nb_element_lieu[i] = 0;

    /* lecture du fichier ligne a ligne et traitement des informations*/
    while(fscanf(file, "%d;%d;%d;%d\n", &l1, &l2, &distance, &insecurite) == 4){
        /*si le nombre d'arcs enregistre est superieur ou egale au nombre d'element disponible, on augmante le nombre delements de nb_element*/
        if(data->lieux[l1].nb_arc >= nb_element_lieu[l1]){
            ch_tmp = (Arc**)realloc(data->map[l1], (nb_element + nb_element_lieu[l1])*sizeof(Arc*));
            if(ch_tmp == NULL) fatalerreur("ajout_arcs : echec de l'allocation de map lv2");
            data->map[l1] = ch_tmp;

            nb_element_lieu[l1] += nb_element; /*gaumentation du nombre d'elements possible*/
        }

        data->map[l1][data->lieux[l1].nb_arc] = (Arc *)malloc(sizeof(Arc));
        if(data->map[l1][data->lieux[l1].nb_arc] == NULL) fatalerreur("ajout_arcs : allocation de l'arc");
        /* on instrit l'arc a son lieu de depart*/
        data->map[l1][data->lieux[l1].nb_arc]->depart = l1;
        data->map[l1][data->lieux[l1].nb_arc]->insecurite = insecurite;
        data->map[l1][data->lieux[l1].nb_arc]->distance = distance;
        data->map[l1][data->lieux[l1].nb_arc]->destination = l2;
        data->lieux[l1].nb_arc++; /*gaumentation du nombre d'arcs enregirte*/

        /*si le nombre d'arcs enregistre est superieur ou egale au nombre d'element disponible, on augmante le nombre delements de nb_element*/
        if(data->lieux[l2].nb_arc >= nb_element_lieu[l2]){
            ch_tmp = (Arc**)realloc(data->map[l2], (nb_element + nb_element_lieu[l2])*sizeof(Arc*));
            if(ch_tmp == NULL) fatalerreur("ajout_arcs : echec de l'allocation de map lv2");
            data->map[l2] = ch_tmp;

            nb_element_lieu[l2] += nb_element; /*gaumentation du nombre d'elements possible*/
        }

        data->map[l2][data->lieux[l2].nb_arc] = (Arc *)malloc(sizeof(Arc));
        if(data->map[l2][data->lieux[l2].nb_arc] == NULL) fatalerreur("ajout_arcs : allocation de l'arc");
        /* on instrit l'arc a son lieu de d'arrive*/
        data->map[l2][data->lieux[l2].nb_arc]->depart = l2;
        data->map[l2][data->lieux[l2].nb_arc]->insecurite = insecurite;
        data->map[l2][data->lieux[l2].nb_arc]->distance = distance;
        data->map[l2][data->lieux[l2].nb_arc]->destination = l1;
        data->lieux[l2].nb_arc++; /*gaumentation du nombre d'arcs enregirte*/
    }

    /* sauvgarde du nombre d'arc dans la table definiassant les lieux et tri les arcs de map*/
    free(nb_element_lieu);
}
/**
 * \fn static void ajout_arcs(Donnee * data, FILE * file)
 * \brief Ouvre le fichier et coordonne les differantes fonctions parmetant le stockage des informations en memoire.
 *
 * \param Une chaine de caractères designant le fichier contenant les données.
 */
Donnee * main_create_db(char * path){
    char * line ;
    int i;
    Donnee * data;

    /*allocation de la structure contenent toutes les donnees et initialisation*/
    data = (Donnee *)malloc(sizeof(Donnee));

    data->temps_execution = 0;
    data->nb_lieux_total = 0;
    data->nb_arcs = 0;
    data->lieux = NULL;
    data->index_lieu = NULL;
    data->map = NULL;
    data->solution = NULL;

    /*ouvreture du fichier*/
    FILE * file = open_file(path);

    /*parcour de tous le fichier*/
    while(!feof(file)){
        /*lit les gigne une a une*/
        line = readLine(file);

        /*si la ligne commance par un # on utilise la fonction corespondane*/
        if(line[0] == '#'){
            if( (strcasecmp(line + 1, "Parametres\n") == 0) ) ajout_parametre(data, file);
            else if( (strcasecmp(line + 1, "Lieux\n") == 0) ) ajout_lieux(data, file);
                else if( (strcasecmp(line + 1, "Arcs\n") == 0) ) ajout_arcs(data, file);
                    else fatalerreur("main_creat_db : aucun traitement pour cette ligne\n");
        }
        free(line);
    }
    for( i = 0; i < data->nb_lieux_total; ++i){
        /* tri des arcs*/
        quicksort_map(data, i, 0, data->lieux[i].nb_arc-1);

        /*supression des arcs domine*/
        data->lieux[i].nb_arc = epure_map(data, i);
    }
    return data;
}

/**
 * \fn static void free_db(Donnee * data)
 * \brief supprime toutes les données du tas.
 *
 * \param la tructure Donnée aloué sur le tas.
 */
void free_db(Donnee * data){
    int i,j;

    /*liberation de toutes les tables*/
    for(i = 0; i < data->nb_lieux_total; ++i){
        free(data->lieux[i].nom);
        for(j = 0; j < data->lieux[i].nb_arc; ++j)
            free(data->map[i][j]);
        free(data->map[i]);
    }
    /*liberation de leur entet*/
    free(data->lieux);
    free(data->map);
    free(data);

}
