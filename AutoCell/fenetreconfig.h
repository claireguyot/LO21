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
         * Destructeur virtuel de la classe fenetreConfig. Ses attributs subsistent après la destruction d'un objet de type \a fenetreConfig.
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
    /*!
     * \brief Attribut de la classe fenetreElementaryRule
     *
     * Cet attribut est de type \a QSpinBox*. Il permet à l'utilisateur de choisir le nombre d'états possibles pour chaque cellule de l'automate 1D (minimum 2 et maximum 4).
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QSpinBox* m_nombreEtats;
    /*!
     * \brief Attribut statique de la classe fenetreElementaryRule
     *
     * Cet attribut est de type \a static \a const \a unsigned \a int. Il permet de définir l'ordre du voisinage pour un automate 1D.
     * Cet attribut est statique car il s'agit d'une caractéristique commune et partagée par tous les objets de la classe \a fenetreElementaryRule. L'ordre du voisinage est fixé à 2.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    static const unsigned int m_ordreVoisinage;
    /*!
     * \brief Attribut de la classe fenetreElementaryRule
     *
     * Cet attribut est de type \a QLineEdit*. Il permet à l'utilisateur de saisir la règle associée à l'automate 1D.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QLineEdit* m_regle;
    /*!
     * \brief Attribut de la classe fenetreElementaryRule
     *
     * Cet attribut est de type \a QRegExpValidator*. Il permet de vérifier que la règle entrée par l'utilisateur est conforme au nombre d'états possibles \a m_nombreEtats pour une cellule, à savoir qu'elle est composée de 0, de 1, de 2 ou de 3 selon de \a m_nombreEtats saisi.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QRegExpValidator* m_regleValidator;
    /*!
     * \brief Attribut de la classe fenetreElementaryRule
     *
     * Cet attribut est de type \a QLabel*. Il permet d'informer l'utilisateur du nombre de caractères nécessaires dans la règle à entrer suivant le nombre d'états possibles \a m_nombreEtats pour une cellule entré.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QLabel* nbCaract;

public:
        /*!
         * \brief Constructeur de la classe fenetreElementaryRule
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa fenetreConfig
         *
         * Constructeur de la classe fenetreElementaryRule permettant d'initialiser les attributs \a m_nombreEtats, \a m_regle, \a m_regleValidator et \a nbCaract, notamment à l'aide des méthodes \a changementRegExp() et \a changementLabel().
         * Il permet également de mettre en forme les différents champs à l'aide des attributs de fenetreConfig \a m_formulaire, \a m_info et \a m_layoutPrincipal.
         * Il va ensuite faire appel à la méthode \a loadContexte() pour charger le contexte de l'automate 1D.
         */
    explicit fenetreElementaryRule(QWidget *parent = nullptr);
        /*!
         * \brief Méthode de la classe fenetreElementaryRule
         * \sa CABuilder1D
         *
         * Cette méthode permet de construire un automate 1D selon les données saisies par l'utilisateur, en faisant notamment appel à la classe \a CABuilder1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void constructionAutomate() const override;
        /*!
         * \brief Destructeur de la classe fenetreElementaryRule
         *
         * Destructeur de la classe fenetreElementaryRule. Ses attributs subsistent après la destruction d'un objet de type \a fenetreElementaryRule.
         */
    ~fenetreElementaryRule()
    {

    }
        /*!
         * \brief Méthode de la classe fenetreElementaryRule
         *
         * Cette méthode virtuelle permet de charger le contexte d'un automate 1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void loadContexte() override;
        /*!
         * \brief Méthode de la classe fenetreElementaryRule
         *
         * Cette méthode virtuelle permet de sauvegarder le contexte d'un automate 1D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void saveContexte() override;

private slots:
        /*!
         * \brief Méthode slot de la classe fenetreElementaryRule
         *
         * Cette méthode permet de modifier l'attribut \a m_regleValidator, c'est-à-dire les valeurs que l'utilisateur peut entrer dans la règle qu'il saisi, selon le nombre d'états possibles pour une cellule saisi \a m_nombreEtats.
         */
    void changementRegExp();
        /*!
         * \brief Méthode slot de la classe fenetreElementaryRule
         *
         * Cette méthode permet de modifier l'attribut \a nbCaract, c'est-à-dire le nombre de caractère que l'utilisateur peut entrer dans la règle qu'il saisi, selon le nombre d'états possibles pour une cellule saisi \a m_nombreEtats.
         */
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
    /*!
     * \brief Attribut de la classe fenetreGameOfLife
     * \sa Moore, VonNeumann
     *
     * Cet attribut est de type \a QComboBox*. Il permet de définir le type de voisinage pour un automate 2D de type Jeu de la Vie, à savoir VonNeumann ou Moore.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QComboBox* m_choixVoisinage;
    /*!
     * \brief Attribut de la classe fenetreGameOfLife
     *
     * Cet attribut est de type \a QSpinBox*. Il permet de définir l'ordre du voisinage pour un automate 2D de type Jeu de la Vie.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QSpinBox* m_ordreVoisinage;
    /*!
     * \brief Attribut statique de la classe fenetreGameOfLife
     *
     * Cet attribut est de type \a static \a const \a unsigned \a int. Il permet de définir le nombre d'états possibles pour une cellule dans un automate 2D de type Jeu de la Vie.
     * Cet attribut est statique car il s'agit d'une caractéristique commune et partagée par tous les objets de la classe \a fenetreGameOfLife. Le nombre d'états possibles est fixé à 2.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    static const unsigned int m_nombreEtats;
    /*!
     * \brief Attribut de la classe fenetreGameOfLife
     *
     * Cet attribut est de type \a QSpinBox*. Il permet de définir le nombre minimum de voisins vivants pour qu'une cellule survive dans un automate 2D de type Jeu de la Vie.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QSpinBox* m_minVivants;
    /*!
     * \brief Attribut de la classe fenetreGameOfLife
     *
     * Cet attribut est de type \a QSpinBox*. Il permet de définir le nombre maximum de voisins vivants pour qu'une cellule survive dans un automate 2D de type Jeu de la Vie.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QSpinBox* m_maxVivants;

public:
        /*!
         * \brief Constructeur de la classe fenetreGameOfLife
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa fenetreConfig
         *
         * Constructeur de la classe fenetreGameOfLife permettant d'initialiser les attributs \a m_choixVoisinage, \a m_ordreVoisinage, \a m_minVivants et \a m_maxVivants.
         * Il permet également de mettre en forme les différents champs à l'aide des attributs de fenetreConfig \a m_formulaire, \a m_info et \a m_layoutPrincipal.
         * Il va ensuite faire appel à la méthode \a loadContexte() pour charger le contexte de l'automate 2D de type Jeu de la Vie.
         */
    explicit fenetreGameOfLife(QWidget *parent = nullptr);
        /*!
         * \brief Méthode de la classe fenetreGameOfLife
         * \sa CABuilder2D
         *
         * Cette méthode permet de construire un automate 2D de type Jeu de la Vie selon les données saisies par l'utilisateur, en faisant notamment appel à la classe \a CABuilder2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void constructionAutomate() const override;
        /*!
         * \brief Destructeur de la classe fenetreGameOfLife
         *
         * Destructeur de la classe fenetreGameOfLife. Ses attributs subsistent après la destruction d'un objet de type \a fenetreGameOfLife.
         */
    ~fenetreGameOfLife()
    {

    }
        /*!
         * \brief Méthode de la classe fenetreGameOfLife
         *
         * Cette méthode virtuelle permet de charger le contexte d'un automate 2D de type Jeu de la Vie.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void loadContexte() override;
        /*!
         * \brief Méthode de la classe fenetreGameOfLife
         *
         * Cette méthode virtuelle permet de sauvegarder le contexte d'un automate 2D de type Jeu de la Vie.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
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
    /*!
     * \brief Attribut de la classe fenetreFeuForet
     * \sa Moore, VonNeumann
     *
     * Cet attribut est de type \a QComboBox*. Il permet de définir le type de voisinage pour un automate 2D de type Feu de Forêt, à savoir VonNeumann ou Moore.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QComboBox* m_choixVoisinage;
    /*!
     * \brief Attribut de la classe fenetreFeuForet
     *
     * Cet attribut est de type \a QSpinBox*. Il permet de définir l'ordre du voisinage pour un automate 2D de type Feu de Forêt.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    QSpinBox* m_ordreVoisinage;
    /*!
     * \brief Attribut statique de la classe fenetreFeuForet
     *
     * Cet attribut est de type \a static \a const \a unsigned \a int. Il permet de définir le nombre d'états possibles pour une cellule dans un automate 2D de type Feu de Forêt.
     * Cet attribut est statique car il s'agit d'une caractéristique commune et partagée par tous les objets de la classe \a fenetreFeuForet. Le nombre d'états possibles est fixé à 4.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers de ses méthodes.
     */
    static const unsigned int m_nombreEtats;

public:
        /*!
         * \brief Constructeur de la classe fenetreFeuForet
         * \param parent Paramètre de type \a QWidget* représentant l'application
         * \sa fenetreConfig
         *
         * Constructeur de la classe fenetreFeuForet permettant d'initialiser les attributs \a m_choixVoisinage et \a m_ordreVoisinage.
         * Il permet également de mettre en forme les différents champs à l'aide des attributs de fenetreConfig \a m_formulaire, \a m_info et \a m_layoutPrincipal.
         * Il va ensuite faire appel à la méthode \a loadContexte() pour charger le contexte de l'automate 2D de type Feu de Forêt.
         */
    explicit fenetreFeuForet(QWidget *parent = nullptr);
        /*!
         * \brief Méthode de la classe fenetreFeuForet
         * \sa CABuilder2D
         *
         * Cette méthode permet de construire un automate 2D de type Feu de Forêt selon les données saisies par l'utilisateur, en faisant notamment appel à la classe \a CABuilder2D.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    void constructionAutomate() const override;
        /*!
         * \brief Destructeur de la classe fenetreFeuForet
         *
         * Destructeur de la classe fenetreFeuForet. Ses attributs subsistent après la destruction d'un objet de type \a fenetreFeuForet.
         */
    ~fenetreFeuForet()
    {

    }
        /*!
         * \brief Méthode de la classe fenetreFeuForet
         *
         * Cette méthode virtuelle permet de charger le contexte d'un automate 2D de type Feu de Forêt.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void loadContexte() override;
        /*!
         * \brief Méthode de la classe fenetreFeuForet
         *
         * Cette méthode virtuelle permet de sauvegarder le contexte d'un automate 2D de type Feu de Forêt.
         * Le mot clé \a override permet de s'assurer que le prototype est conforme à celui de la classe mère.
         */
    virtual void saveContexte() override;
};

#endif // FENETRECONFIG_H
