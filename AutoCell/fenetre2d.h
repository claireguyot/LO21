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
#include "cellularautomata.h"
#include "automateexception.h"
#include "fenetreconfig.h"
#include "sauvegarde.h"
#include <QTimer>
#include <QDesktopWidget>
#include <QSettings>
#include <sstream>


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

    fenetreGameOfLife* configGameOfLife;
    fenetreFeuForet* configFeuForet;
    CellularAutomata* m_simulateur;

    QTimer* m_timer;
    QLabel* m_info;


public:
    explicit fenetre2D(QWidget* parent = nullptr);
    ~fenetre2D()
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
    void ConstruireAutomate(int nbEtats=-1);

private:
    void afficherDernierEtat();
    void ConstructionManuelle();
    void UpdateInfo();
};
#endif // fenetre2D_H
