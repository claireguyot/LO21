#ifndef CABUILDER_H
#define CABUILDER_H
/*!
  * \file cabuilder.h
  * \brief Déclaration des classes CABuilder1D et CABuilder2D
*/

#include "cellularautomata.h"
/*!
 * \class CABuilder1D
 * \brief Classe permettant de construire toutes les sous-parties nécessaires à la construction d'un automate cellulaire 1D
 * \todo L'implémentation ne permet pas de pouvoir éxécuter plusieurs automates cellulaires différents en même temps
 *
 * Les constructeurs et destructeurs des classes construitent ne sont pas en private car cette Classe permet juste de stocker les éléments nécessaire à la construction de CellularAutomate, ce n'est pas une fabrique à proprement parlé et il pourrait être possible de construire ces éléments autrement
 * Par exemple: la classe CellularAutomata construit des Etat. On aurait pu factoriser le code (héritage) des 2 Builder
 *
 * C'est un singleton
 *
 * \todo Accesseur sur les éléments et méthodes permettant de construire les éléments
 */

class CABuilder1D
{
private:
    GenerateurEtat *m_generateurEtat;
    Etat *m_etatDepart;
    TransitionRule1D* m_transitionRule;
    Voisinage1D* m_voisinageDefinition;


    CABuilder1D(): m_etatDepart(nullptr),m_generateurEtat(nullptr),m_transitionRule(nullptr),m_voisinageDefinition(nullptr)
    {

    }
    ~CABuilder1D();
    CABuilder1D(const CABuilder1D&) = delete;
    CABuilder1D& operator=(const CABuilder1D&) = delete;
public:
    static CABuilder1D& getInstance();
};
#include "cellularautomata.h"
/*!
 * \class CABuilder2D
 * \brief Classe permettant de construire toutes les sous-parties nécessaires à la construction d'un automate cellulaire 2D
 * \todo L'implémentation ne permet pas de pouvoir éxécuter plusieurs automates cellulaires différents en même temps. On
 *
 * Les constructeurs et destructeurs des classes construitent ne sont pas en private car cette Classe permet juste de stocker les éléments nécessaire à la construction de CellularAutomate, ce n'est pas une fabrique à proprement parlé et il pourrait être possible de construire ces éléments autrement
 * Par exemple: la classe CellularAutomata construit des Etat.
 *
 *  C'est un singleton
 *
 * \todo Accesseur sur les éléments et méthodes permettant de construire les éléments
 */
class CABuilder2D
{
private:
    GenerateurEtat *m_generateurEtat;
    Etat *m_etatDepart;
    TransitionRule2D* m_transitionRule;
    Voisinage2D* m_voisinageDefinition;


    CABuilder2D(): m_etatDepart(nullptr),m_generateurEtat(nullptr),m_transitionRule(nullptr),m_voisinageDefinition(nullptr)
    {

    }
    ~CABuilder2D();
    CABuilder2D(const CABuilder2D&) = delete;
    CABuilder2D& operator=(const CABuilder2D&) = delete;
public:
    static CABuilder2D& getInstance();
};

#endif // CABUILDER_H
