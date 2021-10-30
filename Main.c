#include <stdio.h>
#include <string.h>

#include "Structures.h"
#include "GestionEtudiant.h"
#include "GestionUE.h"
#include "GestionAA.h"
#include "GestionNote.h"
#include "GestionDeliberation.h"

Etudiant* listeEtudiants;
UE* listeUE;
AA* listeAA;
Note* listeNotes;

char fdatUE[100];
char fdatAA[100];
char fdatNote[100];
char fdatEtu[100];

int annee;

int main() {
    void menuGeneral();

    menuGeneral();
}

void menuGeneral(){
    char reponse[3];
    char sectionUtilise[3];

    void menuAvance();
    printf("!!! Vous pouvez revenir ici n'importe quand en tapant MG !!!\n");

    printf("+------------------------------+\n");
    printf("| AD | Assistant de Direction  |\n");
    printf("+------------------------------+\n");
    printf("| CT | Comptabilite            |\n");
    printf("+------------------------------+\n");
    printf("| IG | Informatique de Gestion |\n");
    printf("+------------------------------+\n");
    printf("| XX | Quitter le logiciel     |\n");
    printf("+------------------------------+\n");

    while(strcmp(sectionUtilise,"CT") != 0
          && strcmp(sectionUtilise,"IG") != 0
          && strcmp(sectionUtilise,"AD") != 0
          && strcmp(sectionUtilise,"XX") != 0
          && strcmp(sectionUtilise,"MG") != 0)
    {
        printf("Dans quelle section voulez-vous intervenir ?");
        scanf("%s",sectionUtilise);
    }

    if(strcmp(sectionUtilise,"MG")==0)
    {
        menuGeneral();
    }
    else if(strcmp(sectionUtilise,"XX")==0)
    {
        return;
    }
    else if (strcmp(sectionUtilise, "IG") == 0)
    {
        strcpy(fdatEtu,"SectionIG/ListeEtudiantIG.dat");
        strcpy(fdatAA,"SectionIG/ListeAAIG.dat");
        strcpy(fdatUE,"SectionIG/ListeUEIG.dat");
        strcpy(fdatNote,"SectionIG/NoteEtudiantIG.dat");
    }
    else if (strcmp(sectionUtilise, "CT") == 0)
    {
        strcpy(fdatEtu,"SectionCT/ListeEtudiantCT.dat");
        strcpy(fdatAA,"SectionCT/ListeAACT.dat");
        strcpy(fdatUE,"SectionCT/ListeUECT.dat");
        strcpy(fdatNote,"SectionCT/NoteEtudiantCT.dat");
    }
    else if (strcmp(sectionUtilise, "AD") == 0)
    {
        strcpy(fdatEtu,"SectionAD/ListeEtudiantAD.dat");
        strcpy(fdatAA,"SectionAD/ListeAAAD.dat");
        strcpy(fdatUE,"SectionAD/ListeUEAD.dat");
        strcpy(fdatNote,"SectionAD/NoteEtudiantAD.dat");
    }

    while(strcmp(reponse,"1") !=0
          && strcmp(reponse,"2") != 0
          && strcmp(reponse,"3") != 0
          && strcmp(reponse,"MG") != 0)
    {
        printf("En quelle annee voulez-vous intervenir (1/2/3)?");
        scanf("%s",reponse);
    }

    if(strcmp(reponse,"MG") == 0)
    {
        menuGeneral();
    }
    else if(strcmp(reponse,"1") == 0)
    {
        annee = 1;
    }
    else if(strcmp(reponse,"2") == 0)
    {
        annee = 2;
    }
    else if(strcmp(reponse,"3") == 0)
    {
        annee = 3;
    }

    listeEtudiants = lireFichierEtudiants(fdatEtu);
    listeUE = lireFichierUE(fdatUE);
    listeAA = lireFichierAA(fdatAA);
    listeNotes = lireFichierNotes(fdatNote, listeAA, listeEtudiants, listeUE);


    menuAvance();
}
void menuAvance(){
    void gestionUE();
    void gestionAA();
    void gestionEtudiants();
    void gestionNote();

    char data[3];

    printf("\n\n");
    printf("!!! Vous pouvez revenir ici n'importe quand en tapant MA !!!\n");

    printf("+------------------------------+\n");
    printf("| UE | Gerer les UE            |\n");
    printf("+------------------------------+\n");
    printf("| AA | Gerer les AA            |\n");
    printf("+------------------------------+\n");
    printf("| NO | Gerer les notes         |\n");
    printf("+------------------------------+\n");
    printf("| EL | Gerer les eleves        |\n");
    printf("+------------------------------+\n");
    printf("| AR | Afficher les Resultats  |\n");
    printf("+------------------------------+\n");
    printf("| EX | Exporter les Resultats  |\n");
    printf("+------------------------------+\n");
    printf("| XX | Quitter le logiciel     |\n");
    printf("+------------------------------+\n");

    while(strcmp(data,"UE")!=0
            &&strcmp(data,"AA")!=0
            &&strcmp(data,"XX")!=0
            &&strcmp(data,"EL")!=0
            &&strcmp(data,"AR")!=0
            &&strcmp(data,"MG")!=0
            && strcmp(data,"MA")!=0
            && strcmp(data,"EX")!=0
            && strcmp(data,"NO")!=0){
        printf("Que voulez-vous faire ?");
        scanf("%s",data);
    }

    if(strcmp(data,"MG")==0)
    {
        menuGeneral();
    }
    else if(strcmp(data,"MA")==0)
    {
        menuAvance();
    }
    else if(strcmp(data,"XX")==0)
    {
        return;
    }
    else if(strcmp(data,"UE")==0)
    {
        gestionUE();
    }
    else if(strcmp(data,"AA")==0)
    {
        gestionAA();
    }
    else if(strcmp(data,"EL")==0)
    {
        gestionEtudiants();
    }
    else if(strcmp(data,"NO")==0)
    {
        gestionNote();
    }
    else if(strcmp(data,"AR")==0){
        printf("\n\n");
        printf("Resultats des Deliberations\n");
        printf("===========================\n\n");
        afficherDeliberations(listeUE, listeNotes, listeEtudiants);
        menuAvance();
        return;
    }
    else if(strcmp(data,"EX")==0){
        char nomFichierREs[50];
        printf("Dans quelle fichier souhaitez vous exportez les resultats ?");
        scanf("%s",nomFichierREs);

        exporterDeliberations(listeUE, listeNotes, listeEtudiants,nomFichierREs);

        printf("Export termine");
        menuAvance();
        return;
    }
}

void gestionUE() {
    char type[3];
    printf("\n\n");


    printf("+------------------------------+\n");
    printf("| L | Afficher les UE          |\n");
    printf("+------------------------------+\n");
    printf("| A | Ajouter une UE           |\n");
    printf("+------------------------------+\n");
    printf("| M | Modifier une UE          |\n");
    printf("+------------------------------+\n");
    printf("| S | Supprimer une UE         |\n");
    printf("+------------------------------+\n");

    while (strcmp(type, "A") != 0 && strcmp(type, "M") != 0 && strcmp(type, "L") != 0 && strcmp(type, "S") != 0 && strcmp(type, "MG") != 0 &&
           strcmp(type, "MA") != 0) {
        printf("Que voulez-vous faire ?");
        scanf("%s", type);
    }

    if (strcmp(type, "MG") == 0)
    {
        menuGeneral();
        return;
    }
    else if (strcmp(type, "MA") == 0)
    {
        menuAvance();
        return;
    }
    else if (strcmp(type, "L") == 0)
    {
        afficherUE(listeUE);
        gestionUE();
        return;
    }
    else if (strcmp(type, "A") == 0)
    {
        char idUE[6];
        char nom[50];
        int ponderation;
        printf("Quel est son ID ?");
        scanf("%s", idUE);
        printf("Quel est son intitule ?");
        scanf("%s", nom);
        printf("Quel est sa ponderation ?");
        scanf("%d", &ponderation);
        listeUE = ajouterUE(fdatUE, listeUE, idUE, nom, ponderation);
        printf("Operation terminee\n");
        gestionUE();
        return;
    }
    else if (strcmp(type, "M") == 0)
    {
        char idUE[6];
        char nom[50];
        char choix[2];
        char validation[2];
        int ponderation;

        afficherUE(listeUE);
        printf("Quel est l'ID de l'UE a modifier?");
        scanf("%s", idUE);

        UE *UEaModif = rechercheUE(listeUE, idUE);
        if(UEaModif == NULL) {
            printf("Aucune UE ne correspond a cet ID\n");
            gestionUE();
            return;
        }

        printf("+------------------------------+\n");
        printf("| N | Modifier le Nom          |\n");
        printf("+------------------------------+\n");
        printf("| C | Modifier les credits     |\n");
        printf("+------------------------------+\n");

        do {
            printf("Que voulez vous modifier? ");
            scanf("%s", choix);
        } while (strcmp(choix,"N")!= 0 && strcmp(choix,"C")!= 0);

        if (strcmp(choix,"N")== 0)
        {
            printf("Quel est son intitule ?");
            scanf("%s", nom);
            ponderation = UEaModif->nbCredit;
            do {
                printf("Etes-vous sure de vouloir changer %-s en %-s?(O/N)", UEaModif->intitule, nom);
                scanf("%s", validation);
            } while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0 );
        }
        else
        {
            strcpy(nom, UEaModif->intitule);
            printf("Quel est son nombre de credits ?");
            scanf("%d", &ponderation);
            do {
                printf("Etes-vous sure de vouloir changer %d en %d?(O/N)", UEaModif->nbCredit, ponderation);
                scanf("%s", validation);
            } while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0 );
        }



        if (strcmp(validation,"O") == 0) {
            listeUE = modifierUE(fdatUE, listeUE, idUE, nom, ponderation);
            printf("Modification effectuee\n");
        }

        gestionUE();
        return;
    }
    else if (strcmp(type, "S") == 0)
    {
        char validation[2];
        char codeUE[6];

        afficherUE(listeUE);

        printf("Quel est l'ID de l'UE a supprimer ?");
        scanf("%s",codeUE);

        UE *UEaModif = rechercheUE(listeUE, codeUE);

        do {
            printf("Etes-vous sure de vouloir supprimer %-s? (O/N)",UEaModif->intitule);
            scanf("%s",validation);
        } while(strcmp(validation,"O") != 0 && strcmp(validation,"N") !=0);

        if(strcmp(validation,"O") == 0){
            listeUE = supprimerUE(fdatUE, listeUE,codeUE);
            printf("UE supprimee\n");
        }

        gestionUE();
        return;
    }
}

void gestionAA()
{
    char type[3];
    printf("\n\n");

    printf("+------------------------------+\n");
    printf("| L | Afficher les AA          |\n");
    printf("+------------------------------+\n");
    printf("| A | Ajouter une AA           |\n");
    printf("+------------------------------+\n");
    printf("| M | Modifier une AA          |\n");
    printf("+------------------------------+\n");
    printf("| S | Supprimer une AA         |\n");
    printf("+------------------------------+\n");

    while (strcmp(type, "A") != 0 && strcmp(type, "M") != 0 && strcmp(type, "L") != 0 && strcmp(type, "S") != 0 && strcmp(type, "MG") != 0 &&
           strcmp(type, "MA") != 0) {
        printf("Que voulez-vous faire ?");
        scanf("%s", type);
    }

    if (strcmp(type, "MG") == 0)
    {
        menuGeneral();
        return;
    }
    else if (strcmp(type, "MA") == 0)
    {
        menuAvance();
        return;
    }
    else if (strcmp(type, "L") == 0)
    {
        afficherAA(listeAA);
        gestionAA();
        return;
    }
    else if (strcmp(type, "A") == 0)
    {
        char idUE[6],idAA[5],nom[50];
        int ponderation;
        printf("Quel est l'ID de son UE ?");
        scanf("%s",idUE);
        printf("Quel est son ID ?");
        scanf("%s",idAA);
        printf("Quel est son intitule ?");
        scanf("%s",nom);
        printf("Quel est sa ponderation ?");
        scanf("%d",&ponderation);

        listeAA = ajouterAA(fdatAA,listeAA,idUE,idAA,nom,ponderation);
        gestionAA();
        return;
    }
    else if(strcmp(type,"M")==0)
    {
        char codeAA[5], idUE[6], intitule[50], choix[3], validation[2];
        int ponderation;

        afficherAA(listeAA);
        printf("Quel est l'ID de la AA a modifier'?");
        scanf("%s", codeAA);

        AA *AAaModif = rechercheAA(listeAA, codeAA);

        if(AAaModif == NULL)
        {
            printf("Aucune AA ne correspond à cet ID\n");
            gestionAA();
            return;
        }

        printf("\n\n");
        printf("+-----------------------------------------------+\n");
        printf("| UE | Modifier l'UE à laquelle l'AA appartient |\n");
        printf("+-----------------------------------------------+\n");
        printf("|  N | Modifier le Nom                          |\n");
        printf("+-----------------------------------------------+\n");
        printf("|  C | Modifier le Pourcentage dans l'UE        |\n");
        printf("+-----------------------------------------------+\n");
        while (strcmp(choix, "UE") != 0 && strcmp(choix, "N") != 0 && strcmp(choix, "C") != 0) {
            printf("Que voulez vous modifiez ?");
            scanf("%s", choix);
        }
        if (strcmp(choix, "UE") == 0) {
            printf("Quel est l'ID de son UE ?");
            scanf("%s", idUE);
            strcpy(intitule, AAaModif->intitule);
            ponderation = AAaModif->ponderation;
            do{
                printf("Etes-vous sure de vouloir changer %-s en %-s?(O/N)", AAaModif->codeUE, idUE);
                scanf("%s", validation);
            }while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);
        } else if (strcmp(choix, "N") == 0) {
            printf("Quel est son intitule ?");
            scanf("%s", intitule);
            strcpy(idUE, AAaModif->codeUE);
            ponderation = AAaModif->ponderation;

            do{
                printf("Etes-vous sure de vouloir changer %-s en %-s?(O/N)", AAaModif->intitule, intitule);
                scanf("%s", validation);
            }while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);
        } else {
            printf("Quel est sa ponderation ?");
            scanf("%d", &ponderation);
            strcpy(idUE, AAaModif->codeUE);
            strcpy(intitule, AAaModif->intitule);

            do{
                printf("Etes-vous sure de vouloir changer %d en %d?(O/N)", AAaModif->ponderation, ponderation);
                scanf("%s", validation);
            }while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);
        }

        if (strcmp(validation,"O") ==0) {
            listeAA = modifierAA(fdatAA, listeAA, codeAA, idUE, intitule, ponderation);
        }
        gestionAA();
        return;
    }
    else if (strcmp(type, "S") == 0)
    {
        char codeAA[5];
        char validation[2];

        afficherAA(listeAA);
        printf("Quel est l'ID de la AA a supprimer ?");
        scanf("%s",codeAA);
        AA *AAaModif = rechercheAA(listeAA,codeAA);
        do{
            printf("Etes-vous sure de vouloir supprimer %-s?(O/N)",AAaModif->intitule);
            scanf("%s",validation);
        }while(strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);

        if(strcmp(validation,"O") ==0){
            listeAA = supprimerAA(fdatAA, listeAA ,codeAA);
        }
        gestionAA();
        return;

    }

}

void gestionEtudiants()
{
    char type[3];
    printf("\n\n");
    printf("+------------------------------+\n");
    printf("| L | Afficher les etudiant    |\n");
    printf("+------------------------------+\n");
    printf("| A | Ajouter un etudiant      |\n");
    printf("+------------------------------+\n");
    printf("| M | Modifier un etudiant     |\n");
    printf("+------------------------------+\n");
    printf("| S | Supprimer un etudiant    |\n");
    printf("+------------------------------+\n");

    while (strcmp(type, "A") != 0 && strcmp(type, "M") != 0 && strcmp(type, "L") != 0 && strcmp(type, "S") != 0 && strcmp(type, "MG") != 0 &&
           strcmp(type, "MA") != 0) {
        printf("Que voulez-vous faire ?");
        scanf("%s", type);
    }
    if (strcmp(type, "MG") == 0)
    {
        menuGeneral();
        return;
    }
    else if (strcmp(type, "MA") == 0)
    {
        menuAvance();
        return;
    }
    else if (strcmp(type, "L") == 0)
    {
        afficherEtudiants(etudiantsPourAnnee(listeEtudiants, annee));
        gestionEtudiants();
        return;
    }
    else if (strcmp(type, "A") == 0)
    {
        char id[10],nom[50],prenom[50],sexe[2];
        int age;
        printf("Quel est son matricule ?");
        scanf("%s",id);
        printf("Quel est son nom ?");
        scanf("%s",nom);
        printf("Quel est son prenom ?");
        scanf("%s",prenom);
        printf("Quel est son age ?");
        scanf("%d",&age);
        printf("Quel est son genre ?");
        scanf("%s",sexe);

        listeEtudiants = ajouterEtudiant(fdatEtu,listeEtudiants,id,nom,prenom,age, sexe[0], annee);
        gestionEtudiants();
        return;
    }
    else if (strcmp(type, "M") == 0)
    {
        char id[10],nom[50],prenom[50], sexe=' ',choix[3], validation[2];
        int age;

        afficherEtudiants(listeEtudiants);
        printf("Quel est son matricule ?");
        scanf("%s",id);

        printf("\n\n");

        printf("+---------------------------------+\n");
        printf("|  N | Modifier le Nom            |\n");
        printf("+---------------------------------+\n");
        printf("|  P | Modifier le Prenom         |\n");
        printf("+---------------------------------+\n");
        printf("|  G | Modifier le Genre          |\n");
        printf("+---------------------------------+\n");


        do {
            printf("Que voulez-vous modifier?");
            scanf("%s",choix);
        } while(strcmp(choix,"AA")!=0&&strcmp(choix,"N")!=0&&strcmp(choix,"P")!=0&&strcmp(choix,"G")!=0);

        Etudiant *EtudiantAModif = rechercheEtudiant(listeEtudiants,id);
        age = EtudiantAModif->age;

        if(strcmp(choix,"AA")==0) afficherAA(listeAA);

        if(strcmp(choix,"N")==0){
            printf("Quel est le nom de l'eleve ?");
            scanf("%s",nom);
            strcpy(prenom,EtudiantAModif->prenom);
            sexe=EtudiantAModif->sexe;

            do{
                printf("Etes-vous sure de vouloir changer %-s en %-s?(O/N)",EtudiantAModif->nom,nom);
                scanf("%s",validation);
            }while(strcmp(validation,"O")!= 0 && strcmp(validation,"N") != 0);
        }else if(strcmp(choix,"P")==0){
            printf("Quel est le prenom de l'eleve ?");
            scanf("%s",prenom);
            strcpy(nom,EtudiantAModif->nom);
            sexe=EtudiantAModif->sexe;

            do{
                printf("Etes-vous sure de vouloir changer %-s en %-s?(O/N)",EtudiantAModif->prenom,prenom);
                scanf("%s",validation);
            }while(strcmp(validation,"O")!= 0 && strcmp(validation,"N") != 0);
        }else if(strcmp(choix,"G")==0){
            printf("Quel est le genre de l'eleve ?");
            scanf("%c",&sexe);
            strcpy(prenom,EtudiantAModif->prenom);
            strcpy(nom,EtudiantAModif->nom);

            do{
                printf("Etes-vous sure de vouloir changer %c en %c?(O/N)",EtudiantAModif->sexe,sexe);
                scanf("%s",validation);
            }while(strcmp(validation,"O")!= 0 && strcmp(validation,"N") != 0);
        }

        if(strcmp(validation,"O") ==0)
        {
            listeEtudiants = modifierEtudiant(fdatEtu,listeEtudiants,id,nom,prenom,age,sexe,annee);
        }

        gestionEtudiants();
        return;
    }
    else if (strcmp(type, "S") == 0)
    {
        char id[10],validation[2];

            afficherEtudiants(listeEtudiants);
            printf("Quel est le matricule de l'eleve a supprimer ?");
            scanf("%s",id);
            Etudiant *EtudiantAModif = rechercheEtudiant(listeEtudiants,id);

            do
            {
                printf("Etes-vous sure de vouloir supprimer %-s %-s? (O/N)",EtudiantAModif->nom,EtudiantAModif->prenom);
                scanf("%s",validation);
            }while(strcmp(validation,"O")!= 0 && strcmp(validation,"N") != 0);

            if(strcmp(validation,"O")==0){
                listeEtudiants = supprimerEtudiant(fdatEtu,listeEtudiants ,id);
            }

        gestionEtudiants();
        return;

    }

}
void gestionNote()
{
    char type[3],validation[2];
    char idEtu[10],idAA[5],idUE[5];
    float note;
    printf("\n\n");
    printf("+-----------------------------------+\n");
    printf("| L | Afficher toutes les notes     |\n");
    printf("+-----------------------------------+\n");
    printf("| E | Afficher les notes d'un eleve |\n");
    printf("+-----------------------------------+\n");
    printf("| A | Ajouter une note              |\n");
    printf("+-----------------------------------+\n");
    printf("| M | Modifier une note             |\n");
    printf("+-----------------------------------+\n");
    printf("| S | Supprimer une note            |\n");
    printf("+-----------------------------------+\n");

    while (strcmp(type, "A") != 0 && strcmp(type, "M") != 0 && strcmp(type, "L") != 0 && strcmp(type, "E") != 0 &&strcmp(type, "S") != 0 && strcmp(type, "MG") != 0 &&
           strcmp(type, "MA") != 0) {
        printf("Que voulez-vous faire ?");
        scanf("%s", type);
    }

    if (strcmp(type, "MG") == 0)
    {
        menuGeneral();
        return;
    }
    else if (strcmp(type, "MA") == 0)
    {
        menuAvance();
        return;
    }
    else if (strcmp(type, "L") == 0)
    {
        afficherNotes(listeNotes);
        gestionNote();
        return;
    }
    else if (strcmp(type, "E") == 0)
    {
        char id[10];
        printf("Quelle est l'identifiant de l'eleve ?");
        scanf("%s",id);
        Note*noteEtudiant = recupToutesNotesEtudiant(listeNotes,id);

        afficherNotes(noteEtudiant);
        gestionNote();
        return;
    }
    else if (strcmp(type, "A") == 0)
    {


        printf("Quel est l'id de l'etudiant ?");
        scanf("%s",idEtu);
        printf("Quel est son code UE ?");
        scanf("%s",idUE);
        printf("Quel est son code AA ?");
        scanf("%s",idAA);
        printf("Quel est la note ?");
        scanf("%f",&note);

        listeNotes= ajouterNote(fdatNote,listeNotes,listeEtudiants,listeUE,listeAA,note,idAA,idEtu);
        gestionNote();
        return;
    }
    else if (strcmp(type, "M") == 0) {
        printf("Quel est l'ID de la AA ou il faut modifier la note ?");
        scanf("%s", idAA);
        printf("Quel est l'id de l'etudiant ?");
        scanf("%s", idEtu);
        Note *NoteAModif = rechercheNote(listeNotes, idAA, idEtu);
        printf("Quel est la note a attribuer ?");
        scanf("%f", &note);

        do {
            printf("Etes-vous sure de vouloir changer %4.1f en %4.1f? (O/N)", NoteAModif->note, note);
            scanf("%s", validation);
        } while (strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);

        if (strcmp(validation,"O") ==0) {
            listeNotes = modifierNote(fdatNote, listeNotes, idEtu, idAA, note);

        }
        gestionNote();
        return;
    }
    else if (strcmp(type, "S") == 0)
    {
        afficherNotes(listeNotes);
        printf("Quel est le matricule de l'eleve de la note a supprimer ?");
        scanf("%s",idEtu);
        printf("Quel est le code AA  de la note a supprimer ?");
        scanf("%s",idAA);
        Note*noteAsupprimer  = rechercheNote(listeNotes,idAA,idEtu);

        do
        {
            printf("Etes-vous sure de vouloir supprimer %s %s %4.1f ?(O/N)",noteAsupprimer->etudiant->identifiant,noteAsupprimer->AA->codeAA, noteAsupprimer->note);
            scanf("%s",validation);
        }while(strcmp(validation,"O") != 0 && strcmp(validation,"N") != 0);

        if(strcmp(validation,"O") ==0){
            listeNotes = supprimerNote(fdatNote,listeNotes ,idAA,idEtu);
        }

        gestionNote();
        return;

    }


}

