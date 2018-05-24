#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H
#include "cell.h"
#include "generateuretat.h"
#include "etat.h"
#include "voisinage.h"
#include "transitionrule.h"

class CellularAutomata
{
private:
    const TransitionRule *m_rule;
    const Voisinage *m_voisinageDefinition;
    Etat** m_etats;
    const Etat* m_depart;
    unsigned int m_nbEtats;
    unsigned int m_buffer;
    unsigned int m_rang;

    void Build(unsigned int c);
    /*CellularAutomata(const CellularAutomata& s);
    CellularAutomata& operator=(const CellularAutomata& s);*/
public:
    //CellularAutomata( TransitionRule const* rule, unsigned int buffer = 2);
    CellularAutomata(const TransitionRule &rule ,unsigned int nbEtats, const Voisinage &definitionVoisinage, unsigned int buffer);
    CellularAutomata(const Etat& dep, const TransitionRule& rule , unsigned int nbEtats, Voisinage const& definitionVoisinage, unsigned int buffer = 2);
    void setEtatDepart(const Etat &dep);
    //void setEtatDepart(const Etat& e);
    void Run(unsigned int nbSteps); // génère les n prochains états
    void Next(); // génère le prochain état
    const Etat& Dernier() const;
    unsigned int GetRangDernier() const { return m_rang; }
    void Reset(); // revenir à l'état de départ
    ~CellularAutomata();

};

#endif // CELLULARAUTOMATA_H
