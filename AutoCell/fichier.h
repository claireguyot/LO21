#ifndef FICHIER_H
#define FICHIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <QMessageBox>
#include "cellularautomata.h"
#include "cabuilder.h"
#include "fenetre1d.h"
#include "fenetre2d.h"

#define TAILLE_BUF 100

class fenetre1D;
class fenetre2D;

class fichier
{
public:
    fichier(const std::string nom) : nomF(nom){}
    virtual bool save(const CellularAutomata& automate)=0;
    virtual bool load(CellularAutomata*& automate)=0;
    virtual ~fichier(){if(f.is_open()) f.close();}
protected:
    std::string nomF;
    std::fstream f;
};

class fichierEtat1D : public fichier
{
public:
    fichierEtat1D(const std::string nom) : fichier(nom) {}
    bool save(const CellularAutomata& automate);
    bool load(CellularAutomata*& automate);
    //~fichierEtat1D(){f.close();}
private:

};

class fichierEtat2D : public fichier
{
public:
    fichierEtat2D(const std::string nom) : fichier(nom) {}
    bool save(const CellularAutomata& automate);
    bool load(CellularAutomata*& automate);
    //~fichierEtat2D(){f.close();}
private:

};

class fichierConfig1D : public fichier
{
public:
    fichierConfig1D(const std::string nom) : fichier(nom) {}
    bool save(const CellularAutomata& automate);
    bool load(CellularAutomata*& automate);
    //~fichierConfig1D(){f.close();}
private:

};

class fichierConfig2D : public fichier
{
public:
    fichierConfig2D(const std::string nom) : fichier(nom) {}
    bool save(const CellularAutomata& automate);
    bool load(CellularAutomata*& automate);
    //~fichierConfig2D(){f.close();}
private:

};

#endif // FICHIER_H
