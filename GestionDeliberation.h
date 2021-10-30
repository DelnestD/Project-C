//
// Created by Rabha on 09/12/2020.
//

#ifndef PROJET_C_2020_GESTIONDELIBERATION_H
#define PROJET_C_2020_GESTIONDELIBERATION_H
#include <string.h>
#include "Structures.h"
#include "GestionAA.h"
#include "GestionUE.h"
#include "GestionEtudiant.h"

float notePonderee(float note,int ponderation)
{
    return note*((float)ponderation/20.f);
}

int deliberationUE(UE *ue, Note*listeNote)
{
    Note *parcoursNote = listeNote;

    int nbEchec = 0;
    float sommeNote = 0;

    while(parcoursNote != NULL)
    {
        sommeNote += notePonderee(parcoursNote->note,parcoursNote->AA->ponderation);
        if(parcoursNote->note < 10)
        {
            nbEchec++;
        }

        parcoursNote = parcoursNote->suivant;
    }

    if(sommeNote >= ((float)ue->nbCredit/2.f) && nbEchec <= 1)
    {
        return ue->nbCredit;
    }

    return 0;

}

int deliberationEtudiant(UE*listeUE , Note*listeNote , Etudiant *etudiant)
{
    UE*parcoursUE = listeUE;
    Note* notesEtudiantUE;
    int totalPonderation = 0;
    while(parcoursUE != NULL)
    {
        notesEtudiantUE = recupNotesEtudiant(listeNote, etudiant->identifiant, parcoursUE->codeUE);
        totalPonderation+= deliberationUE(parcoursUE,notesEtudiantUE);
        parcoursUE = parcoursUE->suivant;
    }

    return totalPonderation;
}

void exporterDeliberations(UE*listeUE , Note*listeNote , Etudiant *listeEtudiant,char*fdatResultat)
{
    FILE*fdatRes = fopen(fdatResultat,"w");
    Etudiant* parcoursEtudiant = listeEtudiant;

    fprintf(fdatRes,"Résultats des Délibérations\n");
    fprintf(fdatRes,"===========================\n\n");

    int deliberation;
    while(parcoursEtudiant != NULL)
    {
        deliberation = deliberationEtudiant(listeUE,listeNote,parcoursEtudiant);
        fprintf(fdatRes,"Decision du jury pour l'etudiant %s %s : Validation de %d credits sur 60 credits\n", parcoursEtudiant->nom,parcoursEtudiant->prenom,deliberation/10);
        parcoursEtudiant = parcoursEtudiant->suivant;
    }
    fclose(fdatRes);

}

void afficherDeliberations(UE*listeUE , Note*listeNote , Etudiant *listeEtudiant)
{
    Etudiant* parcoursEtudiant = listeEtudiant;

    int deliberation;
    while(parcoursEtudiant != NULL)
    {
        deliberation = deliberationEtudiant(listeUE,listeNote,parcoursEtudiant);
        printf("Decision du jury pour l'etudiant %s %s : Validation de %d credits sur 60 credits\n", parcoursEtudiant->nom,parcoursEtudiant->prenom,deliberation/10);
        parcoursEtudiant = parcoursEtudiant->suivant;
    }

}


#endif //PROJET_C_2020_GESTIONDELIBERATION_H
