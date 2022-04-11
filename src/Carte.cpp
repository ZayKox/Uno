
#include "carte.h"

using namespace std;

Carte::Carte()
{
    
}

Carte::Carte(Couleur couleur, Valeur valeur) : m_couleur(couleur), m_valeur(valeur) 
{

}

Valeur Carte::getValeur(){return m_valeur;}

Couleur Carte::getCouleur(){return m_couleur;}

void Carte::afficher()
{
    cout << "(";
    switch (m_valeur)
    {
    case 10:
        cout << "+2";
        break;
    case 11:
        cout << "+4";
        break;
    case 12:
        cout << "Changement de sens";
        break;
    case 13:
        cout << "Changement de couleur";
        break;
    case 14:
        cout << "Sens interdit";
        break;
    default:
        cout << m_valeur;
        break;
    }

    switch (m_couleur)
    {
    case 0:
        cout << " rouge";
        break;
    case 1:
        cout << " jaune";
        break;
    case 2:
        cout << " vert";
        break;
    case 3:
        cout << " bleu";
        break;
    default:
        break;
    }
    cout << ")";
}