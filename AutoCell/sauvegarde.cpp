#include "sauvegarde.h"

sauvegarde::sauvegarde(const fenetre1D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    std::string nomDoc = "";
    if(t==gest_fich::TypeFichier::ETAT)
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn").toStdString();
    else if(t==gest_fich::TypeFichier::CONFIG)
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.csv","","*.csv").toStdString();

    setTypeFichier(nomDoc,_1D);
    if(this->f != nullptr)
        this->f->save(fen);
    else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");
    delete this->f;
}

sauvegarde::sauvegarde(const fenetre2D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    std::string nomDoc = "";
    if(t==gest_fich::TypeFichier::ETAT)
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn").toStdString();
    else if(t==gest_fich::TypeFichier::CONFIG)
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.csv","","*.csv").toStdString();

    setTypeFichier(nomDoc,_2D);
    if(this->f != nullptr)
        this->f->save(fen);
    else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");
    delete this->f;
}

chargement::chargement(const fenetre1D &fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    std::string nomDoc = "";
    if(t==gest_fich::TypeFichier::ETAT)
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.bn","","*.bn").toStdString();
    else if(t==gest_fich::TypeFichier::CONFIG)
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.csv","","*.csv").toStdString();

    setTypeFichier(nomDoc,_1D);
    if(this->f != nullptr)
        this->f->load(fen);
    else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");
    delete this->f;
}

chargement::chargement(const fenetre2D& fen, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    std::string nomDoc = "";
    if(t==gest_fich::TypeFichier::ETAT)
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.bn","","*.bn").toStdString();
    else if(t==gest_fich::TypeFichier::CONFIG)
        nomDoc = QFileDialog::getOpenFileName(this,"Nouveau.csv","","*.csv").toStdString();

    setTypeFichier(nomDoc,_2D);
    if(this->f != nullptr)
        this->f->load(fen);
    else
        QMessageBox::critical(nullptr,"Erreur chargement fichier","Extension non reconnue.");

    delete this->f;
}

void gest_fich::setTypeFichier(const std::string& nom, DimType dim) //choix de l'algorithme à utiliser
{
    //delete this->f;
    if(dim == _1D)
    {
        if(nom.find(".csv"))
            this->f = new fichierConfig1D(nom);
        else if(nom.find(".bn"))
            this->f = new fichierEtat1D(nom);
        else
            f = nullptr;

    }
    else if(dim == _2D)
    {
        if(nom.find(".csv"))
            this->f = new fichierConfig2D(nom);
        else if(nom.find(".bn"))
            this->f = new fichierEtat2D(nom);
        else
            f = nullptr;

    }
}

