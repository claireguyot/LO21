#include "cabuilder.h"

/*!
 * \file cabuilder.cpp
 * \brief implémentation des méthodes de CABuilder1D et CABuilder2D
 */

CABuilder1D::~CABuilder1D()
{
    delete m_voisinageDefinition;
    delete m_transitionRule;
    delete m_generateurEtat;
    delete m_etatDepart;
}

CABuilder1D& CABuilder1D::getInstance()
{
    static CABuilder1D m;
    return m;
};

CABuilder2D::~CABuilder2D()
{
    delete m_voisinageDefinition;
    delete m_transitionRule;
    delete m_generateurEtat;
    delete m_etatDepart;
}

CABuilder2D& CABuilder2D::getInstance()
{
    static CABuilder2D m;
    return m;
};
