#ifndef FENETRESIMULATION_H
#define FENETRESIMULATION_H


#include "fenetreconfig.h"
#include "cellularautomata.h"
#include "automateexception.h"
#include "sauvegarde.h"

#include <QApplication>
#include <QDesktopWidget>

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
#include <QTimer>
#include <QSettings>



class FenetreAutomate: public SousFenetre
{
    Q_OBJECT
protected:
    CellularAutomata* m_simulateur;

    QPushButton* m_genererEtat;
    QPushButton* m_sauvegarderEtat;
    QPushButton* m_chargerEtat;

    QSpinBox* m_largeur;
    QSpinBox* m_longueur;

    QComboBox* m_choixGenerateur;

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


    QTimer* m_timer;
    QLabel* m_info;
    QLabel* m_lLongueur;
    QLabel* m_lLargeur;

    QHBoxLayout* m_layoutGlobal;
    QVBoxLayout* m_layoutSimulation;
    QVBoxLayout* m_menuGauche;
    QHBoxLayout* m_menuAutomate;
    QHBoxLayout* m_menuInferieur;
    QHBoxLayout* m_menuSuperieur ;

    QStackedWidget* m_automates;


public:
    FenetreAutomate(QWidget* parent = nullptr) : SousFenetre(parent), m_simulateur(nullptr) {}
    virtual ~FenetreAutomate() {delete m_simulateur;}
    virtual const CellularAutomata* getSimulateur() const;
protected slots:
    virtual void cellActivation(const QModelIndex& index) = 0;
    virtual void buildGrille() = 0;
    virtual void generationSuivante();
    virtual void play();
    virtual void pause();
    virtual void appelConfig() const = 0;
    virtual void ConstruireEtat() = 0;
    virtual void reset();
    virtual void sauverAutomate()  = 0;
    virtual void chargerAutomate() = 0;
    virtual void sauverEtat() = 0;
    virtual void chargerEtat() = 0;
    virtual void ConstruireAutomate(int nbEtats) = 0;
protected:
    virtual void afficherDernierEtat() = 0;
    virtual void ConstructionManuelle() = 0;
    virtual void UpdateInfo() = 0;
};

#endif // FENETRESIMULATION_H
