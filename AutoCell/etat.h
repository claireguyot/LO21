#ifndef ETAT_H
#define ETAT_H
#include "cell.h"
#include "generateuretat.h"

class Etat
{
public:
   Etat(unsigned int largeur, unsigned int longueur, GenerateurEtat const& generateur, unsigned int nbEtats ); //le nombre d'Etats ne sera pas stocké dans la classe Etat car ça sert à rien on va le stocker dans la grande classe simulateur. ça ne sert qu'à générer le 1er Etat ou à regénérer et on va éviter de dupliquer des informations
   Etat(unsigned int largeur, unsigned int longueur, std::vector<std::vector<int>> tab);
   Etat(unsigned int largeur, unsigned int longueur);
   Etat(Etat const& e);
   Etat& operator=(Etat const& e);
   void Regenerer(int nbEtats) //avec l'interface il faudra laisser la possibilité de regenerer l'etat initial uniquement si on a mit un algo de génération
   {
       m_generateur->GenererEtat(nbEtats,m_cellules,m_largeur,m_longueur);
   }
   int GetLongueur() const { return m_longueur; }
   int GetLargeur() const { return m_largeur; }
   Cell& GetCellule(int i, int j)  {
       if (i>=m_largeur || i<0 || j< 0 || j>= m_longueur)
           throw AutomateException("Tentative d'accès à un élément hors grille");
       return m_cellules[i][j];}
   Cell const& GetCellule(int i, int j) const {
       if (i>=m_largeur || i<0 || j< 0 || j>= m_longueur)
           throw AutomateException("Tentative d'accès à un élément hors grille");
       return m_cellules[i][j];}
   ~Etat();
   void afficher() const;
   friend class iterator;
   class iterator {
       friend class Etat;
           Etat* etat;
           int i;
           int j;
           iterator(Etat* e) :etat(e), i(0), j(0) {}
           iterator(Etat*e, int ligne, int colonne) :etat(e), i(ligne), j(colonne) {}
       public:
           iterator& operator++() {
               j++;
               if (j==etat->m_longueur && i<etat->m_largeur)
               {
                    j=0;
                    i++;
               }
               return *this;
           }
           Cell& operator*() const {
                return etat->m_cellules[i][j];
           }
           bool operator!=(iterator it) const { return etat != it.etat || i != it.i || j != it.j; }
       };

       iterator begin() {	return iterator(this,0,0); }
       iterator end() {  return iterator(this, m_largeur,m_longueur);}

       friend class const_iterator;
       class const_iterator {
           friend class Etat;
               Etat const* etat;
               int i;
               int j;
               const_iterator(Etat const* e) :etat(e), i(0), j(0) {}
               const_iterator(Etat const* e, int ligne, int colonne) :etat(e), i(ligne), j(colonne) {}
           public:

               const_iterator & operator++() {
                   j++;
                   if (j==etat->m_longueur)
                   {
                        j=0;
                        i++;
                   }
                   return *this;
               }
               Cell const& operator*() const {
                    return etat->m_cellules[i][j];
               }
               bool operator!=(const_iterator it) const { return etat != it.etat || i != it.i || j != it.j; }
           };

           const_iterator begin() const {	return const_iterator(this,0,0); }
           const_iterator end() const {  return const_iterator(this, m_largeur,0); }


private:
   GenerateurEtat const* m_generateur; //pointeur sur le générateur d'Etat (ne sera pas détruit avec la destruction de l'Etat car le generateur peut exister sans l'Etat.
   Cell** m_cellules; //représente un tableau 2D de Cell, on n'utilise pas de Cell* car pour chaque grille il faut avoir des Cell différentes sinon si on supprime une grille on perd toutes les informations
   // De plus on n'utilise pas des Cell* car on dispose d'un constructeur par défaut dans la classe Cell si on n'en avait pas on serait obligé d'utiliser des Cell* et de faire un Cell*** tab;

   // les durées de vie des cellules sont liés à la durée de vie de la grille
   unsigned int m_largeur;
   unsigned int m_longueur;



};

#endif // ETAT_H
