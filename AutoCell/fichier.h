#ifndef FICHIER_H
#define FICHIER_H

#include <iostream>
#include <fstream>
#include "cellularautomata.h"
#include "fichierexception.h"

class fichier
{
public:
    fichier(const std::string nom) : nomF(nom){}
    virtual void save(const CellularAutomata& automate) = 0;
    virtual void Load(CellularAutomata& automate) = 0;
    virtual ~fichier(){file.close}
protected:
    std::string nomF;
    ofstream file;
};

class fichierEtat : public Fichier
{
public:
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
private:
    fichierEtat(const std::string nom) : nomF(nom){}
}

class fichierConfig : public Fichier
{
public:
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
private:
    fichierConfig(const std::string nom) : nomF(nom){}
}

#endif // FICHIER_H
