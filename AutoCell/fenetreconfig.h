#ifndef FENETRECONFIG_H
#define FENETRECONFIG_H

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
#include "cabuilder.h"

class fenetreConfig : public QWidget
{
    Q_OBJECT
public:
    explicit fenetreConfig(QWidget *parent = nullptr): QWidget(parent)
    {

    }

    virtual void constructionAutomate() const = 0;
    virtual ~fenetreConfig()
    {

    }

signals:
    void configConstruite(int) const;


};

class fenetreElementaryRule : public fenetreConfig
{
    Q_OBJECT
private:
    QSpinBox* m_nombreEtats;
    static unsigned int m_ordreVoisinage;
    QLineEdit* m_regle;
    QRegExpValidator* m_regleValidator;
    QLabel* nbCaract;



public:

    explicit fenetreElementaryRule(QWidget *parent = nullptr);
    void constructionAutomate() const override;
    ~fenetreElementaryRule()
    {

    }
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
    static unsigned int m_nombreEtats;
    QSpinBox* m_minVivants;
    QSpinBox* m_maxVivants;




public:

    explicit fenetreGameOfLife(QWidget *parent = nullptr);
    void constructionAutomate() const override;
    ~fenetreGameOfLife()
    {

    }
};

#endif // FENETRECONFIG_H
