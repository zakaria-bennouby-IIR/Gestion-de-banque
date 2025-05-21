#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Virement {
    float montant;
    char compteSource[50];
    char compteBeneficiaire[50];
    char date[50];
    struct Virement* suivant;
} Virement;


Virement* creerVirement(float montant, char* compteSource, char* compteBeneficiaire, char* date) {
    Virement* nvVirement = (Virement*)malloc(sizeof(Virement));
    if (nvVirement == NULL) {
        printf("Erreur\n");
        exit(1);
    }
    nvVirement->montant = montant;
    strcpy(nvVirement->compteSource, compteSource);
    strcpy(nvVirement->compteBeneficiaire, compteBeneficiaire);
    strcpy(nvVirement->date, date);
    nvVirement->suivant = NULL;
    return nvVirement;
}


void ajouterVirement(Virement** tete, float montant, char* compteSource, char* compteBeneficiaire, char* date) {
    Virement* nvVirement = creerVirement(montant, compteSource, compteBeneficiaire, date);
    nvVirement->suivant = *tete;
    *tete = nvVirement;
    printf("Virement ajouter\n");
}


void supprimerVirement(Virement** tete, char* compteSource, char* compteBeneficiaire, char* date) {
    Virement* p = *tete;
    Virement* precedent = NULL;

    while (p != NULL && (strcmp(p->compteSource, compteSource) != 0 || strcmp(p->compteBeneficiaire, compteBeneficiaire) != 0 || strcmp(p->date, date) != 0)) {
        precedent = p;
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Virement non existant.\n");
        return;
    }

    if (precedent == NULL) {
        *tete = p->suivant;
    } else {
        precedent->suivant = p->suivant;
    }

    free(p);
    printf("Virement supprimer\n");
}


void modifierVirement(Virement* tete, char* compteSource, char* compteBeneficiaire, char* date, float nouveauMontant, char* nouveauCompteSource, char* nouveauCompteBeneficiaire, char* nouvelleDate) {
    Virement* p = tete;

    while (p != NULL && (strcmp(p->compteSource, compteSource) != 0 || strcmp(p->compteBeneficiaire, compteBeneficiaire) != 0 || strcmp(p->date, date) != 0)) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Virement non trouver.\n");
        return;
    }

    p->montant = nouveauMontant;
    strcpy(p->compteSource, nouveauCompteSource);
    strcpy(p->compteBeneficiaire, nouveauCompteBeneficiaire);
    strcpy(p->date, nouvelleDate);
    printf("Virement modifier.\n");
}


void afficherVirements(Virement* tete) {
    Virement* p = tete;

    if (p == NULL) {
        printf("Aucun virement a afficher.\n");
        return;
    }

    while (p != NULL) {
        printf("Montant: %.2f, Compte Source: %s/n, Compte Beneficiaire: %s/n, Date: %s\n", p->montant, p->compteSource, p->compteBeneficiaire, p->date);
        p = p->suivant;
    }
}


void rechercherVirement(Virement* tete, char* compteSource, char* compteBeneficiaire, char* date) {
    Virement* p = tete;

    while (p != NULL) {
        if (strcmp(p->compteSource, compteSource) == 0 && strcmp(p->compteBeneficiaire, compteBeneficiaire) == 0 && strcmp(p->date, date) == 0) {
            printf("Montant: %.2f, Compte Source: %s/n, Compte Beneficiaire: %s/n, Date: %s\n", p->montant, p->compteSource, p->compteBeneficiaire, p->date);
            return;
        }
        p = p->suivant;
    }

    printf("Virement non trouver.\n");
}


void effectuerVirements(Virement* tete) {
    Virement* p = tete;

    if (p == NULL) {
        printf("Aucun virement a ete effectuer\n");
        return;
    }

    while (p != NULL) {
        printf("Montant: %.2f/n, Compte Source: %s/n, Compte Beneficiaire: %s/n, Date: %s\n", p->montant, p->compteSource, p->compteBeneficiaire, p->date);
        p = p->suivant;
    }
}


int afficherMenu() {
    int choix;
    printf("\nMenu:\n");
    printf("1. Ajouter un virement\n");
    printf("2. Supprimer un virement\n");
    printf("3. Modifier un virement\n");
    printf("4. Afficher tous les virements\n");
    printf("5. Rechercher un virement\n");
    printf("6. Effectuer les virements\n");
    printf("7. Quitter\n");
    printf("Choisissez une option: ");
    scanf("%d", &choix);
    return choix;
}


void main() {
    Virement* listeVirements = NULL;
    int choix;
    float montant;
    char compteSource[50];
    char compteBeneficiaire[50];
    char date[50];
    float nouveauMontant;
    char nouveauCompteSource[50];
    char nouveauCompteBeneficiaire[50];
    char nouvelleDate[11];

    do {
        choix = afficherMenu();
        switch (choix) {
            case 1:
                printf("Montant: ");
                scanf("%f", &montant);
                printf("Compte Source: ");
                scanf("%s", compteSource);
                printf("Compte Beneficiaire: ");
                scanf("%s", compteBeneficiaire);
                printf("Date: ");
                scanf("%s", date);
                ajouterVirement(&listeVirements, montant, compteSource, compteBeneficiaire, date);
                break;
            case 2:
                printf("Supprimer un virement:\n");
                printf("Compte Source: ");
                scanf("%s", compteSource);
                printf("Compte Beneficiaire: ");
                scanf("%s", compteBeneficiaire);
                printf("Date: ");
                scanf("%s", date);
                supprimerVirement(&listeVirements, compteSource, compteBeneficiaire, date);
                break;
            case 3:
                printf("Modifier un virement:\n");
                printf("Compte Source: ");
                scanf("%s", compteSource);
                printf("Compte Beneficiaire: ");
                scanf("%s", compteBeneficiaire);
                printf("Date: ");
                scanf("%s", date);
                printf("Nouveau Montant: ");
                scanf("%f", &nouveauMontant);
                printf("Nouveau Compte Source: ");
                scanf("%s", nouveauCompteSource);
                printf("Nouveau Compte Beneficiaire: ");
                scanf("%s", nouveauCompteBeneficiaire);
                printf("Nouvelle Date (YYYY-MM-DD): ");
                scanf("%s", nouvelleDate);
                modifierVirement(listeVirements, compteSource, compteBeneficiaire, date, nouveauMontant, nouveauCompteSource, nouveauCompteBeneficiaire, nouvelleDate);
                break;
            case 4:
                printf("Liste des virements:\n");
                afficherVirements(listeVirements);
                break;
            case 5:
                printf("Rechercher un virement:\n");
                printf("Compte Source: ");
                scanf("%s", compteSource);
                printf("Compte Beneficiaire: ");
                scanf("%s", compteBeneficiaire);
                printf("Date: ");
                scanf("%s", date);
                rechercherVirement(listeVirements, compteSource, compteBeneficiaire, date);
                break;
            case 6:
                printf("Effectuer les virements:\n");
                effectuerVirements(listeVirements);
                break;
            case 7:
                printf("Quitter.\n");
                break;
            default:
                printf("Option invalide.\n");
                break;
        }
    } while (choix != 7);


    Virement* p = listeVirements;
    while (p != NULL) {
        Virement* temp = p;
        p = p->suivant;
        free(temp);
    }

}
