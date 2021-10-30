//
// Created by Rabha on 07/12/2020.
//

#ifndef PROJET_C_2020_GESTIONNOTE_H
#define PROJET_C_2020_GESTIONNOTE_H

#include <string.h>
#include "Structures.h"
#include "GestionAA.h"
#include "GestionUE.h"
#include "GestionEtudiant.h"

Note * insererNote (Note *listeNote, Etudiant *etudiant, UE* ue, AA*aa, float note)
{
    Note *NotePrecedent = NULL;
    Note *parcoursNote = listeNote;
    Note *newNote = NULL;

    while(parcoursNote != NULL)
    {
        NotePrecedent = parcoursNote;
        parcoursNote = parcoursNote->suivant;
    }

    newNote = malloc(sizeof(Note));
    newNote->etudiant = etudiant;
    newNote->UE = ue;
    newNote->AA = aa;
    newNote->note = note;
    newNote->suivant = NULL;

    NotePrecedent->suivant = newNote;


    return listeNote;
}

Note * lireFichierNotes(char *cheminFichier,AA*listeAA,Etudiant*listeEtudiant ,UE*listeUE)
{
    FILE *fdat = fopen(cheminFichier,"r");
    char idEtu[11],codeAA[5];
    float note;
    Note *debutListeNote;
    debutListeNote=NULL;
    int ligne = 0;

    while(!feof(fdat))
    {
        fscanf(fdat, "%s %s %f", idEtu,codeAA,&note);
        ligne++;
        Etudiant *etuTmp = rechercheEtudiant(listeEtudiant,idEtu);
        if(etuTmp == NULL)
        {
            printf("ERR lecture note ligne %d : Etudiant inexistant.\n", ligne);
        }

        AA *aaTmp = rechercheAA(listeAA,codeAA);
        UE *ueTmp = NULL;

        if(aaTmp == NULL)
        {
            printf("ERR lecture note ligne %d : AA inexistante.\n", ligne);
        } else
        {
            ueTmp = rechercheUE(listeUE,aaTmp->codeUE);
            if(ueTmp ==NULL)
            {
                printf("ERR lecture note ligne %d : UE inexistante.\n", ligne);
            }
        }

        if(ueTmp != NULL && aaTmp !=NULL && etuTmp!=NULL)
        {
            if(debutListeNote == NULL) {
                debutListeNote = malloc(sizeof(Note));
                debutListeNote->etudiant = etuTmp;
                debutListeNote->AA = aaTmp;
                debutListeNote->UE = ueTmp;
                debutListeNote->note = note;
                debutListeNote->suivant = NULL;
            }
            else {
                debutListeNote = insererNote(debutListeNote,etuTmp, ueTmp, aaTmp, note);
            }
        }

    }
    fclose(fdat);

    return debutListeNote;
}

Note* recupNotesEtudiant(Note*listeNote,char id[9],char codeUE[6])
{
    Note *parcoursNote = listeNote;

    Note *newNoteEtudiant=NULL;
    Note *parcoursNoteEtudiant=NULL;
    Note *listeNoteEtudiant=NULL;

    while(parcoursNote != NULL)
    {
        if(strcmp(id,parcoursNote->etudiant->identifiant)== 0 && strcmp(codeUE,parcoursNote->UE->codeUE)==0)
        {
            if(listeNoteEtudiant == NULL) {
                newNoteEtudiant = malloc(sizeof(Note));
                parcoursNoteEtudiant = newNoteEtudiant;
                listeNoteEtudiant = parcoursNoteEtudiant;
            }
            else {
                newNoteEtudiant = malloc(sizeof(Note));
                parcoursNoteEtudiant->suivant = newNoteEtudiant;
                parcoursNoteEtudiant = newNoteEtudiant;
            }
            newNoteEtudiant->UE = parcoursNote->UE;
            newNoteEtudiant->etudiant = parcoursNote->etudiant;
            newNoteEtudiant->AA = parcoursNote->AA;
            newNoteEtudiant->note = parcoursNote->note;
        }

        parcoursNote = parcoursNote->suivant;
    }

    return listeNoteEtudiant;
}

Note* recupToutesNotesEtudiant(Note*listeNote,char id[9])
{
    Note *parcoursNote = listeNote;

    Note *newNoteEtudiant=NULL;
    Note *parcoursNoteEtudiant=NULL;
    Note *listeNoteEtudiant=NULL;

    while(parcoursNote != NULL)
    {
        if(strcmp(id,parcoursNote->etudiant->identifiant) == 0)
        {
            if(listeNoteEtudiant == NULL) {
                newNoteEtudiant = malloc(sizeof(Note));
                parcoursNoteEtudiant = newNoteEtudiant;
                listeNoteEtudiant = parcoursNoteEtudiant;
            }
            else {
                newNoteEtudiant = malloc(sizeof(Note));
                parcoursNoteEtudiant->suivant = newNoteEtudiant;
                parcoursNoteEtudiant = newNoteEtudiant;
            }
            newNoteEtudiant->UE = parcoursNote->UE;
            newNoteEtudiant->etudiant = parcoursNote->etudiant;
            newNoteEtudiant->AA = parcoursNote->AA;
            newNoteEtudiant->note = parcoursNote->note;
        }

        parcoursNote = parcoursNote->suivant;
    }

    return listeNoteEtudiant;
}


Note * rechercheNote(Note *listeNote , char idAA[5],char idEtud[10])
{
    Note *parcourNote = listeNote;

    while (parcourNote != NULL)
    {
        if((strcmp(parcourNote->AA->codeAA, idAA) == 0)&&(strcmp(parcourNote->etudiant->identifiant,idEtud) == 0))
        {
            return parcourNote;
        }
        parcourNote = parcourNote->suivant;
    }

    return NULL;
}

Note *ajouterNote(char*fichierNote,Note *listeNote, Etudiant *listeEtudiant, UE* listeUE, AA* listeAA, float note, char idAA[5], char idEtud[10])
{
    FILE *fdat = fopen(fichierNote, "a");

    if(rechercheNote(listeNote, idAA,idEtud) != NULL){
        printf("Il existe deja une note pour cette AA\n");
        return listeNote;
    }

    fprintf(fdat, "\n%s %s %4.1f",idEtud, idAA, note);
    fclose(fdat);

    AA* aa = rechercheAA(listeAA, idAA);
    UE* ue = rechercheUE(listeUE, aa->codeUE);
    Etudiant* etudiant = rechercheEtudiant(listeEtudiant, idEtud);
    return insererNote(listeNote,etudiant,ue,aa,note);

}
void reecrireFichierNote(char * cheminFichier , Note*listeNote )
{
    FILE *fdat = fopen(cheminFichier,"w");
    Note *parcoursNote = listeNote;

    while (parcoursNote != NULL)
    {
        fprintf(fdat, "%s %s %4.1f", parcoursNote->etudiant->identifiant, parcoursNote->AA->codeAA, parcoursNote->note);

        if(parcoursNote->suivant != NULL){
            fprintf(fdat,"\n");
        }
        parcoursNote = parcoursNote->suivant;
    }

    fclose(fdat);
}

Note* supprimerNote(char *fichierDat, Note *listeNote , char codeAA[], char id[] )
{

    if(rechercheNote(listeNote,codeAA,id) == NULL)
    {
        printf("la note n'existe pas impossible a supprimer");
        return listeNote;
    }
    else{
        Note *parcoursNote = listeNote;
        Note *notePrecedent = NULL;

        while (parcoursNote != NULL)
        {
            if((strcmp(parcoursNote->AA->codeAA, codeAA) == 0) && (strcmp(parcoursNote->etudiant->identifiant,id)==0))
            {
                if (notePrecedent != NULL)
                {
                    notePrecedent->suivant = parcoursNote->suivant;
                    free(parcoursNote);
                    reecrireFichierNote(fichierDat, listeNote);
                    return listeNote;
                }
                else
                {
                    notePrecedent = listeNote;
                    listeNote = listeNote->suivant;
                    free(notePrecedent);
                    reecrireFichierNote(fichierDat, listeNote);
                    return listeNote;
                }
            }

            notePrecedent = parcoursNote;
            parcoursNote = parcoursNote->suivant;
        }
    }

    return listeNote;
}


Note * modifierNote(char *fichierDat, Note *listeNote , char id[],char codeAA[], float note)
{
    if(rechercheNote(listeNote, codeAA,id) == NULL)
    {
        printf("la note n'existe pas impossible a modifier");
        return listeNote;
    }
    else {
        Note *parcoursNote = listeNote;

        while (parcoursNote != NULL) {
            if((strcmp(parcoursNote->AA->codeAA, codeAA) == 0) && (strcmp(parcoursNote->etudiant->identifiant,id)==0)){

                parcoursNote->note = note;
                reecrireFichierNote(fichierDat, listeNote);
                return listeNote;
            }

            parcoursNote = parcoursNote->suivant;
        }
    }

    return listeNote;

}

unsigned long plusLongNomEtudiantNote(Note* liste)
{
    Note* parcours = liste;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->etudiant->nom);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}

unsigned long plusLongPrenomEtudiantNote(Note* liste)
{
    Note* parcours = liste;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->etudiant->prenom);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}


unsigned long plusLongIntituleAANote(Note* liste)
{
    Note* parcours = liste;
    unsigned long retour = 0;

    while(parcours != NULL)
    {
        unsigned long taille = strlen(parcours->AA->intitule);
        if(taille > retour) retour = taille;
        parcours = parcours->suivant;
    }

    return retour;
}

void afficherNotes(Note* listeNotes)
{
    Note * parcoursNote = listeNotes;
    unsigned long tailleNom = plusLongNomEtudiantNote(listeNotes);
    unsigned long taillePrenom = plusLongPrenomEtudiantNote(listeNotes);
    unsigned long tailleIntitule = plusLongIntituleAANote(listeNotes);

    if(tailleNom < 3) tailleNom = 3;
    if(taillePrenom < 6) taillePrenom = 6;
    if(tailleIntitule < 2) tailleIntitule = 2;

    printf("+----------+-");
    for(int i = 0; i < tailleNom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < taillePrenom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < tailleIntitule; i ++) printf("-");
    printf("-+------+\n");

    printf("| Identif. | Nom");
    for(int i = 0; i < tailleNom-3; i ++) printf(" ");
    printf(" | Prenom");
    for(int i = 0; i < taillePrenom-6; i ++) printf(" ");
    printf(" | AA");
    for(int i = 0; i < tailleIntitule-2; i ++) printf(" ");
    printf(" | Note |\n");

    printf("+----------+-");
    for(int i = 0; i < tailleNom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < taillePrenom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < tailleIntitule; i ++) printf("-");
    printf("-+------+\n");

    while(parcoursNote != NULL)
    {
        printf("| %-8s ", parcoursNote->etudiant->identifiant);
        printf("| %-s",parcoursNote->etudiant->nom);
        for(int i = 0; i < tailleNom-(strlen(parcoursNote->etudiant->nom)-1); i ++) printf(" ");
        printf("| %-s",parcoursNote->etudiant->prenom);
        for(int i = 0; i < taillePrenom-(strlen(parcoursNote->etudiant->prenom)-1); i ++) printf(" ");
        printf("| %-s",parcoursNote->AA->intitule);
        for(int i = 0; i < tailleIntitule-(strlen(parcoursNote->AA->intitule)-1); i ++) printf(" ");
        printf("| %4.1f |\n",parcoursNote->note);
        parcoursNote = parcoursNote->suivant;
    }

    printf("+----------+-");
    for(int i = 0; i < tailleNom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < taillePrenom; i ++) printf("-");
    printf("-+-");
    for(int i = 0; i < tailleIntitule; i ++) printf("-");
    printf("-+------+\n");
}

#endif //PROJET_C_2020_GESTIONNOTE_H
