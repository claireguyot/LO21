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

    QPushButton* m_genererEtat;
    QPushButton* m_sauvegarderEtat;
    QPushButton* m_chargerEtat;
    QSpinBox* m_largeur;
    QSpinBox* m_longueur;
    QLabel* m_lLongueur;
    QLabel* m_lLargeur;
    QComboBox* m_choixGenerateur;
    QTableWidget* m_depart;
    QTableWidget* m_grille;
    QPushButton* m_start;
    QPushButton* m_pause;
    QPushButton* m_retourDepart;
    QPushButton* m_nextFrame;
    QSpinBox* m_selectVitesse;

    QPushButton* m_genererAutomate;
    QPushButton* m_sauvegarderAutomate;
    QPushButton* m_chargerAutomate;

    QComboBox* m_choixAutomate;


    QHBoxLayout* m_layoutGlobal;
    QVBoxLayout* m_layoutSimulation;
    QVBoxLayout* m_menuGauche;
    QHBoxLayout* m_menuAutomate;
    QHBoxLayout* m_menuInferieur;
    QHBoxLayout* m_menuSuperieur ;

    QStackedWidget* m_automates;

    fenetreElementaryRule* m_configElementaryRule;
    CellularAutomata* m_simulateur;

    QTimer* m_timer;
    QLabel* m_info;


public:
    explicit fenetre1D(QWidget* parent = nullptr);
    ~fenetre1D()
    {
        delete m_simulateur;
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
