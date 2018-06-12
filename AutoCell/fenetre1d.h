#ifndef FENETRE1D_H
#define FENETRE1D_H

/*!
 * \file fenetre1d.h
 * \brief Déclaration de la classes fenetre1D, et définition de ses méthodes inline
 */

#include "fenetresimulation.h"

class fenetre1D : public FenetreAutomate
{
    Q_OBJECT

    QTableWidget* m_depart;
    QComboBox* m_choixAutomate;
    fenetreElementaryRule* m_configElementaryRule;



public:
    explicit fenetre1D(QWidget* parent = nullptr);
    ~fenetre1D() {}
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
    void ConstructionManuelle() override;
    void UpdateInfo() override;
};
#endif // FENETRE1D_H
