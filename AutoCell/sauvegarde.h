#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

/*!
 * \file sauvegarde.h
 * \brief Déclaration des méthodes liées à la sauvegarde du contexte d'un automate
 */

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

enum TypeFichier {ETAT, CONFIG};

enum DimType {_1D,_2D};

bool sauvegarde(const CellularAutomata &automate, TypeFichier t, DimType d);

bool chargement(CellularAutomata *&automate, TypeFichier t, DimType d);

#endif // SAUVEGARDE_H
