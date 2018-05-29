#include "sauvegarde.h"

sauvegarde::sauvegarde(fenetre1D& f, QWidget* parent) : QWidget(parent)
{
    /*création de la fenêtre de sauvegarde*/
    f=nullptr;

    setWindowTitle("Sauvegarder");

    bSauvEtat = new QPushButton("Sauvegarder l'état actuel",this);
    bSauvConfig = new QPushButton("Sauvegarder la configuration actuelle",this);
    bAnnuler = new QPushButton("Quitter sauvegarde",this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(bSauvEtat);
    layout->addWidget(bSauvConfig);
    layout->addWidget(bAnnuler);

    setLayout(layout);

    connect(bSauvEtat,SIGNAL(clicked(bool)),this,SLOT(sauverFichier(f,ETAT)));
    connect(bSauvConfig,SIGNAL(clicked(bool)),this,SLOT(sauverFichier(f,CONFIG)));

    connect(bAnnuler,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void sauvegarde::setTypeFichier(const std::string& nom) //choix de l'algorithme à utiliser
{
    if(nom.find(".csv"))
        f = new fichierConfig(nom);
    else if(nom.find(".bn"))
        f = new fichierEtat(nom);
    else
        throw(FichierException("Le type du fichier n'est pas reconnu."));
}

sauvegarde::sauverFichier(fenetre1D& f, TypeFichier t) //fonction de sauvegarde de l'état : fait appel à la classe fichier
{
    std::string nomDoc = "";
    if(t==ETAT)
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.bn","","*.bn").toStdString();
    else
        nomDoc = QFileDialog::getSaveFileName(this,"Nouveau.csv","","*.csv").toStdString();

    setTypeFichier(nomDoc);
    f->save(f);
    delete f;
}

