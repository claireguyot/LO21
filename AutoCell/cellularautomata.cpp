#include "cellularautomata.h"
#include <iostream>

using namespace std;


CellularAutomata::CellularAutomata(unsigned int nbEtats, const Etat *dep, const TransitionRule *rule, const Voisinage *definitionVoisinage, unsigned int buffer):
    m_rule(rule), m_etats(nullptr), m_depart(dep), m_buffer(buffer),m_rang(0),m_nbEtats(nbEtats), m_voisinageDefinition(definitionVoisinage) {

    m_etats = new Etat*[m_buffer];
    for (unsigned int i = 0; i < m_buffer; i++) m_etats[i] = nullptr;
    if(m_depart != nullptr)
        m_etats[0] = new Etat(*m_depart);
    if (m_voisinageDefinition != nullptr && m_etats[0]!= nullptr)
        m_voisinageDefinition->definirVoisinage(*m_etats[0]);

}


void CellularAutomata::setEtatDepart(const Etat &dep)
{
    m_depart = &dep;
    Reset();
}
void CellularAutomata::Build(unsigned int indice) {
    if (indice >= m_buffer) throw AutomateException("erreur taille buffer");
    if (m_depart==nullptr) throw AutomateException("etat depart indefini");
    if (m_etats[indice] == nullptr || m_etats[indice]->GetLargeur() != m_depart->GetLargeur() || m_etats[indice]->GetLongueur() != m_depart->GetLongueur()) //si on a changé l 'etat de départ et que les tailles ont changées il faut re build les états du buffer
    {
        if(m_etats[indice]==nullptr)
            delete m_etats[indice];

        m_etats[indice] = new Etat(*m_depart);
        if (m_voisinageDefinition != nullptr)
            m_voisinageDefinition->definirVoisinage(*m_etats[indice]); //le voisinage est lié à la grille donc quand on recrée une grille on doit recréer un voisinage pour cette grille donc c'est important de ne pas avoir un buffer trop grand pour pas recalculer le voisinage trop de fois + pour éviter le surplus mémoire
        //mais ça évite de recalculer le voisinage à chaque transition
    };
}



void CellularAutomata::Reset() {
    if (m_depart==nullptr) throw AutomateException("etat depart indefini");
    Build(0);
    *m_etats[0] = *m_depart;
    if (m_voisinageDefinition != nullptr)
        m_voisinageDefinition->definirVoisinage(*m_etats[0]); //il faut redéfinir le voisinage car on l'a supprimé en faisant *m_etats[0] = *m_depart;
    m_rang = 0;
}

void CellularAutomata::Next() {
    if (m_depart == nullptr) throw AutomateException("etat depart indefini");
    if(m_rule == nullptr) throw AutomateException("règle de transition non défini");
    Build((m_rang+1)%m_buffer);
    m_rule->EffectuerTransition(*m_etats[m_rang% m_buffer],*m_etats[(m_rang+1)% m_buffer]);
    m_rang++;

}

void CellularAutomata::Run(unsigned int nb_steps) {
    for (unsigned int i = 0; i < nb_steps; i++) Next();
}

const Etat& CellularAutomata::Dernier() const {
    if (m_depart==nullptr) throw AutomateException("etat depart indefini: le simulateur ne peut pas renvoyer le dernier état généré car il n'a pas d'état de départ de défini");
    return *m_etats[m_rang%m_buffer];
}


CellularAutomata::~CellularAutomata() {
    for (unsigned int i = 0; i < m_buffer; i++)
    {
        if(m_etats[i]!= nullptr)
            delete m_etats[i];
    }
    delete[] m_etats;
}

void CellularAutomata::setRule(const TransitionRule &rule)
{
    m_rule = &rule;
}
void CellularAutomata::setVoisinageDefinition(const Voisinage &voisinage)
{
    m_voisinageDefinition =&voisinage;
    for(unsigned int i = 0;i<m_buffer;i++)
    {
        if(m_etats[i]!= nullptr)
        {
            m_voisinageDefinition->definirVoisinage(*m_etats[i]);
        }
    }

}
