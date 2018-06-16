#ifndef fenetre2D_H
#define fenetre2D_H
/*!
 * \file fenetre2d.h
 * \brief Déclaration de la classes fenetre2D, et définition de ses méthodes inline
 */

#include "fenetresimulation.h"

#include "sauvegarde.h"


/*! \class fenetre2D
  * \brief Classe héritant de FenetreAutomate et permettant de sauvegarder le contexte de la fenêtre de simulation 2D inclue dans MainWindow, ainsi que de générer la simulation d'un automate 2D de type Jeu de la Vie, ou Feu de Forêt
  * \sa MainWindow, FenetreAutomate
  *
  * Cette classe fourni une interface et un comportement permettant de sauvegarder le contexte de la fenêtre de simulation 2D inclue dans MainWindow, ainsi que de générer la simulation d'un automate 2D de type Jeu de la Vie, ou Feu de Forêt.
  */
class fenetre2D : public FenetreAutomate
{
    Q_OBJECT

    /*!
     * \brief Attribut de la classe fenetre2D
     * \sa fenetreGameOfLife
     *
     * Cet attribut est de type \a fenetreGameOfLife*. Il permet de stocker l'ensemble de l'interface et du comportement de l'automate 2D de type Jeu de la Vie du simulateur.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    fenetreGameOfLife* m_configGameOfLife;
    /*!
     * \brief Attribut de la classe fenetre2D
     * \sa fenetreFeuForet
     *
     * Cet attribut est de type \a fenetreFeuForet*. Il permet de stocker l'ensemble de l'interface et du comportement de l'automate 2D de type Feu de Forêt du simulateur.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    fenetreFeuForet* m_configFeuForet;



public:
        /*!
         * \brief Constructeur de la classe fenetre2D
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa FenetreAutomate
         *
         * Constructeur de la classe fenetre2D permettant d'initialiser tous les attributs de la classe, de construire la grille de simulation, de mettre en forme l'ensemble de l'interface de la fenêtre 2D, et de connecter chaque bouton à la méthode slot qui lui est associée.
         */
    explicit fenetre2D(QWidget* parent = nullptr);
        /*!
         * \brief Destructeur de la classe fenetre2D
         * \sa FenetreAutomate
         *
         * Destructeur de la classe fenetre2D. Ses attributs subsistent après la destruction d'un objet de type \a fenetre2D. Il fait appel au destructeur de la classe mère \a FenetreAutomate pour détruire \a m_simulateur pointant sur un automate qui est lié à la fenêtre de simulation.
         */
    ~fenetre2D(){}
        /*!
         * \brief Méthode de la classe fenetre2D
         *
         * Cette méthode permet de charger le contexte d'un automate 2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void loadContexte() override;
        /*!
         * \brief Méthode de la classe fenetre2D
         *
         * Cette méthode permet de sauvegarder le contexte d'un automate 2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void saveContexte() override;

private slots:
        /*!
         * \brief Méthode slot de la classe fenetre2D
         *
         * Cette méthode permet de modifier la couleur des cases de la grille de cellules de l'automate 2D du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void cellActivation(const QModelIndex& index) override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         *
         * Cette méthode permet d'initialiser la grille de cellules de l'automate 2D du simulateur en taille et en couleur (blanc).
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void buildGrille() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         *
         * Cette méthode permet d'afficher les paramètres de configuration de l'automate 2D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void appelConfig() const override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa CABuilder2D
         *
         * Cette méthode permet de construire l'état de départ de l'automate 2D dans la fenêtre active selon les paramètres entrés par l'utilisateur, notamment à l'aide des méthodes \a buildGrille(), \a afficherDernierEtat() et des méthodes de \a CABuilder2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstruireEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa sauvegarde()
         *
         * Cette méthode permet de sauvegarder la configuration de l'automate 2D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void sauverAutomate() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa chargement()
         *
         * Cette méthode permet de charger une configuration pour l'automate 2D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void chargerAutomate() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa sauvegarde()
         *
         * Cette méthode permet de sauvegarder un état de l'automate 2D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void sauverEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa chargement()
         *
         * Cette méthode permet de charger un état pour l'automate 2D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void chargerEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre2D
         * \sa CABuilder2D, CellularAutomata
         *
         * Cette méthode permet de construire les sous parties d'un automate 2D puis l'automate 2D entier dans \a m_simulateur, à l'aide des méthodes des classes \a CABuilder2D puis \a CellularAutomata.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstruireAutomate(int nbEtats) override;

private:
        /*!
         * \brief Méthode de la classe fenetre2D
         *
         * Cette méthode permet d'afficher le dernier état généré de l'automate en associant une couleur à chaque cases de la grille de cellules de l'automate 2D du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void afficherDernierEtat() override;
        /*!
         * \brief Méthode de la classe fenetre2D
         * \sa CABuilder2D
         *
         * Cette méthode permet de construire manuellement l'état de départ de l'automate 2D du simulateur, en choisissant l'état (couleur) de chaque cellule de la grille, notamment à l'aide des méthodes de \a CABuilder2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstructionManuelle()override;
        /*!
         * \brief Méthode de la classe fenetre2D
         * \sa CABuilder2D
         *
         * Cette méthode permet de mettre à jour les caractéristiques \a m_info de l'automate 2D courant selon les changements faits par l'utilisateur.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void UpdateInfo() override;
};
#endif // fenetre2D_H
