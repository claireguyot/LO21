#include "sauvegarde.h"

sauvegarde::sauvegarde(const fenetre1D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
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
        this->f->save(fen);
    /*else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");*/
    delete this->f;
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
        this->f->save(fen);
    /*else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");*/
    delete this->f;
}

chargement::chargement(const fenetre1D &fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
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
        this->f->load(fen);
    /*else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");*/
    delete this->f;
}

chargement::chargement(const fenetre2D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
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
        this->f->load(fen);
    /*else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");*/

    delete this->f;
}

