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
     * Cet attribut est de type \a QStackedWidget*. Il permet de garder en mémoire l'automate courant lorsque l'on passe d'un automate 1D à un automate 2D et inversement.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QStackedWidget* m_automates;


public:
        /*!
         * \brief Constructeur de la classe FenetreAutomate
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa SousFenetre
         *
         * Constructeur de la classe FenetreAutomate faisant appel au constructeur de \a SousFenetre en utilisant le paramètre \a parent. Le simulateur \a m_simulateur pointant sur un automate est initialisé à \a nullptr.
         */
    FenetreAutomate(QWidget* parent = nullptr) : SousFenetre(parent), m_simulateur(nullptr) {}
        /*!
         * \brief Destructeur de la classe FenetreAutomate
         *
         * Destructeur virtuel de la classe FenetreAutomate. Ses attributs subsistent après la destruction d'un objet de type \a FenetreAutomate, sauf le simulateur \a m_simulateur pointant sur un automate qui lui est lié à la fenêtre de simulation.
         */
    virtual ~FenetreAutomate() {delete m_simulateur;}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_simulateur
         *
         * \details Méthode virtuelle permettant de récupérer un \a const \a CellularAutomata* pointant sur l'automate lié à la fenêtre.
         * \return \a const \a CellularAutomata* pointant sur l'automate lié à la fenêtre.
         */
    virtual const CellularAutomata* getSimulateur() const;
protected slots:
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle pure permet de modifier la couleur des cases de la grille de cellules de l'automate du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         */
    virtual void cellActivation(const QModelIndex& index) = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle pure permet d'initialiser la grille de cellules de l'automate du simulateur en taille et en couleur (blanc).
         */
    virtual void buildGrille() = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle permet de passer à l'état suivant de l'automate du simulateur à l'aide des méthodes \a Next() et \a afficherDernierEtat().
         */
    virtual void generationSuivante();
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle permet de démarrer la simulation de l'automate en générant un état suivant à chaque pas de temps défini à l'aide de \a m_selectVitesse.
         */
    virtual void play();
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle permet de mettre en pause la simulation de l'automate sur le dernier état généré.
         */
    virtual void pause();
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         *
         * Cette méthode virtuelle pure permet d'afficher les paramètres de configuration selon la fenêtre active (automate 1D ou 2D).
         */
    virtual void appelConfig() const = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa CABuilder
         *
         * Cette méthode virtuelle pure permet de construire l'état de départ de l'automate 1D ou 2D dans la fenêtre active selon les paramètres entrés par l'utilisateur, notamment à l'aide des méthodes \a buildGrille(), \a afficherDernierEtat() et des méthodes de \a CABuilder1D ou \a CABuilder2D.
         */
    virtual void ConstruireEtat() = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa CellularAutomata
         *
         * Cette méthode virtuelle permet de remettre à l'état de départ l'automate 1D ou 2D de la fenêtre active, notamment à l'aide des méthodes \a buildGrille(), \a afficherDernierEtat() et de la méthode \a Reset() de \a CellularAutomata.
         */
    virtual void reset();
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa sauvegarde()
         *
         * Cette méthode virtuelle pure permet de sauvegarder la configuration de l'automate 1D ou 2D dans la fenêtre active.
         */
    virtual void sauverAutomate()  = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa chargement()
         *
         * Cette méthode virtuelle pure permet de charger une configuration pour l'automate 1D ou 2D dans la fenêtre active.
         */
    virtual void chargerAutomate() = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa sauvegarde()
         *
         * Cette méthode virtuelle pure permet de sauvegarder un état de l'automate 1D ou 2D dans la fenêtre active.
         */
    virtual void sauverEtat() = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa chargement()
         *
         * Cette méthode virtuelle pure permet de charger un état pour l'automate 1D ou 2D dans la fenêtre active.
         */
    virtual void chargerEtat() = 0;
        /*!
         * \brief Méthode slot de la classe FenetreAutomate
         * \sa CABuilder, CellularAutomata
         *
         * Cette méthode virtuelle pure permet de construire les sous parties d'un automate puis l'automate entier dans \a m_simulateur, à l'aide des méthodes des classes \a CABuilder1D ou \a CABuilder2D, puis \a CellularAutomata.
         */
    virtual void ConstruireAutomate(int nbEtats) = 0;
protected:
        /*!
         * \brief Méthode de la classe FenetreAutomate
         *
         * Cette méthode virtuelle pure permet d'afficher le dernier état généré de l'automate en associant une couleur à chaque cases de la grille de cellules de l'automate du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         */
    virtual void afficherDernierEtat() = 0;
        /*!
         * \brief Méthode de la classe FenetreAutomate
         * \sa CABuilder
         *
         * Cette méthode virtuelle pure permet de construire manuellement l'état de départ de l'automate du simulateur, en choisissant l'état (couleur) de chaque cellule de la grille, notamment à l'aide des méthodes de \a CABuilder1D ou \a CABuilder2D.
         */
    virtual void ConstructionManuelle() = 0;
        /*!
         * \brief Méthode de la classe FenetreAutomate
         * \sa CABuilder
         *
         * Cette méthode virtuelle pure permet de mettre à jour les caractéristiques \a m_info de l'automate courant selon les changements faits par l'utilisateur.
         */
    virtual void UpdateInfo() = 0;
};

#endif // FENETRESIMULATION_H
