#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QObject>
#include <QWidget>
//#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>
#include "cellularautomata.h"
#include "fichier.h"
#include "fichierexception.h"

class sauvegarde : public QWidget
{
public:
    enum TypeFichier {ETAT, CONFIG};
    explicit sauvegarde(const CellularAutomata& automate, QWidget* parent = nullptr);
    void setTypeFichier(QString nom);
    sauverFichier(const CellularAutomata* automate);

private:
    /*QLabel* lbEtatActuel;
    QLabel* lbConfig;*/
    //QHBoxLayout* layout;
    QPushButton* bSauvEtat;
    QPushButton* bSauvConfig;
    QPushButton* bAnnuler;
    //QLineEdit* nomDoc;

    fichier* f;

public slots:
    void openSauvEtat(const CellularAutomata& automate);
    void openSauvConfig(const CellularAutomata& automate);

};

#endif // SAUVEGARDE_H
