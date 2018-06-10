#ifndef CELL_H
#define CELL_H

/*!
 * \file cell.h
 * \brief Déclaration de la classe Cell, définition de ses méthodes inline, et déclaration des différents états que peut prendre les cellules et la couleur associée
 */

#include <vector>
#include "automateexception.h"

/**
* \enum etat
* \brief Nombre d'états gérés par le programme et couleurs associées
*
* Cette énumération est surtout utile pour la partie interface de l'application ou pour certaines règles de transition afin de les rendre plus claires. (En effet, au niveau de l'architecture, nous ne sommes absolument pas limités à un nombre précis d'états possibles, sauf par la limite maximum des int évidemment.)
* Le nombre d'états pris en compte pour notre automate Feu de Forêt : Blanc = Case vide, Noir = Cendres, Vert = Arbre, Rouge = Feu.
*/

enum etat
{
    BLANC = 0, NOIR = 1, VERT = 2, ROUGE = 3
};

/*! \class Cell
  * \brief Classe représentant une cellule qui est l'élément de base du programme
  * \sa Etat
  *
  * \details Un objet \a Cell est une cellule qui fait nécessairement partie d'un objet \a Etat car seule la classe \a Etat peut construire des objets \a Cell. Une cellule est caractérisée par sa position (sur la ligne et la colonne), son état (sa valeur) et un voisinage.
  */
class Cell
{
public:
    friend class Etat;
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_voisins
         *
         * \details Méthode permettant de récupérer une référence \a const sur l'ensemble des voisins d'une cellule.
         * \return Référence \a const sur le voisinage de la cellule qui est un \a vector de pointeurs de type \a Cell pointant chacun sur une cellule voisine de la cellule.
         */
    std::vector<Cell*> const& GetVoisins() const
    {
        return m_voisins;
    }

        /*!
         * \brief Accesseur en lecture de l'attribut \a m_etat
         *
         * \details Méthode permettant de récupérer un entier représentant l'état d'une cellule.
         * \return Entier représentant l'état de la cellule.
         */
    int GetEtat() const
    {
        return m_etat;
    }
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_x
         *
         * \details Méthode permettant de récupérer un entier représentant la position en X d'une cellule (sur la ligne).
         * \return Entier représentant la position en X d'une cellule (sur la ligne).
         */
    int GetX() const { return m_x; }
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_y
         *
         * \details Méthode permettant de récupérer un entier représentant la position en Y d'une cellule (sur la colonne).
         * \return Entier représentant la position en Y d'une cellule (sur la colonne).
         */
    int GetY() const { return m_y; }
        /*!
         * \brief Modification de l'état d'une cellule
         * \param etat Paramètre de type \a int étant la  nouvelle valeur représentant l'état de la cellule.
         * \details Accesseur en écriture permettant de modifier l'état d'une cellule.
         */
    void SetEtat(int etat);
        /*!
         * \brief Ajout d'un voisin dans le voisinage de la cellule
         * \param voisin Paramètre de type \a Cell*, un pointeur sur la cellule voisine à ajouter.
         * \details Méthode permettant l'ajout d'une nouvelle cellule dans l'attribut \a m_voisins, qui est un \a vector, à l'aide de la fonction \a push_back.
         */
    void AjouterVoisin(Cell *voisin);
        /*!
         * \brief Suppression du voisinage d'une cellule
         * \details Méthode permettant de supprimer le voisinage \a m_voisins d'une cellule à l'aide de la fonction \a clear() de la bibliothèque standard. Celle-ci permet de supprimer tous les éléments contenus dans un \a vector, lui donnant une taille de 0.
         */
    void ClearVoisinage()
    {
        m_voisins.clear();
    }


private:
    /*!
     * \brief Destructeur par défaut de la classe Cell
     * \details Le destructeur par défaut est appelé lors de la destruction d'un objet \a Cell. En effet, les attributs de la classe ne sont pas alloués dynamiquement puisque le \a vector \a m_voisins est un tableau d'adresses et on ne supprime pas les voisins d'une cellule lorsqu'on la détruit.
     */
    ~Cell() = default;
    /*!
     * \brief Constructeur de la classe Cell
     * \sa Etat
     * \details Ce constructeur par défault de la classe Cell permet d'initialiser \a m_x, \a m_y et \a m_etat à 0. Le \a vector \a m_voisins est initialisé vide.
     * \warning Seule la classe Etat peut construire des Cell.
     */
    Cell() : m_etat(0), m_voisins(), m_x(0), m_y(0)
    {

    }
    /*!
     * \brief Constructeur de la classe Cell
     * \param etat Paramètre de type \a int étant la valeur représentant l'état de la cellule
     * \param x Paramètre de type \a int représentant la position de la cellule sur la ligne
     * \param y Paramètre de type \a int représentant la position de la cellule sur la colonne
     * \sa Etat
     * \details Constructeur de la classe Cell permettant d'initaliser les attributs \a m_etat, \a m_x et \a m_y d'une cellule avec les valeurs passées en paramètre.
     * \warning Seule la classe Etat peut construire des Cell.
     */
    Cell(int etat, int x, int y) : m_etat(etat), m_voisins(), m_x(x), m_y(y)
    {

    }
    /*!
     * \brief Constructeur de recopie de la classe Cell.
     * \param c Paramètre de type \a Cell \a const& étant une référence sur la cellule que l'on souhaite copier
     * \sa Etat
     * \details Ce constructeur de recopie de la classe Cell est celui par défaut.
     * \warning Seule la classe Etat peut construire des Cell.
     */
    Cell(Cell const& c) = default;
    /*!
     * \brief Modification de la position de la cellule sur la ligne
     * \param x Paramètre de type \a int représentant la nouvelle position de la cellule sur la ligne
     * \sa Etat
     *
     * Accesseur en écriture sur \a m_x. Seule la classe Etat peut l'utiliser car il est illogique d'affecter une position X en dehors d'une grille.
     * (Cet accesseur n'est pas nécessaire car la classe Etat pourrait modifier \a m_x directement étant donné qu'il s'agit d'une classe amie, mais nous avons pris la décision d'en faire une classe amie plus tard donc nous l'avons laissé afin de ne pas modifier à nouveau le code de la classe Etat.)
     */
    void SetX(int x);
    /*!
     * \brief Modification de la position de la cellule sur la colonne
     * \param y Paramètre de type \a int représentant la nouvelle position de la cellule sur la colonne
     * \sa Etat
     *
     * Accesseur en écriture sur \a m_y. Seule la classe Etat peut l'utiliser car il est illogique d'affecter une position Y en dehors d'une grille.
     * (Cet accesseur n'est pas nécessaire car la classe Etat pourrait modifier \a m_y directement étant donné qu'il s'agit d'une classe amie, mais nous avons pris la décision d'en faire une classe amie plus tard donc nous l'avons laissé afin de ne pas modifier à nouveau le code de la classe Etat.)
     */
    void SetY(int y);

    /*!
     * \brief Surcharge de l'opérateur d'affectation de la classe Cell avec celui par défaut
     * \param c Paramètre de type \a Cell \a const& étant une référence sur la cellule qui va être affectée à la cellule courante.
     */
    Cell& operator=(Cell const& c) = default;

    /*!
     * \brief Attribut de la classe Cell
     *
     * Cet attribut est de type \a int. Il représente l'état de la cellule.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    int m_etat;
    /*!
     * \brief Attribut de la classe Cell
     *
     * Cet attribut est de type < em>std::vector<Cell*>< /em>. Il contient les adresses des cellules comprises dans le voisinage de la cellule.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    std::vector<Cell*> m_voisins;
    /*!
     * \brief Attribut de la classe Cell
     *
     * Cet attribut est de type \a int. Il représente la position de la cellule sur la ligne.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    int m_x;
    /*!
     * \brief Attribut de la classe Cell
     *
     * Cet attribut est de type \a int. Il représente la position de la cellule sur la colonne.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    int m_y;


};

#endif // CELL_H
