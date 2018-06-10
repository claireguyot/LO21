#ifndef GENERATEURETAT_H
#define GENERATEURETAT_H

/*!
 * \file generateuretat.h
 * \brief Déclaration des classes GenerateurEtat, GenerateurEtat et GenerateurSymetrieAxeVertical, représentant des algorithmes permettant de générer des Etats
 * \sa Etat, Cell
 *
 * Chaque algorithme permet d'affecter à chaque cellule de type \a Cell contenue dans un objet \a Etat, qui représente une grille de cellules, une valeur précise qui sera l'état de la cellule
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "etat.h"

/*! \class Etat
  * \brief Classe déclarée dans le fichier < em>"etat.h"< /em>
  * \sa Etat
  * \details Le déclaration de cette classe dans le fichier < em>"generateuretat.h"< /em> est nécessaire afin de régler le problème de dépendance circulaire.
  */
class Etat;


/*! \class GenerateurEtat
  * \brief Classe abstraite permettant de générer des états
  * \sa Etat
  *
  * Cette classe permet d'affecter à chaque cellule de type \a Cell contenue dans un objet \a Etat, qui représente une grille de cellules, une valeur qui sera l'état de la cellule.
  */
class GenerateurEtat
{
public:
        /*!
         * \brief Constructeur de la classe GenerateurEtat
         *
         * Constructeur de la classe GenerateurEtat, qui est celui par défaut.
         */
    GenerateurEtat() = default;
        /*!
         * \brief Constructeur de la classe GenerateurEtat
         * \sa GenerateurRandom, GenerateurSymetrieAxeVertical
         *
         * Constructeur virtuel pur de la classe GenerateurEtat.
         */
    virtual void GenererEtat(int nbEtats, Etat& grille) const = 0;
        /*!
         * \brief Destructeur de la classe GenerateurEtat
         *
         * Destructeur virtuel de la classe GenerateurEtat, qui est celui par défaut.
         */
    virtual ~GenerateurEtat()= default;
};


/*! \class GenerateurRandom
  * \brief Classe héritant de GenerateurEtat permettant de générer des états à partir d'un certain mode : aléatoire
  * \sa Etat
  *
  * Cette classe permet d'affecter à chaque cellule de type \a Cell contenue dans un objet \a Etat, qui représente une grille de cellules, une valeur aléatoire qui sera l'état de la cellule.
  */
class GenerateurRandom : public GenerateurEtat
{
public:
        /*!
         * \brief Constructeur de la classe GenerateurRandom
         *
         * Constructeur de la classe GenerateurRandom, qui est celui par défaut.
         */
    GenerateurRandom() = default;
        /*!
         * \brief Constructeur de la classe GenerateurRandom
         * \param nbEtats Paramètre de type \a int permettant de définir le nombre d'états possible pour une cellule
         * \param grille Paramètre de type \a Etat& étant une référence sur un état
         *
         * Constructeur de la classe GenerateurRandom, qui fait appel au constructeur de la classe mère GenererEtat.
         * Il permet de générer un état aléatoire, à l'aide de la fonction \a rand(), parmi ceux possibles pour chaque cellule contenue dans la \a grille.
         * La fonction < em>srand(time(NULL))< /em> permet de s'assurer que la séquence de chiffre aléatoire générée est différente à chaque fois que le constructeur est appelé.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void GenererEtat(int nbEtats, Etat& grille) const override;
        /*!
         * \brief Destructeur de la classe GenerateurRandom
         *
         * Destructeur de la classe GenerateurRandom, qui est celui par défaut.
         */
    ~GenerateurRandom() = default;
};


/*! \class GenerateurSymetrieAxeVertical
  * \brief Classe héritant de GenerateurEtat permettant de générer des états à partir d'un certain mode : symétrique selon l'axe vertical
  * \sa Etat
  *
  * Cette classe permet d'affecter à chaque cellule de type \a Cell contenue dans un objet \a Etat, qui représente une grille de cellules, une valeur aléatoire qui sera l'état de la cellule, selon une symétrique verticale.
  */
class GenerateurSymetrieAxeVertical : public GenerateurEtat
{
public:
        /*!
         * \brief Constructeur de la classe GenerateurSymetrieAxeVertical
         *
         * Constructeur de la classe GenerateurSymetrieAxeVertical, qui est celui par défaut.
         */
    GenerateurSymetrieAxeVertical() = default;
        /*!
         * \brief Constructeur de la classe GenerateurSymetrieAxeVertical
         * \param nbEtats Paramètre de type \a int permettant de définir le nombre d'états possible pour une cellule
         * \param grille Paramètre de type \a Etat& étant une référence sur un état
         *
         * Constructeur de la classe GenerateurSymetrieAxeVertical, qui fait appel au constructeur de la classe mère GenererEtat.
         * Il permet de générer un état aléatoire, à l'aide de la fonction \a rand(), parmi ceux possibles pour chaque cellule contenue dans la première moitié de la \a grille. La cellule située à la symétrie selon l'axe vertical de chacune des ces cellules est affectée avec le même état.
         * La fonction < em>srand(time(NULL))< /em> permet de s'assurer que la séquence de chiffre aléatoire générée est différente à chaque fois que le constructeur est appelé.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void GenererEtat(int nbEtats, Etat& grille) const override;
        /*!
         * \brief Destructeur de la classe GenerateurSymetrieAxeVertical
         *
         * Destructeur de la classe GenerateurSymetrieAxeVertical, qui est celui par défaut.
         */
    ~GenerateurSymetrieAxeVertical() = default;
};




#endif // GENERATEURETAT_H
