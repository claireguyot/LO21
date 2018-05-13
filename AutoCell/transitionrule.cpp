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

void GameOfLife::TransitionCellule(const Cell &depart, Cell &arrivee) const
{
    vector<Cell*> const& voisins = depart.GetVoisins();
    int somme = 0;
    for(int i=0;i<voisins.size();i++)
    {
        if(voisins[i]!= nullptr && voisins[i]!= &depart) //si on est en train de traité un voisin qui existe et qui est différent de la cellule actuelle (car la cellule est stockée dans son voisinage MAIS on ne veut pas la compter dans la somme des voisins pour un GameOfLife)
           {

            //somme += voisins[i]->GetEtat(); //on ajoute 0 si la cellule voisine = 0 (donc morte) 1 sinon (vivante) /!\ il faut que les etats des cellules soit égaux à 0 ou 1 !!!! (à contrôler à la création du CellularAutomata et de la grille de Depart)
            //ou si on veut pas s'embêter à contrôler :
            if (voisins[i]->GetEtat()!= 0) somme++;
        }

    }
    if(somme>=m_minVoisinsVivants && somme<=m_maxVoisinsVivants)
        arrivee.SetEtat(NOIR);
    else
        arrivee.SetEtat(BLANC);

}
