#ifndef DEF_CARTE
#define DEF_CARTE

#include <iostream>
#include <string>

enum Couleur { ROUGE, JAUNE, VERT, BLEU, AUCUNE };
enum Valeur { ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, PLUS_DEUX, PLUS_QUATRE, INVERSION, CHANGEMENT_COULEUR, SENS_INTERDIT };

// representation d'une carte par une valeur et une couleur
class Carte
{
    public:
        Carte();
        Carte(Couleur couleur, Valeur valeur);
        Valeur getValeur();
        Couleur getCouleur();
        void afficher();

    private:
        Valeur m_valeur;
        Couleur m_couleur;
};

#endif