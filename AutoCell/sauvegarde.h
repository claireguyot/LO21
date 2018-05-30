#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include "cellularautomata.h"
#include "fichier.h"
#include "fenetre1d.h"
#include "fenetre2d.h"

class fichier;
class fenetre1D;
class fenetre2D;

class gest_fich : public QWidget
{
public:
    enum TypeFichier {ETAT, CONFIG};

    enum DimType {_1D,_2D};
    ~gest_fich(){delete this->f;}

protected:
    fichier* f;

private:
    QPushButton* bSauvEtat;
    QPushButton* bSauvConfig;
    QPushButton* bAnnuler;
};

class sauvegarde : public gest_fich
{
public slots:
    explicit sauvegarde(const fenetre1D& fen, TypeFichier t);
    explicit sauvegarde(const fenetre2D& fen, TypeFichier t);

};

class chargement : public gest_fich
{
public slots:
    explicit chargement(const fenetre1D& fen, TypeFichier t);
    explicit chargement(const fenetre2D& fen, TypeFichier t);
};

#endif // SAUVEGARDE_H
