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

    /*!
     * \brief Attribut de la classe fenetre1D
     *
     * Cet attribut est de type \a QTableWidget*. Il s'agit de la grille de départ de simulation de l'automate cellulaire 1D de la fenêtre 1D active.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    QTableWidget* m_depart;
    /*!
     * \brief Attribut de la classe fenetre1D
     *
     * Cet attribut est de type \a QComboBox*. Il s'agit d'une boîte permettant de choisir entre "Automates élémentaires revisités" ou les autres types d'automates 1D pouvant être implémentés, pour un automate cellulaire 1D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    QComboBox* m_choixAutomate;
    /*!
     * \brief Attribut de la classe fenetre1D
     * \sa fenetreElementaryRule
     *
     * Cet attribut est de type \a fenetreElementaryRule*. Il permet de stocker l'ensemble de l'interface et du comportement de l'automate 1D du simulateur dans la fenêtre 1D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    fenetreElementaryRule* m_configElementaryRule;



public:
        /*!
         * \brief Constructeur de la classe fenetre1D
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa FenetreAutomate
         *
         * Constructeur de la classe fenetre1D permettant d'initialiser tous les attributs de la classe, de construire la grille de simulation, de mettre en forme l'ensemble de l'interface de la fenêtre 1D, et de connecter chaque bouton à la méthode slot qui lui est associée.
         */
    explicit fenetre1D(QWidget* parent = nullptr);
        /*!
         * \brief Destructeur de la classe fenetre1D
         * \sa FenetreAutomate
         *
         * Destructeur de la classe fenetre1D. Ses attributs subsistent après la destruction d'un objet de type \a fenetre1D. Il fait appel au destructeur de la classe mère \a FenetreAutomate pour détruire \a m_simulateur pointant sur un automate qui est lié à la fenêtre de simulation.
         */
    ~fenetre1D() {}
        /*!
         * \brief Méthode de la classe fenetre1D
         *
         * Cette méthode permet de charger le contexte d'un automate 1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void loadContexte() override;
        /*!
         * \brief Méthode de la classe fenetre1D
         *
         * Cette méthode permet de sauvegarder le contexte d'un automate 1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void saveContexte() override;
private slots:
        /*!
         * \brief Méthode slot de la classe fenetre1D
         *
         * Cette méthode permet de modifier la couleur des cases de la grille de cellules de l'automate 1D du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void cellActivation(const QModelIndex& index) override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         *
         * Cette méthode permet d'initialiser la grille de cellules de l'automate 1D du simulateur en taille et en couleur (blanc).
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void buildGrille() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         *
         * Cette méthode permet d'afficher les paramètres de configuration de l'automate 1D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void appelConfig() const override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa CABuilder1D
         *
         * Cette méthode permet de construire l'état de départ de l'automate 1D dans la fenêtre active selon les paramètres entrés par l'utilisateur, notamment à l'aide des méthodes \a buildGrille(), \a afficherDernierEtat() et des méthodes de \a CABuilder1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstruireEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa sauvegarde()
         *
         * Cette méthode permet de sauvegarder la configuration de l'automate 1D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void sauverAutomate() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa chargement()
         *
         * Cette méthode permet de charger une configuration pour l'automate 1D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void chargerAutomate() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa sauvegarde()
         *
         * Cette méthode permet de sauvegarder un état de l'automate 1D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void sauverEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa chargement()
         *
         * Cette méthode permet de charger un état pour l'automate 1D dans la fenêtre active.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void chargerEtat() override;
        /*!
         * \brief Méthode slot de la classe fenetre1D
         * \sa CABuilder1D, CellularAutomata
         *
         * Cette méthode permet de construire les sous parties d'un automate 1D puis l'automate 1D entier dans \a m_simulateur, à l'aide des méthodes des classes \a CABuilder1D, puis \a CellularAutomata.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstruireAutomate(int nbEtats) override;
private:
        /*!
         * \brief Méthode de la classe fenetre1D
         *
         * Cette méthode permet d'afficher le dernier état généré de l'automate en associant une couleur à chaque cases de la grille de cellules de l'automate 1D du simulateur selon la valeur de chaque cellule et selon les couleur prédéfinies dans \a enum \a etat.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void afficherDernierEtat() override;
        /*!
         * \brief Méthode de la classe fenetre1D
         * \sa CABuilder1D
         *
         * Cette méthode permet de construire manuellement l'état de départ de l'automate 1D du simulateur, en choisissant l'état (couleur) de chaque cellule de la grille, notamment à l'aide des méthodes de \a CABuilder1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void ConstructionManuelle() override;
        /*!
         * \brief Méthode de la classe fenetre1D
         * \sa CABuilder1D
         *
         * Cette méthode permet de mettre à jour les caractéristiques \a m_info de l'automate 1D courant selon les changements faits par l'utilisateur.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void UpdateInfo() override;
};
#endif // FENETRE1D_H
