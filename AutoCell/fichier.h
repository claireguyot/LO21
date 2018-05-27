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
    virtual ~fichier(){file.close;}
protected:
    std::string nomF;
    std::ofstream f;
};

class fichierEtat : public Fichier
{
public:
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
    ~fichierEtat(){f.close();}
    fichierEtat(const std::string nom) : nomF(nom){}
private:

}

class fichierConfig : public Fichier
{
public:
    void save(const CellularAutomata& automate);
    void load(CellularAutomata& automate);
    ~fichierConfig(){f.close();}
    fichierConfig(const std::string nom) : nomF(nom){}
private:

}

#endif // FICHIER_H
