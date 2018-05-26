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






unsigned int puissance(unsigned int a, unsigned int b)
{
    int power = 1;
    for (int i=1;i<=b;i++)
        power *= a;
    return power;
}

