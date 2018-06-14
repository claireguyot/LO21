#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

/*!
 * \file cellularautomata.h
 * \brief Déclaration de la classe CellularAutomata et définition de ses méthodes inline
 */

#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"

/*! \class CellularAutomata
  * \brief Classe représentant un automate cellulaire
  * \sa Etat, TransitionRule, Voisinage
  *
  * Cette classe permet de construire des automates qu'ils soient 1D ou 2D en leur associant une règle de transition, un voisingage particulier choisi par l'utilisateur, et un tableau contenant l'ensemble des états générés.
  */
class CellularAutomata
{
private:
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a const \a TransitionRule*. Il s'agit d'un pointeur sur la règle de transition associée à l'automate.
     * Cet attribut ne sera pas détruit lors de la destruction de l'automate puisque la règle de transition peut exister sans l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    const TransitionRule* m_rule;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a const \a Voisinage*. Il s'agit d'un pointeur sur le type de voisinage associé à l'automate.
     * Cet attribut ne sera pas détruit lors de la destruction de l'automate puisque le type de voisinage peut exister sans l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    const Voisinage* m_voisinageDefinition;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a Etat**. Il s'agit d'un tableau contenant l'ensemble des états générés et associés à l'automate.
     * Cet attribut sera détruit lors de la destruction de l'automate puisque cet ensemble d'états générés est propre à l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    Etat** m_etats;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a const \a Etat*. Il s'agit d'un pointeur sur l'état de départ associé à l'automate.
     * Cet attribut ne sera pas détruit lors de la destruction de l'automate puisque cet état peut exister sans l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    const Etat* m_depart;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre d'états possibles pour une cellule, associé à l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_nbEtats;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre maximum d'états générés qui peuvent être stockés dans \a m_etats, associé à l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_buffer;
    /*!
     * \brief Attribut de la classe CellularAutomata
     *
     * Cet attribut est de type \a unsigned \a int. Il représente le nombre d'états générés dans \a m_etats, associé à l'automate.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_rang;
    /*!
     * \brief Méthode de la classe CellularAutomata
     * \param indice Paramètre de type \a unsigned \a int représentant l'indice du tableau d'états générés \a m_etats où construire une nouvelle itération de l'automate, c'est-à-dire un nouvel état dans le tableau
     *
     * Cette méthode permet de construire un nouvel état dans le tableau des états générés \a m_etats associé à l'automate, à l'indice passé en paramètre.
     * Si l'état de départ a été changé, notamment en longueur ou en largeur, il est nécessaire de construire un nouvel état sur le modèle du nouvel état de départ dans le tableau des états générés \a m_etats.
     * De plus, le voisinage associé à un automate est lié à la grille d'états générés donc lorsque la grille est recréée, il est nécessaire de recréer le voisinage de toute la grille. Ainsi, il est important que le buffer ne soit pas trop grand, pour que cela ne prenne ni trop de temps ni trop d'espace mémoire.
     */
    void Build(unsigned int indice);
    /*CellularAutomata(const CellularAutomata& s);
    CellularAutomata& operator=(const CellularAutomata& s);*/
public:
    //CellularAutomata( TransitionRule const* rule, unsigned int buffer = 2);
        /*!
         * \brief Constructeur de la classe CellularAutomata
         * \param nbEtats Paramètre de type \a unsigned \a int représentant le nombre d'états possibles pour une cellule, associé à l'automate
         * \param dep Paramètre de type \a const \a Etat* étant un pointeur sur un état qui est l'état de départ de l'automate; il est à \a nullptr par défaut
         * \param rule Paramètre de type \a const \a TransitionRule* étant un pointeur sur la règle de transition associée à l'automate; il est à \a nullptr par défaut
         * \param definitionVoisinage Paramètre de type \a const \a Voisinage* étant un pointeur sur le type de voisinage associé à l'automate; il est à \a nullptr par défaut
         * \param buffer Paramètre de type \a unsigned \a int représentant le nombre maximum d'états générés qui peuvent être stockés dans \a m_etats, associé à l'automate; il est à 2 par défaut
         * \sa Cell
         *
         * Constructeur de la classe CellularAutomata permettant d'initaliser les attributs \a m_nbEtats, \a m_depart, \a m_rule, \a m_voisinageDefinition et \a m_buffer d'un automate avec les valeurs passées en paramètre.
         * L'attribut \a m_etats sera initialisé à l'aide de \a buffer pour définir la taille du tableau 2D. Les voisinages de tous les états du tableau sont initialisés à l'aide de \a definitionVoisinage par la même occasion, et le premier état de \a m_etats est initialisé avec l'état de départ à l'aide de \a dep.
         */
    CellularAutomata(unsigned int nbEtats,const Etat *dep = nullptr, const TransitionRule *rule = nullptr, const Voisinage *definitionVoisinage=nullptr, unsigned int buffer = 2);
        /*!
         * \brief Accesseur en écriture de l'attribut \a m_depart
         *
         * \details Méthode permettant d'associer un nouvel état de départ à un automate à partir du \a const& \a Etat passé en paramètre. Elle fait appel à la fonction \a Reset() une fois \a m_depart modifié.
         */
    void setEtatDepart(const Etat &dep);
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_depart
         *
         * \details Méthode permettant de récupérer un \a Etat \a const* pointant sur l'état de départ associé à l'automate.
         * \return \a Etat \a const* pointant sur l'état de départ associé à l'automate.
         */
    Etat const* getEtatDepart() const {return m_depart;}
        /*!
         * \brief Méthode de la classe CellularAutomata
         * \param nbSteps Paramètre de type \a unsigned \a int représentant le nombre d'états que l'on veut générer
         *
         * Cette méthode permet de généré les \a nbSteps états suivants de l'automate dans \a m_etats à l'aide de la fonction \a Next().
         */
    void Run(unsigned int nbSteps); // génère les n prochains états
        /*!
         * \brief Méthode de la classe CellularAutomata
         *
         * Cette méthode permet de généré l'état suivant de l'automate dans \a m_etats à l'aide des fonctions \a Build() et \a EffectuerTransition() de Etat.
         * \a Build() permet de construire un nouvel état vierge dans \a m_etats, et \a EffectuerTransition() permet de mettre à jour ce nouvel état comme étant l'état suivant le dernier état généré par l'automate.
         */
    void Next(); // génère le prochain état
        /*!
         * \brief Méthode de la classe CellularAutomata
         *
         * Cette méthode permet de renvoyer le dernier état généré par l'automate dans \a m_etats.
         */
    const Etat& Dernier() const;
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_rang
         *
         * \details Méthode permettant de récupérer un \a unsigned \a int représentant le numéro du dernier état généré dans le tableau \a m_etats associé à l'automate.
         * \return \a Unsigned \a int représentant le numéro du dernier état généré dans le tableau \a m_etats associé à l'automate.
         */
    unsigned int GetRangDernier() const { return m_rang; }
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_nbEtats
         *
         * \details Méthode permettant de récupérer un \a unsigned \a int représentant le nombre d'états possibles pour une cellule, associé à l'automate.
         * \return \a Unsigned \a int représentant le nombre d'états possibles pour une cellule, associé à l'automate.
         */
    unsigned int GetNombreEtats() const { return m_nbEtats; }
        /*!
         * \brief Méthode de la classe CellularAutomata
         *
         * Cette méthode permet de remettre l'automate à 0, c'est-à-dire à son état de départ \a m_depart associé.
         * Cette méthode nécessite notamment de redéfinir le voisinage pour cet état de départ dans \a m_etats à l'aide du voisinage \a m_voisinageDefinition associé à l'automate.
         */
    void Reset(); // revenir à l'état de départ
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_rule
         *
         * \details Méthode permettant de récupérer un \a const \a TransitionRule* étant un pointeur sur la règle de transition associée à l'automate.
         * \return \a Const \a TransitionRule* étant un pointeur sur la règle de transition associée à l'automate.
         */
    const TransitionRule* getTransition() const { return m_rule;}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_voisinageDefinition
         *
         * \details Méthode permettant de récupérer un \a const \a Voisinage* étant un pointeur sur le type de voisinage associé à l'automate.
         * \return \a Const \a Voisinage* étant un pointeur sur le type de voisinage associé à l'automate.
         */
    const Voisinage* getVoisinage() const { return m_voisinageDefinition;}
        /*!
         * \brief Accesseur en écriture de l'attribut \a m_rule
         *
         * \details Méthode permettant d'associer une nouvelle règle de transition à un automate à partir de la \a const \a TransitionRule& passée en paramètre.
         */
    void setRule(const TransitionRule &rule);
        /*!
         * \brief Accesseur en écriture de l'attribut \a m_voisinageDefinition
         *
         * \details Méthode permettant d'associer un nouveau type de voisinage à un automate à partir du \a const \a Voisinage& passé en paramètre. Elle permet également de modifier le voisinage de tous les états contenus dans \a m_etats avec le nouveau type de voisinage.
         */
    void setVoisinageDefinition(const Voisinage &voisinage);
        /*!
         * \brief Destructeur de la classe CellularAutomata
         *
         * Le destructeur est appelé lors de la destruction d'un objet \a CellularAutomata.
         * Il permet de supprimer les attributs automatiques \a m_nbEtats, \a m_buffer et \a m_rang, et de désallouer la mémoire pour l'attribut \a m_états alloué dynamiquement.
         * L'état de départ \a m_depart, la règle de transition \a m_rule et le voisinage \a m_voisinageDefinition ne sont pas supprimés puisqu'ils subsistent après la destruction de l'objet \a CellularAutomata.
         */
    ~CellularAutomata();

};

#endif // CELLULARAUTOMATA_H
