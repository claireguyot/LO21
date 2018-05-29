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
    virtual void save(const fenetre1D& fen)=0;
    virtual void load(const fenetre1D& fen)=0;
    virtual void save(const fenetre2D& fen)=0;
    virtual void load(const fenetre2D& fen)=0;
    ~fichier(){f.close();}
protected:
    std::string nomF;
    std::fstream f;
};

class fichierEtat1D : public fichier
{
public:
    fichierEtat1D(const std::string nom) : fichier(nom) {}
    void save(const fenetre1D& fen);
    void load(const fenetre1D& fen);
    virtual void save(const fenetre2D& fen){return;}
    virtual void load(const fenetre2D& fen){return;}
    ~fichierEtat1D(){f.close();}
private:

};

class fichierEtat2D : public fichier
{
public:
    fichierEtat2D(const std::string nom) : fichier(nom) {}
    void save(const fenetre2D& fen);
    void load(const fenetre2D& fen);
    virtual void save(const fenetre1D& fen){return;}
    virtual void load(const fenetre1D& fen){return;}
    ~fichierEtat2D(){f.close();}
private:

};

class fichierConfig1D : public fichier
{
public:
    fichierConfig1D(const std::string nom) : fichier(nom) {}
    void save(const fenetre1D& fen);
    void load(const fenetre1D& fen);
    virtual void save(const fenetre2D& fen){return;}
    virtual void load(const fenetre2D& fen){return;}
    ~fichierConfig1D(){f.close();}
private:

};

class fichierConfig2D : public fichier
{
public:
    fichierConfig2D(const std::string nom) : fichier(nom) {}
    void save(const fenetre2D& fen);
    void load(const fenetre2D& fen);
    virtual void save(const fenetre1D& fen){return;}
    virtual void load(const fenetre1D& fen){return;}
    ~fichierConfig2D(){f.close();}
private:

};

#endif // FICHIER_H
