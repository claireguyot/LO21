#include "fichier.h"

void fichierEtat::save(const fenetre1D* fen = nullptr) //sauvegarde d'un état (1D ou 2D)
{
    const Etat* e = &fen->getSimulateur().Dernier();
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

void fichierEtat1D::load(const fenetre1D& fen) //chargement état 1D
{
    f.open(nomF,std::ofstream::in);
    int longueur=1,largeur=1;
    char numEtat;
    std::vector<int> elements(largeur);
    f.read(numEtat,1);
    while(f.eof() == false)
    {
        if(numEtat==";")
        {
            QMessageBox::critical(fen,"Alerte chargement état 1D","Le fichier décrit un automate 2D. Seule la première ligne a été chargée.");
            break;
        }
        else if(numEtat=",")
            largeur++;

        else
            elements.push_back(numEtat);
    }
    f.close();
    int ** tab = new int*[longueur];
    for(i=0;i<longueur;i++)
    {
        tab[i] = new int[largeur];
        for(j=0;j<largeur;j++)
        {
            tab[i][j]=elements[i*(longueur-1)+j];
        }
    }
    CABuilder1D &m = CABuilder1D::getInstance();
    m.BuildEtatDepart(largeur,tab);
}

void fichierEtat2D::load(const fenetre2D& fen) //chargement état 2D
{
    f.open(nomF,std::ofstream::in);
    int longueur=1,largeur=1, largPrec=0;
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
            if(largPrec == 0 || largeur == largPrec) //on vérifie que toutes les lignes ont la même largeur
            {
                largPrec = largeur;
                largeur=0;
            }
            else
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier est corrompu et n'a pas pu être chargé.");
                f.close();
                return;
            }
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
            tab[i][j]=elements[i*(longueur-1)+j];
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
    const Voisinage* voi = m.GetVoisinageDefinition();
    const TransitionRule* tra = m.GetTransitionRule();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi.getType() << ",ordre," << voi.GetOrdre();
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
    const Voisinage* voi = m.GetVoisinageDefinition();
    const TransitionRule* tra = m.GetTransitionRule();
    if(voi!=nullptr)
    {
        f << "voisinage," << voi.getType() << "," << voi.GetOrdre();
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
    int a=0, b=0;
    while(f.eof()==false)
    {
        a=0,b=0;
        f.getline(mot,100000,',');
        switch(mot)
        {
        case "voisinage":
            f.getline(mot,100000,','); //voisinage1D, VonNeumann ou Moore
            if(mot != "voisinage1D")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier est une configuration 2D.");
                f.close();
                return;
            }
            f.getline(mot,100000,','); //ordre
            if(mot=="" || a=std::stoi(mot) == 0)
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            m.BuildVoisinageDef(a);
            break;

        case "transition":
            f.getline(mot,100000,',');
            if(mot != "1D")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier est une configuration 2D.");
                f.close();
                return;
            }
            f.getline(rule,100000,',');//m_rule
            if(rule=="")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            f.getline(mot,100000,',');//m_nbEtats
            if(mot=="")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            a=std::stoi(mot);
            m.BuildElementaryRule(rule,a);
            break;
        }
    }
    f.close();
}

void fichierConfig2D::load(const fenetre2D& fen) //chargement config 2D
{
    f.open(nomF,std::ofstream::in);
    CABuilder2D &m = CABuilder2D::getInstance();
    std::string mot, rule, mode;
    int a=0, b=0;
    while(f.eof()==false)
    {
        a=0,b=0;
        f.getline(mot,100000,',');
        switch(mot)
        {
        case "voisinage":
            f.getline(mot,100000,','); //voisinage1D, VonNeumann ou Moore
            if(mot == "VonNeumann")
            {
                f.getline(mot,100000,','); //ordre
                if(mot=="" || a=std::stoi(mot) == 0)
                {
                    QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                m.BuildVoisinageVonNeumann(a);
            }
            else if(mot == "Moore")
            {
                f.getline(mot,100000,','); //ordre
                if(mot=="" || a=std::stoi(mot) == 0)
                {
                    QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                m.BuildVoisinageMoore(a);
            }
            else
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier est une configuration 1D.");
                f.close();
                return;
            }
            break;

        case "transition":
            f.getline(mot,100000,',');
            if(mot != "2D")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier est une configuration 1D.");
                f.close();
                return;
            }
            f.getline(mode,100000,',');//GameOfLife ou FeuForet
            switch(mode)
            {
            case "GameOfLife":
                f.getline(mot,100000,',');//m_minVoisinsVivants
                if(mot=="")
                {
                    QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                a=std::stoi(mot);
                f.getline(mot,100000,',');//m_maxVoisinsVivants
                if(mot=="")
                {
                    QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                    f.close();
                    return;
                }
                b=std::stoi(mot);
                m.BuildGameOfLife(a,b);
                break;
            case "FeuForet":
                m.BuildFeuForet();
                break;
            default:
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            if(rule=="")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            f.getline(mot,100000,',');//m_nbEtats
            if(mot=="")
            {
                QMessageBox::critical(fen,"Erreur chargement","Le fichier semble corrompu.");
                f.close();
                return;
            }
            a=std::stoi(mot);
            m.BuildElementaryRule(rule,a);
            break;
        }
    }
    f.close();
}
