#ifndef FICHIER_H
#define FICHIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <QMessageBox>
#include "cellularautomata.h"
#include "cabuilder.h"
#include "fichierexception.h"
#include "fenetre1d.h"
#include "fenetre2d.h"

class fichier
{
public:
    fichier(const std::string nom) : nomF(nom){}
    virtual ~fichier(){f.close();}
protected:
    std::string nomF;
    std::fstream f;
};

class fichierEtat : public fichier
{
public:
    fichierEtat(const std::string nom) : fichier(nom){}
    virtual void save(const fenetre1D* fen = nullptr);
    virtual void load(fenetre1D& fen) = 0;
};

class fichierConfig : public fichier
{
public:
    fichierConfig(const std::string nom) : fichier(nom){}
    virtual void save(const fenetre2D& fen) = 0;
    virtual void load(fenetre2D& fen) = 0;
};

class fichierEtat1D : public fichierEtat
{
public:
    fichierEtat1D(const std::string nom) : fichierEtat(nom) {}
    void load(const fenetre1D& fen);
    ~fichierEtat1D(){f.close();}
private:

};

class fichierEtat2D : public fichierEtat
{
public:
    fichierEtat2D(const std::string nom) : fichierEtat(nom) {}
    void load(const fenetre2D& fen);
    ~fichierEtat2D(){f.close();}
private:

};

class fichierConfig1D : public fichierConfig
{
public:
    fichierConfig1D(const std::string nom) : fichierConfig(nom) {}
    void save(const fenetre1D& fen);
    void load(const fenetre1D& fen);
    ~fichierConfig1D(){f.close();}
private:

};

class fichierConfig2D : public fichierConfig
{
public:
    fichierConfig2D(const std::string nom) : fichierConfig(nom) {}
    void save(const fenetre2D& fen);
    void load(const fenetre2D& fen);
    ~fichierConfig2D(){f.close();}
private:

};

#endif // FICHIER_H
