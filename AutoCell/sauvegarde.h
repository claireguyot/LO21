#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H


/*!
 * \file sauvegarde.h
 * \brief Déclaration des fonctions liées à la sauvegarde du contexte d'un automate
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


class fichier;

/**
* \enum TypeFichier
* \brief Type de sauvegarde de données
*
* Cette énumération défini le type de sauvegarde du fichier : soit un état, soit une configuration d'un automate 1D ou 2D.
*/
enum TypeFichier {ETAT, CONFIG};

/**
* \enum DimType
* \brief Type de sauvegarde de données
*
* Cette énumération défini le type d'automate sauvegardé : soit 1D, soit 2D.
*/
enum DimType {_1D,_2D};



/*!
 * \brief Fonction liée à la sauvegarde des données d'un automate 1D ou 2D
 *
 * Cette fonction permet de sauvegarder l'état ou la configuration d'un automate dans un fichier \a .bn ou \a .csv, avec un nom saisi par l'utilisateur.
 */
bool sauvegarde(const CellularAutomata &automate, TypeFichier t, DimType d);

/*!
 * \brief Fonction liée au chargement des données d'un automate 1D ou 2D
 *
 * Cette fonction permet de charger l'état ou la configuration d'un automate à partir d'un fichier \a .bn ou \a .csv.
 */
bool chargement(CellularAutomata *&automate, TypeFichier t, DimType d);

#endif // SAUVEGARDE_H
