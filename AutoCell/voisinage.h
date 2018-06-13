#ifndef VOISINAGE_H
#define VOISINAGE_H

/*!
 * \file voisinage.h
 * \brief Déclaration des classes Voisinage, Voisinage1D, VonNeumann et Moore, et définition de leurs méthodes inline
 */

#include "etat.h"

/*! \class Voisinage
  * \brief Classe abstraite représentant le voisinage d'une cellule de type \a Cell
  * \sa Cell, Etat
  * \details Cette classe permet de construire le voisinage de chaque cellule de type \a Cell d'un état de type \a Etat.
  */
class Voisinage
{
protected:
    /*!
     * \brief Attribut de la classe Voisinage
     *
     * Cet attribut est de type \a int. Il représente la distance maximale entre la cellule courante et une cellule voisine. Il est au minimum de 1.
     * Par exemple : si l'ordre est de 2, le voisinage comprendra la cellule courante ainsi que ses deux cellules voisines de chaque côté (selon de type de voisinage bien évidemment).
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_ordre;
public:
        /*!
         * \brief Constructeur de la classe Voisinage
         * \param ordre Paramètre de type \a int permettant d'initialiser l'attribut \a m_ordre
         *
         * Ce constructeur permet d'initialiser l'attribut \a m_ordre avec la valeur passée en paramètre.
         */
    Voisinage(unsigned int ordre): m_ordre(ordre)
    {

    }
        /*!
         * \brief Destructeur de la classe Voisinage
         *
         * Destructeur virtuel de la classe Voisinage, qui est celui par défaut.
         */
    virtual ~Voisinage() = default;
        /*!
         * \brief Méthode de la classe Voisinage
         * \param e Paramètre de type \a Etat& étant une référence sur l'état pour lequel on veut définir le voisinage de chaque cellule de type \a Cell
         * \sa Voisinage1D, VonNeumann, Moore
         *
         * Cette méthode virtuelle pure permet de définir le voisinage de chaque cellule contenue dans l'état passé en paramètre. Le voisinage est centré sur le cellule courante.
         */
    virtual void definirVoisinage(Etat& e) const = 0;
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_ordre
         *
         * \details Méthode permettant de récupérer un \a unsigned \a int représentant l'ordre du voisinage.
         * \return \a Unsigned \a int représentant l'ordre du voisinage.
         */
    unsigned int GetOrdre() const { return m_ordre; }
        /*!
         * \brief Méthode permettant de retourner le type de voisinage
         * \sa sauvegarde.h, sauvegarde.cpp
         *
         * \details Méthode virtuelle pure permettant de récupérer un \a std::string contenant le nom du type de voisinage. Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * \return \a std::string contenant le nom du type de voisinage
         */
    virtual std::string getType() const {return "";}
};


/*! \class Voisinage1D
  * \brief Classe représentant le voisinage d'une cellule de type \a Cell dans un automate cellulaire 1D
  * \sa Cell, Etat, Voisinage
  * \details Cette classe permet de construire le voisinage de chaque cellule de type \a Cell d'un état de type \a Etat, dans un automate cellulaire 1D.
  */
class Voisinage1D : public Voisinage
{
public:
        /*!
         * \brief Constructeur de la classe Voisinage1D
         * \param ordre Paramètre de type \a int permettant d'initialiser l'attribut \a m_ordre
         *
         * Ce constructeur fait appel au constructeur de Voisinage qui permet d'initialiser l'attribut \a m_ordre avec la valeur passée en paramètre.
         */
    Voisinage1D(unsigned int ordre) : Voisinage(ordre)
    {

    }
        /*!
         * \brief Destructeur de la classe Voisinage1D
         *
         * Destructeur virtuel de la classe Voisinage1D, qui est celui par défaut.
         */
    ~Voisinage1D() = default;
        /*!
         * \brief Méthode de la classe Voisinage1D
         * \param e Paramètre de type \a Etat& étant une référence sur l'état pour lequel on veut définir le voisinage de chaque cellule de type \a Cell
         * \sa Voisinage
         *
         * Cette méthode permet de définir le voisinage de chaque cellule contenue dans l'état passé en paramètre. Le voisinage est centré sur le cellule courante.
         * Ainsi, il y a autant de  voisins à gauche qu'à droite si cela est possible, sinon il y a uniquement les voisins d'un seul côté (\a ex: sur les bords de la grille).
         * Le mot-clé \a final permet d'empêcher cette méthode d'être utilisée par les autres classes filles de Voisinage.
         */
    void definirVoisinage(Etat &e) const final;
        /*!
         * \brief Méthode permettant de retourner le type de voisinage
         * \sa sauvegarde.h, sauvegarde.cpp
         *
         * \details Méthode permettant de récupérer un \a std::string contenant le nom du type de voisinage (ici \a "voisinage1D"). Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * \return \a std::string contenant le nom du type de voisinage
         */
    std::string getType() const {return "voisinage1D";}
};


/*! \class VonNeumann
  * \brief Classe représentant un voisinage en croix d'une cellule de type \a Cell dans un automate cellulaire 2D
  * \sa Cell, Etat, Voisinage
  * \details Cette classe permet de construire le voisinage en croix de chaque cellule de type \a Cell d'un état de type \a Etat, dans un automate cellulaire 2D.
  */
class VonNeumann : public Voisinage
{
public:
        /*!
         * \brief Constructeur de la classe VonNeumann
         * \param ordre Paramètre de type \a int permettant d'initialiser l'attribut \a m_ordre
         *
         * Ce constructeur fait appel au constructeur de Voisinage qui permet d'initialiser l'attribut \a m_ordre avec la valeur passée en paramètre.
         */
    VonNeumann(unsigned int ordre): Voisinage(ordre)
    {

    }
        /*!
         * \brief Destructeur de la classe VonNeumann
         *
         * Destructeur virtuel de la classe VonNeumann, qui est celui par défaut.
         */
    ~VonNeumann() = default;
        /*!
         * \brief Méthode de la classe VonNeumann
         * \param e Paramètre de type \a Etat& étant une référence sur l'état pour lequel on veut définir le voisinage de chaque cellule de type \a Cell
         * \sa Voisinage
         *
         * Cette méthode permet de définir le voisinage en croix de chaque cellule contenue dans l'état passé en paramètre. Le voisinage est centré sur le cellule courante.
         * Ainsi, il y a autant de  voisins à gauche qu'à droite qu'en haut et qu'en bas si cela est possible, sinon il y a uniquement les voisins d'un seul côté, d'en haut et d'en bas (\a ex: sur les bords de la grille).
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void definirVoisinage(Etat &e) const override;
        /*!
         * \brief Méthode permettant de retourner le type de voisinage
         * \sa sauvegarde.h, sauvegarde.cpp
         *
         * \details Méthode permettant de récupérer un \a std::string contenant le nom du type de voisinage (ici \a "VonNeumann"). Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * \return \a std::string contenant le nom du type de voisinage
         */
    std::string getType() const {return "VonNeumann";}
};


/*! \class Moore
  * \brief Classe représentant un voisinage en carré d'une cellule de type \a Cell dans un automate cellulaire 2D
  * \sa Cell, Etat, Voisinage
  * \details Cette classe permet de construire le voisinage en carré de chaque cellule de type \a Cell d'un état de type \a Etat, dans un automate cellulaire 2D.
  */
class Moore : public Voisinage
{
public:
        /*!
         * \brief Constructeur de la classe Moore
         * \param ordre Paramètre de type \a int permettant d'initialiser l'attribut \a m_ordre
         *
         * Ce constructeur fait appel au constructeur de Voisinage qui permet d'initialiser l'attribut \a m_ordre avec la valeur passée en paramètre.
         */
    Moore(unsigned int ordre): Voisinage(ordre)
    {

    }
        /*!
         * \brief Destructeur de la classe Moore
         *
         * Destructeur virtuel de la classe Moore, qui est celui par défaut.
         */
    ~Moore() = default;
        /*!
         * \brief Méthode de la classe Moore
         * \param e Paramètre de type \a Etat& étant une référence sur l'état pour lequel on veut définir le voisinage de chaque cellule de type \a Cell
         * \sa Voisinage
         *
         * Cette méthode permet de définir le voisinage en carré de chaque cellule contenue dans l'état passé en paramètre. Le voisinage est centré sur le cellule courante.
         * Ainsi, il y a autant de  voisins à gauche qu'à droite qu'en haut et qu'en bas si cela est possible, sinon il y a uniquement les voisins d'un seul côté, d'en haut et d'en bas (\a ex: sur les bords de la grille).
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void definirVoisinage(Etat &e) const override;
        /*!
         * \brief Méthode permettant de retourner le type de voisinage
         * \sa sauvegarde.h, sauvegarde.cpp
         *
         * \details Méthode permettant de récupérer un \a std::string contenant le nom du type de voisinage (ici \a "Moore"). Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * \return \a std::string contenant le nom du type de voisinage
         */
    std::string getType() const {return "Moore";}
};
#endif // VOISINAGE_H

