#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QObject>
#include <QWidget>
//#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
//#include <QString>
#include <QMessageBox>
#include "cellularautomata.h"
#include "fichier.h"
#include "fenetre1d.h"
#include "fenetre2d.h"

class gest_fich : public QWidget
{
public:
    enum TypeFichier {ETAT, CONFIG};

    enum DimType {_1D,_2D};
    /*explicit sauvegarde(const fenetre1D& fen, QWidget* parent = nullptr);
    explicit sauvegarde(const fenetre2D& fen, QWidget* parent = nullptr);*/
    void setTypeFichier(const std::string& nom, DimType dim);
    ~gest_fich(){delete this->f;}

protected:
    fichier* f;

private:
    /*QLabel* lbEtatActuel;
    QLabel* lbConfig;*/
    //QHBoxLayout* layout;
    QPushButton* bSauvEtat;
    QPushButton* bSauvConfig;
    QPushButton* bAnnuler;
    //QLineEdit* nomDoc;

/*public slots:
    sauverFichier(const fenetre1D& fen, TypeFichier t);
    sauverFichier(const fenetre2D& fen, TypeFichier t);*/
};

class sauvegarde : public gest_fich
{
public slots:
    explicit sauvegarde(const fenetre1D& fen, TypeFichier t, QWidget* parent = nullptr);
    explicit sauvegarde(const fenetre2D& fen, TypeFichier t, QWidget* parent = nullptr);
/*public:
    enum TypeFichier {ETAT, CONFIG};
    explicit sauvegarde(const fenetre1D& fen, QWidget* parent = nullptr);
    explicit sauvegarde(const fenetre2D& fen, QWidget* parent = nullptr);
    void setTypeFichier(const std::string& nom);

private:
    QLabel* lbEtatActuel;
    QLabel* lbConfig;
    QHBoxLayout* layout;
    QPushButton* bSauvEtat;
    QPushButton* bSauvConfig;
    QPushButton* bAnnuler;
    QLineEdit* nomDoc;

    fichier* f;*/

};

class chargement : public gest_fich
{
public slots:
    explicit chargement(const fenetre1D& fen, TypeFichier t, QWidget* parent = nullptr);
    explicit chargement(const fenetre2D& fen, TypeFichier t, QWidget* parent = nullptr);
};

#endif // SAUVEGARDE_H
