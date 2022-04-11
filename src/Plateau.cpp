
#include "Plateau.h"

using namespace std;

Plateau::Plateau()
{
    m_nbCartes = 108;

    const Couleur listeCouleur[] = { ROUGE, JAUNE, VERT, BLEU };
    const Valeur listeValeur[] = { ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, PLUS_DEUX, PLUS_QUATRE, INVERSION, CHANGEMENT_COULEUR, SENS_INTERDIT };

    for (Couleur c : listeCouleur)
    {
        for (Valeur v : listeValeur)
        {
            Carte carte(c, v);
            if (v == ZERO) m_pioche.push_back(carte);
            else if (v == PLUS_QUATRE || v == CHANGEMENT_COULEUR)
            {
                Carte c(AUCUNE, v);
                m_pioche.push_back(c);
            }
            else
            {
                m_pioche.push_back(carte);
                m_pioche.push_back(carte);
            }
        }            
    }

    random_device rd;
    default_random_engine rng(rd());
    shuffle(m_pioche.begin(), m_pioche.end(), rng);
}

vector<Carte> Plateau::getPioche(){return m_pioche;}

vector<Carte> Plateau::getDefausse(){return m_defausse;}

Carte Plateau::getDerniereCartePioche(){return m_pioche.at(m_pioche.size()-1);}

Carte Plateau::getDerniereCarteDefausse(){return m_defausse.at(m_defausse.size()-1);}

Carte Plateau::getCartePioche(int i){return m_pioche.at(i);}

void Plateau::ajouterCartePioche(Carte c)
{
    m_pioche.push_back(c);
}

void Plateau::melangerPioche()
{
    random_shuffle(m_pioche.begin(), m_pioche.end());
}

void Plateau::ajouterCarteDefausse(Carte c)
{
    m_defausse.push_back(c);
}

bool Plateau::estPosable(Carte c)
{
    return getDerniereCarteDefausse().getCouleur() == c.getCouleur() || getDerniereCarteDefausse().getValeur() == c.getValeur() 
        || c.getValeur() == PLUS_QUATRE || c.getValeur() == CHANGEMENT_COULEUR;
}

bool Plateau::piocheEstVide(){return m_pioche.size() == 0;}

void Plateau::piocheVide()
{
    // pioche bien vide
    for (int i = 0; i < m_defausse.size()-1; i++)
    {
        m_pioche.push_back(m_defausse.at(i));
        m_defausse.erase(m_defausse.begin() + i);
    }
    random_device rd;
    default_random_engine rng(rd());
    shuffle(m_pioche.begin(), m_pioche.end(), rng);
}

Carte Plateau::enleverDerniereCartePioche()
{
    Carte c(getDerniereCartePioche().getCouleur(), getDerniereCartePioche().getValeur());
    m_pioche.pop_back();
    return c;
}