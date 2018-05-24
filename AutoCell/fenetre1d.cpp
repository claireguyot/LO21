#include "fenetre1D.h"
unsigned int fenetre1D::dimension = 25;
unsigned int fenetre1D::nombreEtats = 25;
fenetre1D::fenetre1D(QWidget *parent) : QWidget(parent)
{
     num = new QSpinBox(this);
     num->setRange(0,255);
     numl = new QLabel("Numéro",this);
     numc = new QVBoxLayout();
     numc->addWidget(numl);
     numc->addWidget(num);

     numeroc = new QHBoxLayout();
     numeroc->addLayout(numc);

     zeroOneValidator = new QIntValidator(0,1,this);
     for(int i =0;i<8;i++)
     {
         int j = 7 - i;
         const char* chaine = NumToNumBit(j).c_str();
         char chaine2[3];
         chaine2[0]= chaine[5];
         chaine2[1]= chaine[6];
         chaine2[2]= chaine[7];

         numeroBitl[i]= new QLabel(QString(chaine2),this);
         numeroBit[i] = new QLineEdit("0",this);
         numeroBit[i]->setMaxLength(1);
         numeroBit[i]->setMaxLength(20);
         numeroBit[i]->setValidator(zeroOneValidator);

         QObject::connect(numeroBit[i],SIGNAL(textChanged(QString)),this,SLOT(synchronizeNumBitToNum(QString)));
         bitc[i] = new QVBoxLayout();
         bitc[i]->addWidget(numeroBitl[i]);
         bitc[i]->addWidget(numeroBit[i]);
         numeroc->addLayout(bitc[i]);
     }

     depart = new QTableWidget(1,dimension,this);
     depart->horizontalHeader()->setVisible(false);
     depart->verticalHeader()->setVisible(false);
     depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     unsigned int taille = 50;
     depart->setFixedSize(dimension*taille,taille);
     for(unsigned int i = 0;i<dimension;i++)
     {
         depart->setColumnWidth(i,taille);
         depart->setItem(0, i, new QTableWidgetItem(""));
     }
     connect(depart,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(cellActivation(QModelIndex)));



     simulation = new QPushButton("Simulation",this);
     connect(simulation,SIGNAL(clicked(bool)),this,SLOT(faireSimulation()));


     layout = new QVBoxLayout;

     etats  = new QTableWidget(dimension,dimension,this);
     etats->horizontalHeader()->setVisible(false);
     etats->verticalHeader()->setVisible(false);
     etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     etats->setFixedSize(dimension*taille,dimension*taille);
     //non éditable
     etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
     for(unsigned int i=0;i<dimension;i++)
     {
         etats->setColumnWidth(i,taille);
         etats->setRowHeight(i,taille);
         for(unsigned int j = 0;j<dimension;j++)
             etats->setItem(j,i,new QTableWidgetItem(""));

     }

     layout->addLayout(numeroc);
     layout->addWidget(depart);
     layout->addWidget(simulation);
     layout->addWidget(etats);
     setLayout(layout);


     QObject::connect(num, SIGNAL(valueChanged(int)),this,SLOT(synchronizeNumToNumBit(int)));
}

void fenetre1D::faireSimulation()
{
    /*Etat e(dimension);
    for(unsigned int i= 0;i<dimension;i++)
    {
        if (depart->item(0,i)->text()!="") e.setCellule(i,true);

    }
    const Automate& A = AutomateManager::getAutomateManager().getAutomate(num->value());
    Simulateur S(A,e);
    for(unsigned int i=0;i<dimension;i++)
    {
        S.next();
        const Etat& d=S.dernier();
        for (unsigned int j=0;j<dimension;j++)
        {
            if (d.getCellule(j))
                etats->item(i,j)->setBackgroundColor("black");
            else
                etats->item(i,j)->setBackgroundColor(("white"));

        }
    }*/

}
void fenetre1D::synchronizeNumToNumBit(int i)
{



    std::string chaine = NumToNumBit(i);
    for(int j = 0;j<8;j++)
    {
        numeroBit[j]->setText(QString(QChar(chaine[j])));
    }
}

void fenetre1D::synchronizeNumBitToNum(const QString& s)
{

    if (s == QString()) return;
    if (numeroBit[0]->text() == QString()) return;
    QString temp(numeroBit[0]->text());
    for(int i = 1;i<8;i++)
    {
        if (numeroBit[i]->text() == QString()) return;
        temp +=numeroBit[i]->text();


    }
    num->setValue(NumBitToNum(temp.toStdString()));
}

void fenetre1D::cellActivation(const QModelIndex& index)
{
    if (depart->item(0,index.column())->text()=="")
    {
        depart->item(0,index.column())->setText("_");
        depart->item(0,index.column())->setBackgroundColor("black");
        depart->item(0,index.column())->setTextColor("black");
    }
    else
    {
        depart->item(0,index.column())->setText("");
        depart->item(0,index.column())->setBackgroundColor("white");
        depart->item(0,index.column())->setTextColor("white");
    }
}

short unsigned int NumBitToNum(const std::string& num) {
    if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;
    short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

std::string NumToNumBit(short unsigned int num) {
    std::string numeroBit;
    if (num > 256) throw AutomateException("Numero d'automate indefini");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) {
            numeroBit.push_back('1');
            num -= p;
        }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;
}

/*void lancerSimulation()
{

}*/
