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
        exit(EXIT_FAILURE);//Arrete le code 
    }
    fwrite(&nombreDarticles, sizeof(int), 1, fichier);
    fwrite(inventaire, sizeof(Produit), nombreDarticles, fichier);
    fclose(fichier);
    printf("Inventaire sauvegardé avec succès !\n");
}
void chargerInventaire  (Produit **inventaire, int *nombreDarticles) {
    FILE *fichier = fopen("inventaire.bin", "rb");
    if (fichier == NULL) {
        printf("Aucun fichier d'inventaire trouvé. Initialisation de l'inventaire vide.\n");
        *nombreDarticles = 0;
        return;
    }
    fread(nombreDarticles, sizeof(int), 1, fichier);
    *inventaire = (Produit *)malloc(*nombreDarticles * sizeof(Produit));
    if (*inventaire == NULL) {
        perror("Erreur d'allocation de mémoire");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }
    free(*inventaire)
    fread(*inventaire, sizeof(Produit), *nombreDarticles, fichier);
    fclose(fichier);
    printf("Inventaire chargé avec succès !\n");
}
void afficherInventaire(Produit *inventaire, int nombreDarticles) {
    if (nombreDarticles == 0) {
        printf("L'inventaire est vide.\n");
        return;
    }
    printf("\nInventaire :\n");
    for (int i = 0; i < nombreDarticles; i++) {
        printf("Produit %d : %s, catégorie : %s, Quantité : %d, Prix : %.2f\n", i + 1, inventaire[i].nom, inventaire[i].categorie, inventaire[i].quantite, inventaire[i].prix);
    }
}
void ajouterProduit (Produit **inventaire, int *nombreDarticles) {
    if (*nombreDarticles >= MAX_PRODUITS) {
        printf("L'inventaire est plein, veuillez supprimer certains produits.\n");
        return;
    }
    Produit nouveauProduit;
    printf("Nom du produit : ");
    fgets(nouveauProduit.nom, sizeof(nouveauProduit.nom), stdin);
    nouveauProduit.nom[strcspn(nouveauProduit.nom, "\n")] = 0;//Suprime le passage à la ligne crée par fgets
    printf("Catégorie : ");
    fgets(nouveauProduit.categorie, sizeof(nouveauProduit.categorie), stdin);
    nouveauProduit.categorie[strcspn(nouveauProduit.categorie,"\n")] = 0;
    printf("Quantité : ");
    scanf("%d", &nouveauProduit.quantite);
    printf("Prix : ");
    scanf("%f", &nouveauProduit.prix);
    *inventaire = (Produit *)realloc(*inventaire, (*nombreDarticles + 1) * sizeof(Produit));
    if (*inventaire == NULL) {
        printf("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    (*inventaire)[*nombreDarticles] = nouveauProduit;
    (*nombreDarticles)++;
    printf("Produit ajouté avec succès !\n");
}
void suppression (Produit **inventaire, int *nombreDarticles) {    
    if (*nombreDarticles == 0) {
        printf("Inventaire vide. Il n'y a rien à supprimer.\n");
        return;
    }
    printf("Quel article voulez-vous supprimer ? (Entrez le nom du produit) :\n");
    char articleASupprimer[MAX_NOM];
    fgets(articleASupprimer, sizeof(articleASupprimer), stdin);
    articleASupprimer[strcspn(articleASupprimer, "\n")] = 0;// Suprime le passage à la ligne crée par fgets
    int produitTrouve = 0;
    for (int i = 0; i < *nombreDarticles; i++) {
        if (strcmp((*inventaire)[i].nom, articleASupprimer) == 0) {
            produitTrouve = 1;
            for (int j = i; j < *nombreDarticles - 1; j++) {
                (*inventaire)[j] = (*inventaire)[j + 1];
            }
            (*nombreDarticles)--;
            if (*nombreDarticles == 0) {
              free(*inventaire);
                *inventaire = NULL;
                 }else{*inventaire = (Produit *)realloc(*inventaire, (*nombreDarticles) * sizeof(Produit));}
            printf("Produit supprimé avec succès !\n");
            break;
        }
    }
    if (produitTrouve == 0) {
        printf("Produit non trouvé dans l'inventaire.\n");
    }
}
void modifierproduit(Produit**inventaire,int *nombreDarticles){
    int choix,indicateur = 0 ;
    float nouveauprix;
    char ProduitAmodifier[MAX_NOM],nouvellecategorie[MAX_NOM];
    printf("Quel produit voulez vous modifier? \n");
    fgets(ProduitAmodifier,sizeof(ProduitAmodifier),stdin);
    ProduitAmodifier[strcspn(ProduitAmodifier,"\n")]=0;
    for (int i=0;i< *nombreDarticles;i++){
        if(strcmp((*inventaire[i]).nom,ProduitAmodifier) == 0){
            printf("Que voulez vous modifier ?\n");
            printf("1-categorie\n");
            printf("2-prix\n");
            printf("Votre choix:");
            scanf("%d",&choix);
            getchar();
            switch (choix )
            {
            case 1:
                printf ("entrez la nouvelle categorie");
                fgets(nouvellecategorie,sizeof(nouvellecategorie),stdin);
                nouvellecategorie[strcspn(nouvellecategorie, "\n")]=0;
                strcpy((*inventaire)[i].categorie , nouvellecategorie);
                printf("Modification reussie");
                break;
            case 2:
                printf("Entrez le nouveau prix \n");
                scanf("%f",&nouveauprix);
                (*inventaire)[i].prix=nouveauprix;
                printf("Modification reussie");
                break;
            default:
            printf("choix invalide");
                break;
            }
        }else{indicateur++;}
    }
    if (indicateur==*nombreDarticles){printf("le produit que vous souhaitez modifier n'est pas dans l'inventaire.");}
}
void chercherProduit (Produit *inventaire, int nombreDarticles) {
    printf("nombre d'article %d\n", nombreDarticles);
    if (nombreDarticles == 0) {
        printf("L'inventaire est vide.\n");
        return;
    }
    char recherche[MAX_NOM];
    int choixrecherche=0,j=0;
    printf("Voulez-vous chercher un produit ?\n");
    printf("1. Par nom\n");
    printf("2. Par catégorie\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choixrecherche);
    getchar();
    switch (choixrecherche) {
        case 1:
            printf("Entrez le nom du produit recherché : ");
            fgets (recherche, sizeof(recherche), stdin);
            recherche[strcspn(recherche, "\n")]= '\0';
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
            fgets (recherche,sizeof(recherche),stdin);
            recherche[strcspn(recherche,"\n")]=0;
            produitTrouve = 0;
            for (int i = 0; i < nombreDarticles; i++) {
                if (strcmp(inventaire[i].categorie, recherche) == 0) {
                    printf("Produit trouvé : %s, Quantité : %d, Prix : %.2f\n",  inventaire[i].nom, inventaire[i].quantite, inventaire[i].prix);
                    produitTrouve = 1;
                }else {produitTrouve=2;j=j+1;}
            }
            if (j == nombreDarticles) {
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
    printf("nombreDarticles après chargement : %d\n\n", nombreDarticles); // Affichage pour vérifier la valeur de nombreDarticles

    int choix;
    do {
        printf("\nMenu :\n");
        printf("1. Afficher l'inventaire\n");
        printf("2. Ajouter un produit\n");
        printf("3. Supprimer un produit\n");
        printf("4. Chercher un produit\n");
        printf("5. Modifier un produit\n");
        printf("6. Sauvegarder et quitter\n");
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
                modifierproduit(&inventaire,&nombreDarticles);
                break;
            case 6:
                sauvegarderInventaire(inventaire, nombreDarticles);
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 6);
    free(inventaire);
    return 0;
}
