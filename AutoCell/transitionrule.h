#ifndef TRANSITIONRULE_H
#define TRANSITIONRULE_H
#include "etat.h"
#include <string>
#include <vector>

class TransitionRule
{
public:
    TransitionRule() = default;
    virtual void EffectuerTransition(Etat const& depart, Etat& arrivee);
    virtual void TransitionCellule(Cell const& depart, Cell& arrivee) = 0;
    ~TransitionRule()= default;
};

class TransitionRule1D : public TransitionRule
{
public:
    TransitionRule1D() = default;
    ~TransitionRule1D() = default;
};

class ElementaryRule : public TransitionRule1D
{
public:
    void TransitionCellule(Cell const& depart,Cell& arrivee) override;
    ElementaryRule(std::string rule,int nbEtats) : TransitionRule1D(), m_rule(rule), m_nbEtats(nbEtats)
    {

    }
    ~ElementaryRule() = default;
private:
    std::string m_rule;
    int m_nbEtats;
};
#endif // TRANSITIONRULE_H
