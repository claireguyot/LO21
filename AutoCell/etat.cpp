#include "etat.h"

using namespace std;
Etat::Etat(int largeur, int longueur, const GenerateurEtat &generateur, int nbEtats ) : m_largeur(largeur), m_longueur(longueur), m_generateur(&generateur), m_cellules()
{
    for (int i=0;i<largeur;i++)
    {
        m_cellules.push_back(vector<Cell>());
        for(int j=0; j<longueur;j++)
        {
            m_cellules[i].push_back(Cell(0,i,j));
        }

    }

    m_generateur->GenererEtat(nbEtats,m_cellules);
}

Etat::Etat(int largeur, int longueur, vector<vector<int> > tab) : m_largeur(largeur), m_longueur(longueur), m_cellules()
{
    for (int i=0;i<largeur;i++)
    {
        m_cellules.push_back(vector<Cell>());
        for(int j=0; j<longueur;j++)
        {
            m_cellules[i].push_back(Cell(tab[i][j],i,j));
        }

    }
}

Etat::Etat(int largeur, int longueur) : m_largeur(largeur), m_longueur(longueur), m_cellules()
{
    for (int i=0;i<largeur;i++)
    {
        m_cellules.push_back(vector<Cell>());
        for(int j=0; j<longueur;j++)
        {
            m_cellules[i].push_back(Cell(0,i,j));
        }

    }
}


void Etat::afficher() const
{
    for (int i=0;i<m_largeur;i++)
    {

        for(int j=0; j<m_longueur;j++)
        {
            cout << m_cellules[i][j].GetEtat();
        }
        cout << endl;

    }
}
