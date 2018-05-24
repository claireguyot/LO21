#ifndef FENETRE1D_H
#define FENETRE1D_H
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

class fenetre1D : public QWidget{
    Q_OBJECT

    QPushButton* bGenerer;
    QPushButton* bSauvegarder;
    QPushButton* bCharger;
    QSpinBox* bLargeur;
    QSpinBox* bLongueur;
    //QLabel* lHauteur;
    //QLabel* lLargeur;
    //QHBoxLayout* menuSuperieur;
    //QSpinBox* num; // numéro
    /*QLineEdit* numeroBit[8]; // un QLineEdit par bit
    QLabel* numl;
    QLabel* numeroBitl[8];
    QVBoxLayout* numc;
    QVBoxLayout* bitc[8];
    QHBoxLayout* numeroc;
    QIntValidator* zeroOneValidator;
    */
    QTableWidget* depart;
    //QVBoxLayout *layout;
    QPushButton *simulation;
    QTableWidget* etats;
   // static unsigned int dimension;
   // static unsigned int nombreEtats;
    QPushButton* bStart;
    QPushButton* bPause;
    QPushButton* bRetourDepart;
    QPushButton* bNextFrame;
    QSpinBox* bSelectVitesse;
    QHBoxLayout* menuInferieur;
    /*QPushButton* bGenAleatoire;
    QPushButton* bGenSymetrique;
    */
    //QVBoxLayout* menuGauche;
    QHBoxLayout* layoutGlobal;
public:
    explicit fenetre1D(QWidget* parent = nullptr);
private slots:
    void cellActivation(const QModelIndex& index);
    void faireSimulation();
    void buildGrille();
};
#endif // FENETRE1D_H
