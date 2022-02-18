
# Refrigerateur-intelligent-en-C-
Le projet consiste un réfrigérateur intelligent. 
Vous devez écrire un programme C++ n pour la gestion de l'inventaire des ingrédients d'un réfrigérateur
intelligent. Votre programme reçoit en entrée un flux de commandes. les six types de commande sont :

1. l'ajout d'un produit (nom du produit, nombre et date de péremption);
2. le retrait d'un produit (nom du produit et nombre);
3. la spécification d'une recette (une liste d'ingrédients);
4. la recommendation de recettes (liste des recettes possibles qui utilisent l'ingrédient dont la date de péremption
est la plus proche.);
5. l'utilisation des produits d'une recette.
6. l'affichage des produits disponibles.

Le programme doit traiter les commandes en continue, comme s'il était utilisé en temps réel.
Cela implique que les commandes doivent être traitéesséquentiellement dans leur ordre d'apparition dans l'entrée.
Une fois une commande lue, il faut la traiter immédiatement afin d'afficher son résultat.
Il nefaut surtout pas lire toutes les commandes en premier et ensuite effectuer les traitements.
Pour faciliter leparsingau moyen destd::cin>>, il y a au moins un espace blanc (espace, tabulation ou retour de ligne) après chaque chaîne de caractèreou nombre.
