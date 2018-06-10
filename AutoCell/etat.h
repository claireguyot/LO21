#ifndef ETAT_H
#define ETAT_H

/*!
 * \file etat.h
 * \brief Déclaration de la classe Etat et définition de ses méthodes inline
 */

#include "cell.h"

/*! \class GenerateurEtat
  * \brief Classe déclarée dans le fichier < em>"generateuretat.h"< /em>
  * \sa GenerateurEtat
  * \details Le déclaration de cette classe dans le fichier < em>"etat.h"< /em> est nécessaire afin de régler le problème de dépendance circulaire.
  */
class GenerateurEtat;

/*! \class Etat
  * \brief Classe représentant un état de la grille de cellules
  * \sa Cell, GenerateurEtat
  * \details Cette classe permet de construire des objets \a Cell. Un objet \a Etat est représenté par une longueur, une largeur, un tableau de \a Cell à deux entrées, et un générateur d'état.
  */
class Etat
{
public:
        /*!
         * \brief Constructeur de la classe Etat
         * \param largeur Paramètre de type \a unsigned \a int représentant la largeur de la grille Etat
         * \param longueur Paramètre de type \a unsigned \a int représentant la longueur de la grille Etat
         * \param générateur Paramètre de type \a GenerateurEtat \a const& représentant le générateur d'états associé à l'état
         * \param nbEtats Paramètre de type \a unsigned \a int représentant le nombre d'états du générateur d'états associé à l'état
         * \sa GenerateurEtat, Cell
         *
         * Constructeur de la classe Etat permettant d'initaliser les attributs \a m_largeur, \a m_longueur et \a m_generateur d'un état avec les valeurs passées en paramètre.
         * L'attribut \a m_cellules sera initialisé à l'aide de \a largeur et \a longueur pour définir la taille du tableau 2D. Les positions X et Y de chacun sont initialisées par la même occasion.
         * Le nombre d'états du générateur d'états n'est pas stocké dans \a Etat car cela ne concerne que la classe \a GenerateurEtat, il est stocké dans le simulateur à savoir \a GenerateurEtat.
         */
    Etat(unsigned int largeur, unsigned int longueur, GenerateurEtat const& generateur, unsigned int nbEtats );
        /*!
         * \brief Constructeur de la classe Etat
         * \param largeur Paramètre de type \a unsigned \a int représentant la largeur de la grille Etat
         * \param longueur Paramètre de type \a unsigned \a int représentant la longueur de la grille Etat
         * \param tab Paramètre de type \a int** représentant une grille de cellules de type \a Cell ayant un état représenté par un \a int
         * \sa Cell
         *
         * Constructeur de la classe Etat permettant d'initaliser les attributs \a m_largeur, \a m_longueur et \a m_cellules d'un état avec les valeurs passées en paramètre.
         * L'attribut \a m_cellules sera initialisé à l'aide de \a largeur et \a longueur pour définir la taille du tableau 2D. Les positions X et Y et l'état de chacune sont initialisés par la même occasion.
         */
    Etat(unsigned int largeur, unsigned int longueur, int** tab);
        /*!
         * \brief Constructeur de la classe Etat
         * \param largeur Paramètre de type \a unsigned \a int représentant la largeur de la grille Etat
         * \param longueur Paramètre de type \a unsigned \a int représentant la longueur de la grille Etat
         * \sa Cell
         *
         * Constructeur de la classe Etat permettant d'initaliser les attributs \a m_largeur et \a m_longueur d'un état avec les valeurs passées en paramètre.
         * L'attribut \a m_cellules sera initialisé à l'aide de \a largeur et \a longueur pour définir la taille du tableau 2D. Les positions X et Y de chacune sont initialisées par la même occasion.
         */
    Etat(unsigned int largeur, unsigned int longueur);
        /*!
         * \brief Constructeur de recopie de la classe Etat
         * \param e Paramètre de type \a Etat \a const& étant une référence sur l'état que l'on souhaite copier
         * \details Ce constructeur de recopie de la classe Etat permet de copier tous les éléments d'un état donné en paramètre et de les affecter à l'état courant, et ce notamment pour \a m_cellules qui est alloué dynamiquement.
         */
    Etat(Etat const& e);
        /*!
         * \brief Surcharge de l'opérateur d'affectation de la classe Etat
         * \param e Paramètre de type \a Etat \a const& étant une une référence sur l'état qui va être affecté à l'état courant
         *
         * Cet opérateur d'affectation de la classe Etat permet d'affecter tous les éléments d'un état donné en paramètre à l'état courant.
         * Notamment, pour \a m_cellules qui est alloué dynamiquement, si la taille de \a m_cellules n'est pas la même pour les deux états, la grille de cellules est redimensionnée avant d'être mise à jour avec les nouvelles valeurs contenues dans l'état passé en paramètre.
         */
    Etat& operator=(Etat const& e);
        /*!
         * \brief Méthode de la classe Etat
         * \param nbEtats Paramètre de type \a unsigned \a int représentant le nombre d'états du générateur d'états associé à l'état
         *
         * Cette méthode permet de revenir à l'état initial, et de remettre à 0 le générateur d'états associé à l'état avec le nombre d'états passé en paramètre.
         * L'interface laisse la possibilité de régénérer l'état initial uniquement si il y a une algorithme de génération.
         */
    void Regenerer(int nbEtats); //avec l'interface il faudra laisser la possibilité de regenerer l'etat initial uniquement si on a mis un algo de génération
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_longueur
         *
         * \details Méthode permettant de récupérer un \a unsigned \a int représentant la longueur de la grille de l'état.
         * \return \a Unsigned \a int représentant la longueur de la grille de l'état.
         */
    unsigned int GetLongueur() const { return m_longueur; }
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_largeur
         *
         * \details Méthode permettant de récupérer un \a unsigned \a int représentant la largeur de la grille de l'état.
         * \return \a Unsigned \a int représentant la largeur de la grille de l'état.
         */
    unsigned int GetLargeur() const { return m_largeur; }
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_cellules
         * \param i Paramètre de type \a unsigned \a int représentant la position en X de la cellule voulue (sur la ligne)
         * \param j Paramètre de type \a unsigned \a int représentant la position en Y de la cellule voulue (sur la colonne)
         * \sa AutomateException
         *
         * Méthode permettant de récupérer une \a Cell& à l'aide de sa position sur la grille d'état.
         * Si la cellule voulue n'est pas dans la grille, une exception est lancée à l'aide de la classe \a AutomateException.
         * \return \a Cell&, référence sur la cellule voulue.
         */
    Cell& GetCellule(unsigned int i, unsigned int j)  {
        if (i>=m_largeur || j>= m_longueur)
            throw AutomateException("Tentative d'accès à un élément hors grille");
        return m_cellules[i][j];}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_cellules
         * \param i Paramètre de type \a unsigned \a int représentant la position en X de la cellule voulue (sur la ligne)
         * \param j Paramètre de type \a unsigned \a int représentant la position en Y de la cellule voulue (sur la colonne)
         * \sa AutomateException
         *
         * Méthode permettant de récupérer une \a Cell& à l'aide de sa position sur la grille d'état.
         * Si la cellule voulue n'est pas dans la grille, une exception est lancée à l'aide de la classe \a AutomateException.
         * \return \a Cell \a const&, référence \a const sur la cellule voulue.
         */
    Cell const& GetCellule(unsigned int i, unsigned int j) const {
        if (i>=m_largeur || j>= m_longueur)
            throw AutomateException("Tentative d'accès à un élément hors grille");
        return m_cellules[i][j];}
        /*!
         * \brief Destructeur de la classe Etat
         *
         * Le destructeur est appelé lors de la destruction d'un objet \a Etat.
         * Il permet de supprimer les attributs automatiques \a m_largeur et \a m_longueur, et de désallouer la mémoire pour l'attribut \a m_cellules alloué dynamiquement.
         * Le générateur d'état associé \a m_generateur n'est pas supprimé puisqu'il subsite après la destruction de l'objet \a Etat.
         */
    ~Etat();
        /*!
         * \brief Méthode de la classe Etat
         *
         * Cette méthode permet d'afficher la grille de cellules de l'état. La couleur associée à l'état d'une cellule est attribuée au niveau de l'interface.
         */
    void afficher() const;

    friend class iterator;
    /*! \class iterator
      * \brief Classe déclarée au sein de la classe Etat
      * \sa Etat, const_iterator
      * Cette classe suit le Design Pattern \a Iterator et permet de parcourir séquentiellement toutes les cases de la grille d'un objet de type \a Etat.
      * Cette méthode n'est pas plus optimale que faire une boucle classique à l'aide de \a GetLongueur et \a GetLargeur, mais cela permet d'avoir une structure plus "universelle" pour parcourir la grille de l'état car cela ressemble à la bibliothèque standard.
      */
    class iterator {
        friend class Etat;
            /*!
             * \brief Attribut de la classe iterator
             *
             * Cet attribut est de type \a Etat*. Il s'agit d'un pointeur sur l'état courant de l'iterator.
             * Cet attribut ne sera pas détruit lors de la destruction de l'iterator puisque l'états peut exister sans l'iterator.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            Etat* etat;
            /*!
             * \brief Attribut de la classe iterator
             *
             * Cet attribut est de type \a int. Il représente la position de l'iterator sur la ligne de l'état courant.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            int i;
            /*!
             * \brief Attribut de la classe iterator
             *
             * Cet attribut est de type \a int. Il représente la position de l'iterator sur la colonne de l'état courant.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            int j;
            /*!
             * \brief Constructeur de la classe iterator
             * \param e Paramètre de type \a Etat* qui est un pointeur sur un objet de type \a Etat
             *
             * Ce constructeur permet d'initialiser les attributs d'un \a iterator \a i et \a j à 0, et \a etat à l'aide de l'état passé en paramètre.
             */
            iterator(Etat* e) :etat(e), i(0), j(0) {}
            /*!
             * \brief Constructeur de la classe iterator
             * \param e Paramètre de type \a Etat* qui est un pointeur sur un objet de type \a Etat
             * \param ligne Paramètre de type \a int qui représente la position de l'iterator sur la ligne de l'état
             * \param colonne Paramètre de type \a int qui représente la position de l'iterator sur la colonne de l'état
             *
             * Ce constructeur permet d'initialiser les attributs d'un \a iterator \a i, \a j et \a etat à l'aide des valeurs passées en paramètres.
             */
            iterator(Etat*e, int ligne, int colonne) :etat(e), i(ligne), j(colonne) {}

        public:
            /*!
             * \brief Destructeur de la classe iterator
             *
             * Ce destructeur permet de supprimer les attributs \a i et \a j qui sont automatiques. L'attribut \a etat n'est pas détruit puisqu'il subsiste quand un objet \a iterator est détruit.
             */
            ~iterator() = default;

            /*!
             * \brief Surcharge de l'opérateur d'incrémentation de la classe iterator
             *
             * Cet opérateur permet de passer à la cellule suivante dans la grille de l'état courant. Lorsque l'iterator arrive au bout d'une ligne de la grille, il passe à la ligne du dessous si elle existe.
             */
            iterator& operator++() {
                j++;
                if (j==etat->m_longueur && i<etat->m_largeur)
                {
                    j=0;
                    i++;
                }
                return *this;
            }
            /*!
             * \brief Surcharge de l'opérateur de référencement de la classe iterator
             *
             * Cet opérateur permet de retourner une référence sur la cellule de type \a Cell située à la position \a i et \a j sur la grille de l'état courant.
             */
            Cell& operator*() const {
                return etat->m_cellules[i][j];
            }
            /*!
             * \brief Surcharge de l'opérateur d'inégalité de la classe iterator
             * \param it Paramètre de type \a iterator qui fait l'objet d'une comparaison avec l'iterator courant
             *
             * Cet opérateur permet de retourner un booléen selon si l'iterator passé en paramètre est différent ou non de l'iterator courant en comparant chacun de leurs attributs entre eux.
             */
            bool operator!=(iterator it) const { return etat != it.etat || i != it.i || j != it.j; }
    };
        /*!
         * \brief Méthode de la classe iterator
         *
         * Cette méthode permet de retourner un \a iterator pointant sur la première case de la grille d'un objet \a Etat.
         */
    iterator begin() {	return iterator(this,0,0); }
        /*!
         * \brief Méthode de la classe iterator
         *
         * Cette méthode permet de retourner un \a iterator pointant sur la dernière case de la grille d'un objet \a Etat.
         */
    iterator end() {  return iterator(this, m_largeur,0);}

    friend class const_iterator;
    /*! \class const_iterator
      * \brief Classe déclarée au sein de la classe Etat
      * \sa Etat, iterator
      * Cette classe suit le Designe Pattern \a Iterator et permet de parcourir séquentiellement toutes les cases de la grille d'un objet de type \a const \a Etat.
      * Cette méthode n'est pas plus optimale que faire une boucle classique à l'aide de \a GetLongueur et \a GetLargeur, mais cela permet d'avoir une structure plus "universelle" pour parcourir la grille de l'état car cela ressemble à la bibliothèque standard.
      */
    class const_iterator {
        friend class Etat;
            /*!
             * \brief Attribut de la classe const_iterator
             *
             * Cet attribut est de type \a Etat*. Il s'agit d'un pointeur sur l'état courant du const_iterator.
             * Cet attribut ne sera pas détruit lors de la destruction du const_iterator puisque l'états peut exister sans le const_iterator.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            Etat const* etat;
            /*!
             * \brief Attribut de la classe iterator
             *
             * Cet attribut est de type \a int. Il représente la position du const_iterator sur la ligne de l'état courant.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            int i;
            /*!
             * \brief Attribut de la classe iterator
             *
             * Cet attribut est de type \a int. Il représente la position du const_iterator sur la colonne de l'état courant.
             * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
             */
            int j;
            /*!
             * \brief Constructeur de la classe const_iterator
             * \param e Paramètre de type \a Etat* qui est un pointeur sur un objet de type \a const \a Etat
             *
             * Ce constructeur permet d'initialiser les attributs d'un \a const_iterator \a i et \a j à 0, et \a etat à l'aide de l'état passé en paramètre.
             */
            const_iterator(Etat const* e) :etat(e), i(0), j(0) {}
            /*!
             * \brief Constructeur de la classe const_iterator
             * \param e Paramètre de type \a Etat* qui est un pointeur sur un objet de type \a Etat
             * \param ligne Paramètre de type \a int qui représente la position du const_iterator sur la ligne de l'état
             * \param colonne Paramètre de type \a int qui représente la position du const_iterator sur la colonne de l'état
             *
             * Ce constructeur permet d'initialiser les attributs d'un \a const_iterator \a i, \a j et \a etat à l'aide des valeurs passées en paramètres.
             */
            const_iterator(Etat const* e, int ligne, int colonne) :etat(e), i(ligne), j(colonne) {}

        public:
            /*!
             * \brief Destructeur de la classe const_iterator
             *
             * Ce destructeur permet de supprimer les attributs \a i et \a j qui sont automatiques. L'attribut \a etat n'est pas détruit puisqu'il subsiste quand un objet \a const_iterator est détruit.
             */
            ~const_iterator() = default;
            /*!
             * \brief Surcharge de l'opérateur d'incrémentation de la classe const_iterator
             *
             * Cet opérateur permet de passer à la case suivante dans la grille de l'état courant. Lorsque le const_iterator arrive au bout d'une ligne de la grille, il passe à la ligne du dessous si elle existe.
             */
            const_iterator & operator++() {
                j++;
                if (j==etat->m_longueur)
                {
                    j=0;
                    i++;
                }
                return *this;
            }
            /*!
             * \brief Surcharge de l'opérateur de référencement de la classe const_iterator
             *
             * Cet opérateur permet de retourner une référence \a const sur la cellule de type \a Cell \a const située à la position \a i et \a j sur la grille de l'état courant.
             */
            Cell const& operator*() const {
                return etat->m_cellules[i][j];
            }
            /*!
             * \brief Surcharge de l'opérateur d'inégalité de la classe const_iterator
             * \param it Paramètre de type \a const_iterator qui fait l'objet d'une comparaison avec le const_iterator courant
             *
             * Cet opérateur permet de retourner un booléen selon si le const_iterator passé en paramètre est différent ou non du const_iterator courant en comparant chacun de leurs attributs entre eux.
             */
            bool operator!=(const_iterator it) const { return etat != it.etat || i != it.i || j != it.j; }
    };
        /*!
         * \brief Méthode de la classe const_iterator
         *
         * Cette méthode permet de retourner un \a const_iterator pointant sur la première case de la grille d'un objet \a const \a Etat.
         */
    const_iterator begin() const {	return const_iterator(this,0,0); }
        /*!
         * \brief Méthode de la classe const_iterator
         *
         * Cette méthode permet de retourner un \a const_iterator pointant sur la dernière case de la grille d'un objet \a const \a Etat.
         */
    const_iterator end() const {  return const_iterator(this, m_largeur,0); }


private:
    /*!
     * \brief Attribut de la classe Etat
     *
     * Cet attribut est de type \a GenerateurEtat \a const*. Il s'agit d'un pointeur sur le générateur d'états associé à l'état.
     * Cet attribut ne sera pas détruit lors de la destruction de l'état puisque le générateur d'états peut exister sans l'état.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    GenerateurEtat const* m_generateur;
    /*!
     * \brief Attribut de la classe Etat
     *
     * Cet attribut est de type \a Cell**. Il représente un tableau 2D de cellules de type \a Cell, et les durées de vie des cellules sont liées à la durée de vie de la grille \a Etat.
     * Le type de cet attribut n'est pas \a Cell* car pour chaque grille, il est nécessaire d'avoir des cellules différentes. Ainsi, si on supprime une grille, les informations de celle-ci sont concervées.
     * De plus, comme l'on dispose d'un constructeur par défaut de la classe \a Cell, on peut utiliser \a Cell** au lieu de \a Cell* qui nous aurait obligés à utiliser \a Cell*** \a tab au lieu de \a Cell**.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    Cell** m_cellules;
    /*!
     * \brief Attribut de la classe Etat
     *
     * Cet attribut est de type \a unsigned \a int. Il représente la largeur de la grille de cellules de l'état.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_largeur;
    /*!
     * \brief Attribut de la classe Etat
     *
     * Cet attribut est de type \a unsigned \a int. Il représente la longueur de la grille de cellules de l'état.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_longueur;



};

#endif // ETAT_H
