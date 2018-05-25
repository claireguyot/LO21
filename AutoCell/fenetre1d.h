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
#include <QComboBox>
#include <QStackedWidget>
#include "cellularautomata.h"
#include "automateexception.h"
#include "fenetreconfig.h"
#include <QTimer>
//#include "automate.h"



class fenetre1D : public QWidget{
    Q_OBJECT

    QPushButton* bGenererEtat;
    QPushButton* bSauvegarderEtat;
    QPushButton* bChargerEtat;
    QSpinBox* bLargeur;
    QSpinBox* bLongueur;
    QLabel* lLongueur;
    QLabel* lLargeur;
    QComboBox* bchoixGenerateur;
    QTableWidget* depart;
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

    fenetreElementaryRule* configElementaryRule;
    CellularAutomata* simulateur;

    QTimer* m_timer;


public:
    explicit fenetre1D(QWidget* parent = nullptr);
    ~fenetre1D()
    {
        delete simulateur;
    }
private slots:
    void cellActivation(const QModelIndex& index);
    void buildGrille();
    void generationSuivante();
    void play();
    void pause();
    void appelConfig() const;
    void construireEtat();
    void reset();

public slots:
    void construireAutomate(int nbEtats);
private:
    void afficherDernierEtat();
};
#endif // FENETRE1D_H
