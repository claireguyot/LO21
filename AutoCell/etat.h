#ifndef ETAT_H
#define ETAT_H
#include <vector>
#include "cell.h"
#include "generateuretat.h"
#include <iostream>

class Etat
{
public:
   Etat(int largeur, int longueur, GenerateurEtat& generateur, int nbEtats ); //le nombre d'Etats ne sera pas stocké dans la classe Etat car ça sert à rien on va le stocker dans la grande classe simulateur. ça ne sert qu'à générer le 1er Etat ou à regénérer et on va éviter de dupliquer des informations
   Etat(int largeur, int longueur, int **tab);
   Etat(int largeur, int longueur);
   Etat(Etat const&) = default;
   void Regenerer(int nbEtats) //avec l'interface il faudra laisser la possibilité de regenerer l'etat initial uniquement si on a mit un algo de génération
   {
       m_generateur->GenererEtat(nbEtats,m_cellules);
   }
   int GetLongueur() const { return m_longueur; }
   int GetLargeur() const { return m_largeur; }
   Cell const& GetCellule(int i, int j) const {
       if (i>=m_largeur || i<0 || j< 0 || j>= m_longueur)
           throw "Trop loin";
       return m_cellules[i][j];}
   Cell& GetCellule(int i, int j) {
       if (i>=m_largeur || i<0 || j< 0 || j>= m_longueur)
           throw "Trop loin";
       return m_cellules[i][j];}
   ~Etat() = default;
   void afficher() const;
private:
   GenerateurEtat* m_generateur; //pointeur sur le générateur d'Etat (ne sera pas détruit avec la destruction de l'Etat car le generateur peut exister sans l'Etat.
   std::vector<std::vector<Cell>> m_cellules; //pas de vector<vector<Cell*>> Car on ne pourra pas détruire les Cell dans le vector en même temps que l'Etat car sinon toutes les copies de l'Etat initial (donc les Etats suivants) perdront leur grille (on va donc augmenter le cout mémoire en faisant un tableau de Cell à chaque Etat sachant que généralement on aura que 3 grilles simultanément, 1 pour garder la configuration par défaut , 1 pour l'Etat courant, 1 pour l'Etat précédent)
   //Si vous avez des idées pour pouvoir faire un vector de Cell* afin d'économiser le coût mémoire lors de la copie des Etats sans supprimer les Cells quand on va supprimer un Etat proposez votre idée ^^
   int m_longueur;
   int m_largeur;



};

#endif // ETAT_H
