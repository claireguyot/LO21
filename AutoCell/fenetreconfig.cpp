#include "fenetreconfig.h"
unsigned int fenetreElementaryRule::m_ordreVoisinage = 1;
fenetreElementaryRule::fenetreElementaryRule(QWidget *parent): fenetreConfig(parent)
{
    m_nombreEtats = new QSpinBox(this);
    m_nombreEtats->setRange(2,4);

    m_regleValidator = new QRegExpValidator(this);



    m_regle = new QLineEdit(this);
    m_regle->setValidator(m_regleValidator);

    changementRegExp();

    QFormLayout *formulaire = new QFormLayout;
    formulaire->addRow("nombre d'Etats",m_nombreEtats);
    formulaire->addRow("Regle de transition",m_regle);
    QString text= "Informations: \n L'ordre du voisinage est de 1 obligatoirement car sinon la règle serait beaucoup trop longue pour un nombre d'Etats supérieur ou égal à 3.\n etats:\n 0 = blanc\n 1= noir\n 2 = vert\n 3= rouge\nRègle de transition :\n- doit avoir une taille égale à (nombre d'etats)^(nombre de voisins)\n- doit comporter que des chiffres de 0 à nombre d'Etats.";
    QPlainTextEdit* info = new QPlainTextEdit(text);
    info->setReadOnly(true);

    nbCaract = new QLabel();

    changementLabel();
    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(formulaire);
    layoutPrincipal->addWidget(nbCaract);
    layoutPrincipal->addWidget(info);
    setLayout(layoutPrincipal);

    connect(m_nombreEtats,SIGNAL(valueChanged(int)),this,SLOT(changementRegExp()));
    connect(m_nombreEtats,SIGNAL(valueChanged(int)),this,SLOT(changementLabel()));
    connect(m_regle,SIGNAL(textChanged(QString)),this,SLOT(changementLabel()));
}

void fenetreElementaryRule::constructionAutomate() const
{
    unsigned int nombreVoisins = 2*m_ordreVoisinage+1;
    unsigned int nbCaract =puissance(m_nombreEtats->value(),nombreVoisins);
    if(m_regle->text() == "" || m_regle->text().length() != nbCaract)
       QMessageBox::critical(0, "Erreur", "Problème de taille de la règle");
    else
    {
        CABuilder1D& builder = CABuilder1D::getInstance();
        builder.BuildVoisinageDef(m_ordreVoisinage);
        builder.BuildElementaryRule(m_regle->text().toStdString(), m_nombreEtats->value());
        int nombreEtats = m_nombreEtats->value();
        emit configConstruite(nombreEtats);

    }
}

void fenetreElementaryRule::changementRegExp()
{
   switch(m_nombreEtats->value())
   {
   case 2:
       m_regleValidator->setRegExp(QRegExp("[0-1]+"));
       break;
   case 3:
       m_regleValidator->setRegExp(QRegExp("[0-2]+"));
       break;
   case 4:
       m_regleValidator->setRegExp(QRegExp("[0-3]+"));
       break;
   default:
       m_regleValidator->setRegExp(QRegExp("[0-1]+"));
   }
   m_regle->clear();
}

void fenetreElementaryRule::changementLabel()
{
    nbCaract->clear();
    unsigned int nombreVoisins = 2*m_ordreVoisinage+1;
    unsigned int nbCarac =puissance(m_nombreEtats->value(),nombreVoisins)- m_regle->text().length();
    QString test("Nombre de caractères nécessaires: ");
    test += nbCarac/10 + '0';
    nbCarac = nbCarac%10;
    test += nbCarac + '0';
    nbCaract->setText(test);
}

unsigned int fenetreGameOfLife::m_nombreEtats = 2;

fenetreGameOfLife::fenetreGameOfLife(QWidget *parent): fenetreConfig(parent)
{
    m_choixVoisinage = new QComboBox(this);
    m_choixVoisinage->addItem("Moore");
    m_choixVoisinage->addItem("Von Neumann");

    m_ordreVoisinage = new QSpinBox(this);
    m_ordreVoisinage->setRange(1,50);

    m_maxVivants = new QSpinBox(this);
    m_maxVivants->setMinimum(0);

    m_minVivants = new QSpinBox(this);
    m_minVivants->setMinimum(0);



    QFormLayout *formulaire = new QFormLayout;
    formulaire->addRow("type de voisinage",m_choixVoisinage);
    formulaire->addRow("ordre du voisinage",m_ordreVoisinage);
    formulaire->addRow("nombre minimum de voisins vivants", m_minVivants);
    formulaire->addRow("nombre maximum de Voisins vivants", m_maxVivants);
    QString text= "Informations Jeu de la vie: \n- 2 etats possibles:\n blanc = vivant\n noir= mort\n- Ordre du voisinage = distance maximum possible entre une cellule et le voisin le plus lointain \n - Entrer un ordre plus grand que la taille de la grille ne pose pas de problème les 'voisins' qui n'existent pas ne seront pas ajoutés \n- nombre minimum de voisins et nombre maximum de voisins:\n Nombre minimum et maximum de voisins vivants au temps t pour que la cellule soit vivante au temps t+1.\n- Type de voisinage:\n - Moore: carré centré autour de la cellule\n - Von Neumann: Croix(+) centrée autour de la cellule ";
    QPlainTextEdit* info = new QPlainTextEdit(text);
    info->setReadOnly(true);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(formulaire);
    layoutPrincipal->addWidget(info);
    setLayout(layoutPrincipal);

}

void fenetreGameOfLife::constructionAutomate() const
{
    if(m_minVivants->value()>m_maxVivants->value()) QMessageBox::critical(0,"Erreur","Le nombre minimum de voisins vivants est supérieur au nombre maximum");
    else
    {
        CABuilder2D& builder = CABuilder2D::getInstance();
        switch(m_choixVoisinage->currentIndex())
        {
        case 0:
            builder.BuildVoisinageMoore(m_ordreVoisinage->value());
            break;
        case 1:
            builder.BuildVoisinageVonNeumann(m_ordreVoisinage->value());
            break;
        default:
            builder.BuildVoisinageMoore(m_ordreVoisinage->value());
            break;
        }
        builder.BuildGameOfLife(m_minVivants->value(),m_maxVivants->value());
        emit configConstruite(m_nombreEtats);

    }
}

unsigned int fenetreFeuForet::m_nombreEtats = 4;

fenetreFeuForet::fenetreFeuForet(QWidget *parent): fenetreConfig(parent)
{
    m_choixVoisinage = new QComboBox(this);
    m_choixVoisinage->addItem("Moore");
    m_choixVoisinage->addItem("Von Neumann");

    m_ordreVoisinage = new QSpinBox(this);
    m_ordreVoisinage->setRange(1,50);





    QFormLayout *formulaire = new QFormLayout;
    formulaire->addRow("type de voisinage",m_choixVoisinage);
    formulaire->addRow("ordre du voisinage",m_ordreVoisinage);

    QString text= "Informations Feu de Forêt: \n- 4 etats possibles:\n blanc = vide\n noir= arbre mort\n rouge = arbre en feu\n vert = arbre vivant\n- Règle de transition\n - vide->vide\n - Feu->arbre mort\n - Arbre mort-> Arbre mort\n - Arbre vivant -> Feu si un voisin est en feu vivant sinon\n- Ordre du voisinage = distance maximum possible entre une cellule et le voisin le plus lointain \n - Entrer un ordre plus grand que la taille de la grille ne pose pas de problème les 'voisins' qui n'existent pas ne seront pas ajoutés \n- Type de voisinage:\n - Moore: carré centré autour de la cellule\n - Von Neumann: Croix(+) centrée autour de la cellule ";
    QPlainTextEdit* info = new QPlainTextEdit(text);
    info->setReadOnly(true);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(formulaire);
    layoutPrincipal->addWidget(info);
    setLayout(layoutPrincipal);

}

void fenetreFeuForet::constructionAutomate() const
{

        CABuilder2D& builder = CABuilder2D::getInstance();
        switch(m_choixVoisinage->currentIndex())
        {
        case 0:
            builder.BuildVoisinageMoore(m_ordreVoisinage->value());
            break;
        case 1:
            builder.BuildVoisinageVonNeumann(m_ordreVoisinage->value());
            break;
        default:
            builder.BuildVoisinageMoore(m_ordreVoisinage->value());
            break;
        }
        builder.BuildFeuForet();
        emit configConstruite(m_nombreEtats);


}



unsigned int puissance(unsigned int a, unsigned int b)
{
    int power = 1;
    for (int i=1;i<=b;i++)
        power *= a;
    return power;
}


