/**
 * @file stock.cpp
 * @author 
 * @brief Fichier contenant l'implementation des classes
 * @version 2.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "stock.h"
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

//============================================================================
//------------------------METHODES DES PRODUITS-------------------------------
Produit::Produit(std::string name, std::string date, int quantite) : nom(name), date(date), quantite(quantite) {}
Produit::Produit(std::string name, int quantite) : nom(name), date(""), quantite(quantite) {}
Produit::Produit() : nom(""), date(""), quantite() {}
Produit::~Produit() {}
int Produit::Produit::getQuantite(){
    return quantite;
}
std::string Produit::getName(){
    return nom;
}
std::string Produit::getDate() { 
    return date; 
}
void Produit::setName(std::string c) { 
    nom = c; 
}

void Produit::setDate(std::string d) { 
    date = d; 
}
void Produit::setQuantite(int q) { 
    this->quantite = q; 
}
bool Produit::operator<(const Produit &e) const { 
    return nom < e.nom; 
}
//============================================================================
//------------------------METHODES DE LA CLASSE INGREDIENT-------------------------------
Ingredient::Ingredient() : nom(""), quantite(0) {}
Ingredient::~Ingredient() {}
Ingredient::Ingredient(std::string nom, int quantite) : nom(nom), quantite(quantite) {}
int Ingredient::getQuantite() { return quantite; }
void Ingredient::setQuantite(int quantite) { this->quantite = quantite; }
std::string Ingredient::getNom() { return nom; }
void Ingredient::setNom(std::string nom) { this->nom = nom; }
bool Ingredient::operator<(const Ingredient &e) const { return nom < e.nom; }

//============================================================================
//------------------------METHODES DE Recette-------------------------------
std::istream &operator>>(std::istream &is, Recette &recette)
{
    std::string chaine;
    int quantite;
    for (;;)
    {
        is >> chaine;
        if (chaine == ";")
            break;
        is >> quantite;
        if (recette.existe(chaine))
            recette.miseAJour(chaine, quantite);
        else
            recette.ajouter(chaine, quantite);
    }
    return is;
}
Recette::Recette() {}
Recette::Recette(std::string nomRecette) : nomrecette(nomRecette){};
Recette::~Recette() {}
Ingredient Recette::getIngredient(std::string chaine) { return ingredients.at(chaine); }
void Recette::ajouter(std::string chaine, int quantite)
{
    Ingredient ing;
    ing.setQuantite(quantite);
    ing.setNom(chaine);
    ingredients[chaine] = ing;
}
void Recette::miseAJour(std::string chaine, int quantite)
{
    ingredients[chaine].setQuantite(ingredients[chaine].getQuantite() + quantite);
}

bool Recette::existe(std::string chaine)
{
    if (ingredients.find(chaine) != ingredients.end())
        return true;
    else
        return false;
}

//============================================================================
//------------------------METHODES DE STOCK-------------------------------
Stock::Stock(){};
Stock::~Stock(){};
Stock::Stock(std::vector<Produit> p): produits(p){}
void Stock::ajout(std::string nomingredient, std::string date, int nombre)
{
    for (Produit i : produits)
    {
        if (i.getName() == nomingredient && i.getDate() == date)
        {
            i.setQuantite(i.getQuantite() + nombre);
            return;
        }
    }
    Produit p(nomingredient, date, nombre);
    produits.push_back(p);
}
void Stock::ajout(Produit p)
{
    produits.push_back(p);
}
int getJour(const std::string date)
{
    std::string j;
    j = date.substr(8, 9);
    int i=0;
    try
    {
        i = (int)std::stoi(j);
    }
    catch (...)
    {
    }
    return i;
}
int getMois(const std::string date)
{
    std::string j;
    j = date.substr(5, 6);
    int i=0;
    try
    {
        i = (int)std::stoi(j);
    }
    catch (...)
    {
    }
    return i;
}
int getAnnee(const std::string date)
{
    std::string j;
    j = date.substr(0, 4);
    int i=0;
    try
    {
        i = (int)std::stoi(j);
    }
    catch (...)
    {
    }
    return i;
}
bool Stock::compare(std::string date1, std::string date2)
{
    const std::string d11(date1), d12(date1);
    const std::string d21(date2), d22(date2);
    int jj1, jj2, mm1, mm2, aa1, aa2;
    jj1 = getJour(d12);
    jj2 = getJour(d22);
    aa1 = getAnnee(date1);
    aa2 = getAnnee(date2);
    mm1 = getMois(d11);
    mm2 = getMois(d21);
    if (aa1 > aa2)
        return true;
    else if (aa1 == aa2)
    {
        if (mm1 > mm2)
            return true;
        else if (mm1 == mm2)
        {
            if (jj1 > jj2)
                return true;
            else if (jj1 == jj2) return true;
            else return false;
        }
        else
            return false;
    }
    else
        return false;
}
std::string Stock::getDateMin(std::vector<Produit> prods)
{
    std::string datemin = prods[0].getDate();
    int n = prods.size();
    for (int i = 1; i < n; i++)
    {
        if (compare(datemin, prods[i].getDate()))
            datemin = prods[i].getDate();
    }
    return datemin;
}
void Stock::retrait(std::string nomingredient, int nombre){
    for (Produit iter : produits){
        if (iter.getName() == nomingredient)
        {
              iter.setQuantite(iter.getQuantite() - nombre);
                return;

        }
    }
}
std::vector<Produit> Stock::getDate(){
    std::vector<Produit> prod;
     std::vector<Produit> produit(0);
    for (Produit i : prod)
        produit.push_back(i);
         int SIZE = (int)produit.size();
    int i, j;
    Produit tmp;
    for (i = 1; i <= SIZE - 1; i++)
    {
        j = i;
        while (j > 0 && compare(produit[j].getDate(),produit[j - 1].getDate())==true)
        {
            tmp = produit[j];
            produit[j] = produit[j - 1];
            produit[j - 1] = tmp;
            j--;
        }
    }
    return produit;
}
std::vector<Produit> Stock::trier(std::vector<Produit> prod)
{
    std::vector<Produit> produit(0);
    for (Produit i : prod)
        produit.push_back(i);
    int SIZE = (int)produit.size();
    int i, j;
    Produit tmp;
    for (i = 1; i <= SIZE - 1; i++)
    {
        j = i;
        while (j > 0 && produit[j - 1].getName() > produit[j].getName())
        {
            tmp = produit[j];
            produit[j] = produit[j - 1];
            produit[j - 1] = tmp;
            j--;
        }
    }
    return produit;
}
void Stock::affichage()
{
    std::vector<Produit> p = trier(produits);
    int taille = (int)p.size();
    std::vector<int> index;
    int count =0;
    bool trouve = false;
    for (int i = 0; i < taille; i++)
    {
        trouve = false;
        for(int j = 0; j < (int)index.size(); j++){
            if(index[j] == i) trouve = true;
        }
        if(trouve) continue;
        std::cout << p[i].getName() << " ";
        std::string nom = p[i].getName();
        count =p[i].getQuantite();
        for (int j = i+1; j < taille; j++){
                if (nom == p[j].getName()){
                    count+= p[j].getQuantite();
                    index.push_back(j);
                }
        }
        index.push_back(i);
        std::cout<<count<<std::endl;
    }
    std::cout << ";" << std::endl;
}
void Stock::retrait(Recette &recette)
{
    int nombre =0;
    std::map<std::string, Ingredient>::iterator i= recette.ingredients.begin();
    for (; i != recette.ingredients.end(); ++i)
    {
        nombre = i->second.getQuantite();
        for (Produit iter : produits)
        {
            if (iter.getName() == i->second.getNom())
            {
                    iter.setQuantite(iter.getQuantite() - nombre);
                    return;
    
            }
        }
          
    }
}
std::string Stock::dateExpiration(Recette &recette)
{
    std::map<std::string, Ingredient>::iterator i = recette.ingredients.begin();
    std::vector<std::string> dates(0);
    for (; i != recette.ingredients.end(); ++i)
    {
        for (Produit iter : produits)
        {
            if (iter.getName() == i->second.getNom())
                dates.push_back(miniDateProduit(iter.getName()));
        }
    }
    std::string dateTmp = dates[0];
    int taille = dates.size();
    for (int i = 1; i < taille; i++)
    {
        if (compare(dates[i - 1], dates[i]))
        {
            dateTmp = dates[i];
        }
    }
    return dateTmp;
}
std::string Stock::miniDateProduit()
{
    std::string minim = produits[0].getDate();
    int n = (int)produits.size();
    for (int i = 1; i < n; i++)
    {
        if (compare(minim, produits[i].getDate()))
            minim = produits[i].getDate();
    }
    return minim;
}
std::string Stock::miniDateProduit(std::string nom)
{
    std::string minim;
    for (Produit it : produits)
    {
        if (it.getName() == nom)
        {
            minim = it.getDate();
            break;
        }
    }
    for (Produit it : produits)
    {
        if (it.getName() == nom)
        {
            if (compare(minim, it.getDate()))
                minim = it.getDate();
        }
    }
    return minim;
}
bool Stock::realisable(Recette &recette)
{
    std::map<std::string, Ingredient>::iterator i = recette.ingredients.begin();
    for (; i != recette.ingredients.end(); ++i)
    {
        int j = 0;
        int q = 0;
        for (Produit iter : produits)
        {
            if (iter.getName() == i->second.getNom())
            {
                if (iter.getQuantite() >= i->second.getQuantite())
                    break;
                else
                    q += iter.getQuantite();
            }
            if (q >= i->second.getQuantite())
                break;
            j++;
            if (j == (int)produits.size())
                return false;
        }
    }
    return true;
}

bool Stock::utilisation(Recette &recette){
    std::map<std::string, Ingredient>::iterator i = recette.ingredients.begin();
    for (; i != recette.ingredients.end(); ++i)
        this->retrait(i->second.getNom(), i->second.getQuantite());
    return true;
}
Produit Stock::getProduit(std::string nom, std::string date)
{
    for (Produit it : produits)
    {
        if (it.getName() == nom && it.getDate() == date)
            return it;
    }
    Produit p;
    p.setName("null"); 
    return p;
}
std::vector<Produit> Stock::getProduits(std::string nom)
{
    std::vector<Produit> prods(0);
    for (Produit it : produits)
    {
        if (it.getName() == nom)
            prods.push_back(it);
    }
    return prods;
}
