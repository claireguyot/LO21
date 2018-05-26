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
#include <QTimer>



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
    CellularAutomata* simulateur;

    QTimer* m_timer;


public:
    explicit fenetre2D(QWidget* parent = nullptr);
    ~fenetre2D()
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
    void ConstruireEtat();
    void reset();

public slots:
    void ConstruireAutomate(int nbEtats);
private:
    void afficherDernierEtat();
    void ConstructionManuelle();
};
#endif // fenetre2D_H
