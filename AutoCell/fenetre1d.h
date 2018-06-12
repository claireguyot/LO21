#ifndef FENETRE1D_H
#define FENETRE1D_H
#include "fenetresimulation.h"



class fenetre1D : public FenetreAutomate
{
    Q_OBJECT

    QTableWidget* m_depart;


    QComboBox* m_choixAutomate;



    fenetreElementaryRule* m_configElementaryRule;



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
