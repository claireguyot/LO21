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

    QPushButton* m_genererEtat;
    QPushButton* m_sauvegarderEtat;
    QPushButton* m_chargerEtat;
    QSpinBox* m_largeur;
    QSpinBox* m_longueur;
    QLabel* m_lLongueur;
    QLabel* m_lLargeur;
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

    fenetreGameOfLife* m_configGameOfLife;
    fenetreFeuForet* m_configFeuForet;
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
