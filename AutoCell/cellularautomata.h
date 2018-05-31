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
    const TransitionRule* m_rule;
    const Voisinage* m_voisinageDefinition;
    Etat** m_etats;
    const Etat* m_depart;
    unsigned int m_nbEtats;
    unsigned int m_buffer;
    unsigned int m_rang;


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
