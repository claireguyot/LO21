#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file mainwindow.h
 * \brief Déclaration de la classe MainWindow, et définition de ses méthodes inline
 */

#include "fenetre1d.h"
#include "fenetre2d.h"
#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QSettings>

/*! \class MainWindow
  * \brief Classe représentant la fenetre principale de l'interface
  * \sa fenetre1D, fenetre2D
  *
  * Cette classe permet de construire la fenetre principale qui permet d'intervertir entre la fenetre pour un automate 1D et celle pour un automate 2D à l'aide d'un bouton spécifique.
  */
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    /*!
     * \brief Attribut de la classe MainWindow
     *
     * Cet attribut est de type \a QComboBox*. Il permet de construire un bouton pour le choix "Automate 1D" ou "Automate 2D" de l'interface.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    QComboBox *m_choixDimension;
    /*!
     * \brief Attribut de la classe MainWindow
     *
     * Cet attribut est de type \a fenetre1D*. Il permet de construire une sous fenêtre correspondant à l'interface pour "Automate 1D". On y accède à l'aide du bouton \a m_choixDimension.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    fenetre1D* m_dim1;
    /*!
     * \brief Attribut de la classe MainWindow
     *
     * Cet attribut est de type \a fenetre2D*. Il permet de construire une sous fenêtre correspondant à l'interface pour "Automate 2D". On y accède à l'aide du bouton \a m_choixDimension.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    fenetre2D* m_dim2;
    /*!
     * \brief Attribut de la classe MainWindow
     *
     * Cet attribut est de type \a QStackedWidget*. Il permet de permet de passer de la sous fenetre "Automate 1D" à "Automate 2D" et inversement, à l'aide du bouton \a m_choixDimension et de fenêtres \a m_dim1 et \a m_dim2.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    QStackedWidget *m_switchDim;
    /*!
     * \brief Attribut de la classe MainWindow
     *
     * Cet attribut est de type \a QVBoxLayout*. Il permet de disposer verticalement le bouton de choix \a m_choixDimension, et la sous fenêtre \a m_dim1 ou \a m_dim2.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    QVBoxLayout *m_layout;
    /*!
     * \brief Méthode de la classe MainWindow
     *
     * Cette méthode permet d'initialiser la fenêtre principale à l'aide de \a QSettings.
     * Elle est privée afin de la rendre accessible uniquement au travers des méthodes de la classe.
     */
    void loadContexte();
public:
        /*!
         * \brief Constructeur de la classe MainWindow
         * \param parent Paramètre de type \a QWidget* représentant l'application où construire la fenêtre principale
         *
         * Constructeur de la classe MainWindow permettant de configurer l'ensemble de ses attributs \a m_choixDimension, \a m_dim1, \a m_dim2, \a m_switchDim et \a m_layout, puis de charger le contexte de la fenêtre principale à l'aide de \a loadContexte().
         */
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
        /*!
         * \brief Méthode de la classe MainWindow
         * \param event Paramètre de type \a QCloseEvent* représentant un évènement de fermeture de la fenêtre principale
         * \sa fenetre1D, fenetre2D
         *
         * Cette méthode permet de sauvegarder le contexte de la fenêtre principale ainsi que de ses sous fenêtres \a m_dim1 et \a m_dim2 lorsque la fenêtre principale est fermée par l'utilisateur. Elle fait notamment appel aux méthodes \a saveContexte() des classes \a fenetre1D et \a fenetre2D.
         */
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
