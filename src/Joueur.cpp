
#include "Joueur.h"

using namespace std;

Joueur::Joueur()
{

}

Joueur::Joueur(string nom) : m_nom(nom)
{

}

string Joueur::getNom(){return m_nom;}

vector<Carte> Joueur::getCartes(){return m_cartes;}

Carte Joueur::getCarte(int i){return m_cartes.at(i);}

void Joueur::ajouterCarte(Carte c)
{
    m_cartes.push_back(c);
}

Carte Joueur::enleverCarte(int i)
{
    Carte c(m_cartes[i].getCouleur(), m_cartes[i].getValeur());
    m_cartes.erase(m_cartes.begin() + i);
    return c;
}

void Joueur::ajouterNom(string nom)
{
    m_nom = nom;
}

int Joueur::nombreCartes(){return m_cartes.size();}