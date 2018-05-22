#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>

const int maxLargeurTableau = 30;
const int maxHauteurTableau = 30;

class fenetre : public QMainWindow
{
    Q_OBJECT
public:
    explicit fenetre(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // INTERFACE_H
