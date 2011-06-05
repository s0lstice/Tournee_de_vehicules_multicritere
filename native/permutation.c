/**
 * \file permutation.c
 * \brief methodes pour réaliser une permutation à partir du chemin de base
 * \author Cyrille Picard
 * \date 14 mai 2011
 *
 */
#include "create_bd.h"
#include "use_bd.h"
#include "use_index.h"
#include <stdlib.h>
#include "erreur.h"
#include "use_solution.h"

/**
 * \fn permutation_possible (Donnee *data, int id_lieu_depart, int id_lieu_arrive)
 * \brief permet de tester si il existe un arc entre deux lieux pour réaliser une permutation.
 *
 *
 * \param Un pointeur sur une structure Donnee.
 * \param l'indentifiant du lieu de depart.
 * \param l'indentifiant du lieu d'arrvie.
 * \return 1 ou 0 en fonction de si il existe un arc ente les 2 lieux
 */
 int permutation_possible (Donnee *data, int id_lieu_depart, int id_lieu_arrive){

    if (relation_index_lieu(data, id_lieu_depart, id_lieu_arrive)==1)
        return 1;
    else
    return 0;

}

/*int permutation (Donnee *data,id_solutin,nb_lieu_solution)
{
int i, tmp;
//création tableau + remplissage avec les identifiants de la solution de base
int idlieu_Chbase[nb_lieu_solution];
for (i=0; i < nb_lieu_total; i++){
	idlieu_Chbase[i]= cpy_solution(data,0,1);
}
//réalisation de la permutation
for (i=0; i!=nb_lieu_solution; i++){
	if (permutation_possible(i+2;i+1)==1) {
		tmp = idlieu_Chbase[i+2];
		idlieu_Chbase[i+2] = lieu[i+1];
		idlieu_Chbase[i+1] = tmp;
		break;
	}
	else
		fprint("Il n'y a pas de permutation possible\n");
		exit 0;
}
	return 1;


}*/


