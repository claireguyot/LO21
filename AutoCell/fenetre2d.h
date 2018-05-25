#ifndef fenetre2D_H
#define fenetre2D_H
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
#include <QComboBox>
#include <QStackedWidget>
#include "automateexception.h"
//#include "automate.h"

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);

class fenetre2D : public QWidget{
    Q_OBJECT

    QPushButton* bGenererEtat;
    QPushButton* bSauvegarderEtat;
    QPushButton* bChargerEtat;
    QSpinBox* bLargeur;
    QSpinBox* bLongueur;
    QLabel* lLongueur;
    QLabel* lLargeur;
    QComboBox* bchoixGenerateur;
    //QTableWidget* depart;
    //QVBoxLayout *layout;
    QTableWidget* grille;
    QPushButton* bStart;
    QPushButton* bPause;
    QPushButton* bRetourDepart;
    QPushButton* bNextFrame;
    QSpinBox* bSelectVitesse;

    QPushButton* bGenererAutomate;
    QPushButton* bSauvegarderAutomate;
    QPushButton* bChargerAutomate;

    QComboBox* choixAutomate;
    //QHBoxLayout* menuInferieur;
    //QHBoxLayout* layoutGlobal;

public:
    explicit fenetre2D(QWidget* parent = nullptr);
private slots:
    void cellActivation(const QModelIndex& index);
    void faireSimulation();
    void buildGrille();
};
#endif // fenetre2D_H
