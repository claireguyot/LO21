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
#include "sauvegarde.h"
#include <QTimer>
#include <QSettings>

//#include "automate.h"

class gest_fich;

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
    QLabel* m_info;


public:
    explicit fenetre1D(QWidget* parent = nullptr);
    ~fenetre1D()
    {
        delete simulateur;
    }
    const CellularAutomata* getSimulateur() const;
    void loadContexte();
    void saveContexte();
private slots:
    void cellActivation(const QModelIndex& index);
    void buildGrille();
    void generationSuivante();
    void play();
    void pause();
    void appelConfig() const;
    void ConstruireEtat();
    void reset();
    void sauverAutomate();
    void chargerAutomate();
    void sauverEtat();
    void chargerEtat();

//public slots:
    void ConstruireAutomate(int nbEtats=-1);
private:
    void afficherDernierEtat();
    void ConstructionManuelle();
    void UpdateInfo();
};
#endif // FENETRE1D_H
