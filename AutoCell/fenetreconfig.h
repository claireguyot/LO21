#ifndef FENETRECONFIG_H
#define FENETRECONFIG_H

/*!
 * \file fenetreconfig.h
 * \brief Déclaration des classes SousFenetre, fenetreConfig, fenetreElementaryRule, fenetreGameOfLife et fenetreFeuForet, et définition de leurs méthodes inline
 */

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QPlainTextEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QComboBox>
#include <sstream>
#include <QSettings>
#include "cabuilder.h"

/*! \class SousFenetre
  * \brief Classe abstraite permettant de sauvegarder le contexte de toutes les fenêtres inclues dans MainWindow
  * \sa MainWindow, fenetreConfig, fenetreElementaryRule, fenetreGameOfLife, fenetreFeuForet
  *
  * Cette classe abstraite fourni une interface (et non un comportement) permettant de sauvegarder le contexte de toutes les fenêtres inclues dans MainWindow
  */
class SousFenetre : public QWidget//cette classe fournie seulement une interface (pas de comportement) pour la sauvegarde du contexte de toutes les fenetres inclues dans MainWindow
{
public:
        /*!
         * \brief Méthode de la classe SousFenetre
         *
         * Cette méthode virtuelle pure permet de charger le contexte d'une fenêtre inclue dans MainWindow.
         */
    virtual void loadContexte() = 0;
        /*!
         * \brief Méthode de la classe SousFenetre
         *
         * Cette méthode virtuelle pure permet de sauvegarder le contexte d'une fenêtre inclue dans MainWindow.
         */
    virtual void saveContexte() = 0;
        /*!
         * \brief Constructeur de la classe SousFenetre
         * \param parent Paramètre de type \a QWidget* représentant l'application
         *
         * Constructeur de la classe SousFenetre faisant appel au constructeur de \a QWidget en utilisant le paramètre \a parent.
         */
    SousFenetre(QWidget *parent = nullptr): QWidget(parent) {}
        /*!
         * \brief Destructeur de la classe SousFenetre
         *
         * Destructeur virtuel de la classe SousFenetre
         */
    virtual ~SousFenetre() {}
};


/*! \class fenetreConfig
  * \brief Classe abstraite permettant de sauvegarder le contexte de toutes les fenêtres inclues dans MainWindow
  * \sa MainWindow, SousFenetre, fenetreElementaryRule, fenetreGameOfLife, fenetreFeuForet
  *
  * Cette classe abstraite fourni un comportement à l'interface et permet de sauvegarder le contexte de toutes les fenêtres inclues dans MainWindow. Elle concerne la partie gauche de l'interface.
  */
class fenetreConfig : public SousFenetre
{
    Q_OBJECT
public:
        /*!
         * \brief Constructeur de la classe fenetreConfig
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa SousFenetre
         *
         * Constructeur de la classe fenetreConfig faisant appel au constructeur de \a SousFenetre en utilisant le paramètre \a parent.
         */
    explicit fenetreConfig(QWidget *parent = nullptr): SousFenetre(parent)
    {

    }
        /*!
         * \brief Méthode de la classe fenetreConfig
         *
         * Cette méthode virtuelle pure permet de construire un automate 1D ou 2D selon la fenêtre dans laquelle on se situe dans l'interface.
         */
    virtual void constructionAutomate() const = 0;
        /*!
         * \brief Destructeur de la classe fenetreConfig
         *
         * Destructeur virtuel de la classe fenetreConfig
         */
    virtual ~fenetreConfig()
    {

    }
        /*!
         * \brief Méthode de la classe fenetreConfig
         *
         * Cette méthode virtuelle pure permet de charger le contexte d'une fenêtre inclue dans MainWindow.
         */
    virtual void loadContexte() = 0;
        /*!
         * \brief Méthode de la classe fenetreConfig
         *
         * Cette méthode virtuelle pure permet de sauvegarder le contexte d'une fenêtre inclue dans MainWindow.
         */
    virtual void saveContexte() = 0;

signals:
        /*!
         * \brief Méthode signal de la classe fenetreConfig
         *
         * Cette méthode permet de signaler lorsque la construction d'un automate est terminée et que la configuration est finie.
         */
    void configConstruite(int) const;
protected:
    /*!
     * \brief Attribut de la classe fenetreConfig
     *
     * Cet attribut est de type \a QFormLayout*. Il permet de consruire l'environnement de saisie des paramètres des automates 1D ou 2D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QFormLayout* m_formulaire;
    /*!
     * \brief Attribut de la classe fenetreConfig
     *
     * Cet attribut est de type \a QPlainTextEdit*. Il permet d'afficher en lecture seule les informations relatives au fonctionnement des automates 1D ou 2D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QPlainTextEdit* m_info;
    /*!
     * \brief Attribut de la classe fenetreConfig
     *
     * Cet attribut est de type \a QVBoxLayout*. Il permet de disposer verticalement le formulaire de saisie \a m_formulaire, et les informations sur le fonctionnement \a m_info.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    QVBoxLayout* m_layoutPrincipal;
};


/*! \class fenetreElementaryRule
  * \brief Classe permettant de sauvegarder le contexte de la fenêtre pour un automate 1D, inclue dans MainWindow
  * \sa MainWindow, SousFenetre, fenetreConfig, fenetreGameOfLife, fenetreFeuForet
  *
  * Cette classe fourni un comportement à l'interface et permet de sauvegarder le contexte de la fenêtre pour un automate 1D, inclue dans MainWindow
  */
class fenetreElementaryRule : public fenetreConfig
{
    Q_OBJECT
private:
    QSpinBox* m_nombreEtats;
    static const unsigned int m_ordreVoisinage;
    QLineEdit* m_regle;
    QRegExpValidator* m_regleValidator;
    QLabel* nbCaract;

public:

    explicit fenetreElementaryRule(QWidget *parent = nullptr);
    void constructionAutomate() const override;
    ~fenetreElementaryRule()
    {

    }
    virtual void loadContexte() override;
    virtual void saveContexte() override;

private slots:
    void changementRegExp();
    void changementLabel();
};

unsigned int puissance(unsigned int a, unsigned int b);


/*! \class fenetreGameOfLife
  * \brief Classe permettant de sauvegarder le contexte de la fenêtre pour un automate 2D de type Jeu de la Vie, inclue dans MainWindow
  * \sa MainWindow, SousFenetre, fenetreConfig, fenetreElementaryRule, fenetreFeuForet
  *
  * Cette classe fourni un comportement à l'interface et permet de sauvegarder le contexte de la fenêtre pour un automate 2D de type Jeu de la Vie, inclue dans MainWindow
  */
class fenetreGameOfLife : public fenetreConfig
{
    Q_OBJECT
private:
    QComboBox* m_choixVoisinage;
    QSpinBox* m_ordreVoisinage;
    static const unsigned int m_nombreEtats;
    QSpinBox* m_minVivants;
    QSpinBox* m_maxVivants;

public:

    explicit fenetreGameOfLife(QWidget *parent = nullptr);
    void constructionAutomate() const override;
    ~fenetreGameOfLife()
    {

    }
    virtual void loadContexte() override;
    virtual void saveContexte() override;
};


/*! \class fenetreFeuForet
  * \brief Classe permettant de sauvegarder le contexte de la fenêtre pour un automate 2D de type Feu de Forêt, inclue dans MainWindow
  * \sa MainWindow, SousFenetre, fenetreConfig, fenetreElementaryRule, fenetreGameOfLife
  *
  * Cette classe fourni un comportement à l'interface et permet de sauvegarder le contexte de la fenêtre pour un automate 2D de type Feu de Forêt, inclue dans MainWindow
  */
class fenetreFeuForet : public fenetreConfig
{
    Q_OBJECT
private:
    QComboBox* m_choixVoisinage;
    QSpinBox* m_ordreVoisinage;
    static const unsigned int m_nombreEtats;

public:

    explicit fenetreFeuForet(QWidget *parent = nullptr);
    void constructionAutomate() const override;
    ~fenetreFeuForet()
    {

    }
    virtual void loadContexte() override;
    virtual void saveContexte() override;
};

#endif // FENETRECONFIG_H
