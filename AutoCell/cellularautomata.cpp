#include "cellularautomata.h"
#include <iostream>

using namespace std;


CellularAutomata::CellularAutomata(const Etat &dep, const TransitionRule &rule , unsigned int nbEtats, const Voisinage &definitionVoisinage, unsigned int buffer):
    m_rule(&rule), m_etats(nullptr), m_depart(&dep), m_buffer(buffer),m_rang(0),m_nbEtats(nbEtats), m_voisinageDefinition(&definitionVoisinage) {
    m_etats = new Etat*[m_buffer];

    for (unsigned int i = 0; i < m_buffer; i++) m_etats[i] = nullptr;

    m_etats[0] = new Etat(*m_depart);
    m_voisinageDefinition->definirVoisinage(*m_etats[0]);

}

CellularAutomata::CellularAutomata(const TransitionRule &rule ,unsigned int nbEtats, const Voisinage &definitionVoisinage, unsigned int buffer):
    m_rule(&rule), m_etats(nullptr), m_depart(nullptr), m_buffer(buffer),m_rang(0),m_nbEtats(nbEtats), m_voisinageDefinition(&definitionVoisinage) {
    m_etats = new Etat*[m_buffer];

    for (unsigned int i = 0; i < m_buffer; i++) m_etats[i] = nullptr;

}

void CellularAutomata::setEtatDepart(const Etat &dep)
{
    m_depart = &dep;
    m_etats[0] = new Etat(*m_depart);
    m_voisinageDefinition->definirVoisinage(*m_etats[0]);
}
void CellularAutomata::Build(unsigned int cellule) {
    if (cellule >= m_buffer) throw AutomateException("erreur taille buffer");
    if (m_etats[cellule] == nullptr)
    {
        m_etats[cellule] = new Etat(*m_depart);
        m_voisinageDefinition->definirVoisinage(*m_etats[cellule]); //le voisinage est lié à la grille donc quand on recrée une grille on doit recréer un voisinage pour cette grille donc c'est important de ne pas avoir un buffer trop grand pour pas recalculer le voisinage trop de fois + pour éviter le surplus mémoire
        //mais ça évite de recalculer le voisinage à chaque transition
    };
}



void CellularAutomata::Reset() {
    if (m_depart==nullptr) throw AutomateException("etat depart indefini");
    Build(0);
    *m_etats[0] = *m_depart;
    m_rang = 0;
}

void CellularAutomata::Next() {
    if (m_depart == nullptr) throw AutomateException("etat depart indefini");
    Build((m_rang+1)%m_buffer);
    m_rule->EffectuerTransition(*m_etats[m_rang% m_buffer],*m_etats[(m_rang+1)% m_buffer]);
    m_rang++;

}

void CellularAutomata::Run(unsigned int nb_steps) {
    for (unsigned int i = 0; i < nb_steps; i++) Next();
}

const Etat& CellularAutomata::Dernier() const {
    return *m_etats[m_rang%m_buffer];
}

CellularAutomata::~CellularAutomata() {
    for (unsigned int i = 0; i < m_buffer; i++) delete m_etats[i];
    delete[] m_etats;
}
