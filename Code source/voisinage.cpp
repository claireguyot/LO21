/*!
 * \file voisinage.cpp
 * \brief Implémentation des méthodes non inline des classes du fichier < em>"voisinage.h"< /em>
 * \version 1.0
 * \sa voisinage.h
 */

#include "voisinage.h"

void Voisinage1D::definirVoisinage(Etat &e) const //nombre de Voisins minimum  = 3 (la cellule est comprise dans son propre voisinage)
{

    for(int i=0; i<e.GetLongueur();i++)
    {
        Cell& actuel = e.GetCellule(0,i);
        if(actuel.GetVoisins().size() != 0) actuel.ClearVoisinage();

            for (int j=-1*m_ordre; j<= m_ordre; j++)
            {


                if(j == 0)
                {
                        actuel.AjouterVoisin(&actuel);
                }
                else
                {
                    if(i+j>=0 && i+j<e.GetLongueur())
                    {

                        actuel.AjouterVoisin(&(e.GetCellule(0,i+j)));
                    }

                    else
                    {
                        actuel.AjouterVoisin(nullptr);

                    }
                }
            }
    }
}

void VonNeumann::definirVoisinage(Etat &e) const //nbVoisins = minimum 5 (la cellule est comprise dans son propre voisinage)
{

    for(int i=0; i<e.GetLargeur();i++)
    {
        for(int j=0;j<e.GetLongueur();j++)
        {
            Cell& actuel = e.GetCellule(i,j);
            if(actuel.GetVoisins().size() != 0) actuel.ClearVoisinage();


                for (int k=-m_ordre; k<= m_ordre; k++)
                {
                    if(k == 0)
                    {
                            actuel.AjouterVoisin(&actuel);
                    }
                    else
                    {
                        if(j+k>=0 && j+k<e.GetLongueur())
                            actuel.AjouterVoisin(&(e.GetCellule(i,j+k)));
                        else
                            actuel.AjouterVoisin(nullptr);
                    }

                }
                for (int k=-m_ordre; k<= m_ordre; k++)
                {
                    if(k != 0)
                    {
                        if(i+k>=0 && i+k<e.GetLargeur())
                            actuel.AjouterVoisin(&(e.GetCellule(i+k,j)));
                        else
                            actuel.AjouterVoisin(nullptr);

                    }

                }

        }

    }
}

void Moore::definirVoisinage(Etat &e) const
{
    for(int i=0; i<e.GetLargeur();i++)
    {
        for(int j=0;j<e.GetLongueur();j++)
        {
            Cell& actuel = e.GetCellule(i,j);
            if(actuel.GetVoisins().size() != 0) actuel.ClearVoisinage();
                for (int k=-m_ordre; k<= m_ordre; k++)
                {
                    for (int l = -m_ordre; l<= m_ordre; l++)
                    {
                        if(k == 0 && l == 0)
                        {
                                actuel.AjouterVoisin(&actuel);
                        }
                        else
                        {
                            if(j+k>=0 && j+k<e.GetLongueur() && i+l >=0 && i+l < e.GetLargeur())
                                actuel.AjouterVoisin(&(e.GetCellule(i+l,j+k)));
                            else
                                actuel.AjouterVoisin(nullptr);
                        }
                    }

                }


        }

    }
}
