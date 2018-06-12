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
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Sauvegarde état","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat1D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Sauvegarde config","","*.csv");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierConfig1D(nomDoc.toStdString());
        }
    }
    else
    {
        if(t==ETAT)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Chargement état","","*.bn");
            if(!nomDoc.isNull() && !nomDoc.isEmpty())
                f = new fichierEtat2D(nomDoc.toStdString());
        }
        else if(t==CONFIG)
        {
            nomDoc = QFileDialog::getSaveFileName(nullptr,"Chargement config","","*.csv");
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

bool chargement(CellularAutomata*& automate, TypeFichier t, DimType d)
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
        if(f->load(automate))
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


