//
// Created by Rabha on 06/12/2020.
//

#ifndef PROJET_C_2020_GESTIONAA_H
#define PROJET_C_2020_GESTIONAA_H

#include "Structures.h"
#include <stdlib.h>

AA * insererAA (AA *listeAA, char idUE[],char idAA[], char nom[], int ponderation)
{
    AA *AAPrecedent =NULL;
    AA *parcoursAA = listeAA;

    AA *newAA = NULL;

    while(parcoursAA != NULL)
    {
        if(strcmp(parcoursAA->codeAA, idAA) < 0)
        {
            AAPrecedent = parcoursAA;
            parcoursAA = parcoursAA->suivant;
        }
        else{
            newAA = malloc(sizeof(AA));
            strcpy(newAA->intitule, nom);
            strcpy(newAA->codeUE, idUE);
            strcpy(newAA->codeAA, idAA);

            newAA->ponderation = ponderation;

            if(AAPrecedent != NULL)
            {
                AAPrecedent->suivant = newAA;
            }
            else {
                listeAA = newAA;
            }
            newAA->suivant = parcoursAA;

            break;
        }
    }

    if(newAA == NULL)
    {
        newAA = malloc(sizeof(UE));
        strcpy(newAA->intitule, nom);
        strcpy(newAA->codeUE, idUE);
        newAA->ponderation = ponderation;
        strcpy(newAA->codeAA, idAA);
        AAPrecedent->suivant = newAA;
        newAA->suivant = NULL;

    }

    return listeAA;
}

AA* rechercheAA(AA*listeAA , char id[5])
{
    AA *parcoursAA = listeAA;

    while (parcoursAA != NULL)
    {
        if(strcmp(parcoursAA->codeAA, id) == 0)
        {
            return parcoursAA;
        }
        parcoursAA = parcoursAA->suivant;
    }

    return NULL;
}

AA * lireFichierAA(char *cheminFichier)
{
    FILE *fdat = fopen(cheminFichier,"r");
    char codeUE[6],codeAA[5],intitule[50];
    int ponderation;
    AA *debutListeAA;
    debutListeAA=malloc(sizeof(AA));

    fscanf(fdat, "%s %s %s %d",debutListeAA->codeUE,debutListeAA->codeAA,debutListeAA->intitule,&debutListeAA->ponderation);

    debutListeAA->suivant = NULL;

    while(!feof(fdat))
    {
        fscanf(fdat,"%s %s %s %d",codeUE,codeAA,intitule,&ponderation);
        debutListeAA = insererAA(debutListeAA,codeUE,codeAA,intitule,ponderation);
    }

    fclose(fdat);
    return debutListeAA;
}
AA *ajouterAA(char*fichierAA,AA *listeAA, char idUE[],char idAA[], char nom[], int ponderation)
{
    FILE *fdat = fopen(fichierAA, "a");
    if(rechercheAA(listeAA, idAA) != NULL){
        printf("L'AA existe déja\n");
        return listeAA;
    }

    fprintf(fdat, "\n%s %s %s %d", idUE,idAA, nom, ponderation);
    fclose(fdat);
    return insererAA(listeAA, idUE,idAA, nom, ponderation);

}

void reecrireFichierAA(char * cheminFichier , AA*listeAA )
{
    FILE *fdat = fopen(cheminFichier,"w");
    AA *parcoursAA = listeAA;

    while (parcoursAA != NULL)
    {
        fprintf(fdat, "%s %s %s %d", parcoursAA->codeUE, parcoursAA->codeAA,parcoursAA->intitule, parcoursAA->ponderation);

        if(parcoursAA->suivant != NULL){
            fprintf(fdat,"\n");
        }
        parcoursAA = parcoursAA->suivant;
    }

    fclose(fdat);
}

AA* supprimerAA(char *fichierDat, AA *listeAA , char codeAA[] )
{

    if(rechercheAA(listeAA, codeAA) == NULL)
    {
        printf("l'AA n'existe pas impossible a supprimer");
        return listeAA;
    }
    else{
        AA *parcoursAA = listeAA;
        AA *aaPrecedent = NULL;

        while (parcoursAA != NULL)
        {
            if(strcmp(parcoursAA->codeAA, codeAA) == 0)
            {
                if (aaPrecedent != NULL)
                {
                    aaPrecedent->suivant = parcoursAA->suivant;
                    free(parcoursAA);
                    reecrireFichierAA(fichierDat, listeAA);
                    return listeAA;
                }
                else
                {
                    aaPrecedent = listeAA;
                    listeAA = listeAA->suivant;
                    free(aaPrecedent);
                    reecrireFichierAA(fichierDat, listeAA);
                    return listeAA;
                }
            }

            aaPrecedent = parcoursAA;
            parcoursAA = parcoursAA->suivant;
        }
    }

    return listeAA;
}
AA * modifierAA(char *fichierDat, AA *listeAA ,char codeAA[],char idUE[], char intitule[],int ponderation)
{
    if(rechercheAA(listeAA, codeAA) == NULL)
    {
        printf("l'AA n'existe pas impossible a modifier");
        return listeAA;
    }
    else {
        AA *parcoursAA = listeAA;

        while (parcoursAA != NULL) {
            if (strcmp(parcoursAA->codeAA, codeAA) == 0) {

                strcpy(parcoursAA->intitule, intitule);
                strcpy(parcoursAA->codeUE, idUE);
                parcoursAA->ponderation = ponderation;
                reecrireFichierAA(fichierDat, listeAA);
                return listeAA;
            }

            parcoursAA = parcoursAA->suivant;
        }
    }

    return listeAA;

}

unsigned long plusLongIntituleAA(AA* listeAA)
{
    AA* parcours = listeAA;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->intitule);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}

void afficherAA(AA* listeAA)
{
    AA* parcoursAA = listeAA;

    unsigned long tailleIntitule = plusLongIntituleAA(listeAA);
    if(tailleIntitule < 8) tailleIntitule = 8;

    printf("+---------+---------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+-------------+\n");

    printf("| Code UE | Code AA | Intitule");
    for(int i = 0; i < tailleIntitule-8; i++)
    {
        printf(" ");
    }
    printf(" | Ponderation |\n");

    printf("+---------+---------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+-------------+\n");

    while(parcoursAA != NULL)
    {
        printf("|  %-5s  |  %-5s  | %-s", parcoursAA->codeUE,parcoursAA->codeAA,parcoursAA->intitule);
        for(int i = 0; i < tailleIntitule-(strlen(parcoursAA->intitule)-1 ); i++)
        {
            printf(" ");
        }
        printf("| %11d |\n", parcoursAA->ponderation);
        parcoursAA = parcoursAA->suivant;
    }

    printf("+---------+---------+-");
    for(int i = 0; i < tailleIntitule; i++)
    {
        printf("-");
    }
    printf("-+-------------+\n");
}

#endif //PROJET_C_2020_GESTIONAA_H
