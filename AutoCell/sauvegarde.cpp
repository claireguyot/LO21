#include "sauvegarde.h"
#include <QDebug>

bool sauvegarde(const CellularAutomata& automate, TypeFichier t, DimType d)
{
    fichier *f = nullptr;
    QString nomDoc;
    if(d == _1D)
    {
        if(t==ETAT)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Nouveau.bn","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat1D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Nouveau.csv","","*.csv");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierConfig1D(nomDoc.toStdString());
        }
    }
    else
    {
        if(t==ETAT)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Nouveau.bn","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat2D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Nouveau.csv","","*.csv");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierConfig2D(nomDoc.toStdString());
        }
    }

    if(f != nullptr)
    {
        if(f->save(automate))
        {
            delete f;
            return true;
        }
        else
        {
            delete f;
            return false;
        }
    }
    else
        return false;
}

bool chargement(const CellularAutomata& automate, TypeFichier t, DimType d)
{
    fichier *f = nullptr;
    QString nomDoc;
    if(d == _1D)
    {
        if(t==ETAT)
        {
            nomDoc = QFileDialog::getOpenFileName(nullptr,"Nouveau.bn","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat1D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getOpenFileName(nullptr,"Nouveau.csv","","*.csv");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierConfig1D(nomDoc.toStdString());
        }
    }
    else
    {
        if(t==ETAT)
        {
            nomDoc = QFileDialog::getOpenFileName(nullptr,"Nouveau.bn","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat2D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getOpenFileName(nullptr,"Nouveau.csv","","*.csv");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierConfig2D(nomDoc.toStdString());
        }
    }

    if(f != nullptr)
    {
        if(f->load(&automate))
        {
            delete f;
            return true;
        }
        else
        {
            delete f;
            return false;
        }
    }
    else
        return false;
}

/*sauvegarde::sauvegarde(const fenetre1D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    f=nullptr;
    QString nomDoc;
    if(t==gest_fich::TypeFichier::ETAT)
    {
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierEtat1D(nomDoc.toStdString());
    }
    else if(t==gest_fich::TypeFichier::CONFIG)
    {
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.csv","","*.csv");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierConfig1D(nomDoc.toStdString());
    }

    if(this->f != nullptr)
    {
        this->f->save(fen);
    }
}

sauvegarde::sauvegarde(const fenetre2D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    f=nullptr;
    QString nomDoc;
    if(t==gest_fich::TypeFichier::ETAT)
    {
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierEtat2D(nomDoc.toStdString());
    }
    else if(t==gest_fich::TypeFichier::CONFIG)
    {
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.csv","","*.csv");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierConfig2D(nomDoc.toStdString());
    }
    if(this->f != nullptr)
    {
        this->f->save(fen);
    }
}

chargement::chargement(const fenetre1D &fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    f=nullptr;
    QString nomDoc;
    if(t==gest_fich::TypeFichier::ETAT)
    {
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.bn","","*.bn");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierEtat1D(nomDoc.toStdString());
    }
    else if(t==gest_fich::TypeFichier::CONFIG)
    {
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.csv","","*.csv");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierConfig1D(nomDoc.toStdString());
    }
    if(this->f != nullptr)
    {
        this->f->load(fen);
    }
}

chargement::chargement(const fenetre2D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    f=nullptr;
    QString nomDoc;
    if(t==gest_fich::TypeFichier::ETAT)
    {
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.bn","","*.bn");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierEtat2D(nomDoc.toStdString());
    }
    else if(t==gest_fich::TypeFichier::CONFIG)
    {
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.csv","","*.csv");
        if(!nomDoc.isNull() && !nomDoc.isEmpty())
            this->f = new fichierConfig2D(nomDoc.toStdString());
    }
    if(this->f != nullptr)
    {
        this->f->load(fen);
    }
}

gest_fich::~gest_fich()
{
    if(f!=nullptr)
        delete f;
    f=nullptr;
}
sauvegarde::~sauvegarde()
{
    if(f!=nullptr)
        delete f;
    f=nullptr;
}
chargement::~chargement()
{
    if(f!=nullptr)
        delete f;
    f=nullptr;
}*/

