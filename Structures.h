//
// Created by Rabha on 01/12/2020.
//
#ifndef PROJET_C_2020_STRUCTURES_H
#define PROJET_C_2020_STRUCTURES_H

typedef struct AA
{
    char codeUE[6];
    char codeAA[5];
    char intitule[50];
    int ponderation;
    struct AA*suivant;
}AA;

typedef struct UE
{
    char codeUE[6];
    char intitule[50];
    int nbCredit;
    struct UE *suivant;
}UE;


typedef struct Etudiant
{
    char nom[50];
    char prenom[50];
    char identifiant[10];
    int age;
    char sexe;
    int annee;
    struct Etudiant *suivant;

}Etudiant;

typedef struct Note
{
    struct Etudiant *etudiant;
    struct UE *UE;
    struct AA* AA;
    float note;
    struct Note *suivant;


}Note;

#endif