#include "etat.h"

using namespace std;
Etat::Etat(unsigned int largeur, unsigned int longueur, const GenerateurEtat &generateur, unsigned int nbEtats ) : m_largeur(largeur), m_longueur(longueur), m_generateur(&generateur), m_cellules()
{
    m_cellules = new Cell*[largeur];
    for (unsigned int i =0; i<largeur; i++)
    {
        m_cellules[i] = new Cell[longueur];
        for(unsigned int j=0; j<longueur;j++)
        {
            m_cellules[i][j].SetX(i);
            m_cellules[i][j].SetY(j);
        }
    }

    m_generateur->GenererEtat(nbEtats,m_cellules,m_largeur,m_longueur);
}

Etat::Etat(unsigned int largeur, unsigned int longueur, vector<vector<int> > tab) : m_largeur(largeur), m_longueur(longueur), m_cellules()
{
    m_cellules = new Cell*[largeur];
    for (unsigned int i =0; i<largeur; i++)
    {
        m_cellules[i] = new Cell[longueur];
        for(unsigned int j=0; j<longueur;j++)
        {
            m_cellules[i][j].SetX(i);
            m_cellules[i][j].SetY(j);
            m_cellules[i][j].SetEtat(tab[i][j]);
        }
    }
}

Etat::Etat(unsigned int largeur, unsigned int longueur) : m_largeur(largeur), m_longueur(longueur)
{
    m_cellules = new Cell*[largeur];
    for (unsigned int i =0; i<largeur; i++)
    {
        m_cellules[i] = new Cell[longueur];
        for(unsigned int j=0; j<longueur;j++)
        {
            m_cellules[i][j].SetX(i);
            m_cellules[i][j].SetY(j);
        }
    }
}

Etat::~Etat()
{
   for(unsigned int i = 0; i< m_largeur;i++)
       delete[] m_cellules[i];
   delete[] m_cellules;
}

Etat::Etat(const Etat &e): m_largeur(e.m_largeur), m_longueur(e.m_longueur),m_generateur(e.m_generateur)
{
    m_cellules = new Cell*[e.m_largeur];
    for (unsigned int i =0; i<e.m_largeur; i++)
    {
        m_cellules[i] = new Cell[e.m_longueur];
        for(unsigned int j=0; j<e.m_longueur;j++)
        {
               m_cellules[i][j]= e.m_cellules[i][j];
        }
    }
}

Etat& Etat::operator=(const Etat &e)
{
    if (this != &e)
    {
        if(m_longueur != e.m_longueur && m_largeur != e.m_largeur)
        {
            for(unsigned int i = 0; i< m_largeur;i++)
                delete[] m_cellules[i];
            delete[] m_cellules;
            m_largeur = e.m_largeur;
            m_longueur = e.m_longueur;
            m_cellules = new Cell*[e.m_largeur];
            for (unsigned int i =0; i<e.m_largeur; i++)
            {
                m_cellules[i] = new Cell[e.m_longueur];
                for(unsigned int j=0; j<e.m_longueur;j++)
                {
                       m_cellules[i][j]= e.m_cellules[i][j];
                }
            }
        }
        else
        {
            for (unsigned int i =0; i<e.m_largeur; i++)
            {
                for(unsigned int j=0; j<e.m_longueur;j++)
                {
                       m_cellules[i][j]= e.m_cellules[i][j];
                }
            }
        }
        m_generateur = e.m_generateur;
    }
    return *this;
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
