#include "fichier.h"

fichierEtat::save(CellularAutomata& automate)
{
    const Etat* e = &automate.Dernier();
    f.open(f.nomF,out|trunc);
    for(int i=0 ; i < e->GetLongueur() ; i++)
    {
        for(int j=0 ; j < e->GetLargeur()-1 ; j++)
        {
            f << e->GetCellule(i,j).GetEtat() << ",";
        }
        f << e->GetCellule(i,j).GetEtat()
        f << ";";
    }
    f.close();
}

fichierConfig::save(CellularAutomata& automate)
{
    f.open(f.nomF,out|trunc);

    f.close();
}
