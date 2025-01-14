#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOM 50
#define MAX_PRODUITS 100

typedef struct {
    char nom[MAX_NOM];
    char categorie[MAX_NOM];
    int quantite;
    float prix;
} Produit;
void sauvegarderInventaire(Produit *inventaire, int nombreDarticles) {
    FILE *fichier = fopen("inventaire.bin", "wb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour la sauvegarde");
        exit(EXIT_FAILURE);
    }
    fwrite(&nombreDarticles, sizeof(int), 1, fichier);
    fwrite(inventaire, sizeof(Produit), nombreDarticles, fichier);
    fclose(fichier);
    printf("Inventaire sauvegardé avec succès !\n");
}
void chercherProduit /*(shalom)*/(Produit *inventaire, int nombreDarticles) {
    printf("nombre d'article %d\n", nombreDarticles);
    if (nombreDarticles == 0) {
        printf("L'inventaire est vide.\n");
        return;
    }
    char recherche[MAX_NOM];
    int choixrecherche,j;
    printf("Voulez-vous chercher un produit ?\n");
    printf("1. Par nom\n");
    printf("2. Par catégorie\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choixrecherche);

    switch (choixrecherche) {
        case 1:
            printf("Entrez le nom du produit recherché : ");
            scanf("%s", recherche);
            int produitTrouve = 0;
            for (int i = 0; i < nombreDarticles; i++) {
                if (strcmp(inventaire[i].nom, recherche) == 0) {
                    printf("Voici les imformations concernant ce produit :\ncategorie : %s, Quantité : %d, Prix : %.2f\n", inventaire[i].categorie, inventaire[i].quantite, inventaire[i].prix);
                        produitTrouve = 1;
                    break;
                }
            }
            if (produitTrouve == 0) {
                       printf("Produit non trouvé dans l'inventaire.\n");
            }
            break;
        case 2:
            printf("Entrez la catégorie du produit recherché : ");
            scanf("%s", recherche);
            produitTrouve = 0;
            for (int i = 0; i < nombreDarticles; i++) {
                if (strcmp(inventaire[i].categorie, recherche) == 0) {
                    printf("Produit trouvé : %s, Quantité : %d, Prix : %.2f\n",  inventaire[i].nom, inventaire[i].quantite, inventaire[i].prix);
                    produitTrouve = 1;
                }else {produitTrouve=2;j=j++;}
            }
            if (j == nombreDarticles-1) {
                printf("Cette catégorie n'existe pas ou est vide.\n");
            }
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }
}
int main() {
    Produit *inventaire = NULL;
    int nombreDarticles = 0;

    chargerInventaire(&inventaire, &nombreDarticles);
    printf("nombreDarticles après chargement : %d\n", nombreDarticles); // Affichage pour vérifier la valeur de nombreDarticles

    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Afficher l'inventaire\n");
        printf("2. Ajouter un produit\n");
        printf("3. Supprimer un produit\n");
        printf("4. Chercher un produit\n");
        printf("5. Sauvegarder et quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Consomme le saut de ligne laissé par scanf

        switch (choix) {
            case 1:
                afficherInventaire(inventaire, nombreDarticles);
                break;
            case 2:
                ajouterProduit(&inventaire, &nombreDarticles);
                break;
            case 3:
                suppression(&inventaire, &nombreDarticles);
                break;
            case 4:
                chercherProduit(inventaire, nombreDarticles);
                break;
            case 5:
                sauvegarderInventaire(inventaire, nombreDarticles);
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 5);

    free(inventaire);
    return 0;
}
