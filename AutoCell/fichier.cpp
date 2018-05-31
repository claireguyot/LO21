#include "fichier.h"
#include <QDebug>
#include <QMessageBox>

void fichierEtat1D::save(const fenetre1D& fen) //sauvegarde d'un état (1D ou 2D)
{
    const Etat* e = &fen.getSimulateur()->Dernier();
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    unsigned int i,j;
    for(i=0 ; i < e->GetLargeur() ; i++)
    {
        for(j=0 ; j < e->GetLongueur()-1 ; j++)
        {
            f << e->GetCellule(i,j).GetEtat() << ",";
        }
        f << e->GetCellule(i,j).GetEtat();
        /*if(i != e->GetLargeur()-1) //ne devrait pas arriver (largeur=1 en 1D)
            f << ";";*/
    }
    f.close();
}

void fichierEtat2D::save(const fenetre2D &fen) //sauvegarde d'un état (1D ou 2D)
{
    const Etat* e = &fen.getSimulateur()->Dernier();
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    unsigned int i,j;
    for(i=0 ; i < e->GetLargeur() ; i++)
    {
        for(j=0 ; j < e->GetLongueur()-1 ; j++)
        {
            f << e->GetCellule(i,j).GetEtat() << ",";
        }
        f << e->GetCellule(i,j).GetEtat();
        if(i != e->GetLargeur()-1) //empêche de mettre un point virgule à la fin du document
            f << ";";
    }
    f.close();
}

void fichierEtat1D::load(const fenetre1D& fen) //chargement état 1D
{
    f.open(nomF,std::ofstream::in);
    unsigned int longueur=0,largeur=1;
    unsigned int etatMax = fen.getSimulateur()->GetNombreEtats()-1;
    char numEtat;
    std::vector<int> elements(longueur);

    f.read(&numEtat,1);
    while(f.eof() == false)
    {
        if(numEtat==';')
        {
            QMessageBox::critical(nullptr,"Alerte chargement état 1D","Le fichier décrit un automate 2D. Seule la première ligne a été chargée.");
            break;
        }
        else if(numEtat==',')
            longueur++;

        else
        {
            if(numEtat-'0'>etatMax)
                elements.push_back(etatMax);
            else
                elements.push_back(numEtat-'0');
        }

        f.read(&numEtat,1);
    }
    f.close();
    longueur++;
    int ** tab = new int*[largeur];
    for(int i=0;i<largeur;i++)
    {
        tab[i] = new int[longueur];
        for(int j=0;j<longueur;j++)
        {
            tab[i][j]=elements[i*(largeur-1)+j];
        }
    }
    CABuilder1D &m = CABuilder1D::getInstance();
    m.BuildEtatDepart(longueur,tab);
    for(int i=0;i<largeur;i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
}

void fichierEtat2D::load(const fenetre2D& fen) //chargement état 2D
{
    f.open(nomF,std::ofstream::in);
    int longueur=0,largeur=1, longPrec=0;
    char numEtat;
    unsigned int etatMax = fen.getSimulateur()->GetNombreEtats()-1;
    std::vector<int> elements(longueur);
    f.read(&numEtat,1);
    while(f.eof() == false)
    {
        if(numEtat==',')
        {
            longueur++;
        }
        else if(numEtat==';')
        {
            largeur++;
            longueur++;
            if(longPrec == 0 || longueur == longPrec) //on vérifie que toutes les lignes ont la même largeur
            {
                longPrec = longueur;
                longueur=0;
            }
            else
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier est corrompu et n'a pas pu être chargé.");
                f.close();
                return;
            }
        }
        else
        {
            if(numEtat-'0'>etatMax)
                elements.push_back(etatMax);
            else
                elements.push_back(numEtat-'0');
        }
    }
    int ** tab = new int*[largeur];
    for(int i=0;i<largeur;i++)
    {
        tab[i] = new int[longueur];
        for(int j=0;j<longueur;j++)
        {
            tab[i][j]=elements[i*(largeur-1)+j];
        }
    }
    f.close();
    CABuilder2D &m = CABuilder2D::getInstance();
    m.BuildEtatDepart(longueur,largeur,tab);
}

void fichierConfig1D::save(const fenetre1D& fen) //sauvegarde config 1D
{
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    CABuilder1D &m = CABuilder1D::getInstance();
    const Voisinage* voi = &m.GetVoisinageDefinition();
    const TransitionRule* tra = &m.GetTransitionRule();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi->getType() << "," << voi->GetOrdre();
        if(tra != nullptr)
            f << ",";
    }
    if(tra != nullptr)
    {
        f << "transition," << tra->getTransition();
    }
    f.close();
}

void fichierConfig2D::save(const fenetre2D& fen) //sauvegarde config 2D
{
    f.open(nomF,std::ofstream::out|std::ofstream::trunc);
    CABuilder2D &m = CABuilder2D::getInstance();
    const Voisinage* voi = &m.GetVoisinageDefinition();
    const TransitionRule* tra = &m.GetTransitionRule();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi->getType() << "," << voi->GetOrdre();
        if(tra != nullptr)
            f << ",";
    }
    if(tra != nullptr)
    {
        f << "transition," << tra->getTransition();
    }
    f.close();
}

void fichierConfig1D::load(const fenetre1D& fen) //chargement config 1D
{
    f.open(nomF,std::ofstream::in);
    CABuilder1D &m = CABuilder1D::getInstance();
    std::string mot, rule;
    char st[TAILLE_BUF];
    int a=0;
    while(f.eof()==false)
    {
        a=0;
        f.getline(st,TAILLE_BUF,',');
        mot = st;
        if(mot=="voisinage")
        {
            f.getline(st,TAILLE_BUF,','); //voisinage1D, VonNeumann ou Moore
            mot = st;
            if(mot != "voisinage1D")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier est une configuration 2D.");
                f.close();
                return;
            }
            f.getline(st,TAILLE_BUF,','); //ordre
            mot = st;
            if(mot=="")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            a=std::stoi(mot);
            m.BuildVoisinageDef(a);
        }
        else if(mot == "transition")
        {
            f.getline(st,TAILLE_BUF,',');
            mot = st;
            if(mot != "1D")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier est une configuration 2D.");
                f.close();
                return;
            }
            f.getline(st,TAILLE_BUF,',');//m_rule
            rule = st;
            if(rule=="")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            f.getline(st,TAILLE_BUF,',');//m_nbEtats
            mot = st;
            if(mot=="")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            a=std::stoi(mot);
            m.BuildElementaryRule(rule,a);
        }
    }
    f.close();
}

void fichierConfig2D::load(const fenetre2D& fen) //chargement config 2D
{
    f.open(nomF,std::ofstream::in);
    CABuilder2D &m = CABuilder2D::getInstance();
    std::string mot, rule, mode;
    char st[TAILLE_BUF];
    int a=0, b=0;
    while(f.eof()==false)
    {
        a=0,b=0;
        f.getline(st,TAILLE_BUF,',');
        mot = st;
        if(mot == "voisinage")
        {
            f.getline(st,TAILLE_BUF,','); //voisinage1D, VonNeumann ou Moore
            mot = st;
            if(mot == "VonNeumann")
            {
                f.getline(st,TAILLE_BUF,','); //ordre
                mot = st;
                if(mot=="")
                {
                    QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                a=std::stoi(mot);
                m.BuildVoisinageVonNeumann(a);
            }
            else if(mot == "Moore")
            {
                f.getline(st,TAILLE_BUF,','); //ordre
                mot = st;
                if(mot=="")
                {
                    QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                a=std::stoi(mot);
                m.BuildVoisinageMoore(a);
            }
            else
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier est une configuration 1D.");
                f.close();
                return;
            }
        }
        else if(mot == "transition")
        {
            f.getline(st,TAILLE_BUF,',');
            mot = st;
            if(mot != "2D")
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier est une configuration 1D.");
                f.close();
                return;
            }
            f.getline(st,TAILLE_BUF,',');//GameOfLife ou FeuForet
            mode = st;
            if(mode == "GameOfLife")
            {
                f.getline(st,TAILLE_BUF,',');//m_minVoisinsVivants
                mot = st;
                if(mot=="")
                {
                    QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                a=std::stoi(mot);
                f.getline(st,TAILLE_BUF,',');//m_maxVoisinsVivants
                mot = st;
                if(mot=="")
                {
                    QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                b=std::stoi(mot);
                m.BuildGameOfLife(a,b);
            }
            else if(mode == "FeuForet")
            {
                m.BuildFeuForet();
            }
            else
            {
                QMessageBox::critical(nullptr,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
        }
    }
    f.close();
}
