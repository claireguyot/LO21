#ifndef FICHIER_H
#define FICHIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "cellularautomata.h"
#include "fichierexception.h"

class fichier
{
public:
    fichier(const std::string nom) : nomF(nom){}
    virtual void save(const CellularAutomata& automate) = 0;
    virtual void load(CellularAutomata& automate) = 0;
    virtual ~fichier(){f.close();}
protected:
    std::string nomF;
    std::fstream f;
};

class fichierEtat : public fichier
{
public:
    fichierEtat(const std::string nom) : fichier(nom) {this->nomF = nom;}
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
    ~fichierEtat(){f.close();}
private:

};

class fichierConfig : public fichier
{
public:
    fichierConfig(const std::string nom) : fichier(nom) {this->nomF = nom;}
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
    ~fichierConfig(){f.close();}
private:

};

#endif // FICHIER_H
