#include "fenetreconfig.h"
#include "fichier.h"

const unsigned int fenetreElementaryRule::m_ordreVoisinage = 1;

fenetreElementaryRule::fenetreElementaryRule(QWidget *parent): fenetreConfig(parent)
{
    m_nombreEtats = new QSpinBox(this);
    m_nombreEtats->setRange(2,4);

    m_regleValidator = new QRegExpValidator(this);



    m_regle = new QLineEdit(this);
    m_regle->setValidator(m_regleValidator);

    changementRegExp();

    m_formulaire = new QFormLayout;
    m_formulaire->addRow("nombre d'Etats",m_nombreEtats);
    m_formulaire->addRow("Regle de transition",m_regle);
    QString text= "Informations: \n L'ordre du voisinage, distance entre la cellule et son plus lointain voisin, est de 1 obligatoirement car sinon la règle serait beaucoup trop longue pour un nombre d'Etats supérieur ou égal à 3.\n etats:\n 0 = blanc\n 1 = noir\n 2 = vert\n 3 = rouge\nRègle de transition :\n- doit avoir une taille égale à (nombre d'etats)^(nombre de voisins)\n- doit comporter que des chiffres de 0 à nombre d'Etats-1.";
    m_info = new QPlainTextEdit(text);
    m_info->setReadOnly(true);

    nbCaract = new QLabel();

    changementLabel();
    m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addLayout(formulaire);
    m_layoutPrincipal->addWidget(nbCaract);
    m_layoutPrincipal->addWidget(info);
    setLayout(layoutPrincipal);

    connect(m_nombreEtats,SIGNAL(valueChanged(int)),this,SLOT(changementRegExp()));
    connect(m_nombreEtats,SIGNAL(valueChanged(int)),this,SLOT(changementLabel()));
    connect(m_regle,SIGNAL(textChanged(QString)),this,SLOT(changementLabel()));

    loadContexte();
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

   m_regle->clear();
   std::stringstream flux;
   flux << "[0-"<<m_nombreEtats->value()-1<<"]+";

   m_regleValidator->setRegExp(QRegExp(flux.str().c_str()));
}

void fenetreElementaryRule::changementLabel()
{
    nbCaract->clear();
    unsigned int nombreVoisins = 2*m_ordreVoisinage+1;
    int nbCarac =puissance(m_nombreEtats->value(),nombreVoisins)- m_regle->text().length();
    std::stringstream flux;
    flux << "Nombre de caractères nécessaires:"<<nbCarac;
    nbCaract->setText(QString(flux.str().c_str()));
}

const unsigned int fenetreGameOfLife::m_nombreEtats = 2;

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



    QFormLayout *m_formulaire = new QFormLayout;
    m_formulaire->addRow("type de voisinage",m_choixVoisinage);
    m_formulaire->addRow("ordre du voisinage",m_ordreVoisinage);
    m_formulaire->addRow("nombre minimum de voisins vivants", m_minVivants);
    m_formulaire->addRow("nombre maximum de Voisins vivants", m_maxVivants);
    QString text= "Informations Jeu de la vie: \n- 2 etats possibles:\n blanc = mort\n noir = vivant\n- Ordre du voisinage = distance maximum possible entre une cellule et le voisin le plus lointain \n - Entrer un ordre plus grand que la taille de la grille ne pose pas de problème les 'voisins' qui n'existent pas ne seront pas ajoutés \n- nombre minimum de voisins et nombre maximum de voisins:\n - Nombre minimum et maximum de voisins vivants au temps t pour que la cellule soit vivante au temps t+1 si la cellule était vivante au temps t (sinon elle meurt d'isolement ou de surpopulation).\n - si une cellule est 'morte' à l'instant t, elle repasse vivante à l'instant t+1 si il y exactements 'nombre max de voisins' cellules voisines vivantes à l'instant t.\n- Type de voisinage:\n - Moore: carré centré autour de la cellule\n - Von Neumann: Croix(+) centrée autour de la cellule ";
    QPlainTextEdit* m_info = new QPlainTextEdit(text);
    m_info->setReadOnly(true);

    QVBoxLayout* m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addLayout(m_formulaire);
    m_layoutPrincipal->addWidget(m_info);
    setLayout(m_layoutPrincipal);

    loadContexte();

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

const unsigned int fenetreFeuForet::m_nombreEtats = 4;

fenetreFeuForet::fenetreFeuForet(QWidget *parent): fenetreConfig(parent)
{
    m_choixVoisinage = new QComboBox(this);
    m_choixVoisinage->addItem("Moore");
    m_choixVoisinage->addItem("Von Neumann");

    m_ordreVoisinage = new QSpinBox(this);
    m_ordreVoisinage->setRange(1,50);





    QFormLayout *m_formulaire = new QFormLayout;
    m_formulaire->addRow("type de voisinage",m_choixVoisinage);
    m_formulaire->addRow("ordre du voisinage",m_ordreVoisinage);

    QString text= "Informations Feu de Forêt: \n- 4 etats possibles:\n blanc = vide\n noir= arbre mort\n rouge = arbre en feu\n vert = arbre vivant\n- Règle de transition\n - vide->vide\n - Feu->arbre mort\n - Arbre mort-> Arbre mort\n - Arbre vivant -> Feu si un voisin est en feu vivant sinon\n- Ordre du voisinage = distance maximum possible entre une cellule et le voisin le plus lointain \n - Entrer un ordre plus grand que la taille de la grille ne pose pas de problème les 'voisins' qui n'existent pas ne seront pas ajoutés \n- Type de voisinage:\n - Moore: carré centré autour de la cellule\n - Von Neumann: Croix(+) centrée autour de la cellule ";
    QPlainTextEdit* m_info = new QPlainTextEdit(text,this);
    m_info->setReadOnly(true);

    QVBoxLayout* m_layoutPrincipal = new QVBoxLayout();
    m_layoutPrincipal->addLayout(m_formulaire);
    m_layoutPrincipal->addWidget(m_info);
    setLayout(m_layoutPrincipal);

    loadContexte();

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


//SAUVEGARDE ET CHARGEMENT DU CONTEXTE

void fenetreElementaryRule::saveContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("ElementaryRuleWindow");

    settings.setValue("nbEtats",m_nombreEtats->value());
    settings.setValue("rule",m_regle->text());
    settings.endGroup();
}

void fenetreElementaryRule::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("ElementaryRuleWindow");

    m_nombreEtats->setValue(settings.value("nbEtats",m_nombreEtats->value()).toInt());
    m_regle->setText(settings.value("rule",m_regle->text()).toString());

    settings.endGroup();
}

void fenetreGameOfLife::saveContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("GameOfLifeWindow");

    settings.setValue("choixVoisinage",m_choixVoisinage->currentIndex());
    settings.setValue("ordreVoisinage",m_ordreVoisinage->value());
    settings.setValue("minVivants",m_minVivants->value());
    settings.setValue("maxVivants",m_maxVivants->value());

    settings.endGroup();
}

void fenetreGameOfLife::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("GameOfLifeWindow");

    m_choixVoisinage->setCurrentIndex(settings.value("choixVoisinage",m_choixVoisinage->currentIndex()).toInt());
    m_ordreVoisinage->setValue(settings.value("ordreVoisinage",m_ordreVoisinage->value()).toInt());
    m_minVivants->setValue(settings.value("minVivants",m_minVivants->value()).toInt());
    m_maxVivants->setValue(settings.value("maxVivants",m_maxVivants->value()).toInt());

    settings.endGroup();
}

void fenetreFeuForet::saveContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("ForestFireWindow");

    settings.setValue("choixVoisinage",m_choixVoisinage->currentIndex());
    settings.setValue("ordreVoisinage",m_ordreVoisinage->value());
    settings.endGroup();
}

void fenetreFeuForet::loadContexte()
{
    QSettings settings("options.ini", QSettings::IniFormat);

    settings.beginGroup("ForestFireWindow");

    m_choixVoisinage->setCurrentIndex(settings.value("choixVoisinage",m_choixVoisinage->currentIndex()).toInt());
    m_ordreVoisinage->setValue(settings.value("ordreVoisinage",m_ordreVoisinage->value()).toInt());

    settings.endGroup();
}
