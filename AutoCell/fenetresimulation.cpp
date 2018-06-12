#include "fenetresimulation.h"

void FenetreAutomate::generationSuivante() //ne change pas par rapport à la fenetre 1D
{
    if (m_simulateur== nullptr || m_simulateur->getTransition() == nullptr )
    {
            pause();
            QMessageBox::critical(0,"erreur","L'automate n'est pas généré !");
    }
    else if (m_simulateur->getEtatDepart() == nullptr)
    {
        pause();
        QMessageBox::critical(0,"erreur","L'état de départ n'est pas généré !");


    }
    else
    {
        m_simulateur->Next();
        afficherDernierEtat();
    }

}

void FenetreAutomate::pause() //ne change pas par rapport à la fenetre1D
{
    m_timer->stop();
}

void FenetreAutomate::reset() //ne change pas par rapport à fenetre1D
{
    if (m_simulateur== nullptr )
    {
            pause();
            QMessageBox::critical(0,"erreur","L'automate n'est pas généré !");
    }
    else if (m_simulateur->getEtatDepart() == nullptr)
    {
        pause();
        QMessageBox::critical(0,"erreur","L'état de départ n'est pas généré !");


    }
    else
    {
        pause();
        m_simulateur->Reset();
        buildGrille();
        afficherDernierEtat();
    }
}

void FenetreAutomate::play() //ne change pas par rapport à la fenetre1D
{

    m_timer->start(m_selectVitesse->value()*1000);
    generationSuivante();
}

const CellularAutomata* FenetreAutomate::getSimulateur() const //pareil que fenetre1D
{
    return m_simulateur;
}
