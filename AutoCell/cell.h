#ifndef CELL_H
#define CELL_H
/*!
 * \file cell.h
 * \brief Déclaration de la classe Cell et déclaration des différents états que peut prendre les cellules et la couleur associée
 * \version 1.0
 */
#include <vector>
#include "automateexception.h"

//nombre d'etat pris en compte pour nos automates : Dans le cadre de l'automate FeuDeFôret : Blanc = case vide, Noir = cendre, Vert = Arbre, Rouge = Feu
/**
* \enum etat
* \brief Nombre d'états gérés par le programme et couleurs associées
* \details Cette énumération est surtout utile pour la partie interface de l'application ou pour certaines règles de transition afin de les rendre plus claires. (En effet, au niveau de l'architecture, nous ne sommes absolument pas limité à un nombre précis d'états possibles, sauf par la limite maximum des int évidemment)
*/

enum etat
{
    BLANC = 0, NOIR = 1, VERT = 2, ROUGE = 3
};

/*! \class Cell
  * \brief classe représentant une cellule : élément de base du programme
  *
  * \details La classe permet de créer des cellules, leur affecter une position, un etat, et des voisins
  */
class Cell
{
public:
    friend class Etat;
    /*!
         * \brief Accesseur en lecture sur m_voisins
         *
         * \details Méthode permettant de récupérer une référence const sur l'ensemble des voisins d'une cellule
         * \return voisins de la cellule
         */
    std::vector<Cell*> const& GetVoisins() const
    {
        return m_voisins;
    }

    /*!
         *  \brief Accesseur en lecture sur m_etat
         *
         *
         * \return etat de la cellule
         */
    int GetEtat() const
    {
        return m_etat;
    }
    /*!
         *  \brief Accesseur en lecture sur m_x
         *
         *
         * \return position en X (ligne)
         */
    int GetX() const { return m_x; }
    /*!
         *  \brief Accesseur en lecture sur m_y
         *
         *
         * \return position en Y (colonne)
         */
    int GetY() const { return m_y; }
    /*!
         *  \brief modification de l'etat
         * \param etat : valeur prise par la cellule
         */
    void SetEtat(int etat);
    /*!
         *  \brief ajout d'un voisin dans le voisinage de la cellule
         * \param voisin = pointeur sur la cellule voisine à ajouter
         */
    void AjouterVoisin(Cell *voisin);
    /*!
      * \brief Suppression du voisinage
      *
      */
    void ClearVoisinage()
    {
        m_voisins.clear();
    }


private:
    /*!
         *  \brief Destructeur par défaut
         *
         */

    ~Cell() = default; //pas d'allocation dynamique dans la classe car le vector m_voisins est un tableau d'adresses (on ne supprime pas les voisins d'une Cellule quand on détruit la Cellule)
    /*!
         *  \brief Constructeur
         *
         *  \details Constructeur par défault de la classe Cell : X, Y et l'état sont initialisés à 0. Seule la classe Etat peut construire des Cell.
         *
         *
         */
    Cell() : m_etat(0), m_voisins(), m_x(0), m_y(0)
    {

    }
    /*!
         *  \brief Constructeur
         *
         *  \details Constructeur de la classe Cell. Seule la classe Etat peut construire des Cell.
         *
         *
         *  \param etat : valeur prise par la cellule
         *  \param x,y : positions
         */
    Cell(int etat, int x, int y) : m_etat(etat), m_voisins(), m_x(x), m_y(y)
    {

    }
    /*!
         *  \brief Constructeur de recopie.
         * \details Constructeur de recopie de la classe Cell. Seule la classe Etat peut construire des Cell.
         * \param c : référence sur la Cell qu'on souhaite copier
         */
    Cell(Cell const& c) = default;
    /*!
         *  \brief modification de la position X
         * \details accesseur en écriture sur m_x. Seule la classe Etat peut l'utiliser car il est illogique d'affecter une position X en dehors d'une grille. (Cet accesseur n'a pas grand intérêt car la classe Etat pourrait modifier m_x directement vu que c'est une classe amie, mais nous avons pris la décision d'en faire une classe amie plus tard donc nous l'avons laissé afin de ne pas remodifier le code de la classe Etat)
         * \param x : ligne
         */
    void SetX(int x);
    /*!
         *  \brief modification de la position Y
         * \details accesseur en écriture sur m_y. Seule la classe Etat peut l'utiliser car il est illogique d'affecter une position Y en dehors d'une grille. (Cet accesseur n'a pas grand intérêt car la classe Etat pourrait modifier m_y directement vu que c'est une classe amie, mais nous avons pris la décision d'en faire une classe amie plus tard donc nous l'avons laissé afin de ne pas remodifier le code de la classe Etat)
         * \param y : colonne
         */
    void SetY(int y);

    /*!
      * \brief surcharge de l'opérateur d'affectation (défaut)
      * \param c : référence sur la cellule qui va nous servir à affecter la cellule courante
      */
    Cell& operator=(Cell const& c) = default;


    /*!
         *  \brief état (valeur) de la cellule
         *
         */
    int m_etat;
    /*!
         *  \brief vecteur de pointeurs sur les voisins de la cellule
         *
         */
    std::vector<Cell*> m_voisins;
    /*!
         *  \brief position en ligne de la cellule
         *
         */
    int m_x;
    /*!
         *  \brief position en colonne de la cellule
         *
         */
    int m_y;


};

#endif // CELL_H
