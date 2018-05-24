#include "sauvegarde.h"

sauvegarde::sauvegarde(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Sauvegarder");

    QString nomDoc = QFileDialog::getOpenFileName(this,"","",""); //à mettre dans les classes filles

    bXml = new QPushButton("Sauvegarder en XML",this);
    bJson = new QPushButton("Sauvegarder en JSON",this);
    bAnnuler = new QPushButton("Annuler",this);
    //nomDoc = new QLineEdit("Entrez le nom",this);

    layout = new QHBoxLayout();
    layout->addWidget(bXml);
    layout->addWidget(bJson);
    layout->addWidget(bAnnuler);

    setLayout(layout);

    connect(bXml,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(bJson,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(bAnnuler,SIGNAL(clicked(bool)),this,SLOT(close()));
}
