#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

<<<<<<< HEAD
=======
/*!
 * \file sauvegarde.h
 * \brief Déclaration des méthodes liées à la sauvegarde du contexte d'un automate
 */
>>>>>>> 830695642cd0dec4ce5b22223f09a73d31cedebf

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


class fichier;


enum TypeFichier {ETAT, CONFIG};

enum DimType {_1D,_2D};

bool sauvegarde(const CellularAutomata &automate, TypeFichier t, DimType d);

bool chargement(CellularAutomata *&automate, TypeFichier t, DimType d);

#endif // SAUVEGARDE_H
