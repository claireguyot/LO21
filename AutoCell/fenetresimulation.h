#ifndef FENETRESIMULATION_H
#define FENETRESIMULATION_H

/*!
 * \file fenetresimulation.h
 * \brief Déclaration de la classe abstraite FenetreAutomate, et définition de ses méthodes inline
 */

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


/*! \class FenetreAutomate
  * \brief Classe abstraite permettant de sauvegarder le contexte de toutes les fenêtres inclues dans MainWindow
  * \sa MainWindow, SousFenetre
  *
  * Cette classe abstraite fourni une interface (et non un comportement) permettant de sauvegarder le contexte de la fenêtre de simulation 1D ou 2D inclue dans MainWindow
  */
class FenetreAutomate: public SousFenetre
{
    Q_OBJECT
protected:
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a CellularAutomata*. Il permet de définir l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    CellularAutomata* m_simulateur;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de générer un état de départ pour l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_genererEtat;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de sauvegarder un état de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_sauvegarderEtat;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de charger un état de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_chargerEtat;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QSpinBox*. Il s'agit d'une boîte permettant à l'utilisateur de saisir la largeur de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QSpinBox* m_largeur;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QSpinBox*. Il s'agit d'une boîte permettant à l'utilisateur de saisir la longueur de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QSpinBox* m_longueur;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QComboBox*. Il s'agit d'une boîte permettant à l'utilisateur de choisir le type de générateur pour l'état de départ de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QComboBox* m_choixGenerateur;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QTableWidget*. Il s'agit de la grille de simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QTableWidget* m_grille;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de démarrer la simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_start;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de mettre en pause la simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_pause;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de remettre à l'état de départ la simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_retourDepart;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de passer au prochain état de la simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_nextFrame;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QSpinBox*. Il s'agit d'une boîte permettant à l'utilisateur de choisir la vitesse la simulation de l'automate cellulaire 1D ou 2D de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QSpinBox* m_selectVitesse;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de générer l'automate cellulaire 1D ou 2D dans la fenêtre active, selon les paramètres entrés par l'utilisateur.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_genererAutomate;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de sauvegarder l'automate cellulaire 1D ou 2D actuel, selon les paramètres entrés par l'utilisateur.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_sauvegarderAutomate;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QPushButton*. Il s'agit d'un bouton permettant de charger un automate cellulaire 1D ou 2D dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPushButton* m_chargerAutomate;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QComboBox*. Il s'agit d'une boîte permettant de choisir entre "Jeu de la Vie" ou "Feu de Forêt" pour un automate cellulaire 2D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QComboBox* m_choixAutomate;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QTimer*. Il s'agit d'un \a widget permettant d'exécuter une action à chaque pas de temps défini. Ici, il permet de passer au prochain état de l'automate 1D ou 2D à chaque pas de temps que l'utilisateur définit dans \a m_selectVitesse.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QTimer* m_timer;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QLabel*. Il s'agit d'un champ de texte en lecture permettant d'afficher les caractéristiques de l'automate courant.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QLabel* m_info;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QLabel*. Il s'agit d'un champ de texte en lecture permettant de signaler où saisir la largeur de la grille de simulation de l'automate 1D ou 2D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QLabel* m_lLongueur;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QLabel*. Il s'agit d'un champ de texte en lecture permettant de signaler où saisir la longueur de la grille de simulation de l'automate 1D ou 2D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QLabel* m_lLargeur;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QHBoxLayout*. Il permet de mettre en forme horizontalement l'ensemble des \a widgets de la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QHBoxLayout* m_layoutGlobal;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QVBoxLayout*. Il permet de mettre en forme verticalement l'ensemble des \a widgets pour la simulation dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QVBoxLayout* m_layoutSimulation;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QVBoxLayout*. Il permet de mettre en forme verticalement l'ensemble des \a widgets pour le menu de configuration dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QVBoxLayout* m_menuGauche;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QHBoxLayout*. Il permet de mettre en forme horizontalement l'ensemble des \a widgets concernant le menu pour l'automate dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QHBoxLayout* m_menuAutomate;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QHBoxLayout*. Il permet de mettre en forme horizontalement l'ensemble des \a widgets concernant le menu inférieur pour l'état, la simulation et le timer, dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QHBoxLayout* m_menuInferieur;
    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QHBoxLayout*. Il permet de mettre en forme horizontalement l'ensemble des \a widgets concernant le menu supérieur pour l'état de départ et la grille de simulation, dans la fenêtre active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QHBoxLayout* m_menuSuperieur ;

    /*!
     * \brief Attribut de la classe FenetreAutomate
     *
     * Cet attribut est de type \a QStackedWidget*. Il permet de garder en mémoire l'automate courant lorsque l'on passe d'un automate 1D à un automate 2D et inversement   .
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
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
