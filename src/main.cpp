
#include <iostream>
#include "Plateau.h"
#include "Joueur.h"

using namespace std;

void affichageDebut()
{
    cout << "Bonjour et merci de jouer au UNO fait par ZayKo_." << endl;
    cout << "Les regles sont simples vous pouvez poser une carte sur le talon que si la carte que vous avez choisi est" << endl;
    cout << "de la meme couleur ou de meme valeur, cependant il existe des cartes speciales (+2, +4, changement de couleur, " << endl;
    cout << "changement de sens et sens interdit) les +2 et +4 sont cumulables, il n'est pas possible de dire uno " << endl;
    cout << "par souci de simplicite." << endl;
}

void choisirJoueur(vector<Joueur> *joueurs)
{
    int nombreJoueurs;
    string nomJoueur;

    cout << "Maintenant veuillez choisir le nombre de joueur: ";
    cin >> nombreJoueurs;
    cout << endl;

    while (!(nombreJoueurs >= 2 && nombreJoueurs <= 10))
    {
        cout << "Ce nombre de joueur n'est pas valide (entre 2 et 10) reessaye: ";
        cin >> nombreJoueurs;
        cout << endl;
    }

    for (int i = 0; i < nombreJoueurs; i++)
    {
        cout << "Choisissez le prenom du joueur " << i+1 << ": ";
        cin >> nomJoueur;
        joueurs->push_back(Joueur(nomJoueur));
        cout << endl;
    }
}

void lancement(Plateau *p, vector<Joueur> *joueurs)
{
    for (int i = 0; i < joueurs->size(); i++)
    {
        for (int j = 0; j < 7; j++) // 7 cartes par joueurs
            joueurs->at(i).ajouterCarte(p->enleverDerniereCartePioche());
    }
    while (p->getDerniereCartePioche().getValeur() == PLUS_QUATRE || p->getDerniereCartePioche().getValeur() == CHANGEMENT_COULEUR)
    {
        p->getPioche().insert(p->getPioche().begin(), p->enleverDerniereCartePioche());
    }
    p->ajouterCarteDefausse(p->enleverDerniereCartePioche());
}

void affichageCartesJoueur(Joueur joueur)
{
    system("cls");
    cout << joueur.getNom() << " vos cartes sont: " << endl;
    for (int i = 0; i < joueur.nombreCartes()-1; i++)
    {
        cout << "Carte " << i+1 << " ";
        joueur.getCarte(i).afficher();
        cout << ",\n";
    }
    cout << "Carte " << joueur.nombreCartes() << " ";
    joueur.getCarte(joueur.nombreCartes()-1).afficher();
    cout << "." << endl;   
}

void joueurChoisirCarte(Plateau *p, Joueur *joueur, int *etatJoueur, int *nbCartesAPiocher, int *etatDerniereCarteDefausse)
{
    int numCarteChoisi;
    bool etat = true;

    cout << "La carte du talon est: ";
    p->getDerniereCarteDefausse().afficher();
    cout << endl;
    cout << joueur->getNom() << " veuillez choisir une carte en tapant son numero (si vous voulez piocher taper 0): ";
    cin >> numCarteChoisi;
    cout << endl;

    while (etat)
    {
        while (!(numCarteChoisi >= -1 && numCarteChoisi <= joueur->nombreCartes()))
        {
            cout << "Numero de carte choisie n'est pas valide reessaye: ";
            cin >> numCarteChoisi;
            cout << endl;
        }

        if (numCarteChoisi == 0 && *etatJoueur == 0) 
        {
            cout << "La carte pioche est ";
            p->getDerniereCartePioche().afficher();
            cout << "." << endl;
            system("pause");
            if (p->estPosable(p->getDerniereCartePioche()))
            {
                cout << "Voulez vous poser la carte (O pour oui ou N pour non): ";
                char choix;
                cin >> choix;
                while (!(toupper(choix)== 'O' || toupper(choix) == 'N'))
                {
                    cout << "Cette reponse n'est pas acceptable veuillez reessaye: ";
                    cin >> choix;
                }
                if (toupper(choix) == 'O') p->ajouterCarteDefausse(p->enleverDerniereCartePioche());
                else joueur->ajouterCarte(p->enleverDerniereCartePioche());
            }
            else joueur->ajouterCarte(p->enleverDerniereCartePioche());
            etat = false;
            if (p->getDerniereCarteDefausse().getValeur() >= 10) *etatDerniereCarteDefausse = 1;
        }
        else if (numCarteChoisi == 0 && *etatJoueur == 1)
        {
            cout << "Les cartes pioches sont ";
            for (int i = 0; i < *nbCartesAPiocher-1; i++)
            {
                joueur->ajouterCarte(p->enleverDerniereCartePioche());
                joueur->getCarte(joueur->nombreCartes()-1).afficher();
                cout << ", ";
            }
            joueur->ajouterCarte(p->enleverDerniereCartePioche());
            joueur->getCarte(joueur->nombreCartes()-1).afficher();
            cout << "." << endl;
            system("pause");
            *etatJoueur = 0;
            etat = false;
            *nbCartesAPiocher = 0;  
            if (p->getDerniereCarteDefausse().getValeur() >= 10) *etatDerniereCarteDefausse = 1;
        }
        else if (numCarteChoisi != 0 && *etatJoueur == 1)
        {
            if (joueur->nombreCartes() == 1 && joueur->getCarte(numCarteChoisi-1).getValeur() >= 10)
            {
                cout << "Vous ne pouvez pas finir par une carte comme celle la, vous devez donc piocher." << endl;
                cout << "Les cartes pioches sont ";
                for (int i = 0; i < *nbCartesAPiocher-1; i++)
                {
                    joueur->ajouterCarte(p->enleverDerniereCartePioche());
                    joueur->getCarte(joueur->nombreCartes()-1).afficher();
                    cout << ", ";
                }
                joueur->ajouterCarte(p->enleverDerniereCartePioche());
                joueur->getCarte(joueur->nombreCartes()-1).afficher();
                cout << "." << endl;
                *etatJoueur = 0;
                etat = false;
                *nbCartesAPiocher = 0;  
            }
            while (p->getDerniereCarteDefausse().getValeur() == PLUS_DEUX && joueur->getCarte(numCarteChoisi-1).getValeur() != PLUS_DEUX)
            {
                cout << "La carte choisie n'est pas posable, veuillez choisir une carte +2 ou piocher: ";
                cin >> numCarteChoisi; 
                cout << endl;
            }
            while (p->getDerniereCarteDefausse().getValeur() == PLUS_QUATRE && joueur->getCarte(numCarteChoisi-1).getValeur() != PLUS_QUATRE)
            {
                cout << "La carte choisie n'est pas posable, veuillez choisir une carte +4 ou piocher: ";
                cin >> numCarteChoisi; 
                cout << endl;
            }
            cout << "Vous avez choisi la carte: ";
            joueur->getCarte(numCarteChoisi-1).afficher();
            cout << "." << endl;
            p->ajouterCarteDefausse(joueur->enleverCarte(numCarteChoisi-1));
            *etatJoueur = 0;
            etat = false;
        }
        else if (numCarteChoisi != 0 && *etatJoueur == 0)
        {
            if (joueur->nombreCartes() == 1 && (p->estPosable(joueur->getCarte(numCarteChoisi-1))) && joueur->getCarte(numCarteChoisi-1).getValeur() >= 10)
            {
                cout << "Vous ne pouvez pas finir par une carte comme celle la, vous devez donc piocher" << endl;
                joueur->ajouterCarte(p->enleverDerniereCartePioche());
                cout << "Vous avez pioche la carte ";
                joueur->getCarte(joueur->nombreCartes()-1).afficher();
                cout << "." << endl;
                system("pause");
                etat = false;
            }            
            else if (p->estPosable(joueur->getCarte(numCarteChoisi-1)))
            {
                cout << "Vous avez choisie la carte: ";
                joueur->getCarte(numCarteChoisi-1).afficher();
                cout << "." << endl;
                p->ajouterCarteDefausse(joueur->enleverCarte(numCarteChoisi-1));
                etat = false;
            }
            else 
            {
                cout << "La carte choisie n'est pas posable, veuillez choisir une autre carte: ";
                cin >> numCarteChoisi; 
                cout << endl;
            }               
        }
    }
}

string capitalizeString(string s)
{
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return toupper(c); });
    return s;
}

void pasBonneCarte(vector<Joueur> *joueurs, Plateau *p, int *nbCartesAPiocher, int *i)
{
    system("cls");
    cout << joueurs->at((*i+1)%joueurs->size()).getNom() << " vous avez pioche des cartes car vous n'aviez pas de bonne carte a poser: ";
    for (int j = 0; j < *nbCartesAPiocher-1; j++) 
    {
        joueurs->at((*i+1)%joueurs->size()).ajouterCarte(p->enleverDerniereCartePioche());
        joueurs->at((*i+1)%joueurs->size()).getCarte(joueurs->at((*i+1)%joueurs->size()).nombreCartes()-1).afficher();
        cout << ", ";
    }
    joueurs->at((*i+1)%joueurs->size()).ajouterCarte(p->enleverDerniereCartePioche());
    joueurs->at((*i+1)%joueurs->size()).getCarte(joueurs->at((*i+1)%joueurs->size()).nombreCartes()-1).afficher();
    cout << "." << endl;
    *nbCartesAPiocher = 0;
    system("pause");
}

Couleur verifCouleur(string s)
{
    if (s == "ROUGE") return ROUGE;
    else if (s == "JAUNE") return JAUNE;
    else if (s == "VERT") return VERT;
    else if (s == "BLEU") return BLEU;
    else return AUCUNE;
}

void actionCarte(Plateau *p, vector<Joueur> *joueurs, int *nbCartesAPiocher, int *i, int *etatJoueur)
{
    string couleurChoisi;
    int tmp1 = 0;
    vector<Joueur> tmp2;
    int cpt = 0;

    switch (p->getDerniereCarteDefausse().getValeur())
    {
    case 10:
        *nbCartesAPiocher += 2;
        for (int j = 0; j < joueurs->at((*i+1)%joueurs->size()).nombreCartes(); j++)
            if (joueurs->at((*i+1)%joueurs->size()).getCarte(j).getValeur() != 10) tmp1++;
        if (tmp1 == joueurs->at((*i+1)%joueurs->size()).nombreCartes()) 
        {
            pasBonneCarte(joueurs, p, nbCartesAPiocher, i); 
            *i = (*i+2)%joueurs->size();
        }
        else 
        {
            *etatJoueur = 1;
            *i = (*i+1)%joueurs->size();
        }
        break;
    case 11:
        *nbCartesAPiocher += 4;
        cout << "Choisir la couleur que vous voulez: ";
        cin >> couleurChoisi;

        while (!(capitalizeString(couleurChoisi) == "ROUGE" || capitalizeString(couleurChoisi) == "JAUNE" || capitalizeString(couleurChoisi) == "VERT" 
        || capitalizeString(couleurChoisi) == "BLEU")) 
        {
            cout << "Couleur non valide veuillez reessayer: ";
            cin >> couleurChoisi;
        }
        p->getDefausse().pop_back();
        p->ajouterCarteDefausse(Carte(verifCouleur(capitalizeString(couleurChoisi)), PLUS_QUATRE));
        system("pause");

        for (int j = 0; j < joueurs->at((*i+1)%joueurs->size()).nombreCartes(); j++)
            if (joueurs->at((*i+1)%joueurs->size()).getCarte(j).getValeur() != 11) tmp1++;
        if (tmp1 == joueurs->at((*i+1)%joueurs->size()).nombreCartes()) 
        {
            pasBonneCarte(joueurs, p, nbCartesAPiocher, i); 
            *i = (*i+2)%joueurs->size();
        }
        else 
        {
            *etatJoueur = 1;
            *i = (*i+1)%joueurs->size();
        }
        break;
    case 12: 
        for (int j = joueurs->size()-1; j >= 0; j--)
            tmp2.push_back(joueurs->at(j));
        for (int j = 0; j < joueurs->size(); j++)
            if (joueurs->at(*i).getNom() == tmp2.at(j).getNom()) *i = (j+1)%joueurs->size();
        for (int j = 0; j < joueurs->size(); j++)
            joueurs->at(j) = tmp2.at(j);
        cout << "C'est au tour du joueur " << joueurs->at((*i+1)%joueurs->size()).getNom() << "." << endl;
        system("pause");    
        break; 
    case 13:
        cout << "Choisir la couleur que vous voulez: ";
        cin >> couleurChoisi;

        while (!(capitalizeString(couleurChoisi) == "ROUGE" || capitalizeString(couleurChoisi) == "JAUNE" || capitalizeString(couleurChoisi) == "VERT" 
        || capitalizeString(couleurChoisi) == "BLEU")) 
        {
            cout << "Couleur non valide veuillez reessayer: ";
            cin >> couleurChoisi;
        }
        p->getDefausse().pop_back();
        p->ajouterCarteDefausse(Carte(verifCouleur(capitalizeString(couleurChoisi)), CHANGEMENT_COULEUR));
        system("pause");
        *i = (*i+1)%joueurs->size();
        break;
    case 14:
        cout << "Le joueur " << joueurs->at((*i+1)%joueurs->size()).getNom();
        cout << " doit passer son tour." << endl;
        system("pause");
        *i = (*i+2)%joueurs->size();
        break;
    default:
        break;
    }
}

void commencer()
{
    vector<Joueur> joueurs;
    Plateau p;
    bool etatPartie = true; // définit quand la partie est finie
    int nbCartesAPiocher = 0; // définie le nombre dgite carte à piocher
    int i = 0; // définit quel joueur doit jouer
    int etatJoueur = 0; // définit quel genre de carte doit être mise (si etatJoueur = 1 alors le joueur doit mettre une carte spéciale qui correspond à la dernière carte de la défausse)
    int etatDerniereCarteDefausse = 0; // permet que les autres joueurs n'aient pas de répercutions si un joueur se prend des cartes

    affichageDebut(); // affiche les règles
    choisirJoueur(&joueurs); // choisir le nom des joueurs
    lancement(&p, &joueurs); // lance la partie (distribution des cartes aux joueurs et mise d'une carte dans la défausse)

    while (etatPartie)
    {
        affichageCartesJoueur(joueurs.at(i)); // affiche les cartes des joueurs
        joueurChoisirCarte(&p, &joueurs.at(i), &etatJoueur, &nbCartesAPiocher, &etatDerniereCarteDefausse); // permet à un joueur de choisir la carte qu'il veut

        if (p.getDerniereCarteDefausse().getValeur() >= 10 && etatDerniereCarteDefausse == 0)
            actionCarte(&p, &joueurs, &nbCartesAPiocher, &i, &etatJoueur); // permet d'appliquer une action d'une carte spéciale (ex: +2, +4, etc)
        else
        {
            i = (i+1)%joueurs.size();
            etatDerniereCarteDefausse = 0;
        }

        if (p.piocheEstVide()) p.piocheVide(); // si la pioche est vide on mélange la défausse

        if (joueurs.at(i).getCartes().size() == 0) // fin quand un gagnant est désigné
        {
            cout << "Le gagnant est " << joueurs.at(i).getNom() << "." << endl;
            etatPartie = false;            
        }
    }
}

int main()
{
    commencer(); // lancement du code

    return 0;
}