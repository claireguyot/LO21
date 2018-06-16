#ifndef TRANSITIONRULE_H
#define TRANSITIONRULE_H

/*!
 * \file transitionrule.h
 * \brief Déclaration des classes TransitionRule, ElementaryRule, GameOfLife et FeuForet, et définition de leurs méthodes inline
 */

#include "etat.h"
#include <string>
#include <vector>

/*! \class TransitionRule
  * \brief Classe abstraite représentant une règle de transition pour un état
  * \sa Cell, Etat
  * \details Cette classe abstraite permet d'associer une règle de transition à un état.
  */
class TransitionRule
{
public:
        /*!
         * \brief Constructeur de la classe TransitionRule
         *
         * Constructeur de la classe abstraite TransitionRule, qui est celui par défaut.
         */
    TransitionRule() = default;
        /*!
         * \brief Méthode de la classe TransitionRule
         * \param depart Paramètre de type \a Etat \a const& représentant l'état de départ avant la transition
         * \param arrivee Paramètre de type \a Etat& représentant l'état d'arrivée après la transition
         * \sa Etat, TransitionCellule, ElementaryRule, GameOfLife, FeuForet
         *
         * Cette méthode virtuelle permet de parcourir la grille de cellules de l'état de départ et de modifier l'état de chaque cellule selon la règle de transition à l'aide de TransitionCellule propre à chaque type de transition (1D, Jeu de la Vie, Feu de Forêt).
         */
    virtual void EffectuerTransition(Etat const& depart, Etat& arrivee) const;
        /*!
         * \brief Méthode de la classe TransitionRule
         * \param depart Paramètre de type \a Cell \a const& représentant la cellule de départ avant la transition
         * \param arrivee Paramètre de type \a Cell& représentant la cellule d'arrivée après la transition
         * \sa Cell, TransitionCellule, ElementaryRule, GameOfLife, FeuForet
         *
         * Cette méthode virtuelle pure permet de modifier l'état de chaque cellule selon la règle de transition propre à chaque type de transition (1D, Jeu de la Vie, Feu de Forêt).
         */
    virtual void TransitionCellule(Cell const& depart, Cell& arrivee) const = 0;
        /*!
         * \brief Accesseur en lecture des attributs de la classe TransitionRule
         * \sa ElementaryRule, GameOfLife, FeuForet
         *
         * \details Méthode virtuelle permettant de récupérer un \a std::string contenant les attributs définissant la transition. Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * \return \a std::string contenant les attributs définissant la transition.
         */
    virtual std::string getTransition() const {return "";}
        /*!
         * \brief Destructeur de la classe TransitionRule
         *
         * Destructeur de la classe abstraite TransitionRule, qui est celui par défaut.
         */
    virtual ~TransitionRule()= default;
};


/*! \class ElementaryRule
  * \brief Classe héritant de TransitionRule représentant une règle de transition pour un état d'un automate 1D
  * \sa Cell, Etat, TransitionRule
  * \details Cette classe héritant de TransitionRule permet d'associer une règle de transition élémentaire à un état d'un automate élémentaire 1D.
  */
class ElementaryRule : public TransitionRule
{
public:
        /*!
         * \brief Méthode de la classe ElementaryRule
         * \param depart Paramètre de type \a Cell \a const& représentant la cellule de départ avant la transition
         * \param arrivee Paramètre de type \a Cell& représentant la cellule d'arrivée après la transition
         * \sa Cell, TransitionCellule, TransitionRule, GameOfLife, FeuForet
         *
         * Cette méthode permet de modifier l'état de chaque cellule selon la règle de transition (donnée par l'utilisateur et stockée dans \a m_rule) et selon le nombre de voisins vivants ou morts.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
        /*!
         * \brief Constructeur de la classe ElementaryRule
         * \param rule Paramètre de type \a std::string représentant le nom de la règle de transition
         * \param nbEtats Paramètre de type \a unsigned \a int représentant le nombre d'états possibles pour les cellules de l'automate 1D
         *
         * Ce constructeur de la classe ElementaryRule permet d'initialiser \a m_rule et \a m_nbEtats avec les valeurs passées en paramètre.
         */
    ElementaryRule(std::string rule, unsigned int nbEtats) : TransitionRule(), m_rule(rule), m_nbEtats(nbEtats)
    {
        if (m_nbEtats>10) throw AutomateException("Erreur: nombre d'etats de la regle élementaire > 10 , cela n'est pas pris en charge");
    }
        /*!
         * \brief Accesseur en lecture des attributs de la classe ElementaryRule
         * \sa TransitionRule, GameOfLife, FeuForet
         *
         * Méthode permettant de récupérer un \a std::string contenant les attributs définissant la transition. Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         * \return \a std::string contenant les attributs définissant la transition.
         */
    std::string getTransition() const override;
        /*!
         * \brief Destructeur de la classe ElementaryRule
         *
         * Destructeur de la classe ElementaryRule, qui est celui par défaut.
         */
    ~ElementaryRule() = default;
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_rule
         *
         * Méthode permettant de récupérer un \a std::string contenant la règle entrée par l'utilisateur et stockée dans \a m_rule.
         * \return \a std::string contenant les attributs définissant la transition.
         */
    std::string const& GetRule() const {return m_rule;}
private:
    /*!
     * \brief Attribut de la classe ElementaryRule
     *
     * Cet attribut est de type \a std::string. Il représente la chaîne de caractères (0 ou 1) définissant la règle de transition.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    std::string m_rule;
    /*!
     * \brief Attribut de la classe ElementaryRule
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre d'états possibles pour les cellules de l'automate 1D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_nbEtats;
};


/*! \class GameOfLife
  * \brief Classe héritant de TransitionRule représentant une règle de transition pour un état d'un automate 2D
  * \sa Cell, Etat, TransitionRule
  * \details Cette classe héritant de TransitionRule permet d'associer une règle de transition à un état d'un automate 2D du Jeu de la Vie.
  */
class GameOfLife : public TransitionRule //nombre d'Etats forcément = à 2 !!!!!!!!
{
public:
        /*!
         * \brief Méthode de la classe GameOfLife
         * \param depart Paramètre de type \a Cell \a const& représentant la cellule de départ avant la transition
         * \param arrivee Paramètre de type \a Cell& représentant la cellule d'arrivée après la transition
         * \sa Cell, TransitionCellule, TransitionRule, ElementaryRule, FeuForet
         *
         * Cette méthode permet de modifier l'état de chaque cellule selon la règle de transition du Jeu de la Vie, selon le nombre de voisins vivants minimum pour qu'une cellule survive, selon le nombre de voisins vivants maximum pour qu'une cellule survive, et selon le nombre de voisins vivants ou morts.
         * La règle de transition est la suivante :
         * - si la cellule est entouré d'un nombre de voisins compris entre \a m_minVoisinsVivants et \a m_maxVoisinsVivants, la cellule survit, ou nait si elle était morte
         * - si la cellule est entouré d'un nombre de voisins inférieur à \a m_minVoisinsVivants ou supérieur à \a m_maxVoisinsVivants, la cellule meurt, ou ne nait pas si elle était morte
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
        /*!
         * \brief Constructeur de la classe GameOfLife
         * \param minVoisinsVivants Paramètre de type \a unsigned \a int représentant le nombre de voisins vivants minimum pour qu'une cellule survive
         * \param maxVoisinsVivants Paramètre de type \a unsigned \a int représentant le nombre de voisins vivants maximum pour qu'une cellule survive
         *
         * Ce constructeur de la classe GameOfLife permet d'initialiser \a m_minVoisinsVivants et \a m_maxVoisinsVivants avec les valeurs passées en paramètre.
         */
    GameOfLife(unsigned int minVoisinsVivants,unsigned int maxVoisinsVivants ) : TransitionRule(), m_minVoisinsVivants(minVoisinsVivants), m_maxVoisinsVivants(maxVoisinsVivants)
    {

    }
        /*!
         * \brief Accesseur en lecture des attributs de la classe GameOfLife
         * \sa TransitionRule, ElementaryRule, FeuForet
         *
         * Méthode permettant de récupérer un \a std::string contenant les attributs définissant la transition. Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         * \return \a std::string contenant les attributs définissant la transition.
         */
    std::string getTransition() const override;
        /*!
         * \brief Destructeur de la classe GameOfLife
         *
         * Destructeur de la classe GameOfLife, qui est celui par défaut.
         */
    ~GameOfLife() = default;
private:
    /*!
     * \brief Attribut de la classe GameOfLife
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre de voisins vivants minimum pour qu'une cellule survive.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_minVoisinsVivants;
    /*!
     * \brief Attribut de la classe GameOfLife
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre de voisins vivants maximum pour qu'une cellule survive.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_maxVoisinsVivants;
};


/*! \class FeuForet
  * \brief Classe héritant de TransitionRule représentant une règle de transition pour un état d'un automate 2D
  * \sa Cell, Etat, TransitionRule
  * \details Cette classe héritant de TransitionRule permet d'associer une règle de transition à un état d'un automate 2D du Feu de Forêt.
  */
class FeuForet : public TransitionRule //nombre d'Etats forcément = à 4 !!!!!!!!
{
public:
        /*!
         * \brief Méthode de la classe FeuForet
         * \param depart Paramètre de type \a Cell \a const& représentant la cellule de départ avant la transition
         * \param arrivee Paramètre de type \a Cell& représentant la cellule d'arrivée après la transition
         * \sa Cell, TransitionCellule, TransitionRule, ElementaryRule, GameOfLife
         *
         * Cette méthode permet de modifier l'état de chaque cellule selon la règle de transition du Feu de Foret qui est :
         * - une cellule Vide reste Vide
         * - une cellule Cendre reste Cendre
         * - une cellule Feu devient Cendre
         * - une cellule Arbre :
         *      - devient Feu si un de ses voisins est en Feu
         *      - reste Arbre sinon.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
        /*!
         * \brief Constructeur de la classe FeuForet
         *
         * Constructeur de la classe FeuForet, qui est celui par défaut.
         */
    FeuForet() = default;
        /*!
         * \brief Accesseur en lecture des attributs de la classe FeuForet
         * \sa TransitionRule, ElementaryRule, GameOfLife
         *
         * Méthode permettant de récupérer un \a std::string contenant les attributs définissant la transition. Cette méthode est utilisée seulement dans le cadre de la sauvegarde.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         * \return \a std::string contenant les attributs définissant la transition.
         */
    std::string getTransition() const override;
        /*!
         * \brief Destructeur de la classe FeuForet
         *
         * Destructeur de la classe FeuForet, qui est celui par défaut.
         */
    ~FeuForet() = default;
};

#endif // TRANSITIONRULE_H
