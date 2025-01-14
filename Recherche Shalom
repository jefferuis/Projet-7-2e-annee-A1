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
