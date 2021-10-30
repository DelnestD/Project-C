//
// Created by Rabha on 06/12/2020.
//

#ifndef PROJET_C_2020_GESTIONETUDIANT_H
#define PROJET_C_2020_GESTIONETUDIANT_H

#include <stdlib.h>
#include "Structures.h"

Etudiant * inserer (Etudiant *listeEtudiant,char id[],char nom[], char prenom[],int age,char sexe,int annee)
{
    Etudiant *etudiantPrecedent = NULL;
    Etudiant *parcoursEtudiant = listeEtudiant;
    Etudiant *newEtudiant = NULL;

    while(parcoursEtudiant != NULL)
    {
        if(strcmp(parcoursEtudiant->identifiant,id)< 0)
        {
            etudiantPrecedent = parcoursEtudiant;
            parcoursEtudiant = parcoursEtudiant->suivant;
        }
        else{
            newEtudiant = malloc(sizeof(Etudiant));
            strcpy(newEtudiant->nom, nom);
            strcpy(newEtudiant->prenom,prenom);
            strcpy(newEtudiant->identifiant,id);
            newEtudiant->sexe =sexe;
            newEtudiant->annee = annee;
            newEtudiant->age = age;

            if(etudiantPrecedent != NULL)
            {
                etudiantPrecedent->suivant = newEtudiant;
            }
            else {
                listeEtudiant = newEtudiant;
            }
            newEtudiant->suivant = parcoursEtudiant;

            break;
        }
    }

    if(newEtudiant == NULL)
    {
        newEtudiant = malloc(sizeof(Etudiant));
        strcpy(newEtudiant->nom, nom);
        strcpy(newEtudiant->prenom,prenom);
        strcpy(newEtudiant->identifiant,id);
        newEtudiant->sexe =sexe;
        newEtudiant->annee = annee;
        newEtudiant->age = age;
        etudiantPrecedent->suivant = newEtudiant;
        newEtudiant->suivant = NULL;

    }

    return listeEtudiant;
}

Etudiant * lireFichierEtudiants(char *cheminFichier )
{
    FILE *fdatEtu = fopen(cheminFichier,"r");
    char nom[21],prenom[21],idEtudiant[9],sexe;
    int age,annee;
    Etudiant *debutListeEtudiant;
    debutListeEtudiant=malloc(sizeof(Etudiant));

    fscanf(fdatEtu, "%s %s %s %d %c %d",debutListeEtudiant->identifiant,debutListeEtudiant->nom,debutListeEtudiant->prenom,&debutListeEtudiant->age,&debutListeEtudiant->sexe,&debutListeEtudiant->annee);

    debutListeEtudiant->suivant = NULL;

    while(!feof(fdatEtu))
    {
        fscanf(fdatEtu,"%s %s %s %d %c %d",idEtudiant,nom,prenom,&age,&sexe,&annee);
        debutListeEtudiant = inserer(debutListeEtudiant,idEtudiant, nom,prenom,age,sexe,annee);
    }

    fclose(fdatEtu);
    return debutListeEtudiant;
}

Etudiant* rechercheEtudiant(Etudiant*listeEtudiant , char id[9])
{
    Etudiant *parcoursEtudiant = listeEtudiant;

    while (parcoursEtudiant != NULL)
    {
        if(strcmp(parcoursEtudiant->identifiant,id) == 0)
        {
            return parcoursEtudiant;
        }
        parcoursEtudiant = parcoursEtudiant->suivant;
    }

    return NULL;
}

Etudiant *ajouterEtudiant(char*fichierEtudiant,Etudiant *listeEtudiant,char id[],char nom[], char prenom[],int age,char sexe,int annee)
{
    FILE *fdat = fopen(fichierEtudiant,"a");
    if(rechercheEtudiant(listeEtudiant,id) != NULL){
        printf("Etudiant existe deja\n");
        return listeEtudiant;
    }

    fprintf(fdat,"\n%s %s %s %d %c %d",id,nom,prenom,age,sexe,annee);
    fclose(fdat);
    return inserer(listeEtudiant,id,nom,prenom,age,sexe,annee);
}



void reecrireFichierEtudiant(char * cheminFichier , Etudiant*listeEtudiant )
{
    FILE *fdat = fopen(cheminFichier,"w");
    Etudiant *parcoursEtudiant = listeEtudiant;

    while (parcoursEtudiant != NULL)
    {
        fprintf(fdat,"%s %s %s %d %c %d",parcoursEtudiant->identifiant,parcoursEtudiant->nom,parcoursEtudiant->prenom,parcoursEtudiant->age,parcoursEtudiant->sexe,parcoursEtudiant->annee);

        if(parcoursEtudiant->suivant != NULL){
            fprintf(fdat,"\n");
        }
        parcoursEtudiant = parcoursEtudiant->suivant;
    }

    fclose(fdat);
}

Etudiant* supprimerEtudiant(char *fichierDat,Etudiant *listeEtudiant ,char id[] )
{

    if(rechercheEtudiant(listeEtudiant,id) == NULL)
    {
        printf("l'etudiant n'existe pas impossible a supprimer");
        return listeEtudiant;
    }
    else{
        Etudiant *parcoursEtudiant = listeEtudiant;
        Etudiant *etudiantPrecedent = NULL;

        while (parcoursEtudiant !=NULL)
        {
            if(strcmp(parcoursEtudiant->identifiant,id)==0)
            {
                if (etudiantPrecedent != NULL)
                {
                    etudiantPrecedent->suivant = parcoursEtudiant->suivant;
                    free(parcoursEtudiant);
                    reecrireFichierEtudiant(fichierDat,listeEtudiant);
                    return listeEtudiant;
                }
                else
                {
                    etudiantPrecedent = listeEtudiant;
                    listeEtudiant = listeEtudiant->suivant;
                    free(etudiantPrecedent);
                    reecrireFichierEtudiant(fichierDat,listeEtudiant);
                    return listeEtudiant;
                }
            }

            etudiantPrecedent = parcoursEtudiant;
            parcoursEtudiant = parcoursEtudiant->suivant;
        }
    }

    return listeEtudiant;
}

Etudiant* modifierEtudiant(char *fichierDat,Etudiant *listeEtudiant ,char id[],char nom[], char prenom[],int age,char sexe,int annee)
{
    if(rechercheEtudiant(listeEtudiant,id) == NULL)
    {
        printf("l'etudiant n'existe pas impossible a modifier");
        return listeEtudiant;
    }
    else {
        Etudiant *parcoursEtudiant = listeEtudiant;

        while (parcoursEtudiant != NULL) {
            if (strcmp(parcoursEtudiant->identifiant, id) == 0) {

                strcpy(parcoursEtudiant->nom, nom);
                strcpy(parcoursEtudiant->prenom, prenom);
                parcoursEtudiant->sexe = sexe;
                parcoursEtudiant->annee = annee;
                parcoursEtudiant->age = age;

                reecrireFichierEtudiant(fichierDat, listeEtudiant);
                return listeEtudiant;
            }

            parcoursEtudiant = parcoursEtudiant->suivant;
        }
    }

    return listeEtudiant;

}

Etudiant* etudiantsPourAnnee(Etudiant* listeEtudiants, int annee)
{
    Etudiant *parcoursEtudiant = listeEtudiants;

    Etudiant *newEtudiant=NULL;
    Etudiant *parcoursEtudiantAnnee=NULL;
    Etudiant *listeEtudiantAnnee=NULL;

    while(parcoursEtudiant != NULL)
    {
        if(annee == parcoursEtudiant->annee)
        {
            if(listeEtudiantAnnee == NULL) {
                newEtudiant = malloc(sizeof(Etudiant));
                parcoursEtudiantAnnee = newEtudiant;
                listeEtudiantAnnee = parcoursEtudiantAnnee;
            }
            else {
                newEtudiant = malloc(sizeof(Etudiant));
                parcoursEtudiantAnnee->suivant = newEtudiant;
                parcoursEtudiantAnnee = newEtudiant;
            }

            strcpy(newEtudiant->identifiant, parcoursEtudiant->identifiant);
            strcpy(newEtudiant->nom, parcoursEtudiant->nom);
            strcpy(newEtudiant->prenom, parcoursEtudiant->prenom);
            newEtudiant->sexe = parcoursEtudiant->sexe;
            newEtudiant->age = parcoursEtudiant->age;
            newEtudiant->annee = parcoursEtudiant->annee;
        }

        parcoursEtudiant = parcoursEtudiant->suivant;
    }

    return listeEtudiantAnnee;

}

unsigned long plusLongNomEtudiant(Etudiant* listeEtudiants)
{
    Etudiant* parcours = listeEtudiants;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->nom);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}

unsigned long plusLongPrenomEtudiant(Etudiant* listeEtudiants)
{
    Etudiant* parcours = listeEtudiants;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->prenom);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}

void afficherEtudiants(Etudiant* listeEtudiants)
{
    Etudiant * parcoursEtudiant = listeEtudiants;

    unsigned long tailleNom = plusLongNomEtudiant(listeEtudiants);
    unsigned long taillePrenom = plusLongPrenomEtudiant(listeEtudiants);

    if(tailleNom < 3) tailleNom = 3;
    if(taillePrenom < 6) taillePrenom = 6;


    printf("+----------+-");
    for(int i = 0; i < tailleNom; i++)
    {
        printf("-");
    }
    printf("-+-");
    for(int i = 0; i < taillePrenom; i++)
    {
        printf("-");
    }
    printf("-+-----+-------+-------+\n");

    printf("| Identif. | Nom");
    for(int i = 0; i < tailleNom-2; i++)
    {
        printf(" ");
    }
    printf("| Prenom");
    for(int i = 0; i < taillePrenom-5; i++)
    {
        printf(" ");
    }
    printf("| Age | Genre | Annee |\n");


    printf("+----------+-");
    for(int i = 0; i < tailleNom; i++)
    {
        printf("-");
    }
    printf("-+-");
    for(int i = 0; i < taillePrenom; i++)
    {
        printf("-");
    }
    printf("-+-----+-------+-------+\n");

    while(parcoursEtudiant != NULL)
    {
        printf("| %-8s | %-s", parcoursEtudiant->identifiant, parcoursEtudiant->nom);
        for(int i = 0; i < tailleNom-(strlen(parcoursEtudiant->nom)-1 ); i++)
        {
            printf(" ");
        }

        printf("| %-s", parcoursEtudiant->prenom);
        for(int i = 0; i < taillePrenom-(strlen(parcoursEtudiant->prenom)-1 ); i++)
        {
            printf(" ");
        }

        printf("| %3d |   %-c   | %5d |\n", parcoursEtudiant->age,parcoursEtudiant->sexe,parcoursEtudiant->annee);
        parcoursEtudiant = parcoursEtudiant->suivant;
    }


    printf("+----------+-");
    for(int i = 0; i < tailleNom; i++)
    {
        printf("-");
    }
    printf("-+-");
    for(int i = 0; i < taillePrenom; i++)
    {
        printf("-");
    }
    printf("-+-----+-------+-------+\n");

}

#endif //PROJET_C_2020_GESTIONETUDIANT_H
