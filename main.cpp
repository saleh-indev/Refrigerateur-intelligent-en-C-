/*
  Squelette de départ. Vous pouvez modifier ce fichier à votre guise.
*/

#include <fstream>
#include "stock.h"


int main(int argc, const char** argv) {
    std::istream* entree;
    std::ifstream* entree_fichier = NULL;

    if(argc>1){
         entree = entree_fichier = new std::ifstream(argv[1]);
         if(entree->fail())
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
    } else {
         entree = &std::cin;
    }
    std::vector<Produit> p(0);
    Stock stock(p);
    std::map<std::string, Recette> recettes;
    std::string commande;
    while(*entree){
        *entree >> commande;
        if(!(*entree)) break;
        if(commande=="recette"){
            std::string nomrecette;
            *entree >> nomrecette;
            Recette recette(nomrecette);
            *entree >> recette;
            recettes[nomrecette] = recette;
        } else if(commande=="ajout") {
            std::string nomingredient;
            *entree >> nomingredient;
            int nombre = 0;
            *entree >> nombre;
            if( nombre <= 0) {
                std::cerr << "Erreur sur le nombre d'ingredient." << std::endl;
                return -1;
            }
            std::string date;
            *entree >> date;
            stock.ajout(nomingredient, date, nombre);
        } else if(commande=="retrait") {
            if(stock.produits.empty()) continue;
            std::string nomingredient;
            *entree >> nomingredient;
            std::cerr << "retrait " << nomingredient << std::endl;
            int nombre = 0;
            *entree >> nombre;
            if( nombre <= 0) {
                std::cerr << "Erreur sur le nombre d'ingredient." << std::endl;
                return -1;
            }
            stock.retrait(nomingredient, nombre);
        } else if(commande=="recommendation") {
           if(stock.produits.empty()) continue;
           if(recettes.empty()) continue;
           int count = 0;
            for(std::map<std::string,Recette>::iterator i = recettes.begin();i!=recettes.end();++i){
                    if(stock.realisable(i->second)){
                       if(stock.dateExpiration(i->second) >= stock.miniDateProduit()){
                             std::cout<<i->second.getNomRecette();
                             count++;
                             break;
                        }
                    }
            }
            if(count) std::cout <<" ;"<< std::endl;
        } else if(commande=="utilisation") {
            if(stock.produits.empty()) continue;
            if(recettes.empty()) continue;
            std::string nomrecette;
            *entree >> nomrecette;
            if(stock.realisable(recettes[nomrecette])) {
                if(stock.utilisation(recettes[nomrecette]))
                    std::cout<< nomrecette<<" : 1"<<std::endl;
            }
            else std::cout<< " : 0 "<<std::endl;
        } else if(commande=="affichage") {
            if(stock.produits.empty()) continue;
            stock.affichage();
        } else {
            std::cerr << "commande \"" << commande << " non reconnue !" << std::endl; 
        }
    }
    delete entree_fichier;
    entree_fichier = nullptr;
    return 0;
}
