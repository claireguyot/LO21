#include "fichier.h"

void fichierEtat::save(const CellularAutomata& automate)
{
    const Etat* e = &automate.Dernier();
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    int i,j;
    for(i=0 ; i < e->GetLongueur() ; i++)
    {
        for(j=0 ; j < e->GetLargeur()-1 ; j++)
        {
            f << e->GetCellule(i,j).GetEtat() << ",";
        }
        f << e->GetCellule(i,j).GetEtat();
        f << ";";
    }
    f.close();
}

void fichierConfig::save(const CellularAutomata& automate)
{
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);

    f.close();
}
