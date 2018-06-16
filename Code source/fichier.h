#ifndef FICHIER_H
#define FICHIER_H

/*!
 * \file fichier.h
 * \brief Déclaration des classes fichier, fichierEtat1D, fichierEtat2D, fichierConfig1D et fichierConfig2D, et définition de leurs méthodes inline
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <QMessageBox>
#include "cellularautomata.h"
#include "cabuilder.h"


#define TAILLE_BUF 100


/*! \class fichier
  * \brief Classe abstraite permettant de sauvegarder la configuration et le dernier état d'un automate 1D ou 2D
  * \sa MainWindow, SousFenetre, fenetre1D, fenetre2D
  *
  * Cette classe abstraite permet de sauvegarder la configuration et le dernier état d'un automate 1D ou 2D
  */
class fichier
{
public:
        /*!
         * \brief Constructeur de la classe fichier
         * \param nom Paramètre de type \a const \a std::string représentant le nom du fichier
         *
         * Constructeur de la classe fichier permettant d'initialiser l'attribut \a nomF à l'aide de la valeur passée en paramètre
         */
    fichier(const std::string nom) : nomF(nom){}
        /*!
         * \brief Méthode de la classe fichier
         * \param automate Paramètre de type \a const \a CellularAutomata& représentant l'automate 1D ou 2D dont on veut sauvegarder les données
         *
         * Cette méthode virtuelle pure permet de sauvegarder les données d'un automate 1D ou 2D dans un fichier.
         */
    virtual bool save(const CellularAutomata& automate)=0;
        /*!
         * \brief Méthode de la classe fichier
         * \param automate Paramètre de type \a CellularAutomata*& représentant l'automate 1D ou 2D dans lequel on veut charger les données
         *
         * Cette méthode virtuelle pure permet de charger des données d'un fichier dans un automate 1D ou 2D.
         */
    virtual bool load(CellularAutomata*& automate)=0;
        /*!
         * \brief Destructeur de la classe fichier
         *
         * Destructeur virtuel de la classe fichier. Il permet de fermer le flux \a f si celui-ci n'est pas fermé lors de la fermeture du fichier.
         */
    virtual ~fichier(){if(f.is_open()) f.close();}
protected:
    /*!
     * \brief Attribut de la classe fichier
     *
     * Cet attribut est de type \a std::string. Il permet d'attribuer un nom au fichier en question.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    std::string nomF;
    /*!
     * \brief Attribut de la classe fichier
     *
     * Cet attribut est de type \a std::fstream. Il s'agit d'un flux permettant l'écriture et la lecture d'un fichier qui va servir pour la sauvegarde et le chargement de données.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe et de ses classes filles.
     */
    std::fstream f;
};



/*! \class fichierEtat1D
  * \brief Classe héritant de fichier permettant de sauvegarder le dernier état d'un automate 1D
  * \sa fichier, fenetre1D
  *
  * Cette classe abstraite permet de sauvegarder le dernier état d'un automate 1D
  */
class fichierEtat1D : public fichier
{
public:
        /*!
         * \brief Constructeur de la classe fichierEtat1D
         * \param nom Paramètre de type \a const \a std::string représentant le nom du fichier
         *
         * Constructeur de la classe fichierEtat1D faisant appel au constructeur de la classe \a fichier avec le paramètre \a nom.
         */
    fichierEtat1D(const std::string nom) : fichier(nom) {}
        /*!
         * \brief Méthode de la classe fichierEtat1D
         * \param automate Paramètre de type \a const \a CellularAutomata& représentant l'automate 1D dont on veut sauvegarder les données
         *
         * Cette méthode permet de sauvegarder le dernier état d'un automate 1D dans un fichier.
         */
    bool save(const CellularAutomata& automate);
        /*!
         * \brief Méthode de la classe fichierEtat1D
         * \param automate Paramètre de type \a CellularAutomata*& représentant l'automate 1D pour lequel on veut charger l'état de départ
         * \sa CABuilder1D
         *
         * Cette méthode permet de charger un état de départ contenu dans un fichier, dans un automate 1D.
         * Elle fait notamment appel à \a CABuilder1D pour construire les sous parties de l'automate avec les données voulues du fichier.
         */
    bool load(CellularAutomata*& automate);
    //~fichierEtat1D(){f.close();}
private:

};



/*! \class fichierEtat2D
  * \brief Classe héritant de fichier permettant de sauvegarder le dernier état d'un automate 2D
  * \sa fichier, fenetre2D
  *
  * Cette classe abstraite permet de sauvegarder le dernier état d'un automate 2D
  */
class fichierEtat2D : public fichier
{
public:
        /*!
         * \brief Constructeur de la classe fichierEtat2D
         * \param nom Paramètre de type \a const \a std::string représentant le nom du fichier
         *
         * Constructeur de la classe fichierEtat2D faisant appel au constructeur de la classe \a fichier avec le paramètre \a nom.
         */
    fichierEtat2D(const std::string nom) : fichier(nom) {}
        /*!
         * \brief Méthode de la classe fichierEtat2D
         * \param automate Paramètre de type \a const \a CellularAutomata& représentant l'automate 1D dont on veut sauvegarder les données
         *
         * Cette méthode permet de sauvegarder le dernier état d'un automate 2D dans un fichier.
         */
    bool save(const CellularAutomata& automate);
        /*!
         * \brief Méthode de la classe fichierEtat2D
         * \param automate Paramètre de type \a CellularAutomata*& représentant l'automate 2D pour lequel on veut charger l'état de départ
         * \sa CABuilder2D
         *
         * Cette méthode permet de charger un état de départ contenu dans un fichier, dans un automate 2D.
         * Elle fait notamment appel à \a CABuilder2D pour construire les sous parties de l'automate avec les données voulues du fichier.
         */
    bool load(CellularAutomata*& automate);
    //~fichierEtat2D(){f.close();}
private:

};



/*! \class fichierConfig1D
  * \brief Classe héritant de fichier permettant de sauvegarder la configuration d'un automate 1D
  * \sa fichier, fenetre1D, fichierEtat1D
  *
  * Cette classe abstraite permet de sauvegarder la configuration d'un automate 1D
  */
class fichierConfig1D : public fichier
{
public:
        /*!
         * \brief Constructeur de la classe fichierConfig1D
         * \param nom Paramètre de type \a const \a std::string représentant le nom du fichier
         *
         * Constructeur de la classe fichierConfig1D faisant appel au constructeur de la classe \a fichier avec le paramètre \a nom.
         */
    fichierConfig1D(const std::string nom) : fichier(nom) {}
        /*!
         * \brief Méthode de la classe fichierConfig1D
         * \param automate Paramètre de type \a const \a CellularAutomata& représentant l'automate 1D dont on veut sauvegarder les données
         *
         * Cette méthode permet de sauvegarder la configuration d'un automate 1D dans un fichier.
         */
    bool save(const CellularAutomata& automate);
        /*!
         * \brief Méthode de la classe fichierConfig1D
         * \param automate Paramètre de type \a CellularAutomata*& représentant l'automate 1D pour lequel on veut charger l'état de départ
         * \sa CABuilder1D
         *
         * Cette méthode permet de charger un état de départ contenu dans un fichier, dans un automate 1D.
         * Elle fait notamment appel à \a CABuilder1D pour construire les sous parties de l'automate avec les données voulues du fichier.
         */
    bool load(CellularAutomata*& automate);
    //~fichierConfig1D(){f.close();}
private:

};



/*! \class fichierConfig2D
  * \brief Classe héritant de fichier permettant de sauvegarder la configuration d'un automate 2D
  * \sa fichier, fenetre2D, fichierEtat2D
  *
  * Cette classe abstraite permet de sauvegarder la configuration d'un automate 2D
  */
class fichierConfig2D : public fichier
{
public:
        /*!
         * \brief Constructeur de la classe fichierConfig2D
         * \param nom Paramètre de type \a const \a std::string représentant le nom du fichier
         *
         * Constructeur de la classe fichierConfig2D faisant appel au constructeur de la classe \a fichier avec le paramètre \a nom.
         */
    fichierConfig2D(const std::string nom) : fichier(nom) {}
        /*!
         * \brief Méthode de la classe fichierConfig2D
         * \param automate Paramètre de type \a const \a CellularAutomata& représentant l'automate 1D dont on veut sauvegarder les données
         *
         * Cette méthode permet de sauvegarder la configuration d'un automate 2D dans un fichier.
         */
    bool save(const CellularAutomata& automate);
        /*!
         * \brief Méthode de la classe fichierConfig2D
         * \param automate Paramètre de type \a CellularAutomata*& représentant l'automate 2D pour lequel on veut charger l'état de départ
         * \sa CABuilder2D
         *
         * Cette méthode permet de charger un état de départ contenu dans un fichier, dans un automate 2D.
         * Elle fait notamment appel à \a CABuilder2D pour construire les sous parties de l'automate avec les données voulues du fichier.
         */
    bool load(CellularAutomata*& automate);
    //~fichierConfig2D(){f.close();}
private:

};

#endif // FICHIER_H
