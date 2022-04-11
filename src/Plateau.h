#ifndef DEF_PLATEAU
#define DEF_PLATEAU

#include "Carte.h"
#include <vector>
#include <random>
#include <algorithm>

// représentation d'un plateau de jeu par sa pioche et son talon (défausse)
class Plateau
{
    public:
        Plateau();
        std::vector<Carte> getPioche();
        std::vector<Carte> getDefausse();
        Carte getDerniereCartePioche();
        Carte getCartePioche(int i);
        void ajouterCartePioche(Carte c);
        void melangerPioche();
        Carte getDerniereCarteDefausse();
        void ajouterCarteDefausse(Carte c);
        bool estPosable(Carte c);
        bool piocheEstVide();
        void piocheVide();
        Carte enleverDerniereCartePioche();

    private:
        std::vector<Carte> m_pioche; 
        std::vector<Carte> m_defausse;
        int m_nbCartes;
};

#endif