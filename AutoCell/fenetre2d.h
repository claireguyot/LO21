#ifndef FENETRE2D_H
#define FENETRE2D_H
#include <QApplication>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QHeaderView>
#include "automateexception.h"
//#include "automate.h"

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);

class fenetre2D : public QWidget{
    Q_OBJECT

    QPushButton* bGenerer;
    QPushButton* bSauvegarder;
    QPushButton* bCharger;
    QSpinBox* bLargeur;
    QSpinBox* bHauteur;
    QLabel* lHauteur;
    QLabel* lLargeur;
    QHBoxLayout* menuSuperieur;
    QVBoxLayout *layout;
    QPushButton *simulation;
    QTableWidget* etats;
    static unsigned int dimension;
    static unsigned int nombreEtats;
    QPushButton* bStart;
    QPushButton* bPause;
    QPushButton* bRetourDepart;
    QPushButton* bNextFrame;
    QSpinBox* bSelectVitesse;
    QHBoxLayout* menuInferieur;
    QPushButton* bGenAleatoire;
    QPushButton* bGenSymetrique;
    QVBoxLayout* menuGauche;
    QHBoxLayout* layoutGlobal;
public:
    explicit fenetre2D(QWidget* parent = nullptr);
private slots:
    void cellActivation(const QModelIndex& index);
    void faireSimulation();
};
#endif // FENETRE2D_H
