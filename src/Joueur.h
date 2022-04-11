#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include "Carte.h"
#include <vector>

// représentation d'un joueur par son nom et sa main de cartes
class Joueur
{
    public:
        Joueur();
        Joueur(std::string nom);
        std::string getNom();
        std::vector<Carte> getCartes();
        void ajouterCarte(Carte c);
        Carte getCarte(int i);
        Carte enleverCarte(int i);
        void ajouterNom(std::string nom);
        int nombreCartes();

    private:
        std::string m_nom;
        std::vector<Carte> m_cartes;
};

#endif