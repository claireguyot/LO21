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
        if(i != e->GetLongueur()-1)
            f << ";";
    }
    f.close();
}

void fichierEtat::load(CellularAutomata& automate)
{
    f.open(nomF,std::ofstream::in);
    int longueur=0,largeur=0;
    char numEtat;
    std::vector<int> elements(largeur);
    f.read(numEtat,1);
    while(f.eof() == false)
    {
        switch(numEtat)
        {
        case ",":
            largeur++;
            break;

        case ";":
            longueur++;
            largeur=0;
            break;

        default:
            elements.push_back(numEtat);
            break;
        }
    }
    int ** tab = new int*[longueur];
    for(i=0;i<longueur;i++)
    {
        tab[i] = new int[largeur];
        for(j=0;j<largeur;j++)
        {
            tab[i][j]=elements[i*longueur+j];
        }
    }
    f.close();
    Etat::Etat newEtat(largeur,longueur,tab); //peut-être pas bon par ici
    automate.setEtatDepart(newEtat);
}

void fichierConfig::save(const CellularAutomata& automate)
{
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    Voisinage* voi = automate.getVoisinage();
    TransitionRule* tra = automate.getTransition();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi->GetOrdre();
        if(tra != nullptr)
            f << ",";
    }
    if(tra != nullptr)
    {
        f << "transition," << tra->getTransition();
    }
    f.close();
}

void fichierConfig::load(CellularAutomata& automate)
{
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    Voisinage* voi = automate.getVoisinage();
    TransitionRule* tra = automate.getTransition();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi->GetOrdre();
        if(tra != nullptr)
            f << ",";
    }
    if(tra != nullptr)
    {
        f << "transition," << tra->getTransition();
    }
    f.close();
}
