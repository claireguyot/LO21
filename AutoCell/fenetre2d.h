#ifndef fenetre2D_H
#define fenetre2D_H

#include "fenetresimulation.h"
#include "sauvegarde.h"


class fenetre2D : public FenetreAutomate
{
    Q_OBJECT

    fenetreGameOfLife* m_configGameOfLife;
    fenetreFeuForet* m_configFeuForet;



public:
    explicit fenetre2D(QWidget* parent = nullptr);
    ~fenetre2D(){}
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
