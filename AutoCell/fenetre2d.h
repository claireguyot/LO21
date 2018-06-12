#ifndef fenetre2D_H
#define fenetre2D_H
/*!
 * \file fenetre2d.h
 * \brief Déclaration de la classes fenetre2D, et définition de ses méthodes inline
 */

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
    void loadContexte() override;
    void saveContexte() override;

private slots:
    void cellActivation(const QModelIndex& index) override;
    void buildGrille() override;
    void appelConfig() const override;
    void ConstruireEtat() override;
    void sauverAutomate() override;
    void chargerAutomate() override;
    void sauverEtat() override;
    void chargerEtat() override;
    void ConstruireAutomate(int nbEtats) override;

private:
    void afficherDernierEtat() override;
    void ConstructionManuelle()override;
    void UpdateInfo() override;
};
#endif // fenetre2D_H
