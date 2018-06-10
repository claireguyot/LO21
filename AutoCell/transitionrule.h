#ifndef TRANSITIONRULE_H
#define TRANSITIONRULE_H
#include "etat.h"
#include <string>
#include <vector>

class TransitionRule
{
public:
    TransitionRule() = default;
    virtual void EffectuerTransition(Etat const& depart, Etat& arrivee) const;
    virtual void TransitionCellule(Cell const& depart, Cell& arrivee) const = 0;
    virtual std::string getTransition() const {return "";}
    virtual unsigned int getNbEtats() const = 0;
    virtual ~TransitionRule()= default;
};



class ElementaryRule : public TransitionRule
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    ElementaryRule(std::string rule, unsigned int nbEtats) : TransitionRule(), m_rule(rule), m_nbEtats(nbEtats)
    {
        if (m_nbEtats>10) throw AutomateException("Erreur: nombre d'etats de la regle élementaire > 10 , cela n'est pas pris en charge");
    }
    std::string getTransition() const override;
    ~ElementaryRule() = default;
    std::string const& GetRule() const {return m_rule;}
    unsigned int getNbEtats() const{return m_nbEtats;}
protected:
    std::string m_rule;
    unsigned int m_nbEtats;
};



class GameOfLife : public TransitionRule //nombre d'Etats forcément = à 2 !!!!!!!!
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    GameOfLife(unsigned int minVoisinsVivants,unsigned int maxVoisinsVivants ) : TransitionRule(), m_minVoisinsVivants(minVoisinsVivants), m_maxVoisinsVivants(maxVoisinsVivants)
    {

    }
    std::string getTransition() const override;
    unsigned int getNbEtats() const {return 2;}
    ~GameOfLife() = default;
protected:
    unsigned int m_minVoisinsVivants;
    unsigned int m_maxVoisinsVivants;
};
class FeuForet : public TransitionRule //nombre d'Etats forcément = à 2 !!!!!!!!
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) const override;
    FeuForet() = default;
    std::string getTransition() const override;
    unsigned int getNbEtats() const {return 4;}
    ~FeuForet() = default;
};

#endif // TRANSITIONRULE_H
