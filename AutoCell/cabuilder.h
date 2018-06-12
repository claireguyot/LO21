#ifndef CABUILDER_H
#define CABUILDER_H
/*!
  * \file cabuilder.h
  * \brief Déclaration des classes CABuilder1D et CABuilder2D selon le Design Pattern \a Builder.
*/

#include "cellularautomata.h"
#include <vector>

/*!
 * \class CABuilder
 * \brief Classe de base permettant de construire les sous-parties nécessaires à la construction d'un \a CellularAutomata.
 *
 * Les accesseurs sur les attributs et méthodes permettant de construire les éléments.
 * Les constructeurs et destructeurs des classes construites ne sont pas en \a private car cette classe permet seulement de stocker les éléments nécessaires à la construction de \a CellularAutomata, ce n'est pas une fabrique à proprement parlé et il pourrait être possible de construire ces éléments autrement.
 * \a Ex: la classe \a CellularAutomata construit des \a Etat. On aurait pu factoriser le code (héritage) des deux \a Builder.
 *
 * Cette classe n'est pas instanciable car elle ne sert qu'à "factoriser" du code commun à CABuilder1D et CABuilder2D pour éviter de copier-coller le même morceau de code.
 * Elle n'est cependant pas virtuelle pure (car toutes les méthodes sont bien définies et il est impossible de déclarer une méthode virtuelle pure qui pourra être utile à la fois dans CABuilder1D et CABuilder2D).
 *
 * L'implémentation nécessite de bloquer l'utilisation du \a Simulateur lorsque l'on fait une modification du \a Simulateur car lorsque l'on modifie une sous-partie, on supprime l'ancienne.
 *
 * \warning L'implémentation ne permet pas de pouvoir exécuter plusieurs automates cellulaires différents en même temps.
 */
class CABuilder
{
protected:
    /*!
     * \brief Constructeur de recopie par défaut de la classe abstraite CABuilder supprimé pour s'assurer que l'automate construit est unique.
     */
    CABuilder(const CABuilder&) = delete;
    /*!
     * \brief Opérateur d'affectation par défaut de la classe abstraite CABuilder supprimé pour s'assurer que l'automate construit est unique.
     */
    CABuilder& operator=(const CABuilder&) = delete;
    /*!
     * \brief Constructeur de la classe abstraite CABuilder.
     * \sa ~CABuilder(), CellularAutomata
     *
     * Ce constructeur permet de mettre tous les attributs à \a nullptr pour initialiser un automate.
     * Il est en privé afin d'empêcher l'utilisateur d'instancier CABuilder sinon la classe serait instanciable, et cela n'aurait pas de sens de l'instancier étant donné qu'elle ne permet de construire qu'une sous partie d'un automate.
     */
    CABuilder(): m_etatDepart(nullptr),m_generateurEtat(nullptr),m_transitionRule(nullptr),m_voisinageDefinition(nullptr)
    {

    }
    /*!
     * \brief Destructeur virtuel de la classe abstraite CABuilder.
     * \sa CABuilder(), CellularAutomata
     *
     * Ce destructeur est appelé lors de la destruction d'un objet de la classe \a CABuilder. Il permet de désallouer la mémoire pour les attributs d'un automate qui sont des pointeurs.
     * Il est en privé afin d'empêcher l'utilisateur d'instancier CABuilder sinon la classe serait instanciable, et cela n'aurait pas de sens de l'instancier étant donné qu'elle ne permet de construire qu'une sous partie d'un automate.
     */
    virtual ~CABuilder()
    {
        delete m_etatDepart;
        delete m_generateurEtat;
        delete m_transitionRule;
        delete m_voisinageDefinition;
    }
    /*!
     * \brief Attribut de la classe abstraite CABuilder.
     *
     * Cet attribut est un pointeur sur \a GenerateurEtat. Il permet d'attribuer un générateur d'état à l'automate construit à l'aide des classes Builder.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    GenerateurEtat *m_generateurEtat;
    /*!
     * \brief Attribut de la classe abstraite CABuilder.
     *
     * Cet attribut est un pointeur sur \a Etat. Il permet d'attribuer un état de départ à l'automate construit à l'aide des classes Builder.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    Etat *m_etatDepart;
    /*!
     * \brief Attribut de la classe abstraite CABuilder.
     *
     * Cet attribut est un pointeur sur \a TransitionRule. Il permet d'attribuer une règle de transition à l'automate construit à l'aide des classes Builder.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    TransitionRule* m_transitionRule;
    /*!
     * \brief Attribut de la classe abstraite CABuilder.
     *
     * Cet attribut est un pointeur sur \a Voisinage. Il permet d'attribuer un voisinage à l'automate construit à l'aide des classes Builder.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    Voisinage* m_voisinageDefinition;
public:
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_voisinageDefinition de la classe abstraite CABuilder.
         *
         * Cet accesseur permet d'accéder en lecture à l'attribut privé \a m_voisinageDefinition, en le renvoyant en \a const. Cette méthode ne modifie par l'attribut, c'est pourquoi elle est \a const.
         */
    Voisinage const* GetVoisinageDefinition() const {return m_voisinageDefinition;}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_transitionRule de la classe abstraite CABuilder.
         *
         * Cet accesseur permet d'accéder en lecture à l'attribut privé \a m_transitionRule, en le renvoyant en \a const. Cette méthode ne modifie par l'attribut, c'est pourquoi elle est \a const.
         */
    TransitionRule const* GetTransitionRule() const {return m_transitionRule;}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_etatDepart de la classe abstraite CABuilder.
         *
         * Cet accesseur permet d'accéder en lecture à l'attribut privé \a m_etatDepart, en le renvoyant en \a const. Cette méthode ne modifie par l'attribut, c'est pourquoi elle est \a const.
         */
    Etat const* GetEtatDepart() const{ return m_etatDepart;}
        /*!
         * \brief Accesseur en lecture de l'attribut \a m_generateurEtat de la classe abstraite CABuilder.
         *
         * Cet accesseur permet d'accéder en lecture à l'attribut privé \a m_generateurEtat, en le renvoyant en \a const. Cette méthode ne modifie par l'attribut, c'est pourquoi elle est \a const.
         */
    GenerateurEtat const* GetGenerateurEtat() const {return m_generateurEtat;}
        /*!
         * \brief Méthode de la classe abstraite CABuilder permettant de construire un automate ayant un générateur d'état aléatoire.
         *
         * Cette méthode attribut un nouveau générateur d'état aléatoire (avec la classe \a GenerateurRandom) à un automate, également si le générateur d'état de celui-ci est déjà existant.
         */
    void BuildGenerateurEtatRandom() {
        if(m_generateurEtat != nullptr)
            delete m_generateurEtat;
        m_generateurEtat = new GenerateurRandom;
    }
        /*!
         * \brief Méthode de la classe abstraite CABuilder permettant de construire un automate ayant un générateur d'état symétrique selon l'axe vertical.
         *
         * Cette méthode attribut un nouveau générateur d'état symétrique selon l'axe vertical (avec la classe \a GenerateurSymetrieAxeVertical) à un automate, également si le générateur d'état de celui-ci est déjà existant.
         */
    void BuildGenerateurEtatSymetrieAxeVertical()
    {
        if(m_generateurEtat != nullptr)
            delete m_generateurEtat;
        m_generateurEtat = new GenerateurSymetrieAxeVertical;
    }

};


/*!
 * \class CABuilder1D
 * \brief Classe permettant de construire toutes les sous-parties nécessaires à la construction d'un automate cellulaire 1D en utilisant le Design Pattern \a Singleton.
 *
 * On a décidé d'utiliser le Design Pattern \a Singleton sur cette classe afin d'être sûrs de n'avoir qu'une seule instance du \a builder pour créer un seul simulateur 1D car notre application ne peut gérer qu'un simulateur 1D à la fois.
 *
 * \todo Améliorer l'implémentation pour pouvoir gérer la construction de plusieurs automates en même temps.
 * \warning L'implémentation ne permet pas de pouvoir exécuter plusieurs automates cellulaires différents en même temps.
 */
class CABuilder1D : public CABuilder
{
private:
    /*!
     * \brief Constructeur de la classe CABuilder1D.
     *
     * Ce constructeur permet de mettre tous les attributs à \a nullptr pour initialiser un automate 1D car il fait appel au constructeur de la classe mère \a CABuilder.
     */
    CABuilder1D() : CABuilder()
    {

    }
    /*!
     * \brief Destructeur de la classe CABuilder1D.
     *
     * Ce destructeur est appelé lors de la destruction d'un objet de la classe \a CABuilder1D. Il permet de supprimer l'attribut automatique \a m_nbEtats, et de désallouer, en faisant appel au destructeur de la classe mère \a CABuilder, la mémoire pour les autres attributs d'un automate 1D qui sont des pointeurs.
     */
    ~CABuilder1D()
    {

    }
    /*!
     * \brief Constructeur de recopie par défaut supprimé pour s'assurer que l'automate 1D construit est unique.
     */
    CABuilder1D(const CABuilder1D&) = delete;
    /*!
     * \brief Opérateur d'affectation par défaut supprimé pour s'assurer que l'automate 1D construit est unique.
     */
    CABuilder1D& operator=(const CABuilder1D&) = delete;
    /*!
     * \brief Attribut de la classe CABuilder1D.
     *
     * Cet attribut est un \a unsigned \a int. Il permet d'attribuer un nombre d'états à l'automate construit à l'aide des classes Builder.
     * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
     */
    unsigned int m_nbEtats;
public:
        /*!
         * \brief Méthode statique de la classe CABuilder1D permettant de retourner un automate de la classe.
         *
         * Cette méthode retourne une référence sur un automate 1D unique, qui est instancié au sein même de cette méthode.
         * Cette méthode est statique car il s'agit d'une caractéristique commune et partagée par tous les objets de la classe \a CABuilder1D.
         */
    static CABuilder1D& getInstance()
    {
            static CABuilder1D m;
            return m;
    }
        /*!
         * \brief Méthode de la classe CABuilder1D permettant de définir le voisinage d'un automate 1D.
         * \param ordre Paramètre de type \a unsigned \a int permettant de définir l'ordre du voisinage d'un automate 1D.
         * \sa Voisinage1D
         *
         * Cette méthode permet de définir l'ordre du voisinage d'un automate 1D, si celui-ci existe et n'a pas le même ordre, en faisant notamment appel au constructeur de la classe \a Voisinage1D.
         * Si le voisinage existe déjà mais qu'il n'est pas du même ordre que l'ordre passé en paramètre de la méthode, le voisinage actuel \a m_voisinageDefinition est alors supprimé en désallouant la mémoire et en créant un voisinage d'ordre \a ordre.
         */
    void BuildVoisinageDef(unsigned int ordre) {
        if (m_voisinageDefinition != nullptr && m_voisinageDefinition->GetOrdre() == ordre) return;
        if(m_voisinageDefinition != nullptr)
        {
            delete m_voisinageDefinition;
            m_voisinageDefinition = nullptr;
        }
        m_voisinageDefinition = new Voisinage1D(ordre);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder1D permettant de définir l'état de départ d'un automate 1D.
         * \param taille Paramètre de type \a unsigned \a int permettant de définir la taille de l'état de départ d'un automate 1D.
         * \param generateur Paramètre de type \a GenerateurEtat \a const& permettant de définir le générateur d'état associé à l'état de départ d'un automate 1D.
         * \param nbEtats Paramètre de type \a int permettant de définir le nombre d'états associé l'état de départ d'un automate 1D.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 1D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a taille, de générateur d'états \a générateur, et de nombre d'états \a nbEtats.
         */
    void BuildEtatDepart(unsigned int taille, GenerateurEtat const& generateur,int nbEtats)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(1,taille,generateur,nbEtats);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder1D permettant de définir l'état de départ d'un automate 1D.
         * \param taille Paramètre de type \a unsigned \a int permettant de définir la taille de l'état de départ d'un automate 1D.
         * \param tab Paramètre de type \a int** permettant de définir l'état associé à l'état de départ d'un automate 1D, à partir d'un état stocké dans un tableau d' \a int à double entrée.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 1D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a taille, et d'état celui contenu dans \a tab.
         */
    void BuildEtatDepart(unsigned int taille, int** tab)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(1,taille,tab);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder1D permettant de définir l'état de départ d'un automate 1D.
         * \param taille Paramètre de type \a unsigned \a int permettant de définir la taille de l'état de départ d'un automate 1D.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 1D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a taille.
         */
    void BuildEtatDepart(unsigned int taille)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(1,taille);
    }
        /*!
         * \brief Méthode de la classe CABuilder1D permettant de définir la règle de transition d'un automate 1D.
         * \param rule Paramètre de type \a std::string \a const& permettant de définir la règle à suivre de la règle de transition d'un automate 1D.
         * \param nbEtats Paramètre de type \a unsigned \a int permettant de définir le nombre d'états d'un automate 1D.
         * \sa ElementaryRule
         *
         * Cette méthode permet de définir la règle de transition d'un automate 1D en faisant notamment appel à un des constructeurs de la classe \a ElementaryRule.
         * Si la règle de transition existe déjà, la règle de transition actuelle \a m_transitionRule est alors supprimée en désallouant la mémoire et en créant une règle de transition de règle \a rule, et de nombre d'états \a nbEtats.
         */
    void BuildElementaryRule(std::string const& rule, unsigned int nbEtats)
    {
        if(m_transitionRule != nullptr)
        {
            delete m_transitionRule;
            m_transitionRule= nullptr;
        }
        m_transitionRule = new ElementaryRule(rule,nbEtats);
    }


};


/*!
 * \class CABuilder2D
 * \brief Classe permettant de construire toutes les sous-parties nécessaires à la construction d'un automate cellulaire 2D en utilisant le Design Pattern \a Singleton.
 *
 * On a décidé d'utiliser le Design Pattern \a Singleton sur cette classe afin d'être sûrs de n'avoir qu'une seule instance du \a builder pour créer un seul simulateur 2D car notre application ne peut gérer qu'un simulateur 2D à la fois.
 *
 * \todo Améliorer l'implémentation pour pouvoir gérer la construction de plusieurs automates en même temps.
 * \warning L'implémentation ne permet pas de pouvoir exécuter plusieurs automates cellulaires différents en même temps.
 */
class CABuilder2D : public CABuilder
{
private:
    /*!
     * \brief Constructeur de la classe CABuilder2D.
     *
     * Ce constructeur permet de mettre tous les attributs à \a nullptr pour initialiser un automate 2D car il fait appel au constructeur de la classe mère \a CABuilder.
     */
    CABuilder2D() : CABuilder()
    {

    }
    /*!
     * \brief Destructeur de la classe CABuilder2D.
     *
     * Ce destructeur est appelé lors de la destruction d'un objet de la classe \a CABuilder2D. Il permet de désallouer, en faisant appel au destructeur de la classe mère \a CABuilder, la mémoire des attributs d'un automate 2D qui sont des pointeurs.
     */
    ~CABuilder2D() = default;
    /*!
     * \brief Constructeur de recopie par défaut supprimé pour s'assurer que l'automate 2D construit est unique.
     */
    CABuilder2D(const CABuilder2D&) = delete;
    /*!
     * \brief Opérateur d'affectation par défaut supprimé pour s'assurer que l'automate 2D construit est unique.
     */
    CABuilder2D& operator=(const CABuilder2D&) = delete;
public:
        /*!
         * \brief Méthode statique de la classe CABuilder2D permettant de retourner un automate de la classe.
         *
         * Cette méthode retourne une référence sur un automate 2D unique, qui est instancié au sein même de cette méthode.
         * Cette méthode est statique car il s'agit d'une caractéristique commune et partagée par tous les objets de la classe \a CABuilder2D.
         */
    static CABuilder2D& getInstance()
    {
        static CABuilder2D m;
        return m;
    }
        /*!
         * \brief Méthode de la classe CABuilder2D permettant de définir le voisinage selon Von Neumann d'un automate 2D.
         * \param ordre Paramètre de type \a unsigned \a int permettant de définir l'ordre du voisinage d'un automate 2D.
         * \sa VonNeumann
         *
         * Cette méthode permet de définir l'ordre du voisinage d'un automate 2D en faisant notamment appel au constructeur de la classe \a VonNeumann.
         * Si le voisinage existe déjà mais qu'il n'est pas du même ordre que l'ordre passé en paramètre de la méthode, le voisinage actuel \a m_voisinageDefinition est alors supprimé en désallouant la mémoire et en créant un voisinage d'ordre \a ordre.
         */
    void BuildVoisinageVonNeumann(unsigned int ordre) {

        if(m_voisinageDefinition != nullptr)
        {
            delete m_voisinageDefinition;
            m_voisinageDefinition = nullptr;
        }
        m_voisinageDefinition = new VonNeumann(ordre);
    }
        /*!
         * \brief Méthode de la classe CABuilder2D permettant de définir le voisinage selon Moore d'un automate 2D.
         * \param ordre Paramètre de type \a unsigned \a int permettant de définir l'ordre du voisinage d'un automate 2D.
         * \sa Moore
         *
         * Cette méthode permet de définir l'ordre du voisinage d'un automate 2D en faisant notamment appel au constructeur de la classe \a Moore.
         * Si le voisinage existe déjà mais qu'il n'est pas du même ordre que l'ordre passé en paramètre de la méthode, le voisinage actuel \a m_voisinageDefinition est alors supprimé en désallouant la mémoire et en créant un voisinage d'ordre \a ordre.
         */
    void BuildVoisinageMoore(unsigned int ordre) {

        if(m_voisinageDefinition != nullptr)
        {
            delete m_voisinageDefinition;
            m_voisinageDefinition = nullptr;
        }
        m_voisinageDefinition = new Moore(ordre);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder2D permettant de définir l'état de départ d'un automate 2D.
         * \param nbLignes Paramètre de type \a unsigned \a int permettant de définir le nombre de lignes de l'état de départ d'un automate 2D.
         * \param nbColonnes Paramètre de type \a unsigned \a int permettant de définir le nombre de colonnes de l'état de départ d'un automate 2D.
         * \param generateur Paramètre de type \a GenerateurEtat \a const& permettant de définir le générateur d'état associé à l'état de départ d'un automate 2D.
         * \param nbEtats Paramètre de type \a int permettant de définir le nombre d'états associé l'état de départ d'un automate 2D.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 2D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a nbLignes et \a nbColonnes, de générateur d'états \a générateur, et de nombre d'états \a nbEtats.
         */
    void BuildEtatDepart(unsigned int nbLignes, unsigned int nbColonnes, GenerateurEtat const& generateur,int nbEtats)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(nbLignes,nbColonnes,generateur,nbEtats);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder2D permettant de définir l'état de départ d'un automate 2D.
         * \param nbLignes Paramètre de type \a unsigned \a int permettant de définir le nombre de lignes de l'état de départ d'un automate 2D.
         * \param nbColonnes Paramètre de type \a unsigned \a int permettant de définir le nombre de colonnes de l'état de départ d'un automate 2D.
         * \param tab Paramètre de type \a int** permettant de définir l'état associé à l'état de départ d'un automate 2D, à partir d'un état stocké dans un tableau d' \a int à double entrée.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 2D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a nbLignes et \a nbColonnes, et d'état celui contenu dans \a tab.
         */
    void BuildEtatDepart(unsigned int nbLignes, unsigned int nbColonnes, int** tab)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(nbLignes,nbColonnes,tab);
    }
        /*!
         * \brief Surcharge de la méthode de la classe CABuilder2D permettant de définir l'état de départ d'un automate 2D.
         * \param nbLignes Paramètre de type \a unsigned \a int permettant de définir le nombre de lignes de l'état de départ d'un automate 2D.
         * \param nbColonnes Paramètre de type \a unsigned \a int permettant de définir le nombre de colonnes de l'état de départ d'un automate 2D.
         * \sa Etat
         *
         * Cette méthode permet de définir l'état de départ d'un automate 2D en faisant notamment appel à un des constructeurs de la classe \a Etat.
         * Si l'état de départ existe déjà, l'état de départ actuel \a m_etatDepart est alors supprimé en désallouant la mémoire et en créant un état de départ de taille \a nbLignes et \a nbColonnes.
         */
    void BuildEtatDepart(unsigned int nbLignes, unsigned int nbColonnes)
    {
        if(m_etatDepart != nullptr)
        {
            delete m_etatDepart;
            m_etatDepart= nullptr;
        }
        m_etatDepart = new Etat(nbLignes,nbColonnes);
    }
        /*!
         * \brief Méthode de la classe CABuilder2D permettant de définir la règle de transition d'un automate 2D de type Jeu de la Vie.
         * \param minVoisinsVivants Paramètre de type \a unsigned \a int permettant de définir le nombre de voisins minimum d'une cellule pour la règle de transition du Jeu de la Vie.
         * \param maxVoisinsVivants Paramètre de type \a unsigned \a int permettant de définir le nombre de voisins maximum d'une cellule pour la règle de transition du Jeu de la Vie.
         * \sa GameOfLife
         *
         * Cette méthode permet de définir la règle de transition d'un automate 2D de type Jeu de la Vie, en faisant notamment appel à un des constructeurs de la classe \a GameOfLife.
         * Si la règle de transition de l'automate existe déjà, la règle de transition actuelle \a m_transitionRule est alors supprimée en désallouant la mémoire et en créant une règle de transition du Jeu de la Vie de minimum de voisins \a minVoisinsVivants, et de maximum de voisins \a maxVoisinsVivants.
         */
    void BuildGameOfLife(unsigned int minVoisinsVivants, unsigned int maxVoisinsVivants)
    {
        if(m_transitionRule != nullptr)
        {
            delete m_transitionRule;
            m_transitionRule = nullptr;
        }
        m_transitionRule = new GameOfLife(minVoisinsVivants,maxVoisinsVivants);
    }
        /*!
         * \brief Méthode de la classe CABuilder2D permettant de définir la règle de transition d'un automate 2D de type Feu de Forêt.
         * \sa FeuForet
         *
         * Cette méthode permet de définir la règle de transition d'un automate 2D de type Feu de Forêt, en faisant notamment appel à un des constructeurs de la classe \a FeuForet.
         * Si la règle de transition de l'automate existe déjà, la règle de transition actuelle \a m_transitionRule est alors supprimée en désallouant la mémoire et en créant une règle de transition du Feu de Forêt.
         */
    void BuildFeuForet()
    {
        if(m_transitionRule != nullptr)
        {
            delete m_transitionRule;
            m_transitionRule = nullptr;
        }
        m_transitionRule = new FeuForet();
    }

};

#endif // CABUILDER_H
