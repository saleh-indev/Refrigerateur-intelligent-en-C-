/**
 * @file stock.h
 * @author 
 * @brief Description des classes utilisees
 * @version 4.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include <map>
#include <vector>

/**
 * @brief Produit decrit un produit dans le stcock (refrigerateur)
 * 
 */
class Produit {
  public:
    Produit(std::string name,std::string date, int quantite);
    Produit(std::string name, int quantite);
    Produit();
    ~Produit();
    int getQuantite();
    std::string getName();
    void setName(std::string unNom);
    std::string getDate();
    void setDate(std::string date);
    void setQuantite(int q);
    bool operator < (const Produit& e) const;
private:
    std::string nom;
    std::string date;
    int quantite;
};
/**
 * @brief Classe decrivant un ingredient 
 * 
 */
class Ingredient{
    public:
        Ingredient();
        ~Ingredient();
        Ingredient(std::string nom, int quantite);
        int getQuantite();
        void setQuantite(int quantite);
        std::string getNom();
        void setNom(std::string nom);
        bool operator < (const Ingredient& e) const ;
    private:
      std::string nom;
      int quantite;
};


/**
 * @brief Classe decrivant une recette
 * 
 */
class Recette {
   public: 
        Recette(std::string nomRecette);
        Recette();
        ~Recette();
        void ajouter(std::string chaine, int quantite);
        void miseAJour(std::string chaine, int quantite);
        bool existe(std::string chaine);
        std::string getNomRecette(){return nomrecette;}
        Ingredient getIngredient(std::string chaine);

        std::map<std::string,Ingredient> ingredients;
    private:
    std::string nomrecette;
    friend std::istream& operator >> (std::istream& is, Recette& recette);
};


/**
 * @brief Classe decrivant un stock
 * 
 */
class Stock
{
public:
    Stock();
    ~Stock();
    Stock(std::vector<Produit> p);
    void ajout(std::string nomingredient, std::string date, int nombre);
    void ajout(Produit p);
    void retrait(std::string nomingredient, int nombre);
    void retrait(Recette& recette);
    void affichage();
    std::string dateExpiration(Recette& recette);
    bool realisable(Recette& recette) ;
    bool utilisation(Recette& recette);

    //Autres methodes utiles
    Produit getProduit(std::string nom, std::string date);
    std::vector<Produit> produits;  
    std::string miniDateProduit();  
    std::string miniDateProduit(std::string nom);
    std::vector<Produit> getProduits(std::string nom);
    bool compare(std::string date1, std::string date2);
    std::string getDateMin(std::vector<Produit> prods);
    std::vector<Produit> trier(std::vector<Produit> p);
    std::vector<Produit> getDate();
};
#endif // STOCK_H