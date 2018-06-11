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
     * \param indice Paramètre de type \a unsigned \a int représentant le nombre d'états du générateur d'états associé à l'état
     *
     * Cette méthode permet de revenir à l'état initial, et de remettre à 0 le générateur d'états associé à l'état avec le nombre d'états passé en paramètre.
     * L'interface laisse la possibilité de régénérer l'état initial uniquement si il y a une algorithme de génération.
     */
    void Build(unsigned int indice);
    /*CellularAutomata(const CellularAutomata& s);
    CellularAutomata& operator=(const CellularAutomata& s);*/
public:
    //CellularAutomata( TransitionRule const* rule, unsigned int buffer = 2);
    CellularAutomata(unsigned int nbEtats,const Etat *dep = nullptr, const TransitionRule *rule = nullptr, const Voisinage *definitionVoisinage=nullptr, unsigned int buffer = 2);
    void setEtatDepart(const Etat &dep);
    Etat const* getEtatDepart() const {return m_depart;}
    void Run(unsigned int nbSteps); // génère les n prochains états
    void Next(); // génère le prochain état
    const Etat& Dernier() const;
    unsigned int GetRangDernier() const { return m_rang; }
    unsigned int GetNombreEtats() const { return m_nbEtats; }
    void Reset(); // revenir à l'état de départ
    const TransitionRule* getTransition() const { return m_rule;}
    const Voisinage* getVoisinage() const { return m_voisinageDefinition;}
    void setRule(const TransitionRule &rule);
    void setVoisinageDefinition(const Voisinage &voisinage);
    ~CellularAutomata();

};

#endif // CELLULARAUTOMATA_H
