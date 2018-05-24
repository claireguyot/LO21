#include "fenetre1D.h"

fenetre1D::fenetre1D(QWidget *parent) : QWidget(parent)
{

    /*
     * Définition du menu supérieur : sauvegarde, chargement, définition état départ pour 1D
     */

    QPushButton *bSauvegarde = new QPushButton("Sauvegarder",this);
    QPushButton *bChargement = new QPushButton("Charger",this);
    QSpinBox *largeur = new QSpinBox(this);
    largeur->setMaximum(maxLargeurTableau);
    largeur->setMinimum(1);
    largeur->setValue(largInit);
    QSpinBox *hauteur = new QSpinBox(this);
    hauteur->setMaximum(maxHauteurTableau);
    hauteur->setMinimum(1);
    hauteur->setValue(largInit);

    QHBoxLayout *topMenu = new QHBoxLayout(this); //on met en place le menu supérieur

    topMenu->addWidget(bSauvegarde);
    topMenu->addWidget(bChargement);
    topMenu->addWidget(largeur);
    topMenu->addWidget(hauteur);

    QTableWidget *selectAutomateDepart = new QTableWidget(1,largeur->value(),this);
    selectAutomateDepart->horizontalHeader()->setVisible(false);
    selectAutomateDepart->verticalHeader()->setVisible(false);
    selectAutomateDepart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //selectAutomateDepart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    selectAutomateDepart->setFixedSize(largeur->value()*taille,taille);
    for(int i = 0;i<largeur->value();i++)
    {
        selectAutomateDepart->setColumnWidth(i,taille);
        selectAutomateDepart->setItem(0, i, new QTableWidgetItem(""));
    }
    connect(selectAutomateDepart,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));

    topMenu->addWidget(selectAutomateDepart);

    /*
     * Définition du menu gauche
     */


}

void fenetre1D::cellActivation(const QModelIndex& index)
{
    if (selectAutomateDepart->item(0,index.column())->text()=="")
    {
        selectAutomateDepart->item(0,index.column())->setText("_");
        selectAutomateDepart->item(0,index.column())->setBackgroundColor("black");
        selectAutomateDepart->item(0,index.column())->setTextColor("black");
    }
    else
    {
        selectAutomateDepart->item(0,index.column())->setText("");
        selectAutomateDepart->item(0,index.column())->setBackgroundColor("white");
        selectAutomateDepart->item(0,index.column())->setTextColor("white");
    }
}
