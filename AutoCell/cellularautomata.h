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
    Etat* m_depart;
    unsigned int m_nbEtats;
    unsigned int m_buffer;
    unsigned int m_rang;
    unsigned int m_nombreVoisins;
    void Build(unsigned int c);
    /*CellularAutomata(const CellularAutomata& s);
    CellularAutomata& operator=(const CellularAutomata& s);*/
public:
    //CellularAutomata( TransitionRule const* rule, unsigned int buffer = 2);
    CellularAutomata(const TransitionRule* rule ,Etat& dep, unsigned int nbEtats,unsigned int nombreVoisins,Voisinage const* definitionVoisinage,unsigned int buffer = 2);
    //void setEtatDepart(const Etat& e);
    void Run(unsigned int nbSteps); // génère les n prochains états
    void Next(); // génère le prochain état
    const Etat& Dernier() const;
    unsigned int GetRangDernier() const { return m_rang; }
    void Reset(); // revenir à l'état de départ
    ~CellularAutomata();
/*
    class iterator {
        friend class CellularAutomata;
        CellularAutomata* sim;
        int i;
        iterator(CellularAutomata* s) :sim(s), i(s->m_rang) {}
        iterator(CellularAutomata* s, int dep) :sim(s), i(dep) {}
    public:
        iterator():sim(nullptr),i(0) {}
        iterator& operator++() {
            i--;
            if (i == -1 && sim->m_rang >= sim->m_buffer) i = sim->m_buffer - 1;
            return *this;
        }
        Etat& operator*() const {
            return *sim->m_etats[i%sim->m_buffer;
        }
        bool operator!=(iterator it) const { return sim != it.sim || i != it.i; }
    };

    iterator begin() {	return iterator(this); }
    iterator end() { if (m_rang < m_buffer) return iterator(this, -1); else return iterator(this, m_rang - m_buffer);  }


    class const_iterator {
        friend class CellularAutomata;
        const CellularAutomata* sim;
        int i;
        const_iterator(const CellularAutomata* s) :sim(s), i(s->m_rang) {}
        const_iterator(const CellularAutomata* s, int dep) :sim(s), i(dep) {}
    public:
        const_iterator():sim(nullptr),i(0) {}
        const_iterator& operator++() {
            i--;
            if (i == -1 && sim->m_rang >= sim->m_buffer) i = sim->m_buffer- 1;
            return *this;
        }
        const Etat& operator*() const {
            return *sim->m_etats[i%sim->m_buffer];
        }
        bool operator!=(const_iterator it) const { return sim != it.sim || i != it.i; }
    };

    const_iterator begin() const { return const_iterator(this); }
    const_iterator end() const { if (m_rang < m_buffer) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_buffer); }
    const_iterator cbegin() const { return const_iterator(this); }
    const_iterator cend() const { if (m_rang < m_buffer) return const_iterator(this, -1); else return const_iterator(this, m_rang - m_buffer);
*/
};

#endif // CELLULARAUTOMATA_H
