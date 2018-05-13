#include "transitionrule.h"
using namespace std;
void TransitionRule::EffectuerTransition(const Etat &depart, Etat &arrivee) const
{
    for(int i = 0;i<depart.GetLargeur();i++)
    {
        for(int j=0; j<depart.GetLongueur();j++)
            TransitionCellule(depart.GetCellule(i,j),arrivee.GetCellule(i,j));
    }
}

void ElementaryRule::TransitionCellule(const Cell &depart, Cell &arrivee) const
{
    // /!\ IL FAUT CONTROLER LA TAILLE DE m_rule : DOIT AVOIR UNE TAILLE = A N^M ou N = nbre Etats M = nbre Voisins
    vector<Cell*> const& voisins = depart.GetVoisins();
    int somme = 0;
    int k = 1;
    if( voisins.size() == 0) cout << "PROBLEME" <<endl;
    for(int i= voisins.size()-1;i>=0;i--)
    {
        if(voisins[i] == nullptr) k *= m_nbEtats;
        else
        {
            somme += voisins[i]->GetEtat()*k;
            k *= m_nbEtats;
        }
    }
    arrivee.SetEtat(m_rule[m_rule.size()-somme-1]-'0');
}
