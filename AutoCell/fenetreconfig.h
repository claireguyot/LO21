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

class SousFenetre : public QWidget//cette classe fournie seulement une interface (pas de comportement) pour la sauvegarde du contexte de toutes les fenetres inclues dans MainWindow
{
public:
    virtual void loadContexte() = 0;
    virtual void saveContexte() = 0;
    SousFenetre(QWidget *parent = nullptr): QWidget(parent) {}
    virtual ~SousFenetre() {}
};

class fenetreConfig : public SousFenetre
{
    Q_OBJECT
public:
    explicit fenetreConfig(QWidget *parent = nullptr): SousFenetre(parent)
    {

    }

    virtual void constructionAutomate() const = 0;
    virtual ~fenetreConfig()
    {

    }
    virtual void loadContexte() = 0;
    virtual void saveContexte() = 0;

signals:
    void configConstruite(int) const;
protected:
    QFormLayout* m_formulaire;
    QPlainTextEdit* m_info;
    QVBoxLayout* m_layoutPrincipal;


};

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
