#include "interface.h"

fenetre::fenetre(QWidget *parent) : QMainWindow(parent)
{
    /*
     * Mise en place du qStackedWidget pour switcher entre 1 et 2 dimensions
     */

    QWidget *dim1 = new QWidget();
    QWidget *dim2 = new QWidget();

    QStackedWidget *switchDim = new QStackedWidget();
    switchDim->addWidget(dim1);
    switchDim->addWidget(dim2);

    switchDim->setCurrentIndex(0);

    /*
     * Définition des boutons de sélection 1D / 2D
     */

    QComboBox *choixDimension = new QComboBox;

    choixDimension->addItem("1D");
    choixDimension->addItem("2D");
    connect(choixDimension, SIGNAL(activated(int)), switchDim, SLOT(setCurrentIndex(int)));

    /*
     * Définition du menu supérieur : sauvegarde, chargement
     */

    QPushButton *bSauvegarde = new QPushButton("Sauvegarder");
    QPushButton *bChargement = new QPushButton("Charger");
    QSpinBox *largeur = new QSpinBox();
    largeur->setMaximum(maxLargeurTableau);
    largeur->setMinimum(1);
    QSpinBox *hauteur = new QSpinBox();
    hauteur->setMaximum(maxHauteurTableau);
    hauteur->setMinimum(1);

    QHBoxLayout *topMenu = new QHBoxLayout(); //on met en place le menu supérieur

    topMenu->addWidget(bSauvegarde);
    topMenu->addWidget(bChargement);
    topMenu->addWidget(largeur);
    topMenu->addWidget(hauteur);


    /*
     * Définition du menu gauche : celui-ci sera modifié en fonction du mode 1D ou 2D
     */



    QGridLayout *layoutGlobal = new QGridLayout; //on crée le layout global de la fenêtre

    layoutGlobal->addWidget(choixDimension,0,0,1,1);
    layoutGlobal->addLayout(topMenu,0,1,1,10);



    dim1->setLayout(layoutGlobal);
    //dim1->setLayout(layoutGlobal1D);
    //dim2->setLayout(layoutGlobal2D);

    setCentralWidget(switchDim);
}
