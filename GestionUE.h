//
// Created by Rabha on 06/12/2020.
//

#ifndef PROJET_C_2020_GESTIONUE_H
#define PROJET_C_2020_GESTIONUE_H

#include <stdlib.h>
#include "Structures.h"

UE * insererUE (UE *listeUE, char idUE[], char nom[],int ponderation)
{
    UE *UEPrecedent = NULL;
    UE *parcoursUE = listeUE;

    UE *newUE = NULL;

    while(parcoursUE != NULL)
    {
        if(strcmp(parcoursUE->codeUE, idUE) < 0)
        {
            UEPrecedent = parcoursUE;
            parcoursUE = parcoursUE->suivant;
        }
        else{
            newUE = malloc(sizeof(UE));
            strcpy(newUE->intitule, nom);
            strcpy(newUE->codeUE, idUE);
            newUE->nbCredit = ponderation;

            if(UEPrecedent != NULL)
            {
                UEPrecedent->suivant = newUE;
            }
            else {
                listeUE = newUE;
            }
            newUE->suivant = parcoursUE;

            break;
        }
    }

    if(newUE == NULL)
    {
        newUE = malloc(sizeof(UE));
        strcpy(newUE->intitule, nom);
        strcpy(newUE->codeUE, idUE);
        newUE->nbCredit = ponderation;
        UEPrecedent->suivant = newUE;
        newUE->suivant=NULL;
    }

    return listeUE;
}

UE* rechercheUE(UE*listeUE , char id[6])
{
    UE *parcoursUE = listeUE;

    while (parcoursUE != NULL)
    {
        if(strcmp(parcoursUE->codeUE, id) == 0)
        {
            return parcoursUE;
        }
        parcoursUE = parcoursUE->suivant;
    }

    return NULL;
}

UE * lireFichierUE(char *cheminFichier)
{
    FILE *fdat = fopen(cheminFichier,"r");
    char codeUE[6],intitule[50];
    int ponderation;
    UE *debutListeUE;
    debutListeUE=malloc(sizeof(UE));

    fscanf(fdat, "%s %s %d",debutListeUE->codeUE,debutListeUE->intitule,&debutListeUE->nbCredit);

    debutListeUE->suivant = NULL;

    while(!feof(fdat))
    {
        fscanf(fdat,"%s %s %d",codeUE,intitule,&ponderation);
        debutListeUE = insererUE(debutListeUE,codeUE,intitule,ponderation);
    }

    fclose(fdat);
    return debutListeUE;
}
UE *ajouterUE(char*fichierUE,UE *listeUE, char idUE[], char nom[],int ponderation)
{
    FILE *fdat = fopen(fichierUE,"a");
    if(rechercheUE(listeUE,idUE) != NULL){
        printf("L'UE existe deja\n");
        return listeUE;
    }

    fprintf(fdat,"\n%s %s %d",idUE,nom,ponderation);
    fclose(fdat);
    return insererUE(listeUE,idUE,nom,ponderation);

}

void reecrireFichierUE(char * cheminFichier , UE*listeUE )
{
    FILE *fdat = fopen(cheminFichier,"w");
    UE *parcoursUE = listeUE;

    while (parcoursUE != NULL)
    {
        fprintf(fdat,"%s %s %d",parcoursUE->codeUE,parcoursUE->intitule,parcoursUE->nbCredit);

        if(parcoursUE->suivant != NULL){
            fprintf(fdat,"\n");
        }
        parcoursUE = parcoursUE->suivant;
    }

    fclose(fdat);
}

UE* supprimerUE(char *fichierDat, UE *listeUE , char codeUE[] )
{

    if(rechercheUE(listeUE, codeUE) == NULL)
    {
        printf("l'UE n'existe pas impossible a supprimer");
        return listeUE;
    }
    else{
        UE *parcoursUE = listeUE;
        UE *uePrecedent = NULL;

        while (parcoursUE != NULL)
        {
            if(strcmp(parcoursUE->codeUE, codeUE) == 0)
            {
                if (uePrecedent != NULL)
                {
                    uePrecedent->suivant = parcoursUE->suivant;
                    free(parcoursUE);
                    reecrireFichierUE(fichierDat, listeUE);
                    return listeUE;
                }
                else
                {
                    uePrecedent = listeUE;
                    listeUE = listeUE->suivant;
                    free(uePrecedent);
                    reecrireFichierUE(fichierDat, listeUE);
                    return listeUE;
                }
            }

            uePrecedent = parcoursUE;
            parcoursUE = parcoursUE->suivant;
        }
    }

    return listeUE;
}

UE * modifierUE(char *fichierDat, UE *listeUE , char id[], char intitule[],int ponderation)
{
    if(rechercheUE(listeUE, id) == NULL)
    {
        printf("l'UE n'existe pas impossible a modifier");
        return listeUE;
    }
    else {
         UE *parcoursUE = listeUE;

        while (parcoursUE != NULL) {
            if (strcmp(parcoursUE->codeUE, id) == 0) {

                strcpy(parcoursUE->intitule,intitule);
                parcoursUE->nbCredit = ponderation;
                reecrireFichierUE(fichierDat, listeUE);
                return listeUE;
            }

            parcoursUE = parcoursUE->suivant;
        }
    }

    return listeUE;

}

unsigned long plusLongIntituleUE(UE* listeUE)
{
    UE* parcoursUE = listeUE;
    unsigned long retour = 0;

    while(parcoursUE != NULL)
    {
        unsigned long taille = strlen(parcoursUE->intitule);
        if(taille > retour) retour = taille;
        parcoursUE = parcoursUE->suivant;
    }

    return retour;
}

void afficherUE(UE* listeUE)
{
    UE* parcoursUE = listeUE;

    unsigned long tailleIntitule = plusLongIntituleUE(listeUE);
    if(tailleIntitule < 8) tailleIntitule = 8;

    printf("+-------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+---------+\n");

    printf("| Code  | Intitule");
    for(int i = 0; i < tailleIntitule-8; i++)
    {
        printf(" ");
    }
    printf(" | Credits |\n");

    printf("+-------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+---------+\n");


    while(parcoursUE != NULL)
    {
        printf("| %-5s | %-s", parcoursUE->codeUE, parcoursUE->intitule);
        for(int i = 0; i < tailleIntitule-(strlen(parcoursUE->intitule)-1 ); i++)
        {
            printf(" ");
        }
        printf("| %7d |\n",parcoursUE->nbCredit);
        parcoursUE = parcoursUE->suivant;
    }

    printf("+-------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+---------+\n");

}

#endif //PROJET_C_2020_GESTIONUE_H
