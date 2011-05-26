/**
 * \file create_bd.c
 * \brief Parcours le document texte et stock toutes les valeurs en memoire.
 * \author Mickael PURET & CP
 * \date 21 mars 2011
 *
 */

#include "create_bd.h"
#include "erreur.h"
#include "use_bd.h"
#include "use_map.h"
#include "use_index.h"
#include "use_liste.h"
#include "use_solution.h"
#include "use_lieu.h"
#include "use_resultat.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/**
 * \fn static FILE * open_file(char * path)
 * \brief ouvre un fichier et retourne un pointeur sur une structure FILE.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param chaine de caractères indiquant le arc du fichier à ouvrir.
 * \return Un pointeur sur une structure FILE.
 */
static FILE * open_file(Donnee *data,char * path){
    FILE * file;
    if( (file = fopen(path, "rt")) == NULL ) fatalerreur(data, "open_file : ouverture du fichier imposible");
    return file;
}

/**
 * \fn static char * readLine(FILE * fichier)
 * \brief lit une ligne d'au maximum 1024 caractères et la retourne sous forme d'une chaine allouée sur le tas.
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
    fscanf(file, "%d;%d;%d;%c", &data->parametres.temps_execution, &data->parametres.nb_lieux, &data->parametres.nb_arcs, &data->parametres.ordre_lieu);
}

/**
 * \fn static void ajout_lieux(Donnee * data, FILE * file)
 * \brief Ajoute l'identifiant, le nom, le nombre d'arcs et l'interet de chaques lieu dans la table Lieux.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param Un pointeur sur une structure FILE.
 */
static void ajout_lieux(Donnee * data, FILE * file){
    char nom_lieu[1024];
    int num_lieu, intret_lieu, id = 0;

    /* allocation du tableau de type Lieu*/
    if(data->lieux == NULL) if((data->lieux = (Lieu*)malloc(data->parametres.nb_lieux*sizeof(Lieu))) == NULL)  fatalerreur(data, "ajout_lieux : la creation du table lieux a echoué\n");

    /* initialisation des tableau lieux et interet*/
    while(fscanf(file, "%d;%d;%s\n", &num_lieu, &intret_lieu, nom_lieu) == 3){
        data->lieux[num_lieu].interet = intret_lieu;
        data->lieux[num_lieu].nom = strdup(nom_lieu);
        data->lieux[num_lieu].nb_arc = 0;
        data->lieux[num_lieu].id = id++;
    }
}

/**
 * \fn static int position_arc(const void *p1, const void *p2).
 * \brief indique si l'arc p1 doit se trouver avant l'arc p2 selon :
 * p1.destination.interet >= p2.destination.interet et
 * p1.distance <= p2.distance et
 * p1.insecurité <= p2.insecurité.
 *
 * \param pointeur sur l'arc 1.
 * \param pointeur sur l'arc 2.
 */
static int position_arc(const void *p1, const void *p2){
    Arc *a = *((Arc* const*)p1);
    Arc *b = *((Arc* const*)p2);

    /*comparaison*/

    /*distinction des lieux d'interet differant, l'interet le plus fort est placé avant*/
    if(a->destination->interet > b->destination->interet)
        return -1;

    if(a->destination->interet == b->destination->interet){
        /*distinction des lieux d'interet identique, l'identifiant le plus faible est placé avant*/
        if(a->destination->id < b->destination->id)
            return -1;

        /*distinction des distance, la distance la plus faible est placé avant*/
        if(a->distance < b->distance)
            return -1;

        /* en cas de distance identique, c'est l'insecurite qui devient placent, l'insecurite le plus faible est placeavant*/
        if(a->distance == b->distance)
            if(a->insecurite <= b->insecurite)
                return -1;
    }
    return 1;
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
    int id_arc, id_key = 0, id_cpy = 1;

    int arc_distance, arc_insecurite, arc_destination;

    /*recuperation des valeurs de la clef*/
    int key_distance = distance_map_arc(data, id_lieu, id_key);
    int key_insecurite = insecurite_map_arc(data, id_lieu, id_key);
    int key_destination = destination_map_arc(data, id_lieu, id_key);

    /*lecture de tous le tableau*/
    for(id_arc = 1 ; id_arc < nbre_arc ; ++id_arc){
        /*si l'arc n'existe pas, on prends le suivant*/
        while((id_arc != nbre_arc)&&(existe_map_arc(data, id_lieu, id_arc) == 0)) id_arc++;

        /*recuperation des valeurs de l'arc*/
        arc_distance = distance_map_arc(data, id_lieu, id_arc);
        arc_insecurite = insecurite_map_arc(data, id_lieu, id_arc);
        arc_destination = destination_map_arc(data, id_lieu, id_arc);

        /*si l'arc est domine, on le suprime*/
        /*a destination egale, les inetret sont egaux*/
        if((arc_destination == key_destination)&&(arc_distance >= key_distance)&&(arc_insecurite >= key_insecurite)){
            spr_str_map_arc(data, id_lieu, id_arc);
            maj_str_map_arc(data, id_lieu, id_arc, NULL);
        }
        else{
            /*si les lieux de destinations sont differant*/
            if(arc_destination != key_destination){
                /*on deplace la clef d'un*/
                ++id_key;
                /*si l'arc n'existe pas, on prends le suivant*/
                while((id_key != nbre_arc)&&(str_map_arc(data, id_lieu, id_key) == NULL)) ++id_key;

                /*recuperation des valeurs de la clef*/
                key_distance = distance_map_arc(data, id_lieu, id_key);
                key_insecurite = insecurite_map_arc(data, id_lieu, id_key);
                key_destination = destination_map_arc(data, id_lieu, id_key);
            }

            /* s'il y a des arc de supprimes, on comble les trous*/
            if(id_arc != id_cpy){
                if(str_map_arc(data, id_lieu, id_cpy) != NULL) spr_str_map_arc(data, id_lieu, id_cpy);
                maj_str_map_arc(data, id_lieu, id_cpy, str_map_arc(data, id_lieu, id_arc));
                maj_str_map_arc(data, id_lieu, id_arc, NULL);
            }
            ++id_cpy;
        }
    }
    return id_cpy;
}

/**
 * \fn static void ajout_arcs(Donnee * data, FILE * file)
 * \brief Ajoute les arcs(lieu de depart, distance, insecurité, lieu d'arrivé) dans la variable data. C'est information contenue dans le tableau map sont classé en fonction de le lieu de depart, de l'interet du lieu d'arrivé (decroissant), de la distance (croissant) puis de l'insecurité (croissant). Les doublons et les dominés ont été suprimé.
 *
 * \param Un pointeur sur une structure Donnee.
 * \param Un pointeur sur une structure FILE.
 */
static void ajout_arcs(Donnee * data, FILE * file){
    int nb_element = data->parametres.nb_arcs / data->parametres.nb_lieux + 1;
    Arc **ch_tmp;
    int i = 0, l1, l2, distance, insecurite;
    int * nb_element_lieu;

    /* allocation du tableau map a deux dimantions. cette table grandi en fonction de nb_element et du nombre d'arcs pour un lieu*/
    data->map = (Arc ***)malloc(data->parametres.nb_lieux*sizeof(Arc**));
    if(data->map == NULL) fatalerreur(data, "ajout_arcs : echec de l'allocation de map lv1");

    for(i = 0;  i < data->parametres.nb_lieux; ++i){
        data->map[i] = (Arc**)malloc(nb_element*sizeof(Arc*));
        if(data->map[i] == NULL) fatalerreur(data, "ajout_arcs : echec de l'allocation de map lv2");
    }

    /* allocation d'un tableau temporaire servent a gere l'alloaction du nombre d'arcs de chaque lieu.*/
    nb_element_lieu = (int *)malloc((data->parametres.nb_lieux)*sizeof(int));
    if(nb_element_lieu == NULL) fatalerreur(data, "ajout_arcs : echec de l'allocation de nb_element_lieu");

    /* initialisation de cette table a deux dimantions (nombre d'element x nombre d'element max)*/
    for(i = 0; i < data->parametres.nb_lieux; ++i)
        nb_element_lieu[i] = 0;

    /* lecture du fichier ligne a ligne et traitement des informations*/
    while(fscanf(file, "%d;%d;%d;%d\n", &l1, &l2, &distance, &insecurite) == 4){
        /*si le nombre d'arcs enregistre est superieur ou egale au nombre d'element disponible, on augmante le nombre delements de nb_element*/
        if(data->lieux[l1].nb_arc >= nb_element_lieu[l1]){
            ch_tmp = (Arc**)realloc(data->map[l1], (nb_element + nb_element_lieu[l1])*sizeof(Arc*));
            if(ch_tmp == NULL) fatalerreur(data, "ajout_arcs : echec de l'allocation de map lv2");
            data->map[l1] = ch_tmp;

            nb_element_lieu[l1] += nb_element; /*gaumentation du nombre d'elements possible*/
        }

        data->map[l1][data->lieux[l1].nb_arc] = (Arc *)malloc(sizeof(Arc));
        if(data->map[l1][data->lieux[l1].nb_arc] == NULL) fatalerreur(data, "ajout_arcs : allocation de l'arc");
        /* on instrit l'arc a son lieu de depart*/
        data->map[l1][data->lieux[l1].nb_arc]->depart = &data->lieux[l1];
        data->map[l1][data->lieux[l1].nb_arc]->insecurite = insecurite;
        data->map[l1][data->lieux[l1].nb_arc]->distance = distance;
        data->map[l1][data->lieux[l1].nb_arc]->destination = &data->lieux[l2];
        data->lieux[l1].nb_arc++; /*gaumentation du nombre d'arcs enregirte*/

        /*si le nombre d'arcs enregistre est superieur ou egale au nombre d'element disponible, on augmante le nombre delements de nb_element*/
        if(data->lieux[l2].nb_arc >= nb_element_lieu[l2]){
            ch_tmp = (Arc**)realloc(data->map[l2], (nb_element + nb_element_lieu[l2])*sizeof(Arc*));
            if(ch_tmp == NULL) fatalerreur(data, "ajout_arcs : echec de l'allocation de map lv2");
            data->map[l2] = ch_tmp;

            nb_element_lieu[l2] += nb_element; /*gaumentation du nombre d'elements possible*/
        }

        data->map[l2][data->lieux[l2].nb_arc] = (Arc *)malloc(sizeof(Arc));
        if(data->map[l2][data->lieux[l2].nb_arc] == NULL) fatalerreur(data, "ajout_arcs : allocation de l'arc");
        /*on instrit l'arc a son lieu de d'arrive*/
        data->map[l2][data->lieux[l2].nb_arc]->depart = &data->lieux[l2];
        data->map[l2][data->lieux[l2].nb_arc]->insecurite = insecurite;
        data->map[l2][data->lieux[l2].nb_arc]->distance = distance;
        data->map[l2][data->lieux[l2].nb_arc]->destination = &data->lieux[l1];
        data->lieux[l2].nb_arc++; /*gaumentation du nombre d'arcs enregirte*/
    }

    free(nb_element_lieu);

    /*suppression des arc dommine et mise a jour de la table lieux en fonction*/
    for( i = 0; i < data->parametres.nb_lieux; ++i){
        qsort(data->map[i], data->lieux[i].nb_arc, sizeof(Arc*), position_arc);
        data->lieux[i].nb_arc = epure_map(data, i);
    }
}

/**
 * \fn static int interet_decroissant(const void *val1, const void *val2).
 * \brief indique si l'interet de lieu1 et plus fort que l'interet de lieu2.
 *
 * \param pointeur sur lieu1.
 * \param pointeur sur lieu2.
 */
static int interet_decroissant(const void *lieu1, const void *lieu2){
    int a = ((Coef_lieu const*)lieu1)->coef;
    int b = ((Coef_lieu const*)lieu2)->coef;
    return b - a;
}

/**
 * \fn static int interet_(de)croissant(const void *val1, const void *val2).
 * \brief indique si l'interet de lieu1 et plus faible que l'interet de lieu2.
 *
 * \param pointeur sur lieu1.
 * \param pointeur sur lieu2.
 */
static int interet_croissant(const void *lieu1, const void *lieu2){
    int a = ((Coef_lieu const*)lieu1)->coef;
    int b = ((Coef_lieu const*)lieu2)->coef;
    return a - b;
}

/**
 * \fn static void create_liste(Donnee *data).
 * \brief cree la table interet et la tris en fonction du parametre ordre_lieu.
 *
 * \param Un pointeur sur une structure Donnee.
 */
static void create_liste(Donnee *data){
    int i;

    /*creation de la liste*/
    data->liste_lieu = (Coef_lieu*)malloc(data->parametres.nb_lieux*sizeof(Coef_lieu));
    if(data->liste_lieu == NULL) fatalerreur(data, "creat_interet : echec de l'allocation de la table liste_lieu");

    /*affectation de l'interet et du lieu*/
    for(i = 0; i < data->parametres.nb_lieux; ++i){
        data->liste_lieu[i].coef = data->lieux[i].interet;
        data->liste_lieu[i].lieu = &data->lieux[i];
    }

    /*tris en croissant ou decroissant*/
    if(data->parametres.ordre_lieu == 'd')
        qsort(data->liste_lieu, data->parametres.nb_lieux, sizeof(Coef_lieu), interet_decroissant);
    else
        qsort(data->liste_lieu, data->parametres.nb_lieux, sizeof(Coef_lieu), interet_croissant);
}

/**
 * \fn static void create_index(Donnee *data, int id_lieu).
 * \brief cree la table d'index et l'initalise en fonction de map.
 *
 * \param Un pointeur sur une structure Donnee.
 */
static void create_index(Donnee *data){
    int id_lieu,i, last_lieu;
    Arc **map;

    /*creation de l'index de niveau 1*/
    data->index_lieu = (Index_arc***)malloc(data->parametres.nb_lieux * sizeof(Index_arc**));
    if(data->index_lieu == NULL)
        fatalerreur(data, "create_index : creation de la table d'index impossible lv 1");


    for( id_lieu = 0; id_lieu < data->parametres.nb_lieux; ++id_lieu){
        map = data->map[id_lieu];

        /*creation de l'index de niveau 1*/
        data->index_lieu[id_lieu] = (Index_arc**)malloc(data->parametres.nb_lieux * sizeof(Index_arc*));
        if(data->index_lieu[id_lieu] == NULL)
            fatalerreur(data, "create_index : creation de la table d'index impossible lv 2");

        /*initialisation a NULL*/
        for(i = 0; i < data->parametres.nb_lieux; ++i)
            data->index_lieu[id_lieu][i] = NULL;

        /*creation de la structure Index_arc en fonction de map*/
        data->index_lieu[id_lieu][map[0]->destination->id] = (Index_arc*)malloc(sizeof(Index_arc));
        data->index_lieu[id_lieu][map[0]->destination->id]->id_arc = 0;

        /*creation de la structure Index_arc en fonction de map pour les destination suivente*/
        last_lieu = 0;
        for(i = 1; i < data->lieux[id_lieu].nb_arc; ++i){
            if(map[last_lieu]->destination != map[i]->destination){
                data->index_lieu[id_lieu][map[i]->destination->id] = (Index_arc*)malloc(sizeof(Index_arc));
                data->index_lieu[id_lieu][map[i]->destination->id]->id_arc = i;

                data->index_lieu[id_lieu][map[last_lieu]->destination->id]->nb_arc = i - last_lieu;

                last_lieu = i;
            }

        }

        /*mise a jour du nombre d'arc disponible dans l'index*/
        data->index_lieu[id_lieu][map[last_lieu]->destination->id]->nb_arc = i - last_lieu;
    }
}

/**
 * \fn static void ajout_arcs(Donnee * data, FILE * file)
 * \brief Ouvre le fichier et coordonne les differantes fonctions parmetant le stockage des informations en memoire.
 *
 * \param Une chaine de caractères designant le fichier contenant les données.
 */
Donnee * main_create_db(char * path){
    char * line ;
    Donnee * data;

    /*allocation de la structure contenent toutes les donnees et initialisation*/
    data = (Donnee *)malloc(sizeof(Donnee));

    data->parametres.temps_execution = 0;

    data->parametres.nb_arcs = 0;
    data->lieux = NULL;
    data->index_lieu = NULL;
    data->map = NULL;
    data->liste_lieu = NULL;

    init_solution(data);
    init_resultat(data);

    /*ouvreture du fichier*/
    FILE * file = open_file(data, path);


    /*parcour de tous le fichier*/
    while(!feof(file)){
        /*lit les gigne une a une*/
        line = readLine(file);

        /*si la ligne commance par un # on utilise la fonction corespondane*/
        if(line[0] == '#'){
            if( strcasecmp(line + 1, "Parametres\n") == 0 ) ajout_parametre(data, file);
            else if( strcasecmp(line + 1, "Lieux\n") == 0 ) ajout_lieux(data, file);
                else if( strcasecmp(line + 1, "Arcs\n") == 0 ) ajout_arcs(data, file);
                    else fatalerreur(data, "main_creat_db : aucun traitement pour cette ligne\n");
        }
        free(line);
    }

    create_liste(data);
    create_index(data);

    /*fermeture du fichier*/
    fclose(file);
    return data;
}

/**
 * \fn static void free_db(Donnee * data)
 * \brief supprime toutes les données du tas.
 *
 * \param la tructure Donnée aloué sur le tas.
 */
void free_db(Donnee * data){
    unall_resultats(data);
    unall_solutions(data);
    unall_index(data);
    unall_liste(data);
    unall_map(data);
    unall_lieu(data);
    free(data);
}
