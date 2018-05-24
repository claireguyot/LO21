#ifndef CABUILDER_H
#define CABUILDER_H
/*!
  * \file cabuilder.h
  * \brief Déclaration des classes CABuilder1D et CABuilder2D
*/

#include "cellularautomata.h"
/*!
 * \class CABuilder
 * \brief Classe de base qui permet de construire les sous-parties nécessaire à la construction d'un CellularAutomata
 *
 *
 * Les constructeurs et destructeurs des classes construitent ne sont pas en private car cette Classe permet juste de stocker les éléments nécessaire à la construction de CellularAutomate, ce n'est pas une fabrique à proprement parlé et il pourrait être possible de construire ces éléments autrement
 * Par exemple: la classe CellularAutomata construit des Etat. On aurait pu factoriser le code (héritage) des 2 Builder
 *
 * Cette classe n'est pas instanciable car elle ne sert qu'à "factoriser" du code commun à CABuilder1D et CABuilder2D pour éviter de copier coller le même morceau de code.
 * Mais elle n'est pas virtuelle pure (car toutes les méthodes sont bien définies et il est impossible de déclarer une méthode virtuelle pure qui pourra être utile à la fois dans CABuilder1D et CABuilder2D
 *
 * L'implémentation necessite de bloquer l'utilisation du simulateur lorsqu'on fait une modification du simulateur car quand on modifie une sous-partie on supprime l'ancienne
 *
 * \todo L'implémentation ne permet pas de pouvoir éxécuter plusieurs automates cellulaires différents en même temps
 * \todo Accesseur sur les éléments et méthodes permettant de construire les éléments
 */
class CABuilder
{
private:
    CABuilder(): m_etatDepart(nullptr),m_generateurEtat(nullptr),m_transitionRule(nullptr),m_voisinageDefinition(nullptr)
    {

    }
    virtual ~CABuilder()
    {
        delete m_etatDepart;
        delete m_generateurEtat;
        delete m_transitionRule;
        delete m_voisinageDefinition;
    }
    CABuilder(const CABuilder&) = delete;
    CABuilder& operator=(const CABuilder&) = delete;
    GenerateurEtat *m_generateurEtat;
    Etat *m_etatDepart;
    TransitionRule* m_transitionRule;
    Voisinage* m_voisinageDefinition;
public:
    Voisinage const& GetVoisinageDefinition() const {return *m_voisinageDefinition;}
    TransitionRule const& GetTransitionRule() const {return *m_transitionRule;}
    Etat const& GetEtatDepart() const{ return *m_etatDepart;}
    GenerateurEtat const& GetGenerateurEtat() const {return *m_generateurEtat}
    void BuildGenerateurEtatRandom() {
        if(m_generateurEtat != nullptr)
            delete m_generateurEtat;
        m_generateurEtat = new GenerateurRandom;
    }
    void BuildGenerateurEtatSymetrieAxeLargeur()
    {
        if(m_generateurEtat != nullptr)
            delete m_generateurEtat;
        m_generateurEtat = new GenerateurSymetrieAxeLargeur;
    }


}
/*!
 * \class CABuilder1D
 * \brief Classe permettant de construire toutes les sous-parties nécessaires à la construction d'un automate cellulaire 1D
 * \todo L'implémentation ne permet pas de pouvoir éxécuter plusieurs automates cellulaires différents en même temps
 *
 * Les constructeurs et destructeurs des classes construitent ne sont pas en private car cette Classe permet juste de stocker les éléments nécessaire à la construction de CellularAutomate, ce n'est pas une fabrique à proprement parlé et il pourrait être possible de construire ces éléments autrement
 * Par exemple: la classe CellularAutomata construit des Etat. On aurait pu factoriser le code (héritage) des 2 Builder
 *
 * C'est un singleton car dans notre application il est impossible de gérer plusieurs automates 1D en même temps
 * \todo modifier l'implémentation pour pouvoir gérer la construction de plusieurs automates en même temps
 *
 * \todo Accesseur sur les éléments et méthodes permettant de construire les éléments
 */

class CABuilder1D : public CABuilder
{
private:
    CABuilder1D() = default;
    ~CABuilder1D() = default;
    CABuilder1D(const CABuilder1D&) = delete;
    CABuilder1D& operator=(const CABuilder1D&) = delete;
public:
    static CABuilder1D& getInstance()
    {
            static CABuilder1D m;
            return m;
    }
    void BuildVoisinageDef(unsigned int ordre) {
        if (m_voisinageDefinition != nullptr && m_voisinageDefinition->GetOrdre() == ordre) return;
        if(m_voisinageDefinition != nullptr) delete m_voisinageDefinition;
        m_voisinageDefinition = new Voisinage1D(ordre);
    }
    void BuildEtatDepart(unsigned int taille, GenerateurEtat const& generateur,int nbEtats)
    {
        if(m_etatDepart != nullptr) delete m_etatDepart;
        m_etatDepart = new Etat(1,taille,generateur,nbEtats);
    }
    void BuildEtatDepart(unsigned int taille, vector<vector<int>> tab)
    {
        if(m_etatDepart != nullptr) delete m_etatDepart;
        m_etatDepart = new Etat(1,taille,tab);
    }
    void BuildEtatDepart(unsigned int taille)
    {
        if(m_etatDepart != nullptr) delete m_etatDepart;
        m_etatDepart = new Etat(1,taille);
    }
    void BuildElementaryRule(std::string& rule, unsigned int nbEtats)
    {
        if(m_transitionRule != nullptr) delete m_transitionRule;
        m_transitionRule = new ElementaryRule(rule,nbEtats)
    }


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
class CABuilder2D : CABuilder
{
private:
    CABuilder2D() = default;
    ~CABuilder2D() = default;
    CABuilder2D(const CABuilder2D&) = delete;
    CABuilder2D& operator=(const CABuilder2D&) = delete;
public:
    static CABuilder2D& getInstance()
    {
        static CABuilder2D m;
        return m;
    }
};

#endif // CABUILDER_H