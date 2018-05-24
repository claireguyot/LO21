#ifndef INTERFACE_H
#define INTERFACE_H

//#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <QHeaderView>
#include <QModelIndex>

class fenetre1D : public QWidget
{
    Q_OBJECT
public:
    explicit fenetre1D(QWidget *parent = nullptr);
    void cellActivation(const QModelIndex& index);

private:
    const unsigned int maxLargeurTableau = 30;
    const unsigned int maxHauteurTableau = 30;
    const unsigned int largInit = 10;
    const unsigned int taille = 40;
    QPushButton *bSauvegarde;
    QPushButton *bChargement;
    QSpinBox *largeur;
    QSpinBox *hauteur;
    QHBoxLayout *topMenu;
    QTableWidget *selectAutomateDepart;


signals:

public slots:
};

#endif // INTERFACE_H
